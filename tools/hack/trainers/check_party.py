#!/usr/bin/env python3
"""
check_party.py - sanity-check trainer parties in .party files.

  python3 tools/hack/trainers/check_party.py                       # all of src/data/trainers.party
  python3 tools/hack/trainers/check_party.py batch.party --caps     # a batch, with level caps
  python3 tools/hack/trainers/check_party.py --only TRAINER_ROXANNE_1 TRAINER_BRAWLY_1
  python3 tools/hack/trainers/check_party.py batch.party --caps --proc   # also run trainerproc on it

Checks per trainer:
  - 1-6 Pokemon, at least 2 for a double battle
  - the presentation fields (Name, Class, Pic, Gender, Music, Double Battle, Battle Type) match
    src/data/trainers.party when the trainer already exists there (--allow-header to skip)
  - no Tera Type / Dynamax / Gigantamax
Checks per Pokemon:
  - species, held item and nature exist; the ability is one of the species' abilities
  - at most 4 moves, each learnable by the species or one of its pre-evolutions
    (src/data/pokemon/all_learnables.json: TM/HM, tutor and egg moves, plus the level-up learnsets)
  - evolved forms are not below the level at which their line evolves by level-up
    (e.g. Salamence below 50; up to EVO_SLACK levels under is a warning, allowed for aces and
    bosses only; stone/trade evolutions are not checked)
  - the species is in the Hoenn Pokedex (with cross-generation evolutions) or used by some trainer
    in vanilla Emerald (warning otherwise; story trainers with their own rosters are exempt)
  - Mega Stones only for trainers listed in MEGA_TRAINERS (warning otherwise)
  - with --caps: levels do not exceed the trainer's segment cap (tools/hack/trainers/segments.json)
Errors fail the run (exit 1).
"""

import argparse
import glob
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import party  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
EVO_SLACK = 3
STORY_TRAINERS = re.compile(r"^TRAINER_(BRENDAN|MAY|WALLY|ASTER|NERINE|ZINNIA)_")
HEADER_FIELDS = ("Name", "Class", "Pic", "Gender", "Music", "Double Battle", "Battle Type")
# Trainers allowed to hold a Mega Stone (docs/hack_trainers.md, "Megas").
MEGA_TRAINERS = re.compile(r"^(PARTNER_|TRAINER_(BRENDAN|MAY|WALLY|ASTER|NERINE|ZINNIA|MAXIE_MAGMA_HIDEOUT|MAXIE_SOOTOPOLIS|ARCHIE|STEVEN|"
                           r"(ROXANNE|BRAWLY|WATTSON|FLANNERY|NORMAN|WINONA|TATE_AND_LIZA|JUAN)_5))")


def levelup_file():
    """The level-up learnset file the ROM uses (P_LVL_UP_LEARNSETS in include/config/pokemon.h)."""
    cfg = open(os.path.join(ROOT, "include/config/pokemon.h")).read()
    gen = re.search(r"#define P_LVL_UP_LEARNSETS\s+GEN_(\w+)", cfg).group(1)
    return os.path.join(ROOT, "src/data/pokemon/level_up_learnsets/gen_%s.h" % ("9" if gen == "LATEST" else gen))


def load_levelup():
    """learnset symbol -> set of MOVE_* from the level-up learnset file the ROM uses."""
    sets = {}
    for path in [levelup_file()]:
        for m in re.finditer(r"(\w+)\[\]\s*=\s*\{(.*?)\};", open(path).read(), re.S):
            sets[m.group(1)] = set(re.findall(r"LEVEL_UP_MOVE\(\s*\d+,\s*(MOVE_\w+)\)", m.group(2)))
    return sets


def load_species_info():
    """(parents: child -> (parent, method, param), abilities: species -> set of ABILITY_*,
    levelup: species -> set of MOVE_* it learns by level-up)."""
    draconid = {k: int(v) for k, v in re.findall(r"#define (DRACONID_\w+)\s+(\d+)",
                                                   open(os.path.join(ROOT, "include/constants/draconid.h")).read())}
    parent, abilities, levelup = {}, {}, {}
    lsets = load_levelup()
    for path in glob.glob(os.path.join(ROOT, "src/data/pokemon/species_info/*.h")):
        text = open(path).read()
        for m in re.finditer(r"\[SPECIES_(\w+)\]\s*=\s*\{(.*?)\n    \},", text, re.S):
            name, body = m.group(1), m.group(2) + "\n"
            lp = re.search(r"\.levelUpLearnset\s*=\s*(\w+)", body)
            if lp:
                levelup[name] = lsets.get(lp.group(1), set())
            ab = re.search(r"\.abilities\s*=\s*\{([^}]*)\}", body)
            if ab:
                abilities[name] = {a.strip() for a in ab.group(1).split(",") if a.strip()}
            ev = re.search(r"\.evolutions\s*=\s*EVOLUTION\((.*?)\),\s*\n", body, re.S)
            if not ev:
                continue
            for method, param, child in re.findall(r"\{\s*(EVO_\w+)\s*,\s*([^,]+?)\s*,\s*SPECIES_(\w+)", ev.group(1)):
                param = str(draconid.get(param.strip(), param.strip()))  # DRACONID_EVO_LEVEL_* (D-107)
                parent.setdefault(child, (name, method, param))
    return parent, abilities, levelup


