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
- [x] Outfit system: `VAR_PLAYER_OUTFIT`, `src/player_outfit.c`, `special SetPlayerOutfit` (saved with the game)
- [p] Draconid tamer M/F: walk, run, Mach, Acro, surf, field move, fish, underwater, watering, decorating
      (Acro wheelies and watering can are rough – `TODO(art)`)
- [p] Magma disguise M/F: same states (same `TODO(art)` items)
- [x] Reflection palettes (generated), underwater uses the shared underwater palette
- [x] Trainer front pics (Draconid M/F; Magma = grunt pics), back pics with throw frames (4 sets)
- [x] Gender choice, trainer card, Hall of Fame, battle transitions, Pokédex size screen, region map/PokéNav icon,
      decorating, easy-chat interview follow the outfit; contests/Union Room use the player's object
- [ ] Opening movie + credits bike scenes still show Brendan/May – `TODO(art)`
- [x] Validation (`tools/hack/art/manifests/draconid.json`, 50 files OK) + in-game checks (walk/run, both genders,
      battle back pic, trainer card, Magma outfit); Brendan/May files unchanged

## Phase 3 – Other sprites
- [x] Elder, Aster, Draconid villager overworld sprites (shared Draconid NPC palette) + dragon egg objects
- [x] Aster trainer class (DRACONID), front pic, music (intense encounter theme, rival battle theme)
- [x] Mega placeholders: none needed (all required Megas exist, D-010)
- [x] `docs/hack_art_pipeline.md` (player, NPCs, objects)
- [ ] Rayquaza shrine statue / meteorites as custom Porytiles tiles – `TODO(art)`, later

## Phase 4 – Story events
- [x] Egg event (Deino / Dreepy / Jangmo-o) + Aster counter-pick var + hatch rite at the shrine (Lv 5) –
      verified in the emulator: bedroom → clock → ceremony → rite → Running Shoes → Aster battle → Littleroot
- [x] Birch intro rework: Route 101 rescue with the hatchling; lab: Brendan Treecko, May Torchic, player Pokédex;
      Route 103 May – verified in the emulator (`tools/hack/emu/tests/opening.play`, `route103.play`)
- [ ] Rival houses in Littleroot (gender logic, bedrooms), SS Ticket/Lati TV scene → Draconid house,
      lab post-game rival lines (gender-branched, sprite is always May) **← next in Phase 4/5**
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
