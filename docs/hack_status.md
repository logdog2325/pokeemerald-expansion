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
- [x] Porymap scripts (`tools/hack/porymap_scripts/`: decorate + auto-tile) + register script (logic checked under a Node API mock)
- [x] Map tools (`tools/hack/mapgen/`): renderer, inspector, learner/auto-tiler (self-test 90%+), spec builder + writer
- [x] Art tools (`tools/hack/art/`): validate, quantize, recolor, kitbash, contact sheet
- [x] `CLAUDE.md` + SessionStart hook (validated: toolchain, Pillow, Poryscript)
- [x] `docs/hack_resources.md`, `docs/hack_tools.md`
- [x] Headless emulator runner `tools/hack/emu/gbarun` (libmgba): scripted input + screenshots
- [x] Debug menu: expansion default `DISABLED_ON_RELEASE` = on in `make`, off in `make release` (R + Start)

## Phase 1 – Draconid village
- [p] Village map `DraconidVillage` (General + Fallarbor) with elder's house, player's house, shrine cave, 2 homes,
      crater, waterfall + pond, gatekeeper at the south exit – 5 preview iterations (placeholder NPC sprites)
- [p] Interiors: player house 1F/2F (Brendan-house copy), Elder's house, shrine (Sealed Chamber copy), 2 homes
- [x] Mountain path `DraconidPass` → Littleroot's west edge (3–4 preview iterations)
- [x] New game starts in the bedroom; truck intro removed; respawn/whiteout/fly/continue point to the village
- [x] Previews rendered + critiqued, ≥2 iterations (`tools/hack/mapgen/specs/draconid_*.py`)
- [ ] Custom Porytiles tiles (shrine, Rayquaza statue, meteorites) – `TODO(art)`, later

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
- [x] Egg event (Deino / Dreepy / Jangmo-o) + Aster counter-pick var + hatch rite at the shrine (Lv 5) –
      verified in the emulator: bedroom → clock → ceremony → rite → Running Shoes → Aster battle → Littleroot
- [ ] Birch intro rework (Route 101 rescue with the hatchling; lab: Brendan Treecko, May Torchic, player Pokédex)
      **← resume here.** Known: walking north in Littleroot with `VAR_LITTLEROOT_TOWN_STATE`=1 triggers the twin
      and then the player is blocked at (10,2); check black tiles at the west connection on the first frame.
- [ ] Route 103 May, Oldale rival scene, rival houses/bedrooms, SS Ticket/Lati TV scene → Draconid house
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
