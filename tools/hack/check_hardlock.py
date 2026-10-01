#!/usr/bin/env python3
"""
check_hardlock.py - hard-lock checker for the round 1 scripts (D-263 - D-265, docs/hack_progression.md).

  python3 tools/hack/check_hardlock.py              # every check; exit 1 on a LOCK finding
  python3 tools/hack/check_hardlock.py -v           # also the notes (declined prompts, retries, by-design traps)
  python3 tools/hack/check_hardlock.py --only lock,wait,frame,coord,battle,trap,reentry
  python3 tools/hack/check_hardlock.py --markdown   # the findings table for docs/hack_progression.md
  python3 tools/hack/check_hardlock.py --battles    # every round 1 battle and what a loss does

A static companion to check_progression.py: it reuses its script parser, constants, map views, tile search and the
story table tools/hack/progression.json. Every path of the round 1 scripts is followed on its own - the files in
data/scripts/draconid/, the new maps' scripts.pory, and every vanilla label block with an `@ Draconid Emerald` line
- from each place the game starts a script (objects, coord triggers, signs, OnFrame / OnWarp tables, the C hooks),
forking at every branch the path can't decide (a YES/NO, a menu, a battle's outcome, a flag set elsewhere; a branch
taken is remembered, so a later test of the same flag goes the same way). Scenes the story table plays start from
the state the table's simulation has there. Findings carry file:line label and a severity: LOCK (the player is
stuck or the story can't go on), CHECK (a lead to verify in the emulator) and NOTE (by design; shown with -v).

  lock    a lock/lockall path of a round 1 script that reaches end (or its last return) without release. The engine
          unlocks the player's controls whenever a script ends (ScriptContext_RunScript), so this is not a hard
          lock: the other objects on the map stay frozen until it reloads (CHECK; emulator-tested, D-264)
  wait    an explicit waitstate with nothing before it (since the last waitstate) that resumes the script - a warp,
          a special marked waitstate=1 (data/specials.inc; the macro adds its own), or C code that calls
          ScriptContext_Enable or returns to the field with CB2_ReturnToFieldContinueScript*: the player stays
          frozen (LOCK); a movement script without step_end or with a non-movement command (LOCK)
  frame   an OnFrame entry (map_script_2) with a path that neither changes its var nor warps: the scene starts
          again on the next frame. Through a YES/NO or a lost battle it is a forced retry (NOTE), with no choice
          on the path a LOCK
  coord   a coord trigger with a path that leaves its var, the player's tile and the map as they were: stepping
          back on starts it again. A NOTE when the player can step off onto a tile without that trigger, a LOCK
          when every tile off it is the same trigger or a wall
  battle  every round 1 battle (trainerbattle*, multi_*, scripted wild battles) and what a loss does: goes on
          (FLAG_DRACONID_NO_WHITEOUT, an early-rival battle, the first battle) - then is the flag cleared again? -
          or whites out to the last heal location (EventScript_WhiteOut runs: the Elite Four reset, Mr. Briney).
          After a whiteout the scene must start again: its object shown, its trigger's var as it was (temp vars and
          flags reset, load scripts run); for story-table scenes that is checked on the table's state, and a walk
          back from every heal location the story passed before (boats, the cable car and ferries included: the
          table's "then" rides and objects whose script warps)
  trap    from the end of every story leg's walk and the landing of every warp its scenes take, a heal location
          (a Pokémon Center, the village house) can be reached with what the player has then; maps where being
          shut in is the design (the Elite Four) are listed in the table ("no_heal_ok")
  reentry every story-scene path that gives control back before the scene is done - it writes less than another
          path of the same scene (a declined prompt, a lost battle) - must leave the scene startable again after
          leaving and re-entering the map (temp vars and flags reset, load scripts run again) or retryable by
          talking to someone on the map; and a temp var/flag a script sets to the value a warp's destination
          waits for is lost in the warp (CHECK)

Not modelled: what C code does inside specials (a special's VAR_RESULT is a fork), the party (every battle can be
won or lost), gym puzzles (the table's "puzzles": getting in is enough), which Pokémon Centers the player really
used. A finding is a lead: every LOCK is reproduced in the emulator before it is fixed or reported.
"""

import argparse
import glob
import json
import os
import re
import sys
from collections import namedtuple

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_progression as cp  # noqa: E402

ROOT = cp.ROOT
UNK = cp.UNK
MAX_PATHS = 3000      # paths followed per entry script before the rest are cut
MAX_STEPS = 400000    # commands per entry script

LOCK, CHECK, NOTE = "LOCK", "CHECK", "NOTE"
Finding = namedtuple("Finding", "severity kind where what")

NO_WHITEOUT = ("FLAG_DRACONID_NO_WHITEOUT", "B_FLAG_NO_WHITEOUT")
HEAL_SPECIALS = {"HealPlayerParty"}
# msgbox types whose std script locks and releases by itself (data/scripts/std_msgbox.inc)
MSGBOX_RELEASES = {"MSGBOX_NPC", "MSGBOX_SIGN", "MSGBOX_AUTOCLOSE"}
WILD_BATTLE = re.compile(r"^(BattleSetup_Start\w*Battle|Start\w*Battle)$")
# battles whose loss never whites out: the early-rival battle (heals, VAR_RESULT = lost), the first battle
LOSS_GOES_ON = {"trainerbattle_earlyrival", "StartBirchRescueBattle", "StartOldManTutorialBattle"}
CONT_BATTLES = {"trainerbattle_no_intro", "trainerbattle_two_trainers_no_intro", "trainerbattle_earlyrival"}
# vars/flags that aren't story state
SCRATCH_VARS = re.compile(r"^VAR_(0x80[0-9A-F]{2}|RESULT|FACING|LAST_TALKED|TEMP_\w+)$")


def rel(path):
    return os.path.relpath(path, ROOT) if os.path.isabs(path) else path


# ---------------------------------------------------------------------------
# What the engine does that the scripts can't tell
# ---------------------------------------------------------------------------

def specials_with_waitstate():
    """specials the special macro follows with its own waitstate (def_special ..., waitstate=1)"""
    out = set()
    for line in open(os.path.join(ROOT, "data/specials.inc")):
        m = re.match(r"\s*def_special\s+(\w+).*waitstate\s*=\s*1", line)
        if m:
            out.add(m.group(1))
    return out


class CSource:
    """C function bodies: does a special/callnative resume a waiting script?"""
    RESUME = re.compile(r"ScriptContext_Enable|CB2_ReturnToFieldContinueScript\w*|FieldCB_ContinueScript\w*")

    def __init__(self):
        self.bodies = {}
        for path in glob.glob(os.path.join(ROOT, "src/*.c")):
            text = open(path, errors="replace").read()
            for m in re.finditer(r"^(?:static\s+)?(?:\w+\s+)+\**(\w+)\s*\([^;{]*\)\s*\{", text, re.M):
                depth, i = 1, m.end()
                while i < len(text) and depth:
                    depth += {"{": 1, "}": -1}.get(text[i], 0)
                    i += 1
                self.bodies.setdefault(m.group(1), text[m.end():i])
        self._cache = {}

    def resumes(self, func, depth=0):
        """True if func (or a function, task or callback it names, two levels down) resumes the script"""
        if (func, depth) in self._cache:
            return self._cache[(func, depth)]
        body = self.bodies.get(func)
        if body is None:
            return None
        res = bool(self.RESUME.search(body))
        if not res and depth < 2:
            for callee in set(re.findall(r"\b([A-Z]\w+)\b", body)):
                if callee != func and callee in self.bodies and self.resumes(callee, depth + 1):
                    res = True
                    break
        self._cache[(func, depth)] = res
        return res


