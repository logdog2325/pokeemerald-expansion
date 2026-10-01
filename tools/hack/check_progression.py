#!/usr/bin/env python3
"""
check_progression.py - story-lock checker: can the player walk every leg of the v2 story?

  python3 tools/hack/check_progression.py                 # every leg + the warp check, exit 1 on a lock
  python3 tools/hack/check_progression.py --leg 4.07      # one leg (id or a word of its name), with its path
  python3 tools/hack/check_progression.py --list          # the story table (legs, scenes, HMs/badges)
  python3 tools/hack/check_progression.py --markdown      # the leg table for docs/hack_progression.md
  python3 tools/hack/check_progression.py -v              # also scenes passed on the way, guesses, map-load notes
  python3 tools/hack/check_progression.py --state 3.05    # the simulated flags/vars at a leg (after its scenes)

The story table is tools/hack/progression.json: ordered legs in v2 story order (Act 1 to the post-game), each
naming the scene(s) that happen before it (script labels) and the badges/HMs the player has by then; after its
scenes the player walks to where the next leg's first scene starts. "side" legs (ways back, the way on) are
checked and then undone. Leg fields: scenes, to, via (waypoints walked through first; entering a map runs its
load scripts for real), from, side, have; scene fields: at / map / talk (where it starts), then (where it
leaves the player; branches that warp elsewhere give way), expect, pre (+ why: what C code does first), enter.
Table fields: start, assume (the value a specialvar's C function gives, e.g. HasAllHoennMons), puzzles,
no_heal_ok (check_hardlock.py). For every leg the checker

 1. simulates the flags/vars/bag: new game (EventScript_ResetAllMapFlags, the Draconid new-game setup), then
    every scene of every leg so far, statically: setflag/clearflag/setvar/addvar/subvar/copyvar,
    removeobject (= set that object's flag), giveitem/additem/removeitem/checkitem, trainer battles (= the
    trainer's flag, then the continue script), following call/goto/call_if_*/goto_if_*/switch and the labels
    Poryscript generates; entering a map runs its OnTransition/OnLoad/OnResume scripts. A condition the
    simulated state decides takes one branch; an unknown one (a YES/NO, a multichoice, a battle's outcome)
    takes both – a value written on one side only is kept (the player takes the path that moves the story
    on), values that differ become unknown – and is reported as a guess (-v); a branch cut short in a loop or
    repeating a state already seen gives way to the other. A warp after a branch on the player's answer
    (VAR_RESULT, Poryscript's compare + goto_if included) is only a "may warp": the table says where ("then"). What C code does is given in the table ("pre",
    "assume") or known here: the cable car's warp, the Hall of Fame's and the credits' way home (GameClear sets
    FLAG_SYS_GAME_CLEAR), a menu special's VAR_RESULT. Enum constants (SS_TIDAL_*, DIR_*) are read from the
    headers too, and the player's scripted movement is followed (applymovement, getplayerxy), so a scene's next
    walk starts where it leaves the player;
 2. checks that each scene can start: its object is shown, its coord trigger's var matches, its OnFrame
    entry is the first one due after the map's load scripts (and an object an OnWarp table adds counts as
    shown); that it sets what the table expects (flags, VAR=VALUE, ITEM_X, TRAINER_X defeated); that an OnFrame
    scene moves its var on (else it starts again every frame: a softlock); and that a "then" is a place the
    scene really warps to;
 3. searches the tiles (breadth first) from where the player is to where the next scene starts, across
    maps (connections, warps as field_control_avatar.c takes them – doors walked into from below, arrows
    stepped off the way they point –, dive/emerge incl. setdivewarp, holes, Fly from outdoors to towns
    reached before), on each map's grid after its load scripts ran on the simulated state (setmetatile,
    setmaplayoutindex, setobjectxyperm, setholewarp, temp flags/vars cleared first). Blocked by: collision,
    elevation, ledges (one way), directionally impassable tiles, objects whose flag is clear (unless talking
    to them removes them or sends them elsewhere – an item ball, a Devon Scope Kecleon, a guard who steps
    aside), coord triggers whose var matches and whose script walks the player back without moving the var
    on, water / waterfalls / dive spots / Strength boulders / Rock Smash rocks / Cut trees unless the player
    has that HM **and** its badge (field_move.c; knowing the move is not needed), Acro Bike rails / bumpy
    slopes and Mach Bike mud slopes unless a bike is in the bag. A blocked leg is searched again with every
    obstacle passable at a high cost: the first obstacle on the cheapest path is reported with what clears
    it (the flag/var and the scripts that write it). If a coord scene the player can reach clears the way
    it is triggered; one off the path is a detour the story doesn't lead to (reported as DTOR);
 4. checks every warp/warpsilent/warpdoor/... destination of the round 1 scripts (data/scripts/draconid,
    new maps' scripts.pory, `@ Draconid Emerald` lines) and of the table's scenes: the tile is walkable and
    connects to an exit of the map (no closed pocket).

Not modelled (a note where they matter): gym puzzles (the table's "puzzles": only getting in is checked),
sea currents, the party (a "do you have a Pokémon that knows ..." branch is a guess), wild battles, which
places a Pokémon Center visit or a whiteout returns the player to (tools/hack/check_hardlock.py checks those).
run_story(hooks=...) lets check_hardlock.py see the state before and after each scene and at each leg's end.
"""

import argparse
import glob
import heapq
import json
import os
import re
import subprocess
import sys
import tempfile
from collections import deque

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(ROOT, "tools/hack/mapgen"))
import pokemap  # noqa: E402

TABLE = os.path.join(ROOT, "tools/hack/progression.json")

UNK = "?"          # an unknown flag/var value in the simulator
LOOP = object()    # a jump the simulator stops following (the label was visited too often in this scene)
PENALTY = 1000     # cost of crossing an obstacle in the "what blocks it" search
STEP_BUDGET = 60000  # commands per scene before the simulator gives up (loops)
MAX_FORK_DEPTH = 40  # unknown branches followed on both sides, nested
SIDE_BUDGET = 3000   # the same for a script run only to see whether an object or trigger is in the way

# ---------------------------------------------------------------------------
# Constants: the project's own headers through the C preprocessor (#if IS_FRLG etc. resolved)
# ---------------------------------------------------------------------------

HEADERS = ["global.h", "constants/flags.h", "constants/vars.h", "constants/opponents.h", "constants/draconid.h",
           "constants/metatile_labels.h", "constants/maps.h", "constants/layouts.h", "constants/event_objects.h",
           "constants/battle_partner.h", "constants/trainer_types.h", "constants/map_scripts.h",
           "constants/outfits.h", "constants/weather.h", "constants/battle.h", "constants/field_specials.h",
           "constants/script_menu.h", "constants/items.h", "constants/species.h", "constants/moves.h",
           "constants/heal_locations.h", "constants/pokemon.h", "constants/trainers.h", "constants/battle_frontier.h"]
FALLBACK = {"TRUE": 1, "FALSE": 0, "YES": 1, "NO": 0, "MALE": 0, "FEMALE": 1, "NULL": 0}


class Constants:
    def __init__(self):
        self.raw = {}
        self.cache = dict(FALLBACK)
        src = "".join('#include "%s"\n' % h for h in HEADERS)
        cmd = ["arm-none-eabi-gcc", "-E", "-mthumb", "-mabi=apcs-gnu", "-std=gnu17", "-DMODERN=1", "-DTESTING=0",
               "-iquote", os.path.join(ROOT, "include")]
        try:
            with tempfile.TemporaryDirectory() as td:
                c = os.path.join(td, "consts.c")
                open(c, "w").write(src)
                out = subprocess.run(cmd[:2] + ["-dM"] + cmd[2:] + [c], capture_output=True, text=True, check=True).stdout
                code = subprocess.run(cmd + [c], capture_output=True, text=True, check=True).stdout
        except (OSError, subprocess.CalledProcessError) as e:
            sys.exit("check_progression: the C preprocessor failed (%s); run tools/hack/install_tools.sh" % e)
        for line in out.splitlines():
            m = re.match(r"#define (\w+) (.*)$", line)
            if m:
                self.raw[m.group(1)] = m.group(2).strip()
        self._enums(code)

    def _enums(self, code):
        """enum constants (SS_TIDAL_*, DIR_*, …): the scripts use them like #defines"""
        code = re.sub(r"^#.*$", "", code, flags=re.M)
        for body in re.findall(r"\benum\b[^{};]*\{([^{}]*)\}", code):
            nxt = 0
            for item in body.split(","):
                item = item.strip()
                if not item:
                    continue
                name, _, expr = item.partition("=")
                name = name.strip()
                if not re.fullmatch(r"[A-Za-z_]\w*", name):
                    nxt = None
                    continue
                v = self.value(expr.strip()) if expr.strip() else nxt
                if v is not None and name not in self.raw:
                    self.raw[name] = str(v)
                    self.cache.pop(name, None)
                nxt = v + 1 if v is not None else None

    def value(self, token, depth=0):
        """int value of a constant expression, or None"""
        if isinstance(token, int):
            return token
        token = str(token).strip()
        if token in self.cache:
            return self.cache[token]
        if depth > 40:
            return None
        v = None
        if re.fullmatch(r"-?(0x[0-9a-fA-F]+|\d+)", token):
            v = int(token, 0)
        elif re.fullmatch(r"\w+", token):
            if token in self.raw:
                v = self.value(self.raw[token], depth + 1)
        else:
            expr = re.sub(r"\b(0x[0-9a-fA-F]+|\d+)[uUlL]*\b", r"\1", token)
            names = set(re.findall(r"\b[A-Za-z_]\w*\b", expr))
            vals = {}
            for n in names:
                vals[n] = self.value(n, depth + 1)
                if vals[n] is None:
                    break
            else:
                if re.fullmatch(r"[\w\s()+\-*/<>|&~^]*", expr):
                    try:
                        v = int(eval(re.sub(r"\b[A-Za-z_]\w*\b", lambda m: str(vals[m.group(0)]), expr).replace("/", "//")))
                    except Exception:
                        v = None
        self.cache[token] = v
        return v


# ---------------------------------------------------------------------------
# Event scripts (compiled .inc, including the .inc Poryscript generates)
# ---------------------------------------------------------------------------

class Scripts:
    def __init__(self):
        self.cmds = []        # [(op, args, file, line)]
        self.labels = {}      # label -> index into cmds
        self.label_at = []    # nearest label for each command
        self.tagged = set()   # indices of commands on an "@ Draconid Emerald" line
        files = sorted(glob.glob(os.path.join(ROOT, "data/maps/*/scripts.inc")))
        files += sorted(glob.glob(os.path.join(ROOT, "data/scripts/**/*.inc"), recursive=True))
        files += [os.path.join(ROOT, "data/event_scripts.s")]
        for path in files:
            self._parse(path)

    # the preprocessor conditions the event scripts use (Emerald build: not FRLG, no BUGFIX/UBFIX)
    PP_TRUE = {"IS_FRLG": False, "BUGFIX": False, "UBFIX": False}

    def _parse(self, path):
        rel = os.path.relpath(path, ROOT)
        cur = None
        live = [True]  # #if nesting: is this branch compiled?
        for n, line in enumerate(open(path, errors="replace"), 1):
            pp = re.match(r"#\s*(if|ifdef|ifndef|elif|else|endif)\b\s*(\w*)", line)
            if pp:
                kw, name = pp.groups()
                if kw in ("if", "ifdef", "ifndef"):
                    v = self.PP_TRUE.get(name, False)
                    live.append(live[-1] and (not v if kw == "ifndef" else v))
                elif kw == "elif":
                    live[-1] = live[-2] and not live[-1] and self.PP_TRUE.get(name, False)
                elif kw == "else":
                    live[-1] = live[-2] and not live[-1]
                elif len(live) > 1:
                    live.pop()
                continue
            if not live[-1]:
                continue
            tagged = "Draconid Emerald" in line
            s = line.split("@")[0].strip() if '"' not in line else line.strip()
            if not s or s.startswith(".string") or s.startswith("//") or s.startswith(".include"):
                continue
            m = re.match(r"^([A-Za-z_]\w*)::?\s*(.*)$", s)
            if m:
                cur = m.group(1)
                self.labels.setdefault(cur, len(self.cmds))
                s = m.group(2).strip()
                if not s:
                    continue
            parts = s.split(None, 1)
            op = parts[0]
            args = [a.strip() for a in parts[1].split(",")] if len(parts) > 1 else []
            if tagged:
                self.tagged.add(len(self.cmds))
            self.cmds.append((op, args, rel, n))
            self.label_at.append(cur)

    def file_of(self, label):
        i = self.labels.get(label)
        return self.cmds[i][2] if i is not None and i < len(self.cmds) else None


# ---------------------------------------------------------------------------
# Maps
# ---------------------------------------------------------------------------

