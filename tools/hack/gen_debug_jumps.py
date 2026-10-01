#!/usr/bin/env python3
"""
gen_debug_jumps.py - the story state behind the debug menu's "Jump to act…" (debug builds; D-480 - D-489).

  python3 tools/hack/gen_debug_jumps.py              # write data/scripts/draconid/debug_jumps_state.inc
  python3 tools/hack/gen_debug_jumps.py --check      # exit 1 if that file is stale (a story change since)
  python3 tools/hack/gen_debug_jumps.py --show ACT3  # one stop: what it sets, and how it was chosen

The jump list itself (the menu, the warps, the party, the respawn points) is hand-written in
data/scripts/draconid/debug_jumps.pory; this writes the part that must follow the story, from the story
simulation of tools/hack/check_progression.py (table tools/hack/progression.json):

 - the state at each stop: the simulated flags, vars and bag after the walk to the stop's first scene (the
   state a real playthrough has when that scene is about to start). Every flag, var and story item the
   simulation writes anywhere in the story is set or cleared at every stop (the full state, so a jump backwards
   resets what came later too). Written as a chain: the first stop sets everything, each later one only what
   changed since the one before, and a stop runs the chain up to itself;
 - what the simulation does not model, from its own data (the walk's maps and the segments of
   tools/hack/trainers/segments.json): FLAG_VISITED_* of every town the walk has entered (Fly), and the trainer
   flags of the map trainers the story has walked past: a trainer is beaten once the walk has passed its map in
   its own segment or a later one (docs/hack_trainers.md; the segments are the level-cap steps);
 - the player's choices before the stop (CHOICES): kept if the save has made them, else the default given here;
 - Debug_EventScript_DraconidJumpProgress, how far a save has got (VAR_RESULT = the number of stops whose first
   scene it has played), for the "This rewinds the story" question. Each stop's marker is a flag or var its first
   scene moves on and no later leg moves back (picked from the simulation, checked against every leg).

Poké Balls stay out of the bag part (the jump tops them up with the medicine, src/draconid_debug_jumps.c);
temp flags/vars, special vars and object graphics vars are not state.
"""

import argparse
import difflib
import json
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(ROOT, "tools/hack"))
import check_progression as cp  # noqa: E402

OUT = os.path.join(ROOT, "data/scripts/draconid/debug_jumps_state.inc")
PORY = os.path.join(ROOT, "data/scripts/draconid/debug_jumps.pory")
SEGMENTS = os.path.join(ROOT, "tools/hack/trainers/segments.json")
DRACONID_H = os.path.join(ROOT, "include/constants/draconid.h")

# The stops, in story order: (id, the leg whose first scene starts the act, what the menu calls it). The jump
# sets the state of the walk's end just before that leg (the scene is about to start). The ids name the
# constants DRACONID_JUMP_STOP_<ID> (include/constants/draconid.h) and the labels of debug_jumps.pory.
STOPS = [
    ("WOODS", "1.13", "Act 1: Petalburg Woods (Nerine robs the researcher, Courtney)"),
    ("ACT2", "2.01", "Act 2: Rustboro (Nerine steals the Devon Goods)"),
    ("ACT3", "3.01", "Act 3: Meteor Falls (Maxie takes the meteorite)"),
    ("ACT4", "4.01", "Act 4: Petalburg (Wally at the Gym door, Norman)"),
    ("ACT5", "5.01", "Act 5: the Aqua Hideout (Nerine fight 5, Matt)"),
    ("REVENGE", "6.R1", "Sootopolis aftermath: Team Magma's revenge (Juan's Gym door)"),
    ("LEAGUE", "6.02", "Act 6: the Pokémon League (the door guards, the Elite Four)"),
    ("ELDER", "7.01", "Act 7: the Elder's call (the foot of the Sky Pillar)"),
    ("VILLAGE", "7.09", "Act 7: the attack on the village"),
    ("POSTGAME", "P.01", "Post-game: home after the SS Ticket (Nerine, Aster, Drake, Lance)"),
]

