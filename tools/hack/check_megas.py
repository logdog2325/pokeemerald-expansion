#!/usr/bin/env python3
"""
check_megas.py - every Mega Stone and Z-Crystal of the build: who can use it and where the player gets it
(round 1, feedback 1.33 and 2.5; D-221, D-222, D-320 - D-325; docs/hack_items.md "## Mega Stones").

  python3 tools/hack/check_megas.py              # the report; exit 1 on an error
  python3 tools/hack/check_megas.py --problems   # only the stones and crystals with an error or a note
  python3 tools/hack/check_megas.py --write      # regenerate the post-game lists in battle_items.pory

Mega Stones are the items with HOLD_EFFECT_MEGA_STONE in src/data/items.h, Z-Crystals those with
HOLD_EFFECT_Z_CRYSTAL (type crystals have a TYPE_* secondaryId; a species crystal's Pokémon come from
sSignatureZMoves in src/battle_z_move.c), so a stone or crystal the build adds later is picked up. For each:
  - the Pokémon that Mega Evolves with the stone (FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM in
    src/data/pokemon/form_change_tables.h) and its line: every species linked to it by evolutions (an
    evolution that only happens in another region, IF_REGION, doesn't link);
  - whether and when the player can get the line: the Hoenn wild tables (src/data/wild_encounters.json; the
    area's segment from MAP_WHEN or check_wild.py's WILD_SEGMENTS, later for Surf / Dive / rods), givemon /
    giveegg / setwildbattle / ingame_trade in the event scripts (the map's segment or SCRIPT_WHEN; gifts a
    flag holds back until later in GIFT_WHEN) and the C-code sources in EXTRA_SOURCES (the roaming Latis);
  - its sources: item balls and hidden items (map.json), giveitem / finditem in the scripts (also a stone
    put into a var that giveitem hands over) and the battle item counter (data/scripts/draconid/
    battle_items.pory: Draconid_BattleItems_TierN = BATTLE_ITEMS_TIER_N_BADGES badges, the *_PostGame
    lists after the Champion).
"When" is a story segment: S1 ... S9 (tools/hack/trainers/build_segments.py), POST = after the Champion
(FLAG_IS_CHAMPION, set at the Hall of Fame); "?" = not known (add the map or file to MAP_WHEN / SCRIPT_WHEN).

Errors (exit 1):
  - a stone whose line the player can get before the post-game has no source before the post-game
  - a stone or crystal missing from the post-game lists, or the lists differ from what --write makes
    (the stones in National Dex order of their Pokémon, X before Y, a second Mega form's stone after the first;
    the 18 type crystals in type order, then the species crystals)
  - a stone or crystal with price 0 (a mart sells a 0-price item for nothing, up to 999 at once)
  - a stone source before the Mega Ring (Jagged Pass, Act 3: segment S4; D-221)
  - a Pokémon gift or a stone source whose "when" is unknown
Notes: a line the player can get only with an evolution item that has no source in the game (PENDING_ITEM_BALLS
lists spots another branch adds); a stone placed in the story whose line only comes in the post-game; how many type
crystals have a story source.
"""

import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(ROOT, "tools/hack"))
import check_wild as cw  # noqa: E402

ORDER = cw.ORDER
POST = "POST"
UNKNOWN = "?"
MEGA_RING = "S4"  # Aster gives the Mega Ring on Jagged Pass (Act 3, D-221)
ITEMS_H = os.path.join(ROOT, "src/data/items.h")
ITEMS_ENUM = os.path.join(ROOT, "include/constants/items.h")
FORM_TABLES = os.path.join(ROOT, "src/data/pokemon/form_change_tables.h")
Z_MOVES = os.path.join(ROOT, "src/battle_z_move.c")
TRADES = os.path.join(ROOT, "src/data/trade.h")
DRACONID_H = os.path.join(ROOT, "include/constants/draconid.h")
COUNTER = os.path.join(ROOT, "data/scripts/draconid/battle_items.pory")
COUNTER_STONES = "Draconid_MegaStones_PostGame"
COUNTER_CRYSTALS = "Draconid_ZCrystals_PostGame"
WRITE_BEGIN = "// BEGIN check_megas.py --write"
WRITE_END = "// END check_megas.py --write"