SURFABLE = {"MB_POND_WATER", "MB_INTERIOR_DEEP_WATER", "MB_DEEP_WATER", "MB_WATERFALL", "MB_SOOTOPOLIS_DEEP_WATER",
            "MB_OCEAN_WATER", "MB_NO_SURFACING", "MB_SEAWEED", "MB_SEAWEED_NO_SURFACING", "MB_EASTWARD_CURRENT",
            "MB_WESTWARD_CURRENT", "MB_NORTHWARD_CURRENT", "MB_SOUTHWARD_CURRENT", "MB_WATER_DOOR",
            "MB_WATER_SOUTH_ARROW_WARP", "MB_FAST_WATER", "MB_CYCLING_ROAD_WATER"}
SURF_START = {"MB_POND_WATER", "MB_OCEAN_WATER", "MB_INTERIOR_DEEP_WATER", "MB_DEEP_WATER", "MB_SOOTOPOLIS_DEEP_WATER",
              "MB_EASTWARD_CURRENT", "MB_WESTWARD_CURRENT", "MB_NORTHWARD_CURRENT", "MB_SOUTHWARD_CURRENT"}
DIVEABLE = {"MB_INTERIOR_DEEP_WATER", "MB_DEEP_WATER", "MB_SOOTOPOLIS_DEEP_WATER"}
NO_EMERGE = {"MB_NO_SURFACING", "MB_SEAWEED_NO_SURFACING"}
ACRO = {"MB_BUMPY_SLOPE", "MB_ISOLATED_VERTICAL_RAIL", "MB_ISOLATED_HORIZONTAL_RAIL", "MB_VERTICAL_RAIL",
        "MB_HORIZONTAL_RAIL"}
HOLES = {"MB_CRACKED_FLOOR_HOLE", "MB_CRACKED_FLOOR"}
COUNTER = "MB_COUNTER"
# field_control_avatar.c: stepping onto a warp tile with one of these warps (IsWarpMetatileBehavior); an arrow
# warp needs a step the arrow's way while standing on it (TryArrowWarp); an animated door is walked into from
# below although the tile itself is impassable (TryDoorWarp)
STEP_WARP = {"MB_ANIMATED_DOOR", "MB_LADDER", "MB_UP_ESCALATOR", "MB_DOWN_ESCALATOR", "MB_NON_ANIMATED_DOOR",
             "MB_WATER_DOOR", "MB_DEEP_SOUTH_WARP", "MB_LAVARIDGE_GYM_B1F_WARP", "MB_LAVARIDGE_GYM_1F_WARP",
             "MB_AQUA_HIDEOUT_WARP", "MB_MT_PYRE_HOLE", "MB_MOSSDEEP_GYM_WARP", "MB_BRIDGE_OVER_OCEAN"}
ARROW_WARP = {"N": {"MB_NORTH_ARROW_WARP", "MB_STAIRS_OUTSIDE_ABANDONED_SHIP"},
              "S": {"MB_SOUTH_ARROW_WARP", "MB_WATER_SOUTH_ARROW_WARP", "MB_SHOAL_CAVE_ENTRANCE"},
              "W": {"MB_WEST_ARROW_WARP", "MB_UP_LEFT_STAIR_WARP", "MB_DOWN_LEFT_STAIR_WARP"},
              "E": {"MB_EAST_ARROW_WARP", "MB_UP_RIGHT_STAIR_WARP", "MB_DOWN_RIGHT_STAIR_WARP"}}
DOOR_WARP = "MB_ANIMATED_DOOR"
DIRS = {"S": (0, 1), "N": (0, -1), "W": (-1, 0), "E": (1, 0)}
LEDGE = {"S": "MB_JUMP_SOUTH", "N": "MB_JUMP_NORTH", "W": "MB_JUMP_WEST", "E": "MB_JUMP_EAST"}
# a tile blocks entering from the side it names / leaving towards it (metatile_behavior.c)
BLOCKS = {"N": {"MB_IMPASSABLE_NORTH", "MB_IMPASSABLE_NORTHEAST", "MB_IMPASSABLE_NORTHWEST", "MB_IMPASSABLE_SOUTH_AND_NORTH"},
          "S": {"MB_IMPASSABLE_SOUTH", "MB_IMPASSABLE_SOUTHEAST", "MB_IMPASSABLE_SOUTHWEST", "MB_IMPASSABLE_SOUTH_AND_NORTH"},
          "E": {"MB_IMPASSABLE_EAST", "MB_IMPASSABLE_NORTHEAST", "MB_IMPASSABLE_SOUTHEAST", "MB_IMPASSABLE_WEST_AND_EAST",
                "MB_SECRET_BASE_BREAKABLE_DOOR"},
          "W": {"MB_IMPASSABLE_WEST", "MB_IMPASSABLE_NORTHWEST", "MB_IMPASSABLE_SOUTHWEST", "MB_IMPASSABLE_WEST_AND_EAST",
                "MB_SECRET_BASE_BREAKABLE_DOOR"}}
OPPOSITE = {"N": "S", "S": "N", "E": "W", "W": "E"}
BOULDER = ("OBJ_EVENT_GFX_PUSHABLE_BOULDER", "OBJ_EVENT_GFX_PUSHABLE_BOULDER_FRLG")
ROCK = ("OBJ_EVENT_GFX_BREAKABLE_ROCK", "OBJ_EVENT_GFX_BREAKABLE_ROCK_FRLG")
TREE = ("OBJ_EVENT_GFX_CUTTABLE_TREE", "OBJ_EVENT_GFX_CUTTABLE_TREE_FRLG")
WALK, SURF, DIVE = 0, 1, 2
OUTDOOR = ("MAP_TYPE_TOWN", "MAP_TYPE_CITY", "MAP_TYPE_ROUTE", "MAP_TYPE_OCEAN_ROUTE")  # where Fly works
ELEVATION_TRANSITION, ELEVATION_DEFAULT, ELEVATION_MULTI_LEVEL = 0, 3, 15


class MapData:
    def __init__(self, name, mj):
        self.name = name
        self.id = mj["id"]
        self.json = mj
        self.layout_id = mj["layout"]
        self.map_type = mj.get("map_type", "")
        self.connections = mj.get("connections") or []
        self.warps = mj.get("warp_events") or []
        self.coords = mj.get("coord_events") or []
        self.bgs = mj.get("bg_events") or []
        self.objects = []
        for i, o in enumerate(mj.get("object_events") or []):
            if o.get("type") == "clone":
                continue
            o = dict(o)
            o["index"] = i + 1
            self.objects.append(o)


class World:
    def __init__(self):
        os.chdir(ROOT)
        self.proj = pokemap.Project()
        self.maps = {}       # MAP_X -> MapData
        self.by_name = {}    # folder name -> MapData
        for n in self.proj.map_names():
            p = os.path.join(ROOT, "data/maps/%s/map.json" % n)
            if not os.path.exists(p):
                continue
            md = MapData(n, json.load(open(p)))
            self.maps[md.id] = md
            self.by_name[n] = md
        self.localids = {}   # LOCALID_X -> (MAP_X, index)
        for md in self.maps.values():
            for o in md.objects:
                if o.get("local_id"):
                    self.localids[o["local_id"]] = (md.id, o["index"])
        self._layouts = {}
        self._behavior_names = pokemap.behavior_names()
        self._beh_cache = {}
        self.heal = json.load(open(os.path.join(ROOT, "src/data/heal_locations.json")))["heal_locations"]

    def layout(self, layout_id):
        if layout_id not in self._layouts:
            lay = self.proj.layout(layout_id)
            pair = self.proj.pair_for_layout(lay)
            self._layouts[layout_id] = (lay, pair)
        return self._layouts[layout_id]

    def behavior(self, pair, mid):
        key = (id(pair), mid)
        if key not in self._beh_cache:
            self._beh_cache[key] = self._behavior_names[pair.behavior(mid)] or "" if pair.metatile(mid)[0] else ""
        return self._beh_cache[key]

    def map_for_label(self, label):
        """the map a script label belongs to (longest map folder name that prefixes it)"""
        best = None
        for n in self.by_name:
            if label.startswith(n + "_") and (best is None or len(n) > len(best)):
                best = n
        return self.by_name[best].id if best else None

    def pretty(self, map_id):
        md = self.maps.get(map_id)
        return md.name if md else map_id


# ---------------------------------------------------------------------------
# The flag/var simulator
# ---------------------------------------------------------------------------

_GONE = object()


class Layer:
    """a dict as a shared base plus this copy's changes, so a scene's branches copy and merge cheaply"""
    __slots__ = ("base", "diff")

    def __init__(self, base=None, diff=None):
        self.base = base if base is not None else {}
        self.diff = diff if diff is not None else {}

    def get(self, k, default=None):
        v = self.diff.get(k, _GONE) if k in self.diff else self.base.get(k, default)
        return default if v is _GONE else v

    def __setitem__(self, k, v):
        self.diff[k] = v

    def pop(self, k, default=None):
        v = self.get(k, default)
        self.diff[k] = _GONE
        return v

    def items(self):
        merged = dict(self.base)
        merged.update(self.diff)
        return [(k, v) for k, v in merged.items() if v is not _GONE]

    def keys(self):
        return [k for k, _ in self.items()]

    def copy(self):
        return Layer(self.base, dict(self.diff))

    def flat(self):
        return Layer(dict(self.items()))


class State:
    """flags (key -> True/False/UNK), vars (key -> int/UNK), bag (item -> count or UNK); missing = 0"""
    DEFAULTS = (("flags", False), ("vars", 0), ("items", 0))

    def __init__(self, flags=None, vars=None, items=None, cut=False):
        self.flags = flags or Layer()
        self.vars = vars or Layer()
        self.items = items or Layer()
        self.cut = cut  # the path was cut short (a loop the simulator stopped following): the other branch wins

    def copy(self):
        return State(self.flags.copy(), self.vars.copy(), self.items.copy(), self.cut)

    def key(self):
        """hashable: equal keys, equal states (within one scene run, where the layers share their bases)"""
        return tuple((id(l.base), frozenset((k, v if v is not _GONE else "_GONE") for k, v in l.diff.items()))
                     for l in (self.flags, self.vars, self.items))

    def flattened(self):
        return State(self.flags.flat(), self.vars.flat(), self.items.flat())

    def flag(self, k):
        return self.flags.get(k, False)

    def var(self, k):
        return self.vars.get(k, 0)

    def has(self, item):
        v = self.items.get(item, 0)
        return UNK if v == UNK else v > 0

    @staticmethod
    def merge(pre, a, b):
        """both branches of an unknown condition: equal values stay, a value written on one side only is kept,
        values the branches disagree on become unknown. A branch cut short in a loop gives way to the other one."""
        if a.cut != b.cut:
            return b if a.cut else a
        out = []
        for attr, default in State.DEFAULTS:
            lp, la, lb = getattr(pre, attr), getattr(a, attr), getattr(b, attr)
            if la.base is lb.base is lp.base:
                keys = set(la.diff) | set(lb.diff) | set(lp.diff)
                res = Layer(la.base)
            else:
                keys = set(la.keys()) | set(lb.keys()) | set(lp.keys())
                res = Layer()
            for k in keys:
                va, vb, vp = la.get(k, default), lb.get(k, default), lp.get(k, default)
                if k == PLAYER_XY and va != vb:
                    res.diff[k] = UNK  # the player walked differently on the two sides: where to is unknown
                elif va == vb:
                    res.diff[k] = va
                elif va == vp:
                    res.diff[k] = vb
                elif vb == vp:
                    res.diff[k] = va
                else:
                    res.diff[k] = UNK
            out.append(res)
        return State(*out, cut=a.cut and b.cut)


class Ctx:
    """one scene run: the map it runs on, and what it did"""

    def __init__(self, map_id, last_talked=0, loading=False, budget=STEP_BUDGET):
        self.budget = budget            # commands before the simulator gives up
        self.map = map_id
        self.last_talked = last_talked
        self.loading = loading          # a map's OnTransition/OnLoad/OnResume
        self.warps = []                 # (op, MAP_X, x, y, warp_id)
        self.warp_depths = []           # 0: the scene surely warps; more: only after an answer it couldn't decide
        self.choice = 0                 # nested branches on the player's answer
        self.switch_on_result = False
        self.guesses = []               # (label, condition)
        self.steps = 0
        self.visits = {}
        self.seen = set()               # (pc, call stack, state) at labels: a path that gets there again repeats
        self.added = set()              # objects an addobject shows although their flag is set (the map's own)
        self.metatiles = {}             # (x, y) -> (metatile, impassable)
        self.layout = None
        self.objxy = {}                 # object index -> (x, y)
        self.holewarp = None
        self.divewarp = None
        self.battles = []
        self.ops = []                   # state-changing commands, for --verbose
        self.moves_player = False       # an applymovement on the player (a trigger that walks them back)
        self.depth = 0                  # nested unknown branches
        self.label = None               # the label of the command being applied
        self.then_map = None            # the table's "then": branches warping elsewhere give way


