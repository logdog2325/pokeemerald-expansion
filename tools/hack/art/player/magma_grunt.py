#!/usr/bin/env python3
"""
magma_grunt.py - build the player's Team Magma disguise (PLAYER_OUTFIT_MAGMA) as an ordinary grunt.

Overworld, graphics/object_events/pics/people/magma_{m,f}/: the walking sheet *is* the vanilla grunt
(team_magma/magma_member_{m,f}.png, index for index); every other pose the outfit system draws is built
from the grunt's own walk frames - hood, face, torso, legs - plus small drawn patches (arms, gloves, the
Poke Ball). The props come from the FRLG Red sheets that the old disguise was built on: the Mach Bike
(red_bike.png) and the fishing rods (red_fish.png), recoloured; the frame positions follow those sheets
so the engine's animations line up as before. The palettes are npc_2.pal's grunt colours (index for
index) plus greys for the bike and rod; the player F has navy hair like the female grunt's front pic.
The derived sheets (Acro Bike, underwater, watering, decorating, region map icon) and the palette files
come from the "derived" / "palette" entries of magma_{m,f}.json (build_player.build_derived).

Battle back pic, graphics/trainers/back_pics/magma_{m,f}.png (5 frames, sBackAnims_Kanto): drawn in
the vanilla grunt front pic's palette (front_pics/magma_grunt_{m,f}.png, all 16 colours). The hood is
drawn here (dome, centre seam, folds, folded rim with a sliver of the face, two dark-grey horn
points); the body is Game Freak's back-pic cloth and arms re-coloured: the male on Steven's back pic
(broad build; suit -> red top, cuffs -> grey wristbands, hands -> grey gloves), the female on Leaf's
poses (hat removed, hair -> navy, top -> red, bag strap removed, hands -> grey gloves, skirt -> grey).
Kanto frame order: 0 idle, 1 wind-up (ball in hand), 2 arm up (ball), 3 release, 4 follow-through.
Tabitha's back pic (back_pics/magma_admin.png, his Space Center partner role) is the male grunt's frames in
his deeper crimson admin jacket.

  python3 tools/hack/art/player/magma_grunt.py                    # write every sheet, pic and palette
  python3 tools/hack/art/player/magma_grunt.py --preview DIR      # also write enlarged previews

Brendan's and May's graphics are never read. See docs/hack_art_pipeline.md ("Round 2: the Magma
disguise as a real grunt") and D-380.
"""

import argparse
import json
import math
import os
import sys

from PIL import Image

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_player import ROOT, build_derived, gba_color, write_jasc  # noqa: E402

PEOPLE = "graphics/object_events/pics/people/"
GRUNT = {"m": PEOPLE + "team_magma/magma_member_m.png", "f": PEOPLE + "team_magma/magma_member_f.png"}
RED_BIKE = PEOPLE + "red/red_bike.png"
RED_FISH = PEOPLE + "red/red_fish.png"
SPEC = {s: "tools/hack/art/player/magma_%s.json" % s for s in "mf"}
STEVEN_BACK = "graphics/trainers/back_pics/steven.png"
LEAF_BACK = "graphics/trainers/back_pics/leaf.png"
FRONT_PIC = {"m": "graphics/trainers/front_pics/magma_grunt_m.png",
             "f": "graphics/trainers/front_pics/magma_grunt_f.png"}
BACK_OUT = {"m": "graphics/trainers/back_pics/magma_m.png", "f": "graphics/trainers/back_pics/magma_f.png"}

# grey indices of the bike / rod / watering can per gender (the female grunt uses 7 for her hair)
GREY = {"m": {"hi": 0x5, "mid": 0x6, "dark": 0x7}, "f": {"hi": 0x5, "mid": 0x6, "dark": 0xd}}


# ------------------------------------------------------------------------------------------ helpers
def load(path):
    return Image.open(os.path.join(ROOT, path))


def frame(path, w, h, i):
    im = load(path)
    px = im.load()
    vert = im.width == w and im.height > h
    ox, oy = (0, i * h) if vert else (i * w, 0)
    return [[px[ox + x, oy + y] for x in range(w)] for y in range(h)]


def blank(w, h):
    return [[0] * w for _ in range(h)]


def copy(g):
    return [r[:] for r in g]


def paste(dst, src, dx=0, dy=0, rect=None, remap=None):
    h, w = len(src), len(src[0])
    x0, y0, x1, y1 = rect or (0, 0, w - 1, h - 1)
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            v = src[y][x]
            if not v:
                continue
            v = remap.get(v, v) if remap else v
            tx, ty = x + dx, y + dy
            if 0 <= ty < len(dst) and 0 <= tx < len(dst[0]):
                dst[ty][tx] = v
    return dst


def draw(dst, rows, dx=0, dy=0, cmap=None):
    """ASCII patch: hex digit = palette index, '.' keeps, '_' clears; cmap re-maps characters first."""
    for ty, r in enumerate(rows):
        for tx, c in enumerate(r):
            if cmap and c in cmap:
                c = cmap[c]
            if c == ".":
                continue
            x, y = dx + tx, dy + ty
            if 0 <= y < len(dst) and 0 <= x < len(dst[0]):
                dst[y][x] = 0 if c == "_" else int(c, 16)
    return dst


def rows_of(g, y0, y1):
    return ["".join("%x" % v if v else "." for v in g[y]) for y in range(y0, y1 + 1)]


