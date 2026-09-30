#!/usr/bin/env python3
"""
scrape_serebii.py - ORAS (Omega Ruby / Alpha Sapphire) trainer teams from Serebii.net.

  python3 tools/hack/trainers/oras/scrape_serebii.py --cache DIR            # fetch (cached) + parse
  python3 tools/hack/trainers/oras/scrape_serebii.py --cache DIR --offline  # parse the cache only
  python3 tools/hack/trainers/oras/scrape_serebii.py --cache DIR --only route104 --dump

Sources: https://www.serebii.net/pokearth/hoenn/<location>.shtml (the "Gen VI" Pokéarth pages, i.e. ORAS;
every location in the page's location menu except legendary lairs, Mirage spots and battle facilities) and
https://www.serebii.net/omegarubyalphasapphire/elitefour.shtml (Elite Four and Champion, first battle and the
post-Delta-Episode rematch, with moves). Every page is fetched once, one request at a time with a pause between
requests, and kept in the cache directory (use a scratch directory, not the repo); later runs read the cache.
The result goes to tools/hack/trainers/oras/oras_trainers.json:

  {"source", "fetched", "locations": {page: {"title", "url", "trainers": [
      {"area", "class", "name", "full", "battle", "note", "pic", "items",
       "mons": [{"species", "level", "item", "moves"?}]}]}},
   "grouped": {page: [{"area", "class", "name", "full", "note", "pic", "teams": [team, ...],
                       "alternates"?: [team, ...]}]}}

"trainers" is every trainer table in page order. "grouped" folds consecutive tables of one trainer (same
class + name + area + note; not grunts) whose top level rises into one entry: the first team is the first
battle, the later teams are the rematches / later battles in page order. Serebii marks rematchable trainers
"Rematch" (the note); Nicolas, John & Jay, Gabby & Ty etc. have later battles without that note. A table at
the same top level as the first one with other species is a version variant (Omega Ruby / Alpha Sapphire) and
goes under "alternates". The note is "Ruby" / "Sapphire" for version-only trainers (Magma / Aqua).
Serebii lists species, levels, held items and bag items; moves only on the Elite Four page; no abilities or
natures.
"""

import argparse
import datetime
import html
import json
import os
import re
import sys
import time
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "oras_trainers.json")
BASE = "https://www.serebii.net/pokearth/hoenn/"
INDEX = BASE + "index.shtml"
# Extra ORAS pages: cache name -> URL
EXTRA = {"oras_elitefour": "https://www.serebii.net/omegarubyalphasapphire/elitefour.shtml"}
AGENT = "Mozilla/5.0 (compatible; DraconidEmerald-trainer-data/1.0; one request at a time)"
DELAY = 2.0  # seconds between two requests
# Pages without trainers of the story (legendary lairs, Mirage spots, battle facilities).
SKIP = {"index", "battlefrontier", "battleresort", "battletower", "birthisland", "navelrock", "farawayisland",
        "southernisland", "crescentisle", "alteringcave", "artisancave", "fabledcave", "gnarledden",
        "namelesscavern", "pathlessplain", "tracklessforest", "miragecave", "mirageforest", "mirageisland",
        "miragemountain", "miragetower", "soaringinthesky", "secretislet", "secretmeadow", "secretshore",
        "marinecave", "terracave", "caveoforigin", "sealedchamber", "safarizone", "desertunderpass",
        "scorchedslab"}

_last = [0.0]


def fetch(url, path, offline):
    if os.path.exists(path):
        return open(path, encoding="latin-1").read()
    if offline:
        sys.exit("not cached: %s (%s)" % (url, path))
    wait = DELAY - (time.time() - _last[0])
    if wait > 0:
        time.sleep(wait)
    req = urllib.request.Request(url, headers={"User-Agent": AGENT})
    with urllib.request.urlopen(req, timeout=60) as r:
        data = r.read()
    _last[0] = time.time()
    open(path, "wb").write(data)
    print("fetched %s (%d bytes)" % (url, len(data)), file=sys.stderr)
    return data.decode("latin-1")


def fix(text):
    """Serebii serves UTF-8 bytes; the cache is read as latin-1 so it round-trips. Undo that, unescape."""
    try:
        text = text.encode("latin-1").decode("utf-8")
    except UnicodeError:
        pass
    return re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", text)).replace("\xa0", " ")).strip()


def page_list(cache, offline):
    text = fetch(INDEX, os.path.join(cache, "index.shtml"), offline)
    pages = []
    for href in re.findall(r'(?:href|value)="/pokearth/hoenn/([\w.]+)\.shtml"', text):
        if href not in SKIP and href not in pages:
            pages.append(href)
    return pages