# The player's choices the jump keeps: (key, the leg where it is made, the value for a save that hasn't made it,
# why). Before that leg the key gets the simulation's value (the choice not made yet).
CHOICES = [
    ("VAR_STARTER_MON", "1.04", "DRACONID_EGG_DEINO", "the egg (a save from the bedroom has none yet)"),
    ("VAR_ASTER_EGG", "1.04", "DRACONID_EGG_DREEPY", "Aster's egg, the one Deino leaves (D-105)"),
    ("VAR_SECOND_STARTER", "1.17", "SECOND_STARTER_CHARMANDER", "Prof. Oak's partner: Charmander"),
    ("FLAG_DEVON_GOODS_RETURNED", "2.04", True, "the Devon Goods: returned (the simulation's way, D-258)"),
    ("FLAG_DRACONID_CAUGHT_REGIDRAGO", "7.03", False, "Regidrago not caught: it waits in the shrine depths"),
]

# Not state: the simulator's scratch, and keys the hand-written part sets (debug_jumps.pory)
SKIP_VARS = {"VAR_RESULT", "VAR_FACING", "VAR_PLAYER_OUTFIT", "VAR_MAXIE_CALL_STEPS"}
SKIP_FLAG_PREFIX = ("FLAG_DEBUG_",)
# Set by hand in Debug_EventScript_DraconidJumpCommon: gifts that follow the egg or Prof. Oak's partner (the
# simulation takes every branch of their switch and would hand out all of them), and Prof. Oak in Slateport, who
# is off the story table's path
BY_HAND = {
    ("flag", "FLAG_RECEIVED_OAK_Z_CRYSTAL"), ("flag", "FLAG_RECEIVED_KOMMONIUM_Z"),
    ("item", "ITEM_FIRIUM_Z"), ("item", "ITEM_WATERIUM_Z"), ("item", "ITEM_GRASSIUM_Z"), ("item", "ITEM_KOMMONIUM_Z"),
    ("item", "ITEM_CHARIZARDITE_X"), ("item", "ITEM_FERALIGITE"), ("item", "ITEM_SCEPTILITE"),
}
# value names for the story vars (the constants the scripts compare them with)
VALUE_PREFIX = {
    "VAR_DRACONID_STATE": "DRACONID_STATE_", "VAR_ASTER_STATE": "ASTER_STATE_", "VAR_BRENDAN_STATE": "BRENDAN_STATE_",
    "VAR_MAY_STATE": "MAY_STATE_", "VAR_WALLY_STATE": "WALLY_STATE_", "VAR_NERINE_STATE": "NERINE_STATE_",
    "VAR_MAGMA_STATE": "MAGMA_STATE_", "VAR_DRACONID_REPUTATION": "REPUTATION_",
    "VAR_DRACONID_FINALE_STATE": "FINALE_STATE_", "VAR_DRACONID_VILLAGE_STATE": "VILLAGE_STATE_",
    "VAR_MAXIE_CALL": "MAXIE_CALL_", "VAR_STARTER_MON": "DRACONID_EGG_", "VAR_ASTER_EGG": "DRACONID_EGG_",
    "VAR_SECOND_STARTER": "SECOND_STARTER_",
}
# marker preference: story vars first (their values only grow), then other vars, then flags
STORY_VARS = tuple(VALUE_PREFIX)
TEMP_CHOICE_VARS = ["VAR_TEMP_%X" % i for i in range(16)]
BEGIN = "@ ---- generated ----"


# ---------------------------------------------------------------------------
# names
# ---------------------------------------------------------------------------

