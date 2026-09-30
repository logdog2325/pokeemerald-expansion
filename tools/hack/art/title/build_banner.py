#!/usr/bin/env python3
"""
build_banner.py - the title screen's "DRACONID EMERALD" banner (round 1, D-277).

  python3 tools/hack/art/title/build_banner.py                 # writes the banner PNG
  python3 tools/hack/art/title/build_banner.py --preview x.png  # + a zoomed preview (scratchpad)

Built only from the vanilla "EMERALD VERSION" banner (graphics/title_screen/emerald_version.png) and
pixels drawn here (no third-party art):
  * every letter of the vanilla banner is cut out with the dark outline around it (each outline pixel
    belongs to the nearest letter face, so neighbouring letters split their shared outline);
  * "EMERALD" is the vanilla top line, verbatim (the "VERSION" line under it is dropped and the
    outline closed where the two lines shared it);
  * "DRACONID" above it reuses the vanilla D, R and A and four letters drawn here in the same style
    (GLYPHS: C, O, N, I – white face, grey bevel, dark outline, the vanilla palette's greys);
  * the letters of "DRACONID" follow an arch like vanilla's "EMERALD" (lower at the ends); the left D,
    which leans right like every letter at the right end of vanilla's arch, is sheared upright.
The output keeps the vanilla banner's palette, so the in-game look (silver letters) is unchanged.
"""

import argparse
import os
import sys
from collections import deque

from PIL import Image

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import gbaart  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "..", ".."))
SRC = os.path.join(ROOT, "graphics/title_screen/emerald_version.png")
DST = os.path.join(ROOT, "graphics/title_screen/draconid_emerald.png")

WIDTH, HEIGHT = 128, 64

# Brightness levels: the vanilla palette's 15 greys sorted dark to light ('0' .. 'e');
# '.' is transparent. The glyph maps below use this alphabet.
LEVELS = "0123456789abcde"
FACE_LEVEL = LEVELS.index("a")   # a face pixel (seed of a letter's ownership)
OUTLINE_LEVEL = 0                # the outline filled in where letters were cut apart
OUTLINE_RADIUS = 2               # every pixel this close to a face is opaque
GAP_FILL = 3                     # pinholes in the dark plate up to this wide are filled

# The vanilla letters are the components of face pixels: E, M, E, R, A, L, D on the top line, the
# "VERSION" letters under it. R and A touch at the foot of R's leg; they are split at this x.
RA_SPLIT_X = 64

# Letters drawn for "DRACONID" (face, bevel and the outline around them).
GLYPHS = {
    "C": [
        "...................",
        ".....456789985.....",
        "....3ceeeeeedb7....",
        "...3ceeeeeeeeeb6...",
        "..3ceeeeeeeeeeed5..",
        "..3eeeeebaa9aa983..",
        "..3eeeec000000000..",
        "..3eeeeb000000000..",
        "..3eeeeb000000000..",
        "..3eeeeb000000000..",
        "..3eeeec000000000..",
        "..3eeeeeeeeeeeeb3..",
        "..59eeeeeeeeeeea5..",
        "...59eeeeeeeeea6...",
        "....59cddddddb5....",
        ".....134677641.....",
        "...................",
    ],
    "O": [
        "...................",
        ".....456789985.....",
        "....3ceeeeeedb7....",
        "...3ceeeeeeeeeb6...",
        "..3ceeeeeeeeeeed5..",
        "..3eeeeeeeeeeeee5..",
        "..3eeeeea3aeeeee5..",
        "..3eeeeb000ceeee5..",
        "..3eeeeb000ceeee5..",
        "..3eeeeb000ceeee5..",
        "..3eeeee9b9eeeee5..",
        "..3eeeeeeeeeeeee5..",
        "..59eeeeeeeeeeea6..",
        "...59eeeeeeeeea6...",
        "....59cddddddb5....",
        ".....134677641.....",
        "...................",
    ],
    "N": [
        "...................",
        "...4567000007899...",
        "..3ceeb00000ceeb5..",
        "..3eeeec0000eeee5..",
        "..3eeeeec000eeee5..",
        "..3eeeeee000eeee5..",
        "..3eeeeeec00eeee5..",
        "..3eeeeeeec0deee5..",
        "..3eeeeeeee0deee5..",
        "..3eeeb09eeeeeee5..",
        "..3eeeb009eeeeee5..",
        "..3eeeb0009eeeee5..",
        "..3eeeb00009eeee5..",
        "..3eeeb00009eeee5..",
        "..39dda000009dda5..",
        "...3665000006543...",
        "...................",
    ],
    "I": [
        "...........",
        "...45678...",
        "..3ceeed5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..3eeeee5..",
        "..39dddb5..",
        "...46764...",
        "...........",
    ],
}

