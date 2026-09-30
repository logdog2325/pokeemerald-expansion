# Draconid Emerald – status / roadmap

This is the resume point for any new session. Legend: `[x]` done, `[~]` in progress,
`[ ]` todo, `[p]` done with a placeholder (see notes / `TODO(art)` / `TODO(dialogue)`).

Base: pokeemerald-expansion 1.17.1 (`master` @ dfb0f843). Working branch: `draconid-emerald`.
Other docs: [decisions](hack_decisions.md) · [changes](hack_changes.md) · [tools](hack_tools.md) ·
[art pipeline](hack_art_pipeline.md) · [trainers](hack_trainers.md) · [resources](hack_resources.md) ·
[playtest guide](playtest_guide.md) · [feedback](hack_feedback.md)

## Where things stand
**v1** (all seven phases, commit 94f937d3) was handed to the playtester. **Round 1** brought the full story
add-on ([hack_story.md](hack_story.md)) and a fourth rival, Nerine; the checklist is in
[hack_feedback.md](hack_feedback.md) and the round's decisions are D-100 onwards. Build: `make` (debug, R + Start
menu) → `pokeemerald.gba`, `make release` → `pokeemerald-release.gba`; zipped ROMs for the playtester go to
`dist/` (gitignored).

## Round 1 – v2 story (in progress)
- [x] Docs: story saved, feedback checklist, superseded decisions marked, v2 decisions (D-100–D-116)
- [x] Quick fixes: dragon lines evolve at 25/50 (D-107), every Mega checked, player sprite audit (never Brendan/May)
- [x] Core: reputation var, outfit timeline, variant trainers (D-101), Nerine + Aster leftover egg
- [x] Story teams: Nerine (75), Aster (12), Brendan (7), May (5), Steven / Maxie / Archie; partners Tabitha,
      May, Brendan, Nerine ×9 – rival trainer ids renamed to the round 1 schedule
- [x] Act 1: village without Mom (prologue, Aster, Elder's prophecy), Poochyena rescue, families (Birch/Brendan,
      Norman/May), Littleroot moms, Petalburg Woods (Nerine, Courtney, outpost cabin, uniform), Rustboro (Brendan,
      Tabitha's order, Birch's lines); v1 Route 104 Brendan and Route 119 Aster removed – emulator-tested
      (`woods.play`, `rustboro.play`, matrix 18/18)
- [x] Act 4 part: Petalburg Gym – Norman is May's father, uniform lines, May watches the battle (tested by hand)
- [ ] Act 2: Rusturf goods choice, Steven, Slateport museum, Route 110 May (PokéNav), Mauville Wally
- [ ] Act 3–5: Meteor Falls, Mt. Chimney sabotage, Jagged Pass Mega Ring, Lavaridge, Weather Institute, Mt. Pyre,
      Magma Hideout promotion, Aqua Hideout, Mossdeep reversed tag battle, Seafloor reveal, Sootopolis turn,
      Rayquaza calling, aftermath (v1 scenes still in place there: cable car disguise, Slateport May, Sootopolis
      Megas, Elder's Mega Ring)
- [ ] Act 6–7: Hall of Fame → meteor alert → Sky Pillar finale (double, Rayquaza catch, Deoxys, Mega Rayquaza),
      credits, post-game (the Elder brings the SS Ticket)
- [~] Reputation dialogue (shared NPCs, key NPCs, townsfolk) + `docs/hack_script.md` (agent working)
- [~] Art: Nerine (Aqua disguise + true outfit), Courtney, back pics (agent working); tamer scarf (1.14)
- [ ] Trainers from real ORAS rematch data (Serebii), Elite Four post-game rematches
- [ ] Verification (matrix incl. Nerine/Aster variants, story checks, per-act debug warps) + v2 ROM

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
- [x] Credits: the player runs in their own sprite (D-049); the opening movie keeps Brendan/May (no player yet)
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
- [x] Rival houses in Littleroot belong to Brendan's and May's families; remaining gender branches (Oldale,
      Lavaridge, Champion's room, lab post-game) always use May; Hall of Fame respawns in the Draconid bedroom;
      SS Ticket / Lati TV scene plays in the Draconid house (`postgame_home.play`); scenes that drew the player as
      Brendan/May use the outfit sprite (Southern Island checked in the emulator)
- [x] Second starter after gym 1: Birch outside the Rustboro Gym, Charmander / Totodile / Treecko Lv 10
      (`second_starter.play`)
- [x] Aster arc: Meteor Falls, cable car, Route 119, Magma Hideout, Sky Pillar, post-game shrine (`aster.play`)
- [x] Magma disguise arc (cable car → Mt. Chimney, Magma Hideout) + Mega Ring and the second starter's Mega Stone
      from the Elder (`aster.play`)
- [x] Vanilla flow verification of every new scene (Phase 7 matrix); open: grunt lines that should notice the
      disguise `TODO(dialogue)`

## Phase 5 – Rival battles
- [x] Decouple Brendan & May from player gender (scenes, sprites, PokéNav)
- [x] 10-battle schedule (D-070) – new scenes in `data/scripts/draconid/rivals.pory`, teams in trainers.party;
      flow-tested in the emulator (`route104.play`, `rivals.play`; Space Center partner checked by hand)
- [x] Aster fights by egg: Meteor Falls / Route 119 / Sky Pillar / post-game (scenes in the Aster arc, Phase 4)
- [x] Wally extra fights (Petalburg Gym door, Lilycove; Mega Gallade)
- [x] Dialogue polish: reachable vanilla lines that assumed the player moved to Littleroot (Rustboro, Rydel)

## Phase 6 – Trainers / difficulty
- [x] Level caps (hard, per badge) + rematch tiers gated by badges – `make check` green
- [x] Rulebook `docs/hack_trainers.md`, segments (`tools/hack/trainers/segments.json`), trainer tools
- [x] Trainer overhaul merged: 798 trainers rewritten in 9 batches (362 Emerald rematch rosters, 436 enhanced own
      teams, **no ORAS rosters**), rematch tiers made consistent; `check_party.py` 0 errors (11 allowed early-evolved
      aces/bosses), `check_tiers.py` 0/0; table at the end of `docs/hack_trainers.md`; Roxanne's team checked in battle

## Phase 7 – Polish
- [x] Script/flag reachability checks: `tools/hack/check_story.py` (0 errors; 3 record-only flags); Route 119
      Aster moved onto a real chokepoint after an elevation-aware path search showed the old spot could be skipped
- [x] Both genders × 3 eggs × 3 second starters: `tools/hack/emu/matrix.py` – 18 combinations, 58 emulator runs
      (opening, Route 103/104, rivals, post-game home, second starter, Aster arc with opponent ids, Mega Stone,
      Draconid/Magma sprites) all pass on the Phase 6 ROM. It caught two bugs, both fixed: the first May battle
      could white out to the far-away Draconid bedroom (D-048), and early-rival battles fought a wild Zigzagoon
- [ ] Not automated: a full hand playthrough of the vanilla story between the new scenes (see the playtest guide)
- [x] `docs/playtest_guide.md`, `docs/hack_feedback.md`
- [x] Release build (`make release`) boots through the real menus into the Draconid bedroom (`release_boot.play`)
- [x] Final summary
