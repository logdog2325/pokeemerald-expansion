#!/usr/bin/env python3
"""
Generates the interior map specs of Draconid Village (copied or shared vanilla
layouts + events). Writes one JSON spec per map next to this file.

  python3 tools/hack/mapgen/specs/draconid_interiors.py
  for f in tools/hack/mapgen/specs/draconid_village_*.json; do
      python3 tools/hack/mapgen/mapbuild.py $f --write; done

Village warp ids: 0 player's house, 1 elder's house, 2 east house (House1),
3 south-west house (House2), 4 Rayquaza shrine.
"""

import json
import os

HERE = os.path.dirname(__file__)
GROUP = "gMapGroup_IndoorDraconid"


def obj(gfx, x, y, script, flag="0", local_id=None, movement="MOVEMENT_TYPE_FACE_DOWN", rx=0, ry=0, elevation=3):
    o = {}
    if local_id:
        o["local_id"] = local_id
    o.update({
        "graphics_id": gfx, "x": x, "y": y, "elevation": elevation, "movement_type": movement,
        "movement_range_x": rx, "movement_range_y": ry, "trainer_type": "TRAINER_TYPE_NONE",
        "trainer_sight_or_berry_tree_id": "0", "script": script, "flag": flag,
    })
    return o


def warp(x, y, dest_map, dest_warp, elevation=0):
    return {"x": x, "y": y, "elevation": elevation, "dest_map": dest_map, "dest_warp_id": str(dest_warp)}


def sign(x, y, script, facing="BG_EVENT_PLAYER_FACING_ANY"):
    return {"type": "sign", "x": x, "y": y, "elevation": 0, "player_facing_dir": facing, "script": script}


INDOOR = {
    "music": "MUS_FALLARBOR", "region_map_section": "MAPSEC_DRACONID_VILLAGE", "weather": "WEATHER_NONE",
    "map_type": "MAP_TYPE_INDOOR", "allow_cycling": False, "allow_escaping": False, "allow_running": False,
    "show_map_name": False,
}

specs = []

# Player's house (copy of Brendan's house so edits never touch the rival's house)
specs.append({
    "name": "DraconidVillage_PlayersHouse_1F",
    "copy_layout": "LAYOUT_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F",
    "header": INDOOR, "group": GROUP,
    "events": {
        "object_events": [
            obj("OBJ_EVENT_GFX_DRACONID_ELDER", 2, 6, "DraconidVillage_PlayersHouse_1F_EventScript_Elder",
                "FLAG_HIDE_DRACONID_HOUSE_ELDER", local_id="LOCALID_DRACONID_HOUSE_ELDER",
                movement="MOVEMENT_TYPE_FACE_RIGHT"),
        ],
        "warp_events": [
            warp(9, 8, "MAP_DRACONID_VILLAGE", 0),
            warp(8, 8, "MAP_DRACONID_VILLAGE", 0),
            warp(8, 2, "MAP_DRACONID_VILLAGE_PLAYERS_HOUSE_2F", 0),
        ],
        "coord_events": [],
        "bg_events": [
        ],
    },
})