class Names:
    """flag / var / item / trainer names for the simulator's numeric keys, in the headers' own order (the first
    Emerald name of a value; FRLG aliases and FLAG_UNUSED_* only if nothing else names it)"""

    def __init__(self, chk):
        self.chk = chk
        self.flags, self.vars = {}, {}
        for path, out, prefix in (("include/constants/flags.h", self.flags, "FLAG_"),
                                  ("include/constants/vars.h", self.vars, "VAR_")):
            for line in open(os.path.join(ROOT, path)):
                m = re.match(r"#define (%s\w+)\s" % prefix, line)
                if not m:
                    continue
                name = m.group(1)
                v = chk.c.value(name)
                if v is None or v <= 0:
                    continue
                weak = re.search(r"UNUSED|_FRLG$|_0x[0-9A-Fa-f]+$", name)
                if v not in out or (out[v][1] and not weak):
                    out[v] = (name, bool(weak))
        self.flags = {k: v[0] for k, v in self.flags.items()}
        self.vars = {k: v[0] for k, v in self.vars.items()}
        self.trainer_start = chk.c.value("TRAINER_FLAGS_START")
        self.trainers = {}
        for line in open(os.path.join(ROOT, "include/constants/opponents.h")):
            m = re.match(r"#define (TRAINER_\w+)\s", line)
            if m:
                v = chk.c.value(m.group(1))
                if v is not None and v not in self.trainers and not m.group(1).startswith("TRAINER_FLAGS"):
                    self.trainers[v] = m.group(1)
        self.values = {}
        for path in ("include/constants/draconid.h", "include/constants/outfits.h"):
            for line in open(os.path.join(ROOT, path)):
                m = re.match(r"#define (\w+)\s+(\d+)\b", line)
                if m and not m.group(1).endswith("_COUNT"):
                    self.values.setdefault(m.group(1), int(m.group(2)))

    def flag(self, key):
        if isinstance(key, str):
            return key
        if self.trainer_start is not None and key >= self.trainer_start and key - self.trainer_start in self.trainers:
            return self.trainers[key - self.trainer_start]
        return self.flags.get(key, "FLAG_0x%X" % key)

    def var(self, key):
        return key if isinstance(key, str) else self.vars.get(key, "VAR_0x%X" % key)

    def value(self, var, v):
        """a var's value as the constant the scripts use, where one names it"""
        prefix = VALUE_PREFIX.get(var)
        if prefix and isinstance(v, int):
            for name, val in self.values.items():
                if name.startswith(prefix) and val == v:
                    return name
        return str(v)

    def item(self, token):
        t, seen = token, 0
        while not t.startswith("ITEM_") and t in self.chk.c.raw and seen < 8:
            t, seen = self.chk.c.raw[t].strip(), seen + 1
        return t


def item_pockets():
    pockets, cur = {}, None
    for line in open(os.path.join(ROOT, "src/data/items.h")):
        m = re.match(r"\s*\[(ITEM_\w+)\]\s*=", line)
        if m:
            cur = m.group(1)
        m = re.search(r"\.pocket\s*=\s*(POCKET_\w+)", line)
        if m and cur:
            pockets[cur] = m.group(1)
    return pockets


# ---------------------------------------------------------------------------
# the simulation
# ---------------------------------------------------------------------------

class Hooks:
    """check_progression.run_story hooks: each leg's state at its end (after the walk), the maps it passed, and the
    state just after the first scene of a leg"""

    def __init__(self):
        self.end, self.maps, self.visited, self.after = {}, {}, {}, {}
        self.scene_maps = {}

    def scene(self, leg, e, st, target, pos, scene_map, view):
        self.scene_maps.setdefault(leg["id"], set()).add(scene_map)

    def scene_after(self, leg, e, st):
        self.after.setdefault(leg["id"], st.flattened())

    def leg_end(self, leg, res, st, pos, visited):
        self.end[leg["id"]] = st
        self.maps[leg["id"]] = set(getattr(res, "path_maps", None) or []) | self.scene_maps.get(leg["id"], set())
        self.visited[leg["id"]] = set(visited)


def simulate():
    table = json.load(open(cp.TABLE))
    chk = cp.Checker("MALE")  # the story state doesn't depend on the gender (only scratch vars do)
    hooks = Hooks()
    cp.run_story(chk, table, hooks=hooks)
    return chk, table, hooks


