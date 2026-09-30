#!/usr/bin/env python3
"""
match_oras.py - pair each Emerald trainer with its ORAS counterpart (tools/hack/trainers/oras/oras_trainers.json).

  python3 tools/hack/trainers/oras/match_oras.py            # write oras_matches.json + print a summary
  python3 tools/hack/trainers/oras/match_oras.py --list     # one line per trainer
  python3 tools/hack/trainers/oras/match_oras.py --show TRAINER_BILLY

A match needs the same name (case-insensitive; "GINA & MIA" = "Gina & Mia") on the ORAS page of the trainer's
map (segments.json "map" -> Serebii page, see PAGE). Status:
  exact      same name, same page, same class (Emerald class names mapped to ORAS ones, CLASS_MAP)
  class      same name and page, another class (ORAS renamed the class, e.g. Beauty -> Lass): used, flagged
  elsewhere  only on another page, but the one ORAS trainer of that class and name there: the same person
             placed elsewhere (Shelby: Mt. Chimney -> Jagged Pass) or a namesake; reported, not used
  ambiguous  more than one ORAS trainer of that name on the page, or only on another page: not used
  none       no ORAS trainer of that name
For each trainer the result says whether it has Emerald rematch tiers (gRematchTable) and whether the ORAS
counterpart has rematch teams, and names the ORAS team a rewrite would use.
Story trainers (Brendan, May, Wally, Aster, Nerine, Steven, Maxie, Archie, Tabitha, Shelly, Matt, gym leaders)
and grunts (no names in either game) are skipped.
"""

import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TRAINERS = os.path.dirname(HERE)
sys.path.insert(0, TRAINERS)
import party  # noqa: E402
import scan_maps  # noqa: E402

ROOT = os.path.abspath(os.path.join(TRAINERS, "..", "..", ".."))
OUT = os.path.join(HERE, "oras_matches.json")

# Emerald class -> ORAS class (Serebii's spelling); classes not listed are the same in both games.
CLASS_MAP = {
    "Cooltrainer": "Ace Trainer", "Pkmn Breeder": "Pokémon Breeder", "Pkmn Ranger": "Pokémon Ranger",
    "Pokefan": "Poké Fan", "Pokemaniac": "Poké Maniac", "Swimmer M": "Swimmer", "Swimmer F": "Swimmer",
    "Tuber M": "Tuber", "Tuber F": "Tuber", "Sis And Bro": "Sis & Bro", "Sr And Jr": "Sr. & Jr.",
    "Winstrate": "The Winstrates’", "Interviewer": "Interviewers", "School Kid": "Schoolkid",
    "Elite Four": "Elite Four", "Champion": "Champion",
}
# Emerald map (segments.json) -> Serebii page. Longest prefix wins; the rest is the map name lowercased.
PAGE = [
    ("EverGrandeCity_ChampionsRoom", "oras_elitefour"), ("EverGrandeCity_", "oras_elitefour"),
    ("Route110_TrickHouse", "route110"), ("Route109_SeashoreHouse", "route109"),
    ("Route119_WeatherInstitute", "route119"), ("MossdeepCity_SpaceCenter", "mossdeepcity"),
    ("MtPyre", "mt.pyre"), ("MtChimney", "mt.chimney"), ("SSTidal", "sstidal"), ("MeteorFalls", "meteorfalls"),
    ("VictoryRoad", "victoryroad"), ("SeafloorCavern", "seafloorcavern"), ("AquaHideout", "aquahideout"),
    ("MagmaHideout", "magmahideout"), ("GraniteCave", "granitecave"),
    ("AbandonedShip", "seamauville"),  # ORAS replaced the Abandoned Ship with Sea Mauville (same trainers)
    ("JaggedPass", "jaggedpass"), ("PetalburgWoods", "petalburgwoods"), ("RusturfTunnel", "rusturftunnel"),
    ("SkyPillar", "skypillar"), ("ShoalCave", "shoalcave"), ("NewMauville", "newmauville"),
]
SKIP = re.compile(r"^TRAINER_(BRENDAN|MAY|WALLY|ASTER|NERINE|STEVEN|MAXIE|ARCHIE|TABITHA|SHELLY|MATT|GRUNT|"
                  r"ROXANNE|BRAWLY|WATTSON|FLANNERY|NORMAN|WINONA|TATE_AND_LIZA|JUAN|DRACONID)")


def page_of(mapname):
    if not mapname:
        return None
    for prefix, page in PAGE:
        if mapname.startswith(prefix):
            return page
    return mapname.split("_")[0].lower()


def norm(name):
    return re.sub(r"\s+", " ", name.upper().replace(" AND ", " & ")).strip()


def tiered():
    """trainer id -> base id (the _1 / first entry) for every id with rematch tiers in gRematchTable
    (rows naming one id five times - the Elite Four, Wallace - have no tiers)."""
    out = {}
    for tiers, _ in scan_maps.rematches():
        if len(set(tiers)) > 1:
            for t in tiers:
                out.setdefault(t, tiers[0])
    return out


