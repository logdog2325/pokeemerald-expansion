AquaHideout_B2F_EventScript_DraconidNerine::
	lock
	faceplayer
	call AquaHideout_B2F_EventScript_DraconidNerineBattle
	release
	return


AquaHideout_B2F_EventScript_DraconidNerineStepsIn::
	lockall
	msgbox AquaHideout_B2F_EventScript_DraconidNerineStepsIn_Text_0
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	call AquaHideout_B2F_EventScript_DraconidNerineBattle
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return


AquaHideout_B2F_EventScript_DraconidNerineBattle::
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_0
	msgbox AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_1
	trainerbattle_no_intro TRAINER_NERINE_AQUA_HIDEOUT_DEINO_CHARMANDER, AquaHideout_B2F_Text_DraconidNerineDefeat
	msgbox AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_2
	closemessage
	applymovement LOCALID_AQUA_HIDEOUT_NERINE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_M_DIVE
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_AQUA_HIDEOUT_NERINE
	fadescreen FADE_FROM_BLACK
	msgbox AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_3
	closemessage
	setvar VAR_NERINE_STATE, NERINE_STATE_AQUA_HIDEOUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	return


MossdeepCity_EventScript_DraconidTabithaRaidOrder::
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MossdeepCity_EventScript_DraconidTabithaRaidOrder_Text_0
	closemessage
	return


MossdeepCity_EventScript_DraconidTabithaRaidEnd::
	savebgm MUS_DUMMY
	fadedefaultbgm
	return


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 7
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_2
MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_1:
	applymovement LOCALID_SPACE_CENTER_TABITHA, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_1
	closemessage
	applymovement LOCALID_SPACE_CENTER_TABITHA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_2
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_3
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_4
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_5
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_6
	closemessage
	playfanfare MUS_HEAL
	special HealPlayerParty
	waitfanfare
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_7
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_8
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_9
	closemessage
	call MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle
	goto MossdeepCity_SpaceCenter_2F_EventScript_DefeatedMaxieTabitha
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_2:
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_0
	closemessage
	switch VAR_TEMP_1
	case 5, MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_6
	case 6, MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_7
	case 7, MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_8
	case 8, MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_9
	applymovement LOCALID_PLAYER, MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow9
MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_4:
	waitmovement 0
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_1

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_6:
	applymovement LOCALID_PLAYER, MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow5
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_4

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_7:
	applymovement LOCALID_PLAYER, MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow6
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_4

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_8:
	applymovement LOCALID_PLAYER, MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow7
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_4

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_9:
	applymovement LOCALID_PLAYER, MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow8
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_4


MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle_2:
	compare VAR_RESULT, FALSE
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle_3
	setflag FLAG_DRACONID_NO_WHITEOUT
	multi_2_vs_2 TRAINER_STEVEN_MOSSDEEP, MossdeepCity_SpaceCenter_2F_Text_DraconidStevenDefeat, TRAINER_BRENDAN_MOSSDEEP, MossdeepCity_SpaceCenter_2F_Text_DraconidBrendanDefeat, PARTNER_TABITHA
	clearflag FLAG_DRACONID_NO_WHITEOUT
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle_3:
	special LoadPlayerParty
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle_Text_0
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle_2


MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_2
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_1
MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_1:
	closemessage
	playse SE_PIN
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_2
	closemessage
	applymovement LOCALID_SPACE_CENTER_TABITHA, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_3
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_4
	closemessage
	applymovement LOCALID_SPACE_CENTER_TABITHA, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_5
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_2:
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_0
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_1


MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_2
MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_1:
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_1
	closemessage
	applymovement LOCALID_SPACE_CENTER_2F_BRENDAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SPACE_CENTER_2F_BRENDAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_2
	closemessage
	applymovement LOCALID_SPACE_CENTER_2F_BRENDAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_3
	closemessage
	applymovement LOCALID_SPACE_CENTER_2F_BRENDAN, MossdeepCity_SpaceCenter_2F_Movement_DraconidBrendanStormsOff
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_SPACE_CENTER_2F_BRENDAN
	delay 30
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_4
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_MOSSDEEP
	setvar VAR_MAGMA_STATE, MAGMA_STATE_SPACE_CENTER
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_2:
	msgbox MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_0
	closemessage
	playfanfare MUS_HEAL
	special HealPlayerParty
	waitfanfare
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_1


MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow5:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow6:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow7:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow8:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

MossdeepCity_SpaceCenter_2F_Movement_DraconidJoinTabithaFromRow9:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

MossdeepCity_SpaceCenter_2F_Movement_DraconidBrendanStormsOff:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

SeafloorCavern_Room9_EventScript_DraconidOnTransition::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_NERINE_AQUA
	end