TRAINER_TABLE = re.compile(r'<table class="trainer">')
# Area headings on Pokéarth pages; "Rematches" on the ORAS Elite Four page.
AREA = re.compile(r'<a name="xy[^"]*"><font size="4"><b><u>(.*?)</u>|<p><font size="3"><b><u>(Rematches)</u>')
TABLE_END = re.compile(r"</tr>\s*</table>\s*(?:<table class=|<p>|</td>|$)")


def parse_trainer(chunk):
    pic = re.search(r'/pokearth/trainers/oras/(\w+)\.png', chunk)
    name_row = re.search(r'<td\s*>(.*?)</td>(.*?)</tr>', chunk, re.S)
    full = fix(name_row.group(1))
    species = [fix(s) for s in re.findall(r'<td align="center"><a href="/pokedex-xy/[^"]*">(.*?)</a></td>',
                                          name_row.group(2), re.S)]
    battle = re.search(r'<b>Battle Type</b><br />\s*(.*?)<br />', chunk, re.S)
    items_cell = re.search(r'<b>Items</b><br />(.*?)</td><td class="level"', chunk, re.S)
    bag = [fix(t) for t in re.findall(r'title="([^"]+)"', items_cell.group(1))] if items_cell else []
    levels = [int(v) for v in re.findall(r'<td class="level"[^>]*>\s*Level (\d+)', chunk)]
    held = []
    for cell in re.findall(r'<b>Hold Item</b>:<br />(.*?)</td>', chunk, re.S):
        t = re.search(r'title="([^"]+)"', cell)
        name = fix(t.group(1)) if t else fix(cell)
        held.append(None if name in ("No Item", "") else name)
    moves = []
    for cell in re.findall(r'<td valign="top" class="bor">(.*?)</td>', chunk, re.S):
        if "Hold Item" in cell:
            continue
        cell = cell.replace("<b>Attacks</b>:", "")
        moves.append([fix(m) for m in re.split(r"<br\s*/?>", cell) if fix(m)])
    note = re.findall(r'<i>(.*?)</i>', chunk, re.S)
    mons = []
    for i, sp in enumerate(species):
        mon = {"species": sp, "level": levels[i] if i < len(levels) else None,
               "item": held[i] if i < len(held) else None}
        if i < len(moves):
            mon["moves"] = moves[i]
        mons.append(mon)
    return {"full": full, "battle": fix(battle.group(1)) if battle else None,
            "note": fix(note[-1]) if note else "", "pic": pic.group(1) if pic else None,
            "items": bag, "mons": mons}


def parse_page(text):
    title = re.search(r'<font size="4"><b>(.*?)</b></font><br />', text)
    out = []
    # Walk the page: area headings and trainer tables in document order.
    marks = [(m.start(), "area", fix(m.group(1) or m.group(2))) for m in AREA.finditer(text)]
    marks += [(m.start(), "trainer", None) for m in TRAINER_TABLE.finditer(text)]
    marks.sort()
    area = ""
    for i, (pos, kind, val) in enumerate(marks):
        if kind == "area":
            area = val
            continue
        end = marks[i + 1][0] if i + 1 < len(marks) else len(text)
        chunk = text[pos:end]
        # The table ends after the held items / note rows; the rest (items list, headings) is not ours.
        # (Search past the level row: the bag items cell holds a small table of its own.)
        stop = TABLE_END.search(chunk, max(0, chunk.find('class="level"')))
        if stop:
            chunk = chunk[:stop.end()]
        t = parse_trainer(chunk)
        t["area"] = area
        out.append(t)
    return (fix(title.group(1)) if title else None), out


# Trainer classes as Serebii writes them (longest first so "Team Magma Grunt" wins over "Grunt").
CLASSES = sorted("""Aroma Lady|Battle Girl|Beauty|Bird Keeper|Black Belt|Bug Catcher|Bug Maniac|Camper|
Collector|Ace Trainer|Cyclist|Dragon Tamer|Elite Four|Expert|Fisherman|Gentleman|Guitarist|Hex Maniac|Hiker|
Interviewers|Kindler|Lady|Lass|Leader|Leaders|Madame|Ninja Boy|Parasol Lady|Picnicker|Poké Fan|Poké Maniac|
Pokémon Breeder|Pokémon Ranger|Pokémon Trainer|Psychic|Rich Boy|Ruin Maniac|Sailor|Schoolkid|Sis & Bro|
Swimmer|Tuber|Triathlete|Twins|Young Couple|Old Couple|Youngster|Team Magma|Team Aqua|Magma Admin|Aqua Admin|
Magma Leader|Aqua Leader|Champion|Delinquent|Fairy Tale Girl|Backpacker|Ace Duo|Teammates|Mysterious Sisters|
Brains & Brawn|Free Diver|Scuba Diver|Street Thug|Fare Prince|Rotation Girl|Sootopolitan|Lorekeeper|
Secret Base Expert|The Winstrates’""".replace("\n", "").split("|"), key=len, reverse=True)


