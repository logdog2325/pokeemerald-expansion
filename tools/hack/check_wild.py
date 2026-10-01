#!/usr/bin/env python3
"""
check_wild.py - sanity-check the wild encounter tables (src/data/wild_encounters.json).

  python3 tools/hack/check_wild.py                  # all checks; exit 1 on errors
  python3 tools/hack/check_wild.py --changes        # Markdown rows of every Hoenn slot that differs from vanilla
  python3 tools/hack/check_wild.py --doc            # the same table into docs/hack_wild.md ("## Table changes")
  python3 tools/hack/check_wild.py --info Nymble Beldum   # what the build knows about a species
  python3 tools/hack/check_wild.py --vanilla FILE   # compare against FILE instead of master's JSON
  python3 tools/hack/check_wild.py --wild FILE      # check FILE instead of src/data/wild_encounters.json

"Hoenn tables" are the gWildMonHeaders entries of Hoenn maps (FRLG tables end in _FireRed / _LeafGreen);
"vanilla" is src/data/wild_encounters.json on the master branch (pokeemerald-expansion 1.17.1).
Species data comes from the preprocessed src/data/pokemon/species_info.h (gSpeciesInfo as this build compiles it),
so a species whose family or form is switched off in include/config/species_enabled.h is "not enabled".

Checks (docs/hack_wild.md):
  - every species exists (include/constants/species.h, aliases resolved) and is enabled in this build
  - it has a front pic, a cry and a level-up learnset
  - no legendary, sub-legendary, mythical, paradox or Ultra Beast; no Mega / Primal / Gigantamax / Totem /
    Tera / Ultra Burst form; no regional form (Alolan, Galarian, Hisuian, Paldean) outside REGIONAL_OK (D-193)
  - every table keeps its slot count and encounter rate; FRLG, Battle Pyramid and Battle Pike tables stay vanilla
  - a table of a map the hack added (HACK_MAPS, e.g. Draconid Pass) has no vanilla counterpart: it must have
    the field's slot count and an encounter rate some vanilla Hoenn table of that field uses, and every slot
    counts as changed (the level rule below uses the area's cap); any other table without a vanilla
    counterpart is an error
  - 1 <= min <= max <= 100; a slot the hack changed keeps its vanilla levels or stays within the area's
    level cap + LEVEL_MARGIN (area -> segment in WILD_SEGMENTS, the method can push it later, caps from
    src/caps.c)
  - a species the hack added is not below the level at which its line evolves by level-up
  - every species of the vanilla Hoenn tables is still in some Hoenn table
  - Beldum is in a 1% land slot of every Granite Cave table, within that table's level range
Prints one line per finding and a summary.
"""

import argparse
import json
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
WILD = os.path.join(ROOT, "src/data/wild_encounters.json")
DOC = os.path.join(ROOT, "docs/hack_wild.md")
DOC_HEADING = "## Table changes"
sys.path.insert(0, os.path.join(ROOT, "tools/hack/trainers"))
import build_segments  # noqa: E402

ORDER = build_segments.ORDER
# A changed slot may go this many levels over the cap in force where it is first met. Wild Pokemon are
# caught, not fought for EXP, and the hard cap stops them from levelling until the next badge anyway;
# vanilla slots keep their levels even where they are higher (Route 115, Good Rod slots).
LEVEL_MARGIN = 3
BELDUM = "SPECIES_BELDUM"
# Regional forms allowed in the wild (D-193: none - every Hoenn species keeps its Hoenn look).
REGIONAL_OK = set()
FORBIDDEN_FLAGS = ("isRestrictedLegendary", "isSubLegendary", "isMythical", "isParadox", "isUltraBeast",
                   "isMegaEvolution", "isPrimalReversion", "isGigantamax", "isTotem", "isTeraForm", "isUltraBurst")
REGIONAL_FLAGS = ("isAlolanForm", "isGalarianForm", "isHisuianForm", "isPaldeanForm")

