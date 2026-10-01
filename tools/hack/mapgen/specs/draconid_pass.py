#!/usr/bin/env python3
"""
Generates draconid_pass.json: the short mountain path from Draconid Village
(north, brown Fallarbor highland) over a stream and bridge into a green valley
that opens east onto Route 101's west edge, where Prof. Birch is attacked.

  python3 tools/hack/mapgen/specs/draconid_pass.py

Connections: village exit (village x 18..21) = pass x 10..13 (offset -8);
pass east exit rows 26..27 = Route 101 rows 4..5 (offset 22).

Seams: the game draws the cells across a connection with the current map's tilesets,
so only primary (General) metatiles may be drawable across a seam with a different
secondary tileset (see check_seams.py). The offset keeps the Fallarbor highland
(rows 0..13) out of Route 101's view, and Route 101's west strip is all General.
"""

import json
import os

W, H = 28, 36
g = [["." for _ in range(W)] for _ in range(H)]


def fill(ch, x0, y0, x1, y1):
    for y in range(max(y0, 0), min(y1, H - 1) + 1):
        for x in range(max(x0, 0), min(x1, W - 1) + 1):
            g[y][x] = ch


def trees(ch, x0, y0, x1, y1):
    """Whole 2x2 trees on the even lattice ('T' Fallarbor trees, 'Z' General trees)."""
    fill(ch, x0 - x0 % 2, y0 - y0 % 2, x1 + (1 - x1 % 2), y1 + (1 - y1 % 2))


# --- brown highland (y 0..13) -------------------------------------------------
trees("T", 0, 0, 3, 13)
trees("T", W - 4, 0, W - 1, 13)
trees("T", 4, 0, 9, 1)
trees("T", 14, 0, 23, 1)
trees("T", 4, 4, 7, 7)          # groves on the highland
trees("T", 18, 6, 21, 9)
trees("T", 4, 10, 5, 13)
trees("T", 22, 2, 23, 3)
fill("=", 11, 0, 12, 4)         # path down from the village
fill("=", 11, 4, 15, 5)
fill("=", 14, 5, 15, 10)
fill("=", 11, 10, 15, 11)
fill("=", 11, 11, 12, 13)
# --- stream with the bridge (y 14..17) ----------------------------------------
fill("~", 0, 14, W - 1, 17)
# --- green valley (y 18..35) ----------------------------------------------------
trees("Z", 0, 18, 3, H - 1)
trees("Z", W - 4, 18, W - 1, 25)
trees("Z", W - 4, 28, W - 1, H - 1)
trees("Z", 0, 34, W - 1, H - 1)
fill(",", 4, 18, W - 5, 33)
fill(",", W - 4, 26, W - 1, 27)  # east exit to Route 101
fill('"', 4, 19, 9, 23)          # tall grass
fill('"', 15, 29, 21, 32)
fill('"', 5, 28, 9, 31)
trees("Z", 16, 20, 19, 23)       # copse in the valley
fill(":", 11, 18, 12, 26)        # worn path
fill(":", 11, 26, W - 5, 27)  # the worn path ends at the trees; plain grass to Route 101 (caps over the trees below)

spec = {
    "name": "DraconidPass",
    "map_id": "MAP_DRACONID_PASS",
    "layout_id": "LAYOUT_DRACONID_PASS",
    "brush": "general_fallarbor",
    "grid": ["".join(r) for r in g],
    "variety": {"ground": 0.06, "grass": 0.05},
    "stamps": [],
    "blocks": [
        # wooden bridge (Route 114 design): cap row on the north bank, then the deck
        {"at": [10, 14], "block": "2C0:0:3"}, {"at": [11, 14], "block": "28B:0:3"},
        {"at": [12, 14], "block": "28B:0:3"}, {"at": [13, 14], "block": "2C1:0:3"},
    ] + [{"at": [x, y], "block": b} for y in range(15, 18)
         for x, b in ((10, "2C8:0:3"), (11, "293:0:3"), (12, "293:0:3"), (13, "2C9:0:3"))] + [
        {"at": [9, 3], "block": "2AF:1:0"},
        {"at": [17, 12], "block": "2BF:1:0"},
        {"at": [21, 11], "block": "2AF:1:0"},
        {"at": [8, 9], "block": "2BF:1:0"},
        # flowers in the valley
        {"at": [13, 28], "block": "004:0:3"}, {"at": [14, 29], "block": "004:0:3"},
        {"at": [22, 24], "block": "004:0:3"}, {"at": [21, 25], "block": "004:0:3"},
        # sign at the valley fork
        {"at": [14, 25], "block": "003:1:0"},
    ],
    "border": {"blocks": ["1D4:0:0", "1D5:0:0", "1DC:0:0", "1DD:0:0"]},
    "header": {
        "music": "MUS_ROUTE101",
        "region_map_section": "MAPSEC_DRACONID_PASS",
        "weather": "WEATHER_SUNNY",
        "map_type": "MAP_TYPE_ROUTE",
        "show_map_name": True,
    },
    "group": "gMapGroup_TownsAndRoutes",
    "connections": [
        {"map": "MAP_DRACONID_VILLAGE", "direction": "up", "offset": -8},
        {"map": "MAP_ROUTE101", "direction": "right", "offset": 22},
    ],
    "events": {
        "object_events": [{"local_id": "LOCALID_DRACONID_PASS_ASTER", "graphics_id": "OBJ_EVENT_GFX_ASTER",
                           "x": 13, "y": 19, "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_UP",
                           "movement_range_x": 0, "movement_range_y": 0, "trainer_type": "TRAINER_TYPE_NONE",
                           "trainer_sight_or_berry_tree_id": "0", "script": "DraconidPass_EventScript_Aster",
                           "flag": "FLAG_HIDE_DRACONID_PASS_ASTER"}],
        "warp_events": [],
        "coord_events": [{"type": "trigger", "x": x, "y": 18, "elevation": 3, "var": "VAR_DRACONID_STATE",
                          "var_value": "DRACONID_STATE_READY_TO_LEAVE", "script": "DraconidPass_EventScript_AsterBattle"}
                         for x in (10, 11, 12, 13)],
        "bg_events": [{"type": "sign", "x": 14, "y": 25, "elevation": 0, "player_facing_dir": "BG_EVENT_PLAYER_FACING_ANY",
                       "script": "DraconidPass_EventScript_Sign"}],
    },
}

out = os.path.join(os.path.dirname(__file__), "draconid_pass.json")
with open(out, "w") as f:
    json.dump(spec, f, indent=2)
    f.write("\n")
print("wrote", out)