def split_name(full):
    full = full.replace(" ? ", " ")  # Serebii writes Swimmer♂/♀ as "Swimmer ?"
    for c in CLASSES:
        if full.startswith(c + " "):
            return c, full[len(c) + 1:]
    parts = full.rsplit(" ", 1)
    return (parts[0], parts[1]) if len(parts) == 2 else ("", full)


GRUNTS = re.compile(r"^Grunts?$")


def top(team):
    return max((m["level"] or 0) for m in team["mons"]) if team["mons"] else 0


def group(trainers):
    groups = []
    for t in trainers:
        team = {"battle": t["battle"], "items": t["items"], "mons": t["mons"]}
        last = groups[-1] if groups else None
        if (last and last["full"] == t["full"] and last["area"] == t["area"] and last["note"] == t["note"]
                and not GRUNTS.match(t["name"])):
            prev = last["teams"][-1]
            if top(team) > top(prev):
                last["teams"].append(team)
                continue
            if top(team) == top(prev) and len(last["teams"]) == 1:
                last.setdefault("alternates", []).append(team)
                continue
        groups.append({"area": t["area"], "full": t["full"], "class": t["class"], "name": t["name"],
                       "note": t["note"], "pic": t["pic"], "teams": [team]})
    return groups


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--cache", required=True, help="directory for the fetched pages (not the repo)")
    ap.add_argument("--offline", action="store_true", help="only parse pages already in the cache")
    ap.add_argument("--only", nargs="*", help="page names to parse (e.g. route104)")
    ap.add_argument("--dump", action="store_true", help="print the parsed trainers instead of writing the JSON")
    ap.add_argument("--out", default=OUT)
    args = ap.parse_args()
    os.makedirs(args.cache, exist_ok=True)
    pages = page_list(args.cache, args.offline)
    data = {"source": "%s<location>.shtml (Serebii.net Pokéarth, Gen VI pages = Omega Ruby / Alpha Sapphire) + %s"
                      % (BASE, ", ".join(EXTRA.values())),
            "fetched": None, "locations": {}, "grouped": {}}
    stamps = []
    urls = [(p, BASE + p + ".shtml") for p in pages] + list(EXTRA.items())
    for p, url in urls:
        if args.only and p not in args.only:
            continue
        path = os.path.join(args.cache, p + ".shtml")
        text = fetch(url, path, args.offline)
        stamps.append(os.path.getmtime(path))
        title, trainers = parse_page(text)
        if not trainers:
            continue
        for t in trainers:
            t["class"], t["name"] = split_name(t["full"])
        data["locations"][p] = {"title": title, "url": url, "trainers": trainers}
        data["grouped"][p] = group(trainers)
    data["fetched"] = datetime.date.fromtimestamp(max(stamps)).isoformat() if stamps else None
    if args.dump:
        for p, gs in data["grouped"].items():
            for g in gs:
                print("%s | %s | %s | %s | %s" % (p, g["area"], g["class"], g["name"], g["note"]))
                teams = [("first" if i == 0 else "re%d" % i, tm) for i, tm in enumerate(g["teams"])]
                teams += [("alt", tm) for tm in g.get("alternates", [])]
                for label, tm in teams:
                    print("    %s %s: %s" % (label, tm["battle"], ", ".join(
                        "%s %s%s%s" % (m["species"], m["level"], " @" + m["item"] if m["item"] else "",
                                       " [%s]" % "/".join(m["moves"]) if m.get("moves") else "")
                        for m in tm["mons"])))
        return
    json.dump(data, open(args.out, "w", encoding="utf-8"), indent=1, ensure_ascii=False)
    n = sum(len(v["trainers"]) for v in data["locations"].values())
    print("wrote %s: %d pages, %d trainer tables, %d trainers" % (
        args.out, len(data["locations"]), n, sum(len(v) for v in data["grouped"].values())))


if __name__ == "__main__":
    main()
