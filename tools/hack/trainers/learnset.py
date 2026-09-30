#!/usr/bin/env python3
"""
learnset.py - show what a species learns, to write trainer movesets.

  python3 tools/hack/trainers/learnset.py Grovyle            # level-up moves (with levels) + abilities
  python3 tools/hack/trainers/learnset.py Grovyle --level 23 # the last 4 level-up moves at Lv 23 (the default set)
  python3 tools/hack/trainers/learnset.py Grovyle --all      # also every other learnable move (TM, tutor, egg)
"""

import argparse
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import party  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))


def species_fields(sp):
    for path in glob.glob(os.path.join(ROOT, "src/data/pokemon/species_info/*.h")):
        text = open(path).read()
        m = re.search(r"\[SPECIES_%s\]\s*=\s*\{(.*?)\n    \}," % sp, text, re.S)
        if m:
            return m.group(1)
    return None


def levelup(pointer):
    from check_party import levelup_file
    for path in [levelup_file()]:
        text = open(path).read()
        m = re.search(r"%s\[\]\s*=\s*\{(.*?)\};" % pointer, text, re.S)
        if m:
            return [(int(lv), mv) for lv, mv in re.findall(r"LEVEL_UP_MOVE\(\s*(\d+),\s*(MOVE_\w+)\)", m.group(1))]
    return []


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("species")
    ap.add_argument("--level", type=int)
    ap.add_argument("--all", action="store_true")
    args = ap.parse_args()
    sp = party.const_name(args.species, "SPECIES_")[len("SPECIES_"):]
    body = species_fields(sp)
    if body is None:
        sys.exit("unknown species %s" % sp)
    ab = re.search(r"\.abilities\s*=\s*\{([^}]*)\}", body)
    ptr = re.search(r"\.levelUpLearnset\s*=\s*(\w+)", body)
    moves = levelup(ptr.group(1)) if ptr else []
    print("%s  abilities: %s" % (sp, ab.group(1).strip() if ab else "?"))
    if args.level:
        known = []
        for lv, mv in moves:
            if lv <= args.level and mv not in known:
                known.append(mv)
        print("default set at Lv %d: %s" % (args.level, ", ".join(known[-4:])))
    print("level-up: " + ", ".join("%d %s" % (lv, mv[5:]) for lv, mv in moves))
    if args.all:
        learn = json.load(open(os.path.join(ROOT, "src/data/pokemon/all_learnables.json")))
        other = sorted(set(learn.get(sp, [])) - {mv for _, mv in moves})
        print("other: " + ", ".join(m[5:] for m in other))


if __name__ == "__main__":
    main()
