# Draconid Emerald – list of changes

Every new or changed flag, var, constant, config option, script and build rule.
Grouped by area; each entry names the file(s).

## Build / tooling
| Change | Where | Notes |
|---|---|---|
| `include poryscript_rules.mk` | `Makefile` | compiles `data/**/*.pory` → `.inc` (generated target) |
| New rule file | `poryscript_rules.mk` | uses `tools/poryscript/poryscript` + its JSON configs |
| Poryscript configs | `tools/poryscript/{font,command}_config.json` | copied from Poryscript 3.6.1 |
| Tool installer | `tools/hack/install_tools.sh` | toolchain, Pillow, Poryscript, optional Porytiles |
| Map tools | `tools/hack/mapgen/` | see docs/hack_tools.md |
| Art tools | `tools/hack/art/` | see docs/hack_tools.md |
| Porymap scripts | `tools/hack/porymap_scripts/` | registered by `register.py` |
| `.gitignore` | `.gitignore` | tool binaries ignored; `tools/hack/porymap_scripts/*.js` un-ignored |

## Config options
| Option | Old | New | File |
|---|---|---|---|
| (none yet) | | | |

## Flags
| Flag | Meaning |
|---|---|

## Vars
| Var | Values |
|---|---|

## Constants
| Constant | Where |
|---|---|

## Scripts
| Script / label | File |
|---|---|
