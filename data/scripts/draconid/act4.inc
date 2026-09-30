PetalburgCity_Gym_EventScript_DraconidHideMay::
	setflag FLAG_TEMP_11
	return


PetalburgCity_Gym_EventScript_DraconidNormanUniform::
	switch VAR_PETALBURG_GYM_STATE
	case 2, PetalburgCity_Gym_EventScript_DraconidNormanUniform_3
	case 3, PetalburgCity_Gym_EventScript_DraconidNormanUniform_4
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_3
PetalburgCity_Gym_EventScript_DraconidNormanUniform_1:
	release
	return

PetalburgCity_Gym_EventScript_DraconidNormanUniform_3:
	compare VAR_BRENDAN_STATE, BRENDAN_STATE_RUSTBORO
	goto_if_lt PetalburgCity_Gym_EventScript_DraconidNormanUniform_6
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_1
	goto PetalburgCity_Gym_EventScript_DraconidNormanUniform_1

PetalburgCity_Gym_EventScript_DraconidNormanUniform_4:
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_2
	goto PetalburgCity_Gym_EventScript_DraconidNormanUniform_1

PetalburgCity_Gym_EventScript_DraconidNormanUniform_6:
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_0
	goto PetalburgCity_Gym_EventScript_DraconidNormanUniform_1


PetalburgCity_Gym_EventScript_DraconidNormanRevealed::
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanRevealed_Text_0
	release
	return


PetalburgCity_Gym_EventScript_DraconidMay::
	lock
	faceplayer
	msgbox PetalburgCity_Gym_EventScript_DraconidMay_Text_0
	release
	return


PetalburgCity_Gym_EventScript_DraconidMayWatched::
	applymovement LOCALID_PETALBURG_GYM_MAY, PetalburgCity_Gym_Movement_DraconidMayStepUp
	waitmovement 0
	compare VAR_FACING, DIR_WEST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_2
	compare VAR_FACING, DIR_EAST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_3
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PETALBURG_GYM_MAY, Common_Movement_WalkInPlaceFasterLeft
PetalburgCity_Gym_EventScript_DraconidMayWatched_1:
	waitmovement 0
	msgbox PetalburgCity_Gym_EventScript_DraconidMayWatched_Text_0
	closemessage
	applymovement LOCALID_PETALBURG_GYM_MAY, PetalburgCity_Gym_Movement_DraconidMayLeave
	waitmovement 0
	removeobject LOCALID_PETALBURG_GYM_MAY
	compare VAR_FACING, DIR_WEST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_8
	compare VAR_FACING, DIR_EAST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_9
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
PetalburgCity_Gym_EventScript_DraconidMayWatched_7:
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_DraconidMayWatched_2:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PETALBURG_GYM_MAY, Common_Movement_WalkInPlaceFasterUp
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_1

PetalburgCity_Gym_EventScript_DraconidMayWatched_3:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PETALBURG_GYM_MAY, Common_Movement_WalkInPlaceFasterLeft
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_1

PetalburgCity_Gym_EventScript_DraconidMayWatched_8:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_7

PetalburgCity_Gym_EventScript_DraconidMayWatched_9:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_7


PetalburgCity_Gym_Movement_DraconidMayStepUp:
	walk_left
	step_end

PetalburgCity_Gym_Movement_DraconidMayLeave:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	set_invisible
	step_end

LavaridgeTown_Gym_1F_EventScript_DraconidWallyWaits::
	compare VAR_WALLY_STATE, WALLY_STATE_START
	goto_if_eq LavaridgeTown_Gym_1F_EventScript_DraconidWallyWaits_1
	return

LavaridgeTown_Gym_1F_EventScript_DraconidWallyWaits_1:
	setvar VAR_WALLY_STATE, WALLY_STATE_PETALBURG
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLY_GYM
	return


PetalburgCity_EventScript_DraconidWallyTalk::
	goto PetalburgCity_EventScript_DraconidWallyTrigger
	return