SeafloorCavern_Room9_EventScript_DraconidNerineReveal::
	lockall
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_0
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_1
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_2
	closemessage
	fadeoutbgm 1
	fadescreen FADE_TO_BLACK
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_NERINE
	removeobject LOCALID_SEAFLOOR_CAVERN_NERINE
	clearflag FLAG_HIDE_SEAFLOOR_CAVERN_NERINE
	addobject LOCALID_SEAFLOOR_CAVERN_NERINE
	playse SE_M_DETECT
	delay 30
	fadescreen FADE_FROM_BLACK
	playbgm MUS_ENCOUNTER_INTENSE, FALSE
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_3
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_4
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_5
	trainerbattle_no_intro TRAINER_NERINE_SEAFLOOR_DEINO_CHARMANDER, SeafloorCavern_Room9_Text_DraconidNerineDefeat
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_6
	msgbox SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_7
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SEAFLOOR_CAVERN_NERINE
	fadescreen FADE_FROM_BLACK
	setvar VAR_NERINE_STATE, NERINE_STATE_REVEALED
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end


SootopolisCity_EventScript_DraconidMaxie::
	applymovement LOCALID_SOOTOPOLIS_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	compare VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	goto_if_lt SootopolisCity_EventScript_DraconidMaxie_2
	msgbox SootopolisCity_EventScript_DraconidMaxie_Text_1
SootopolisCity_EventScript_DraconidMaxie_1:
	closemessage
	call SootopolisCity_EventScript_DraconidStandBeforeMaxie
	compare VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	goto_if_lt SootopolisCity_EventScript_DraconidMaxie_6
SootopolisCity_EventScript_DraconidMaxie_5:
	checktrainerflag TRAINER_MAXIE_SOOTOPOLIS
	goto_if 0, SootopolisCity_EventScript_DraconidMaxie_9
SootopolisCity_EventScript_DraconidMaxie_8:
	call SootopolisCity_EventScript_DraconidMultiBattle
	goto SootopolisCity_EventScript_DraconidRayquaza
	return

SootopolisCity_EventScript_DraconidMaxie_2:
	msgbox SootopolisCity_EventScript_DraconidMaxie_Text_0
	goto SootopolisCity_EventScript_DraconidMaxie_1

SootopolisCity_EventScript_DraconidMaxie_6:
	call SootopolisCity_EventScript_DraconidTheTurn
	goto SootopolisCity_EventScript_DraconidMaxie_5

SootopolisCity_EventScript_DraconidMaxie_9:
	trainerbattle_no_intro TRAINER_MAXIE_SOOTOPOLIS, SootopolisCity_Text_DraconidMaxieDefeat
	msgbox SootopolisCity_EventScript_DraconidMaxie_Text_2
	closemessage
	goto SootopolisCity_EventScript_DraconidMaxie_8


SootopolisCity_EventScript_DraconidStandBeforeMaxie::
	switch VAR_FACING
	case DIR_EAST, SootopolisCity_EventScript_DraconidStandBeforeMaxie_3
	case DIR_WEST, SootopolisCity_EventScript_DraconidStandBeforeMaxie_4
	case DIR_SOUTH, SootopolisCity_EventScript_DraconidStandBeforeMaxie_5
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
SootopolisCity_EventScript_DraconidStandBeforeMaxie_1:
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_MAXIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SootopolisCity_EventScript_DraconidStandBeforeMaxie_3:
	applymovement LOCALID_PLAYER, SootopolisCity_Movement_DraconidStandBeforeMaxieFromWest
	goto SootopolisCity_EventScript_DraconidStandBeforeMaxie_1

SootopolisCity_EventScript_DraconidStandBeforeMaxie_4:
	applymovement LOCALID_PLAYER, SootopolisCity_Movement_DraconidStandBeforeMaxieFromEast
	goto SootopolisCity_EventScript_DraconidStandBeforeMaxie_1

SootopolisCity_EventScript_DraconidStandBeforeMaxie_5:
	applymovement LOCALID_PLAYER, SootopolisCity_Movement_DraconidStandBeforeMaxieFromNorth
	goto SootopolisCity_EventScript_DraconidStandBeforeMaxie_1


SootopolisCity_EventScript_DraconidTheTurn::
	msgbox SootopolisCity_EventScript_DraconidTheTurn_Text_0
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	msgbox SootopolisCity_EventScript_DraconidTheTurn_Text_1
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidTheTurn_Text_2
	msgbox SootopolisCity_EventScript_DraconidTheTurn_Text_3
	closemessage
	setvar VAR_0x8004, PLAYER_OUTFIT_DRACONID
	call Draconid_EventScript_ChangeOutfit
	setvar VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	setvar VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	applymovement LOCALID_SOOTOPOLIS_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidTheTurn_Text_4
	msgbox SootopolisCity_EventScript_DraconidTheTurn_Text_5
	msgbox SootopolisCity_EventScript_DraconidTheTurn_Text_6
	return


