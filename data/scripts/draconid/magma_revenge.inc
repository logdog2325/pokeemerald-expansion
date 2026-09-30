SootopolisCity_EventScript_DraconidRevengeOnTransition::
	setflag FLAG_TEMP_12
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_EventScript_DraconidRevengeOnTransition_3
	return

SootopolisCity_EventScript_DraconidRevengeOnTransition_1:
	setvar VAR_TEMP_3, 1
	return

SootopolisCity_EventScript_DraconidRevengeOnTransition_2:
	goto_if_unset FLAG_IS_CHAMPION, SootopolisCity_EventScript_DraconidRevengeOnTransition_6
	return

SootopolisCity_EventScript_DraconidRevengeOnTransition_3:
	compare VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	goto_if_ge SootopolisCity_EventScript_DraconidRevengeOnTransition_2
	return

SootopolisCity_EventScript_DraconidRevengeOnTransition_6:
	checktrainerflag TRAINER_GRUNT_SOOTOPOLIS_REVENGE_2
	goto_if 0, SootopolisCity_EventScript_DraconidRevengeOnTransition_1
	return


SootopolisCity_EventScript_DraconidRevengeAmbush::
	lockall
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidRevengeAmbush_Text_0
	closemessage
	compare VAR_TEMP_0, 30
	goto_if_eq SootopolisCity_EventScript_DraconidRevengeAmbush_2
	compare VAR_TEMP_0, 32
	goto_if_eq SootopolisCity_EventScript_DraconidRevengeAmbush_3
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
SootopolisCity_EventScript_DraconidRevengeAmbush_1:
	waitmovement 0
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	opendoor 31, 32
	waitdooranim
	clearflag FLAG_TEMP_12
	addobject LOCALID_SOOTOPOLIS_REVENGE_GRUNT_1
	applymovement LOCALID_SOOTOPOLIS_REVENGE_GRUNT_1, SootopolisCity_Movement_DraconidRevengeGrunt1Out
	waitmovement 0
	addobject LOCALID_SOOTOPOLIS_REVENGE_GRUNT_2
	applymovement LOCALID_SOOTOPOLIS_REVENGE_GRUNT_2, SootopolisCity_Movement_DraconidRevengeGrunt2Out
	waitmovement 0
	closedoor 31, 32
	waitdooranim
	msgbox SootopolisCity_EventScript_DraconidRevengeAmbush_Text_1
	msgbox SootopolisCity_EventScript_DraconidRevengeAmbush_Text_2
	closemessage
	cleartrainerflag TRAINER_GRUNT_SOOTOPOLIS_REVENGE_1
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_eq SootopolisCity_EventScript_DraconidRevengeAmbush_8
	trainerbattle_no_intro TRAINER_GRUNT_SOOTOPOLIS_REVENGE_1, SootopolisCity_Text_DraconidRevengeGrunt1Defeat
	trainerbattle_no_intro TRAINER_GRUNT_SOOTOPOLIS_REVENGE_2, SootopolisCity_Text_DraconidRevengeGrunt2Defeat
SootopolisCity_EventScript_DraconidRevengeAmbush_7:
	msgbox SootopolisCity_EventScript_DraconidRevengeAmbush_Text_3
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SOOTOPOLIS_REVENGE_GRUNT_1
	removeobject LOCALID_SOOTOPOLIS_REVENGE_GRUNT_2
	setvar VAR_TEMP_3, 0
	fadescreenswapbuffers FADE_FROM_BLACK
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

SootopolisCity_EventScript_DraconidRevengeAmbush_2:
	applymovement LOCALID_PLAYER, SootopolisCity_Movement_DraconidRevengeFromWest
	goto SootopolisCity_EventScript_DraconidRevengeAmbush_1

SootopolisCity_EventScript_DraconidRevengeAmbush_3:
	applymovement LOCALID_PLAYER, SootopolisCity_Movement_DraconidRevengeFromEast
	goto SootopolisCity_EventScript_DraconidRevengeAmbush_1

SootopolisCity_EventScript_DraconidRevengeAmbush_8:
	trainerbattle_two_trainers_no_intro TRAINER_GRUNT_SOOTOPOLIS_REVENGE_1, SootopolisCity_Text_DraconidRevengeGrunt1Defeat, TRAINER_GRUNT_SOOTOPOLIS_REVENGE_2, SootopolisCity_Text_DraconidRevengeGrunt2Defeat
	goto SootopolisCity_EventScript_DraconidRevengeAmbush_7