def shift_rows(g, y0, y1, dx, dy):
    part = blank(len(g[0]), len(g))
    paste(part, g, rect=(0, y0, len(g[0]) - 1, y1))
    out = copy(g)
    for y in range(y0, y1 + 1):
        out[y] = [0] * len(g[0])
    return paste(out, part, dx, dy)


def comp(w, h, layers, cmap=None):
    g = blank(w, h)
    for rows, x, y in layers:
        draw(g, rows, x, y, cmap)
    return g


def in_poly(x, y, pts):
    c = False
    for i in range(len(pts)):
        x1, y1 = pts[i]
        x2, y2 = pts[(i + 1) % len(pts)]
        if (y1 > y) != (y2 > y) and x < x1 + (y - y1) * (x2 - x1) / (y2 - y1):
            c = not c
    return c


def line_px(pts):
    out = []
    for (x0, y0), (x1, y1) in zip(pts, pts[1:]):
        n = max(abs(x1 - x0), abs(y1 - y0), 1)
        for i in range(n + 1):
            p = (round(x0 + (x1 - x0) * i / n), round(y0 + (y1 - y0) * i / n))
            if not out or out[-1] != p:
                out.append(p)
    return out


def nb4(x, y):
    return ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1))


def save_sheet(frames, w, h, palette, path, vertical=False):
    n = len(frames)
    im = Image.new("P", (w, h * n) if vertical else (w * n, h), 0)
    flat = [v for c in palette for v in c]
    im.putpalette(flat + [0] * (768 - len(flat)))
    px = im.load()
    for i, g in enumerate(frames):
        ox, oy = (0, i * h) if vertical else (i * w, 0)
        for y in range(h):
            for x in range(w):
                px[ox + x, oy + y] = g[y][x]
    im.save(os.path.join(ROOT, path))
    print("wrote", path)
    return im


# ------------------------------------------------------------------------------------------ overworld
class Grunt:
    """The vanilla grunt's walk frames and the parts the other poses are built from."""

    def __init__(self, s):
        self.s = s
        self.walk = [frame(GRUNT[s], 16, 32, i) for i in range(9)]
        w0, w1, w2 = self.walk[0], self.walk[1], self.walk[2]
        self.head_d, self.torso_d, self.legs_d = rows_of(w0, 11, 20), rows_of(w0, 21, 26), rows_of(w0, 27, 30)
        self.head_u, self.torso_u, self.legs_u = rows_of(w1, 11, 20), rows_of(w1, 21, 26), rows_of(w1, 27, 30)
        self.head_l, self.torso_l, self.legs_l = rows_of(w2, 11, 21), rows_of(w2, 22, 27), rows_of(w2, 28, 30)
        g = GREY[s]
        # patch characters: 'G'/'g' glove (M: the grunt's long black gloves; F: bare hands), 'R'/'r'/'w' rod
        # or can greys, 'W' white
        if s == "m":
            self.cmap = {"G": "c", "g": "d", "S": "3", "s": "4", "H": "9", "h": "8"}
        else:
            self.cmap = {"G": "2", "g": "3", "S": "3", "s": "4", "H": "b", "h": "b"}
        self.cmap.update({"R": "%x" % g["mid"], "r": "%x" % g["dark"], "w": "%x" % g["hi"], "W": "e"})


def lean(g, waist, dx=0, dy=1):
    out = blank(16, 32)
    paste(out, g, rect=(0, waist + 1, 15, 31))
    top = blank(16, 32)
    paste(top, g, dx, dy, rect=(0, 0, 15, waist))
    return paste(out, top)


def running(G):
    """Running: the standing frames crouch a pixel (torso over the boots), the side frames lean forward."""
    W = G.walk
    r = [comp(16, 32, [(G.head_d, 0, 12), (G.torso_d, 0, 22), (G.legs_d[1:], 0, 28)]),
         comp(16, 32, [(G.head_u, 0, 12), (G.torso_u, 0, 22), (G.legs_u[1:], 0, 28)]),
         comp(16, 32, [(G.head_l, -1, 12), (G.torso_l[:5], -1, 23), (G.legs_l, 0, 28)])]
    r += [copy(W[i]) for i in (3, 4, 5, 6)]
    r += [shift_rows(W[i], 0, 25, -1, 0) for i in (7, 8)]
    return r


def surfing(G):
    """Surfing (sitting on the surf blob): the walk frames without the trousers / thigh row."""
    s0 = comp(16, 32, [(G.head_d, 0, 11), (G.torso_d, 0, 21), (G.legs_d[1:], 0, 27)])
    back = ["...ffffffffff...", "....ffffffff...."] if G.s == "m" else ["...4933443394...", "....ffffffff...."]
    s1 = comp(16, 32, [(G.head_u, 0, 11), (G.torso_u, 0, 21), (back, 0, 27)])
    s2 = comp(16, 32, [(G.head_l, 0, 11), (G.torso_l[:5], 0, 22), (G.legs_l, 0, 27)])
    return [s0, s1, s2]