def is_state_flag(names, key):
    if isinstance(key, str):
        return False
    temp_end = names.chk.c.value("TEMP_FLAGS_END")
    special = names.chk.c.value("SPECIAL_FLAGS_START")
    if key <= temp_end or key >= special:
        return False
    return not names.flag(key).startswith(SKIP_FLAG_PREFIX)


def is_state_var(names, key):
    if isinstance(key, str):
        return False
    c = names.chk.c
    if key < c.value("VARS_START") or key >= c.value("SPECIAL_VARS_START"):
        return False
    if c.value("TEMP_VARS_START") <= key <= c.value("TEMP_VARS_END"):
        return False
    name = names.var(key)
    return not (name.startswith("VAR_OBJ_GFX_ID_") or name in SKIP_VARS)


def badge_count(st, chk):
    return sum(1 for b in cp.BADGES if st.flag(chk.sim.fkey(b)) is True)


def segment_index(st, chk):
    """the level-cap step of a state: badges + 1 (S1 - S9), 10 after the Champion (POST)"""
    if st.flag(chk.sim.fkey("FLAG_IS_CHAMPION")) is True:
        return 10
    return badge_count(st, chk) + 1


def seg_of(name):
    return 10 if name == "POST" else int(name[1:])


def map_trainers(world):
    """trainer -> map, for the trainers on the maps (their object scripts' trainerbattle, rematches aside)"""
    out = {}
    rx = re.compile(r"^\s*trainerbattle_(?:single|double|no_intro|earlyrival|lavaridge)\s+(TRAINER_\w+)(?:\s*,\s*(TRAINER_\w+))?")
    by_name = {md.name: mid for mid, md in world.maps.items()}
    for d in sorted(os.listdir(os.path.join(ROOT, "data/maps"))):
        path = os.path.join(ROOT, "data/maps", d, "scripts.inc")
        if not os.path.exists(path) or d not in by_name:
            continue
        for line in open(path):
            m = rx.match(line)
            if m:
                for t in m.groups():
                    if t and t not in out:
                        out[t] = by_name[d]
    return out