SootopolisCity_Movement_DraconidRevengeFromWest:
	walk_down
	walk_right
	face_up
	step_end

SootopolisCity_Movement_DraconidRevengeFromEast:
	walk_down
	walk_left
	face_up
	step_end

SootopolisCity_Movement_DraconidRevengeGrunt1Out:
	walk_down
	walk_left
	face_down
	step_end

SootopolisCity_Movement_DraconidRevengeGrunt2Out:
	walk_down
	walk_right
	face_down
	step_end

EverGrandeCity_EventScript_DraconidRevengeOnTransition::
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	compare VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	goto_if_lt EverGrandeCity_EventScript_DraconidRevengeOnTransition_2
	goto_if_set FLAG_IS_CHAMPION, EverGrandeCity_EventScript_DraconidRevengeOnTransition_2
	checktrainerflag TRAINER_GRUNT_EVER_GRANDE_SHORE_2
	goto_if 1, EverGrandeCity_EventScript_DraconidRevengeOnTransition_7
	setvar VAR_TEMP_2, 1
EverGrandeCity_EventScript_DraconidRevengeOnTransition_6:
	checktrainerflag TRAINER_GRUNT_EVER_GRANDE_CENTER
	goto_if 1, EverGrandeCity_EventScript_DraconidRevengeOnTransition_11
EverGrandeCity_EventScript_DraconidRevengeOnTransition_10:
	checktrainerflag TRAINER_SHELLY_EVER_GRANDE
	goto_if 0, EverGrandeCity_EventScript_DraconidRevengeOnTransition_14
EverGrandeCity_EventScript_DraconidRevengeOnTransition_13:
	checktrainerflag TRAINER_MAXIE_VICTORY_ROAD
	goto_if 0, EverGrandeCity_EventScript_DraconidRevengeOnTransition_17
EverGrandeCity_EventScript_DraconidRevengeOnTransition_16:
	checktrainerflag TRAINER_GRUNT_VICTORY_ROAD_EXIT
	goto_if 1, EverGrandeCity_EventScript_DraconidRevengeOnTransition_20
	setvar VAR_TEMP_5, 1
EverGrandeCity_EventScript_DraconidRevengeOnTransition_19:
	checktrainerflag TRAINER_GRUNT_POKEMON_LEAGUE_2
	goto_if 1, EverGrandeCity_EventScript_DraconidRevengeOnTransition_23
	setvar VAR_TEMP_6, 1
	return

EverGrandeCity_EventScript_DraconidRevengeOnTransition_2:
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_16
	setflag FLAG_TEMP_17
	return

EverGrandeCity_EventScript_DraconidRevengeOnTransition_7:
	setflag FLAG_TEMP_11
	goto EverGrandeCity_EventScript_DraconidRevengeOnTransition_6

EverGrandeCity_EventScript_DraconidRevengeOnTransition_11:
	setflag FLAG_TEMP_12
	goto EverGrandeCity_EventScript_DraconidRevengeOnTransition_10

EverGrandeCity_EventScript_DraconidRevengeOnTransition_14:
	setvar VAR_TEMP_3, 1
	goto EverGrandeCity_EventScript_DraconidRevengeOnTransition_13

EverGrandeCity_EventScript_DraconidRevengeOnTransition_17:
	setvar VAR_TEMP_4, 1
	goto EverGrandeCity_EventScript_DraconidRevengeOnTransition_16

EverGrandeCity_EventScript_DraconidRevengeOnTransition_20:
	setflag FLAG_TEMP_16
	goto EverGrandeCity_EventScript_DraconidRevengeOnTransition_19

EverGrandeCity_EventScript_DraconidRevengeOnTransition_23:
	setflag FLAG_TEMP_17
	return


EverGrandeCity_EventScript_DraconidShoreAmbush::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_EVER_GRANDE_SHORE_GRUNT_1, Common_Movement_ExclamationMark
	applymovement LOCALID_EVER_GRANDE_SHORE_GRUNT_2, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidShoreAmbush_Text_0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidShoreAmbush_Text_1
	closemessage
	cleartrainerflag TRAINER_GRUNT_EVER_GRANDE_SHORE_1
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_eq EverGrandeCity_EventScript_DraconidShoreAmbush_2
	trainerbattle_no_intro TRAINER_GRUNT_EVER_GRANDE_SHORE_1, EverGrandeCity_Text_DraconidShoreGrunt1Defeat
	trainerbattle_no_intro TRAINER_GRUNT_EVER_GRANDE_SHORE_2, EverGrandeCity_Text_DraconidShoreGrunt2Defeat