VAR_RESULT = "VAR_RESULT"
RESULT_UNKNOWN_OPS = {"yesnobox", "multichoice", "multichoicedefault", "multichoicegrid", "dynmultichoice", "random",
                      "getpartysize", "checkmoney", "checkpartymove", "givemon", "giveegg", "checkcoins",
                      "getplayerxy", "checkpokerus", "checkobjectat", "choosecontestmon", "getpricereduction",
                      "checkfieldmove", "checkmonmodernfatefulencounter"}
MULTI_BATTLE_OPS = {"multi_2_vs_2", "multi_2_vs_1", "multi_fixed_2_vs_2", "multi_fixed_2_vs_1", "multi_wild",
                    "multi_fixed_wild"}
RESULT_SPECIAL = re.compile(r"^(ScriptMenu_|Get|Check|Choose|Is|Has|Should|Count|Try|Are|Does|Can)")
WARP_OPS = {"warp", "warpsilent", "warpdoor", "warphole", "warpteleport", "warpspinenter", "warpmossdeepgym",
            "warpwhitefade", "teleport", "warpsootopolislegend"}
# specials that set up a warp in C (src/field_specials.c), by VAR_0x8004
SPECIAL_WARPS = {
    "CableCarWarp": lambda going_down: ("MAP_ROUTE112_CABLE_CAR_STATION", 6, 4) if going_down not in (0, UNK)
                    else ("MAP_MT_CHIMNEY_CABLE_CAR_STATION", 6, 4),
}
# specials / callnatives after which C code sends the player to a heal location: the Hall of Fame screens and the
# finale's credits end in the village bedroom (CB2_ReturnHomeDraconid, src/overworld.c)
NATIVE_HEAL_WARPS = {
    "GameClear": "HEAL_LOCATION_DRACONID_VILLAGE_PLAYERS_HOUSE_2F",
    "Draconid_StartCredits": "HEAL_LOCATION_DRACONID_VILLAGE_PLAYERS_HOUSE_2F",
}
# flags C code sets in a special (src/post_battle_event_funcs.c: GameClear)
NATIVE_FLAGS = {
    "GameClear": ["FLAG_SYS_GAME_CLEAR"],
}
PLAYER_IDS = ("LOCALID_PLAYER", "OBJ_EVENT_ID_PLAYER", "255")
PLAYER_XY = "PLAYER_XY"  # a pseudo var: where scripted movement leaves the player, (x, y) on the scene's map
# scripted movement commands that move the player one tile (two for jump_2_*), by direction
MOVE_STEP = re.compile(r"^(?:walk|walk_slow|walk_slower|walk_slowest|walk_fast|walk_faster|walk_fastest|player_run|"
                       r"slide|ride_water_current|jump|jump_2|acro_wheelie_hop|acro_end_wheelie_move|"
                       r"acro_wheelie_move|walk_slow_stairs|walk_stairs)_(up|down|left|right)$")
MOVE_DIR = {"up": (0, -1), "down": (0, 1), "left": (-1, 0), "right": (1, 0)}
COND = {"lt": lambda a, b: a < b, "eq": lambda a, b: a == b, "gt": lambda a, b: a > b,
        "le": lambda a, b: a <= b, "ge": lambda a, b: a >= b, "ne": lambda a, b: a != b}


class Sim:
    def __init__(self, consts, scripts, world, gender="MALE"):
        self.c = consts
        self.s = scripts
        self.w = world
        self.gender = consts.value(gender)
        self.trainer_flags = consts.value("TRAINER_FLAGS_START")
        self.var_lo = consts.value("VARS_START") or 0x4000
        self.special_lo = consts.value("SPECIAL_VARS_START") or 0x8000
        self.result_key = self.vkey(VAR_RESULT)
        self.label_pcs = set(scripts.labels.values())
        self.assume = {}  # specialvar function -> the value the story table assumes ("assume")

    # --- keys and values -------------------------------------------------
    def fkey(self, name):
        v = self.c.value(name)
        return v if v is not None else name

    def vkey(self, name):
        v = self.c.value(name)
        return v if v is not None else name

    def is_var(self, token):
        v = self.c.value(token)
        if v is None:
            return str(token).startswith("VAR_")
        return self.var_lo <= v < self.var_lo + 0x100 or self.special_lo <= v < self.special_lo + 0x100

    def val(self, token, st):
        """a command argument: a var's value if it names a var, else the constant"""
        if self.is_var(token):
            return st.var(self.vkey(token))
        v = self.c.value(token)
        return v if v is not None else UNK

    def object_of(self, token, st, ctx, map_arg=None):
        """(MapData, object dict) for a removeobject/addobject/setobjectxyperm argument"""
        lid = token
        if self.is_var(token):
            lid = st.var(self.vkey(token))
            if self.vkey(token) == self.vkey("VAR_LAST_TALKED"):
                lid = ctx.last_talked
        map_id = map_arg or ctx.map
        if isinstance(lid, str) and lid in self.w.localids:
            m, idx = self.w.localids[lid]
            md = self.w.maps.get(map_arg or m)
            return md, next((o for o in md.objects if o["index"] == idx), None) if md else None
        n = self.c.value(lid) if not isinstance(lid, int) else lid
        md = self.w.maps.get(map_id)
        if md is None or n is None or n == UNK:
            return md, None
        return md, next((o for o in md.objects if o["index"] == n), None)

    def movement_delta(self, label):
        """(dx, dy) a movement script moves its object by, or None if it can't be told (not a label, no step_end)"""
        i = self.s.labels.get(label)
        if i is None:
            return None
        dx = dy = 0
        for op, _, _, _ in self.s.cmds[i:i + 200]:
            if op == "step_end":
                return dx, dy
            m = MOVE_STEP.match(op)
            if m:
                n = 2 if op.startswith("jump_2_") else 1
                ddx, ddy = MOVE_DIR[m.group(1)]
                dx, dy = dx + n * ddx, dy + n * ddy
        return None

    def trainer_flag(self, trainer):
        t = self.c.value(trainer)
        return self.trainer_flags + t if t is not None and self.trainer_flags is not None else "TFLAG_" + trainer

    # --- execution -------------------------------------------------------
    def run(self, label, st, ctx):
        if label not in self.s.labels:
            ctx.guesses.append((label, "label not found"))
            return st
        st.vars[self.vkey("VAR_FACING")] = UNK  # the way the player faces when the script starts
        return self._exec(self.s.labels[label], st, ctx, ())

    def _cond(self, op, args, st, cmp_state):
        """(True / False / UNK, target) for a conditional"""
        kind = op.split("_if_")[1] if "_if_" in op else op
        if kind in ("set", "unset"):
            v = st.flag(self.fkey(args[0]))
            if v == UNK:
                return UNK, args[1]
            return (v if kind == "set" else not v), args[1]
        if kind in ("defeated", "not_defeated"):
            v = st.flag(self.trainer_flag(args[0]))
            if v == UNK:
                return UNK, args[1]
            return (v if kind == "defeated" else not v), args[1]
        if kind not in COND:
            return UNK, args[-1]
        if len(args) == 3:
            a, b = self.val(args[0], st), self.val(args[1], st)
            target = args[2]
        else:  # after compare
            a, b = cmp_state if cmp_state else (UNK, UNK)
            target = args[0]
        if a == UNK or b == UNK:
            return UNK, target
        return COND[kind](a, b), target

    def _exec(self, pc, st, ctx, stack):
        cmp_state = None
        cmp_var = None  # what the last compare looked at (Poryscript: compare VAR_RESULT, X + goto_if_ne label)
        n = len(self.s.cmds)
        while pc < n:
            ctx.steps += 1
            if pc in self.label_pcs:
                # the same place with the same state again: this path only repeats (a menu asked again, a loop)
                k = (pc, stack, st.key())
                if k in ctx.seen:
                    st.cut = True
                    return st
                ctx.seen.add(k)
            if ctx.steps > ctx.budget:
                ctx.guesses.append((self.s.label_at[pc], "step budget exceeded (a loop?)"))
                st.cut = True
                return st
            op, args, _, _ = self.s.cmds[pc]
            if op == "end":
                return st
            if op == "return":
                if stack and isinstance(stack[-1], int):
                    pc, stack = stack[-1], stack[:-1]
                    continue
                return st  # the end of the script, or of a call run on its own (a branch, see _branch)
            if op == "goto":
                pc = self._jump(args[0], pc, ctx)
                if pc is None or pc is LOOP:
                    st.cut = pc is LOOP
                    return st
                continue
            if op == "call":
                t = self._jump(args[0], pc, ctx)
                if t is LOOP:
                    st.cut = True
                    return st
                if t is None:
                    pc += 1
                    continue
                stack = stack + (pc + 1,)
                pc = t
                continue
            if op == "compare":
                cmp_state = (self.val(args[0], st), self.val(args[1], st))
                cmp_var = args[0]
                pc += 1
                continue
            if op in ("checkflag", "checktrainerflag"):  # Poryscript: flag() / defeated() -> check… + goto_if 0/1
                v = st.flag(self.fkey(args[0]) if op == "checkflag" else self.trainer_flag(args[0]))
                cmp_state = (UNK if v == UNK else int(v), 1)
                cmp_var = None
                pc += 1
                continue
            if op == "goto_if" or op == "call_if":  # after checkflag: goto_if TRUE/FALSE, dest
                v = cmp_state[0] if cmp_state else UNK
                want = self.c.value(args[0])
                cond = UNK if v == UNK or want is None else (v == want)
                res = self._branch(op[:4], cond, args[1], pc, st, ctx, stack, "%s %s" % (op, ", ".join(args)))
            elif op == "switch":
                st.vars[self.vkey("VAR_0x8000")] = self.val(args[0], st)
                ctx.switch_on_result = args[0] == VAR_RESULT
                pc += 1
                continue
            elif op == "case" and len(args) < 2:
                pc += 1  # a malformed case line (FRLG's pkmn_center_nurse_frlg.inc): not in this build
                continue
            elif op == "case":
                v = st.var(self.vkey("VAR_0x8000"))
                c = self.c.value(args[0])
                cond = UNK if v == UNK or c is None else v == c
                res = self._branch("goto", cond, args[1], pc, st, ctx, stack, "case %s" % args[0])
            elif op.startswith("goto_if") or op.startswith("call_if"):
                cond, target = self._cond(op, args, st, cmp_state)
                what = "%s %s" % (op, ", ".join(args))
                if len(args) == 1 and cmp_var:
                    what += " (after compare %s)" % cmp_var  # a branch on the player's answer is a choice
                res = self._branch(op[:4], cond, target, pc, st, ctx, stack, what)
            elif op.startswith("trainerbattle"):
                res = self._trainerbattle(op, args, pc, st, ctx)
                if res is None or res is LOOP:
                    st.cut = res is LOOP
                    return st
            elif op in WARP_OPS:
                ctx.warps.append(self._warp_dest(op, args))
                ctx.warp_depths.append(ctx.choice)
                if ctx.then_map and args and args[0] != ctx.then_map and ctx.depth:
                    st.cut = True  # a branch the table's "then" says the player doesn't take
                return st
            else:
                ctx.label = self.s.label_at[pc]
                self._apply(op, args, st, ctx)
                pc += 1
                continue
            # a branch result: a state (the script finished on both sides), a pc, or a call to make
            if isinstance(res, State):
                return res
            if isinstance(res, tuple):
                t = self._jump(res[1], pc, ctx)
                if t is LOOP:
                    st.cut = True
                    return st
                if t is None:
                    pc += 1
                    continue
                stack = stack + (pc + 1,)
                pc = t
                continue
            pc = res
        return st

    def _jump(self, label, pc, ctx):
        t = self.s.labels.get(label)
        if t is None:
            ctx.guesses.append((self.s.label_at[pc], "jump to unknown label %s" % label))
            return None
        ctx.visits[t] = ctx.visits.get(t, 0) + 1
        if ctx.visits[t] > 12:
            return LOOP
        return t

    def _branch(self, kind, cond, target, pc, st, ctx, stack, what):
        if cond is True:
            if kind == "goto":
                t = self._jump(target, pc, ctx)
                if t is LOOP:
                    st.cut = True
                return t if t is not None and t is not LOOP else st
            return ("call", target)
        if cond is False:
            return pc + 1
        ctx.guesses.append((self.s.label_at[pc], what))
        t = self.s.labels.get(target)
        if t is None:
            return pc + 1
        pre = st.copy()
        if ctx.depth >= MAX_FORK_DEPTH:
            ctx.guesses.append((self.s.label_at[pc], "too many unknown branches in a row: only the next line is followed"))
            return pc + 1
        # a branch on the player's answer (VAR_RESULT) makes what follows uncertain (a warp, e.g.); one on the
        # way they face or where they stand (VAR_FACING, getplayerxy) doesn't
        choice = "VAR_RESULT" in what or (what.startswith("case") and ctx.switch_on_result)
        ctx.depth += 1
        ctx.choice += choice
        try:
            if kind == "goto":
                a = self._exec(t, st.copy(), ctx, stack)
                b = self._exec(pc + 1, st.copy(), ctx, stack)
                return State.merge(pre, a, b)
            # call: run the called script on its own (up to its return), merge, go on once
            a = self._exec(t, st.copy(), ctx, (("call", pc),))
        finally:
            ctx.depth -= 1
            ctx.choice -= choice
        merged = State.merge(pre, a, st)
        st.flags, st.vars, st.items = merged.flags, merged.vars, merged.items
        return pc + 1

    def _trainerbattle(self, op, args, pc, st, ctx):
        if op == "trainerbattle" and len(args) >= 17:
            trainers = [args[1]] + ([args[6]] if args[6] not in ("TRAINER_NONE", "0") else [])
            event = args[4] if args[4] not in ("NULL", "0", "FALSE") else None
            cont = args[16] == "TRUE"
        else:
            if op == "trainerbattle_lavaridge":
                trainers, event = [args[1]], args[4]
            elif op in ("trainerbattle_two_trainers", "trainerbattle_two_trainers_no_intro"):
                trainers, event = [args[0], args[2]], None
            else:
                trainers, event = [args[0]], None
                if op == "trainerbattle_single" and len(args) > 3 and args[3] not in ("FALSE", "NULL"):
                    event = args[3]
                if op == "trainerbattle_double" and len(args) > 4 and args[4] not in ("FALSE", "NULL"):
                    event = args[4]
            cont = op in ("trainerbattle_no_intro", "trainerbattle_two_trainers_no_intro", "trainerbattle_earlyrival")
        for t in trainers:
            st.flags[self.trainer_flag(t)] = True
            ctx.battles.append(t)
        if event:
            return self._jump(event, pc, ctx)
        return pc + 1 if cont else None

    def _warp_dest(self, op, args):
        m = args[0] if args else "?"
        rest = args[1:]
        wid = x = y = None
        if len(rest) == 1:
            wid = rest[0]
        elif len(rest) == 2:
            x, y = rest
        elif len(rest) >= 3:
            wid, x, y = rest[:3]
        xi = self.c.value(x) if x is not None else None
        yi = self.c.value(y) if y is not None else None
        return (op, m, xi, yi, wid)

    def _apply(self, op, args, st, ctx):
        c = self.c
        if op == "setflag":
            st.flags[self.fkey(args[0])] = True
        elif op == "clearflag":
            st.flags[self.fkey(args[0])] = False
        elif op in ("settrainerflag", "cleartrainerflag") and args:  # Poryscript's defeated() scenes (D-245)
            st.flags[self.trainer_flag(args[0])] = op == "settrainerflag"
        elif op in ("setvar", "setorcopyvar") and len(args) >= 2:
            if op == "setorcopyvar" and self.is_var(args[1]):
                st.vars[self.vkey(args[0])] = self.val(args[1], st)
            else:
                v = c.value(args[1])
                st.vars[self.vkey(args[0])] = v if v is not None else UNK
        elif op == "copyvar" and len(args) >= 2:
            st.vars[self.vkey(args[0])] = self.val(args[1], st)
        elif op in ("addvar", "subvar") and len(args) >= 2:
            cur = st.var(self.vkey(args[0]))
            d = self.val(args[1], st)
            st.vars[self.vkey(args[0])] = UNK if UNK in (cur, d) else (cur + d if op == "addvar" else cur - d) & 0xFFFF
        elif op in ("giveitem", "additem", "finditem") and args:
            cur = st.items.get(args[0], 0)
            n = c.value(args[1]) if len(args) > 1 else 1
            st.items[args[0]] = UNK if cur == UNK else cur + (n or 1)
            st.vars[self.result_key] = 1
        elif op == "removeitem" and args:
            cur = st.items.get(args[0], 0)
            n = c.value(args[1]) if len(args) > 1 else 1
            st.items[args[0]] = UNK if cur == UNK else max(0, cur - (n or 1))
        elif op == "checkitem" and args:
            has = st.has(args[0])
            st.vars[self.result_key] = UNK if has == UNK else int(has)
        elif op == "checkplayergender":
            st.vars[self.result_key] = self.gender
        elif op == "specialvar" and args:
            v = self.assume.get(args[1]) if len(args) > 1 else None
            st.vars[self.vkey(args[0])] = UNK if v is None else self.c.value(v)
        elif op in ("special", "callnative") and args and RESULT_SPECIAL.match(args[0]):
            st.vars[self.result_key] = UNK  # a menu or a check written in C answers in VAR_RESULT
        elif op in MULTI_BATTLE_OPS:
            # the multi battle macros (asm/macros/battle_frontier/battle_tower.inc) continue after the battle
            for t in args:
                if t.startswith("TRAINER_") and t != "TRAINER_NONE":
                    st.flags[self.trainer_flag(t)] = True
                    ctx.battles.append(t)
        elif op == "getplayerxy" and len(args) >= 2:
            xy = st.vars.get(PLAYER_XY, UNK)
            st.vars[self.vkey(args[0])] = xy[0] if isinstance(xy, tuple) else UNK
            st.vars[self.vkey(args[1])] = xy[1] if isinstance(xy, tuple) else UNK
        elif op == "msgbox" and len(args) > 1 and args[1] == "MSGBOX_YESNO":
            st.vars[self.result_key] = UNK
        elif op in RESULT_UNKNOWN_OPS:
            st.vars[self.result_key] = UNK
        elif op in ("removeobject", "addobject") and args:
            md, obj = self.object_of(args[0], st, ctx, args[1] if len(args) > 1 else None)
            if op == "removeobject" and obj is not None and obj.get("flag") not in (None, "0", 0):
                st.flags[self.fkey(obj["flag"])] = True
            if op == "addobject" and obj is not None and md is not None and md.id == ctx.map:
                ctx.added.add(obj["index"])
        elif op == "setmetatile" and len(args) >= 4:
            x, y, mt = c.value(args[0]), c.value(args[1]), c.value(args[2])
            imp = c.value(args[3]) == 1
            if None not in (x, y, mt):
                ctx.metatiles[(x, y)] = (mt, imp, ctx.label)
        elif op == "setmaplayoutindex" and args:
            ctx.layout = args[0]
        elif op == "setobjectxyperm" and len(args) >= 3:
            md, obj = self.object_of(args[0], st, ctx)
            if obj is not None:
                ctx.objxy[obj["index"]] = (c.value(args[1]), c.value(args[2]))
        elif op == "setdivewarp" and len(args) >= 3:
            ctx.divewarp = (args[0], c.value(args[1]), c.value(args[2]))
        elif op == "setholewarp" and args:
            ctx.holewarp = args[0]
        elif op == "applymovement" and args and args[0] in PLAYER_IDS:
            ctx.moves_player = True
            xy = st.vars.get(PLAYER_XY, UNK)
            if isinstance(xy, tuple) and len(args) > 1:
                d = self.movement_delta(args[1])
                st.vars[PLAYER_XY] = (xy[0] + d[0], xy[1] + d[1]) if d is not None else UNK
            return
        elif op == "special" and args and args[0] in SPECIAL_WARPS:
            dest = SPECIAL_WARPS[args[0]](st.var(self.vkey("VAR_0x8004")))
            ctx.warps.append(("special " + args[0],) + dest + (None,))
            ctx.warp_depths.append(ctx.choice)
        elif op in ("special", "callnative") and args and (args[0] in NATIVE_FLAGS or args[0] in NATIVE_HEAL_WARPS):
            for f in NATIVE_FLAGS.get(args[0], ()):
                st.flags[self.fkey(f)] = True
            h = next((h for h in self.w.heal if h["id"] == NATIVE_HEAL_WARPS.get(args[0])), None)
            if h:
                ctx.warps.append(("%s %s" % (op, args[0]), h["map"], h["x"], h["y"], None))
                ctx.warp_depths.append(ctx.choice)
        else:
            return
        ctx.ops.append((op, args))