SootopolisCity_EventScript_DraconidMultiBattle::
	applymovement LOCALID_SOOTOPOLIS_ARCHIE, SootopolisCity_Movement_DraconidArchieJoins
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_0
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_1
	closemessage
	playbgm MUS_ENCOUNTER_MAY, FALSE
	goto_if_set FLAG_HIDE_SOOTOPOLIS_CITY_RIVALS, SootopolisCity_EventScript_DraconidMultiBattle_2
	call SootopolisCity_EventScript_DraconidRivalsStepUp
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_7
SootopolisCity_EventScript_DraconidMultiBattle_1:
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_8
	closemessage
	playfanfare MUS_HEAL
	special HealPlayerParty
	waitfanfare
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_9
	message SootopolisCity_EventScript_DraconidMultiBattle_Text_10
	waitmessage
	dynmultichoice 15, 6, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, SootopolisCity_EventScript_DraconidMultiBattle_Text_11, SootopolisCity_EventScript_DraconidMultiBattle_Text_12
	closemessage
	compare VAR_RESULT, 0
	goto_if_eq SootopolisCity_EventScript_DraconidMultiBattle_6
	setvar VAR_TEMP_2, PARTNER_MAY
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_16
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_17
	closemessage
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, SootopolisCity_Movement_DraconidBrendanToAdmins
	waitmovement 0
	playmoncry SPECIES_SCEPTILE, CRY_MODE_ENCOUNTER
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_18
	waitmoncry
	closemessage
	applymovement LOCALID_SOOTOPOLIS_MAY, SootopolisCity_Movement_DraconidMayToPartner
	waitmovement 0
SootopolisCity_EventScript_DraconidMultiBattle_5:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_19
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
SootopolisCity_EventScript_DraconidMultiBattle_10:
	compare VAR_RESULT, FALSE
	goto_if_eq SootopolisCity_EventScript_DraconidMultiBattle_11
	compare VAR_TEMP_2, PARTNER_BRENDAN
	goto_if_eq SootopolisCity_EventScript_DraconidMultiBattle_14
	multi_2_vs_2 TRAINER_MAXIE_SOOTOPOLIS_MULTI, SootopolisCity_Text_DraconidMaxieMultiDefeat, TRAINER_ARCHIE_SOOTOPOLIS_MULTI, SootopolisCity_Text_DraconidArchieMultiDefeat, PARTNER_MAY
SootopolisCity_EventScript_DraconidMultiBattle_13:
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne SootopolisCity_EventScript_DraconidMultiBattle_19
SootopolisCity_EventScript_DraconidMultiBattle_17:
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_21
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_22
	closemessage
	compare VAR_TEMP_2, PARTNER_BRENDAN
	goto_if_eq SootopolisCity_EventScript_DraconidMultiBattle_23
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, SootopolisCity_Movement_DraconidBrendanBack
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_24
SootopolisCity_EventScript_DraconidMultiBattle_22:
	closemessage
	return

SootopolisCity_EventScript_DraconidMultiBattle_2:
	playse SE_M_FLY
	fadescreen FADE_TO_BLACK
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_RIVALS
	addobject LOCALID_SOOTOPOLIS_BRENDAN
	addobject LOCALID_SOOTOPOLIS_MAY
	delay 20
	fadescreen FADE_FROM_BLACK
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_2
	closemessage
	call SootopolisCity_EventScript_DraconidRivalsStepUp
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_3
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_4
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_5
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_6
	goto SootopolisCity_EventScript_DraconidMultiBattle_1

SootopolisCity_EventScript_DraconidMultiBattle_6:
	setvar VAR_TEMP_2, PARTNER_BRENDAN
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_13
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_14
	closemessage
	applymovement LOCALID_SOOTOPOLIS_MAY, SootopolisCity_Movement_DraconidMayToAdmins
	waitmovement 0
	playmoncry SPECIES_BLAZIKEN, CRY_MODE_ENCOUNTER
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_15
	waitmoncry
	closemessage
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, SootopolisCity_Movement_DraconidBrendanToPartner
	waitmovement 0
	goto SootopolisCity_EventScript_DraconidMultiBattle_5

SootopolisCity_EventScript_DraconidMultiBattle_11:
	special LoadPlayerParty
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_20
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto SootopolisCity_EventScript_DraconidMultiBattle_10

SootopolisCity_EventScript_DraconidMultiBattle_14:
	multi_2_vs_2 TRAINER_MAXIE_SOOTOPOLIS_MULTI, SootopolisCity_Text_DraconidMaxieMultiDefeat, TRAINER_ARCHIE_SOOTOPOLIS_MULTI, SootopolisCity_Text_DraconidArchieMultiDefeat, PARTNER_BRENDAN
	goto SootopolisCity_EventScript_DraconidMultiBattle_13

SootopolisCity_EventScript_DraconidMultiBattle_18:
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	goto SootopolisCity_EventScript_DraconidMultiBattle_17

SootopolisCity_EventScript_DraconidMultiBattle_19:
	goto_if_unset FLAG_DRACONID_NO_WHITEOUT, SootopolisCity_EventScript_DraconidMultiBattle_18
	goto SootopolisCity_EventScript_DraconidMultiBattle_17

SootopolisCity_EventScript_DraconidMultiBattle_23:
	applymovement LOCALID_SOOTOPOLIS_MAY, SootopolisCity_Movement_DraconidMayBack
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidMultiBattle_Text_23
	goto SootopolisCity_EventScript_DraconidMultiBattle_22