EverGrandeCity_EventScript_DraconidShoreAmbush_1:
	msgbox EverGrandeCity_EventScript_DraconidShoreAmbush_Text_2
	closemessage
	applymovement LOCALID_EVER_GRANDE_SHORE_GRUNT_1, EverGrandeCity_Movement_DraconidShoreGrunt1Flees
	applymovement LOCALID_EVER_GRANDE_SHORE_GRUNT_2, EverGrandeCity_Movement_DraconidShoreGrunt2Flees
	waitmovement 0
	removeobject LOCALID_EVER_GRANDE_SHORE_GRUNT_1
	removeobject LOCALID_EVER_GRANDE_SHORE_GRUNT_2
	setvar VAR_TEMP_2, 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

EverGrandeCity_EventScript_DraconidShoreAmbush_2:
	trainerbattle_two_trainers_no_intro TRAINER_GRUNT_EVER_GRANDE_SHORE_1, EverGrandeCity_Text_DraconidShoreGrunt1Defeat, TRAINER_GRUNT_EVER_GRANDE_SHORE_2, EverGrandeCity_Text_DraconidShoreGrunt2Defeat
	goto EverGrandeCity_EventScript_DraconidShoreAmbush_1


EverGrandeCity_Movement_DraconidShoreGrunt1Flees:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

EverGrandeCity_Movement_DraconidShoreGrunt2Flees:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

EverGrandeCity_EventScript_DraconidCenterGrunt::
	trainerbattle_single TRAINER_GRUNT_EVER_GRANDE_CENTER, EverGrandeCity_Text_DraconidCenterGruntIntro, EverGrandeCity_Text_DraconidCenterGruntDefeat, EverGrandeCity_EventScript_DraconidCenterGruntLeaves
	releaseall
	return


EverGrandeCity_EventScript_DraconidCenterGruntLeaves::
	msgbox EverGrandeCity_EventScript_DraconidCenterGruntLeaves_Text_0
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_EVER_GRANDE_CENTER_GRUNT
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	return


EverGrandeCity_EventScript_DraconidAquaGauntlet::
	lockall
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 20
	goto_if_eq EverGrandeCity_EventScript_DraconidAquaGauntlet_2
EverGrandeCity_EventScript_DraconidAquaGauntlet_1:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	cleartrainerflag TRAINER_GRUNT_AQUA_GAUNTLET_1
	cleartrainerflag TRAINER_GRUNT_AQUA_GAUNTLET_2
	cleartrainerflag TRAINER_GRUNT_AQUA_GAUNTLET_3
	cleartrainerflag TRAINER_GRUNT_AQUA_GAUNTLET_4
	cleartrainerflag TRAINER_GRUNT_AQUA_GAUNTLET_5
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_0
	closemessage
	clearflag FLAG_TEMP_13
	addobject LOCALID_EVER_GRANDE_AQUA_GRUNT_1
	addobject LOCALID_EVER_GRANDE_AQUA_GRUNT_2
	addobject LOCALID_EVER_GRANDE_AQUA_GRUNT_3
	addobject LOCALID_EVER_GRANDE_AQUA_GRUNT_4
	addobject LOCALID_EVER_GRANDE_AQUA_GRUNT_5
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_EVER_GRANDE_AQUA_GRUNT_1, EverGrandeCity_Movement_DraconidAquaStepRight
	applymovement LOCALID_EVER_GRANDE_AQUA_GRUNT_2, EverGrandeCity_Movement_DraconidAquaStepLeft
	applymovement LOCALID_EVER_GRANDE_AQUA_GRUNT_3, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_EVER_GRANDE_AQUA_GRUNT_4, EverGrandeCity_Movement_DraconidAquaStepDown
	applymovement LOCALID_EVER_GRANDE_AQUA_GRUNT_5, EverGrandeCity_Movement_DraconidAquaStepDown
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_1
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_2
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_3
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_AQUA_GAUNTLET_1, EverGrandeCity_Text_DraconidAquaGrunt1Defeat
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_4
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_AQUA_GAUNTLET_2, EverGrandeCity_Text_DraconidAquaGrunt2Defeat
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_5
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_AQUA_GAUNTLET_3, EverGrandeCity_Text_DraconidAquaGrunt3Defeat
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_6
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_AQUA_GAUNTLET_4, EverGrandeCity_Text_DraconidAquaGrunt4Defeat
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_7
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_AQUA_GAUNTLET_5, EverGrandeCity_Text_DraconidAquaGrunt5Defeat
	clearflag FLAG_TEMP_14
	addobject LOCALID_EVER_GRANDE_SHELLY
	applymovement LOCALID_EVER_GRANDE_SHELLY, EverGrandeCity_Movement_DraconidShellyWalksDown
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_8
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_9
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_10
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_11
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_12
	closemessage
	trainerbattle_no_intro TRAINER_SHELLY_EVER_GRANDE, EverGrandeCity_Text_DraconidShellyDefeat
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_13
	msgbox EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_14
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_EVER_GRANDE_AQUA_GRUNT_1
	removeobject LOCALID_EVER_GRANDE_AQUA_GRUNT_2
	removeobject LOCALID_EVER_GRANDE_AQUA_GRUNT_3
	removeobject LOCALID_EVER_GRANDE_AQUA_GRUNT_4
	removeobject LOCALID_EVER_GRANDE_AQUA_GRUNT_5
	removeobject LOCALID_EVER_GRANDE_SHELLY
	setvar VAR_TEMP_3, 0
	fadescreenswapbuffers FADE_FROM_BLACK
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

