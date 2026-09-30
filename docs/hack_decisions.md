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
  connecting the village (north) to **Route 101's west edge** (pass rows 26–27 = Route 101 rows 4–5, the existing
  gaps in its tree line). – Alt: Littleroot's west edge (first version), or a warp from a cave. – *Changed after
  testing*: the game draws cells across a connection with the current map's tilesets, so Littleroot's houses
  (Petalburg tiles) came out as garbage next to the pass (Fallarbor tiles). Route 101's west strip uses only
  General tiles, and the offset keeps the Fallarbor highland out of view. The player now walks straight into the
  Birch rescue. `check_seams.py` guards against this for every new map.
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
- **D-038 Route 101 rescue**: entering Route 101 from the pass starts the rescue; Birch and the Zigzagoon run laps
  in the clearing by the entrance and the **hatchling fights the Zigzagoon** in the vanilla first-battle mode
  (Lv 2, no running), via a new special instead of `ChooseStarter`. Birch then warps the player to the lab as in
  vanilla. – Alt: keep the bag and let the player pick a vanilla starter. – The player already has a partner and
  gets a second starter after Gym 1 (brief).
- **D-039 Lab scene**: Brendan (5,4), Birch (6,4), May (7,4). Birch gives Brendan Treecko and May Torchic, the
  player gets the Pokédex **and 5 Poké Balls from Birch** (vanilla: from the rival after Route 103); May goes
  ahead to Route 103, Brendan heads west (sets up his Route 104 fight). No Oldale rival scene. – Alt: keep the
  vanilla "Pokédex after Route 103" loop. – Shorter, and no reason to withhold the Pokédex.
- **D-040 `{RIVAL}` = MAY**: vanilla expands `{RIVAL}` by player gender; almost every use means "Birch's kid", which
  is May here, so it is always MAY in Emerald. Scenes where the rival is Brendan name him directly.
- **D-041 Debug toggles**: the expansion's no-encounter / no-trainer-sight / no-collision toggles get real flags
  (0x2E–0x30) so they work in the debug menu and in emulator tests. The game never sets them.
- **D-042 Second starter**: after the Stone Badge, Prof. Birch waits outside the Rustboro Gym with Charmander,
  Totodile and Treecko (Lv 10, `SECOND_STARTER_LEVEL`); the pick goes to `VAR_SECOND_STARTER`. – Alt: at the lab
  (a long walk back), Lv 5. – Birch has business in Rustboro in vanilla too; Lv 10 is below the Stone Badge cap
  (20) and catches up in a route or two. All three have a Dragon-type Mega (Charizard X, Feraligatr, Sceptile),
  which fits the clan and gives the player a Mega since the dragon line has none (brief).
- **D-043 Aster's arc**: Draconid Pass (battle) → Meteor Falls after Magma takes the meteorite (riddle + battle)
  → Route 112 cable car (hands over the Magma disguise) → Route 119 on the path to Fortree, past the rival spot
  (a row of triggers every route crosses, checked with an elevation-aware path search; she heals the party
  first since Brendan's fight is a few steps back; battle, Mega Altaria) → Magma Hideout after Maxie (sends the player home) → Sky Pillar top before Rayquaza wakes (climax,
  Mega Salamence) → village shrine after the League (rematch). One var, `VAR_ASTER_STATE`, drives all of it.
  – Alt: Aster at Mt. Pyre / Sootopolis. – Follows the meteorite and Rayquaza threads, where Zinnia is in ORAS.
- **D-044 Magma disguise is a costume, not a stealth mode**: worn from the cable car to Maxie on Mt. Chimney and
  again inside the Magma Hideout (it goes back on at the entrance) until Maxie there; grunts still battle.
  – Alt: grunts ignore a disguised player. – Keeps the trainer fights and their EXP before Flannery and the
  Hideout; the outfit system shows it everywhere (sprites, trainer pics). Grunt lines that should notice the
  costume are `TODO(dialogue)`.
- **D-045 Mega Ring**: the Elder gives it in Draconid Village right after the Magma Hideout, with the Mega Stone
  for the second starter. – Alt: stones hidden in the world. – The brief's timing; one stone the player can use
  at once (the dragon has no Mega), more stones for the rest later.
- **D-046 Post-game home**: the SS Ticket / Lati TV scene plays in the Draconid house – Norman visits there, and
  the scene uses the vanilla Brendan-house movements for both genders (the house is a copy of that layout). The
  TV news code, the Hall of Fame respawn and the Littleroot fly spot follow the Draconid house; the Littleroot
  houses belong to Brendan's and May's families. – Alt: keep the scene in Littleroot. – The player never lived
  there.
