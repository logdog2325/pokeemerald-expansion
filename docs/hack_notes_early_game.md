# Vanilla early-game state machine (reference)

Analysis of the vanilla Emerald scripts this hack rewrites (Littleroot, the houses, Route 101,
the lab, Route 103, Oldale). Line numbers refer to the vanilla files at expansion 1.17.1 and
may have moved since the rework; labels are stable. Kept for future sessions.

## Must-haves for any replacement intro
- **Wall clock**: `special StartWallClock` (after `fadescreen FADE_TO_BLACK`) is the only
  non-debug way to set `FLAG_SYS_CLOCK_SET` (`src/clock.c`). Without it time-based events stay off.
- **Truck callback**: `CB2_NewGame` set `gFieldCallback = ExecuteTruckSequence`
  (`src/overworld.c`) and `WarpToTruck` hard-coded `MAP_INSIDE_OF_TRUCK` (`src/new_game.c`).
- **Whiteout location**: `ClearSav1` zeroes `lastHealLocation`; the truck's `setrespawn` was the
  only thing that fixed it before the first Pokémon Center. The new intro must `setrespawn`.
- **Route 103 sequence break**: the Route 103 rival is visible from the start
  (`FLAG_HIDE_ROUTE_103_RIVAL` never set); beating them set `VAR_BIRCH_LAB_STATE` 4, which made
  the lab hand out the Pokédex even without rescuing Birch.

