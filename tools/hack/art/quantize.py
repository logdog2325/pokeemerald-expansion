#!/usr/bin/env python3
"""
quantize.py - turn any RGBA/RGB image into a Gen 3-ready indexed PNG.

  python3 tools/hack/art/quantize.py in.png out.png                     # auto palette (<=15 + transparent)
  python3 tools/hack/art/quantize.py in.png out.png --pal target.pal    # map onto an existing palette
  python3 tools/hack/art/quantize.py in.png out.png --key 255,0,255     # treat magenta as transparent
  python3 tools/hack/art/quantize.py in.png out.png --write-pal out.pal

Transparent pixels (alpha < 128, or the --key colour) become index 0. Colours
are snapped to the 15-bit GBA grid so the preview matches the hardware.
"""

import argparse
import os
import sys

from PIL import Image

sys.path.insert(0, os.path.dirname(__file__))
import gbaart  # noqa: E402


def nearest(c, pal, start=1):
    best, bi = None, start
    for i in range(start, len(pal)):
        p = pal[i]
        dist = (c[0] - p[0]) ** 2 * 3 + (c[1] - p[1]) ** 2 * 4 + (c[2] - p[2]) ** 2 * 2
        if best is None or dist < best:
            best, bi = dist, i
    return bi


def quantize(src, pal=None, key=None, colors=15, transparent=(115, 197, 164)):
    src = src.convert("RGBA")
    px = src.load()
    opaque = []
    mask = [[False] * src.width for _ in range(src.height)]
    for y in range(src.height):
        for x in range(src.width):
            r, g, b, a = px[x, y]
            if a >= 128 and (key is None or (r, g, b) != key):
                mask[y][x] = True
                opaque.append(gbaart.gba_color((r, g, b)))
    if pal is None:
        rgb = Image.new("RGB", (len(opaque) or 1, 1))
        rgb.putdata(opaque or [(0, 0, 0)])
        q = rgb.quantize(colors=colors, method=Image.Quantize.MEDIANCUT, dither=Image.Dither.NONE)
        qp = gbaart.palette_rgb(q, colors)
        pal = [gbaart.gba_color(transparent)] + [gbaart.gba_color(c) for c in qp]
    out = gbaart.make_indexed(src.size, pal)
    opx = out.load()
    cache = {}
    for y in range(src.height):
        for x in range(src.width):
            if mask[y][x]:
                c = gbaart.gba_color(px[x, y][:3])
                if c not in cache:
                    cache[c] = nearest(c, pal)
                opx[x, y] = cache[c]
    return out, pal


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("src")
    ap.add_argument("dst")
    ap.add_argument("--pal", help="JASC palette to map onto (index 0 = transparent)")
    ap.add_argument("--key", help="r,g,b colour to treat as transparent")
    ap.add_argument("--colors", type=int, default=15)
    ap.add_argument("--write-pal")
    args = ap.parse_args()
    pal = gbaart.read_jasc(args.pal) if args.pal else None
    key = tuple(int(v) for v in args.key.split(",")) if args.key else None
    out, pal = quantize(Image.open(args.src), pal, key, args.colors)
    gbaart.ensure_dir(args.dst)
    out.save(args.dst)
    if args.write_pal:
        gbaart.write_jasc(args.write_pal, pal)
    print("wrote", args.dst)


if __name__ == "__main__":
    main()
