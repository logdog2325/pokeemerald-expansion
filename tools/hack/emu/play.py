#!/usr/bin/env python3
"""
play.py - scripted smoke tests on the real ROM (wraps tools/hack/emu/gbarun).

  python3 tools/hack/emu/play.py script.play -o outdir [--rom pokeemerald.gba]

A .play script is a gbarun script plus:
  @SYMBOL / @@SYMBOL      address of SYMBOL from the ELF (@@ = Thumb function pointer, |1)
  newgame [MAX]           Quickstart a new game (tap SELECT until the overworld runs)
  mash KEY MAX            tap KEY until the player regains control (script ends);
                          KEY may be a cycle like A,UP (answers YES to a NO-default prompt)
  wait_free MAX           run until the player regains control, pressing nothing
  choose N [MAX]          tap A until a dynmultichoice menu opens, then pick entry N (0 = first)
  flag NAME               print a flag (FLAG_*) from the save block
  var NAME                print a var (VAR_*) from the save block
  expect_flag NAME 0|1    like flag, but fails the run on mismatch
  expect_var NAME VALUE   like var, but fails the run on mismatch
  expect_trainer TRAINER_X 0|1   the trainer's "defeated" flag (TRAINER_FLAGS_START + id)
  expect_item ITEM_X 0|1  whether ITEM_X is anywhere in the bag (all pockets are scanned)
  expect_gfx OBJ_EVENT_GFX_X   the player's current object graphics (outfit, gender, avatar state)
  expect_opponent TRAINER_X   the last trainer battle's opponent A (kept until the next battle is set
                          up; works when a mashed battle is lost, unlike expect_trainer)
  setflag NAME / clearflag NAME   change a flag in the save block (e.g. FLAG_DEBUG_NO_ENCOUNTER)
  settrainer TRAINER_X 0|1        set or clear a trainer's "defeated" flag
  setvar NAME VALUE       change a var in the save block
  mapid                   print the current map group/num (gSaveBlock1Ptr->location)
  walk DIR COORD [MAX]    hold DIR until the player's x (LEFT/RIGHT) or y (UP/DOWN) is COORD
  pos                     print the player's map coordinates (+7 MAP_OFFSET)
  path MAP X0 Y0 X1 Y1    walk from (X0,Y0) to (X1,Y1) on MAP along the shortest path over
                          walkable cells (collision 0), avoiding tall grass/water/warps when
                          it can; jumps down ledges; ignores NPCs. Expands to walk commands.
  savestate/loadstate F   relative paths are inside the output directory
  gender M|F              set the player's gender (the sprite follows on the next map load)
  warp MAP_X X Y [MAX]    debug builds: warp to (X, Y) on MAP_X the next time the player is free
  heal                    debug builds: heal the party the next time the player is free
  givemon SPECIES_X LEVEL [ITEM_X]   debug builds: add a Pokemon (holding ITEM_X) to the party the next
                          time the player is free
  giveitem ITEM_X         debug builds: add one ITEM_X to the bag the next time the player is free
  expect_party SLOT SPECIES_X   the species in party slot SLOT (0 = first; decrypts the box data)
  default NAME VALUE      default for ${NAME}; override with -D NAME=VALUE on the command line
Lines are otherwise passed to gbarun unchanged (run/press/hold/repeat/shot/savestate/...).
Exit code 1 if an expectation fails or an "until" times out.
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
GBARUN = os.path.join(ROOT, "tools/hack/emu/gbarun")


def symbols(elf):
    out = subprocess.run(["arm-none-eabi-nm", elf], capture_output=True, text=True, check=True).stdout
    syms = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 3:
            syms.setdefault(parts[2], int(parts[0], 16))
    # release builds use LTO, which renames file-local symbols (sLockFieldControls.lto_priv.0)
    for name, addr in list(syms.items()):
        base = name.split(".lto_priv.")[0]
        if base != name:
            syms.setdefault(base, addr)
    return syms


def probe(names, debug_hook=False):
    """Evaluate C constants (and SaveBlock1 offsets) with the project's own headers."""
    src = '#include "global.h"\n#include "constants/flags.h"\n#include "constants/vars.h"\n#include "constants/maps.h"\n'
    src += '#include "constants/items.h"\n#include "constants/opponents.h"\n#include "battle_setup.h"\n'
    src += '#include "constants/event_objects.h"\n#include "pokemon.h"\n'
    if debug_hook:
        src += '#include "draconid.h"\n'
    src += "const u32 gProbe[] = {\n  offsetof(struct SaveBlock1, flags),\n  offsetof(struct SaveBlock1, vars),\n"
    src += "  offsetof(struct SaveBlock1, location),\n"
    src += "  offsetof(struct ObjectEvent, currentCoords),\n"
    for n in names:
        src += "  (u32)(%s),\n" % n
    src += "};\n"
    with tempfile.TemporaryDirectory() as td:
        c = os.path.join(td, "probe.c")
        o = os.path.join(td, "probe.o")
        open(c, "w").write(src)
        subprocess.run(["arm-none-eabi-gcc", "-mthumb", "-mabi=apcs-gnu", "-O1", "-std=gnu17", "-DMODERN=1", "-DEMERALD", "-DTESTING=0",
                        "-iquote", os.path.join(ROOT, "include"),
                        "-c", c, "-o", o], check=True, capture_output=True, text=True)
        dump = subprocess.run(["arm-none-eabi-objdump", "-s", "-j", ".rodata", o], capture_output=True,
                              text=True, check=True).stdout
    data = b""
    for line in dump.splitlines():
        m = re.match(r"^\s*[0-9a-f]+ ((?:[0-9a-f]{8} ?){1,4})", line)
        if m:
            data += bytes.fromhex(m.group(1).replace(" ", ""))
    vals = [int.from_bytes(data[i * 4:i * 4 + 4], "little") for i in range(4 + len(names))]
    return vals[0], vals[1], vals[2], vals[3], dict(zip(names, vals[4:]))


