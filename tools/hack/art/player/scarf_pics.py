#!/usr/bin/env python3
"""
scarf_pics.py - draw the Draconid tamer's scarf on the 64x64 pics (front, back, credits run cycle).

The scarf on the trainer pics is too big to type as ASCII by hand, so its shapes are written here as
polygons and region fills; this script turns them into ASCII "overlays" in the pic specs, which
build_pics.py then draws. The specs stay the source of truth (a hand edit there is kept until this
script is run again for that pic).

  python3 tools/hack/art/player/scarf_pics.py [m_front m_back f_front f_back m_credits f_credits]
  python3 tools/hack/art/player/build_pics.py tools/hack/art/player/draconid_m_pics.json   # etc.

Every shape is filled with the scarf red ('R'), outlined in black where it meets anything but the
body's own outline ('K'), darkened along one side ('r') and tiled with the fish-scale pattern SCALES.
Coordinates are pixels of the 64x64 frame (see docs/hack_art_pipeline.md, round 1 scarf).
"""

import argparse
import json
import os
import sys
import tempfile

from PIL import Image, ImageDraw

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_pics  # noqa: E402
from build_player import ROOT  # noqa: E402

K = 15
ALL = set(range(16))
# U-shaped scales 4 px wide and 3 rows tall, each row offset by half a scale
SCALES = ["rRRR",
          "rRRR",
          "Rrrr",
          "RRrR",
          "RRrR",
          "rrRr"]
SIDES = {"down": (0, 1), "up": (0, -1), "left": (-1, 0), "right": (1, 0)}


def base_image(p):
    """The pic as build_pics.py makes it, without the scarf overlays."""
    q = json.loads(json.dumps(p))
    q.pop("overlays", None)
    with tempfile.TemporaryDirectory() as td:
        q["out"] = os.path.join(td, "base.png")
        old, sys.stdout = sys.stdout, open(os.devnull, "w")
        try:
            im, _, fh = build_pics.build_pic(q)
        finally:
            sys.stdout.close()
            sys.stdout = old
    return im, fh