# ---------------------------------------------------------------------------
# A map as the player finds it: its load scripts run on the simulated state
# ---------------------------------------------------------------------------

MAP_SCRIPT_TYPES = ("MAP_SCRIPT_ON_TRANSITION", "MAP_SCRIPT_ON_LOAD", "MAP_SCRIPT_ON_RESUME")


def map_scripts(scripts, md):
    """{MAP_SCRIPT_*: label} and the ON_FRAME table [(var, value, label)] of a map"""
    out, frame = {}, []
    i = scripts.labels.get(md.name + "_MapScripts")
    while i is not None and i < len(scripts.cmds) and scripts.cmds[i][0] == "map_script":
        _, args, _, _ = scripts.cmds[i]
        out[args[0]] = args[1]
        i += 1
    t = scripts.labels.get(out.get("MAP_SCRIPT_ON_FRAME_TABLE", ""))
    while t is not None and t < len(scripts.cmds) and scripts.cmds[t][0] == "map_script_2":
        frame.append(tuple(scripts.cmds[t][1][:3]))
        t += 1
    return out, frame


def warp_into_table(scripts, headers):
    """the ON_WARP_INTO_MAP table [(var, value, label)]: the first entry due runs when the player warps in"""
    out = []
    t = scripts.labels.get(headers.get("MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE", ""))
    while t is not None and t < len(scripts.cmds) and scripts.cmds[t][0] == "map_script_2":
        out.append(tuple(scripts.cmds[t][1][:3]))
        t += 1
    return out


class MapView:
    def __init__(self, chk, md, state, persist=False):
        sim, c = chk.sim, chk.c
        self.md = md
        st = state if persist else state.copy()
        for k in range(c.value("TEMP_FLAGS_START"), c.value("TEMP_FLAGS_END") + 1):
            st.flags.pop(k, None)
        for k in range(c.value("TEMP_VARS_START"), c.value("TEMP_VARS_END") + 1):
            st.vars.pop(k, None)
        ctx = Ctx(md.id, loading=True)
        headers, self.frame_table = map_scripts(chk.scripts, md)
        self.load_labels = [headers[t] for t in MAP_SCRIPT_TYPES if t in headers]
        for label in self.load_labels:
            st = sim.run(label, st, ctx)
        # warping in: the first ON_WARP_INTO_MAP entry due (it may add objects whose hide flag is set)
        for var, value, label in warp_into_table(chk.scripts, headers):
            have, want = st.var(sim.vkey(var)), c.value(value)
            if have == UNK or have == want:
                st = sim.run(label, st, ctx)
                break
        self.state = st
        self.guesses = ctx.guesses
        self.layout_id = ctx.layout or md.layout_id
        lay, pair = chk.world.layout(self.layout_id)
        self.w, self.h = lay.width, lay.height
        blocks = list(lay.blocks)
        self.closed = {}
        for (x, y), (mt, imp, label) in ctx.metatiles.items():
            if 0 <= x < self.w and 0 <= y < self.h:
                old = blocks[y * self.w + x]
                blocks[y * self.w + x] = (old & pokemap.MAPGRID_ELEVATION_MASK) | (mt & pokemap.MAPGRID_METATILE_ID_MASK) | ((1 if imp else 0) << pokemap.MAPGRID_COLLISION_SHIFT)
                if imp:
                    self.closed[(x, y)] = label
        self.coll = [(b >> pokemap.MAPGRID_COLLISION_SHIFT) & 3 for b in blocks]
        self.elev = [(b >> pokemap.MAPGRID_ELEVATION_SHIFT) & 15 for b in blocks]
        self.beh = [chk.world.behavior(pair, b & pokemap.MAPGRID_METATILE_ID_MASK) for b in blocks]
        self.holewarp = ctx.holewarp
        self.divewarp = ctx.divewarp  # where diving or surfacing leads when the map has no dive/emerge connection
        # objects on the map now
        self.objects = []
        self.obj_at = {}
        for o in md.objects:
            flag = o.get("flag")
            shown = True
            unknown = False
            if flag not in (None, "0", 0, ""):
                v = st.flag(sim.fkey(flag))
                unknown = v == UNK
                shown = v is not True or o["index"] in ctx.added
            if not shown:
                continue
            x, y = ctx.objxy.get(o["index"], (o["x"], o["y"]))
            ob = dict(o, cx=x, cy=y, unknown=unknown)
            self.objects.append(ob)
            self.obj_at.setdefault((x, y), []).append(ob)
        # coord triggers whose var matches
        self.triggers = {}
        for ev in md.coords:
            if ev.get("type") != "trigger" or not ev.get("var") or sim.vkey(ev["var"]) == 0:
                continue  # TRIGGER_RUN_IMMEDIATELY: a script that only sets temp state, it can't stop the player
            want = c.value(ev.get("var_value"))
            have = st.var(sim.vkey(ev["var"]))
            if have == UNK or want is None or have == want:
                self.triggers.setdefault((ev["x"], ev["y"]), []).append(dict(ev, unknown=have == UNK))
        # the OnFrame scene that runs on entry, if any
        self.frame_scene = None
        for var, value, label in self.frame_table:
            have, want = st.var(sim.vkey(var)), c.value(value)
            if have == UNK or have == want:
                self.frame_scene = label
                break
        self.warps_at = {}
        for i, wv in enumerate(md.warps):
            self.warps_at.setdefault((wv["x"], wv["y"]), []).append((i, wv))

    def inside(self, x, y):
        return 0 <= x < self.w and 0 <= y < self.h

    def tile(self, x, y):
        i = y * self.w + x
        return self.beh[i], self.coll[i], self.elev[i]


