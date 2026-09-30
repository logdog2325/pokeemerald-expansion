# Draconid Emerald – story-lock audit (feedback 1.23)

> "make sure you can actually get to the next place without stuff from Emerald blocking you so you're not
> story locked, or you get transported to the next place without stuff blocking you" – playtester, round 1

Round 1 moved, removed and replaced many vanilla events, and vanilla Emerald hides and moves its path
blockers with the flags and vars those events set. This audit walks the whole v2 story (Acts 1–5, the
village to Juan's badge) with a checker and fixes what blocks the way. Decisions: D-213 – D-215.

```sh
python3 tools/hack/check_progression.py            # every leg + the warp check; exit 1 on a lock
python3 tools/hack/check_progression.py --leg 4.16 # one leg, with its notes and guesses
python3 tools/hack/check_progression.py --markdown # the leg table below
python3 tools/hack/check_progression.py --state 4.16 --grep SLATEPORT   # simulated flags/vars at a leg
python3 tools/hack/emu/play.py tools/hack/emu/tests/progression.play -o DIR   # the fix, in the game
```

## How the checker works

`tools/hack/check_progression.py` reads the real project data (compiled event scripts including the `.inc`
Poryscript writes, `map.json`, layouts, metatile behaviours, constants through the C preprocessor) and the
story table `tools/hack/progression.json`. Details are in the script's docstring; in short:

- **Story table** – 74 legs in v2 story order plus 5 side trips. A leg names the scene(s) that happen first
  (their script labels; the checker finds the object, coord trigger, sign or OnFrame entry that starts each)
  and the badges/HMs the player has by then; then the player walks to where the next leg's first scene
  starts. Fields: `to` (a tile, a map or a label instead of the next scene), `then` (where a scene with a
  YES/NO or a boat ride leaves the player), `expect` (flags/vars/items the scene must set: badges, HMs, the
  Magma Emblem …), `pre` (what C code does before a scene, with the reason), `side` (a way back or the way
  on: checked, then undone), `puzzles` (gyms whose puzzle is C code: only getting in is checked).
- **Flag/var simulator** – starts from the new game (`EventScript_ResetAllMapFlags` + the Draconid setup),
  then runs every scene statically: set/clear/var ops, `removeobject` (= the object's flag), items, trainer
  battles, call/goto/conditionals/switch; entering a map runs its OnTransition/OnLoad/OnResume. A condition
  the state decides takes its branch; an unknown one (YES/NO, multichoice, a battle's outcome) takes both,
  keeps a value written on one side only (the player takes the path that moves the story on) and is listed
  as a guess (`-v`). Each scene is checked: can it start (object shown, trigger var matching, OnFrame entry
  due), does it set what the table expects, does an OnFrame scene move its var on (else it would restart
  every frame).
- **Reachability** – a breadth-first search over tiles across maps: connections, warps as the engine takes
  them (doors walked into from below, arrow warps, step warps), dive/emerge (incl. `setdivewarp`), holes,
  Fly from outdoors to towns reached before. Each map is seen after its load scripts ran on the simulated
  state (`setmetatile`, `setmaplayoutindex`, `setobjectxyperm`, temp flags cleared). Blocked by collision,
  elevation, one-way ledges and directional tiles; objects whose flag is clear (unless talking to them makes
  them leave or step aside – an item ball, a Devon Scope Kecleon, the Space Center's stair guard); coord
  triggers whose var matches and whose script walks the player back; water, waterfalls, dive spots, Strength
  boulders, Rock Smash rocks and Cut trees unless the **HM is in the bag and its badge is won**
  (`src/field_move.c`; no Pokémon needs to know the move); Acro Bike rails / bumpy slopes and Mach Bike mud
  slopes unless a bike is in the bag. A blocked leg is searched again with every obstacle passable at a cost,
  and the first obstacle on the cheapest path is reported with what clears it (the flag or var and every
  script that writes it). If a coord scene the player can reach clears the way, it is triggered – on the
  path it is part of the walk (Route 121's Aqua grunts), off the path it is a **detour** the story doesn't
  lead to, and counts as a lock.
- **Warps** – every `warp`/`warpsilent`/`warpwhitefade`/… destination in the round 1 scripts and every warp a
  table scene took: the tile is walkable and joins an exit of its map (no closed pocket). 13 checked.

Not modelled (a note on the leg where it matters): gym puzzles (Mauville's barriers, Petalburg's room doors,
Mossdeep's spinners, Sootopolis's ice – the table lists them under `puzzles`), sea currents, the party, wild
battles. The checker was tested by taking single commands out of the scripts: without the Meteor Falls
scene's `setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA` leg 3.01 reports the Route 112 grunts; without Maxie's
`giveitem ITEM_MAGMA_EMBLEM` the summit scene becomes an OnFrame loop and the Jagged Pass guard blocks leg
4.15; without `FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE` Wallace and the locked Gym door block 5.14 and the
Waterfall the way to Victory Road; without Peeko's rescue Mr. Briney's scene can't start.

## What blocked, and what changed

| # | Leg | Found | Fix |
|---|---|---|---|
| 1 | 4.16 Magma Hideout → Aqua Hideout | **Detour.** Maxie's call after the promotion sends the player to Aqua's hideout in Lilycove, but vanilla keeps two grunts in its entrance (Aqua Hideout 1F (13, 11), (14, 11)) until the Slateport harbor scene (`SlateportCity_Harbor_EventScript_AquaEscapeScene`: Archie steals Stern's submarine, `setflag FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_1/2_BLOCKING_ENTRANCE`), which vanilla set up in the Magma Hideout and nothing in the v2 story leads to. The checker: *"the way opens only after SlateportCity_Harbor_EventScript_AquaEscapeTrigger3 on SlateportCity_Harbor (8, 14), off the path"*. | D-213: Archie takes the submarine off-screen. `MagmaHideout_4F_EventScript_Maxie` no longer sets up the Slateport scenes (Stern and Gabby & Ty in the city, `VAR_SLATEPORT_CITY_STATE`/`VAR_SLATEPORT_HARBOR_STATE` 1); it calls `MagmaHideout_4F_EventScript_DraconidAquaTakesSubmarine` (`data/scripts/draconid/progression.pory`), which sets what the harbor scene left set: both states 2, Stern in the harbor (his vanilla "Why…" line), `FLAG_MET_TEAM_AQUA_HARBOR`, `FLAG_HIDE_LILYCOVE_MOTEL_SCOTT`, the two entrance grunts hidden. The Aqua Hideout's own scene still shows the submarine leave with Archie, and Nerine and Maxie's next call already speak of it. |

Checked and kept (vanilla requirements the v2 order still meets; no change):

- **Norman's four badges** – `PetalburgCity_Gym_EventScript_Norman` battles at `VAR_PETALBURG_GYM_STATE` 6: the Wally
  tutorial (2) plus the four badges' `addvar`s; the checker expects the Balance Badge from the scene (4.02).
- **Route 112 cable car grunts** – hidden by the Meteor Falls scene (act3); **Mt. Chimney → Jagged Pass**, the
  Mega Ring trigger and the cable car back (side trip 3.03b) are open.
- **HM Strength for the Magma Hideout** (its 1F boulders) – vanilla too. The Rusturf Tunnel reunion hands it over
  once the rocks are smashed, and the only land route from Lavaridge back to Petalburg for Norman (no Surf yet)
  runs through that tunnel (legs 3.07–3.08; `pre` stands in for the C that counts the smashed rock).
- **Mr. Briney** after Peeko's rescue (2.07), both boat rides back (side trips 2.07b, 2.10b), the way back
  through Petalburg Woods from the outpost door (1.14b).
- **Kecleons** (Route 119/120, the Fortree Gym) go with the Devon Scope from Steven (4.08); **Route 121's Aqua
  grunts** leave when the player walks up to them (4.09).
- **The Jagged Pass guard** opens the hideout for Maxie's emblem (4.15); **the Space Center's stair guard**
  steps aside after the rank test (5.03).
- **Sootopolis** – in by diving (Route 126); after the turn Archie and Maxie must both be talked to before the
  Gym door unlocks (`FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE`, vanilla), then Wallace gives Waterfall and steps aside
  (5.12–5.14); Waterfall opens the way to Victory Road (side trip 5.15b, where Acts 6–7 take over).
- **No OnFrame loops** in any scene the table plays or the walks pass; all 13 warp destinations are open.

## In the emulator

`tools/hack/emu/tests/progression.play` (from `rustboro_done.ss`): Maxie's promotion in the Magma Hideout, then
the flags (`VAR_SLATEPORT_*` 2, the entrance grunts hidden, Stern in the harbor), a walk from the Aqua Hideout
landing (13, 12) north through the grunts' tile to (13, 9), and Stern's line in the Slateport harbor (no theft
scene left, no Archie or submarine). `act4.play` expects the new states after the promotion. The chain opening →
route103 → woods → rustboro → act2 → act3 → act4 → act5 → progression passes.

## Extending (Acts 6–7)

Append legs to `tools/hack/progression.json` with ids `6.xx` / `7.xx`: a scene label per leg (the checker finds
where it starts; give `at`/`map`/`talk` when a label is used in several places), `expect` for badges, items and
states the next leg needs, `then` where a YES/NO or a ride decides where the player ends up, `side: true` for
ways back. Put gym puzzles under `puzzles`. Rerun the checker and paste `--markdown` below.

## The legs (Acts 1–5)

Generated by `python3 tools/hack/check_progression.py --markdown` (after the fix). "Walk" is from where the
leg's scenes leave the player to where the next scene starts.

| Leg | What happens (the scenes, then the walk) | Badges / HMs | Walk | Result |
|---|---|---|---|---|
| 1.01 | Bedroom: the night prologue, Aster at the door<br>`DraconidVillage_PlayersHouse_2F_EventScript_WakeUp` | 0 / – | DraconidVillage_PlayersHouse_2F (3, 4) → DraconidVillage_PlayersHouse_2F next to (5, 1) | ok, 4 steps via DraconidVillage_PlayersHouse_2F |
| 1.02 | Set the wall clock, go to the Elder<br>`DraconidVillage_PlayersHouse_2F_EventScript_WallClock` | 0 / – | DraconidVillage_PlayersHouse_2F (5, 2) → DraconidVillage_EldersHouse (entering) | ok, 32 steps via DraconidVillage_PlayersHouse_2F, DraconidVillage_PlayersHouse_1F, DraconidVillage, DraconidVillage_EldersHouse |
| 1.03 | Egg ceremony, go to the shrine<br>`DraconidVillage_EldersHouse_EventScript_Ceremony` | 0 / – | DraconidVillage_EldersHouse (4, 7) → DraconidVillage_Shrine (entering) | ok, 15 steps via DraconidVillage_EldersHouse, DraconidVillage, DraconidVillage_Shrine |
| 1.04 | Hatching rite, back to the village<br>`DraconidVillage_Shrine_EventScript_HatchingRite` | 0 / – | DraconidVillage_Shrine (10, 19) → DraconidVillage (entering) | ok, 1 steps via DraconidVillage_Shrine, DraconidVillage |
| 1.05 | Running Shoes, down to Draconid Pass<br>`DraconidVillage_EventScript_RunningShoes` | 0 / – | DraconidVillage (19, 5) → DraconidPass (10, 18) (11, 18) (12, 18) … | ok, 43 steps via DraconidVillage, DraconidPass |
| 1.06 | Aster's tutorial battle, on to Route 101<br>`DraconidPass_EventScript_AsterBattle` | 0 / – | DraconidPass (11, 18) → Route101 (0, 4) | ok, 25 steps via DraconidPass, Route101 |
| 1.07 | Birch's rescue, the lab<br>`Route101_EventScript_DraconidRescueTop` | 0 / – | LittlerootTown_ProfessorBirchsLab (6, 5) → LittlerootTown_ProfessorBirchsLab (entering) | ok, 0 steps via LittlerootTown_ProfessorBirchsLab |
| 1.08 | Lab welcome (Pokédex), to May on Route 103<br>`LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome` | 0 / – | LittlerootTown_ProfessorBirchsLab (6, 5) → Route103 next to (10, 3) | ok, 121 steps via LittlerootTown_ProfessorBirchsLab, LittlerootTown, Route101, OldaleTown, Route103 |
| 1.09 | May on Route 103, to Norman in Petalburg<br>`Route103_EventScript_Rival` | 0 / – | Route103 (9, 3) → PetalburgCity_Gym (entering) | ok, 125 steps via Route103, OldaleTown, Route102, PetalburgCity, PetalburgCity_Gym |
| 1.10 | Norman sends the player with Wally<br>`PetalburgCity_Gym_EventScript_Norman` | 0 / – | PetalburgCity (15, 8) → PetalburgCity (entering) | ok, 0 steps via PetalburgCity |
| 1.11 | Wally catches Ralts<br>`PetalburgCity_EventScript_WallyTutorial` | 0 / – | PetalburgCity_Gym (4, 108) → PetalburgCity_Gym (entering) | ok, 0 steps via PetalburgCity_Gym |
| 1.12 | Back in the gym, to Petalburg Woods<br>`PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial` | 0 / – | PetalburgCity_Gym (4, 111) → PetalburgWoods (26, 23) | ok, 114 steps via PetalburgCity_Gym, PetalburgCity, Route104, PetalburgWoods |
| 1.13 | Nerine robs the researcher, Courtney recruits the player<br>`PetalburgWoods_EventScript_DevonResearcherLeft` | 0 / – | PetalburgWoods_MagmaOutpost (4, 6) → PetalburgWoods_MagmaOutpost (entering) | ok, 0 steps via PetalburgWoods_MagmaOutpost |
| 1.14 | Outpost cabin: the uniform, out to Route 104 and Rustboro<br>`PetalburgWoods_MagmaOutpost_EventScript_Uniform` | 0 / – | PetalburgWoods_MagmaOutpost (4, 6) → RustboroCity (12, 53) | ok, 77 steps via PetalburgWoods_MagmaOutpost, Route104, RustboroCity |
| 1.14b | Way back: from the outpost door through Petalburg Woods to Petalburg *(side trip)*<br>– | 0 / – | Route104 (10, 30) → PetalburgCity (20, 17) | ok, 108 steps via Route104, PetalburgWoods, Route104, PetalburgCity |
| 1.15 | Brendan at Rustboro's south edge, to Roxanne<br>`RustboroCity_EventScript_RivalTrigger0` | 0 / – | RustboroCity (12, 53) → RustboroCity_Gym next to (5, 2) | ok, 73 steps via RustboroCity, RustboroCity_Gym |
| 1.16 | Stone Badge, out of the gym<br>`RustboroCity_Gym_EventScript_Roxanne` | 1 / – | RustboroCity_Gym (4, 2) → RustboroCity (entering) | ok, 25 steps via RustboroCity_Gym, RustboroCity |
| 1.17 | Tabitha's order, Birch's second starter<br>`RustboroCity_EventScript_DraconidSecondStarter` | 1 / – | RustboroCity (27, 19) → RustboroCity (23, 20) | ok, 5 steps via RustboroCity |
| 2.01 | Nerine steals the Devon Goods, Tabitha's order<br>`RustboroCity_EventScript_StolenGoodsTrigger0` | 1 / – | RustboroCity (23, 20) → RustboroCity (30, 9) | ok, 20 steps via RustboroCity |
| 2.02 | The Devon employee asks for help, to Route 116<br>`RustboroCity_EventScript_HelpGetGoodsTrigger0` | 1 / – | RustboroCity (30, 9) → Route116 (47, 9) | ok, 71 steps via RustboroCity, Route116 |
| 2.03 | Mr. Briney's Peeko, into Rusturf Tunnel<br>`Route116_EventScript_BrineyTrigger` | 1 / – | Route116 (47, 9) → RusturfTunnel next to (13, 5) | ok, 15 steps via Route116, RusturfTunnel |
| 2.04 | Nerine fight 2, the goods choice, back to Rustboro<br>`RusturfTunnel_EventScript_Grunt` | 1 / – | RusturfTunnel (12, 5) → RustboroCity (30, 9) | ok, 83 steps via RusturfTunnel, Route116, RustboroCity |
| 2.05 | The employee takes the goods back, to Mr. Stone<br>`RustboroCity_EventScript_ReturnGoodsTrigger0` | 1 / – | RustboroCity_DevonCorp_3F (2, 2) → RustboroCity_DevonCorp_3F (entering) | ok, 0 steps via RustboroCity_DevonCorp_3F |
| 2.06 | Mr. Stone: PokéNav, Exp. Share, the letter; to Mr. Briney's cottage<br>`RustboroCity_DevonCorp_3F_EventScript_MeetPresident` | 1 / – | RustboroCity_DevonCorp_3F (2, 2) → Route104_MrBrineysHouse next to (9, 3) | ok, 220 steps via RustboroCity_DevonCorp_3F, RustboroCity_DevonCorp_2F, RustboroCity_DevonCorp_1F, RustboroCity, Route104, PetalburgWoods, Route104, Route104_MrBrineysHouse |
| 2.07 | Mr. Briney sails to Dewford (Maxie's first call), to Brawly<br>`Route104_MrBrineysHouse_EventScript_Briney`<br>`Route104_EventScript_StartSailToDewford` | 1 / – | DewfordTown (11, 9) → DewfordTown_Gym next to (4, 3) | ok, 57 steps via DewfordTown, DewfordTown_Gym |
| 2.07b | Way back from Dewford before the letter: Mr. Briney sails to Petalburg *(side trip)*<br>`DewfordTown_EventScript_Briney` | 1 / – | Route104 (13, 51) → PetalburgCity (20, 17) | ok, 63 steps via Route104, PetalburgCity |
| 2.08 | Knuckle Badge, to Steven in Granite Cave<br>`DewfordTown_Gym_EventScript_Brawly` | 2 / – | DewfordTown_Gym (4, 4) → GraniteCave_StevensRoom next to (7, 8) | ok, 270 steps via DewfordTown_Gym, DewfordTown, Route106, GraniteCave_1F, GraniteCave_B1F, GraniteCave_B2F, GraniteCave_B1F, GraniteCave_1F, GraniteCave_StevensRoom |
| 2.09 | Steven gets the letter, back to Mr. Briney<br>`GraniteCave_StevensRoom_EventScript_Steven` | 2 / – | GraniteCave_StevensRoom (7, 7) → DewfordTown next to (12, 9) | ok, 82 steps via GraniteCave_StevensRoom, GraniteCave_1F, Route106, DewfordTown |
| 2.10 | Sail to Slateport, to the shipyard<br>`DewfordTown_EventScript_Briney` | 2 / – | Route109 (21, 23) → SlateportCity_SternsShipyard_1F next to (5, 5) | ok, 68 steps via Route109, SlateportCity, SlateportCity_SternsShipyard_1F |
| 2.10b | Way back from Slateport before Surf: Mr. Briney sails to Dewford *(side trip)*<br>`Route109_EventScript_MrBriney` | 2 / – | DewfordTown (11, 9) → DewfordTown_Gym (entering) | ok, 19 steps via DewfordTown, DewfordTown_Gym |
| 2.11 | Dock: Stern is at the museum<br>`SlateportCity_SternsShipyard_1F_EventScript_Dock` | 2 / – | SlateportCity_SternsShipyard_1F (4, 5) → SlateportCity_OceanicMuseum_1F (9, 7) | ok, 45 steps via SlateportCity_SternsShipyard_1F, SlateportCity, SlateportCity_OceanicMuseum_1F |
| 2.12 | Museum fee, Tabitha's order, to Stern on 2F<br>`SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft` | 2 / – | SlateportCity_OceanicMuseum_1F (9, 7) → SlateportCity_OceanicMuseum_2F next to (13, 6) | ok, 21 steps via SlateportCity_OceanicMuseum_1F, SlateportCity_OceanicMuseum_2F |
| 2.13 | Aqua's raid (Nerine fight 2), Stern gets the parts; to Route 110<br>`SlateportCity_OceanicMuseum_2F_EventScript_CaptStern` | 2 / – | SlateportCity_OceanicMuseum_2F (12, 6) → Route110 (33, 56) | ok, 140 steps via SlateportCity_OceanicMuseum_2F, SlateportCity_OceanicMuseum_1F, SlateportCity, Route110 |
| 2.14 | May on Route 110 (PokéNav), to Mauville<br>`Route110_EventScript_RivalTrigger1` | 2 / – | Route110 (33, 56) → MauvilleCity next to (8, 6) | ok, 136 steps via Route110, MauvilleCity |
| 2.15 | Wally in Mauville, to Wattson<br>`MauvilleCity_EventScript_Wally` | 2 / – | MauvilleCity (8, 7) → MauvilleCity_Gym (entering) | ok, 2 steps via MauvilleCity, MauvilleCity_Gym |
| 2.16 | Dynamo Badge, to the Rock Smash house<br>`MauvilleCity_Gym_EventScript_Wattson` | 3 / – | MauvilleCity_Gym (4, 20) → MauvilleCity_House1 next to (4, 4) | ok, 39 steps via MauvilleCity_Gym, MauvilleCity, MauvilleCity_House1 |
| 2.17 | HM Rock Smash, to Rydel's bikes<br>`MauvilleCity_House1_EventScript_RockSmashDude` | 3 / Rock Smash | MauvilleCity_House1 (3, 4) → MauvilleCity_BikeShop next to (2, 5) | ok, 25 steps via MauvilleCity_House1, MauvilleCity, MauvilleCity_BikeShop |
| 2.18 | A bike from Rydel; north over Route 111, Fiery Path, Fallarbor to Meteor Falls<br>`MauvilleCity_BikeShop_EventScript_Rydel` | 3 / Rock Smash | MauvilleCity_BikeShop (3, 5) → MeteorFalls_1F_1R (14, 18) | ok, 587 steps via MauvilleCity_BikeShop, MauvilleCity, Route111, Route112, FieryPath, Route112, Route111, Route113, FallarborTown, Route114, MeteorFalls_1F_1R |
| 3.01 | Meteor Falls: Maxie, the stand-off with Aqua, Aster; to the cable car<br>`MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene` | 3 / Rock Smash | MeteorFalls_1F_1R (14, 18) → Route112_CableCarStation next to (6, 6) | ok, 443 steps via MeteorFalls_1F_1R, Route114, FallarborTown, Route113, Route111, Route112, FieryPath, Route112, Route112_CableCarStation |
| 3.02 | Cable car up Mt. Chimney, to Maxie<br>`Route112_CableCarStation_EventScript_Attendant` | 3 / Rock Smash | MtChimney_CableCarStation (6, 4) → MtChimney next to (13, 6) | ok, 79 steps via MtChimney_CableCarStation, MtChimney |
| 3.03 | Mt. Chimney: Tabitha, Nerine fight 3, Brendan, the sabotage; down Jagged Pass<br>`MtChimney_EventScript_Maxie` | 3 / Rock Smash | MtChimney (12, 6) → JaggedPass (13, 8) (14, 8) | ok, 72 steps via MtChimney, JaggedPass |
| 3.03b | Way back from Mt. Chimney by cable car *(side trip)*<br>`MtChimney_CableCarStation_EventScript_Attendant` | 3 / Rock Smash | Route112_CableCarStation (6, 4) → Route112 (28, 29) | ok, 10 steps via Route112_CableCarStation, Route112 |
| 3.04 | Aster brings the Mega Ring, to the traveller in Lavaridge<br>`JaggedPass_EventScript_DraconidAster` | 3 / Rock Smash | JaggedPass (14, 8) → LavaridgeTown next to (17, 8) | ok, 40 steps via JaggedPass, Route112, LavaridgeTown |
| 3.05 | The Mega Stone, to Flannery<br>`LavaridgeTown_EventScript_DraconidTraveller` | 3 / Rock Smash | LavaridgeTown (18, 8) → LavaridgeTown_Gym_1F next to (13, 9) | ok, 99 steps via LavaridgeTown, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F |
| 3.06 | Heat Badge, out of the gym<br>`LavaridgeTown_Gym_1F_EventScript_Flannery` | 4 / Rock Smash | LavaridgeTown_Gym_1F (12, 9) → LavaridgeTown (entering) | ok, 10 steps via LavaridgeTown_Gym_1F, LavaridgeTown |
| 3.07 | May's Go-Goggles; back towards Petalburg through Rusturf Tunnel<br>`LavaridgeTown_EventScript_RivalGiveGoGoggles` | 4 / Rock Smash | LavaridgeTown (5, 15) → RusturfTunnel (23, 4) | ok, 274 steps via LavaridgeTown, Route112, Route111, MauvilleCity, Route117, VerdanturfTown, RusturfTunnel |
| 3.08 | Rusturf Tunnel opened with Rock Smash: HM Strength; on to Petalburg<br>`RusturfTunnel_EventScript_ClearTunnelScene` | 4 / Rock Smash, Strength | RusturfTunnel (23, 4) → PetalburgCity (15, 9) | ok, 315 steps via RusturfTunnel, Route116, RustboroCity, Route104, PetalburgWoods, Route104, PetalburgCity |
| 4.01 | Wally at the Petalburg Gym door, to Norman<br>`PetalburgCity_EventScript_DraconidWallyTrigger` | 4 / Rock Smash, Strength | PetalburgCity (15, 9) → PetalburgCity_Gym (entering) | ok, 1 steps via PetalburgCity, PetalburgCity_Gym |
| 4.02 | Balance Badge (May watches), out to Wally's father<br>`PetalburgCity_Gym_EventScript_Norman` | 5 / Rock Smash, Strength | PetalburgCity (15, 8) → PetalburgCity (entering) | ok, 0 steps via PetalburgCity |
| 4.03 | Wally's father walks the player home<br>`PetalburgCity_EventScript_WalkToWallyHouse` | 5 / Rock Smash, Strength | PetalburgCity_WallysHouse (2, 4) → PetalburgCity_WallysHouse (entering) | ok, 0 steps via PetalburgCity_WallysHouse |
| 4.04 | HM Surf, over Route 118 to Tabitha at the Weather Institute<br>`PetalburgCity_WallysHouse_EventScript_GiveHMSurf` | 5 / Rock Smash, Strength, Surf | PetalburgCity_WallysHouse (2, 4) → Route119 (6, 33) | ok, 607 steps via PetalburgCity_WallysHouse, PetalburgCity, Route102, OldaleTown, Route103, Route110, MauvilleCity, Route118, Route119 |
| 4.05 | Tabitha's order, up to Shelly<br>`Route119_EventScript_DraconidTabithaOrder` | 5 / Rock Smash, Strength, Surf | Route119 (6, 33) → Route119_WeatherInstitute_2F next to (4, 6) | ok, 53 steps via Route119, Route119_WeatherInstitute_1F, Route119_WeatherInstitute_2F |
| 4.06 | Aqua leaves the Institute, May covers for the player; to Brendan<br>`Route119_WeatherInstitute_2F_EventScript_Shelly` | 5 / Rock Smash, Strength, Surf | Route119_WeatherInstitute_2F (5, 6) → Route119 (25, 31) | ok, 68 steps via Route119_WeatherInstitute_2F, Route119_WeatherInstitute_1F, Route119 |
| 4.07 | Brendan on Route 119 (HM Fly, PokéNav), to Fortree and Steven<br>`Route119_EventScript_RivalTrigger1` | 5 / Rock Smash, Strength, Surf, Fly | Route119 (25, 31) → Route120 next to (13, 15) | ok, 135 steps via Route119, FortreeCity, Route120 |
| 4.08 | Steven's Devon Scope, back to the Fortree Gym<br>`Route120_EventScript_Steven` | 5 / Rock Smash, Strength, Surf, Fly | Route120 (14, 15) → FortreeCity_Gym next to (15, 2) | ok, 115 steps via Route120, FortreeCity, FortreeCity_Gym |
| 4.09 | Feather Badge, over Route 121 to Lilycove<br>`FortreeCity_Gym_EventScript_Winona` | 6 / Rock Smash, Strength, Surf, Fly | FortreeCity_Gym (14, 2) → LilycoveCity next to (27, 7) | ok, 388 steps via FortreeCity_Gym, FortreeCity, Route120, Route121, LilycoveCity |
| 4.10 | Brendan and May in Lilycove (double), to Wally<br>`LilycoveCity_EventScript_Rival` | 6 / Rock Smash, Strength, Surf, Fly | LilycoveCity (28, 7) → LilycoveCity next to (26, 16) | ok, 3 steps via LilycoveCity |
| 4.11 | Wally's Mega Gallade, over Route 122 to the Mt. Pyre summit<br>`LilycoveCity_EventScript_DraconidWally` | 6 / Rock Smash, Strength, Surf, Fly | LilycoveCity (25, 16) → MtPyre_Summit (entering) | ok, 270 steps via LilycoveCity, Route121, Route122, MtPyre_1F, MtPyre_Exterior, MtPyre_Summit |
| 4.12 | Maxie's order and the Magma Emblem, down to Nerine<br>`MtPyre_Summit_EventScript_DraconidMaxieOrders` | 6 / Rock Smash, Strength, Surf, Fly | MtPyre_Summit (23, 31) → MtPyre_Summit (22, 10) (23, 10) (24, 10) | ok, 21 steps via MtPyre_Summit |
| 4.13 | Nerine fight 4, up to Archie<br>`MtPyre_Summit_EventScript_DraconidNerine` | 6 / Rock Smash, Strength, Surf, Fly | MtPyre_Summit (23, 10) → MtPyre_Summit (22, 7) | ok, 4 steps via MtPyre_Summit |
| 4.14 | Archie takes the Red Orb; to the Jagged Pass guard<br>`MtPyre_Summit_EventScript_TeamAquaTrigger0` | 6 / Rock Smash, Strength, Surf, Fly | MtPyre_Summit (22, 7) → JaggedPass next to (16, 19) | ok, 68 steps via MtPyre_Summit, Fly to LavaridgeTown, Route112, JaggedPass |
| 4.15 | The guard opens the hideout, up to Maxie<br>`JaggedPass_EventScript_MagmaHideoutGuard` | 6 / Rock Smash, Strength, Surf, Fly | JaggedPass (17, 19) → MagmaHideout_4F next to (16, 21) | ok, 316 steps via JaggedPass, MagmaHideout_1F, MagmaHideout_2F_1R, MagmaHideout_3F_1R, MagmaHideout_4F |
| 4.16 | Maxie's promotion, Groudon wakes and escapes; to the Aqua Hideout (Maxie's call)<br>`MagmaHideout_4F_EventScript_Maxie` | 6 / Rock Smash, Strength, Surf, Fly | MagmaHideout_4F (15, 21) → AquaHideout_B2F next to (23, 19) | ok, 354 steps via MagmaHideout_4F, MagmaHideout_3F_3R, MagmaHideout_2F_3R, MagmaHideout_1F, JaggedPass, Fly to LilycoveCity, AquaHideout_1F, AquaHideout_B1F, AquaHideout_B2F, AquaHideout_B1F, AquaHideout_B2F |
| 5.01 | Aqua Hideout: Nerine fight 5 and Matt; over Route 124 to Mossdeep<br>`AquaHideout_B2F_EventScript_Matt` | 6 / Rock Smash, Strength, Surf, Fly | AquaHideout_B2F (24, 19) → MossdeepCity_Gym (entering) | ok, 250 steps via AquaHideout_B2F, AquaHideout_B1F, AquaHideout_1F, LilycoveCity, Route124, MossdeepCity, MossdeepCity_Gym |
| 5.02 | Mind Badge, to Tabitha's raid<br>`MossdeepCity_Gym_EventScript_TateAndLiza` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity_Gym (6, 35) → MossdeepCity (40, 25) (40, 26) (41, 22) … | ok, 20 steps via MossdeepCity_Gym, MossdeepCity |
| 5.03 | Tabitha's raid order, into the Space Center<br>`MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity (41, 22) → MossdeepCity_SpaceCenter_2F (entering) | ok, 59 steps via MossdeepCity, MossdeepCity_SpaceCenter_1F, MossdeepCity_SpaceCenter_2F |
| 5.04 | Space Center 2F: the rank tests, to Steven and Brendan<br>`MossdeepCity_SpaceCenter_2F_EventScript_ThreeMagmaGrunts` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity_SpaceCenter_2F (13, 1) → MossdeepCity_SpaceCenter_2F (7, 5) (7, 6) (7, 7) … | ok, 12 steps via MossdeepCity_SpaceCenter_2F |
| 5.05 | The tag battle, the sealed tanks; to Steven's house<br>`MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity_SpaceCenter_2F (7, 5) → MossdeepCity_StevensHouse (entering) | ok, 42 steps via MossdeepCity_SpaceCenter_2F, MossdeepCity_SpaceCenter_1F, MossdeepCity, MossdeepCity_StevensHouse |
| 5.06 | HM Dive, down to the Seafloor Cavern<br>`MossdeepCity_StevensHouse_EventScript_StevenGivesDive` | 7 / Rock Smash, Strength, Surf, Fly, Dive | MossdeepCity_StevensHouse (3, 7) → SeafloorCavern_Room9 (entering) | ok, 261 steps via MossdeepCity_StevensHouse, MossdeepCity, Route127, Route128, Underwater_Route128, Underwater_SeafloorCavern, SeafloorCavern_Entrance, SeafloorCavern_Room1, SeafloorCavern_Room2, SeafloorCavern_Room7, SeafloorCavern_Room3, SeafloorCavern_Room8, SeafloorCavern_Room9 |
| 5.07 | Nerine's reveal (fight 6), to Archie<br>`SeafloorCavern_Room9_EventScript_DraconidNerineReveal` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SeafloorCavern_Room9 (5, 4) → SeafloorCavern_Room9 (17, 42) | ok, 62 steps via SeafloorCavern_Room9 |
| 5.08 | Kyogre wakes, back to Route 128<br>`SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre` | 7 / Rock Smash, Strength, Surf, Fly, Dive | Route128 (38, 22) → Route128 (entering) | ok, 0 steps via Route128 |
| 5.09 | Archie and Maxie on Route 128, dive to Sootopolis<br>`Route128_EventScript_KyogreAwakenedScene` | 7 / Rock Smash, Strength, Surf, Fly, Dive | Route128 (38, 22) → SootopolisCity (entering) | ok, 149 steps via Route128, Route127, Route126, Underwater_Route126, Underwater_SootopolisCity, SootopolisCity |
| 5.10 | Groudon and Kyogre clash, to Maxie on the Gym island<br>`SootopolisCity_EventScript_StartLegendariesScene` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (29, 53) → SootopolisCity next to (29, 33) | ok, 25 steps via SootopolisCity |
| 5.11 | The turn, Maxie, the multi battle, Rayquaza, the Elder's call, the rivals; to Archie<br>`SootopolisCity_EventScript_Maxie` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (31, 34) → SootopolisCity next to (34, 35) | ok, 5 steps via SootopolisCity |
| 5.12 | Archie admits his failure, to Maxie<br>`SootopolisCity_EventScript_Archie` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (34, 36) → SootopolisCity next to (33, 35) | ok, 1 steps via SootopolisCity |
| 5.13 | Maxie admits his, both leave (the Gym door opens); to Wallace<br>`SootopolisCity_EventScript_Maxie` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (31, 34) → SootopolisCity next to (31, 33) | ok, 0 steps via SootopolisCity |
| 5.14 | HM Waterfall, Wallace steps aside; to Juan<br>`SootopolisCity_EventScript_Wallace` | 7 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SootopolisCity (31, 34) → SootopolisCity_Gym_1F (entering) | ok, 2 steps via SootopolisCity, SootopolisCity_Gym_1F |
| 5.15 | Rain Badge (end of Act 5)<br>`SootopolisCity_Gym_1F_EventScript_Juan` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | – | ok |
| 5.15b | Way on to Act 6: out of Sootopolis, up the waterfall to Victory Road *(side trip)*<br>– | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SootopolisCity_Gym_1F (8, 25) → VictoryRoad_1F (entering) | ok, 291 steps via SootopolisCity_Gym_1F, SootopolisCity, Fly to MossdeepCity, Route127, Route128, EverGrandeCity, VictoryRoad_1F |