class Story:
    def __init__(self):
        self.chk, self.table, self.hooks = simulate()
        self.names = Names(self.chk)
        self.legs = [lg for lg in self.table["legs"]]
        self.main = [lg["id"] for lg in self.legs if not lg.get("side")]
        self.index = {lid: i for i, lid in enumerate(self.main)}
        self.pockets = item_pockets()
        seg = json.load(open(SEGMENTS))
        self.trainer_seg = {t: seg_of(v["segment"]) for t, v in seg["info"].items()}
        # the map trainers the walk passes. Story fights (rivals, admins, the Draconids' side battles) and every
        # trainer a scene of the table fights (MATT, the gym leaders) only from the simulation: such a flag set before
        # its scene would skip the scene's battle
        fought = set()
        for st in self.hooks.end.values():
            fought |= {self.names.flag(k) for k in st.flags.keys() if not isinstance(k, str)}
        self.trainer_map = {t: m for t, m in map_trainers(self.chk.world).items()
                            if t in self.trainer_seg and not seg["info"][t].get("story") and t not in fought}
        self.leg_seg = {lid: segment_index(self.hooks.end[lid], self.chk) for lid in self.main}
        self.towns = {}
        for mid in self.chk.world.maps:
            flag = "FLAG_VISITED_" + mid[len("MAP_"):]
            v = self.chk.c.value(flag)
            if v:
                self.towns[mid] = flag
        self.check_table()

    def check_table(self):
        for sid, leg, _ in STOPS:
            if leg not in self.index:
                sys.exit("gen_debug_jumps: stop %s names leg %s, which isn't a main leg of progression.json" % (sid, leg))
            if self.index[leg] == 0:
                sys.exit("gen_debug_jumps: stop %s can't be the first leg" % sid)
        for key, leg, _, _ in CHOICES:
            if leg not in self.index:
                sys.exit("gen_debug_jumps: choice %s names leg %s, which isn't a main leg" % (key, leg))

    def prev(self, leg):
        return self.main[self.index[leg] - 1]

    # --- one state as {name: value} ---------------------------------------------
    def desired(self, leg):
        """the state a jump to `leg` sets: ({("flag"|"var"|"trainer"|"item", name): value}, the keys the simulation
        lost track of there (UNK: left as the save has them))"""
        before = self.prev(leg)
        st = self.hooks.end[before]
        out, unknown = {}, set()
        n = self.names
        for k, v in st.flags.items():
            if is_state_flag(n, k):
                name = n.flag(k)
                key = ("trainer" if name.startswith("TRAINER_") else "flag", name)
                if name.startswith("FLAG_DECLINED_"):
                    # written on a YES/NO's NO side, which the simulation keeps beside the YES side's battle: a jump
                    # takes the YES (the battle fought, the bike taken)
                    out[key] = False
                elif v == cp.UNK:
                    unknown.add(key)
                else:
                    out[key] = bool(v)
        for k, v in st.vars.items():
            if is_state_var(n, k):
                if v == cp.UNK:
                    unknown.add(("var", n.var(k)))
                else:
                    out[("var", n.var(k))] = v
        for k, v in st.items.items():
            name = n.item(k)
            if self.pockets.get(name) == "POCKET_POKE_BALLS":
                continue
            if v == cp.UNK:
                unknown.add(("item", name))
            else:
                out[("item", name)] = out.get(("item", name), 0) + v
        # not simulated: Fly (the towns the walk entered) and the map trainers the walk passed
        visited = self.hooks.visited[before]
        for mid, flag in self.towns.items():
            if mid in visited:
                out[("flag", flag)] = True
            else:
                out.setdefault(("flag", flag), False)
        passed = {}  # map -> the highest segment it was passed in
        for lid in self.main[:self.index[before] + 1]:
            for m in self.hooks.maps.get(lid, ()):
                passed[m] = max(passed.get(m, 0), self.leg_seg[lid])
        for t, m in self.trainer_map.items():
            if ("trainer", t) in out:
                continue  # a story battle the simulation fought
            out[("trainer", t)] = passed.get(m, 0) >= self.trainer_seg[t]
        return ({k: v for k, v in out.items() if self.is_state_key(k)},
                {k for k in unknown if self.is_state_key(k)})

    def is_state_key(self, key):
        """not set by hand (BY_HAND), and an item key names an item (giveitem VAR_0x8004 the simulation couldn't
        resolve is not one)"""
        return key not in BY_HAND and (key[0] != "item" or key[1].startswith("ITEM_"))

    def universe(self):
        """every key a stop's state names, plus every key any leg of the story writes (so a jump back from later
        than the last stop resets it too)"""
        keys = set()
        for sid, leg, _ in STOPS:
            known, unknown = self.desired(leg)
            keys |= set(known) | unknown
        n = self.names
        for lid in self.main:
            st = self.hooks.end[lid]
            keys |= {("trainer" if n.flag(k).startswith("TRAINER_") else "flag", n.flag(k))
                     for k, v in st.flags.items() if is_state_flag(n, k)}
            keys |= {("var", n.var(k)) for k, v in st.vars.items() if is_state_var(n, k)}
            keys |= {("item", n.item(k)) for k in st.items.keys() if self.pockets.get(n.item(k)) != "POCKET_POKE_BALLS"}
        return {k for k in keys if self.is_state_key(k)}

    # --- markers ----------------------------------------------------------------
    def marker(self, leg):
        """a flag or var the leg's first scene moves on and that stays moved on for every later leg end, and is not
        there at any earlier one: (kind, name, value)"""
        before = self.hooks.end[self.prev(leg)]
        after = self.hooks.after[leg]
        i = self.index[leg]
        earlier = [self.hooks.end[lid] for lid in self.main[:i]]
        later = [self.hooks.end[lid] for lid in self.main[i:]]
        n = self.names
        cands = []
        for k, v in after.vars.items():
            if not is_state_var(n, k) or not isinstance(v, int):
                continue
            b = before.vars.get(k, 0)
            if not isinstance(b, int) or v <= b:
                continue
            name = n.var(k)
            if any(not isinstance(s.vars.get(k, 0), int) or s.vars.get(k, 0) >= v for s in earlier):
                continue
            if any(not isinstance(s.vars.get(k, 0), int) or s.vars.get(k, 0) < v for s in later):
                continue
            rank = 0 if name in STORY_VARS else 1
            cands.append((rank, name, ("var", name, v)))
        for k, v in after.flags.items():
            if not is_state_flag(n, k) or v is not True or before.flags.get(k, False) is not False:
                continue
            if any(s.flags.get(k, False) is not False for s in earlier) or any(s.flags.get(k, False) is not True for s in later):
                continue
            name = n.flag(k)
            cands.append((2 if name.startswith("FLAG_") else 3, name, ("trainer" if name.startswith("TRAINER_") else "flag", name, True)))
        if not cands:
            sys.exit("gen_debug_jumps: no flag or var marks leg %s as played (none is moved on there for good)" % leg)
        return sorted(cands)[0][2]


