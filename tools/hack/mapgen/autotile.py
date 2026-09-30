#!/usr/bin/env python3
"""
autotile.py - learn auto-tiling rules from vanilla maps and resolve class grids.

A *brush file* (tools/hack/mapgen/brushes/<name>.json) names a tileset pair,
the vanilla maps to learn from, and terrain classes (tree, cliff, water, path,
ground, ...) as lists of real metatile IDs. `learn` scans every learn_from map,
labels each cell with its class, and records which block (metatile + collision
+ elevation) vanilla mappers used for each neighbourhood:

  key                                          fallback order
  C | ctx8 (classes of 8 neighbours) | parity   1
  C | ctx8                                     2
  C | ctx4 (4 neighbours)            | parity   3
  C | ctx4                                     4
  C | same-class 8-mask (normalised) | parity   5
  C | same-class 8-mask                        6
  C | same-class 4-mask              | parity   7
  C | same-class 4-mask                        8
  C | parity                                   9
  C                                            10  (brush "default")

"parity" is (x%2, y%2) after aligning each map so the class's most common
interior tile sits on (0,0) – that is what keeps 2x2 tree patterns intact.
Cells outside the map count as the same class (forests run off the edge).

  python3 tools/hack/mapgen/autotile.py learn general_fallarbor
  python3 tools/hack/mapgen/autotile.py stats general_fallarbor
"""

import json
import os
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(__file__))
import pokemap  # noqa: E402

BRUSH_DIR = os.path.join(os.path.dirname(__file__), "brushes")
N8 = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]
N4 = [(0, -1), (-1, 0), (1, 0), (0, 1)]
OTHER = "o"


def parse_block(s):
    """'279' | '279:0:3' | 0x279 -> (metatile, collision, elevation or None)."""
    if isinstance(s, int):
        return s, None, None
    parts = str(s).split(":")
    mid = int(parts[0], 16)
    col = int(parts[1]) if len(parts) > 1 else None
    elev = int(parts[2], 16) if len(parts) > 2 else None
    return mid, col, elev


def block_str(v):
    m, c, e = pokemap.unpack_block(v)
    return "%03X:%d:%X" % (m, c, e)


def load_brush(name):
    path = name if name.endswith(".json") else os.path.join(BRUSH_DIR, name + ".json")
    brush = json.load(open(path))
    brush["_path"] = path
    brush["_name"] = os.path.splitext(os.path.basename(path))[0]
    member_class = {}
    for cname, c in brush["classes"].items():
        c["_ids"] = set(parse_block(m)[0] for m in c.get("members", []))
        for m in c["_ids"]:
            member_class[m] = cname
    brush["_member_class"] = member_class
    brush["_char_class"] = {c["char"]: cname for cname, c in brush["classes"].items() if "char" in c}
    return brush


def class_code(brush, cname):
    """Single-character code used inside rule keys."""
    if cname is None or cname == OTHER:
        return OTHER
    return brush["classes"][cname].get("code", cname[0].upper())


def norm8(mask_bits):
    """Clear diagonal bits unless both adjacent orthogonals are set (47-blob normalisation)."""
    b = list(mask_bits)
    # indices: 0 NW,1 N,2 NE,3 W,4 E,5 SW,6 S,7 SE
    if not (b[1] and b[3]):
        b[0] = 0
    if not (b[1] and b[4]):
        b[2] = 0
    if not (b[6] and b[3]):
        b[5] = 0
    if not (b[6] and b[4]):
        b[7] = 0
    return "".join(str(v) for v in b)


def keys_for(cls, ctx8, ctx4, px, py, parity=True):
    same8 = norm8([1 if c == cls else 0 for c in ctx8])
    same4 = "".join("1" if c == cls else "0" for c in ctx4)
    c8 = "".join(ctx8)
    c4 = "".join(ctx4)
    p = "%d%d" % (px, py)
    keys = [
        "%s|c8=%s|p=%s" % (cls, c8, p),
        "%s|c8=%s" % (cls, c8),
        "%s|c4=%s|p=%s" % (cls, c4, p),
        "%s|c4=%s" % (cls, c4),
        "%s|m8=%s|p=%s" % (cls, same8, p),
        "%s|m8=%s" % (cls, same8),
        "%s|m4=%s|p=%s" % (cls, same4, p),
        "%s|m4=%s" % (cls, same4),
        "%s|p=%s" % (cls, p),
    ]
    if not parity:
        # classes without a 2x2 pattern (cliffs, ground, water...) skip the parity keys
        keys = [k if "|p=" not in k else None for k in keys]
    return keys