# Earliest segment in which the player reaches each area (docs/hack_trainers.md; round 1 story order).
# Exact map names first, then prefixes.
WILD_SEGMENTS = [
    ("MAP_METEOR_FALLS_1F_1R", "S4"), ("MAP_METEOR_FALLS_STEVENS_CAVE", "POST"),
    ("MAP_DRACONID_PASS", "S1"),
    ("MAP_ROUTE101", "S1"), ("MAP_ROUTE102", "S1"), ("MAP_ROUTE103", "S1"), ("MAP_ROUTE104", "S1"),
    ("MAP_PETALBURG_WOODS", "S1"), ("MAP_ROUTE116", "S1"), ("MAP_PETALBURG_CITY", "S1"),
    ("MAP_RUSTURF_TUNNEL", "S2"), ("MAP_GRANITE_CAVE", "S2"), ("MAP_ROUTE115", "S2"), ("MAP_DEWFORD_TOWN", "S2"),
    ("MAP_ROUTE110", "S3"), ("MAP_ROUTE117", "S3"), ("MAP_ROUTE118", "S3"), ("MAP_SLATEPORT_CITY", "S3"),
    ("MAP_ROUTE111", "S4"), ("MAP_ROUTE112", "S4"), ("MAP_ROUTE113", "S4"), ("MAP_ROUTE114", "S4"),
    ("MAP_FIERY_PATH", "S4"), ("MAP_JAGGED_PASS", "S4"),
    ("MAP_MIRAGE_TOWER", "S5"),
    ("MAP_ROUTE105", "S6"), ("MAP_ROUTE106", "S6"), ("MAP_ROUTE107", "S6"), ("MAP_ROUTE108", "S6"),
    ("MAP_ROUTE109", "S6"), ("MAP_ROUTE119", "S6"), ("MAP_NEW_MAUVILLE", "S6"), ("MAP_ABANDONED_SHIP", "S6"),
    ("MAP_METEOR_FALLS", "S6"),
    ("MAP_ROUTE12", "S7"), ("MAP_ROUTE13", "S7"), ("MAP_MT_PYRE", "S7"), ("MAP_LILYCOVE_CITY", "S7"),
    ("MAP_SAFARI_ZONE", "S7"), ("MAP_MAGMA_HIDEOUT", "S7"), ("MAP_SHOAL_CAVE", "S7"), ("MAP_MOSSDEEP_CITY", "S7"),
    ("MAP_PACIFIDLOG_TOWN", "S7"),
    ("MAP_UNDERWATER", "S8"), ("MAP_SEAFLOOR_CAVERN", "S8"), ("MAP_CAVE_OF_ORIGIN", "S8"),
    ("MAP_SOOTOPOLIS_CITY", "S8"), ("MAP_SKY_PILLAR", "S8"),
    ("MAP_VICTORY_ROAD", "S9"), ("MAP_EVER_GRANDE_CITY", "S9"),
    ("MAP_DESERT_UNDERPASS", "POST"), ("MAP_ARTISAN_CAVE", "POST"), ("MAP_ALTERING_CAVE", "POST"),
]
# The method can make a table later than its area: Surf (5th badge), Dive (7th), Rock Smash (3rd badge),
# the Old Rod (Dewford), Good Rod (Route 118), Super Rod (Mossdeep).
METHOD_SEGMENT = {"water_mons": "S6", "rock_smash_mons": "S4", "old_rod": "S2", "good_rod": "S3", "super_rod": "S7"}
DIVE_SEGMENT = "S8"
# Maps the hack added (D-300): their tables have no vanilla counterpart, so every slot is new.
HACK_MAPS = {"MAP_DRACONID_PASS"}


def cpp_command():
    for exe in ("arm-none-eabi-cpp", "cpp"):
        if shutil.which(exe):
            return exe
    sys.exit("check_wild.py: needs arm-none-eabi-cpp or cpp")


def species_aliases():
    """SPECIES_* constant -> canonical name (aliases such as SPECIES_SHELLOS = SPECIES_SHELLOS_WEST resolved)."""
    text = open(os.path.join(ROOT, "include/constants/species.h")).read()
    alias = {}
    for name, value in re.findall(r"\b(SPECIES_\w+)\s*=\s*([^,\n]+),", text):
        value = value.strip()
        alias[name] = value if value.startswith("SPECIES_") else name
    for name in re.findall(r"#define (SPECIES_\w+)", text):
        alias.setdefault(name, name)

    def resolve(name):
        seen = set()
        while name in alias and alias[name] != name and name not in seen:
            seen.add(name)
            name = alias[name]
        return name
    return {name: resolve(name) for name in alias}


