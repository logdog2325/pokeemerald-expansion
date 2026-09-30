#!/usr/bin/env python3
"""
Generates draconid_village.json (the readable spec mapbuild.py consumes).
The ASCII grid in the JSON can be hand-edited afterwards; this script just
records how the layout was drafted.

  python3 tools/hack/mapgen/specs/draconid_village.py

Tree blocks are snapped to the 2x2 tree lattice (even x/y, even size) so the
auto-tiler can draw whole trees – see docs/hack_tools.md.
"""

import json
import os

def obj(gfx, x, y, script, flag="0", local_id=None, movement="MOVEMENT_TYPE_FACE_DOWN", rx=0, ry=0):
    o = {"local_id": local_id} if local_id else {}
    o.update({"graphics_id": gfx, "x": x, "y": y, "elevation": 3, "movement_type": movement,
              "movement_range_x": rx, "movement_range_y": ry, "trainer_type": "TRAINER_TYPE_NONE",
              "trainer_sight_or_berry_tree_id": "0", "script": script, "flag": flag})
    return o


def warp(x, y, dest_map, dest_warp):
    return {"x": x, "y": y, "elevation": 0, "dest_map": dest_map, "dest_warp_id": str(dest_warp)}


def sign(x, y, script):
    return {"type": "sign", "x": x, "y": y, "elevation": 0, "player_facing_dir": "BG_EVENT_PLAYER_FACING_ANY",
            "script": script}


W, H = 40, 30
g = [["." for _ in range(W)] for _ in range(H)]


def fill(ch, x0, y0, x1, y1):
    for y in range(max(y0, 0), min(y1, H - 1) + 1):
        for x in range(max(x0, 0), min(x1, W - 1) + 1):
            g[y][x] = ch


def trees(x0, y0, x1, y1):
    """Whole 2x2 trees: snap the box outwards onto the even lattice."""
    fill("T", x0 - x0 % 2, y0 - y0 % 2, x1 + (1 - x1 % 2), y1 + (1 - y1 % 2))


# plateau forest, a lip of plateau ground, then the north cliff band
trees(0, 0, W - 1, 1)
fill(".", 4, 2, 35, 2)
fill("#", 4, 3, 35, 5)
# river on the plateau falling down the cliff into a pond
fill("~", 30, 0, 33, 2)
fill("|", 30, 3, 33, 5)
fill("~", 29, 6, 34, 8)
# forest edges and groves
trees(0, 0, 3, H - 1)
trees(W - 4, 0, W - 1, H - 1)
trees(4, 20, 5, 23)
trees(34, 10, 35, 13)
trees(0, 26, W - 1, H - 1)
fill(".", 18, 26, 21, H - 1)      # south exit to the mountain path
trees(30, 22, 33, 25)
trees(24, 22, 25, 25)
trees(12, 6, 13, 7)
# roads
fill("=", 19, 10, 20, H - 1)      # main road
fill("=", 8, 15, 18, 16)          # player's house
fill("=", 21, 12, 24, 13)         # elder's house
fill("=", 21, 18, 29, 19)         # east house
fill("=", 12, 24, 18, 25)         # south-west house

