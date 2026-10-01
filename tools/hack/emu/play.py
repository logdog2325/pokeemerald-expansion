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
  expect_opponent_b TRAINER_X   the same for opponent B of the last two-trainer battle (multi, double)
  expect_partner PARTNER_X      the last multi battle's in-game partner (gPartnerTrainerId)
  expect_roamer N SPECIES_X     roamer slot N (gSaveBlock1Ptr->roamer[N]) is active and SPECIES_X
  wait_species N SPECIES_X [MAX] [KEY]   tap KEY (default A) until battler N (gBattleMons[N]; 1 = the
                          opponent in a single battle) is SPECIES_X, e.g. a Mega Evolution
  expect_wild MAP_X [FIELD]   during a wild battle: the opponent (gBattleMons[1]) is one of the species of MAP_X's
                          FIELD table (default land_mons) in src/data/wild_encounters.json
  battlepp N [VALUE]      during a battle: the PP of battler N's four moves (gBattleMons[N]) to VALUE (default 64)
  battlehp N [VALUE]      during a battle: battler N's current HP (gBattleMons[N].hp) to VALUE (default 1) – a
                          mashed boss battle that must be won (memory only; the party files stay as written)
  wait_gimmick N GIMMICK_X [MAX] [KEY]   tap KEY (default A) until battler N's trainer has used GIMMICK_X in this battle
                          (gBattleStruct->gimmick.activated[N][GIMMICK_X], e.g. GIMMICK_Z_MOVE: the Z-Move is starting)
  battlemon N FIELD VALUE   during a battle: one stat of battler N (gBattleMons[N]: hp, maxHP, attack, defense, speed,
                          spAttack, spDefense), e.g. speed 999 once a slow Pokemon has let the opponent show its move
  monstat SLOT FIELD VALUE   one unencrypted field of the player's party Pokemon at SLOT (level, hp, maxHP, attack,
                          defense, speed, spAttack, spDefense), e.g. after boost: speed 1 so the opponent moves first
  boost SLOT [VALUE]      set the player's party Pokemon at SLOT to level 100 with VALUE (default 999) HP and
                          stats, for a flow test that must win (999) or quickly lose (1) a battle (the
                          unencrypted party fields; a level-up or a stat recalculation undoes it)
  until_var NAME VALUE MAX [KEYS]   run until a var equals VALUE, tapping KEYS (a cycle like B,R) meanwhile
  wait_opponent TRAINER_X [MAX] [KEY]   tap KEY (default A) until the trainer battle being set up is against
                          TRAINER_X (opponent A), e.g. the next battle of a gauntlet; stops before it starts
  setflag NAME / clearflag NAME   change a flag in the save block (e.g. FLAG_DEBUG_NO_ENCOUNTER)
  settrainer TRAINER_X 0|1        set or clear a trainer's "defeated" flag
  setvar NAME VALUE       change a var in the save block
  mapid                   print the current map group/num (gSaveBlock1Ptr->location)
  walk DIR COORD [MAX]    hold DIR until the player's x (LEFT/RIGHT) or y (UP/DOWN) is COORD
  pos                     print the player's map coordinates (+7 MAP_OFFSET)
  path MAP X0 Y0 X1 Y1    walk from (X0,Y0) to (X1,Y1) on MAP along the shortest path over
                          walkable cells (collision 0), avoiding tall grass/water/warps when
                          it can; jumps down ledges; ignores NPCs. Expands to walk commands.
  savestate/loadstate F   relative paths are inside the output directory; each savestate gets a F.rom stamp (the
                          ROM's SHA-1), and loading one made by another ROM build prints a WARNING – rebuild the
                          chain (opening.play → …) after every build
  gender M|F              set the player's gender (the sprite follows on the next map load)
  warp MAP_X X Y [MAX]    debug builds: warp to (X, Y) on MAP_X the next time the player is free
  heal                    debug builds: heal the party the next time the player is free
  giveitem ITEM_X [N]     debug builds: put N (default 1) ITEM_X in the bag the next time the player is free
  callscript LABEL        debug builds: run the event script LABEL (a ROM symbol) the next time the player is free
  givemon SPECIES_X LEVEL [ITEM_X]   debug builds: add a Pokémon (level-up moves, holding ITEM_X) to the party
                          the next time the player is free
  expect_party_hms N      debug builds: how many HM moves the party's Pokémon know (IsMoveHM)
  expect_party SLOT SPECIES_X   the species in party slot SLOT (0 = first; decrypts the box data)
  expect_text LABEL [BUFFER]    the text now in BUFFER (default gStringVar4) starts like the ROM text LABEL
                          (up to 24 bytes, stopping at its first placeholder such as {PLAYER}; e.g. a PokéNav call)
  expect_pos X Y          the player's map coordinates (without MAP_OFFSET)
  expect_map MAP_X        the current map (gSaveBlock1Ptr->location)
  bagcursor POCKET_X N    the bag opens on pocket POCKET_X with the cursor on its entry N (0 = first), and the
                          start menu on its first entry (then START, DOWN, DOWN, A opens the bag once the
                          POKéDEX and POKéMON entries are there)
  default NAME VALUE      default for ${NAME}; override with -D NAME=VALUE on the command line
Lines are otherwise passed to gbarun unchanged (run/press/hold/repeat/shot/savestate/...).
Exit code 1 if an expectation fails or an "until" times out.
"""

import argparse
import hashlib
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
GBARUN = os.path.join(ROOT, "tools/hack/emu/gbarun")
GBARUN_CRASHED = 3  # gbarun's CRASH_EXIT_CODE: the game crashed (usually a savestate from another ROM build)


def rom_stamp(rom):
    """SHA-1 of the ROM: written next to every savestate (F.rom) and checked when one is loaded."""
    return hashlib.sha1(open(rom, "rb").read()).hexdigest()


def check_savestate(path, rom, stamp):
    """A warning (or None) when the savestate PATH wasn't made by this ROM build."""
    try:
        made_by = open(path + ".rom").read().strip()
    except OSError:
        made_by = None
    if made_by is not None:
        if made_by != stamp:
            return "savestate %s was made by another ROM build (%s, this ROM %s)" % (path, made_by[:10], stamp[:10])
        return None
    if os.path.exists(path) and os.path.getmtime(path) < os.path.getmtime(rom):
        return "savestate %s is older than the ROM and has no .rom stamp" % path
    return None


def wild_species(map_name, field):
    """The SPECIES_* constants of MAP_X's FIELD table (the Emerald one, gWildMonHeaders) in wild_encounters.json."""
    import json
    data = json.load(open(os.path.join(ROOT, "src/data/wild_encounters.json")))
    for group in data["wild_encounter_groups"]:
        if group["label"] != "gWildMonHeaders":
            continue
        for enc in group["encounters"]:
            if enc.get("map") == map_name and not enc["base_label"].endswith(("_FireRed", "_LeafGreen")):
                if field not in enc:
                    sys.exit("expect_wild: %s has no %s table" % (map_name, field))
                return sorted({m["species"] for m in enc[field]["mons"]})
    sys.exit("expect_wild: no wild table for %s" % map_name)


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


def probe(names):
    """Evaluate C constants (and SaveBlock1 offsets) with the project's own headers."""
    src = '#include "global.h"\n#include "constants/flags.h"\n#include "constants/vars.h"\n#include "constants/maps.h"\n'
    src += '#include "constants/items.h"\n#include "constants/opponents.h"\n#include "battle_setup.h"\n'
    src += '#include "constants/event_objects.h"\n#include "draconid.h"\n#include "item_menu.h"\n#include "pokemon.h"\n'
    src += '#include "constants/battle_partner.h"\n#include "battle.h"\n#include "constants/species.h"\n'
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
OPPONENT_B_OFFSET = "offsetof(struct _TrainerBattleParameter, opponentB)"
BATTLE_MON_SIZE, BATTLE_MON_SPECIES = "sizeof(struct BattlePokemon)", "offsetof(struct BattlePokemon, species)"
BATTLE_MON_PP = "offsetof(struct BattlePokemon, pp)"
BATTLE_MON_HP = "offsetof(struct BattlePokemon, hp)"
BAG_OFFSET, SLOT_SIZE, BAG_SIZE = "offsetof(struct SaveBlock1, bag)", "sizeof(struct ItemSlot)", "sizeof(struct Bag)"
ROAMER_OFFSET, ROAMER_SIZE = "offsetof(struct SaveBlock1, roamer)", "sizeof(struct Roamer)"
ROAMER_SPECIES, ROAMER_ACTIVE = "offsetof(struct Roamer, species)", "offsetof(struct Roamer, active)"
# the debug-build test hook (include/draconid.h): only probed when a test uses giveitem / givemon / expect_party_hms
HOOK_COMMANDS = ("giveitem", "givemon", "expect_party_hms", "callscript")
TEST_ITEM_OFFSET, TEST_HMS_OFFSET = "offsetof(struct DraconidTestWarp, item)", "offsetof(struct DraconidTestWarp, partyHMMoves)"
TEST_SPECIES_OFFSET, TEST_LEVEL_OFFSET = "offsetof(struct DraconidTestWarp, species)", "offsetof(struct DraconidTestWarp, level)"
TEST_GIVE_ITEM, TEST_COUNT_HMS, TEST_GIVE_MON = "DRACONID_TEST_GIVE_ITEM", "DRACONID_TEST_COUNT_HMS", "DRACONID_TEST_GIVE_MON"
TEST_SCRIPT, TEST_SCRIPT_OFFSET = "DRACONID_TEST_SCRIPT", "offsetof(struct DraconidTestWarp, script)"
BAG_POCKET, BAG_CURSOR, BAG_SCROLL = ("offsetof(struct BagPosition, pocket)", "offsetof(struct BagPosition, cursorPosition)",
                                      "offsetof(struct BagPosition, scrollPosition)")
# party decoding (expect_party)
MON_SIZE, SECURE_OFFSET, SUBSTRUCT_SIZE = "sizeof(struct Pokemon)", "offsetof(struct BoxPokemon, secure)", "NUM_SUBSTRUCT_BYTES"
TEXT_BYTES = 24  # expect_text compares up to 24 bytes
SUBSTRUCT0_POS = [0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3]  # pokemon.c sSubstructOffsets[0]
# boost: the unencrypted party fields
MON_FIELD = "offsetof(struct Pokemon, %s)"
# wait_gimmick: whether battler N's trainer has used a gimmick (Mega Evolution, a Z-Move) in this battle
GIMMICK_FIELD = "offsetof(struct BattleStruct, gimmick.activated[%s][%s])"
BATTLE_MON_FIELD = "offsetof(struct BattlePokemon, %s)"
MON_STATS = ("level", "hp", "maxHP", "attack", "defense", "speed", "spAttack", "spDefense")

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
    names = sorted({l.split()[1] for l in lines if l.split() and l.split()[0] in ("flag", "var", "expect_flag", "expect_var", "setflag", "clearflag", "setvar", "warp", "expect_trainer", "expect_item", "expect_opponent", "expect_opponent_b", "expect_gfx", "giveitem", "givemon", "expect_map", "bagcursor", "settrainer", "until_var", "wait_opponent")})
    names += sorted({l.split()[2] for l in lines if l.split() and l.split()[0] == "expect_party"})
    names += sorted({l.split()[3] for l in lines if l.split() and l.split()[0] == "givemon" and len(l.split()) > 3})
    names += ["TRAINER_PARTNER(%s)" % l.split()[1] for l in lines if l.split()[:1] == ["expect_partner"]]
    names += [l.split()[2] for l in lines if l.split()[:1] == ["wait_species"]]
    names += [GIMMICK_FIELD % (l.split()[1], l.split()[2]) for l in lines if l.split()[:1] == ["wait_gimmick"]]
    names += [BATTLE_MON_FIELD % l.split()[2] for l in lines if l.split()[:1] == ["battlemon"]]
    if any(l.split()[:1] == ["expect_roamer"] for l in lines):
        names += [l.split()[2] for l in lines if l.split()[:1] == ["expect_roamer"]]
        names += [ROAMER_OFFSET, ROAMER_SIZE, ROAMER_SPECIES, ROAMER_ACTIVE]
    names += [OPPONENT_A_OFFSET, OPPONENT_B_OFFSET, GFX_OFFSET, BATTLE_MON_SIZE, BATTLE_MON_SPECIES, BATTLE_MON_PP, BATTLE_MON_HP]
    wild_tables = {}  # (MAP_X, field) -> its SPECIES_* constants (expect_wild)
    for l in lines:
        t = l.split()
        if t[:1] == ["expect_wild"]:
            key = (t[1], t[2] if len(t) > 2 else "land_mons")
            wild_tables.setdefault(key, wild_species(*key))
    names += sorted({sp for spp in wild_tables.values() for sp in spp})
    names += [BAG_OFFSET, SLOT_SIZE, BAG_SIZE, "TRAINER_FLAGS_START", MON_SIZE, SECURE_OFFSET, SUBSTRUCT_SIZE]
    if any(l.split() and l.split()[0] in HOOK_COMMANDS for l in lines):
        names += [TEST_ITEM_OFFSET, TEST_HMS_OFFSET, TEST_SPECIES_OFFSET, TEST_LEVEL_OFFSET,
                  TEST_GIVE_ITEM, TEST_COUNT_HMS, TEST_GIVE_MON, TEST_SCRIPT, TEST_SCRIPT_OFFSET]
    if any(l.split() and l.split()[0] == "bagcursor" for l in lines):
        names += [BAG_POCKET, BAG_CURSOR, BAG_SCROLL]
    if any(l.split() and l.split()[0] in ("boost", "monstat") for l in lines):
        names += ["B_TRAINER_PLAYER", "PARTY_SIZE"] + [MON_FIELD % f for f in MON_STATS]
    flags_off, vars_off, loc_off, coords_off, consts = probe(names)
    # the player is object event 0 (spawned first on every map load); MAP_OFFSET is 7
    player_x = syms["gObjectEvents"] + coords_off
    player_y = player_x + 2
    sb1 = "*%X" % syms["gSaveBlock1Ptr"]
    expects = []
    item_checks = {}  # label -> [item name, item id, wanted, found]
    party_checks = {}  # label -> [species name, species id, slot, {word key: value}]
    text_checks = {}  # label -> [text label, {"b<i>": RAM word, "r<i>": ROM word}]
    wild_checks = {}  # label -> [MAP_X, field, {species id: SPECIES_*}, species read or None]

    def sym(m):
        name = m.group(2)
        if name not in syms:
            sys.exit("unknown symbol " + name)
        return "%X" % (syms[name] | (1 if m.group(1) == "@@" else 0))

    out = []
    saved, loaded = [], []  # savestate files the script writes and reads
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
        elif t[0] == "expect_opponent_b":
            # opponentB sits at an odd offset of the packed struct (a halfword read would be aligned down):
            # compare it byte by byte
            addr = syms["gTrainerBattleParameter"] + consts[OPPONENT_B_OFFSET]
            for i, part in enumerate((consts[t[1]] & 0xFF, consts[t[1]] >> 8)):
                label = "opponent_b_%s_byte%d#%d" % (t[1], i, len(expects))
                expects.append((label, part))
                out.append("read %X 1 %s" % (addr + i, label))
        elif t[0] == "expect_partner":
            label = "partner_%s#%d" % (t[1], len(expects))
            expects.append((label, consts["TRAINER_PARTNER(%s)" % t[1]]))
            out.append("read %X 2 %s" % (syms["gPartnerTrainerId"], label))
        elif t[0] == "expect_roamer":
            base = consts[ROAMER_OFFSET] + int(t[1]) * consts[ROAMER_SIZE]
            label = "roamer%s_species_%s#%d" % (t[1], t[2], len(expects))
            expects.append((label, consts[t[2]]))
            out.append("read %s+%X 2 %s" % (sb1, base + consts[ROAMER_SPECIES], label))
            label = "roamer%s_active#%d" % (t[1], len(expects))
            expects.append((label, 1))
            out.append("read %s+%X 1 %s" % (sb1, base + consts[ROAMER_ACTIVE], label))
        elif t[0] == "wait_species":
            addr = syms["gBattleMons"] + int(t[1]) * consts[BATTLE_MON_SIZE] + consts[BATTLE_MON_SPECIES]
            out.append("until %X 2 %X %s %s 24" % (addr, consts[t[2]], t[3] if len(t) > 3 else "60000",
                                                  t[4] if len(t) > 4 else "A"))
        elif t[0] == "battlehp":
            addr = syms["gBattleMons"] + int(t[1]) * consts[BATTLE_MON_SIZE] + consts[BATTLE_MON_HP]
            value = int(t[2]) if len(t) > 2 else 1
            out.append("poke %X %X" % (addr, value & 0xFF))
            out.append("poke %X %X" % (addr + 1, value >> 8))
        elif t[0] == "wait_gimmick":
            # gBattleStruct is allocated per battle: read through the pointer
            off = consts[GIMMICK_FIELD % (t[1], t[2])]
            out.append("until *%X+%X 1 1 %s %s 24" % (syms["gBattleStruct"], off, t[3] if len(t) > 3 else "60000",
                                                     t[4] if len(t) > 4 else "A"))
        elif t[0] == "battlemon":
            addr, val = syms["gBattleMons"] + int(t[1]) * consts[BATTLE_MON_SIZE] + consts[BATTLE_MON_FIELD % t[2]], int(t[3])
            out.append("poke %X %X" % (addr, val & 0xFF))
            out.append("poke %X %X" % (addr + 1, val >> 8))
        elif t[0] == "monstat":
            mon = syms["gParties"] + (consts["B_TRAINER_PLAYER"] * consts["PARTY_SIZE"] + int(t[1])) * consts[MON_SIZE]
            addr, val = mon + consts[MON_FIELD % t[2]], int(t[3])
            out.append("poke %X %X" % (addr, val & 0xFF))
            if t[2] != "level":
                out.append("poke %X %X" % (addr + 1, val >> 8))
        elif t[0] == "expect_wild":
            # the wild opponent (battler 1) is one of the species of the map's table
            key = (t[1], t[2] if len(t) > 2 else "land_mons")
            label = "wild%d" % len(wild_checks)
            wild_checks[label] = [key[0], key[1], {consts[sp]: sp for sp in wild_tables[key]}, None]
            addr = syms["gBattleMons"] + consts[BATTLE_MON_SIZE] + consts[BATTLE_MON_SPECIES]
            out.append("read %X 2 %s" % (addr, label))
        elif t[0] == "battlepp":
            # gBattleMons[N].pp[0..3] = VALUE: a long mashed battle must not run the lead's first move out of PP
            # ("There's no PP left for this move!" and mashing A picks it again forever)
            addr = syms["gBattleMons"] + int(t[1]) * consts[BATTLE_MON_SIZE] + consts[BATTLE_MON_PP]
            for i in range(4):
                out.append("poke %X %X" % (addr + i, int(t[2]) if len(t) > 2 else 64))
        elif t[0] == "boost":
            mon = syms["gParties"] + (consts["B_TRAINER_PLAYER"] * consts["PARTY_SIZE"] + int(t[1])) * consts[MON_SIZE]
            value = int(t[2]) if len(t) > 2 else 999
            for f in MON_STATS:
                addr, val = mon + consts[MON_FIELD % f], 100 if f == "level" else value
                out.append("poke %X %X" % (addr, val & 0xFF))
                if f != "level":
                    out.append("poke %X %X" % (addr + 1, val >> 8))
        elif t[0] == "wait_opponent":
            # a scene with several battles in a row: stop when the next one is set up (before it starts)
            addr = syms["gTrainerBattleParameter"] + consts[OPPONENT_A_OFFSET]
            out.append("until %X 2 %X %s %s 24" % (addr, consts[t[1]], t[2] if len(t) > 2 else "60000",
                                                  t[3] if len(t) > 3 else "A"))
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
        elif t[0] == "until_var":
            v = consts[t[1]]
            keys = " %s 24" % t[4] if len(t) > 4 else ""
            out.append("until %s+%X 2 %X %s%s" % (sb1, vars_off + (v - 0x4000) * 2, int(t[2], 0), t[3], keys))
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
        elif t[0] == "giveitem":
            # debug builds only: Draconid_TryTestWarp adds the item when the player is free
            w, item = syms["gDraconidTestWarp"], consts[t[1]]
            for _ in range(int(t[2]) if len(t) > 2 else 1):
                out.append("poke %X %X" % (w + consts[TEST_ITEM_OFFSET], item & 0xFF))
                out.append("poke %X %X" % (w + consts[TEST_ITEM_OFFSET] + 1, item >> 8))
                out.append("poke %X %X" % (w, consts[TEST_GIVE_ITEM]))
                out.append("until %X 1 0 900" % w)  # the hook took the request
        elif t[0] == "givemon":
            # debug builds only: Draconid_TryTestWarp gives the Pokémon (holding ITEM_X) when the player is free
            w, species = syms["gDraconidTestWarp"], consts[t[1]]
            held = consts[t[3]] if len(t) > 3 else 0
            out.append("poke %X %X" % (w + consts[TEST_SPECIES_OFFSET], species & 0xFF))
            out.append("poke %X %X" % (w + consts[TEST_SPECIES_OFFSET] + 1, species >> 8))
            out.append("poke %X %X" % (w + consts[TEST_LEVEL_OFFSET], int(t[2])))
            out.append("poke %X %X" % (w + consts[TEST_ITEM_OFFSET], held & 0xFF))
            out.append("poke %X %X" % (w + consts[TEST_ITEM_OFFSET] + 1, held >> 8))
            out.append("poke %X %X" % (w, consts[TEST_GIVE_MON]))
            out.append("until %X 1 0 900" % w)  # the hook has taken the request (a later one would overwrite it)
            out.append("run 10")
        elif t[0] == "callscript":
            # debug builds only: Draconid_TryTestWarp starts the script when the player is free
            w, addr = syms["gDraconidTestWarp"], syms[t[1]]
            for i in range(4):
                out.append("poke %X %X" % (w + consts[TEST_SCRIPT_OFFSET] + i, (addr >> (8 * i)) & 0xFF))
            out.append("poke %X %X" % (w, consts[TEST_SCRIPT]))
            out.append("until %X 1 0 900" % w)  # the hook has started it
        elif t[0] == "expect_party_hms":
            # debug builds only: Draconid_TryTestWarp counts the party's HM moves when the player is free
            w = syms["gDraconidTestWarp"]
            label = "party_hm_moves#%d" % len(expects)
            expects.append((label, int(t[1])))
            out.append("poke %X FF" % (w + consts[TEST_HMS_OFFSET]))
            out.append("poke %X %X" % (w, consts[TEST_COUNT_HMS]))
            out.append("until %X 1 0 900" % w)
            out.append("read %X 1 %s" % (w + consts[TEST_HMS_OFFSET], label))
        elif t[0] == "bagcursor":
            # the bag and the start menu remember their cursors (gBagPosition, sStartMenuCursorPos)
            bag, pocket, entry = syms["gBagPosition"], consts[t[1]], int(t[2])
            out.append("poke %X %X" % (bag + consts[BAG_POCKET], pocket))
            for field, value in ((BAG_CURSOR, entry), (BAG_SCROLL, 0)):
                addr = bag + consts[field] + 2 * pocket
                out.append("poke %X %X" % (addr, value & 0xFF))
                out.append("poke %X %X" % (addr + 1, value >> 8))
            out.append("poke %X 0" % syms["sStartMenuCursorPos"])
        elif t[0] == "expect_pos":
            for axis, addr, coord in (("x", player_x, t[1]), ("y", player_y, t[2])):
                label = "player_%s+7#%d" % (axis, len(expects))
                expects.append((label, int(coord) + 7))
                out.append("read %X 2 %s" % (addr, label))
        elif t[0] == "expect_map":
            # location is {s8 mapGroup, s8 mapNum}; MAP_X constants are (group << 8) | num
            m = consts[t[1]]
            label = "map_%s#%d" % (t[1], len(expects))
            expects.append((label, (m >> 8) | ((m & 0xFF) << 8)))
            out.append("read %s+%X 2 %s" % (sb1, loc_off, label))
        elif t[0] == "expect_text":
            # compare the first TEXT_BYTES bytes of the buffer (RAM) and of the text label (ROM)
            label = "text%d" % len(text_checks)
            text_checks[label] = [t[1], {}]
            buf = syms[t[2] if len(t) > 2 else "gStringVar4"]
            for i in range(TEXT_BYTES):  # byte reads: text labels aren't word-aligned (the bus would rotate)
                out.append("read %X 1 %s_b%d" % (buf + i, label, i))
                out.append("read %X 1 %s_r%d" % (syms[t[1]] + i, label, i))
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
        elif t[0] in ("savestate", "loadstate") and len(t) > 1:
            # relative savestates live in the output directory
            path = t[1] if os.path.isabs(t[1]) else os.path.abspath(os.path.join(args.out, t[1]))
            (saved if t[0] == "savestate" else loaded).append(path)
            out.append("%s %s" % (t[0], path))
        else:
            out.append(re.sub(r"(@@?)([A-Za-z_]\w*)", sym, l))
    os.makedirs(args.out, exist_ok=True)
    stamp = rom_stamp(args.rom)
    stale = [w for w in (check_savestate(p, args.rom, stamp) for p in loaded if p not in saved) if w]
    for w in stale:
        print("WARNING: %s – rebuild the savestate chain (opening.play → …) with this ROM" % w, file=sys.stderr)
    gs = os.path.join(args.out, "_gbarun.txt")
    open(gs, "w").write("\n".join(out) + "\n")
    # gbarun prints at most a few emulator errors and exits with GBARUN_CRASHED when the game crashes, so its
    # output stays small enough to capture
    res = subprocess.run([GBARUN, args.rom, gs, args.out], capture_output=True, text=True)
    for path in saved:
        if os.path.exists(path):
            open(path + ".rom", "w").write(stamp + "\n")
    ok = True
    for line in res.stdout.splitlines():
        m = re.match(r"read (\S+?)(?:>>(\d))? = 0x([0-9A-F]+)", line)
        if m and m.group(1).split("_")[0] in text_checks:
            prefix, key = m.group(1).split("_", 1)
            text_checks[prefix][1][key] = int(m.group(3), 16)
            continue  # reported after the run
        if m and m.group(1).split("_")[0] in party_checks:
            prefix, key = m.group(1).split("_", 1)
            party_checks[prefix][3][key] = int(m.group(3), 16)
            continue  # reported after the run
        if m and m.group(1) in wild_checks:
            wild_checks[m.group(1)][3] = int(m.group(3), 16)
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
    for map_name, field, ids, got in wild_checks.values():
        line = "wild species = %s (%s %s)" % (got, map_name, field)
        if got in ids:
            line += ": %s" % ids[got]
        else:
            line += "   <-- EXPECTED one of %s" % ", ".join(sorted(ids.values()))
            ok = False
        print(line)
    for name, words in text_checks.values():
        ram = bytes(words.get("b%d" % i, 0) for i in range(TEXT_BYTES))
        rom = bytes(words.get("r%d" % i, 0) for i in range(TEXT_BYTES))
        n = min([rom.index(c) for c in (b"\xfd", b"\xff") if c in rom] + [len(rom)])  # up to a placeholder / EOS
        same = n > 0 and ram[:n] == rom[:n]
        line = "text %s %s" % (name, "matches" if same else "differs")
        if not same:
            line += " (buffer %s, ROM %s)   <-- EXPECTED %s" % (ram[:n].hex(), rom[:n].hex(), name)
            ok = False
        print(line)
    if res.stderr.strip():
        print(res.stderr.strip(), file=sys.stderr)
    if res.returncode == GBARUN_CRASHED:
        print("FAIL: the game crashed during %s%s" % (args.script, " – " + "; ".join(stale) if stale else
              " – if it loads a savestate, rebuild the savestate chain with this ROM"), file=sys.stderr)
    elif not ok and stale:
        print("FAIL (the savestate may be stale): %s" % "; ".join(stale), file=sys.stderr)
    sys.exit(0 if ok and res.returncode == 0 else 1)


if __name__ == "__main__":
    main()
