#!/usr/bin/env python3
"""
Generates the spec of DraconidVillage_Shrine_Depths (Act 7 extension, D-202): the chamber behind the shrine's
carved wall where REGIDRAGO sleeps. A small Regi-style room (the size and layout of the Regi chambers in
IslandCave / DesertRuins / AncientTomb: a boulder in each corner, the legend in the middle, the way out at the
bottom) put together from the shrine's own purple rock (a copy of the Sealed Chamber), so the two rooms match:
the shrine's top wall with its carved alcove, its side walls and its bottom row with the exit.

  python3 tools/hack/mapgen/specs/draconid_shrine_depths.py
  python3 tools/hack/mapgen/mapbuild.py tools/hack/mapgen/specs/draconid_shrine_depths.json --write
"""

import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import pokemap  # noqa: E402

proj = pokemap.Project()
shrine = proj.layout(proj.map_json("DraconidVillage_Shrine")["layout"])

# new column -> shrine column: the shrine's left and right walls, its carved alcove (shrine x 8-12) in the middle,
# two floor columns on each side of it
COLS = [0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 15, 16, 17, 18, 19, 20]
# new row -> shrine row: the top wall (0-5), plain floor rows (9), the bottom rows with the exit (18-22)
ROWS = [0, 1, 2, 3, 4, 5, 9, 9, 9, 9, 18, 19, 20, 21, 22]
FLOOR = "201:0:3"
BOULDER = "2ED:1:0"  # the purple rock pile of the Seafloor Cavern


def block_str(v):
    m, c, e = pokemap.unpack_block(v)
    return "%03X:%d:%d" % (m, c, e)


grid = []
for r in ROWS:
    grid.append([block_str(shrine.block(c, r)) for c in COLS])
# the shrine's row 18 has its pillars' feet: plain floor here
for x in range(4, 13):
    grid[10][x] = FLOOR
# a boulder in each corner of the floor, like the Regi chambers
for x, y in ((5, 6), (11, 6), (4, 9), (12, 9)):
    grid[y][x] = BOULDER

W, H = len(COLS), len(ROWS)
EXIT_X, EXIT_Y = 8, 11  # the shrine's exit tile (207) under the carved alcove

spec = {
    "name": "DraconidVillage_Shrine_Depths",
    "blockgrid": [" ".join(row) for row in grid],
    "tilesets": [shrine.primary_symbol, shrine.secondary_symbol],
    "border": {"from": "DraconidVillage_Shrine"},
    "header": {
        "music": "MUS_SEALED_CHAMBER",
        "region_map_section": "MAPSEC_DRACONID_VILLAGE",
        "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND",
        "allow_cycling": False,
        "allow_escaping": False,
        "allow_running": False,
        "show_map_name": False,
    },
    "group": "gMapGroup_IndoorDraconid",
    "events": {
        "object_events": [
            {
                "local_id": "LOCALID_SHRINE_DEPTHS_REGIDRAGO",
                "graphics_id": "OBJ_EVENT_GFX_SPECIES(REGIDRAGO)",
                "x": 8, "y": 7, "elevation": 3,
                "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
                "movement_range_x": 0, "movement_range_y": 0,
                "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
                "script": "DraconidVillage_Shrine_Depths_EventScript_Regidrago",
                "flag": "FLAG_TEMP_11",
            },
        ],
        "warp_events": [
            {"x": EXIT_X, "y": EXIT_Y, "elevation": 3, "dest_map": "MAP_DRACONID_VILLAGE_SHRINE", "dest_warp_id": "1"},
        ],
        "coord_events": [],
        "bg_events": [
            {"type": "sign", "x": x, "y": 4, "elevation": 0, "player_facing_dir": "BG_EVENT_PLAYER_FACING_ANY",
             "script": "DraconidVillage_Shrine_Depths_EventScript_Carving"} for x in (7, 8, 9)
        ],
    },
}

out = os.path.join(HERE, "draconid_shrine_depths.json")
with open(out, "w") as f:
    json.dump(spec, f, indent=2)
    f.write("\n")
print("wrote", out, "(%dx%d)" % (W, H))
