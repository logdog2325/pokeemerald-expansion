#!/usr/bin/env python3
"""
build_falling_star.py - the night sky and the clan's peaks of the opening's falling star (round 2, D-460).

  python3 tools/hack/art/falling_star/build_falling_star.py [--preview out.png]

The scene (src/draconid_falling_star.c) is two backgrounds and Game Freak's own sprites (the FRLG
Game Freak intro's star and sparkles, Emerald's intro sparkle). This script draws the new parts and
writes graphics/falling_star/:

  sky.png, sky.bin            BG3: the night sky in Game Freak's banding - flat bands joined by the
                              3-row checker step of the vanilla title sky (graphics/title_screen/
                              rayquaza.png) - from near black at the top to deep blue at the horizon,
                              with stars: dim ones, four that twinkle (palette entries the scene cycles)
                              and four bright crosses (BG palette 0)
  mountains.png, .bin         BG1: the Draconid peaks in silhouette, a far range (lit and shadowed
                              faces, a starlit rim, snow on the two highest peaks) and a near range in
                              front; the far ridge around the saddle where the star falls uses glow
                              entries that the scene lights up (BG palette 1)
  glow.png                    OBJ 64x32: the light behind the ridge, alpha-blended over the sky
  star.pal                    Game Freak's star (graphics/intro_frlg/game_freak/star.png) recoloured
                              from saturated yellow to a white-gold meteor head

--preview writes a 3x composite (a quiet frame and the landing) to check the art without a build.
Everything is drawn from the shapes and colours below; no third-party art.
"""

import argparse
import math
import os
import random
import struct
import sys

from PIL import Image

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import gbaart  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "..", ".."))
OUT = os.path.join(ROOT, "graphics/falling_star")
STAR_PNG = os.path.join(ROOT, "graphics/intro_frlg/game_freak/star.png")

W, H = 256, 160            # the 32x20 tiles a 256x256 text BG shows on screen (240 visible)
SCREEN_W = 240
MAP_W, MAP_H = 32, 32
TILE = 8
SKY_BG_PALETTE = 0
MOUNTAIN_BG_PALETTE = 1

# Where the star drops behind the far ridge (src/draconid_falling_star.c: LAND_X, LAND_Y must match)
LAND_X, LAND_Y = 128, 107

# ---------------------------------------------------------------------------------------------
# Sky (BG palette 0)
# ---------------------------------------------------------------------------------------------
SKY_DIM_STAR = 1
SKY_GRADIENT = [10, 9, 8, 7, 6, 5, 4]       # entries top -> horizon, as in the vanilla title sky
SKY_TWINKLE = [11, 12, 13, 14]              # cycled by the scene (SKY_TWINKLE_FIRST), each with its own phase
SKY_BRIGHT_STAR = 15
SKY_PAL = [(0, 0, 0)] * 16
SKY_PAL[0] = (8, 8, 24)
SKY_PAL[SKY_DIM_STAR] = (80, 96, 144)
for entry, colour in zip(SKY_GRADIENT, [(8, 8, 24), (8, 16, 40), (16, 24, 56), (16, 32, 72),
                                         (24, 40, 88), (32, 48, 104), (40, 64, 120)]):
    SKY_PAL[entry] = colour
for entry in SKY_TWINKLE:
    SKY_PAL[entry] = (144, 160, 208)        # the scene animates these (TWINKLE_DIM .. TWINKLE_BRIGHT)
SKY_PAL[SKY_BRIGHT_STAR] = (232, 240, 255)
# y where the step from one band to the next starts (3 checker rows, then the next band): the bands
# narrow towards the horizon
SKY_STEPS = [18, 36, 52, 66, 78, 88]

BRIGHT_STARS = [(30, 20), (147, 12), (211, 34), (88, 52)]   # the scene glints Emerald's sparkle here (sGlintCoords)
STAR_SEED = 0x0D7A


def sky_index(x, y):
    for i, step in enumerate(SKY_STEPS):
        if y < step:
            return SKY_GRADIENT[i]
        if y < step + 3:
            # vanilla's step: a 1-px checker, the upper colour on the even pixels of rows 0 and 2
            return SKY_GRADIENT[i] if (x + y - step) % 2 == 0 else SKY_GRADIENT[i + 1]
    return SKY_GRADIENT[-1]