class Frame:
    """One frame of a pic: the base indices and the overlay being drawn (None = keep)."""

    def __init__(self, im, fy, fh):
        self.w, self.h = im.width, fh
        px = im.load()
        self.base = [[px[x, fy + y] for x in range(self.w)] for y in range(fh)]
        self.grid = [[None] * self.w for _ in range(fh)]

    def inside(self, x, y):
        return 0 <= x < self.w and 0 <= y < self.h

    def polygon(self, pts):
        mask = Image.new("L", (self.w, self.h), 0)
        ImageDraw.Draw(mask).polygon(pts, fill=1)
        mp = mask.load()
        return {(x, y) for y in range(self.h) for x in range(self.w) if mp[x, y]}

    def fill(self, pts, allowed, **kw):
        """Paint a polygon over the pixels `allowed` lets through: a set of base indices (0 = transparent)
        or a predicate (x, y, index)."""
        ok = allowed if callable(allowed) else (lambda x, y, i: i in allowed)
        self.paint({(x, y) for x, y in self.polygon(pts) if ok(x, y, self.base[y][x])}, **kw)

    def region(self, seeds, over, box, extra=None, keep=None):
        """The pixels reached from indices `seeds` through indices `over` inside box (x0, y0, x1, y1),
        plus black pixels enclosed by them (straps, seams); `extra` polygons add pixels of `over` or
        transparent ones; keep(x, y) excludes pixels. Used to turn Red's backpack into the cape."""
        x0, y0, x1, y1 = box

        def inb(x, y):
            return x0 <= x <= x1 and y0 <= y <= y1 and self.inside(x, y) and not (keep and keep(x, y))

        def enclosed(x, y):
            nb = ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1))
            return all(self.inside(nx, ny) and self.base[ny][nx] in over | {K} for nx, ny in nb)

        ok = {(x, y) for y in range(y0, y1 + 1) for x in range(x0, x1 + 1)
              if inb(x, y) and (self.base[y][x] in over or (self.base[y][x] == K and enclosed(x, y)))}
        reg = {(x, y) for x, y in ok if self.base[y][x] in seeds}
        stack = list(reg)
        while stack:
            x, y = stack.pop()
            for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
                if n in ok and n not in reg:
                    reg.add(n)
                    stack.append(n)
        for poly in extra or []:
            reg |= {(x, y) for x, y in self.polygon(poly) if inb(x, y) and self.base[y][x] in over | {0}}
        return reg

    def paint(self, region, shade="down", scales=True, phase=(0, 0)):
        """Outline, shade one side, tile the scales (or plain red)."""
        out = set()
        for x, y in region:
            for nx, ny in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
                if (nx, ny) in region or not self.inside(nx, ny):
                    continue  # the frame edge is not an edge of the scarf
                if self.base[ny][nx] != K or self.grid[ny][nx] is not None:
                    out.add((x, y))
                    break
        inner = region - out
        dark = set()
        if shade:
            dx, dy = SIDES[shade]
            dark = {(x, y) for x, y in inner if (x + dx, y + dy) not in inner and self.inside(x + dx, y + dy)}
        px0, py0 = phase
        for x, y in region:
            if (x, y) in out:
                ch = "K"
            elif (x, y) in dark:
                ch = "r"
            elif scales:
                ch = SCALES[(y + py0) % len(SCALES)][(x + px0) % len(SCALES[0])]
            else:
                ch = "R"
            self.grid[y][x] = ch

    def line(self, pts, ch="r"):
        """A 1 px fold line over the scarf drawn so far."""
        img = Image.new("L", (self.w, self.h), 0)
        ImageDraw.Draw(img).line(pts, fill=1)
        ip = img.load()
        for y in range(self.h):
            for x in range(self.w):
                if ip[x, y] and self.grid[y][x] not in (None, "K"):
                    self.grid[y][x] = ch

    def overlay(self, frame=None):
        pts = [(x, y) for y in range(self.h) for x in range(self.w) if self.grid[y][x] is not None]
        if not pts:
            return None
        x0, x1 = min(x for x, _ in pts), max(x for x, _ in pts)
        y0, y1 = min(y for _, y in pts), max(y for _, y in pts)
        o = {"at": [x0, y0], "rows": ["".join(self.grid[y][x] or "." for x in range(x0, x1 + 1))
                                      for y in range(y0, y1 + 1)]}
        if frame is not None:
            o["frames"] = [frame]
        return o


# ------------------------------------------------------------------ male front pic
def m_front(f):
    # both ends stream out behind his right shoulder (viewer's left), over where Red's backpack was
    bag = lambda x, y, i: i == 0 or (x <= 28 and 27 <= y <= 40 and i in (11, 4, 15, 13, 8))  # noqa: E731
    f.fill([(28, 29), (28, 39), (25, 41), (21, 44), (19, 51), (16, 45), (11, 49), (13, 41), (15, 35), (19, 31),
            (23, 29)], bag, shade="left", phase=(1, 0))
    f.fill([(25, 26), (18, 26), (11, 27), (3, 29), (9, 31), (15, 33), (23, 33)], bag, shade="down", phase=(2, 1))
    # the wrap around the neck, over the collar, with a fold
    f.fill([(24, 26), (26, 24), (29, 25), (33, 25), (36, 24), (38, 25), (39, 27), (37, 29), (33, 30), (29, 30),
            (26, 29), (24, 28)], ALL, scales=False)
    f.line([(26, 27), (30, 28), (34, 28), (37, 27)])


# ------------------------------------------------------------------ male back pic (idle + throw)
BACK_OVER = {13, 14, 4, 1, 11, 12, 8}  # the backpack's reds, browns and the jacket's back


def m_back(box, wrap, keep=None):
    def fn(f):
        f.paint(f.region({13, 14}, BACK_OVER, box, keep=keep), shade="left")
        f.fill(wrap, ALL, scales=False)
    return fn


def m_back_throw(wrap):
    def fn(f):
        # the arm stays in front; only the strap's teal (left of x 10) joins the cape, not the jacket
        keep = lambda x, y: ((x <= 14 and y >= 48 and f.base[y][x] in (2, 3, 4))  # noqa: E731
                             or (x > 10 and f.base[y][x] == 12))
        f.paint(f.region({13, 14}, {13, 14, 4, 1, 12}, (0, 36, 24, 63), keep=keep), shade="left")
        f.fill(wrap, ALL, scales=False)
    return fn