# ---------------------------------------------------------------------------
# Path explorer: every path of a script on its own (no merging)
# ---------------------------------------------------------------------------

class P:
    """one path through a script"""
    __slots__ = ("pc", "stack", "w", "a", "facing_not", "lock", "nowo", "healed", "xy", "choices", "events", "touched",
                 "enabler", "labels", "cmp", "cmpkey")

    def __init__(self, pc):
        self.pc = pc
        self.stack = ()
        self.w = {}            # writes on this path: ("F"|"V"|"I", key) -> value
        self.a = {}            # what the branches taken imply (a flag found set, a var found equal)
        self.lock = None       # the pc of the lock/lockall still in force
        self.nowo = None       # the pc of the setflag FLAG_DRACONID_NO_WHITEOUT still in force
        self.healed = False
        self.xy = (0, 0)       # the player's scripted movement so far (None: can't tell)
        self.choices = []      # pcs where the player's answer (or a battle's outcome) decided the way
        self.events = []       # ("battle", pc, info)
        self.touched = False   # passed a round 1 command
        self.enabler = None    # a command since the last waitstate that resumes a waiting script
        self.labels = []
        self.cmp = None        # (a, b) of the last compare / checkflag
        self.cmpkey = None     # (key, constant) the last compare / checkflag tested
        self.facing_not = frozenset()  # directions VAR_FACING was found not to be (a switch / if chain on it)

    def fork(self):
        q = P(self.pc)
        for k in self.__slots__:
            v = getattr(self, k)
            setattr(q, k, dict(v) if isinstance(v, dict) else list(v) if isinstance(v, list) else v)
        return q


End = namedtuple("End", "how pc path info")  # how: end, return, warp, battle (a trainer battle takes over), cut