PetalburgCity_EventScript_DraconidWallyTrigger::
	lockall
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_PETALBURG_WALLY_GYM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PETALBURG_WALLY_GYM, Common_Movement_WalkRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgCity_EventScript_DraconidWallyTrigger_Text_0
	msgbox PetalburgCity_EventScript_DraconidWallyTrigger_Text_1
	msgbox PetalburgCity_EventScript_DraconidWallyTrigger_Text_2
	trainerbattle_no_intro TRAINER_WALLY_PETALBURG, PetalburgCity_Text_DraconidWallyDefeat
	msgbox PetalburgCity_EventScript_DraconidWallyTrigger_Text_3
	closemessage
	applymovement LOCALID_PETALBURG_WALLY_GYM, PetalburgCity_Movement_DraconidWallyLeave
	waitmovement 0
	removeobject LOCALID_PETALBURG_WALLY_GYM
	setflag FLAG_HIDE_PETALBURG_CITY_WALLY_GYM
	setvar VAR_WALLY_STATE, WALLY_STATE_LILYCOVE
	clearflag FLAG_HIDE_LILYCOVE_CITY_WALLY
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


PetalburgCity_Movement_DraconidWallyLeave:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

Route119_EventScript_DraconidTabithaOrder::
	goto_if_set FLAG_HIDE_ROUTE_119_TABITHA, Route119_EventScript_DraconidTabithaOrder_2
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_ROUTE119_TABITHA, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Route119_EventScript_DraconidTabithaOrder_Text_0
	closemessage
	applymovement LOCALID_ROUTE119_TABITHA, Route119_Movement_DraconidTabithaLeave
	waitmovement 0
	removeobject LOCALID_ROUTE119_TABITHA
	setflag FLAG_HIDE_ROUTE_119_TABITHA
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

Route119_EventScript_DraconidTabithaOrder_2:
	end


Route119_Movement_DraconidTabithaLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route119_EventScript_DraconidTabitha::
	msgbox Route119_EventScript_DraconidTabitha_Text_0, MSGBOX_NPC
	return


Route119_WeatherInstitute_2F_EventScript_DraconidHideScene::
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	return


Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers::
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_0
	closemessage
	playbgm MUS_ENCOUNTER_MAY, FALSE
	addobject LOCALID_WEATHER_INSTITUTE_2F_MAY
	applymovement LOCALID_WEATHER_INSTITUTE_2F_MAY, Route119_WeatherInstitute_2F_Movement_DraconidMayArrive
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_DraconidPlayerHearsMay
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_1
	applymovement LOCALID_WEATHER_INSTITUTE_2F_MAY, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_2
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_3
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_4
	closemessage
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	addobject LOCALID_WEATHER_INSTITUTE_2F_TABITHA
	applymovement LOCALID_WEATHER_INSTITUTE_2F_TABITHA, Route119_WeatherInstitute_2F_Movement_DraconidTabithaArrive
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_5
	closemessage
	applymovement LOCALID_WEATHER_INSTITUTE_2F_MAY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_6
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_7
	closemessage
	applymovement LOCALID_WEATHER_INSTITUTE_2F_TABITHA, Route119_WeatherInstitute_2F_Movement_DraconidTabithaLeave
	waitmovement 0
	removeobject LOCALID_WEATHER_INSTITUTE_2F_TABITHA
	playbgm MUS_ENCOUNTER_MAY, FALSE
	applymovement LOCALID_WEATHER_INSTITUTE_2F_MAY, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_8
	closemessage
	applymovement LOCALID_WEATHER_INSTITUTE_2F_MAY, Route119_WeatherInstitute_2F_Movement_DraconidMayLeave
	waitmovement 0
	removeobject LOCALID_WEATHER_INSTITUTE_2F_MAY
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	setvar VAR_MAY_STATE, MAY_STATE_WEATHER_INSTITUTE
	setvar VAR_MAGMA_STATE, MAGMA_STATE_WEATHER_INSTITUTE
	savebgm MUS_DUMMY
	fadedefaultbgm
	return


Route119_WeatherInstitute_2F_Movement_DraconidMayArrive:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route119_WeatherInstitute_2F_Movement_DraconidPlayerHearsMay:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

Route119_WeatherInstitute_2F_Movement_DraconidTabithaArrive:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route119_WeatherInstitute_2F_Movement_DraconidTabithaLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

Route119_WeatherInstitute_2F_Movement_DraconidMayLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

