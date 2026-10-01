#!/usr/bin/env python3
"""
draconid_eggs.py - the three dragon eggs' own egg graphics (round 2 playtest, D-404), made from the ceremony's
overworld eggs (graphics/object_events/pics/misc/draconid_egg_*.png) and vanilla's egg art:

  python3 tools/hack/art/draconid_eggs.py            # writes graphics/pokemon/draconid_eggs/<egg>/*.png
  python3 tools/hack/art/draconid_eggs.py --check    # exit 1 if the committed PNGs differ from what it would write

For each egg (Deino, Dreepy, Jangmo-o):
  egg_sprite.png  64x128, the summary screen's egg (2 frames, the second with vanilla's first crack)
  hatch.png       32x128, the hatching egg (4 frames, vanilla's cracks)
  icon_egg.png    32x64, the party / PC icon (2 frames), in one of the six shared icon palettes

The 24x24 summary and hatch eggs keep vanilla's outline, cracks and shading (highlight / base / shade) and take the
overworld egg's colours and markings at 2x: each pixel inside the egg looks up the overworld egg pixel at the same
place (the 12x14 overworld egg body scaled to 24x24) and is painted with that egg's marking colour if the overworld
pixel is a marking (Deino's pink eyes and checker band, Dreepy's pale bands and red eyes, Jangmo-o's gold scales);
vanilla's green spots become plain base or shade. The icon is the overworld egg itself, in the nearest colours of
the egg's icon palette, with a squash for the second frame as vanilla's icon has.
"""

import argparse
import os
import sys

from PIL import Image

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
OW = os.path.join(ROOT, "graphics/object_events/pics/misc/draconid_egg_%s.png")
VANILLA = os.path.join(ROOT, "graphics/pokemon/egg")
OUT = os.path.join(ROOT, "graphics/pokemon/draconid_eggs")
ICON_PALS = os.path.join(ROOT, "graphics/pokemon/icon_palettes/pal%d.pal")

# vanilla egg palette roles (graphics/pokemon/egg/normal.pal): 1 outline, 2 light outline / cracks, 3 highlight,
# 4 base, 5 shade, 6 / 7 green spots on base / shade
TRANSPARENT = (164, 255, 148)

# per egg: the palette (index: colour) and which overworld pixels are markings
# (overworld palette, OBJ_EVENT_PAL_TAG_DRACONID_EGGS: 1 navy, 2 dark navy, 3 light navy, 4 pink, 5 mint,
#  6 dark mint, 7 pale mint, 8 red, 9 silver, a dark silver, b light silver, c gold, d white, f black)
EGGS = {
    "deino": {
        "pal": {1: (32, 36, 64), 2: (88, 96, 136), 3: (120, 140, 200), 4: (72, 88, 144), 5: (52, 62, 108),
                6: (40, 48, 88), 7: (28, 32, 60), 8: (232, 96, 152), 9: (196, 72, 124)},
        # the pink eyes; the checker band (dark navy) only in its two rows, not the shading below it
        "marks": lambda c, oy: 8 if c == 0x4 else (6 if c == 0x2 and oy in (24, 25) else None),
        "icon_pal": 3,
    },
    "dreepy": {
        "pal": {1: (40, 72, 68), 2: (110, 150, 142), 3: (192, 240, 224), 4: (120, 200, 184), 5: (84, 156, 142),
                6: (204, 246, 232), 7: (156, 214, 200), 8: (216, 56, 64), 9: (176, 40, 52)},
        # the pale bands (below the highlight) and the red eyes
        "marks": lambda c, oy: 8 if c == 0x8 else (6 if c == 0x7 and oy >= 21 else None),
        "icon_pal": 0,
    },
    "jangmo_o": {
        "pal": {1: (56, 56, 64), 2: (140, 140, 150), 3: (232, 232, 240), 4: (176, 176, 184), 5: (130, 130, 144),
                6: (232, 184, 56), 7: (184, 136, 32), 8: (232, 184, 56), 9: (184, 136, 32)},
        "marks": lambda c, oy: 6 if c == 0xC else None,
        "icon_pal": 2,
    },
}

OW_X0, OW_Y0, OW_W, OW_H = 2, 17, 12, 14   # the overworld egg body (outline included) in its 16x32 frame
EGG = 24                                    # vanilla's summary / hatch egg is 24x24


def palette_list(pal):
    out = [TRANSPARENT] + [pal.get(i, (0, 0, 0)) for i in range(1, 16)]
    return [v for rgb in out for v in rgb]


def plain_tone(px, x, y, w, h):
    """vanilla's spot pixel (6 / 7) becomes the base (4) or shade (5) around it"""
    votes = {4: 0, 5: 0}
    for r in range(1, 5):
        for dy in range(-r, r + 1):
            for dx in range(-r, r + 1):
                X, Y = x + dx, y + dy
                if 0 <= X < w and 0 <= Y < h:
                    v = px[X, Y]
                    if v in (3, 4):
                        votes[4] += 1
                    elif v == 5:
                        votes[5] += 1
        if votes[4] or votes[5]:
            break
    return 5 if votes[5] > votes[4] else 4