# field move: right arm raised beside the hood, a dip, the ball at the chest, at the shoulder, thrust up
FIELD = {
    "m": [
        [(0, 16, [".ff.", "fGGf", "fggf", ".ff9", ".fS9", ".s48", "..4f", "...f", "___f", "___f", "_fff"])],
        [(0, 13, [".ff.", "fGGf", "fggf", ".ffa", ".ffa", ".fS9", ".sS9", ".fS9", ".s48", "..4f", "...f", "___f",
                  "___f", "_fff"])],
        [(0, 21, ["..48943333498a..", ".423f9dffd9f324.", ".f3fGff88ffGf3f.", "_ffdGfWWWfGdff_", "_.ff9fffff9fff._",
                  "_.ffff9999ffff._"])],
        [(0, 19, ["............ff..", "...........f88f.", "..48943333498WWf", ".42399d44d9fGGf.", ".ff39f9999fggf._",
                  "fccf9ff99ff9f.__", "fddfdf9ff9fdf___", ".ffff999999ff___"])],
        [(0, 14, ["............ff..", "...........f88f.", "...........fWWf.", "...........fGGf.", "...........fggf.",
                  "............ff..", "............fSf.", "..48943333498f4.", ".42399d44d99f_._", ".ff39f9999f9f.__",
                  "fccf9ff99ff9f___", "fddfdf9ff9fdf___", ".ffff999999ff___"])],
    ],
    "f": [
        [(0, 15, [".ff.", "f23f", "f34f", ".f3f", ".f3c", ".f3c", ".44c", "..4c", "..cb", "_.cc", "__.c", "___c"])],
        [(0, 12, [".ff.", "f23f", "f34f", ".f3a", ".f3a", ".f3a", ".43c", ".f3c", ".44c", "..4c", "..cb", "_.cc",
                  "__.c", "___c"])],
        [(0, 23, ["..ccbf88ffbcc..", ".c2f2f8eef2f2c.", "_.f33fWeefff33f._"[:16], "..44ffffff44..._"])],
        [(0, 19, ["............ff..", "...........f88f.", "..cb43333334fWWf", "..cbbf4444f23f..", "..ccbffffff34f._",
                  ".c23c9ffff9cf___", "423fff9ee9fff___", ".4448ffffff8f___"])],
        [(0, 14, ["............ff..", "...........f88f.", "...........fWWf.", "...........f23f.", "...........f34f.",
                  "............f3f.", "............f3f.", "..cb43333334f4..", "..cbbf4444fbf_._", "..ccbffffffcf.__",
                  ".c23c9ffff9cf___", "423fff9ee9fff___", ".4448ffffff8f___"])],
    ],
}


def field_move(G):
    base = G.walk[0]
    dip = comp(16, 32, [(G.head_d, 0, 12), (G.torso_d, 0, 22), (G.legs_d[1:], 0, 28)])
    out = []
    for i, patches in enumerate(FIELD[G.s]):
        g = copy(dip if i == 1 else base)
        for x, y, rows in patches:
            draw(g, rows, x, y, G.cmap)
        out.append(g)
    return out


# Mach Bike: the rider from the grunt's parts on Red's bike (recoloured)
BIKE_MAP = {"m": {0x6: 0x7, 0x4: 0x7, 0x8: 0x9, 0xa: 0x5, 0x9: 0xe, 0xc: 0x9, 0xe: 0x9, 0x7: 0x7, 0xd: 0x5,
                  0xb: 0x8, 0x5: 0x5, 0x2: 0x2, 0x3: 0x3, 0x1: 0x1},
            "f": {0x6: 0xd, 0x4: 0xd, 0x8: 0x9, 0xa: 0x5, 0x9: 0xe, 0xc: 0x9, 0xe: 0x9, 0x7: 0xd, 0xd: 0x5,
                  0xb: 0x8, 0x5: 0x5, 0x2: 0x2, 0x3: 0x3, 0x1: 0x1}}
BIKE_D = {  # local rows 20-26: shoulders, gloves on the grips, handlebar
    "m": ["..48943333498a..", ".42399d44d99324.", ".ff39f9999f93ff.", ".fGGf9f99f9fGGf.", "..fggf9ff9fggf..",
          "..fGfff99fffGf..", "...ffffffffff..."],
    "f": ["..cb43333334bc..", "..cbbf4444fbbc..", "..ccbffffffbcc..", "..c4c9ffff9c4c..", "..f23f9ee9f32f..",
          "..f3fff99fff3f..", "...ffffffffff..."],
}
BIKE_U = {  # local rows 19-26
    "m": ["..a89aaaaaa98a..", ".42399999999324.", ".ff3a999999a3ff.", ".fGfa999999afGf.", "..fgfaaaaaafgf..",
          "...ffddddddff...", "...ff.ffff.ff...", "....f.f99f.f...."],
    "f": ["..c4bbaffabb4c..", "..c44ffffff4bc..", "..cbffffffffbc..", "..cf9ffffff9fc..", "...f9ffffff9f...",
          "...ff999999ff...", "...ff.ffff.ff...", "....f.f99f.f...."],
}
BIKE_WHEEL = [".....f9rf9f.....", ".....f9wf9f.....", "......frff......", ".......rf.......", ".......ff......."]
BIKE_L = {  # rows 20-28 at x 8: shoulder, arm forward to the handlebar, the leg on the pedal
    "m": [".....448899a....", "....fS389999a...", ".fGGff99f999a...", ".fggf.f9ff99a...", "..ff..f99999a...",
          ".....fffffffa...", ".....f9ff.......", ".....f99f.......", ".....fddf......."],
    "f": [".....4bb47f.....", "....f42ff4f.....", ".f23ff9ff9f.....", ".f34f.f9ee9f....", "..ff..fffff.....",
          ".....f43334f....", ".....f434f......", ".....f989f......", ".....fffff......"],
}