EverGrandeCity_EventScript_DraconidAquaGauntlet_2:
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	waitmovement 0
	goto EverGrandeCity_EventScript_DraconidAquaGauntlet_1


EverGrandeCity_Movement_DraconidAquaStepRight:
	walk_right
	face_right
	step_end

EverGrandeCity_Movement_DraconidAquaStepLeft:
	walk_left
	walk_left
	face_left
	step_end

EverGrandeCity_Movement_DraconidAquaStepDown:
	walk_down
	face_down
	step_end

EverGrandeCity_Movement_DraconidShellyWalksDown:
	walk_down
	walk_right
	walk_down
	walk_down
	face_down
	step_end

EverGrandeCity_EventScript_DraconidMaxie::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	clearflag FLAG_TEMP_15
	addobject LOCALID_EVER_GRANDE_MAXIE
	applymovement LOCALID_EVER_GRANDE_MAXIE, Common_Movement_WalkDown
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_0
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_1
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_2
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_3
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_4
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_VICTORY_ROAD, EverGrandeCity_Text_DraconidMaxieDefeat
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_5
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_6
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_7
	msgbox EverGrandeCity_EventScript_DraconidMaxie_Text_8
	closemessage
	applymovement LOCALID_EVER_GRANDE_MAXIE, Common_Movement_WalkUp
	waitmovement 0
	removeobject LOCALID_EVER_GRANDE_MAXIE
	setvar VAR_TEMP_4, 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


EverGrandeCity_EventScript_DraconidExitGrunt::
	lockall
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_EVER_GRANDE_EXIT_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	compare VAR_TEMP_0, 25
	goto_if_eq EverGrandeCity_EventScript_DraconidExitGrunt_2
	compare VAR_TEMP_0, 27
	goto_if_eq EverGrandeCity_EventScript_DraconidExitGrunt_3
EverGrandeCity_EventScript_DraconidExitGrunt_1:
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_EVER_GRANDE_EXIT_GRUNT, Common_Movement_WalkDown
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidExitGrunt_Text_0
	msgbox EverGrandeCity_EventScript_DraconidExitGrunt_Text_1
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_VICTORY_ROAD_EXIT, EverGrandeCity_Text_DraconidExitGruntDefeat
	msgbox EverGrandeCity_EventScript_DraconidExitGrunt_Text_2
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_EVER_GRANDE_EXIT_GRUNT
	setvar VAR_TEMP_5, 0
	fadescreenswapbuffers FADE_FROM_BLACK
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

EverGrandeCity_EventScript_DraconidExitGrunt_2:
	applymovement LOCALID_PLAYER, Common_Movement_WalkRight
	goto EverGrandeCity_EventScript_DraconidExitGrunt_1

EverGrandeCity_EventScript_DraconidExitGrunt_3:
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	goto EverGrandeCity_EventScript_DraconidExitGrunt_1