def load_species():
    """Canonical SPECIES_* -> dict of the fields the checks need, for every species this build compiles."""
    src = '#include "global.h"\n#include "data/pokemon/species_info.h"\n'
    out = subprocess.run([cpp_command(), "-P", "-iquote", "include", "-iquote", "src", "-DMODERN=1", "-DTESTING=0",
                          "-DEMERALD", "-std=gnu17", "-"], cwd=ROOT, input=src, capture_output=True, text=True)
    if out.returncode:
        sys.exit("check_wild.py: preprocessing src/data/pokemon/species_info.h failed:\n" + out.stderr[:2000])
    text = out.stdout
    start = text.index("const struct SpeciesInfo gSpeciesInfo[] =")
    body = text[text.index("{", start) + 1:]
    species, depth, i = {}, 0, 0
    entry = re.compile(r"\s*\[(SPECIES_\w+)\]\s*=\s*")
    while True:
        m = entry.match(body, i)
        if not m:
            nxt = body.find("[SPECIES_", i)
            if nxt < 0 or body.find("};", i) < nxt:
                break
            i = nxt
            continue
        j = m.end()
        assert body[j] == "{", body[j:j + 40]
        depth, k = 0, j
        while True:
            c = body[k]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    break
            k += 1
        species[m.group(1)] = parse_entry(body[j:k + 1])
        i = k + 1
    return species


def parse_entry(text):
    def field(name, default=None):
        m = re.search(r"\.%s\s*=\s*([^,}]+)" % name, text)
        return m.group(1).strip() if m else default
    types = re.search(r"\.types\s*=\s*\{([^{}]*)\}", text)
    info = {
        "name": (re.search(r'\.speciesName\s*=\s*_\("([^"]*)"\)', text) or [None, "?"])[1],
        "types": list(dict.fromkeys(c_value(v) for v in split_top(types.group(1)))) if types else [],
        "natDexNum": field("natDexNum", "NATIONAL_DEX_NONE"),
        "frontPic": field("frontPic"),
        "cryId": field("cryId", "CRY_NONE"),
        "levelUpLearnset": field("levelUpLearnset"),
        "catchRate": field("catchRate"),
        "evolutions": re.findall(r"\{\s*(EVO_\w+)\s*,\s*([^,]+?)\s*,\s*(SPECIES_\w+)", field_block(text, "evolutions")),
        "flags": {f for f in FORBIDDEN_FLAGS + REGIONAL_FLAGS if re.search(r"\.%s\s*=\s*(1|TRUE)\b" % f, text)},
    }
    return info


def split_top(text):
    """Split a C initializer list at top-level commas."""
    parts, depth, cur = [], 0, ""
    for c in text:
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == "," and depth == 0:
            parts.append(cur.strip())
            cur = ""
        else:
            cur += c
    if cur.strip():
        parts.append(cur.strip())
    return parts


def c_value(expr):
    """A preprocessed constant expression: '(8 >= 5 ? TYPE_FAIRY : TYPE_GRASS)' -> 'TYPE_FAIRY'."""
    expr = expr.strip()
    while expr.startswith("(") and expr.endswith(")"):
        expr = expr[1:-1].strip()
    m = re.match(r"^([^?]*)\?(.*?):(.*)$", expr)
    if not m:
        return expr
    try:
        taken = bool(eval(re.sub(r"!(?!=)", " not ", m.group(1).replace("&&", " and ").replace("||", " or "))))
    except Exception:
        taken = True
    return c_value(m.group(2) if taken else m.group(3))


def field_block(text, name):
    m = re.search(r"\.%s\s*=" % name, text)
    if not m:
        return ""
    i = text.index("{", m.end())
    depth = 0
    for k in range(i, len(text)):
        if text[k] == "{":
            depth += 1
        elif text[k] == "}":
            depth -= 1
            if depth == 0:
                return text[i:k + 1]
    return ""


