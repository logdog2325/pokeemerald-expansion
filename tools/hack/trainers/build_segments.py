#!/usr/bin/env python3
"""
build_segments.py - write tools/hack/trainers/segments.json: every Emerald trainer's story segment,
role and level band. Rules live here; docs/hack_trainers.md explains them.

  python3 tools/hack/trainers/build_segments.py            # write segments.json + print a summary
  python3 tools/hack/trainers/build_segments.py --list S3  # list one segment's trainers

A segment is the stretch of the game between two badges. S1 = before the 1st badge (cap 15) ...
S9 = Victory Road and the League (cap 60), POST = after the Champion (no cap). Caps are read from
src/caps.c (sLevelCapFlagMap), so the ROM and the checks can't disagree. A trainer is put in the
EARLIEST segment in which the player can reach it, so its levels never beat the cap in force.

Rematch tiers: tier N (N >= 2) needs OW_REMATCH_BADGE_COUNT + N - 2 badges, the last tier the game
cleared (OW_REMATCH_TIER_BADGES, src/battle_setup.c), so tier 2 -> S6, 3 -> S7, 4 -> S8, 5 -> POST,
never earlier than the trainer's first battle. Gym leader / Wally rematches are post-game.
"""

import argparse
import json
import os
import re
import sys
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import scan_maps  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "segments.json")