SootopolisCity_EventScript_DraconidRivalsStepUp::
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, Common_Movement_WalkUp
	applymovement LOCALID_SOOTOPOLIS_MAY, Common_Movement_WalkUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return


SootopolisCity_EventScript_DraconidRivalTalk::
	lock
	faceplayer
	msgbox SootopolisCity_EventScript_DraconidRivalTalk_Text_0
	release
	return


SootopolisCity_EventScript_DraconidRayquaza::
	fadeoutbgm 1
	playse SE_THUNDER
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 5
	special ShakeCamera
	waitstate
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_0
	closemessage
	fadescreen FADE_TO_BLACK
	delay 30
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_1
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_2
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_3
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_4
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_5
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_6
	closemessage
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox SootopolisCity_EventScript_DraconidRayquaza_Text_7
	closemessage
	setvar VAR_ASTER_STATE, ASTER_STATE_RAYQUAZA_CALLED
	delay 30
	fadescreen FADE_FROM_BLACK
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SootopolisCity_Movement_DraconidPanToLegendaries
	waitmovement 0
	delay 60
	fadescreenspeed FADE_TO_BLACK, 8
	special RemoveCameraObject
	call SootopolisCity_EventScript_SetRoughWater
	removeobject LOCALID_SOOTOPOLIS_GROUDON
	removeobject LOCALID_SOOTOPOLIS_KYOGRE
	addobject LOCALID_SOOTOPOLIS_RAYQUAZA
	hideobjectat LOCALID_SOOTOPOLIS_RAYQUAZA, MAP_SOOTOPOLIS_CITY
	setvar VAR_SOOTOPOLIS_CITY_STATE, 5
	setvar VAR_SKY_PILLAR_STATE, 1
	setvar VAR_0x8004, TRUE
	special Script_DoRayquazaScene
	playse SE_THUNDER
	special SpawnCameraObject
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 3
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 5
	special ShakeCamera
	waitstate
	waitmoncry
	setweather WEATHER_NONE
	doweather
	applymovement LOCALID_SOOTOPOLIS_RAYQUAZA, SootopolisCity_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject LOCALID_SOOTOPOLIS_RAYQUAZA
	special WaitWeather
	clearflag FLAG_SYS_WEATHER_CTRL
	setvar VAR_SKY_PILLAR_STATE, 3
	clearflag FLAG_LEGENDARIES_IN_SOOTOPOLIS
	fadenewbgm MUS_SOOTOPOLIS
	applymovement LOCALID_CAMERA, SootopolisCity_Movement_DraconidPanBackToIsland
	waitmovement 0
	special RemoveCameraObject
	delay 30
	call SootopolisCity_EventScript_DraconidElderCall
	call SootopolisCity_EventScript_DraconidRivalsAftermath
	setvar VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 1
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	warpwhitefade MAP_SOOTOPOLIS_CITY, 31, 34
	waitstate
	releaseall
	end


SootopolisCity_EventScript_DraconidElderCall::
	pokenavcall SootopolisCity_Text_DraconidElderCall
	waitmessage
	closemessage
	return


SootopolisCity_EventScript_DraconidRivalsAftermath::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	compare VAR_TEMP_2, PARTNER_BRENDAN
	goto_if_eq SootopolisCity_EventScript_DraconidRivalsAftermath_2
	applymovement LOCALID_SOOTOPOLIS_MAY, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, Common_Movement_WalkInPlaceFasterUp
SootopolisCity_EventScript_DraconidRivalsAftermath_1:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SootopolisCity_EventScript_DraconidRivalsAftermath_Text_0
	msgbox SootopolisCity_EventScript_DraconidRivalsAftermath_Text_1
	msgbox SootopolisCity_EventScript_DraconidRivalsAftermath_Text_2
	msgbox SootopolisCity_EventScript_DraconidRivalsAftermath_Text_3
	msgbox SootopolisCity_EventScript_DraconidRivalsAftermath_Text_4
	closemessage
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_SOOTOPOLIS
	setvar VAR_MAY_STATE, MAY_STATE_SOOTOPOLIS
	delay 30
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_SOOTOPOLIS_BRENDAN
	waitfieldeffect FLDEFF_NPCFLY_OUT
	delay 20
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_SOOTOPOLIS_MAY
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

SootopolisCity_EventScript_DraconidRivalsAftermath_2:
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SOOTOPOLIS_MAY, Common_Movement_WalkInPlaceFasterUp
	goto SootopolisCity_EventScript_DraconidRivalsAftermath_1


SootopolisCity_EventScript_DraconidSteven::
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_ge SootopolisCity_EventScript_DraconidSteven_2
	compare VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	goto_if_ge SootopolisCity_EventScript_DraconidSteven_3
	msgbox SootopolisCity_EventScript_DraconidSteven_Text_2
SootopolisCity_EventScript_DraconidSteven_1:
	releaseall
	end

SootopolisCity_EventScript_DraconidSteven_2:
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, SootopolisCity_EventScript_DraconidSteven_7
	msgbox SootopolisCity_EventScript_DraconidSteven_Text_0
	goto SootopolisCity_EventScript_DraconidSteven_1

