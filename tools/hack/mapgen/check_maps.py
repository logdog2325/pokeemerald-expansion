#!/usr/bin/env python3
"""
check_maps.py - lint the hack's own maps for the tile errors a playtester sees (playtest 2.1, D-340).
  python3 tools/hack/mapgen/check_maps.py                 # every map built from tools/hack/mapgen/specs/*.json
  python3 tools/hack/mapgen/check_maps.py DraconidPass    # named maps (vanilla ones too)
  python3 tools/hack/mapgen/check_maps.py --vanilla       # the rules against every vanilla map (expect ~0)

Checks:
  - tree:  every 2x2 tree is whole. General trees (1D4..1E7) and their crown caps (1C6/1C7/1CE/1CF), and
           Fallarbor's round trees (206/207/26B/26C over 273/274/20E/20F/2CA/2CB): each corner needs its
           partners beside and above/below it (a cap needs the tree top under it).
  - elev:  no pocket of walkable land at an elevation its walkable neighbours don't share: one odd cell in a
           field is an invisible wall (Draconid Pass had six, elevation 5 in elevation-3 grass).
Exit 1 on any finding.
"""

import argparse
import glob
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pokemap  # noqa: E402

SPECS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "specs")

# corner families, with the variants vanilla uses (staggered forests: 1F2/1F3 under, 1FC/1FD over a tree; 1EC/1ED and
# 1DE/1DF over other ground) - checked with --vanilla
G_TL, G_TR = {0x1D4, 0x1D6, 0x1FC}, {0x1D5, 0x1D7, 0x1FD}
G_BL, G_BR = {0x1DC, 0x1E4, 0x1E6, 0x1F3, 0x1EC, 0x1DE}, {0x1DD, 0x1E5, 0x1E7, 0x1F2, 0x1ED, 0x1DF}
G_CAP_L, G_CAP_R = {0x1C6, 0x1CE}, {0x1C7, 0x1CF}
F_TL, F_TR = {0x206, 0x26B, 0x2C2, 0x214}, {0x207, 0x26C, 0x2C3, 0x215}
F_BL, F_BR = {0x273, 0x20E, 0x2CA, 0x2CE}, {0x274, 0x20F, 0x2CB, 0x2CF}
F_ALL = F_TL | F_TR | F_BL | F_BR
TREE_RULES = {
    # (corner family, [(dx, dy, wanted neighbour set), ...])
    "general": [(G_TL, [(1, 0, G_TR), (0, 1, G_BL)]), (G_TR, [(-1, 0, G_TL), (0, 1, G_BR)]),
                (G_BL, [(1, 0, G_BR), (0, -1, G_TL)]), (G_BR, [(-1, 0, G_BL), (0, -1, G_TR)]),
                (G_CAP_L, [(0, 1, G_TL)]), (G_CAP_R, [(0, 1, G_TR)])],
    # Fallarbor's round trees stagger by a column from row to row, so a corner's partners may be any tree tile:
    # what must not happen is a corner with open ground where the rest of its tree should be
    "fallarbor": [(F_TL, [(1, 0, F_ALL), (0, 1, F_ALL)]), (F_TR, [(-1, 0, F_ALL), (0, 1, F_ALL)]),
                  (F_BL, [(1, 0, F_ALL), (0, -1, F_ALL | {0x269, 0x278})]),
                  (F_BR, [(-1, 0, F_ALL), (0, -1, F_ALL | {0x269, 0x278})])],
}
WATER_BEHAVIORS = None
POCKET_MAX = 6  # a same-elevation patch this small, walled in by other elevations, is a mapping slip


def spec_maps():
    names = []
    for p in sorted(glob.glob(os.path.join(SPECS, "*.json"))):
        try:
            names.append(json.load(open(p))["name"])
        except (KeyError, ValueError):
            pass
    return names