Route119_EventScript_DraconidRegisterBrendan::
	msgbox Route119_EventScript_DraconidRegisterBrendan_Text_0
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route119_EventScript_DraconidRegisterBrendan_Text_1
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_BRENDAN_MATCH_CALL
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_ROUTE_119
	msgbox Route119_EventScript_DraconidRegisterBrendan_Text_2
	return


LilycoveCity_EventScript_DraconidRivals::
	lock
	faceplayer
	playbgm MUS_ENCOUNTER_MAY, TRUE
	goto_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_DraconidRivals_2
	msgbox LilycoveCity_EventScript_DraconidRivals_Text_1, MSGBOX_YESNO
LilycoveCity_EventScript_DraconidRivals_1:
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_EventScript_DraconidRivals_6
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne LilycoveCity_EventScript_DraconidRivals_9
	msgbox LilycoveCity_EventScript_DraconidRivals_Text_3
	trainerbattle_two_trainers_no_intro TRAINER_BRENDAN_LILYCOVE, LilycoveCity_Text_DraconidBrendanDefeat, TRAINER_MAY_LILYCOVE, LilycoveCity_Text_DraconidMayDefeat
	msgbox LilycoveCity_EventScript_DraconidRivals_Text_4
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	call LilycoveCity_EventScript_DraconidFlyAway
	setflag FLAG_MET_RIVAL_LILYCOVE
	setflag FLAG_HIDE_LILYCOVE_CITY_RIVAL
	compare VAR_BRENDAN_STATE, BRENDAN_STATE_LILYCOVE
	goto_if_lt LilycoveCity_EventScript_DraconidRivals_12
LilycoveCity_EventScript_DraconidRivals_11:
	compare VAR_MAY_STATE, MAY_STATE_LILYCOVE
	goto_if_lt LilycoveCity_EventScript_DraconidRivals_15
LilycoveCity_EventScript_DraconidRivals_14:
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	return

LilycoveCity_EventScript_DraconidRivals_2:
	msgbox LilycoveCity_EventScript_DraconidRivals_Text_0, MSGBOX_YESNO
	goto LilycoveCity_EventScript_DraconidRivals_1

LilycoveCity_EventScript_DraconidRivals_6:
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_EventScript_DraconidRivals_Text_2
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_DraconidRivals_9:
	msgbox LilycoveCity_Text_DraconidRivalsNeedTwo, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_DraconidRivals_12:
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_LILYCOVE
	goto LilycoveCity_EventScript_DraconidRivals_11

LilycoveCity_EventScript_DraconidRivals_15:
	setvar VAR_MAY_STATE, MAY_STATE_LILYCOVE
	goto LilycoveCity_EventScript_DraconidRivals_14


LilycoveCity_EventScript_DraconidFlyAway::
	applymovement LOCALID_LILYCOVE_BRENDAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_LILYCOVE_MAY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_LILYCOVE_BRENDAN
	waitfieldeffect FLDEFF_NPCFLY_OUT
	delay 20
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_LILYCOVE_MAY
	waitfieldeffect FLDEFF_NPCFLY_OUT
	return


LilycoveCity_EventScript_DraconidWally::
	lock
	faceplayer
	msgbox LilycoveCity_EventScript_DraconidWally_Text_0
	msgbox LilycoveCity_EventScript_DraconidWally_Text_1
	trainerbattle_no_intro TRAINER_WALLY_LILYCOVE, LilycoveCity_Text_DraconidWallyDefeat
	msgbox LilycoveCity_EventScript_DraconidWally_Text_2
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_LILYCOVE_WALLY
	setflag FLAG_HIDE_LILYCOVE_CITY_WALLY
	compare VAR_WALLY_STATE, WALLY_STATE_LILYCOVE_DONE
	goto_if_lt LilycoveCity_EventScript_DraconidWally_2
LilycoveCity_EventScript_DraconidWally_1:
	fadescreen FADE_FROM_BLACK
	release
	return

LilycoveCity_EventScript_DraconidWally_2:
	setvar VAR_WALLY_STATE, WALLY_STATE_LILYCOVE_DONE
	goto LilycoveCity_EventScript_DraconidWally_1


