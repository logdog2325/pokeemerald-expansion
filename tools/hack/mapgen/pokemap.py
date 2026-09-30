"""
pokemap.py - shared library for the Draconid Emerald command-line map tools.

Reads the real project data (layouts.json, map.json, tileset headers, metatile
binaries, tile sheets, palettes, object event graphics tables) so every tool
works from actual metatile IDs instead of guesses.

Nothing here writes to the project; see mapbuild.py / newmap.py for writers.
"""

import json
import os
import re
import struct
from functools import lru_cache

from PIL import Image

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))

NUM_TILES_IN_PRIMARY = 512
NUM_METATILES_IN_PRIMARY = 512
NUM_PALS_IN_PRIMARY = 6
NUM_PALS_TOTAL = 13

MAPGRID_METATILE_ID_MASK = 0x03FF
MAPGRID_COLLISION_MASK = 0x0C00
MAPGRID_COLLISION_SHIFT = 10
MAPGRID_ELEVATION_MASK = 0xF000
MAPGRID_ELEVATION_SHIFT = 12

METATILE_ATTR_BEHAVIOR_MASK = 0x00FF
METATILE_ATTR_LAYER_SHIFT = 12

LAYER_NORMAL, LAYER_COVERED, LAYER_SPLIT = 0, 1, 2


def rel(path):
    return os.path.join(ROOT, path)


def read_json(path):
    with open(rel(path)) as f:
        return json.load(f)


def write_json(path, data):
    """Write JSON the way Porymap does (2-space indent, trailing newline)."""
    with open(rel(path), "w") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write("\n")


def pack_block(metatile, collision=0, elevation=0):
    return (metatile & MAPGRID_METATILE_ID_MASK) | ((collision & 3) << MAPGRID_COLLISION_SHIFT) | ((elevation & 15) << MAPGRID_ELEVATION_SHIFT)


def unpack_block(v):
    return v & MAPGRID_METATILE_ID_MASK, (v & MAPGRID_COLLISION_MASK) >> MAPGRID_COLLISION_SHIFT, (v & MAPGRID_ELEVATION_MASK) >> MAPGRID_ELEVATION_SHIFT


def read_jasc_pal(path):
    with open(rel(path)) as f:
        lines = [l.strip() for l in f.read().splitlines() if l.strip()]
    assert lines[0] == "JASC-PAL", path
    n = int(lines[2])
    return [tuple(int(c) for c in lines[3 + i].split()[:3]) for i in range(n)]


# ---------------------------------------------------------------------------
# Tilesets
# ---------------------------------------------------------------------------

class TilesetIndex:
    """Resolves gTileset_* symbols to their asset files by parsing src/data/tilesets/*.h."""

    def __init__(self):
        headers = open(rel("src/data/tilesets/headers.h")).read()
        # Most tilesets live in src/data/tilesets/graphics.h, but the primary
        # ones (General, Building) are declared in src/graphics.c.
        graphics = open(rel("src/data/tilesets/graphics.h")).read() + open(rel("src/graphics.c")).read()
        metatiles = open(rel("src/data/tilesets/metatiles.h")).read()
        self.headers = {}
        for m in re.finditer(r"const struct Tileset (gTileset_\w+)\s*=\s*\{(.*?)\};", headers, re.S):
            body = m.group(2)
            fields = dict(re.findall(r"\.(\w+)\s*=\s*([^,]+),", body))
            self.headers[m.group(1)] = fields
        self.tiles = {}
        for m in re.finditer(r"const u32 (gTilesetTiles_\w+)\[\]\s*=\s*INC\w+\(\"([^\"]+)\"", graphics):
            self.tiles[m.group(1)] = m.group(2)
        self.palettes = {}
        for m in re.finditer(r"const u16 (?:ALIGNED\(\d+\) )?(gTilesetPalettes_\w+)\[\]\[16\]\s*=\s*\{(.*?)\};", graphics, re.S):
            self.palettes[m.group(1)] = re.findall(r"\"([^\"]+\.pal)\"", m.group(2))
        self.metatiles = {}
        self.attributes = {}
        for m in re.finditer(r"const u16 (gMetatiles_\w+)\[\]\s*=\s*INCBIN_U16\(\"([^\"]+)\"\)", metatiles):
            self.metatiles[m.group(1)] = m.group(2)
        for m in re.finditer(r"const u16 (gMetatileAttributes_\w+)\[\]\s*=\s*INCBIN_U16\(\"([^\"]+)\"\)", metatiles):
            self.attributes[m.group(1)] = m.group(2)

    def names(self):
        return sorted(self.headers)

    def info(self, symbol):
        h = self.headers[symbol]
        return {
            "secondary": h.get("isSecondary", "FALSE").strip() == "TRUE",
            "tiles": self.tiles.get(h["tiles"].strip()),
            "palettes": self.palettes.get(h["palettes"].strip(), []),
            "metatiles": self.metatiles.get(h["metatiles"].strip()),
            "attributes": self.attributes.get(h["metatileAttributes"].strip()),
        }


