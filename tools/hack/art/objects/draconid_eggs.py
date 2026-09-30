#!/usr/bin/env python3
"""
draconid_eggs.py - draw the three dragon eggs on the Elder's table (16x32 objects, one shared palette).

  python3 tools/hack/art/objects/draconid_eggs.py

Deino: navy shell with a jagged dark "jaw" band. Dreepy: pale teal with wavy ghostly bands.
Jangmo-o: grey with golden scale arcs. Writes graphics/object_events/pics/misc/draconid_egg_*.png
and graphics/object_events/palettes/draconid_eggs.pal.
"""

import os

from PIL import Image

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "..", ".."))

PALETTE = [
    (115, 197, 164),                                            # 0 transparent
    (72, 88, 144), (40, 48, 88), (120, 140, 200), (232, 96, 152),  # 1-4 Deino: base, dark, light, accent
    (120, 200, 184), (64, 128, 120), (192, 240, 224), (216, 56, 64),  # 5-8 Dreepy
    (176, 176, 184), (112, 112, 128), (232, 232, 240), (232, 184, 56),  # 9-12 Jangmo-o
    (255, 255, 255), (80, 80, 88),                            # 13 shine, 14 shadow on the table
    (0, 0, 0),                                                  # 15 outline
]

SHAPE = [  # O outline, B base, D dark, L light, W shine
    "................",
    "......OOOO......",
    ".....OLLBBO.....",
    "....OLWLBBBO....",
    "....OLLBBBBO....",
    "...OBBBBBBBBO...",
    "...OBBBBBBBBO...",
    "..OBBBBBBBBBBO..",
    "..OBBBBBBBBBDO..",
    "..OBBBBBBBBBDO..",
    "..OBBBBBBBBDDO..",
    "...OBBBBBBDDO...",
    "...ODBBBBDDDO...",
    "....ODDDDDDO....",
    ".....OOOOOO.....",
    "................",
]

# pattern overlays on base cells: (row, col, role)
PATTERNS = {
    "deino": [(8, c, "D") for c in range(3, 13) if c % 2] + [(9, c, "D") for c in range(3, 13) if not c % 2]
             + [(6, 5, "A"), (6, 10, "A")],
    "dreepy": [(6, c, "L") for c in (5, 6, 9, 10)] + [(7, c, "L") for c in (4, 7, 8, 11)]
              + [(10, c, "L") for c in (4, 5, 8, 9)] + [(11, c, "L") for c in (6, 7)] + [(8, 6, "A"), (8, 9, "A")],
    "jangmo_o": [(5, c, "A") for c in (5, 8, 11)] + [(6, c, "A") for c in (4, 6, 7, 9, 10)]
                + [(8, c, "A") for c in (4, 7, 10)] + [(9, c, "A") for c in (3, 5, 6, 8, 9, 11)]
                + [(11, c, "A") for c in (6, 9)],
}
ROLES = {"deino": (1, 2, 3, 4), "dreepy": (5, 6, 7, 8), "jangmo_o": (9, 10, 11, 12)}


def draw(name):
    base, dark, light, accent = ROLES[name]
    idx = {"O": 15, "B": base, "D": dark, "L": light, "A": accent, "W": 13}
    grid = [list(r) for r in SHAPE]
    for r, c, role in PATTERNS[name]:
        if grid[r][c] == "B":
            grid[r][c] = role
    im = Image.new("P", (16, 32), 0)
    im.putpalette([v for c in PALETTE for v in c] + [0] * (768 - 48))
    px = im.load()
    for y, row in enumerate(grid):
        for x, ch in enumerate(row):
            if ch != ".":
                px[x, 16 + y] = idx[ch]
    # soft shadow on the table under the egg
    for x in range(5, 11):
        if px[x, 31] == 0:
            px[x, 31] = 14
    return im


def main():
    out = os.path.join(ROOT, "graphics/object_events/pics/misc")
    for name in ROLES:
        path = os.path.join(out, "draconid_egg_%s.png" % name)
        draw(name).save(path)
        print("wrote", os.path.relpath(path, ROOT))
    pal = os.path.join(ROOT, "graphics/object_events/palettes/draconid_eggs.pal")
    with open(pal, "w", newline="\r\n") as f:
        f.write("JASC-PAL\n0100\n16\n" + "".join("%d %d %d\n" % c for c in PALETTE))
    print("wrote", os.path.relpath(pal, ROOT))


if __name__ == "__main__":
    main()
