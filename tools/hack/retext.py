#!/usr/bin/env python3
"""
retext.py - rewrite the text of vanilla dialogue labels in a map's scripts.inc (Draconid Emerald).

  python3 tools/hack/retext.py data/maps/X/scripts.inc changes.json
  # or from Python:
  sys.path.insert(0, "tools/hack"); from retext import retext
  retext("data/maps/X/scripts.inc", {"X_Text_Label": ["NORMAN: Hm…\\n", "Line two.$"]})

changes.json maps each text label to its new .string lines, exactly as they'd appear between the quotes
(control codes like \\n \\p \\l and the final $ included). The label keeps its name and gets an
"@ Draconid Emerald" comment, so reworked vanilla texts are easy to find; every other line of the file
stays untouched. Fails if a label isn't found.
"""

import json
import re
import sys


def retext(path, texts):
    s = open(path).read()
    for label, lines in texts.items():
        m = re.search(r'^(%s:{1,2}[^\n]*\n)((?:\t\.string .*\n)+)' % re.escape(label), s, re.M)
        if not m:
            raise SystemExit("%s: label %s not found" % (path, label))
        head = m.group(1).rstrip('\n')
        if "@ Draconid Emerald" not in head:
            head += '  @ Draconid Emerald'
        body = ''.join('\t.string "%s"\n' % l for l in lines)
        s = s[:m.start()] + head + '\n' + body + s[m.end():]
    open(path, 'w').write(s)


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    retext(sys.argv[1], json.load(open(sys.argv[2])))


if __name__ == "__main__":
    main()
