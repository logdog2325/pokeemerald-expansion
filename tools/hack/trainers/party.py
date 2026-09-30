"""
party.py - read and write src/data/trainers.party (Showdown-style trainer syntax).

A file is split into blocks, one per "=== TRAINER_XXX ===" header. Everything before the first
header (the format comment) is kept verbatim. Each block keeps its raw text so untouched blocks
round-trip byte for byte; parse_block() gives a structured view for checks.
"""

import re

HEADER = re.compile(r"^=== (TRAINER_\w+) ===\s*$", re.M)


def split(text):
    """Return (preamble, [(trainer_id, raw_block_text), ...]); raw text starts at the header line."""
    matches = list(HEADER.finditer(text))
    if not matches:
        return text, []
    pre = text[:matches[0].start()]
    blocks = []
    for i, m in enumerate(matches):
        end = matches[i + 1].start() if i + 1 < len(matches) else len(text)
        blocks.append((m.group(1), text[m.start():end]))
    return pre, blocks


def join(pre, blocks):
    return pre + "".join(raw for _, raw in blocks)


def parse_block(raw):
    """{'id', 'fields': {key: value}, 'mons': [{'species', 'item', 'level', 'moves', 'lines'}]}"""
    lines = raw.split("\n")
    tid = HEADER.match(lines[0]).group(1)
    paras, cur = [], []
    for line in lines[1:]:
        if line.strip() == "":
            if cur:
                paras.append(cur)
                cur = []
        else:
            cur.append(line)
    if cur:
        paras.append(cur)
    fields = {}
    mons = []
    if paras:
        for line in paras[0]:
            if ":" in line:
                k, v = line.split(":", 1)
                fields[k.strip()] = v.strip()
    for para in paras[1:]:
        head = para[0]
        item = None
        if " @ " in head:
            head, item = head.split(" @ ", 1)
            item = item.strip()
        head = re.sub(r"\((M|F)\)\s*$", "", head).strip()
        m = re.search(r"\(([^()]+)\)\s*$", head)
        species = m.group(1) if m else head
        mon = {"species": species.strip(), "item": item, "level": 100, "moves": [], "lines": para}
        for line in para[1:]:
            s = line.strip()
            if s.startswith("- "):
                mon["moves"].append(s[2:].strip())
            elif s.startswith("Level:"):
                mon["level"] = int(s.split(":", 1)[1])
            elif ":" in s:
                k, v = s.split(":", 1)
                mon[k.strip().lower()] = v.strip()
            elif s.endswith("Nature"):
                mon["nature"] = s[:-len("Nature")].strip()
        mons.append(mon)
    return {"id": tid, "fields": fields, "mons": mons}


def const_name(name, prefix):
    """'Mr. Mime' -> SPECIES_MR_MIME; 'Will-O-Wisp' -> MOVE_WILL_O_WISP (same rule trainerproc uses)."""
    if name.startswith(prefix):
        return name
    s = name.upper().replace("É", "E").replace("♀", "_F").replace("♂", "_M")
    s = re.sub(r"[^A-Z0-9]+", "_", s).strip("_")
    return prefix + s