def bike(G):
    s = G.s
    hd = G.head_d
    hu = G.head_u
    hl = G.head_l
    foot = ["f99f", "fddf", ".ff."] if s == "m" else ["f98f", "f89f", ".ff."]

    def down(dx, side=None):
        g = comp(32, 32, [(hd, 8 + dx, 10), (BIKE_D[s], 8 + dx, 20)], G.cmap)
        draw(g, BIKE_WHEEL, 8, 27, G.cmap)
        if side:
            draw(g, foot, 9 if side == "l" else 19, 25)
        return g

    def up(dx, side=None):
        g = comp(32, 32, [(hu, 8 + dx, 9), (BIKE_U[s], 8 + dx, 19)], G.cmap)
        draw(g, BIKE_WHEEL, 8, 27, G.cmap)
        if side:
            draw(g, foot, 10 if side == "l" else 18, 26)
        return g

    def left(i):
        g = blank(32, 32)
        paste(g, frame(RED_BIKE, 32, 32, i), rect=(0, 25, 31, 31), remap=BIKE_MAP[s])
        paste(g, frame(RED_BIKE, 32, 32, i), rect=(9, 22, 11, 24), remap=BIKE_MAP[s])
        draw(g, hl, 8, 9)
        draw(g, BIKE_L[s], 8, 20, G.cmap)
        return g

    return [down(0), up(0), left(2), down(-1, "l"), down(1, "r"), up(-1, "l"), up(1, "r"), left(7), left(8)]


# fishing: Red's rod (the biggest rod-coloured blob outside the body), the grunt at Red's body position
FISH_OFF = [(10, 1), (16, 0), (13, 1), (16, 0), (7, -4), (7, 1), (8, -1), (8, -1), (9, -2), (9, -8), (9, -6), (8, -9)]
FISH_FACING = "lllluuuudddd"
FISH_PATCH = {
    2: [(12, 20, ["fGGf", "fggf", ".fff3", "..ff3"])],
    3: [(17, 22, ["..ff", ".fGGf", "ffggf", ".fff"]), (21, 24, ["ff"])],
    4: [(20, 21, ["Rf", "Rf"])],
    6: [(21, 13, [".ff.", "fGGf", "fggf", ".ff.", ".fS.", ".sS."])],
    8: [(9, 12, [".ff.", "fGGf", "fggf", ".ffH", ".fSH", ".s4h", "..4f", "...f", "___f", "___f", "_fff"])],
    9: [(8, 7, [".ff.", "fGGf", "fggf", ".ffa", ".ffH", ".fSH", ".s4h", "..4f", "...f", "___f", "___f", "_fff"])],
    10: [(10, 20, ["Rf", "Rf"])],
    11: [(10, 15, ["...ff.ff...", "..fGGfGGf..", "..fggfggf..", "...ffRff...", "....fRf....", "....fRf...."])],
}


def fishing(G):
    rodmap = {0x5: int(G.cmap["R"], 16), 0x6: int(G.cmap["R"], 16), 0xc: 0x9, 0xd: 0x8}
    rodc = tuple(rodmap)
    out = []
    for i in range(12):
        red = frame(RED_FISH, 32, 32, i)
        ox, oy = FISH_OFF[i]
        body = G.walk["dul".index(FISH_FACING[i])]
        covered = {(x + ox, y + oy) for y in range(32) for x in range(16) if body[y][x]}
        seen, best, score = set(), [], -1
        for y in range(32):
            for x in range(32):
                if (x, y) in seen or red[y][x] not in rodc:
                    continue
                blob, st = [], [(x, y)]
                seen.add((x, y))
                while st:
                    cx, cy = st.pop()
                    blob.append((cx, cy))
                    for ddx in (-1, 0, 1):
                        for ddy in (-1, 0, 1):
                            q = (cx + ddx, cy + ddy)
                            if 0 <= q[0] < 32 and 0 <= q[1] < 32 and q not in seen and red[q[1]][q[0]] in rodc:
                                seen.add(q)
                                st.append(q)
                sc = sum(1 for p in blob if p not in covered)
                if sc > score:
                    best, score = blob, sc
        rod = set(best)
        g = blank(32, 32)
        for x, y in rod:
            g[y][x] = rodmap[red[y][x]]
        for y in range(32):
            for x in range(32):
                if red[y][x] == 0xf and any(q in rod for q in nb4(x, y)):
                    g[y][x] = 0xf
        paste(g, body, ox, oy)
        for x, y, rows in FISH_PATCH.get(i, []):
            draw(g, rows, x, y, G.cmap)
        out.append(g)
    return out


def navy_hair(frames):
    """Female grunt: her hair indices (b, c, 7) are navy in the palette; the hair's own shading pixels of
    index 4 (touching the hair, not the skin) move to 7, so the face and arms keep 4."""
    for g in frames:
        h, w = len(g), len(g[0])
        near = lambda x, y, idx: any(0 <= x + dx < w and 0 <= y + dy < h and g[y + dy][x + dx] in idx
                                     for dx in (-1, 0, 1) for dy in (-1, 0, 1))
        for _ in range(3):      # spreads along strands of 4 that leave the hood's sides
            hair = [(x, y) for y in range(h) for x in range(w)
                    if g[y][x] == 4 and near(x, y, (0x7, 0xb, 0xc)) and not near(x, y, (0x1, 0x2, 0x3))]
            for x, y in hair:
                g[y][x] = 7
    return frames


