#!/usr/bin/env python3
"""No trainer gets weaker by accident: compare src/data/trainers.party (and battle_partners.party) with a git ref.

  python3 tools/hack/trainers/check_strength.py [--ref origin/draconid-emerald]

For every trainer in both versions, it reports fewer Pokémon, a lower level total, fewer held items, fewer moves,
fewer EV lines or shorter AI flags. Tests make battles winnable in emulator memory only (play.py boost / battlepp,
pokes of the enemy party after the battle starts) – never by editing the party files (the playtester: "make sure if you
weaken teams for testing you put them back to their full strength … we want this rom hack to have some degree of
difficulty"). An intended change goes into ALLOWED with its reason. Exit 1 on any unexplained loss.
"""

import argparse
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import party  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
FILES = ("src/data/trainers.party", "src/data/battle_partners.party")

# Trainer ids whose strength dropped on purpose, with the decision that did it.
ALLOWED = {
    "TRAINER_STEVEN": "D-250: TRAINER_STEVEN became the Champion's first battle (Lv 57-60, cap 60); his post-game "
                      "strength moved to TRAINER_STEVEN_REMATCH (Lv 77-79)",
}


def strength(raw):
    b = party.parse_block(raw)
    mons = b["mons"]
    return {
        "mons": len(mons),
        "levels": sum(m["level"] for m in mons),
        "items": sum(1 for m in mons if m.get("item")),
        "moves": sum(len(m["moves"]) for m in mons),
        "EV lines": raw.count("EVs:"),
        "AI flags": len([f for f in b["fields"].get("AI", "").split("/") if f.strip()]),
    }


def blocks(text):
    _, bl = party.split(text)
    return {tid: raw for tid, raw in bl}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", default="origin/draconid-emerald", help="git ref to compare with")
    args = ap.parse_args()
    bad = 0
    compared = 0
    for path in FILES:
        try:
            old_text = subprocess.run(["git", "-C", ROOT, "show", "%s:%s" % (args.ref, path)],
                                      capture_output=True, text=True, check=True).stdout
        except subprocess.CalledProcessError:
            print("%s: not in %s, skipped" % (path, args.ref))
            continue
        old, new = blocks(old_text), blocks(open(os.path.join(ROOT, path)).read())
        for tid, raw in new.items():
            if tid not in old:
                continue
            compared += 1
            a, b = strength(old[tid]), strength(raw)
            losses = ["%s %d -> %d" % (k, a[k], b[k]) for k in a if b[k] < a[k]]
            if not losses:
                continue
            if tid in ALLOWED:
                print("ok      %s: %s (%s)" % (tid, "; ".join(losses), ALLOWED[tid]))
                continue
            print("WEAKER  %s: %s" % (tid, "; ".join(losses)))
            bad += 1
        for tid in old:
            if tid not in new and tid not in ALLOWED:
                print("REMOVED %s" % tid)
                bad += 1
    print("%d trainers compared with %s, %d weaker or removed" % (compared, args.ref, bad))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
