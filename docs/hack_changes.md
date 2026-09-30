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
| Emulator regression tests | `tools/hack/emu/tests/*.play` | `opening.play` (new game → lab, `-D GENDER=F`), `route103.play` (→ May), `route104.play` (Brendan), `rivals.play` (the other new rival scenes); `play.py` gained `warp`, `heal` (debug builds) and ledge-aware `path` |
| Player outfit art builders | `tools/hack/art/player/build_player.py`, `build_pics.py`, specs `draconid_m/f.json`, `magma_m/f.json`, `*_pics.json` | see docs/hack_art_pipeline.md |
| Outfit C code generator | `tools/hack/art/player/gen_outfit_code.py` | writes between `DRACONID PLAYER OUTFITS` markers |
| Art manifest | `tools/hack/art/manifests/draconid.json` | `validate.py --manifest` for all player art; new `map_icon` profile in `gbaart.py` |
| Trainer tools | `tools/hack/trainers/`: `party.py` (reader/writer), `scan_maps.py` (map → trainers), `build_segments.py` → `segments.json` (segment, role, cap per trainer), `check_party.py` (legality, caps, headers, trainerproc), `splice_party.py` (merge batches), `learnset.py` | see docs/hack_trainers.md |

## Config options
| Option | Old | New | File |
|---|---|---|---|
| `B_FLAG_NO_WHITEOUT` | `0` | `FLAG_DRACONID_NO_WHITEOUT` | `include/config/battle.h` |
| `WE_FLAG_NO_ENCOUNTER` | `0` | `FLAG_DEBUG_NO_ENCOUNTER` | `include/config/wild_encounter.h` |
| `OW_FLAG_NO_TRAINER_SEE` | `0` | `FLAG_DEBUG_NO_TRAINER_SEE` | `include/config/overworld.h` |
| `OW_FLAG_NO_COLLISION` | `0` | `FLAG_DEBUG_NO_COLLISION` | `include/config/overworld.h` |
| `B_EXP_CAP_TYPE` | `EXP_CAP_NONE` | `EXP_CAP_HARD` | `include/config/caps.h` |
| `B_LEVEL_CAP_TYPE` | `LEVEL_CAP_NONE` | `LEVEL_CAP_FLAG_LIST` | `include/config/caps.h` |
| `B_RARE_CANDY_CAP` | `FALSE` | `TRUE` | `include/config/caps.h` |
| `B_LEVEL_CAP_EXP_UP` | `FALSE` | `TRUE` | `include/config/caps.h` |
| `OW_REMATCH_TIER_BADGES` (new) | – | `TRUE` | `include/config/overworld.h` |
| Tests build: caps off (`B_EXP_CAP_TYPE`, `B_LEVEL_CAP_TYPE`, `B_RARE_CANDY_CAP`, `B_LEVEL_CAP_EXP_UP` back to vanilla) | – | – | `include/config/test.h` |

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
| `FLAG_HIDE_ROUTE_104_BRENDAN` (0x39) | Brendan at the Petalburg Woods entrance (cleared by the lab welcome) |
| `FLAG_HIDE_SLATEPORT_CITY_MAY` (0x3A) | May at Slateport's north exit (cleared after the Oceanic Museum) |
| `FLAG_HIDE_SOOTOPOLIS_CITY_RIVALS` (0x3B) | Brendan and May below the Sootopolis Gym (cleared by the Rain Badge) |
| `FLAG_HIDE_PETALBURG_CITY_WALLY_GYM` (0x3C) | Wally beside the Petalburg Gym door (cleared by the Heat Badge) |
| `FLAG_HIDE_LILYCOVE_CITY_WALLY` (0x3D) | Wally by the Lilycove Pokémon Center (cleared after the Petalburg battle) |
| `FLAG_HIDE_MOSSDEEP_SPACE_CENTER_RIVALS` (0x3E) | Brendan and May at the Space Center (cleared by the Mind Badge) |
| `FLAG_ENABLE_BRENDAN_MATCH_CALL` (0x3F) | Brendan in the PokéNav (registered after the Route 110 battle); May keeps `FLAG_ENABLE_RIVAL_MATCH_CALL` |