def repaint(frame, ow, marks, x0, y0):
    """frame: a vanilla egg frame (P image); (x0, y0): its 24x24 egg's top-left"""
    src = frame.load()
    w, h = frame.size
    out = frame.copy()
    dst = out.load()
    owpx = ow.load()
    for y in range(h):
        for x in range(w):
            v = src[x, y]
            if v not in (3, 4, 5, 6, 7):
                continue  # transparent, outline and cracks stay
            tone = plain_tone(src, x, y, w, h) if v in (6, 7) else v
            ox = OW_X0 + (x - x0) * OW_W // EGG
            oy = OW_Y0 + (y - y0) * OW_H // EGG
            m = marks(owpx[ox, oy], oy) if 0 <= ox < 16 and 0 <= oy < 32 else None
            if m is None:
                dst[x, y] = tone
            else:
                dst[x, y] = m + 1 if tone == 5 else m   # the marking's darker twin on the shaded side
    return out


def egg_bbox(frame):
    px = frame.load()
    w, h = frame.size
    xs = [x for y in range(h) for x in range(w) if px[x, y]]
    ys = [y for y in range(h) for x in range(w) if px[x, y]]
    return min(xs), min(ys)


def build_sheet(path, frame_w, frame_h, egg):
    van = Image.open(path)
    frames = []
    n = van.size[1] // frame_h
    for i in range(n):
        fr = van.crop((0, i * frame_h, frame_w, (i + 1) * frame_h))
        x0, y0 = egg_bbox(fr)
        frames.append(repaint(fr, egg["ow"], egg["marks"], x0, y0))
    sheet = Image.new("P", van.size, 0)
    sheet.putpalette(palette_list(egg["pal"]))
    for i, fr in enumerate(frames):
        sheet.paste(fr, (0, i * frame_h))
    sheet.info["transparency"] = 0
    return sheet


def read_jasc(path):
    lines = open(path).read().split("\n")
    return [tuple(int(v) for v in l.split()) for l in lines[3:19]]


def build_icon(egg):
    pal = read_jasc(ICON_PALS % egg["icon_pal"])
    ow = egg["ow"]
    owpal = ow.getpalette()
    owpx = ow.load()

    def nearest(rgb):
        best, bi = None, 0
        for i in range(1, 16):
            d = sum((a - b) ** 2 for a, b in zip(rgb, pal[i]))
            if best is None or d < best:
                best, bi = d, i
        return bi

    body = [[0] * OW_W for _ in range(OW_H)]
    for y in range(OW_H):
        for x in range(OW_W):
            c = owpx[OW_X0 + x, OW_Y0 + y]
            if c:
                body[y][x] = nearest(tuple(owpal[c * 3:c * 3 + 3]))
    sheet = Image.new("P", (32, 64), 0)
    sheet.putpalette([v for rgb in pal for v in rgb])
    sp = sheet.load()
    # frame 0: where vanilla's icon egg stands (x 10.., bottom row 26); frame 1: squashed a row, a column wider
    for y in range(OW_H):
        for x in range(OW_W):
            if body[y][x]:
                sp[10 + x, 26 - (OW_H - 1) + y] = body[y][x]
    squash = [row[:OW_W // 2] + [row[OW_W // 2 - 1]] + row[OW_W // 2:] for row in body]
    squash = squash[:4] + squash[5:]   # drop a row from the top half
    for y, row in enumerate(squash):
        for x, v in enumerate(row):
            if v:
                sp[9 + x, 32 + 26 - (len(squash) - 1) + y] = v
    sheet.info["transparency"] = 0
    return sheet


def outputs():
    for name, egg in EGGS.items():
        egg = dict(egg)
        egg["ow"] = Image.open(OW % name)
        yield name, "egg_sprite.png", build_sheet(os.path.join(VANILLA, "anim_front.png"), 64, 64, egg)
        yield name, "hatch.png", build_sheet(os.path.join(VANILLA, "hatch.png"), 32, 32, egg)
        yield name, "icon_egg.png", build_icon(egg)


def same(a_path, img):
    if not os.path.exists(a_path):
        return False
    a = Image.open(a_path)
    return a.mode == img.mode and a.size == img.size and a.tobytes() == img.tobytes() \
        and a.getpalette()[:48] == img.getpalette()[:48]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    stale = 0
    for name, fname, img in outputs():
        path = os.path.join(OUT, name, fname)
        if args.check:
            if not same(path, img):
                print("STALE %s" % os.path.relpath(path, ROOT))
                stale += 1
            continue
        os.makedirs(os.path.dirname(path), exist_ok=True)
        img.save(path, transparency=0)
        print("wrote %s" % os.path.relpath(path, ROOT))
    if args.check:
        print("%s" % ("OK" if not stale else "%d stale" % stale))
        sys.exit(1 if stale else 0)


if __name__ == "__main__":
    main()