EverGrandeCity_EventScript_DraconidLeagueGrunts::
	lockall
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_EVER_GRANDE_LEAGUE_GRUNT_1, Common_Movement_ExclamationMark
	applymovement LOCALID_EVER_GRANDE_LEAGUE_GRUNT_2, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_0
	closemessage
	switch VAR_TEMP_0
	case 16, EverGrandeCity_EventScript_DraconidLeagueGrunts_3
	case 17, EverGrandeCity_EventScript_DraconidLeagueGrunts_4
	case 19, EverGrandeCity_EventScript_DraconidLeagueGrunts_5
	case 20, EverGrandeCity_EventScript_DraconidLeagueGrunts_6
EverGrandeCity_EventScript_DraconidLeagueGrunts_1:
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_EVER_GRANDE_LEAGUE_GRUNT_1, Common_Movement_WalkDown
	applymovement LOCALID_EVER_GRANDE_LEAGUE_GRUNT_2, Common_Movement_WalkDown
	waitmovement 0
	msgbox EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_1
	msgbox EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_2
	closemessage
	cleartrainerflag TRAINER_GRUNT_POKEMON_LEAGUE_1
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_eq EverGrandeCity_EventScript_DraconidLeagueGrunts_8
	trainerbattle_no_intro TRAINER_GRUNT_POKEMON_LEAGUE_1, EverGrandeCity_Text_DraconidLeagueGrunt1Defeat
	trainerbattle_no_intro TRAINER_GRUNT_POKEMON_LEAGUE_2, EverGrandeCity_Text_DraconidLeagueGrunt2Defeat
EverGrandeCity_EventScript_DraconidLeagueGrunts_7:
	msgbox EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_3
	msgbox EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_4
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_EVER_GRANDE_LEAGUE_GRUNT_1
	removeobject LOCALID_EVER_GRANDE_LEAGUE_GRUNT_2
	setvar VAR_TEMP_6, 0
	fadescreenswapbuffers FADE_FROM_BLACK
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

EverGrandeCity_EventScript_DraconidLeagueGrunts_3:
	applymovement LOCALID_PLAYER, EverGrandeCity_Movement_DraconidLeagueFrom16
	goto EverGrandeCity_EventScript_DraconidLeagueGrunts_1

EverGrandeCity_EventScript_DraconidLeagueGrunts_4:
	applymovement LOCALID_PLAYER, Common_Movement_WalkRight
	goto EverGrandeCity_EventScript_DraconidLeagueGrunts_1

EverGrandeCity_EventScript_DraconidLeagueGrunts_5:
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	goto EverGrandeCity_EventScript_DraconidLeagueGrunts_1

EverGrandeCity_EventScript_DraconidLeagueGrunts_6:
	applymovement LOCALID_PLAYER, EverGrandeCity_Movement_DraconidLeagueFrom20
	goto EverGrandeCity_EventScript_DraconidLeagueGrunts_1

EverGrandeCity_EventScript_DraconidLeagueGrunts_8:
	trainerbattle_two_trainers_no_intro TRAINER_GRUNT_POKEMON_LEAGUE_1, EverGrandeCity_Text_DraconidLeagueGrunt1Defeat, TRAINER_GRUNT_POKEMON_LEAGUE_2, EverGrandeCity_Text_DraconidLeagueGrunt2Defeat
	goto EverGrandeCity_EventScript_DraconidLeagueGrunts_7


EverGrandeCity_Movement_DraconidLeagueFrom16:
	walk_right
	walk_right
	step_end

EverGrandeCity_Movement_DraconidLeagueFrom20:
	walk_left
	walk_left
	step_end

VictoryRoad_B1F_EventScript_DraconidOnTransition::
	setflag FLAG_TEMP_18
	compare VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	goto_if_ge VictoryRoad_B1F_EventScript_DraconidOnTransition_4
VictoryRoad_B1F_EventScript_DraconidOnTransition_1:
	end

VictoryRoad_B1F_EventScript_DraconidOnTransition_2:
	setvar VAR_TEMP_2, 1
	goto VictoryRoad_B1F_EventScript_DraconidOnTransition_1

VictoryRoad_B1F_EventScript_DraconidOnTransition_3:
	checktrainerflag TRAINER_COURTNEY_VICTORY_ROAD
	goto_if 0, VictoryRoad_B1F_EventScript_DraconidOnTransition_2
	goto VictoryRoad_B1F_EventScript_DraconidOnTransition_1

VictoryRoad_B1F_EventScript_DraconidOnTransition_4:
	goto_if_unset FLAG_IS_CHAMPION, VictoryRoad_B1F_EventScript_DraconidOnTransition_3
	goto VictoryRoad_B1F_EventScript_DraconidOnTransition_1


