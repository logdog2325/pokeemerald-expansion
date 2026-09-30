#!/usr/bin/env python3
"""
gen_script_doc.py - collect every new or reworked line of dialogue into docs/hack_script.md.

  python3 tools/hack/gen_script_doc.py [--check]

Sources, in story order:
  - data/scripts/draconid/new_game.pory, the Draconid maps' scripts.pory (the village and the pass),
    birch_intro / act1 / second_starter / act2 … act7 / rivals / aster .pory: every script and text block,
    with the lines of each msgbox / message in order;
  - vanilla texts reworked in place: labels tagged "@ Draconid Emerald" in data/maps/*/scripts.inc
    (tools/hack/retext.py writes them), grouped by map;
  - the reputation lines (townsfolk, services, gyms) are listed in docs/reputation_dialogue.md, linked here.
Control codes: \\p starts a new text box (a new line here), \\n and \\l are line breaks inside a box.
--check exits 1 if docs/hack_script.md is out of date (for a pre-commit check).
"""

import glob
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
OUT = os.path.join(ROOT, "docs/hack_script.md")

# Poryscript files in story order (anything else found is appended at the end)
ORDER = [
    "data/scripts/draconid/new_game.pory",
    "data/maps/DraconidVillage_PlayersHouse_2F/scripts.pory",
    "data/maps/DraconidVillage_PlayersHouse_1F/scripts.pory",
    "data/maps/DraconidVillage/scripts.pory",
    "data/maps/DraconidVillage_EldersHouse/scripts.pory",
    "data/maps/DraconidVillage_Shrine/scripts.pory",
    "data/maps/DraconidVillage_House1/scripts.pory",
    "data/maps/DraconidVillage_House2/scripts.pory",
    "data/maps/DraconidPass/scripts.pory",
    "data/scripts/draconid/birch_intro.pory",
    "data/scripts/draconid/act1.pory",
    "data/maps/PetalburgWoods_MagmaOutpost/scripts.pory",
    "data/scripts/draconid/second_starter.pory",
    "data/scripts/draconid/act2.pory",
    "data/scripts/draconid/act3.pory",
    "data/scripts/draconid/act4.pory",
    "data/scripts/draconid/act5.pory",
    "data/scripts/draconid/act6.pory",
    "data/scripts/draconid/act7.pory",
    "data/scripts/draconid/rivals.pory",
    "data/scripts/draconid/aster.pory",
]

STRING = r'"(?:[^"\\]|\\.)*"'
FORMAT = re.compile(r'format\(\s*((?:%s\s*)+)' % STRING)
BLOCK = re.compile(r'^(script|text)\s+(\w+)\s*\{', re.M)


def join_strings(blob):
    return "".join(s[1:-1] for s in re.findall(STRING, blob))


def pretty(text):
    """One line per text box; \\n / \\l become spaces."""
    text = text.replace('\\"', '"')
    text = re.sub(r"\\[nl]", " ", text).rstrip("$")
    boxes = [re.sub(r"\s+", " ", b).strip() for b in text.split("\\p")]
    return [b for b in boxes if b]


def blocks(src):
    """(kind, name, body) for each top-level script/text block (brace matching)."""
    out = []
    for m in BLOCK.finditer(src):
        i = src.index("{", m.start())
        depth, j, in_str = 0, i, False
        while j < len(src):
            c = src[j]
            if in_str:
                if c == "\\":
                    j += 1  # skip the escaped character
                elif c == '"':
                    in_str = False
            elif c == '"':
                in_str = True  # {PLAYER} and friends inside strings aren't braces
            elif c == "/" and src.startswith("//", j):
                j = src.find("\n", j)  # comments may hold anything
                if j < 0:
                    break
            elif c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        out.append((m.group(1), m.group(2), src[i + 1:j]))
    return out


def pory_section(path):
    src = open(os.path.join(ROOT, path)).read()
    header = []
    for line in src.splitlines():
        if line.startswith("//"):
            header.append(line[2:].strip())
        else:
            break
    texts = {}
    items = blocks(src)
    for kind, name, body in items:
        if kind == "text":
            m = FORMAT.search(body)
            if m:
                texts[name] = join_strings(m.group(1))
            else:
                texts[name] = join_strings(body)
    lines = []
    for kind, name, body in items:
        if kind != "script":
            continue
        said = []
        # msgbox/message with an inline format() or a text label, in order
        for m in re.finditer(r'(?:msgbox|message)\(\s*(format\(\s*(?:%s\s*)+\)|\w+)' % STRING, body):
            arg = m.group(1)
            if arg.startswith("format"):
                said.append(join_strings(arg))
            elif arg in texts:
                said.append(texts[arg])
        if not said:
            continue
        lines.append("### `%s`" % name)
        for t in said:
            for box in pretty(t):
                lines.append("- %s" % box)
        lines.append("")
    if not lines:
        return []
    title = os.path.relpath(path, ROOT)
    out = ["## %s" % title]
    if header:
        out.append("")
        out.append(" ".join(header))
    out.append("")
    return out + lines


def vanilla_section():
    out = ["## Reworked vanilla texts (`@ Draconid Emerald` labels in `data/maps/*/scripts.inc`)", ""]
    label = re.compile(r'^(\w+_Text_\w+):{1,2}\s*@ Draconid Emerald[^\n]*\n((?:\t\.string .*\n)+)', re.M)
    for path in sorted(glob.glob(os.path.join(ROOT, "data/maps/*/scripts.inc"))):
        src = open(path).read()
        found = label.findall(src)
        if not found:
            continue
        out.append("### %s" % os.path.basename(os.path.dirname(path)))
        for name, body in found:
            text = "".join(re.findall(r'\.string "((?:[^"\\]|\\.)*)"', body))
            boxes = pretty(text)
            out.append("- `%s`: %s" % (name, " / ".join(boxes)))
        out.append("")
    return out


def build():
    paths = [p for p in ORDER if os.path.exists(os.path.join(ROOT, p))]
    extra = sorted(os.path.relpath(p, ROOT) for p in glob.glob(os.path.join(ROOT, "data/scripts/draconid/*.pory"))
                   + glob.glob(os.path.join(ROOT, "data/maps/*/scripts.pory")))
    paths += [p for p in extra if p not in paths]
    out = [
        "# Draconid Emerald – script (all new and reworked dialogue)",
        "",
        "Generated by `tools/hack/gen_script_doc.py` from the scripts – edit the scripts, not this file, then",
        "rerun the tool. One bullet per text box, in the order the scene shows them (branches follow each",
        "other). Townsfolk, services and gyms by reputation state: [reputation_dialogue.md](reputation_dialogue.md).",
        "The story they follow: [hack_story.md](hack_story.md).",
        "",
    ]
    for p in paths:
        out += pory_section(p)
    out += vanilla_section()
    return "\n".join(out).rstrip() + "\n"


def main():
    text = build()
    if "--check" in sys.argv:
        ok = os.path.exists(OUT) and open(OUT).read() == text
        print("docs/hack_script.md is %s" % ("up to date" if ok else "out of date"))
        sys.exit(0 if ok else 1)
    open(OUT, "w").write(text)
    print("wrote %s (%d lines)" % (os.path.relpath(OUT, ROOT), text.count("\n")))


if __name__ == "__main__":
    main()