def load_constants(path, prefix):
    text = open(os.path.join(ROOT, path)).read()
    return set(re.findall(r"\b(%s\w+)\s*=" % prefix, text)) | set(re.findall(r"#define (%s\w+)" % prefix, text))


def mega_stones():
    text = open(os.path.join(ROOT, "src/data/items.h")).read()
    return set(re.findall(r"\[(ITEM_\w+)\]\s*=\s*\{[^{}]*?HOLD_EFFECT_MEGA_STONE", text, re.S))


def species_pool():
    """Hoenn dex (FOREACH_SPECIES_IN_HOENN_DEX_ORDER, cross-gen evolutions included) + every species
    a vanilla Emerald trainer uses (git HEAD of master is not needed: the vanilla file is in git)."""
    text = open(os.path.join(ROOT, "include/constants/pokedex.h")).read()
    m = re.search(r"#define FOREACH_SPECIES_IN_HOENN_DEX_ORDER\(F\)(.*?)\n\n", text, re.S)
    pool = set(re.findall(r"F\((\w+)\)", m.group(1)))
    # Draconid Emerald: the dragon egg lines and Birch's second starters (the player's, Aster's and Nerine's)
    pool |= {"DEINO", "ZWEILOUS", "HYDREIGON", "DREEPY", "DRAKLOAK", "DRAGAPULT", "JANGMO_O", "HAKAMO_O", "KOMMO_O",
             "CHARMANDER", "CHARMELEON", "CHARIZARD", "TOTODILE", "CROCONAW", "FERALIGATR"}
    vanilla = subprocess.run(["git", "-C", ROOT, "show", "master:src/data/trainers.party"],
                             capture_output=True, text=True).stdout
    for _, raw in party.split(vanilla)[1]:
        for mon in party.parse_block(raw)["mons"]:
            pool.add(party.const_name(mon["species"], "SPECIES_")[len("SPECIES_"):])
    return pool


# Round 1 ORAS data (docs/hack_trainers.md, "ORAS data"): the Elite Four use their ORAS post-game rosters,
# species from all regions included, so they skip the species-pool warning (D-173); their post-game rematch
# holds the ORAS Mega Stones, like the trainers in MEGA_TRAINERS (D-174).
ORAS_ROSTER_TRAINERS = re.compile(r"^TRAINER_(SIDNEY|PHOEBE|GLACIA|DRAKE)(_REMATCH)?$")
ORAS_MEGA_TRAINERS = re.compile(r"^TRAINER_(SIDNEY|PHOEBE|GLACIA|DRAKE)_REMATCH$")


def min_level(species, parents):
    """Lowest level a species can have when every level-up evolution in its line is respected."""
    lv, cur, seen = 1, species, set()
    while cur in parents and cur not in seen:
        seen.add(cur)
        par, method, param = parents[cur]
        if method in ("EVO_LEVEL", "EVO_LEVEL_FEMALE", "EVO_LEVEL_MALE") and param.isdigit():
            lv = max(lv, int(param))
        cur = par
    return lv


