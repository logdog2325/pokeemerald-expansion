#!/usr/bin/env python3
"""
scan_maps.py - which trainers are fought on which map.

  python3 tools/hack/trainers/scan_maps.py                 # map: trainers, one line per map
  python3 tools/hack/trainers/scan_maps.py --json out.json # {map: [TRAINER_...]}
  python3 tools/hack/trainers/scan_maps.py --unplaced      # Emerald trainer ids no map script names

A trainer belongs to a map when that map's scripts.inc/.pory names it (trainerbattle macros,
setflag/checktrainerflag, etc.). Rematch tiers (_2.._5) come from gRematchTable in
src/battle_setup.c: they are listed under the map of their first battle with a "#tier" suffix
stripped, and reported separately by --rematches. FRLG maps (_Frlg) are skipped.
"""

import argparse
import glob
import json
import os
import re

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
TRAINER_RE = re.compile(r"\bTRAINER_[A-Z0-9_]+\b")
REMATCH_RE = re.compile(r"REMATCH\((TRAINER_\w+), (TRAINER_\w+), (TRAINER_\w+), (TRAINER_\w+), (TRAINER_\w+), (MAP_\w+)\)")


def trainer_ids():
    """Emerald trainer ids (value <= TRAINERS_COUNT_EMERALD) from include/constants/opponents.h."""
    ids = {}
    text = open(os.path.join(ROOT, "include/constants/opponents.h")).read()
    for m in re.finditer(r"#define (TRAINER_\w+)\s+(\d+)\s*$", text, re.M):
        ids[m.group(1)] = int(m.group(2))
    return ids


def scan_pory(ids, maps):
    """Draconid story scripts (data/scripts/draconid/*.pory): a script's map is its label prefix
    (MossdeepCity_SpaceCenter_2F_EventScript_X -> MossdeepCity_SpaceCenter_2F)."""
    for path in sorted(glob.glob(os.path.join(ROOT, "data/scripts/draconid/*.pory"))):
        text = open(path).read()
        for m in re.finditer(r"^script (\w+?)_EventScript_\w+ \{(.*?)^\}", text, re.M | re.S):
            for t in TRAINER_RE.findall(m.group(2)):
                if t in ids and ids[t] != 0 and t not in maps.setdefault(m.group(1), []):
                    maps[m.group(1)].append(t)
    return {k: v for k, v in maps.items() if v}


def scan(ids):
    maps = {}
    for d in sorted(glob.glob(os.path.join(ROOT, "data/maps/*"))):
        name = os.path.basename(d)
        if name.endswith("_Frlg"):
            continue
        found = []
        for f in ("scripts.inc", "scripts.pory"):
            p = os.path.join(d, f)
            if os.path.exists(p):
                for t in TRAINER_RE.findall(open(p).read()):
                    if t in ids and ids[t] != 0 and t not in found:
                        found.append(t)
        if found:
            maps[name] = found
    return scan_pory(ids, maps)


def rematches():
    """[(tiers [TRAINER_X_1..5], MAP_CONST)] from gRematchTable."""
    text = open(os.path.join(ROOT, "src/battle_setup.c")).read()
    return [(list(m.groups()[:5]), m.group(6)) for m in REMATCH_RE.finditer(text)]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json")
    ap.add_argument("--unplaced", action="store_true")
    ap.add_argument("--rematches", action="store_true")
    args = ap.parse_args()
    ids = trainer_ids()
    maps = scan(ids)
    if args.json:
        json.dump(maps, open(args.json, "w"), indent=1)
    if args.rematches:
        for tiers, m in rematches():
            print(m, " ".join(tiers))
        return
    if args.unplaced:
        placed = {t for ts in maps.values() for t in ts}
        for tiers, _ in rematches():
            placed |= set(tiers)
        emerald = [t for t, v in sorted(ids.items(), key=lambda kv: kv[1]) if 0 < v < 858]
        for t in emerald:
            if t not in placed:
                print(t)
        return
    for name, ts in maps.items():
        print("%s: %s" % (name, " ".join(ts)))


if __name__ == "__main__":
    main()