def tree_findings(L, rules):
    out = []
    W, H = L.width, L.height
    for y in range(H):
        for x in range(W):
            m = L.metatile_at(x, y)
            for family, needs in rules:
                if m not in family:
                    continue
                for dx, dy, want in needs:
                    X, Y = x + dx, y + dy
                    if not (0 <= X < W and 0 <= Y < H):
                        continue  # the border / a connection continues it
                    n = L.metatile_at(X, Y)
                    if n not in want and not (n >= pokemap.NUM_METATILES_IN_PRIMARY and min(want) < 0x200):
                        # (a General tree against a secondary tileset's own tree tile: can't judge)
                        out.append("tree  (%d,%d) %03X: (%d,%d) is %03X, wants %s" % (
                            x, y, m, X, Y, n, "/".join("%03X" % v for v in sorted(want))))
    return out


def elev_findings(L, pair):
    W, H = L.width, L.height
    names = pokemap.behavior_names()

    def land(x, y):
        m, col, e = pokemap.unpack_block(L.block(x, y))
        if col or e in (0, 15):
            return None
        b = pair.behavior(m)
        n = names.get(b, "") if isinstance(names, dict) else ""
        if "WATER" in n or "POND" in n or "WATERFALL" in n or "SEA" in n or "OCEAN" in n or e == 1:
            return None
        return e

    seen = set()
    out = []
    for y in range(H):
        for x in range(W):
            e = land(x, y)
            if e is None or (x, y) in seen:
                continue
            comp, stack, border = [], [(x, y)], set()
            seen.add((x, y))
            while stack:
                cx, cy = stack.pop()
                comp.append((cx, cy))
                for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                    X, Y = cx + dx, cy + dy
                    if not (0 <= X < W and 0 <= Y < H):
                        continue
                    ne = land(X, Y)
                    if ne == e and (X, Y) not in seen:
                        seen.add((X, Y))
                        stack.append((X, Y))
                    elif ne is not None and ne != e:
                        border.add(ne)
            if len(comp) <= POCKET_MAX and border:
                # walled in only if no neighbour of the patch is walkable at elevation 0/15 or the same elevation
                open_side = False
                for cx, cy in comp:
                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        X, Y = cx + dx, cy + dy
                        if 0 <= X < W and 0 <= Y < H and (X, Y) not in comp:
                            m, col, ne = pokemap.unpack_block(L.block(X, Y))
                            if not col and ne in (0, 15):
                                open_side = True
                if not open_side:
                    out.append("elev  %s at elevation %d, surrounded by walkable elevation %s" % (
                        " ".join("(%d,%d)" % c for c in sorted(comp)), e, "/".join(map(str, sorted(border)))))
    return out


def check_layout(proj, lid):
    L = proj.layout(lid)
    pair = proj.pair_for_layout(L)
    rules = []
    if L.primary_symbol == "gTileset_General":
        rules += TREE_RULES["general"]
    if L.secondary_symbol == "gTileset_Fallarbor":
        rules += TREE_RULES["fallarbor"]
    return tree_findings(L, rules) + elev_findings(L, pair)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("maps", nargs="*")
    ap.add_argument("--vanilla", action="store_true", help="run the rules on every vanilla layout instead")
    args = ap.parse_args()
    proj = pokemap.Project()
    if args.vanilla:
        own = set(proj.map_json(n)["layout"] for n in spec_maps())
        lids = [l for l in proj.layout_ids() if l not in own]
    else:
        lids = [proj.map_json(n)["layout"] for n in (args.maps or spec_maps())]
    total = 0
    for lid in lids:
        try:
            found = check_layout(proj, lid)
        except (OSError, KeyError) as e:
            print("skip  %s: %s" % (lid, e))
            continue
        for f in found:
            print("%-32s %s" % (lid, f))
        total += len(found)
    print("%d layout(s) checked, %d finding(s)" % (len(lids), total))
    sys.exit(1 if total and not args.vanilla else 0)


if __name__ == "__main__":
    main()
