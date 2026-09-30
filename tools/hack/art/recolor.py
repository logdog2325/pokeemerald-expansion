#!/usr/bin/env python3
"""
recolor.py - re-palette / index-remap indexed sprites without touching pixels.

  # give a sheet a new palette (same indices, new colours)
  python3 tools/hack/art/recolor.py in.png out.png --pal new.pal

  # swap individual palette slots: index=r,g,b
  python3 tools/hack/art/recolor.py in.png out.png --set 3=40,40,48 --set 4=24,24,32

  # move pixels from one index to another (e.g. merge two shades)
  python3 tools/hack/art/recolor.py in.png out.png --remap 7:5 --remap 8:6

  # print the palette with pixel counts
  python3 tools/hack/art/recolor.py in.png --show

Several inputs can share one output directory with --out-dir.
"""

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
import gbaart  # noqa: E402


def apply(im, pal=None, sets=(), remaps=()):
    im = im.copy()
    if remaps:
        table = list(range(256))
        for a, b in remaps:
            table[a] = b
        im = im.point(table)
    p = gbaart.palette_rgb(im, 16)
    if pal:
        p = list(pal[:16]) + p[len(pal):]
    for i, c in sets:
        p[i] = c
    return gbaart.set_palette(im, p)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("src", nargs="+")
    ap.add_argument("--pal")
    ap.add_argument("--set", action="append", default=[])
    ap.add_argument("--remap", action="append", default=[])
    ap.add_argument("--show", action="store_true")
    ap.add_argument("--out-dir")
    args = ap.parse_args()

    srcs = args.src
    dst = None
    if not args.show and not args.out_dir:
        srcs, dst = args.src[:-1], args.src[-1]
    pal = gbaart.read_jasc(args.pal) if args.pal else None
    sets = [(int(s.split("=")[0]), tuple(int(v) for v in s.split("=")[1].split(","))) for s in args.set]
    remaps = [tuple(int(v) for v in r.split(":")) for r in args.remap]
    for s in srcs:
        im = gbaart.load_indexed(s)
        if args.show:
            counts = {}
            for v in im.tobytes():
                counts[v] = counts.get(v, 0) + 1
            print(s)
            for i, c in enumerate(gbaart.palette_rgb(im, 16)):
                print("  %2d  %3d %3d %3d   %d px" % (i, *c, counts.get(i, 0)))
            continue
        out = apply(im, pal, sets, remaps)
        path = os.path.join(args.out_dir, os.path.basename(s)) if args.out_dir else dst
        gbaart.ensure_dir(path)
        out.save(path)
        print("wrote", path)


if __name__ == "__main__":
    main()