def draw_sky(ridge_far):
    im = gbaart.make_indexed((W, H), SKY_PAL)
    px = im.load()
    for y in range(H):
        for x in range(W):
            px[x, y] = sky_index(x, y)
    rng = random.Random(STAR_SEED)
    placed = list(BRIGHT_STARS)
    stars = []
    tries = 0
    while len(stars) < 46 and tries < 5000:
        tries += 1
        x, y = rng.randrange(2, SCREEN_W - 2), rng.randrange(3, 96)
        if y > ridge_far[x] - 8:
            continue
        # fewer stars towards the horizon
        if rng.random() < y / 110.0:
            continue
        if any((x - a) ** 2 + (y - b) ** 2 < 11 ** 2 for a, b in placed):
            continue
        placed.append((x, y))
        stars.append((x, y))
    for n, (x, y) in enumerate(stars):
        px[x, y] = SKY_TWINKLE[n % len(SKY_TWINKLE)] if n % 3 == 0 else SKY_DIM_STAR
    for x, y in BRIGHT_STARS:
        px[x, y] = SKY_BRIGHT_STAR
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            px[x + dx, y + dy] = SKY_DIM_STAR
    return im


# ---------------------------------------------------------------------------------------------
# Mountains (BG palette 1)
# ---------------------------------------------------------------------------------------------
M_NEAR_SHADE, M_NEAR_LIT, M_NEAR_RIM = 1, 2, 3
M_FAR_SHADE, M_FAR_LIT, M_FAR_RIM = 4, 5, 6
M_SNOW_SHADE, M_SNOW_LIT = 7, 8
# glow entries on the far ridge's top pixel near the landing point: 3 rings x (shadowed face, lit
# face); the scene blends them from their face colour towards the glow (RIDGE_GLOW_*)
M_GLOW_SHADE = [9, 10, 11]
M_GLOW_LIT = [12, 13, 14]
GLOW_RADII = [7, 15, 27]                    # px from LAND_X along the ridge for rings 1-3

MOUNTAIN_PAL = [(0, 0, 0)] * 16
MOUNTAIN_PAL[M_NEAR_SHADE] = (8, 8, 16)
MOUNTAIN_PAL[M_NEAR_LIT] = (16, 16, 32)
MOUNTAIN_PAL[M_NEAR_RIM] = (32, 40, 64)
MOUNTAIN_PAL[M_FAR_SHADE] = (16, 24, 48)
MOUNTAIN_PAL[M_FAR_LIT] = (24, 32, 64)
MOUNTAIN_PAL[M_FAR_RIM] = (48, 64, 104)
MOUNTAIN_PAL[M_SNOW_SHADE] = (56, 72, 112)
MOUNTAIN_PAL[M_SNOW_LIT] = (104, 120, 160)
for i in range(3):
    MOUNTAIN_PAL[M_GLOW_SHADE[i]] = MOUNTAIN_PAL[M_FAR_SHADE]
    MOUNTAIN_PAL[M_GLOW_LIT[i]] = MOUNTAIN_PAL[M_FAR_RIM]

# ridge control points (x, top y); peaks are the local minima of y
FAR_RIDGE = [(-8, 108), (10, 101), (26, 104), (54, 86), (72, 98), (84, 94), (101, 99), (116, 105),
             (128, 108), (142, 101), (157, 89), (176, 68), (194, 88), (206, 85), (222, 99), (236, 94),
             (252, 104), (266, 101)]
NEAR_RIDGE = [(-8, 130), (18, 122), (42, 135), (66, 126), (92, 141), (114, 133), (140, 147),
              (164, 136), (186, 125), (204, 132), (228, 120), (250, 131), (266, 126)]
SNOW_PEAKS = {176: 14, 54: 8}               # peak x -> snow line below the summit
RIDGE_SEED = 0x51A7
FAR_FACE_DEPTH = 30                         # rows below a summit its shadowed face reaches
NEAR_FACE_DEPTH = 18