## Vars
| Var | Values |
|---|---|
| `VAR_DRACONID_STATE` (0x40F7) | `DRACONID_STATE_*`: 0 new game, 1 set clock, 2 clock set, 3 egg received, 4 egg hatched, 5 ready to leave, 6 left village |
| `VAR_ASTER_EGG` (0x40F8) | Aster's egg, `DRACONID_EGG_*` (counter-pick of the player's) |
| `VAR_SECOND_STARTER` (0x40F9) | `SECOND_STARTER_*`: 0 none, 1 Charmander, 2 Totodile, 3 Treecko |
| `VAR_PLAYER_OUTFIT` (0x40FA) | `PLAYER_OUTFIT_*`: 0 Draconid, 1 Magma – picks the player's sprites and trainer pics (`src/player_outfit.c`) |
| `VAR_ASTER_STATE` (0x40FB) | Aster arc progress (Phase 4) |
| `VAR_BRENDAN_STATE` (0x40FC) | `BRENDAN_STATE_*`: 0 waits on Route 104, 1 beaten there, 2 waits in Sootopolis, 3 Megas done |
| `VAR_MAY_STATE` (0x40FD) | `MAY_STATE_*`: 0, 1 waits at Slateport's north exit, 2 beaten there |
| `VAR_WALLY_STATE` (0x40FE) | `WALLY_STATE_*`: 0, 1 waits at the Petalburg Gym, 2 waits in Lilycove, 3 beaten there |
| `VAR_STARTER_MON` (changed meaning) | now the player's egg, `DRACONID_EGG_*`; the starter table in `src/starter_choose.c` maps it to Deino/Dreepy/Jangmo-o |

