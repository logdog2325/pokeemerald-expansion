#!/usr/bin/env python3
"""
build_player.py - build a player outfit's overworld sheets from a base set.

The Draconid player outfits are derived from the FRLG Red/Leaf sheets (never from
Brendan/May): each frame keeps the base body and pose, gets a new palette (same index
roles), and has its headwear replaced by a head template drawn for this outfit.

  python3 tools/hack/art/player/build_player.py tools/hack/art/player/draconid_m.json
  python3 tools/hack/art/player/build_player.py SPEC --preview out.png   # enlarged review sheet

Spec (JSON):
  "base_dir": "graphics/object_events/pics/people/red"
  "out_dir":  "graphics/object_events/pics/people/draconid_m"
  "palette_out": "graphics/object_events/palettes/draconid_m.pal"
  "palette": [[r, g, b] x16]           index 0 = transparent key
  "roles": {"K": 15, "H": 6, ...}       template characters -> palette index ('.' = keep, '_' = clear)
  "cap": [8, 11, 12]                    indices of the old headwear; its top-left pixel anchors a head
  "clear": [8, 9, 10, 11, 12, 15, 1, 4] indices cleared in the head rows before the template is drawn
  "heads": {"down": {"anchor": [-4, -1], "rows": ["...", ...], "clear_above": 0}, "up": ..., "left": ...}
            anchor = template top-left relative to (cap left x, cap top y); clear_above = extra rows
            above the template that are cleared too
  "sheets": [{"src": "red_normal.png", "out": "walking.png", "w": 16, "h": 32,
              "pick": [0, 1, ...],                 source frames (default: all)
              "heads": ["down", "up", "left", ...], per output frame (null = no head swap)
              "fix": {"3": {"dx": 0, "dy": 1}}     per-frame anchor nudges (output frame index)
              "clear_above": 0                     overrides the heads' clear_above (keep fishing rods)
              "overlays": ["scarf_down", ...],     per output frame, a body overlay (null = none)
              "overlay_fix": {"3": {"dx": 0, "dy": 1}}  per-frame overlay nudges
              "pixels": {"3": ["x,y,ROLE", ...]}}]  per-frame pixel touch-ups after the swap
  "overlays": {"scarf_down": {"anchor": [dx, dy], "under": [...], "rows": [...]}}
            body overlays (the Draconid scarf), anchored on the head template's top-left after the
            swap (so they follow the head's fix nudges); "under" rows only paint transparent pixels
            (behind the body), then "rows" paint over it
  "derived": [...]                      sheets made from built frames (see build_derived); "path"
                                        saves one outside out_dir (e.g. the region map icon)
  "reflection_palette_out": "...pal"    generated water-reflection palette
"""

import argparse
import json
import os
import sys

from PIL import Image, ImageDraw

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "..", ".."))


def load_indexed(path):
    im = Image.open(path)
    if im.mode != "P":
        sys.exit("%s is not an indexed PNG" % path)
    return im


def write_jasc(path, colors):
    with open(path, "w", newline="\r\n") as f:
        f.write("JASC-PAL\n0100\n%d\n" % len(colors))
        for r, g, b in colors:
            f.write("%d %d %d\n" % (r, g, b))


def gba_color(c):
    """Round to the GBA's 15-bit colour so previews match the game."""
    return tuple((v >> 3) << 3 for v in c)


def largest_component(px, fx, fy, w, h, indices):
    """Pixels of the biggest 4-connected blob of the given indices (the headwear, not a rod tip)."""
    seen = set()
    best = []
    for y in range(h):
        for x in range(w):
            if (x, y) in seen or px[fx + x, fy + y] not in indices:
                continue
            blob, stack = [], [(x, y)]
            seen.add((x, y))
            while stack:
                cx, cy = stack.pop()
                blob.append((cx, cy))
                for nx, ny in ((cx + 1, cy), (cx - 1, cy), (cx, cy + 1), (cx, cy - 1)):
                    if 0 <= nx < w and 0 <= ny < h and (nx, ny) not in seen and px[fx + nx, fy + ny] in indices:
                        seen.add((nx, ny))
                        stack.append((nx, ny))
            if len(blob) > len(best):
                best = blob
    return best