VictoryRoad_B1F_EventScript_DraconidAdmins::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_0
	closemessage
	clearflag FLAG_TEMP_18
	playse SE_EXIT
	addobject LOCALID_VICTORY_ROAD_B1F_TABITHA
	applymovement LOCALID_VICTORY_ROAD_B1F_TABITHA, VictoryRoad_B1F_Movement_DraconidTabithaDown
	waitmovement 0
	playse SE_EXIT
	addobject LOCALID_VICTORY_ROAD_B1F_COURTNEY
	applymovement LOCALID_VICTORY_ROAD_B1F_COURTNEY, VictoryRoad_B1F_Movement_DraconidCourtneyDown
	waitmovement 0
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_1
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_2
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_3
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_4
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_5
	closemessage
	cleartrainerflag TRAINER_TABITHA_VICTORY_ROAD
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_eq VictoryRoad_B1F_EventScript_DraconidAdmins_2
	trainerbattle_no_intro TRAINER_TABITHA_VICTORY_ROAD, VictoryRoad_B1F_Text_DraconidTabithaDefeat
	trainerbattle_no_intro TRAINER_COURTNEY_VICTORY_ROAD, VictoryRoad_B1F_Text_DraconidCourtneyDefeat
VictoryRoad_B1F_EventScript_DraconidAdmins_1:
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_6
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_7
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_8
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_9
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_10
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_11
	msgbox VictoryRoad_B1F_EventScript_DraconidAdmins_Text_12
	closemessage
	applymovement LOCALID_VICTORY_ROAD_B1F_COURTNEY, VictoryRoad_B1F_Movement_DraconidCourtneyUp
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_VICTORY_ROAD_B1F_COURTNEY
	applymovement LOCALID_VICTORY_ROAD_B1F_TABITHA, VictoryRoad_B1F_Movement_DraconidTabithaUp
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_VICTORY_ROAD_B1F_TABITHA
	setvar VAR_TEMP_2, 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

VictoryRoad_B1F_EventScript_DraconidAdmins_2:
	trainerbattle_two_trainers_no_intro TRAINER_TABITHA_VICTORY_ROAD, VictoryRoad_B1F_Text_DraconidTabithaDefeat, TRAINER_COURTNEY_VICTORY_ROAD, VictoryRoad_B1F_Text_DraconidCourtneyDefeat
	goto VictoryRoad_B1F_EventScript_DraconidAdmins_1


VictoryRoad_B1F_Movement_DraconidTabithaDown:
	walk_right
	walk_right
	face_down
	step_end

VictoryRoad_B1F_Movement_DraconidCourtneyDown:
	walk_right
	face_down
	step_end

VictoryRoad_B1F_Movement_DraconidCourtneyUp:
	walk_left
	step_end

VictoryRoad_B1F_Movement_DraconidTabithaUp:
	walk_left
	walk_left
	step_end

MtPyre_Summit_EventScript_DraconidOldLadyOrbsKept::
	msgbox MtPyre_Summit_EventScript_DraconidOldLadyOrbsKept_Text_0
	release
	end


SootopolisCity_EventScript_DraconidRevengeAmbush_Text_0:
	.string "???: Hold it right there, TRAITOR!$"

SootopolisCity_EventScript_DraconidRevengeAmbush_Text_1:
	.string "GRUNT: We watched your whole GYM\n"
	.string "battle from the stands, traitor.$"

SootopolisCity_EventScript_DraconidRevengeAmbush_Text_2:
	.string "GRUNT: The boss gave us one order. You\n"
	.string "don't reach the LEAGUE!$"

SootopolisCity_EventScript_DraconidRevengeAmbush_Text_3:
	.string "GRUNT: Tch… This isn't over!\p"
	.string "There's more of us between here and\n"
	.string "EVER GRANDE. Count on it!$"

EverGrandeCity_EventScript_DraconidShoreAmbush_Text_0:
	.string "GRUNT: There! Coming up the waterfall!\n"
	.string "It's the TRAITOR!$"

EverGrandeCity_EventScript_DraconidShoreAmbush_Text_1:
	.string "GRUNT: You're not setting one foot on\n"
	.string "EVER GRANDE!$"

EverGrandeCity_EventScript_DraconidShoreAmbush_Text_2:
	.string "GRUNT: Fall back! Fall back!$"