spec = {
    "name": "DraconidVillage",
    "map_id": "MAP_DRACONID_VILLAGE",
    "layout_id": "LAYOUT_DRACONID_VILLAGE",
    "brush": "general_fallarbor",
    "grid": ["".join(r) for r in g],
    "variety": {"ground": 0.06},
    "stamps": [
        # player's house (Cozmo's house design, Fallarbor) - door at (8, 14)
        {"from": "FallarborTown", "rect": [5, 13, 4, 5], "at": [7, 10], "mask": ["..xx", "xxxx", "xxxx", "xxxx", "xxxx"]},
        # elder's house (red roof, Route 114 Lanette's design) - door at (24, 11)
        {"from": "Route114", "rect": [25, 33, 5, 4], "at": [22, 8]},
        # east villager house (Glass Workshop design) - door at (29, 17)
        {"from": "Route113", "rect": [32, 2, 4, 4], "at": [28, 14]},
        # south-west villager house (Fallarbor house) - door at (12, 23)
        {"from": "FallarborTown", "rect": [5, 13, 4, 5], "at": [11, 19], "mask": ["..xx", "xxxx", "xxxx", "xxxx", "xxxx"]},
        # meteor crater in front of the shrine
        {"from": "FallarborTown", "rect": [1, 14, 3, 3], "at": [18, 7]},
        # garden plots
        {"from": "Route113", "rect": [3, 7, 4, 3], "at": [6, 18]},
        {"from": "Route113", "rect": [8, 7, 4, 3], "at": [32, 15]},
    ],
    "blocks": [
        # Rayquaza shrine: cave mouth carved into the cliff (METATILE_Fallarbor_RedCaveEntrance_*)
        {"at": [19, 4], "block": "347:1:0"},
        {"at": [19, 5], "block": "34F:0:3"},
        # meteorite boulders around the crater
        {"at": [17, 6], "block": "2AF:1:0"},
        {"at": [21, 6], "block": "2BF:1:0"},
        {"at": [16, 9], "block": "2BF:1:0"},
        {"at": [27, 21], "block": "2AF:1:0"},
        # signs
        {"at": [18, 11], "block": "003:1:0"},
        {"at": [6, 14], "block": "003:1:0"},
    ],
    "border": {"blocks": ["26B:0:0", "26C:0:0", "273:0:0", "274:0:0"]},
    "header": {
        "music": "MUS_FALLARBOR",
        "region_map_section": "MAPSEC_DRACONID_VILLAGE",
        "weather": "WEATHER_SUNNY",
        "map_type": "MAP_TYPE_TOWN",
        "show_map_name": True,
    },
    "group": "gMapGroup_TownsAndRoutes",
    "events": {
        "object_events": [
            obj("OBJ_EVENT_GFX_DRACONID_MAN", 16, 8, "DraconidVillage_EventScript_Apprentice", movement="MOVEMENT_TYPE_FACE_RIGHT"),
            obj("OBJ_EVENT_GFX_DRACONID_OLD_WOMAN", 22, 6, "DraconidVillage_EventScript_OldWoman", movement="MOVEMENT_TYPE_FACE_LEFT"),
            obj("OBJ_EVENT_GFX_DRACONID_WOMAN", 30, 10, "DraconidVillage_EventScript_PondWoman", movement="MOVEMENT_TYPE_FACE_UP"),
            obj("OBJ_EVENT_GFX_DRACONID_BOY", 10, 18, "DraconidVillage_EventScript_Boy", movement="MOVEMENT_TYPE_WANDER_AROUND", rx=2, ry=2),
            obj("OBJ_EVENT_GFX_DRACONID_GUARD", 22, 25, "DraconidVillage_EventScript_Gatekeeper",
                movement="MOVEMENT_TYPE_FACE_LEFT", local_id="LOCALID_DRACONID_GATEKEEPER"),
            obj("OBJ_EVENT_GFX_MOM", 19, 8, "0x0", "FLAG_HIDE_DRACONID_VILLAGE_MOM",
                local_id="LOCALID_DRACONID_VILLAGE_MOM", movement="MOVEMENT_TYPE_FACE_UP"),
        ],
        "warp_events": [
            warp(8, 14, "MAP_DRACONID_VILLAGE_PLAYERS_HOUSE_1F", 0),
            warp(24, 11, "MAP_DRACONID_VILLAGE_ELDERS_HOUSE", 0),
            warp(29, 17, "MAP_DRACONID_VILLAGE_HOUSE1", 0),
            warp(12, 23, "MAP_DRACONID_VILLAGE_HOUSE2", 0),
            warp(19, 5, "MAP_DRACONID_VILLAGE_SHRINE", 0),
        ],
        # VAR_TEMP_1 is 0 until the player may leave (set on transition / after the Running Shoes)
        "coord_events": [{"type": "trigger", "x": x, "y": 27, "elevation": 3, "var": "VAR_TEMP_1", "var_value": "0",
                          "script": "DraconidVillage_EventScript_GatekeeperStop"} for x in (18, 19, 20, 21)],
        "bg_events": [
            sign(18, 11, "DraconidVillage_EventScript_VillageSign"),
            sign(6, 14, "DraconidVillage_EventScript_PlayersHouseSign"),
        ],
    },
}

out = os.path.join(os.path.dirname(__file__), "draconid_village.json")
with open(out, "w") as f:
    json.dump(spec, f, indent=2)
    f.write("\n")
print("wrote", out)