# When the player first reaches an area, where it differs from check_wild.py's WILD_SEGMENTS (those place the
# wild levels) or isn't in it (towns, buildings, story caves). Exact names first, then prefixes.
MAP_WHEN = [
    ("MAP_SAFARI_ZONE_NORTHEAST", POST),   # the Johto areas: construction workers until the Hall of Fame
    ("MAP_SAFARI_ZONE_SOUTHEAST", POST),   # (FLAG_HIDE_SAFARI_ZONE_SOUTH_CONSTRUCTION_WORKERS)
    ("MAP_SKY_PILLAR", POST),              # the finale opens it after the Hall of Fame (progression leg 6.10)
    ("MAP_DRACONID_VILLAGE", "S1"), ("MAP_DRACONID_PASS", "S1"), ("MAP_LITTLEROOT_TOWN", "S1"),
    ("MAP_OLDALE_TOWN", "S1"), ("MAP_RUSTBORO_CITY", "S1"), ("MAP_MAUVILLE_CITY", "S3"),
    ("MAP_VERDANTURF_TOWN", "S3"), ("MAP_FALLARBOR_TOWN", "S4"), ("MAP_LAVARIDGE_TOWN", "S4"),
    ("MAP_FORTREE_CITY", "S6"), ("MAP_AQUA_HIDEOUT", "S8"),
    ("MAP_DESERT_RUINS", "S8"), ("MAP_ISLAND_CAVE", "S8"), ("MAP_ANCIENT_TOMB", "S8"),  # the Regis: Dive
    ("MAP_BATTLE_FRONTIER", POST), ("MAP_SOUTHERN_ISLAND", POST), ("MAP_MARINE_CAVE", POST),
    ("MAP_TERRA_CAVE", POST), ("MAP_NAVEL_ROCK", POST), ("MAP_BIRTH_ISLAND", POST), ("MAP_FARAWAY_ISLAND", POST),
]
# Event scripts outside data/maps (file name without extension) -> when their gifts happen.
SCRIPT_WHEN = {
    "act1": "S1", "act2": "S2", "act3": "S4", "act4": "S5", "act5": "S8", "act6": "S9", "act7": POST, "act7x": POST,
    "second_starter": "S2",   # Prof. Oak, after the Stone Badge (D-233)
    "kecleon": "S6",          # the Devon Scope Kecleon of Routes 119 / 120
    "lance": POST, "frontier_legends": POST,
}
# A gift a flag holds back past its map's segment: (map folder or script name, species) -> (when, why).
GIFT_WHEN = {
    ("LittlerootTown_ProfessorBirchsLab", "SPECIES_CYNDAQUIL"): (POST, "Birch's Johto starters"),
    ("LittlerootTown_ProfessorBirchsLab", "SPECIES_TOTODILE"): (POST, "Birch's Johto starters"),
    ("LittlerootTown_ProfessorBirchsLab", "SPECIES_CHIKORITA"): (POST, "Birch's Johto starters"),
    ("MossdeepCity_StevensHouse", "SPECIES_BELDUM"): (POST, "Steven's Beldum (shown at the Hall of Fame)"),
}
# Pokémon the C code hands out: (species, when, how).
EXTRA_SOURCES = [
    ("SPECIES_LATIAS", POST, "roams Hoenn after the finale (special InitRoamer, DraconidVillage_PlayersHouse_1F)"),
    ("SPECIES_LATIOS", POST, "roams Hoenn after the finale (special InitRoamer, DraconidVillage_PlayersHouse_1F)"),
]
# Item balls another branch is adding, so the evolution-item note knows them before the merge (the main session's
# Dawn / Dusk Stone task; the map.json scan finds them once both branches are in, and this can go): item -> spots.
PENDING_ITEM_BALLS = {
    "ITEM_DAWN_STONE": [("MAP_ABANDONED_SHIP_ROOMS_1F", 4, 5), ("MAP_VICTORY_ROAD_1F", 40, 26)],
    "ITEM_DUSK_STONE": [("MAP_MT_PYRE_EXTERIOR", 27, 15), ("MAP_MT_PYRE_EXTERIOR", 16, 22)],  # a ball, a hidden item
}
# Scripts that never reach the player in this ROM.
SKIP_SCRIPT = re.compile(r"(^|/)(debug\.inc|debug_jumps\w*\.(inc|pory)|gift_\w+\.inc|script_cmd_table\.inc|\w+_frlg\.inc)$|_Frlg/")

