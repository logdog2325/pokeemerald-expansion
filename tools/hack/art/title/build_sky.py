#!/usr/bin/env python3
"""
build_sky.py - the title screen's sky behind Regidrago (round 1, D-276).

  python3 tools/hack/art/title/build_sky.py

Vanilla's BG0 (graphics/title_screen/rayquaza.png + rayquaza.bin) is a sky gradient with the Rayquaza
silhouette drawn into it. Regidrago is an OBJ (its own front pic at 2x), so BG0 keeps only the sky:
the gradient tiles of the vanilla tilemap's rows, copied from rayquaza.png, one tile per row.
Writes graphics/title_screen/sky.png (the tiles), sky.bin (the tilemap, BG palette 14) and
sky_and_clouds.pal (BG palette 14, shared with the clouds: SKY recolours the gradient, CLOUDS the
clouds' tint; the Rayquaza-only entries are cleared).
"""

import os
import struct
import sys

from PIL import Image

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import gbaart  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "..", ".."))
GFX = os.path.join(ROOT, "graphics/title_screen")

TILE = 8
MAP_W, MAP_H = 32, 32
SCREEN_ROWS = 20          # visible tile rows (160 px)
PALETTE_NUM = 14          # the BG palette the sky and the clouds share
SKY_ENTRIES = range(4, 11)  # palette entries of the vanilla gradient, bottom (4) to top (10)
RAYQUAZA_ENTRIES = (11, 15)  # the silhouette and its glowing markings, unused now
CLOUD_ENTRY = 12          # the clouds' tint (entry 2 is their white)

# None keeps the vanilla colour.
SKY = {
    10: (16, 16, 56),
    9: (24, 24, 72),
    8: (40, 32, 96),
    7: (64, 40, 112),
    6: (88, 48, 128),
    5: (120, 64, 136),
    4: (152, 80, 136),
}
CLOUDS = (200, 176, 232)


def main():
    pal = gbaart.read_jasc(os.path.join(GFX, "rayquaza_and_clouds.pal"))
    tiles_im = Image.open(os.path.join(GFX, "rayquaza.png"))
    raw = open(os.path.join(GFX, "rayquaza.bin"), "rb").read()
    entries = struct.unpack("<%dH" % (len(raw) // 2), raw)

    for i in RAYQUAZA_ENTRIES:
        pal[i] = (0, 0, 0)
    for i, c in SKY.items():
        pal[i] = c
    if CLOUDS:
        pal[CLOUD_ENTRY] = CLOUDS

    # one gradient tile per visible row (column 0 is always sky)
    row_tiles = [entries[y * MAP_W] & 0x3FF for y in range(SCREEN_ROWS)]
    unique = []
    for t in row_tiles:
        if t not in unique:
            unique.append(t)
    sheet = gbaart.make_indexed((TILE * (len(unique) + 1), TILE), pal)   # tile 0 stays blank
    per_row = tiles_im.width // TILE
    for n, t in enumerate(unique):
        tx, ty = (t % per_row) * TILE, (t // per_row) * TILE
        sheet.paste(tiles_im.crop((tx, ty, tx + TILE, ty + TILE)), ((n + 1) * TILE, 0))
    sheet.save(os.path.join(GFX, "sky.png"))

    out = []
    for y in range(MAP_H):
        for x in range(MAP_W):
            tile = unique.index(row_tiles[y]) + 1 if y < SCREEN_ROWS else 0
            out.append(tile | (PALETTE_NUM << 12))
    with open(os.path.join(GFX, "sky.bin"), "wb") as f:
        f.write(struct.pack("<%dH" % len(out), *out))
    gbaart.write_jasc(os.path.join(GFX, "sky_and_clouds.pal"), pal)
    print("wrote graphics/title_screen/sky.png (%d tiles), sky.bin, sky_and_clouds.pal" % (len(unique) + 1))


if __name__ == "__main__":
    main()