AVOID = ("MB_TALL_GRASS", "MB_LONG_GRASS", "MB_DEEP_SAND", "MB_ASHGRASS")


def plan_path(map_name, x0, y0, x1, y1):
    """Straight-line walk segments [(DIR, COORD)] from (x0, y0) to (x1, y1) on map_name."""
    import heapq
    sys.path.insert(0, os.path.join(ROOT, "tools/hack/mapgen"))
    import pokemap
    os.chdir(ROOT)
    proj = pokemap.Project()
    mj = proj.map_json(map_name)
    lay = proj.layout(mj["layout"])
    pair = proj.pair_for_layout(lay)
    names = pokemap.behavior_names()
    warps = {(w["x"], w["y"]) for w in mj.get("warp_events") or []}

    def behavior(x, y):
        return names[pair.behavior(lay.block(x, y) & 0x3FF)] or ""

    def cost(x, y):
        b = lay.block(x, y)
        if (b >> 10) & 3:
            return None
        name = behavior(x, y)
        if name.startswith("MB_JUMP_"):
            return None  # ledges are crossed by the jump rule below
        if "WATER" in name or "WATERFALL" in name:
            return None
        if (x, y) in warps and (x, y) != (x1, y1):
            return 400
        return 60 if name in AVOID else 1

    dist = {(x0, y0): 0}
    prev = {}
    heap = [(0, x0, y0, None)]
    moves = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}
    while heap:
        d, x, y, last = heapq.heappop(heap)
        if (x, y) == (x1, y1):
            break
        if d > dist.get((x, y), 1 << 30):
            continue
        for dname, (dx, dy) in moves.items():
            nx, ny = x + dx, y + dy
            if not (0 <= nx < lay.width and 0 <= ny < lay.height):
                continue
            # a ledge facing this way: the player jumps over it and lands one tile further
            if behavior(nx, ny) == LEDGE_JUMP.get(dname):
                nx, ny = nx + dx, ny + dy
                if not (0 <= nx < lay.width and 0 <= ny < lay.height):
                    continue
            c = cost(nx, ny)
            if c is None:
                continue
            nd = d + c + (0 if dname == last else 2)  # prefer fewer turns
            if nd < dist.get((nx, ny), 1 << 30):
                dist[(nx, ny)] = nd
                prev[(nx, ny)] = (x, y, dname)
                heapq.heappush(heap, (nd, nx, ny, dname))
    if (x1, y1) not in prev and (x1, y1) != (x0, y0):
        sys.exit("path: no route on %s from (%d,%d) to (%d,%d)" % (map_name, x0, y0, x1, y1))
    steps = []
    cur = (x1, y1)
    while cur != (x0, y0):
        px, py, dname = prev[cur]
        steps.append((dname, cur))
        cur = (px, py)
    steps.reverse()
    segs = []
    for dname, (x, y) in steps:
        coord = x if dname in ("LEFT", "RIGHT") else y
        if segs and segs[-1][0] == dname:
            segs[-1] = (dname, coord)
        else:
            segs.append((dname, coord))
    return segs