class Explorer:
    def __init__(self, chk, round1_pcs, csrc, special_ws):
        self.chk = chk
        self.s = chk.scripts
        self.c = chk.c
        self.sim = chk.sim
        self.round1 = round1_pcs
        self.csrc = csrc
        self.special_ws = special_ws
        self.label_pcs = set(self.s.labels.values())
        self.all_dirs = {self.c.value(d) for d in ("DIR_SOUTH", "DIR_NORTH", "DIR_WEST", "DIR_EAST")}
        self.wait_findings = {}
        self.movement_ok = {}
        self.whiteouts = []
        self.cur_map = None

    # --- values -------------------------------------------------------------------
    def fkey(self, name):
        return ("F", self.sim.fkey(name))

    def vkey(self, name):
        return ("V", self.sim.vkey(name))

    def get(self, p, key, base):
        if key in p.w:
            return p.w[key]
        if key in p.a:
            return p.a[key]
        return base(key)

    def val(self, token, p, base):
        if self.sim.is_var(token):
            return self.get(p, self.vkey(token), base)
        v = self.c.value(token)
        return v if v is not None else UNK

    def cond(self, op, args, p, base):
        """(cond True/False/UNK, target, (key, value if taken, value if not taken))"""
        kind = op.split("_if_")[1] if "_if_" in op else op
        if kind in ("set", "unset"):
            key = self.fkey(args[0])
            v = self.get(p, key, base)
            imp = (key, kind == "set", kind != "set")
            return (UNK if v == UNK else (bool(v) if kind == "set" else not v)), args[1], imp
        if kind in ("defeated", "not_defeated"):
            key = ("F", self.sim.trainer_flag(args[0]))
            v = self.get(p, key, base)
            imp = (key, kind == "defeated", kind != "defeated")
            return (UNK if v == UNK else (bool(v) if kind == "defeated" else not v)), args[1], imp
        if kind not in cp.COND:
            return UNK, args[-1], None
        if len(args) == 3:
            a, b, target = self.val(args[0], p, base), self.val(args[1], p, base), args[2]
            key = self.vkey(args[0]) if self.sim.is_var(args[0]) else None
            const = self.c.value(args[1]) if not self.sim.is_var(args[1]) else None
        else:
            a, b = p.cmp if p.cmp else (UNK, UNK)
            target = args[0]
            key, const = p.cmpkey if p.cmpkey else (None, None)
        imp = None
        if key is not None and const is not None:
            imp = (key, const if kind == "eq" else None, const if kind == "ne" else None)
        if a == UNK or b == UNK:
            return UNK, target, imp
        return cp.COND[kind](a, b), target, imp

    # --- the walk -----------------------------------------------------------------
    def explore(self, label, base, max_paths=MAX_PATHS):
        """all paths of the script at label. base(key) -> the value at the start (UNK if unknown)"""
        start = self.s.labels.get(label)
        if start is None:
            return []
        ends = []
        work = [P(start)]
        seen = set()
        steps = 0
        while work:
            p = work.pop()
            while True:
                steps += 1
                if steps > MAX_STEPS or len(ends) + len(work) > max_paths:
                    ends.append(End("cut", p.pc, p, "too many paths"))
                    break
                if p.pc >= len(self.s.cmds):
                    ends.append(End("end", p.pc, p, "runs off the file"))
                    break
                pc = p.pc
                if pc in self.label_pcs:
                    k = (pc, p.stack, frozenset(p.w.items()), frozenset(p.a.items()), p.lock is None, p.nowo is None)
                    if k in seen:
                        ends.append(End("cut", pc, p, "repeats"))
                        break
                    seen.add(k)
                    p.labels.append(self.s.label_at[pc])
                if pc in self.round1:
                    p.touched = True
                op, args, _, _ = self.s.cmds[pc]
                res = self.step(p, op, args, base, work)
                if res is not None:
                    ends.append(res)
                    break
        return ends

    def jump(self, p, label):
        t = self.s.labels.get(label)
        if t is None:
            return False
        p.pc = t
        return True

    def branch(self, p, cond, target, kind, work, choice, imp=None, facing=None):
        """facing: the direction an unknown VAR_FACING test compares with - the side where it isn't that direction
        can't happen once all four are ruled out (a switch on VAR_FACING with a case per direction)"""
        if cond is True or cond is False:
            if cond:
                if kind == "call":
                    p.stack = p.stack + (p.pc + 1,)
                if not self.jump(p, target):
                    p.pc += 1
            else:
                p.pc += 1
            return None
        q = p.fork()
        if choice:
            q.choices.append(p.pc)
            p.choices.append(p.pc)
        if imp is not None:
            key, if_taken, if_not = imp
            if if_taken is not None:
                q.a[key] = if_taken
            if if_not is not None:
                p.a[key] = if_not
        if kind == "call":
            q.stack = q.stack + (q.pc + 1,)
        if self.jump(q, target):
            work.append(q)
        p.pc += 1
        if facing is not None:
            p.facing_not = p.facing_not | {facing}
            if self.all_dirs <= p.facing_not:
                return End("cut", p.pc, p, "VAR_FACING is none of the four directions: can't happen")
        return None

    def step(self, p, op, args, base, work):
        pc = p.pc
        if op == "end":
            return End("end", pc, p, None)
        if op == "return":
            if p.stack:
                p.pc, p.stack = p.stack[-1], p.stack[:-1]
                return None
            return End("return", pc, p, None)
        if op == "goto":
            if not self.jump(p, args[0]):
                return End("end", pc, p, "goto unknown label %s" % args[0])
            return None
        if op == "call":
            ret = pc + 1
            if self.jump(p, args[0]):
                p.stack = p.stack + (ret,)
            else:
                p.pc = ret
            return None
        if op == "compare":
            p.cmp = (self.val(args[0], p, base), self.val(args[1], p, base))
            p.cmpkey = (self.vkey(args[0]) if self.sim.is_var(args[0]) else None,
                        self.c.value(args[1]) if not self.sim.is_var(args[1]) else None)
            p.pc += 1
            return None
        if op in ("checkflag", "checktrainerflag"):
            key = self.fkey(args[0]) if op == "checkflag" else ("F", self.sim.trainer_flag(args[0]))
            v = self.get(p, key, base)
            p.cmp = (UNK if v == UNK else int(bool(v)), 1)
            p.cmpkey = (key, "flag")
            p.pc += 1
            return None
        if op in ("goto_if", "call_if"):  # after checkflag: goto_if 0/1, target
            v = p.cmp[0] if p.cmp else UNK
            want = self.c.value(args[0])
            cond = UNK if v == UNK or want is None else (v == want)
            imp = None
            if p.cmpkey and p.cmpkey[1] == "flag" and want is not None:
                imp = (p.cmpkey[0], bool(want), not bool(want))
            return self.branch(p, cond, args[1], op[:4], work, choice=False, imp=imp)
        if op == "switch":
            p.w[self.vkey("VAR_0x8000")] = self.val(args[0], p, base)
            p.cmpkey = (self.vkey(args[0]) if self.sim.is_var(args[0]) else None, None)
            p.pc += 1
            return None
        if op == "case":
            if len(args) < 2:
                p.pc += 1
                return None
            v = self.get(p, self.vkey("VAR_0x8000"), base)
            c = self.c.value(args[0])
            cond = UNK if v == UNK or c is None else v == c
            imp = (self.vkey("VAR_0x8000"), c, None) if c is not None else None
            facing = c if p.cmpkey and p.cmpkey[0] == self.vkey("VAR_FACING") else None
            return self.branch(p, cond, args[1], "goto", work, choice=facing is None, imp=imp, facing=facing)
        if op.startswith("goto_if") or op.startswith("call_if"):
            cond, target, imp = self.cond(op, args, p, base)
            choice = "VAR_RESULT" in args[0] or (len(args) == 1 and p.cmpkey and p.cmpkey[0] == self.vkey("VAR_RESULT"))
            facing = None
            if imp and imp[0] == self.vkey("VAR_FACING") and imp[1] is not None:
                if imp[1] in p.facing_not:
                    cond = False  # already found not to face that way
                facing = imp[1]
            return self.branch(p, cond, target, op[:4], work, choice, imp, facing=facing)
        if op.startswith("trainerbattle") or op in cp.MULTI_BATTLE_OPS or op == "dotrainerbattle":
            return self.battle(p, op, args, base, work)
        if op in ("special", "callnative") and args and WILD_BATTLE.match(args[0]):
            return self.battle(p, op, args, base, work)
        if op in cp.WARP_OPS:
            return End("warp", pc, p, self.sim._warp_dest(op, args))
        if op == "special" and args and args[0] == "SetCB2WhiteOut":
            return End("warp", pc, p, None)  # a scripted whiteout: the map reloads at the last heal location
        if op == "special" and args and args[0] in cp.SPECIAL_WARPS:
            return End("warp", pc, p, ("special",) + cp.SPECIAL_WARPS[args[0]](UNK) + (None,))
        if op in ("special", "callnative") and args and args[0] in cp.NATIVE_HEAL_WARPS:
            h = next((h for h in self.chk.world.heal if h["id"] == cp.NATIVE_HEAL_WARPS[args[0]]), None)
            for f in cp.NATIVE_FLAGS.get(args[0], ()):
                p.w[self.fkey(f)] = True
            return End("warp", pc, p, (op, h["map"], h["x"], h["y"], None) if h else None)
        self.apply(p, op, args, base)
        p.pc += 1
        return None

    def battle(self, p, op, args, base, work):
        """a battle: a loss goes on (FLAG_DRACONID_NO_WHITEOUT, an early-rival battle) or whites out"""
        pc = p.pc
        trainers = [a for a in args if a.startswith("TRAINER_") and a != "TRAINER_NONE"]
        if op == "trainerbattle" and len(args) >= 17:
            trainers = [args[1]] + ([args[6]] if args[6] not in ("TRAINER_NONE", "0") else [])
        cont = (op in CONT_BATTLES or op in cp.MULTI_BATTLE_OPS or op in ("special", "callnative")
                or (op == "trainerbattle" and len(args) >= 17 and args[16] == "TRUE"))
        name = args[0] if op in ("special", "callnative") else op
        goes_on = "NO_WHITEOUT" if p.nowo is not None else ("its own rule" if name in LOSS_GOES_ON else None)
        p.events.append(("battle", pc, (op, tuple(trainers) or (name,), goes_on, cont)))
        if goes_on is None:
            self.whiteouts.append(End("whiteout", pc, p.fork(), (op, tuple(trainers) or (name,))))
        else:
            p.choices.append(pc)  # a lost battle goes on: its outcome decides the way
        if op in ("special", "callnative"):
            p.enabler = pc  # the special's own waitstate
        p.lock = None  # back from a battle the map's objects are set up again, unfrozen (emulator-checked)
        for t in trainers:
            p.w[("F", self.sim.trainer_flag(t))] = True
        if not cont:
            return End("battle", pc, p, (op, tuple(trainers)))
        p.pc += 1
        return None

    def apply(self, p, op, args, base):
        c = self.c
        if op in ("lock", "lockall"):
            p.lock = p.pc
        elif op in ("release", "releaseall"):
            p.lock = None
        elif op == "msgbox":
            if len(args) > 1 and args[1] in MSGBOX_RELEASES:
                p.lock = None
            if len(args) > 1 and args[1] == "MSGBOX_YESNO":
                p.w[self.vkey("VAR_RESULT")] = UNK
        elif op == "setflag" and args:
            p.w[self.fkey(args[0])] = True
            if args[0] in NO_WHITEOUT:
                p.nowo = p.pc
        elif op == "clearflag" and args:
            p.w[self.fkey(args[0])] = False
            if args[0] in NO_WHITEOUT:
                p.nowo = None
        elif op in ("setvar", "setorcopyvar") and len(args) >= 2:
            if op == "setorcopyvar" and self.sim.is_var(args[1]):
                p.w[self.vkey(args[0])] = self.val(args[1], p, base)
            else:
                v = c.value(args[1])
                p.w[self.vkey(args[0])] = v if v is not None else UNK
        elif op == "copyvar" and len(args) >= 2:
            p.w[self.vkey(args[0])] = self.val(args[1], p, base)
        elif op in ("addvar", "subvar") and len(args) >= 2:
            cur, d = self.get(p, self.vkey(args[0]), base), self.val(args[1], p, base)
            p.w[self.vkey(args[0])] = UNK if UNK in (cur, d) else (cur + d if op == "addvar" else cur - d) & 0xFFFF
        elif op == "specialvar" and args:
            v = self.sim.assume.get(args[1]) if len(args) > 1 else None
            p.w[self.vkey(args[0])] = UNK if v is None else c.value(v)
        elif op in ("special", "callnative") and args:
            if args[0] in HEAL_SPECIALS:
                p.healed = True
            if cp.RESULT_SPECIAL.match(args[0]):
                p.w[self.vkey("VAR_RESULT")] = UNK
            if (args[0] in self.special_ws or any("waitstate" in a for a in args[1:])
                    or self.csrc.resumes(args[0])):
                p.enabler = p.pc
        elif op in cp.RESULT_UNKNOWN_OPS:
            p.w[self.vkey("VAR_RESULT")] = UNK
        elif op in ("giveitem", "additem", "finditem") and args:
            cur = self.get(p, ("I", args[0]), base)
            n = c.value(args[1]) if len(args) > 1 else 1
            p.w[("I", args[0])] = UNK if cur == UNK else cur + (n or 1)
            p.w[self.vkey("VAR_RESULT")] = 1
        elif op == "removeitem" and args:
            cur = self.get(p, ("I", args[0]), base)
            p.w[("I", args[0])] = UNK if cur == UNK else max(0, cur - 1)
        elif op == "checkitem" and args:
            v = self.get(p, ("I", args[0]), base)
            p.w[self.vkey("VAR_RESULT")] = UNK if v == UNK else int(v > 0)
        elif op == "removeobject" and args:
            md, obj = self.sim.object_of(args[0], cp.State(), cp.Ctx(self.cur_map), args[1] if len(args) > 1 else None)
            if obj is not None and obj.get("flag") not in (None, "0", 0, ""):
                p.w[self.fkey(obj["flag"])] = True
        elif op == "applymovement" and len(args) >= 2:
            self.check_movement(args[1], p.pc)
            if args[0] in cp.PLAYER_IDS and p.xy is not None:
                d = self.sim.movement_delta(args[1])
                p.xy = (p.xy[0] + d[0], p.xy[1] + d[1]) if d else None
        elif op == "waitstate":
            self.check_waitstate(p)
            p.enabler = None

    # --- waits ------------------------------------------------------------------------
    def check_waitstate(self, p):
        pc = p.pc
        if p.enabler is not None or pc in self.wait_findings or pc not in self.round1:
            return
        self.wait_findings[pc] = Finding(LOCK, "wait", where(self.s, pc),
                                         "waitstate with nothing before it that resumes the script (no warp, no "
                                         "special with its own waitstate, no C code calling ScriptContext_Enable): "
                                         "the player stays frozen")

    def check_movement(self, label, pc):
        if label in self.movement_ok or pc not in self.round1:
            return
        i = self.s.labels.get(label)
        problem = None
        if i is None:
            problem = "the movement %s doesn't exist" % label
        else:
            for op, _, _, _ in self.s.cmds[i:i + 400]:
                if op == "step_end":
                    break
                if op not in MOVEMENT_OPS:
                    problem = "the movement %s has %s before its step_end (not a movement command)" % (label, op)
                    break
            else:
                problem = "the movement %s has no step_end" % label
        self.movement_ok[label] = problem is None
        if problem:
            self.wait_findings[("move", label)] = Finding(LOCK, "wait", where(self.s, pc), problem)


