#!/usr/bin/env python3
"""
gen49.py - Gen 4-9 Pokemon on generic trainers and grunts (round 1: D-195, D-240 - D-242).

  python3 tools/hack/trainers/gen49.py                  # apply gen49_plan.py -> batch_gen49.party, gen49_swaps.json
  python3 tools/hack/trainers/splice_party.py tools/hack/trainers/batch_gen49.party
  python3 tools/hack/trainers/gen49.py --coverage       # share of trainers with a Gen 4-9 Pokemon + rule checks
  python3 tools/hack/trainers/gen49.py --moves Clawitzer 40 S7   # the set the rules give a species
  python3 tools/hack/trainers/gen49.py --base OLD.party --out NEW.party   # apply to another file

The plan (gen49_plan.py) says per trainer which Pokemon family makes way for which Gen 4-9 line; this
script writes the Pokemon (docs/hack_trainers.md, "Gen 4-9 swaps"):
  - same slot, level, IVs, EVs and nature (Atk/SpA mirrored when a physical mon becomes a special one);
  - the stage the level allows (level-up evolutions; stone / friendship / other evolutions at SET_LEVEL);
  - the ability (only where the block names one): the species' first regular ability that does something;
  - the held item carried over (a type booster follows the new STAB, set-specific items become a berry,
    or a Life Orb from S7);
  - moves: level-up moves at or below the level (+ Emerald's TMs and HMs from S4), STAB of each type,
    coverage, one status or set-up move; nothing over 90 power before S4 and rarely before S7 (the batches'
    own style), no OHKO, self-KO, recharge or two-turn moves.
A swap is skipped when the block already has the new family, so running it again changes nothing.
"Gen 4-9 Pokemon" = a species from Gens 4-9 that is not in the Hoenn Pokedex (Roserade, Gallade,
Magnezone ... are Hoenn species here).
"""