def neighbours(grid, x, y, w, h, offsets):
    out = []
    here = grid[y][x]
    for dx, dy in offsets:
        nx, ny = x + dx, y + dy
        out.append(grid[ny][nx] if 0 <= nx < w and 0 <= ny < h else here)
    return out


# ---------------------------------------------------------------------------
# learning
# ---------------------------------------------------------------------------

def label_layout(brush, layout):
    grid = []
    for y in range(layout.height):
        row = []
        for x in range(layout.width):
            cname = brush["_member_class"].get(layout.metatile_at(x, y))
            row.append(class_code(brush, cname))
        grid.append(row)
    return grid


def components(grid, cls):
    """4-connected regions of one class -> list of cell lists."""
    h, w = len(grid), len(grid[0])
    seen = [[False] * w for _ in range(h)]
    out = []
    for y in range(h):
        for x in range(w):
            if grid[y][x] != cls or seen[y][x]:
                continue
            stack, cells = [(x, y)], []
            seen[y][x] = True
            while stack:
                cx, cy = stack.pop()
                cells.append((cx, cy))
                for dx, dy in N4:
                    nx, ny = cx + dx, cy + dy
                    if 0 <= nx < w and 0 <= ny < h and not seen[ny][nx] and grid[ny][nx] == cls:
                        seen[ny][nx] = True
                        stack.append((nx, ny))
            out.append(cells)
    return out


def map_phases(brush, layout, grid, anchors):
    """Per-cell phase of a labelled vanilla layout: for every connected region of a class,
    the (x%2, y%2) where that region's anchor tile sits. Returns {(x, y): (px, py)}."""
    out = {}
    for c, anchor in anchors.items():
        whole = Counter((x % 2, y % 2) for y in range(layout.height) for x in range(layout.width)
                        if grid[y][x] == c and layout.metatile_at(x, y) == anchor)
        default = whole.most_common(1)[0][0] if whole else (0, 0)
        for cells in components(grid, c):
            par = Counter((x % 2, y % 2) for x, y in cells if layout.metatile_at(x, y) == anchor)
            ph = par.most_common(1)[0][0] if par else default
            for xy in cells:
                out[xy] = ph
    return out


def learn(brush):
    proj = pokemap.Project()
    layouts = []
    for m in brush["learn_from"]:
        lid = proj.map_json(m)["layout"] if os.path.exists(pokemap.rel("data/maps/%s/map.json" % m)) else m
        L = proj.layout(lid)
        if (L.primary_symbol, L.secondary_symbol) != (brush["primary"], brush["secondary"]):
            print("skip %s: tilesets %s/%s" % (m, L.primary_symbol, L.secondary_symbol))
            continue
        layouts.append((m, L, label_layout(brush, L)))

    codes = {class_code(brush, c): c for c in brush["classes"]}
    # 1) anchor tile per class = most common block among fully surrounded cells
    interior = defaultdict(Counter)
    for _, L, g in layouts:
        for y in range(L.height):
            for x in range(L.width):
                c = g[y][x]
                if c == OTHER:
                    continue
                if all(n == c for n in neighbours(g, x, y, L.width, L.height, N8)):
                    interior[c][L.metatile_at(x, y)] += 1
    anchors = {c: cnt.most_common(1)[0][0] for c, cnt in interior.items() if cnt}
    for cname, cdef in brush["classes"].items():
        if "anchor" in cdef:
            anchors[class_code(brush, cname)] = parse_block(cdef["anchor"])[0]

    # 2) per-map phase for each class
    rules = defaultdict(Counter)
    for name, L, g in layouts:
        cell_phase = map_phases(brush, L, g, anchors)
        for y in range(L.height):
            for x in range(L.width):
                c = g[y][x]
                if c == OTHER:
                    continue
                ph = cell_phase.get((x, y), (0, 0))
                px, py = (x - ph[0]) % 2, (y - ph[1]) % 2
                ctx8 = neighbours(g, x, y, L.width, L.height, N8)
                ctx4 = neighbours(g, x, y, L.width, L.height, N4)
                blk = L.block(x, y)
                for k in keys_for(c, ctx8, ctx4, px, py):
                    rules[k][blk] += 1

    out = {
        "brush": brush["_name"],
        "primary": brush["primary"],
        "secondary": brush["secondary"],
        "codes": codes,
        "anchors": {c: "%03X" % a for c, a in anchors.items()},
        "rules": {k: [[block_str(b), n] for b, n in cnt.most_common(6)] for k, cnt in sorted(rules.items())},
    }
    path = os.path.join(BRUSH_DIR, brush["_name"] + ".rules.json")
    with open(path, "w") as f:
        json.dump(out, f, indent=0, sort_keys=True)
        f.write("\n")
    print("learned %d keys from %d maps -> %s" % (len(out["rules"]), len(layouts), os.path.relpath(path, pokemap.ROOT)))
    return out