def swap_head(px, fx, fy, w, h, head, roles, cap, clear, nudge, clear_above=None):
    """Replace the headwear of one frame (frame origin fx, fy) with a head template.

    Returns the template's top-left (x, y) inside the frame (overlays anchor on it), or None."""
    caps = largest_component(px, fx, fy, w, h, cap)
    if not caps:
        return None
    top = min(y for _, y in caps)
    left = min(x for x, y in caps if y == top)
    ax, ay = head["anchor"]
    ox = left + ax + nudge.get("dx", 0)
    oy = top + ay + nudge.get("dy", 0)
    rows = head["rows"]
    # columns the old headwear spans inside the template rows (plus a 1px outline margin)
    in_rows = [(x, y) for x, y in caps if oy <= y < oy + len(rows)] or [(0, oy)]
    x0 = max(0, min(x for x, _ in in_rows) - 1)
    x1 = min(w - 1, max(x for x, _ in in_rows) + 1) if len(in_rows) > 1 or in_rows[0] != (0, oy) else -1
    # rows above the template too (e.g. hair flying up in run frames), if the head asks for it
    above = head.get("clear_above", 0) if clear_above is None else clear_above
    for y in range(max(0, oy - above), min(h, oy + len(rows))):
        for x in range(x0, x1 + 1):
            if px[fx + x, fy + y] in clear:
                px[fx + x, fy + y] = 0
    for ty, row in enumerate(rows):
        for tx, ch in enumerate(row):
            x, y = ox + tx, oy + ty
            if ch == "." or not (0 <= x < w and 0 <= y < h):
                continue
            px[fx + x, fy + y] = 0 if ch == "_" else roles[ch]
    return ox, oy


def draw_overlay(px, fx, fy, w, h, tpl, roles, origin, nudge):
    """Draw a body overlay (e.g. the Draconid scarf) anchored on the head template's top-left.

    tpl = {"anchor": [dx, dy], "under": [...], "rows": [...]}: "under" rows paint only transparent
    pixels (behind the body), then "rows" paint over everything; '.' keeps, '_' clears."""
    ax, ay = tpl["anchor"]
    ox = origin[0] + ax + nudge.get("dx", 0)
    oy = origin[1] + ay + nudge.get("dy", 0)
    for layer, behind in (("under", True), ("rows", False)):
        for ty, row in enumerate(tpl.get(layer, [])):
            for tx, ch in enumerate(row):
                x, y = ox + tx, oy + ty
                if ch == "." or not (0 <= x < w and 0 <= y < h):
                    continue
                if behind and px[fx + x, fy + y]:
                    continue
                px[fx + x, fy + y] = 0 if ch == "_" else roles[ch]


def build(spec, preview=None):
    base_dir = os.path.join(ROOT, spec["base_dir"])
    out_dir = os.path.join(ROOT, spec["out_dir"])
    os.makedirs(out_dir, exist_ok=True)
    palette = [gba_color(c) for c in spec["palette"]]
    flat = [v for c in palette for v in c]
    roles = spec["roles"]
    outputs = []
    for sh in spec["sheets"]:
        src = load_indexed(os.path.join(base_dir, sh["src"]))
        w, h = sh.get("w", 16), sh.get("h", 32)
        n = src.width // w
        pick = sh.get("pick", list(range(n)))
        out = Image.new("P", (w * len(pick), h), 0)
        out.putpalette(flat + [0] * (768 - len(flat)))
        for i, f in enumerate(pick):
            out.paste(src.crop((f * w, 0, f * w + w, h)), (i * w, 0))
        px = out.load()
        heads = sh.get("heads", [])
        overlays = sh.get("overlays", [])
        for i in range(len(pick)):
            name = heads[i] if i < len(heads) else None
            origin = None
            if name:
                origin = swap_head(px, i * w, 0, w, h, spec["heads"][name], roles, set(spec["cap"]),
                                   set(spec["clear"]), sh.get("fix", {}).get(str(i), {}), sh.get("clear_above"))
                if not origin:
                    print("warning: %s frame %d: no headwear found" % (sh["out"], i))
            ov = overlays[i] if i < len(overlays) else None
            if ov and origin:
                draw_overlay(px, i * w, 0, w, h, spec["overlays"][ov], roles, origin,
                             sh.get("overlay_fix", {}).get(str(i), {}))
            for p in sh.get("pixels", {}).get(str(i), []):
                x, y, ch = p.split(",")
                px[i * w + int(x), int(y)] = 0 if ch == "_" else roles[ch]
        path = os.path.join(out_dir, sh["out"])
        out.save(path)
        outputs.append((sh["out"], out, w, h))
        print("wrote", os.path.relpath(path, ROOT))
    built = {name: (im, w, h) for name, im, w, h in outputs}
    for dv in spec.get("derived", []):
        out = build_derived(dv, built, palette, flat, roles, spec)
        path = os.path.join(ROOT, dv["path"]) if "path" in dv else os.path.join(out_dir, dv["out"])
        out.save(path)
        built[dv["out"]] = (out, dv.get("w", 32), dv.get("h", 32))
        outputs.append((dv["out"], out, dv.get("w", 32), dv.get("h", 32)))
        print("wrote", os.path.relpath(path, ROOT))
    if spec.get("palette_out"):
        write_jasc(os.path.join(ROOT, spec["palette_out"]), palette)
        print("wrote", spec["palette_out"])
    if spec.get("reflection_palette_out"):
        # water reflections: washed out and slightly blue, like brendan_reflection.pal
        refl = [gba_color(tuple(min(255, int(0.58 * v + b)) for v, b in zip(c, (106, 112, 116)))) for c in palette]
        refl[0] = palette[0]
        write_jasc(os.path.join(ROOT, spec["reflection_palette_out"]), refl)
        print("wrote", spec["reflection_palette_out"])
    if preview:
        make_preview(outputs, palette, preview)


