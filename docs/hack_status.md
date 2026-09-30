# Draconid Emerald – status / roadmap

This is the resume point for any new session. Legend: `[x]` done, `[~]` in progress,
`[ ]` todo, `[p]` done with a placeholder (see notes / `TODO(art)` / `TODO(dialogue)`).

Base: pokeemerald-expansion 1.17.1 (`master` @ dfb0f843). Working branch: `draconid-emerald`.
Other docs: [decisions](hack_decisions.md) · [changes](hack_changes.md) · [tools](hack_tools.md) ·
[art pipeline](hack_art_pipeline.md) · [trainers](hack_trainers.md) · [resources](hack_resources.md) ·
[playtest guide](playtest_guide.md) · [feedback](hack_feedback.md)

## Phase 0 – Tools and extensions
- [x] Toolchain (apt `gcc-arm-none-eabi` 13.2) – baseline `make` OK (2m30s, 79.7% ROM)
- [x] Baseline `make check`: 5414 passed / 0 failed (18 known-failing, 9 expected-failing, 421 to-do)
- [x] Poryscript 3.6.1 wired into the build (`poryscript_rules.mk`, generated `.inc` committed)
- [x] Porytiles 2.0.0 built from source (clang + libc++), `tools/porytiles/porytiles`
- [ ] Porytiles build integration (`make tilesets`) + first custom tileset
- [ ] Porymap scripts (`tools/hack/porymap_scripts/`: decorate + auto-tile) + register script
- [~] Map tools (`tools/hack/mapgen/`): renderer [x], inspector [x], learner/auto-tiler [ ], builder [ ], new-map writer [ ]
- [x] Art tools (`tools/hack/art/`): validate, quantize, recolor, kitbash, contact sheet
- [ ] `CLAUDE.md` + SessionStart hook
- [ ] `docs/hack_resources.md`
- [x] Debug menu: expansion default `DISABLED_ON_RELEASE` = on in `make`, off in `make release` (R + Start)

## Phase 1 – Draconid village
- [ ] Village map (General + Fallarbor tilesets) with elder's house, player's house, Rayquaza shrine, homes
- [ ] Interiors: player house 1F/2F, elder house, shrine, 1–2 homes
- [ ] Mountain path map → Route 101/Littleroot
- [ ] New game starts at home in the village; truck intro removed
- [ ] Previews rendered + critiqued, ≥2 iterations
- [ ] Custom Porytiles tiles (shrine, Rayquaza statue, meteorites) – later

## Phase 2 – Custom player character
- [ ] Outfit system (var + script command/special, survives save)
- [ ] Draconid tamer M/F: walk, run, mach, acro, surf, field move, fish, underwater, watering, decorating
- [ ] Magma disguise M/F: same states
- [ ] Reflections / palettes
- [ ] Trainer front pics (4), back pics with throw frames (4)
- [ ] Intro/gender select, trainer card, Hall of Fame, PokéNav, contest, Union Room, battle transition mugshots
- [ ] Validation + contact sheets; Brendan/May unchanged

## Phase 3 – Other sprites
- [ ] Elder, Aster, Draconid villager overworld sprites
- [ ] Aster trainer class, front pic, battle music
- [ ] Mega placeholders (none needed yet: all required Megas exist, see decisions)
- [ ] `docs/hack_art_pipeline.md`

## Phase 4 – Story events
- [ ] Egg event (Deino / Dreepy / Jangmo-o) + Aster counter-pick var + hatch cutscene
- [ ] Birch intro rework (Route 101 / lab; Brendan Treecko, May Torchic)
- [ ] Second starter after gym 1 (Charmander / Totodile / Treecko)
- [ ] Aster arc (6 appearances)
- [ ] Magma disguise arc + Mega Ring
- [ ] Vanilla flow verification

## Phase 5 – Rival battles
- [ ] Decouple Brendan & May from player gender
- [ ] 10-battle schedule
- [ ] Aster fights by egg
- [ ] Wally extra fights

## Phase 6 – Trainers / difficulty
- [ ] Level caps + AI config
- [ ] Trainer batches (see hack_trainers.md)

## Phase 7 – Polish
- [ ] Script/flag reachability checks, both genders × 9 starter combos
- [ ] `docs/playtest_guide.md`
- [ ] Final summary