SootopolisCity_EventScript_DraconidSteven_3:
	msgbox SootopolisCity_EventScript_DraconidSteven_Text_1
	goto SootopolisCity_EventScript_DraconidSteven_1

SootopolisCity_EventScript_DraconidSteven_7:
	msgbox SootopolisCity_Text_MaxieArchieLeft, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidSteven_1


SootopolisCity_Movement_DraconidStandBeforeMaxieFromWest:
	walk_down
	walk_right
	face_up
	step_end

SootopolisCity_Movement_DraconidStandBeforeMaxieFromEast:
	walk_down
	walk_left
	face_up
	step_end

SootopolisCity_Movement_DraconidStandBeforeMaxieFromNorth:
	walk_left
	walk_down
	walk_down
	walk_right
	face_up
	step_end

SootopolisCity_Movement_DraconidArchieJoins:
	walk_left
	face_down
	step_end

SootopolisCity_Movement_DraconidMayToAdmins:
	walk_right
	walk_right
	walk_right
	walk_right
	face_right
	step_end

SootopolisCity_Movement_DraconidBrendanToPartner:
	walk_right
	walk_up
	face_up
	step_end

SootopolisCity_Movement_DraconidBrendanToAdmins:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_right
	step_end

SootopolisCity_Movement_DraconidMayToPartner:
	walk_up
	face_up
	step_end

SootopolisCity_Movement_DraconidMayBack:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

SootopolisCity_Movement_DraconidBrendanBack:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_up
	step_end

SootopolisCity_Movement_DraconidPanToLegendaries:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_diag_southeast
	walk_slow_diag_southeast
	step_end

SootopolisCity_Movement_DraconidPanBackToIsland:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_diag_northwest
	walk_diag_northwest
	step_end

AquaHideout_B2F_EventScript_DraconidNerineStepsIn_Text_0:
	.string "NERINE: Leave MATT alone. He's only\n"
	.string "stalling you.$"

AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_0:
	.string "NERINE: MAXIE sent you after ARCHIE.\n"
	.string "Of course he did.\p"
	.string "His favorite grunt, sneaking through\n"
	.string "the enemy's base…\p"
	.string "You look tired of that red, {PLAYER}. I\n"
	.string "know the feeling.$"

AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_1:
	.string "NERINE: One more battle. Then we both\n"
	.string "go where we're needed.$"

AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_2:
	.string "NERINE: ARCHIE is taking the submarine\n"
	.string "down. Deep, where the sea is darkest.\p"
	.string "I'll be aboard. Someone has to be close\n"
	.string "when he does something foolish.\p"
	.string "Soon, neither of us will need a borrowed\n"
	.string "uniform.\p"
	.string "Follow the sea, {PLAYER}. And don't keep\n"
	.string "the sky waiting.$"

AquaHideout_B2F_EventScript_DraconidNerineBattle_Text_3:
	.string "NERINE dove into the water and swam\n"
	.string "for the submarine.$"

MossdeepCity_EventScript_DraconidTabithaRaidOrder_Text_0:
	.string "TABITHA: Hehehe! There you are,\n"
	.string "{PLAYER}!\p"
	.string "Leader MAXIE is busy chasing after\n"
	.string "GROUDON. So today, this squad is mine.\p"
	.string "The SPACE CENTER keeps rocket fuel.\n"
	.string "Lots of it. We're taking every last drop.\p"
	.string "Follow us in. And try to look like you're\n"
	.string "enjoying it. Hehehe!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_0:
	.string "TABITHA: Hehehe! Over here, grunt!\n"
	.string "Quick!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_1:
	.string "TABITHA: Look who's guarding the fuel.\n"
	.string "The CHAMPION of HOENN himself… and\l"
	.string "some kid.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_2:
	.string "BRENDAN: {PLAYER}… Figures.\n"
	.string "Wherever MAGMA goes, you go.\p"
	.string "I came to help STEVEN protect\n"
	.string "this place.\p"
	.string "And you're here to steal rocket\n"
	.string "fuel for MAGMA?!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_3:
	.string "STEVEN: TABITHA. What does MAGMA want\n"
	.string "with rocket fuel?$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_4:
	.string "TABITHA: Hehehe! Since you asked so\n"
	.string "nicely…\p"
	.string "We're going to dump every drop into MT.\n"
	.string "CHIMNEY.\p"
	.string "The mountain wakes up, the lava flows,\n"
	.string "and the land grows. Leader MAXIE's\l"
	.string "dream!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_5:
	.string "STEVEN: Then the fuel stays here.\p"
	.string "…{PLAYER}{KUN}. We meet again.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_6:
	.string "TABITHA: Two against two, then. Here,\n"
	.string "grunt. Don't embarrass me.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_7:
	.string "TABITHA healed {PLAYER}'s POKéMON.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_8:
	.string "STEVEN: BRENDAN, with me.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid_Text_9:
	.string "BRENDAN: Right behind you!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle_Text_0:
	.string "TABITHA: Well? Pick your POKéMON,\n"
	.string "grunt!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_0:
	.string "TABITHA: Hehehe! The CHAMPION, beaten!\p"
	.string "Out of the way, STEVEN. The fuel is\n"
	.string "ours!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_1:
	.string "TABITHA: Tch! Useless grunt!\p"
	.string "…Fine. I'll take the fuel myself!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_2:
	.string "SCIENTIST: STEVEN! We did it! The fuel\n"
	.string "tanks are sealed!\p"
	.string "We locked them down while they were\n"
	.string "battling. Nobody can open them now. Not\l"
	.string "even us!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_3:
	.string "TABITHA: Sealed?! While we were…\n"
	.string "battling?!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_4:
	.string "STEVEN: The fuel stays where it is,\n"
	.string "TABITHA.\p"
	.string "And so do the people who work here.\n"
	.string "They're behind me.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidFuelSealed_Text_5:
	.string "TABITHA: …You kept them busy a long\n"
	.string "time, grunt.\p"
	.string "Long enough for this. …Hmph.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_0:
	.string "STEVEN: Your POKéMON fought hard. Let\n"
	.string "them rest.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_1:
	.string "STEVEN: …{PLAYER}{KUN}. A word, quietly.\p"
	.string "Those tanks take time to seal. Someone\n"
	.string "kept TABITHA busy long enough.\p"
	.string "I know you let us win the important\n"
	.string "part.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_2:
	.string "BRENDAN: LET us?! STEVEN, you saw it\n"
	.string "yourself! {PLAYER} battled for MAGMA!$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_3:
	.string "BRENDAN: I don't care what you “let”\n"
	.string "happen, {PLAYER}.\p"
	.string "You were right there with MAGMA again!\p"
	.string "That's it. I give up trying to\n"
	.string "figure you out.$"

