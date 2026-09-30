#!/usr/bin/env python3
"""
check_evos.py - Draconid Emerald has no trade evolutions (round 1, D-216/D-217).

  python3 tools/hack/check_evos.py            # checks + the table of former trade evolutions
  python3 tools/hack/check_evos.py --markdown # the table as Markdown (docs/hack_items.md)

Scans src/data/pokemon/species_info/*.h:
  - no species keeps an EVO_TRADE evolution or an IF_TRADE_PARTNER_SPECIES condition (error)
  - no level evolution is shadowed: GetEvolutionTargetSpecies (src/pokemon.c) takes the FIRST entry whose
    conditions hold, so an unconditional EVO_LEVEL listed before a conditional EVO_LEVEL of the same or a
    higher level would make that branch unreachable (error)
  - the Deino, Dreepy and Jangmo-o lines evolve at 25 and 50 (D-107) (error otherwise)
  - every former trade evolution (a level entry with a DRACONID_TRADE_EVO_LEVEL_* level, or a held-item
    level entry in a block tagged D-216/D-217) is printed with its level, held item and the base stat totals
Exit 1 on errors.
"""

import argparse
import glob
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
MARK = re.compile(r"Draconid Emerald \(D-21[67]\)")
ENTRY = re.compile(r"\{\s*(EVO_\w+)\s*,\s*([^,{}]+?)\s*,\s*SPECIES_(\w+)\s*(?:,\s*CONDITIONS\((.*?)\)\s*)?\}")
STATS = ("baseHP", "baseAttack", "baseDefense", "baseSpeed", "baseSpAttack", "baseSpDefense")


def constants():
    text = open(os.path.join(ROOT, "include/constants/draconid.h")).read()
    return {k: int(v) for k, v in re.findall(r"#define (DRACONID_\w+)\s+(\d+)", text)}


def stat_value(expr, macros):
    """Base stat expressions: a number, a P_UPDATED_STATS ternary (the newest value) or a macro of either."""
    expr = expr.strip()
    expr = macros.get(expr, expr).strip("() ")
    m = re.match(r"^\d+$", expr)
    if m:
        return int(expr)
    m = re.search(r"\?\s*(\d+)\s*:", expr)
    return int(m.group(1)) if m else None


def load():
    """species -> {'evos': [(method, param, target, conditions)], 'marked': bool, 'bst': int|None}"""
    species = {}
    for path in sorted(glob.glob(os.path.join(ROOT, "src/data/pokemon/species_info/*.h"))):
        text = open(path).read()
        macros = {}
        for k, v in re.findall(r"#define (\w+)\s+(.+?)\s*$", text, re.M):
            macros.setdefault(k, v)  # inside #if P_UPDATED_STATS blocks the newest value comes first
        for m in re.finditer(r"\[SPECIES_(\w+)\]\s*=\s*\{(.*?)\n    \},", text, re.S):
            name, body = m.group(1), m.group(2) + "\n"
            info = {"evos": [], "marked": bool(MARK.search(body)), "bst": None, "file": os.path.basename(path)}
            vals = []
            for s in STATS:
                sm = re.search(r"\.%s\s*=\s*([^,\n]+)," % s, body)
                vals.append(stat_value(sm.group(1), macros) if sm else None)
            if None not in vals:
                info["bst"] = sum(vals)
            ev = re.search(r"\.evolutions\s*=\s*EVOLUTION\((.*?)\),\s*\n", body, re.S)
            if ev:
                code = re.sub(r"//[^\n]*", "", ev.group(1))
                for method, param, target, cond in ENTRY.findall(code):
                    info["evos"].append((method, param.strip(), target, cond or ""))
            species.setdefault(name, info)
    return species


def nice(name):
    """SPECIES_/ITEM_ suffix -> "Graveler Alola", "Deep Sea Tooth"."""
    return name.replace("_", " ").title()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--markdown", action="store_true", help="print the table as Markdown")
    args = ap.parse_args()
    consts = constants()
    species = load()
    errors = 0
    rows = []
    for name, info in species.items():
        levels = []
        for method, param, target, cond in info["evos"]:
            if method == "EVO_TRADE" or "IF_TRADE_PARTNER_SPECIES" in cond:
                print("ERROR %s -> %s: still a trade evolution (%s)" % (name, target, info["file"]))
                errors += 1
            if method == "EVO_LEVEL":
                level = consts.get(param, int(param) if param.isdigit() else None)
                for plevel, ptarget, pcond in levels:
                    if not pcond and level is not None and plevel is not None and plevel <= level:
                        print("ERROR %s -> %s: shadowed by %s at level %d listed before it" % (name, target, ptarget, plevel))
                        errors += 1
                levels.append((level, target, cond))
                item = re.search(r"IF_HOLD_ITEM\s*,\s*ITEM_(\w+)", cond)
                if param.startswith("DRACONID_TRADE_EVO_LEVEL") or (info["marked"] and item):
                    rows.append((level, name, target, item.group(1) if item else "", info["bst"],
                                 species.get(target, {}).get("bst")))
    # the egg dragons evolve at 25 and 50 (D-107; the playtester asked for it for all three lines)
    for frm, to, want in (("DEINO", "ZWEILOUS", 25), ("ZWEILOUS", "HYDREIGON", 50),
                          ("DREEPY", "DRAKLOAK", 25), ("DRAKLOAK", "DRAGAPULT", 50),
                          ("JANGMO_O", "HAKAMO_O", 25), ("HAKAMO_O", "KOMMO_O", 50)):
        got = [consts.get(param, int(param) if param.isdigit() else None)
               for method, param, target, cond in species.get(frm, {}).get("evos", [])
               if method == "EVO_LEVEL" and target == to]
        if got != [want]:
            print("ERROR %s -> %s: evolves at %s, not %d (D-107)" % (frm, to, got or "no level", want))
            errors += 1
    rows.sort(key=lambda r: (r[0], r[1]))
    if args.markdown:
        print("| From | To | Level | Held item | BST from → to |")
        print("|---|---|---|---|---|")
        for level, frm, to, item, b1, b2 in rows:
            print("| %s | %s | %d | %s | %s → %s |" % (nice(frm), nice(to), level, nice(item) or "–", b1, b2))
    else:
        print("%-18s %-20s %5s  %-16s %s" % ("from", "to", "level", "held item", "BST"))
        for level, frm, to, item, b1, b2 in rows:
            print("%-18s %-20s %5d  %-16s %s -> %s" % (frm, to, level, item or "-", b1, b2))
        print("%d former trade evolutions, %d errors" % (len(rows), errors))
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