# ---------------------------------------------------------------------------
# output
# ---------------------------------------------------------------------------

def emit_set(names, kind, name, value):
    m = re.match(r"(?:FLAG|VAR)_(0x[0-9A-F]+)$", name)
    if m:
        name = m.group(1)  # no name in the headers: its number
    if kind == "flag":
        return "\t%s %s" % ("setflag" if value else "clearflag", name)
    if kind == "trainer":
        return "\t%s %s" % ("settrainerflag" if value else "cleartrainerflag", name)
    if kind == "var":
        return "\tsetvar %s, %s" % (name, names.value(name, value))
    return ("\tsetvar VAR_0x8004, %s\n\tsetvar VAR_0x8005, %d\n\tcallnative Draconid_DebugJumpSetItem" % (name, value))


def key_order(k):
    order = {"flag": 0, "trainer": 1, "var": 2, "item": 3}
    return (order[k[0]], k[1])


def marker_test(names, m, false_label):
    kind, name, value = m
    if kind == "flag":
        return "\tgoto_if_unset %s, %s" % (name, false_label)
    if kind == "trainer":
        return "\tchecktrainerflag %s\n\tgoto_if FALSE, %s" % (name, false_label)
    return "\tgoto_if_lt %s, %s, %s" % (name, names.value(name, value), false_label)


def marker_text(m):
    kind, name, value = m
    return name if kind != "var" else "%s >= %s" % (name, value)


def stop_constants():
    vals = {}
    for line in open(DRACONID_H):
        m = re.match(r"#define (DRACONID_JUMP_STOP_\w+)\s+(\d+)", line)
        if m:
            vals[m.group(1)] = int(m.group(2))
    return vals