MossdeepCity_SpaceCenter_2F_EventScript_DraconidStevenAndBrendan_Text_4:
	.string "STEVEN: He'll understand one day. I\n"
	.string "hope you'll let him.$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_0:
	.string "NERINE: You found the way down. I knew\n"
	.string "you would.$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_1:
	.string "NERINE: ARCHIE is below us, with the\n"
	.string "RED ORB. KYOGRE sleeps under his feet.\p"
	.string "Before you go down there… no more\n"
	.string "games. Not between us.$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_2:
	.string "NERINE pulled the bandana from her hair\n"
	.string "and let the AQUA uniform fall away…$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_3:
	.string "NERINE: My name really is NERINE. That\n"
	.string "part was never a lie.\p"
	.string "I'm DRACONID, like you. The ELDER sent\n"
	.string "me down the mountain years ago.\p"
	.string "Into AQUA, to watch ARCHIE… and, when\n"
	.string "your time came, to watch you.$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_4:
	.string "NERINE: The ELDER sent me to test you.\n"
	.string "You passed…\p"
	.string "…almost.$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_5:
	.string "NERINE: One more battle, {PLAYER}. No\n"
	.string "disguises this time.\p"
	.string "Show me everything the ELDER saw in\n"
	.string "you!$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_6:
	.string "NERINE: …The ELDER chose well. I'll tell\n"
	.string "him so myself.\p"
	.string "ARCHIE will wake KYOGRE. I can't stop\n"
	.string "that, and neither can you.\p"
	.string "When it happens, MAXIE will call for you.\n"
	.string "He trusts you more than anyone.\p"
	.string "And then you'll have to choose,\n"
	.string "{PLAYER}. The red… or the sky.$"

SeafloorCavern_Room9_EventScript_DraconidNerineReveal_Text_7:
	.string "NERINE: I have somewhere to be.\n"
	.string "Somewhere high.\p"
	.string "ASTER is waiting for me there. She'll\n"
	.string "pretend she isn't worried about you.$"

SootopolisCity_EventScript_DraconidMaxie_Text_0:
	.string "MAXIE: {PLAYER}.\n"
	.string "You came, as I knew you would.\p"
	.string "Stand here with me.\n"
	.string "I want you to see this.$"

SootopolisCity_EventScript_DraconidMaxie_Text_1:
	.string "MAXIE: You again. Have you come to beg\n"
	.string "for your place back, or to finish this?$"

SootopolisCity_EventScript_DraconidMaxie_Text_2:
	.string "MAXIE: Humph… Beaten by a child who\n"
	.string "wore my own colors.$"

SootopolisCity_EventScript_DraconidTheTurn_Text_0:
	.string "MAXIE: Look at them, {PLAYER}. KYOGRE\n"
	.string "would drown the world, and only GROUDON\l"
	.string "stands against it.\p"
	.string "The BLUE ORB failed me once. This time,\n"
	.string "with your help, I will bring GROUDON\l"
	.string "under control.\p"
	.string "When the rain ends, we will shape the\n"
	.string "land together. Our ideal world, {PLAYER}!$"

SootopolisCity_EventScript_DraconidTheTurn_Text_1:
	.string "{PLAYER} looked out at GROUDON and\n"
	.string "KYOGRE, tearing at each other in the\l"
	.string "storm…\p"
	.string "…and remembered the ELDER's words.\p"
	.string "“When the sky splits, you must stand\n"
	.string "beside RAYQUAZA.”$"