ORDER = ["S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "POST"]
LABELS = {
    "S1": "Draconid Pass to Roxanne",
    "S2": "Rusturf Tunnel, Dewford, Brawly",
    "S3": "Slateport, Route 110, Mauville, Wattson",
    "S4": "Routes 111-114, Mt. Chimney, Jagged Pass, Flannery",
    "S5": "Desert, Norman",
    "S6": "Surf routes, Abandoned Ship, Route 119, Weather Institute, Winona",
    "S7": "Routes 120-134, Mt. Pyre, Lilycove, both hideouts, Tate & Liza",
    "S8": "Space Center, Seafloor Cavern, Sky Pillar, Juan",
    "S9": "Victory Road, Elite Four, Champion",
    "POST": "After the Champion (no cap)",
}
# Level bands inside a segment: (route trainers, gym trainers, gym leader / boss ace). Ace = cap.
BANDS = {
    "S1": ((5, 12), (11, 13), (13, 15)),
    "S2": ((12, 17), (16, 18), (18, 20)),
    "S3": ((17, 22), (21, 23), (23, 25)),
    "S4": ((21, 27), (26, 28), (28, 30)),
    "S5": ((26, 31), (30, 32), (32, 34)),
    "S6": ((30, 35), (34, 36), (36, 38)),
    "S7": ((34, 41), (39, 42), (42, 44)),
    "S8": ((40, 45), (44, 46), (46, 48)),
    "S9": ((48, 55), (54, 57), (57, 60)),
    "POST": ((60, 70), (66, 72), (70, 80)),
}
POST_CAP = 100

# Whole maps (prefix match on the map folder name).
MAP_SEGMENT = [
    ("DraconidPass", "S1"), ("Route102", "S1"), ("Route104", "S1"), ("PetalburgWoods", "S1"),
    ("RustboroCity", "S1"), ("Route116", "S1"),
    ("RusturfTunnel", "S2"), ("DewfordTown", "S2"), ("Route109_SeashoreHouse", "S2"),
    ("SlateportCity", "S3"), ("Route110_TrickHousePuzzle1", "S3"), ("Route110_TrickHousePuzzle2", "S4"),
    ("Route110_TrickHousePuzzle3", "S5"), ("Route110_TrickHousePuzzle4", "S6"),
    ("Route110_TrickHousePuzzle6", "S8"), ("Route110_TrickHousePuzzle7", "S9"),
    ("Route110_TrickHousePuzzle8", "POST"),
    ("Route110", "S3"), ("Route103", "S3"), ("MauvilleCity", "S3"), ("Route117", "S3"), ("Route118", "S3"),
    ("Route111", "S4"), ("Route112", "S4"), ("Route113", "S4"), ("Route114", "S4"),
    ("MtChimney", "S4"), ("JaggedPass", "S4"), ("LavaridgeTown", "S4"),
    ("PetalburgCity", "S5"),
    ("Route105", "S6"), ("Route107", "S6"), ("Route108", "S6"), ("Route109", "S6"),
    ("AbandonedShip", "S6"), ("Route119", "S6"), ("FortreeCity", "S6"),
    ("Route120", "S7"), ("Route121", "S7"), ("Route123", "S7"), ("MtPyre", "S7"), ("LilycoveCity", "S7"),
    ("AquaHideout", "S7"), ("MagmaHideout", "S7"), ("Route124", "S7"), ("Route125", "S7"),
    ("Route126", "S7"), ("Route127", "S7"), ("Route128", "S7"), ("Route129", "S7"), ("Route130", "S7"),
    ("Route131", "S7"), ("Route132", "S7"), ("Route133", "S7"), ("Route134", "S7"),
    ("MossdeepCity_Gym", "S7"),
    ("MossdeepCity_SpaceCenter", "S8"), ("SeafloorCavern", "S8"), ("SootopolisCity", "S8"),
    ("VictoryRoad", "S9"), ("EverGrandeCity", "S9"), ("MeteorFalls_1F_2R", "S9"),
    ("MeteorFalls_StevensCave", "POST"), ("SSTidal", "POST"), ("LittlerootTown_ProfessorBirchsLab", "POST"),
]

EGGS = ("DEINO", "DREEPY", "JANGMO_O")
STARTERS = ("CHARMANDER", "TOTODILE", "TREECKO")

# Trainers whose part of a map is reached at another time (checked against map.json coordinates).
OVERRIDES = {
    # Route 111 desert (needs the Go-Goggles from Flannery)
    **{t: "S5" for t in ["DREW", "BEAU", "HEIDI", "BECKY", "DUSTY_1", "CELIA", "BRYAN", "BRANDEN"]},
    # Route 118 east of the river (Surf)
    **{t: "S6" for t in ["BARNY", "PERRY", "CHESTER"]},
    # Route 115 north (Surf); the south half is reachable straight after Rustboro
    **{t: "S6" for t in ["TIMOTHY_1", "KOICHI", "KYRA", "JAIDEN", "ALIX", "HELENE"]},
    **{t: "S2" for t in ["NOB_1", "CYNDY_1", "HECTOR", "MARLENE"]},
    # Beaches reached by Mr. Briney's boat (Route 106 west beach, Route 109 sand)
    **{t: "S2" for t in ["ELLIOT_1", "NED", "HUEY", "EDMOND", "RICKY_1", "LOLA_1", "CHANDLER", "HAILEY"]},
    **{t: "S6" for t in ["DOUGLAS", "KYLA"]},
    # Winstrate family's house (Route 111 south)
    **{t: "S4" for t in ["VICTOR", "VICTORIA", "VIVI", "VICKY"]},
    # League
    **{t: "S9" for t in ["SIDNEY", "PHOEBE", "GLACIA", "DRAKE", "WALLY_VR_1"]},
    # Steven is the Champion; his ORAS post-game team after the Hall of Fame; Wallace guards Sootopolis (D-250 - D-252)
    "STEVEN": "S9", "STEVEN_REMATCH": "POST", "WALLACE": "POST",
    # Story battles (round 1 schedule, data/scripts/draconid/*.pory); variant ids (D-101) share their fight's segment
    "MAY_ROUTE_103": "S1", "BRENDAN_RUSTBORO": "S1", "MAY_ROUTE_110": "S3", "BRENDAN_MT_CHIMNEY": "S4",
    "BRENDAN_ROUTE_119": "S6", "BRENDAN_LILYCOVE": "S7", "MAY_LILYCOVE": "S7", "BRENDAN_MOSSDEEP": "S8",
    "MAY_RUSTBORO": "S2", "WALLY_PETALBURG": "S5",
    # more rival battles in Acts 1-5 (data/scripts/draconid/rivals2.pory, D-234)
    "BRENDAN_ROUTE_104": "S2", "WALLY_ROUTE_112": "S4", "MAY_LAVARIDGE": "S5", "WALLY_ROUTE_120": "S6",
    "BRENDAN_JAGGED_PASS": "S7", "MAY_MOSSDEEP": "S8",
    "WALLY_VR_2": "POST",  # Wally's rematches start after the Champion
    # Steven at the Space Center is overlevelled on purpose: he's the Champion (D-108), so no cap applies
    "STEVEN_MOSSDEEP": "POST",
    "MAXIE_SOOTOPOLIS": "S8", "MAXIE_SOOTOPOLIS_MULTI": "S8", "ARCHIE_SOOTOPOLIS_MULTI": "S8",
    # Team Magma's revenge (data/scripts/draconid/magma_revenge.pory, D-244 - D-249): from the Rain Badge to the
    # League door, so the Sootopolis ambush (out of Juan's Gym) is S9 like the Ever Grande and Victory Road ones
    **{t: "S9" for t in ["GRUNT_SOOTOPOLIS_REVENGE_1", "GRUNT_SOOTOPOLIS_REVENGE_2", "GRUNT_EVER_GRANDE_SHORE_1",
                         "GRUNT_EVER_GRANDE_SHORE_2", "GRUNT_EVER_GRANDE_CENTER", "SHELLY_EVER_GRANDE",
                         "MAXIE_VICTORY_ROAD", "TABITHA_VICTORY_ROAD", "COURTNEY_VICTORY_ROAD",
                         "GRUNT_VICTORY_ROAD_EXIT", "GRUNT_POKEMON_LEAGUE_1", "GRUNT_POKEMON_LEAGUE_2"]
       + ["GRUNT_AQUA_GAUNTLET_%d" % i for i in range(1, 6)]},
    **{"ASTER_PASS_" + e: "S1" for e in EGGS},
    **{"ASTER_METEOR_FALLS_" + e: "S4" for e in EGGS},
    # the Sky Pillar finale is after the League (D-109)
    **{"ASTER_SKY_PILLAR_" + e: "POST" for e in EGGS},
    **{"ASTER_POSTGAME_" + e: "POST" for e in EGGS},
    "ZINNIA_SKY_PILLAR": "POST",
    # the Elite Four's ORAS post-game rematch teams, used once the game is cleared (D-174)
    **{t + "_REMATCH": "POST" for t in ("SIDNEY", "PHOEBE", "GLACIA", "DRAKE")},
    # the Battle Frontier legends and their legends' tag teams, after the Hall of Fame (D-225, D-226)
    **{t + "_FRONTIER" + m: "POST" for t in ("WES", "RED", "BLUE") for m in ("", "_MULTI")},
    # Lance in the Draconid village, from the SS Ticket on (lance.pory, D-262)
    "LANCE_DRACONID": "POST",
    **{"NERINE_PETALBURG_WOODS_" + e: "S1" for e in EGGS},
    **{"NERINE_%s_%s_%s" % (f, e, st): seg for f, seg in (("RUSTURF", "S2"), ("SLATEPORT", "S3"), ("MT_CHIMNEY", "S4"),
                                                         ("MT_PYRE", "S7"), ("AQUA_HIDEOUT", "S7"), ("SEAFLOOR", "S8"),
                                                         ("POSTGAME", "POST"))
       for e in EGGS for st in STARTERS},
    **{t: "POST" for t in ["BRENDAN_POSTGAME", "MAY_POSTGAME", "BRENDAN_POSTGAME_DOUBLE", "MAY_POSTGAME_DOUBLE"]},
    # the attack on the Draconid village after the Sky Pillar, the Primal finale (act7x.pory, D-205, D-206)
    **{"GRUNT_VILLAGE_%d" % i: "POST" for i in range(1, 7)},
    "TABITHA_VILLAGE": "POST", "SHELLY_VILLAGE": "POST", "MAXIE_FINALE": "POST", "ARCHIE_FINALE": "POST",
    "WALLACE_SKY_PILLAR": "POST",  # before the Trial of Three (D-203)
    # Gabby & Ty move on after every battle (Route 111 -> 118 -> 120 ...)
    "GABBY_AND_TY_1": "S4", "GABBY_AND_TY_2": "S4", "GABBY_AND_TY_3": "S5",
    "GABBY_AND_TY_4": "S6", "GABBY_AND_TY_5": "S7", "GABBY_AND_TY_6": "S8",
}
# every id the game uses (TRAINERS_COUNT_EMERALD)
MAX_ID = 979

TIER_MIN = {2: "S6", 3: "S7", 4: "S8", 5: "POST", 6: "POST"}

LEADERS = ["ROXANNE_1", "BRAWLY_1", "WATTSON_1", "FLANNERY_1", "NORMAN_1", "WINONA_1", "TATE_AND_LIZA_1", "JUAN_1"]
ELITE = ["SIDNEY", "PHOEBE", "GLACIA", "DRAKE", "WALLACE", "STEVEN", "STEVEN_REMATCH"]
BOSSES = ["MAXIE", "ARCHIE"]
ADMINS = ["TABITHA", "SHELLY", "MATT", "COURTNEY"]
# Battles written by hand with the story (Phase 5): not in the trainer batches.
STORY = re.compile(r"^TRAINER_(BRENDAN|MAY|WALLY|ASTER|NERINE|ZINNIA|STEVEN_MOSSDEEP|MAXIE_SOOTOPOLIS|ARCHIE_SOOTOPOLIS|"
                   # Team Magma's revenge (magma_revenge.pory, D-245 - D-247)
                   r"GRUNT_SOOTOPOLIS_REVENGE|GRUNT_EVER_GRANDE|GRUNT_AQUA_GAUNTLET|SHELLY_EVER_GRANDE|MAXIE_VICTORY_ROAD|"
                   r"TABITHA_VICTORY_ROAD|COURTNEY_VICTORY_ROAD|GRUNT_VICTORY_ROAD_EXIT|GRUNT_POKEMON_LEAGUE|"
                   # the village attack and the Primal finale, Wallace at the Sky Pillar (act7x.pory, D-203, D-205)
                   r"MAXIE_FINALE|ARCHIE_FINALE|TABITHA_VILLAGE|SHELLY_VILLAGE|GRUNT_VILLAGE_|WALLACE_SKY_PILLAR)")
SKIP = {"TRAINER_BRENDAN_PLACEHOLDER", "TRAINER_MAY_PLACEHOLDER", "TRAINER_RED", "TRAINER_LEAF",
        "TRAINER_GRUNT_UNUSED", "TRAINER_CINDY_2", "TRAINER_AMY_AND_LIV_3", "TRAINER_GINA_AND_MIA_2",
        "TRAINER_LUCAS_2", "TRAINER_MIKE_1", "TRAINER_DUDLEY", "TRAINER_KAYLEE", "TRAINER_TERRY",
        # Frontier Brains: their parties come from the Frontier code, not trainers.party
        "TRAINER_ANABEL", "TRAINER_TUCKER", "TRAINER_SPENSER", "TRAINER_GRETA", "TRAINER_NOLAND",
        "TRAINER_LUCY", "TRAINER_BRANDON",
        # round 1: a vanilla Aqua grunt whose battle is Nerine's now
        "TRAINER_GRUNT_RUSTURF_TUNNEL",
        # round 1 Act 4: Maxie promotes the player in the Magma Hideout instead of battling (D-134)
        "TRAINER_MAXIE_MAGMA_HIDEOUT",
        # round 1 Act 3: Mt. Chimney is one scene with Nerine and Brendan; Tabitha and Maxie don't battle (D-123)
        "TRAINER_TABITHA_MT_CHIMNEY", "TRAINER_MAXIE_MT_CHIMNEY",
        # round 1 Act 5: at the Space Center Tabitha is the player's partner against Steven + Brendan (D-141)
        "TRAINER_TABITHA_MOSSDEEP", "TRAINER_MAXIE_MOSSDEEP"}


def read_caps():
    text = open(os.path.join(ROOT, "src/caps.c")).read()
    caps = [int(v) for v in re.findall(r"\{FLAG_\w+,\s*(\d+)\}", text)]
    assert len(caps) == 9, caps
    return dict(zip(ORDER[:9], caps), POST=POST_CAP)


def map_segment(name):
    for prefix, seg in MAP_SEGMENT:
        if name == prefix or name.startswith(prefix + "_") or name.startswith(prefix):
            if name.startswith(prefix):
                return seg
    return None


def role_of(tid, mapname):
    short = tid[len("TRAINER_"):]
    if short in LEADERS or re.match(r"(%s)_\d$" % "|".join(l[:-2] for l in LEADERS), short):
        return "leader"
    if short in ELITE:
        return "elite"
    if any(short == b or short.startswith(b + "_") for b in BOSSES):
        return "boss"
    if any(short == b or short.startswith(b + "_") for b in ADMINS):
        return "admin"
    if short.startswith("GRUNT"):
        return "grunt"
    if mapname and "_Gym" in mapname:
        return "gym"
    return "route"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--list")
    args = ap.parse_args()

    caps = read_caps()
    ids = scan_maps.trainer_ids()
    maps = scan_maps.scan(ids)
    where = {}
    for m, ts in maps.items():
        for t in ts:
            where.setdefault(t, m)
    trainers = {}

    def put(tid, seg, role, tier=1, base=None):
        if tid in SKIP or tid in trainers:
            return
        trainers[tid] = {"segment": seg, "role": role, "map": where.get(tid) or (base and where.get(base)),
                         "story": bool(STORY.match(tid))}
        if tier > 1:
            trainers[tid]["tier"] = tier
            trainers[tid]["first"] = base

    rematch = scan_maps.rematches()
    tiers = {}
    for row, _ in rematch:
        for i, t in enumerate(row[1:], start=2):
            if t != row[0]:
                tiers.setdefault(t, (i, row[0]))

    for tid in sorted(ids, key=ids.get):
        if not 0 < ids[tid] < MAX_ID or tid in tiers:
            continue
        short = tid[len("TRAINER_"):]
        seg = OVERRIDES.get(short) or (map_segment(where[tid]) if tid in where else None)
        if seg is None:
            continue
        put(tid, seg, role_of(tid, where.get(tid)))
    for tid, (tier, base) in tiers.items():
        if base not in trainers:
            continue
        b = trainers[base]
        if b["role"] in ("leader", "elite") or tid.startswith("TRAINER_WALLY"):
            seg = "POST"
        else:
            seg = ORDER[max(ORDER.index(b["segment"]), ORDER.index(TIER_MIN[tier]))]
        put(tid, seg, b["role"], tier, base)

    unplaced = [t for t in ids if 0 < ids[t] < MAX_ID and t not in trainers and t not in SKIP]
    segs = {s: {"cap": caps[s], "label": LABELS[s], "route": BANDS[s][0], "gym": BANDS[s][1],
                "ace": BANDS[s][2]} for s in ORDER}
    data = {"segments": segs, "trainers": {t: trainers[t]["segment"] for t in sorted(trainers, key=ids.get)},
            "info": {t: trainers[t] for t in sorted(trainers, key=ids.get)}}
    json.dump(data, open(OUT, "w"), indent=1)

    if args.list:
        for t, v in data["info"].items():
            if v["segment"] == args.list:
                print(t, v["role"], v["map"], "tier %d" % v["tier"] if "tier" in v else "", "STORY" if v["story"] else "")
        return
    count = Counter((v["segment"]) for v in trainers.values() if not v["story"])
    print("segments.json: %d trainers (%d story)" % (len(trainers), sum(v["story"] for v in trainers.values())))
    for s in ORDER:
        print("  %-4s cap %3d  %3d trainers  %s" % (s, caps[s], count[s], LABELS[s]))
    if unplaced:
        print("unplaced:", " ".join(unplaced))


if __name__ == "__main__":
    main()
