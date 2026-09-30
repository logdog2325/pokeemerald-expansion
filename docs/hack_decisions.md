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

- **D-010 All required Megas already exist in 1.17.1** (re-checked in round 1: Charizard X, Sceptile, Blaziken, Feraligatr, Altaria, Salamence, Gallade, Gardevoir, Camerupt, Sharpedo, Metagross, Rayquaza, Latios, Latias all have form species, form-change entries and sprites; Mega Feraligatr is the expansion's Legends: Z-A data – Water/Dragon, 85/160/125/89/93/78, Dragonize – with its own front/back pics): Charizard-Mega-X, Sceptile, Blaziken, Altaria,
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

- **D-030 Player family** *(superseded by D-100, round 1)*: Norman stays the player's Dad (Petalburg Gym is unchanged); Mom lives with the player in
  Draconid Village. – Alt: a Draconid father figure. – Keeps the vanilla Petalburg/Norman beats working untouched.
- **D-031 Rival families** *(superseded by D-100, round 1)*: **May is Prof. Birch's daughter; Brendan is Birch's nephew** living next door in
  Littleroot. – Alt: both Birch's children (twins). – Both rivals decoupled from the player's gender, both
  plausibly in the lab; the two Littleroot houses still have owners.
- **D-032 Opening order** *(superseded by D-102, round 1)*: bedroom (Mom, wall clock) → Elder's egg ceremony → shrine hatching rite → Mom gives the
  Running Shoes → first Aster battle on the pass → Littleroot → Route 101 rescue with the hatchling → lab: Birch
  gives Brendan Treecko and May Torchic, **the player gets the Pokédex right away** → Route 103 May. – Alt: keep
  the vanilla "Pokédex after Route 103". – The player already has a partner, so the Pokédex is the natural gift;
  it also removes the vanilla Route 103 sequence break.
- **D-033 Egg choice storage**: `VAR_STARTER_MON` holds the egg (`DRACONID_EGG_*`: 0 Deino, 1 Dreepy, 2 Jangmo-o)
  and `sStarterMon` in `src/starter_choose.c` lists the three egg species. – Alt: a new var. – Every vanilla reader
  (`IsStarterInParty`, credits, Game Corner doll) keeps working and gets the right species; rival battle switches
  on `VAR_STARTER_MON` are rewritten in Phase 5 anyway.
- **D-034 Hatching** *(the rite superseded by D-231, round 1; the Lv 5 raise stays)*: the egg hatches at the shrine during a rite (normal `EggHatch` animation), then a special
  raises it to **Lv 5** with its level-up moves. – Alt: hatch at Lv 1 / hatch by walking. – The brief says "hatches
  early"; Lv 1 would lose to the Route 101 Zigzagoon and the first Aster fight.
- **D-035 Aster** *(egg and role superseded by D-105, round 1)*: female, the Elder's granddaughter, same age as the player; her egg counter-picks the player's
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
- **D-040 `{RIVAL}` = MAY** *(superseded by D-100: `{RIVAL}` = BRENDAN, round 1)*: vanilla expands `{RIVAL}` by player gender; almost every use means "Birch's kid", which
  is May here, so it is always MAY in Emerald. Scenes where the rival is Brendan name him directly.
- **D-041 Debug toggles**: the expansion's no-encounter / no-trainer-sight / no-collision toggles get real flags
  (0x2E–0x30) so they work in the debug menu and in emulator tests. The game never sets them.
- **D-042 Second starter** *(Birch superseded by Prof. Oak, D-233, round 1)*: after the Stone Badge, Prof. Birch waits outside the Rustboro Gym with Charmander,
  Totodile and Treecko (Lv 10, `SECOND_STARTER_LEVEL`); the pick goes to `VAR_SECOND_STARTER`. – Alt: at the lab
  (a long walk back), Lv 5. – Birch has business in Rustboro in vanilla too; Lv 10 is below the Stone Badge cap
  (20) and catches up in a route or two. All three have a Dragon-type Mega (Charizard X, Feraligatr, Sceptile),
  which fits the clan and gives the player a Mega since the dragon line has none (brief).
- **D-043 Aster's arc** *(superseded by D-105, round 1)*: Draconid Pass (battle) → Meteor Falls after Magma takes the meteorite (riddle + battle)
  → Route 112 cable car (hands over the Magma disguise) → Route 119 on the path to Fortree, past the rival spot
  (a row of triggers every route crosses, checked with an elevation-aware path search; she heals the party
  first since Brendan's fight is a few steps back; battle, Mega Altaria) → Magma Hideout after Maxie (sends the player home) → Sky Pillar top before Rayquaza wakes (climax,
  Mega Salamence) → village shrine after the League (rematch). One var, `VAR_ASTER_STATE`, drives all of it.
  – Alt: Aster at Mt. Pyre / Sootopolis. – Follows the meteorite and Rayquaza threads, where Zinnia is in ORAS.
- **D-044 Magma disguise is a costume, not a stealth mode** *(superseded by D-103, round 1)*: worn from the cable car to Maxie on Mt. Chimney and
  again inside the Magma Hideout (it goes back on at the entrance) until Maxie there; grunts still battle.
  – Alt: grunts ignore a disguised player. – Keeps the trainer fights and their EXP before Flannery and the
  Hideout; the outfit system shows it everywhere (sprites, trainer pics). Grunt lines that should notice the
  costume are `TODO(dialogue)`.
- **D-045 Mega Ring** *(superseded by D-105, round 1)*: the Elder gives it in Draconid Village right after the Magma Hideout, with the Mega Stone
  for the second starter. – Alt: stones hidden in the world. – The brief's timing; one stone the player can use
  at once (the dragon has no Mega), more stones for the rest later.
- **D-046 Post-game home** *(superseded by D-112, round 1)*: the SS Ticket / Lati TV scene plays in the Draconid house – Norman visits there, and
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
- **D-065 Species pool** *(extended by D-195, round 1)*: Hoenn Pokédex (with cross-gen evolutions) + every species a vanilla Emerald trainer uses;
  Deino/Dreepy/Jangmo-o lines only for the player and Aster; no legendaries. – Alt: any species. – Keeps Hoenn's
  feel and the player's dragon special.
- **D-066 Trainer Megas**: Maxie (Magma Hideout, Camerupt), Archie (Seafloor Cavern, Sharpedo) as in ORAS,
  Steven (Metagross), gym leaders' last rematch tier, and the story trainers late. – Alt: Megas for all bosses.
  – Megas stay special; the ORAS villains' Megas are canon.
- **D-037 Trainer ID capacity** *(raised in D-101, round 1)*: `MAX_TRAINERS_COUNT` is 864 and vanilla uses 855, so only 9 new IDs fit.
  Aster's first fight uses 3 (one per egg). **Phase 5 (done)**: the 30 vanilla rival ids (3 starters × Brendan/May ×
  Routes 103/110/119, Rustboro, Lilycove) are renamed in place for the 28 Draconid story battles; 2 are spare and
  858–863 stay free. – Alt: raise `MAX_TRAINERS_COUNT` (costs save space). – Same numbers, so trainer flags and
  save data layout don't move.
- **D-070 Rival schedule** *(superseded by D-106, round 1)*: Route 103 May → Route 104 Brendan (Petalburg Woods entrance) → Rustboro May → Slateport
  May (after the museum; the brief's "Slateport/Mauville") → Route 110 Brendan → Route 119 Brendan → Lilycove both
  (two-on-two) → Space Center tag with the rival of the player's choice → Sootopolis both with Megas (right after the
  Rain Badge, before Victory Road) → post-game in the lab: a single with each, then a double. Brendan's ace is
  Sceptile, May's Blaziken; their teams don't depend on the player's egg. – Alt: Megas only post-game. – The brief's
  list; Sootopolis after Juan is the first moment both Key Stones make sense (Birch sends them).
- **D-071 Who the rival is in vanilla scenes** *(superseded by D-100, round 1)*: `{RIVAL}` and the common rival sprite are May; Rustboro/Route 104 and
  Lavaridge are May's, Routes 110/119 Brendan's; both register in the PokéNav (May in Rustboro, Brendan after
  Route 110). – Alt: keep the player-gender switch. – Brendan and May are separate characters now (D-031).
- **D-072 Space Center partner** *(superseded by D-108, round 1)*: Steven stays and leads the scene; May and Brendan come to help and the player picks
  one (YES = May, NO = Brendan) as the multi-battle partner. – Alt: replace Steven. – Keeps Steven's Dive/house
  follow-up untouched while making it a rival tag battle.
- **D-073 Wally**: vanilla Mauville and Victory Road, plus Petalburg Gym door (after the Heat Badge, before Norman)
  and Lilycove (Mega Gallade). His Ralts line becomes **Gallade** (ORAS Wally), Mega from Lilycove on. – Alt: Mega
  Gardevoir. – ORAS canon; one Ralts can't be both.
- **D-074 Test hooks**: debug builds get `gDraconidTestWarp` (warp/heal on request) so emulator tests can reach any
  scene; release builds compile it out. Flow tests set `FLAG_DRACONID_NO_WHITEOUT` so a mashed battle doesn't end
  the script. – Alt: walking every route in tests (fragile: NPCs block paths).

## Round 1 (story add-on, `docs/hack_story.md`)
The playtester's story add-on is the source of truth; these fill its gaps and record what it overturned.

- **D-100 Families and `{RIVAL}`**: the player has no family in the village (Mom is gone, the Elder and the clan
  raise the young); **Brendan is Prof. Birch's son, May is Norman's daughter** (the family moved to Littleroot
  from Johto), so Norman's Petalburg scenes speak of May, not the player. `{RIVAL}` now expands to **BRENDAN**
  (Birch's son, which is what vanilla's `{RIVAL}` means); scenes about May name her. – Alt: keep D-030/D-031.
  – The add-on's cast list.
- **D-101 Variant trainers**: a fight that depends on the player's choices has one **base trainer id** in the
  script; `Draconid_ResolveVariantTrainer` remaps it when the battle loads to base + variant (egg: 3 variants;
  egg × second starter: 9). `MAX_TRAINERS_COUNT` is raised so the variants fit (a few save bytes: trainer flags).
  – Alt: 9-way branches in every script; party pools. – One script line per fight and one table to check.
- **D-102 Opening (Act 1)** *(the ceremony and the hatch superseded by D-230/D-231, round 1)*: night prologue (a falling star, screen flash) → the player wakes in their own house
  (Aster at the door: the Elder calls) → wall clock → egg ceremony with the prophecy and the mission → hatching rite
  → a villager gives the Running Shoes → **Aster's tutorial battle** on Draconid Pass → Route 101. – Alt: the
  Elder wakes the player. – Keeps the tested egg/hatch flow; Aster is there from the first minute.
- **D-103 Life in the uniform**: the reputation var (`VAR_DRACONID_REPUTATION`: 0 `pre_uniform`, 1 `uniform`,
  2 `revealed`) drives NPC lines; the outfit var follows it (tamer → Magma at Petalburg Woods → tamer at the
  Sootopolis turn). **Magma grunts who were trainers stay trainers**, with new lines: they test the new
  recruit ("show me what the boss sees in you") – Aqua is the team the player fights for real. – Alt: turn
  Magma grunts into non-battlers. – Keeps the EXP curve the caps were tuned for, and fits the story.
- **D-104 Nerine's teams**: counter-egg dragon (Deino→Jangmo-o, Dreepy→Deino, Jangmo-o→Dreepy) from fight 1;
  the counter Mega starter (Charmander→Totodile, Totodile→Treecko, Treecko→Charmander) from fight 2 (Rusturf, the
  first fight after the second starter); Water/Dark "Aqua cover" members until the reveal, dragons after
  (Kingdra, Flygon, Dragalge); her starter Mega Evolves from the Seafloor reveal on. 3 + 8 × 9 = 75 teams.
- **D-105 Aster (round 1)**: the Elder's apprentice (no longer his granddaughter); raises the **leftover egg**
  (neither the player's nor Nerine's), so all three dragon lines appear. Appearances: tutorial battle on Draconid
  Pass, battle deep in Meteor Falls, the **Mega Ring at Jagged Pass** (made from the meteorite fragment; no
  battle), the Rayquaza calling at Sky Pillar with Nerine (scene), the Sky Pillar finale double battle, post-game.
  The second starter's Mega Stone is a Draconid gift in Lavaridge.
- **D-106 Rival schedule (round 1)** *(more battles: D-234; the Latis: D-237)*: May – Route 103, Route 110, Lilycove (double), Sootopolis partner option,
  post-game; Brendan – Rustboro city edge, Mt. Chimney (not a must-win), Route 119, Lilycove (double), Mossdeep
  with Steven (not a must-win), Sootopolis partner option, post-game. Teams from the round 1 notes: Brendan
  Sceptile / Mightyena / Swellow / Slaking / Magcargo / Latios, May Blaziken / Beautifly / Wailord / Tropius /
  Delcatty / Latias, gaining members at the points the ORAS rival does; each Lati joins after the Balance Badge
  (when ORAS hands out the Eon Flute); Megas from Mossdeep (Brendan) and the post-game. After every loss they
  react to the uniform and walk off.
- **D-107 Dragon evolutions**: Deino, Dreepy and Jangmo-o lines evolve at **25 and 50** (Deino 50/64, Dreepy 50/60,
  Jangmo-o 35/45 before), for every trainer too. The second starters keep their own levels (Charmander 16/36,
  Totodile 18/30, Treecko 16/36). – Alt: all starters at 25/50. – The note is about the dragons evolving too late.
- **D-108 Mossdeep Space Center**: Tabitha leads the raid; **the player + Tabitha vs Steven + Brendan**, can't
  white out and the scene goes on whoever wins (Magma never gets the fuel). Steven is overlevelled (his ace above
  the cap, as the Champion he is). – The round 1 note.