# ---------------------------------------------------------------------------
# Tile search
# ---------------------------------------------------------------------------

class Obstacle:
    def __init__(self, kind, map_id=None, x=None, y=None, what="", key=None, clear=""):
        self.kind, self.map, self.x, self.y, self.what, self.key, self.clear = kind, map_id, x, y, what, key, clear

    def __repr__(self):
        return self.what

    def ident(self):
        return (self.kind, self.map, self.x, self.y, self.key)


class Search:
    """tile search for one leg with a fixed simulated state"""

    def __init__(self, chk, state, visited_fly):
        self.chk = chk
        self.w = chk.world
        self.sim = chk.sim
        self.state = state
        self.views = {}
        self.visited_fly = visited_fly
        self.passable_cache = {}
        self.fly_emitted = False
        a = chk.abilities(state)
        self.can = a

    def view(self, map_id):
        v = self.views.get(map_id)
        if v is None:
            md = self.w.maps.get(map_id)
            if md is None:
                return None
            v = MapView(self.chk, md, self.state)
            self.views[map_id] = v
        return v

    # --- geometry ---------------------------------------------------------
    def step(self, map_id, x, y, d):
        v = self.view(map_id)
        dx, dy = DIRS[d]
        nx, ny = x + dx, y + dy
        if v.inside(nx, ny):
            return map_id, nx, ny
        want = {"N": "up", "S": "down", "W": "left", "E": "right"}[d]
        for conn in v.md.connections:
            if conn.get("direction") != want:
                continue
            cv = self.view(conn["map"])
            if cv is None:
                continue
            off = conn.get("offset", 0)
            if d == "N":
                cx, cy = nx - off, cv.h - 1
            elif d == "S":
                cx, cy = nx - off, 0
            elif d == "W":
                cx, cy = cv.w - 1, ny - off
            else:
                cx, cy = 0, ny - off
            if cv.inside(cx, cy):
                return conn["map"], cx, cy
        return None

    def mode_at(self, map_id, x, y):
        v = self.view(map_id)
        if v.md.map_type == "MAP_TYPE_UNDERWATER":
            return DIVE
        b, _, _ = v.tile(x, y)
        return SURF if b in SURF_START else WALK

    def node_at(self, map_id, x, y):
        v = self.view(map_id)
        if v is None or not v.inside(x, y):
            return None
        _, _, e = v.tile(x, y)
        return (map_id, x, y, ELEVATION_DEFAULT if e == ELEVATION_MULTI_LEVEL else e, self.mode_at(map_id, x, y))

    def warp_nodes(self, map_id, warps):
        for _, wv in warps:
            for dm, dx, dy in self.warp_dests(map_id, wv):
                n = self.node_at(dm, dx, dy)
                if n:
                    yield n

    def warp_dests(self, map_id, warp):
        dm, wid = warp.get("dest_map"), str(warp.get("dest_warp_id"))
        out = []
        if dm == "MAP_DYNAMIC" or not wid.isdigit():
            # back to where the player came in (link rooms, secret bases, the elevator): nothing new is reached
            return out
        md = self.w.maps.get(dm)
        if md is None or int(wid) >= len(md.warps):
            return out
        wv = md.warps[int(wid)]
        return [(dm, wv["x"], wv["y"])]

    # --- obstacles --------------------------------------------------------
    def field(self, move):
        ok = self.can.get(move)
        if ok:
            return None
        badge, item = self.chk.field_moves.get(move, (None, None))
        need = {"BIKE": "a bike (ITEM_MACH_BIKE / ITEM_ACRO_BIKE)"}.get(move, "%s + %s" % (item, badge))
        return Obstacle("field", what="needs %s: %s" % (move, need), key=move, clear=need)

    def object_obstacle(self, map_id, ob):
        md = self.w.maps[map_id]
        key = (map_id, ob["index"])
        if key in self.passable_cache:
            cached = self.passable_cache[key]
            return cached
        gfx = ob.get("graphics_id", "")
        res = None
        name = ob.get("local_id") or "object %d" % ob["index"]
        if gfx in BOULDER:
            res = self.field("STRENGTH")
        elif gfx in ROCK:
            res = self.field("ROCK_SMASH")
        elif gfx in TREE:
            res = self.field("CUT")
        else:
            flag = ob.get("flag")
            removable = False
            script = ob.get("script")
            if script and script in self.chk.scripts.labels:
                # talking to it: does it leave (its flag gets set), or stand somewhere else once the map
                # reloads (a guard that steps aside after the battle, e.g. copyobjectxytoperm + a var)?
                st = self.view(map_id).state.copy()
                ctx = Ctx(map_id, last_talked=ob["index"], budget=SIDE_BUDGET)
                st = self.sim.run(script, st, ctx)
                if flag not in (None, "0", 0, ""):
                    removable = st.flag(self.sim.fkey(flag)) is True
                if not removable and (ctx.ops or ctx.battles):
                    again = MapView(self.chk, md, st)
                    removable = not any(o["index"] == ob["index"] and (o["cx"], o["cy"]) == (ob["cx"], ob["cy"])
                                        for o in again.objects)
            if not removable:
                if flag in (None, "0", 0, ""):
                    clear = "always there (no hide flag)"
                else:
                    clear = "hidden once %s is set%s; written by %s" % (
                        flag, " (unknown in the simulation)" if ob.get("unknown") else "",
                        self.chk.writers_text(self.sim.fkey(flag), flag))
                what = "%s (%s, script %s) on %s at (%d, %d)" % (name, gfx.replace("OBJ_EVENT_GFX_", ""), script,
                                                                 md.name, ob["cx"], ob["cy"])
                res = Obstacle("object", map_id, ob["cx"], ob["cy"], what, key=flag, clear=clear)
        self.passable_cache[key] = res
        return res

    def closed_obstacle(self, tv, x, y):
        label = tv.closed[(x, y)]
        return Obstacle("closed", tv.md.id, x, y, "tile (%d, %d) on %s is shut by the load script %s" % (
            x, y, tv.md.name, label), key=(tv.md.id, x, y), clear="whatever %s checks before its setmetatile" % label)

    def trigger_obstacle(self, map_id, ev):
        """a coord trigger that turns the player back: its script walks the player (or warps them away) and
        doesn't move its var on. A switch or a one-off message that leaves the player where they are is not."""
        key = (map_id, ev["x"], ev["y"], ev["script"])
        if key in self.passable_cache:
            return self.passable_cache[key]
        st = self.view(map_id).state.copy()
        ctx = Ctx(map_id, budget=SIDE_BUDGET)
        vk = self.sim.vkey(ev["var"])
        before = st.var(vk)
        st = self.sim.run(ev["script"], st, ctx)
        res = None
        if (st.var(vk) == before and ctx.moves_player) or ctx.warps:
            md = self.w.maps[map_id]
            what = "coord trigger on %s at (%d, %d): %s == %s runs %s%s" % (
                md.name, ev["x"], ev["y"], ev["var"], ev["var_value"], ev["script"],
                " (it warps the player away)" if ctx.warps else " (it doesn't change %s)" % ev["var"])
            res = Obstacle("trigger", map_id, ev["x"], ev["y"], what, key=ev["var"],
                           clear="%s written by %s" % (ev["var"], self.chk.writers_text(vk, ev["var"])))
        self.passable_cache[key] = res
        return res

    # --- moves ------------------------------------------------------------
    def neighbors(self, node, goal_tiles):
        map_id, x, y, e, mode = node
        v = self.view(map_id)
        cb, _, ce = v.tile(x, y)
        # Fly: from the first outdoor tile the search reaches, to every town visited before
        if not self.fly_emitted and v.md.map_type in OUTDOOR and self.can.get("FLY"):
            self.fly_emitted = True
            for n in self.fly_nodes():
                yield n, (), "fly"
        # warps: the tile the player stands on (step warps; arrow warps below, the way the arrow points)
        here = v.warps_at.get((x, y), ())
        if here and cb in STEP_WARP:
            for n in self.warp_nodes(map_id, here):
                yield n, (), "warp"
        if cb in HOLES and v.holewarp:
            n = self.node_at(v.holewarp, x, y)
            if n:
                yield n, (), "fall"
        conns = {c.get("direction"): c["map"] for c in v.md.connections}
        # dive / surface: the map's dive or emerge connection at the same x, y, else its setdivewarp
        # destination (SetDiveWarp, field_control_avatar.c)
        for want_mode, beh_ok, conn, how in ((SURF, cb in DIVEABLE, "dive", "dive"),
                                             (DIVE, cb not in NO_EMERGE, "emerge", "emerge")):
            if mode != want_mode or not beh_ok:
                continue
            if conn in conns:
                dest = (conns[conn], x, y)
            elif v.divewarp:
                dest = v.divewarp
            else:
                continue
            dv = self.view(dest[0])
            if dv and dv.inside(dest[1], dest[2]):
                ob = self.field("DIVE")
                nmode = DIVE if dv.md.map_type == "MAP_TYPE_UNDERWATER" else SURF if dv.tile(dest[1], dest[2])[0] in SURFABLE else WALK
                yield (dest[0], dest[1], dest[2], dv.tile(dest[1], dest[2])[2], nmode), (ob,) if ob else (), how
        for d in DIRS:
            if here and cb in ARROW_WARP[d]:
                for n in self.warp_nodes(map_id, here):
                    yield n, (), "warp"
            if cb in BLOCKS[d]:
                continue
            t = self.step(map_id, x, y, d)
            if t is None:
                continue
            tm, tx, ty = t
            tv = self.view(tm)
            tb, tc, te = tv.tile(tx, ty)
            if d == "N" and tm == map_id and (tx, ty) in tv.warps_at and (tb == DOOR_WARP or (tx, ty) in tv.closed):
                # a door; one a load script locked (setmetatile) is an obstacle
                obs = (self.closed_obstacle(tv, tx, ty),) if (tx, ty) in tv.closed else ()
                for n in self.warp_nodes(tm, tv.warps_at[(tx, ty)]):
                    yield n, obs, "door"
                continue
            if tb in BLOCKS[OPPOSITE[d]]:
                continue
            obs = []
            if mode == WALK and tb == LEDGE[d]:
                land = self.step(tm, tx, ty, d)
                if land is None:
                    continue
                lm, lx, ly = land
                le = self.view(lm).tile(lx, ly)[2]
                yield (lm, lx, ly, le if le != ELEVATION_MULTI_LEVEL else e, WALK), (), "jump"
                continue
            if tc:
                if (tx, ty) in tv.closed:
                    obs.append(self.closed_obstacle(tv, tx, ty))
                else:
                    continue
            mismatch = not (e == ELEVATION_TRANSITION or te in (ELEVATION_TRANSITION, ELEVATION_MULTI_LEVEL) or te == e)
            nmode = mode
            if mode == WALK:
                if tb in SURFABLE:
                    if tb not in SURF_START:
                        continue
                    ob = self.field("SURF")
                    if ob:
                        obs.append(ob)
                    nmode = SURF
                elif mismatch:
                    continue
            elif mode == SURF:
                if tb in SURFABLE or not mismatch:
                    if tb == "MB_WATERFALL" and d == "N":
                        ob = self.field("WATERFALL")
                        if ob:
                            obs.append(ob)
                elif te == ELEVATION_DEFAULT and not tc and not tv.obj_at.get((tx, ty)):
                    nmode = WALK
                else:
                    continue
            elif mismatch:
                continue
            for ob in tv.obj_at.get((tx, ty), ()):
                oe = ob.get("elevation", 0)
                if e == ELEVATION_TRANSITION or oe == ELEVATION_TRANSITION or oe == e:
                    o = self.object_obstacle(tm, ob)
                    if o:
                        obs.append(o)
            if nmode == WALK and tb in ACRO:
                ob = self.field("BIKE")
                if ob:
                    obs.append(ob)
            if nmode == WALK and tb == "MB_MUDDY_SLOPE" and d == "N":
                ob = self.field("BIKE")
                if ob:
                    obs.append(ob)
            ne = e if (te == ELEVATION_MULTI_LEVEL or ce == ELEVATION_MULTI_LEVEL) else te
            if (tm, tx, ty) not in goal_tiles:
                for ev in tv.triggers.get((tx, ty), ()):
                    ee = ev.get("elevation", 0)
                    if ee == 0 or ee == ne:
                        o = self.trigger_obstacle(tm, ev)
                        if o:
                            obs.append(o)
            yield (tm, tx, ty, ne, nmode), tuple(obs), d

    def fly_nodes(self):
        out = []
        if not self.can.get("FLY"):
            return out
        for h in self.w.heal:
            if h["map"] in self.visited_fly and "respawn_map" in h:
                n = self.node_at(h["map"], h["x"], h["y"])
                if n:
                    out.append(n)
        return out

    def search(self, starts, goal, goal_tiles, relaxed=False):
        """starts: nodes; goal(node) -> bool. Returns (end node, prev) or (None, prev)."""
        prev = {}
        self.fly_emitted = False
        if not relaxed:
            dq = deque()
            for s in starts:
                if s not in prev:
                    prev[s] = None
                    dq.append(s)
            while dq:
                n = dq.popleft()
                if goal(n):
                    return n, prev
                for nn, obs, how in self.neighbors(n, goal_tiles):
                    if obs or nn in prev:
                        continue
                    prev[nn] = (n, how, ())
                    dq.append(nn)
            return None, prev
        dist = {}
        heap = []
        for i, s in enumerate(starts):
            dist[s] = 0
            prev[s] = None
            heap.append((0, i, s))
        heapq.heapify(heap)
        tie = len(heap)
        while heap:
            d, _, n = heapq.heappop(heap)
            if d > dist.get(n, 1 << 60):
                continue
            if goal(n):
                return n, prev
            for nn, obs, how in self.neighbors(n, goal_tiles):
                nd = d + 1 + PENALTY * len(obs)
                if nd < dist.get(nn, 1 << 60):
                    dist[nn] = nd
                    prev[nn] = (n, how, obs)
                    tie += 1
                    heapq.heappush(heap, (nd, tie, nn))
        return None, prev

    @staticmethod
    def path(prev, end):
        out = []
        n = end
        while n is not None and prev.get(n) is not None:
            p, how, obs = prev[n]
            out.append((p, how, obs, n))
            n = p
        out.reverse()
        return out


