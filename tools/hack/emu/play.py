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
  flag NAME               print a flag (FLAG_*) from the save block
  var NAME                print a var (VAR_*) from the save block
  expect_flag NAME 0|1    like flag, but fails the run on mismatch
  expect_var NAME VALUE   like var, but fails the run on mismatch
  mapid                   print the current map group/num (gSaveBlock1Ptr->location)
  walk DIR COORD [MAX]    hold DIR until the player's x (LEFT/RIGHT) or y (UP/DOWN) is COORD
  pos                     print the player's map coordinates (+7 MAP_OFFSET)
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
    return syms


def probe(names):
    """Evaluate C constants (and SaveBlock1 offsets) with the project's own headers."""
    src = '#include "global.h"\n#include "constants/flags.h"\n#include "constants/vars.h"\n'
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


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("script")
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("--rom", default=os.path.join(ROOT, "pokeemerald.gba"))
    args = ap.parse_args()
    elf = os.path.splitext(args.rom)[0] + ".elf"
    syms = symbols(elf)
    lines = open(args.script).read().splitlines()
    names = sorted({l.split()[1] for l in lines if l.split() and l.split()[0] in ("flag", "var", "expect_flag", "expect_var")})
    flags_off, vars_off, loc_off, coords_off, consts = probe(names)
    # the player is object event 0 (spawned first on every map load); MAP_OFFSET is 7
    player_x = syms["gObjectEvents"] + coords_off
    player_y = player_x + 2
    sb1 = "*%X" % syms["gSaveBlock1Ptr"]
    expects = []

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
        elif t[0] == "wait_free":
            out.append("run 8")
            out.append("until %X 1 0 %s" % (syms["sLockFieldControls"], t[1]))
        elif t[0] in ("flag", "expect_flag"):
            f = consts[t[1]]
            out.append("read %s+%X 1 %s>>%d" % (sb1, flags_off + f // 8, t[1], f % 8))
            if t[0] == "expect_flag":
                expects.append(("flag", t[1], int(t[2]), f % 8))
        elif t[0] in ("var", "expect_var"):
            v = consts[t[1]]
            out.append("read %s+%X 2 %s" % (sb1, vars_off + (v - 0x4000) * 2, t[1]))
            if t[0] == "expect_var":
                expects.append(("var", t[1], int(t[2], 0), 0))
        elif t[0] == "walk":
            # walk DIR COORD: hold DIR until the player's x (LEFT/RIGHT) or y (UP/DOWN) equals COORD
            addr = player_x if t[1] in ("LEFT", "RIGHT") else player_y
            out.append("untilhold %X 2 %X %s %s" % (addr, int(t[2]) + 7, t[3] if len(t) > 3 else "900", t[1]))
        elif t[0] == "pos":
            out.append("read %X 2 player_x+7" % player_x)
            out.append("read %X 2 player_y+7" % player_y)
        elif t[0] == "mapid":
            out.append("read %s+%X 2 map_group_num" % (sb1, loc_off))
        else:
            out.append(re.sub(r"(@@?)([A-Za-z_]\w*)", sym, l))
    os.makedirs(args.out, exist_ok=True)
    gs = os.path.join(args.out, "_gbarun.txt")
    open(gs, "w").write("\n".join(out) + "\n")
    res = subprocess.run([GBARUN, args.rom, gs, args.out], capture_output=True, text=True)
    ok = True
    for line in res.stdout.splitlines():
        m = re.match(r"read (\S+?)(?:>>(\d))? = 0x([0-9A-F]+)", line)
        if m:
            name, bit, val = m.group(1), m.group(2), int(m.group(3), 16)
            if bit is not None:
                val = (val >> int(bit)) & 1
            line = "%s = %d" % (name, val)
            for kind, n, want, _ in expects:
                if n == name and val != want:
                    line += "   <-- EXPECTED %d" % want
                    ok = False
        if "TIMEOUT" in line:
            ok = False
        print(line)
    if res.stderr.strip():
        print(res.stderr.strip(), file=sys.stderr)
    sys.exit(0 if ok and res.returncode == 0 else 1)


if __name__ == "__main__":
    main()