GIFT_MON = re.compile(r"\b(givemon|giveegg|givecustommon|setwildbattle)\b[\s(]+(\w+)")
TRADE = re.compile(r"\bingame_trade\b[\s(]+(INGAME_TRADE_\w+)")
GIVE_ITEM = re.compile(r"\b(giveitem|finditem|additem)\b[\s(]+(ITEM_\w+)")
GIVE_VAR = re.compile(r"\bgiveitem\b[\s(]+(VAR_\w+)")
SET_VAR_ITEM = re.compile(r"\bsetvar\b[\s(]+(VAR_\w+)\s*,\s*(ITEM_\w+)")


def idx(when):
    """Order of a segment; an unknown one sorts with the first (as early as it could be)."""
    return ORDER.index(when) if when in ORDER else 0


def map_when(mapname):
    for prefix, when in MAP_WHEN:
        if mapname == prefix:
            return when
    for prefix, when in MAP_WHEN:
        if mapname.startswith(prefix):
            return when
    return cw.area_segment(mapname) or UNKNOWN


def nice(const):
    """ITEM_CHARIZARDITE_X / SPECIES_MR_MIME -> "Charizardite X" / "Mr Mime"."""
    return const.split("_", 1)[1].replace("_", " ").title()


# ---------------------------------------------------------------------------
# Items
# ---------------------------------------------------------------------------

def load_items():
    """ITEM_* -> {name, price (int or None), hold, secondary, id} for every Mega Stone and Z-Crystal."""
    text = open(ITEMS_H).read()
    defines = {k: int(v) for k, v in re.findall(r"#define (\w+)\s+(\d+)\s*$", text, re.M)}
    ids = {k: int(v) for k, v in re.findall(r"\b(ITEM_\w+)\s*=\s*(\d+)\s*,", open(ITEMS_ENUM).read())}
    items = {}
    for m in re.finditer(r"\[(ITEM_\w+)\]\s*=\s*\{(.*?)\n    \},", text, re.S):
        body = m.group(2)
        hold = re.search(r"\.holdEffect\s*=\s*(HOLD_EFFECT_\w+)", body)
        if not hold or hold.group(1) not in ("HOLD_EFFECT_MEGA_STONE", "HOLD_EFFECT_Z_CRYSTAL"):
            continue
        price = re.search(r"\.price\s*=\s*(\w+)", body)
        value = None
        if price:
            value = int(price.group(1)) if price.group(1).isdigit() else defines.get(price.group(1))
        sec = re.search(r"\.secondaryId\s*=\s*(\w+)", body)
        name = re.search(r'\.name\s*=\s*ITEM_NAME\("([^"]*)"\)', body)
        items[m.group(1)] = {"name": name.group(1) if name else nice(m.group(1)), "price": value,
                             "price_expr": price.group(1) if price else "?", "hold": hold.group(1),
                             "secondary": sec.group(1) if sec else None, "id": ids.get(m.group(1), 1 << 20)}
    return items