# ---------------------------------------------------------------------------
# The checker: story table, scenes, legs, warps
# ---------------------------------------------------------------------------

VANILLA_FIELD_MOVES = {"CUT": "FLAG_BADGE01_GET", "FLASH": "FLAG_BADGE02_GET", "ROCK_SMASH": "FLAG_BADGE03_GET",
                       "STRENGTH": "FLAG_BADGE04_GET", "SURF": "FLAG_BADGE05_GET", "FLY": "FLAG_BADGE06_GET",
                       "DIVE": "FLAG_BADGE07_GET", "WATERFALL": "FLAG_BADGE08_GET"}
BADGES = ["FLAG_BADGE%02d_GET" % i for i in range(1, 9)]
BIKES = ("ITEM_MACH_BIKE", "ITEM_ACRO_BIKE")


def field_move_badges():
    """{MOVE: (badge flag or None, HM item)} from src/field_move.c (the Emerald side of IS_FRLG ? a : b)"""
    out = {}
    try:
        text = open(os.path.join(ROOT, "src/field_move.c")).read()
    except OSError:
        text = ""
    for m in re.finditer(r"\[FIELD_MOVE_(\w+)\]\s*=\s*\{(.*?)\n\s*\},", text, re.S):
        move, body = m.group(1), m.group(2)
        if move not in VANILLA_FIELD_MOVES:
            continue
        arg = re.search(r"\.arg\s*=\s*(.*?),\s*$", body, re.M)
        badge = None
        if "BADGE_UNLOCK" in body and arg:
            flags = re.findall(r"FLAG_BADGE\d\d_GET", arg.group(1))
            badge = flags[-1] if flags else None
        out[move] = (badge, "ITEM_HM_" + move)
    for move, badge in VANILLA_FIELD_MOVES.items():
        out.setdefault(move, (badge, "ITEM_HM_" + move))
    return out


def parse_pos(text):
    """"MAP_X 12 34" -> ("MAP_X", 12, 34)"""
    t = text.split()
    return (t[0], int(t[1]), int(t[2]))


class Checker:
    def __init__(self, gender="MALE"):
        self.c = Constants()
        self.scripts = Scripts()
        self.world = World()
        self.sim = Sim(self.c, self.scripts, self.world, gender)
        self.field_moves = field_move_badges()
        self._writers = None
        self._names = None
        self.refs = {}
        for md in self.world.maps.values():
            for o in md.objects:
                if o.get("script") and o["script"] != "0x0":
                    self.refs.setdefault(o["script"], []).append(("object", md.id, o))
            for ev in md.coords:
                if ev.get("type") == "trigger" and ev.get("script"):
                    self.refs.setdefault(ev["script"], []).append(("coord", md.id, ev))
            for ev in md.bgs:
                if ev.get("script"):
                    self.refs.setdefault(ev["script"], []).append(("bg", md.id, ev))
            _, frame = map_scripts(self.scripts, md)
            for var, value, label in frame:
                self.refs.setdefault(label, []).append(("frame", md.id, (var, value)))

    # --- indexes ------------------------------------------------------------
    def writers(self, key):
        if self._writers is None:
            self._writers = {}
            for i, (op, args, _, _) in enumerate(self.scripts.cmds):
                if op in ("setflag", "clearflag") and args:
                    k = self.sim.fkey(args[0])
                elif op in ("setvar", "addvar", "subvar", "copyvar") and args:
                    k = self.sim.vkey(args[0])
                elif op == "removeobject" and args and args[0] in self.world.localids:
                    m, idx = self.world.localids[args[0]]
                    ob = next((o for o in self.world.maps[m].objects if o["index"] == idx), None)
                    if not ob or ob.get("flag") in (None, "0"):
                        continue
                    k = self.sim.fkey(ob["flag"])
                    op = "removeobject"
                else:
                    continue
                self._writers.setdefault(k, []).append((op, args[1] if op in ("setvar", "addvar") and len(args) > 1 else None,
                                                        self.scripts.label_at[i]))
        return self._writers.get(key, [])

    def writers_text(self, key, name, limit=4):
        w = self.writers(key)
        if not w:
            return "no script"
        seen = []
        for op, val, label in w:
            s = "%s (%s%s)" % (label, op, " " + val if val else "")
            if s not in seen:
                seen.append(s)
        return ", ".join(seen[:limit]) + (" +%d more" % (len(seen) - limit) if len(seen) > limit else "")

    def name_of(self, key, prefix):
        if self._names is None:
            self._names = {}
            for n in self.c.raw:
                if n.startswith(("FLAG_", "VAR_")) and not n.startswith(("FLAG_TEMP_", "VAR_TEMP_")):
                    v = self.c.value(n)
                    if v is None:
                        continue
                    key2 = (n.split("_")[0], v)
                    # a real name beats a numbered alias (VAR_0x40A0, FLAG_UNUSED_…)
                    if key2 not in self._names or re.search(r"_0x[0-9A-Fa-f]+$|UNUSED", self._names[key2]):
                        self._names[key2] = n
        if isinstance(key, str):
            return key
        return self._names.get((prefix, key), "%s_0x%X" % (prefix, key))

    # --- state ----------------------------------------------------------------
    def new_game_state(self):
        st = State()
        ctx = Ctx(None)
        st = self.sim.run("EventScript_ResetAllMapFlags", st, ctx)
        return st

    def abilities(self, st):
        can = {}
        for move, (badge, item) in self.field_moves.items():
            can[move] = st.has(item) is True and (badge is None or st.flag(self.sim.fkey(badge)) is True)
        can["BIKE"] = any(st.has(b) is True for b in BIKES)
        return can

    def have_summary(self, st):
        badges = [b for b in BADGES if st.flag(self.sim.fkey(b)) is True]
        hms = [m for m, (_, item) in self.field_moves.items() if st.has(item) is True]
        return len(badges), hms

    # --- scenes ---------------------------------------------------------------
    def scene_target(self, entry, maps_hint=None):
        """where a scene starts: ("tile", map, {(x, y)}) / ("adjacent", map, x, y, obj) / ("map", map)"""
        label = entry["label"]
        if entry.get("at"):
            m, x, y = parse_pos(entry["at"])
            return ("tile", m, {(x, y)}, None)
        if entry.get("map"):
            return ("map", entry["map"], None, None)
        refs = self.refs.get(label, [])
        if entry.get("talk"):
            m, idx = self.world.localids[entry["talk"]]
            ob = next(o for o in self.world.maps[m].objects if o["index"] == idx)
            return ("adjacent", m, (ob["x"], ob["y"]), ob)
        if not refs:
            return None
        maps = {r[1] for r in refs}
        if len(maps) > 1:
            return ("ambiguous", sorted(maps), None, None)
        m = refs[0][1]
        coords = [r[2] for r in refs if r[0] == "coord"]
        if coords:
            return ("tile", m, {(ev["x"], ev["y"]) for ev in coords}, coords)
        objs = [r[2] for r in refs if r[0] == "object"]
        if objs:
            return ("adjacent", m, (objs[0]["x"], objs[0]["y"]), objs[0])
        bgs = [r[2] for r in refs if r[0] == "bg"]
        if bgs:
            return ("adjacent", m, (bgs[0]["x"], bgs[0]["y"]), None)
        return ("map", m, None, None)

    def check_trigger(self, entry, target, view):
        """problems that stop the scene from starting, with the simulated state"""
        label = entry["label"]
        problems = []
        if target is None or target[0] == "ambiguous":
            return problems
        m = target[1]
        refs = [r for r in self.refs.get(label, []) if r[1] == m]
        coords = [r[2] for r in refs if r[0] == "coord"]
        if coords and not any(t["script"] == label for ev in coords for t in view.triggers.get((ev["x"], ev["y"]), ())):
            ev = coords[0]
            problems.append("its coord trigger (%d, %d) needs %s == %s, the simulation has %s" % (
                ev["x"], ev["y"], ev["var"], ev["var_value"], view.state.var(self.sim.vkey(ev["var"]))))
        frames = [r[2] for r in refs if r[0] == "frame"]
        if frames and view.frame_scene != label:
            var, value = frames[0]
            problems.append("its OnFrame entry %s == %s is not the one due (the simulation has %s; due: %s)" % (
                var, value, view.state.var(self.sim.vkey(var)), view.frame_scene))
        objs = [r[2] for r in refs if r[0] == "object"]
        if entry.get("talk"):
            objs = [target[3]]
        if objs and not any(o["index"] == ob["index"] for ob in objs for o in view.objects):
            ob = objs[0]
            problems.append("its object %s is hidden (%s is set)" % (ob.get("local_id") or ob["index"], ob.get("flag")))
        return problems

    def frame_loop(self, map_id, label, st, ctx):
        """an OnFrame scene must move its var on, or it starts again on the next frame (a softlock)"""
        if not any(r[0] == "frame" and r[1] == map_id for r in self.refs.get(label, [])):
            return None
        if ctx.warps and any(w[1] != map_id for w in ctx.warps):
            return None  # it sends the player elsewhere; it would only replay on the next visit
        again = MapView(self, self.world.maps[map_id], st)
        if again.frame_scene == label:
            return "%s: the OnFrame scene leaves its var as it was – it would start again right away (softlock)" % label
        return None

    def check_expect(self, expect, st):
        bad = []
        for e in expect:
            neg = e.startswith("!")
            e2 = e[1:] if neg else e
            if "=" in e2:
                var, val = e2.split("=", 1)
                have, want = st.var(self.sim.vkey(var.strip())), self.c.value(val.strip())
                ok = have == want
                if not ok:
                    bad.append("%s is %s, not %s" % (var.strip(), have, val.strip()))
                continue
            if e2.startswith("ITEM_"):
                ok = st.has(e2) is True
            elif e2.startswith("TRAINER_"):
                ok = st.flag(self.sim.trainer_flag(e2)) is True
            else:
                ok = st.flag(self.sim.fkey(e2)) is True
            if ok == neg:
                bad.append("%s %s" % (e2, "is set" if neg else "is not set"))
        return bad

    def warp_position(self, w):
        op, m, x, y, wid = w
        if x is not None and y is not None and x >= 0 and y >= 0:
            return (m, x, y)
        md = self.world.maps.get(m)
        wi = self.c.value(wid) if wid is not None else None
        if md and wi is not None and 0 <= wi < len(md.warps):
            return (m, md.warps[wi]["x"], md.warps[wi]["y"])
        return None


def norm_entry(e):
    return {"label": e} if isinstance(e, str) else dict(e)


