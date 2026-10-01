#!/usr/bin/env python3
"""
mapbuild.py - build a map from a readable spec (ASCII terrain + stamps + events).

  python3 tools/hack/mapgen/mapbuild.py tools/hack/mapgen/specs/draconid_village.json --preview out.png
  python3 tools/hack/mapgen/mapbuild.py tools/hack/mapgen/specs/draconid_village.json --write
  python3 tools/hack/mapgen/mapbuild.py spec.json --write --overwrite-events   # also replace map.json events

Spec (JSON):
  "name": "DraconidVillage"                 map folder / name
  "map_id": "MAP_DRACONID_VILLAGE"          (default MAP_<NAME in caps>)
  "layout_id": "LAYOUT_DRACONID_VILLAGE"
  "brush": "general_fallarbor"              brush file with classes + learned rules
  -- or, instead of brush/grid, reuse vanilla blocks: --
  "copy_layout": "LAYOUT_X" | "MapName"     copy that layout's blocks into a new layout (editable copy)
  "use_layout": "LAYOUT_X"                  point the map at an existing layout (shared, no copy)
  "blockgrid": ["2F1:1:0 2EB:1:0 ...", ...] every block written out (metatile:collision:elevation), one row a
  "tilesets": ["gTileset_General", "gTileset_Cave"]    string: small rooms put together from another map's blocks
  "grid": ["TTTT....", ...]                 one char per metatile
  "legend": {"h": "ground", "d": {"block": "20A:0:3"}, "_": {"class": "ground", "elev": 4}}
                                            chars not listed use the brush's class chars
  "phase": {"T": [0, 0]}                    shift a class's 2x2 pattern
  "variety": {"ground": 0.08}               pick runners-up (tufts etc.) this often
  "stamps": [{"from": "FallarborTown", "rect": [x, y, w, h], "at": [x, y],
              "keep": ["279"], "mask": ["xx.x", ...]}]
            copy real blocks from a vanilla map. "keep" lists metatiles NOT copied (left to the
            auto-tiler), "mask" rows mark copied cells with any char except '.'.
  "blocks": [{"at": [x, y], "block": "0B3:0:1"}]            single fixed blocks, applied last
  "scatter": [{"class": "ground", "blocks": {"29F:0:3": 0.05}, "seed": 1}]
            random decorations on interior cells of a class
  "elevation": ["3333444", ...]             optional hex-digit elevation override ('.' = keep)
  "border": {"from": "Route114"} | {"blocks": ["269:1:0", ...]}   2x2 border
  "header": {...map.json header keys...}
  "group": "gMapGroup_TownsAndRoutes"
  "connections": [{"map": "MAP_ROUTE101", "direction": "left", "offset": 0, "reciprocal": true}]
  "events": {"object_events": [...], "warp_events": [...], "coord_events": [...], "bg_events": [...]}

--write creates/updates: data/layouts/<Name>/{map,border}.bin, layouts.json, map_groups.json,
data/maps/<Name>/map.json, a scripts.pory stub, and the .include in data/event_scripts.s.
Existing map.json events are kept unless --overwrite-events. Everything opens in Porymap.
"""

import argparse
import json
import os
import random
import re
import struct
import subprocess
import sys

from PIL import Image

sys.path.insert(0, os.path.dirname(__file__))
import autotile  # noqa: E402
import pokemap  # noqa: E402
import render  # noqa: E402

DEFAULT_HEADER = {
    "music": "MUS_LITTLEROOT",
    "region": "REGION_HOENN",
    "region_map_section": "MAPSEC_LITTLEROOT_TOWN",
    "requires_flash": False,
    "weather": "WEATHER_SUNNY",
    "map_type": "MAP_TYPE_TOWN",
    "allow_cycling": True,
    "allow_escaping": False,
    "allow_running": True,
    "show_map_name": True,
    "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
}

HEADER_ORDER = ["id", "name", "layout", "music", "region", "region_map_section", "requires_flash", "weather",
                "map_type", "allow_cycling", "allow_escaping", "allow_running", "show_map_name", "floor_number",
                "battle_scene", "connections", "object_events", "warp_events", "coord_events", "bg_events"]