GFX_OFFSET = "offsetof(struct ObjectEvent, graphicsId)"
OPPONENT_A_OFFSET = "offsetof(struct _TrainerBattleParameter, opponentA)"
BAG_OFFSET, SLOT_SIZE, BAG_SIZE = "offsetof(struct SaveBlock1, bag)", "sizeof(struct ItemSlot)", "sizeof(struct Bag)"
# party decoding (expect_party) and the debug hook's give requests (givemon / giveitem)
MON_SIZE, SECURE_OFFSET, SUBSTRUCT_SIZE = "sizeof(struct Pokemon)", "offsetof(struct BoxPokemon, secure)", "NUM_SUBSTRUCT_BYTES"
GIVE_FIELDS = ("offsetof(struct DraconidTestWarp, species)", "offsetof(struct DraconidTestWarp, level)",
               "offsetof(struct DraconidTestWarp, item)", "DRACONID_TEST_GIVE_MON", "DRACONID_TEST_GIVE_ITEM")
SUBSTRUCT0_POS = [0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3]  # pokemon.c sSubstructOffsets[0]

LEDGE_JUMP = {"DOWN": "MB_JUMP_SOUTH", "UP": "MB_JUMP_NORTH", "LEFT": "MB_JUMP_WEST", "RIGHT": "MB_JUMP_EAST"}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("script")
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("--rom", default=os.path.join(ROOT, "pokeemerald.gba"))
    ap.add_argument("-D", dest="defines", action="append", default=[], help="NAME=VALUE for ${NAME}")
    args = ap.parse_args()
    elf = os.path.splitext(args.rom)[0] + ".elf"
    syms = symbols(elf)
    lines = open(args.script).read().splitlines()
    defines = {}
    for l in lines:
        t = l.split()
        if len(t) == 3 and t[0] == "default":
            defines.setdefault(t[1], t[2])
    defines.update(dict(d.split("=", 1) for d in args.defines))
    lines = [re.sub(r"\$\{(\w+)\}", lambda m: defines[m.group(1)], l) for l in lines if not l.startswith("default ")]
    names = sorted({l.split()[1] for l in lines if l.split() and l.split()[0] in ("flag", "var", "expect_flag", "expect_var", "setflag", "clearflag", "setvar", "warp", "expect_trainer", "expect_item", "expect_opponent", "expect_gfx", "givemon", "giveitem", "settrainer")})
    names += sorted({l.split()[2] for l in lines if l.split() and l.split()[0] == "expect_party"})
    names += sorted({l.split()[3] for l in lines if l.split() and l.split()[0] == "givemon" and len(l.split()) > 3})
    names += [OPPONENT_A_OFFSET, GFX_OFFSET]
    names += [BAG_OFFSET, SLOT_SIZE, BAG_SIZE, "TRAINER_FLAGS_START", MON_SIZE, SECURE_OFFSET, SUBSTRUCT_SIZE]
    debug_hook = any(l.split() and l.split()[0] in ("givemon", "giveitem") for l in lines)
    if debug_hook:
        names += list(GIVE_FIELDS)
    flags_off, vars_off, loc_off, coords_off, consts = probe(names, debug_hook)
    # the player is object event 0 (spawned first on every map load); MAP_OFFSET is 7
    player_x = syms["gObjectEvents"] + coords_off
    player_y = player_x + 2
    sb1 = "*%X" % syms["gSaveBlock1Ptr"]
    expects = []
    item_checks = {}  # label -> [item name, item id, wanted, found]
    party_checks = {}  # label -> [species name, species id, slot, {word key: value}]

    def sym(m):
        name = m.group(2)
        if name not in syms:
            sys.exit("unknown symbol " + name)
        return "%X" % (syms[name] | (1 if m.group(1) == "@@" else 0))

    out = []
    for l in lines:
        t = l.split()
        if not t or t[0].startswith("#"):
            continue
        if t[0] == "newgame":
            mx = t[1] if len(t) > 1 else "20000"
            out.append("until %X 4 %X %s SELECT 20" % (syms["gMain"] + 4, syms["CB2_Overworld"] | 1, mx))
            out.append("run 60")
        elif t[0] == "mash":
            # press once so a script can start, then keep tapping until control returns
            out.append("press %s 4 20" % t[1].split(",")[0])
            out.append("until %X 1 0 %s %s 24" % (syms["sLockFieldControls"], t[2], t[1]))
            out.append("run 8")
        elif t[0] == "choose":
            # sDynamicMenuEventScratchPad (src/script_menu.c) is allocated while a dynmultichoice is open
            out.append("until %X 4 !0 %s A 24" % (syms["sDynamicMenuEventScratchPad"], t[2] if len(t) > 2 else "20000"))
            out.append("run 20")
            for _ in range(int(t[1])):
                out.append("press DOWN 2 12")
            out.append("press A 2 20")
        elif t[0] == "wait_free":
            out.append("run 8")
            out.append("until %X 1 0 %s" % (syms["sLockFieldControls"], t[1]))
        elif t[0] in ("flag", "expect_flag"):
            f = consts[t[1]]
            label = t[1]
            if t[0] == "expect_flag":
                label = "%s#%d" % (t[1], len(expects))
                expects.append((label, int(t[2])))
            out.append("read %s+%X 1 %s>>%d" % (sb1, flags_off + f // 8, label, f % 8))
        elif t[0] == "expect_trainer":
            f = consts["TRAINER_FLAGS_START"] + consts[t[1]]
            label = "%s#%d" % (t[1], len(expects))
            expects.append((label, int(t[2])))
            out.append("read %s+%X 1 %s>>%d" % (sb1, flags_off + f // 8, label, f % 8))
        elif t[0] == "expect_opponent":
            label = "opponent_%s#%d" % (t[1], len(expects))
            expects.append((label, consts[t[1]]))
            out.append("read %X 2 %s" % (syms["gTrainerBattleParameter"] + consts[OPPONENT_A_OFFSET], label))
        elif t[0] == "expect_gfx":
            label = "player_gfx_%s#%d" % (t[1], len(expects))
            expects.append((label, consts[t[1]]))
            out.append("read %X 2 %s" % (syms["gObjectEvents"] + consts[GFX_OFFSET], label))
        elif t[0] == "expect_item":
            label = "item%d" % len(item_checks)
            item_checks[label] = [t[1], consts[t[1]], int(t[2]), False]
            for off in range(0, consts[BAG_SIZE], consts[SLOT_SIZE]):
                out.append("read %s+%X 2 %s" % (sb1, consts[BAG_OFFSET] + off, label))
        elif t[0] == "settrainer":
            f = consts["TRAINER_FLAGS_START"] + consts[t[1]]
            out.append("pokebit %s+%X %d %d" % (sb1, flags_off + f // 8, f % 8, int(t[2])))
        elif t[0] in ("setflag", "clearflag"):
            f = consts[t[1]]
            out.append("pokebit %s+%X %d %d" % (sb1, flags_off + f // 8, f % 8, 1 if t[0] == "setflag" else 0))
        elif t[0] == "setvar":
            v, val = consts[t[1]], int(t[2], 0)
            addr = vars_off + (v - 0x4000) * 2
            out.append("poke %s+%X %X" % (sb1, addr, val & 0xFF))
            out.append("poke %s+%X %X" % (sb1, addr + 1, val >> 8))
        elif t[0] in ("var", "expect_var"):
            v = consts[t[1]]
            label = t[1]
            if t[0] == "expect_var":
                label = "%s#%d" % (t[1], len(expects))
                expects.append((label, int(t[2], 0)))
            out.append("read %s+%X 2 %s" % (sb1, vars_off + (v - 0x4000) * 2, label))
        elif t[0] == "walk":
            # walk DIR COORD: hold DIR until the player's x (LEFT/RIGHT) or y (UP/DOWN) equals COORD
            addr = player_x if t[1] in ("LEFT", "RIGHT") else player_y
            out.append("untilhold %X 2 %X %s %s" % (addr, int(t[2]) + 7, t[3] if len(t) > 3 else "900", t[1]))
        elif t[0] == "path":
            for dname, coord in plan_path(t[1], *map(int, t[2:6])):
                addr = player_x if dname in ("LEFT", "RIGHT") else player_y
                out.append("untilhold %X 2 %X 900 %s" % (addr, coord + 7, dname))
        elif t[0] == "warp":
            # debug builds only: src/draconid.c Draconid_TryTestWarp picks this up when the player is free
            if "gDraconidTestWarp" not in syms:
                sys.exit("warp: gDraconidTestWarp not in the ELF (release build?)")
            w, m = syms["gDraconidTestWarp"], consts[t[1]]
            out.append("poke %X %X" % (w + 1, m >> 8))
            out.append("poke %X %X" % (w + 2, m & 0xFF))
            out.append("poke %X %X" % (w + 3, int(t[2])))
            out.append("poke %X %X" % (w + 4, int(t[3])))
            out.append("poke %X 1" % w)  # DRACONID_TEST_WARP
            out.append("run 30")
            out.append("until %X 1 0 %s" % (syms["sLockFieldControls"], t[4] if len(t) > 4 else "900"))
            out.append("run 20")
        elif t[0] == "heal":
            # debug builds only: HealPlayerParty() the next time the player is free
            out.append("poke %X 2" % syms["gDraconidTestWarp"])  # DRACONID_TEST_HEAL
            out.append("run 10")
        elif t[0] in ("givemon", "giveitem"):
            # debug builds only: Draconid_TryTestWarp gives the Pokemon / item when the player is free
            if "gDraconidTestWarp" not in syms:
                sys.exit("%s: gDraconidTestWarp not in the ELF (release build?)" % t[0])
            w = syms["gDraconidTestWarp"]
            if t[0] == "givemon":
                sp = consts[t[1]]
                out.append("poke %X %X" % (w + consts[GIVE_FIELDS[0]], sp & 0xFF))
                out.append("poke %X %X" % (w + consts[GIVE_FIELDS[0]] + 1, sp >> 8))
                out.append("poke %X %X" % (w + consts[GIVE_FIELDS[1]], int(t[2])))
                held = consts[t[3]] if len(t) > 3 else 0
                out.append("poke %X %X" % (w + consts[GIVE_FIELDS[2]], held & 0xFF))
                out.append("poke %X %X" % (w + consts[GIVE_FIELDS[2]] + 1, held >> 8))
                out.append("poke %X %X" % (w, consts[GIVE_FIELDS[3]]))
            else:
                it = consts[t[1]]
                out.append("poke %X %X" % (w + consts[GIVE_FIELDS[2]], it & 0xFF))
                out.append("poke %X %X" % (w + consts[GIVE_FIELDS[2]] + 1, it >> 8))
                out.append("poke %X %X" % (w, consts[GIVE_FIELDS[4]]))
            out.append("until %X 1 0 900" % w)  # the hook has taken the request (a later one would overwrite it)
            out.append("run 10")
        elif t[0] == "expect_party":
            # gParties[B_TRAINER_PLAYER] (index 0) slot N: personality, OT id and the encrypted substructs
            label = "party%d" % len(party_checks)
            party_checks[label] = [t[2], consts[t[2]], int(t[1]), {}]
            base = syms["gParties"] + int(t[1]) * consts[MON_SIZE]
            out.append("read %X 4 %s_p" % (base, label))
            out.append("read %X 4 %s_o" % (base + 4, label))
            for i in range(consts[SUBSTRUCT_SIZE]):  # all four substructs, one u32 each (12 bytes = 3 words each)
                out.append("read %X 4 %s_w%d" % (base + consts[SECURE_OFFSET] + 4 * i, label, i))
        elif t[0] == "gender":
            g = 0 if t[1].upper().startswith("M") else 1
            out.append("poke *%X+8 %X" % (syms["gSaveBlock2Ptr"], g))
        elif t[0] == "pos":
            out.append("read %X 2 player_x+7" % player_x)
            out.append("read %X 2 player_y+7" % player_y)
        elif t[0] == "mapid":
            out.append("read %s+%X 2 map_group_num" % (sb1, loc_off))
        elif t[0] in ("savestate", "loadstate", "shot") and len(t) > 1 and not os.path.isabs(t[1]) and t[0] != "shot":
            # relative savestates live in the output directory
            out.append("%s %s" % (t[0], os.path.abspath(os.path.join(args.out, t[1]))))
        else:
            out.append(re.sub(r"(@@?)([A-Za-z_]\w*)", sym, l))
    os.makedirs(args.out, exist_ok=True)
    gs = os.path.join(args.out, "_gbarun.txt")
    open(gs, "w").write("\n".join(out) + "\n")
    res = subprocess.run([GBARUN, args.rom, gs, args.out], capture_output=True, text=True)
    ok = True
    for line in res.stdout.splitlines():
        m = re.match(r"read (\S+?)(?:>>(\d))? = 0x([0-9A-F]+)", line)
        if m and m.group(1).split("_")[0] in party_checks:
            prefix, key = m.group(1).split("_", 1)
            party_checks[prefix][3][key] = int(m.group(3), 16)
            continue  # reported after the run
        if m and m.group(1) in item_checks:
            check = item_checks[m.group(1)]
            check[3] |= int(m.group(3), 16) == check[1]
            continue  # reported after the run
        if m:
            name, bit, val = m.group(1), m.group(2), int(m.group(3), 16)
            if bit is not None:
                val = (val >> int(bit)) & 1
            line = "%s = %d" % (name.split("#")[0], val)
            for n, want in expects:
                if n == name and val != want:
                    line += "   <-- EXPECTED %d" % want
                    ok = False
        if "TIMEOUT" in line:
            ok = False
        print(line)
    for check in item_checks.values():
        line = "%s in bag = %d" % (check[0], check[3])
        if int(check[3]) != check[2]:
            line += "   <-- EXPECTED %d" % check[2]
            ok = False
        print(line)
    for name, want, slot, words in party_checks.values():
        pers, otid = words.get("p", 0), words.get("o", 0)
        pos = SUBSTRUCT0_POS[pers % 24] * consts[SUBSTRUCT_SIZE] // 4
        species = (words.get("w%d" % pos, 0) ^ pers ^ otid) & 0x7FF  # PokemonSubstruct0.species:11
        line = "party slot %d species = %d (%s = %d)" % (slot, species, name, want)
        if species != want:
            line += "   <-- EXPECTED %s" % name
            ok = False
        print(line)
    if res.stderr.strip():
        print(res.stderr.strip(), file=sys.stderr)
    sys.exit(0 if ok and res.returncode == 0 else 1)


if __name__ == "__main__":
    main()