MtPyre_Summit_EventScript_DraconidOnTransition::
	compare VAR_MT_PYRE_STATE, 0
	goto_if_eq MtPyre_Summit_EventScript_DraconidOnTransition_3
MtPyre_Summit_EventScript_DraconidOnTransition_1:
	compare VAR_MT_PYRE_STATE, 0
	goto_if_eq MtPyre_Summit_EventScript_DraconidOnTransition_8
MtPyre_Summit_EventScript_DraconidOnTransition_7:
	setflag FLAG_TEMP_11
	return

MtPyre_Summit_EventScript_DraconidOnTransition_2:
	checkitem ITEM_MAGMA_EMBLEM
	compare VAR_RESULT, FALSE
	goto_if_eq MtPyre_Summit_EventScript_DraconidOnTransition_11
	goto MtPyre_Summit_EventScript_DraconidOnTransition_1

MtPyre_Summit_EventScript_DraconidOnTransition_3:
	compare VAR_MAGMA_STATE, MAGMA_STATE_MT_PYRE
	goto_if_lt MtPyre_Summit_EventScript_DraconidOnTransition_2
	goto MtPyre_Summit_EventScript_DraconidOnTransition_1

MtPyre_Summit_EventScript_DraconidOnTransition_6:
	setvar VAR_TEMP_2, 1
	return

MtPyre_Summit_EventScript_DraconidOnTransition_8:
	compare VAR_NERINE_STATE, NERINE_STATE_MT_PYRE
	goto_if_lt MtPyre_Summit_EventScript_DraconidOnTransition_6
	goto MtPyre_Summit_EventScript_DraconidOnTransition_7

MtPyre_Summit_EventScript_DraconidOnTransition_11:
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_MT_PYRE_SUMMIT_MAXIE, 23, 27
	setobjectmovementtype LOCALID_MT_PYRE_SUMMIT_MAXIE, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	goto MtPyre_Summit_EventScript_DraconidOnTransition_1


MtPyre_Summit_EventScript_DraconidMaxieOrders::
	lockall
	setvar VAR_TEMP_1, 0
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8005, 30
	goto_if_ne MtPyre_Summit_EventScript_DraconidMaxieOrders_2
MtPyre_Summit_EventScript_DraconidMaxieOrders_1:
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_DraconidMaxieApproach
	waitmovement 0
	msgbox MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_0
	msgbox MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_1
	msgbox MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_2
	msgbox MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_3
	giveitem ITEM_MAGMA_EMBLEM
	msgbox MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_4
	closemessage
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_DraconidMaxieLeave
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_DraconidPlayerWatchMaxie
	waitmovement 0
	removeobject LOCALID_MT_PYRE_SUMMIT_MAXIE
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

MtPyre_Summit_EventScript_DraconidMaxieOrders_2:
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	goto MtPyre_Summit_EventScript_DraconidMaxieOrders_1


MtPyre_Summit_Movement_DraconidMaxieApproach:
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_DraconidMaxieLeave:
	walk_left
	walk_down
	walk_down
	set_invisible
	step_end

MtPyre_Summit_Movement_DraconidPlayerWatchMaxie:
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_EventScript_DraconidNerine::
	lockall
	setvar VAR_TEMP_2, 0
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	getplayerxy VAR_0x8004, VAR_0x8005
	switch VAR_0x8004
	case 22, MtPyre_Summit_EventScript_DraconidNerine_3
	case 23, MtPyre_Summit_EventScript_DraconidNerine_4
	applymovement LOCALID_MT_PYRE_SUMMIT_NERINE, MtPyre_Summit_Movement_DraconidNerineToRight
MtPyre_Summit_EventScript_DraconidNerine_1:
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MtPyre_Summit_EventScript_DraconidNerine_Text_0
	msgbox MtPyre_Summit_EventScript_DraconidNerine_Text_1
	trainerbattle_no_intro TRAINER_NERINE_MT_PYRE_DEINO_CHARMANDER, MtPyre_Summit_Text_DraconidNerineDefeat
	msgbox MtPyre_Summit_EventScript_DraconidNerine_Text_2
	closemessage
	switch VAR_0x8004
	case 22, MtPyre_Summit_EventScript_DraconidNerine_8
	applymovement LOCALID_MT_PYRE_SUMMIT_NERINE, MtPyre_Summit_Movement_DraconidNerineLeaveLeft
