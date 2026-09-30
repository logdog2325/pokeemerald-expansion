#!/usr/bin/env python3
"""Compare the before/after screenshots of tests/fades.play (D-278): a same-screen fade must not change the picture.

  python3 tools/hack/emu/fade_check.py OUTDIR [--tolerance 1.0]

Prints the mean colour of each pair and fails (exit 1) when an "after" shot's mean red, green or blue differs from
its "before" shot's by more than the tolerance (0-255). A double weather or day/night tint moves them by 20-40; the
fog's drift (Cave of Origin) moves pixels but not the means. The pixel difference is printed for information."""
import argparse
import glob
import os
import sys

from PIL import Image, ImageChops, ImageStat


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("out")
    ap.add_argument("--tolerance", type=float, default=1.5)
    args = ap.parse_args()
    ok = True
    befores = sorted(glob.glob(os.path.join(args.out, "fade_*_before.png")))
    if not befores:
        sys.exit("no fade_*_before.png in %s (run tests/fades.play first)" % args.out)
    for before in befores:
        a = Image.open(before).convert("RGB")
        for after in sorted(glob.glob(before.replace("_before.png", "_after*.png"))):
            b = Image.open(after).convert("RGB")
            ma, mb = ImageStat.Stat(a).mean, ImageStat.Stat(b).mean
            shift = max(abs(x - y) for x, y in zip(ma, mb))
            pixels = sum(ImageStat.Stat(ImageChops.difference(a, b)).mean) / 3
            line = "%-28s mean RGB %s -> %s   shift %5.1f   pixels %5.1f" % (os.path.basename(after)[:-4],
                   "/".join("%.0f" % x for x in ma), "/".join("%.0f" % x for x in mb), shift, pixels)
            if shift > args.tolerance:
                line += "   <-- CHANGED"
                ok = False
            print(line)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