def mega_forms():
    """stone -> [(form change table, mega species)] from form_change_tables.h."""
    text = open(FORM_TABLES).read()
    stones = {}
    for m in re.finditer(r"static const struct FormChange (s\w+FormChangeTable)\[\]\s*=\s*\{(.*?)\};", text, re.S):
        for mega, item in re.findall(r"FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM\s*,\s*(SPECIES_\w+)\s*,\s*(ITEM_\w+)",
                                     m.group(2)):
            stones.setdefault(item, []).append((m.group(1), mega))
    return stones


def signature_species():
    """species crystal -> species that use it (sSignatureZMoves)."""
    text = open(Z_MOVES).read()
    body = re.search(r"sSignatureZMoves\[\]\s*=\s*\{(.*?)\};", text, re.S).group(1)
    users = {}
    for sp, item in re.findall(r"\{\s*(SPECIES_\w+)\s*,\s*(ITEM_\w+)", body):
        users.setdefault(item, []).append(sp)
    return users


# ---------------------------------------------------------------------------
# Species: lines and where the player gets them
# ---------------------------------------------------------------------------

def load_species():
    """check_wild.load_species plus each species' form change table and its evolutions with conditions."""
    plain = cw.parse_entry

    def parse_entry(text):
        info = plain(text)
        m = re.search(r"\.formChangeTable\s*=\s*(\w+)", text)
        info["formChangeTable"] = m.group(1) if m else None
        evos = []
        block = cw.field_block(text, "evolutions")
        for part in re.split(r"(?=\{\s*EVO_)", block):
            e = re.match(r"\{\s*(EVO_\w+)\s*,\s*([^,]+?)\s*,\s*(SPECIES_\w+)", part)
            if e:
                evos.append((e.group(1), e.group(2), e.group(3), "IF_REGION" in re.sub(r"IF_NOT_REGION", "", part)))
        info["evos"] = evos
        return info

    cw.parse_entry = parse_entry
    try:
        return cw.load_species()
    finally:
        cw.parse_entry = plain


def families(species):
    """species -> frozenset of its line (undirected evolution links; other-region evolutions don't link)."""
    parent = {sp: sp for sp in species}

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    for sp, info in species.items():
        for _method, _param, child, other_region in info["evos"]:
            if child in parent and not other_region:
                parent[find(sp)] = find(child)
    groups = {}
    for sp in species:
        groups.setdefault(find(sp), set()).add(sp)
    return {sp: frozenset(groups[find(sp)]) for sp in species}


def script_files():
    """(path, owner, when) for every event script the player can meet; a .pory hides its generated .inc."""
    files = []
    for path in sorted(glob.glob(os.path.join(ROOT, "data/**/*.pory"), recursive=True) +
                       glob.glob(os.path.join(ROOT, "data/**/*.inc"), recursive=True)):
        rel = os.path.relpath(path, ROOT)
        if SKIP_SCRIPT.search(rel) or (path.endswith(".inc") and os.path.exists(path[:-4] + ".pory")):
            continue
        parts = rel.split(os.sep)
        if parts[1] == "maps" and len(parts) >= 4:
            owner = parts[2]
            try:
                mapname = json.load(open(os.path.join(ROOT, "data/maps", owner, "map.json")))["id"]
            except (OSError, KeyError, ValueError):
                mapname = ""
            when = map_when(mapname) if mapname else UNKNOWN
        else:
            owner = os.path.splitext(parts[-1])[0]
            when = SCRIPT_WHEN.get(owner, UNKNOWN)
        files.append((path, rel, owner, when))
    return files