MtPyre_Summit_EventScript_DraconidNerine_6:
	waitmovement 0
	removeobject LOCALID_MT_PYRE_SUMMIT_NERINE
	setvar VAR_NERINE_STATE, NERINE_STATE_MT_PYRE
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

MtPyre_Summit_EventScript_DraconidNerine_3:
	applymovement LOCALID_MT_PYRE_SUMMIT_NERINE, MtPyre_Summit_Movement_DraconidNerineToLeft
	goto MtPyre_Summit_EventScript_DraconidNerine_1

MtPyre_Summit_EventScript_DraconidNerine_4:
	applymovement LOCALID_MT_PYRE_SUMMIT_NERINE, MtPyre_Summit_Movement_DraconidNerineToMiddle
	goto MtPyre_Summit_EventScript_DraconidNerine_1

MtPyre_Summit_EventScript_DraconidNerine_8:
	applymovement LOCALID_MT_PYRE_SUMMIT_NERINE, MtPyre_Summit_Movement_DraconidNerineLeaveRight
	goto MtPyre_Summit_EventScript_DraconidNerine_6


MtPyre_Summit_Movement_DraconidNerineToLeft:
	walk_left
	walk_down
	step_end

MtPyre_Summit_Movement_DraconidNerineToMiddle:
	walk_down
	step_end

MtPyre_Summit_Movement_DraconidNerineToRight:
	walk_right
	walk_down
	step_end

MtPyre_Summit_Movement_DraconidNerineLeaveRight:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_DraconidNerineLeaveLeft:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

JaggedPass_EventScript_DraconidGuardGreets::
	goto_if_set FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD, JaggedPass_EventScript_DraconidGuardGreets_2
	playse SE_PIN
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_EventScript_DraconidGuardGreets_Text_0
	closemessage
	return

JaggedPass_EventScript_DraconidGuardGreets_2:
	return


JaggedPass_EventScript_DraconidGuardGoesIn::
	goto_if_set FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD, JaggedPass_EventScript_DraconidGuardGoesIn_2
	msgbox JaggedPass_EventScript_DraconidGuardGoesIn_Text_0
	closemessage
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, JaggedPass_Movement_DraconidGuardGoIn
	waitmovement 0
	removeobject LOCALID_MAGMA_HIDEOUT_GUARD
	setflag FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD
	return

JaggedPass_EventScript_DraconidGuardGoesIn_2:
	return


JaggedPass_Movement_DraconidGuardGoIn:
	face_up
	delay_8
	walk_up
	set_invisible
	step_end

MagmaHideout_4F_EventScript_DraconidPromotion::
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MagmaHideout_4F_EventScript_DraconidPromotion_Text_0
	msgbox MagmaHideout_4F_EventScript_DraconidPromotion_Text_1
	msgbox MagmaHideout_4F_EventScript_DraconidPromotion_Text_2
	closemessage
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 30
	return


MagmaHideout_4F_EventScript_DraconidSendWord::
	delay 30
	msgbox MagmaHideout_4F_EventScript_DraconidSendWord_Text_0
	setvar VAR_MAGMA_STATE, MAGMA_STATE_PROMOTED
	return


PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_0:
	.string "NORMAN: {PLAYER}?\n"
	.string "…That's a TEAM MAGMA uniform.\p"
	.string "I won't ask why. But I will remember it.\p"
	.string "Come back when you have four BADGES.$"

PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_1:
	.string "NORMAN: That's a MAGMA uniform,\n"
	.string "{PLAYER}. MAY told me. I didn't want to\l"
	.string "believe her.\p"
	.string "Still, a GYM LEADER doesn't choose his\n"
	.string "challengers. Come back with four\l"
	.string "BADGES.$"

PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_2:
	.string "NORMAN: ROXANNE's BADGE… and that red\n"
	.string "uniform. An odd pair.\p"
	.string "Go on to DEWFORD. I'll battle you when\n"
	.string "you have four BADGES.$"

PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_3:
	.string "NORMAN: Hm… You've gotten stronger. I\n"
	.string "can tell by your BADGES.\p"
	.string "I only wish I knew what you're getting\n"
	.string "stronger for.$"