- **D-047 Player stand-ins**: scenes that draw the player as an NPC (Frontier battle rooms, battle tents, contest
  hall, the Route 111 Mirage Tower fall, Southern Island) use the current outfit's sprite through the special
  `GetPlayerOutfitNormalGfx` instead of Brendan/May. – Alt: a fixed Draconid sprite. – Brendan/May are the
  rivals (brief), and the Magma outfit shows too while worn.
- **D-048 First May battle can't white out**: Route 103 uses the expansion's early-rival battle (as FRLG's first
  rival fight): a loss heals the party and the scene goes on with a different line. – Alt: vanilla (a loss
  whites out). – The respawn point is the Draconid bedroom, a long walk back; the emulator matrix lost this
  fight once with a mashed Lv 5 Jangmo-o, so it can happen to a new player too.
- **D-049 Credits**: the player runs in their own sprite (Draconid M/F run cycles derived from FRLG's credits
  Red/Leaf, like the rest of the player art) and May rides in on her bike, instead of Brendan or May standing in
  for the player. – Alt: draw a Draconid bike rider (no non-rival base with that pose); keep Brendan/May (the brief
  forbids their art for the player). – The on-foot sprite is taller than the riders, so it runs in a lane nearer
  the camera. The opening movie keeps Brendan and May: no player exists yet when it plays.
- **D-050 Player art base**: the four player sets are **derived from the FRLG Red/Leaf sprites** already in the
  repo (recoloured through their palette index roles, new head drawn from templates), and the Emerald-only states
  (Acro Bike, underwater, watering, decorating) are composed from those frames. – Alt: draw everything from scratch
  (weeks of pixel work to do well); base on Brendan/May (forbidden: they are the rivals); NPC sheets (walk frames
  only). – Red/Leaf are the only non-Brendan/May sets with bike/surf/fishing/field-move poses. The pipeline is
  scripted, so any frame can be hand-polished later without losing the rest (`TODO(art)` list in
  docs/hack_art_pipeline.md).
- **D-051 Player look**: black hair (spiky M, long F), teal headband with two ivory dragon horns, teal jacket, red
  accents. – Alt: Zinnia-style cloak. – Horns make the silhouette readable at 16×32 and tie in with the Draconid
  clan; teal/red stays distinct from Brendan (white/red/green), May (red/green) and Aster.
- **D-052 Magma disguise**: the grunt's red hood (with its two ear points) and charcoal uniform on the player's
  body; the front pic is the vanilla Magma Grunt pic (it is a disguise), the back pic is the player's with the hood.
  – Alt: a unique outfit. – Grunts must mistake the player for one of their own.