def mon_sources(species, alias, scripts):
    """canonical species -> [(when, how)]."""
    out = {}

    def add(sp, when, how):
        sp = alias.get(sp, sp)
        out.setdefault(sp, []).append((when, how))

    data = json.load(open(cw.WILD))
    for g in data["wild_encounter_groups"]:
        if "fields" not in g:
            continue
        methods = cw.slot_methods(g)
        for e in g["encounters"]:
            if not cw.is_hoenn(g, e):
                continue
            mapname = e.get("map", "")
            seg = map_when(mapname)
            for ftype, mons in ((k, v) for k, v in e.items() if k.endswith("_mons")):
                for i, mon in enumerate(mons["mons"]):
                    method = methods[ftype][i]
                    if ftype == "water_mons" and mapname.startswith("MAP_UNDERWATER"):
                        mseg = cw.DIVE_SEGMENT
                    else:
                        mseg = cw.METHOD_SEGMENT.get(method, seg)
                    when = seg if seg == UNKNOWN else cw.later(seg, mseg if mseg in ORDER else seg)
                    add(mon["species"], when, "wild, %s (%s)" % (cw.pretty_map(mapname),
                                                                  cw.ROD_NAME.get(method) or cw.FIELD_NAME[ftype]))
    draconid = dict(re.findall(r"#define (DRACONID_\w+)\s+(SPECIES_\w+)", open(DRACONID_H).read()))
    trade_text = open(TRADES).read()
    trades = {}
    for m in re.finditer(r"\[(INGAME_TRADE_\w+)\]\s*=\s*\{(.*?)\n    \},", trade_text, re.S):
        sp = re.search(r"\.species\s*=\s*(SPECIES_\w+)", m.group(2))
        if sp:
            trades.setdefault(m.group(1), sp.group(1))  # the first block is the Emerald one
    for path, rel, owner, when in scripts:
        text = open(path).read()
        for cmd, arg in GIFT_MON.findall(text):
            sp = draconid.get(arg, arg)
            if not sp.startswith("SPECIES_"):
                continue
            w, why = GIFT_WHEN.get((owner, sp), (when, None))
            how = {"givemon": "gift", "givecustommon": "gift", "giveegg": "egg", "setwildbattle": "encounter"}[cmd]
            add(sp, w, "%s, %s%s" % (how, rel, " – " + why if why else ""))
        for t in TRADE.findall(text):
            if t in trades:
                add(trades[t], when, "trade, %s" % rel)
    for sp, when, how in EXTRA_SOURCES:
        add(sp, when, how)
    return out


# ---------------------------------------------------------------------------
# Item sources
# ---------------------------------------------------------------------------

def counter_lists():
    """[(label, [items])] of the battle item counter in file order: the items from each label to the next label
    or ITEM_NONE (a tier's label runs on through the lower tiers in the shop; here each item is in its own tier)."""
    lists, cur = [], None
    for line in open(COUNTER).read().splitlines():
        m = re.match(r"^\s*(\w+)::", line)
        if m:
            cur = (m.group(1), [])
            lists.append(cur)
            continue
        m = re.match(r"^\s*\.2byte\s+(ITEM_\w+)", line)
        if m and cur is not None:
            if m.group(1) == "ITEM_NONE":
                cur = None
            else:
                cur[1].append(m.group(1))
    return lists


def label_when(label, tiers):
    m = re.match(r"Draconid_BattleItems_Tier(\d+)$", label)
    if m:
        badges = tiers.get(int(m.group(1)), 0)
        return "S%d" % (badges + 1), "counter, %d badge%s" % (badges, "" if badges == 1 else "s")
    if label.endswith("_PostGame"):
        return POST, "counter, after the Champion"
    return UNKNOWN, "counter list %s" % label