PetalburgCity_Gym_EventScript_DraconidNormanRevealed_Text_0:
	.string "NORMAN: {PLAYER}. MAY told me\n"
	.string "everything about SOOTOPOLIS.\p"
	.string "I judged you by a uniform. A GYM LEADER\n"
	.string "should know better.\p"
	.string "Your POKéMON never doubted you.\n"
	.string "Neither will I, from now on.$"

PetalburgCity_Gym_EventScript_DraconidMay_Text_0:
	.string "MAY: I'm here to watch my dad beat you.\p"
	.string "He won't go easy on a MAGMA grunt.$"

PetalburgCity_Gym_EventScript_DraconidMayWatched_Text_0:
	.string "MAY: Dad says you fought honestly.\n"
	.string "That's not what MAGMA does.\p"
	.string "…So why are you wearing that uniform?\p"
	.string "Whatever you're up to, {PLAYER}, I'm\n"
	.string "going to find out.$"

PetalburgCity_EventScript_DraconidWallyTrigger_Text_0:
	.string "WALLY: {PLAYER}. I came to thank MR.\n"
	.string "NORMAN for helping me catch RALTS.\p"
	.string "He's MAY's dad. She says you're going to\n"
	.string "challenge him.$"

PetalburgCity_EventScript_DraconidWallyTrigger_Text_1:
	.string "WALLY: You went up MT. CHIMNEY with\n"
	.string "MAGMA, didn't you?\p"
	.string "The whole mountain was smoking!\n"
	.string "LAVARIDGE was right below it!$"

PetalburgCity_EventScript_DraconidWallyTrigger_Text_2:
	.string "WALLY: MR. NORMAN helped me when I was\n"
	.string "weak.\p"
	.string "So before you challenge him… you'll have\n"
	.string "to get past me!$"

PetalburgCity_EventScript_DraconidWallyTrigger_Text_3:
	.string "WALLY: I'm going to travel all over\n"
	.string "HOENN and get even stronger.\p"
	.string "Wherever MAGMA shows up, I'll be there\n"
	.string "to stop them.\n"
	.string "You too, {PLAYER}.$"

Route119_EventScript_DraconidTabithaOrder_Text_0:
	.string "TABITHA: Hehehe! There you are, grunt.\n"
	.string "Right on time.\p"
	.string "AQUA got here first. They're inside,\n"
	.string "pushing the eggheads around.\p"
	.string "This INSTITUTE studies the weather.\n"
	.string "Rain, sun, storms…\p"
	.string "Leader MAXIE wants to know what\n"
	.string "they've found. So do I.\p"
	.string "Get in there and take the research\n"
	.string "before AQUA does.\p"
	.string "I'll round up the others. When I come\n"
	.string "back, you'd better have it. Hehehe!$"

Route119_EventScript_DraconidTabitha_Text_0:
	.string "TABITHA: Well? The INSTITUTE's door is\n"
	.string "right there, grunt. Hehehe!$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_0:
	.string "In the confusion, {PLAYER} had slipped\n"
	.string "into the back room and quietly untied\l"
	.string "the scientists.$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_1:
	.string "MAY: I heard shouting from the road! Is\n"
	.string "TEAM AQUA still here?\p"
	.string "{PLAYER}?! So MAGMA is here, too!\p"
	.string "What did you do to these people?!$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_2:
	.string "MAY: Huh? Those people in the back room\n"
	.string "are untied…$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_3:
	.string "SCIENTIST: It's true! That trainer\n"
	.string "drove AQUA off and set us free!$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_4:
	.string "MAY: You set them free?\p"
	.string "{PLAYER}, you're not really one of…$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_5:
	.string "TABITHA: Hehehe! Not really one of\n"
	.string "what, little girl?$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_6:
	.string "MAY: …One of the TRAINERS worth my\n"
	.string "time! Hmph!\p"
	.string "Chasing off a few AQUA grunts? Anybody\n"
	.string "could do that!\p"
	.string "You MAGMA people are all the same!$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_7:
	.string "TABITHA: Hehehe! Feisty.\p"
	.string "AQUA ran like rats, grunt. Good work.\p"
	.string "And the eggheads left their notes lying\n"
	.string "around. Weather records… something\l"
	.string "about ancient ORBS.\p"
	.string "Leader MAXIE will love this. I'll take it\n"
	.string "to him myself.\p"
	.string "Keep your POKéNAV on. He'll have orders\n"
	.string "for you soon. Hehehe!$"

