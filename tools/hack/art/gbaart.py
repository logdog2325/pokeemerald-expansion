"""
gbaart.py - shared helpers for Gen 3 sprite work (Pillow only).

Conventions used by every tool in tools/hack/art:
  * sprites are indexed PNGs ("P" mode) with at most 16 colours;
  * palette index 0 is the transparent colour;
  * frames are laid out left-to-right in a single row (object events) or
    top-to-bottom (trainer back pics), exactly like the vanilla files.
"""

import os

from PIL import Image

# Known sheet layouts: name -> (frame_w, frame_h, frames, axis)
# axis "x" = frames side by side, "y" = frames stacked.
PROFILES = {
    "ow_walk": (16, 32, 9, "x"),        # walking.png / running.png
    "ow_mach_bike": (32, 32, 9, "x"),
    "ow_acro_bike": (32, 32, 27, "x"),
    "ow_surf": (32, 32, 6, "x"),        # surfing.png (6 frames)
    "ow_field_move": (32, 32, 5, "x"),
    "ow_fishing": (32, 32, 12, "x"),
    "ow_underwater": (32, 32, 4, "x"),
    "ow_watering": (32, 32, 6, "x"),
    "ow_decorating": (16, 32, 1, "x"),
    "ow_npc16": (16, 32, 9, "x"),       # standard NPC sheet
    "ow_npc16_single": (16, 32, 1, "x"),
    "ow_npc16_3": (16, 32, 3, "x"),
    "trainer_front": (64, 64, 1, "y"),
    "trainer_back": (64, 64, 4, "y"),   # idle + 3 throw frames
    "icon": (32, 32, 2, "y"),          # Pokémon icon
    "map_icon": (16, 16, 1, "x"),      # region map / PokéNav player head
}


def load_indexed(path):
    im = Image.open(path)
    if im.mode != "P":
        raise ValueError("%s is %s, expected indexed (P)" % (path, im.mode))
    return im


def palette_rgb(im, n=16):
    pal = im.getpalette() or []
    pal = pal + [0] * (3 * 256 - len(pal))
    return [tuple(pal[i * 3:i * 3 + 3]) for i in range(n)]


def used_indices(im):
    return sorted(set(im.tobytes()))


def make_indexed(size, palette):
    """New P image whose palette is padded to 16 colours."""
    im = Image.new("P", size, 0)
    flat = []
    for c in list(palette)[:16] + [(0, 0, 0)] * (16 - len(palette)):
        flat.extend(c)
    im.putpalette(flat)
    return im


def set_palette(im, palette):
    flat = []
    for c in list(palette)[:16] + [(0, 0, 0)] * max(0, 16 - len(palette)):
        flat.extend(c)
    im.putpalette(flat)
    return im


def frames(im, fw, fh, axis="x"):
    n = (im.width // fw) if axis == "x" else (im.height // fh)
    out = []
    for i in range(n):
        box = (i * fw, 0, (i + 1) * fw, fh) if axis == "x" else (0, i * fh, fw, (i + 1) * fh)
        out.append(im.crop(box))
    return out


def join_frames(frame_list, axis="x"):
    fw, fh = frame_list[0].size
    size = (fw * len(frame_list), fh) if axis == "x" else (fw, fh * len(frame_list))
    out = Image.new("P", size, 0)
    out.putpalette(frame_list[0].getpalette())
    for i, f in enumerate(frame_list):
        out.paste(f, (i * fw, 0) if axis == "x" else (0, i * fh))
    return out


def to_rgba(im, transparent_index=0):
    """Indexed -> RGBA with index 0 transparent."""
    pal = palette_rgb(im, 256)
    src = im.load()
    out = Image.new("RGBA", im.size, (0, 0, 0, 0))
    dst = out.load()
    for y in range(im.height):
        for x in range(im.width):
            c = src[x, y]
            if c != transparent_index:
                dst[x, y] = (*pal[c], 255)
    return out


def write_jasc(path, palette):
    with open(path, "w", newline="\r\n") as f:
        f.write("JASC-PAL\n0100\n16\n")
        for c in list(palette)[:16] + [(0, 0, 0)] * (16 - len(palette)):
            f.write("%d %d %d\n" % c)


def read_jasc(path):
    with open(path) as f:
        lines = [l.strip() for l in f.read().splitlines() if l.strip()]
    n = int(lines[2])
    return [tuple(int(v) for v in lines[3 + i].split()) for i in range(n)]


def gba_color(c):
    """Snap an RGB colour to the 15-bit GBA grid (what the hardware can show)."""
    return tuple((v >> 3) << 3 for v in c)


def ensure_dir(path):
    d = os.path.dirname(path)
    if d:
        os.makedirs(d, exist_ok=True)