# "DRACONID": (letter, x, y, shear). x/y place the letter's cut (vanilla letters: moved from where they
# sit in the vanilla banner; drawn letters: their map's top-left corner). shear = pixels the top row
# moves left relative to the bottom row. The faces' tops (8, 6, 6, 5, 5, 6, 7, 8) make the arch.
LINE1 = [
    ("D", -84, 0, 2),
    ("R", -29, 1, 0),   # R and A stay the pair they are in vanilla
    ("A", -29, 1, 0),
    ("C", 47, 3, 0),
    ("O", 61, 3, 0),
    ("N", 75, 4, 0),
    ("I", 89, 5, 0),
    ("D", 8, 0, 0),
]
# "EMERALD": the vanilla line moved by (dx, dy), centred under "DRACONID".
LINE2_OFFSET = (4, 16)
CENTRE_DX = 5   # both lines move right by this to centre the banner in its 128 px


def load_levels():
    im = gbaart.load_indexed(SRC)
    pal = gbaart.palette_rgb(im)
    used = sorted({i for i in im.tobytes() if i != 0}, key=lambda i: sum(pal[i]))
    to_level = {idx: n for n, idx in enumerate(used)}
    px = im.load()
    lv = {}
    for y in range(im.height):
        for x in range(im.width):
            if px[x, y]:
                lv[(x, y)] = to_level[px[x, y]]
    return im, pal, used, lv


def components(points):
    points = set(points)
    seen = set()
    comps = []
    for p in sorted(points):
        if p in seen:
            continue
        seen.add(p)
        stack, comp = [p], []
        while stack:
            q = stack.pop()
            comp.append(q)
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                r = (q[0] + dx, q[1] + dy)
                if r in points and r not in seen:
                    seen.add(r)
                    stack.append(r)
        comps.append(comp)
    return comps


def own(lv, seeds):
    """Multi-source BFS over opaque pixels: pixel -> (owner, distance to the owner's face)."""
    owner = {}
    queue = deque()
    for name, pts in seeds.items():
        for p in pts:
            owner[p] = (name, 0)
            queue.append(p)
    while queue:
        p = queue.popleft()
        name, d = owner[p]
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)):
            q = (p[0] + dx, p[1] + dy)
            if q in lv and q not in owner:
                owner[q] = (name, d + 1)
                queue.append(q)
    return owner


def vanilla_letters(lv):
    """Cut the vanilla banner into letters: name -> {(x, y): (level, distance)}."""
    faces = [p for p, v in lv.items() if v >= FACE_LEVEL]
    names_top = ["E1", "M", "E2", "R", "A", "L", "D"]
    top, bottom = [], []
    for comp in components(faces):
        (top if min(y for _, y in comp) < 18 else bottom).append(comp)
    top.sort(key=lambda c: min(x for x, _ in c))
    bottom.sort(key=lambda c: min(x for x, _ in c))
    # R and A form one component
    seeds = {}
    i = 0
    for comp in top:
        xs = [x for x, _ in comp]
        if min(xs) < RA_SPLIT_X <= max(xs):
            seeds["R"] = [p for p in comp if p[0] < RA_SPLIT_X]
            seeds["A"] = [p for p in comp if p[0] >= RA_SPLIT_X]
            i += 2
        else:
            seeds[names_top[i]] = comp
            i += 1
    assert i == len(names_top), "unexpected vanilla letter layout"
    for n, comp in enumerate(bottom):
        seeds["v%d" % n] = comp
    owner = own(lv, seeds)
    cuts = {}
    for p, (name, d) in owner.items():
        cuts.setdefault(name, {})[p] = (lv[p], d)
    return cuts


