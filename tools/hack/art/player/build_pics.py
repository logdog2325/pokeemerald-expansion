#!/usr/bin/env python3
"""
build_pics.py - build a player outfit's trainer front pic and back pic (throw frames).

Same idea as build_player.py: the FRLG Red/Leaf pics give pose and body, the outfit gets a
new palette (same index roles) and a new head drawn over the old headwear.

  python3 tools/hack/art/player/build_pics.py tools/hack/art/player/draconid_m_pics.json [--preview out.png]

Spec (JSON), one entry per pic in "pics":
  {"src": "graphics/trainers/back_pics/red.png", "out": "graphics/trainers/back_pics/draconid_m.png",
   "frame_h": 64,                         frames are stacked vertically (back pics have 4-5)
   "palette": [[r, g, b] x16], "roles": {...}, "cap": [...], "clear": [...],
   "head": {"anchor": [dx, dy], "rows": [...]},  drawn on every frame, anchored like build_player
   "fix": {"3": {"dx": 0, "dy": 0}},      per-frame nudges
   "remap": [{"rect": [x0, y0, x1, y1], "map": {"4": 6}}],  per-frame recolours (frame coords), after the head;
                                          "frames": [1, 2] limits one to those frames (default: all)
   "pattern": [{"rect": [...], "on": [6], "tile": ["dT", "Td"], "frames": [...]}],
                                          tile an ASCII pattern (roles) over the pixels of indices `on`
   "pixels": {"0": ["x,y,ROLE"]}}
"""

import argparse
import json
import os
import sys

from PIL import Image

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_player import ROOT, gba_color, load_indexed, swap_head  # noqa: E402


def build_pic(p):
    src = load_indexed(os.path.join(ROOT, p["src"]))
    palette = [gba_color(c) for c in p["palette"]]
    flat = [v for c in palette for v in c]
    out = src.copy()
    out.putpalette(flat + [0] * (768 - len(flat)))
    px = out.load()
    w, fh = out.width, p.get("frame_h", out.height)
    roles = p["roles"]
    for i in range(out.height // fh):
        fy = i * fh
        if "head" in p:
            ok = swap_head(px, 0, fy, w, fh, p["head"], roles, set(p["cap"]), set(p["clear"]),
                           p.get("fix", {}).get(str(i), {}))
            if not ok:
                print("warning: %s frame %d: no headwear found" % (p["out"], i))
        for r in p.get("remap", []):
            if "frames" in r and i not in r["frames"]:
                continue
            x0, y0, x1, y1 = r["rect"]
            m = {int(k): v for k, v in r["map"].items()}
            for y in range(y0, y1 + 1):
                for x in range(x0, x1 + 1):
                    if px[x, fy + y] in m:
                        px[x, fy + y] = m[px[x, fy + y]]
        for t in p.get("pattern", []):
            if "frames" in t and i not in t["frames"]:
                continue
            x0, y0, x1, y1 = t["rect"]
            on, tile = set(t["on"]), t["tile"]
            for y in range(y0, y1 + 1):
                for x in range(x0, x1 + 1):
                    ch = tile[(y - y0) % len(tile)][(x - x0) % len(tile[0])]
                    if px[x, fy + y] in on and ch != ".":
                        px[x, fy + y] = roles[ch]
        for q in p.get("pixels", {}).get(str(i), []):
            x, y, ch = q.split(",")
            px[int(x), fy + int(y)] = 0 if ch == "_" else roles[ch]
    path = os.path.join(ROOT, p["out"])
    os.makedirs(os.path.dirname(path), exist_ok=True)
    out.save(path)
    print("wrote", p["out"])
    return out, palette, fh


def preview(results, path, zoom=4):
    tiles = []
    for im, palette, fh in results:
        for i in range(im.height // fh):
            fr = im.crop((0, i * fh, im.width, i * fh + fh)).convert("RGBA")
            bg = Image.new("RGBA", fr.size, (90, 90, 110, 255))
            bg.alpha_composite(fr)
            tiles.append(bg.convert("RGB"))
    sheet = Image.new("RGB", (sum(t.width + 4 for t in tiles), max(t.height for t in tiles)), (20, 20, 24))
    x = 0
    for t in tiles:
        sheet.paste(t, (x, 0))
        x += t.width + 4
    sheet = sheet.resize((sheet.width * zoom, sheet.height * zoom), Image.NEAREST)
    sheet.save(path)
    print("preview", path)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("spec")
    ap.add_argument("--preview")
    args = ap.parse_args()
    spec = json.load(open(args.spec))
    results = [build_pic(p) for p in spec["pics"]]
    if args.preview:
        preview(results, args.preview)


if __name__ == "__main__":
    main()