- **D-109 Sky Pillar before the League**: the player does not climb it in Act 5; Aster and Nerine call Rayquaza
  there in a scene, and the tower stays closed until the post-League finale. – Alt: vanilla climb. – The add-on.
- **D-110 Must-catch Rayquaza and the Deoxys boss**: no running; if Rayquaza faints, or the player loses to Deoxys,
  a line and the battle again (no whiteout). Rayquaza learns Dragon Ascent from the Elder (Mega Evolution needs it).
- **D-111 Deoxys later**: catchable in the post-game at the Sky Pillar summit (where it fell), once. – Alt: Birth
  Island (needs an event ticket). – Reachable in a normal save.
- **D-112 Post-game start**: credits roll after the finale; the player wakes at home in the village, where the
  Elder brings the SS Ticket (sent by Captain Stern) and the Lati TV news airs. – Alt: Norman (now May's father).
- **D-113 Magma outpost cabin**: a small cutscene map (`PetalburgWoods_MagmaOutpost`, a copy of the Fossil
  Maniac's house with the tunnel walled up) reached by a fade after Courtney's offer; Courtney and two grunts are
  inside, the uniform goes on there, and the door leads out to Route 104 at the woods' north entrance. It can't
  be visited again. – Alt: a cabin building at the woods' edge on Route 104 (new exterior tiles, seam rules). – The
  add-on asks for a small cutscene map; no new exterior art needed.
- **D-114 Recruitment without a YES/NO**: the player remembers the Elder's words and nods. – Alt: a YES/NO that
  loops until YES. – The Elder ordered it; a refusal the game can't honour would be a fake choice.
- **D-115 Rustboro, Act 1**: Brendan uses the vanilla rival object and triggers on row 53 (the only way in from the
  woods), now on `VAR_BRENDAN_STATE`; the vanilla May registration in Rustboro / at Briney's cottage is skipped
  (May registers on Route 110, D-106). After the Stone Badge **Tabitha gives the order first, then Birch**
  (Prof. Oak since D-233), who saw them talking. Tabitha's overworld sprite is the Magma grunt, as in vanilla.
  – Alt: Brendan inside the city.
- **D-116 May at the Norman battle**: she stands by the mat whenever the gym is open to the fourth-badge
  challenge (talkable), speaks her line after the badge and leaves before Wally's father comes in. – The add-on.
- **D-117 Reputation dialogue**: who reacts to `VAR_DRACONID_REPUTATION` and how (lines in
  [reputation_dialogue.md](reputation_dialogue.md)). **Townsfolk** (3–5 per town, 2 in Ever Grande, which has no
  more): ordinary people with idle lines; not the ones whose lines follow story state that the story rework owns
  (Sootopolis crisis residents outside, Slateport's Stern interview, Lilycove's Team Aqua lines, Wally, Scott), so
  Sootopolis uses the people in its houses. Their object's `script` in `map.json` points at the new script, which
  goes to the vanilla one in pre-uniform. **Services never refuse**: the nurse heals, clerks sell, the Cable Club
  links and the Day Care raises – only the words around them change (a hook line in the vanilla script). Some
  townsfolk turn their back after a uniform line. **Gyms** (not Petalburg: Norman is the story's): Leader intro +
  post-battle line and the Gym Guide; badges, TMs and rematches stay vanilla. **Unreachable combinations keep
  vanilla** instead of new text: a Leader's intro after the reveal when the badge is required before it (all but
  Winona and Juan), Juan's gym and Ever Grande in uniform, Mr. Briney on the S.S. Tidal in uniform. – Alt: a flag
  per NPC so the apology plays once; refusing service in uniform; hooks in every town's `scripts.inc`. – The
  services are the player's lifeline, a repeated line is how vanilla NPCs work, and redirecting the object keeps
  the vanilla scripts (which the story rework edits) untouched.
- **D-118 The Devon Goods choice** (Rusturf Tunnel, after Nerine): "Return to DEVON" or "Keep for MAGMA"
  (`FLAG_DEVON_GOODS_RETURNED`). Both continue the same way, as the add-on asks: the Devon employee catches the
  player outside Devon either way (the "keep" path gets a line about it) and Mr. Stone sends them on; Tabitha's
  museum order reacts to the flag (Magma wants Stern's submarine tracked, so the parts get delivered anyway).
  – Alt: a YES/NO; skipping Mr. Stone on the "keep" path (would cut the PokéNav and the letter).
- **D-119 Act 2 staging**: Tabitha gives the order in person twice – out of the Rustboro Gym right after the
  theft, and past the Oceanic Museum ticket counter (he stays there, "watching" Aqua, until the raid ends).
  Nerine is the Rustboro thief, the Rusturf "grunt" (she lets Peeko go unharmed) and the **second** museum
  battle (the first is still a plain grunt, so she can say "Stand aside"). May's Route 110 battle is the vanilla
  rival scene with her lines, and she registers in the PokéNav there (the vanilla Rustboro registration is
  skipped, D-115); Brendan registers on Route 119 (Act 4). – Alt: a Magma messenger grunt.
- **D-120 Meteor Falls staging (Act 3)**: Maxie stands with the two grunts over Cozmo (a new object sharing their
  hide flag), comes up onto the stairs to meet the player in person (his PokéNav call sent them there) and gives
  them a shard of the meteorite (D-121); Aqua comes in from the west, Maxie orders "hold the stairs", the player
  steps aside for Magma and back into the way, and Archie **backs down without a battle** ("a brawl on these
  stairs costs more time than we've got") and leaves west, the long way round. Then Aster walks up from deeper in
  the Falls (the lower level, west) for her battle. – Alt: an Aqua grunt battle to cover the retreat (no Aqua grunt
  trainer belongs to Meteor Falls or Mt. Chimney, and the unused vanilla ones are Lv 9–18); Aster waiting further
  in (a detour off the way to Route 112, so missable). – The stairs are the only way east, so standing on them is
  covering the retreat, and Aster's battle stays the scene's one fight.
- **D-121 The Mega Ring's stone**: Maxie's shard – a chip of Cozmo's meteorite, "every great work begins with a
  small stone" – goes to the Elder with Aster after Meteor Falls, and comes back set in the Mega Ring at Jagged
  Pass. The meteorite itself still comes out of the machine at Mt. Chimney (`ITEM_METEORITE`, Cozmo's TM as in
  vanilla). – Alt: a fragment of the meteorite pulled at Mt. Chimney (Aster meets the player minutes later: no
  time for the Elder to make a ring). – Keeps the story's order believable, and Maxie's gift becomes the key to the
  player's Megas, which the betrayal makes cost him more.
- **D-122 Aster's Meteor Falls battle can be lost**: `trainerbattle_earlyrival` with `RIVAL_BATTLE_HEAL_AFTER` (as
  May's Route 103 battle, D-048); her lines follow the result. – Alt: must-win (v1; a whiteout after Magma and Aqua
  have left would strand the scene's state). – One unbroken scene, and Aster tests the player rather than blocks them.
- **D-123 Mt. Chimney staging**: one scene from talking to Maxie at his machine: Tabitha comes up for her order
  and goes down the path (she no longer battles; her object is no longer a trainer), the player walks to (10, 10),
  the only way up to the crater, Nerine and then Brendan come up, the mountain rumbles, Maxie turns his back on the
  machine to watch the smoke and the player pulls the meteorite; he blames Aqua, and in a fade Magma and Aqua leave.
  The flags the vanilla Maxie battle set come from this scene (Jagged Pass, Lavaridge's trainers, Cozmo, the cookie
  lady). Nerine's battle is a must-win, like her others: nothing is set before it, so a whiteout replays the scene
  from Maxie (Tabitha is only hidden – removing her would set `FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA` and hide Maxie).
  Nerine and Brendan are scene-only objects hidden by `FLAG_TEMP_11` (set on every load). The two Magma grunt
  trainers on the path stay trainers with rank-test lines (D-103). – Alt: the player walks to the post and a trigger
  starts the fights (a saved state to carry across a whiteout, and the player could leave before the sabotage);
  battles with Tabitha and Maxie (the player never fights them before Sootopolis). – The add-on asks for a scripted,
  choice-free scene.
- **D-124 Brendan at Mt. Chimney is not a must-win**: `trainerbattle_earlyrival(TRAINER_BRENDAN_MT_CHIMNEY,
  RIVAL_BATTLE_HEAL_AFTER, …)` – a loss heals the party and the scene goes on, Brendan gets a victory line and
  `VAR_RESULT` picks his after-line. – Alt: `FLAG_DRACONID_NO_WHITEOUT` around `trainerbattle_no_intro` and a heal
  (D-108, Draconid Pass; the script can't tell who won). – One command, the same mechanism as Route 103 (D-048).
- **D-125 Jagged Pass**: Aster waits at the top of the pass (shown by the Mt. Chimney scene) and walks over when the
  player steps off the stairs from the summit ((13, 8) / (14, 8), on `ASTER_STATE_METEOR_FALLS`: the only way down);
  no battle; she hands over the ring, points the player to Lavaridge and leaves in a fade. – Alt: at the foot of the
  pass by Route 112. – The first thing after the summit, and the stairs can't be skipped.
- **D-126 The Mega Stone gift**: a Draconid villager (`OBJ_EVENT_GFX_DRACONID_MAN`) waits by Lavaridge's east
  entrance, shown by the Jagged Pass scene; talking to him gives the second starter's stone by `VAR_SECOND_STARTER`
  (Charizardite X / Feraligite / Sceptilite, as the v1 Elder did); with a full bag he waits; then he leaves in a fade.
  – Alt: a trigger that walks him to the player. – Aster names him, he stands on the way into town, and he can't be
  missed for good.
- **D-127 Act 3 side lines**: May's vanilla Go-Goggles scene in Lavaridge stays (the desert needs them) with round 1
  lines – the uniform, Mt. Chimney, "my DAD's GYM in PETALBURG is next" (Norman's daughter, D-100; she watches that
  battle, D-116). Cozmo at Meteor Falls fears the uniform; the Route 112 grunts send the "rookie" to Meteor Falls;
  Archie at Mt. Chimney knows the player from the falls. – Alt: vanilla text ("challenge your dad").
- **D-130 Weather Institute (Act 4)**: Tabitha waits by the Institute door on Route 119 (the order runs on the
  doorstep, the only way in) and sends the player in; the vanilla Aqua fights stay, with Shelly and the grunts
  reacting to the uniform. After Aqua flees, the player unties the scientists off-screen; May runs up the stairs
  and starts to say what she saw just as Tabitha comes up to collect, turns it into an insult to cover for the
  player, then whispers "I'll pretend I didn't see you save them". Tabitha takes the Institute's notes (the
  "research": the weather answers to two ancient orbs, which Maxie's next phone call picks up); the scientist
  still gives Castform, now as thanks for the rescue. – Alt: a Magma messenger grunt instead of Tabitha;
  Castform as the research. – May can only "nearly expose" the player in front of a Magma witness, and Tabitha
  has given the orders in person since Rustboro (D-115, D-119).
- **D-131 Brendan on Route 119**: the vanilla scene and HM Fly stay (Brendan hands it over because May made him
  promise), then he registers in the PokéNav (as May on Route 110) and rides off; Scott's line is unchanged.
  – Alt: Fly from someone else. – The progression item stays where vanilla has it.
- **D-132 Mt. Pyre**: the vanilla orbs (Magma takes the Blue Orb first, Aqua the Red). On the first visit Maxie
  meets the player at the top of the summit stairs (OnFrame; his vanilla summit object), shows the Blue Orb,
  orders them to hold off Aqua and gives them the Magma Emblem himself (the old lady's "they left this behind"
  goes; she now wonders about the child in red who fought the others). The four summit grunts are the ones to
  hold off (lines retold for a Magma opponent); Nerine blocks the stairs below the altar (a trigger row across
  the only way up) and walks off down the mountain after the fight; then Archie takes the Red Orb (vanilla, his
  lines address the player). `MAGMA_STATE_MT_PYRE` is set when Archie has left, so Maxie's call about the orbs
  comes after it; until then the emblem in the bag marks Maxie's scene as done. – Alt: Maxie on the exterior;
  Nerine as a sight trainer (can be walked past). – One arrival scene carries the order, the orb and the emblem.
- **D-133 Magma Hideout entrance**: the Jagged Pass guard stays after Mt. Pyre (vanilla hid him there). When the
  player comes with the emblem (the vanilla emblem triggers, or talking to him) he recognizes it, the rock opens
  as in vanilla and he goes in ahead (`FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD` is set then). Before that his vanilla
  battle is a rank test and he won't talk about the door. Inside, the grunts and Tabitha keep their battles as
  rank tests (D-103); lines that called the player an intruder were rewritten. – Alt: the door opens with no
  NPC. – "The guard lets them in" (story); a trusted member doesn't sneak in.
- **D-134 Maxie's promotion, no battle**: talking to Maxie by the magma pool first plays the promotion (Tabitha's
  report on Mt. Pyre, "I have watched you since Meteor Falls", "Stand beside me as the land is reborn"), then
  vanilla's awakening and Groudon's escape. The battle is cut; Maxie tells his plan instead (land for everyone,
  the seas will shrink, the Red Orb is missing, he'll need someone inside Aqua's walls) in the two texts that
  framed the vanilla battle, and every flag and var vanilla sets after it is still set. The player then writes
  to the Elder (a narrated letter a traveller carries to the mountains). Maxie's Magma Hideout team (and its Mega
  Camerupt, D-066) is not fought here any more. – Alt: keep the battle as a "test"; a call to the Elder (he has
  no PokéNav). – The story cuts the battle; a letter needs no new object or item.
- **D-135 Lilycove and Wally (round 1)** *(the rivals' tone: D-211; Wally's: D-236)*: the v1 fights and staging stay, with new lines. Before the double,
  Brendan and May argue about the player (Brendan hurt but unsure since Route 119, May sure the player is secretly
  good); afterwards both go home to Littleroot as in v1. Wally trusts what he saw in Mauville, at the Petalburg
  Gym door ("MR. NORMAN", May's dad) and in Lilycove. – The add-on.
- **D-136 Scene-only NPCs use temp flags**: May and Tabitha on the Weather Institute 2F and Nerine on the summit
  are hidden by `FLAG_TEMP_11/12`, which the map's OnTransition sets (as May in the Petalburg Gym, D-116); Maxie
  on the summit borrows his vanilla object and flag. Only Tabitha on Route 119 needs a saved flag (0x35).
  – Alt: a saved flag per NPC. – The shared flag budget is small, and these NPCs never stay after their scene.
- **D-137 Steven on Route 120**: vanilla scene and Devon Scope; he notices the uniform ("Still wearing red, I
  see"), "Whoever you're really working for, they trust you", and leaves with "Keep your head down. I'm watching
  MAXIE, too." (story step 19).
- **D-140 Tabitha's raid, no Maxie at Mossdeep**: Maxie is off chasing Groudon (his PokéNav call sends the player to
  Tabitha), so the vanilla city scene's Maxie object is Tabitha (drawn as a grunt, D-115) and the Space Center 2F
  has no Maxie; his vanilla "is our goal misguided?" doubts are not said here (at Sootopolis he still wants
  Groudon). The Magma grunt trainers on 1F and the three on 2F stay battles as **rank tests** of the promoted
  rookie (D-103). – Alt: Maxie at the Space Center without battling (he would have to doubt himself before
  Sootopolis, where the add-on has him order the player to help him control Groudon).
- **D-141 Space Center staging**: Steven and Brendan hold the 2F corner by the fuel, Tabitha faces them; coord
  triggers across the only way in (x 7, after the grunts) walk the player to Tabitha's side, so the scene can't be
  skipped or talked into from odd angles. Tabitha heals the player's team first (there is no break between the
  rank test and the battle), the player picks three (the vanilla half-party menu), and the battle can't white out.
  **Whoever wins, the scientists have sealed the tanks during the battle** (a voice from the control room); Steven
  says the player kept Tabitha busy long enough ("I know you let us win the important part"), heals the team after a
  loss, and Brendan storms off down the stairs. The vanilla ending runs after that (every flag, Steven's house and
  HM Dive). Brendan's object reuses 0x3E (`FLAG_HIDE_MOSSDEEP_SPACE_CENTER_RIVALS`, name kept). – Alt: a must-win
  battle (the add-on says not); Magma retreating only after a loss (then a win would give them the fuel).
- **D-142 Nerine, Aqua Hideout and Seafloor Cavern**: in the hideout she stands beside Matt at the submarine dock and
  **talking to Matt brings her in first**, so fight 5 can't be skipped; afterwards she dives after Archie's
  submarine. In the Seafloor Cavern she waits at the entrance of the last room (Room 9, before Archie's chamber) and
  the reveal plays on arrival: her object draws from `VAR_OBJ_GFX_ID_0` and changes from the Aqua disguise to her
  own outfit behind a fade. Both are ordinary must-win battles (a loss whites out; the scene plays again).
  `MAGMA_STATE_SEAFLOOR` is set when Kyogre wakes (end of the vanilla Archie scene), not at the reveal, because
  Maxie's next PokéNav call says Kyogre is awake. – Alt: a second object for her true look (one more flag); the
  reveal in Room 8 (the boulder room: no free tile beside the exit).
- **D-143 The Sootopolis turn**: after the vanilla Groudon/Kyogre scene the player surfs to the Gym island and talks
  to Maxie; he orders the player to help him control Groudon, the player remembers the Elder's words and takes the
  uniform off (outfit → tamer, `REPUTATION_REVEALED`, `MAGMA_STATE_TURNED`), then **Maxie alone**, then Archie
  joins him and Brendan and May fly in; May heals the team (the Maxie battle came right before), the player picks
  the partner (`PARTNER_BRENDAN` / `PARTNER_MAY`), the other walks to the shore and "holds off the admins"
  off-screen (a cry and a line; the admins aren't drawn). Both battles
  are must-win with the vanilla whiteout, and the scene is **re-entrant**: talking to Maxie again resumes at the
  battle that was lost (the uniform stays off; Brendan and May wait on the island). – Alt: retry loops without
  whiteout (D-110 style: a flow test can't mash through them); admins as objects (four more flags).
- **D-144 No Cave of Origin trip**: Steven no longer leads the player to Wallace in the Cave of Origin – he points
  at Maxie on the island (and, after the crisis, says he was right about the player since Granite Cave). The
  expert keeps blocking the cave (`FLAG_STEVEN_GUIDES_TO_CAVE_OF_ORIGIN` is never set), so Wallace's Cave of Origin
  and Sky Pillar scenes can't run; Wallace appears by the Gym after Rayquaza, and his lines say he saw the uniform
  come off and that the Sky Pillar is sealed. – Alt: keep the Cave of Origin visit (Wallace would have to send the
  player somewhere, D-109 says not the Sky Pillar).
- **D-145 The Rayquaza calling and the Sky Pillar state**: after the multi battle, thunder, then over black "Far
  away, at the SKY PILLAR…" (Aster and Nerine; `ASTER_STATE_RAYQUAZA_CALLED`); then the vanilla Rayquaza scene,
  seen from the island (own camera pans, the rest as `SootopolisCity_EventScript_RayquazaSceneFromPokeCenter`).
  Everything the vanilla Sky Pillar trip leaves set is set: `VAR_SOOTOPOLIS_CITY_STATE` 5 (the vanilla aftermath:
  Maxie, Archie, Wallace, Steven by the Gym; Juan's badge makes it 6), `VAR_SKY_PILLAR_STATE` 3 (Rayquaza is back at
  the top: floors cracked, its object shown), `VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE` 1, Wallace shown in the city – but
  **not `FLAG_WALLACE_GOES_TO_SKY_PILLAR`**, so the tower door stays shut until Acts 6–7 open it.
- **D-146 The Elder's word and the rivals' reactions**: right after Rayquaza leaves, a PokéNav call (the vanilla
  `pokenavcall`, no Match Call entry needed): the Elder, with Aster and Nerine beside him for a line each – "It isn't
  time yet. The sky will tell us when." Then, still on the island, May's "I KNEW it!" and Brendan's awkward
  apology; both fly home (`BRENDAN_STATE_SOOTOPOLIS`, `MAY_STATE_SOOTOPOLIS`) before the city reloads. Maxie and
  Archie admit their failure in the vanilla aftermath, with a line each about the player. – Alt: a letter (needs a
  messenger); the rivals' lines after the reload (another state var for the OnFrame).
- **D-150 After the Hall of Fame (Act 6)**: no credits; the Hall of Fame screen sends the new Champion home to the
  village bedroom (the Hall of Fame save continues there too, so both paths agree). Upstairs a night of celebration
  ends in a quake and a red glare; downstairs the TV breaks in with the meteor news and the Elder, waiting at the
  table, speaks the prophecy's words and sends the player to the Sky Pillar; his dragon can fly the player there at
  once (YES/NO; talk to him again later), or the player flies/surfs to Route 131. The sky stays dark (weather shade)
  in the village and at the Sky Pillar until the meteor breaks. Later Hall of Fame entries also end at home, without
  credits. – Alt: vanilla credits right after the Hall of Fame; the alert at Ever Grande City; a forced warp to the
  Sky Pillar. – The save already continues at home, and it mirrors the prologue (a falling star, the Elder calls).
- **D-151 The Trial of Three (Act 7)**: Aster and Nerine wait below the Sky Pillar's door and meet the player at the
  cave mouth; the clan's last rite before anyone stands beside Rayquaza: the player + Nerine vs Aster, a
  `multi_2_vs_1` in which the player picks three (Aster's teams are `Multi Party: Half`). The script names Aster's
  base id and `PARTNER_NERINE_DEINO_CHARMANDER`; `SetMultiTrainerBattle` resolves both (the partner through the same
  egg × second starter table as her trainer teams). The door opens when the trial is won (it stays shut before, so
  the trial can't be walked past); Nerine heals the party and the three climb together (a fade to 3F). A loss: a
  heal, and talking to Aster or Nerine starts it again. – Alt: nine script branches for the partner;
  `multi_fixed_2_vs_1` (the first three Pokémon). – One line per battle, as D-101.
- **D-152 The credits after the finale**: the game saves first (like the Hall of Fame: the save continues in the
  bedroom), the vanilla credits roll, and they end in the bedroom instead of a soft reset; the player wakes the next
  day and the Elder waits downstairs with the SS Ticket (D-112). – Alt: soft reset into the saved game (the vanilla
  flow). – No progress can be lost to a cut-short credits sequence, and the post-game begins without the title screen.
- **D-153 The must-catch Rayquaza**: at the summit the Elder calls it down (it lands in the vanilla spot); the wild
  battle (Lv 70, its level-up moves) can't be run from and can't white out; if Rayquaza faints or the player loses,
  a line, a heal and the battle again (D-110). The Elder hands over 5 Ultra Balls whenever the player has none.
  Rayquaza's catch rate is 45, as in ORAS (3 in Emerald: under 1 % per Ultra Ball). After the catch it leads the
  party (fetched from the PC if the party was full, the old lead takes its box slot) and learns Dragon Ascent (an
  empty slot, else over Rest, else the last move). – Alt: a guaranteed "victory catch"; a Master Ball from the
  Elder. – A catch the story requires should not need a hundred balls; ORAS made the same change.
- **D-154 Deoxys and the meteor**: Deoxys (Normal Forme, Lv 72, its level-up moves: Zen Headbutt, Cosmic Power,
  Recover, Psycho Boost) drops onto the summit right after the catch; a wild boss battle with no catching, no running
  and no whiteout, fought again after a loss (with a heal); Rayquaza leads. After the win Deoxys breaks into light,
  Rayquaza Mega Evolves on the field (flashes, cries), flies up, and the "Rayquaza takes flight" shot of the
  Sootopolis cutscene plays on its own; then flashes, thunder, a quake, the shade weather clears, and Rayquaza comes
  back and returns to its ball. The Elder: "The sky's debt is paid… for now." – Alt: Deoxys Attack Forme (Mega
  Rayquaza one-shots it). – A boss that lasts a few turns, and an ending built from what the engine can show.
- **D-155 Zinnia (the playtester's request)**: the Lorekeeper of the Meteor Falls Draconids, a sister clan, waits on
  the Sky Pillar 3F between the trial and the summit and tests "the Elder's chosen"; Aster and Nerine know of her,
  and the Elder greets her at the summit. Her ORAS Delta Episode Sky Pillar team (Serebii) with the boss
  enhancements: held items (Assault Vest, Life Orb, Leftovers, Choice Band, the Salamencite), natures, EVs, IVs 31,
  2 Full Restores, `Smart Trainer / Prediction / Ace Pokemon`. New class LOREKEEPER (25 money, Ultra Ball), battle
  music `MUS_VS_FRONTIER_BRAIN` (a master outside the League). A loss doesn't white out: the climb is one scene, so
  Nerine heals the party and talking to Zinnia starts the battle again. Her sprite and pic are the drawn art of
  D-180/D-181. – Alt: a normal boss battle that whites out (the player would climb the cracked floors
  back alone); the Champion theme.
- **D-156 Brendan and May after the finale**: their Littleroot lab battles (and Brendan in the lab) wait for the
  finale, not the Hall of Fame; the lines are rewritten for the truth being out (Brendan's apology, May's "I told
  you"). Each single battle sets that rival's post-game state; the double comes after both. – Alt: at the Hall of
  Fame, as v1.
- **D-157 Nerine and Aster at home**: Nerine waits by the village pond at (28, 7), by the waterfall (she spent years
  among the sea people; the water of home), for one battle as herself (her post-game team by egg × second starter);
  she stays in the village afterwards. Aster's shrine battle (v1) waits for the finale and ends with her admitting
  the Elder chose right. – Alt: Nerine in the Elder's house; at the Sky Pillar.
- **D-158 Deoxys later (D-111 in practice)**: Deoxys (Normal Forme, Lv 80 as in ORAS) floats at the summit after the
  finale; caught = gone (`FLAG_BATTLED_DEOXYS`), beaten = gone until the next Hall of Fame, which clears
  `FLAG_DEFEATED_DEOXYS` (the Birth Island rule; Birth Island itself is unreachable without the event ticket).
- **D-159 Staging and the Champion's room** *(the Champion is Steven since D-250)*: the finale's scenes start from each map's OnFrame through `VAR_TEMP_7`
  (set by the OnTransition hook), so a lost battle ends the scene instead of looping it; the climb from the base to
  3F and from 3F to the summit are fades, not walks (the tower's cracked floors need the Mach Bike and would split
  the three up). In the Champion's room Brendan runs in (Birch's son), and May follows Birch in; Wallace and Birch
  speak of the uniform; Wally's Victory Road lines know the truth. The Hall of Fame no longer puts Norman in the
  Littleroot houses (they are the rivals' homes) and the Draconid house has no Norman object. – Alt: the vanilla
  Champion's room with May (v1).
- **D-160 Nerine's disguise detail**: the female Aqua grunt sheet and pic unchanged except her own **silver-blue
  hair** under the bandana (the real grunts' is magenta/red). – Alt: a teal scale scarf; a gold horn clip on the
  bandana. – The hair is the one detail readable at 16×32 among grunts (a clip is 2–3 px), it is the same hair
  she has after the reveal, and it is not "Draconid" on a first playthrough, only in hindsight (story rule on hints).
- **D-161 Nerine's true look**: long silver-blue hair, deep navy clothes, a teal shawl with a scale lattice, a gold
  sash/belt and cuffs, and **one** small gold horn clip on her left side. Bases: Frontier Brain Lucy's walk sheet
  (overworld: very long hair, 9 frames), Winona's front pic (long hair, flowing scarf → shawl; the winged headpiece
  removed, crown and hair redrawn), Leaf's back pic (like the Draconid F back pic, own crown). – Alt: the Leaf
  pipeline with a new head, like Aster (same silhouette as Aster and the player); Lucy's front pic (needs a shawl
  drawn from scratch). – A single asymmetric horn and no headband separate her from the player (teal band, ivory
  horns) and Aster (crimson band, two gold horns); the long hair gives her a different silhouette.
- **D-162 Courtney's look**: the female Magma grunt with lilac hair, a dark crimson admin jacket instead of the black
  top, and a gold Magma emblem; the hood keeps the grunts' red. – Alt: Tabitha's duller crimson for the hood (washed
  out, less "Magma"); black tights. – Visible at a glance next to grunts from every side, still one of Magma.
- **D-163 Partner back pics**: Nerine (Sky Pillar) and Tabitha (Space Center) get back pics, used for any
  `TRAINER_PIC_NERINE` / `TRAINER_PIC_MAGMA_ADMIN` partner. Tabitha's is the Magma disguise back pic (Red's build)
  recoloured into his crimson hooded jacket. – Alt: draw a heavier build for him (`TODO(art)` if wanted). – Partners
  are drawn from behind; reusing the player's rigs keeps the 5-frame Kanto throw animation.
- **D-164 The tamer's scarf** (feedback 1.14): a long **red** scarf in the clan's red with a fish-scale pattern,
  worn **with** the horned headband (the clan mark, kept – the two do not clash: the scarf sits at the neck, the
  horns on the head). Wrapped at the neck, its two ends hang down the back as a short cape (M) or lie over the long
  hair as two tails (F), trail behind in the side view and stream out when running, cycling and in the credits run;
  on the pics they stream out like Zinnia's. – Alt: Zinnia's dark grey scarf (not a Draconid colour, reads as Team
  Aqua/Magma black at 16×32); a teal scarf (lost against the teal jacket); an ivory one (fights the horns); a
  cloak that replaces the headband (D-051's horns are what makes the silhouette). – Red on the teal jacket is the
  strongest contrast the palette has, and the cape from behind gives the tamer a silhouette of its own.
- **D-165 The backpack goes under the cape (M)**: Red's red backpack is covered by the scarf's ends everywhere
  (overworld back and side views, back pic, front pic, credits); the female keeps her gold bag. – Alt: keep the
  backpack and hang the scarf over it (two reds in the same place read as one lump at 16×32). – The cape replaces
  the pack's area pixel for pixel, so the walk animation keeps its proportions.
- **D-166 Scale detail by size**: the pics and the credits run cycle get a clear pattern (U-shaped scales 4 px wide,
  offset rows); the 16×32 / 32×32 sprites only a dot hint in the dark red. No new colours: each palette's existing
  red pair is reused (the female overworld palette's unused bright red), so palettes, reflection palettes and the
  C data stay as they are. – Alt: a third red for scale highlights (costs a slot every sheet would have to give
  up). – A readable pattern where it fits, and nothing that would need the outfit code regenerated.
- **D-167 Small fixes riding along**: the Wailmer Pail on the watering frames is teal (it was a red blob in the
  scarf's colour; the real pail is blue), and the male front pic's Poké Ball is red (it had come out teal).
  – Alt: leave them (the pail would merge with the scarf's tail). – Both are on sheets redrawn anyway and cost a
  line each in the specs.
- **D-170 ORAS data source**: Serebii's Pokéarth "Gen VI" location pages and its ORAS Elite Four page, scraped once
  (2026-09-30, one request at a time, cached outside the repo) into `tools/hack/trainers/oras/oras_trainers.json`
  with the scraper next to it. – Alt: rosters from memory (v1: none could be vouched for); Bulbapedia (HTTP 403).
  – A recorded, re-parsable source; Serebii lists species, levels and items, so sets are still written and
  checked here.
- **D-171 Matching Emerald ↔ ORAS**: same name on the Serebii page of the trainer's map, class mapped (Cooltrainer =
  Ace Trainer, …); a namesake on another page or two candidates on one page are recorded, not used; the Abandoned
  Ship's trainers are looked up in Sea Mauville (ORAS replaced it). – Alt: fuzzy names, name-only anywhere. – The
  brief's "record ambiguous ones instead of guessing": ORAS moved and renamed many trainers (Julie, Georgia, …
  are other people in ORAS).
- **D-172 `oras-first` teams**: ORAS rematch teams exist only for trainers that already have Emerald tiers (rule 1),
  so the ORAS data reaches regular trainers through their first-battle team: used when it has **more evolution
  families** (species pool only) than the trainer's vanilla Emerald team (27 trainers; Gilbert and Cole already
  had the ORAS species). The new team keeps the block's header, party size and levels: the ORAS roster (the ORAS
  ace last, level-up evolutions to the slot's level, stone / trade / friendship evolutions not applied, e.g.
  Clamperl stays Clamperl, with a Deep Sea Tooth), filled with the current members, Emerald families first (one
  more slot if none would survive and the party band allows it); sets from the same species elsewhere in
  `trainers.party`, only moves known at that level (`build_oras_batch.py --check`). – Alt: ORAS first teams for
  every matched trainer (would replace the richer enhanced teams with 1–3 Pokémon); only when the ORAS team is
  bigger than the current one (never true). – "Richer" is read against the team the enhanced one was built from.
- **D-173 Elite Four rosters**: the first battle uses their **ORAS post-game rosters** (species from all regions:
  Scrafty, Zoroark, Mandibuzz, Mismagius, Drifblim, Chandelure, Abomasnow, Beartic, Vanilluxe, Dragalge,
  Haxorus – exempt from the species pool, D-065) at the S9 levels they had (aces 55–58), no Megas; the ace is the
  ORAS first battle's ace (Absol, Dusknoir, Walrein, Salamence), because the rematch aces Sableye and Glalie lean on
  their Megas. Sets start from Serebii's ORAS moves, made into full competitive sets. – Alt: the ORAS first-battle
  rosters (nearly the Emerald ones); Hoenn-only replacements. – The brief and the playtester ask for the post-game
  teams; the League is where a wider roster fits.
- **D-174 Elite Four rematch**: blocks at the ORAS rematch levels (70–75, the POST ace band) with the ORAS Mega
  Stones (Absolite, Sablenite, Glalitite, Salamencite) as `TRAINER_{SIDNEY,PHOEBE,GLACIA,DRAKE}_REMATCH` in
  `tools/hack/trainers/oras/elite_four_rematch.party`, allowed Megas in `check_party.py`; **not in the ROM**: it needs
  four trainer ids (`include/constants/opponents.h`, 924–927 are free) and a game-clear switch in the Elite Four
  rooms or a variant rule (`src/draconid.c`), files owned by the story work this round. – Alt: Megas in the first
  battle. – Megas stay a post-game treat (D-066) and the rematch is ready to wire.
- **D-175 Wallace unchanged** *(superseded by D-250 – D-252: Steven is the Champion, Wallace post-game)*: ORAS has no Champion Wallace; its only other Wallace battle on Serebii
  ("Sootopolitan Wallace", Route 131 page) has exactly his Emerald Champion roster, which his current team already
  uses. – Alt: Steven's ORAS Champion roster (Steven is story-owned). – Nothing in the ORAS data improves him.
- **D-180 Zinnia's look**: her ORAS Lorekeeper design at GBA size – a black chin-length bob with blunt bangs, a
  **red bead** hair tie on her left side, red eyes (front pic), a ragged **cream cloak** with a wound high collar,
  olive leaf-shaped shoulder pads, a black top with two red crescents, a red rope belt with cream ends, olive shorts
  and boots, cream socks, and her blue-grey Mega Anklet on the right leg (front pic only). The cloak shows from every
  side: behind her at the sides from the front, covering her back from behind, trailing from the side. – Alt: a dark
  (charcoal) cloak for an all-dark outfit; a teal or crimson cloak in the clan colours. – Cream is her canon cloak
  colour and nobody else in the cast wears it: Nerine has silver-blue hair and a teal shawl, Aster a crimson band and
  gold horns, the player a teal band, ivory horns and teal/red clothes (the tamer scarf added to the player's outfit
  should stay out of cream so the two scarves stay apart); Zinnia has no horns and no headband, so she reads as a
  different kind of Draconid (the Lorekeeper), and a dark cloak would merge with her black hair at 16×32.
- **D-181 Zinnia's art bases**: overworld from Frontier Brain **Anabel's** walk sheet (the only 9-frame NPC sheet with
  a short bob; her hair and face keep their palette roles, the body is redrawn per frame over Anabel's poses); front
  pic from the **Psychic F** pic (short hair, dark top, shorts, bare legs, arms spread wide as if calling the sky; the
  psychic rings and the floating Poké Ball are erased, the cloak is painted behind the body). No back pic (she never
  fights beside the player). – Alt: the Leaf pipeline like Aster (same silhouette as Aster and the player); Lucy's
  sheet (long hair, taken by Nerine); Lance's caped FRLG pic (male build, trousers, new head needed); Anabel's
  pic (pointing pose, trousers). – Short-haired bases give her a silhouette of her own next to the long-haired Nerine,
  Aster and the player, and every step is a kitbash recipe, so the art can be polished without redrawing.
- **D-185 Gen 6 Exp. Share**: `I_EXP_SHARE_ITEM` is `GEN_6` (a key item that shares EXP with the whole party
  while `FLAG_EXP_SHARE_ON` is set; using it toggles the flag). Mr. Stone hands it over **with the PokéNav** at
  the first Devon meeting and it starts switched on; vanilla gave a held Exp. Share only on a return visit after
  Steven's letter, which many players never make. The hard level caps still apply. – Alt: keep the held item;
  Gen 7 always-on. – The playtester's note.
- **D-186 Maxie's calls**: Maxie phones the recruit after each key story point and names the next place. The
  first call replaces vanilla's call from "Dad" Norman on Mr. Briney's boat (Norman is May's father now, so he is
  no longer registered in the PokéNav); the others ring on the 10th step outdoors after the Oceanic Museum,
  Meteor Falls, Mt. Chimney, the Weather Institute, Mt. Pyre, the promotion, the Aqua Hideout, the Space Center
  and the Seafloor Cavern (story states, `src/draconid.c`). Only the latest due call plays; none after the
  Sootopolis turn. – Alt: calls at the end of each scene (they would ring in the middle of the aftermath);
  Maxie in the Match Call list (needs a new entry with his own call texts). – The playtester's note.
- **D-187 Rival staging and the level audit** *(the Latis: D-237)*: Brendan's first fight (Rustboro, after Petalburg Woods) is
  Poochyena, Taillow, Slakoth and Treecko at 10–13 (IVs 15, since the player may have only their dragon there);
  each later fight grows the team the way ORAS does (Mt. Chimney 5 with Grovyle and Slugma, the Latis after the
  Balance Badge, all six from Route 119 / Lilycove). May: Torchic on Route 103, four on Route 110, six at
  Lilycove. `build_segments.py` places every story fight (and every Nerine/Aster variant) on the round 1
  schedule – Steven's Space Center team is exempt from the cap on purpose (D-108), the Sky Pillar finale and
  Zinnia are post-League (D-109) – and `check_party.py --caps` passes with 0 errors.
- **D-190 HM field moves without a Pokémon that knows them** (feedback 1.27): once the player **owns the HM** (HMs
  are never used up, so it is in the bag) **and has the badge** vanilla requires for its field move
  (`IsFieldMoveUnlocked`: Cut Stone, Flash Knuckle, Rock Smash Dynamo, Strength Heat, Surf Balance, Fly Feather,
  Dive Mind, Waterfall Rain), the field move works from the overworld as if a party Pokémon knew it: Cut trees,
  Rock Smash rocks, Strength boulders, Surf, Waterfall, Dive down and surfacing all go through the vanilla prompts
  (`checkfieldmove`, `PartyHasMonWithSurf`), so every story obstacle (Rusturf's rock, the Seafloor Cavern and
  Victory Road boulders, the Dive spots, the Ever Grande waterfall) opens the same way. A Pokémon still appears in
  the field-move animation and the vanilla "{STR_VAR_1} used CUT!" lines stay: one that knows the move (vanilla),
  else the first party Pokémon that **could learn** it (level-up or teachable list), else the first one that isn't
  an Egg (vanilla lets fainted Pokémon use field moves, so they may stand in too). Without the badge nothing
  changes (the vanilla "can't" lines); TM field moves (Secret Power, Dig) still need a Pokémon that knows them.
  Switch: `OW_FIELD_MOVES_WITH_HM`. – Alt: a key item per move (ORAS Poké Ride style, needs new items and art);
  field moves for any Pokémon that could learn them (still forces the right species into the party); dropping the
  badge gates (would open the story out of order). – The playtester's note, and the HM + badge pair keeps the
  vanilla order of city access.
- **D-191 HMs used from the bag**: with its badge, using an HM from the bag first asks "Cut can be used here.
  Would you like to use it?" when its field move has something to act on right here (the party-menu setup
  `SetUpFieldMove` decides: a tree or grass for Cut, water to Surf on, a dark cave for Flash, a Fly-able map, …);
  **Yes** does the move with the D-190 stand-in, **No** goes on to the vanilla "Booted up an HM… Teach it?"
  question. Anywhere else, and without the badge, using an HM teaches it as in vanilla. Fly opens the region map
  (cancelling it returns to the bag, not to the party menu); Flash lights a dark cave; the Braille puzzles that
  need Rock Smash (Regirock) and Flash (Registeel) work the same way. – Alt: a USE / TEACH / CANCEL list in the bag
  (new menu code in the bag); separate key items; bag use only for Fly and Flash (Cut on tall grass and the Braille
  puzzles would then still need a Pokémon). – Reuses the bag's own yes/no and the party menu's field-move setup, so
  every HM behaves the same and the vanilla teaching path is one "No" away.
- **D-192 HMs can be forgotten**: `P_CAN_FORGET_HIDDEN_MOVE` is TRUE (a new move can replace an HM move, the Move
  Deleter takes the last Surf). – Alt: keep HM moves locked. – With D-190 no Pokémon has to keep an HM move.
- **D-193 Gen 4–9 in the wild** (feedback 1.28, docs/hack_wild.md): 95 species from Gens 4–9 join the Hoenn
  tables (281 slots in 110 tables: land, surf, Rock Smash, all three rods) by habitat, region and story point –
  forest bugs and birds, cave rock/ground/ghost types and bats, desert ground types, Mt. Chimney's coal and fire
  types, ghosts on Mt. Pyre, sea birds, rays and reef fish; Alolan and Paldean species suit subtropical Hoenn.
  A new species only **replaces a duplicate slot and keeps its vanilla levels**, so no table loses a species, no
  Hoenn species moves, level ranges and Emerald's slot rates stay, and the slot's rate is its rarity (10% common,
  5%/4% uncommon, 1% for Larvesta, Mimikyu, Hawlucha, Stufful, Morelull and the dragons). No legendary, mythical,
  paradox or Ultra Beast, **no regional forms** (every Hoenn species keeps its Hoenn look), the Deino / Dreepy /
  Jangmo-o lines stay out (D-065); other dragons are rare and late (Gible 1% in the desert, Goomy in the rain of
  Routes 119/120, Noibat and Druddigon in Meteor Falls, Druddigon 1% atop the Sky Pillar). Minior is its Meteor
  Form (red core). The Johto Safari areas, Artisan / Altering Cave, Mirage Island and the Sootopolis crater stay
  vanilla. – Alt: add slots (Emerald's slot counts and rates are fixed in the engine); replace whole tables
  with Gen 4–9 species (loses Hoenn's feel); ORAS's DexNav-only species (the brief asks for Gens 4–9 broadly). –
  The brief asks for new species "where it makes sense"; taking duplicate slots keeps every vanilla encounter.
- **D-194 Beldum at 1% in Granite Cave**: every Granite Cave land table (1F, B1F, B2F, Steven's Room – the only
  floors with tables) has Beldum in one 1% slot at that floor's level (1F Lv 9 and B1F Lv 11 replace a duplicate
  Geodude / Sableye in slot 11, B2F Lv 12 a Sableye in slot 10, Steven's Room Lv 8 an Aron in slot 11).
  `check_wild.py` fails without it. – Alt: a scripted Beldum gift; Beldum in both 1% slots (2%). – The brief asks
  for exactly a 1% encounter; Steven's own Metagross line stays a rare find in his favourite cave.
- **D-195 Gen 4–9 on generic trainers** *(extended by D-240 – D-242: 60%, grunts too)* (docs/hack_trainers.md, "Gen 4–9 swaps"): 122 of the 434 generic trainers
  (first battles, route and gym roles; 28%) swap one Pokémon – two for Timothy, Wilton and Nicolas – in all their
  rematch tiers (214 blocks), keeping level, IVs, EVs, nature and slot. The new species fits the class and the area
  (a hiker's Rolycoly, a Petalburg Woods bug catcher's Nymble, a Mt. Pyre hex maniac's Litwick), comes from the
  wild tables (D-193) or, for rematch trainers, from the trainer's **own ORAS roster** (Serebii data, D-170: Haley
  Whimsicott, Jerry Bisharp, Cindy and Winston Pyroar, Dalton Chatot, Benjamin Klinklang, Ethan Skuntank, Shelby
  Lucario, Wilton Talonflame and Haxorus, Brooke Purugly, Dusty Tyrantrum, Tony Jellicent, Timothy Hawlucha and
  Conkeldurr, Jackson Unfezant, Catherine Excadrill, Valerie Mismagius, Jessica Krookodile, Jenny Alomomola,
  Isaiah Floatzel, Robert Staraptor, Walter Stoutland, Nicolas Noivern and Druddigon) and appears at the stage its
  level allows in every tier. Aces are kept except Jerry's (ORAS gives him Bisharp for Banette). Magma / Aqua
  grunts keep their teams (the teams' signature Poochyena / Zubat / Numel / Carvanha lines). The species pool
  (D-065) now also holds the families of every species wild in Hoenn or on an ORAS Hoenn trainer
  (`check_party.py`). Moves: level-up (and TMs from S4) chosen for STAB + coverage + a status or set-up move, no
  moves over 90 power before S4. – Alt: one new Pokémon added on top (party sizes are fixed per segment); new
  species for story trainers too (they are hand-written, out of scope). – "Roughly a quarter" of the generic
  trainers, each change following the rulebook, the tiers and ORAS where ORAS knows the trainer.
- **D-196 National Pokédex from the start**: Birch's lab scene (`birch_intro.pory`) enables the National Dex right
  after giving the Pokédex, with one line from Birch about Pokémon from faraway regions. Hoenn mode is still in
  the menu; the Hoenn count, Birch's rating and the diploma are unchanged. `TODO(dialogue)`: the post-game National
  Dex scene still calls it an upgrade (reword with the post-game rework). – Alt: add the new species to the Hoenn
  dex (changes `HOENN_DEX_COUNT`, the diploma and every regional count); the National Dex at the Hall of Fame as
  vanilla (the new species and the player's own dragon would be invisible until then). – The player catches
  non-Hoenn species from Route 101 on, and their dragon is one of them.
- **D-197 Wild checks** (`tools/hack/check_wild.py`): species exist, are enabled (preprocessed `species_info.h`),
  have a front pic, cry and level-up learnset, and are not legendary / mythical / paradox / Ultra Beast / Mega /
  Gigantamax / regional forms; tables keep slot counts and rates; FRLG, Pyramid and Pike tables stay vanilla; every
  vanilla Hoenn species stays wild; Beldum is at 1% in Granite Cave; a changed slot keeps its vanilla levels or
  stays within the area's cap + 3 (`LEVEL_MARGIN`; area → segment in `WILD_SEGMENTS`, Surf / Dive / Rock Smash /
  rods can make it later); a new species is not below its line's level-up evolution level; a table losing a
  species is a warning. – Alt: a flat cap + 6 for every slot (vanilla Route 115 and Mirage Island go 6 over). –
  Vanilla levels are Emerald's own design and wild Pokémon are caught, not fought for EXP; the hack itself never
  raises a slot over the cap.
- **D-210 Maxie's voice** (feedback 1.26): composed and formal, full sentences with few contractions, grandiose and
  sincere about the land, humankind and "our ideal"; dry pride ("That is the difference between us"); short and
  sharp only when something goes wrong ("What?! The METEORITE is gone!"), then composed again. He praises the player
  rarely and exactly, so the promotion ("you are my right hand") and the betrayal ("After everything I gave you?!")
  land. Vanilla's own words come back where they fit: "Fufufu…", "Humph", "No matter", "Even without the METEORITE,
  there is still the ORB" (his Mt. Chimney line), "I, MAXIE, beaten by my own recruit?!" (after his "I, MAXIE, was
  caught off guard?!"), and the vanilla Groudon, Seafloor and Route 128 lines stay verbatim. At most one aphorism a
  scene. His calls keep naming the next place, in fewer, shorter boxes. Tabitha is a man (vanilla, the trainer data
  and the other lines): Maxie's "she speaks well of you" was a slip. – Alt: an ORAS-style Maxie (more lecturing, "my
  ideal world" speeches). – The note asks for Maxie as he is in the games; Emerald's Maxie is terse and proud, and
  short boxes are what the playtester reads on a phone.
- **D-211 Brendan's and May's voices** (feedback 1.26 and the follow-up "have them be really hostile to you because
  they're trying to stop Team Magma and protect Hoenn, not knowing your true mission"): Brendan casual, confident
  and blunt, short sentences, "Huh?", "Hmm…", "Tch…", "Man,"; May warm, curious and quick, with exclamations and a
  researcher's eye for how POKéMON act. **While the player wears the uniform** (`REPUTATION_UNIFORM`: Rustboro to
  the Sootopolis turn) both treat the player as an enemy of HOENN: every line before and after a battle is hostile
  and earnest – they want to stop MAGMA and protect people, and they are angry the player joined ("Those guys want
  to wreck HOENN!", "I'm going to stop you right here!"). Brendan is betrayed and angry; May fights just as hard,
  and her suspicion shows only as a small crack, one hesitation or question a scene ("…What are you really doing,
  {PLAYER}?"), never as warmth – even her cover at the Weather Institute ends "But don't think this changes
  anything. You still work for MAGMA." What they hand over (the Dowsing Machine, Go-Goggles, HM Fly) is given
  grudgingly, and the PokéNav registrations are to keep tabs on a MAGMA grunt. **After the turn** they warm up as
  the story says (May's "I KNEW it!" moved from the Weather Institute to Sootopolis only, Brendan's awkward
  apology). Both say "my dad" / "Dad" as vanilla does (the round 1 lines had "DAD" like a name). Vanilla reference
  lines, habits to use and to avoid: [hack_voices.md](hack_voices.md). – Alt: keep the round 1 lines with light
  edits (May friendly and sure of the player from Route 110 on). – The playtester called them clunky and asked for
  real hostility; the story's beats (May's doubt on Route 110, her cover at the Institute) survive as cracks in it.
- **D-212 The voice pass rules and scope**: every round 1 Maxie / Brendan / May line of Acts 1–5 was reread against
  these rules and rewritten where it broke one: one idea per box and 1–3 boxes a beat; no "Not X. Y." or "X, not Y"
  antitheses, no rhetorical triplets, no stacked fragments, no em dashes (a cut-off line ends in "…"), at most one
  "…" per box, nobody narrates their own feelings, no modern phrasing; `\n` placed by hand where `format()` would
  split a name ("MT. CHIMNEY") or leave one word on a line. Only text changed – labels, scripts, flags and movements
  are untouched (the emulator tests mash through text, so box counts don't matter); every story fact, place and
  quote from the add-on is kept ("…you've joined MAGMA?!", "I'll pretend I didn't see you save them", "Stand beside
  me as the land is reborn", "After everything I gave you?!", "I KNEW it!"). Verbatim vanilla lines keep their
  punctuation even where it breaks a rule ("Fu… Fuhahaha…"). Out of scope: the lab intro and Route 103 (v1, already
  in voice), and the post-game lab battles (`rivals.pory`, owned by the Acts 6–7 work). Other characters' lines
  changed only where a reply had to follow (none needed it). – Alt: rewrite everything from scratch. – The facts and
  staging were tested act by act; the note is about how the lines sound.
- **D-213 The Aqua Hideout opens with Maxie's order** (feedback 1.23): Archie takes Captain Stern's submarine
  **off-screen**. Maxie's call after the promotion sends the player straight to Aqua's hideout in Lilycove, but
  vanilla kept two grunts in its entrance until the Slateport harbor scene (Archie steals the submarine), which
  vanilla set up in the Magma Hideout and nothing in the v2 story leads to (the checker's detour on leg 4.16).
  The Magma Hideout no longer sets up the Slateport scenes (Stern's interview in the city, the harbor theft);
  its promotion scene sets what the harbor scene left set instead – `VAR_SLATEPORT_CITY_STATE` and
  `VAR_SLATEPORT_HARBOR_STATE` 2, Stern in the harbor with his vanilla "Why…" line, `FLAG_MET_TEAM_AQUA_HARBOR`,
  Scott gone from the motel, the entrance grunts gone. – Alt: point Maxie's call at Slateport first (a text
  change in the dialogue pass's lines, and a detour the add-on's outline – Magma Hideout, then "Maxie orders the
  player to infiltrate Aqua's base" – doesn't have); leave the vanilla hint from the entrance grunts ("our boss
  is in Slateport"). – The add-on's order, one hook in the scene that sends the player on, and the hideout's own
  scene (the submarine leaving with Archie, Nerine diving after it) and Maxie's next call already tell the theft.
- **D-214 What counts as a story lock** (`tools/hack/check_progression.py`): a leg whose walk is blocked (tile,
  object, turn-back trigger, a missing HM or badge), a scene that can't start (its object hidden, its trigger's
  var or OnFrame entry not due), a scene that doesn't set what the next leg needs (`expect`), an OnFrame scene
  that leaves its var as it was (it would restart every frame), a warp into a closed pocket, and a **detour**: a
  way that opens only through a scene off the path the story gives. A walk-through scene on the path (Route 121's
  Aqua grunts leaving) is part of the walk. The model is generous where the player controls it – an HM counts
  from the bag once its badge is won (the HM work makes field moves usable without a Pokémon knowing them), one
  bike counts as both (Rydel swaps them), unknown YES/NO or battle branches keep the progressing side – and strict
  where the game is: collision, elevation, one-way ledges, objects and triggers as the simulated flags leave
  them. Gym puzzles written in C (Mauville, Petalburg, Mossdeep, Sootopolis) are not modelled: only getting in
  is checked. – Alt: a playthrough per leg in the emulator (hours per run, and it only proves the order tested);
  treating every unknown branch as unknown (every YES/NO would "lock"). – A static check runs in ~40 s after any
  script change, and the emulator (`progression.play`) covers the fix itself.
- **D-215 Vanilla requirements the v2 order meets stay as they are**: HM Strength for the Magma Hideout (the
  Rusturf Tunnel reunion, on the only walk from Lavaridge back to Petalburg before Surf), Norman's fourth-badge
  check, the Wally tutorial before Petalburg's west exit, and talking to both Archie and Maxie in Sootopolis before
  the Gym door unlocks and Wallace gives Waterfall – no flag set early, no hint added. The story table walks them
  as the player will (legs 1.10–1.12, 3.07–3.08, 5.12–5.14). – Alt: hand out Strength in a story scene; open the
  Sootopolis Gym door with the turn. – None of them blocks the way on: the player passes them, or is told on the
  spot by the vanilla lines, and changing them would rework vanilla content no feedback asks about.
- **D-216 No trade evolutions** (feedback 1.31): every `EVO_TRADE` (30 entries, Karrablast/Shelmet's
  trade-partner ones included) is a level evolution. **Rule**: the level follows the evolved form's base stat total,
  next to Hoenn's own level-up evolutions of that power, so it lands in the matching level-cap segment
  (`src/caps.c`): up to ~480 → **30** (`DRACONID_TRADE_EVO_LEVEL_LOW`; Sharpedo/Crawdaunt, the Flannery cap) –
  Trevenant, Aromatisse, Slurpuff; ~485–515 → **36** (`_MID`; the Hoenn starters' final stage, the Winona segment)
  – Alakazam, Machamp, Golem (and Alolan), Gengar, Gigalith, Conkeldurr, Gourgeist (4 sizes), Escavalier,
  Accelgor, Steelix, Scizor, Porygon2, Politoed, Huntail, Gorebyss; ~525–540 → **42** (`_HIGH`; Aggron, Glalie, the
  Tate & Liza segment) – Kingdra, Electivire, Magmortar, Dusknoir, Porygon-Z; Rhyperior **48** (`_LATE`: Rhydon
  itself comes at 42). Exceptions: **Slowking 37** (Slowbro's level, D-217); **Milotic 36** although it is a 540 –
  Feebas lives only on Route 119 (cap 38) and, like Magikarp, its weak first stage is the price (Beauty still works).
  The expansion's "use the item from the bag" shortcuts on these lines (Linking Cord, Metal Coat, King's Rock,
  Dragon Scale, Up-Grade, Protector, …) are removed so the level is the one rule: Metal Coat and King's Rock are
  sold from the first counter tiers (D-218) and would otherwise make Steelix or Slowking at any level. Everstone:
  `P_KADABRA_EVERSTONE` is `GEN_3`, so an Everstone stops Kadabra like any other (the Gen 4 exception was a trade
  quirk). In-game trades and link trades just never evolve now; the Pokédex does not show methods
  (`POKEDEX_PLUS_HGSS` is off). `tools/hack/check_evos.py` checks and prints the table (docs/hack_items.md).
  Trainers: `check_party.py` has 0 errors; 11 new warnings are generic trainers 1–2 levels under the new levels
  (Kira & Dan's Huntail/Gorebyss, Thalia, Nob, Trent, Sawyer, Aaron) – left to the trainer pass that owns
  `trainers.party`. – Alt: Linking Cord item from a shop (still a gate the playtester didn't want); one level for
  all (36 would give Trevenant late and Kingdra early); the core games' "level + 1 after the pre-evolution".
  – The playtester's note: "Pokémon just evolve at a set level".
- **D-217 Branches keep an item**: where a trade shared its base with another method, the held item still picks
  the branch, now on a level-up (`EVO_LEVEL` + `IF_HOLD_ITEM`, which `GetEvolutionTargetSpecies` supports and
  which consumes the item like the trade did): Poliwhirl → **Politoed at 36 holding a King's Rock** (Poliwrath stays
  on the Water Stone); Slowpoke → **Slowking at 37 holding a King's Rock**, listed before Slowbro at 37 (the first
  matching entry wins); Clamperl → **Huntail / Gorebyss at 36 holding the Deep Sea Tooth / Scale** (no item, no
  evolution, as before). Sources: King's Rock – the Mossdeep boy (vanilla) and the battle item counter from two
  badges; Deep Sea Tooth / Scale – Captain Stern's Scanner trade (one of them, vanilla) and the counter from two
  badges (both). – Alt: plain levels with a gender or personality split (no player control); keep the trade for
  these three only. – Both branches stay reachable in one save.
- **D-218 The battle item counter** (feedback 1.33): a second clerk behind the counter of every town Poké Mart
  (Oldale, Petalburg, Rustboro, Slateport, Mauville, Verdanturf, Fallarbor, Lavaridge, Fortree, Mossdeep,
  Sootopolis) and the Battle Frontier Mart, at (1, 2) next to the vanilla clerk (the counter tile in front of it is
  a counter, so the player talks across it from (3, 2)); a third clerk between the two on the Lilycove Department
  Store 3F (the battle floor). Not the Pokémon League 1F: its counter has one talkable tile, and the Acts 6–7 work
  owns that map. The stock grows with the **badge count** (any order), so it follows the level caps: 0 → the 18
  type boosters; 2 → accuracy / damage / utility items and the branch items (D-217); 4 → Leftovers, Rocky Helmet,
  Focus Sash, Eviolite, the herbs …; 6 → Choice items, Life Orb, Assault Vest … and the first Mega Stones; 8 →
  every other competitive item (weather rocks, orbs, seeds, Loaded Dice, Clear Amulet …) and more Mega Stones;
  after the Champion (`FLAG_IS_CHAMPION`) the rest of the Mega Stones. The tiers are **one list, newest first**:
  each tier's label starts its new items and runs on through the lower tiers to one `ITEM_NONE`, so nothing is
  listed twice and new stock shows at the top. Greeting by reputation (D-103); the goodbye is the Mart clerks'.
  Booster Energy is not sold (no Paradox Pokémon to hold it). Table: docs/hack_items.md. – Alt: the expansion's
  per-item `shopCriteriaFunc` (one list, but a global rule in `items.h` for every shop); stock by town (a late
  town would have to be revisited for early items); Battle Points (the Frontier is post-game). – One script, one
  list, no C code, and the badge count is what the caps follow.
- **D-219 Prices climb with the tiers**: from the prize money a player earns per segment (all first battles:
  ~15k by Roxanne, ~61k by Wattson, ~117k by Flannery, ~209k by Winona, ~463k by Juan) an item of a tier costs
  a few percent to a fifth of what that stretch pays: type boosters **1,000** (`TYPE_BOOSTING_PRICE`, the Gen 7
  price; Charcoal and Metal Coat too), tier 2 **4,000–6,000**, tier 3 **5,000–15,000** (Leftovers 15,000), tier 4
  **20,000–40,000** (the Choice items 40,000, the most expensive held items), tier 5 and unchanged items at their
  Gen 9 prices (5,000–30,000). Only the Gen 9 branch of each price block changed. – Alt: the Gen 9 prices as they
  are (Rocky Helmet, Eviolite and Focus Sash at 50,000 when they unlock, Choice items at 100,000 – out of reach
  before the League); `I_PRICE` GEN_7 (changes every item in the game). – Prices follow the money curve.
- **D-220 Story gifts on top**: each Gym Leader hands over their type's booster after their TM (Hard Stone,
  Black Belt, Magnet, Charcoal, Silk Scarf, Sharp Beak, Twisted Spoon, Mystic Water) with a line of their own –
  one `call` in both vanilla TM paths (straight after the battle, and the later visit when the bag was full). A
  full bag only costs the booster (the counter sells it). Vanilla item balls and hidden items for battle items
  stay. – Alt: item balls on routes (new flags in a crowded range while other work adds flags too). – No new flag
  (the TM flag already makes it once), and the gift says what the Leader's type is about.
- **D-221 Mega Stones through the story** (the player's addition to 1.33): nothing before the Mega Ring (Jagged
  Pass, Act 3); the second starter's stone stays the Lavaridge traveller's gift (D-126). After the Ring, **nine
  stones lie on maps the story opens later**, at ORAS's spot where Emerald has it (Serebii's ORAS Mega Evolution
  page, 2026-09-30): Manectite – New Mauville (ORAS: the Cycling Road, passed long before the Ring); Banettite –
  Mt. Pyre 3F; Cameruptite – Magma Hideout; Absolite – Safari Zone NE; Gyaradosite – Route 123; Sharpedonite –
  Aqua Hideout B2F; Metagrossite – Mossdeep (Steven's town; Beldum is the 1% Granite Cave find); Glalitite – Shoal
  Cave; Garchompite – Victory Road B2F (Gabite's floor). The **counter** sells more (D-218): at six badges the
  stones whose ORAS spots the player passes before the Ring (Alakazite, Aggronite, Mawilite, Sablenite,
  Gardevoirite, Altarianite, Pinsirite, Heracronite) and those of early new wild species (Excadrite, Staraptite,
  Hawluchanite, Chandelurite); at eight badges Charizardite Y and the Legends Z-A stones of Hoenn and late new
  species (Skarmorite, Starminite, Chimechite, Raichunite X/Y, Absolite Z, Pyroarite, Golisopite, Barbaracite,
  Dragalgite, Glimmoranite, Golurkite); after the Champion Salamencite, the Lati stones, Galladite, Garchompite Z
  and the signature stones of the rivals, Nerine and Aster (Blazikenite, Sceptilite, Charizardite X, Feraligite).
  **Only stones of species the player can get** (the Hoenn wild tables with the Gen 4–9 additions of D-193 –
  D-197, gifts, the eggs and second starters, evolutions; Galladite as Wally's signature although the Dawn Stone
  isn't in the game yet): no Venusaurite, Blastoisinite, Beedrillite, Pidgeotite, Slowbronite, Gengarite,
  Kangaskhanite, Aerodactylite, Mewtwonite, Ampharosite, Steelixite, Scizorite, Houndoominite, Tyranitarite,
  Swampertite, Medichamite, Lopunnite, Lucarionite (Riolu is on trainers only), Abomasite, Audinite, Froslassite,
  Diancite or the other Z-A stones; docs/hack_items.md lists them to recheck against docs/hack_wild.md. – Alt: all
  stones post-game (the player wants them "throughout the story"); ORAS's exact spots (most are towns and routes
  the player passes before the Ring). – Paced like the counter tiers, and every stone has a Pokémon to use it.
- **D-222 Mega Stone details**: placed stones **replace low-value vanilla items** (Paralyze Heal, Super Repel,
  Escape Rope, Nugget, Ultra Ball, Nest Ball, Net Ball, Ice Heal, Full Heal) and keep their pickup flag's number,
  renamed after the stone – no new flags. Sold stones cost **50,000** (`MEGA_STONE_PRICE` in `src/data/items.h`,
  about a quarter of what the Winona → Tate & Liza stretch pays); stones that are only found or given stay at 0
  (not sellable). – Alt: new item balls with new flags; one price per stone. – Flags are shared with parallel work;
  one price is easy to read.
- **D-225 The Battle Frontier legends (post-game)**: Wes (Pokémon Colosseum), Red and Blue wait on
  `BattleFrontier_OutsideEast` from the Hall of Fame on (`FLAG_HIDE_BATTLE_FRONTIER_*`, set or cleared by the map's
  OnTransition from `FLAG_SYS_GAME_CLEAR`): **Wes** in the BATTLE PYRAMID's sands among the rocks (58, 22) – a desert,
  like his Orre; **Red** at the foot of the cliff below ARTISAN CAVE (29, 10), a quiet dead end by a cave mouth, like
  Mt. Silver; **Blue** by the BATTLE TOWER door (18, 15), where the toughest facility is. SCOTT invited them (his
  vanilla job is scouting strong trainers). Each battles **again whenever asked** (a YES/NO first), with the same
  team. Red is silent ("…" boxes, a line of narration), Blue cocky ("I picked the wrong POKéMON again", "Smell ya
  later"), Wes terse and a mirror of the player (he walked out on Team Snagem as the player did on Magma). Red and
  Blue are "{PKMN} TRAINER" (`TRAINER_CLASS_LEGEND`, as the PWT calls them) and fight to **`MUS_RG_VS_CHAMPION`**
  (the FRLG Champion battle – Blue's own final battle, Kanto's strongest theme); Wes is an "ORRE HERO"
  (`TRAINER_CLASS_ORRE_HERO`) and fights to **`MUS_VS_FRONTIER_BRAIN`** (the Frontier's top-fight theme). Encounter
  music: Red Elite Four, Blue Cool, Wes Intense; E4-style mugshots (Red yellow, Blue green, Wes purple); prize money
  class 25 (like the Elite Four, since the battles repeat). – Alt: once a day (three daily flags; the RTC decides
  when the post-game's best fights come back); one battle only (a dead end for the tag); `MUS_VS_CHAMPION`
  (Wallace's; the League already uses it); "SNAG MASTER" / "DRIFTER" for Wes. – A post-game gauntlet the player can
  replay, three voices the playtester will recognise, and no new flag budget beyond the three hide flags.
- **D-226 The legends' teams and levels**: Red and Blue use their **PWT Champions Tournament** teams (Serebii,
  `tools/hack/trainers/pwt/pwt_champions.json`) – species, held items and moves as listed – with **Charizardite X**
  on Red's Charizard and **Alakazite** on Blue's Alakazam (both replace a Focus Sash) and the Mega as the ace
  (last; the rest in Serebii's order). Serebii lists no abilities or natures, so those (and EVs) are picked for the
  sets (Pikachu Lightning Rod, Machamp No Guard for Stone Edge, Exeggutor Chlorophyll, …). **Wes**: exactly Espeon,
  Umbreon, Raikou, Entei, Suicune, Ho-Oh – his Colosseum partners lead, Umbreon keeps its Colosseum Confuse Ray, the
  beasts and Ho-Oh carry their signature moves (Sacred Fire, Extreme Speed, Scald / Calm Mind), Ho-Oh last as the
  ace. **Levels 82–83, the ace 85**: above everything else in the post-game (Elite Four rematch 70–75, rivals 75–80,
  gym leaders' last tier and Steven up to 80), as the post-game's top fights; the PWT's flat 50 would be the easiest
  battles of the post-game. 3 Full Restores and the Elite Four rematch AI (`Smart Trainer / Prediction / Ace
  Pokemon`). – Alt: flat 80; Lv 100; PWT items unchanged (no Megas). – The brief's "about 80, the ace higher".
- **D-227 The LEGENDS' TAG**: an **attendant beside the BATTLE TOWER door** (14, 15; the Tower attendants' sprite)
  hosts it. The player picks a partner **from the legends they have beaten** (a `dynmultipush` menu of those plus
  CANCEL); the other two are the opponents, so all three pairings (six partner/opponent pairs) are reachable. The
  attendant heals the party, the player walks onto the mat in front of the Tower, and under a fade the partner steps
  up beside them and the other two face them (the legends' own objects, moved with `setobjectxyperm` and sent back
  home afterwards). **Three Pokémon each** (the player picks three; `Multi Party: Half`, as round 1's Sootopolis multi
  battle): each legend has a doubles-minded **tag team** of three, which is both his `PARTNER_*` team and his
  `TRAINER_*_FRONTIER_MULTI` team – Wes Espeon (screens) / Umbreon / Ho-Oh, Red Pikachu (Fake Out) / Venusaur /
  Mega Charizard X, Blue Arcanine / Gyarados (two Intimidates) / Mega Alakazam; no Earthquake (it would hit the
  partner). A loss whites out like any trainer battle. – Alt: SCOTT hosting in his house on the west side (the
  house is 6×8, and the battle would happen far from the legends); a second SCOTT by the Tower (two SCOTTs at once);
  the legends offering the tag themselves (no host, as the brief's default asks for one); full six-Pokémon teams
  (the expansion supports them, but 12 against 12 is a very long battle and unlike every other multi battle here).
- **D-228 Wes's art and Blue's back pic**: no third-party art. Wes is built from **Steven's** sprites (silver spiky
  hair, a suit to turn into a coat): the walk sheet gets whiter hair, black sunglasses, a navy coat down to the knees
  (the suit's black and grey inside the outline) with light lapels and a dark shirt; the front pic the same, with the
  coat's tails drawn over the legs down to a hem (trousers charcoal below it) and the purple stripes as light lapels;
  the back pic (Steven's four frames, `sBackAnims_Hoenn`) the same colours plus the lens over the visible eye. Blue's
  FRLG champion pic has no back pic, so his partner back pic is Steven's recoloured into Blue's orange-brown hair
  and slate shirt (colours from `champion_rival_frlg.pal`). Red uses his FRLG sprites; Blue's FRLG overworld sheet is
  registered for Emerald as `OBJ_EVENT_GFX_FRONTIER_BLUE` (vanilla's `OBJ_EVENT_GFX_BLUE` exists only in FRLG builds: in
  an Emerald build it has no graphics info, so the object is invisible and talking to it crashes). – Alt: Maxie's long-coat pic
  with a new head (a head swap across palettes); Red's back pic for Blue (his cap and backpack would have to be
  redrawn). – The closest in-repo silhouettes, every step a kitbash recipe; Wes and Steven differ at a glance by the
  shades, the long navy coat and the light collar.
- **D-229 Trainer ids and the save layout**: the legends take ids 925–930 (three singles, three tag teams;
  `TRAINERS_COUNT_EMERALD` 931) and `MAX_TRAINERS_COUNT_EMERALD` goes from 928 to **944**, so the finale's two
  upcoming ids fit with room to spare. Trainer flags are save flags: 16 more flags move the system flags up by 16
  and `SaveBlock1` grows by 4 bytes (15576 → 15580, `test/save.c`), so saves from before the change don't carry over
  (as with D-101). The partners are `PARTNER_WES`/`_RED`/`_BLUE` (14–16, `PARTNER_COUNT` 17). – Alt: reuse the
  unused vanilla `TRAINER_RED` (851; still no room for the rest); 936 (only three spare ids). – One raise for this
  round.
- **D-230 The egg ceremony in the shrine** (feedback 1.38; supersedes D-102's ceremony): the prophecy and the
  mission stay in the Elder's house; then "We go up together" and a warp puts the player at the shrine's entrance,
  where the Elder stands before the Rayquaza statue with the three eggs at his feet (the egg objects moved there
  from his house; the dragon egg sprites stay) and Aster waits beside them. He presents them as eggs clan
  travellers brought home from far lands – **Deino's from Unova, Dreepy's from Galar, Jangmo-o's from Alola**,
  where each line was first found – instead of "brought up from Meteor Falls", and each egg's description names
  its region. The choice and its confirm, Nerine's counter egg kept aside and Aster's leftover egg (D-105) and every
  flag and var the old ceremony set are unchanged; the ceremony ends with the Elder sending the player to Prof.
  Birch. No new `DRACONID_STATE_*` value: the shrine arms the ceremony when the state is `CLOCK_SET` and the Elder
  is there (`FLAG_HIDE_DRACONID_SHRINE_ELDER` clear, done by the house scene), because the emulator tests of every
  act set the state numbers literally. – Alt: the player walks up to the shrine alone (v1); a new state value
  (renumbering 3–8). – Regidrago will wait in a sealed part of this cave (feedback 1.30), where the egg must come
  from; the warp keeps the Elder "taking" the player up.
- **D-231 Hatch after 5 steps** (feedback 1.38; supersedes D-034's rite): after the ceremony the egg hatches on the
  `DRACONID_EGG_HATCH_STEPS` (5)th step **outdoors** (step hook `Draconid_ShouldHatchEgg`, counter
  `VAR_DRACONID_EGG_STEPS`, the old `VAR_UNUSED_0x4083`): "Oh? The egg is moving!", the normal hatch animation, then
  the hatchling is raised to Lv 5 as before. Steps in the shrine or a house don't count; before the Running Shoes
  the village is the only outdoor map the player can reach, so the hatch always plays there, right after a step –
  and the old woman with the Running Shoes then hurries over to the tile the player just left (always free) instead
  of walking up to the cave mouth. – Alt: count steps on every map (the hatch could play indoors, where she can't
  come); a fixed spot the player has to walk to. – The playtester: "have the egg hatch after like 5 steps".
- **D-232 Aster's hatchling**: Aster walks out of the shrine ahead of the player ("Mine is already stirring") and
  shows her hatchling at the Draconid Pass battle – its name and cry, and her "long way to climb" line from the
  old rite; her tutorial battle is unchanged. – Alt: her egg hatches a beat after the player's (she would have to
  be on screen wherever the player's egg hatches). – Keeps the hatch about the player and gives her the bridge.
- **D-233 Prof. Oak gives the second starter** (feedback 1.38; supersedes Birch in D-042 and D-115): Prof. Oak,
  visiting his old friend Birch in Hoenn, waits outside the Rustboro Gym after the Stone Badge with Charmander
  (Kanto), Totodile (Johto) and Treecko (Hoenn) at `SECOND_STARTER_LEVEL`; same choice flow and
  `VAR_SECOND_STARTER`. He sees the Magma uniform and is puzzled but kind: Birch vouched for the player (Birch's v1
  line "I'll trust that version of you" is now quoted by Oak). Renamed `LOCALID_RUSTBORO_OAK`,
  `FLAG_HIDE_RUSTBORO_CITY_OAK` (same flag 0x40), `RustboroCity_Gym_EventScript_DraconidOakWaits`. Oak's FRLG
  overworld sprite was built for FireRed only; it and its `NPC_WHITE` palette now build for Emerald too. Birch keeps
  the Route 101 rescue and the lab (Act 1); the Lavaridge traveller still brings the Mega Stone (D-126), "for the
  partner PROF. OAK gave you". – Alt: Oak brings the Mega Stone instead (feedback row 1.37's first reading).
  – The playtester: "have the professor who gives it to you be oak since he already has a in game sprite".
- **D-234 More rival battles: the schedule** (feedback 1.32 "a few more Brendan and May battles", 1.34 "more Wally
  battles"): two more each in Acts 1–5, placed where a rival had no fight for two segments and the story gives them
  a reason to be there, on the player's only way forward (segment = level-cap band, docs/hack_trainers.md).
  **Brendan**: Route 104 at Mr. Briney's cottage (S2, after Mr. Stone's letter – he told his dad, and Birch's "give
  them a chance" makes him angrier; the vanilla rival spot and trigger, armed again by the Devon scientist) and
  Jagged Pass as the player walks out of the Magma Hideout (S7, Groudon has just woken: the ground shook "all the
  way to LITTLEROOT"). **May**: Lavaridge before the Go-Goggles (S5, the vanilla scene out of the Gym: the town
  nearly lost its homes to MT. CHIMNEY) and Mossdeep outside the Space Center (S8, Brendan called her after the
  raid; her one crack is "STEVEN is sticking up for you. …Why would he?"). **Wally**: Route 112 at the cable car
  (S4, after Meteor Falls, where the Magma grunts had blocked it – he wanted the Lavaridge hot springs for his
  lungs – and Magma has gone up the mountain) and Route 120's south bridge (S6, after the Weather Institute; the
  bridge is a two-tile cut of every way from Fortree to Lilycove). Every segment from S1 to S8 now has a rival
  fight; the closest pair is Wally's Route 120 and Lilycove battles (Route 121 apart; the Lilycove one is talk-to,
  so the player picks when). The fights are marked done by their own trainer flags, so no
  state value was added or renumbered and none of the free flags (0x36–0x38, 0x44, 0x4C, 0x4D) is used; scene-only
  objects use temp flags (D-136). Out of the uniform era, Wally's Victory Road battle stays with Acts 6–7. – Alt
  (the brief's list): May in Slateport after the museum (right before her Route 110 fight, which is where she first
  sees the uniform); Brendan on Route 117 or at Fortree (Route 117 is a dead end off the way, Fortree comes right
  after his Route 119 fight); Wally in Verdanturf (optional, easily missed) or at Mt. Pyre's foot (right after his
  Lilycove fight, no level growth). – On the way, spread out, and each one reacts to something Magma just did.
- **D-235 Can the new fights be lost?** The existing rule: a fight on its own is a must-win vanilla battle (a loss
  whites out and the trigger is still armed when the player comes back, as in Rustboro, Route 110, Route 119 and
  Petalburg), a fight inside a scene the player can't come back to is `trainerbattle_earlyrival` with
  `RIVAL_BATTLE_HEAL_AFTER` (a loss heals and the rival's line follows the result, D-122/D-124). So Route 104,
  Route 112 and Route 120 are must-win (the boat, the cable car and the way to Lilycove bring the player back);
  Lavaridge (straight out of the Gym, and the Go-Goggles are needed for the desert), Jagged Pass and Mossdeep (the
  story never returns to the hideout or the Space Center door) are early-rival. Each scene also sets its trainer
  flag at its end, so a mashed test run with no whiteout can't replay it. – Alt: all must-win (a lost Jagged Pass or
  Mossdeep fight would be gone for good); all early-rival (rivals would stop blocking anything).
- **D-236 Wally in the uniform era** (feedback 1.34 "really hostile … trying to stop Team Magma and protect Hoenn,
  not knowing your true mission"; supersedes D-135's "Wally trusts what he saw"): normally gentle, now angry and
  brave. Mauville: "You helped me catch RALTS! How could you join TEAM MAGMA?", his uncle wants the player away
  from him and from Verdanturf, and his PokéNav registration is to know where to find the player "if MAGMA hurts
  anyone"; Route 112: he won't let the player up the mountain; Petalburg: the smoke over Mt. Chimney, "you'll have
  to get past me"; Route 120: the Weather Institute; Lilycove: the Key Stone is "to protect people". Short, plain
  sentences like Brendan's and May's (docs/hack_voices.md); his health shows (the hot springs, "I didn't cough
  once") but not as self-pity. His Lilycove line says KIRLIA evolved (he had Kirlia since Petalburg). – Alt: Wally
  scared but trusting (D-135, the round 1 story's version). – The playtester's note.
- **D-237 No Latis before the finale** (part of feedback 1.25: "they shouldn't get their Lati until close to the
  climax"; supersedes the Lati part of D-106 and D-187): Latios and Latias are gone from every Brendan / May team
  and partner team of Acts 1–5 (Route 119, the Lilycove double, the Space Center tag, the Sootopolis partners). The
  singles and the double keep five; the half parties that need three take a member of the given team instead:
  Brendan's Space Center Mightyena, the Sootopolis partners May's Tropius (Wide Guard for the multi battle) and
  Brendan's Swellow. The post-game lab teams keep theirs; the Acts 6–7 work brings the Latis in near the climax.
  – Alt: another species in the sixth slot (the round 1 notes give each rival exactly six). – The note.
- **D-238 Teams of the new fights**: from the round 1 rosters, growing between the neighbouring fights at the top of
  each segment's band (the rivals are bosses, default IVs): Brendan Route 104 Poochyena / Taillow / Slakoth 17,
  Grovyle 19 (between Rustboro's four at 10–13 and Mt. Chimney's five at 27–29); Jagged Pass Mightyena / Swellow /
  Magcargo 42, Slaking 43, Sceptile 44. May Lavaridge Wailmer / Beautifly / Skitty / Tropius 31, Combusken 33
  (Tropius joins); Mossdeep Delcatty / Beautifly 45, Tropius / Wailord 46, Blaziken 47 with its **Blazikenite** –
  her Mega shows up in the same segment as Brendan's at the Space Center (D-106: the rivals' Megas from Mossdeep).
  Wally Route 112 Roselia / Swablu 25, Kirlia 27; Route 120 Roselia / Altaria / Magneton / Delcatty 36, Kirlia 38
  (Gallade only in Lilycove, with the Dawn Stone story). `check_party.py --caps --proc` 0 errors. – Alt: May's
  Mega only at Sootopolis (her Mossdeep fight would be weaker than Brendan's tag half a segment earlier).
- **D-239 The rivals' bedrooms**: after Lilycove both go home (act4) and stay until the Hall of Fame, so their
  Littleroot bedroom lines only meet the uniform and the revealed player: in uniform Brendan tells the player to
  get out before his dad sees them and May won't let them out of her sight; after the turn Brendan is awkward
  ("Don't make me say sorry twice, okay?") and May cheerful. Each object's `script` in `map.json` points at its own
  line (both used to run May's vanilla text). – Alt: a reputation branch inside the vanilla shared script (it can't
  tell the two houses apart without a map check).
- **D-240 Gen 4–9 on ~60% of generic trainers** (feedback 1.40, docs/hack_trainers.md "Gen 4–9 swaps, second
  pass"): 269 of the 434 generic trainers (62%; 60–65% in every segment) have a Gen 4–9 Pokémon – a species of
  Gens 4–9 outside the Hoenn Pokédex, so Roserade or Gallade don't count – in their first battle and every rematch
  tier, and from S5 on every such block with 4+ Pokémon has **two** (D-195's trainers and tiers included; a rematch
  chain's second one comes from a family its earlier tiers don't have, so the tiers still only grow). Same rules as
  D-195 (area, class, ORAS roster, ace kept, level / IVs / EVs / nature kept), plus: the new stage has at least 80%
  of the replaced Pokémon's base stat total (no Skrelp at 39 – a line may still grow through the tiers), and moves
  over 90 power are held back before S7 as the batches do. The swaps are data (`tools/hack/trainers/gen49_plan.py`)
  and the Pokémon are written by rule (`gen49.py`), so the pass can be rerun and checked (`--coverage`). The
  trade-evolution warnings (D-216) are fixed by pre-evolving (Clamperl holding its Deep Sea item, Seadra, Machoke,
  Graveler), not by raising levels. – Alt: one per team at every size (a big late team would show a token
  newcomer); raise the under-level Pokémon to the new evolution levels (out of the segments' route bands); new
  species chosen at random per class. – The playtester wants the new species to "spice things up"; 60% leaves a
  share of all-Hoenn teams, and two in the bigger teams makes them visible.
- **D-241 Gym trainers get their gym's type**: all 57 trainers inside the gyms have a Gen 4–9 Pokémon of the gym's
  type (Roggenrola, Sawk, Pawmo, Larvesta, Gumshoos, Staraptor, Musharna, Floatzel …), also where the trainer's
  class is another type – Vivian, a Battle Girl in Wattson's gym, gets electric/fighting Pawmo; Danielle's D-195
  Gurdurr in the fire gym became Heatmor; the Mossdeep Hex Maniacs get psychic ones. The species pool has only
  five psychic lines (Bronzor, Munna, Woobat, Sigilyph, Bruxish), so Mossdeep repeats them. – Alt: the class's type
  (Battle Girls with fighting types in every gym); only some gym trainers. – A gym is one theme, and the newcomers
  should read as part of it.
- **D-242 Grunts get one Gen 4–9 Pokémon** (reverses D-195's grunt exclusion): 44 of the 49 grunts swap one
  Pokémon – Magma for fire / ground / rock (Salazzle, Excadrill, Heatmor, Coalossal, Mudsdale, Hippowdon …, the
  Magma Hideout's own Carkol / Salandit / Heatmor lines among them), Aqua for water / dark (Clawitzer, Toxapex,
  Barraskewda, Kilowattrel, Palafin, Thievul, Skuntank, Zoroark …). Never the Poochyena / Zubat / Numel / Carvanha
  lines and never the ace, so the five grunts whose teams are only those lines keep them (Museum, both Mt. Chimney
  grunts, Jagged Pass, Aqua Hideout 8). Purrloin is not in the species pool (not wild in Hoenn, not on an ORAS
  Hoenn trainer), so the Nickit, Stunky, Scraggy and Zorua lines are the dark types. – Alt: two for the big grunt teams; only
  Magma grunts (the player's side). – D-195 kept grunts as they were to keep the teams' identity; with the
  signature lines kept on every team, one newcomer adds the new species without losing it, and grunts are the
  trainers the player fights most in Acts 3–5.
- **D-243 The rivals' PokéNav calls follow the story and the reputation**: Brendan's, May's and Wally's Match Call
  texts (vanilla neighbour chat and tips) are replaced by `data/scripts/draconid/rival_calls.pory`. Each rival has two
  tables in `src/pokenav_match_call_data.c`: one while the player wears the uniform and one after the Sootopolis
  turn (`VAR_DRACONID_REPUTATION` ≥ `REPUTATION_REVEALED`); an entry is used once the rival's own state var
  (`VAR_MAY_STATE` / `VAR_BRENDAN_STATE` / `VAR_WALLY_STATE`) has reached its value and its flag (badges, the Orb,
  Victory Road, the Hall of Fame) is set, and the last such entry wins. In uniform they keep the number to watch a
  MAGMA grunt (hostile, one crack per rival – docs/hack_voices.md); after the turn they call as friends and point the
  way (Juan, the League through Victory Road, the lab rematch). The contact descriptions "RAD NEIGHBOR" become
  "NORMAN'S KID" / "BIRCH'S KID" (neither is the player's neighbour in v2). – Alt: keep the vanilla flag-gated
  tables and only rewrite the texts (vanilla's gates are story events round 1 moved or removed); one table with a
  reputation condition per entry (harder to read). – The playtester asked for the rivals to be hostile while the
  player is in uniform (follow-up 4); the calls were the last friendly lines left.
- **D-244a Who knows the player's mission** (follow-up 20): until the public reveal at Sootopolis only the Draconids
  (the Elder, Aster, Nerine, the villagers), Prof. Birch and Prof. Oak know the player is undercover. Everyone else
  may suspect – May's small crack, Steven thinking the player is "the strongest TEAM MAGMA grunt he's ever faced" –
  but never knows. Oak says so at Rustboro (the Elder's letter told Birch, Birch told Oak, nobody else; Brendan
  mustn't know yet); Brendan's Space Center call quotes Steven's "strongest grunt" instead of "you let us win".
  – Alt: Steven guesses the truth at the Space Center (the earlier version). – The playtester: "I don't think anybody
  should know that you're undercover besides the Draconids and Birch and Oak."
- **D-250 Steven is the Champion** (the playtester: "is Steven the Champion and if not, can we make him the
  Champion?"; supersedes D-175): **Steven** waits in the Champion's room (his sprite, `LOCALID_CHAMPIONS_ROOM_STEVEN`)
  and walks the new Champion into the Hall of Fame. His battle reuses the vanilla post-game id `TRAINER_STEVEN`
  (nothing in the story used it: the Space Center tag is `TRAINER_STEVEN_MOSSDEEP`, and his vanilla Meteor Falls
  battle is gone, D-252) with his **ORAS Champion roster** (Serebii: Skarmory, Claydol, Aggron, Cradily, Armaldo,
  Metagross @ Metagrossite) at the S9 Champion band (57–59, Mega Metagross 60 = the cap), Elite Four-style sets built
  from his ORAS moves (items, natures, EVs), 4 Full Restores, `Smart Trainer / Prediction / Ace Pokemon`, class
  CHAMPION (the Champion's music, battle arena and prize money). He Mega Evolves in the first battle, unlike the
  Elite Four (D-173): ORAS's Champion does too, and he is the last wall before the Hall of Fame. His lines pay off
  the story as the player lived it: a TEAM MAGMA grunt walked into GRANITE CAVE to deliver his mail; at the SPACE
  CENTER the player was the strongest MAGMA grunt he had ever faced (he did **not** know – nobody but the
  Draconids, Birch and Oak did; only "your POKéMON trusted you far too much" as a flicker of doubt); only at
  SOOTOPOLIS, when the uniform came off in front of Maxie, did he understand; "Today, I want to battle the real
  you." After the battle, "In GRANITE CAVE, I said that kind of trust is hard to fake. It was never an act, was
  it?" Brendan, Prof. Birch and May come in around him exactly as before (D-159). Every text that named Wallace
  as Champion is fixed: the Champion's room and Hall of Fame (the vanilla labels retold), the Sootopolis PC's
  "WALLACE is rumored to be the toughest TRAINER in HOENN", Wallace's Match Call entry (D-252) and Steven's calls
  (a new one once the player has all eight badges, "I'll be waiting at the very top. Come as you really are.", and
  his Hall of Fame call); the credits, TV shows and the Pokédex rating never named him. – Alt: keep Champion Wallace
  (vanilla Emerald, D-175); Steven as a battle after Wallace (two Champions in one League). – The playtester's
  question; the story already calls Steven "the CHAMPION of HOENN himself" at the Space Center (Tabitha, Act 5) and
  overlevels him there for that reason (D-108), and ORAS made him the Champion.
- **D-251 The Champion's rematch**: after the Hall of Fame the League loads Steven's **ORAS post-game roster**
  (Skarmory, Claydol, Carbink, Aerodactyl, Aggron 77, Mega Metagross 79 – Serebii's levels) as
  `TRAINER_STEVEN_REMATCH`, through `sPostgameRematches` like the Elite Four (D-174), so the script names
  `TRAINER_STEVEN` both times. The id is **976** and `MAX_TRAINERS_COUNT_EMERALD` goes from 944 to **992** (a
  multiple of 16; ids 937–975 are left for the other round 1 v2 follow-ups): 48 more trainer flags move the system
  flags up and `SaveBlock1` grows by 4 bytes (15580 → 15584, `test/save.c`), so saves from before the change don't
  carry over (as with D-101, D-229). The rematch is Steven alone: new lines ("A few new partners have joined us,
  too. I found them among the stones, of course."), the battle, then he walks the player straight into the Hall of
  Fame – Brendan, May and Prof. Birch don't come in again. – Alt: the vanilla flow, which replays the rival scene
  on every visit (May's "Did I miss it?!" and Birch's first-Champion lines would repeat after the finale, when the
  rivals are waiting in Littleroot); a Steven rematch somewhere else (Meteor Falls, his vanilla spot). – The League
  is where the Champion is, and the Elite Four already work this way.
- **D-252 Wallace, Sootopolis's guardian, and Steven's Meteor Falls spot**: **Wallace** keeps his Act 5 role
  (Waterfall), and Act 7 has him battle the player at the Sky Pillar before the finale
  (`TRAINER_WALLACE_SKY_PILLAR`, the Act 7 branch), so his post-game battle is his **rematch**. Once the finale is
  over (`VAR_DRACONID_FINALE_STATE` ≥ `FINALE_STATE_METEOR_DESTROYED`, like the other post-finale scenes; after the
  Hall of Fame alone he would stand in two places) he stands at the CAVE OF ORIGIN's entrance, (31, 19) between the
  lamp posts right before the cave's Expert – far from the Act 5 turn scene's objects on the Gym island (y 33–36) –
  as a new object (`LOCALID_SOOTOPOLIS_POSTGAME_WALLACE`) hidden by `FLAG_TEMP_1` until then (set by
  `SootopolisCity_OnTransition`), so no save flag is spent. He handed the Gym back to his mentor Juan to watch over
  the cave (vanilla's "something came up" and Juan's "compelling reason"), and a line looks back at the Sky Pillar:
  "At the SKY PILLAR, I tested the one the prophecy chose. Today, I simply wish to battle the TRAINER who stands as
  STEVEN's equal." He battles **whenever asked** (YES/NO, like the Frontier legends, D-225). The battle reuses
  `TRAINER_WALLACE` (the vanilla Champion id, free now) with his **Emerald Champion team** – which is ORAS's
  "Sootopolitan Wallace" (Serebii, Route 131) – clearly above the Sky Pillar version: Lv 75, Gyarados 76, Milotic 78,
  his rain sets (Ludicolo with Energy Ball and Focus Blast for coverage), 3 Full Restores, and **Mega Gyarados**
  (Gyaradosite; Dragon Dance, Waterfall, Crunch, Earthquake, Adamant) – the playtester's "wallace can use mega
  gyrados", as at the Sky Pillar, and every post-game boss carries a Mega (the Elite Four rematch, the leaders' last
  tier, the rivals, Steven; Milotic has none). He gets his ORAS title as a new class, **SOOTOPOLITAN** (50 money,
  Ultra Ball), and keeps the Emerald Champion battle theme (`MUS_VS_CHAMPION`, his own theme in Emerald). His Match
  Call entry, registered by that battle as in vanilla, reads "SOOTOPOLITAN" at Sootopolis, and his call talks about
  Steven and the cave. **Steven's Meteor Falls spot** becomes a short chat: his vanilla battle there
  (`TRAINER_STEVEN`, now the Champion) and its texts are removed; after the Hall of Fame he searches for stones in
  his cave, points to the League rematch and, after the finale, remembers watching the sky break apart from there;
  before the Hall of Fame he is hidden (`FLAG_TEMP_1`, the map's new OnTransition), since he waits at the League. –
  Alt: shown from the Hall of Fame on (before his Sky Pillar battle); class LEADER (ORAS's Gym Leader Wallace; Juan
  leads the Gym here), CHAMPION (contradicts D-250) or {PKMN} TRAINER (Brendan and May's rival theme); Wallace
  beside the Expert at (30, 18) / (32, 18) (walled in behind him) or at (33, 19) off the lamp posts (keeps the
  Expert talkable, but reads as a bystander – post-game the Expert's line is lost behind Wallace instead); the
  vanilla Wallace object (its flag is set by Juan's badge and its position follows the aftermath states); a battle
  once per Hall of Fame; Steven's cave battle kept under another id (a second Champion rematch). – The brief's
  post-game Wallace, with the ORAS title the data already had.
- **D-266 Megas are the gimmick: no Terastallization, no Dynamax** (follow-up 26): `B_ALLOW_TERASTALLIZATION` and
  `B_ALLOW_DYNAMAX` (new, `include/config/battle.h`) are FALSE, and `CanTerastallize` / `CanDynamax` return FALSE for
  every battler outside the test suite. The trainer data never set a Tera type or Dynamax level (`check_party.py`
  rejects the fields), but the expansion lets any opponent whose Pokémon wasn't built from trainer data use them: its
  "don't use a gimmick" marker is only written by the trainer party loader, so AI-controlled wild Pokémon (roamers,
  the finale's legendaries, smart wild AI) and Battle Frontier facility teams could Terastallize (Tera type = their own
  type). – Alt: set the Tera type to `TYPE_MYSTERY` on every created Pokémon (touches every creation path; one missed
  path brings it back); remove the Tera Orb only (opponents don't need one). – The playtester: "no teras or
  dynamaxing/gigantamaxing". The test suite keeps testing both (`TESTING`), so `make check` is unaffected.
