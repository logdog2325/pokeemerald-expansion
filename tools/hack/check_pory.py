#!/usr/bin/env python3
"""Every committed Poryscript .inc matches its .pory (run after a merge, before testing).

  python3 tools/hack/check_pory.py [--fix]

make regenerates an .inc only when its .pory is newer. A merge that resolves a .pory and then checks out either
side's .inc leaves the .inc newer but stale, and the ROM silently builds the old script (round 1: Lance's village
hooks went missing after the Act 7 merge). This compiles every data/**/*.pory with the Makefile's arguments
(poryscript_rules.mk) and compares; --fix writes the fresh .inc. Exit 1 when one is stale and not fixed.
"""

import argparse
import os
import subprocess
import sys
import tempfile

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
PORY_DIR = os.path.join(ROOT, "tools", "poryscript")
ARGS = ["-fc", os.path.join(PORY_DIR, "font_config.json"), "-cc", os.path.join(PORY_DIR, "command_config.json"),
        "-lm=false"]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fix", action="store_true", help="rewrite stale .inc files")
    args = ap.parse_args()
    exe = os.path.join(PORY_DIR, "poryscript")
    if not os.access(exe, os.X_OK):
        sys.exit("tools/poryscript/poryscript missing: run tools/hack/install_tools.sh")
    srcs = subprocess.run(["git", "-C", ROOT, "ls-files", "data/*.pory", "data/**/*.pory"],
                          capture_output=True, text=True, check=True).stdout.split()
    stale = 0
    for rel in sorted(set(srcs)):
        pory = os.path.join(ROOT, rel)
        inc = pory[:-len(".pory")] + ".inc"
        with tempfile.NamedTemporaryFile(suffix=".inc", delete=False) as tmp:
            out = tmp.name
        try:
            res = subprocess.run([exe, "-i", pory, "-o", out] + ARGS, capture_output=True, text=True)
            if res.returncode:
                print("ERROR   %s: %s" % (rel, res.stderr.strip()))
                stale += 1
                continue
            fresh = open(out).read()
            current = open(inc).read() if os.path.exists(inc) else None
            if fresh != current:
                if args.fix:
                    open(inc, "w").write(fresh)
                    print("FIXED   %s" % os.path.relpath(inc, ROOT))
                else:
                    print("STALE   %s" % os.path.relpath(inc, ROOT))
                    stale += 1
        finally:
            os.unlink(out)
    print("%d .pory file(s) checked, %d stale" % (len(set(srcs)), stale))
    sys.exit(1 if stale else 0)


if __name__ == "__main__":
    main()