@lru_cache(maxsize=None)
def tileset_index():
    return TilesetIndex()


class Tileset:
    def __init__(self, symbol):
        self.symbol = symbol
        info = tileset_index().info(symbol)
        self.secondary = info["secondary"]
        self.dir = os.path.dirname(info["metatiles"])
        img = Image.open(rel(info["tiles"]))
        if img.mode != "P":
            img = img.convert("P")
        self.tile_img = img
        w, h = img.size
        self.num_tiles = (w // 8) * (h // 8)
        self.tiles_per_row = w // 8
        self.pixels = img.load()
        self.palettes = [read_jasc_pal(p) for p in info["palettes"]]
        raw = open(rel(info["metatiles"]), "rb").read()
        self.metatiles = [struct.unpack_from("<8H", raw, i * 16) for i in range(len(raw) // 16)]
        rawa = open(rel(info["attributes"]), "rb").read()
        self.attributes = list(struct.unpack("<%dH" % (len(rawa) // 2), rawa))

    def tile_indices(self, tile):
        """Return 8x8 list of color indices for local tile number."""
        tx = (tile % self.tiles_per_row) * 8
        ty = (tile // self.tiles_per_row) * 8
        px = self.pixels
        return [[px[tx + x, ty + y] & 0xF for x in range(8)] for y in range(8)]


class TilesetPair:
    """A primary + secondary tileset as the game combines them."""

    def __init__(self, primary, secondary):
        self.primary = Tileset(primary) if isinstance(primary, str) else primary
        self.secondary = Tileset(secondary) if isinstance(secondary, str) else secondary
        pals = []
        for i in range(NUM_PALS_TOTAL):
            src = self.primary if i < NUM_PALS_IN_PRIMARY else self.secondary
            pals.append(src.palettes[i] if i < len(src.palettes) else [(255, 0, 255)] * 16)
        self.palettes = pals
        self._tile_cache = {}
        self._meta_cache = {}

    @property
    def num_metatiles(self):
        return NUM_METATILES_IN_PRIMARY + len(self.secondary.metatiles)

    def metatile(self, mid):
        if mid < NUM_METATILES_IN_PRIMARY:
            ts, local = self.primary, mid
        else:
            ts, local = self.secondary, mid - NUM_METATILES_IN_PRIMARY
        if local >= len(ts.metatiles):
            return None, 0
        return ts.metatiles[local], ts.attributes[local]

    def behavior(self, mid):
        _, attr = self.metatile(mid)
        return attr & METATILE_ATTR_BEHAVIOR_MASK

    def layer_type(self, mid):
        _, attr = self.metatile(mid)
        return attr >> METATILE_ATTR_LAYER_SHIFT

    def _tile_rgba(self, entry):
        key = entry
        if key in self._tile_cache:
            return self._tile_cache[key]
        tile = entry & 0x3FF
        hflip = (entry >> 10) & 1
        vflip = (entry >> 11) & 1
        pal = (entry >> 12) & 0xF
        if tile < NUM_TILES_IN_PRIMARY:
            ts, local = self.primary, tile
        else:
            ts, local = self.secondary, tile - NUM_TILES_IN_PRIMARY
        im = Image.new("RGBA", (8, 8), (0, 0, 0, 0))
        if local < ts.num_tiles and pal < len(self.palettes):
            idx = ts.tile_indices(local)
            colors = self.palettes[pal]
            p = im.load()
            for y in range(8):
                for x in range(8):
                    c = idx[y][x]
                    if c:
                        r, g, b = colors[c]
                        p[x, y] = (r, g, b, 255)
            if hflip:
                im = im.transpose(Image.FLIP_LEFT_RIGHT)
            if vflip:
                im = im.transpose(Image.FLIP_TOP_BOTTOM)
        self._tile_cache[key] = im
        return im

    def render_metatile(self, mid, background=True):
        key = (mid, background)
        if key in self._meta_cache:
            return self._meta_cache[key]
        entries, _ = self.metatile(mid)
        bg = self.palettes[0][0] if background else (0, 0, 0)
        im = Image.new("RGBA", (16, 16), (*bg, 255 if background else 0))
        if entries is None:
            # out-of-range metatile: draw magenta X so mistakes are obvious
            p = im.load()
            for i in range(16):
                p[i, i] = p[15 - i, i] = (255, 0, 255, 255)
        else:
            for layer in range(2):
                for q in range(4):
                    e = entries[layer * 4 + q]
                    t = self._tile_rgba(e)
                    im.alpha_composite(t, ((q % 2) * 8, (q // 2) * 8))
        self._meta_cache[key] = im
        return im

    def render_sheet(self, secondary_only=False, scale=2, label=True, cols=8):
        """Render all metatiles in a labelled grid (for picking IDs by eye)."""
        from PIL import ImageDraw
        start = NUM_METATILES_IN_PRIMARY if secondary_only else 0
        ids = list(range(start, NUM_METATILES_IN_PRIMARY)) if False else []
        ids = list(range(0 if not secondary_only else NUM_METATILES_IN_PRIMARY,
                         NUM_METATILES_IN_PRIMARY + len(self.secondary.metatiles)))
        if not secondary_only:
            ids = list(range(0, len(self.primary.metatiles))) + list(
                range(NUM_METATILES_IN_PRIMARY, NUM_METATILES_IN_PRIMARY + len(self.secondary.metatiles)))
        cell = 16 * scale + (12 if label else 0)
        rows = (len(ids) + cols - 1) // cols
        sheet = Image.new("RGBA", (cols * (16 * scale + 4), rows * (cell + 4)), (40, 40, 40, 255))
        d = ImageDraw.Draw(sheet)
        for i, mid in enumerate(ids):
            x = (i % cols) * (16 * scale + 4)
            y = (i // cols) * (cell + 4)
            sheet.alpha_composite(self.render_metatile(mid).resize((16 * scale, 16 * scale), Image.NEAREST), (x, y + (12 if label else 0)))
            if label:
                d.text((x, y), "%03X" % mid, fill=(255, 255, 0, 255))
        return sheet


# ---------------------------------------------------------------------------
# Layouts & maps
# ---------------------------------------------------------------------------

class Layout:
    def __init__(self, entry):
        self.entry = entry
        self.id = entry["id"]
        self.name = entry["name"]
        self.width = entry["width"]
        self.height = entry["height"]
        self.primary_symbol = entry["primary_tileset"]
        self.secondary_symbol = entry["secondary_tileset"]
        self.border_w = entry.get("border_width", 2)
        self.border_h = entry.get("border_height", 2)
        self.blocks = self._read(entry["blockdata_filepath"], self.width * self.height)
        self.border = self._read(entry["border_filepath"], self.border_w * self.border_h)

    @staticmethod
    def _read(path, n):
        p = rel(path)
        if not os.path.exists(p):
            return [0] * n
        raw = open(p, "rb").read()
        return list(struct.unpack("<%dH" % (len(raw) // 2), raw))

    def block(self, x, y):
        return self.blocks[y * self.width + x]

    def metatile_at(self, x, y):
        return self.blocks[y * self.width + x] & MAPGRID_METATILE_ID_MASK

    def save(self):
        with open(rel(self.entry["blockdata_filepath"]), "wb") as f:
            f.write(struct.pack("<%dH" % len(self.blocks), *self.blocks))
        with open(rel(self.entry["border_filepath"]), "wb") as f:
            f.write(struct.pack("<%dH" % len(self.border), *self.border))


class Project:
    def __init__(self):
        self.layouts_json = read_json("data/layouts/layouts.json")
        self.map_groups = read_json("data/maps/map_groups.json")
        self._layouts = {l["id"]: l for l in self.layouts_json["layouts"] if "id" in l}
        self._pairs = {}

    def layout_ids(self):
        return list(self._layouts)

    def layout(self, layout_id):
        return Layout(self._layouts[layout_id])

    def map_names(self):
        names = []
        for g in self.map_groups["group_order"]:
            names.extend(self.map_groups[g])
        return names

    def map_json(self, map_name):
        return read_json("data/maps/%s/map.json" % map_name)

    def map_name_for_id(self, map_id):
        for n in self.map_names():
            p = rel("data/maps/%s/map.json" % n)
            if os.path.exists(p):
                with open(p) as f:
                    if json.load(f).get("id") == map_id:
                        return n
        return None

    def tileset_pair(self, primary, secondary):
        key = (primary, secondary)
        if key not in self._pairs:
            self._pairs[key] = TilesetPair(primary, secondary)
        return self._pairs[key]

    def pair_for_layout(self, layout):
        return self.tileset_pair(layout.primary_symbol, layout.secondary_symbol)


# ---------------------------------------------------------------------------
# Object event graphics (for previews)
# ---------------------------------------------------------------------------

class ObjectGfx:
    """Resolves OBJ_EVENT_GFX_* constants to their first frame for map previews."""

    def __init__(self):
        base = "src/data/object_events/"
        ptrs = open(rel(base + "object_event_graphics_info_pointers.h")).read()
        infos = open(rel(base + "object_event_graphics_info.h")).read()
        pics = open(rel(base + "object_event_pic_tables.h")).read()
        gfx = open(rel(base + "object_event_graphics.h")).read()
        self.gfx_to_info = dict(re.findall(r"\[(OBJ_EVENT_GFX_\w+)\]\s*=\s*&(\w+)", ptrs))
        self.info = {}
        for m in re.finditer(r"const struct ObjectEventGraphicsInfo (\w+)\s*=\s*\{(.*?)\};", infos, re.S):
            f = dict(re.findall(r"\.(\w+)\s*=\s*([^,]+),", m.group(2)))
            self.info[m.group(1)] = f
        self.pic_tables = {}
        for m in re.finditer(r"static const struct SpriteFrameImage (\w+)\[\]\s*=\s*\{(.*?)\};", pics, re.S):
            sym = re.search(r"(gObjectEventPic_\w+)", m.group(2))
            if sym:
                self.pic_tables[m.group(1)] = sym.group(1)
        self.pic_files = {}
        for m in re.finditer(r"const u32 (gObjectEventPic_\w+)\[\]\s*=\s*INC\w+\(\"([^\"]+)\"", gfx):
            path = m.group(2)
            path = re.sub(r"\.4bpp$", ".png", path)
            self.pic_files[m.group(1)] = path
        self._cache = {}

    def frame(self, gfx_const):
        if gfx_const in self._cache:
            return self._cache[gfx_const]
        img = None
        try:
            info = self.info[self.gfx_to_info[gfx_const]]
            w, h = int(info["width"]), int(info["height"])
            pic = self.pic_files[self.pic_tables[info["images"].strip()]]
            src = Image.open(rel(pic))
            pal = src.getpalette()
            src = src.convert("P") if src.mode != "P" else src
            fr = src.crop((0, 0, w, h))
            img = Image.new("RGBA", (w, h), (0, 0, 0, 0))
            p = img.load()
            fp = fr.load()
            for y in range(h):
                for x in range(w):
                    c = fp[x, y]
                    if c:
                        p[x, y] = (pal[c * 3], pal[c * 3 + 1], pal[c * 3 + 2], 255)
        except Exception:
            img = None
        self._cache[gfx_const] = img
        return img


@lru_cache(maxsize=None)
def object_gfx():
    return ObjectGfx()
