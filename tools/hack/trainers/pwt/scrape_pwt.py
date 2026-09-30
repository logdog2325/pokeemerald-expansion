#!/usr/bin/env python3
"""
scrape_pwt.py - Pokemon World Tournament (Black 2 / White 2) teams from Serebii.net.

  python3 tools/hack/trainers/pwt/scrape_pwt.py --cache DIR            # fetch (cached) + parse
  python3 tools/hack/trainers/pwt/scrape_pwt.py --cache DIR --offline  # parse the cache only

Source: https://www.serebii.net/black2white2/pwt/champion.shtml (the Champions Tournament: Red, Blue, Lance,
Steven, Wallace, Cynthia, Alder, Iris). The page is fetched once and kept in the cache directory (use a scratch
directory, not the repo). The result goes to tools/hack/trainers/pwt/pwt_champions.json:

  {"source", "url", "fetched", "trainers": [{"name", "class", "mons": [{"species", "level", "item", "moves"}]}]}

Serebii lists species, level (a flat 50), held item and moves; no abilities or natures ("Abilities are not
included"). Draconid Emerald uses Red's and Blue's teams for the Battle Frontier legends (D-225, D-226).
"""

import argparse
import datetime
import html
import json
import os
import re
import sys
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "pwt_champions.json")
URL = "https://www.serebii.net/black2white2/pwt/champion.shtml"
AGENT = "Mozilla/5.0 (compatible; DraconidEmerald-trainer-data/1.0; one request at a time)"


def fetch(cache, offline):
    path = os.path.join(cache, "pwt_champion.html")
    if not os.path.exists(path):
        if offline:
            sys.exit("not cached: %s" % path)
        req = urllib.request.Request(URL, headers={"User-Agent": AGENT})
        with urllib.request.urlopen(req, timeout=60) as r:
            data = r.read()
        os.makedirs(cache, exist_ok=True)
        with open(path, "wb") as f:
            f.write(data)
    return open(path, encoding="latin-1").read()


def text(s):
    return re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", s))).strip()


def parse(page):
    trainers = []
    for table in re.findall(r'<table class="trainer">(.*?)</table>', page, re.S):
        who = re.search(r"<td\s*>\s*([^<]*?Trainer[^<]*?)\s*</td>", table)
        if not who:
            continue
        full = text(who.group(1))
        cls, _, name = full.rpartition(" ")
        row = table[who.end():]
        species = [text(s) for s in re.findall(r'<a href="/pokedex-bw/\d+\.shtml">([^<]+)</a>', row.split("</tr>")[0])]
        levels = [int(v) for v in re.findall(r'class="level"[^>]*>\s*Level (\d+)', table)]
        attacks = [[text(a) for a in re.findall(r"<a [^>]*>([^<]+)</a>", cell)]
                   for cell in re.findall(r"<b>Attacks</b>:(.*?)</td>", table, re.S)]
        items = [text(re.sub(r"<img[^>]*>", "", cell)) for cell in re.findall(r"<b>Hold Item</b>:(.*?)</td>", table, re.S)]
        mons = []
        for i, sp in enumerate(species):
            mons.append({"species": sp, "level": levels[i] if i < len(levels) else None,
                         "item": items[i] if i < len(items) else None,
                         "moves": attacks[i] if i < len(attacks) else []})
        trainers.append({"name": name, "class": cls, "mons": mons})
    return trainers


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--cache", required=True, help="directory for the downloaded page (not in the repo)")
    ap.add_argument("--offline", action="store_true", help="only parse the cached page")
    args = ap.parse_args()
    page = fetch(args.cache, args.offline)
    trainers = parse(page)
    out = {"source": "Serebii.net, Pokemon World Tournament - Champions Tournament (Black 2 / White 2)",
           "url": URL, "fetched": datetime.date.fromtimestamp(os.path.getmtime(
               os.path.join(args.cache, "pwt_champion.html"))).isoformat(),
           "trainers": trainers}
    with open(OUT, "w") as f:
        json.dump(out, f, indent=1, ensure_ascii=False)
        f.write("\n")
    for t in trainers:
        print("%s %s: %s" % (t["class"], t["name"], ", ".join("%s @ %s" % (m["species"], m["item"]) for m in t["mons"])))


if __name__ == "__main__":
    main()