M_BACK = [
    m_back((0, 43, 41, 63), [(31, 41), (34, 40), (40, 40), (44, 41), (45, 44), (42, 46), (36, 46), (31, 45)],
           keep=lambda x, y: x >= 38 and y >= 55),
    m_back((12, 44, 37, 63), [(16, 46), (19, 44), (24, 43), (29, 43), (31, 45), (30, 49), (24, 50), (18, 49)]),
    m_back((3, 43, 34, 63), [(17, 43), (20, 41), (27, 40), (32, 41), (33, 44), (29, 46), (21, 46), (17, 45)],
           keep=lambda x, y: x <= 8 and y <= 50),
    m_back_throw([(20, 38), (24, 36), (30, 36), (36, 37), (38, 39), (35, 41), (28, 42), (21, 41)]),
    m_back_throw([(21, 44), (25, 42), (31, 42), (37, 43), (38, 45), (35, 47), (28, 48), (21, 47)]),
]


# ------------------------------------------------------------------ female front pic
def f_front(f):
    # both ends stream out over her left shoulder and the long hair (viewer's right), away from the red skirt
    over_hair = lambda x, y, i: x >= 36 and (i in (0, 4, 8, 15) or (y < 31 and i in (1, 2, 3)))  # noqa: E731
    f.fill([(37, 27), (44, 28), (51, 29), (61, 32), (55, 34), (57, 37), (48, 35), (42, 33), (38, 31)], over_hair,
           phase=(1, 0))
    f.fill([(36, 23), (41, 21), (48, 18), (59, 13), (55, 18), (58, 20), (50, 23), (44, 26), (38, 27)], over_hair,
           phase=(2, 1))
    f.fill([(26, 25), (28, 24), (31, 24), (34, 24), (36, 25), (36, 27), (33, 28), (29, 28), (26, 27)], ALL,
           scales=False)


# ------------------------------------------------------------------ female back pic: over the long hair
HAIR = {4, 1, 8, 15, 0}


def f_back(band, upper, lower):
    def fn(f):
        f.fill(lower, HAIR, shade="left", phase=(1, 0))
        f.fill(upper, HAIR, phase=(3, 0))
        f.fill(band, ALL, scales=False)
    return fn


F_BACK = [
    f_back([(13, 43), (22, 42), (30, 41), (36, 40), (41, 40), (42, 43), (37, 46), (29, 46), (20, 47), (14, 47)],
           [(20, 41), (12, 41), (5, 43), (0, 46), (4, 48), (1, 52), (8, 51), (14, 49), (20, 47)],
           [(20, 46), (17, 50), (14, 55), (8, 63), (11, 57), (7, 58), (10, 52), (14, 47)]),
    f_back([(14, 46), (24, 45), (33, 44), (40, 43), (42, 46), (37, 48), (26, 49), (15, 50)],
           [(18, 48), (14, 52), (10, 56), (7, 62), (11, 59), (12, 62), (16, 56), (21, 50)],
           [(24, 49), (23, 54), (21, 59), (19, 63), (23, 60), (26, 63), (26, 56), (28, 50)]),
    f_back([(19, 44), (28, 43), (36, 42), (43, 41), (45, 44), (40, 47), (30, 47), (20, 48)],
           [(21, 46), (14, 48), (8, 51), (3, 55), (8, 56), (5, 59), (12, 56), (17, 53), (22, 50)],
           [(22, 50), (19, 54), (16, 58), (11, 63), (15, 61), (17, 63), (20, 57), (23, 53)]),
    f_back([(18, 40), (26, 39), (33, 38), (39, 37), (40, 40), (35, 42), (26, 43), (18, 44)],
           [(19, 40), (12, 40), (5, 41), (0, 43), (5, 45), (2, 48), (10, 46), (15, 45), (20, 44)],
           [(19, 44), (13, 46), (7, 48), (2, 51), (7, 52), (5, 55), (12, 51), (18, 48)]),
    f_back([(18, 44), (26, 43), (33, 42), (40, 41), (41, 44), (36, 46), (27, 47), (18, 48)],
           [(19, 44), (12, 44), (5, 45), (0, 47), (5, 49), (2, 52), (10, 50), (15, 48), (20, 47)],
           [(19, 48), (14, 51), (9, 54), (4, 58), (9, 57), (8, 60), (14, 55), (19, 52)]),
]


