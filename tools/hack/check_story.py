#!/usr/bin/env python3
"""
check_story.py - static reachability checks for the Draconid Emerald flags and story vars.

  python3 tools/hack/check_story.py

Scans the compiled event scripts (data/**/*.inc, data/**/*.s), map.json files and src/**/*.c:
  - every Draconid flag (flags.h lines tagged "Draconid Emerald") is written somewhere (error) and read
    somewhere (a flag nothing reads is only a record, e.g. "received X": warning); an item ball's flag
    (object script Common_EventScript_FindItem) is set by picking the ball up, a hidden item's flag (map.json
    bg_events "hidden_item") by finding it, and the field reads it (the item is gone)
  - every FLAG_HIDE_* flag hides an object and toggles: set by the new game and cleared later (the object
    appears), or not set by the new game and set later (the object leaves)
  - every story var state constant (DRACONID_STATE_*, ASTER_STATE_*, BRENDAN_STATE_*, MAY_STATE_*,
    WALLY_STATE_*) other than 0 is written to its var (error); states no script compares against are
    listed as notes (end states such as "..._DONE" only record progress)
Prints one line per finding; exit 1 on errors. Config / debug and reserved flags are in ALLOWED with the
reason.
"""

import glob
import json
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

STATE_VARS = {
    "VAR_DRACONID_STATE": "DRACONID_STATE_",
    "VAR_ASTER_STATE": "ASTER_STATE_",
    "VAR_BRENDAN_STATE": "BRENDAN_STATE_",
    "VAR_MAY_STATE": "MAY_STATE_",
    "VAR_WALLY_STATE": "WALLY_STATE_",
    "VAR_NERINE_STATE": "NERINE_STATE_",
    "VAR_MAGMA_STATE": "MAGMA_STATE_",
    "VAR_DRACONID_REPUTATION": "REPUTATION_",
    "VAR_DRACONID_FINALE_STATE": "FINALE_STATE_",
    "VAR_DRACONID_VILLAGE_STATE": "VILLAGE_STATE_",
}
PLAIN_VARS = ["VAR_ASTER_EGG", "VAR_SECOND_STARTER", "VAR_PLAYER_OUTFIT"]

# flag -> why the usual rule doesn't apply
ALLOWED = {
    "FLAG_DEBUG_NO_ENCOUNTER": "config flag (WE_FLAG_NO_ENCOUNTER), toggled by the debug menu and tests",
    "FLAG_DEBUG_NO_TRAINER_SEE": "config flag (OW_FLAG_NO_TRAINER_SEE), toggled by the debug menu and tests",
    "FLAG_DEBUG_NO_COLLISION": "config flag (OW_FLAG_NO_COLLISION), toggled by the debug menu and tests",
    "FLAG_HIDE_DRACONID_VILLAGE_ASTER": "reserved for later village visits (docs/hack_changes.md)",
    "FLAG_DRACONID_NO_WHITEOUT": "config flag (B_FLAG_NO_WHITEOUT), read by the battle engine",
    "FLAG_DRACONID_NO_RUNNING": "config flag (WE_FLAG_NO_RUNNING), read by the battle engine",
    "FLAG_DRACONID_NO_CATCHING": "config flag (WE_FLAG_NO_CATCHING), read by the battle engine",
    "FLAG_EXP_SHARE_ON": "config flag (I_EXP_SHARE_FLAG), toggled by the Exp. Share, read by the battle engine",
}

# Round 1 (v2 story) is being built act by act: states of acts that aren't scripted yet. Each is
# reported as a NOTE until its act lands; take it out of this set then.
PENDING = {
}

# flags whose scene belongs to an act that isn't scripted yet (NOTE instead of ERROR until it lands)
PENDING_FLAGS = {
}

READ_CMDS = r"(?:goto_if_set|goto_if_unset|call_if_set|call_if_unset|checkflag)"
VAR_READ_CMDS = r"(?:goto_if_\w+|call_if_\w+|compare|map_script_2|switch)"


def corpus():
    scripts = ""
    for pat in ("data/**/*.inc", "data/**/*.s"):
        for p in glob.glob(os.path.join(ROOT, pat), recursive=True):
            scripts += open(p, errors="replace").read() + "\n"
    c = ""
    for p in glob.glob(os.path.join(ROOT, "src/**/*.c"), recursive=True):
        c += open(p, errors="replace").read() + "\n"
    maps = [json.load(open(p)) for p in glob.glob(os.path.join(ROOT, "data/maps/*/map.json"))]
    return scripts, c, maps