SootopolisCity_EventScript_DraconidTheTurn_Text_2:
	.string "MAXIE: {PLAYER}?\n"
	.string "What are you waiting for?$"

SootopolisCity_EventScript_DraconidTheTurn_Text_3:
	.string "{PLAYER} pulled off the red hood…\p"
	.string "…and let the TEAM MAGMA uniform fall to\n"
	.string "the ground.$"

SootopolisCity_EventScript_DraconidTheTurn_Text_4:
	.string "MAXIE: Those colors… I know them.\n"
	.string "You are one of the DRACONID.\p"
	.string "So you were never truly one of us.$"

SootopolisCity_EventScript_DraconidTheTurn_Text_5:
	.string "MAXIE: After everything I gave you?!\p"
	.string "I trusted you with my plans. I made you\n"
	.string "my right hand!$"

SootopolisCity_EventScript_DraconidTheTurn_Text_6:
	.string "MAXIE: Very well. I will take GROUDON\n"
	.string "without you.\p"
	.string "But first, I will deal with the traitor in\n"
	.string "my ranks!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_0:
	.string "ARCHIE: Fufufu! MAXIE's own grunt,\n"
	.string "turning on him! Now that's a show.\p"
	.string "But don't get cocky, kid. KYOGRE is still\n"
	.string "mine to take.$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_1:
	.string "MAXIE: For once, ARCHIE,\n"
	.string "we agree on something.\p"
	.string "This child stands in both our ways.$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_2:
	.string "???: {PLAYER}!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_3:
	.string "MAY: We saw everything from the sky!\n"
	.string "You threw that uniform away right in\l"
	.string "front of MAXIE!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_4:
	.string "BRENDAN: {PLAYER}… Just who ARE you?$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_5:
	.string "MAY: Save it for later, BRENDAN! Two\n"
	.string "against one isn't fair.\p"
	.string "{PLAYER}, one of us will fight with you!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_6:
	.string "BRENDAN: Their ADMINS are crossing the\n"
	.string "water, too.\p"
	.string "Whoever doesn't fight here has to hold\n"
	.string "them back.$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_7:
	.string "MAY: {PLAYER}, you're back! We kept them\n"
	.string "busy for you.\p"
	.string "Let's try that again!\n"
	.string "Who's your partner?$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_8:
	.string "MAY: But first, your POKéMON look worn\n"
	.string "out. Hold still!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_9:
	.string "{PLAYER}'s POKéMON were fully healed!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_10:
	.string "Who will fight beside {PLAYER}?$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_11:
	.string "BRENDAN$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_12:
	.string "MAY$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_13:
	.string "BRENDAN: Me? After all the things I\n"
	.string "said to you?\p"
	.string "…All right. Let's go, {PLAYER}!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_14:
	.string "MAY: Then the ADMINS are mine!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_15:
	.string "MAY: BLAZIKEN!\n"
	.string "Keep them off the island!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_16:
	.string "MAY: I was hoping you'd say that!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_17:
	.string "BRENDAN: Then I'll take the ADMINS.\n"
	.string "Don't you dare lose, {PLAYER}!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_18:
	.string "BRENDAN: SCEPTILE, nobody lands on\n"
	.string "this island!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_19:
	.string "ARCHIE: Two kids against the leaders of\n"
	.string "MAGMA and AQUA? Fufufu… Bring it on!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_20:
	.string "Choose the POKéMON that will battle\n"
	.string "beside your partner!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_21:
	.string "MAXIE: The land is slipping\n"
	.string "through my fingers…$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_22:
	.string "ARCHIE: KYOGRE won't even look at the\n"
	.string "RED ORB anymore…$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_23:
	.string "MAY: Their ADMINS ran off! And you two\n"
	.string "beat MAXIE and ARCHIE!$"

SootopolisCity_EventScript_DraconidMultiBattle_Text_24:
	.string "BRENDAN: The ADMINS turned tail! And\n"
	.string "you two actually beat them!$"

SootopolisCity_EventScript_DraconidRivalTalk_Text_0:
	.string "MAY: We're right here, {PLAYER}. Talk to\n"
	.string "MAXIE when you're ready!$"

SootopolisCity_EventScript_DraconidRayquaza_Text_0:
	.string "Thunder split the sky over SOOTOPOLIS…$"

SootopolisCity_EventScript_DraconidRayquaza_Text_1:
	.string "Far away, at the SKY PILLAR…$"

SootopolisCity_EventScript_DraconidRayquaza_Text_2:
	.string "ASTER: The storm reaches all the way\n"
	.string "out here. Look at that sky.$"

SootopolisCity_EventScript_DraconidRayquaza_Text_3:
	.string "NERINE: Then there's no more time to\n"
	.string "wait. The ELDER's words, ASTER. Every\l"
	.string "one of them.$"

SootopolisCity_EventScript_DraconidRayquaza_Text_4:
	.string "ASTER: I know the words. I've known\n"
	.string "them since I was six.\p"
	.string "…{PLAYER} held the line down there.\n"
	.string "Hmph. Not bad, for a red coat.$"