import argparse
import collections
import glob
import importlib.util
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_party  # noqa: E402
import party  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = check_party.ROOT
SEGS = ["S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "POST"]

# Evolutions that don't happen by level-up get a set level (D-195, D-240).
SET_LEVEL = {"LUCARIO": 30, "SWOOBAT": 30, "WHIMSICOTT": 30, "LILLIGANT": 30, "CHANDELURE": 50, "TSAREENA": 29,
             "GRAPPLOCT": 35, "FROSMOTH": 35, "PAWMOT": 30, "BELLIBOLT": 30, "KINGAMBIT": 64, "MUSHARNA": 30,
             "SIMISEAR": 30, "SIMISAGE": 30, "SIMIPOUR": 30, "POLTEAGEIST_PHONY": 30}
BOOSTER = {"NORMAL": "Silk Scarf", "FIRE": "Charcoal", "WATER": "Mystic Water", "GRASS": "Miracle Seed",
           "ELECTRIC": "Magnet", "ICE": "Never-Melt Ice", "FIGHTING": "Black Belt", "POISON": "Poison Barb",
           "GROUND": "Soft Sand", "FLYING": "Sharp Beak", "PSYCHIC": "Twisted Spoon", "BUG": "Silver Powder",
           "ROCK": "Hard Stone", "GHOST": "Spell Tag", "DRAGON": "Dragon Fang", "DARK": "Black Glasses",
           "STEEL": "Metal Coat", "FAIRY": "Fairy Feather"}
BOOSTERS = set(BOOSTER.values()) | {"Sea Incense", "Wave Incense", "Odd Incense", "Rock Incense", "Rose Incense"}
SET_SPECIFIC = {"Flame Orb", "Toxic Orb", "White Herb", "Choice Band", "Choice Specs", "Choice Scarf", "Light Clay",
                "Damp Rock", "Heat Rock", "Smooth Rock", "Icy Rock", "Chesto Berry", "Deep Sea Tooth",
                "Deep Sea Scale", "Light Ball", "Throat Spray", "Power Herb", "Big Root", "Grip Claw",
                "Binding Band", "Everstone"}
USELESS_ABILITIES = {"NONE", "HONEY_GATHER", "PICKUP", "RUN_AWAY", "ILLUMINATE", "FRISK", "BALL_FETCH",
                     "ANTICIPATION", "FOREWARN", "KLUTZ", "STALL", "SLOW_START", "TRUANT", "DEFEATIST", "CUD_CHEW"}
NATURES = {  # nature: (raised, lowered)
    "Hardy": ("Atk", "Atk"), "Lonely": ("Atk", "Def"), "Brave": ("Atk", "Spe"), "Adamant": ("Atk", "SpA"),
    "Naughty": ("Atk", "SpD"), "Bold": ("Def", "Atk"), "Docile": ("Def", "Def"), "Relaxed": ("Def", "Spe"),
    "Impish": ("Def", "SpA"), "Lax": ("Def", "SpD"), "Timid": ("Spe", "Atk"), "Hasty": ("Spe", "Def"),
    "Serious": ("Spe", "Spe"), "Jolly": ("Spe", "SpA"), "Naive": ("Spe", "SpD"), "Modest": ("SpA", "Atk"),
    "Mild": ("SpA", "Def"), "Quiet": ("SpA", "Spe"), "Bashful": ("SpA", "SpA"), "Rash": ("SpA", "SpD"),
    "Calm": ("SpD", "Atk"), "Gentle": ("SpD", "Def"), "Sassy": ("SpD", "Spe"), "Careful": ("SpD", "SpA"),
    "Quirky": ("SpD", "SpD")}
BY_STATS = {v: k for k, v in NATURES.items() if v[0] != v[1]}
SWAP_STAT = {"Atk": "SpA", "SpA": "Atk"}

# Moves the rules never pick: OHKO, self-KO, recharge, two-turn, and moves that depend on things a trainer
# can't set up or that the AI plays badly.
BANNED = {"MOVE_" + x for x in """FOCUS_PUNCH HIDDEN_POWER FRUSTRATION RETURN SECRET_POWER NATURAL_GIFT FLING
    LAST_RESORT DREAM_EATER BELCH SPIT_UP SWALLOW STOCKPILE SNORE SLEEP_TALK BIDE COUNTER MIRROR_COAT METAL_BURST
    ENDEAVOR PRESENT HOLD_BACK FALSE_SWIPE FEINT ROLLOUT ICE_BALL UPROAR STEEL_BEAM MIND_BLOWN SELF_DESTRUCT
    EXPLOSION MISTY_EXPLOSION CHLOROBLAST BURN_UP DOUBLE_SHOCK FUTURE_SIGHT DOOM_DESTINY SYNCHRONOISE SHELL_TRAP
    BEAK_BLAST TRUMP_CARD STRUGGLE SOLAR_BEAM SOLAR_BLADE SKY_ATTACK RAZOR_WIND SKULL_BASH FLY DIG DIVE BOUNCE
    PHANTOM_FORCE SHADOW_FORCE FREEZE_SHOCK ICE_BURN GEOMANCY METEOR_BEAM ELECTRO_SHOT SKY_DROP HYPER_BEAM
    GIGA_IMPACT BLAST_BURN HYDRO_CANNON FRENZY_PLANT ROCK_WRECKER ROAR_OF_TIME PRISMATIC_LASER ETERNABEAM
    METEOR_ASSAULT FINAL_GAMBIT MEMENTO HEALING_WISH LUNAR_DANCE DESTINY_BOND PERISH_SONG GUILLOTINE HORN_DRILL
    FISSURE SHEER_COLD RAGE FURY_CUTTER ECHOED_VOICE ROUND FAKE_OUT FIRST_IMPRESSION SPLASH CELEBRATE HAPPY_HOUR
    HOLD_HANDS COPYCAT MIMIC METRONOME ASSIST SKETCH TRANSFORM NATURE_POWER HELPING_HAND FOLLOW_ME RAGE_POWDER
    AFTER_YOU ALLY_SWITCH WIDE_GUARD QUICK_GUARD CRAFTY_SHIELD MAT_BLOCK SPOTLIGHT INSTRUCT QUASH ROTOTILLER
    FLOWER_SHIELD MAGNETIC_FLUX GEAR_UP AROMATIC_MIST DECORATE COACHING LIFE_DEW TEETER_DANCE SWAGGER FLATTER
    BATON_PASS TELEPORT POLTERGEIST DRAGON_RAGE SONIC_BOOM SUPER_FANG NATURES_MADNESS RUINATION DOUBLE_TEAM
    MINIMIZE FOCUS_ENERGY LOCK_ON MIND_READER FORESIGHT ODOR_SLEUTH MIRACLE_EYE BELLY_DRUM CURSE SPITE GRUDGE
    CONVERSION CONVERSION_2 CAMOUFLAGE REFLECT_TYPE SOAK MAGIC_POWDER TRICK SWITCHEROO BESTOW RECYCLE
    ENTRAINMENT ROLE_PLAY SKILL_SWAP SNATCH IMPRISON POWER_SPLIT GUARD_SPLIT POWER_SWAP GUARD_SWAP HEART_SWAP
    SPEED_SWAP POWER_TRICK SIMPLE_BEAM WORRY_SEED GASTRO_ACID TORMENT ATTRACT CAPTIVATE NIGHTMARE EMBARGO
    HEAL_BLOCK TELEKINESIS MAGNET_RISE GRAVITY TRICK_ROOM WONDER_ROOM MAGIC_ROOM ION_DELUGE ELECTRIFY FAIRY_LOCK
    POWDER PLAY_NICE TEARFUL_LOOK CONFIDE NOBLE_ROAR TAIL_WHIP LEER GROWL SAND_ATTACK SMOKESCREEN KINESIS FLASH
    MUD_SPORT WATER_SPORT DEFOG HAZE MIST SAFEGUARD LUCKY_CHANT SCREECH METAL_SOUND FAKE_TEARS SCARY_FACE
    STRING_SHOT COTTON_SPORE TICKLE CHARM BABY_DOLL_EYES HOWL GROWTH SHARPEN HARDEN WITHDRAW DEFENSE_CURL
    MEDITATE ACUPRESSURE TAR_SHOT SPICY_EXTRACT OCTOLOCK NO_RETREAT CLANGOROUS_SOUL FILLET_AWAY STUFF_CHEEKS
    TEATIME COURT_CHANGE CORROSIVE_GAS SNOWSCAPE CHILLY_RECEPTION REVIVAL_BLESSING SHED_TAIL DOODLE STEEL_ROLLER
    MISTY_TERRAIN GRASSY_TERRAIN ELECTRIC_TERRAIN PSYCHIC_TERRAIN HAIL RAIN_DANCE SUNNY_DAY SANDSTORM DETECT
    ENDURE SUBSTITUTE REST AQUA_RING INGRAIN ROAR WHIRLWIND BLOCK MEAN_LOOK SPIDER_WEB PUNISHMENT FLAIL REVERSAL
    WRING_OUT CRUSH_GRIP WATER_SPOUT ERUPTION DRAGON_ENERGY NIGHT_SHADE SEISMIC_TOSS PSYWAVE STORED_POWER
    POWER_TRIP FOUL_PLAY BODY_PRESS SPLISHY_SPLASH TERA_BLAST RAGING_FURY WEATHER_BALL LASER_FOCUS SHORE_UP
    MOONLIGHT MORNING_SUN SYNTHESIS BIND WRAP CLAMP FIRE_SPIN WHIRLPOOL SAND_TOMB MAGMA_STORM INFESTATION
    THUNDER_CAGE SNAP_TRAP ABSORB MEGA_DRAIN""".split()}
# weight / speed based power: an estimate for the pick
VARIABLE_POWER = {"MOVE_LOW_KICK": 60, "MOVE_GRASS_KNOT": 60, "MOVE_HEAVY_SLAM": 60, "MOVE_HEAT_CRASH": 60,
                  "MOVE_GYRO_BALL": 60, "MOVE_ELECTRO_BALL": 60}
# harmless moves a low-level mon may still use to fill its set (the game's own default set would)
FILLER = {"MOVE_" + x for x in """HARDEN WITHDRAW DEFENSE_CURL GROWL LEER TAIL_WHIP SAND_ATTACK SMOKESCREEN
    STRING_SHOT FOCUS_ENERGY SCARY_FACE SCREECH HOWL GROWTH SHARPEN MEDITATE CHARM FAKE_TEARS METAL_SOUND DEFOG
    MIST HAZE SAFEGUARD PROTECT DETECT REST SUBSTITUTE RAIN_DANCE SUNNY_DAY SANDSTORM HAIL ROAR WHIRLWIND FAKE_OUT
    ECHOED_VOICE ROUND FURY_CUTTER ROLLOUT ABSORB MEGA_DRAIN BIND WRAP CLAMP FIRE_SPIN WHIRLPOOL SAND_TOMB
    INFESTATION PAYBACK ASSURANCE ACROBATICS WEATHER_BALL CHARGE""".split()}
# status / set-up moves worth a slot, best first; physical and special set-ups go by the mon's better side
SETUP_PHYS = ["SWORDS_DANCE", "DRAGON_DANCE", "BULK_UP", "SHIFT_GEAR", "COIL", "HONE_CLAWS", "VICTORY_DANCE"]
SETUP_SPEC = ["NASTY_PLOT", "QUIVER_DANCE", "CALM_MIND", "TAIL_GLOW", "TAKE_HEART"]
STATUS = ["SPORE", "WILL_O_WISP", "THUNDER_WAVE", "TOXIC", "SLEEP_POWDER", "YAWN", "GLARE", "STUN_SPORE",
          "LEECH_SEED", "STEALTH_ROCK", "SPIKES", "TOXIC_SPIKES", "STICKY_WEB", "HYPNOSIS", "CONFUSE_RAY",
          "POISON_POWDER", "ROOST", "RECOVER", "SLACK_OFF", "SOFT_BOILED", "MILK_DRINK", "STRENGTH_SAP",
          "PARTING_SHOT", "TAUNT", "ENCORE", "REFLECT", "LIGHT_SCREEN", "IRON_DEFENSE", "AMNESIA",
          "ROCK_POLISH", "AGILITY", "COTTON_GUARD", "WORK_UP", "PAIN_SPLIT", "FEATHER_DANCE", "PROTECT",
          "SUPERSONIC", "SWEET_KISS", "DISABLE", "SING", "GRASS_WHISTLE", "LOVELY_KISS", "POISON_GAS"]
# coverage preference when two moves are close
TYPE_ORDER = ["GROUND", "ICE", "FIGHTING", "FIRE", "ROCK", "DARK", "ELECTRIC", "WATER", "GRASS", "FLYING",
              "PSYCHIC", "GHOST", "POISON", "STEEL", "BUG", "DRAGON", "FAIRY", "NORMAL"]
GYM_TYPE = {"RustboroCity_Gym": "ROCK", "DewfordTown_Gym": "FIGHTING", "MauvilleCity_Gym": "ELECTRIC",
            "LavaridgeTown_Gym_1F": "FIRE", "LavaridgeTown_Gym_B1F": "FIRE", "PetalburgCity_Gym": "NORMAL",
            "FortreeCity_Gym": "FLYING", "MossdeepCity_Gym": "PSYCHIC", "SootopolisCity_Gym_B1F": "WATER",
            "SootopolisCity_Gym_1F": "WATER"}


# ---------------------------------------------------------------- data

def _first_alt(v):
    """'B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95' -> '90' (the configs are GEN_LATEST)."""
    m = re.match(r".*?\?\s*(.*?)\s*:\s*(.*)$", v.strip())
    return m.group(1).strip() if m else v.strip()


def load_moves():
    text = open(os.path.join(ROOT, "src/data/moves_info.h")).read()
    moves = {}
    for m in re.finditer(r"\[(MOVE_\w+)\]\s*=\s*\{(.*?)\n    \},", text, re.S):
        const, body = m.group(1), m.group(2)
        d = {}
        nm = re.search(r'\.name\s*=\s*COMPOUND_STRING\("([^"]*)"\)', body)
        d["name"] = nm.group(1) if nm else const
        for key in ("effect", "power", "type", "accuracy", "category", "strikeCount"):
            mm = re.search(r"\n\s*\.%s\s*=\s*([^,\n]+(?:\?[^,\n]+)?),?\n" % key, body)
            if mm:
                d[key] = _first_alt(mm.group(1).rstrip(","))
        d["power"] = int(d["power"]) if str(d.get("power", "0")).isdigit() else 0
        d["accuracy"] = int(d["accuracy"]) if str(d.get("accuracy", "0")).isdigit() else 0
        d["type"] = d.get("type", "TYPE_NORMAL")[len("TYPE_"):]
        d["category"] = d.get("category", "DAMAGE_CATEGORY_STATUS")[len("DAMAGE_CATEGORY_"):]
        d["recharge"] = "MOVE_EFFECT_RECHARGE" in body
        d["strikes"] = int(d["strikeCount"]) if str(d.get("strikeCount", "")).isdigit() else 1
        if re.search(r"\.multiHit\s*=\s*TRUE", body):
            d["strikes"] = 3
        d["selfdrop"] = bool(re.search(r"\.self\s*=\s*TRUE", body))
        st = re.search(r"MOVE_EFFECT_(PARALYSIS|BURN|POISON|TOXIC|SLEEP)\b[^}]*?\}", body, re.S)
        ch = re.search(r"\.chance\s*=\s*(?:[^?,\n]*\?\s*)?(\d+)", st.group(0)) if st else None
        d["status_hit"] = bool(st and (not ch or int(ch.group(1)) >= 50))
        moves[const] = d
    return moves


def load_species():
    lvl = {}
    for m in re.finditer(r"(\w+)\[\]\s*=\s*\{(.*?)\};", open(check_party.levelup_file()).read(), re.S):
        lvl[m.group(1)] = [(int(a), b) for a, b in re.findall(r"LEVEL_UP_MOVE\(\s*(\d+),\s*(MOVE_\w+)\)", m.group(2))]
    info = {}
    for path in glob.glob(os.path.join(ROOT, "src/data/pokemon/species_info/*.h")):
        for m in re.finditer(r"\[SPECIES_(\w+)\]\s*=\s*\{(.*?)\n    \},", open(path).read(), re.S):
            body = m.group(2)
            d = {"bst": 0}
            for k in ("baseHP", "baseAttack", "baseDefense", "baseSpeed", "baseSpAttack", "baseSpDefense"):
                mm = re.search(r"\.%s\s*=\s*([^,\n]+)," % k, body)
                v = _first_alt(mm.group(1)) if mm else "0"
                d[k] = int(v) if v.isdigit() else 0
                d["bst"] += d[k]
            ab = re.search(r"\.abilities\s*=\s*\{([^}]*)\}", body)
            d["abilities"] = [a.strip()[len("ABILITY_"):] for a in ab.group(1).split(",")] if ab else []
            lp = re.search(r"\.levelUpLearnset\s*=\s*(\w+)", body)
            d["levelup"] = lvl.get(lp.group(1), []) if lp else []
            nm = re.search(r'\.speciesName\s*=\s*_\("([^"]*)"\)', body)
            d["name"] = nm.group(1) if nm else m.group(1).title()
            ty = re.search(r"\.types\s*=\s*MON_TYPES\(([^)]*)\)", body)
            d["types"] = [x.strip()[len("TYPE_"):] for x in ty.group(1).split(",")] if ty else []
            dex = re.search(r"\.natDexNum\s*=\s*(NATIONAL_DEX_\w+)", body)
            d["dex"] = dex.group(1) if dex else None
            info[m.group(1)] = d
    return info


MOVES = load_moves()
SPECIES = load_species()
PARENTS, _, _ = check_party.load_species_info()
CHILDREN = collections.defaultdict(list)
for _c, (_p, _, _) in PARENTS.items():
    CHILDREN[_p].append(_c)
LEARN = {k.upper(): set(v) for k, v in json.load(open(os.path.join(ROOT, "src/data/pokemon/all_learnables.json"))).items()}
ALIAS = dict(re.findall(r"\bSPECIES_(\w+)\s*=\s*SPECIES_(\w+)\s*,",
                        open(os.path.join(ROOT, "include/constants/species.h")).read()))
REV_ALIAS = {v: k for k, v in ALIAS.items()}
_dex = open(os.path.join(ROOT, "include/constants/pokedex.h")).read()
NATDEX = {n: i for i, n in enumerate(re.findall(r"(NATIONAL_DEX_\w+)",
                                                re.search(r"enum NationalDexOrder\s*\{(.*?)\}", _dex, re.S).group(1)))}
HOENN_DEX = set(re.findall(r"F\((\w+)\)", re.search(r"#define FOREACH_SPECIES_IN_HOENN_DEX_ORDER\(F\)(.*?)\n\n",
                                                     _dex, re.S).group(1)))
_tms = re.search(r"#define FOREACH_TM\(F\)(.*?)\n\n", open(os.path.join(ROOT, "include/constants/tms_hms.h")).read(),
                 re.S).group(1)
TMS = {"MOVE_" + x for x in re.findall(r"F\((\w+)\)", _tms)} | \
      {"MOVE_SURF", "MOVE_STRENGTH", "MOVE_ROCK_SMASH", "MOVE_WATERFALL", "MOVE_CUT"}


def sp_const(name):
    sp = party.const_name(name, "SPECIES_")[len("SPECIES_"):]
    return ALIAS.get(sp, sp)


def is_gen49(sp):
    """A species from Gens 4-9 that is not in the Hoenn Pokedex."""
    num = NATDEX.get(SPECIES.get(sp, {}).get("dex"), 0)
    return num > 386 and sp not in HOENN_DEX


def line_of(sp):
    line = [sp]
    while line[-1] in PARENTS:
        line.append(PARENTS[line[-1]][0])
    return line


def family(sp):
    todo, out = [line_of(sp)[-1]], set()
    while todo:
        c = todo.pop()
        if c not in out:
            out.add(c)
            todo += CHILDREN.get(c, [])
    return out


def learnable(sp):
    return LEARN.get(sp, set()) | LEARN.get(REV_ALIAS.get(sp, sp), set())


def stage_for(target, level):
    chain = list(reversed(line_of(target)))
    best = chain[0]
    for sp in chain[1:]:
        _, method, prm = PARENTS[sp]
        lv = SET_LEVEL.get(sp)
        if lv is None:
            if not (method.startswith("EVO_LEVEL") and prm.isdigit() and int(prm) > 0):
                sys.exit("%s evolves by %s %s: add it to SET_LEVEL" % (sp, method, prm))
            lv = int(prm)
        if level < lv:
            break
        best = sp
    return best


# ---------------------------------------------------------------- moves

def known_moves(sp, level, seg):
    """Level-up moves at or below the level (the species and its pre-evolutions), + TMs / HMs from S4."""
    got = {}
    for s in line_of(sp):
        for lv, mv in SPECIES.get(s, {}).get("levelup", []):
            if lv <= level and mv not in got:
                got[mv] = lv
    if SEGS.index(seg) >= SEGS.index("S4"):
        learn = set()
        for s in line_of(sp):
            learn |= learnable(s)
        for mv in TMS & learn:
            got.setdefault(mv, 0)
    return got


def side(sp):
    a, s = SPECIES[sp]["baseAttack"], SPECIES[sp]["baseSpAttack"]
    return "BOTH" if abs(a - s) <= 10 else "PHYSICAL" if a > s else "SPECIAL"


def score(mv, sp, seg):
    d = MOVES.get(mv)
    if not d or d["category"] == "STATUS" or mv in BANNED or d["recharge"]:
        return 0
    eff = d.get("effect", "")
    if any(x in eff for x in ("OHKO", "EXPLOSION", "TWO_TURN", "SEMI_INVULNERABLE", "SOLAR_BEAM", "SKY_DROP",
                                "FIXED", "LEVEL_DAMAGE", "SUPER_FANG", "COUNTER", "MIRROR_COAT")):
        return 0
    p = VARIABLE_POWER.get(mv, d["power"])
    if p <= 1:
        return 0
    si = SEGS.index(seg)
    if si < SEGS.index("S4") and p > 90:
        return 0
    val = p * (3 if "MULTI_HIT" in eff else d["strikes"]) * (d["accuracy"] or 100) / 100.0
    if p > 90:  # the batches rarely give moves over 90 power before S7 (3-4 % of moves in S4-S6)
        val *= 0.6 if si <= SEGS.index("S5") else 0.75 if si == SEGS.index("S6") else 0.9 if si <= SEGS.index("S8") else 1.0
    if d["type"] in SPECIES[sp]["types"]:
        val *= 1.5
    if side(sp) != "BOTH" and d["category"] != side(sp):
        val *= 0.55
    if d["selfdrop"] and "ATK" not in eff:
        val *= 0.7
    if d["status_hit"]:
        val += 25
    return val


def pick_moves(sp, level, seg):
    known = known_moves(sp, level, seg)
    types = SPECIES[sp]["types"]
    atk = [(s, m) for s, m in sorted(((score(m, sp, seg), m) for m in known), reverse=True) if s > 0]
    chosen, covered = [], set()

    def take(pred):
        for s, m in atk:
            if m not in chosen and pred(m, s):
                chosen.append(m)
                covered.add(MOVES[m]["type"])
                return m
        return None

    best = atk[0][0] if atk else 0
    for ty in types:  # STAB of each type
        take(lambda m, s, ty=ty: MOVES[m]["type"] == ty and s >= 0.35 * best)
    cover = sorted(((s * (1.0 + 0.02 * (len(TYPE_ORDER) - TYPE_ORDER.index(MOVES[m]["type"]))), m) for s, m in atk
                    if MOVES[m]["type"] not in types and MOVES[m]["type"] != "NORMAL"), reverse=True)
    for s, m in cover:  # coverage
        if len(chosen) >= 3:
            break
        if MOVES[m]["type"] not in covered and s >= 0.35 * best:
            chosen.append(m)
            covered.add(MOVES[m]["type"])
    order = {"PHYSICAL": SETUP_PHYS, "SPECIAL": SETUP_SPEC}.get(side(sp), SETUP_PHYS + SETUP_SPEC)
    status = next(("MOVE_" + x for x in order + STATUS if "MOVE_" + x in known), None)
    limit = 3 if status else 4
    while len(chosen) < limit and take(lambda m, s: MOVES[m]["type"] not in covered):
        pass
    for x in STATUS:  # a second status move before a second move of the same type
        if len(chosen) < limit and "MOVE_" + x in known and "MOVE_" + x not in (status, *chosen):
            chosen.append("MOVE_" + x)
    while len(chosen) < limit and take(lambda m, s: True):
        pass
    if status:
        chosen.append(status)
    if len(chosen) < 4:  # low level: what it knows last (the game's own default set)
        chosen += [m for m, lv in sorted(known.items(), key=lambda kv: -kv[1])
                   if m not in chosen and (m not in BANNED or m in FILLER)
                   and not (MOVES[m]["category"] != "STATUS" and score(m, sp, seg) == 0 and m not in FILLER)][:4 - len(chosen)]
    return chosen[:4]


def move_name(mv):
    name = MOVES[mv]["name"]
    return name if party.const_name(name, "MOVE_") == mv else " ".join(w.capitalize() for w in mv[5:].split("_"))


# ---------------------------------------------------------------- one Pokemon

def ability_for(sp):
    regular = [a for a in SPECIES[sp]["abilities"][:2] if a != "NONE"]
    return next((a for a in regular if a not in USELESS_ABILITIES), regular[0] if regular else None)


def flip_nature(n):
    up, down = (SWAP_STAT.get(x, x) for x in NATURES[n])
    return BY_STATS.get((up, down), n) if up != down else n


def new_item(item, new_sp, moves, seg):
    if not item:
        return None
    if item in BOOSTERS:
        return BOOSTER[MOVES[moves[0]]["type"]]
    if item == "Muscle Band" and side(new_sp) == "SPECIAL":
        return "Wise Glasses"
    if item == "Wise Glasses" and side(new_sp) == "PHYSICAL":
        return "Muscle Band"
    if item in SET_SPECIFIC or item == "Black Sludge" and "POISON" not in SPECIES[new_sp]["types"] \
            or item == "Eviolite" and new_sp not in CHILDREN:
        si = SEGS.index(seg)
        return "Life Orb" if si >= SEGS.index("S7") else "Sitrus Berry" if si >= SEGS.index("S3") else "Oran Berry"
    return item


def build_mon(mon, new_sp, seg, keep_moves=None, item=None):
    """The mon's paragraph for new_sp: same level, IVs, EVs and nature (mirrored if the side flips)."""
    flip = {side(sp_const(mon["species"])), side(new_sp)} == {"PHYSICAL", "SPECIAL"}
    mv = keep_moves if keep_moves is not None else pick_moves(new_sp, mon["level"], seg)
    item = item or new_item(mon["item"], new_sp, mv, seg)
    out = [SPECIES[new_sp]["name"] + (" @ " + item if item else "")]
    for line in mon["lines"][1:]:
        s = line.strip()
        if s.startswith("- "):
            if not any(x.startswith("- ") for x in out):
                out += ["- " + move_name(m) for m in mv]
        elif s.startswith("Ability:"):
            out.append("Ability: " + " ".join(w.capitalize() for w in ability_for(new_sp).split("_")))
        elif s.startswith("EVs:") and flip:
            out.append(re.sub(r"\b(Atk|SpA)\b", lambda m: SWAP_STAT[m.group(1)], s))
        elif s.startswith("Nature:") and flip:
            out.append("Nature: " + flip_nature(s.split(":", 1)[1].strip()))
        else:
            out.append(s)
    if not any(x.startswith("- ") for x in out):
        out += ["- " + move_name(m) for m in mv]
    return out, mv


def render_block(raw, new_paras):
    paras = [p.split("\n") for p in re.split(r"\n\s*\n", raw.strip("\n"))]
    for i, lines in new_paras.items():
        paras[i + 1] = lines
    return "\n\n".join("\n".join(p) for p in paras) + "\n\n"


# ---------------------------------------------------------------- the plan

def parse_cond(c):
    kind, _, tiers = c.partition(":")
    allowed = None
    if tiers:
        allowed = set()
        for part in tiers.split(","):
            a, _, z = part.partition("-")
            allowed |= set(range(int(a), int(z or a) + 1))
    return kind, allowed


def apply_plan(plan, blocks, seg, swaps, log):
    """blocks: {tid: raw}. Returns {tid: new raw} and updates swaps ({tid: ["Old -> New", ...]})."""
    info = seg["info"]
    chains = collections.defaultdict(list)
    for t, v in info.items():
        if "tier" in v:
            chains[v["first"]].append((v["tier"], t))
    todo = collections.OrderedDict()
    for short, sws in plan.PLAN.items():
        first = "TRAINER_" + short
        if first not in info:
            sys.exit("gen49_plan.py: unknown trainer " + short)
        for t in [first] + [t for _, t in sorted(chains.get(first, []))]:
            todo.setdefault(t, []).extend(sws)
    for short in plan.FIX:
        todo.setdefault("TRAINER_" + short, [])
    out, errors = {}, []
    for tid, sws in todo.items():
        mons = party.parse_block(blocks[tid])["mons"]
        sname = info[tid]["segment"]
        tier = info[tid].get("tier", 1)
        big = SEGS.index(sname) >= SEGS.index("S5") and len(mons) >= 4
        cur = [sp_const(m["species"]) for m in mons]
        rec = list(swaps.get(tid, []))
        new_paras = {}
        # pre-evolve Pokemon under their line's evolution level (D-216 trade evolutions)
        for old, new, item in plan.FIX.get(tid[len("TRAINER_"):], []):
            idx = next((i for i, sp in enumerate(cur) if sp == sp_const(old)), None)
            if idx is None:
                continue  # already done
            nsp = sp_const(new)
            learn = set()
            for s in line_of(nsp):
                learn |= learnable(s) | {x for _, x in SPECIES[s]["levelup"]}
            olds = [party.const_name(x, "MOVE_") for x in mons[idx]["moves"]]
            lines, mv = build_mon(mons[idx], nsp, sname, keep_moves=olds if set(olds) <= learn else None, item=item)
            new_paras[idx], cur[idx] = lines, nsp
            log.append("%s: %s %d -> %s (%s)" % (tid, mons[idx]["species"], mons[idx]["level"], SPECIES[nsp]["name"],
                                                 ", ".join(move_name(x) for x in mv)))
        conds = [(s, parse_cond(s[2] if len(s) > 2 else "all")) for s in sws]
        conds = [(s, k) for s, (k, allowed) in conds if allowed is None or tier in allowed]
        for s, kind in [c for c in conds if c[1] != "big"] + [c for c in conds if c[1] == "big"]:
            old, target = s[0], sp_const(s[1])
            if kind == "big" and (not big or sum(map(is_gen49, cur)) >= 2):
                continue
            if kind != "big" and family(target) & set(cur):
                continue  # already there (an earlier swap, or run twice)
            allow_ace, allow_new = old.endswith("!"), old.startswith("~")
            old, _, nth = old.strip("!~").partition("#")
            idx = None
            for alt in old.split("|"):
                fam = family(sp_const(alt))
                hits = [i for i, sp in enumerate(cur) if sp in fam and i not in new_paras
                        and (allow_new or not is_gen49(sp)) and (allow_ace or i != len(mons) - 1)]
                if len(hits) >= int(nth or 1):
                    idx = hits[int(nth or 1) - 1]
                    break
            if idx is None:
                errors.append("%s: no %s for %s (%s)" % (tid, s[0], s[1], ", ".join(cur)))
                continue
            m = mons[idx]
            nsp = stage_for(target, m["level"])
            lines, mv = build_mon(m, nsp, sname)
            prev = cur[idx]
            new_paras[idx], cur[idx] = lines, nsp
            if allow_new:  # replaces an earlier swap: keep that record's vanilla side
                j = next(j for j, r in enumerate(rec) if r.split(" -> ")[1] == SPECIES[prev]["name"])
                rec[j] = rec[j].split(" -> ")[0] + " -> " + SPECIES[nsp]["name"]
            else:
                rec.append("%s -> %s" % (SPECIES[prev]["name"], SPECIES[nsp]["name"]))
            log.append("%s: %s %d -> %s (%s)%s" % (tid, m["species"], m["level"], SPECIES[nsp]["name"],
                                                   ", ".join(move_name(x) for x in mv),
                                                   "  [BST %d -> %d]" % (SPECIES[prev]["bst"], SPECIES[nsp]["bst"])
                                                   if SPECIES[nsp]["bst"] < 0.8 * SPECIES[prev]["bst"] else ""))
        if new_paras:
            out[tid] = render_block(blocks[tid], new_paras)
            if rec:
                swaps[tid] = rec
    return out, errors


def load_plan():
    spec = importlib.util.spec_from_file_location("gen49_plan", os.path.join(HERE, "gen49_plan.py"))
    plan = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(plan)
    return plan


# ---------------------------------------------------------------- coverage

def coverage(path, seg):
    """Share of generic trainers (route / gym roles, not story) and grunts with a Gen 4-9 Pokemon, and the
    rules: a block from S5 on with 4+ Pokemon has two (grunts one), a gym trainer has one of the gym's type."""
    blocks = {t: party.parse_block(r) for t, r in party.split(open(path).read())[1]}
    first, have, blk, blkhave, problems = [collections.Counter() for _ in range(4)] + [[]]
    grunts = [0, 0]
    for t, v in seg["info"].items():
        if t not in blocks or v["story"]:
            continue
        mons = blocks[t]["mons"]
        news = [sp_const(m["species"]) for m in mons if is_gen49(sp_const(m["species"]))]
        if v["role"] == "grunt":
            grunts[0] += 1
            grunts[1] += bool(news)
            if len(news) > 1:
                problems.append("%s: grunt with %d Gen 4-9 Pokemon" % (t, len(news)))
            continue
        if v["role"] not in ("route", "gym"):
            continue
        blk[v["segment"]] += 1
        blkhave[v["segment"]] += bool(news)
        if "tier" not in v:
            first[v["segment"]] += 1
            have[v["segment"]] += bool(news)
        if news and SEGS.index(v["segment"]) >= SEGS.index("S5") and len(mons) >= 4 and len(news) < 2:
            problems.append("%s: %s, %d Pokemon, one Gen 4-9 Pokemon" % (t, v["segment"], len(mons)))
        if v["role"] == "gym" and not any(GYM_TYPE.get(v["map"]) in SPECIES[n]["types"] for n in news):
            problems.append("%s: no Gen 4-9 Pokemon of the gym's type" % t)
    return first, have, blk, blkhave, grunts, problems


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--base", default=os.path.join(ROOT, "src/data/trainers.party"), help="party file to read")
    ap.add_argument("--out", help="also write the whole party file here")
    ap.add_argument("--coverage", action="store_true")
    ap.add_argument("--moves", nargs=3, metavar=("SPECIES", "LEVEL", "SEGMENT"))
    ap.add_argument("-v", "--verbose", action="store_true", help="print every swap")
    args = ap.parse_args()
    seg = json.load(open(os.path.join(HERE, "segments.json")))
    if args.moves:
        sp = sp_const(args.moves[0])
        print(SPECIES[sp]["name"], ", ".join(move_name(m) for m in pick_moves(sp, int(args.moves[1]), args.moves[2])))
        return
    if args.coverage:
        first, have, blk, blkhave, grunts, problems = coverage(args.base, seg)
        print("Generic trainers with a Gen 4-9 Pokemon (first battles; blocks with rematch tiers):")
        for s in SEGS:
            print("  %-4s %3d / %3d (%3.0f%%)   %3d / %3d" % (s, have[s], first[s], 100.0 * have[s] / max(1, first[s]),
                                                         blkhave[s], blk[s]))
        print("  all  %3d / %3d (%3.0f%%)   %3d / %3d" % (sum(have.values()), sum(first.values()),
                                                     100.0 * sum(have.values()) / sum(first.values()),
                                                     sum(blkhave.values()), sum(blk.values())))
        print("Grunts with a Gen 4-9 Pokemon: %d / %d" % (grunts[1], grunts[0]))
        for p in problems:
            print("PROBLEM " + p)
        sys.exit(1 if problems else 0)
    pre, blist = party.split(open(args.base).read())
    blocks = dict(blist)
    swaps_path = os.path.join(HERE, "gen49_swaps.json")
    swaps = json.load(open(swaps_path))
    log = []
    new, errors = apply_plan(load_plan(), blocks, seg, swaps, log)
    blocks.update(new)
    for e in errors:
        print("ERROR   " + e)
    if args.verbose:
        print("\n".join(log))
    if errors:
        sys.exit(1)
    json.dump(dict(sorted(swaps.items())), open(swaps_path, "w"), indent=1, ensure_ascii=False)
    open(swaps_path, "a").write("\n")
    # the batch: every block with a swap or a fix, in its old order, new blocks after in file order
    batch_path = os.path.join(HERE, "batch_gen49.party")
    old_order = [t for t, _ in party.split(open(batch_path).read())[1]] if os.path.exists(batch_path) else []
    ids = set(swaps) | set(new) | {"TRAINER_" + t for t in load_plan().FIX}
    order = [t for t in old_order if t in ids] + [t for t, _ in blist if t in ids and t not in old_order]
    open(batch_path, "w").write("".join(blocks[t] for t in order))
    if args.out:
        open(args.out, "w").write(party.join(pre, [(t, blocks[t]) for t, _ in blist]))
    print("%d block(s) changed; batch_gen49.party: %d blocks, gen49_swaps.json: %d blocks" % (len(new), len(order), len(swaps)))


if __name__ == "__main__":
    main()