def caps(name):
    # split lowercase->Uppercase only, like vanilla (PlayersHouse_1F -> PLAYERS_HOUSE_1F, House1 -> HOUSE1)
    return re.sub(r"(?<=[a-z])(?=[A-Z])", "_", name).upper()


def parse_block_full(s, default_col=0, default_elev=3):
    m, c, e = autotile.parse_block(s)
    return pokemap.pack_block(m, default_col if c is None else c, default_elev if e is None else e)


class Build:
    def __init__(self, spec):
        self.spec = spec
        self.name = spec["name"]
        self.proj = pokemap.Project()
        self.src_layout = None
        if "blockgrid" in spec:
            rows = [r.split() for r in spec["blockgrid"]]
            self.h, self.w = len(rows), len(rows[0])
            assert all(len(r) == self.w for r in rows), "blockgrid rows differ in length"
            self.blockgrid = [parse_block_full(b) for r in rows for b in r]
            primary, secondary = spec["tilesets"]
            self.brush = {"primary": primary, "secondary": secondary, "classes": {}, "_member_class": {}}
            return
        if "copy_layout" in spec or "use_layout" in spec:
            ref = spec.get("copy_layout") or spec.get("use_layout")
            lid = ref if ref.startswith("LAYOUT_") else self.proj.map_json(ref)["layout"]
            self.src_layout = self.proj.layout(lid)
            self.w, self.h = self.src_layout.width, self.src_layout.height
            self.brush = {"primary": self.src_layout.primary_symbol, "secondary": self.src_layout.secondary_symbol,
                          "classes": {}, "_member_class": {}}
            return
        self.brush = autotile.load_brush(spec["brush"])
        self.rules = autotile.load_rules(self.brush)
        self.grid = spec["grid"]
        self.h = len(self.grid)
        self.w = max(len(r) for r in self.grid)

    def legend(self, ch):
        leg = self.spec.get("legend", {})
        if ch in leg:
            v = leg[ch]
            if isinstance(v, str):
                return {"class": v}
            return v
        if ch in self.brush["_char_class"]:
            return {"class": self.brush["_char_class"][ch]}
        raise SystemExit("grid char %r has no legend entry and is not a brush class char" % ch)

    def build(self):
        w, h = self.w, self.h
        if "blockgrid" in self.spec:
            self.blocks = list(self.blockgrid)
            for b in self.spec.get("blocks", []):
                x, y = b["at"]
                self.blocks[y * w + x] = parse_block_full(b["block"])
            self.diag = []
            return self.blocks
        if self.src_layout is not None:
            self.blocks = list(self.src_layout.blocks)
            for b in self.spec.get("blocks", []):
                x, y = b["at"]
                self.blocks[y * w + x] = parse_block_full(b["block"])
            self.diag = []
            return self.blocks
        code = lambda cname: autotile.class_code(self.brush, cname)  # noqa: E731
        classes = [[autotile.OTHER] * w for _ in range(h)]
        fixed = {}
        elev_over = {}
        for y, row in enumerate(self.grid):
            row = row.ljust(w, row[-1])
            for x, ch in enumerate(row):
                d = self.legend(ch)
                if "block" in d:
                    fixed[(x, y)] = parse_block_full(d["block"])
                    mid = pokemap.unpack_block(fixed[(x, y)])[0]
                    classes[y][x] = code(self.brush["_member_class"].get(mid))
                else:
                    classes[y][x] = code(d["class"])
                if "elev" in d:
                    elev_over[(x, y)] = d["elev"]

        # stamps: real blocks from vanilla maps
        for st in self.spec.get("stamps", []):
            src = self.proj.layout(self.proj.map_json(st["from"])["layout"]
                                   if os.path.exists(pokemap.rel("data/maps/%s/map.json" % st["from"])) else st["from"])
            sx, sy, sw, sh = st["rect"]
            ax, ay = st["at"]
            keep = set(int(k, 16) for k in st.get("keep", []))
            mask = st.get("mask")
            for j in range(sh):
                for i in range(sw):
                    if mask and (j >= len(mask) or i >= len(mask[j]) or mask[j][i] == "."):
                        continue
                    tx, ty = ax + i, ay + j
                    if not (0 <= tx < w and 0 <= ty < h):
                        continue
                    blk = src.block(sx + i, sy + j)
                    mid = pokemap.unpack_block(blk)[0]
                    if mid in keep:
                        continue
                    fixed[(tx, ty)] = blk
                    classes[ty][tx] = code(self.brush["_member_class"].get(mid))

        phase = {}
        for c, p in self.spec.get("phase", {}).items():
            for y in range(h):
                for x in range(w):
                    if classes[y][x] == c:
                        phase[(x, y)] = tuple(p)
        variety = {code(k): v for k, v in self.spec.get("variety", {}).items()}
        resolved, diag = autotile.resolve(self.brush, self.rules, classes, phase=phase, variety=variety)

        blocks = [0] * (w * h)
        for y in range(h):
            for x in range(w):
                if (x, y) in fixed:
                    blocks[y * w + x] = fixed[(x, y)]
                elif (x, y) in resolved:
                    blocks[y * w + x] = parse_block_full(resolved[(x, y)])
                else:
                    blocks[y * w + x] = parse_block_full(self.brush["classes"]["ground"]["default"]) if "ground" in self.brush["classes"] else 0

        # scatter decorations on interior cells
        for sc in self.spec.get("scatter", []):
            rng = random.Random(sc.get("seed", 1))
            c = code(sc["class"])
            items = [(parse_block_full(b), p) for b, p in sc["blocks"].items()]
            for y in range(h):
                for x in range(w):
                    if (x, y) in fixed or classes[y][x] != c:
                        continue
                    nb = autotile.neighbours(classes, x, y, w, h, autotile.N8)
                    if sc.get("interior", True) and any(n != c for n in nb):
                        continue
                    r = rng.random()
                    for blk, p in items:
                        if r < p:
                            blocks[y * w + x] = blk
                            break
                        r -= p

        for b in self.spec.get("blocks", []):
            x, y = b["at"]
            blocks[y * w + x] = parse_block_full(b["block"])
            if "elev" in b:
                elev_over[(x, y)] = b["elev"]

        for y, row in enumerate(self.spec.get("elevation", [])):
            for x, ch in enumerate(row):
                if ch != ".":
                    elev_over[(x, y)] = int(ch, 16)
        for (x, y), e in elev_over.items():
            m, c, _ = pokemap.unpack_block(blocks[y * w + x])
            blocks[y * w + x] = pokemap.pack_block(m, c, e)

        self.blocks = blocks
        self.diag = diag
        return blocks

    def border(self):
        if self.src_layout is not None:
            return list(self.src_layout.border)
        b = self.spec.get("border", {})
        if "blocks" in b:
            return [parse_block_full(v, 0, 0) for v in b["blocks"]]
        if "from" in b:
            src = self.proj.layout(self.proj.map_json(b["from"])["layout"])
            return list(src.border)
        return [parse_block_full(self.brush["classes"]["tree"]["default"], 0, 0)] * 4 if "tree" in self.brush["classes"] else [0] * 4

    # -- preview -----------------------------------------------------------
    def fake_layout(self):
        entry = {
            "id": "PREVIEW", "name": self.name, "width": self.w, "height": self.h,
            "primary_tileset": self.brush["primary"], "secondary_tileset": self.brush["secondary"],
            "border_filepath": "/nonexistent", "blockdata_filepath": "/nonexistent",
        }
        L = pokemap.Layout(entry)
        L.blocks = list(self.blocks)
        L.border = self.border()
        return L

    def preview(self, out, scale=2, grid=False, collision=False, border=0):
        L = self.fake_layout()
        img = render.render_layout(self.proj, L, border=border)
        if collision:
            render.overlay_collision(img, L, border)
        mapj = {k: self.spec.get("events", {}).get(k, []) for k in ("object_events", "warp_events", "coord_events", "bg_events")}
        render.overlay_events(img, mapj, border)
        if grid:
            render.overlay_grid(img, L.width, L.height, border)
        img = img.resize((img.width * scale, img.height * scale), Image.NEAREST)
        img.save(out)
        print("preview", out, img.size, "| deep fallbacks:", len(self.diag))

    # -- write -------------------------------------------------------------
    def write(self, overwrite_events=False):
        name = self.name
        map_id = self.spec.get("map_id", "MAP_" + caps(name))
        if "use_layout" in self.spec:
            layout_id = self.src_layout.id
            write_map_json(name, map_id, layout_id, self.spec, overwrite_events)
            register_map(name, self.spec.get("group", "gMapGroup_TownsAndRoutes"))
            print("wrote %s using shared %s" % (map_id, layout_id))
            return
        layout_id = self.spec.get("layout_id", "LAYOUT_" + caps(name))
        lay_dir = "data/layouts/%s" % name
        os.makedirs(pokemap.rel(lay_dir), exist_ok=True)
        with open(pokemap.rel(lay_dir + "/map.bin"), "wb") as f:
            f.write(struct.pack("<%dH" % len(self.blocks), *self.blocks))
        with open(pokemap.rel(lay_dir + "/border.bin"), "wb") as f:
            bd = self.border()
            f.write(struct.pack("<%dH" % len(bd), *bd))

        lj = pokemap.read_json("data/layouts/layouts.json")
        entry = {
            "id": layout_id, "name": name + "_Layout", "width": self.w, "height": self.h,
            "primary_tileset": self.brush["primary"], "secondary_tileset": self.brush["secondary"],
            "border_filepath": lay_dir + "/border.bin", "blockdata_filepath": lay_dir + "/map.bin",
            "layout_version": "emerald",
        }
        if self.src_layout is not None and (self.src_layout.border_w, self.src_layout.border_h) != (2, 2):
            entry["border_width"], entry["border_height"] = self.src_layout.border_w, self.src_layout.border_h
        for i, l in enumerate(lj["layouts"]):
            if l.get("id") == layout_id:
                lj["layouts"][i] = entry
                break
        else:
            lj["layouts"].append(entry)
        pokemap.write_json("data/layouts/layouts.json", lj)

        old_conns = (pokemap.read_json("data/maps/%s/map.json" % name).get("connections") or []
                     if os.path.exists(pokemap.rel("data/maps/%s/map.json" % name)) else [])
        write_map_json(name, map_id, layout_id, self.spec, overwrite_events)
        register_map(name, self.spec.get("group", "gMapGroup_TownsAndRoutes"))
        if "connections" in self.spec:
            keep = {(c["map"], c["direction"]) for c in self.spec["connections"]}
            for c in old_conns:
                if (c["map"], c["direction"]) not in keep:
                    remove_connection(map_id, c)
        for c in self.spec.get("connections", []):
            add_connection(map_id, c)
        print("wrote %s (%dx%d) + %s" % (map_id, self.w, self.h, layout_id))
        # connected maps with other tilesets must not show secondary metatiles across the seam
        subprocess.run([sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)), "check_seams.py"), name])