EverGrandeCity_EventScript_DraconidCenterGruntLeaves_Text_0:
	.string "GRUNT: Fine! Go heal up.\p"
	.string "It won't help you. Not with what's\n"
	.string "waiting up those steps.$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_0:
	.string "???: Now! Surround the kid!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_1:
	.string "GRUNT: So you're the brat who beat\n"
	.string "MAXIE and ARCHIE in SOOTOPOLIS.$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_2:
	.string "GRUNT: Nobody gets up VICTORY ROAD\n"
	.string "today.\p"
	.string "We'll take turns. One after another,\n"
	.string "until you drop!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_3:
	.string "GRUNT: Me first!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_4:
	.string "GRUNT: No time to catch your breath!\n"
	.string "Next!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_5:
	.string "GRUNT: Looking for a way out? There\n"
	.string "isn't one!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_6:
	.string "GRUNT: Your POKéMON are getting tired.\n"
	.string "I can see it!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_7:
	.string "GRUNT: Last one! Then it's the ADMIN's\n"
	.string "turn!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_8:
	.string "SHELLY: Ahahaha! Still standing after\n"
	.string "all five? Not bad, kid.$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_9:
	.string "SHELLY: Remember me? SHELLY, TEAM\n"
	.string "AQUA's ADMIN.\p"
	.string "Last time we met, at the WEATHER\n"
	.string "INSTITUTE, you were wearing red.$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_10:
	.string "SHELLY: ARCHIE sends his regards.$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_11:
	.string "SHELLY: He and MAXIE had a long talk\n"
	.string "after SOOTOPOLIS.\p"
	.string "For once, the two of them agree on\n"
	.string "something. And that something is you.$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_12:
	.string "SHELLY: Let's see what you have left!$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_13:
	.string "SHELLY: Ahaha… Six battles, and you're\n"
	.string "still on your feet.\p"
	.string "ARCHIE won't like hearing that.$"

EverGrandeCity_EventScript_DraconidAquaGauntlet_Text_14:
	.string "SHELLY: But this isn't the end of it,\n"
	.string "kid.\n"
	.string "MAXIE and ARCHIE have long memories.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_0:
	.string "MAXIE: {PLAYER}.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_1:
	.string "MAXIE: The road to the LEAGUE runs\n"
	.string "through this cave. So I waited for you\l"
	.string "here.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_2:
	.string "MAXIE: My grunts could not stop you.\n"
	.string "Nor could ARCHIE's. No matter.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_3:
	.string "MAXIE: You will not stand as CHAMPION\n"
	.string "while my work lies in ruins.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_4:
	.string "MAXIE: Come, liar.\n"
	.string "Show me the strength you hid from me.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_5:
	.string "MAXIE: …So be it.\n"
	.string "Go on to your LEAGUE.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_6:
	.string "MAXIE: But this is not over, {PLAYER}.\n"
	.string "It is far from over.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_7:
	.string "MAXIE: You have a home, do you not?\n"
	.string "Somewhere in the mountains, under the\l"
	.string "sky you serve.$"

EverGrandeCity_EventScript_DraconidMaxie_Text_8:
	.string "MAXIE: I wonder how your people would\n"
	.string "bear it, to lose everything as I have.$"

EverGrandeCity_EventScript_DraconidExitGrunt_Text_0:
	.string "GRUNT: You made it through VICTORY\n"
	.string "ROAD? Past the ADMINS?!$"

EverGrandeCity_EventScript_DraconidExitGrunt_Text_1:
	.string "GRUNT: Doesn't matter. The boss's\n"
	.string "orders still stand. You don't reach the\l"
	.string "LEAGUE!$"

EverGrandeCity_EventScript_DraconidExitGrunt_Text_2:
	.string "GRUNT: There are two more of us at the\n"
	.string "door.\n"
	.string "They won't go easy on you!$"

EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_0:
	.string "GRUNT: That's far enough, traitor!$"

EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_1:
	.string "GRUNT: The boss said the traitor never\n"
	.string "reaches that door. Never!$"

EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_2:
	.string "GRUNT: We're the last ones.\n"
	.string "So we're giving it everything!$"

EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_3:
	.string "GRUNT: …That's it. That was all of us.$"