MOVEMENT_OPS = set()


def load_movement_ops():
    for line in open(os.path.join(ROOT, "asm/macros/movement.inc")):
        m = re.match(r"\s*create_movement_action\s+(\w+)", line)
        if m:
            MOVEMENT_OPS.add(m.group(1))
    MOVEMENT_OPS.add("step_end")


def where(scripts, pc):
    if pc is None or pc >= len(scripts.cmds):
        return "?"
    _, _, f, n = scripts.cmds[pc]
    return "%s:%d %s" % (f, n, scripts.label_at[pc])


# ---------------------------------------------------------------------------
# Entry points: where the game starts a script
# ---------------------------------------------------------------------------

Entry = namedtuple("Entry", "kind map label info")  # kind: object/coord/bg/frame/warpin/load/c


def entries(chk):
    out = []
    for md in chk.world.maps.values():
        for o in md.objects:
            if o.get("script") and o["script"] != "0x0":
                out.append(Entry("object", md.id, o["script"], o))
        for ev in md.coords:
            if ev.get("type") == "trigger" and ev.get("script"):
                out.append(Entry("coord", md.id, ev["script"], ev))
        for ev in md.bgs:
            if ev.get("script"):
                out.append(Entry("bg", md.id, ev["script"], ev))
        headers, frame = cp.map_scripts(chk.scripts, md)
        for var, value, label in frame:
            out.append(Entry("frame", md.id, label, (var, value)))
        for var, value, label in cp.warp_into_table(chk.scripts, headers):
            out.append(Entry("warpin", md.id, label, (var, value)))
    for path in glob.glob(os.path.join(ROOT, "src/*.c")):
        for m in re.finditer(r"(?:ScriptContext_SetupScript|RunScriptImmediately)\((\w+)\)", open(path, errors="replace").read()):
            if m.group(1) in chk.scripts.labels:
                out.append(Entry("c", chk.world.map_for_label(m.group(1)), m.group(1), rel(path)))
    return out


def round1_pcs(chk):
    """the commands of round 1: the Draconid scripts, the new maps' Poryscript, and every vanilla label block with an
    `@ Draconid Emerald` line"""
    s = chk.scripts
    pory = {os.path.relpath(os.path.splitext(p)[0] + ".inc", ROOT) for p in glob.glob(os.path.join(ROOT, "data/maps/*/scripts.pory"))}
    touched_labels = {s.label_at[i] for i in s.tagged}
    return {i for i, (op, args, f, n) in enumerate(s.cmds)
            if f.startswith("data/scripts/draconid/") or f in pory or s.label_at[i] in touched_labels}


# ---------------------------------------------------------------------------
# A tile search that also rides: the table's boats / cable car / ferries and objects whose script warps
# ---------------------------------------------------------------------------

class RideSearch(cp.Search):
    def __init__(self, hl, state, visited, rides):
        super().__init__(hl.chk, state, visited)
        self.hl = hl
        self.rides = rides        # (map, x, y) -> [(map, x, y)]
        self.talk_cache = {}

    def neighbors(self, node, goal_tiles):
        yield from super().neighbors(node, goal_tiles)
        v = self.view(node[0])
        for dest, obj in self.rides.get((node[0], node[1], node[2]), ()):
            if obj is not None and not any(o["index"] == obj[1] for o in self.view(obj[0]).objects) \
                    and self.hl.flag_of(obj) not in self.hl.travelling:
                continue  # the boatman isn't there (and no ride brings him along)
            n = self.node_at(*dest)
            if n:
                yield n, (), "ride"
        for dx, dy in cp.DIRS.values():
            x, y = node[1] + dx, node[2] + dy
            if v.inside(x, y) and v.tile(x, y)[0] == cp.COUNTER:
                x, y = x + dx, y + dy  # talked to across a counter
            for ob in v.obj_at.get((x, y), ()):
                for dest in self.talk_warps(node[0], ob):
                    n = self.node_at(*dest)
                    if n:
                        yield n, (), "talk"

    def talk_warps(self, map_id, ob):
        key = (map_id, ob["index"])
        if key not in self.talk_cache:
            out = []
            script = ob.get("script")
            if script and script in self.chk.scripts.labels:
                ctx = cp.Ctx(map_id, last_talked=ob["index"], budget=cp.SIDE_BUDGET)
                self.chk.sim.run(script, self.view(map_id).state.copy(), ctx)
                for w in ctx.warps:
                    wp = self.chk.warp_position(w)
                    if wp and wp[0] in self.chk.world.maps:
                        out.append(wp)
            self.talk_cache[key] = out
        return self.talk_cache[key]