SootopolisCity_EventScript_DraconidRayquaza_Text_5:
	.string "NERINE: Not red anymore, I think.$"

SootopolisCity_EventScript_DraconidRayquaza_Text_6:
	.string "ASTER and NERINE raised their voices to\n"
	.string "the sky, together…$"

SootopolisCity_EventScript_DraconidRayquaza_Text_7:
	.string "Something vast answered from above\n"
	.string "the clouds.$"

SootopolisCity_EventScript_DraconidRivalsAftermath_Text_0:
	.string "MAY: Did you see that? That was\n"
	.string "RAYQUAZA! A real, live RAYQUAZA!\p"
	.string "And you were a DRACONID, undercover in\n"
	.string "TEAM MAGMA this whole time!\p"
	.string "I KNEW it! I knew it, I knew it, I KNEW it!\p"
	.string "Nobody who raises dragons like yours\n"
	.string "could ever be one of THEM.$"

SootopolisCity_EventScript_DraconidRivalsAftermath_Text_1:
	.string "BRENDAN: Hey, {PLAYER}… About the\n"
	.string "things I said in RUSTBORO and MOSSDEEP.\p"
	.string "I was wrong about you, okay? I'm sorry.\p"
	.string "…Don't make me say that twice.$"

SootopolisCity_EventScript_DraconidRivalsAftermath_Text_2:
	.string "MAY: Hehe! He practiced that the whole\n"
	.string "way here.$"

SootopolisCity_EventScript_DraconidRivalsAftermath_Text_3:
	.string "BRENDAN: I did NOT!$"

SootopolisCity_EventScript_DraconidRivalsAftermath_Text_4:
	.string "MAY: We're going home to tell our\n"
	.string "dads everything!\p"
	.string "{PLAYER}, come visit LITTLEROOT\n"
	.string "when you can!$"

SootopolisCity_EventScript_DraconidSteven_Text_0:
	.string "STEVEN: So that's RAYQUAZA…\p"
	.string "It's incredible how the two rampaging\n"
	.string "POKéMON fled from it.\p"
	.string "And you, {PLAYER}{KUN}. I've wondered about\n"
	.string "you ever since GRANITE CAVE.\p"
	.string "I'm glad I was right.$"

SootopolisCity_EventScript_DraconidSteven_Text_1:
	.string "STEVEN: I saw you throw off that\n"
	.string "uniform, {PLAYER}{KUN}. From all the way over\l"
	.string "here.\p"
	.string "Go on. MAXIE is still waiting on the\n"
	.string "island.$"

SootopolisCity_EventScript_DraconidSteven_Text_2:
	.string "STEVEN: {PLAYER}{KUN}… MAXIE is on the\n"
	.string "island in front of the GYM.\p"
	.string "He was asking whether anyone had seen\n"
	.string "you.\p"
	.string "I don't know what he wants from you. I\n"
	.string "think you do.\p"
	.string "Whatever you really are, {PLAYER}{KUN}… this\n"
	.string "is the moment to show it.$"

AquaHideout_B2F_Text_DraconidNerineDefeat::
	.string "There it is again. That look of yours.\n"
	.string "Mountain air.$"

MossdeepCity_SpaceCenter_2F_Text_DraconidStevenDefeat::
	.string "STEVEN: Well fought. …Both of you.$"

MossdeepCity_SpaceCenter_2F_Text_DraconidBrendanDefeat::
	.string "BRENDAN: Why waste strength like that\n"
	.string "on THEM?!$"

SeafloorCavern_Room9_Text_DraconidNerineDefeat::
	.string "So this is what the ELDER saw in you.$"

SootopolisCity_Text_DraconidMaxieDefeat::
	.string "Impossible! I, MAXIE, beaten\n"
	.string "by my own recruit?!$"

SootopolisCity_Text_DraconidMaxieMultiDefeat::
	.string "This cannot be happening…$"

SootopolisCity_Text_DraconidArchieMultiDefeat::
	.string "Blast it! Beaten by a pack of kids!$"

SootopolisCity_Text_DraconidElderCall::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "ELDER: {PLAYER}. It is the ELDER.\p"
	.string "I felt it from the mountain. The\n"
	.string "sky has answered.\p"
	.string "ASTER and NERINE called from the\n"
	.string "SKY PILLAR, and RAYQUAZA came\l"
	.string "down to quiet the old ones.\p"
	.string "ASTER: We did. And tell {PLAYER} I\n"
	.string "never liked that red uniform\l"
	.string "anyway.\p"
	.string "NERINE: Tell {PLAYER} well done. No\n"
	.string "“almost” this time.\p"
	.string "ELDER: Hush, both of you.\p"
	.string "{PLAYER}, hear me. RAYQUAZA has\n"
	.string "gone back to its tower.\p"
	.string "It isn't time yet. The sky will tell\n"
	.string "us when.\p"
	.string "Until then, walk your own road. You\n"
	.string "need no borrowed colors now.\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"
