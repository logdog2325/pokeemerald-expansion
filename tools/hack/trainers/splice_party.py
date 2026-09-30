#!/usr/bin/env python3
"""
splice_party.py - replace trainer blocks in src/data/trainers.party with blocks from batch files.

  python3 tools/hack/trainers/splice_party.py docs/trainer_batches/batch1.party [more.party ...]
  python3 tools/hack/trainers/splice_party.py --check batch.party     # only report what would change

Each batch file holds complete "=== TRAINER_XXX ===" blocks. A block replaces the block with the
same id in place (order and every other block stay untouched). Unknown ids are an error unless
--append is given, which adds them at the end. A trainer id present in two batches is an error.
"""

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import party  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
TARGET = os.path.join(ROOT, "src/data/trainers.party")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("batches", nargs="+")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--append", action="store_true")
    args = ap.parse_args()

    pre, blocks = party.split(open(TARGET).read())
    index = {tid: i for i, (tid, _) in enumerate(blocks)}
    incoming = {}
    for path in args.batches:
        _, bb = party.split(open(path).read())
        for tid, raw in bb:
            if tid in incoming:
                sys.exit("%s: %s already given by %s" % (path, tid, incoming[tid][0]))
            if not raw.endswith("\n\n"):
                raw = raw.rstrip("\n") + "\n\n"
            incoming[tid] = (path, raw)
    changed = added = 0
    for tid, (path, raw) in incoming.items():
        if tid in index:
            if blocks[index[tid]][1] != raw:
                blocks[index[tid]] = (tid, raw)
                changed += 1
        elif args.append:
            blocks.append((tid, raw))
            added += 1
        else:
            sys.exit("%s: unknown trainer %s (use --append for new ids)" % (path, tid))
    print("%d block(s) replaced, %d added" % (changed, added))
    if not args.check:
        open(TARGET, "w").write(party.join(pre, blocks))


if __name__ == "__main__":
    main()
