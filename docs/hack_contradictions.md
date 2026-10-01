# Draconid Emerald – base-Emerald contradictions (scrub list)

Feedback 1.46 (follow-up 14): "make sure to scrub any contradictions that are in the game from base Emerald with
the updated story". This is the list of leftover base-Emerald content that contradicted the v2 story
([hack_story.md](hack_story.md), [hack_outline.md](hack_outline.md)): the player is a Draconid dragon tamer from
Draconid Village with no Mom, no Dad and no move to Littleroot; Norman is May's father; Brendan is Birch's son;
neither rival is the player's neighbour; from Petalburg Woods to the Sootopolis turn the player wears the TEAM
MAGMA uniform. The rules applied are decisions D-253 – D-255 in [hack_decisions.md](hack_decisions.md); the
fixed map lines are also in [hack_script.md](hack_script.md) (tagged labels, `contradictions.pory`) and
[reputation_dialogue.md](reputation_dialogue.md) (the new uniform branches); `tools/hack/emu/tests/contradictions.play`
shows a few of them in the ROM. Items that came from the round's story audit are marked "story audit #N".

How it was searched: every text label of `data/maps/*/scripts.inc`, `data/text/*.inc`, `data/scripts/*.inc`,
`data/event_scripts.s`, `src/strings.c`, `src/tv.c` and the PokéNav data was scanned for DAD / MOM / father /
mother / moved / MOVING / truck / neighbor / LITTLEROOT as a home / NORMAN / "LEADER's kid" / `{RIVAL}` / MAGMA
and gang words, and each hit was followed to the script that shows it, to check whether the game can still
reach it in the v2 flow (hide flags, state vars and redirected object scripts included).

Status: **fixed** · **left** (in a file another agent owns right now – passed on, with a suggested fix) ·
**unreachable** (a retired vanilla scene or text; left as it is, D-253) · **fine** (checked, not a contradiction).

## The player's family and home

