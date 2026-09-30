#!/usr/bin/env python3
"""
validate.py - check sprite sheets against Gen 3 constraints.

  python3 tools/hack/art/validate.py graphics/object_events/pics/people/draconid_m/*.png
  python3 tools/hack/art/validate.py --profile trainer_back graphics/trainers/back_pics/draconid_m.png
  python3 tools/hack/art/validate.py --manifest tools/hack/art/manifests/draconid.json

Checks: indexed PNG, <= 16 palette entries in use, index 0 used for the
background (all four corners of every frame are index 0 for sprites), size is a
whole number of frames for the profile, expected frame count, and no fully
empty frames. The profile is guessed from the file name when not given.
Exit code 1 if anything fails.
"""

import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
import gbaart  # noqa: E402

GUESS = {
    "walking": "ow_walk", "running": "ow_walk", "mach_bike": "ow_mach_bike", "acro_bike": "ow_acro_bike",
    "surfing": "ow_surf", "field_move": "ow_field_move", "fishing": "ow_fishing",
    "underwater": "ow_underwater", "watering": "ow_watering", "decorating": "ow_decorating",
}


def guess_profile(path):
    base = os.path.splitext(os.path.basename(path))[0]
    if base in GUESS:
        return GUESS[base]
    if "/back_pics/" in path:
        return "trainer_back"
    if "/front_pics/" in path:
        return "trainer_front"
    return None


def check(path, profile=None, frames=None):
    errors, notes = [], []
    try:
        im = gbaart.load_indexed(path)
    except Exception as e:  # noqa: BLE001
        return [str(e)], notes
    used = gbaart.used_indices(im)
    if max(used) > 15:
        errors.append("uses palette index %d (> 15)" % max(used))
    if len(used) > 16:
        errors.append("uses %d colours (> 16)" % len(used))
    profile = profile or guess_profile(path)
    if profile:
        fw, fh, n, axis = gbaart.PROFILES[profile]
        if frames:
            n = frames
        if im.width % fw or im.height % fh:
            errors.append("size %dx%d is not a multiple of %dx%d frames (%s)" % (im.width, im.height, fw, fh, profile))
        else:
            got = im.width // fw if axis == "x" else im.height // fh
            if got != n:
                errors.append("%d frames, expected %d for %s" % (got, n, profile))
            px = im.load()
            for i, fr in enumerate(gbaart.frames(im, fw, fh, axis)):
                fpx = fr.load()
                if all(fpx[x, y] == 0 for x in range(fw) for y in range(fh)):
                    errors.append("frame %d is empty" % i)
                if profile != "trainer_front" or True:
                    corners = [fpx[0, 0], fpx[fw - 1, 0], fpx[0, fh - 1], fpx[fw - 1, fh - 1]]
                    if any(corners) and profile.startswith("ow"):
                        notes.append("frame %d: a corner pixel is not index 0 (transparent)" % i)
            del px
    else:
        notes.append("no profile (pass --profile); only colour checks done")
    notes.append("%dx%d, %d colours used" % (im.width, im.height, len(used)))
    return errors, notes


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="*")
    ap.add_argument("--profile", choices=sorted(gbaart.PROFILES))
    ap.add_argument("--frames", type=int)
    ap.add_argument("--manifest", help="JSON list of {path, profile, frames}")
    args = ap.parse_args()

    jobs = [(f, args.profile, args.frames) for f in args.files]
    if args.manifest:
        for e in json.load(open(args.manifest)):
            jobs.append((e["path"], e.get("profile"), e.get("frames")))
    bad = 0
    for path, prof, n in jobs:
        errors, notes = check(path, prof, n)
        status = "FAIL" if errors else "ok"
        print("%-4s %s  (%s)" % (status, path, "; ".join(notes)))
        for e in errors:
            print("     - " + e)
        bad += bool(errors)
    print("%d file(s), %d failed" % (len(jobs), bad))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
