#!/usr/bin/env python3
"""
check_tiers.py - do a trainer's rematch tiers read as one trainer?

  python3 tools/hack/trainers/check_tiers.py [party file]   # default src/data/trainers.party

For every row of gRematchTable (src/battle_setup.c) it checks, tier by tier:
  - the ace (last Pokemon) level goes up, and no tier's top level is below the previous tier's
  - the evolution families of a tier are all still in the next tier (a team grows, it doesn't swap)
Families are the root pre-evolution of each species (Swellow -> Taillow). Prints one line per problem
and a summary; exit 1 if a level problem is found (family changes are warnings).
The Draconid rivals' story fights are checked the same way, levels only (D-282): Aster per egg and Nerine per egg x
second starter, each battle in story order (STORY_CHAINS) - its ace and its top level above the battle before.
"""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_party  # noqa: E402
import party  # noqa: E402
import scan_maps  # noqa: E402

ROOT = check_party.ROOT

EGGS = ("DEINO", "DREEPY", "JANGMO_O")
STARTERS = ("CHARMANDER", "TOTODILE", "TREECKO")
# The Draconid rivals' battles in story order (D-282); ids are named after the player's egg (and second starter).
# Aster: Draconid Pass, Granite Cave, Meteor Falls, Route 121, home before the League, the Sky Pillar trial, the
# post-game shrine and pond double. Nerine: her six fights in Aqua blue, the Seafloor reveal, home before the League,
# the post-game pond single and double (her Sky Pillar partner team is a PARTNER_*, not in this file).
ASTER_FIGHTS = ("PASS", "GRANITE_CAVE", "METEOR_FALLS", "ROUTE_121", "VILLAGE", "SKY_PILLAR", "POSTGAME", "DOUBLE")
NERINE_FIGHTS = ("PETALBURG_WOODS", "RUSTURF", "SLATEPORT", "MT_CHIMNEY", "MT_PYRE", "AQUA_HIDEOUT", "SEAFLOOR",
                 "VILLAGE", "POSTGAME", "DOUBLE")


def story_chains():
    for e in EGGS:
        yield ["TRAINER_ASTER_%s_%s" % (f, e) for f in ASTER_FIGHTS]
        for st in STARTERS:
            # Nerine's Petalburg Woods fight comes before the second starter: one team per egg
            yield ["TRAINER_NERINE_%s_%s" % (f, e) if f == "PETALBURG_WOODS" else "TRAINER_NERINE_%s_%s_%s" % (f, e, st)
                   for f in NERINE_FIGHTS]


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, "src/data/trainers.party")
    parents, _, _ = check_party.load_species_info()
    blocks = {tid: party.parse_block(raw) for tid, raw in party.split(open(path).read())[1]}

    def family(species):
        sp = party.const_name(species, "SPECIES_")[len("SPECIES_"):]
        seen = set()
        while sp in parents and sp not in seen:
            seen.add(sp)
            sp = parents[sp][0]
        return sp

    errors = warnings = 0
    for chain in story_chains():
        prev = None
        for t in chain:
            if t not in blocks:
                print("ERROR   %s: missing (STORY_CHAINS)" % t)
                errors += 1
                continue
            mons = blocks[t]["mons"]
            ace, top = mons[-1]["level"], max(m["level"] for m in mons)
            if prev and (ace <= prev[1] or top < prev[2]):
                print("ERROR   %s: ace Lv%d / top Lv%d not above %s (ace Lv%d / top Lv%d)" % (t, ace, top, prev[0], prev[1], prev[2]))
                errors += 1
            prev = (t, ace, top)
    for tiers, _ in scan_maps.rematches():
        row = []
        for t in tiers:
            if t in blocks and (not row or row[-1] != t):
                row.append(t)
        prev = None
        for t in row:
            mons = blocks[t]["mons"]
            fams = {family(m["species"]) for m in mons}
            ace, top = mons[-1]["level"], max(m["level"] for m in mons)
            if prev:
                pt, pfams, pace, ptop = prev
                if ace <= pace or top < ptop:
                    print("ERROR   %s: ace Lv%d / top Lv%d not above %s (ace Lv%d / top Lv%d)" % (t, ace, top, pt, pace, ptop))
                    errors += 1
                lost = pfams - fams
                if lost:
                    print("WARNING %s: drops %s (in %s)" % (t, ", ".join(sorted(lost)), pt))
                    warnings += 1
            prev = (t, fams, ace, top)
    print("%d error(s), %d warning(s)" % (errors, warnings))
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
