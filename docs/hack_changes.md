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
| Emulator runner + driver | `tools/hack/emu/gbarun.c`, `tools/hack/emu/play.py` | headless smoke tests, see docs/hack_tools.md |
| Map specs | `tools/hack/mapgen/specs/draconid_*.{py,json}` | regenerate the Draconid maps with `mapbuild.py` |
| Seam checker | `tools/hack/mapgen/check_seams.py` | flags secondary metatiles drawable across a connection with other tilesets; run by `mapbuild.py --write` |
| Emulator regression tests | `tools/hack/emu/tests/*.play` | `opening.play` (new game → lab), `route103.play` (→ May) |

## Config options
| Option | Old | New | File |
|---|---|---|---|
| `B_FLAG_NO_WHITEOUT` | `0` | `FLAG_DRACONID_NO_WHITEOUT` | `include/config/battle.h` |
| `WE_FLAG_NO_ENCOUNTER` | `0` | `FLAG_DEBUG_NO_ENCOUNTER` | `include/config/wild_encounter.h` |
| `OW_FLAG_NO_TRAINER_SEE` | `0` | `FLAG_DEBUG_NO_TRAINER_SEE` | `include/config/overworld.h` |
| `OW_FLAG_NO_COLLISION` | `0` | `FLAG_DEBUG_NO_COLLISION` | `include/config/overworld.h` |

## Flags
| Flag | Meaning |
|---|---|
| `FLAG_HIDE_DRACONID_ELDERS_HOUSE_ASTER` (0x20) | Aster in the Elder's house (shown for the egg ceremony) |
| `FLAG_HIDE_DRACONID_VILLAGE_ASTER` (0x21) | reserved: Aster standing in the village (later visits) |
| `FLAG_RECEIVED_DRACONID_EGG` (0x22) | player took an egg; hides the three egg objects |
| `FLAG_DRACONID_EGG_HATCHED` (0x23) | the hatching rite ran |
| `FLAG_HIDE_DRACONID_SHRINE_ELDER` (0x24) | Elder at the shrine (rite only) |
| `FLAG_HIDE_DRACONID_SHRINE_ASTER` (0x25) | Aster at the shrine (rite only) |
| `FLAG_HIDE_DRACONID_ELDERS_HOUSE_ELDER` (0x26) | Elder at home (hidden during the rite) |
| `FLAG_HIDE_DRACONID_PASS_ASTER` (0x27) | Aster waiting on Draconid Pass |
| `FLAG_DEFEATED_ASTER_DRACONID_PASS` (0x28) | first Aster battle done |
| `FLAG_RECEIVED_SECOND_STARTER` (0x29) | Birch's second starter taken (Phase 4) |
| `FLAG_HIDE_DRACONID_VILLAGE_MOM` (0x2A) | Mom waiting outside the shrine (Running Shoes) |
| `FLAG_HIDE_DRACONID_HOUSE_2F_MOM` (0x2B) | Mom in the bedroom (wake-up scene) |
| `FLAG_DRACONID_NO_WHITEOUT` (0x2C) | `B_FLAG_NO_WHITEOUT`: set around scripted battles the player may lose |
| `FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BRENDAN` (0x2D) | Brendan in Birch's lab (the welcome scene) |
| `FLAG_DEBUG_NO_ENCOUNTER` (0x2E), `FLAG_DEBUG_NO_TRAINER_SEE` (0x2F), `FLAG_DEBUG_NO_COLLISION` (0x30) | the expansion's debug toggles (debug menu, emulator tests); never set by the game |
| `FLAG_VISITED_DRACONID_VILLAGE` (`SYSTEM_FLAGS+0x21`, was `FLAG_UNUSED_0x881`) | fly destination |

## Vars
| Var | Values |
|---|---|
| `VAR_DRACONID_STATE` (0x40F7) | `DRACONID_STATE_*`: 0 new game, 1 set clock, 2 clock set, 3 egg received, 4 egg hatched, 5 ready to leave, 6 left village |
| `VAR_ASTER_EGG` (0x40F8) | Aster's egg, `DRACONID_EGG_*` (counter-pick of the player's) |
| `VAR_SECOND_STARTER` (0x40F9) | `SECOND_STARTER_*`: 0 none, 1 Charmander, 2 Totodile, 3 Treecko |
| `VAR_PLAYER_OUTFIT` (0x40FA) | `PLAYER_OUTFIT_*`: 0 Draconid, 1 Magma |
| `VAR_ASTER_STATE` (0x40FB) | Aster arc progress (Phase 4) |
| `VAR_STARTER_MON` (changed meaning) | now the player's egg, `DRACONID_EGG_*`; the starter table in `src/starter_choose.c` maps it to Deino/Dreepy/Jangmo-o |