def build_overworld(s, previews):
    spec = json.load(open(os.path.join(ROOT, SPEC[s])))
    palette = [gba_color(c) for c in spec["palette"]]
    flat = [v for c in palette for v in c]
    G = Grunt(s)
    sheets = [("walking.png", 16, [copy(g) for g in G.walk]), ("running.png", 16, running(G)),
              ("surfing.png", 16, surfing(G)), ("bike.png", 32, bike(G)), ("field_move.png", 16, field_move(G)),
              ("fishing.png", 32, fishing(G))]
    built = {}
    for name, w, frames in sheets:
        if s == "f":
            navy_hair(frames)
        im = save_sheet(frames, w, 32, palette, os.path.join(spec["out_dir"], name))
        built[name] = (im, w, 32)
        previews.append(("%s %s" % (s, name), im, w, 32, palette))
    for dv in spec["derived"]:
        out = build_derived(dv, built, palette, flat, spec["roles"], spec)
        path = dv["path"] if "path" in dv else os.path.join(spec["out_dir"], dv["out"])
        out.save(os.path.join(ROOT, path))
        built[dv["out"]] = (out, dv.get("w", 32), dv.get("h", 32))
        print("wrote", path)
        p = palette
        if dv["out"] == "underwater.png":
            p = read_jasc("graphics/object_events/palettes/player_underwater.pal")
        previews.append(("%s %s" % (s, dv["out"]), out, dv.get("w", 32), dv.get("h", 32), p))
    write_jasc(os.path.join(ROOT, spec["palette_out"]), palette)
    refl = [gba_color(tuple(min(255, int(0.58 * v + b)) for v, b in zip(c, (106, 112, 116)))) for c in palette]
    refl[0] = palette[0]
    write_jasc(os.path.join(ROOT, spec["reflection_palette_out"]), refl)
    print("wrote", spec["palette_out"], spec["reflection_palette_out"])


def read_jasc(path):
    v = open(os.path.join(ROOT, path)).read().split()
    n = int(v[2])
    nums = [int(x) for x in v[3:3 + 3 * n]]
    return [tuple(nums[i * 3:i * 3 + 3]) for i in range(n)]


# ------------------------------------------------------------------------------------------ back pics
BALL = ["..ffff..", ".fccdaf.", "fccddaaf", "ffffffff", "feefbbbf", ".febbbf.", "..ffff.."]