def generate(story):
    names = story.names
    consts = stop_constants()
    problems = []
    for i, (sid, leg, _) in enumerate(STOPS):
        if consts.get("DRACONID_JUMP_STOP_" + sid) != i:
            problems.append("include/constants/draconid.h: DRACONID_JUMP_STOP_%s should be %d" % (sid, i))
    if consts.get("DRACONID_JUMP_STOP_COUNT") != len(STOPS):
        problems.append("include/constants/draconid.h: DRACONID_JUMP_STOP_COUNT should be %d" % len(STOPS))
    if problems:
        sys.exit("gen_debug_jumps: " + "; ".join(problems))
    choice_keys = {("flag" if k.startswith("FLAG_") else "var", k) for k, _, _, _ in CHOICES}
    universe = story.universe() | choice_keys
    states = []
    for sid, leg, _ in STOPS:
        known, unknown = story.desired(leg)
        i = story.index[leg]
        full = {}
        for key in universe:
            if key in choice_keys:
                cleg = next(c[1] for c in CHOICES if c[0] == key[1])
                if story.index[cleg] < i:
                    continue  # made before the stop: the stop's choice code sets it
            if key in known:
                full[key] = known[key]
            elif key in choice_keys or key not in unknown:
                # not written by then: the new game's value (a choice not made yet: none)
                full[key] = {"flag": False, "trainer": False, "var": 0, "item": 0}[key[0]]
            # else the simulation lost track of it there (a branch it can't decide): left as the save has it
        states.append(full)

    out = []
    w = out.append
    w("@ Generated by tools/hack/gen_debug_jumps.py - do not edit: change the story, then rerun it")
    w("@ (python3 tools/hack/gen_debug_jumps.py; --check fails while this file is stale).")
    w("@ The story state behind the debug menu's \"Jump to act...\" (debug builds only; the menu, the warps and the")
    w("@ party are in debug_jumps.pory; D-480 - D-489). Each stop's state is check_progression.py's simulated state at")
    w("@ the end of the walk to the stop's first scene, plus FLAG_VISITED_* for the towns that walk entered and the")
    w("@ trainer flags of the map trainers it passed (in their own level-cap segment or later).")
    w("")
    # --- progress -------------------------------------------------------------------
    w("@ VAR_RESULT = how many stops this save has started: the first scene of each has a marker that its scene")
    w("@ moves on and no later part of the story moves back.")
    w("Debug_EventScript_DraconidJumpProgress::")
    w("\tsetvar VAR_RESULT, 0")
    for i, (sid, leg, _) in enumerate(STOPS):
        m = story.marker(leg)
        w("\t@ %s %s: %s" % (sid, leg, marker_text(m)))
        w(marker_test(names, m, "Debug_EventScript_DraconidJumpProgress_Done"))
        w("\tsetvar VAR_RESULT, %d" % (i + 1))
    w("Debug_EventScript_DraconidJumpProgress_Done:")
    w("\treturn")
    w("")
    # --- choices --------------------------------------------------------------------
    legs = []
    for key, leg, _, _ in CHOICES:
        if leg not in legs:
            legs.append(leg)
    slots = {}
    w("@ The player's own choices, read before a jump overwrites the state: VAR_TEMP_<n> = 1 once the save has made")
    w("@ the choice, and the value it made in the next VAR_TEMP (flags: 1 set, 0 clear).")
    w("Debug_EventScript_DraconidJumpKeepChoices::")
    n = 0
    for leg in legs:
        made = TEMP_CHOICE_VARS[n]
        n += 1
        m = story.marker(leg)
        label = "Debug_EventScript_DraconidJumpKeepChoices_%s" % leg.replace(".", "_")
        w("\t@ made in %s (%s)" % (leg, marker_text(m)))
        w("\tsetvar %s, 0" % made)
        w(marker_test(names, m, label))
        w("\tsetvar %s, 1" % made)
        for key, _, _, _ in [c for c in CHOICES if c[1] == leg]:
            slot = TEMP_CHOICE_VARS[n]
            n += 1
            slots[key] = (made, slot)
            if key.startswith("FLAG_"):
                w("\tsetvar %s, 0" % slot)
                w("\tcall_if_set %s, Debug_EventScript_DraconidJumpKeepChoices_%s" % (key, slot))
            else:
                w("\tcopyvar %s, %s" % (slot, key))
        w("%s:" % label)
    w("\treturn")
    for key, (made, slot) in slots.items():
        if key.startswith("FLAG_"):
            w("Debug_EventScript_DraconidJumpKeepChoices_%s:" % slot)
            w("\tsetvar %s, 1" % slot)
            w("\treturn")
    w("")
    w("@ A choice made before a stop: the save's own if it has made it, else the default")
    for leg in legs:
        w("Debug_EventScript_DraconidJumpChoices_%s:" % leg.replace(".", "_"))
        for key, cleg, default, why in CHOICES:
            if cleg != leg:
                continue
            made, slot = slots[key]
            lab = "Debug_EventScript_DraconidJumpChoices_%s_%s" % (leg.replace(".", "_"), key)
            w("\t@ %s: else %s" % (key, why))
            if key.startswith("FLAG_"):
                w("\t%s %s" % ("setflag" if default else "clearflag", key))
                w("\tgoto_if_ne %s, 1, %s" % (made, lab))
                w("\tclearflag %s" % key)
                w("\tgoto_if_ne %s, 1, %s" % (slot, lab))
                w("\tsetflag %s" % key)
            else:
                w("\tsetvar %s, %s" % (key, default))
                w("\tgoto_if_ne %s, 1, %s" % (made, lab))
                w("\tcopyvar %s, %s" % (key, slot))
            w("%s:" % lab)
        w("\treturn")
    w("")
    # --- the stops ------------------------------------------------------------------------
    for i, (sid, leg, title) in enumerate(STOPS):
        w("@ %s - %s" % (sid, title))
        w("@ the state before leg %s (%s's walk: %s)" % (leg, story.prev(leg), ", ".join(sorted(
            story.chk.world.pretty(m) for m in story.hooks.maps.get(story.prev(leg), ())))))
        w("Debug_EventScript_DraconidJumpState_%s::" % sid)
        for j in range(i + 1):
            w("\tcall Debug_EventScript_DraconidJumpStep_%s" % STOPS[j][0])
        for cleg in legs:
            if story.index[cleg] < story.index[leg]:
                w("\tcall Debug_EventScript_DraconidJumpChoices_%s" % cleg.replace(".", "_"))
        w("\treturn")
        w("")
    for i, (sid, leg, title) in enumerate(STOPS):
        full = states[i]
        base = states[i - 1] if i else {}
        changed = sorted((k for k in full if i == 0 or base.get(k) != full[k]), key=key_order)
        w("@ %s: %s" % (sid, "the whole state" if i == 0 else "what changed since %s (%d)" % (STOPS[i - 1][0], len(changed))))
        w("Debug_EventScript_DraconidJumpStep_%s:" % sid)
        for k in changed:
            w(emit_set(names, k[0], k[1], full[k]))
        w("\treturn")
        w("")
    return "\n".join(out) + "\n"