def load_rules(brush):
    path = os.path.join(BRUSH_DIR, brush["_name"] + ".rules.json")
    if not os.path.exists(path):
        return learn(brush)
    return json.load(open(path))


# ---------------------------------------------------------------------------
# resolving
# ---------------------------------------------------------------------------

def _pick(options, x, y, variety):
    """Most common block; with variety, weighted choice among close runners-up."""
    if not variety or len(options) == 1:
        return options[0][0]
    top = options[0][1]
    cands = [(b, n) for b, n in options if n >= top * variety]
    total = sum(n for _, n in cands)
    h = (x * 73856093 ^ y * 19349663) % max(total, 1)
    for b, n in cands:
        if h < n:
            return b
        h -= n
    return cands[0][0]


def resolve(brush, rules, class_grid, phase=(0, 0), variety=None):
    """class_grid: 2D list of class codes (or OTHER). Returns {(x,y): block_str} for class cells
    and a list of (x, y, key-level) diagnostics for cells that needed deep fallbacks.
    phase is an (x, y) tuple for every cell, or a {(x, y): (px, py)} dict (see map_phases)."""
    h = len(class_grid)
    w = len(class_grid[0])
    variety = variety or {}
    out, diag = {}, []
    codes = rules["codes"]
    for y in range(h):
        for x in range(w):
            c = class_grid[y][x]
            if c == OTHER:
                continue
            ph = phase.get((x, y), (0, 0)) if isinstance(phase, dict) else phase
            px, py = (x - ph[0]) % 2, (y - ph[1]) % 2
            ctx8 = neighbours(class_grid, x, y, w, h, N8)
            ctx4 = neighbours(class_grid, x, y, w, h, N4)
            chosen = None
            cdef = brush["classes"].get(codes.get(c), {})
            near = set(ctx8)
            banned = set()
            for r in cdef.get("only_near", []):
                if not near & set(r["classes"]):
                    banned.update(parse_block(t)[0] for t in r["tiles"])
            for level, k in enumerate(keys_for(c, ctx8, ctx4, px, py, cdef.get("parity", True))):
                if k is None or k not in rules["rules"]:
                    continue
                opts = [o for o in rules["rules"][k] if parse_block(o[0])[0] not in banned]
                if not opts:
                    continue
                interior = all(n == c for n in ctx8)
                chosen = _pick(opts, x, y, variety.get(c) if interior and level < 2 else None)
                if level >= 4:
                    diag.append((x, y, level + 1))
                break
            if chosen is None:
                cname = codes.get(c)
                chosen = brush["classes"][cname]["default"] if cname else "000:1:0"
                diag.append((x, y, 10))
            out[(x, y)] = chosen
    return out, diag


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(2)
    cmd, name = sys.argv[1], sys.argv[2]
    brush = load_brush(name)
    if cmd == "learn":
        learn(brush)
    elif cmd == "stats":
        r = load_rules(brush)
        per = Counter(k.split("|")[0] for k in r["rules"])
        print("anchors:", r["anchors"])
        for c, n in per.most_common():
            print("  %s (%s): %d keys" % (c, r["codes"].get(c), n))
    else:
        print(__doc__)
        sys.exit(2)


if __name__ == "__main__":
    main()
