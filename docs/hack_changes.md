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
| Emulator regression tests | `tools/hack/emu/tests/*.play` | `opening.play` (new game → lab, `-D GENDER=F`), `route103.play` (→ May), `route104.play` (Brendan), `rivals.play` (the other new rival scenes), `second_starter.play` (Rustboro), `aster.play` (Aster arc, disguise, Mega Ring), `postgame_home.play` (SS Ticket / Lati TV in the Draconid house); `play.py` gained `warp`, `heal` (debug builds), ledge-aware `path`, `choose`, `expect_opponent/_trainer/_item/_gfx`; `gbarun` `until` takes `!VALUE`; `matrix.py` runs every gender × egg × second starter; `release_boot.play` + LTO symbol names for release ROMs |
| Story checker | `tools/hack/check_story.py` | every new flag / story state written and read, hide flags toggle |
| Player outfit art builders | `tools/hack/art/player/build_player.py`, `build_pics.py`, specs `draconid_m/f.json`, `magma_m/f.json`, `*_pics.json` | see docs/hack_art_pipeline.md |
| Outfit C code generator | `tools/hack/art/player/gen_outfit_code.py` | writes between `DRACONID PLAYER OUTFITS` markers |
| Art manifest | `tools/hack/art/manifests/draconid.json` | `validate.py --manifest` for all player art; new `map_icon` profile in `gbaart.py` |
| Art tool ops (round 1) | `tools/hack/art/kitbash.py`, `tools/hack/art/player/build_pics.py` | kitbash: `remap_inner`, `pattern`, `outline`, `save_pal` (+ reflection), `pixels` `under`, per-frame `frames`/`shift`/`axis: y` on box steps; build_pics: per-frame `remap` (`frames`) and `pattern`; existing specs build byte-identical |
| Zinnia art (round 1): overworld sheet (9 × 16×32) + palette and water-reflection palette, trainer front pic | `graphics/object_events/pics/people/draconid/zinnia.png`, `graphics/object_events/palettes/zinnia{,_reflection}.pal`, `graphics/trainers/front_pics/zinnia.png`; recipes `tools/hack/art/recipes/zinnia.json`, `zinnia_front_pic.json` (kitbash); `tools/hack/art/manifests/draconid.json` | art only, no C here: the Sky Pillar Zinnia branch registers the sprite and the pic at these paths (D-180, D-181); see docs/hack_art_pipeline.md |
| Trainer tools | `tools/hack/trainers/`: `party.py` (reader/writer), `scan_maps.py` (map → trainers), `build_segments.py` → `segments.json` (segment, role, cap per trainer), `check_party.py` (legality, caps, headers, trainerproc), `splice_party.py` (merge batches, `--target`), `learnset.py`, `check_tiers.py` (rematch tiers grow), `report.py` (trainer table in hack_trainers.md), `sources.json` (where each team comes from) | see docs/hack_trainers.md |
| ORAS trainer data (round 1, feedback 1.15): `tools/hack/trainers/oras/` – `scrape_serebii.py` → `oras_trainers.json` (Serebii, 2026-09-30), `match_oras.py` → `oras_matches.json`, `build_oras_batch.py` (drafts + `--check`), batches `batch_oras_first.party` (27 trainers, `oras-first`), `batch_elite_four.party` (Sidney, Phoebe, Glacia, Drake: ORAS post-game rosters at S9 levels, `oras-rematch`) spliced into `src/data/trainers.party`; `elite_four_rematch.party` (ids `TRAINER_{SIDNEY,PHOEBE,GLACIA,DRAKE}_REMATCH`, not in the ROM); `check_party.py`: Elite Four exempt from the species-pool warning, their rematch ids allowed Megas (`ORAS_MEGA_TRAINERS`); `sources.json` updated (D-170–D-175) | `tools/hack/trainers/`, `src/data/trainers.party` | see docs/hack_trainers.md, "ORAS data" |

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
| `FLAG_HIDE_DRACONID_VILLAGE_SHOES_GIVER` (0x2A, was `…_MOM`, round 1) | the old woman outside the shrine who gives the Running Shoes |
| `FLAG_HIDE_DRACONID_HOUSE_2F_ASTER` (0x2B, was `…_2F_MOM`, round 1) | Aster at the bedroom door (prologue: the Elder calls) |
| `FLAG_DRACONID_NO_WHITEOUT` (0x2C) | `B_FLAG_NO_WHITEOUT`: set around scripted battles the player may lose |
| `FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BRENDAN` (0x2D) | Brendan in Birch's lab (the welcome scene) |
| `FLAG_DEBUG_NO_ENCOUNTER` (0x2E), `FLAG_DEBUG_NO_TRAINER_SEE` (0x2F), `FLAG_DEBUG_NO_COLLISION` (0x30) | the expansion's debug toggles (debug menu, emulator tests); never set by the game |
| `FLAG_VISITED_DRACONID_VILLAGE` (`SYSTEM_FLAGS+0x21`, was `FLAG_UNUSED_0x881`) | fly destination |
| `FLAG_HIDE_RUSTBORO_CITY_TABITHA` (0x39, was `FLAG_HIDE_ROUTE_104_BRENDAN`, round 1) | Tabitha beside the Rustboro Gym door (cleared by the Stone Badge; her order) |
| 0x3A (was `FLAG_HIDE_SLATEPORT_CITY_MAY`) | free again (round 1 removed the v1 Slateport May scene) |
| `FLAG_HIDE_SOOTOPOLIS_CITY_RIVALS` (0x3B) | Brendan and May below the Sootopolis Gym (cleared by the Rain Badge) |
| `FLAG_HIDE_PETALBURG_CITY_WALLY_GYM` (0x3C) | Wally beside the Petalburg Gym door (cleared by the Heat Badge) |
| `FLAG_HIDE_LILYCOVE_CITY_WALLY` (0x3D) | Wally by the Lilycove Pokémon Center (cleared after the Petalburg battle) |
| `FLAG_HIDE_MOSSDEEP_SPACE_CENTER_RIVALS` (0x3E) | Brendan and May at the Space Center (cleared by the Mind Badge) |
| `FLAG_HIDE_RUSTBORO_CITY_BIRCH` (0x40) | Prof. Birch outside the Rustboro Gym (cleared by the Stone Badge; second starter) |
| `FLAG_HIDE_METEOR_FALLS_ASTER` (0x41) | Aster in Meteor Falls (after Magma takes the meteorite) |
| `FLAG_HIDE_CABLE_CAR_STATION_ASTER` (0x42) | Aster at the Route 112 cable car station (the disguise) |
| `FLAG_DEVON_GOODS_RETURNED` (0x43, was `FLAG_HIDE_ROUTE_119_ASTER`, round 1) | the player chose to return the Devon Goods to Devon in Rusturf Tunnel (D-118); read by Tabitha in the museum and the employee in Rustboro |
| `FLAG_HIDE_OCEANIC_MUSEUM_TABITHA` (0x49, round 1) | Tabitha in the Oceanic Museum 1F (cleared by the goods choice, set after the raid) |
| `FLAG_HIDE_MAGMA_HIDEOUT_ASTER` (0x44) | Aster in the Magma Hideout 4F (shown after Maxie) |
| `FLAG_HIDE_SKY_PILLAR_TOP_ASTER` (0x45) | Aster at the top of the Sky Pillar |
| `FLAG_RECEIVED_MEGA_RING` (0x46) | the Elder gave the Mega Ring (and the second starter's Mega Stone) |
| `FLAG_HIDE_PLAYERS_HOUSE_DAD` (vanilla) | now also hides Norman in the Draconid house 1F (shown by the Hall of Fame) |
| `FLAG_HIDE_DRACONID_HOUSE_ELDER` (0x47, round 1) | the Elder in the player's house 1F (cleared by the Hall of Fame for the post-game scene, D-112) |
| `FLAG_HIDE_PETALBURG_WOODS_COURTNEY` (0x48, round 1) | Courtney in Petalburg Woods (cleared after Nerine is beaten) |
| `FLAG_HIDE_RUSTBORO_CITY_RIVAL` (vanilla, round 1) | now Brendan at Rustboro's south edge: cleared by the outpost scene, set when he walks off; the Devon 3F no longer clears it |
| `FLAG_EXP_SHARE_ON` (0x68, was unused, round 1) | the Gen 6 Exp. Share is on (`I_EXP_SHARE_FLAG`; set when Mr. Stone gives it, toggled by using it) (D-185) |
| `FLAG_TEMP_11` in `PetalburgCity_Gym` (round 1) | hides May (`LOCALID_PETALBURG_GYM_MAY`) unless `VAR_PETALBURG_GYM_STATE` is 6 (set by the gym's OnTransition) |
| `FLAG_ENABLE_BRENDAN_MATCH_CALL` (0x3F) | Brendan in the PokéNav (registered after the Route 110 battle); May keeps `FLAG_ENABLE_RIVAL_MATCH_CALL` |

## Vars
| Var | Values |
|---|---|
| `VAR_DRACONID_STATE` (0x40F7) | `DRACONID_STATE_*`: 0 new game, 1 set clock, 2 clock set, 3 egg received, 4 egg hatched, 5 ready to leave, 6 left village, 7 Stone Badge (Birch waits in Rustboro), 8 second starter received |
| `VAR_ASTER_EGG` (0x40F8) | Aster's egg, `DRACONID_EGG_*` (counter-pick of the player's) |
| `VAR_SECOND_STARTER` (0x40F9) | `SECOND_STARTER_*`: 0 none, 1 Charmander, 2 Totodile, 3 Treecko |
| `VAR_PLAYER_OUTFIT` (0x40FA) | `PLAYER_OUTFIT_*`: 0 Draconid, 1 Magma – picks the player's sprites and trainer pics (`src/player_outfit.c`) |
| `VAR_ASTER_STATE` (0x40FB) | `ASTER_STATE_*` (round 1, story order; 2, 3, 5 are v1 steps the act reworks remove): 0 start, 1 Meteor Falls, 2 disguised, 3 Mt. Chimney done, 4 unused, 5 Magma Hideout, 6 Mega Ring, 7 Rayquaza called (Act 5), 8 Sky Pillar finale, 9 post-game. |
| `VAR_BRENDAN_STATE` (0x40FC) | `BRENDAN_STATE_*` (round 1, story order): 0 confronts the player at Rustboro's south edge (the vanilla rival triggers on row 53), 1 beaten there, 2 Mt. Chimney, 3 Route 119 (PokéNav), 4 Lilycove, 5 Mossdeep, 6 Sootopolis, 7 v1 Sootopolis Megas (Act 5 reworks), 8 post-game |
| `VAR_MAY_STATE` (0x40FD) | `MAY_STATE_*` (round 1, story order): 0, 1 Route 110 (PokéNav), 2 Weather Institute, 3 Lilycove, 4 Sootopolis, 5 post-game |
| `VAR_WALLY_STATE` (0x40FE) | `WALLY_STATE_*`: 0, 1 waits at the Petalburg Gym, 2 waits in Lilycove, 3 beaten there |
| `VAR_LITTLEROOT_HOUSES_STATE_MAY` (vanilla) | state 3 (after the Hall of Fame) now starts the SS Ticket / Lati TV scene in the Draconid house 1F, not in Littleroot |
| `VAR_DRACONID_REPUTATION` (0x40FF, was unused) | `REPUTATION_*`: 0 pre-uniform, 1 uniform (Magma grunt), 2 revealed – NPC lines and the outfit follow it (D-103) |
| `VAR_NERINE_STATE` (0x40E5, was unused) | `NERINE_STATE_*`: Nerine's fights done, 0 start … 7 revealed … 9 post-game |
| `VAR_ASTER_EGG` (changed meaning, round 1) | Aster's egg is the **leftover** one (D-105), not the counter-pick |
| `VAR_MAGMA_STATE` (0x404E, was unused, round 1) | `MAGMA_STATE_*`: the player's Team Magma career, 0 none, 1 recruited (outpost), 2 Tabitha's order (Stone Badge), 3 Devon Goods … 9 promoted … 12 turned at Sootopolis |
| `VAR_PETALBURG_WOODS_STATE` (vanilla, round 1) | 2 = on the way to the Magma outpost (its OnFrame runs the uniform scene), 3 = recruited; vanilla 1 is skipped |
| `VAR_RUSTBORO_CITY_STATE`, `VAR_ROUTE104_STATE` (vanilla, round 1) | the PokéNav scene sets 8 and 2 directly: the vanilla May registration in Rustboro / at Briney's cottage never runs (May registers on Route 110) |
| `VAR_MAXIE_CALL` (0x40A1), `VAR_MAXIE_CALL_STEPS` (0x40A8) (round 1) | the last of Maxie's calls played (`MAXIE_CALL_*`) and the steps outdoors since the next one became due (D-186) |
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
| `REPUTATION_*`, `NERINE_STATE_*`, `DRACONID_EVO_LEVEL_MIDDLE/_FINAL` | `include/constants/draconid.h` |
| `MAGMA_STATE_*` (0–12), `BRENDAN_STATE_RUSTBORO` (was `…_ROUTE_104`), `DRACONID_RESCUE_SPECIES` (Poochyena) / `DRACONID_RESCUE_LEVEL` (2) (round 1) | `include/constants/draconid.h` |
| Round 1 trainer id renames (same numbers): 520 `TRAINER_BRENDAN_RUSTBORO`, 521 `…_MT_CHIMNEY`, 523 `TRAINER_MAY_ROUTE_110`, 524 `TRAINER_BRENDAN_MOSSDEEP`, 525 `TRAINER_STEVEN_MOSSDEEP`, 533–535 `TRAINER_MAXIE_SOOTOPOLIS`, `…_SOOTOPOLIS_MULTI`, `TRAINER_ARCHIE_SOOTOPOLIS_MULTI`; story teams for Nerine, Aster, Brendan, May, Steven, Maxie, Archie written against the round 1 schedule | `include/constants/opponents.h`, `src/data/trainers.party` |
| `PARTNER_TABITHA` (4), `PARTNER_NERINE_{egg}_{starter}` (5–13), `PARTNER_COUNT` 14; `PARTNER_MAY/_BRENDAN` teams rewritten for the Sootopolis multi battle | `include/constants/battle_partner.h`, `src/data/battle_partners.party` |
| `MAP_PETALBURG_WOODS_MAGMA_OUTPOST` (group `gMapGroup_IndoorRoute104`), `LAYOUT_PETALBURG_WOODS_MAGMA_OUTPOST` (copy of the Fossil Maniac's house without the tunnel), door → Route 104 warp 2 (woods north entrance) (D-113) | `tools/hack/mapgen/specs/petalburg_woods_magma_outpost.json`, `data/maps/PetalburgWoods_MagmaOutpost/`, `data/layouts/` |
| Round 1 objects: `LOCALID_PETALBURG_WOODS_COURTNEY` (22, 17), the woods grunt is Nerine (`OBJ_EVENT_GFX_NERINE_AQUA`), `LOCALID_MAGMA_OUTPOST_COURTNEY/_GRUNT_M/_GRUNT_F`, `LOCALID_RUSTBORO_TABITHA` (25, 20; grunt sprite, as vanilla draws Tabitha), `LOCALID_PETALBURG_GYM_MAY` (7, 4), Rustboro's rival object is Brendan; removed: `LOCALID_ROUTE104_BRENDAN` + its triggers, `LOCALID_ROUTE119_ASTER` + its triggers | `data/maps/*/map.json` |
| Nerine's trainer ids 858–923 (`TRAINER_NERINE_PETALBURG_WOODS_{egg}`, `TRAINER_NERINE_{RUSTURF,SLATEPORT,MT_CHIMNEY,MT_PYRE,AQUA_HIDEOUT,SEAFLOOR,POSTGAME}_{egg}_{starter}`, named after the player's choices); `TRAINERS_COUNT_EMERALD` 924, `MAX_TRAINERS_COUNT_EMERALD` 864 → 928 (system flags move up 64; SaveBlock1 +8 bytes, `test/save.c` updated as it asks) | `include/constants/opponents.h`, `test/save.c`, placeholder teams at the end of `src/data/trainers.party` |
| `OBJ_EVENT_GFX_NERINE_AQUA`, `OBJ_EVENT_GFX_NERINE`, `OBJ_EVENT_GFX_COURTNEY` + palette tags 0x114B–0x114D (sheets from `tools/hack/art/recipes/{nerine_aqua,nerine,courtney}.json`, D-160–D-162) | `tools/hack/art/player/gen_outfit_code.py` (generated regions), `graphics/object_events/pics/people/draconid/`, `graphics/object_events/palettes/` |
| `TRAINER_PIC_NERINE_AQUA`, `TRAINER_PIC_NERINE` (front pics from `recipes/nerine_aqua_front_pic.json`, `recipes/nerine_front_pic.json`); `TRAINER_PIC_NERINE` also has a back pic (`gTrainerBackPic_Nerine`, `player/nerine_pics.json`) for the Sky Pillar tag battle | `include/constants/trainers.h`, `src/data/graphics/trainers.h`, `graphics/trainers/front_pics/nerine*.png`, `graphics/trainers/back_pics/nerine.png` |
| `TRAINER_PIC_MAGMA_ADMIN` (Tabitha) gets a back pic (`gTrainerBackPic_MagmaAdmin`, `player/tabitha_pics.json`) for the Space Center tag battle (D-108, D-163) | `src/data/graphics/trainers.h`, `graphics/trainers/back_pics/magma_admin.png` |
| `DRACONID_STATE_SECOND_STARTER` (7), `DRACONID_STATE_GOT_SECOND_STARTER` (8), `SECOND_STARTER_LEVEL` (10), `ASTER_STATE_*` (0–8) | `include/constants/draconid.h` |
| New objects: `LOCALID_RUSTBORO_BIRCH` (28, 23); Aster: `LOCALID_METEOR_FALLS_ASTER` (17, 18), `LOCALID_CABLE_CAR_STATION_ASTER` (6, 8), `LOCALID_ROUTE119_ASTER` (30, 17) + coord triggers across row 19 (x 28–31, 34–35) on `VAR_ASTER_STATE` 3, `LOCALID_MAGMA_HIDEOUT_4F_ASTER` (18, 21), `LOCALID_SKY_PILLAR_TOP_ASTER` (14, 12); shrine Aster gets a post-game script; `LOCALID_DRACONID_HOUSE_DAD` (Norman, 5, 6) in the Draconid house 1F | `data/maps/*/map.json` |
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
| `{RIVAL}` always expands to BRENDAN (Birch's son, round 1 D-100; v1 had MAY) | `src/string_util.c` |
| Birch's rescue battle is against `DRACONID_RESCUE_SPECIES` (Poochyena) at `DRACONID_RESCUE_LEVEL` (was Zigzagoon Lv 2) (round 1) | `src/battle_controllers.c`, `data/maps/Route101/map.json` (the chasing object) |
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
| New special `GetPlayerOutfitNormalGfx` (the player's walking sprite for the current outfit, for scenes that draw the player as an NPC) | `src/player_outfit.c`, `include/player_outfit.h`, `data/specials.inc` |
| Player's-house TV (Lati news flash, movie, "Mom might like this") checks the Draconid house 1F instead of the gender's Littleroot house (`IsInPlayersHouse1F`) | `src/tv.c` |
| Fix: an early-rival battle with `RIVAL_BATTLE_HEAL_AFTER` no longer turns into the first (tutorial) battle, which in Emerald replaced the rival's team with a wild Lv 2 Zigzagoon (the flag test needs all bits of `RIVAL_BATTLE_TUTORIAL`) | `src/battle_setup.c` |
| Credits: the player is a Draconid run cycle (`CreateCreditsDraconidSprite`, `TAG_DRACONID`, `sAnims_DraconidRun`, `DRACONID_CREDITS_RUN_Y`) and May always rides in as the rival (D-049) | `src/credits.c`, `src/intro_credits_graphics.c`, `include/intro_credits_graphics.h`, `graphics/intro/scene_2/draconid_{m,f}_credits.png`, `tools/hack/art/player/draconid_credits.json` |
| Deino, Dreepy and Jangmo-o lines evolve at `DRACONID_EVO_LEVEL_MIDDLE` (25) and `DRACONID_EVO_LEVEL_FINAL` (50) (D-107) | `src/data/pokemon/species_info/gen_{5,7,8}_families.h`, `include/constants/draconid.h`, `src/data/pokemon/species_info.h` |
| The name-entry screen shows the player's outfit sprite (vanilla drew the rival Brendan/May); linked Emerald players appear as Draconid tamers (`GetOutfitAvatarGfx`) | `src/naming_screen.c`, `src/overworld.c`, `src/player_outfit.c`, `include/player_outfit.h` |
| Variant trainers: `Draconid_ResolveVariantTrainer` swaps a fight's first id for the variant of the player's egg (and second starter) when the battle loads (`TrainerBattleLoadArgs`); table in `src/data/draconid_variant_trainers.h` (Aster's 4 fights, Nerine's 8) (D-101) | `src/draconid.c`, `include/draconid.h`, `src/battle_setup.c`, `src/data/draconid_variant_trainers.h` |
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
| Second starter: Prof. Birch outside the Rustboro Gym after the Stone Badge (Charmander / Totodile / Treecko at Lv 10) | `data/scripts/draconid/second_starter.pory`; hooks: `RustboroCity_Gym` badge → `…_DraconidBirchWaits`, `RustboroCity` OnFrame (`VAR_DRACONID_STATE` 7) |
| Aster's arc (Meteor Falls, cable car disguise, Route 119, Magma Hideout, Mega Ring from the Elder, Sky Pillar, post-game shrine) and the Team Magma disguise (`Draconid_EventScript_ChangeOutfit`) | `data/scripts/draconid/aster.pory`; hooks: end of `MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene`, `Route112_CableCarStation` OnFrame (`VAR_ASTER_STATE` 1), end of `MtChimney_EventScript_Maxie`, `MagmaHideout_1F` OnTransition + new OnFrame (`VAR_TEMP_1` 1), end of `MagmaHideout_4F_EventScript_Maxie`, start and end of `SkyPillar_Top_EventScript_AwakenRayquaza`, Elder (`VAR_ASTER_STATE` 5), shrine OnTransition |
| New game hides Birch in Rustboro and the five Aster objects | `data/scripts/draconid/new_game.pory` |
| Scenes that drew the player as Brendan/May use `GetPlayerOutfitNormalGfx`: Frontier Arena/Dome/Factory/Palace battle rooms, Battle Tower multi room + corridor, Fallarbor/Slateport/Verdanturf battle tents, contest hall, Route 111 Mirage Tower fall, Southern Island | `data/maps/*/scripts.inc` |
| Rival is always May in the remaining gender branches: Oldale, Lavaridge (Go-Goggles), Champion's room, lab post-game lines | `data/maps/{OldaleTown,LavaridgeTown,EverGrandeCity_ChampionsRoom,LittlerootTown_ProfessorBirchsLab}/scripts.inc` |
| Littleroot houses belong to the rivals: no player scenes (moving-in, shoes manual, clock, PC, decorations), May's room always May, Brendan's house sign names him, post-game Birch waits outside May's house | `data/maps/LittlerootTown*/scripts.inc` |
| Hall of Fame: respawn in the Draconid bedroom for both genders | `data/maps/EverGrandeCity_HallOfFame/scripts.inc` |
| SS Ticket / Lati TV scene moved to the Draconid house: new entry label `PlayersHouse_1F_EventScript_SSTicketAndLatiTV` (after the gender setup), `DraconidVillage_PlayersHouse_1F` OnFrame jumps there with the Brendan-house movements; the Littleroot houses' OnFrame entries removed | `data/scripts/players_house.inc`, `data/maps/DraconidVillage_PlayersHouse_1F/scripts.pory`, `data/maps/LittlerootTown_{Brendans,Mays}House_1F/scripts.inc` |
| Dialogue: Rustboro's Mr. Briney hint (May, and Brendan's unused twin) and Rydel's bike speech no longer assume the player just moved to Littleroot | `data/maps/RustboroCity/scripts.inc`, `data/maps/MauvilleCity_BikeShop/scripts.inc` |
| Route 103 May is an early-rival battle (`trainerbattle_earlyrival … RIVAL_BATTLE_HEAL_AFTER`): a loss heals and the scene continues with its own line (D-048) | `data/scripts/draconid/birch_intro.pory` |
| Birch's new-game speech: the player is of the Draconid clan, not moving to Littleroot | `data/text/birch_speech.inc` |
| **Round 1, Act 1** (`docs/hack_story.md`): night prologue with the falling star, Aster wakes the player (no Mom); the Elder's prophecy and mission in the egg ceremony, the leftover egg set aside for Aster, and the egg kept for "one who walks a far road" (Nerine); the old woman gives the Running Shoes | `data/maps/DraconidVillage*/scripts.pory` |
| Round 1: Littleroot – Mrs. Birch in Brendan's house and May's mom in May's house, lines by reputation; house signs; the lab introduces Brendan as Birch's son and May as Norman's daughter | `data/scripts/draconid/act1.pory`, `birch_intro.pory`, `data/maps/LittlerootTown*/` |
| Round 1: Petalburg Gym – Norman is May's father in every line (`@ Draconid Emerald`), uniform lines before the fourth badge, a revealed line after it; May watches the Norman battle and speaks after it (`…_DraconidMayWatched`) | `data/maps/PetalburgCity_Gym/scripts.inc`, `data/scripts/draconid/act4.pory` |
| Round 1: Petalburg Woods – Nerine (Aqua disguise) robs the Devon researcher (`TRAINER_NERINE_PETALBURG_WOODS_DEINO`, resolved by egg), Courtney recruits the player (`PetalburgWoods_EventScript_DraconidRecruitment`), the outpost cabin puts the uniform on (reputation `UNIFORM`, `MAGMA_STATE_RECRUITED`) | `data/maps/PetalburgWoods/scripts.inc`, `data/scripts/draconid/act1.pory`, `data/maps/PetalburgWoods_MagmaOutpost/scripts.pory` |
| Round 1: Rustboro – Brendan's confrontation (`RustboroCity_EventScript_DraconidBrendan`, hooked through `RivalEncounter`), Tabitha's order before Birch's second starter (`…_DraconidTabithaOrders`), Birch's lines about the uniform; the v1 Route 104 Brendan and Route 119 Aster scenes are removed | `data/scripts/draconid/act1.pory`, `second_starter.pory`, `data/maps/RustboroCity/scripts.inc` |
| Emulator tests (round 1): `woods.play` (Nerine, Courtney, outpost, uniform; `-D EGGNAME -D MAGMA`), `rustboro.play` (Brendan) replace `route104.play`; `second_starter.play` also checks Tabitha; `matrix.py` chains opening → route103 → woods → rustboro; `check_story.py` knows `VAR_NERINE_STATE`, `VAR_MAGMA_STATE`, `VAR_DRACONID_REPUTATION` and lists the states of acts not scripted yet as pending | `tools/hack/emu/`, `tools/hack/check_story.py` |
| Reputation dialogue (D-103, D-117): uniform / revealed lines for 68 townsfolk in 16 towns, Wally's family (5), Mr. Briney's idle lines (2), 7 Gym Guides + Leaders (not Petalburg), and the shared NPCs; shared helpers `Draconid_EventScript_RepTurnAway`, `…_NurseGreeting`, `…_MartGreeting`/`…_MartGoodbye`, `…_CableClubAside`, `…_WirelessClubAttendant`; every line in `docs/reputation_dialogue.md` | `data/scripts/draconid/reputation/*.pory` (one file per town/area + `shared.pory`), included in `data/event_scripts.s` |
| Reputation hooks (one `@ Draconid Emerald` line each): nurse greeting / "I'll take them" / "restored"; Poké Mart greeting + goodbye → `call Draconid_EventScript_Mart*` in 17 shops (11 town marts, Lilycove Department Store 2F–5F + rooftop, Pokémon League); Union Room + Direct Corner aside, TEALA's question; Day Care man's idle line, woman's offer; each Gym Leader and Gym Guide script (Rustboro, Dewford, Mauville, Lavaridge, Fortree, Mossdeep; Sootopolis only when revealed) | `data/scripts/{pkmn_center_nurse,cable_club,day_care}.inc`, `data/maps/*_Mart/`, `LilycoveCity_DepartmentStore*/`, `EverGrandeCity_PokemonLeague_1F/`, `*_Gym*/scripts.inc` |
| Reputation townsfolk: the object's `script` in `map.json` → `<Map>_EventScript_DraconidRep<Name>` (falls back to `<Map>_EventScript_<Name>`) for 75 objects | `data/maps/*/map.json` (list in `docs/reputation_dialogue.md`) |
| **Round 1, Act 2**: Nerine steals the Devon Goods in Rustboro (her sprite and line), Tabitha's order out of the Gym (`RustboroCity_EventScript_DraconidTabithaGoodsOrder`, called at the end of the theft), Nerine in Rusturf Tunnel (`TRAINER_NERINE_RUSTURF_DEINO_CHARMANDER`, variant by egg × second starter) and the goods choice (`RusturfTunnel_EventScript_DraconidGoodsChoice`), the employee and Mr. Stone about the uniform, Steven ("MAGMA doesn't usually deliver mail"), Tabitha past the museum counter (`SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder`, called after the fee), Nerine as the second museum battle (`TRAINER_NERINE_SLATEPORT_…`), Archie and Stern about the uniform, May on Route 110 (the vanilla rival scene, `TRAINER_MAY_ROUTE_110`, PokéNav registration `Route110_EventScript_DraconidRegisterMay`), Wally's Mauville lines; the v1 Slateport May scene and the v1 Route 110 Brendan registration are removed | `data/scripts/draconid/act2.pory`; `data/maps/{RustboroCity,RusturfTunnel,RustboroCity_DevonCorp_3F,GraniteCave_StevensRoom,SlateportCity_OceanicMuseum_1F,SlateportCity_OceanicMuseum_2F,Route110,MauvilleCity}/scripts.inc` (`@ Draconid Emerald`), their `map.json` |
| New object `LOCALID_OCEANIC_MUSEUM_1F_TABITHA` (10, 4); Nerine's sprite on the Rustboro thief, the Rusturf grunt and museum 2F grunt 1; the Slateport May object and triggers removed | `data/maps/*/map.json` |
| `act2.play` (theft + Tabitha, Rusturf + choice, Mr. Stone, Steven, museum, Route 110, Mauville; `-D EGGNAME SECOND SECONDNAME GOODS RETURNED`), in the matrix per egg × second starter (Totodile runs keep the goods) | `tools/hack/emu/tests/act2.play`, `tools/hack/emu/matrix.py` |
| `docs/hack_script.md` (all new and reworked dialogue by scene) generated by `tools/hack/gen_script_doc.py` (`--check` for staleness) | `tools/hack/gen_script_doc.py`, `docs/hack_script.md` |
| **Round 1 follow-ups**: Gen 6 Exp. Share (`include/config/item.h`: `I_EXP_SHARE_ITEM` GEN_6, `I_EXP_SHARE_FLAG` = `FLAG_EXP_SHARE_ON`; Mr. Stone gives it with the PokéNav, `RustboroCity_DevonCorp_3F_EventScript_DraconidGiveExpShare`, D-185) | `include/config/item.h`, `data/scripts/draconid/act2.pory`, `data/maps/RustboroCity_DevonCorp_3F/scripts.inc` |
| Maxie's PokéNav calls: `MAXIE_CALL_*` + `MAXIE_CALL_STEPS` (`include/constants/draconid.h`), `Draconid_ShouldDoMaxieCall` (step hook in `TryStartStepCountScript`), specialvar `Draconid_GetDueMaxieCall`, `Draconid_EventScript_MaxieCall` + 10 call texts; Mr. Briney's boat plays Maxie's first call instead of Norman's and no longer registers Norman (D-186) | `src/draconid.c`, `include/draconid.h`, `src/field_control_avatar.c`, `data/specials.inc`, `include/event_scripts.h`, `data/scripts/draconid/maxie_calls.pory`, `data/maps/Route104/scripts.inc` |
| Brendan's Rustboro team: Poochyena, Taillow, Slakoth, Treecko (D-187); `build_segments.py` places the round 1 story fights and variants (`EGGS`, `STARTERS`, `MAX_ID`), `check_party.py` knows Nerine/Zinnia and partner Megas | `src/data/trainers.party`, `tools/hack/trainers/build_segments.py`, `tools/hack/trainers/check_party.py`, `tools/hack/trainers/segments.json` |
| Tests: `maxie_calls.play` (due / skipped / none after the turn); `act2.play` checks the Exp. Share and rides Mr. Briney's boat for Maxie's first call | `tools/hack/emu/tests/` |
| Elite Four post-game rematch: `TRAINER_SIDNEY/_PHOEBE/_GLACIA/_DRAKE_REMATCH` (ids 664, 666, 10, 21 – were `TRAINER_DRACONID_SPARE_1/2` and the unused Aqua grunts of Petalburg Woods and the museum) with the ORAS post-game teams (Lv 70–75, Megas); `Draconid_ResolveVariantTrainer` loads them instead of the first battle once `FLAG_SYS_GAME_CLEAR` is set (`sPostgameRematches`); `elite_four.play` (in the matrix) (D-174) | `include/constants/opponents.h`, `src/data/trainers.party`, `src/draconid.c`, `tools/hack/trainers/build_segments.py`, `tools/hack/emu/tests/elite_four.play` |