def ridge_line(points, rng, rough):
    """Top y of the ridge for every column: straight runs between the points, roughened by midpoint
    displacement, then a 3-tap median so no single pixel spikes stand out."""
    ys = [0.0] * (W + 1)
    for (x0, y0), (x1, y1) in zip(points, points[1:]):
        seg = {x0: float(y0), x1: float(y1)}

        def split(a, b, amp):
            if b - a < 2:
                return
            m = (a + b) // 2
            seg[m] = (seg[a] + seg[b]) / 2 + rng.uniform(-amp, amp)
            split(a, m, amp * 0.55)
            split(m, b, amp * 0.55)
        split(x0, x1, rough)
        for x in range(x0, x1 + 1):
            if 0 <= x <= W:
                ys[x] = seg[x]
    ys = [int(round(v)) for v in ys]
    return [sorted(ys[max(0, x - 1):x + 2])[len(ys[max(0, x - 1):x + 2]) // 2] for x in range(W)]


def peaks_and_valleys(points):
    peaks, valleys = [], []
    for i in range(1, len(points) - 1):
        (xa, ya), (x, y), (xb, yb) = points[i - 1], points[i], points[i + 1]
        if y < ya and y <= yb:
            peaks.append((x, y))
        elif y > ya and y >= yb:
            valleys.append((x, y))
    return peaks, valleys


DIVIDE_SLOPE = 0.7        # px right per row: a peak's divide runs down and right from the summit
VALLEY_SLOPE = 0.55       # px left per row: a valley's gully runs down and left, closing the shadow face
FACE_DITHER = 3           # rows of checker where a shadowed face fades into the silhouette


def face_map(points, rng, depth):
    """True where a pixel is on a shadowed face: a wedge right of each peak's divide (a jagged line
    down and right from the summit) and left of the next valley (its gully runs down and left). The
    wedge only reaches DEPTH rows below the summit and fades out in Game Freak's checker step, so the
    feet of the range are one flat silhouette."""
    peaks, valleys = peaks_and_valleys(points)
    shade = [[False] * W for _ in range(H)]
    for px_, py in peaks:
        nxt = [(vx, vy) for vx, vy in valleys if vx > px_]
        vx, vy = min(nxt) if nxt else (W + 40, py + 40)
        x = float(px_)
        for y in range(py, min(H, py + depth)):
            gully = vx - max(0, y - vy) * VALLEY_SLOPE
            left, right = int(round(x)), int(round(gully))
            if left >= right:
                break
            fade = y >= py + depth - FACE_DITHER
            for xx in range(max(0, left), min(W, right)):
                if not fade or (xx + y) % 2 == 0:
                    shade[y][xx] = True
            x += DIVIDE_SLOPE + rng.uniform(-0.6, 0.6)
    return shade


def smooth_walk(rng, n, lo, hi):
    """A random walk in [lo, hi] that moves at most 1 px every 2-4 columns (a ragged but blocky edge)."""
    out, v, run = [], 0, 0
    for _ in range(n):
        if run <= 0:
            v = max(lo, min(hi, v + rng.choice((-1, 1))))
            run = rng.randrange(2, 5)
        run -= 1
        out.append(v)
    return out


def draw_mountains():
    rng = random.Random(RIDGE_SEED)
    far = ridge_line(FAR_RIDGE, rng, 3.0)
    near = ridge_line(NEAR_RIDGE, rng, 2.5)
    far_shade = face_map(FAR_RIDGE, rng, FAR_FACE_DEPTH)
    near_shade = face_map(NEAR_RIDGE, rng, NEAR_FACE_DEPTH)
    im = gbaart.make_indexed((W, H), MOUNTAIN_PAL)
    px = im.load()
    # far range: faces, and a starlit 1-px rim along the lit faces' ridge
    for x in range(W):
        for y in range(far[x], H):
            px[x, y] = M_FAR_SHADE if far_shade[y][x] else M_FAR_LIT
        if not far_shade[far[x]][x]:
            px[x, far[x]] = M_FAR_RIM
    # snow on the highest peaks: a cap that hugs the ridge, thickest at the summit and thinning down the
    # shoulders, its lower edge ragged with short tapering tongues (snow lying in the gullies); on the
    # shadowed face it lies a little deeper (no sun there)
    for peak_x, depth in SNOW_PEAKS.items():
        summit = min(far[max(0, peak_x - 4):peak_x + 5])
        span = [x for x in range(max(0, peak_x - 40), min(W, peak_x + 41)) if far[x] < summit + depth]
        walk = smooth_walk(rng, len(span), -1, 1)
        tongue = [0] * len(span)
        i = rng.randrange(1, 4)
        while i < len(span) - 2:
            length = rng.randrange(2, 4)
            tongue[i] = length
            tongue[i + 1] = length - 1 if rng.random() < 0.6 else length
            i += rng.randrange(4, 9)
        for i, x in enumerate(span):
            height = far[x] - summit                 # how far this column's ridge is below the summit
            thick = depth - height - abs(x - peak_x) // 4
            if thick <= 0:
                continue
            thick += walk[i] + (tongue[i] if thick > 2 else 0)
            for y in range(far[x], min(H, far[x] + thick + 2)):
                if y >= far[x] + thick and not far_shade[y][x]:
                    continue
                px[x, y] = M_SNOW_SHADE if far_shade[y][x] else M_SNOW_LIT
    # glow entries along the far ridge around the landing point (its top pixel: a backlit rim)
    for x in range(LAND_X - GLOW_RADII[-1], LAND_X + GLOW_RADII[-1] + 1):
        d = abs(x - LAND_X)
        ring = next(i for i, r in enumerate(GLOW_RADII) if d <= r)
        px[x, far[x]] = M_GLOW_SHADE[ring] if far_shade[far[x]][x] else M_GLOW_LIT[ring]
    # near range in front
    for x in range(W):
        for y in range(near[x], H):
            px[x, y] = M_NEAR_SHADE if near_shade[y][x] else M_NEAR_LIT
        if not near_shade[near[x]][x]:
            px[x, near[x]] = M_NEAR_RIM
    return im, far, near


# ---------------------------------------------------------------------------------------------
# Glow sprite (64x32) and the star's palette
# ---------------------------------------------------------------------------------------------
GLOW_W, GLOW_H = 64, 32
GLOW_PAL = [(0, 0, 0), (248, 240, 208), (240, 216, 160), (216, 176, 120), (152, 112, 96), (88, 64, 64)]
GLOW_RINGS = [0.16, 0.34, 0.54, 0.76, 1.0]  # normalised radius where rings 1-5 end
GLOW_RY = 24                                 # vertical radius: the glow is wider than it is tall
DITHER = 0.12                                # width of the checker step between two rings


def draw_glow():
    im = gbaart.make_indexed((GLOW_W, GLOW_H), GLOW_PAL)
    px = im.load()
    cx, cy = GLOW_W / 2 - 0.5, GLOW_H - 0.5
    for y in range(GLOW_H):
        for x in range(GLOW_W):
            d = math.hypot((x - cx) / (GLOW_W / 2), (y - cy) / GLOW_RY)
            for ring, r in enumerate(GLOW_RINGS):
                if d < r:
                    entry = ring + 1
                    if d > r - DITHER and (x + y) % 2:
                        entry = ring + 2 if ring + 2 < len(GLOW_PAL) else 0
                    px[x, y] = entry
                    break
    return im


STAR_ANCHORS = {0: (0, 0, 0), 4: (72, 72, 104), 8: (176, 152, 120), 11: (240, 216, 152), 15: (255, 248, 224)}


def star_palette():
    keys = sorted(STAR_ANCHORS)
    pal = []
    for i in range(16):
        lo = max(k for k in keys if k <= i)
        hi = min(k for k in keys if k >= i)
        t = 0 if hi == lo else (i - lo) / (hi - lo)
        pal.append(tuple(int(a + (b - a) * t) for a, b in zip(STAR_ANCHORS[lo], STAR_ANCHORS[hi])))
    return [gbaart.gba_color(c) for c in pal]


# ---------------------------------------------------------------------------------------------
# Tiles and tilemaps
# ---------------------------------------------------------------------------------------------
TILES_PER_ROW = 16


def write_bg(canvas, name, palette_num, pal):
    px = canvas.load()
    blank = bytes(TILE * TILE)
    tiles = [blank]
    lookup = {blank: 0}
    entries = []
    for ty in range(MAP_H):
        for tx in range(MAP_W):
            if ty * TILE >= H:
                entries.append(palette_num << 12)
                continue
            data = bytes(px[tx * TILE + x, ty * TILE + y] for y in range(TILE) for x in range(TILE))
            if data not in lookup:
                lookup[data] = len(tiles)
                tiles.append(data)
            entries.append(lookup[data] | (palette_num << 12))
    rows = (len(tiles) + TILES_PER_ROW - 1) // TILES_PER_ROW
    sheet = gbaart.make_indexed((TILES_PER_ROW * TILE, rows * TILE), pal)
    spx = sheet.load()
    for n, data in enumerate(tiles):
        ox, oy = (n % TILES_PER_ROW) * TILE, (n // TILES_PER_ROW) * TILE
        for i, v in enumerate(data):
            spx[ox + i % TILE, oy + i // TILE] = v
    sheet.save(os.path.join(OUT, name + ".png"))
    with open(os.path.join(OUT, name + ".bin"), "wb") as f:
        f.write(struct.pack("<%dH" % len(entries), *entries))
    return len(tiles)


# ---------------------------------------------------------------------------------------------
# Preview (no build needed)
# ---------------------------------------------------------------------------------------------
def rgb(im):
    return gbaart.to_rgba(im, transparent_index=-1).convert("RGB")


def preview(path, sky, mountains):
    frames = []
    for lit in (0.0, 1.0):
        sky_rgb = rgb(sky)
        out = sky_rgb.copy()
        if lit:
            glow = gbaart.to_rgba(draw_glow())
            gx, gy = LAND_X - GLOW_W // 2, LAND_Y - GLOW_H + 6
            src = glow.load()
            dst = out.load()
            for y in range(GLOW_H):
                for x in range(GLOW_W):
                    r, g, b, a = src[x, y]
                    if a and 0 <= gx + x < W and 0 <= gy + y < H:
                        o = dst[gx + x, gy + y]
                        k = 10 / 16
                        dst[gx + x, gy + y] = tuple(min(255, int(o[i] + (r, g, b)[i] * k)) for i in range(3))
        mpal = list(MOUNTAIN_PAL)
        if lit:
            targets = [(248, 216, 152), (200, 152, 120), (128, 96, 104)]
            for i in range(3):
                mpal[M_GLOW_SHADE[i]] = targets[i]
                mpal[M_GLOW_LIT[i]] = targets[i]
        m = mountains.copy()
        gbaart.set_palette(m, mpal)
        out.paste(gbaart.to_rgba(m), (0, 0), gbaart.to_rgba(m))
        star = Image.open(STAR_PNG).copy()
        gbaart.set_palette(star, star_palette())
        star = gbaart.to_rgba(star).transpose(Image.FLIP_LEFT_RIGHT)
        if not lit:
            out.paste(star, (60, 40), star)
        frames.append(out.crop((0, 0, SCREEN_W, H)))
    scale = 3
    sheet = Image.new("RGB", (SCREEN_W * scale, H * scale * 2 + 8), (255, 255, 255))
    for i, f in enumerate(frames):
        sheet.paste(f.resize((SCREEN_W * scale, H * scale), Image.NEAREST), (0, i * (H * scale + 8)))
    sheet.save(path)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--preview", help="also write a 3x preview PNG here (scratchpad)")
    args = ap.parse_args()
    os.makedirs(OUT, exist_ok=True)
    mountains, far, near = draw_mountains()
    sky = draw_sky(far)
    n_sky = write_bg(sky, "sky", SKY_BG_PALETTE, SKY_PAL)
    n_mtn = write_bg(mountains, "mountains", MOUNTAIN_BG_PALETTE, MOUNTAIN_PAL)
    draw_glow().save(os.path.join(OUT, "glow.png"))
    gbaart.write_jasc(os.path.join(OUT, "star.pal"), star_palette())
    print("wrote graphics/falling_star/: sky (%d tiles), mountains (%d tiles), glow.png, star.pal" % (n_sky, n_mtn))
    if args.preview:
        preview(args.preview, sky, mountains)
        print("preview:", args.preview)


if __name__ == "__main__":
    main()