## Constants
| Constant | Where |
|---|---|
| `DRACONID_STATE_*`, `DRACONID_EGG_*`, `DRACONID_EGG_SPECIES_0..2`, `DRACONID_EGG_COUNT`, `DRACONID_HATCHLING_LEVEL`, `SECOND_STARTER_*` | `include/constants/draconid.h` |
| `PLAYER_OUTFIT_DRACONID`, `PLAYER_OUTFIT_MAGMA`, `PLAYER_OUTFIT_COUNT` | `include/constants/outfits.h` |
| `TRAINER_ASTER_PASS_DEINO/_DREEPY/_JANGMO_O` (855–857), `TRAINERS_COUNT_EMERALD` 855→858 | `include/constants/opponents.h`, teams in `src/data/trainers.party` |
| `MAP_DRACONID_VILLAGE`, `MAP_DRACONID_PASS` (group TownsAndRoutes); `MAP_DRACONID_VILLAGE_PLAYERS_HOUSE_1F/_2F`, `_ELDERS_HOUSE`, `_SHRINE`, `_HOUSE1`, `_HOUSE2` (new group `gMapGroup_IndoorDraconid`) | `data/maps/map_groups.json`, `data/maps/Draconid*/` |
| `LAYOUT_DRACONID_VILLAGE`, `LAYOUT_DRACONID_PASS`, `LAYOUT_DRACONID_VILLAGE_PLAYERS_HOUSE_1F/_2F`, `_ELDERS_HOUSE`, `_SHRINE` (House1/2 reuse `LAYOUT_HOUSE2`/`LAYOUT_HOUSE1`) | `data/layouts/layouts.json` |
| `MAPSEC_DRACONID_VILLAGE` (x2 y11), `MAPSEC_DRACONID_PASS` (x3 y11) | `src/data/region_map/region_map_sections.json`, `region_map_layout.h`, popup themes in `src/map_name_popup.c` |
| `HEAL_LOCATION_DRACONID_VILLAGE_PLAYERS_HOUSE_2F`, `HEAL_LOCATION_DRACONID_VILLAGE` | `src/data/heal_locations.json` |
| Route 101 ↔ Draconid Pass connection (Route 101 left, offset −22; pass rows 26–27 = Route 101 rows 4–5) | `data/maps/Route101/map.json` |
| `LOCALID_BIRCHS_LAB_BRENDAN` object (5, 4); lab rival object is always `OBJ_EVENT_GFX_RIVAL_MAY_NORMAL` | `data/maps/LittlerootTown_ProfessorBirchsLab/map.json` |
| Route 103 rival object is always `OBJ_EVENT_GFX_RIVAL_MAY_NORMAL` | `data/maps/Route103/map.json` |
| Route 101 coord triggers (0, 4) / (0, 5) on `VAR_ROUTE101_STATE` 1 | `data/maps/Route101/map.json` |

## C changes
| Change | File |
|---|---|
| New: `DraconidRaiseHatchling` special (raise party slot `VAR_0x8004` to `DRACONID_HATCHLING_LEVEL`, full HP, level-up moves) | `src/draconid.c`, `include/draconid.h`, `data/specials.inc` |
| New game warps to the Draconid bedroom instead of the truck | `src/new_game.c` (`WarpToTruck`), `src/overworld.c` (`CB2_NewGame` uses `FieldCB_WarpExitFadeFromBlack`) |
| Starter table = the three eggs; `GetStarterPokemon` off-by-one fixed (`>=`) | `src/starter_choose.c` |
| Whiteout Mom-heal counts the Draconid heal locations | `src/heal_location.c` (`IsLastHealLocationPlayerHouse`) |
| Post-credits continue → Draconid bedroom | `src/post_battle_event_funcs.c` |
| Fly: Littleroot → May's house heal location; Draconid Village fly spot | `src/region_map.c` |
| Bedroom PC turn-off in the Draconid house | `src/player_pc.c`, `include/event_scripts.h` |
| New: `StartBirchRescueBattle` special (vanilla first battle vs Zigzagoon Lv2 without choosing a starter) | `src/battle_setup.c`, `include/battle_setup.h`, `data/specials.inc` |
| `{RIVAL}` always expands to MAY in Emerald (Birch's daughter), for both player genders | `src/string_util.c` |

## Scripts
| Script / label | File |
|---|---|
| `DraconidEmerald_EventScript_NewGameSetup` (called from `EventScript_ResetAllMapFlags`): skips the vanilla Littleroot intro vars, hides trucks/house Moms/Vigoroths/2F balls/Route 103 rival, sets the respawn | `data/scripts/draconid/new_game.pory` |
| Bedroom wake-up, stairs block, wall clock, bedroom PC | `data/maps/DraconidVillage_PlayersHouse_2F/scripts.pory` |
| Mom (1F; falls back to vanilla `PlayersHouse_1F_EventScript_Mom`) | `data/maps/DraconidVillage_PlayersHouse_1F/scripts.pory` |
| Egg ceremony (`dynmultichoice`, `giveegg`, Aster counter-pick) | `data/maps/DraconidVillage_EldersHouse/scripts.pory` |
| Hatching rite (`special EggHatch` + `DraconidRaiseHatchling`) | `data/maps/DraconidVillage_Shrine/scripts.pory` |
| Mom gives Running Shoes, gatekeeper, villagers, signs | `data/maps/DraconidVillage/scripts.pory` |
| First Aster battle (no whiteout) | `data/maps/DraconidPass/scripts.pory` |
| Villager dialogue | `data/maps/DraconidVillage_House1/`, `_House2/scripts.pory` |
| Route 101 rescue with the hatchling, lab welcome (Brendan Treecko, May Torchic, player Pokédex + 5 Poké Balls), Route 103 May | `data/scripts/draconid/birch_intro.pory` |
| Hooks into vanilla: `Route101_OnTransition` calls `Route101_EventScript_DraconidOnTransition`; lab OnFrame state 2 → `…_DraconidWelcome`; `Route103_EventScript_Rival` → `Route103_EventScript_DraconidMay`; `Route103_EventScript_RivalEnd` no longer sets lab state 4 or arms the Oldale rival scene | `data/maps/Route101/`, `LittlerootTown_ProfessorBirchsLab/`, `Route103/scripts.inc` |
| New game: `VAR_LITTLEROOT_TOWN_STATE` 4, `VAR_ROUTE101_STATE` 1, hides Birch's bag and lab Brendan | `data/scripts/draconid/new_game.pory` |