- **D-053 Outfit system**: built here (the expansion 1.17.1 has none): `VAR_PLAYER_OUTFIT` + `src/player_outfit.c`
  tables + `special SetPlayerOutfit`; all player gfx/pic lookups go through it, so it is saved with the game.
  Link partners in other games still appear as Brendan/May (their game's data).
- **D-054 Draconid NPCs**: recoloured vanilla NPCs on one shared palette (teal/red clan colours, black hair),
  the Elder with an ivory horned circlet like the player's. – Alt: new sprites per villager. – Consistent look,
  one palette slot for a whole village.
- **D-055 Aster's look**: maroon-black hair, crimson headband with **gold** horns, black top – a mirror of the
  player (teal, ivory horns). Front pic from Cooltrainer F's energetic pose (Zinnia-like). – Alt: a cloaked
  Lorekeeper design. – Reads as "the other Draconid" at a glance.
- **D-056 Aster's class and music**: new class **DRACONID**; battles use the rival theme (`MUS_VS_RIVAL`), encounter
  music is the "intense" theme. – Alt: new music. – No composing tools in the pipeline; these tracks fit a rival
  from a warrior clan. The Sky Pillar climax can switch to a bigger track by script later.
- **D-060 Level caps**: hard caps (`EXP_CAP_HARD`) from the badge list: 15, 20, 25, 30, 34, 38, 44, 48, 60 until
  the Champion, none after. Rare Candies respect the cap; Pokémon under the cap get extra EXP.
  – Alt: soft caps (reduced EXP), the expansion's defaults (15…58), a cap var. – Hard caps make the "every trainer
  is a rematch team" difficulty fair: trainer levels can be tuned knowing exactly how strong the player can be.
  The numbers leave each gym leader's ace at the cap. The tests build keeps caps off (vanilla EXP tests).
- **D-061 Trainer segments**: each trainer is placed in the earliest segment (between two badges) the player can
  reach it in, per trainer where maps are split by Surf, the desert, Waterfall or Rock Smash; Trick House puzzles
  follow their badge gates; the S.S. Tidal is post-game. – Alt: vanilla map order only. – A trainer's levels then
  never exceed the cap in force. Table: `tools/hack/trainers/segments.json`.
- **D-062 Rematch tiers need badges**: tier 2/3/4 need 5/6/7 badges, the last tier the game cleared
  (`OW_REMATCH_TIER_BADGES`). – Alt: vanilla (all tiers after 5 badges). – Otherwise a tier-5 team could be met
  under the Balance Badge cap.
- **D-063 Where teams come from**: trainers with Emerald rematch tiers use their Emerald rematch roster for every
  tier (so tiers written separately stay one trainer); others use their ORAS rematch team when known with
  confidence, otherwise their own team made fuller. No ORAS data files are in the repo, so every team goes through
  `check_party.py` (moves, abilities, evolution levels, caps). – Alt: ORAS for everyone. – Reproducible and
  checkable; the brief's "Emerald rematch if none". **Outcome**: no batch could vouch for an ORAS roster, so none
  is used – 362 trainers have their Emerald rematch roster, 436 an enhanced own team (`sources.json`); real ORAS
  rosters can replace blocks later through the same checks.
- **D-064 AI**: route trainers `Basic Trainer` (+ `Smart Mon Choices` from S4), gym trainers `Basic Trainer /
  Smart Mon Choices`, bosses and rivals `Smart Trainer / Ace Pokemon`, Elite Four / Champion / post-game bosses
  `+ Prediction`. – Alt: Smart Trainer everywhere. – Bosses feel smart; route trainers stay quick to play.
- **D-065 Species pool**: Hoenn Pokédex (with cross-gen evolutions) + every species a vanilla Emerald trainer uses;
  Deino/Dreepy/Jangmo-o lines only for the player and Aster; no legendaries. – Alt: any species. – Keeps Hoenn's
  feel and the player's dragon special.
- **D-066 Trainer Megas**: Maxie (Magma Hideout, Camerupt), Archie (Seafloor Cavern, Sharpedo) as in ORAS,
  Steven (Metagross), gym leaders' last rematch tier, and the story trainers late. – Alt: Megas for all bosses.
  – Megas stay special; the ORAS villains' Megas are canon.
- **D-037 Trainer ID capacity**: `MAX_TRAINERS_COUNT` is 864 and vanilla uses 855, so only 9 new IDs fit.
  Aster's first fight uses 3 (one per egg). **Phase 5 (done)**: the 30 vanilla rival ids (3 starters × Brendan/May ×
  Routes 103/110/119, Rustboro, Lilycove) are renamed in place for the 28 Draconid story battles; 2 are spare and
  858–863 stay free. – Alt: raise `MAX_TRAINERS_COUNT` (costs save space). – Same numbers, so trainer flags and
  save data layout don't move.
- **D-070 Rival schedule**: Route 103 May → Route 104 Brendan (Petalburg Woods entrance) → Rustboro May → Slateport
  May (after the museum; the brief's "Slateport/Mauville") → Route 110 Brendan → Route 119 Brendan → Lilycove both
  (two-on-two) → Space Center tag with the rival of the player's choice → Sootopolis both with Megas (right after the
  Rain Badge, before Victory Road) → post-game in the lab: a single with each, then a double. Brendan's ace is
  Sceptile, May's Blaziken; their teams don't depend on the player's egg. – Alt: Megas only post-game. – The brief's
  list; Sootopolis after Juan is the first moment both Key Stones make sense (Birch sends them).
- **D-071 Who the rival is in vanilla scenes**: `{RIVAL}` and the common rival sprite are May; Rustboro/Route 104 and
  Lavaridge are May's, Routes 110/119 Brendan's; both register in the PokéNav (May in Rustboro, Brendan after
  Route 110). – Alt: keep the player-gender switch. – Brendan and May are separate characters now (D-031).
- **D-072 Space Center partner**: Steven stays and leads the scene; May and Brendan come to help and the player picks
  one (YES = May, NO = Brendan) as the multi-battle partner. – Alt: replace Steven. – Keeps Steven's Dive/house
  follow-up untouched while making it a rival tag battle.
- **D-073 Wally**: vanilla Mauville and Victory Road, plus Petalburg Gym door (after the Heat Badge, before Norman)
  and Lilycove (Mega Gallade). His Ralts line becomes **Gallade** (ORAS Wally), Mega from Lilycove on. – Alt: Mega
  Gardevoir. – ORAS canon; one Ralts can't be both.
- **D-074 Test hooks**: debug builds get `gDraconidTestWarp` (warp/heal on request) so emulator tests can reach any
  scene; release builds compile it out. Flow tests set `FLAG_DRACONID_NO_WHITEOUT` so a mashed battle doesn't end
  the script. – Alt: walking every route in tests (fragile: NPCs block paths).