decor = [obj("OBJ_EVENT_GFX_VAR_%X" % i, i // 6, i % 6, "0x0", "FLAG_DECORATION_%d" % (i + 1), elevation=3)
         for i in range(12)]
specs.append({
    "name": "DraconidVillage_PlayersHouse_2F",
    "copy_layout": "LAYOUT_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F",
    "header": INDOOR, "group": GROUP,
    "events": {
        "object_events": decor + [
            obj("OBJ_EVENT_GFX_ASTER", 7, 1, "0x0", "FLAG_HIDE_DRACONID_HOUSE_2F_ASTER",
                local_id="LOCALID_DRACONID_HOUSE_2F_ASTER"),
        ],
        "warp_events": [warp(7, 1, "MAP_DRACONID_VILLAGE_PLAYERS_HOUSE_1F", 2)],
        "coord_events": [{"type": "trigger", "x": 7, "y": 2, "elevation": 3, "var": "VAR_DRACONID_STATE",
                          "var_value": "DRACONID_STATE_SET_CLOCK",
                          "script": "DraconidVillage_PlayersHouse_2F_EventScript_StairsBlocked"}],
        "bg_events": [
            sign(0, 1, "DraconidVillage_PlayersHouse_2F_EventScript_PC", "BG_EVENT_PLAYER_FACING_NORTH"),
            sign(1, 1, "PlayersHouse_2F_EventScript_Notebook"),
            sign(5, 1, "DraconidVillage_PlayersHouse_2F_EventScript_WallClock"),
            sign(3, 1, "PlayersHouse_2F_EventScript_GameCube"),
        ],
    },
})

# Elder's house: Fossil Maniac's house with its tunnel doorway walled off; the display
# cases hold clan relics.
specs.append({
    "name": "DraconidVillage_EldersHouse",
    "copy_layout": "LAYOUT_ROUTE114_FOSSIL_MANIACS_HOUSE",
    "blocks": [{"at": [x, 0], "block": "215:1:0"} for x in (3, 4, 5)] +
              [{"at": [x, 1], "block": "21D:1:0"} for x in (3, 4, 5)],
    "header": INDOOR, "group": GROUP,
    "events": {
        "object_events": [
            obj("OBJ_EVENT_GFX_DRACONID_ELDER", 4, 3, "DraconidVillage_EldersHouse_EventScript_Elder",
                "FLAG_HIDE_DRACONID_ELDERS_HOUSE_ELDER", local_id="LOCALID_DRACONID_ELDER"),
            obj("OBJ_EVENT_GFX_ASTER", 2, 3, "DraconidVillage_EldersHouse_EventScript_Aster",
                "FLAG_HIDE_DRACONID_ELDERS_HOUSE_ASTER", local_id="LOCALID_DRACONID_HOUSE_ASTER",
                movement="MOVEMENT_TYPE_FACE_RIGHT"),
            # the three eggs lie in the shrine (round 1, D-230)
        ],
        "warp_events": [
            warp(4, 7, "MAP_DRACONID_VILLAGE", 1),
            warp(5, 7, "MAP_DRACONID_VILLAGE", 1),
        ],
        "coord_events": [],
        "bg_events": [
            sign(5, 3, "DraconidVillage_EldersHouse_EventScript_RelicDisplay", "BG_EVENT_PLAYER_FACING_NORTH"),
            sign(6, 3, "DraconidVillage_EldersHouse_EventScript_RelicDisplay", "BG_EVENT_PLAYER_FACING_NORTH"),
            sign(7, 2, "DraconidVillage_EldersHouse_EventScript_Bookshelf", "BG_EVENT_PLAYER_FACING_NORTH"),
            sign(8, 2, "DraconidVillage_EldersHouse_EventScript_Bookshelf", "BG_EVENT_PLAYER_FACING_NORTH"),
        ],
    },
})

# Rayquaza shrine: the Sealed Chamber's inner room; its inscribed stones become clan lore.
specs.append({
    "name": "DraconidVillage_Shrine",
    "copy_layout": "LAYOUT_SEALED_CHAMBER_INNER_ROOM",
    "header": dict(INDOOR, music="MUS_SEALED_CHAMBER", map_type="MAP_TYPE_UNDERGROUND"),
    "group": GROUP,
    "events": {
        "object_events": [
            # TODO(art): custom Porytiles Rayquaza statue; the still Rayquaza sprite stands in for it
            obj("OBJ_EVENT_GFX_RAYQUAZA_STILL", 10, 6, "DraconidVillage_Shrine_EventScript_Statue",
                local_id="LOCALID_DRACONID_SHRINE_STATUE"),
            obj("OBJ_EVENT_GFX_DRACONID_ELDER", 10, 7, "DraconidVillage_Shrine_EventScript_Elder",
                "FLAG_HIDE_DRACONID_SHRINE_ELDER", local_id="LOCALID_DRACONID_SHRINE_ELDER"),
            obj("OBJ_EVENT_GFX_ASTER", 12, 9, "0x0", "FLAG_HIDE_DRACONID_SHRINE_ASTER",
                local_id="LOCALID_DRACONID_SHRINE_ASTER", movement="MOVEMENT_TYPE_FACE_UP"),
            # the egg ceremony (round 1, D-230): the three eggs at the Elder's feet (Deino, Dreepy, Jangmo-o)
            obj("OBJ_EVENT_GFX_DRACONID_EGG_DEINO", 9, 8, "DraconidVillage_Shrine_EventScript_Egg",
                "FLAG_RECEIVED_DRACONID_EGG", local_id="LOCALID_DRACONID_EGG_1"),
            obj("OBJ_EVENT_GFX_DRACONID_EGG_DREEPY", 10, 8, "DraconidVillage_Shrine_EventScript_Egg",
                "FLAG_RECEIVED_DRACONID_EGG", local_id="LOCALID_DRACONID_EGG_2"),
            obj("OBJ_EVENT_GFX_DRACONID_EGG_JANGMO_O", 11, 8, "DraconidVillage_Shrine_EventScript_Egg",
                "FLAG_RECEIVED_DRACONID_EGG", local_id="LOCALID_DRACONID_EGG_3"),
        ],
        "warp_events": [warp(10, 19, "MAP_DRACONID_VILLAGE", 4, elevation=3)],
        "coord_events": [],
        "bg_events": [
            sign(9, 4, "DraconidVillage_Shrine_EventScript_BackWall"),
            sign(10, 4, "DraconidVillage_Shrine_EventScript_BackWall"),
            sign(11, 4, "DraconidVillage_Shrine_EventScript_BackWall"),
            sign(6, 8, "DraconidVillage_Shrine_EventScript_Lore1"),
            sign(14, 8, "DraconidVillage_Shrine_EventScript_Lore2"),
            sign(4, 13, "DraconidVillage_Shrine_EventScript_Lore3"),
            sign(16, 13, "DraconidVillage_Shrine_EventScript_Lore4"),
            sign(6, 18, "DraconidVillage_Shrine_EventScript_Lore5"),
            sign(14, 18, "DraconidVillage_Shrine_EventScript_Lore6"),
        ],
    },
})

# Villager houses share vanilla layouts (no edits needed)
specs.append({
    "name": "DraconidVillage_House1",
    "use_layout": "LAYOUT_HOUSE2",
    "header": INDOOR, "group": GROUP,
    "events": {
        "object_events": [
            obj("OBJ_EVENT_GFX_DRACONID_OLD_WOMAN", 4, 4, "DraconidVillage_House1_EventScript_Weaver"),
            obj("OBJ_EVENT_GFX_LITTLE_GIRL", 6, 5, "DraconidVillage_House1_EventScript_Girl",
                movement="MOVEMENT_TYPE_WANDER_AROUND", rx=1, ry=1),
        ],
        "warp_events": [warp(3, 7, "MAP_DRACONID_VILLAGE", 2), warp(4, 7, "MAP_DRACONID_VILLAGE", 2)],
        "coord_events": [], "bg_events": [],
    },
})
specs.append({
    "name": "DraconidVillage_House2",
    "use_layout": "LAYOUT_HOUSE1",
    "header": INDOOR, "group": GROUP,
    "events": {
        "object_events": [
            obj("OBJ_EVENT_GFX_DRACONID_MAN", 6, 4, "DraconidVillage_House2_EventScript_Hunter"),
            obj("OBJ_EVENT_GFX_DRACONID_WOMAN", 5, 6, "DraconidVillage_House2_EventScript_Wife",
                movement="MOVEMENT_TYPE_FACE_UP"),
        ],
        "warp_events": [warp(3, 8, "MAP_DRACONID_VILLAGE", 3), warp(4, 8, "MAP_DRACONID_VILLAGE", 3)],
        "coord_events": [], "bg_events": [],
    },
})

for s in specs:
    path = os.path.join(HERE, "draconid_village_%s.json" % s["name"].split("_", 1)[1].lower())
    with open(path, "w") as f:
        json.dump(s, f, indent=2)
        f.write("\n")
    print("wrote", os.path.relpath(path))
