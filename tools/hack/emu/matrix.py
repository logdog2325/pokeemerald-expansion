#!/usr/bin/env python3
"""
matrix.py - run the flow tests for every player gender x egg x second starter (2 x 3 x 3 = 18).

  python3 tools/hack/emu/matrix.py -o /tmp/matrix [-j 3] [--only M_DEINO]

Per gender and egg (6 chains, run in parallel): opening -> route103 -> woods (Nerine's team for the egg,
the Magma sprite for the gender) -> rustboro, then rivals, rivals2, postgame_home, maxie_calls, elite_four, hm_free
(HM field moves without a Pokémon that knows them), frontier_legends (post-game) and the checks of wild,
progression, trade_evos, battle_items, gen49_trainers, magma_revenge (Team Magma's revenge after the
Sootopolis reveal), fades and the title screen – none depends on the egg, so only with Deino – then for each
second starter second_starter (Tabitha + Prof. Oak's pick), aster
(Aster's trainer ids for the egg, the Draconid / Magma sprites for the gender), act2 (Nerine's teams for egg x
second starter; the Totodile runs keep the Devon Goods for Magma), act3 (Aster's and Nerine's teams, the
Mega Stone for the second starter), act4 (Nerine's Mt. Pyre team for egg x second starter, the Magma
sprite for the gender) and act5 (Nerine's teams for egg x second starter; the Totodile runs take May as the
Sootopolis partner), and act7 (the Sky Pillar double: Aster's team by egg, Nerine's partner and post-game
teams by egg x second starter; act6 before it, once, with Deino); last, with Deino, rival_calls (it starts from
act5's Sootopolis aftermath, where the rivals register, D-256). Needs a debug build (the warp hook).
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
# act7.play's attacking move slot for the egg Pokemon in rustboro_done.ss (Dragon Breath, Astonish, Tackle)
MOVE_SLOT = {"DEINO": 2, "DREEPY": 2, "JANGMO_O": 0}
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
    ok = res.returncode == 0
    if test == "fades" and ok:
        # same-screen fades must bring the picture back unchanged (D-278)
        chk = subprocess.run([sys.executable, os.path.join(os.path.dirname(PLAY), "fade_check.py"), out],
                             capture_output=True, text=True)
        with open(log, "a") as f:
            f.write("### fade_check\n%s%s\n" % (chk.stdout, chk.stderr))
        ok = chk.returncode == 0
        bad += [l for l in chk.stdout.splitlines() if "CHANGED" in l]
    return ok, bad


def chain(gender, egg, egg_id, root):
    name = "%s_%s" % (gender, egg)
    out = os.path.join(root, name)
    os.makedirs(out, exist_ok=True)
    log = os.path.join(out, "log.txt")
    open(log, "w").close()
    results = []
    steps = [("opening", {"GENDER": gender, "EGG": egg_id, "EGGNAME": egg}), ("route103", {}),
             ("woods", {"EGGNAME": egg, "MAGMA": "MAGMA_" + gender}), ("rustboro", {})]
    if egg_id == 0:
        steps.append(("title", {}))  # the title screen from power-on (D-276, D-277); needs no savestate
        steps += [("rivals", {}), ("rivals2", {}), ("postgame_home", {}), ("maxie_calls", {}), ("elite_four", {}),
                  ("hm_free", {"MAGMA": "MAGMA_" + gender})]
        steps.append(("frontier_legends", {}))  # the Battle Frontier legends (post-game, D-225 - D-229)
        # wild tables + National Dex (D-193), the Aqua Hideout story-lock fix (D-213), level evolutions (D-216),
        # the battle-item counter (D-218)
        steps += [("wild", {}), ("progression", {}), ("trade_evos", {}), ("battle_items", {})]
        # (rival_calls runs after act5, below: the rivals register in the Sootopolis aftermath, D-256)
        steps.append(("gen49_trainers", {}))  # Gen 4-9 Pokémon on generic trainers and grunts (D-240 - D-242)
        steps.append(("act6", {}))  # the Champion's room, the Hall of Fame, the meteor alert (Act 6)
        # Team Magma's revenge after the Sootopolis reveal, to the League door (D-244 - D-249)
        steps.append(("magma_revenge", {"GFX": "DRACONID_" + gender}))
        steps.append(("fades", {}))  # same-screen fades under weather and the day/night tint (D-278)
    for second, value, stone in SECONDS:
        steps.append(("second_starter", {"PICK": value - 1, "SECOND": value, "MAGMA": "MAGMA_" + gender}))
        steps.append(("aster", {"EGGNAME": egg, "SECOND": value,
                                "GFX": "DRACONID_" + gender, "MAGMA": "MAGMA_" + gender}))
        # Act 2 (Nerine's teams for egg x second starter); Totodile runs keep the Devon Goods for Magma
        goods = 1 if second == "TOTODILE" else 0
        steps.append(("act2", {"EGGNAME": egg, "SECOND": value, "SECONDNAME": second,
                               "GOODS": goods, "RETURNED": 1 - goods, "GOODSNAME": "Kept" if goods else "Returned"}))
        # Act 3 (Aster's team for the egg, Nerine's for egg x second starter, the second starter's Mega Stone)
        steps.append(("act3", {"EGGNAME": egg, "SECOND": value, "SECONDNAME": second, "STONE": stone}))
        # Act 4 (Nerine's Mt. Pyre team for egg x second starter)
        steps.append(("act4", {"EGGNAME": egg, "SECOND": value, "SECONDNAME": second, "MAGMA": "MAGMA_" + gender}))
        # Act 5 (Nerine's teams for egg x second starter); the Totodile runs take May as the Sootopolis partner
        steps.append(("act5", {"EGGNAME": egg, "SECOND": value, "SECONDNAME": second,
                               "PARTNER": 1 if second == "TOTODILE" else 0, "GFX": "DRACONID_" + gender}))
        # Act 7: the Sky Pillar double picks Aster's team by egg and Nerine's partner team by egg x second starter
        steps.append(("act7", {"EGGNAME": egg, "MOVE": MOVE_SLOT[egg], "SECOND": value, "SECONDNAME": second}))
    if egg_id == 0:
        steps.append(("rival_calls", {}))  # the PokéNav calls of the rivals (D-243, D-256) and Mr. Stone (D-258)
    for test, defines in steps:
        ok, bad = run(test, out, defines, log)
        label = test + ("" if test not in ("second_starter", "aster", "act2", "act3", "act4", "act5", "act7")
                        else " " + SECONDS[defines["SECOND"] - 1][0])
        results.append((name, label, ok, bad))
        if not ok and test in ("opening", "route103", "woods", "rustboro"):
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