## Vars
| Var | Values |
|---|---|
| `VAR_LITTLEROOT_INTRO_STATE` | 1/2 in truck, 3 entered house, 4 told to set clock, 5 on 2F, 6 clock set (TV report), **7 = only inert value**. `< 6` draws moving boxes in *both* 1F maps. |
| `VAR_LITTLEROOT_TOWN_STATE` | **0 = coords (10,1),(11,1) push the player south (Littleroot's only exit!)**, 1 = coord (11,1) `GoSaveBirchTrigger`, 2 inert, 3 = lab gave Pokédex → Mom outside + running-shoes coords, 4 inert. |
| `VAR_LITTLEROOT_HOUSES_STATE_BRENDAN/_MAY` | 1 = "new neighbor" scene in the *opposite* house, 3 = SS Ticket / Lati TV scene (both 1F maps check `_MAY`), 4/5 after it. Leave at 0. |
| `VAR_LITTLEROOT_RIVAL_STATE` | 0/1 → entering the opposite-gender rival's 2F sets 2, which arms the Poké Ball + 1F stair "meet rival" scenes in both houses. 3 = met rival, 4 = Pokédex. |
| `VAR_BIRCH_LAB_STATE` | 2 = rescued Birch → lab OnFrame `GiveStarterEvent` (nicknames party slot 0), 3 agreed to see rival, 4 beat rival → lab OnFrame `GivePokedexEvent`, 5 done. |
| `VAR_ROUTE101_STATE` | 0 → OnFrame sets the *global* `FLAG_HIDE_MAP_NAME_POPUP` and 1; 1 → coords (10,19),(11,19) `StartBirchRescue`; 2 → prevent-exit coords; 3 done. Only `BirchsBag` clears the popup flag. |
| `VAR_OLDALE_RIVAL_STATE` | 1 (set by Route 103 `RivalEnd`) → Oldale coords (8..10,19) rival scene; 2 done. |
| `VAR_OLDALE_TOWN_STATE` | 0 → coord (0,10) blocks the west exit to Route 102; 1 set by the lab or when `FLAG_ADVENTURE_STARTED`. |
| `VAR_STARTER_MON` | 0 Treecko, 1 Torchic, 2 Mudkip. Only written by `CB2_GiveStarter`. Read by `IsStarterInParty` (Petalburg PC), credits, Mauville Game Corner doll, and every rival battle switch. `GetStarterPokemon` has an off-by-one (`> STARTER_MON_COUNT`). |

## Vanilla order: new game → Pokédex, Poké Balls, Running Shoes
1. New game: `EventScript_ResetAllMapFlags` (`data/scripts/new_game.inc`) hides lab Birch/rival,
   house rivals, Dad, dolls, Mom outside, Route 101/103 Birch, Oldale rival. **Not hidden by
   default**: trucks, both player-Mom objects, both Vigoroths, rival moms/siblings, the 2F rival
   Poké Balls, Route 101 Birch/Zigzagoon/bag, the Route 103 rival.
2. Truck `SetIntroFlags`: `setrespawn` house 2F, intro 1/2, houses-state 1, hides other house's objects.
3. Littleroot `StepOffTruck*` → intro 3, `setflag MOM_OUTSIDE`, `clearflag FAT_MAN`.
4. 1F `EnterHouseMovingIn` → intro 4. 2F → 5. Wall clock → `StartWallClock`, intro 6,
   `FLAG_SET_WALL_CLOCK`, Vigoroth flags. 1F TV report → `FLAG_SYS_TV_HOME`, intro 7.
5. Rival's house/room → rival state 3, town state 1. Twin → town state 2.
6. Route 101 bag: `FLAG_SYS_POKEMON_GET`, `FLAG_RESCUED_BIRCH`, `special ChooseStarter` (sets
   `VAR_STARTER_MON`, gives lv5, `BATTLE_TYPE_FIRST_BATTLE` vs Zigzagoon lv2), heal, lab state 2,
   route state 3, clears popup flag, warp to lab (6,5).
7. Lab `GiveStarterEvent` → lab state 3, `clearflag ROUTE_101_BOY`.
8. Route 103 rival → `RivalEnd`: lab state 4, `FLAG_DEFEATED_RIVAL_ROUTE103`, Oldale rival state 1.
9. Lab `GivePokedex`: `FLAG_SYS_POKEDEX_GET`, `FLAG_RECEIVED_POKEDEX_FROM_BIRCH`,
   `VAR_CABLE_CLUB_TUTORIAL_STATE` 1, rival gives 5 Poké Balls, lab 5, `FLAG_ADVENTURE_STARTED`,
   `VAR_OLDALE_TOWN_STATE` 1, rival state 4, town state 3.
10. Littleroot Mom → `FLAG_RECEIVED_RUNNING_SHOES`, `FLAG_SYS_B_DASH`, town state 4.

`FLAG_ADVENTURE_STARTED` also gates the Oldale footprint man/west block and Oldale Mart Poké Balls.

## Gender-decided rival identity
- `Common_EventScript_SetupRivalGfxId` / `…OnBikeGfxId` (`data/scripts/rival_graphics.inc`): male
  player → May. Called by Littleroot, lab, Route 103, Oldale, Route 104, Rustboro, Route 110,
  Route 119, Lavaridge, Lilycove, Champion's room.
- `{RIVAL}` string (`src/string_util.c`), `GetRivalSonDaughterString` (`field_specials.c`),
  rival match-call filtering (`pokenav_match_call_data.c`), credits (`credits.c`).
- Rival battle switches on `VAR_STARTER_MON` (trainer constant names use the *player's* starter):
  Route 103, Route 104 (reuses `*_RUSTBORO_*`), Rustboro, Route 110, Route 119, Lilycove.
  Brendan-with-Treecko = the `_MUDKIP` teams; May-with-Torchic = the `_TREECKO` teams.

## Player-house logic chosen by gender (Littleroot)
2F OnWarp `SecretBase_EventScript_InitDecorations`, bedroom PC (`special BedroomPC`), 1F running
shoes manual metatile, TV news (`tv.c CheckForPlayersHouseNews`), whiteout Mom heal
(`IsLastHealLocationPlayerHouse`, `EventScript_AfterWhiteOutMomHeal`), fly to Littleroot and the
post-credits continue warp (`region_map.c`, `post_battle_event_funcs.c`), Hall of Fame respawn,
SS Ticket + Lati TV + roamer (`PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV`, do not drop),
Mom: Amulet Coin (badge 5), match call registration, healing.