def item_sources(wanted, scripts):
    """ITEM_* (of `wanted`) -> [(when, how)]; also the set of every item constant with some source at all."""
    out, anywhere = {}, set()
    for path in sorted(glob.glob(os.path.join(ROOT, "data/maps/*/map.json"))):
        if "_Frlg" in path:
            continue
        j = json.load(open(path))
        when = map_when(j["id"])
        for o in j.get("object_events", []):
            item = o.get("trainer_sight_or_berry_tree_id", "")
            if item.startswith("ITEM_"):
                anywhere.add(item)
                if item in wanted:
                    out.setdefault(item, []).append((when, "item ball, %s (%d, %d)" % (cw.pretty_map(j["id"]), o["x"], o["y"])))
        for b in j.get("bg_events", []):
            item = b.get("item", "")
            if item.startswith("ITEM_"):
                anywhere.add(item)
                if item in wanted:
                    out.setdefault(item, []).append((when, "hidden item, %s (%d, %d)" % (cw.pretty_map(j["id"]), b["x"], b["y"])))
    for path, rel, owner, when in scripts:
        text = open(path).read()
        given = [i for _c, i in GIVE_ITEM.findall(text)]
        given_vars = set(GIVE_VAR.findall(text))
        given += [i for v, i in SET_VAR_ITEM.findall(text) if v in given_vars]
        anywhere.update(re.findall(r"\.2byte\s+(ITEM_\w+)", text))  # mart lists
        for item in dict.fromkeys(given):
            anywhere.add(item)
            if item in wanted and not path.startswith(COUNTER):
                out.setdefault(item, []).append((when, "gift, %s" % rel))
    anywhere.update(PENDING_ITEM_BALLS)
    tiers = {int(n): int(v) for n, v in re.findall(r"#define BATTLE_ITEMS_TIER_(\d+)_BADGES\s+(\d+)",
                                                     open(DRACONID_H).read())}
    for label, items in counter_lists():
        when, how = label_when(label, tiers)
        for item in items:
            anywhere.add(item)
            if item in wanted:
                out.setdefault(item, []).append((when, how))
    return out, anywhere


# ---------------------------------------------------------------------------
# The post-game lists
# ---------------------------------------------------------------------------

def stone_order(items, stones, bases, species, natnum):
    def key(item):
        nums = [natnum.get(species[b]["natDexNum"], 1 << 20) for b in bases.get(item, ()) if b in species]
        return (min(nums) if nums else 1 << 20, items[item]["id"])
    return sorted(stones, key=key)


def crystal_order(items, crystals):
    return sorted(crystals, key=lambda i: (items[i]["secondary"] in (None, "255"), items[i]["id"]))


def render_lists(stones, crystals):
    lines = [WRITE_BEGIN + ": every Mega Stone (National Dex order) and Z-Crystal (types, then species) of the build",
             "raw `", "\t.align 2", "%s::" % COUNTER_STONES]
    lines += ["\t.2byte %s" % s for s in stones] + ["\t.2byte ITEM_NONE", "", "\t.align 2", "%s::" % COUNTER_CRYSTALS]
    lines += ["\t.2byte %s" % c for c in crystals] + ["\t.2byte ITEM_NONE", "`", WRITE_END]
    return "\n".join(lines)


def write_lists(block):
    text = open(COUNTER).read()
    start, end = text.find(WRITE_BEGIN), text.find(WRITE_END)
    if start < 0 or end < 0:
        sys.exit("check_megas.py: %s has no '%s' ... '%s' block" % (COUNTER, WRITE_BEGIN, WRITE_END))
    end = text.index("\n", end) if "\n" in text[end:] else len(text)
    new = text[:start] + block + text[end:]
    if new != text:
        open(COUNTER, "w").write(new)
        print("check_megas.py: wrote the post-game lists into %s" % os.path.relpath(COUNTER, ROOT))
    else:
        print("check_megas.py: the post-game lists are up to date")


# ---------------------------------------------------------------------------

def earliest(sources):
    return min(sources, key=lambda s: idx(s[0])) if sources else None


