#!/usr/bin/env python3
"""
inspect_map.py - print the real metatile IDs (and collision/elevation) of a map region.

Use it to find the metatile IDs for a legend or a stamp instead of guessing:
  python3 tools/hack/mapgen/inspect_map.py Route114 --rect 0,0,20,12
  python3 tools/hack/mapgen/inspect_map.py FallarborTown --rect 0,0,8,8 --full
  python3 tools/hack/mapgen/inspect_map.py FallarborTown --crop 0,0,8,8 -o crop.png

Output cells are MMM (hex metatile id) by default; --full prints MMM:c:e
(collision, elevation). --crop renders the rect enlarged with a coordinate grid.
"""

import argparse
import os
import sys

from PIL import Image, ImageDraw

sys.path.insert(0, os.path.dirname(__file__))
import pokemap  # noqa: E402
import render  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("map")
    ap.add_argument("--rect", help="x,y,w,h (default whole map)")
    ap.add_argument("--full", action="store_true", help="show collision and elevation")
    ap.add_argument("--crop", help="x,y,w,h region to render")
    ap.add_argument("-o", "--out")
    ap.add_argument("--scale", type=int, default=3)
    args = ap.parse_args()

    proj = pokemap.Project()
    mapj = proj.map_json(args.map) if os.path.exists(pokemap.rel("data/maps/%s/map.json" % args.map)) else None
    layout = proj.layout(mapj["layout"] if mapj else args.map)
    print("# %s %dx%d %s + %s" % (layout.id, layout.width, layout.height, layout.primary_symbol, layout.secondary_symbol))

    if args.crop:
        x0, y0, w, h = map(int, args.crop.split(","))
        img = render.render_layout(proj, layout)
        img = img.crop((x0 * 16, y0 * 16, (x0 + w) * 16, (y0 + h) * 16))
        s = args.scale
        img = img.resize((img.width * s, img.height * s), Image.NEAREST)
        d = ImageDraw.Draw(img)
        for i in range(w):
            for j in range(h):
                d.rectangle([i * 16 * s, j * 16 * s, (i + 1) * 16 * s - 1, (j + 1) * 16 * s - 1], outline=(255, 255, 255, 60))
                d.text((i * 16 * s + 2, j * 16 * s + 1), "%03X" % layout.metatile_at(x0 + i, y0 + j), fill=(255, 255, 0, 255))
        img.save(args.out or "crop.png")
        print("wrote", args.out or "crop.png")
        return

    if args.rect:
        x0, y0, w, h = map(int, args.rect.split(","))
    else:
        x0, y0, w, h = 0, 0, layout.width, layout.height
    print("     " + " ".join(("%-9d" if args.full else "%-3d") % (x0 + i) for i in range(w)))
    for j in range(h):
        row = []
        for i in range(w):
            m, c, e = pokemap.unpack_block(layout.block(x0 + i, y0 + j))
            row.append("%03X:%d:%X  " % (m, c, e) if args.full else "%03X" % m)
        print("%3d: " % (y0 + j) + " ".join(row))


if __name__ == "__main__":
    main()