# ---------------------------------------------------------------------------
# The checks
# ---------------------------------------------------------------------------

class Hardlock:
    def __init__(self, verbose=False):
        self.verbose = verbose
        self.chk = cp.Checker()
        self.table = json.load(open(cp.TABLE))
        self.chk.sim.assume = self.table.get("assume", {})
        load_movement_ops()
        self.r1 = round1_pcs(self.chk)
        self.ex = Explorer(self.chk, self.r1, CSource(), specials_with_waitstate())
        self.findings = []
        self.battles = {}       # pc -> (entry label, info)
        self.scene_states = {}  # label -> (leg, entry dict, State before, target, pos, map)
        self.leg_ends = []      # (leg, res, State, pos, visited)
        self.way_back = {}      # (scene, story writes) already walked back to
        self.lock_hits = {}     # (lock pc, end pc) -> the entries that get there
        self._cand_cache = {}
        self.scene_after_states = {}  # label -> State after the scene
        self.loss_info = {}           # battle pc -> what a whiteout there leads to
        self.travelling = set()       # hide flags a ride scene clears: the boatman who arrives with the player
        c = self.chk.c
        self.temp_flags = range(c.value("TEMP_FLAGS_START"), c.value("TEMP_FLAGS_END") + 1)
        self.temp_vars = range(c.value("TEMP_VARS_START"), c.value("TEMP_VARS_END") + 1)
        heal = self.chk.world.heal
        self.respawn_maps = {h["respawn_map"] for h in heal if h.get("respawn_map")}
        self.heal_by_map = {}
        for h in heal:
            self.heal_by_map.setdefault(h["map"], h)
            if h.get("respawn_map"):
                self.heal_by_map.setdefault(h["respawn_map"], h)

    def flag_of(self, obj):
        md = self.chk.world.maps.get(obj[0])
        ob = next((o for o in md.objects if o["index"] == obj[1]), None) if md else None
        flag = ob.get("flag") if ob else None
        return self.chk.sim.fkey(flag) if flag not in (None, "0", 0, "") else None

    def r1_line(self, pc):
        """a command written in round 1: in a Draconid file / new map's Poryscript, or on an @ Draconid Emerald line"""
        f = self.chk.scripts.cmds[pc][2]
        return pc in self.chk.scripts.tagged or f.startswith("data/scripts/draconid/") or f.endswith("scripts.inc") and \
            os.path.exists(os.path.join(ROOT, f[:-4] + ".pory"))

    def add(self, sev, kind, where_, what):
        f = Finding(sev, kind, where_, what)
        if f not in self.findings:
            self.findings.append(f)

    def is_temp(self, key):
        kind, k = key
        return isinstance(k, int) and ((kind == "F" and k in self.temp_flags) or (kind == "V" and k in self.temp_vars))

    def is_story(self, key):
        """a permanent flag/var/item (not a temp, not VAR_RESULT / VAR_0x80xx)"""
        kind, k = key
        if self.is_temp(key):
            return False
        if kind == "V":
            return not SCRATCH_VARS.match(self.chk.name_of(k, "VAR"))
        return True

    # --- story table hooks ---------------------------------------------------------------
    def scene(self, leg, e, st, target, pos, scene_map, view):
        self.scene_states.setdefault(e["label"], (leg, e, st, target, pos, scene_map))

    def scene_after(self, leg, e, st):
        self.scene_after_states.setdefault(e["label"], st)

    def leg_end(self, leg, res, st, pos, visited):
        self.leg_ends.append((leg, res, st, pos, visited))

    def state_with(self, st, writes, keep_temps=True):
        out = st.copy() if st is not None else cp.State()
        for key, v in writes.items():
            if not keep_temps and self.is_temp(key):
                continue
            kind, k = key
            {"F": out.flags, "V": out.vars, "I": out.items}[kind][k] = v
        return out

    def base_of(self, st, known):
        def base(key):
            if key in known:
                return known[key]
            if st is None:
                return UNK
            kind, k = key
            if kind == "F":
                return st.flag(k)
            if kind == "V":
                return st.var(k)
            return st.items.get(k, 0)
        return base

    # --- per entry ------------------------------------------------------------------------
    def run(self, only):
        _, self.results = cp.run_story(self.chk, self.table, hooks=self)
        self.rides = self.table_rides()
        cache = {}
        for en in entries(self.chk):
            start = self.chk.scripts.labels.get(en.label)
            if start is None:
                continue
            known = {}
            if en.kind in ("frame", "warpin", "coord"):
                var, value = (en.info["var"], en.info["var_value"]) if en.kind == "coord" else en.info
                v = self.chk.c.value(value)
                if v is not None and self.chk.sim.vkey(var) != 0:
                    known[("V", self.chk.sim.vkey(var))] = v
            scene = self.scene_states.get(en.label)
            st = scene[2] if scene and scene[5] == en.map else None
            key = (en.label, en.kind, tuple(sorted(known.items())), st is not None and en.label)
            if key not in cache:
                self.ex.cur_map = en.map
                self.ex.whiteouts = []
                ends = self.ex.explore(en.label, self.base_of(st, known))
                cache[key] = (ends, list(self.ex.whiteouts))
            ends, whiteouts = cache[key]
            if not (any(e.path.touched for e in ends) or start in self.r1):
                continue
            if "lock" in only:
                self.check_lock(en, ends)
            if "frame" in only and en.kind == "frame":
                self.check_frame(en, ends)
            if "coord" in only and en.kind == "coord":
                self.check_coord(en, ends)
            if "battle" in only:
                self.check_battles(en, ends, whiteouts, st, scene if st is not None else None)
            if "reentry" in only:
                if st is not None:
                    self.check_reentry(en, ends, scene)
                self.check_temp_warps(en, ends)
        self.report_locks()
        if "wait" in only:
            for f in self.ex.wait_findings.values():
                self.add(*f)
        if "trap" in only:
            self.check_traps()

    # --- lock ---------------------------------------------------------------------------------
    def check_lock(self, en, ends):
        s = self.chk.scripts
        for e in ends:
            if e.how in ("end", "return") and e.path.lock is not None and self.r1_line(e.path.lock):
                self.lock_hits.setdefault((e.path.lock, e.pc), []).append("%s %s" % (en.kind, en.label))

    def report_locks(self):
        s = self.chk.scripts
        for (lock, end), starts in sorted(self.lock_hits.items()):
            self.add(CHECK, "lock", where(s, lock),
                     "%s is still in force when the script ends at %s (from %s): the objects on the map stay frozen "
                     "until it reloads or a battle (the player can move)" % (
                         s.cmds[lock][0], where(s, end), ", ".join(sorted(set(starts)))))

    # --- OnFrame ---------------------------------------------------------------------------
    def check_frame(self, en, ends):
        s = self.chk.scripts
        var, value = en.info
        key = ("V", self.chk.sim.vkey(var))
        want = self.chk.c.value(value)
        for e in ends:
            if e.how not in ("end", "return"):
                continue
            if e.path.w.get(key, want) != want:
                continue
            if e.path.choices:
                if self.verbose:
                    self.add(NOTE, "frame", where(s, e.pc),
                             "OnFrame %s == %s starts %s again right away after this path (a forced retry: %s)" % (
                                 var, value, en.label, self.why(e)))
            else:
                self.add(LOCK, "frame", where(s, e.pc),
                         "OnFrame %s == %s starts %s again right away: this path ends without changing %s and "
                         "without a choice on the way" % (var, value, en.label, var))

    # --- coord triggers -----------------------------------------------------------------------
    def check_coord(self, en, ends):
        s = self.chk.scripts
        ev = en.info
        if self.chk.sim.vkey(ev["var"]) == 0:
            return
        key = ("V", self.chk.sim.vkey(ev["var"]))
        want = self.chk.c.value(ev["var_value"])
        for e in ends:
            if e.how not in ("end", "return"):
                continue
            if e.path.w.get(key, want) != want or e.path.xy != (0, 0):
                continue
            free = self.step_off(en.map, ev)
            if free:
                if self.verbose:
                    self.add(NOTE, "coord", where(s, e.pc),
                             "%s (%d, %d): this path leaves %s and the player where they were; stepping back on starts "
                             "it again, stepping off to %s doesn't" % (en.label, ev["x"], ev["y"], ev["var"],
                                                                      ", ".join("(%d, %d)" % t for t in free[:3])))
            else:
                self.add(LOCK, "coord", where(s, e.pc),
                         "%s (%d, %d): this path leaves the player on the trigger and every tile off it is the same "
                         "trigger or a wall" % (en.label, ev["x"], ev["y"]))

    def step_off(self, map_id, ev):
        md = self.chk.world.maps[map_id]
        lay, pair = self.chk.world.layout(md.layout_id)
        same = {(c["x"], c["y"]) for c in md.coords if c.get("var") == ev["var"] and c.get("var_value") == ev["var_value"]}
        out = []
        for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            x, y = ev["x"] + dx, ev["y"] + dy
            if not (0 <= x < lay.width and 0 <= y < lay.height) or (x, y) in same:
                continue
            if (lay.blocks[y * lay.width + x] >> cp.pokemap.MAPGRID_COLLISION_SHIFT) & 3:
                continue
            out.append((x, y))
        return out

    # --- battles ----------------------------------------------------------------------------------
    def check_battles(self, en, ends, whiteouts, st, scene):
        s = self.chk.scripts
        for e in ends:
            for kind, pc, info in e.path.events:
                if kind != "battle" or pc not in self.r1:
                    continue
                self.battles.setdefault(pc, (en.label, info))
                op, who, goes_on, cont = info
                if goes_on == "NO_WHITEOUT" and e.how in ("end", "return") and e.path.nowo is not None:
                    self.add(CHECK, "battle", where(s, pc),
                             "%s: FLAG_DRACONID_NO_WHITEOUT is still set when this path ends at %s - a later lost "
                             "trainer battle wouldn't white out" % (", ".join(who), where(s, e.pc)))
        for w in whiteouts:
            if w.pc in self.r1:
                self.check_whiteout(en, w, st, scene)

    def whiteout_state(self, st, writes):
        """the state after a whiteout: the path's writes, temp state reset, EventScript_WhiteOut run"""
        out = self.state_with(st, writes, keep_temps=False)
        return self.chk.sim.run("EventScript_WhiteOut", out, cp.Ctx(None)).flattened()

    def check_whiteout(self, en, w, st, scene):
        s = self.chk.scripts
        op, who = w.info
        who = ", ".join(who)
        puzzles = self.table.get("puzzles", {})
        gauntlet = self.table.get("no_heal_ok", {})
        # 1. without the story state: does the path disarm its own trigger / hide its object before the battle?
        if st is None:
            bad = self.disarms(en, w.path.w)
            if bad:
                self.add(CHECK, "battle", where(s, w.pc),
                         "%s: a whiteout here leaves %s %s unable to start again: %s was written before the battle" % (
                             who, en.kind, en.label, bad))
            return
        # 2. with the story state
        after = self.whiteout_state(st, w.path.w)
        again, view = self.startable(en, after)
        if not again:
            self.add(LOCK, "battle", where(s, w.pc),
                     "leg %s %s: a whiteout here leaves %s %s unable to start again (writes before the battle: %s)" % (
                         scene[0].get("id"), who, en.kind, en.label, self.fmt_writes(w.path.w)))
        if en.map in gauntlet:
            self.loss_info[w.pc] = "leg %s: back through %s (%s)" % (scene[0].get("id"), self.chk.world.pretty(en.map),
                                                                     gauntlet[en.map])
            if self.verbose:
                self.add(NOTE, "battle", where(s, w.pc), "leg %s %s: a whiteout sends the player back through %s (%s)" % (
                    scene[0].get("id"), who, self.chk.world.pretty(en.map), gauntlet[en.map]))
            return
        # 3. the walk back from the last heal location the story passed before this scene
        leg, e, _, target, pos, scene_map = scene
        if target is None:
            return
        if target[1] in puzzles:
            target = ("map", target[1], None, None)
        ckey = (en.label, frozenset((k, v) for k, v in w.path.w.items() if self.is_story(k)))
        if ckey in self.way_back:
            self.loss_info.setdefault(w.pc, self.way_back[ckey])
            return
        self.way_back[ckey] = "leg %s: walked back as for the scene's other battle" % leg.get("id")
        # the respawn is the last Pokémon Center the player entered: any one the story passed before (or the village
        # house). Its load scripts ran then (setrespawn, and Mr. Briney's spot: Common_EventScript_UpdateBrineyLocation),
        # and the whiteout moves him back there (EventScript_WhiteOut)
        base = self.state_with(st, w.path.w, keep_temps=False)
        groups = {}
        for h, delta in self.heal_candidates(leg.get("id")):
            groups.setdefault(frozenset(delta.items()), []).append(h)
        failed, okd = [], []
        for delta, hs in groups.items():
            healed = base.copy()
            for (kind, k), v in delta:
                {"F": healed.flags, "V": healed.vars}[kind][k] = v
            after = self.chk.sim.run("EventScript_WhiteOut", healed, cp.Ctx(None)).flattened()
            srch = RideSearch(self, after, set(), self.rides_until(leg.get("id")))
            goal, goal_tiles = cp.goal_for(srch, target)
            for h in hs:
                start = srch.node_at(h["map"], h["x"], h["y"])
                if start is None:
                    continue
                end, prev = srch.search([start], goal, goal_tiles)
                (okd if end is not None else failed).append(self.chk.world.pretty(h["map"]))
        self.loss_info[w.pc] = ("leg %s: the scene starts again; the way back is open from %s" % (
            leg.get("id"), ", ".join(okd)) if not failed else "leg %s: NO WAY BACK from %s" % (leg.get("id"), ", ".join(failed)))
        self.way_back[ckey] = self.loss_info[w.pc]
        if failed:
            self.add(LOCK, "battle", where(s, w.pc),
                     "leg %s %s: after a whiteout at %s (the respawn if its Pokémon Center was the last one used) the "
                     "player can't get back to %s" % (leg.get("id"), who, ", ".join(failed),
                                                      cp.fmt_target(self.chk, target)))
        elif self.verbose and okd:
            self.add(NOTE, "battle", where(s, w.pc), "leg %s %s: a whiteout; the way back is open from %s" % (
                leg.get("id"), who, ", ".join(okd)))

    ACTS = [1, 2, 3, 4, 5, 6, 7, "post"]

    def heal_candidates(self, leg_id):
        """(heal location, what its Pokémon Center's load scripts wrote when the story passed it) for the heal
        locations the story's walks passed in this act and the one before (side trips left out) - the player may have
        used any of them last; the village house too in Acts 1-2 (before any Pokémon Center is likely)"""
        if leg_id in self._cand_cache:
            return self._cand_cache[leg_id]
        act = next((lg.get("act") for lg in self.table["legs"] if lg.get("id") == leg_id), None)
        i = self.ACTS.index(act) if act in self.ACTS else 0
        window = set(self.ACTS[max(0, i - 1):i + 1])
        out, seen = [], set()
        home = next((h for h in self.chk.world.heal if h["id"] == "HEAL_LOCATION_DRACONID_VILLAGE"), None)
        if home and act in (1, 2):
            out.append((home, {}))
            seen.update((home["id"], home.get("respawn_map")))
        for leg, res, st, pos, visited in self.leg_ends:
            if leg.get("id") == leg_id:
                break
            if leg.get("side") or leg.get("act") not in window:
                continue
            for m in res.path_maps:
                h = self.heal_by_map.get(m)
                if not h or h["id"] in seen or h.get("respawn_map") in seen:
                    continue
                seen.update((h["id"], h.get("respawn_map")))
                delta = {}
                pc_map = self.chk.world.maps.get(h.get("respawn_map") or "")
                if pc_map is not None:
                    after = cp.MapView(self.chk, pc_map, st).state
                    for kind, layer, old in (("F", after.flags, st.flags), ("V", after.vars, st.vars)):
                        for k, v in layer.items():
                            if self.is_story((kind, k)) and v != (old.get(k, False if kind == "F" else 0)):
                                delta[(kind, k)] = v
                out.append((h, delta))
        self._cand_cache[leg_id] = out
        return out

    def disarms(self, en, writes):
        if en.kind in ("coord", "frame"):
            var = en.info["var"] if en.kind == "coord" else en.info[0]
            value = en.info["var_value"] if en.kind == "coord" else en.info[1]
            key = ("V", self.chk.sim.vkey(var))
            if key in writes and not self.is_temp(key) and writes[key] != self.chk.c.value(value):
                return "%s=%s" % (var, writes[key])
        if en.kind == "object":
            flag = en.info.get("flag")
            if flag not in (None, "0", 0, "") and writes.get(("F", self.chk.sim.fkey(flag))) is True \
                    and not self.is_temp(("F", self.chk.sim.fkey(flag))):
                return "%s (its hide flag)" % flag
        return None

    def startable(self, en, state):
        """can the entry's scene start with this state (the map entered afresh)?"""
        md = self.chk.world.maps[en.map]
        view = cp.MapView(self.chk, md, state)
        if en.kind == "object":
            return any(o["index"] == en.info["index"] for o in view.objects), view
        if en.kind == "coord":
            ev = en.info
            return any(t["script"] == en.label for t in view.triggers.get((ev["x"], ev["y"]), ())), view
        if en.kind == "frame":
            return view.frame_scene == en.label, view
        return True, view

    def fmt_writes(self, writes, limit=5):
        out = []
        for key, v in writes.items():
            if not self.is_story(key) and not self.is_temp(key):
                continue
            kind, k = key
            if kind == "F":
                if isinstance(k, int) and self.chk.sim.trainer_flags and k >= self.chk.sim.trainer_flags:
                    continue  # the battle's own trainer flags
                name = self.chk.name_of(k, "FLAG")
            elif kind == "V":
                name = self.chk.name_of(k, "VAR")
            else:
                name = k
            out.append("%s=%s" % (name, v))
        return (", ".join(out[:limit]) + (" …" if len(out) > limit else "")) if out else "none"

    def table_rides(self):
        """(leg id, from tiles, the object that must be there or None, to position) for every table scene with
        "then" (Mr. Briney's boats, the cable car, the ferries). A scene without a tile or an object of its own (the
        boat leaving once the player is aboard) rides from where the scene before it left the player."""
        out = []
        for leg in self.table["legs"]:
            prev_then = None
            for e in leg.get("scenes", []):
                e = cp.norm_entry(e)
                if not e.get("then"):
                    prev_then = None
                    continue
                t = self.chk.scene_target(e)
                obj = None
                if t and t[0] == "tile":
                    tiles = {(t[1], x, y) for x, y in t[2]}
                elif t and t[0] == "adjacent":
                    x, y = t[2]
                    tiles = {(t[1], x + dx, y + dy) for dx, dy in cp.DIRS.values()}
                    obj = (t[1], t[3]["index"]) if isinstance(t[3], dict) else None
                elif prev_then:
                    tiles = {prev_then}
                else:
                    continue
                dest = cp.parse_pos(e["then"])
                out.append((leg.get("id"), tiles, obj, dest))
                prev_then = dest
                before = self.scene_states.get(e["label"])
                after = self.scene_after_states.get(e["label"])
                if before and after:
                    for k, v in after.flags.items():
                        if v is False and before[2].flag(k) is True:
                            self.travelling.add(k)
        return out

    def rides_until(self, leg_id):
        ids = [lg.get("id") for lg in self.table["legs"]]
        upto = ids.index(leg_id) if leg_id in ids else len(ids)
        rides = {}
        for lid, tiles, obj, dest in self.rides:
            if lid in ids and ids.index(lid) <= upto:
                for t in tiles:
                    rides.setdefault(t, []).append((dest, obj))
        return rides

    # --- re-entry / save and reload ------------------------------------------------------------------
    def check_reentry(self, en, ends, scene):
        s = self.chk.scripts
        leg, e, st, target, pos, scene_map = scene
        done = [x for x in ends if x.how in ("end", "return", "warp", "battle")]
        sets = [(x, {k for k, v in x.path.w.items() if self.is_story(k)}) for x in done]
        for end, keys in sets:
            if end.how not in ("end", "return"):
                continue
            longer = [x for x, ks in sets if keys < ks]
            if not longer:
                continue  # nothing goes further: this is how the scene ends
            after = self.state_with(st, end.path.w, keep_temps=False)
            again, view = self.startable(en, after)
            retry = self.retry_by_talk(en, view, end)
            if not again and not retry:
                self.add(LOCK, "reentry", where(s, end.pc),
                         "leg %s %s: this path gives control back before the scene is done (%s), and neither "
                         "re-entering %s nor talking to anyone there starts it again (writes: %s)" % (
                             leg.get("id"), en.label, self.why(end), self.chk.world.pretty(en.map),
                             self.fmt_writes(end.path.w)))
            elif self.verbose:
                how = []
                if retry:
                    how.append("talking to %s tries again" % retry)
                if again:
                    how.append("re-entering the map starts it again")
                self.add(NOTE, "reentry", where(s, end.pc),
                         "leg %s %s: gives control back before the scene is done (%s); %s" % (
                             leg.get("id"), en.label, self.why(end), " and ".join(how)))

    def why(self, end):
        s = self.chk.scripts
        return ("a choice at %s" % ", ".join(sorted({s.label_at[c] for c in end.path.choices}))
                if end.path.choices else "no choice")

    def retry_by_talk(self, en, view, end):
        """an object shown on the map whose script leads to a battle this path went through, or to the scene"""
        s = self.chk.scripts
        want = {pc for kind, pc, info in end.path.events if kind == "battle"} | {s.labels[en.label]} | set(end.path.choices)
        for o in view.objects:
            lab = o.get("script")
            if lab and lab in s.labels and want & self.reachable(lab):
                return o.get("local_id") or "object %d" % o["index"]
        return None

    def reachable(self, label, cache={}):
        if label in cache:
            return cache[label]
        s = self.chk.scripts
        seen = set()
        todo = [s.labels[label]]
        while todo:
            pc = todo.pop()
            while pc < len(s.cmds) and pc not in seen:
                seen.add(pc)
                op, args, _, _ = s.cmds[pc]
                for t in args:
                    if t in s.labels and (op in ("goto", "call", "case") or "_if" in op):
                        todo.append(s.labels[t])
                if op in ("end", "return", "goto") or op in cp.WARP_OPS:
                    break
                pc += 1
        cache[label] = seen
        return seen

    def check_temp_warps(self, en, ends):
        """a temp var/flag set to the value the destination's OnFrame waits for, then a warp: the warp resets it"""
        s = self.chk.scripts
        for end in ends:
            if end.how != "warp" or end.pc not in self.r1 or not end.info or end.info[1] not in self.chk.world.maps:
                continue
            md = self.chk.world.maps[end.info[1]]
            _, frame = cp.map_scripts(s, md)
            for var, value, label in frame:
                key = ("V", self.chk.sim.vkey(var))
                want = self.chk.c.value(value)
                if self.is_temp(key) and key in end.path.w and end.path.w[key] == want and want != 0:
                    self.add(CHECK, "reentry", where(s, end.pc),
                             "%s sets %s = %s and warps to %s, whose OnFrame %s waits for it: the warp resets temp "
                             "vars, so only %s's own load scripts can start it" % (
                                 en.label, var, value, md.name, label, md.name))

    # --- trapped spots -------------------------------------------------------------------------------
    def check_traps(self):
        """every place a scene of a leg can warp the player to (every branch: a YES/NO, a ferry's menu), other than
        where the leg's walk starts (the walk itself is check_progression.py's): a heal location or the leg's walk
        target must be reachable from there with what the player has"""
        ok_maps = self.table.get("no_heal_ok", {})
        for leg, res, st, pos, visited in self.leg_ends:
            done = {tuple(res.start)} if res.start else set()
            for w in res.warps:
                spot = self.chk.warp_position(w)
                if not spot or spot[0] not in self.chk.world.maps or spot in done:
                    continue
                done.add(spot)
                if spot[0] in ok_maps:
                    if self.verbose:
                        self.add(NOTE, "trap", "progression.json leg %s" % leg.get("id"),
                                 "a warp to %s: no heal location from there - by design: %s" % (
                                     cp.fmt_pos(self.chk, spot), ok_maps[spot[0]]))
                    continue
                srch = RideSearch(self, st, visited, self.rides_until(leg.get("id")))
                start = srch.node_at(*spot)
                if start is None:
                    continue
                target_goal = cp.goal_for(srch, res.target)[0] if res.target else (lambda n: False)
                end, prev = srch.search([start], lambda n: self.heal_goal(n) or target_goal(n), set())
                if end is None:
                    self.add(LOCK, "trap", "progression.json leg %s" % leg.get("id"),
                             "a scene can warp the player to %s (%s): from there neither a heal location nor the "
                             "leg's next scene can be reached with what the player has" % (
                                 cp.fmt_pos(self.chk, spot), w[0]))
                elif self.verbose:
                    self.add(NOTE, "trap", "progression.json leg %s" % leg.get("id"),
                             "a warp to %s: %s reached in %d steps" % (
                                 cp.fmt_pos(self.chk, spot), "a heal location" if self.heal_goal(end) else "the next scene",
                                 len(cp.Search.path(prev, end))))

    def heal_goal(self, n):
        if n[0] in self.respawn_maps:
            return True
        h = self.heal_by_map.get(n[0])
        return h is not None and h["map"] == n[0] and abs(n[1] - h["x"]) + abs(n[2] - h["y"]) <= 1

    # --- output ---------------------------------------------------------------------------------------
    def report(self, markdown=False):
        order = {LOCK: 0, CHECK: 1, NOTE: 2}
        fs = sorted(self.findings, key=lambda f: (order[f.severity], f.kind, f.where))
        shown = [f for f in fs if f.severity != NOTE or self.verbose]
        if markdown:
            print("| # | Severity | Check | Where | Finding |")
            print("|---|---|---|---|---|")
            for i, f in enumerate(shown, 1):
                print("| %d | %s | %s | `%s` | %s |" % (i, f.severity, f.kind, f.where, f.what.replace("|", "\\|")))
            return 0
        for f in shown:
            print("[%-5s] %-7s %s\n          %s" % (f.severity, f.kind, f.where, f.what))
        counts = {k: sum(1 for f in fs if f.severity == k) for k in (LOCK, CHECK, NOTE)}
        print("hard-lock check: %d LOCK, %d CHECK, %d NOTE; %d round 1 battles (--battles lists them)" % (
            counts[LOCK], counts[CHECK], counts[NOTE], len(self.battles)))
        return counts[LOCK]

    def report_battles(self, markdown=False):
        s = self.chk.scripts
        if markdown:
            print("| Where | Opponents | After a loss |")
            print("|---|---|---|")
        for pc in sorted(self.battles, key=lambda pc: where(s, pc)):
            label, (op, who, goes_on, cont) = self.battles[pc]
            if goes_on:
                loss = "goes on (%s)" % ("FLAG_DRACONID_NO_WHITEOUT" if goes_on == "NO_WHITEOUT" else
                                         "early-rival / first battle rule")
            else:
                loss = "whites out; " + self.loss_info.get(pc, "the scene can start again (not in the story table: "
                                                               "no walk back checked)")
            if markdown:
                print("| `%s` | %s | %s |" % (where(s, pc), ", ".join(w.replace("TRAINER_", "") for w in who), loss))
            else:
                print("%-72s %-50s %s" % (where(s, pc), ", ".join(who), loss))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--only", default="lock,wait,frame,coord,battle,trap,reentry")
    ap.add_argument("--markdown", action="store_true")
    ap.add_argument("--battles", action="store_true", help="list every round 1 battle and what a loss does")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()
    h = Hardlock(args.verbose)
    h.run(set(args.only.split(",")))
    if args.battles:
        h.report_battles(args.markdown)
        return 0
    if args.markdown:
        return h.report(markdown=True)
    return 1 if h.report() else 0


if __name__ == "__main__":
    sys.exit(main())
