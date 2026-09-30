#!/usr/bin/env python3
"""
contact_sheet.py - render sprite sheets as a labelled, enlarged grid for review.

  python3 tools/hack/art/contact_sheet.py -o sheet.png graphics/object_events/pics/people/draconid_m/*.png
  python3 tools/hack/art/contact_sheet.py -o sheet.png --pal graphics/object_events/palettes/draconid_m.pal a.png b.png

Each input is shown on its own row, split into frames (profile guessed from
the file name like validate.py), on a checkerboard so transparency is visible.
--pal renders with an external JASC palette (what the game actually uses for
object events) instead of the PNG's embedded palette.
"""

import argparse
import os
import sys

from PIL import Image, ImageDraw

sys.path.insert(0, os.path.dirname(__file__))
import gbaart  # noqa: E402
import validate  # noqa: E402


def checker(w, h, s=4):
    im = Image.new("RGBA", (w, h), (200, 200, 200, 255))
    d = ImageDraw.Draw(im)
    for y in range(0, h, s):
        for x in range(0, w, s):
            if (x // s + y // s) % 2:
                d.rectangle([x, y, x + s - 1, y + s - 1], fill=(170, 170, 170, 255))
    return im


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="+")
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("--scale", type=int, default=3)
    ap.add_argument("--pal", action="append", default=[], help="JASC palette per file (repeat) or one for all")
    ap.add_argument("--profile", choices=sorted(gbaart.PROFILES))
    args = ap.parse_args()

    rows = []
    for i, path in enumerate(args.files):
        im = gbaart.load_indexed(path)
        if args.pal:
            pal = gbaart.read_jasc(args.pal[min(i, len(args.pal) - 1)])
            im = gbaart.set_palette(im.copy(), pal)
        prof = args.profile or validate.guess_profile(path)
        if prof:
            fw, fh, _, axis = gbaart.PROFILES[prof]
            frs = gbaart.frames(im, fw, fh, axis)
        else:
            frs = [im]
        rows.append((path, [gbaart.to_rgba(f) for f in frs]))

    s = args.scale
    pad = 4
    label_h = 12
    width = max(sum(f.width * s + pad for f in frs) for _, frs in rows) + pad
    height = sum(max(f.height for f in frs) * s + label_h + pad * 2 for _, frs in rows)
    sheet = Image.new("RGBA", (max(width, 300), height), (48, 48, 56, 255))
    d = ImageDraw.Draw(sheet)
    y = 0
    for path, frs in rows:
        d.text((pad, y + 1), os.path.relpath(path), fill=(255, 255, 160, 255))
        y += label_h
        x = pad
        rh = max(f.height for f in frs) * s
        for n, f in enumerate(frs):
            big = f.resize((f.width * s, f.height * s), Image.NEAREST)
            bg = checker(big.width, big.height)
            bg.alpha_composite(big)
            sheet.paste(bg, (x, y))
            d.text((x + 1, y + 1), str(n), fill=(0, 0, 160, 255))
            x += big.width + pad
        y += rh + pad * 2
    gbaart.ensure_dir(args.out)
    sheet.save(args.out)
    print("wrote", args.out, sheet.size)


if __name__ == "__main__":
    main()
