#!/usr/bin/env python3
"""
check_seams.py - find map connections that will draw garbage tiles.

The game draws every visible cell with the *current* map's tilesets, including the
cells of a connected map across the seam. When two connected maps use different
secondary tilesets (or primaries), any secondary metatile (id >= 0x200) of one map that
can be drawn while standing in the other shows up with the wrong tiles and palettes,
and stays wrong until that part of the screen is redrawn.

The drawn window around the player is 16x16 metatiles (x-7..x+8, y-7..y+8), so this
checks, for every walkable cell near a seam, every cell of the connected map inside
that window.

  python3 tools/hack/mapgen/check_seams.py                 # every map with connections
  python3 tools/hack/mapgen/check_seams.py DraconidPass     # only seams touching these maps

Exit code 1 if a problem is found in a map given on the command line (or in any map
when none is given).
"""

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pokemap  # noqa: E402

NUM_METATILES_IN_PRIMARY = 0x200
VIEW_BEFORE, VIEW_AFTER = 7, 8  # drawn window: player - 7 .. player + 8, both axes
MAPGRID_COLLISION_SHIFT = 10


def origin_of(direction, offset, a, b):
    """Top-left of map b in map a's coordinates for a connection a -> b."""
    if direction == "up":
        return offset, -b.height
    if direction == "down":
        return offset, a.height
    if direction == "left":
        return -b.width, offset
    if direction == "right":
        return a.width, offset
    return None


def bad_cells(proj, a_name, conn):
    """Cells of the connected map that would be drawn wrongly while standing in a_name."""
    a_json = proj.map_json(a_name)
    b_name = proj.map_name_for_id(conn["map"])
    if b_name is None:
        return b_name, []
    b_json = proj.map_json(b_name)
    a = proj.layout(a_json["layout"])
    b = proj.layout(b_json["layout"])
    if a.primary_symbol == b.primary_symbol and a.secondary_symbol == b.secondary_symbol:
        return b_name, []
    only_secondary = a.primary_symbol == b.primary_symbol
    org = origin_of(conn["direction"], int(conn.get("offset", 0)), a, b)
    if org is None:  # dive/emerge
        return b_name, []
    ox, oy = org
    bad = {}
    for y in range(a.height):
        for x in range(a.width):
            if (a.block(x, y) >> MAPGRID_COLLISION_SHIFT) & 3:
                continue  # not walkable
            for vy in range(y - VIEW_BEFORE, y + VIEW_AFTER + 1):
                for vx in range(x - VIEW_BEFORE, x + VIEW_AFTER + 1):
                    if 0 <= vx < a.width and 0 <= vy < a.height:
                        continue
                    bx, by = vx - ox, vy - oy
                    if not (0 <= bx < b.width and 0 <= by < b.height):
                        continue
                    mid = b.metatile_at(bx, by)
                    if mid >= NUM_METATILES_IN_PRIMARY or not only_secondary:
                        bad.setdefault((bx, by), (mid, (x, y)))
    return b_name, sorted(bad.items())


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("maps", nargs="*")
    args = ap.parse_args()
    proj = pokemap.Project()
    names = [n for n in proj.map_names() if os.path.exists(pokemap.rel("data/maps/%s/map.json" % n))]
    wanted = set(args.maps)
    problems = 0
    for name in names:
        conns = proj.map_json(name).get("connections") or []
        for c in conns:
            b_name, bad = bad_cells(proj, name, c)
            if not bad:
                continue
            if wanted and name not in wanted and b_name not in wanted:
                continue
            problems += 1
            cells = ", ".join("(%d,%d)=%03X" % (xy[0], xy[1], v[0]) for xy, v in bad[:12])
            more = " …+%d" % (len(bad) - 12) if len(bad) > 12 else ""
            print("%s -> %s (%s): %d cell(s) of %s drawn with %s's tilesets: %s%s"
                  % (name, b_name, c["direction"], len(bad), b_name, name, cells, more))
    if problems == 0:
        print("seams OK" + (" for " + ", ".join(sorted(wanted)) if wanted else ""))
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