def national_numbers():
    text = open(os.path.join(ROOT, "include/constants/pokedex.h")).read()
    body = re.search(r"enum NationalDexOrder\s*\{(.*?)\};", text, re.S).group(1)
    names = re.findall(r"\b(NATIONAL_DEX_\w+)", body)
    return {n: i for i, n in enumerate(names)}


GEN_STARTS = [(906, 9), (810, 8), (722, 7), (650, 6), (494, 5), (387, 4), (252, 3), (152, 2), (1, 1)]


def generation(num):
    for first, gen in GEN_STARTS:
        if num >= first:
            return gen
    return 0


def parents_of(species):
    """child -> (parent, method, param) for level-up evolution checks (check_party.min_level's format)."""
    draconid = {k: v for k, v in re.findall(r"#define (DRACONID_\w+)\s+(\d+)",
                                            open(os.path.join(ROOT, "include/constants/draconid.h")).read())}
    parents = {}
    for sp, info in species.items():
        for method, param, child in info["evolutions"]:
            parents.setdefault(child, (sp, method, draconid.get(param.strip(), param.strip())))
    return parents


def min_level(sp, parents):
    lv, cur, seen = 1, sp, set()
    while cur in parents and cur not in seen:
        seen.add(cur)
        par, method, param = parents[cur]
        if method in ("EVO_LEVEL", "EVO_LEVEL_FEMALE", "EVO_LEVEL_MALE", "EVO_LEVEL_DAY", "EVO_LEVEL_NIGHT") \
                and param.isdigit():
            lv = max(lv, int(param))
        cur = par
    return lv


def load_vanilla(path):
    if path:
        return json.load(open(path))
    out = subprocess.run(["git", "-C", ROOT, "show", "master:src/data/wild_encounters.json"],
                         capture_output=True, text=True)
    if out.returncode:
        return None
    return json.loads(out.stdout)


def is_hoenn(group, enc):
    return group["label"] == "gWildMonHeaders" and not re.search(r"_(FireRed|LeafGreen)$", enc["base_label"])


def area_segment(mapname):
    for prefix, seg in WILD_SEGMENTS:
        if mapname == prefix or mapname.startswith(prefix):
            return seg
    return None


def slot_methods(group):
    """field type -> list of method keys per slot (fishing slots are split by rod)."""
    methods = {}
    for f in group["fields"]:
        n = len(f["encounter_rates"])
        if "groups" in f:
            per = [None] * n
            for rod, idx in f["groups"].items():
                for i in idx:
                    per[i] = rod
            methods[f["type"]] = per
        else:
            methods[f["type"]] = [f["type"]] * n
    return methods


def later(a, b):
    return a if ORDER.index(a) >= ORDER.index(b) else b


def pretty_map(mapname):
    words = mapname[len("MAP_"):].split("_")
    out = []
    for w in words:
        m = re.match(r"([A-Z]+)(\d+)$", w)
        if m and m.group(1) in ("ROUTE",):
            out.append("Route %s" % m.group(2))
        elif re.match(r"^(B?\d+F|\d+R)$", w):
            out.append(w)
        else:
            out.append(w.capitalize())
    return " ".join(out)


def pretty_species(sp):
    return sp[len("SPECIES_"):].replace("_", " ").title()