def horn_poly(cx, cy, rx, ry, t1, t2, tip):
    """A stiff fabric point on the hood: base on the dome between angles t1..t2 (degrees), tip offset."""
    p1 = (cx + rx * math.cos(math.radians(t1)), cy + ry * math.sin(math.radians(t1)))
    p2 = (cx + rx * math.cos(math.radians(t2)), cy + ry * math.sin(math.radians(t2)))
    mid = ((p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2)
    inner = (cx + (mid[0] - cx) * 0.75, cy + (mid[1] - cy) * 0.75)
    return [p1, (mid[0] + tip[0], mid[1] + tip[1]), p2, inner]


def hood(cx, cy, rx=13.0, ry=12.0, cowl=None, horn=1.25):
    """The grunt's hood from behind and a little to the left, facing right: {(x, y): index} in the front
    pic palette (c light, d mid, a dark, 4 darkest red, 2 sheen, f outline; horns 5/6/8; cheek 2/3).
    The two horn points are part of the hood: one silhouette, one outline. No ear shows: only a thin
    sliver of cheek inside the hood's front edge."""
    m = {}
    cowl = cowl or [(cx - rx, cy + 2), (cx + rx, cy + 2), (cx + rx + 2, cy + 12), (cx + 4, cy + 19),
                    (cx - 3, cy + 19), (cx - rx - 3, cy + 14)]
    horns = [horn_poly(cx, cy, rx, ry, 212, 236, (-1.6 * horn, -4.6 * horn)),
             horn_poly(cx, cy, rx, ry, 292, 312, (1.4 * horn, -4.2 * horn))]
    for y in range(int(cy - ry - 8), int(cy + ry + 12)):
        for x in range(int(cx - rx - 6), int(cx + rx + 6)):
            px, py = x + 0.5, y + 0.5
            inner = ((px - cx) / (rx - 1.5)) ** 2 + ((py - cy) / (ry - 1.5)) ** 2 <= 1
            if any(in_poly(px, py, h) for h in horns) and not inner:
                m[(x, y)] = -1                                    # horn, shaded below
            elif ((px - cx) / rx) ** 2 + ((py - cy) / ry) ** 2 <= 1 or in_poly(px, py, cowl):
                nx = (px - cx) / (rx + 2)
                ny = (py - cy + 1) / (ry + 9)
                nz = math.sqrt(max(0.0, 1 - nx * nx - ny * ny))
                dot = -0.64 * nx - 0.56 * ny + 0.52 * nz        # light from the upper left
                m[(x, y)] = 0xc if dot > 0.64 else 0xd if dot > 0.20 else 0xa
    # horn shading: lit left edge, mid, shadowed right edge, a dark stitched base where it meets the red
    for (x, y), c in list(m.items()):
        if c != -1:
            continue
        left = (x - 1, y) not in m or m[(x - 1, y)] != -1
        right = (x + 1, y) not in m or m[(x + 1, y)] != -1
        base = (x, y + 1) in m and m[(x, y + 1)] != -1
        m[(x, y)] = 0x8 if base or right else 0x5 if left else 0x6
    # folded rim of the face opening on the right: a lit edge with the shadow inside it
    for y in range(int(cy - ry * 0.45), int(cy + ry * 0.95)):
        xs = [x for (x, yy) in m if yy == y]
        if xs:
            xr = max(xs)
            m[(xr - 1, y)] = 0xd
            if (xr - 2, y) in m:
                m[(xr - 2, y)] = 0x4 if m[(xr - 2, y)] == 0xa else 0xa
    # centre seam from the crown to the nape (right of centre in a 3/4 back view), lit on its right
    for (x, y) in line_px([(int(cx + 1), int(cy - ry + 1)), (int(cx + 3), int(cy - 3)), (int(cx + 3), int(cy + 6)),
                          (int(cx + 2), int(cy + 14))]):
        if (x, y) in m and (x + 1, y) in m and m[(x, y)] in (0xc, 0xd, 0xa):
            m[(x, y)] = 0xa if m[(x, y)] != 0xa else 0x4
            m[(x + 1, y)] = {0xd: 0xc, 0xa: 0xd}.get(m[(x + 1, y)], m[(x + 1, y)])
    # side panel seam from the left horn down the side of the head (subtle on the lit side)
    for (x, y) in line_px([(int(cx - rx * 0.62), int(cy - ry * 0.62)), (int(cx - rx * 0.8), int(cy - ry * 0.1)),
                          (int(cx - rx * 0.78), int(cy + ry * 0.45))]):
        if (x, y) in m and m[(x, y)] in (0xc, 0xd) and (x + 1, y) in m:
            m[(x, y)] = 0xd if m[(x, y)] == 0xc else 0xa
    # the crease where the hood turns under towards the nape: dark below, lit lip above
    crease = line_px([(int(cx - rx * 0.85), int(cy + ry * 0.5)), (int(cx - rx * 0.3), int(cy + ry * 0.72)),
                      (int(cx + rx * 0.25), int(cy + ry * 0.78))])
    for (x, y) in crease:
        if (x, y) in m and m[(x, y)] in (0xc, 0xd, 0xa):
            m[(x, y)] = 0xa if m[(x, y)] != 0xa else 0x4
            if (x, y - 1) in m and m[(x, y - 1)] == 0xd:
                m[(x, y - 1)] = 0xc
            for k in (1, 2):
                if (x, y + k) in m and m[(x, y + k)] == 0xc:
                    m[(x, y + k)] = 0xd
    # folds where the hood gathers at the nape and lies on the shoulders
    for f in ([(cx - 9, cy + 9), (cx - 7, cy + 13), (cx - 6, cy + 16)],
              [(cx - 4, cy + 11), (cx - 3, cy + 15), (cx - 2, cy + 18)],
              [(cx + 7, cy + 9), (cx + 8, cy + 13), (cx + 9, cy + 15)]):
        for (x, y) in line_px([(int(a), int(b)) for a, b in f]):
            if (x, y) in m and (x + 1, y) in m:
                m[(x, y)] = 0x4 if m[(x, y)] == 0xa else 0xa
                m[(x + 1, y)] = {0xa: 0xd, 0xd: 0xc}.get(m[(x + 1, y)], m[(x + 1, y)])
    # pale sheen on the crown (the front pic's light dots on the hood)
    for k in range(6):
        a = math.radians(200 + k * 11)
        p = (int(round(cx + (rx - 2.2) * math.cos(a) + 1)), int(round(cy + (ry - 2.2) * math.sin(a))))
        if p in m and m[p] in (0xc, 0xd):
            m[p] = 0x2
    # one outline around hood and horns: black outside, dark red where the hem lies on the body
    out = dict(m)
    for (x, y), c in m.items():
        if any(q not in m for q in ((x + 1, y), (x - 1, y), (x, y - 1))):
            out[(x, y)] = 0xf
        elif (x, y + 1) not in m:
            out[(x, y)] = 0x4
    m = out
    # a thin sliver of cheek and jaw just inside the front edge (never outside the hood's outline)
    for y in range(int(cy + 1), int(cy + 7)):
        xs = [x for (x, yy) in m if yy == y]
        if xs:
            xr = max(xs)
            m[(xr - 1, y)] = 0x2 if y < cy + 4 else 0x3
    return m


def stamp_ball(out, x0, y0):
    for ty, r in enumerate(BALL):
        for tx, ch in enumerate(r):
            if ch != "." and 0 <= x0 + tx < 64 and 0 <= y0 + ty < 64:
                out[(x0 + tx, y0 + ty)] = int(ch, 16)


def in_rects(p, rects):
    return any(x0 <= p[0] <= x1 and y0 <= p[1] <= y1 for x0, y0, x1, y1 in rects)


def to_grid(d):
    g = blank(64, 64)
    for (x, y), c in d.items():
        if 0 <= x < 64 and 0 <= y < 64:
            g[y][x] = c
    return g


STEVEN_GLOVE = {0x1: 0xb, 0x2: 0x5, 0x3: 0x6, 0x4: 0x8}


def steven_body(i, gloves=(), front=(), keep=(), erase=(), face_x0=27):
    """Steven's back pic frame i without his head: suit -> grunt red (lit rims c, cloth d, shade a, inner
    lines 4), cuffs -> grey wristbands, hands -> grey gloves. Returns ({pixel: index}, front pixels)."""
    src = frame(STEVEN_BACK, 64, 64, i)
    g = {(x, y): src[y][x] for y in range(64) for x in range(64) if src[y][x]}
    for p, v in list(g.items()):
        x, y = p
        if in_rects(p, keep):
            continue
        if (y < 40 and v in (0x9, 0xa, 0xb, 0xe) and not in_rects(p, gloves)) or (y < 31 and v in (0x7, 0xf)) \
                or (x >= face_x0 and y < 38 and v in (0x1, 0x2, 0x3, 0x4, 0x8, 0xe) and not in_rects(p, gloves)) \
                or in_rects(p, erase):
            del g[p]
    out = {}
    for p, v in g.items():
        x, y = p
        ext = any(q not in g for q in nb4(x, y))
        if v in STEVEN_GLOVE:
            out[p] = STEVEN_GLOVE[v]
        elif v in (0x9, 0xa, 0xb, 0xe):
            out[p] = {0xe: 0xb, 0x9: 0x5, 0xa: 0x5, 0xb: 0x6}[v]
        elif v == 0x7:
            lit = g.get((x - 1, y)) in (None, 0xf) or g.get((x, y - 1)) in (None, 0xf) or (x - 1, y - 1) not in g
            out[p] = 0xc if lit else 0xd
        elif v == 0x8:
            out[p] = 0xa
        elif v == 0xf:
            out[p] = 0xf if ext else 0x4
        else:
            out[p] = v
    return out, {p: c for p, c in out.items() if in_rects(p, front)}


def back_m():
    frames = []
    # 0 idle (Steven 3)
    body, fr = steven_body(3)
    body.update(hood(32, 21))
    frames.append(body)
    # 1 wind-up, ball in the glove (Steven 0); the arm passes in front of the hood
    body, fr = steven_body(0, gloves=[(0, 28, 22, 43)], front=[(0, 28, 25, 43)], face_x0=24)
    body.update(hood(29, 22))
    body.update(fr)
    stamp_ball(body, 2, 28)
    frames.append(body)
    # 2 arm up behind the head, ball (Steven 1)
    hand = [(12, 28, 21, 39)]
    body, fr = steven_body(1, gloves=hand, front=hand, keep=hand, face_x0=28)
    body.update(hood(31, 21))
    body.update(fr)
    stamp_ball(body, 13, 25)
    frames.append(body)
    # 3 release and 4 follow-through: the arm swung forward (Steven 2, his own throw's forward frame)
    body, fr = steven_body(2, gloves=[(52, 55, 63, 63)], face_x0=18)
    body.update(hood(22, 21))
    frames += [body, dict(body)]
    return [to_grid(f) for f in frames]


LEAF_HAT = [(24, 15), (21, 19), (29, 16), (21, 14), (23, 18)]
LEAF_POSE = [
    # hair polygon, glove rects (hands), wristband rects, ball, front rects (in front of the hood), skirt rect
    ([(10, 28), (38, 28), (38, 47), (34, 52), (30, 58), (12, 58), (10, 44)], [], [], None, [], None),
    ([(12, 32), (41, 32), (41, 51), (33, 58), (14, 58), (12, 46)], [(0, 41, 9, 50)], [(5, 52, 12, 58)], (0, 37),
     [(0, 38, 12, 63)], None),
    ([(16, 30), (46, 30), (46, 50), (37, 58), (19, 58), (16, 44)], [(0, 27, 12, 37)], [(8, 34, 14, 39)], (0, 23),
     [(0, 26, 19, 52)], None),
    ([(0, 30), (32, 30), (32, 44), (22, 50), (0, 50)], [(51, 22, 63, 36)], [(46, 26, 51, 31)], None,
     [(37, 24, 63, 41)], (0, 55, 30, 63)),
    ([(0, 33), (34, 33), (34, 46), (24, 52), (0, 52)], [(43, 59, 58, 63)], [(42, 55, 58, 61)], None, [],
     (0, 57, 30, 63)),
]


def back_f():
    frames = []
    for i, (hair_poly, gloves, cuffs, ball, front, skirt) in enumerate(LEAF_POSE):
        src = frame(LEAF_BACK, 64, 64, i)
        hx, hy = LEAF_HAT[i]
        cx, cy = hx + 5, hy + 16
        g = {(x, y): src[y][x] for y in range(64) for x in range(64) if src[y][x]}
        hair = lambda p: in_poly(p[0] + 0.5, p[1] + 0.5, hair_poly)
        protect = list(gloves) + list(front)
        skin = (0x1, 0x2, 0x3, 0x4)
        if i == 3:      # her eye and mouth where the outstretched arm leaves the face
            for p, v in list(g.items()):
                if in_rects(p, [(37, 26, 42, 37)]) and v not in (0x2, 0x3):
                    del g[p]
        for p, v in list(g.items()):
            x, y = p
            if in_rects(p, protect):
                # inside a protected arm: drop the hat's whites and band, keep the arm and its outline
                if v in (0x9, 0xa, 0xb, 0xc) or (v in (0x6, 0xf, 0x8) and not any(g.get(q) in skin for q in nb4(x, y))):
                    if y <= hy + 19:
                        del g[p]
                continue
            if y <= hy + 19 and v in (0x9, 0xa, 0xb, 0xc, 0x6, 0xf, 0x8) and not hair(p):
                if y <= hy + 17 or v != 0x8:
                    del g[p]          # the hat
            elif hx + 8 <= x <= hx + 24 and hy + 14 <= y <= hy + 29 and v in (0x2, 0x3, 0x9, 0xf, 0x4, 0x8) \
                    and not hair(p):
                del g[p]              # the face (the hood draws its own sliver)
            elif hair(p) and y < cy + 5 and x > cx - 13:
                del g[p]              # hair only comes out of the hood at the nape
        out = {}
        for p, v in g.items():
            x, y = p
            ext = any(q not in g for q in nb4(x, y))
            if in_rects(p, gloves) and v in (0x1, 0x2, 0x3, 0x4):
                out[p] = {0x1: 0xb, 0x2: 0x5, 0x3: 0x6, 0x4: 0x8}[v]
            elif in_rects(p, cuffs) and v in (0x5, 0x6, 0x7):
                out[p] = {0x5: 0x6, 0x6: 0x8, 0x7: 0x6}[v]
            elif hair(p) and v in (0x1, 0x4, 0x8):
                out[p] = {0x1: 0x7, 0x4: 0x7, 0x8: 0x9}[v]
            elif hair(p) and v == 0xf:
                out[p] = 0xf if ext else 0x8
            elif v in (0xd, 0xe):
                out[p] = 0xd          # the bag strap disappears into the top
            elif v == 0x7:
                out[p] = 0xc
            elif v == 0x6:
                out[p] = 0xd
            elif v == 0x5:
                out[p] = 0xa
            elif v == 0xc and skirt and in_rects(p, [skirt]):
                out[p] = 0x6
            elif v == 0x1:
                out[p] = 0x2
            elif v == 0xf:
                out[p] = 0xf if ext else 0x4
            else:
                out[p] = v
        for p, v in list(out.items()):
            if v == 0x4 and sum(1 for q in nb4(*p) if out.get(q) in (0xc, 0xd, 0xa)) >= 2:
                out[p] = 0xd
        for p, v in list(out.items()):
            if v == 0xd and any(out.get((p[0] + k, p[1])) in (None, 0xf) for k in (1, 2)):
                out[p] = 0xa
        fr = {p: c for p, c in out.items() if in_rects(p, front)}
        cowl = [(cx - 10, cy + 2), (cx + 10, cy + 2), (cx + 11, cy + 10), (cx + 5, cy + 13), (cx - 5, cy + 13),
                (cx - 11, cy + 9)]
        out.update(hood(cx, cy, rx=10.5, ry=10.5, cowl=cowl, horn=1.1))
        out.update(fr)
        for _ in range(2):
            for p in [p for p in out if sum(1 for q in nb4(*p) if q in out) <= 1]:
                del out[p]
        if ball:
            stamp_ball(out, *ball)
        frames.append(out)
    return [to_grid(f) for f in frames]


# Tabitha (TRAINER_PIC_MAGMA_ADMIN's back pic, the Space Center partner): the male grunt's frames in his
# deeper crimson admin jacket (darker than the grunts' reds, like his old back pic, D-163)
ADMIN_OUT = "graphics/trainers/back_pics/magma_admin.png"
ADMIN_REDS = {0xc: (192, 64, 80), 0xd: (144, 40, 56), 0xa: (104, 24, 40), 0x4: (64, 16, 32), 0x2: (232, 152, 152)}


def build_back(s, previews):
    pal = [tuple(load(FRONT_PIC[s]).getpalette()[i * 3:i * 3 + 3]) for i in range(16)]
    frames = back_m() if s == "m" else back_f()
    im = save_sheet(frames, 64, 64, pal, BACK_OUT[s], vertical=True)
    previews.append(("%s back pic" % s, im, 64, 64, pal))
    if s == "m":
        admin = [ADMIN_REDS.get(i, c) for i, c in enumerate(pal)]
        im = save_sheet(frames, 64, 64, admin, ADMIN_OUT, vertical=True)
        previews.append(("tabitha back pic", im, 64, 64, admin))


# ------------------------------------------------------------------------------------------ main
def write_previews(previews, out_dir, zoom=4):
    os.makedirs(out_dir, exist_ok=True)
    for name, im, w, h, pal in previews:
        n = (im.width // w) if im.height == h else (im.height // h)
        strip = Image.new("RGB", (n * (w * zoom + 4), h * zoom), (40, 40, 48))
        flat = [v for c in pal for v in c]
        for i in range(n):
            box = (i * w, 0, i * w + w, h) if im.height == h else (0, i * h, w, i * h + h)
            fr = im.crop(box)
            fr.putpalette(flat + [0] * (768 - len(flat)))
            rgba = fr.convert("RGBA")
            a = Image.new("L", fr.size, 0)
            apx, fpx = a.load(), fr.load()
            for y in range(h):
                for x in range(w):
                    apx[x, y] = 255 if fpx[x, y] else 0
            rgba.putalpha(a)
            bg = Image.new("RGBA", fr.size, (150, 150, 165, 255))
            bg.alpha_composite(rgba)
            strip.paste(bg.convert("RGB").resize((w * zoom, h * zoom), Image.NEAREST), (i * (w * zoom + 4), 0))
        p = os.path.join(out_dir, name.replace(" ", "_").replace(".png", "") + ".png")
        strip.save(p)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--preview", help="directory for enlarged previews (scratchpad)")
    ap.add_argument("--only", choices=["ow", "back"])
    args = ap.parse_args()
    previews = []
    for s in "mf":
        if args.only != "back":
            build_overworld(s, previews)
        if args.only != "ow":
            build_back(s, previews)
    if args.preview:
        write_previews(previews, args.preview)


if __name__ == "__main__":
    main()