def tiers_table(result, oras, tiers):
    """Trainers that keep their Emerald rematch roster (rule 1) next to what ORAS gives them."""
    import subprocess
    vanilla = {t: party.parse_block(r) for t, r in party.split(subprocess.run(
        ["git", "-C", ROOT, "show", "master:src/data/trainers.party"], capture_output=True, text=True).stdout)[1]}
    last = {}
    for row, _ in scan_maps.rematches():
        if len(set(row)) > 1:
            last[row[0]] = row[-1]
    last["TRAINER_CINDY_1"] = "TRAINER_CINDY_6"  # the tiers Emerald really uses (docs/hack_trainers.md)
    last["TRAINER_AMY_AND_LIV_1"] = "TRAINER_AMY_AND_LIV_6"
    import check_party
    parents = check_party.load_species_info()[0]

    def family(name):
        sp, seen = party.const_name(name, "SPECIES_")[len("SPECIES_"):], set()
        while sp in parents and sp not in seen:
            seen.add(sp)
            sp = parents[sp][0]
        return sp

    print("| Trainer | Emerald rematch roster (last tier) | ORAS last rematch | New families in ORAS |")
    print("|---|---|---|---|")
    for tid, e in result.items():
        if not e["emerald_tiers"] or not e.get("oras_rematch"):
            continue
        g = oras["grouped"][e["oras"]["page"]][e["oras"]["index"]]
        em = [m["species"] for m in vanilla[last.get(tid, tid)]["mons"]] if last.get(tid, tid) in vanilla else []
        orr = [m["species"] for m in g["teams"][-1]["mons"]]
        emf = {family(s) for s in em}
        new = [s for s in orr if family(s) not in emf]
        where = "" if e["status"] != "elsewhere" else " (ORAS: %s)" % oras["locations"][e["oras"]["page"]]["title"]
        print("| %s%s | %s | %s | %s |" % (tid[len("TRAINER_"):], where, ", ".join(em), ", ".join(
            "%s %d" % (m["species"], m["level"]) for m in g["teams"][-1]["mons"]), ", ".join(new) or "–"))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--show")
    ap.add_argument("--tiers", action="store_true",
                    help="markdown table: Emerald rematch roster vs ORAS rematch roster (trainers with tiers)")
    args = ap.parse_args()
    oras = json.load(open(os.path.join(HERE, "oras_trainers.json"), encoding="utf-8"))
    seg = json.load(open(os.path.join(TRAINERS, "segments.json")))
    blocks = {tid: party.parse_block(raw) for tid, raw in party.split(open(os.path.join(ROOT, "src/data/trainers.party")).read())[1]}
    tiers = tiered()
    by_name = {}
    for page, groups in oras["grouped"].items():
        for i, g in enumerate(groups):
            by_name.setdefault(norm(g["name"]), []).append((page, i, g))
    result = {}
    for tid, info in seg["info"].items():
        if info["story"] or SKIP.match(tid) or tid not in blocks or "tier" in info:
            continue
        f = blocks[tid]["fields"]
        name, cls = norm(f.get("Name", "")), f.get("Class", "")
        page = page_of(info["map"])
        entry = {"name": f.get("Name"), "class": cls, "map": info["map"], "segment": info["segment"],
                 "role": info["role"], "emerald_tiers": tid in tiers, "page": page}
        cands = by_name.get(name, [])
        here = [c for c in cands if c[0] == page]
        want = CLASS_MAP.get(cls, cls)
        if page == "oras_elitefour":
            # First battle and the post-game rematch are two tables on the Elite Four page.
            here = [c for c in here if c[2]["class"] == want]
        if not cands:
            entry["status"] = "none"
        elif not here:
            entry["status"] = "ambiguous"
            entry["why"] = "only on " + ", ".join(sorted({c[0] for c in cands}))
            same = [c for c in cands if c[2]["class"] == want]
            if len(same) == 1:
                # One ORAS trainer of that class and name, elsewhere: the same person placed elsewhere (Shelby:
                # Mt. Chimney -> Jagged Pass). Listed for the report, not used for a rewrite.
                p, i, g = same[0]
                entry["status"] = "elsewhere"
                entry["oras"] = {"page": p, "index": i, "class": g["class"], "name": g["name"],
                                 "area": g["area"], "note": g["note"], "teams": len(g["teams"])}
                entry["oras_rematch"] = len(g["teams"]) > 1
        elif len(here) > 1 and page != "oras_elitefour":
            same = [c for c in here if c[2]["class"] == want]
            if len(same) == 1:
                here = same
            else:
                entry["status"] = "ambiguous"
                entry["why"] = "%d trainers named %s on %s" % (len(here), f.get("Name"), page)
        if "status" not in entry:
            p, i, g = here[0]
            entry["status"] = "exact" if g["class"] == want else "class"
            if entry["status"] == "class":
                entry["why"] = "ORAS class %s" % g["class"]
            entry["oras"] = {"page": p, "index": i, "class": g["class"], "name": g["name"], "area": g["area"],
                             "note": g["note"], "teams": len(g["teams"])}
            if page == "oras_elitefour":
                entry["oras"]["rematch_index"] = here[-1][1]
            entry["oras_rematch"] = len(g["teams"]) > 1 or (page == "oras_elitefour" and len(here) > 1)
        result[tid] = entry
    json.dump(result, open(OUT, "w", encoding="utf-8"), indent=1, ensure_ascii=False)
    if args.show:
        print(json.dumps(result.get(args.show), indent=1, ensure_ascii=False))
        return
    if args.list:
        for tid, e in result.items():
            print("%-28s %-5s %-9s tiers=%-5s orasRe=%-5s %s %s" % (
                tid, e["segment"], e["status"], e["emerald_tiers"], e.get("oras_rematch", ""),
                e.get("oras", {}).get("page", e["page"]), e.get("why", "")))
    if args.tiers:
        tiers_table(result, oras, tiers)
        return
    from collections import Counter
    c = Counter(e["status"] for e in result.values())
    print("matched %d trainers: %s" % (len(result), dict(c)))
    print("  with Emerald tiers: %d; ORAS rematch known for %d of them" % (
        sum(e["emerald_tiers"] for e in result.values()),
        sum(e["emerald_tiers"] and e.get("oras_rematch", False) for e in result.values())))
    print("  without Emerald tiers, ORAS rematch known: %d" % sum(
        not e["emerald_tiers"] and e.get("oras_rematch", False) for e in result.values()))


if __name__ == "__main__":
    main()