# ------------------------------------------------------------------ credits run cycles (running left)
FLUTTER = [(0, 0), (1, -1), (-1, 1)]  # the two tips move a pixel from frame to frame


def m_credits(f, i):
    """The ends stream out behind (right) over the backpack, anchored on it (its right end, its top)."""
    over, box = {13, 14, 1, 4}, (33, 6, 63, 40)
    bag = f.region({13, 14}, over, box)
    rx, ty = max(x for x, _ in bag), min(y for _, y in bag)
    a, b = FLUTTER[i % len(FLUTTER)]
    stream = [(rx - 9, ty - 1), (rx + 1, ty - 3), (rx + 8, ty - 5), (rx + 15, ty - 8 + a), (rx + 11, ty - 1),
              (rx + 17, ty + 3 + b), (rx + 9, ty + 5), (rx + 3, ty + 8), (rx - 1, ty + 11)]
    f.paint(f.region({13, 14}, over, box, extra=[stream]), phase=(i, 0))
    f.fill([(rx - 21, ty + 1), (rx - 16, ty), (rx - 11, ty - 1), (rx - 8, ty + 1), (rx - 10, ty + 4),
            (rx - 16, ty + 4), (rx - 21, ty + 3)], ALL, scales=False)


def f_credits(f, i):
    """Anchored on the teal headband (the right end of its top row); the ends stream out over the hair."""
    band = [(x, y) for y in range(24) for x in range(f.w) if f.base[y][x] == 7]
    ty = min(y for _, y in band)
    rx = max(x for x, y in band if y == ty)
    a, b = FLUTTER[i % len(FLUTTER)]
    f.fill([(rx - 2, ty + 10), (rx + 5, ty + 8), (rx + 11, ty + 7), (rx + 19, ty + 4 + a), (rx + 15, ty + 11),
            (rx + 21, ty + 14 + b), (rx + 12, ty + 15), (rx + 5, ty + 15), (rx - 1, ty + 14)], {0, 1, 4, 8, 15},
           phase=(i, 0))
    f.fill([(rx - 8, ty + 10), (rx - 4, ty + 9), (rx, ty + 9), (rx + 1, ty + 12), (rx - 4, ty + 13),
            (rx - 8, ty + 12)], ALL, scales=False)


def per_frame(fn, n):
    return [lambda f, i=i: fn(f, i) for i in range(n)]


# key: (spec, pic index, one function per frame, scarf roles R/r = the pic's palette indices)
JOBS = {
    "m_front": ("draconid_m_pics.json", 0, [m_front], {"R": 10, "r": 11}),
    "m_back": ("draconid_m_pics.json", 1, M_BACK, {"R": 13, "r": 14}),
    "f_front": ("draconid_f_pics.json", 0, [f_front], {"R": 12, "r": 13}),
    "f_back": ("draconid_f_pics.json", 1, F_BACK, {"R": 11, "r": 12}),
    "m_credits": ("draconid_credits.json", 0, per_frame(m_credits, 6), {"R": 13, "r": 14}),
    "f_credits": ("draconid_credits.json", 1, per_frame(f_credits, 6), {"R": 11, "r": 12}),
}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("jobs", nargs="*", help="any of %s (default: all)" % ", ".join(JOBS))
    args = ap.parse_args()
    unknown = [j for j in args.jobs if j not in JOBS]
    if unknown:
        ap.error("unknown job(s): " + ", ".join(unknown))
    for key in args.jobs or list(JOBS):
        name, pic, frames, roles = JOBS[key]
        path = os.path.join(ROOT, "tools/hack/art/player", name)
        spec = json.load(open(path))
        p = spec["pics"][pic]
        p["roles"].update(roles)
        im, fh = base_image(p)
        overlays = []
        for i, fn in enumerate(frames):
            f = Frame(im, i * fh, fh)
            fn(f)
            o = f.overlay(i if fh < im.height else None)
            if o:
                overlays.append(o)
        p["overlays"] = overlays
        open(path, "w").write(json.dumps(spec, indent=1))
        print("updated %s (%s)" % (name, p["out"]))


if __name__ == "__main__":
    main()