class LegResult:
    def __init__(self, leg):
        self.leg = leg
        self.ok = True
        self.problems = []      # scene problems (trigger, expect, have)
        self.blockers = []      # Obstacles on the cheapest path
        self.notes = []
        self.guesses = []
        self.path_maps = []
        self.steps = 0
        self.start = None
        self.end = None
        self.target = None
        self.have = None
        self.warps = []
        self.detours = []       # the walk only works after an off-path scene the table doesn't list
        self.skipped = False    # not checked this run (--leg)
        self.route = []         # the maps the walk crosses, for printing


def run_story(chk, table, only=None, verbose=False, state_at=None, hooks=None):
    """walk the story table. hooks (check_hardlock.py): an object with scene(leg, entry, state, target, pos, map, view)
    called before each scene runs and leg_end(leg, res, state, pos) after each leg's walk"""
    legs = table["legs"]
    chk.sim.assume = table.get("assume", {})
    st = chk.new_game_state()
    pos = parse_pos(table["start"])
    visited = {pos[0]}
    entered_map = pos[0]
    results = []
    for i, leg in enumerate(legs):
        res = LegResult(leg)
        if leg.get("side"):  # a side check (a way back, a detour): the story goes on from where it was
            saved = (st, pos, entered_map, set(visited))
        entries = [norm_entry(e) for e in leg.get("scenes", [])]
        if leg.get("from"):  # where the leg starts, if not where the last one ended
            pos = parse_pos(leg["from"])
            entered_map = pos[0]
        # 1. the scenes that happen before the walk
        for k, e in enumerate(entries):
            target = chk.scene_target(e)
            if target is None:
                res.problems.append("%s: no object, coord trigger, sign or OnFrame entry uses it; give \"at\"/\"map\"" % e["label"])
            elif target[0] == "ambiguous":
                res.problems.append("%s: used on several maps (%s); give \"at\"/\"map\"" % (e["label"], ", ".join(target[1])))
                target = None
            scene_map = target[1] if target else (chk.world.map_for_label(e["label"]) or pos[0])
            entering = pos[0] != scene_map or scene_map == entered_map or e.get("enter")
            entered_map = None
            for assign in e.get("pre", []):  # what C code does before the scene (the table says why)
                name, _, value = assign.partition("=")
                if name.startswith("FLAG_"):
                    st.flags[chk.sim.fkey(name)] = value.strip() not in ("0", "FALSE")
                elif name.startswith("ITEM_"):
                    st.items[name] = int(value or 1)
                else:
                    st.vars[chk.sim.vkey(name)] = chk.c.value(value.strip())
            view = MapView(chk, chk.world.maps[scene_map], st, persist=entering)
            if entering:
                st = view.state  # the player walked in: the map's load scripts ran for real
            if hooks:
                hooks.scene(leg, e, st.flattened(), target, pos, scene_map, view)
            if target and not e.get("no_trigger_check"):
                for p in chk.check_trigger(e, target, view):
                    res.problems.append("%s can't start: %s" % (e["label"], p))
            ob = target[3] if target and target[0] == "adjacent" else None
            if target and target[0] == "tile" and pos[0] != target[1]:
                pos = (target[1],) + sorted(target[2])[0]  # a coord trigger: the player stands on it
            # where scripted movement leaves the player (a pseudo var the simulator moves with applymovement)
            st.vars[PLAYER_XY] = (pos[1], pos[2]) if pos[0] == scene_map else UNK
            ctx = Ctx(scene_map, last_talked=ob["index"] if isinstance(ob, dict) and "index" in ob else 0)
            ctx.then_map = parse_pos(e["then"])[0] if e.get("then") else None
            st = chk.sim.run(e["label"], st, ctx).flattened()
            moved = st.vars.pop(PLAYER_XY, UNK)
            res.guesses += [(e["label"],) + g for g in ctx.guesses]
            if hooks and hasattr(hooks, "scene_after"):
                hooks.scene_after(leg, e, st)
            for p in chk.check_expect(e.get("expect", []), st):
                res.problems.append("%s: expected %s" % (e["label"], p))
            loop = chk.frame_loop(scene_map, e["label"], st, ctx)
            if loop:
                res.problems.append(loop)
            res.warps += ctx.warps
            if e.get("then"):
                pos = parse_pos(e["then"])
                entered_map = pos[0]
                if ctx.warps and all(d == 0 for d in ctx.warp_depths) and pos[0] not in {w[1] for w in ctx.warps}:
                    res.problems.append("%s: \"then\" says %s, but the scene only warps to %s" % (
                        e["label"], chk.world.pretty(pos[0]), ", ".join(sorted({chk.world.pretty(w[1]) for w in ctx.warps}))))
            elif ctx.warps:
                sure = [w for w, d in zip(ctx.warps, ctx.warp_depths) if d == 0]
                if len({w[1] for w in ctx.warps}) > 1 or not sure:
                    res.notes.append("%s may warp to %s (in a branch the simulation can't decide); the table can say "
                                     "where the player ends up (\"then\")" % (
                                         e["label"], ", ".join(sorted({chk.world.pretty(w[1]) for w in ctx.warps}))))
                wp = chk.warp_position(sure[-1]) if sure else None
                if wp:
                    pos = wp
                    entered_map = pos[0]
            elif isinstance(moved, tuple) and pos[0] == scene_map:
                pos = (scene_map,) + moved
            visited.add(pos[0])
        badges, hms = chk.have_summary(st)
        res.have = (badges, hms)
        want = leg.get("have")
        if want is not None:
            if want.get("badges") is not None and want["badges"] != badges:
                res.problems.append("the table says %d badges by now, the simulation has %d" % (want["badges"], badges))
            if want.get("hms") is not None and sorted(want["hms"]) != sorted(hms):
                res.problems.append("the table says HMs %s, the simulation has %s" % (
                    ", ".join(sorted(want["hms"])) or "none", ", ".join(sorted(hms)) or "none"))
        if state_at and (leg.get("id") == state_at):
            return st, results
        # 2. the walk to where the next scene starts (through the "via" waypoints first)
        to = leg.get("to")
        nxt = next((lg for lg in legs[i + 1:] if not lg.get("side")), None) if not leg.get("side") else None
        if to is None and nxt is not None and nxt.get("scenes"):
            target = chk.scene_target(norm_entry(nxt["scenes"][0]))
        else:
            target = parse_to(chk, to)
        waypoints = [parse_to(chk, v) for v in leg.get("via", [])]
        res.start = pos
        if target is None or target[0] == "ambiguous":
            if nxt is not None or leg.get("side"):
                res.problems.append("no place to walk to (give \"to\")")
            res.skipped = bool(only) and not (leg.get("id") == only or only.lower() in leg.get("name", "").lower())
            results.append(res)
            res.ok = not res.problems
            if hooks:
                hooks.leg_end(leg, res, st.flattened(), pos, set(visited))
            if leg.get("side"):
                st, pos, entered_map, visited = saved
            continue
        puzzles = table.get("puzzles", {})
        if target[1] in puzzles and target[0] != "map":
            res.notes.append("%s: %s – not modelled, the walk only checks that the player gets in" % (
                chk.world.pretty(target[1]), puzzles[target[1]]))
            target = ("map", target[1], None, target[3])
        if pos[0] in puzzles and target[1] != pos[0]:
            md = chk.world.maps[pos[0]]
            res.notes.append("%s: %s – not modelled, the walk starts at its entrance" % (md.name, puzzles[pos[0]]))
            pos = (pos[0], md.warps[0]["x"], md.warps[0]["y"])
            res.start = pos
        res.target = target
        if only is None or leg.get("id") == only or (only.lower() in leg.get("name", "").lower()):
            here = pos
            for k, wp in enumerate(waypoints + [target]):
                sub = LegResult(leg)
                st = walk(chk, st, here, wp, visited, sub, verbose).flattened()
                add_walk(res, sub)
                if not sub.end:
                    break
                here = sub.end
                if wp[0] == "map" and (k < len(waypoints) or isinstance(to, str)):
                    # a waypoint or a "to" that is a map: the player walks in, so its load scripts run for real
                    st = MapView(chk, chk.world.maps[wp[1]], st, persist=True).state.flattened()
            res.end = sub.end
            if sub.target is not None:
                res.target = sub.target  # an object's spot after its map's load scripts moved it
            new = res.end if res.end else target_pos(chk, target)
        else:
            res.skipped = True
            new = target_pos(chk, target)
            visited.add(new[0])
            for k, wp in enumerate(waypoints + [target]):
                if wp[0] == "map" and (k < len(waypoints) or isinstance(to, str)):
                    st = MapView(chk, chk.world.maps[wp[1]], st, persist=True).state.flattened()
        if new[0] != pos[0] or len(res.path_maps) > 1:
            entered_map = new[0]
        pos = new
        res.ok = not res.problems and not res.blockers and not res.detours
        results.append(res)
        if hooks:
            hooks.leg_end(leg, res, st.flattened(), pos, set(visited))
        if leg.get("side"):
            st, pos, entered_map, visited = saved
    return st, results


def parse_to(chk, spec):
    """a walk target from the table: "MAP_X x y" (a tile), "MAP_X" (entering the map), a label, or a scene dict"""
    if isinstance(spec, str) and re.match(r"MAP_\w+ -?\d+ -?\d+$", spec):
        m, x, y = parse_pos(spec)
        return ("tile", m, {(x, y)}, None)
    if isinstance(spec, str) and spec.startswith("MAP_"):
        return ("map", spec, None, None)
    if isinstance(spec, dict):
        return chk.scene_target(dict(spec, label=spec.get("label", "")))
    if isinstance(spec, str):
        return chk.scene_target({"label": spec})
    return None


def add_walk(res, sub):
    """one stretch of a leg's walk (a "via" waypoint, then the target) into the leg's result"""
    res.problems += sub.problems
    res.blockers += sub.blockers
    res.detours += sub.detours
    res.notes += [n for n in sub.notes if n not in res.notes]
    res.guesses += sub.guesses
    res.steps += sub.steps
    res.route += sub.route[1:] if res.route and sub.route and res.route[-1] == sub.route[0] else sub.route
    res.path_maps += sub.path_maps


def target_pos(chk, target):
    """where the player is assumed to be when a walk failed (so the next legs can still be checked)"""
    kind, m, where, _ = target
    if kind == "tile":
        return (m,) + sorted(where)[0]
    if kind == "adjacent":
        return (m, where[0], where[1] + 1)
    md = chk.world.maps.get(m)
    if md and md.warps:
        return (m, md.warps[0]["x"], md.warps[0]["y"])
    return (m, 0, 0)


def goal_for(srch, target):
    kind, m, where, _ = target
    if kind == "tile":
        tiles = {(m, x, y) for x, y in where}
        return (lambda n: (n[0], n[1], n[2]) in tiles), tiles
    if kind == "map":
        return (lambda n: n[0] == m), set()
    ox, oy = where
    v = srch.view(m)
    ob = target[3]
    if isinstance(ob, dict) and v is not None:
        # where the object stands now (its map's OnTransition may move it: setobjectxyperm)
        moved = next(((o["cx"], o["cy"]) for o in v.objects if o["index"] == ob.get("index")), None)
        if moved is not None:
            ox, oy = moved
    srch.goal_pos = (ox, oy)
    goals = set()
    for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0)):
        goals.add((m, ox + dx, oy + dy))
        cx, cy = ox + dx, oy + dy
        if v and v.inside(cx, cy) and v.tile(cx, cy)[0] == COUNTER:
            goals.add((m, ox + 2 * dx, oy + 2 * dy))
    return (lambda n: (n[0], n[1], n[2]) in goals), set()


