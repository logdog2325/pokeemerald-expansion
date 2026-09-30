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
                                                               '0' = make transparent; "under": true
                                                               paints only transparent pixels
                                                               (behind what is already there)
  {"op": "frames", "frame_w": 16, "frame_h": 32, "order": [0,0,1,2]}
                                                               rebuild sheet from frame list
  {"op": "remap_inner", "box": [x,y,w,h], "map": {...}}        like remap_region, but only pixels
                                                               whose 4 neighbours are opaque (keeps
                                                               the outline, recolours inner shading)
  {"op": "outline", "box": [x,y,w,h], "on": [9, 14], "color": 15}
                                                               pixels of `on` next to a transparent
                                                               one become `color` (a new silhouette edge)
  {"op": "pattern", "box": [x,y,w,h], "on": [12, 13],
       "tile": ["AB..", "BA.."], "key": {"A": 12, "B": 13}}    tile an ASCII pattern over the pixels
                                                               of indices `on` ('.' = leave)
  {"op": "save", "dst": "graphics/.../walking.png"}
  {"op": "save_pal", "dst": "x.pal", "reflection": false}      write the palette (GBA colours) as
                                                               JASC; reflection = the washed-out
                                                               water-reflection version (as build_player)

The box / at of remap_region, remap_inner, outline, pattern and pixels is relative to a frame:
"frames": [0, 3], "frame_w": 16 repeats the step on those frames of a sheet (frames side by side),
"frame_h": 64 with "axis": "y" on stacked frames (back pics). Without "frames" it is applied once.
"shift": {"3": [0, 1]} moves the step for single frames (NPC walk frames sit 1 px below the stand).

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


def draw_rows(dst, at, rows, key, frame_offsets=((0, 0),), under=False):
    dp = dst.load()
    for fx, fy in frame_offsets:
        for j, row in enumerate(rows):
            for i, ch in enumerate(row):
                if ch == ".":
                    continue
                x, y = at[0] + fx + i, at[1] + fy + j
                if not (0 <= x < dst.width and 0 <= y < dst.height):
                    continue
                if under and dp[x, y] != 0:
                    continue
                dp[x, y] = 0 if ch == "0" else key[ch]


def outline_box(im, box, off, on, color):
    """Pixels of indices `on` that touch a transparent pixel (4-neighbours) become `color`."""
    px = im.load()
    src = im.copy().load()
    for x, y in box_pixels(im, box, off):
        if src[x, y] in on and any(not (0 <= x + dx < im.width and 0 <= y + dy < im.height)
                                   or src[x + dx, y + dy] == 0
                                   for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
            px[x, y] = color


def frame_offsets(st):
    """(dx, dy) of every frame a step applies to ("frames" + "frame_w", or "frame_h" with axis y),
    plus an optional per-frame "shift": {"3": [0, 1]} (walk frames drawn 1 px lower than the stand)."""
    frames = st.get("frames", [0])
    shift = st.get("shift", {})
    out = []
    for f in frames:
        sx, sy = shift.get(str(f), (0, 0))
        if st.get("axis", "x") == "y":
            out.append((sx, f * st.get("frame_h", 0) + sy))
        else:
            out.append((f * st.get("frame_w", 0) + sx, sy))
    return out


def box_pixels(im, box, off):
    x0, y0, w, h = box
    for y in range(y0 + off[1], y0 + off[1] + h):
        for x in range(x0 + off[0], x0 + off[0] + w):
            if 0 <= x < im.width and 0 <= y < im.height:
                yield x, y


def remap_box(im, box, off, table, inner=False):
    px = im.load()
    src = im.copy().load() if inner else px

    def opaque(x, y):
        return 0 <= x < im.width and 0 <= y < im.height and src[x, y] != 0

    for x, y in box_pixels(im, box, off):
        if inner and not all(opaque(x + dx, y + dy) for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
            continue
        px[x, y] = table[src[x, y]]


def tile_pattern(im, box, off, on, tile, key):
    px = im.load()
    th, tw = len(tile), len(tile[0])
    for x, y in box_pixels(im, box, off):
        if px[x, y] in on:
            ch = tile[(y - box[1] - off[1]) % th][(x - box[0] - off[0]) % tw]
            if ch != ".":
                px[x, y] = key[ch]


def reflection_palette(pal):
    """Water reflections: washed out and slightly blue (same formula as player/build_player.py)."""
    out = [gbaart.gba_color(tuple(min(255, int(0.58 * v + b)) for v, b in zip(c, (106, 112, 116)))) for c in pal]
    out[0] = pal[0]
    return out


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
        elif op in ("remap_region", "remap_inner"):
            table = _remap_table(st["map"])
            for off in frame_offsets(st):
                remap_box(cur, st["box"], off, table, inner=(op == "remap_inner"))
        elif op == "pattern":
            key = {k: int(v) for k, v in st["key"].items()}
            for off in frame_offsets(st):
                tile_pattern(cur, st["box"], off, set(st["on"]), st["tile"], key)
        elif op == "paste":
            src = gbaart.load_indexed(R(st["src"]))
            table = _remap_table(st["map"]) if "map" in st else None
            box = st.get("box", [0, 0, src.width, src.height])
            paste_indexed(cur, src, box, st.get("at", [0, 0]), table, st.get("flip"))
        elif op == "pixels":
            draw_rows(cur, st["at"], st["rows"], {k: int(v) for k, v in st["key"].items()}, frame_offsets(st),
                      st.get("under", False))
        elif op == "outline":
            for off in frame_offsets(st):
                outline_box(cur, st["box"], off, set(st["on"]), st["color"])
        elif op == "frames":
            fw, fh = st["frame_w"], st["frame_h"]
            frs = gbaart.frames(cur, fw, fh, st.get("axis", "x"))
            cur = gbaart.join_frames([frs[i] for i in st["order"]], st.get("axis", "x"))
        elif op == "save":
            gbaart.ensure_dir(R(st["dst"]))
            cur.save(R(st["dst"]))
            log("wrote " + st["dst"])
        elif op == "save_pal":
            pal = [gbaart.gba_color(c) for c in gbaart.palette_rgb(cur, 16)]
            if st.get("reflection"):
                pal = reflection_palette(pal)
            gbaart.ensure_dir(R(st["dst"]))
            gbaart.write_jasc(R(st["dst"]), pal)
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