EverGrandeCity_EventScript_DraconidLeagueGrunts_Text_4:
	.string "GRUNT: Go on, then. Go be CHAMPION.\p"
	.string "But the boss won't forget you.\n"
	.string "None of us will.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_0:
	.string "???: Hehehe… Going somewhere?$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_1:
	.string "TABITHA: Did you really think the\n"
	.string "Leader was the last of us?$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_2:
	.string "TABITHA: I vouched for you, you know,\n"
	.string "in front of the Leader and everyone.\p"
	.string "Now I'm the ADMIN who brought a spy\n"
	.string "home. Hehe… Everybody knows it.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_3:
	.string "COURTNEY: …And I recruited you.\n"
	.string "In PETALBURG WOODS.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_4:
	.string "COURTNEY: Error: mine.\n"
	.string "I do not make the same error twice.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_5:
	.string "COURTNEY: Two of us. Two of your\n"
	.string "POKéMON.\n"
	.string "…Begin.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_6:
	.string "TABITHA: Tch… Hehe… Go on, then.\n"
	.string "Go win your shiny LEAGUE.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_7:
	.string "COURTNEY: …Win. Lose.\n"
	.string "It does not matter anymore.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_8:
	.string "COURTNEY: MAXIE knows where you come\n"
	.string "from now.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_9:
	.string "TABITHA: A village up in the mountains,\n"
	.string "right? Where the dragons nest.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_10:
	.string "COURTNEY: ARCHIE knows, too.\n"
	.string "…They talk. Every night, they talk.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_11:
	.string "TABITHA: When the Leader comes for\n"
	.string "your precious DRACONIDS, you'll wish\l"
	.string "you'd stayed in red.$"

VictoryRoad_B1F_EventScript_DraconidAdmins_Text_12:
	.string "COURTNEY: …The DRACONIDS will pay.\n"
	.string "All of them.$"

MtPyre_Summit_EventScript_DraconidOldLadyOrbsKept_Text_0:
	.string "The ORBS have not come back…\p"
	.string "Those two men still hold them, the one\n"
	.string "in red and the one in blue.\p"
	.string "…You no longer wear their red, I see.\p"
	.string "I fear the land and the sea have not\n"
	.string "had their last word.$"

SootopolisCity_Text_DraconidRevengeGrunt1Defeat::
	.string "GRUNT: The spy's still this strong?!$"

SootopolisCity_Text_DraconidRevengeGrunt2Defeat::
	.string "GRUNT: We trusted you!$"

EverGrandeCity_Text_DraconidShoreGrunt1Defeat::
	.string "GRUNT: Knocked right back into the\n"
	.string "sea…$"

EverGrandeCity_Text_DraconidShoreGrunt2Defeat::
	.string "GRUNT: Why do we keep losing to you?!$"

EverGrandeCity_Text_DraconidCenterGruntIntro::
	.string "GRUNT: Going to heal up, traitor?\n"
	.string "Not while I'm standing here!$"

EverGrandeCity_Text_DraconidCenterGruntDefeat::
	.string "GRUNT: Ugh… I was supposed to wear you\n"
	.string "down!$"

EverGrandeCity_Text_DraconidAquaGrunt1Defeat::
	.string "GRUNT: Hey! I was supposed to\n"
	.string "wear you down!$"

EverGrandeCity_Text_DraconidAquaGrunt2Defeat::
	.string "GRUNT: Grr… Somebody else take over!$"

EverGrandeCity_Text_DraconidAquaGrunt3Defeat::
	.string "GRUNT: How are you still going?!$"

EverGrandeCity_Text_DraconidAquaGrunt4Defeat::
	.string "GRUNT: Guess they're not THAT tired…$"

EverGrandeCity_Text_DraconidAquaGrunt5Defeat::
	.string "GRUNT: SHELLY! Help!$"

EverGrandeCity_Text_DraconidShellyDefeat::
	.string "SHELLY: Ahaha! Well, aren't you\n"
	.string "something!$"

EverGrandeCity_Text_DraconidMaxieDefeat::
	.string "Again… Beaten by you again.$"

EverGrandeCity_Text_DraconidExitGruntDefeat::
	.string "GRUNT: How is anyone this strong?$"

EverGrandeCity_Text_DraconidLeagueGrunt1Defeat::
	.string "GRUNT: The boss is gonna kill us…$"

EverGrandeCity_Text_DraconidLeagueGrunt2Defeat::
	.string "GRUNT: Not even at the very end…$"

VictoryRoad_B1F_Text_DraconidTabithaDefeat::
	.string "TABITHA: Hehe… Beaten by my own grunt.\n"
	.string "Again.$"

VictoryRoad_B1F_Text_DraconidCourtneyDefeat::
	.string "COURTNEY: …Unacceptable.$"
