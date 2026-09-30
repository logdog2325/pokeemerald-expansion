#!/usr/bin/env python3
"""
kitbash.py - build sprite sheets from reproducible JSON recipes.

  python3 tools/hack/art/kitbash.py tools/hack/art/recipes/player_draconid_m.json

A recipe is a list of steps applied to one working sheet:

  {"op": "load", "src": "graphics/.../walking.png"}           start from a sheet
  {"op": "new", "size": [w, h], "pal": "x.pal"}               or a blank one
  {"op": "palette", "pal": "x.pal" | [[r,g,b], ...]}           replace palette
  {"op": "remap", "map": {"3": 5, "4": 5}}                     move pixel indices
  {"op": "remap_region", "box": [x,y,w,h], "map": {...}}       ... only inside a box
  {"op": "paste", "src": "a.png", "box": [x,y,w,h], "at": [x,y],
       "map": {"1": 4}, "flip": "x"}                           copy pixels (index 0 skipped)
  {"op": "pixels", "at": [x,y], "rows": ["..AB", ".AAB"],
       "key": {"A": 3, "B": 4}, "frames": [0,1,2], "frame_w": 16}
                                                               ASCII overlay; '.' = leave,
                                                               '0' = make transparent
  {"op": "frames", "frame_w": 16, "frame_h": 32, "order": [0,0,1,2]}
                                                               rebuild sheet from frame list
  {"op": "save", "dst": "graphics/.../walking.png"}

Paths are relative to the repo root. Several "save" steps may appear.
The recipe file may also be {"steps": [...], "notes": "..."}.
"""

import json
import os
import sys

from PIL import Image

sys.path.insert(0, os.path.dirname(__file__))
import gbaart  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))


def R(p):
    return p if os.path.isabs(p) else os.path.join(ROOT, p)


def _pal(v):
    if isinstance(v, str):
        return gbaart.read_jasc(R(v))
    return [tuple(c) for c in v]


def _remap_table(m):
    t = list(range(256))
    for k, v in m.items():
        t[int(k)] = int(v)
    return t


def paste_indexed(dst, src, box, at, table=None, flip=None):
    x0, y0, w, h = box
    region = src.crop((x0, y0, x0 + w, y0 + h))
    if flip == "x":
        region = region.transpose(Image.FLIP_LEFT_RIGHT)
    elif flip == "y":
        region = region.transpose(Image.FLIP_TOP_BOTTOM)
    rp = region.load()
    dp = dst.load()
    ax, ay = at
    for y in range(h):
        for x in range(w):
            c = rp[x, y]
            if c == 0:
                continue
            tx, ty = ax + x, ay + y
            if 0 <= tx < dst.width and 0 <= ty < dst.height:
                dp[tx, ty] = table[c] if table else c


def draw_rows(dst, at, rows, key, frame_offsets=(0,)):
    dp = dst.load()
    for fx in frame_offsets:
        for j, row in enumerate(rows):
            for i, ch in enumerate(row):
                if ch == ".":
                    continue
                x, y = at[0] + fx + i, at[1] + j
                if not (0 <= x < dst.width and 0 <= y < dst.height):
                    continue
                dp[x, y] = 0 if ch == "0" else key[ch]


def run(steps, log=print):
    cur = None
    for st in steps:
        op = st["op"]
        if op == "load":
            cur = gbaart.load_indexed(R(st["src"])).copy()
        elif op == "new":
            cur = gbaart.make_indexed(tuple(st["size"]), _pal(st["pal"]))
        elif op == "palette":
            cur = gbaart.set_palette(cur, _pal(st["pal"]))
        elif op == "remap":
            pal = cur.getpalette()
            cur = cur.point(_remap_table(st["map"]))
            cur.putpalette(pal)
        elif op == "remap_region":
            x, y, w, h = st["box"]
            region = cur.crop((x, y, x + w, y + h)).point(_remap_table(st["map"]))
            cur.paste(region, (x, y))
        elif op == "paste":
            src = gbaart.load_indexed(R(st["src"]))
            table = _remap_table(st["map"]) if "map" in st else None
            box = st.get("box", [0, 0, src.width, src.height])
            paste_indexed(cur, src, box, st.get("at", [0, 0]), table, st.get("flip"))
        elif op == "pixels":
            fw = st.get("frame_w", 0)
            offs = [f * fw for f in st.get("frames", [0])]
            draw_rows(cur, st["at"], st["rows"], {k: int(v) for k, v in st["key"].items()}, offs)
        elif op == "frames":
            fw, fh = st["frame_w"], st["frame_h"]
            frs = gbaart.frames(cur, fw, fh, st.get("axis", "x"))
            cur = gbaart.join_frames([frs[i] for i in st["order"]], st.get("axis", "x"))
        elif op == "save":
            gbaart.ensure_dir(R(st["dst"]))
            cur.save(R(st["dst"]))
            log("wrote " + st["dst"])
        else:
            raise ValueError("unknown op " + op)
    return cur


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(2)
    for path in sys.argv[1:]:
        data = json.load(open(path))
        steps = data["steps"] if isinstance(data, dict) else data
        run(steps)


if __name__ == "__main__":
    main()