def glyph_cut(rows):
    pts = {}
    for y, row in enumerate(rows):
        for x, ch in enumerate(row):
            if ch != ".":
                pts[(x, y)] = LEVELS.index(ch)
    faces = [p for p, v in pts.items() if v >= FACE_LEVEL]
    owner = own(pts, {"g": faces})
    return {p: (pts[p], owner.get(p, ("g", 9))[1]) for p in pts}


def shear(cut, amount):
    if not amount:
        return cut
    ys = [y for _, y in cut]
    y0, y1 = min(ys), max(ys)
    out = {}
    for (x, y), v in cut.items():
        dx = -round(amount * (y1 - y) / max(1, y1 - y0))
        out[(x + dx, y)] = v
    return out


def place(canvas, cut, dx, dy):
    for (x, y), (v, d) in cut.items():
        q = (x + dx, y + dy)
        old = canvas.get(q)
        if old is None or d < old[1] or (d == old[1] and v < old[0]):
            canvas[q] = (v, d)


def close_outline(canvas):
    """Every pixel near a face is opaque (a round brush), and the plate has no pinholes: a gap of up to
    GAP_FILL pixels between two opaque pixels in a row or a column (e.g. between the lines) is filled."""
    faces = [p for p, (v, _) in canvas.items() if v >= FACE_LEVEL]
    r = OUTLINE_RADIUS
    for (x, y) in faces:
        for dy in range(-r, r + 1):
            for dx in range(-r, r + 1):
                q = (x + dx, y + dy)
                if dx * dx + dy * dy <= r * r + 1 and q not in canvas:
                    canvas[q] = (OUTLINE_LEVEL, r)
    xs = [x for x, _ in canvas]
    ys = [y for _, y in canvas]
    holes = True
    while holes:            # until no pocket is left
        holes = []
        for y in range(min(ys), max(ys) + 1):
            for x in range(min(xs), max(xs) + 1):
                if (x, y) in canvas:
                    continue
                for ax, ay in ((1, 0), (0, 1)):
                    before = any((x - ax * k, y - ay * k) in canvas for k in range(1, GAP_FILL + 1))
                    after = any((x + ax * k, y + ay * k) in canvas for k in range(1, GAP_FILL + 1))
                    if before and after:
                        holes.append((x, y))
                        break
        for q in holes:
            canvas[q] = (OUTLINE_LEVEL, r)


def build():
    im, pal, used, lv = load_levels()
    cuts = vanilla_letters(lv)
    canvas = {}
    dx2, dy2 = LINE2_OFFSET
    for name in ["E1", "M", "E2", "R", "A", "L", "D"]:
        place(canvas, cuts[name], dx2 + CENTRE_DX, dy2)
    for letter, x, y, sh in LINE1:
        if letter in GLYPHS:
            place(canvas, glyph_cut(GLYPHS[letter]), x + CENTRE_DX, y)
        else:
            place(canvas, shear(cuts[letter], sh), x + CENTRE_DX, y)
    close_outline(canvas)
    out = gbaart.make_indexed((WIDTH, HEIGHT), pal)
    px = out.load()
    for (x, y), (v, _) in canvas.items():
        if 0 <= x < WIDTH and 0 <= y < HEIGHT:
            px[x, y] = used[v]
        else:
            print("warning: pixel outside the banner at", (x, y))
    return out


def preview(im, path, scale=6, bg=(48, 64, 120)):
    rgb = im.convert("RGB")
    px, rp = im.load(), rgb.load()
    for y in range(im.height):
        for x in range(im.width):
            if px[x, y] == 0:
                rp[x, y] = bg
    one = rgb.copy()
    big = rgb.resize((im.width * scale, im.height * scale), Image.NEAREST)
    sheet = Image.new("RGB", (big.width, big.height + im.height + 8), (0, 0, 0))
    sheet.paste(big, (0, 0))
    sheet.paste(one, (0, big.height + 4))
    sheet.save(path)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", default=DST)
    ap.add_argument("--preview")
    args = ap.parse_args()
    im = build()
    im.save(args.out)
    print("wrote", os.path.relpath(args.out, ROOT))
    if args.preview:
        preview(im, args.preview)


if __name__ == "__main__":
    main()