## Constants
| Constant | Where |
|---|---|
| `DRACONID_STATE_*`, `DRACONID_EGG_*`, `DRACONID_EGG_SPECIES_0..2`, `DRACONID_EGG_COUNT`, `DRACONID_HATCHLING_LEVEL`, `SECOND_STARTER_*` | `include/constants/draconid.h` |
| `PLAYER_OUTFIT_DRACONID`, `PLAYER_OUTFIT_MAGMA`, `PLAYER_OUTFIT_COUNT` | `include/constants/outfits.h` |
| `OBJ_EVENT_GFX_{DRACONID,MAGMA}_{M,F}_{NORMAL,MACH_BIKE,ACRO_BIKE,SURFING,FIELD_MOVE,FISHING,UNDERWATER,WATERING,DECORATING}` (36 ids) | `include/constants/event_objects.h` (generated region) |
| `OBJ_EVENT_PAL_TAG_{DRACONID,MAGMA}_{M,F}` + `_REFLECTION` (0x1140–0x1147) | `include/constants/event_objects.h` |
| `TRAINER_PIC_DRACONID_M/F`, `TRAINER_PIC_PLAYER_MAGMA_M/F` (Magma: grunt front pic + own back pic) | `include/constants/trainers.h`, `src/data/graphics/trainers.h` |
| `TRAINER_PIC_ASTER` (front only), `TRAINER_CLASS_DRACONID` ("DRACONID", 15 money, battle music `MUS_VS_RIVAL`) | `include/constants/trainers.h`, `src/data/graphics/trainers.h`, `src/battle_main.c`, `src/pokemon.c` |
| `OBJ_EVENT_GFX_DRACONID_{ELDER,OLD_WOMAN,MAN,WOMAN,BOY,GUARD}`, `OBJ_EVENT_GFX_ASTER`, `OBJ_EVENT_GFX_DRACONID_EGG_{DEINO,DREEPY,JANGMO_O}` | `include/constants/event_objects.h` (generated) |
| `OBJ_EVENT_PAL_TAG_DRACONID_NPC` (0x1148), `_ASTER` (0x1149), `_DRACONID_EGGS` (0x114A) | `include/constants/event_objects.h` (generated) |
| Aster's pass teams: `Class: Draconid`, `Pic: Aster`, `Music: Intense` | `src/data/trainers.party` |
| Draconid maps use the new NPC/egg sprites | `data/maps/Draconid*/map.json`, `tools/hack/mapgen/specs/` |
| `TRAINER_ASTER_PASS_DEINO/_DREEPY/_JANGMO_O` (855–857), `TRAINERS_COUNT_EMERALD` 855→858 | `include/constants/opponents.h`, teams in `src/data/trainers.party` |
| `MAP_DRACONID_VILLAGE`, `MAP_DRACONID_PASS` (group TownsAndRoutes); `MAP_DRACONID_VILLAGE_PLAYERS_HOUSE_1F/_2F`, `_ELDERS_HOUSE`, `_SHRINE`, `_HOUSE1`, `_HOUSE2` (new group `gMapGroup_IndoorDraconid`) | `data/maps/map_groups.json`, `data/maps/Draconid*/` |
| `LAYOUT_DRACONID_VILLAGE`, `LAYOUT_DRACONID_PASS`, `LAYOUT_DRACONID_VILLAGE_PLAYERS_HOUSE_1F/_2F`, `_ELDERS_HOUSE`, `_SHRINE` (House1/2 reuse `LAYOUT_HOUSE2`/`LAYOUT_HOUSE1`) | `data/layouts/layouts.json` |
| `MAPSEC_DRACONID_VILLAGE` (x2 y11), `MAPSEC_DRACONID_PASS` (x3 y11) | `src/data/region_map/region_map_sections.json`, `region_map_layout.h`, popup themes in `src/map_name_popup.c` |
| `HEAL_LOCATION_DRACONID_VILLAGE_PLAYERS_HOUSE_2F`, `HEAL_LOCATION_DRACONID_VILLAGE` | `src/data/heal_locations.json` |
| Route 101 ↔ Draconid Pass connection (Route 101 left, offset −22; pass rows 26–27 = Route 101 rows 4–5) | `data/maps/Route101/map.json` |
| `LOCALID_BIRCHS_LAB_BRENDAN` object (5, 4); lab rival object is always `OBJ_EVENT_GFX_RIVAL_MAY_NORMAL` | `data/maps/LittlerootTown_ProfessorBirchsLab/map.json` |
| `BRENDAN_STATE_*`, `MAY_STATE_*`, `WALLY_STATE_*` | `include/constants/draconid.h` |
| Rival trainer ids renamed (same numbers, 520–537, 592/593/599/600, 661–666, 768/769): `TRAINER_BRENDAN_{ROUTE_104,ROUTE_110,ROUTE_119,LILYCOVE,SOOTOPOLIS,POSTGAME,POSTGAME_DOUBLE}`, `TRAINER_MAY_{ROUTE_103,RUSTBORO,SLATEPORT,LILYCOVE,SOOTOPOLIS,POSTGAME,POSTGAME_DOUBLE}`, `TRAINER_ASTER_{METEOR_FALLS,ROUTE_119,SKY_PILLAR,POSTGAME}_{DEINO,DREEPY,JANGMO_O}` (named after the player's egg), `TRAINER_WALLY_{PETALBURG,LILYCOVE}`, spares `TRAINER_DRACONID_SPARE_1/2` | `include/constants/opponents.h`, teams in `src/data/trainers.party` |
| `PARTNER_MAY` (2), `PARTNER_BRENDAN` (3), `PARTNER_COUNT` 4 | `include/constants/battle_partner.h`, `src/data/battle_partners.party` |
| New objects: `LOCALID_ROUTE104_BRENDAN` (10, 39), `LOCALID_SLATEPORT_MAY` (18, 2), `LOCALID_LILYCOVE_MAY` (existing rival object) + `LOCALID_LILYCOVE_BRENDAN` (28, 7), `LOCALID_LILYCOVE_WALLY` (26, 16), `LOCALID_SOOTOPOLIS_MAY/_BRENDAN` (30/32, 35), `LOCALID_PETALBURG_WALLY_GYM` (13, 9), `LOCALID_SPACE_CENTER_2F_MAY/_BRENDAN` (4/5, 5); coord triggers on Route 104 (10–11, 41), Slateport (16–20, 5), Petalburg (15, 9) | `data/maps/*/map.json` |
| Macro `trainerbattle_two_trainers_no_intro` (scripted two-trainer double; the script continues after it) | `asm/macros/event.inc` |
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
| New: player outfits – `GetPlayerOutfit`, `GetPlayerOutfitAvatarGfx`, `GetPlayerOutfitDecoratingGfx`, `GetPlayerOutfitTrainerPic`, `IsFemaleOutfitAvatarGfx`, special `SetPlayerOutfit` | `src/player_outfit.c`, `include/player_outfit.h`, `data/specials.inc` |
| Player avatar gfx come from the outfit (Emerald); state↔gfx lookups go through it | `src/field_player_avatar.c` |
| Player trainer pics come from the outfit: battle back pic, front pic (transitions, Pokédex, Frontier), Hall of Fame, trainer card, new-game gender choice | `src/trainer.c`, `src/pokemon.c`, `src/trainer_pokemon_sprites.c`, `src/trainer_card.c`, `src/main_menu.c` |
| Decorating sprite and easy-chat interview sprite follow the outfit | `src/decoration.c`, `src/easy_chat.c` |
| Region map / PokéNav player icon: Draconid or Magma head per outfit | `src/region_map.c`, `graphics/pokenav/region_map/*_icon.png` |
| Outfit sprite data, palettes, reflection sets (generated) | `src/data/object_events/*.h`, `src/event_object_movement.c` |
| Level caps per badge: 15/20/25/30/34/38/44/48, 60 until the Champion (was 15/19/24/29/31/33/42/46/58) | `src/caps.c` (`sLevelCapFlagMap`) |
| Rematch tiers gated by badges (`IsRematchTierUnlocked`, `GetBadgeCount`) | `src/battle_setup.c` (`GetRematchTrainerIdFromTable`) |
| Match call: Brendan and May are both rivals for either gender; Brendan's entry uses `FLAG_ENABLE_BRENDAN_MATCH_CALL` | `src/pokenav_match_call_data.c` |
| Quickstart (debug) names the player KAI / ZARA instead of the rivals' names | `src/quickstart.c` |
| Emulator test hook (debug builds only): `gDraconidTestWarp` + `Draconid_TryTestWarp` (warp / heal on request), called from `ProcessPlayerFieldInput` | `src/draconid.c`, `include/draconid.h`, `src/field_control_avatar.c` |

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
| Rival battles vanilla doesn't have: Brendan on Route 104, May in Slateport, Brendan's PokéNav registration, Lilycove two-on-two, Space Center partner choice, Sootopolis Megas, post-game lab singles + double, Wally at the Petalburg Gym and in Lilycove | `data/scripts/draconid/rivals.pory` |
| Rival scenes no longer depend on the player's gender: `Common_EventScript_SetupRivalGfxId`/`OnBikeGfxId` always May; Rustboro/Route 104 always May (`TRAINER_MAY_RUSTBORO`); Route 110 and Route 119 always Brendan (gfx set in their OnTransition); per-starter battle branches replaced by one battle each; Route 103's vanilla branches removed | `data/scripts/rival_graphics.inc`, `data/maps/{RustboroCity,Route104,Route110,Route119,Route103}/scripts.inc` |
| Hooks: Lilycove rival → `LilycoveCity_EventScript_DraconidRivals`; Space Center "ready?" → `…_DraconidChoosePartner`, rivals leave after Maxie gives up; Mossdeep Gym shows the Space Center rivals; Sootopolis Gym → `…_DraconidRivalsWait`, Sootopolis OnFrame → Mega scene; Lavaridge Gym → `…_DraconidWallyWaits`; Oceanic Museum 2F → `…_DraconidMayWaits`; Route 110 → `…_DraconidRegisterBrendan`; lab OnTransition/rival/Brendan → post-game scripts; debug menu's Steven multi battle → partner choice | `data/maps/*/scripts.inc`, `data/scripts/debug.inc` |
