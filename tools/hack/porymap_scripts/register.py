#!/usr/bin/env python3
"""
register.py - register the Draconid Emerald Porymap scripts with Porymap.

  python3 tools/hack/porymap_scripts/register.py

Porymap keeps custom scripts in porymap.user.cfg (key "custom_scripts",
comma-separated "path:1" entries) and the Poryscript switch in
porymap.project.cfg ("use_poryscript=1"). Both files are per-user and
gitignored, so run this once after cloning (Porymap must be closed, or
re-open the project afterwards). Existing keys are preserved.
"""

import os

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
SCRIPTS = [
    "tools/hack/porymap_scripts/draconid_decorate.js",
    "tools/hack/porymap_scripts/draconid_autotile.js",
]


def read_cfg(path):
    data = {}
    order = []
    if os.path.exists(path):
        for line in open(path, encoding="utf-8").read().splitlines():
            if "=" in line:
                k, v = line.split("=", 1)
                data[k] = v
                order.append(k)
    return data, order


def write_cfg(path, data, order):
    with open(path, "w", encoding="utf-8") as f:
        for k in order:
            f.write("%s=%s\n" % (k, data[k]))


def main():
    user = os.path.join(ROOT, "porymap.user.cfg")
    data, order = read_cfg(user)
    entries = [e for e in data.get("custom_scripts", "").split(",") if e]
    paths = {e.rsplit(":", 1)[0] if e.endswith((":0", ":1")) else e: e for e in entries}
    for s in SCRIPTS:
        paths[s] = s + ":1"
    data["custom_scripts"] = ",".join(paths.values())
    if "custom_scripts" not in order:
        order.append("custom_scripts")
    write_cfg(user, data, order)
    print("updated", os.path.relpath(user, ROOT))

    proj = os.path.join(ROOT, "porymap.project.cfg")
    data, order = read_cfg(proj)
    data["use_poryscript"] = "1"
    if "use_poryscript" not in order:
        order.append("use_poryscript")
    write_cfg(proj, data, order)
    print("updated", os.path.relpath(proj, ROOT))


if __name__ == "__main__":
    main()