| File | Label | What was wrong | Status |
|---|---|---|---|
| `data/event_scripts.s` | `EventScript_AfterWhiteOutMomHeal` (`gText_HadQuiteAnExperienceTakeRest`, `gText_MomExplainHPGetPotions`) | Vanilla's whiteout at home: "MOM: {PLAYER}! Welcome home… Make me proud, honey!" (story audit #2) | **fixed** (a guard): it jumps to `Draconid_EventScript_AfterWhiteOutHomeHeal` (`contradictions.pory`), where the old woman who gave the Running Shoes speaks, text only. Today the scene doesn't run at all: the Gen 4 whiteout cutscene (`OW_WHITEOUT_CUTSCENE`) needs a rest point with a healer NPC, and the village's (`HEAL_LOCATION_DRACONID_VILLAGE*`) have none, so whiting out there wakes the player in bed, healed, without a word (checked in the emulator); the guard keeps MOM out if a healer is ever added |
| `src/tv.c` | `GetMomOrDadStringForTVMessage` (`gText_MomOrDadMightLikeThisProgram`) | Every TV without a show said "MOM might like this program." / "DAD might like this program." | **fixed**: "The ELDER" / "ASTER might like this program." (D-254) |
| `src/strings.c` | `gText_DadsAdvice` | Using an item in the wrong place: "DAD's advice… {PLAYER}, there's a time and place for everything!" | **fixed**: "The ELDER's words…" (D-254) |
| `data/text/tv.inc` | `TrendWatcher_Text_MaleTaughtMePhrase`, `…FemaleTaughtMePhrase` | The Trend Watcher show: "{STR_VAR_3} from LITTLEROOT taught me". | **fixed**: "from DRACONID VILLAGE" |
| `data/maps/LittlerootTown_MaysHouse_1F` | `RivalsHouse_1F_Text_DoYouHavePokemon` (both rivals' little brothers) | "Hi, neighbor!" – the player never lived next door. | **fixed**: "Hi!" |
| `data/text/match_call.inc` | `MatchCall_Text_MrStone5` | Mr. Stone's call: "I heard… that you're NORMAN's child!" | **fixed**: he heard the player comes from the DRACONID clan, the dragon tamers of the mountains |
| `data/text/match_call.inc` | `MatchCall_Text_MrStone6` | "You battled your own father and defeated him?" | **fixed**: "You battled NORMAN, the GYM LEADER of PETALBURG" |
| `data/maps/LittlerootTown` `LittlerootTown_BrendansHouse_*` `LittlerootTown_MaysHouse_*` | `LittlerootTown_Text_OurNewHomeLetsGoInside`, `…_WearTheseRunningShoes`, `…_ComeHomeIfAnythingHappens`, `PlayersHouse_1F_Text_*` / `PlayersHouse_2F_Text_*` (Mom, Dad, the move, the clock, the Petalburg Gym TV report, the Amulet Coin, the SS Ticket), `RivalsHouse_1F/2F_Text_*WhoAreYou` ("So your move was today", "Moved in next door"), `…_OhYoureTheNewNeighbor`, `…_LikeChildLikeFather`, `…_ShouldGoHomeEverySoOften` | The vanilla truck intro, Mom and Dad at home, the "new neighbour" scenes. | **unreachable**: `new_game.pory` sets `VAR_LITTLEROOT_INTRO_STATE` 7, `VAR_LITTLEROOT_TOWN_STATE` 4, `VAR_LITTLEROOT_RIVAL_STATE` 3 and hides the Moms, Vigoroths, trucks and Poké Balls; the rivals' moms and bedrooms point at `act1.pory` / `rivals2.pory` scripts; the SS Ticket plays in the village (D-112) |
| `data/maps/InsideOfTruck` | all | The moving truck. | **unreachable** (no truck, D-102) |
| `data/text/match_call.inc` | `MatchCall_Text_Mom1`–`3` | Mom's PokéNav calls ("Your father…"). | **unreachable**: `FLAG_ENABLE_MOM_MATCH_CALL` is only set by the hidden Mom |
| `data/maps/LittlerootTown_ProfessorBirchsLab` | `…_Text_LikeYouToHavePokemon`, `…_HeardYouBeatRivalTakePokedex`, `…_BirchRivalGoneHome`, `…_ExplainPokedex` | "I've heard so much about you from your father", "your father's blood", "get some rest at home". | **unreachable**: the lab's `DraconidWelcome` replaced the starter and Pokédex scenes (`VAR_BIRCH_LAB_STATE` 5) |
| `data/maps/OldaleTown` | `OldaleTown_Text_MayLetsGoBack`, `…_BrendanLetsGoBack` | "Let's hurry home!", "my dad's LAB". | **unreachable**: no Oldale rival scene (`VAR_OLDALE_RIVAL_STATE` never 1) |
| `data/maps/LittlerootTown_BrendansHouse_2F` | `PlayersHouse_2F_Text_Notebook` (the rivals' bedrooms) | "{PLAYER} flipped open the notebook." in someone else's room. | **fine**: vanilla shows the same notebook in the rival's room |
| – | Mom's Amulet Coin (`PlayersHouse_1F_EventScript_CheckGiveAmuletCoin`, `FLAG_RECEIVED_AMULET_COIN`) | With Mom gone, the Amulet Coin can't be obtained any more (no other source in Emerald). Not a story contradiction, and no progression depends on it. | **left** – suggestion: a Draconid villager or the battle-item counter hands it out after the Balance Badge |

## Norman is May's father

| File | Label | What was wrong | Status |
|---|---|---|---|
| `data/maps/PetalburgCity_Gym` | `PetalburgCity_Gym_Text_GymGuidePostVictory` | "You've overcome even your own father!" | **fixed**: "…even NORMAN himself!" |
| `data/maps/PetalburgCity_Gym` | `…_GeorgePostBattle` | "…no less from our LEADER's kid." | **fixed**: "…from someone with four GYM BADGES." |
| `data/maps/PetalburgCity_Gym` | `…_BerkeIntro`, `…_BerkePostBattle`, `…_BerkePostBadge` | "…because you're our LEADER's kid", "Your father really is strong", "Since your dad became the LEADER". | **fixed**: four BADGES / NORMAN named |
| `data/maps/PetalburgCity_Gym` | `…_JodyIntro`, `…_JodyPostBattle` | "Even if you happen to be the LEADER's kid!", "your father's style… your father, is waiting!" | **fixed**: "No matter who you happen to be!", "our LEADER's style… NORMAN, is waiting!" |
| `data/text/berries.inc` | `PetalburgCity_Gym_Text_GiveEnigmaBerry` | "DAD: Hi, {PLAYER}!" (the e-Reader Enigma Berry). | **fixed**: "NORMAN:" (practically unreachable, but free to fix) |
| `data/maps/LilycoveCity_PokemonTrainerFanClub` | `…_YouveSurpassedYourFather`, `…_YourFatherNeverGaveUpSoKeepOnBattling`, `…_LongWayToGoComparedToNorman` | The fan who admires Norman calls him the player's father. | **fixed**: NORMAN by name |
| `data/maps/Route110_TrickHousePuzzle5` | `Route110_TrickHousePuzzle5_Text_Mechadoll2Quiz1` | "Which of these POKéMON did WALLY borrow from your father?" | **fixed**: "…from NORMAN?" |
| `data/text/match_call.inc` | `MatchCall_Text_Norman1`–`5`, `…_Norman_*` ("DAD:"), `data/maps/Route105` `Route104_Text_RegisteredDadInPokenav` | Norman's PokéNav calls as the player's father. | **unreachable**: Norman is never registered (Mr. Briney's boat plays Maxie's call instead, D-186); the registration text isn't referenced |
| `data/maps/PetalburgCity_Gym` | Norman's own lines (`…_Text_Dad*`, `…_NormanIntro` …) | Norman as the player's dad. | **fine**: already reworked (Act 1 / Act 4, D-100, D-116) |
| `data/maps/LavaridgeTown_Gym_1F` | `LavaridgeTown_Gym_1F_Text_FlanneryPostBattle` | "You battle like NORMAN" (a hint at the family in vanilla). | **fine**: a comparison, true either way |
| `data/maps/LilycoveCity_PokemonTrainerFanClub` | `…_YouAndNormanAreDifferent` | Compares the player to NORMAN. | **fine** |
| `data/maps/PetalburgCity_House2` | `…_NormanBecameGymLeader` | "He called his family over from somewhere far away." | **fine**: May's family came from JOHTO |
| `data/maps/LavaridgeTown` | `LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad` | Brendan: "your dad looks like he really is tough." | **unreachable** (the Lavaridge rival is always May) |

## Brendan, May and `{RIVAL}`

| File | Label | What was wrong | Status |
|---|---|---|---|
| `data/maps/LittlerootTown_ProfessorBirchsLab` | `…_Text_OtherRegionsUpgradeToNational`, `…_Text_PokedexUpgradedToNational` | The post-game scene: "{PLAYER} and {RIVAL}" (`{RIVAL}` is BRENDAN, but MAY stands there) and an "upgrade to the NATIONAL Mode" of a Pokédex that is National from the start (D-196; the old `TODO(dialogue)`). | **fixed**: "{PLAYER} and MAY", Birch adds his new data on the faraway POKéMON; "{PLAYER}'s POKéDEX was updated with PROF. BIRCH's new data!" |
| several | comments "the rival here is May (Birch's daughter)" (`rival_graphics.inc`, `OldaleTown`, `LittlerootTown_MaysHouse_2F`, the lab, `src/credits.c`) | Stale v1 notes (D-031). | **fixed**: "(Norman's daughter, D-100)" |
| `data/maps/Route110` | `Route110_Text_ImagineSeeingYouHere`, `…_KeepAnEyeOutForRival` | Birch: "where might my {RIVAL} be?" | **fine**: `{RIVAL}` = BRENDAN, his son; Birch knows the mission (D-244a), so no uniform reaction is needed |
| `data/maps/LittlerootTown_ProfessorBirchsLab` | `…_BirchEnjoysRivalsHelpToo` | The aide: "The PROF enjoys {RIVAL}'s help". | **fine** (Brendan) |
| `data/maps/Route103`, `Route119`, `LilycoveCity` | `Route103_Text_May/Brendan*` ("my dad gave you a POKéMON"), `Route119_Text_MayExplainFly` ("FLY home… your mom's worried"), `LilycoveCity_Text_*GoingBackToLittleroot` | Vanilla rival scenes. | **unreachable**: replaced by `birch_intro.pory`, Brendan's Route 119 scene and `act4.pory`'s rivals |
| `src/field_specials.c`, `data/maps/MossdeepCity_SpaceCenter_2F` | `ShouldDoRivalRayquazaCall` → `MossdeepCity_SpaceCenter_2F_EventScript_RivalRayquazaCall` (`MatchCall_Text_MayRayquazaCall`, `…_BrendanRayquazaCall`) | 250 outdoor steps after the Space Center raid, MAY (male player) or BRENDAN (female player) phone as friends about a "giant green POKéMON" over PACIFIDLOG – a rival picked by the player's gender, friendly in the uniform era, and RAYQUAZA only rises at the Sootopolis turn (story audit #20). | **fixed**: `ShouldDoRivalRayquazaCall` returns FALSE (the flag it read, `FLAG_DEFEATED_MAGMA_SPACE_CENTER`, is only used by this call) |
| `src/pokenav_match_call_data.c` | `gText_MatchCallMay_Intro2` (May's check page) | "My POKéMON and I help my father's research." Her father is NORMAN. | **left** (file owned by another agent) – suggested: "PROF. BIRCH's research." |

## Wally and his family

| File | Label | What was wrong | Status |
|---|---|---|---|
| `data/maps/PetalburgCity_WallysHouse` | `PetalburgCity_WallysHouse_Text_PleaseExcuseUs` (the Surf gift) | Right after Norman's badge (always in uniform) Wally's father thanks the player for being "such a great friend" – while WALLY battles the player as TEAM MAGMA (D-236). | **fixed**: he sees the uniform, says WALLY is angry, and gives Surf for what the player did that day |
| `data/maps/VerdanturfTown_WandasHouse` | `VerdanturfTown_WandasHouse_Text_StrongerSpeech`, `…Short` | After the Mauville battle (uniform era) WALLY is friendly: "Please watch me, {PLAYER}." | **fixed**: hostile in his D-236 voice ("Strong enough to stop you, and the rest of TEAM MAGMA.") |
| `data/maps/PetalburgCity_Gym` | `…_WallyThankYouBye`, `…_PleaseComeWithMe` | – | **fine** (before the uniform; Wally's father fetching the player) |

## The uniform era: townsfolk and grunts

| File | Label | What was wrong | Status |
|---|---|---|---|
| `data/maps/PetalburgCity_Gym` | `PetalburgCity_Gym_EventScript_GymGuide` | The only Gym Guide without uniform lines (D-117 left Petalburg to the story): "Hey, how's it going, CHAMPION-bound {PLAYER}?" to a MAGMA grunt. | **fixed**: `PetalburgCity_Gym_EventScript_DraconidRepGymGuide` (uniform advice, uniform / revealed congratulations) |
| `data/maps/FallarborTown_CozmosHouse` | `FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls` | Cozmo's wife tells a MAGMA grunt that her husband left with TEAM MAGMA, as if to a stranger (only shown before Mt. Chimney: always in uniform). | **fixed**: she sees the uniform and begs the player to bring him home |
| `data/maps/FallarborTown_CozmosHouse` | `FallarborTown_CozmosHouse_EventScript_NoticeMeteorite`, `…_GaveMeteorite` | A MAGMA grunt – the one he saw beside MAXIE at the falls – brings back the METEORITE MAGMA took, and Cozmo trades for it without a word (story audit #12). | **fixed**: in the uniform his own question (`…_DraconidRepNoticeMeteoriteUniform`: "Y-you! You're the one from the falls! … I won't tell a soul where it came from."), the vanilla TM trade after it; after the reveal "So THAT's why you gave it back!" (`…_DraconidRepCozmoRevealed`) |
| `data/maps/RustboroCity_CuttersHouse`, `GraniteCave_1F`, `MauvilleCity_House1`, `MauvilleCity_BikeShop` | `…_Text_YouCanPutThisHMToGoodUse`, `…_Text_GetsDarkAheadHereYouGo`, `…_Text_ImRockSmashDudeTakeThis`, `MauvilleCity_BikeShop_Text_RydelGreeting` | The Cutter, the Granite Cave hiker, the Rock Smash Dude and Rydel hand a MAGMA grunt an HM or a bike as if to any kid (story audit #10). | **fixed**: in the uniform the three HM givers say their own version of the speech and rejoin the vanilla gift (`…_DraconidRepCutterUniform`, `…_DraconidRepHikerUniform`, `…_DraconidRepRockSmashDudeUniform` → `…_DraconidGive*`), Rydel adds one line after his greeting (`…_DraconidRepRydelUniform`); every gift and flag is vanilla's (`contradictions.pory`) |
| `data/maps/RustboroCity_DevonCorp_3F` | `RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp` | Mr. Stone warns the player in the MAGMA uniform about "sinister criminals--MAGMA and AQUA" (story audit #9, the logic branch's). | **left** (map owned by another agent) – suggested: he notices the uniform ("…though I see you wear their red. Hm! I judge people by their deeds.") |
| `data/maps/MossdeepCity_SpaceCenter_1F/2F` | `…_Text_AquaShouldBeatMagma`, `…_MagmaWantsToSpoilMyDream`, `…_WhyWouldMagmaStealRocketFuel`, `…_MagmaCantGetAwayWithThis`, `…_DoesMagmaWantToGoToSpace` | While the raid is on, the visitors talk about TEAM MAGMA to the uniformed player as if to an outsider. | **left** (maps owned by another agent) – suggested: uniform lines (fear, "you're one of them") |
| `data/maps/MossdeepCity` | `MossdeepCity_Text_MossdeepTargetedByMagma` | "If you want to know what they're up to, go visit the SPACE CENTER." | **fine**: the sailor's object runs his reputation script (D-117); this line is pre-uniform only |
| `data/maps/MagmaHideout_*` | the grunts' untagged defeat / post-battle lines | – | **fine**: they read as rank tests ("You're a fiery battler", "Listen to me. TEAM MAGMA is right!"; D-103, D-133) |
| `data/maps/MtChimney`, `Route112` | the summit grunts ("We're TEAM MAGMA! They're TEAM AQUA!"), the Route 112 grunt | – | **fine**: comrades talking |
| `data/maps/MtChimney` | `MtChimney_Text_MaxieIntro`, `…_TabithaIntro`, `…_ArchieThankYou` … | The vanilla fight against Maxie. | **unreachable** (`MtChimney_EventScript_Maxie` goes to Act 3's scene) |
| `data/maps/AquaHideout_*`, `SeafloorCavern_*`, `MtPyre_Summit` | Aqua grunts, Matt, Shelly, Archie ("pesky meddler", "Are you a TEAM MAGMA grunt?", "not a TEAM AQUA member") | – | **fine**: the player fights Aqua for real (D-103) |
| `data/maps/SeafloorCavern_Entrance` | `…_Text_HearMagmaNearMossdeep`, `…Short` | "Speaking of TEAM MAGMA, I hear they were spotted near MOSSDEEP" – to the grunt who was on that raid (story audit #26). | **fixed** (retexted: "You're the MAGMA brat from the SPACE CENTER!"), although the grunt can't be met in normal play: Steven's HM Dive gift hides him, and Dive is the only way down |
| `data/maps/Route119` | `Route119_Text_StayAwayFromWeatherInstitute`, `…_DontGoNearWeatherInstitute` | The AQUA lookouts on the bridge warn the MAGMA grunt off "It's not safe" as if to a passer-by (story audit #26). | **fixed**: "…A MAGMA grunt?! Beat it! This INSTITUTE is AQUA business!" (only shown while AQUA holds the Institute) |
| `data/text/match_call.inc` | `MatchCall_Text_Scott4`, `MatchCall_Text_Steven*` | – | **fine**: nothing about the player's side |

## Quizzes and records

| File | Label | What was wrong | Status |
|---|---|---|---|
| `data/maps/Route110_TrickHousePuzzle5` | `Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz2` | "Which of these POKéMON was chasing PROF. BIRCH?" – the right answer was ZIGZAGOON; the v2 rescue is a POOCHYENA (story audit #8). | **fixed**: POOCHYENA is the right answer; round 2 (D-400): nothing chases Birch any more, so the quiz asks "Which of these POKéMON fell with the star on ROUTE 101?" and LUNATONE (the first entry, was POOCHYENA) is right |
| `data/maps/Route110_TrickHousePuzzle5` | `Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz3` | "Which of these POKéMON did TEAM AQUA use in PETALBURG FOREST?" – the right answer was POOCHYENA; the Aqua grunt there is NERINE, whose cover team leads with CARVANHA (story audit #8). | **fixed**: CARVANHA is the right answer |
| `data/maps/Route110_TrickHousePuzzle5` | `…_Mechadoll1Quiz1` | "One of these POKéMON is not found on ROUTE 110" | **fine**: TAILLOW still isn't there after the Gen 4–9 additions |

## Left for the owners of other files

| Where | What | Suggested fix |
|---|---|---|
| `data/maps/SootopolisCity` `SootopolisCity_EventScript_MaxieArchieLeave` → `data/maps/MtPyre_Summit` `…_ArchieMaxieReturnOrbs`, `MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs` | After the Sootopolis aftermath Maxie and Archie return the ORBS at Mt. Pyre, and the old lady says "Perhaps they are not so evil after all" – but v2 has Maxie swear revenge (outline 41, 45) and use the ORBS for Primal Groudon and Kyogre in the finale (outline 53–55; story audit #27). | The Maxie-revenge / Act 7 owner decides: skip the return (don't set `VAR_MT_PYRE_STATE` 2) or keep it and have the ORBS stolen back later |
| `data/maps/MossdeepCity_StevensHouse` `MossdeepCity_StevensHouse_Text_LetterFromSteven` | Post-game: "I've decided to do a little soul-searching and train on the road. I don't plan to return home for some time." – Steven is becoming the Champion (story audit #33). | For the Champion-Steven work |
| `docs/playtest_guide.md` | v1 text throughout: "May (Birch's daughter)", "Aster, the Elder's granddaughter", "Team Magma disguise from the Route 112 cable car". | For the playtest-guide task (final phase) |
| `src/pokenav_match_call_data.c`, `RustboroCity_DevonCorp_3F`, `MossdeepCity_SpaceCenter_1F/2F` | See the tables above. | – |

The family / home scan found nothing to fix in the Draconid scripts themselves (`act1.pory` – `act7.pory`,
`rivals2.pory`, `rival_calls.pory`, `maxie_calls.pory`, the village maps); `magma_revenge.pory` was not in this
tree yet.