def draconid_flags():
    flags = []
    for line in open(os.path.join(ROOT, "include/constants/flags.h")):
        m = re.match(r"#define (FLAG_\w+)\s+\S+.*Draconid Emerald", line)
        if m:
            flags.append(m.group(1))
    return flags


def state_constants(prefix):
    consts = {}
    for line in open(os.path.join(ROOT, "include/constants/draconid.h")):
        m = re.match(r"#define (%s\w+)\s+(\d+)" % prefix, line)
        if m:
            consts[m.group(1)] = int(m.group(2))
    return consts


def main():
    scripts, c, maps = corpus()
    new_game = open(os.path.join(ROOT, "data/scripts/draconid/new_game.inc")).read()
    new_game += open(os.path.join(ROOT, "data/scripts/new_game.inc")).read()
    objects = {}  # flag -> objects hidden by it
    item_balls = set()  # flags of item balls: picking one up sets its flag (Common_EventScript_FindItem)
    hidden_items = set()  # flags of hidden items: finding one sets its flag, the field reads it
    coord_reads = set()
    for mj in maps:
        for o in mj.get("object_events") or []:
            objects.setdefault(o.get("flag"), []).append((mj["name"], o.get("local_id")))
            if o.get("script") == "Common_EventScript_FindItem":
                item_balls.add(o.get("flag"))
        for ev in mj.get("coord_events") or []:
            if ev.get("var"):
                coord_reads.add((ev["var"], str(ev.get("var_value"))))
        for ev in mj.get("bg_events") or []:
            if ev.get("type") == "hidden_item":
                hidden_items.add(ev.get("flag"))
    errors = warnings = 0

    def report(kind, msg):
        nonlocal errors, warnings
        print("%-7s %s" % (kind, msg))
        if kind == "ERROR":
            errors += 1
        elif kind == "WARNING":
            warnings += 1

    removed_localids = set(re.findall(r"removeobject (\w+)", scripts))
    for flag in draconid_flags():
        w = re.search(r"\b(?:setflag|clearflag) %s\b" % flag, scripts) or re.search(r"Flag(?:Set|Clear)\(%s\)" % flag, c)
        hidden_objs = objects.get(flag, [])
        removed = any(lid in removed_localids for _, lid in hidden_objs) or flag in item_balls or flag in hidden_items
        r = (re.search(r"\b%s %s\b" % (READ_CMDS, flag), scripts) or re.search(r"FlagGet\(%s\)" % flag, c)
             or hidden_objs or re.search(r"\b%s\b" % flag, c) or flag in hidden_items)
        if flag in ALLOWED:
            continue
        if flag in PENDING_FLAGS and not (w or removed):
            report("NOTE", "%s: pending – %s" % (flag, PENDING_FLAGS[flag]))
            continue
        if not (w or removed):
            report("ERROR", "%s is never set or cleared" % flag)
        if not r:
            report("WARNING", "%s is set but nothing reads it (a record only)" % flag)
        if flag.startswith("FLAG_HIDE_"):
            if not hidden_objs:
                report("ERROR", "%s hides no object" % flag)
            if re.search(r"\bsetflag %s\b" % flag, new_game):
                if not re.search(r"\bclearflag %s\b" % flag, scripts):
                    report("ERROR", "%s is set by the new game and never cleared: its object never appears" % flag)
            elif not (re.search(r"\bsetflag %s\b" % flag, scripts) or removed):
                report("ERROR", "%s is not set by the new game and never set later: its object never leaves" % flag)

    for var, prefix in STATE_VARS.items():
        consts = state_constants(prefix)
        if not consts:
            report("ERROR", "%s: no %s* constants" % (var, prefix))
        for name, value in consts.items():
            written = re.search(r"\bsetvar %s, %s\b" % (var, name), scripts)
            read = (re.search(r"\b%s %s, %s\b" % (VAR_READ_CMDS, var, name), scripts)
                    or (var, name) in coord_reads or (var, str(value)) in coord_reads)
            if value and not written:
                if name in PENDING:
                    report("NOTE", "%s = %s: pending (its act isn't scripted yet)" % (var, name))
                    continue
                report("ERROR", "%s = %s is never written" % (var, name))
            if not read:
                report("NOTE", "%s = %s: no script compares against it (records progress only)" % (var, name))
    for var in PLAIN_VARS:
        if not re.search(r"\b(?:setvar|copyvar) %s\b" % var, scripts) and not re.search(r"VarSet\(%s" % var, c):
            report("ERROR", "%s is never written" % var)
        if not (re.search(r"\b%s %s\b" % (VAR_READ_CMDS, var), scripts) or re.search(r"VarGet\(%s\)" % var, c)):
            report("ERROR", "%s is never read" % var)
    print("%d error(s), %d warning(s)" % (errors, warnings))
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