def show(story, sid):
    leg = next((l for s, l, _ in STOPS if s == sid), None)
    if leg is None:
        sys.exit("gen_debug_jumps: no stop %s (%s)" % (sid, ", ".join(s for s, _, _ in STOPS)))
    d, unknown = story.desired(leg)
    print("%s: the state before leg %s (end of %s); marker %s" % (sid, leg, story.prev(leg), marker_text(story.marker(leg))))
    for k in sorted(d, key=key_order):
        v = d[k]
        if (k[0] in ("flag", "trainer") and v) or (k[0] in ("var", "item") and v):
            print("  %-8s %-50s %s" % (k[0], k[1], story.names.value(k[1], v) if k[0] == "var" else v))
    for k in sorted(unknown, key=key_order):
        print("  %-8s %-50s (unknown: left as the save has it)" % k)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true", help="exit 1 if the generated file is stale")
    ap.add_argument("--show", metavar="STOP", help="print one stop's state (what is set; cleared keys aside)")
    args = ap.parse_args()
    story = Story()
    if args.show:
        show(story, args.show.upper())
        return 0
    text = generate(story)
    current = open(OUT).read() if os.path.exists(OUT) else ""
    if args.check:
        if text != current:
            diff = list(difflib.unified_diff(current.splitlines(), text.splitlines(), "committed", "generated", lineterm="", n=1))
            print("\n".join(diff[:60]))
            print("STALE   %s: rerun python3 tools/hack/gen_debug_jumps.py (%d changed lines)" % (
                os.path.relpath(OUT, ROOT), sum(1 for l in diff if l[:1] in "+-") - 2))
            return 1
        print("OK      %s matches the story simulation (%d stops)" % (os.path.relpath(OUT, ROOT), len(STOPS)))
        return 0
    if text != current:
        open(OUT, "w").write(text)
        print("wrote %s (%d lines)" % (os.path.relpath(OUT, ROOT), text.count("\n")))
    else:
        print("%s is up to date" % os.path.relpath(OUT, ROOT))
    return 0


if __name__ == "__main__":
    sys.exit(main())