def fmt_sources(sources, limit=3):
    if not sources:
        return "–"
    srt = sorted(sources, key=lambda s: idx(s[0]))
    text = "; ".join("%s %s" % (w, h) for w, h in srt[:limit])
    return text + ("; +%d more" % (len(srt) - limit) if len(srt) > limit else "")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--problems", action="store_true", help="only stones and crystals with an error or a note")
    ap.add_argument("--write", action="store_true", help="regenerate the post-game lists in battle_items.pory")
    args = ap.parse_args()

    items = load_items()
    stones = [i for i in items if items[i]["hold"] == "HOLD_EFFECT_MEGA_STONE"]
    crystals = [i for i in items if items[i]["hold"] == "HOLD_EFFECT_Z_CRYSTAL"]
    alias = cw.species_aliases()
    species = load_species()
    natnum = cw.national_numbers()
    family = families(species)
    forms = mega_forms()
    table_users = {}
    for sp, info in species.items():
        if info["formChangeTable"] and not info["flags"] & {"isMegaEvolution", "isGigantamax", "isPrimalReversion",
                                                             "isTotem", "isTeraForm", "isUltraBurst"}:
            table_users.setdefault(info["formChangeTable"], []).append(sp)
    bases = {s: sorted({b for table, _m in forms.get(s, []) for b in table_users.get(table, [])}) for s in stones}

    want_stones = stone_order(items, stones, bases, species, natnum)
    want_crystals = crystal_order(items, crystals)
    if args.write:
        write_lists(render_lists(want_stones, want_crystals))
        return 0

    scripts = script_files()
    mons = mon_sources(species, alias, scripts)
    isrc, anywhere = item_sources(set(items), scripts)
    lists = dict(counter_lists())
    errors, notes = [], []

    def name(sp):
        return species[sp]["name"] if sp in species else nice(sp)

    def line_sources(members):
        return [(w, "%s: %s" % (name(sp), h)) for sp in sorted(members) for w, h in mons.get(sp, [])]

    # unknown "when" of a Pokémon source (stones' sources are checked below)
    for sp, srcs in sorted(mons.items()):
        for w, h in srcs:
            if w == UNKNOWN:
                errors.append("%s: %s – when? (add the map or script to MAP_WHEN / SCRIPT_WHEN)" % (nice(sp), h))

    print("== Mega Stones (%d) ==" % len(stones))
    print("%-16s %-22s %-26s %-6s %s" % ("stone", "Pokémon", "line: first source", "price", "sources"))
    counts = {"pre": 0, "post": 0, "none": 0}
    for s in want_stones:
        info = items[s]
        members = set()
        for b in bases[s]:
            members |= family.get(b, {b})
        lsrc = line_sources(members)
        first = earliest(lsrc)
        line_when = first[0] if first else None
        srcs = isrc.get(s, [])
        pre = [x for x in srcs if x[0] not in (POST, UNKNOWN)]
        problems = []
        if not bases[s]:
            problems.append(("NOTE", "no Pokémon in this build Mega Evolves with it"))
        if line_when is not None and line_when != POST and not pre:
            problems.append(("ERROR", "the line comes %s (%s), but no source before the post-game" % (line_when, first[1])))
        if line_when is None and pre:
            problems.append(("NOTE", "placed in the story, but nobody can use it"))
        elif line_when == POST and pre:
            problems.append(("NOTE", "placed in the story, but its line only comes after the Champion"))
        if s not in lists.get(COUNTER_STONES, []):
            problems.append(("ERROR", "not in %s (run check_megas.py --write)" % COUNTER_STONES))
        if not info["price"]:
            problems.append(("ERROR", "price %s: a mart would give it away (MEGA_STONE_PRICE)" % info["price_expr"]))
        for w, h in srcs:
            if w == UNKNOWN:
                problems.append(("ERROR", "%s – when? (add the map or script to MAP_WHEN / SCRIPT_WHEN)" % h))
            elif idx(w) < idx(MEGA_RING):
                problems.append(("ERROR", "%s %s is before the Mega Ring (%s)" % (w, h, MEGA_RING)))
        # an evolution item nobody can get between the obtainable members and the Mega's species
        if line_when is not None and bases[s]:
            have = {alias.get(sp, sp) for sp in members if mons.get(sp)}
            reach, frontier, blocked = set(have), list(have), set()
            while frontier:
                cur = frontier.pop()
                for method, param, child, other_region in species.get(cur, {}).get("evos", []):
                    if child in reach or other_region:
                        continue
                    if param.startswith("ITEM_") and method.startswith("EVO_ITEM") and param not in anywhere:
                        blocked.add(param)
                        continue
                    reach.add(child)
                    frontier.append(child)
            if not reach & set(bases[s]) and blocked:
                problems.append(("NOTE", "%s only through the %s, which the game never hands out" % (
                    "/".join(dict.fromkeys(name(b) for b in bases[s])), ", ".join(nice(i) for i in sorted(blocked)))))
        counts["none" if line_when is None else "post" if line_when == POST else "pre"] += 1
        for level, msg in problems:
            (errors if level == "ERROR" else notes).append("%s: %s" % (info["name"], msg))
        if args.problems and not problems:
            continue
        mon = "/".join(dict.fromkeys(name(b) for b in bases[s])) or "–"
        line = "%s %s" % (line_when, first[1].split(":")[0]) if first else "not in the game"
        print("%-16s %-22s %-26s %-6s %s" % (info["name"], mon[:22], line[:26], info["price"], fmt_sources(srcs)))
        for level, msg in problems:
            print("    %s %s" % (level, msg))

    print()
    print("== Z-Crystals (%d) ==" % len(crystals))
    users = signature_species()
    typed = [c for c in want_crystals if items[c]["secondary"] not in (None, "255")]
    with_story = 0
    for c in want_crystals:
        info = items[c]
        srcs = isrc.get(c, [])
        story = [x for x in srcs if not x[1].startswith("counter")]
        problems = []
        if c not in lists.get(COUNTER_CRYSTALS, []):
            problems.append(("ERROR", "not in %s (run check_megas.py --write)" % COUNTER_CRYSTALS))
        if not info["price"]:
            problems.append(("ERROR", "price %s: a mart would give it away (Z_CRYSTAL_PRICE)" % info["price_expr"]))
        for w, h in story:
            if w == UNKNOWN:
                problems.append(("NOTE", "%s – when? (add the map or script to MAP_WHEN / SCRIPT_WHEN)" % h))
        if c in typed:
            kind = info["secondary"][len("TYPE_"):].title() if info["secondary"].startswith("TYPE_") else info["secondary"]
            if any(w not in (POST, UNKNOWN) for w, _h in story):
                with_story += 1
        else:
            members = set()
            for sp in users.get(c, []):
                members |= family.get(sp, {sp})
            first = earliest(line_sources(members))
            kind = "/".join(sorted({name(sp) for sp in users.get(c, [])})) or "–"
            kind += " (%s)" % (first[0] if first else "not in the game")
        for level, msg in problems:
            (errors if level == "ERROR" else notes).append("%s: %s" % (info["name"], msg))
        if args.problems and not problems:
            continue
        print("%-16s %-28s %-6s %s" % (info["name"], kind[:28], info["price"], fmt_sources(srcs)))
        for level, msg in problems:
            print("    %s %s" % (level, msg))
    notes.append("type crystals with a story source before the post-game: %d of %d" % (with_story, len(typed)))

    for label, want in ((COUNTER_STONES, want_stones), (COUNTER_CRYSTALS, want_crystals)):
        have = lists.get(label)
        if have is None:
            errors.append("battle_items.pory has no %s list (run check_megas.py --write)" % label)
        elif have != want:
            errors.append("%s differs from what --write makes (run check_megas.py --write)" % label)

    print()
    print("Mega Stones: %d with a line the player gets before the post-game, %d only after the Champion, "
          "%d not in the game" % (counts["pre"], counts["post"], counts["none"]))
    for n in notes:
        print("NOTE  " + n)
    for e in errors:
        print("ERROR " + e)
    print("%d error(s), %d note(s)" % (len(errors), len(notes)))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