def run_trainerproc(path):
    """Preprocess + trainerproc exactly like trainer_rules.mk; returns error text or ''."""
    cpp = subprocess.run(["arm-none-eabi-cpp", "-I", os.path.join(ROOT, "include"), "-traditional-cpp", "-"],
                         stdin=open(path), capture_output=True, text=True)
    if cpp.returncode:
        return cpp.stderr
    tp = subprocess.run([os.path.join(ROOT, "tools/trainerproc/trainerproc"), "-o", os.devnull, "-i", path, "-"],
                        input=cpp.stdout, capture_output=True, text=True)
    return tp.stderr if tp.returncode else ""


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="*", default=[os.path.join(ROOT, "src/data/trainers.party")])
    ap.add_argument("--only", nargs="*", help="trainer ids to check")
    ap.add_argument("--caps", action="store_true", help="check levels against tools/hack/trainers/segments.json")
    ap.add_argument("--evo-slack", type=int, default=0, help="levels an evolved mon may be under its evolution level")
    ap.add_argument("--allow-header", action="store_true", help="allow Name/Class/Pic/... to differ from trainers.party")
    ap.add_argument("--proc", action="store_true", help="also run cpp + trainerproc on each file")
    args = ap.parse_args()

    learn = {k.upper(): set(v) for k, v in json.load(open(os.path.join(ROOT, "src/data/pokemon/all_learnables.json"))).items()}
    parents, abilities, levelup = load_species_info()
    species_ok = load_constants("include/constants/species.h", "SPECIES_")
    items_ok = load_constants("include/constants/items.h", "ITEM_")
    abilities_ok = load_constants("include/constants/abilities.h", "ABILITY_")
    natures_ok = load_constants("include/constants/pokemon.h", "NATURE_")
    stones = mega_stones()
    pool = species_pool()
    _, base_blocks = party.split(open(os.path.join(ROOT, "src/data/trainers.party")).read())
    base = {tid: party.parse_block(raw)["fields"] for tid, raw in base_blocks}
    caps = {}
    if args.caps:
        seg = json.load(open(os.path.join(ROOT, "tools/hack/trainers/segments.json")))
        for tid, s in seg["trainers"].items():
            caps[tid] = seg["segments"][s]["cap"]

    errors = warnings = 0

    def err(msg):
        nonlocal errors
        print("ERROR   " + msg)
        errors += 1

    def warn(msg):
        nonlocal warnings
        print("WARNING " + msg)
        warnings += 1

    for path in args.files:
        if args.proc:
            out = run_trainerproc(path)
            if out:
                err("%s: trainerproc:\n%s" % (path, out.strip()))
        _, blocks = party.split(open(path).read())
        for tid, raw in blocks:
            if args.only and tid not in args.only:
                continue
            b = party.parse_block(raw)
            f = b["fields"]
            n = len(b["mons"])
            if tid not in ("TRAINER_NONE", "PARTNER_NONE") and not 1 <= n <= 6:
                err("%s: %d Pokemon" % (tid, n))
            doubles = f.get("Double Battle", "No") == "Yes" or f.get("Battle Type", "") == "Doubles"
            if doubles and n < 2:
                err("%s: double battle with %d Pokemon" % (tid, n))
            if tid in base and not args.allow_header:
                for k in HEADER_FIELDS:
                    if f.get(k) != base[tid].get(k):
                        err("%s: %s changed (%r -> %r)" % (tid, k, base[tid].get(k), f.get(k)))
            for i, mon in enumerate(b["mons"]):
                sp = party.const_name(mon["species"], "SPECIES_")[len("SPECIES_"):]
                where = "%s mon %d (%s Lv%d)" % (tid, i + 1, mon["species"], mon["level"])
                if "SPECIES_" + sp not in species_ok:
                    err("%s: unknown species" % where)
                    continue
                for k in ("tera type", "dynamax level", "gigantamax"):
                    if k in mon:
                        err("%s: %s is not used in this hack" % (where, k))
                if mon["item"]:
                    item = party.const_name(mon["item"], "ITEM_")
                    if item not in items_ok:
                        err("%s: unknown item %s" % (where, mon["item"]))
                    elif item in stones and not MEGA_TRAINERS.match(tid) and not ORAS_MEGA_TRAINERS.match(tid):
                        warn("%s: Mega Stone on a trainer outside MEGA_TRAINERS" % where)
                if "nature" in mon and party.const_name(mon["nature"], "NATURE_") not in natures_ok:
                    err("%s: unknown nature %s" % (where, mon["nature"]))
                if "ability" in mon:
                    ab = party.const_name(mon["ability"], "ABILITY_")
                    if ab not in abilities_ok:
                        err("%s: unknown ability %s" % (where, mon["ability"]))
                    elif sp in abilities and ab not in abilities[sp]:
                        err("%s: %s is not one of its abilities" % (where, mon["ability"]))
                if len(mon["moves"]) > 4:
                    err("%s: %d moves" % (where, len(mon["moves"])))
                if not 1 <= mon["level"] <= 100:
                    err("%s: level out of range" % where)
                line = [sp]
                cur = sp
                while cur in parents:
                    cur = parents[cur][0]
                    line.append(cur)
                base_forms = {s.split("_MEGA")[0].split("_PRIMAL")[0] for s in line}
                known = set()
                for s in line + sorted(base_forms):
                    known |= learn.get(s, set()) | levelup.get(s, set())
                for mv in mon["moves"]:
                    const = party.const_name(mv, "MOVE_")
                    if const not in known:
                        err("%s: cannot learn %s" % (where, mv))
                ml = min_level(sp, parents)
                if mon["level"] < ml - args.evo_slack - EVO_SLACK:
                    err("%s: evolves by level-up at %d" % (where, ml))
                elif mon["level"] < ml - args.evo_slack:
                    warn("%s: evolves by level-up at %d (only aces/bosses may be under)" % (where, ml))
                if sp not in pool and not STORY_TRAINERS.match(tid) and not ORAS_ROSTER_TRAINERS.match(tid):
                    warn("%s: not in the Hoenn dex or a vanilla Emerald team" % where)
                if tid in caps and mon["level"] > caps[tid]:
                    err("%s: above the segment cap %d" % (where, caps[tid]))
    print("%d error(s), %d warning(s)" % (errors, warnings))
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