def walk(chk, st, pos, target, visited, res, verbose):
    """search from pos to target; returns the state after the coord scenes the walk had to trigger"""
    applied = set()
    triggered = []
    while True:
        srch = Search(chk, st, visited)
        start = srch.node_at(*pos)
        if start is None:
            res.problems.append("start %s (%d, %d) is not on the map" % pos)
            return st
        goal, goal_tiles = goal_for(srch, target)
        if target[0] == "adjacent" and getattr(srch, "goal_pos", None):
            res.target = (target[0], target[1], srch.goal_pos, target[3])
        starts = [start]
        end, prev = srch.search(starts, goal, goal_tiles)
        if end is not None:
            break
        # a coord scene the player walks onto (and past) may be what clears the way (Route 121's Aqua grunts
        # leave when the player comes near): if a reachable one hides an object on the cheapest path, trigger
        # it and search again
        end2, prev2 = srch.search(starts, goal, goal_tiles, relaxed=True)
        flags = [o.key for _, _, obs, _ in (Search.path(prev2, end2) if end2 else []) for o in obs if o.kind == "object" and o.key]
        found = None
        for n in prev:
            v = srch.view(n[0])
            for ev in v.triggers.get((n[1], n[2]), ()):
                key = (n[0], ev["script"])
                if key in applied or (n[0], n[1], n[2]) in goal_tiles or srch.trigger_obstacle(n[0], ev) is not None:
                    continue
                trial = chk.sim.run(ev["script"], v.state.copy(), Ctx(n[0]))
                if any(trial.flag(chk.sim.fkey(f)) is True for f in flags):
                    found = (n[0], ev)
                    break
            if found:
                break
        if not found:
            break
        m, ev = found
        applied.add((m, ev["script"]))
        triggered.append((m, ev))
        st = MapView(chk, chk.world.maps[m], st, persist=True).state
        ctx = Ctx(m)
        st = chk.sim.run(ev["script"], st, ctx)
        res.notes.append("the walk triggers %s on %s (%d, %d), which clears the way" % (ev["script"], chk.world.pretty(m), ev["x"], ev["y"]))
        res.guesses += [(ev["script"],) + g for g in ctx.guesses]
    if end is not None:
        path = Search.path(prev, end)
    else:
        end2, prev2 = srch.search(starts, goal, goal_tiles, relaxed=True)
        if end2 is None:
            res.problems.append("no path at all (walls only; wrong coordinates?)")
            return st
        path = Search.path(prev2, end2)
        seen = set()
        for _, _, obs, _ in path:
            for o in obs:
                if o.ident() not in seen:
                    seen.add(o.ident())
                    res.blockers.append(o)
        end = None
    maps = [start[0]]
    route = [chk.world.pretty(start[0])]
    for p, how, obs, n in path:
        if maps[-1] != n[0]:
            maps.append(n[0])
            route.append(("Fly to " if how == "fly" else "") + chk.world.pretty(n[0]))
    res.route = route
    for p, how, obs, n in path:
        if how == "fly":
            res.notes.append("flies from %s to %s" % (chk.world.pretty(p[0]), chk.world.pretty(n[0])))
    res.path_maps = maps
    res.steps = len(path)
    if end is not None:
        res.end = end[:3]
        visited.update(maps)
        # a scene that cleared the way but lies off the path is a detour the story doesn't send the player on
        on_path = {(n[0], n[1], n[2]) for _, _, _, n in path}
        for m, ev in triggered:
            tiles = {(m, e["x"], e["y"]) for e in chk.world.maps[m].coords if e.get("script") == ev["script"]}
            if not tiles & on_path:
                res.detours.append("the way opens only after %s on %s (%d, %d), off the path: the story doesn't send the "
                                   "player there" % (ev["script"], chk.world.pretty(m), ev["x"], ev["y"]))
    # scenes the walk passes (entering a map with an OnFrame scene due, or a coord scene that moves on)
    frame_checked = set()
    for p, how, obs, n in path:
        v = srch.view(n[0])
        if (p[0] != n[0]) and v.frame_scene:
            res.notes.append("entering %s runs its OnFrame scene %s" % (v.md.name, v.frame_scene))
            if v.frame_scene not in frame_checked:
                frame_checked.add(v.frame_scene)
                fctx = Ctx(n[0])
                after = chk.sim.run(v.frame_scene, v.state.copy(), fctx)
                loop = chk.frame_loop(n[0], v.frame_scene, after, fctx)
                if loop:
                    res.problems.append(loop)
        for ev in v.triggers.get((n[1], n[2]), ()):
            if (n[0], n[1], n[2]) not in goal_tiles and srch.trigger_obstacle(n[0], ev) is None:
                res.notes.append("passes the coord scene %s on %s (%d, %d)" % (ev["script"], v.md.name, n[1], n[2]))
    for v in srch.views.values():
        if v.md.id in maps:
            res.guesses += [("load " + v.md.name,) + g for g in v.guesses]
    res.notes = list(dict.fromkeys(res.notes))
    return st


# ---------------------------------------------------------------------------
# Warp destinations of the round 1 scenes
# ---------------------------------------------------------------------------

def round1_warps(chk):
    """(label, file, line, warp) for every warp command in the Draconid scripts and tagged vanilla lines"""
    out = []
    pory_maps = {os.path.relpath(os.path.splitext(p)[0] + ".inc", ROOT)
                 for p in glob.glob(os.path.join(ROOT, "data/maps/*/scripts.pory"))}
    for i, (op, args, f, line) in enumerate(chk.scripts.cmds):
        if op not in WARP_OPS:
            continue
        if f.startswith("data/scripts/draconid/") or f in pory_maps or i in chk.scripts.tagged:
            out.append((chk.scripts.label_at[i], f, line, chk.sim._warp_dest(op, args)))
    return out


def check_warps(chk, results=(), verbose=False):
    """the destination tile is walkable and joins the rest of the map (a warp tile or a connection can be
    reached from it). Round 1 scripts' warps, plus every warp the story table's scenes took."""
    st = chk.new_game_state()
    srch = Search(chk, st, set())
    srch.can = {k: True for k in list(chk.field_moves) + ["BIKE"]}
    problems = []
    checked = 0
    todo = round1_warps(chk)
    seen = {(w[1], w[2], w[3], w[4]) for _, _, _, w in todo}
    for r in results:
        for w in r.warps:
            if (w[1], w[2], w[3], w[4]) not in seen:
                seen.add((w[1], w[2], w[3], w[4]))
                todo.append(("a scene of leg %s" % r.leg.get("id"), "progression.json", 0, w))
    for label, f, line, w in todo:
        wp = chk.warp_position(w)
        where = "%s (%s:%d) %s %s" % (label, f, line, w[0], w[1])
        if wp is None:
            problems.append("%s: can't resolve the destination" % where)
            continue
        m, x, y = wp
        v = srch.view(m)
        if v is None or not v.inside(x, y):
            problems.append("%s: (%d, %d) is outside the map" % (where, x, y))
            continue
        checked += 1
        b, coll, e = v.tile(x, y)
        is_warp_tile = (x, y) in v.warps_at
        if coll and not is_warp_tile:
            problems.append("%s: (%d, %d) is an impassable tile" % (where, x, y))
            continue
        static = [o for o in chk.world.maps[m].objects if (o["x"], o["y"]) == (x, y) and o.get("flag") in (None, "0")]
        if static:
            problems.append("%s: (%d, %d) is taken by an object that is always there (%s)" % (
                where, x, y, static[0].get("local_id") or static[0]["index"]))
        start = srch.node_at(m, x, y)
        # an exit: another map, or a warp tile other than the arrival tile
        exits = lambda n: n[0] != m or ((n[1], n[2]) in v.warps_at and (n[1], n[2]) != (x, y))
        end, prev = srch.search([start], exits, set(), relaxed=True)
        if end is None:
            problems.append("%s: (%d, %d) on %s is a closed pocket (no warp or connection reachable)" % (where, x, y, v.md.name))
        elif verbose:
            print("  warp ok: %s -> %s (%d, %d)" % (label, v.md.name, x, y))
    return checked, problems


# ---------------------------------------------------------------------------
# Output
# ---------------------------------------------------------------------------

def fmt_pos(chk, p):
    return "%s (%d, %d)" % (chk.world.pretty(p[0]), p[1], p[2]) if p else "?"


def fmt_target(chk, t):
    if t is None:
        return "?"
    kind, m, where, _ = t
    if kind == "tile":
        return "%s %s" % (chk.world.pretty(m), " ".join("(%d, %d)" % xy for xy in sorted(where)[:3]) + (" …" if len(where) > 3 else ""))
    if kind == "adjacent":
        return "%s next to (%d, %d)" % (chk.world.pretty(m), where[0], where[1])
    return "%s (entering)" % chk.world.pretty(m)


def scene_labels(leg):
    return [norm_entry(e)["label"] for e in leg.get("scenes", [])]


def print_results(chk, results, verbose, show_path):
    locks = 0
    for r in results:
        leg = r.leg
        if getattr(r, "skipped", False):
            continue
        tag = "OK  " if r.ok else "LOCK" if r.blockers else "DTOR" if r.detours and not r.problems else "FAIL"
        if not r.ok:
            locks += 1
        print("[%s] %-5s %s%s" % (tag, leg.get("id", ""), leg.get("name", ""), " (side trip)" if leg.get("side") else ""))
        if r.target is not None:
            print("        %s -> %s: %s" % (fmt_pos(chk, r.start), fmt_target(chk, r.target),
                                         ("%d steps via %s" % (r.steps, " > ".join(r.route)))
                                         if r.end else "blocked"))
        for p in r.problems:
            print("        problem: %s" % p)
        for p in r.detours:
            print("        detour: %s" % p)
        if r.blockers:
            b = r.blockers[0]
            print("        first blocker: %s" % b.what)
            print("          clears when: %s" % b.clear)
            for b in r.blockers[1:]:
                print("        then: %s" % b.what)
        if verbose or not r.ok:
            for n in r.notes:
                print("        note: %s" % n)
        if verbose:
            badges, hms = r.have
            print("        has: %d badges, HMs %s" % (badges, ", ".join(hms) or "none"))
            for g in r.guesses[:12]:
                print("        guess: %s" % " / ".join(str(x) for x in g))
            if len(r.guesses) > 12:
                print("        guess: … %d more" % (len(r.guesses) - 12))
    return locks


def print_markdown(chk, results):
    print("| Leg | What happens (the scenes, then the walk) | Badges / HMs | Walk | Result |")
    print("|---|---|---|---|---|")
    for r in results:
        leg = r.leg
        badges, hms = r.have
        labels = "<br>".join("`%s`" % l for l in scene_labels(leg)) or "–"
        if r.blockers:
            res = "**blocked**: %s" % r.blockers[0].what
        elif r.detours:
            res = "**detour**: %s" % r.detours[0]
        elif r.problems:
            res = "**problem**: %s" % "; ".join(r.problems)
        elif r.end:
            res = "ok, %d steps via %s" % (r.steps, ", ".join(r.route))
        else:
            res = "ok"
        where = "%s → %s" % (fmt_pos(chk, r.start), fmt_target(chk, r.target)) if r.target else "–"
        name = "%s%s" % (leg.get("name", ""), " *(side trip)*" if leg.get("side") else "")
        print("| %s | %s<br>%s | %d / %s | %s | %s |" % (leg.get("id", ""), name, labels, badges,
                                                       ", ".join(h.title().replace("_", " ") for h in hms) or "–",
                                                       where, res))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--leg", help="check one leg (its id, or a word of its name) and print its path")
    ap.add_argument("--list", action="store_true", help="print the story table")
    ap.add_argument("--markdown", action="store_true", help="print the leg table as Markdown")
    ap.add_argument("--state", metavar="LEG", help="print the simulated flags/vars after a leg's scenes")
    ap.add_argument("--grep", default="", help="with --state: only names matching this regex")
    ap.add_argument("--no-warps", action="store_true", help="skip the warp destination check")
    ap.add_argument("--gender", default="MALE", choices=("MALE", "FEMALE"))
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()
    table = json.load(open(TABLE))
    chk = Checker(args.gender)
    if args.list:
        for leg in table["legs"]:
            want = leg.get("have", {})
            print("%-5s %-60s scenes: %s" % (leg.get("id", ""), leg.get("name", ""), ", ".join(scene_labels(leg)) or "-"))
            if want:
                print("      has: %s badges, HMs %s" % (want.get("badges", "?"), ", ".join(want.get("hms", [])) or "none"))
        return 0
    if args.state:
        st, _ = run_story(chk, table, only="-", state_at=args.state)
        rx = re.compile(args.grep) if args.grep else None
        for k, v in sorted(st.vars.items(), key=lambda kv: str(kv[0])):
            n = chk.name_of(k, "VAR")
            if (rx is None and v not in (0,)) or (rx and rx.search(n)):
                print("%-40s %s" % (n, v))
        for k, v in sorted(st.flags.items(), key=lambda kv: str(kv[0])):
            n = chk.name_of(k, "FLAG")
            if rx and rx.search(n):
                print("%-40s %s" % (n, v))
        for k, v in sorted(st.items.items()):
            if rx is None or rx.search(k):
                print("%-40s %s" % (k, v))
        return 0
    _, results = run_story(chk, table, only=args.leg, verbose=args.verbose)
    if args.markdown:
        print_markdown(chk, results)
        return 0
    locks = print_results(chk, results, args.verbose or bool(args.leg), bool(args.leg))
    warp_problems = []
    if not args.no_warps and not args.leg:
        checked, warp_problems = check_warps(chk, results, args.verbose)
        print("warps: %d warp destinations of round 1 and table scenes checked, %d problem(s)" % (checked, len(warp_problems)))
        for p in warp_problems:
            print("  problem: %s" % p)
    total = sum(1 for r in results if not getattr(r, "skipped", False))
    print("%d leg(s) checked, %d blocked or failing" % (total, locks))
    return 1 if locks or warp_problems else 0


if __name__ == "__main__":
    sys.exit(main())