def write_map_json(name, map_id, layout_id, spec, overwrite_events=False):
    path = "data/maps/%s/map.json" % name
    os.makedirs(pokemap.rel("data/maps/" + name), exist_ok=True)
    old = pokemap.read_json(path) if os.path.exists(pokemap.rel(path)) else None
    m = dict(DEFAULT_HEADER)
    m.update(spec.get("header", {}))
    m["id"], m["name"], m["layout"] = map_id, name, layout_id
    ev = spec.get("events", {})
    for k in ("object_events", "warp_events", "coord_events", "bg_events"):
        if old is not None and not overwrite_events:
            m[k] = old.get(k, [])
        else:
            m[k] = ev.get(k, [])
    m["connections"] = old.get("connections") if old else None
    out = {k: m[k] for k in HEADER_ORDER if k in m}
    pokemap.write_json(path, out)
    ensure_script_file(name)


def ensure_script_file(name):
    pory = pokemap.rel("data/maps/%s/scripts.pory" % name)
    inc = pokemap.rel("data/maps/%s/scripts.inc" % name)
    if not os.path.exists(pory) and not os.path.exists(inc):
        with open(pory, "w") as f:
            f.write("mapscripts %s_MapScripts {}\n" % name)
    es = pokemap.rel("data/event_scripts.s")
    text = open(es).read()
    line = '\t.include "data/maps/%s/scripts.inc"\n' % name
    if line not in text:
        # keep Emerald map script includes together: after the last one before the
        # FRLG-only block (".if IS_FRLG"), otherwise the scripts vanish from Emerald builds
        frlg = text.find(".if IS_FRLG")
        idx = text.rfind('.include "data/maps/', 0, frlg if frlg >= 0 else len(text))
        end = text.index("\n", idx) + 1
        text = text[:end] + line + text[end:]
        open(es, "w").write(text)


