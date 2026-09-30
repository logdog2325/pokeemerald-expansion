#!/usr/bin/env python3
"""
render.py - render a PNG preview of a map, layout, or tileset.

Examples:
  python3 tools/hack/mapgen/render.py map LittlerootTown -o /tmp/littleroot.png
  python3 tools/hack/mapgen/render.py map DraconidVillage --grid --collision -o out.png
  python3 tools/hack/mapgen/render.py layout LAYOUT_ROUTE101 -o out.png
  python3 tools/hack/mapgen/render.py sheet gTileset_General gTileset_Fallarbor -o sheet.png

Map previews draw metatiles, object events (their real first sprite frame),
warps (purple), coord events (orange), BG events (cyan) and optionally a
collision overlay (red = impassable) and a 1-tile grid with coordinates.
"""

import argparse
import os
import sys

from PIL import Image, ImageDraw

sys.path.insert(0, os.path.dirname(__file__))
import pokemap  # noqa: E402


def render_layout(proj, layout, scale=1, border=0):
    pair = proj.pair_for_layout(layout)
    W, H = layout.width + 2 * border, layout.height + 2 * border
    img = Image.new("RGBA", (W * 16, H * 16), (0, 0, 0, 255))
    for y in range(H):
        for x in range(W):
            mx, my = x - border, y - border
            if 0 <= mx < layout.width and 0 <= my < layout.height:
                mid = layout.metatile_at(mx, my)
            else:
                bw, bh = layout.border_w, layout.border_h
                mid = layout.border[(my % bh) * bw + (mx % bw)] & pokemap.MAPGRID_METATILE_ID_MASK
            tile = pair.render_metatile(mid)
            if not (0 <= mx < layout.width and 0 <= my < layout.height):
                tile = Image.blend(tile, Image.new("RGBA", (16, 16), (0, 0, 0, 255)), 0.45)
            img.paste(tile, (x * 16, y * 16))
    return img


def overlay_collision(img, layout, border=0):
    ov = Image.new("RGBA", img.size, (0, 0, 0, 0))
    d = ImageDraw.Draw(ov)
    for y in range(layout.height):
        for x in range(layout.width):
            _, col, elev = pokemap.unpack_block(layout.block(x, y))
            px, py = (x + border) * 16, (y + border) * 16
            if col:
                d.rectangle([px, py, px + 15, py + 15], fill=(255, 0, 0, 90))
            if elev not in (0, 3):
                d.text((px + 5, py + 3), "%X" % elev, fill=(255, 255, 255, 255))
    img.alpha_composite(ov)


def overlay_events(img, mapj, border=0, sprites=True):
    d = ImageDraw.Draw(img)
    og = pokemap.object_gfx()
    for w in mapj.get("warp_events", []):
        px, py = (w["x"] + border) * 16, (w["y"] + border) * 16
        d.rectangle([px, py, px + 15, py + 15], outline=(200, 0, 255, 255), width=2)
    for c in mapj.get("coord_events", []):
        px, py = (c["x"] + border) * 16, (c["y"] + border) * 16
        d.rectangle([px + 2, py + 2, px + 13, py + 13], outline=(255, 150, 0, 255), width=1)
    for b in mapj.get("bg_events", []):
        px, py = (b["x"] + border) * 16, (b["y"] + border) * 16
        d.rectangle([px + 4, py + 4, px + 11, py + 11], outline=(0, 220, 255, 255), width=1)
    for o in mapj.get("object_events", []):
        x, y = o.get("x", 0), o.get("y", 0)
        px, py = (x + border) * 16, (y + border) * 16
        fr = og.frame(o.get("graphics_id", "")) if sprites else None
        if fr is not None:
            # sprites are anchored bottom-centre on their tile
            ox = px + 8 - fr.width // 2
            oy = py + 16 - fr.height
            img.alpha_composite(fr, (max(ox, 0), max(oy, 0)))
        else:
            d.ellipse([px + 3, py + 3, px + 12, py + 12], outline=(0, 255, 0, 255), width=2)


def overlay_grid(img, w, h, border=0):
    d = ImageDraw.Draw(img)
    for x in range(w + 1):
        d.line([((x + border) * 16, border * 16), ((x + border) * 16, (h + border) * 16)], fill=(255, 255, 255, 50))
    for y in range(h + 1):
        d.line([(border * 16, (y + border) * 16), ((w + border) * 16, (y + border) * 16)], fill=(255, 255, 255, 50))
    for x in range(0, w, 5):
        d.text(((x + border) * 16 + 1, border * 16 + 1), str(x), fill=(255, 255, 0, 255))
    for y in range(0, h, 5):
        d.text((border * 16 + 1, (y + border) * 16 + 1), str(y), fill=(255, 255, 0, 255))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("kind", choices=["map", "layout", "sheet"])
    ap.add_argument("name", nargs="+")
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("--scale", type=int, default=2)
    ap.add_argument("--border", type=int, default=0, help="draw N tiles of border blocks around the map")
    ap.add_argument("--grid", action="store_true")
    ap.add_argument("--collision", action="store_true")
    ap.add_argument("--no-events", action="store_true")
    ap.add_argument("--secondary-only", action="store_true")
    args = ap.parse_args()

    proj = pokemap.Project()
    if args.kind == "sheet":
        prim = args.name[0]
        sec = args.name[1] if len(args.name) > 1 else "gTileset_Petalburg"
        img = proj.tileset_pair(prim, sec).render_sheet(secondary_only=args.secondary_only, scale=args.scale)
        img.save(args.out)
        return

    if args.kind == "map":
        mapj = proj.map_json(args.name[0])
        layout = proj.layout(mapj["layout"])
    else:
        mapj = None
        layout = proj.layout(args.name[0])
    img = render_layout(proj, layout, border=args.border)
    if args.collision:
        overlay_collision(img, layout, args.border)
    if mapj and not args.no_events:
        overlay_events(img, mapj, args.border)
    if args.grid:
        overlay_grid(img, layout.width, layout.height, args.border)
    if args.scale != 1:
        img = img.resize((img.width * args.scale, img.height * args.scale), Image.NEAREST)
    img.save(args.out)
    print("wrote", args.out, img.size)


if __name__ == "__main__":
    main()