FIELD_NAME = {"land_mons": "Land", "water_mons": "Surf", "rock_smash_mons": "Rock Smash", "fishing_mons": "Fishing"}
ROD_NAME = {"old_rod": "Old Rod", "good_rod": "Good Rod", "super_rod": "Super Rod"}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--changes", action="store_true", help="print the slots that differ from vanilla (Markdown)")
    ap.add_argument("--doc", action="store_true", help="rewrite the table at the end of docs/hack_wild.md")
    ap.add_argument("--info", nargs="+", metavar="SPECIES")
    ap.add_argument("--vanilla", help="vanilla wild_encounters.json (default: git show master:...)")
    ap.add_argument("--wild", default=WILD, help="the tables to check (default src/data/wild_encounters.json)")
    args = ap.parse_args()

    alias = species_aliases()
    species = load_species()
    natnum = national_numbers()
    parents = parents_of(species)

    def canon(sp):
        return alias.get(sp, sp)

    if args.info:
        for name in args.info:
            sp = canon("SPECIES_" + name.upper().replace(" ", "_").replace("-", "_") if not name.startswith("SPECIES_")
                       else name)
            if sp not in species:
                print("%s: not in this build" % name)
                continue
            s = species[sp]
            num = natnum.get(s["natDexNum"], 0)
            print("%s (%s): #%d gen %d, %s, catch rate %s, flags %s" % (
                sp, s["name"], num, generation(num), "/".join(t[5:].title() for t in s["types"]), s["catchRate"],
                ",".join(sorted(s["flags"])) or "-"))
            print("   evolves: %s; from: %s; min level %d" % (
                ", ".join("%s %s -> %s" % (m[4:], p, c[8:]) for m, p, c in s["evolutions"]) or "-",
                parents[sp][0][8:] if sp in parents else "-", min_level(sp, parents)))
        return

    data = json.load(open(args.wild))
    vanilla = load_vanilla(args.vanilla)
    caps = build_segments.read_caps()
    errors = warnings = 0

    def err(msg):
        nonlocal errors
        print("ERROR   " + msg)
        errors += 1

    def warn(msg):
        nonlocal warnings
        print("WARNING " + msg)
        warnings += 1

    vtables = {}
    vrates = {}  # field type -> the encounter rates vanilla Hoenn tables use (for the hack's new tables)
    if vanilla is None:
        warn("no vanilla wild_encounters.json (master branch missing): vanilla comparisons skipped")
    else:
        for g in vanilla["wild_encounter_groups"]:
            for e in g["encounters"]:
                vtables[(g["label"], e["base_label"])] = e
                if "fields" in g and is_hoenn(g, e):
                    for ftype, mons in ((k, v) for k, v in e.items() if k.endswith("_mons")):
                        vrates.setdefault(ftype, set()).add(mons.get("encounter_rate"))

    changes = []
    hack_tables = set()  # base labels of the tables of maps the hack added
    now_species = set()
    for g in data["wild_encounter_groups"]:
        if "fields" not in g:  # Battle Pyramid / Pike: their rates live in the C code
            for e in g["encounters"]:
                if vanilla is not None and vtables.get((g["label"], e["base_label"])) != e:
                    err("%s: not a Hoenn table, must stay vanilla" % e["base_label"])
            continue
        methods = slot_methods(g)
        rates = {f["type"]: f["encounter_rates"] for f in g["fields"]}
        for e in g["encounters"]:
            key = (g["label"], e["base_label"])
            ve = vtables.get(key)
            hoenn = is_hoenn(g, e)
            if not hoenn:
                if vanilla is not None and ve != e:
                    err("%s: not a Hoenn table, must stay vanilla" % e["base_label"])
                continue
            mapname = e.get("map", "")
            seg = area_segment(mapname) if hoenn else None
            if hoenn and seg is None:
                err("%s (%s): no segment in WILD_SEGMENTS" % (e["base_label"], mapname))
                seg = "POST"
            hack_only = mapname in HACK_MAPS
            if vanilla is not None and hack_only and ve is not None:
                err("%s (%s): in HACK_MAPS, but vanilla has this table" % (e["base_label"], mapname))
            if vanilla is not None and not hack_only and ve is None:
                err("%s (%s): no vanilla counterpart (a table for a map the hack added goes in HACK_MAPS)" % (
                    e["base_label"], mapname))
            if hack_only:
                hack_tables.add(e["base_label"])
            for ftype, mons in ((k, v) for k, v in e.items() if k.endswith("_mons")):
                where = "%s %s" % (e["base_label"], ftype)
                vmons = ve.get(ftype) if ve else None
                if len(mons["mons"]) != len(rates[ftype]):
                    err("%s: %d slots, the field has %d" % (where, len(mons["mons"]), len(rates[ftype])))
                if vmons and mons.get("encounter_rate") != vmons.get("encounter_rate"):
                    err("%s: encounter rate changed (%s -> %s)" % (where, vmons.get("encounter_rate"),
                                                                    mons.get("encounter_rate")))
                if hack_only and vanilla is not None and mons.get("encounter_rate") not in vrates.get(ftype, ()):
                    err("%s: encounter rate %s, vanilla Hoenn tables use %s" % (
                        where, mons.get("encounter_rate"), sorted(vrates.get(ftype, ()))))
                if ve is not None and vmons is None:
                    err("%s: a field vanilla's table doesn't have" % where)
                if vmons:
                    lost = {canon(m["species"]) for m in vmons["mons"]} - {canon(m["species"]) for m in mons["mons"]}
                    for sp in sorted(lost):
                        warn("%s: %s no longer in this table (new species take duplicate slots)" % (where, sp))
                for i, mon in enumerate(mons["mons"]):
                    sp = canon(mon["species"])
                    lo, hi = mon["min_level"], mon["max_level"]
                    slot = "%s slot %d (%s Lv%d-%d)" % (where, i, mon["species"], lo, hi)
                    if hoenn:
                        now_species.add(sp)
                    if sp not in species:
                        err("%s: species unknown or not enabled in this build" % slot)
                        continue
                    s = species[sp]
                    if not s["frontPic"] or s["cryId"] == "CRY_NONE" or not s["levelUpLearnset"] \
                            or s["levelUpLearnset"] == "sNoneLevelUpLearnset":
                        err("%s: no front pic, cry or level-up learnset" % slot)
                    bad = s["flags"] & set(FORBIDDEN_FLAGS)
                    if bad:
                        err("%s: %s" % (slot, ", ".join(sorted(bad))))
                    if s["flags"] & set(REGIONAL_FLAGS) and sp not in REGIONAL_OK:
                        err("%s: regional form (D-193)" % slot)
                    if not 1 <= lo <= hi <= 100:
                        err("%s: levels out of order" % slot)
                    vmon = vmons["mons"][i] if vmons and i < len(vmons["mons"]) else None
                    if vmon == mon:
                        continue
                    method = methods[ftype][i]
                    mseg = DIVE_SEGMENT if (ftype == "water_mons" and mapname.startswith("MAP_UNDERWATER")) \
                        else METHOD_SEGMENT.get(method, seg)
                    eff = later(seg, mseg)
                    keeps_levels = vmon is not None and (vmon["min_level"], vmon["max_level"]) == (lo, hi)
                    if not keeps_levels and hi > caps[eff] + LEVEL_MARGIN:
                        err("%s: above the %s cap %d + %d" % (slot, eff, caps[eff], LEVEL_MARGIN))
                    if vmon is None or canon(vmon["species"]) != sp:
                        ml = min_level(sp, parents)
                        if lo < ml:
                            err("%s: its line evolves into it at Lv%d" % (slot, ml))
                    changes.append((e, ftype, i, rates[ftype][i], method, vmon, mon))

    # every vanilla Hoenn species is still wild somewhere
    if vanilla is not None:
        before = set()
        for g in vanilla["wild_encounter_groups"]:
            for e in g["encounters"]:
                if is_hoenn(g, e):
                    for ftype, mons in ((k, v) for k, v in e.items() if k.endswith("_mons")):
                        before |= {canon(m["species"]) for m in mons["mons"]}
        for sp in sorted(before - now_species):
            err("%s: was wild in vanilla Hoenn, no Hoenn table has it now" % sp)

    # Beldum at 1% in every Granite Cave land table
    for g in data["wild_encounter_groups"]:
        if g["label"] != "gWildMonHeaders":
            continue
        rates = {f["type"]: f["encounter_rates"] for f in g["fields"]}
        for e in g["encounters"]:
            if not e.get("map", "").startswith("MAP_GRANITE_CAVE") or "land_mons" not in e:
                continue
            mons = e["land_mons"]["mons"]
            one = [i for i, r in enumerate(rates["land_mons"]) if r == 1]
            others = [m for m in mons if canon(m["species"]) != BELDUM]
            lo, hi = min(m["min_level"] for m in others), max(m["max_level"] for m in others)
            hits = [i for i, m in enumerate(mons) if canon(m["species"]) == BELDUM]
            if not hits:
                err("%s: no Beldum" % e["base_label"])
            for i in hits:
                if i not in one:
                    err("%s slot %d: Beldum outside a 1%% slot" % (e["base_label"], i))
                if not lo <= mons[i]["min_level"] <= mons[i]["max_level"] <= hi:
                    err("%s slot %d: Beldum Lv%d-%d outside the floor's Lv%d-%d" % (
                        e["base_label"], i, mons[i]["min_level"], mons[i]["max_level"], lo, hi))

    if args.changes or args.doc:
        def name(sp):
            sp = canon(sp)
            return species[sp]["name"] if sp in species else pretty_species(sp)

        def levels(mon):
            return "%d" % mon["min_level"] if mon["min_level"] == mon["max_level"] else \
                "%d–%d" % (mon["min_level"], mon["max_level"])

        per_map = {}  # vanilla tables: the changed slots
        new_tables = {}  # tables of maps the hack added: every slot, grouped by field / rod
        for e, ftype, i, rate, method, vmon, mon in changes:
            table = FIELD_NAME[ftype] if method not in ROD_NAME else ROD_NAME[method]
            if e["base_label"] in hack_tables:
                parts = new_tables.setdefault(e["base_label"], (pretty_map(e["map"]), {}))[1]
                parts.setdefault(table, []).append("%s %s (%d%%)" % (name(mon["species"]), levels(mon), rate))
                continue
            old = name(vmon["species"]) if vmon else "–"
            per_map.setdefault(e["base_label"], (pretty_map(e["map"]), []))[1].append(
                "%s %d (%d%%): %s → **%s** %s" % (table, i, rate, old, name(mon["species"]), levels(mon)))
        groups = {}
        for label, (area, items) in per_map.items():
            groups.setdefault("; ".join(items), []).append(area)
        lines = ["| Area | Slot (rate): vanilla → new, levels |", "|---|---|"]
        for items, areas in groups.items():
            lines.append("| %s | %s |" % (", ".join(areas), items))
        new_lines = ["| Area | Table | Species, levels (rate) |", "|---|---|---|"]
        for label, (area, parts) in new_tables.items():
            for table, items in parts.items():
                new_lines.append("| %s | %s | %s |" % (area, table, ", ".join(items)))
        if args.changes:
            if new_tables:
                print("\n".join(new_lines) + "\n")
            print("\n".join(lines))
            return
        n_vanilla = sum(1 for c in changes if c[0]["base_label"] not in hack_tables)
        text = open(DOC).read()
        head = text.index(DOC_HEADING)
        body = [DOC_HEADING, "<!-- generated by tools/hack/check_wild.py --doc -->", ""]
        if new_tables:
            body += ["New tables for maps the hack added (`HACK_MAPS`; every level within the area's cap + %d):"
                     % LEVEL_MARGIN, ""] + new_lines + [""]
        body += ["%d slots in %d vanilla tables changed (every slot keeps its vanilla levels)." % (
                 n_vanilla, len(per_map)), ""] + lines + [""]
        open(DOC, "w").write(text[:head] + "\n".join(body))
        print("wrote %s (%d rows)" % (os.path.relpath(DOC, ROOT), len(groups) + len(new_lines) - 2))
        return

    new = {canon(m["species"]) for _, _, _, _, _, v, m in changes if not v or canon(v["species"]) != canon(m["species"])}
    n_new = sum(1 for c in changes if c[0]["base_label"] in hack_tables)
    print("%d Hoenn slot(s) changed in vanilla tables, %d slot(s) in %d new table(s), %d species added by the hack" % (
        len(changes) - n_new, n_new, len(hack_tables), len(new - set(
        canon(m["species"]) for g in (vanilla or data)["wild_encounter_groups"] for e in g["encounters"]
        if is_hoenn(g, e) for k, v in e.items() if k.endswith("_mons") for m in v["mons"]))))
    print("%d error(s), %d warning(s)" % (errors, warnings))
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