def build_derived(dv, built, palette, flat, roles, spec):
    """A sheet made from frames already built: place / shift / shear / flip / recolour / overlay.

    "derived": [{"out": "acro_bike.png", "w": 32, "h": 32, "frames": [
        {"from": "bike.png", "frame": 0, "place": [0, 0], "shift": [0, -2], "shear": 0.2,
         "flip": false, "lum": [[48, 8], [96, 7], [160, 6], [256, 5]],
         "overlay": {"at": [x, y], "rows": ["..RR", ...]}}, ...]}]
    lum maps every opaque pixel by the brightness of its colour (first threshold above it wins).
    """
    w, h = dv.get("w", 32), dv.get("h", 32)
    out = Image.new("P", (w * len(dv["frames"]), h), 0)
    out.putpalette(flat + [0] * (768 - len(flat)))
    opx = out.load()
    for i, fr in enumerate(dv["frames"]):
        src, sw, shh = built[fr["from"]]
        spx = src.load()
        cell = [[0] * w for _ in range(h)]
        px0, py0 = fr.get("place", [(w - sw) // 2, h - shh])
        dx, dy = fr.get("shift", [0, 0])
        for y in range(shh):
            for x in range(sw):
                v = spx[fr["frame"] * sw + x, y]
                if not v:
                    continue
                sx = sw - 1 - x if fr.get("flip") else x
                tx, ty = px0 + sx + dx, py0 + y + dy
                if 0 <= tx < w and 0 <= ty < h:
                    cell[ty][tx] = v
        k = fr.get("shear", 0)
        if k:
            pivot = fr.get("pivot", w // 2)
            sheared = [[0] * w for _ in range(h)]
            for y in range(h):
                for x in range(w):
                    if cell[y][x]:
                        ny = y + int(round(k * (x - pivot)))
                        if 0 <= ny < h:
                            sheared[ny][x] = cell[y][x]
            cell = sheared
        if "lum" in fr:
            for y in range(h):
                for x in range(w):
                    v = cell[y][x]
                    if v:
                        r, g, b = palette[v]
                        lum = 0.3 * r + 0.59 * g + 0.11 * b
                        cell[y][x] = next(idx for thr, idx in fr["lum"] if lum < thr)
        ov = fr.get("overlay")
        if ov:
            ox, oy = ov["at"]
            for ty, row in enumerate(ov["rows"]):
                for tx, ch in enumerate(row):
                    if ch != "." and 0 <= ox + tx < w and 0 <= oy + ty < h:
                        cell[oy + ty][ox + tx] = 0 if ch == "_" else roles[ch]
        for y in range(h):
            for x in range(w):
                opx[i * w + x, y] = cell[y][x]
    return out


def make_preview(outputs, palette, path, zoom=5):
    strips = []
    for name, im, w, h in outputs:
        n = im.width // w
        rgba = im.convert("RGBA")
        strip = Image.new("RGB", (n * (w * zoom + 4), h * zoom + 14), (40, 40, 48))
        d = ImageDraw.Draw(strip)
        d.text((2, 1), name, fill=(255, 255, 0))
        for i in range(n):
            fr = rgba.crop((i * w, 0, i * w + w, h)).resize((w * zoom, h * zoom), Image.NEAREST)
            bg = Image.new("RGBA", fr.size, palette[0] + (255,))
            bg.alpha_composite(fr)
            strip.paste(bg.convert("RGB"), (i * (w * zoom + 4), 14))
            d.text((i * (w * zoom + 4) + w * zoom - 12, 1), str(i), fill=(160, 200, 255))
        strips.append(strip)
    W = max(s.width for s in strips)
    H = sum(s.height + 6 for s in strips)
    sheet = Image.new("RGB", (W, H), (20, 20, 24))
    y = 0
    for s in strips:
        sheet.paste(s, (0, y))
        y += s.height + 6
    sheet.save(path)
    print("preview", path)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("spec")
    ap.add_argument("--preview")
    args = ap.parse_args()
    build(json.load(open(args.spec)), args.preview)


if __name__ == "__main__":
    main()
