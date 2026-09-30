#!/usr/bin/env python3
"""
build_oras_batch.py - draft the "oras-first" trainer blocks from the ORAS matches (docs/hack_trainers.md).

  python3 tools/hack/trainers/oras/build_oras_batch.py -o DRAFT.party      # write the draft + print decisions
  python3 tools/hack/trainers/oras/build_oras_batch.py --explain           # decisions only

Which trainers (D-172): an exact / class match (oras_matches.json) without Emerald rematch tiers whose ORAS
first team has more evolution families from the species pool than the trainer's vanilla Emerald team. The
new team keeps the current block's header, party size and level spread; its roster is the ORAS team (in
ORAS order, the ORAS ace last), each species at the stage its level allows (level-up evolutions only;
see stage()), filled up to the party size with the current team's other members (their own sets).
Sets for the ORAS members come from a donor: the same species elsewhere in trainers.party (same trainer,
then same segment and role, then nearest level), keeping only moves the Pokémon knows at that level
(check_moves()); missing moves are filled with the strongest legal STAB / coverage moves and one status
or set-up move. Items, IVs and natures follow the segment rules. The draft is reviewed by hand and then
kept as tools/hack/trainers/oras/batch_oras_first.party (the committed batch, the source of truth; hand edits:
Clamperl's Deep Sea Tooth sets, Swablu, Cacturne, Illumise, Grumpig's item, two moves --check flagged).
The draft was made from src/data/trainers.party before the ORAS splice (a1bcaa8b); run on a later file it
treats the spliced teams as "current".
"""

import argparse
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TRAINERS = os.path.dirname(HERE)
sys.path.insert(0, TRAINERS)
import check_party  # noqa: E402
import party  # noqa: E402