def register_map(name, group):
    mg = pokemap.read_json("data/maps/map_groups.json")
    for g in mg["group_order"]:
        if name in mg[g]:
            return
    if group not in mg:
        mg[group] = []
        mg["group_order"].append(group)
    mg[group].append(name)
    pokemap.write_json("data/maps/map_groups.json", mg)


OPPOSITE = {"up": "down", "down": "up", "left": "right", "right": "left", "dive": "emerge", "emerge": "dive"}


def remove_connection(map_id, c):
    """Drop a connection that is no longer in the spec, in both directions."""
    proj = pokemap.Project()
    for name, target, direction in [(proj.map_name_for_id(map_id), c["map"], c["direction"]),
                                    (proj.map_name_for_id(c["map"]), map_id, OPPOSITE[c["direction"]])]:
        if name is None:
            continue
        path = "data/maps/%s/map.json" % name
        mj = pokemap.read_json(path)
        mj["connections"] = [x for x in (mj.get("connections") or [])
                             if not (x["map"] == target and x["direction"] == direction)] or None
        pokemap.write_json(path, mj)
        print("removed connection %s -> %s (%s)" % (name, target, direction))


def add_connection(map_id, c):
    proj = pokemap.Project()
    src_name = proj.map_name_for_id(map_id)
    dst_name = proj.map_name_for_id(c["map"])
    for name, target, direction, offset in [(src_name, c["map"], c["direction"], c.get("offset", 0)),
                                            (dst_name, map_id, OPPOSITE[c["direction"]], -c.get("offset", 0))]:
        if name is None:
            continue
        if name == dst_name and not c.get("reciprocal", True):
            continue
        path = "data/maps/%s/map.json" % name
        mj = pokemap.read_json(path)
        conns = [x for x in (mj.get("connections") or []) if not (x["map"] == target and x["direction"] == direction)]
        conns.append({"map": target, "offset": offset, "direction": direction})
        mj["connections"] = conns
        pokemap.write_json(path, mj)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("spec")
    ap.add_argument("--preview")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--overwrite-events", action="store_true")
    ap.add_argument("--grid", action="store_true")
    ap.add_argument("--collision", action="store_true")
    ap.add_argument("--border", type=int, default=0)
    ap.add_argument("--scale", type=int, default=2)
    args = ap.parse_args()
    spec = json.load(open(args.spec))
    b = Build(spec)
    b.build()
    if args.preview:
        b.preview(args.preview, args.scale, args.grid, args.collision, args.border)
    if args.write:
        b.write(args.overwrite_events)
    if b.diag:
        levels = {}
        for x, y, lvl in b.diag:
            levels.setdefault(lvl, []).append((x, y))
        for lvl, cells in sorted(levels.items()):
            print("  fallback level %d at %d cell(s): %s" % (lvl, len(cells), cells[:8]))


if __name__ == "__main__":
    main()
