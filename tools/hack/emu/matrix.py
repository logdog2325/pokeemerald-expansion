#!/usr/bin/env python3
"""
matrix.py - run the flow tests for every player gender x egg x second starter (2 x 3 x 3 = 18).

  python3 tools/hack/emu/matrix.py -o /tmp/matrix [-j 3] [--only M_DEINO]

Per gender and egg (6 chains, run in parallel): opening -> route103 -> route104, then rivals and
postgame_home (their scenes don't depend on the egg, so only with Deino), then for each second starter
second_starter (Birch's pick) and aster (Aster's trainer ids for the egg, the Mega Stone for the
second starter, the Draconid / Magma sprites for the gender). Needs a debug build (the warp hook).
Prints one line per test run and a summary table; exit 1 if any run failed. Logs are in -o.
"""

import argparse
import concurrent.futures
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PLAY = os.path.join(HERE, "play.py")
TESTS = os.path.join(HERE, "tests")

EGGS = [("DEINO", 0), ("DREEPY", 1), ("JANGMO_O", 2)]                # DRACONID_EGG_*
SECONDS = [("CHARMANDER", 1, "ITEM_CHARIZARDITE_X"),                 # SECOND_STARTER_*, Mega Stone
           ("TOTODILE", 2, "ITEM_FERALIGITE"),
           ("TREECKO", 3, "ITEM_SCEPTILITE")]


def run(test, out, defines, log):
    cmd = [sys.executable, PLAY, os.path.join(TESTS, test + ".play"), "-o", out]
    for k, v in defines.items():
        cmd += ["-D", "%s=%s" % (k, v)]
    res = subprocess.run(cmd, capture_output=True, text=True)
    with open(log, "a") as f:
        f.write("### %s %s\n%s%s\n" % (test, defines, res.stdout, res.stderr))
    bad = [l for l in res.stdout.splitlines() if "EXPECTED" in l or "TIMEOUT" in l]
    return res.returncode == 0, bad


def chain(gender, egg, egg_id, root):
    name = "%s_%s" % (gender, egg)
    out = os.path.join(root, name)
    os.makedirs(out, exist_ok=True)
    log = os.path.join(out, "log.txt")
    open(log, "w").close()
    results = []
    steps = [("opening", {"GENDER": gender, "EGG": egg_id, "EGGNAME": egg}), ("route103", {}), ("route104", {})]
    if egg_id == 0:
        steps += [("rivals", {}), ("postgame_home", {})]
    for second, value, stone in SECONDS:
        steps.append(("second_starter", {"PICK": value - 1, "SECOND": value}))
        steps.append(("aster", {"EGGNAME": egg, "SECOND": value, "STONE": stone,
                                "GFX": "DRACONID_" + gender, "MAGMA": "MAGMA_" + gender}))
    for test, defines in steps:
        ok, bad = run(test, out, defines, log)
        label = test + ("" if test not in ("second_starter", "aster") else " " + SECONDS[defines["SECOND"] - 1][0])
        results.append((name, label, ok, bad))
        if not ok and test in ("opening", "route103", "route104"):
            break  # the rest needs their savestates
    return results


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("-j", "--jobs", type=int, default=3)
    ap.add_argument("--only", help="one chain, e.g. F_DREEPY")
    args = ap.parse_args()
    combos = [(g, e, i) for g in ("M", "F") for e, i in EGGS]
    if args.only:
        combos = [c for c in combos if "%s_%s" % (c[0], c[1]) == args.only]
    failed = 0
    with concurrent.futures.ThreadPoolExecutor(args.jobs) as ex:
        for results in ex.map(lambda c: chain(c[0], c[1], c[2], args.out), combos):
            for name, label, ok, bad in results:
                print("%-4s %-11s %-26s %s" % ("ok" if ok else "FAIL", name, label, "; ".join(bad)))
                failed += not ok
    print("%d run(s) failed" % failed)
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