ROOT = check_party.ROOT
ORDER = ["S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "POST"]
STORY = re.compile(r"^TRAINER_(BRENDAN|MAY|WALLY|ASTER|NERINE|STEVEN|MAXIE|ARCHIE|TABITHA|SHELLY|MATT)")
LEVEL_EVOS = ("EVO_LEVEL", "EVO_LEVEL_FEMALE", "EVO_LEVEL_MALE")
NON_LEVEL_MIN = 32  # stone / trade / friendship evolutions: not before this level (house style, D-172)

# Moves a generated set never picks (charge / recharge / self-KO / situational / OHKO).
BAD_EFFECTS = {"EFFECT_OHKO", "EFFECT_EXPLOSION", "EFFECT_FOCUS_PUNCH", "EFFECT_DREAM_EATER", "EFFECT_SNORE",
               "EFFECT_SLEEP_TALK", "EFFECT_FRUSTRATION", "EFFECT_RETURN", "EFFECT_HIDDEN_POWER",
               "EFFECT_NATURAL_GIFT", "EFFECT_FLING", "EFFECT_LAST_RESORT", "EFFECT_BELCH", "EFFECT_SYNCHRONOISE",
               "EFFECT_TWO_TURNS_ATTACK", "EFFECT_SOLAR_BEAM", "EFFECT_SEMI_INVULNERABLE", "EFFECT_SKY_DROP",
               "EFFECT_RECHARGE", "EFFECT_BIDE", "EFFECT_COUNTER", "EFFECT_MIRROR_COAT", "EFFECT_METAL_BURST",
               "EFFECT_PRESENT", "EFFECT_SPIT_UP", "EFFECT_ENDEAVOR", "EFFECT_FINAL_GAMBIT", "EFFECT_MEMENTO",
               "EFFECT_SUCKER_PUNCH", "EFFECT_FAKE_OUT", "EFFECT_UPPER_HAND", "EFFECT_FIRST_TURN_ONLY",
               "EFFECT_STEEL_ROLLER", "EFFECT_DOUBLE_SHOCK", "EFFECT_BURN_UP", "EFFECT_SNIPE_SHOT",
               "EFFECT_MIND_BLOWN", "EFFECT_SHELL_TRAP", "EFFECT_BEAK_BLAST", "EFFECT_POLTERGEIST",
               "EFFECT_DREAM_EATER", "EFFECT_SPECTRAL_THIEF", "EFFECT_PSYWAVE", "EFFECT_FIXED_HP_DAMAGE",
               "EFFECT_LEVEL_DAMAGE", "EFFECT_SUPER_FANG", "EFFECT_MAGNITUDE", "EFFECT_ROLLOUT",
               "EFFECT_FURY_CUTTER", "EFFECT_THRASH", "EFFECT_UPROAR", "EFFECT_RAGE", "EFFECT_TRIPLE_KICK",
               "EFFECT_ROUND", "EFFECT_ECHOED_VOICE", "EFFECT_STOMPING_TANTRUM", "EFFECT_FUTURE_SIGHT",
               "EFFECT_SHORE_UP"}
BAD_MOVES = {"MOVE_SELF_DESTRUCT", "MOVE_EXPLOSION", "MOVE_HYPER_BEAM", "MOVE_GIGA_IMPACT", "MOVE_BLAST_BURN",
             "MOVE_HYDRO_CANNON", "MOVE_FRENZY_PLANT", "MOVE_ROCK_WRECKER", "MOVE_ROAR_OF_TIME",
             "MOVE_SKY_ATTACK", "MOVE_SKULL_BASH", "MOVE_RAZOR_WIND", "MOVE_SOLAR_BEAM", "MOVE_SOLAR_BLADE",
             "MOVE_METEOR_BEAM", "MOVE_DIG", "MOVE_FLY", "MOVE_DIVE", "MOVE_BOUNCE", "MOVE_PHANTOM_FORCE",
             "MOVE_SHADOW_FORCE", "MOVE_OUTRAGE", "MOVE_PETAL_DANCE", "MOVE_THRASH", "MOVE_FOCUS_PUNCH",
             "MOVE_DOUBLE_EDGE", "MOVE_HEAD_SMASH", "MOVE_SUBMISSION", "MOVE_TAKE_DOWN", "MOVE_STRUGGLE",
             "MOVE_CHATTER", "MOVE_SECRET_POWER", "MOVE_FLAIL", "MOVE_REVERSAL", "MOVE_ENDEAVOR",
             "MOVE_TRUMP_CARD", "MOVE_WRING_OUT", "MOVE_CRUSH_GRIP", "MOVE_ERUPTION", "MOVE_WATER_SPOUT",
             "MOVE_OVERHEAT", "MOVE_DRACO_METEOR", "MOVE_LEAF_STORM", "MOVE_PSYCHO_BOOST", "MOVE_V_CREATE",
             "MOVE_SUPERPOWER", "MOVE_HAMMER_ARM", "MOVE_ICE_HAMMER", "MOVE_SPLASH", "MOVE_CELEBRATE",
             "MOVE_HOLD_HANDS", "MOVE_HAPPY_HOUR", "MOVE_ACUPRESSURE", "MOVE_DOUBLE_TEAM", "MOVE_MINIMIZE",
             "MOVE_SAND_ATTACK", "MOVE_FLASH", "MOVE_SMOKESCREEN", "MOVE_KINESIS", "MOVE_MUD_SLAP",
             "MOVE_OCTAZOOKA", "MOVE_MIRROR_SHOT", "MOVE_MUDDY_WATER", "MOVE_NIGHT_DAZE", "MOVE_LEAF_TORNADO",
             "MOVE_CURSE", "MOVE_RAGE", "MOVE_SPITE", "MOVE_GRUDGE", "MOVE_DESTINY_BOND", "MOVE_PERISH_SONG",
             "MOVE_TRANSFORM", "MOVE_MIMIC", "MOVE_METRONOME", "MOVE_ASSIST", "MOVE_COPYCAT", "MOVE_ME_FIRST",
             "MOVE_MIRROR_MOVE", "MOVE_SKETCH", "MOVE_CONVERSION", "MOVE_CONVERSION_2", "MOVE_CAMOUFLAGE",
             "MOVE_TEETER_DANCE", "MOVE_FLATTER", "MOVE_SWAGGER", "MOVE_ATTRACT", "MOVE_CAPTIVATE",
             "MOVE_CHARM", "MOVE_FEATHER_DANCE", "MOVE_TICKLE", "MOVE_GROWL", "MOVE_LEER", "MOVE_TAIL_WHIP",
             "MOVE_SCARY_FACE", "MOVE_STRING_SHOT", "MOVE_SWEET_SCENT", "MOVE_ODOR_SLEUTH", "MOVE_FORESIGHT",
             "MOVE_MIRACLE_EYE", "MOVE_LOCK_ON", "MOVE_MIND_READER", "MOVE_HARDEN", "MOVE_WITHDRAW",
             "MOVE_DEFENSE_CURL", "MOVE_GROWTH", "MOVE_HOWL", "MOVE_WORK_UP", "MOVE_SHARPEN",
             "MOVE_MEDITATE", "MOVE_FOCUS_ENERGY", "MOVE_LASER_FOCUS", "MOVE_CHARGE", "MOVE_STOCKPILE",
             "MOVE_SWALLOW", "MOVE_SPIT_UP", "MOVE_BIDE", "MOVE_ENDURE", "MOVE_DETECT", "MOVE_SAFEGUARD",
             "MOVE_MIST", "MOVE_HAZE", "MOVE_TELEPORT", "MOVE_ROAR", "MOVE_WHIRLWIND", "MOVE_SUPERSONIC",
             "MOVE_CONFUSE_RAY", "MOVE_SING", "MOVE_GRASS_WHISTLE", "MOVE_LOVELY_KISS", "MOVE_HYPNOSIS",
             "MOVE_SCREECH", "MOVE_METAL_SOUND", "MOVE_FAKE_TEARS", "MOVE_COTTON_SPORE", "MOVE_ROCK_POLISH",
             "MOVE_AGILITY", "MOVE_AUTOTOMIZE", "MOVE_REFRESH", "MOVE_AQUA_RING", "MOVE_INGRAIN",
             "MOVE_HEAL_BELL", "MOVE_AROMATHERAPY", "MOVE_BATON_PASS", "MOVE_SUBSTITUTE", "MOVE_REST",
             "MOVE_WISH", "MOVE_HELPING_HAND", "MOVE_FOLLOW_ME", "MOVE_RAGE_POWDER", "MOVE_SNATCH",
             "MOVE_MAGIC_COAT", "MOVE_RECYCLE", "MOVE_TRICK", "MOVE_SWITCHEROO", "MOVE_ROLE_PLAY",
             "MOVE_SKILL_SWAP", "MOVE_IMPRISON", "MOVE_TORMENT", "MOVE_DISABLE", "MOVE_ENCORE", "MOVE_YAWN",
             "MOVE_NIGHTMARE", "MOVE_MEAN_LOOK", "MOVE_BLOCK", "MOVE_SPIDER_WEB", "MOVE_PAIN_SPLIT",
             "MOVE_PSYCH_UP", "MOVE_SANDSTORM", "MOVE_HAIL", "MOVE_SNOWSCAPE", "MOVE_RAIN_DANCE",
             "MOVE_SUNNY_DAY", "MOVE_LIGHT_SCREEN", "MOVE_REFLECT", "MOVE_MUD_SPORT", "MOVE_WATER_SPORT",
             "MOVE_GRAVITY", "MOVE_TRICK_ROOM", "MOVE_WONDER_ROOM", "MOVE_MAGIC_ROOM", "MOVE_TAILWIND",
             "MOVE_LUCKY_CHANT", "MOVE_POWER_TRICK", "MOVE_POWER_SWAP", "MOVE_GUARD_SWAP", "MOVE_HEART_SWAP",
             "MOVE_POWER_SPLIT", "MOVE_GUARD_SPLIT", "MOVE_SPEED_SWAP", "MOVE_ENTRAINMENT", "MOVE_SOAK",
             "MOVE_SIMPLE_BEAM", "MOVE_WORRY_SEED", "MOVE_GASTRO_ACID", "MOVE_EMBARGO", "MOVE_HEAL_BLOCK",
             "MOVE_TELEKINESIS", "MOVE_MAGNET_RISE", "MOVE_ELECTRIFY", "MOVE_ION_DELUGE", "MOVE_POWDER",
             "MOVE_QUASH", "MOVE_AFTER_YOU", "MOVE_ALLY_SWITCH", "MOVE_BESTOW", "MOVE_REFLECT_TYPE",
             "MOVE_SCARY_FACE", "MOVE_BABY_DOLL_EYES", "MOVE_CONFIDE", "MOVE_NOBLE_ROAR", "MOVE_PLAY_NICE",
             "MOVE_TEARFUL_LOOK", "MOVE_SPOTLIGHT", "MOVE_INSTRUCT", "MOVE_FLORAL_HEALING", "MOVE_HEAL_PULSE",
             "MOVE_LIFE_DEW", "MOVE_JUNGLE_HEALING", "MOVE_DECORATE", "MOVE_COACHING", "MOVE_CORROSIVE_GAS",
             "MOVE_TAR_SHOT", "MOVE_OCTOLOCK", "MOVE_NO_RETREAT", "MOVE_CLANGOROUS_SOUL", "MOVE_STUFF_CHEEKS",
             "MOVE_TEATIME", "MOVE_MAGIC_POWDER", "MOVE_FILLET_AWAY", "MOVE_SHED_TAIL", "MOVE_CHILLY_RECEPTION",
             "MOVE_TIDY_UP", "MOVE_DOODLE", "MOVE_POUNCE", "MOVE_POWER_SHIFT", "MOVE_ODOR_SLEUTH",
             "MOVE_WHIRLPOOL", "MOVE_FIRE_SPIN", "MOVE_SAND_TOMB", "MOVE_WRAP", "MOVE_BIND", "MOVE_CLAMP",
             "MOVE_INFESTATION", "MOVE_SNAP_TRAP", "MOVE_THUNDER_CAGE", "MOVE_MAGMA_STORM",
             "MOVE_FAIRY_LOCK", "MOVE_FORESTS_CURSE", "MOVE_TRICK_OR_TREAT", "MOVE_ROTOTILLER",
             "MOVE_FLOWER_SHIELD", "MOVE_GEAR_UP", "MOVE_MAGNETIC_FLUX", "MOVE_AROMATIC_MIST",
             "MOVE_EERIE_IMPULSE", "MOVE_VENOM_DRENCH", "MOVE_CRAFTY_SHIELD", "MOVE_MAT_BLOCK",
             "MOVE_QUICK_GUARD", "MOVE_WIDE_GUARD", "MOVE_KINGS_SHIELD", "MOVE_SPIKY_SHIELD",
             "MOVE_BANEFUL_BUNKER", "MOVE_OBSTRUCT", "MOVE_SILK_TRAP", "MOVE_BURNING_BULWARK",
             "MOVE_MAX_GUARD", "MOVE_STRENGTH_SAP", "MOVE_PURIFY", "MOVE_SPEED_SWAP", "MOVE_TOPSY_TURVY",
             "MOVE_PARTING_SHOT", "MOVE_HAPPY_HOUR", "MOVE_BELLY_DRUM", "MOVE_SHIFT_GEAR", "MOVE_COIL",
             "MOVE_CHARGE", "MOVE_DEFOG", "MOVE_RAPID_SPIN", "MOVE_COURT_CHANGE", "MOVE_SKETCH"}
# Status / set-up moves a generated set may take, best first (fits the Pokémon's better attacking side).
SETUP_PHYS = ["MOVE_SWORDS_DANCE", "MOVE_DRAGON_DANCE", "MOVE_BULK_UP", "MOVE_HONE_CLAWS"]
SETUP_SPEC = ["MOVE_NASTY_PLOT", "MOVE_CALM_MIND", "MOVE_QUIVER_DANCE"]
SUPPORT = ["MOVE_WILL_O_WISP", "MOVE_THUNDER_WAVE", "MOVE_TOXIC", "MOVE_LEECH_SEED", "MOVE_STUN_SPORE",
           "MOVE_SLEEP_POWDER", "MOVE_SPORE", "MOVE_ROOST", "MOVE_RECOVER", "MOVE_SLACK_OFF", "MOVE_SOFT_BOILED",
           "MOVE_MILK_DRINK", "MOVE_MOONLIGHT", "MOVE_SYNTHESIS", "MOVE_MORNING_SUN", "MOVE_PROTECT",
           "MOVE_STEALTH_ROCK", "MOVE_SPIKES", "MOVE_TOXIC_SPIKES", "MOVE_POISON_POWDER", "MOVE_GLARE"]
BAD_ABILITIES = {"ABILITY_TRUANT", "ABILITY_SLOW_START", "ABILITY_DEFEATIST", "ABILITY_KLUTZ", "ABILITY_STALL",
                 "ABILITY_RUN_AWAY", "ABILITY_HONEY_GATHER", "ABILITY_ILLUMINATE", "ABILITY_PICKUP",
                 "ABILITY_BALL_FETCH", "ABILITY_STENCH", "ABILITY_NONE", "ABILITY_FRISK", "ABILITY_ANTICIPATION",
                 "ABILITY_FOREWARN", "ABILITY_PLUS", "ABILITY_MINUS", "ABILITY_LEAF_GUARD", "ABILITY_SHED_SKIN",
                 "ABILITY_KEEN_EYE", "ABILITY_TANGLED_FEET", "ABILITY_BIG_PECKS", "ABILITY_SUCTION_CUPS",
                 "ABILITY_STICKY_HOLD", "ABILITY_OWN_TEMPO", "ABILITY_OBLIVIOUS", "ABILITY_INNER_FOCUS"}
TYPE_BOOSTER = {"TYPE_NORMAL": "Silk Scarf", "TYPE_FIRE": "Charcoal", "TYPE_WATER": "Mystic Water",
                "TYPE_GRASS": "Miracle Seed", "TYPE_ELECTRIC": "Magnet", "TYPE_ICE": "Never-Melt Ice",
                "TYPE_FIGHTING": "Black Belt", "TYPE_POISON": "Poison Barb", "TYPE_GROUND": "Soft Sand",
                "TYPE_FLYING": "Sharp Beak", "TYPE_PSYCHIC": "Twisted Spoon", "TYPE_BUG": "Silver Powder",
                "TYPE_ROCK": "Hard Stone", "TYPE_GHOST": "Spell Tag", "TYPE_DRAGON": "Dragon Fang",
                "TYPE_DARK": "Black Glasses", "TYPE_STEEL": "Metal Coat", "TYPE_FAIRY": "Fairy Feather"}
IVS = {"S1": 6, "S2": 9, "S3": 12, "S4": 15, "S5": 18, "S6": 20, "S7": 22, "S8": 25, "S9": 28, "POST": 31}


def first(pattern, text, default=None):
    m = re.search(pattern, text)
    return m.group(1) if m else default


class Data:
    def __init__(self):
        self.parents, self.abilities_set, _ = check_party.load_species_info()
        self.pool = check_party.species_pool()
        self.species = {}
        self.children = {}
        draconid = {k: int(v) for k, v in re.findall(r"#define (DRACONID_\w+)\s+(\d+)",
                                                       open(os.path.join(ROOT, "include/constants/draconid.h")).read())}
        for path in glob.glob(os.path.join(ROOT, "src/data/pokemon/species_info/*.h")):
            for m in re.finditer(r"\[SPECIES_(\w+)\]\s*=\s*\{(.*?)\n    \},", open(path).read(), re.S):
                name, body = m.group(1), m.group(2) + "\n"
                if name in self.species:
                    continue
                stats = {k: int(first(r"\.base%s\s*=\s*(\d+)" % k, body, 0)) for k in
                         ("HP", "Attack", "Defense", "Speed", "SpAttack", "SpDefense")}
                types = re.findall(r"TYPE_\w+", first(r"\.types\s*=\s*MON_TYPES\(([^)]*)\)", body, ""))
                abil = [a.strip() for a in first(r"\.abilities\s*=\s*\{([^}]*)\}", body, "").split(",") if a.strip()]
                self.species[name] = {"stats": stats, "types": types, "abilities": abil,
                                      "levelup": first(r"\.levelUpLearnset\s*=\s*(\w+)", body),
                                      "teach": first(r"\.teachableLearnset\s*=\s*(\w+)", body),
                                      "egg": first(r"\.eggMoveLearnset\s*=\s*(\w+)", body)}
                ev = re.search(r"\.evolutions\s*=\s*EVOLUTION\((.*?)\),\s*\n", body, re.S)
                if ev:
                    for method, param, child in re.findall(r"\{\s*(EVO_\w+)\s*,\s*([^,]+?)\s*,\s*SPECIES_(\w+)",
                                                           ev.group(1)):
                        param = str(draconid.get(param.strip(), param.strip()))
                        self.children.setdefault(name, []).append((method, param, child))
        text = open(check_party.levelup_file()).read()
        self.levelup = {m.group(1): [(int(lv), mv) for lv, mv in
                                     re.findall(r"LEVEL_UP_MOVE\(\s*(\d+),\s*(MOVE_\w+)\)", m.group(2))]
                        for m in re.finditer(r"(\w+)\[\]\s*=\s*\{(.*?)\};", text, re.S)}
        self.teach = {m.group(1): set(re.findall(r"MOVE_\w+", m.group(2))) - {"MOVE_UNAVAILABLE"}
                      for m in re.finditer(r"(\w+)\[\]\s*=\s*\{(.*?)\};",
                                           open(os.path.join(ROOT, "src/data/pokemon/teachable_learnsets.h")).read(), re.S)}
        self.eggs = {m.group(1): set(re.findall(r"MOVE_\w+", m.group(2))) - {"MOVE_UNAVAILABLE"}
                     for m in re.finditer(r"(\w+)\[\]\s*=\s*\{(.*?)\};",
                                          open(os.path.join(ROOT, "src/data/pokemon/egg_moves.h")).read(), re.S)}
        tms = open(os.path.join(ROOT, "include/constants/tms_hms.h")).read()
        self.tms = {"MOVE_" + n for n in re.findall(r"F\((\w+)\)", tms)}
        self.moves = {}
        for m in re.finditer(r"\[(MOVE_\w+)\]\s*=\s*\{(.*?)\n    \},", open(os.path.join(ROOT, "src/data/moves_info.h")).read(), re.S):
            body = m.group(2)
            self.moves[m.group(1)] = {
                "name": first(r'\.name\s*=\s*COMPOUND_STRING\("([^"]*)"\)', body, m.group(1)),
                "power": int(first(r"\.power\s*=\s*(?:[^?,\n]*\?\s*)?(\d+)", body, 0)),  # "GEN_x ? new : old"
                "type": first(r"\.type\s*=\s*(TYPE_\w+)", body, "TYPE_NORMAL"),
                "acc": int(first(r"\.accuracy\s*=\s*(?:[^?,\n]*\?\s*)?(\d+)", body, 100)),
                "cat": first(r"\.category\s*=\s*DAMAGE_CATEGORY_(\w+)", body, "STATUS"),
                "effect": first(r"\.effect\s*=\s*(EFFECT_\w+)", body, "EFFECT_HIT"),
                "recharge": "MOVE_EFFECT_RECHARGE" in body,
                "priority": int(first(r"\.priority\s*=\s*(-?\d+)", body, 0)),
            }
        # Everything check_party accepts (the expansion's union of TM / tutor / egg moves across games).
        self.all_learn = {k.upper(): set(v) for k, v in
                          json.load(open(os.path.join(ROOT, "src/data/pokemon/all_learnables.json"))).items()}

    def line(self, sp):
        """[sp, parent, grandparent, ...]"""
        out, seen = [sp], {sp}
        while out[-1] in self.parents and self.parents[out[-1]][0] not in seen:
            out.append(self.parents[out[-1]][0])
            seen.add(out[-1])
        return out

    def min_level(self, sp):
        """Lowest level for sp: level-up evolutions at their level; other evolutions (stone, trade,
        friendship) at NON_LEVEL_MIN or 8 above the parent's own minimum, whichever is higher (a baby's
        friendship evolution - Azurill -> Marill - has no minimum)."""
        if sp not in self.parents:
            return 1
        par, method, param = self.parents[sp]
        base = self.min_level(par)
        if method in LEVEL_EVOS and param.isdigit() and int(param) > 0:
            return max(base, int(param))
        if method in LEVEL_EVOS and par not in self.parents:
            return base  # a baby's friendship evolution (EVO_LEVEL 0 + condition): Azurill -> Marill
        if method == "EVO_SPLIT_FROM_EVO":
            return self.min_level(param.replace("SPECIES_", "")) if param.startswith("SPECIES_") else base
        return max(NON_LEVEL_MIN, base + 8)

    def stage(self, sp, level, evolve=True):
        """sp moved to the evolution stage `level` allows: devolved while below its minimum, evolved
        by plain level-up evolutions (first listed child; not EVO_LEVEL 0 = friendship / place / move
        conditions) while the level allows."""
        while self.min_level(sp) > level and sp in self.parents:
            sp = self.parents[sp][0]
        while evolve:
            nxt = [c for method, param, c in self.children.get(sp, [])
                   if method in LEVEL_EVOS and param.isdigit() and 0 < int(param) <= level and c in self.species]
            if not nxt:
                break
            sp = nxt[0]
        return sp

    def levelup_known(self, sp, level):
        """{move: level learned} for sp and its pre-evolutions, moves learned at or below `level`."""
        out = {}
        for s in self.line(sp):
            for lv, mv in self.levelup.get(self.species.get(s, {}).get("levelup"), []):
                if lv <= level:
                    out.setdefault(mv, lv)
        return out

    def default_moves(self, sp, level):
        """The game's default: the last four level-up moves of the species itself at `level`."""
        known = []
        for lv, mv in self.levelup.get(self.species[sp]["levelup"], []):
            if lv <= level:
                if mv in known:
                    known.remove(mv)
                known.append(mv)
        return known[-4:]

    def teachable(self, sp):
        out = set()
        for s in self.line(sp):
            out |= self.teach.get(self.species.get(s, {}).get("teach"), set())
        return out

    def egg_moves(self, sp):
        out = set()
        for s in self.line(sp):
            out |= self.eggs.get(self.species.get(s, {}).get("egg"), set())
        return out

    def other_learnable(self, sp):
        out = set()
        for s in self.line(sp):
            out |= self.all_learn.get(s, set())
        return out


def sp_const(name):
    return party.const_name(name, "SPECIES_")[len("SPECIES_"):]


def display(data, sp):
    """SPECIES_X -> the name trainers.party uses (from any existing block, else title case)."""
    return data.display.get(sp) or sp.replace("_", " ").title()


def legal(data, sp, level, seg, role, ace, move):
    """Can this Pokémon have `move` at this level under the segment rules? -> (ok, why)"""
    if move in data.levelup_known(sp, level):
        return True, "level"
    si = ORDER.index(seg)
    tm_ok = role in ("leader", "elite", "boss", "admin") or si >= ORDER.index("S4")
    if move in data.tms and move in data.teachable(sp):
        return (tm_ok, "tm")
    if move in data.egg_moves(sp):
        return (ace and si >= ORDER.index("S4") or role in ("elite", "boss"), "egg")
    if move in data.teachable(sp) or move in data.other_learnable(sp):
        # tutor moves, and moves the expansion lists as learnable in other games (check_party's
        # all_learnables.json; the earlier batches use them): late game only
        return (si >= ORDER.index("S7") or role in ("elite", "boss"), "tutor")
    return False, "unknown"


def power_ok(data, move, seg, role, ace):
    return not (ORDER.index(seg) < ORDER.index("S4") and data.moves[move]["power"] > 90
                and not (role == "leader" and ace))


def profile(data, sp):
    st = data.species[sp]["stats"]
    if st["Attack"] >= st["SpAttack"] * 1.15:
        return "phys"
    if st["SpAttack"] >= st["Attack"] * 1.15:
        return "spec"
    return "mixed"


def generate(data, sp, level, seg, role, ace, keep):
    """Fill `keep` (legal moves already chosen) up to four moves."""
    moves = list(keep)
    types = data.species[sp]["types"]
    prof = profile(data, sp)
    cands = set(data.levelup_known(sp, level))
    cands |= {m for m in data.teachable(sp) if legal(data, sp, level, seg, role, ace, m)[0]}
    cands |= {m for m in data.egg_moves(sp) if legal(data, sp, level, seg, role, ace, m)[0]}
    cands = {m for m in cands if m in data.moves and m not in BAD_MOVES
             and data.moves[m]["effect"] not in BAD_EFFECTS and not data.moves[m]["recharge"]
             and power_ok(data, m, seg, role, ace)}

    def score(m):
        mi = data.moves[m]
        if mi["cat"] == "STATUS" or mi["power"] < 30:
            return 0
        s = mi["power"] * min(mi["acc"] or 100, 100) / 100.0
        if mi["type"] in types:
            s *= 1.5
        if (prof == "phys" and mi["cat"] == "SPECIAL") or (prof == "spec" and mi["cat"] == "PHYSICAL"):
            s *= 0.55
        return s

    have_types = {data.moves[m]["type"] for m in moves if data.moves[m]["cat"] != "STATUS"}
    attacks = sorted((m for m in cands if score(m) > 0), key=score, reverse=True)
    # STAB first, one per own type
    for t in types:
        if t in have_types:
            continue
        for m in attacks:
            if data.moves[m]["type"] == t and m not in moves:
                moves.append(m)
                have_types.add(t)
                break
        if len(moves) >= 4:
            return moves[:4]
    # one status / set-up move if none yet
    has_status = any(data.moves[m]["cat"] == "STATUS" for m in moves)
    status = None
    if not has_status and ORDER.index(seg) >= ORDER.index("S3"):
        pref = (SETUP_PHYS if prof == "phys" else SETUP_SPEC if prof == "spec" else []) + SUPPORT
        for m in pref:
            if m in cands and m not in moves and not (m == "MOVE_WILL_O_WISP" and prof == "spec" and False):
                status = m
                break
    want_attacks = 4 - len(moves) - (1 if status else 0)
    for m in attacks:
        if want_attacks <= 0:
            break
        if m in moves or data.moves[m]["type"] in have_types:
            continue
        moves.append(m)
        have_types.add(data.moves[m]["type"])
        want_attacks -= 1
    if status:
        moves.append(status)
    for m in attacks:  # still short: any other attack
        if len(moves) >= 4:
            break
        if m not in moves:
            moves.append(m)
    return moves[:4]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-o", "--out", help="draft .party to write")
    ap.add_argument("--sources", help="sources sidecar to write (default: next to --out)")
    ap.add_argument("--explain", action="store_true")
    ap.add_argument("--check", nargs="+", metavar="PARTY",
                    help="only check these .party files: every move known at its level under the segment rules")
    args = ap.parse_args()

    data = Data()
    if args.check:
        seg = json.load(open(os.path.join(TRAINERS, "segments.json")))
        bad = 0
        for path in args.check:
            for tid, raw in party.split(open(path).read())[1]:
                b = party.parse_block(raw)
                info = seg["info"].get(tid, {"segment": "POST", "role": "elite"})
                for i, mon in enumerate(b["mons"]):
                    sp = sp_const(mon["species"])
                    ace = i == len(b["mons"]) - 1
                    for mv in mon["moves"]:
                        c = party.const_name(mv, "MOVE_")
                        ok, why = legal(data, sp, mon["level"], info["segment"], info["role"], ace, c)
                        if not ok or not power_ok(data, c, info["segment"], info["role"], ace):
                            print("%s %s Lv%d: %s (%s)" % (tid, mon["species"], mon["level"], mv, why))
                            bad += 1
        print("%d move(s) outside the rules" % bad)
        sys.exit(1 if bad else 0)
    matches = json.load(open(os.path.join(HERE, "oras_matches.json"), encoding="utf-8"))
    oras = json.load(open(os.path.join(HERE, "oras_trainers.json"), encoding="utf-8"))
    seg = json.load(open(os.path.join(TRAINERS, "segments.json")))
    import subprocess
    vanilla_text = subprocess.run(["git", "-C", ROOT, "show", "master:src/data/trainers.party"],
                                  capture_output=True, text=True).stdout
    vanilla = {t: party.parse_block(r) for t, r in party.split(vanilla_text)[1]}
    _, cur_blocks = party.split(open(os.path.join(ROOT, "src/data/trainers.party")).read())
    cur = {t: party.parse_block(r) for t, r in cur_blocks}
    raw = dict(cur_blocks)
    data.display = {}
    donors = []  # (species, level, segment, role, tid, mon)
    for tid, b in cur.items():
        for mon in b["mons"]:
            s = sp_const(mon["species"])
            data.display.setdefault(s, mon["species"])
            if tid in seg["info"] and not STORY.match(tid) and not seg["info"][tid]["story"]:
                donors.append((s, mon["level"], seg["info"][tid]["segment"], seg["info"][tid]["role"], tid, mon))

    def family(s):
        return data.line(s)[-1]

    chosen = []
    for tid, e in matches.items():
        if e["status"] not in ("exact", "class") or e["emerald_tiers"] or e["page"] == "oras_elitefour":
            continue
        g = oras["grouped"][e["oras"]["page"]][e["oras"]["index"]]
        team = [m for m in g["teams"][0]["mons"] if sp_const(m["species"]) in data.pool]
        of = {family(sp_const(m["species"])) for m in team}
        vf = {family(sp_const(m["species"])) for m in vanilla[tid]["mons"]}
        if len(of) > len(vf):
            chosen.append((tid, e, g, team))
        elif args.explain:
            print("keep   %-24s ORAS families %d <= vanilla %d" % (tid, len(of), len(vf)))

    out_blocks, sources, unchanged = [], {}, []
    for tid, e, g, team in chosen:
        b = cur[tid]
        info = seg["info"][tid]
        s, role = info["segment"], info["role"]
        levels = sorted(m["level"] for m in b["mons"])
        n = len(b["mons"])
        # ORAS order with the ace (highest level, last of equals) at the end
        top = max(m["level"] for m in team)
        ace_i = max(i for i, m in enumerate(team) if m["level"] == top)
        oras_order = [m for i, m in enumerate(team) if i != ace_i] + [team[ace_i]]
        fams = {family(sp_const(m["species"])) for m in oras_order}
        vfams = {family(sp_const(m["species"])) for m in vanilla[tid]["mons"]}
        # fill: one member per family, the Emerald team's own families first (the trainer's identity), then
        # the other current members; within a family the strongest (highest level) member
        def best_first(ms):
            return sorted(ms, key=lambda m: -m["level"])
        fill, seen = [], set(fams)
        for m in (best_first([m for m in b["mons"] if family(sp_const(m["species"])) in vfams]) +
                  [m for m in b["mons"] if family(sp_const(m["species"])) not in vfams]):
            f = family(sp_const(m["species"]))
            if f not in seen:
                fill.append(m)
                seen.add(f)
        fill += [m for m in b["mons"] if family(sp_const(m["species"])) not in fams and m not in fill]
        need = max(0, n - len(oras_order))
        # a small team keeps at least one Emerald family: one more slot if the party size band allows it
        if vfams - fams and not any(family(sp_const(m["species"])) in vfams for m in fill[:need]):
            band = {"S1": 3, "S2": 3, "S3": 4, "S4": 4, "S5": 5}.get(s, 5 if s in ("S6", "S7") else 6)
            if role == "gym":
                band = {"S1": 3, "S2": 3, "S3": 3, "S4": 4, "S5": 4}.get(s, 5 if s in ("S6", "S7") else 6)
            if n < band:
                n += 1
                need += 1
                levels = sorted(levels + [levels[0]])
        roster = [("oras", sp_const(m["species"]), None) for m in oras_order[:-1]]
        picked = sorted(fill[:need], key=b["mons"].index)
        roster += [("keep", sp_const(m["species"]), m) for m in picked]
        if len(roster) + 1 < n:  # still short: current members again, in order
            extra = [m for m in b["mons"] if m not in picked]
            roster += [("keep", sp_const(m["species"]), m) for m in extra[:n - 1 - len(roster)]]
        roster.append(("oras", sp_const(oras_order[-1]["species"]), None))
        # levels: kept members keep their own; the ace takes the top level (a kept former ace may tie);
        # the other ORAS members take the lowest levels left
        free = list(levels)
        free.remove(levels[-1])
        assign = [None] * len(roster)
        assign[-1] = levels[-1]
        for i, (kind, sp, mon) in enumerate(roster[:-1]):
            if kind == "keep":
                assign[i] = mon["level"]
                if mon["level"] in free:
                    free.remove(mon["level"])
                else:
                    free.pop(0)
        for i in range(len(roster) - 1):
            if assign[i] is None:
                assign[i] = free.pop(0)
        new_species = sorted(data.stage(sp, assign[i], evolve=kind == "oras") for i, (kind, sp, _) in enumerate(roster))
        if new_species == sorted(sp_const(m["species"]) for m in b["mons"]):
            unchanged.append(tid)
            print("same   %-24s the current team already has the ORAS species" % tid)
            continue
        lines = []
        head = raw[tid].split("\n\n")[0]
        lines.append(head.rstrip("\n"))
        iv = None
        for m in b["mons"]:
            if "ivs" in m:
                iv = m["ivs"]
                break
        if iv is None:
            base = IVS[s] + (4 if role == "gym" else 0)
            iv = "%d HP / %d Atk / %d Def / %d SpA / %d SpD / %d Spe" % ((base,) * 6)
        held = sum(1 for m in b["mons"] if m["item"])
        notes = []
        for i, (kind, sp0, mon) in enumerate(roster):
            level = assign[i]
            ace = i == len(roster) - 1
            sp = data.stage(sp0, level, evolve=kind == "oras")
            if kind == "keep" and sp == sp_const(mon["species"]) and mon["level"] == level:
                lines.append("\n".join(mon["lines"]))
                continue
            # donor: same trainer, then same segment + role, then nearest level anywhere
            def dscore(d):
                ds, dl, dseg, drole, dtid, dmon = d
                return (dtid != tid, dseg != s, (drole == "gym") != (role == "gym"), abs(dl - level) + (5 if dl > level + 2 else 0))
            cands = sorted((d for d in donors if d[0] == sp), key=dscore)
            donor = cands[0][5] if cands else None
            moves, dropped = [], []
            if donor:
                for mv in donor["moves"]:
                    c = party.const_name(mv, "MOVE_")
                    ok, why = legal(data, sp, level, s, role, ace, c)
                    if ok and c in data.moves and power_ok(data, c, s, role, ace):
                        moves.append(c)
                    else:
                        dropped.append("%s(%s)" % (mv, why))
            route_default = ORDER.index(s) < ORDER.index("S4") and role in ("route", "grunt")
            if route_default and not donor:
                moves = data.default_moves(sp, level)
            elif len(moves) < 4:
                moves = generate(data, sp, level, s, role, ace, moves)
            abil = None
            sab = data.species[sp]["abilities"]
            if donor and "ability" in donor:
                a = party.const_name(donor["ability"], "ABILITY_")
                if a in sab[:2] or (a in sab and role in ("leader", "elite", "boss")):
                    abil = a
            if abil is None:
                opts = [a for a in sab[:2] if a != "ABILITY_NONE"]
                good = [a for a in opts if a not in BAD_ABILITIES]
                abil = (good or opts or ["ABILITY_NONE"])[0]
            nature = donor.get("nature") if donor else None
            item = None
            if kind == "keep" and mon["item"]:
                item = mon["item"]
            elif ace and held:
                if ORDER.index(s) <= ORDER.index("S3"):
                    item = "Oran Berry"
                elif ORDER.index(s) <= ORDER.index("S6"):
                    stab = [data.moves[m]["type"] for m in moves if data.moves[m]["cat"] != "STATUS"
                            and data.moves[m]["type"] in data.species[sp]["types"]]
                    item = TYPE_BOOSTER.get(stab[0]) if stab else "Sitrus Berry"
                else:
                    item = donor["item"] if donor and donor["item"] else "Sitrus Berry"
            elif held > 1 and ORDER.index(s) >= ORDER.index("S4") and i == 0:
                item = "Sitrus Berry"
            name = display(data, sp)
            ml = ["%s%s" % (name, " @ " + item if item else ""), "Level: %d" % level]
            ml.append("Ability: %s" % abil[len("ABILITY_"):].replace("_", " ").title())
            ml.append("IVs: %s" % iv)
            if nature:
                ml.append("Nature: %s" % nature)
            for mv in moves:
                ml.append("- %s" % data.moves[mv]["name"])
            lines.append("\n".join(ml))
            notes.append("%s%s Lv%d%s%s" % (display(data, sp), "" if sp == sp0 else " (ORAS %s)" % display(data, sp0),
                                            level, " donor=%s Lv%d" % (cands[0][4][8:], cands[0][1]) if cands else " generated",
                                            " dropped " + ",".join(dropped) if dropped else ""))
        block = "=== %s ===\n" % tid + "\n\n".join(lines[0:1]).split("\n", 1)[1] + "\n\n" + "\n\n".join(lines[1:]) + "\n\n\n"
        out_blocks.append(block)
        sources[tid] = "oras-first"
        print("%-24s %-4s ORAS %s | vanilla %s" % (tid, s, ", ".join("%s %d" % (m["species"], m["level"]) for m in team),
                                                   ", ".join(m["species"] for m in vanilla[tid]["mons"])))
        for nline in notes:
            print("      " + nline)
    print("%d trainers rewritten, %d already had the ORAS species" % (len(out_blocks), len(unchanged)))
    if args.out:
        open(args.out, "w").write("".join(out_blocks))
        sp = args.sources or os.path.splitext(args.out)[0] + ".sources.json"
        json.dump(sources, open(sp, "w"), indent=1, sort_keys=True)


if __name__ == "__main__":
    main()
