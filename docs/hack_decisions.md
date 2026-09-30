# Draconid Emerald – design decisions

Every open choice made without asking, so it can be overruled later.
Format: **decision** – alternatives considered – why. Newest feedback always wins;
when a playtest note overrides something here, the entry is updated and marked.

## Project / tooling

- **D-001 Base version**: pokeemerald-expansion 1.17.1 (`master` @ dfb0f843), working branch `draconid-emerald`.
  – Alt: `upcoming`. – `master` is the stable, released line; fewer surprises while building a whole game.
- **D-002 Toolchain**: Ubuntu's `gcc-arm-none-eabi` 13.2 instead of devkitARM.
  – Alt: devkitARM. – INSTALL.md's documented Ubuntu path; no extra downloads; `make` + `make check` pass.
- **D-003 Poryscript output is committed**: `*.pory` → `*.inc` via `poryscript_rules.mk`; the generated `.inc` is committed.
  – Alt: gitignore the `.inc` and require Poryscript for every build. – The ROM still builds on a machine
  without Poryscript; the rule refuses to build if a `.pory` is newer than its `.inc` and the tool is missing,
  so stale scripts can't slip through. Line markers are off (`-lm=false`) to keep the committed files clean.
- **D-004 Porytiles 2.0 from source with clang + libc++**: GCC < 15's libstdc++ lacks C++23
  `vector::append_range`, used 142× in Porytiles 2.0. Built with clang 18 + libc++ 18.
  The binary is not committed (`tools/hack/install_tools.sh --porytiles` rebuilds it).
  – Alt: legacy Porytiles 0.x (`porytiles-legacy`). – 2.0 is current and supports expansion directly.
- **D-005 Debug menu**: kept the expansion default `DEBUG_OVERWORLD_MENU = DISABLED_ON_RELEASE`
  (on for `make`, off for `make release`). Open it with **R + Start** in the overworld.
  – Alt: start-menu entry (`DEBUG_OVERWORLD_IN_MENU`). – Default key combo doesn't change the start menu.
- **D-006 Porymap config**: `porymap.*.cfg` stay gitignored (per-user). `tools/hack/porymap_scripts/register.py`
  writes `custom_scripts` into `porymap.user.cfg` and `use_poryscript=1` into `porymap.project.cfg`.

## Megas

- **D-010 All required Megas already exist in 1.17.1**: Charizard-Mega-X, Sceptile, Blaziken, Altaria,
  Salamence, Gallade, Gardevoir and **Feraligatr-Mega (Legends: Z-A, `SPECIES_FERALIGATR_MEGA` = 1529)**.
  No Mega data had to be added; Hydreigon, Dragapult and Kommo-o have no Megas in the expansion and none were
  invented. (Data source: the expansion's own species data.)

## World

- **D-020 Village tilesets**: General + Fallarbor (brown cliffs, waterfalls, rustic houses, pines – the
  Route 114 / Fallarbor look). – Alt: General + Lavaridge (hot springs), General + Fortree. – Best "mountain
  village" feel with existing art; custom Porytiles tiles (shrine, statues, meteorites) come on top later.
- **D-021 Village layout**: 40×30 village under a cliff (plateau lip y=2, cliff y=3–5) with a waterfall and pond
  to the east, the Rayquaza shrine as a cave mouth in the cliff face, a meteorite crater below it, four houses
  (player, Elder, two villagers) and a single south exit guarded by a gatekeeper. – Alt: village on a plateau
  reached by stairs. – One exit keeps the opening linear; the cliff shrine reads as "above the village".
- **D-022 Draconid Pass**: a new 28×36 route (brown highland → river with a Route 114-style bridge → green valley)
  connecting the village (north) to **Littleroot's west edge**. – Alt: connect to Route 101's west edge, or warp
  from a cave. – Littleroot has no west connection in vanilla, so nothing is displaced; the player reaches Birch's
  town first, as the brief asks.
- **D-023 Interiors reuse vanilla layouts**: player house = copy of Brendan's house (1F/2F), Elder's house = copy of
  the Fossil Maniac's house (doorway walled off), shrine = copy of the Sealed Chamber inner room, two villager homes
  reuse `LAYOUT_HOUSE1/2`. – Alt: new tilesets now. – Works today with correct collision; custom Porytiles art
  (statue, relics) is a later `TODO(art)` pass.

## Story

- **D-030 Player family**: Norman stays the player's Dad (Petalburg Gym is unchanged); Mom lives with the player in
  Draconid Village. – Alt: a Draconid father figure. – Keeps the vanilla Petalburg/Norman beats working untouched.
- **D-031 Rival families**: **May is Prof. Birch's daughter; Brendan is Birch's nephew** living next door in
  Littleroot. – Alt: both Birch's children (twins). – Both rivals decoupled from the player's gender, both
  plausibly in the lab; the two Littleroot houses still have owners.
- **D-032 Opening order**: bedroom (Mom, wall clock) → Elder's egg ceremony → shrine hatching rite → Mom gives the
  Running Shoes → first Aster battle on the pass → Littleroot → Route 101 rescue with the hatchling → lab: Birch
  gives Brendan Treecko and May Torchic, **the player gets the Pokédex right away** → Route 103 May. – Alt: keep
  the vanilla "Pokédex after Route 103". – The player already has a partner, so the Pokédex is the natural gift;
  it also removes the vanilla Route 103 sequence break.
- **D-033 Egg choice storage**: `VAR_STARTER_MON` holds the egg (`DRACONID_EGG_*`: 0 Deino, 1 Dreepy, 2 Jangmo-o)
  and `sStarterMon` in `src/starter_choose.c` lists the three egg species. – Alt: a new var. – Every vanilla reader
  (`IsStarterInParty`, credits, Game Corner doll) keeps working and gets the right species; rival battle switches
  on `VAR_STARTER_MON` are rewritten in Phase 5 anyway.
- **D-034 Hatching**: the egg hatches at the shrine during a rite (normal `EggHatch` animation), then a special
  raises it to **Lv 5** with its level-up moves. – Alt: hatch at Lv 1 / hatch by walking. – The brief says "hatches
  early"; Lv 1 would lose to the Route 101 Zigzagoon and the first Aster fight.
- **D-035 Aster**: female, the Elder's granddaughter, same age as the player; her egg counter-picks the player's
  (Deino→Jangmo-o, Dreepy→Deino, Jangmo-o→Dreepy, stored in `VAR_ASTER_EGG`). First battle on Draconid Pass is
  **no-whiteout** (`B_FLAG_NO_WHITEOUT` → `FLAG_DRACONID_NO_WHITEOUT`) and heals afterwards. – Alt: a losable
  battle with a separate script path. – One script path, no softlock, no free money loss on turn 1 of the game.
- **D-036 Placeholder sprites**: until Phase 3 art lands, Elder = `OBJ_EVENT_GFX_OLD_MAN`, Aster = `WOMAN_3`,
  Aster's trainer pic = Cooltrainer F, eggs = item balls, Rayquaza statue = `RAYQUAZA_STILL`. All marked `TODO(art)`.
- **D-037 Trainer ID capacity**: `MAX_TRAINERS_COUNT` is 864 and vanilla uses 855, so only 9 new IDs fit.
  Aster's first fight uses 3 (one per egg). Plan for Phase 5: reuse the unused/duplicated rival IDs where the
  vanilla game has them, then raise `MAX_TRAINERS_COUNT` together with the trainer-flag space (saveblock
  `FREE_*` options) when that runs out. – Decided when Phase 5 starts; recorded here so nobody burns the last IDs.