Route119_WeatherInstitute_2F_EventScript_DraconidMayCovers_Text_8:
	.string "MAY: I'll pretend I didn't see you save\n"
	.string "them, {PLAYER}.\p"
	.string "But don't think this changes anything.\n"
	.string "You still work for MAGMA.$"

Route119_EventScript_DraconidRegisterBrendan_Text_0:
	.string "BRENDAN: And MAY wants us registered\n"
	.string "in each other's POKéNAVS.\p"
	.string "Fine by me. If MAGMA makes a move, I'll\n"
	.string "know where to find you.$"

Route119_EventScript_DraconidRegisterBrendan_Text_1:
	.string "Registered BRENDAN in the POKéNAV.$"

Route119_EventScript_DraconidRegisterBrendan_Text_2:
	.string "BRENDAN: If MAY's wrong about you, I'm\n"
	.string "the one who stops you.\p"
	.string "I'll be watching, {PLAYER}.$"

LilycoveCity_EventScript_DraconidRivals_Text_0:
	.string "BRENDAN: Back again?\n"
	.string "Ready to settle this?$"

LilycoveCity_EventScript_DraconidRivals_Text_1:
	.string "MAY: {PLAYER}. BRENDAN and I have been\n"
	.string "looking for you.\p"
	.string "BRENDAN: MAGMA raided the\n"
	.string "WEATHER INSTITUTE, and you were there!\p"
	.string "MAY: Whatever your reason is, you're\n"
	.string "still helping MAGMA.\p"
	.string "BRENDAN: So we're stopping you right\n"
	.string "here!\p"
	.string "MAY: The two of us against you,\n"
	.string "{PLAYER}. Ready?$"

LilycoveCity_EventScript_DraconidRivals_Text_2:
	.string "MAY: Running away? That's just what a\n"
	.string "MAGMA grunt would do.\p"
	.string "We're not going anywhere, {PLAYER}.$"

LilycoveCity_EventScript_DraconidRivals_Text_3:
	.string "BRENDAN: MAGMA stops here!\p"
	.string "MAY: {PLAYER}, show us who you\n"
	.string "really are!$"

LilycoveCity_EventScript_DraconidRivals_Text_4:
	.string "BRENDAN: Tch… MAGMA's up to something,\n"
	.string "and you're right in the middle of it.\p"
	.string "MAY: {PLAYER}… Is there something\n"
	.string "you're not telling us?\p"
	.string "BRENDAN: Forget it, MAY.\n"
	.string "We're going home.$"

LilycoveCity_EventScript_DraconidWally_Text_0:
	.string "WALLY: {PLAYER}. My KIRLIA evolved into\n"
	.string "GALLADE on the way here.\p"
	.string "And a man by the sea gave me this KEY\n"
	.string "STONE and a GALLADITE.$"

LilycoveCity_EventScript_DraconidWally_Text_1:
	.string "WALLY: He told me to use their power to\n"
	.string "protect people.\p"
	.string "So that's what I'll do. GALLADE and I are\n"
	.string "going to stop you, right here!$"

LilycoveCity_EventScript_DraconidWally_Text_2:
	.string "WALLY: Next time we battle, it'll be at\n"
	.string "the POKéMON LEAGUE.\p"
	.string "And I'll be ready for you, even if you're\n"
	.string "still wearing that uniform.$"

MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_0:
	.string "MAXIE: Ah, {PLAYER}. I have been\n"
	.string "expecting you.\p"
	.string "TABITHA tells me AQUA fled the\n"
	.string "WEATHER INSTITUTE in disgrace, and\l"
	.string "that it was your doing.$"

MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_1:
	.string "MAXIE: Look at this. The BLUE ORB, kept\n"
	.string "on this mountain since ancient times.\p"
	.string "The land itself seems to stir inside it.\n"
	.string "Magnificent, is it not?$"

MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_2:
	.string "MAXIE: Unfortunately, ARCHIE's rabble\n"
	.string "followed us here. They want the RED ORB,\l"
	.string "and this one too.\p"
	.string "Hold them off at the summit, {PLAYER}.\n"
	.string "We will take the ORB down the mountain.$"

MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_3:
	.string "MAXIE: Take this as well. It is the\n"
	.string "MAGMA EMBLEM.\p"
	.string "Only those I trust carry one. You have\n"
	.string "earned it.$"

MtPyre_Summit_EventScript_DraconidMaxieOrders_Text_4:
	.string "MAXIE: Keep it with you. When the time\n"
	.string "comes, I will call for you.$"

MtPyre_Summit_EventScript_DraconidNerine_Text_0:
	.string "NERINE: …You again.\p"
	.string "So MAXIE left you behind to hold the\n"
	.string "mountain.\p"
	.string "He chose well. That's what worries me.$"

MtPyre_Summit_EventScript_DraconidNerine_Text_1:
	.string "NERINE: Listen, {PLAYER}. Quietly.\p"
	.string "The land and the sea are sleeping.\n"
	.string "These ORBS are the only things that can\l"
	.string "calm them.\p"
	.string "Now each team has one. And each thinks\n"
	.string "it can wake a god and keep it on a leash.\p"
	.string "…ARCHIE is right up there. So we fight.\n"
	.string "Properly.$"

MtPyre_Summit_EventScript_DraconidNerine_Text_2:
	.string "NERINE: Your dragons are learning to\n"
	.string "fly.\p"
	.string "Soon you'll have to choose between the\n"
	.string "red and the sky.\p"
	.string "Choose well.$"

JaggedPass_EventScript_DraconidGuardGreets_Text_0:
	.string "GRUNT: Hey! Over here!\p"
	.string "That EMBLEM… You're the one the LEADER\n"
	.string "sent for!\p"
	.string "Hold it up. The door answers to the\n"
	.string "EMBLEM.$"

JaggedPass_EventScript_DraconidGuardGoesIn_Text_0:
	.string "GRUNT: Welcome to the HIDEOUT.\p"
	.string "The LEADER is waiting at the very\n"
	.string "bottom. I'll tell them you're coming!$"

MagmaHideout_4F_EventScript_DraconidPromotion_Text_0:
	.string "MAXIE: Come here, {PLAYER}.\p"
	.string "TABITHA told me how you held MT. PYRE\n"
	.string "alone against ARCHIE's whole crew.$"

MagmaHideout_4F_EventScript_DraconidPromotion_Text_1:
	.string "MAXIE: I have watched you since\n"
	.string "METEOR FALLS.\p"
	.string "You have exceeded every expectation.\n"
	.string "From now on, you are my right hand.$"

MagmaHideout_4F_EventScript_DraconidPromotion_Text_2:
	.string "MAXIE: Stand beside me, {PLAYER}, as the\n"
	.string "land is reborn.$"

MagmaHideout_4F_EventScript_DraconidSendWord_Text_0:
	.string "Only the magma still moved in the\n"
	.string "chamber where GROUDON had slept.\p"
	.string "{PLAYER} took out paper and wrote to\n"
	.string "the ELDER.\p"
	.string "“MAXIE has woken GROUDON. He means to\n"
	.string "raise the land and drink the sea.\p"
	.string "AQUA holds the RED ORB. I am still\n"
	.string "inside. I will stay close to him.”\p"
	.string "{PLAYER} sealed the letter with the\n"
	.string "clan's mark.\p"
	.string "The next traveler bound for the\n"
	.string "mountains would carry it home.$"

PetalburgCity_Text_DraconidWallyDefeat::
	.string "I lost… but I didn't cough once!$"

LilycoveCity_Text_DraconidBrendanDefeat::
	.string "BRENDAN: Tch… Even with two of us?$"

LilycoveCity_Text_DraconidMayDefeat::
	.string "MAY: …Why do you battle like that\n"
	.string "for MAGMA?$"

LilycoveCity_Text_DraconidWallyDefeat::
	.string "Still not enough…$"

MtPyre_Summit_Text_DraconidNerineDefeat::
	.string "…Hm. The mountain listens to you.$"
