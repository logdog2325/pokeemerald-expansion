BattleFrontier_OutsideEast_EventScript_DraconidLegends::
	goto_if_set FLAG_SYS_GAME_CLEAR, BattleFrontier_OutsideEast_EventScript_DraconidLegends_2
	setflag FLAG_HIDE_BATTLE_FRONTIER_WES
	setflag FLAG_HIDE_BATTLE_FRONTIER_RED
	setflag FLAG_HIDE_BATTLE_FRONTIER_BLUE
BattleFrontier_OutsideEast_EventScript_DraconidLegends_1:
	return

BattleFrontier_OutsideEast_EventScript_DraconidLegends_2:
	clearflag FLAG_HIDE_BATTLE_FRONTIER_WES
	clearflag FLAG_HIDE_BATTLE_FRONTIER_RED
	clearflag FLAG_HIDE_BATTLE_FRONTIER_BLUE
	goto BattleFrontier_OutsideEast_EventScript_DraconidLegends_1


BattleFrontier_OutsideEast_EventScript_DraconidWes::
	lock
	faceplayer
	checktrainerflag TRAINER_WES_FRONTIER
	goto_if 1, BattleFrontier_OutsideEast_EventScript_DraconidWes_2
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_3
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_4, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidWes_5
	msgbox BattleFrontier_OutsideEast_Text_DraconidWesGo
	trainerbattle_no_intro TRAINER_WES_FRONTIER, BattleFrontier_OutsideEast_Text_DraconidWesDefeat
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_6
	release
	return

BattleFrontier_OutsideEast_EventScript_DraconidWes_2:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidWes_8
	msgbox BattleFrontier_OutsideEast_Text_DraconidWesGo
	trainerbattle_no_intro TRAINER_WES_FRONTIER, BattleFrontier_OutsideEast_Text_DraconidWesDefeat
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_2
	release
	end

BattleFrontier_OutsideEast_EventScript_DraconidWes_5:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_5
	release
	end

BattleFrontier_OutsideEast_EventScript_DraconidWes_8:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_1
	release
	end


BattleFrontier_OutsideEast_EventScript_DraconidRed::
	lock
	faceplayer
	checktrainerflag TRAINER_RED_FRONTIER
	goto_if 1, BattleFrontier_OutsideEast_EventScript_DraconidRed_2
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_3
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_4, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidRed_5
	msgbox BattleFrontier_OutsideEast_Text_DraconidRedGo
	trainerbattle_no_intro TRAINER_RED_FRONTIER, BattleFrontier_OutsideEast_Text_DraconidRedDefeat
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_5
	release
	return

BattleFrontier_OutsideEast_EventScript_DraconidRed_2:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidRed_8
	msgbox BattleFrontier_OutsideEast_Text_DraconidRedGo
	trainerbattle_no_intro TRAINER_RED_FRONTIER, BattleFrontier_OutsideEast_Text_DraconidRedDefeat
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_2
	release
	end

BattleFrontier_OutsideEast_EventScript_DraconidRed_5:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	release
	end

BattleFrontier_OutsideEast_EventScript_DraconidRed_8:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	release
	end


BattleFrontier_OutsideEast_EventScript_DraconidBlue::
	lock
	faceplayer
	checktrainerflag TRAINER_BLUE_FRONTIER
	goto_if 1, BattleFrontier_OutsideEast_EventScript_DraconidBlue_2
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_4
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_5
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_6, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidBlue_5
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_8
	trainerbattle_no_intro TRAINER_BLUE_FRONTIER, BattleFrontier_OutsideEast_Text_DraconidBlueDefeat
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_9
	release
	return

BattleFrontier_OutsideEast_EventScript_DraconidBlue_2:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidBlue_8
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_2
	trainerbattle_no_intro TRAINER_BLUE_FRONTIER, BattleFrontier_OutsideEast_Text_DraconidBlueDefeat
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_3
	release
	end

BattleFrontier_OutsideEast_EventScript_DraconidBlue_5:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_7
	release
	end

BattleFrontier_OutsideEast_EventScript_DraconidBlue_8:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_1
	release
	end


BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant::
	lockall
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_2
	checktrainerflag TRAINER_WES_FRONTIER
	goto_if 0, BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_7
BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_4:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_12
	message BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_3
	waitmessage
	checktrainerflag TRAINER_WES_FRONTIER
	goto_if 1, BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_15
BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_14:
	checktrainerflag TRAINER_RED_FRONTIER
	goto_if 1, BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_18
BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_17:
	checktrainerflag TRAINER_BLUE_FRONTIER
	goto_if 1, BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_21
BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_20:
	dynmultipush BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_7, MULTI_B_PRESSED
	dynmultistack 19, 6, FALSE, 4, FALSE, PARTNER_WES, DYN_MULTICHOICE_CB_NONE
	closemessage
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_24
	copyvar VAR_TEMP_1, VAR_RESULT
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_8
	closemessage
	playfanfare MUS_HEAL
	special HealPlayerParty
	waitfanfare
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_9
	closemessage
	call BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat
	call BattleFrontier_OutsideEast_EventScript_DraconidTagBattle
	releaseall
	return

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_2:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_0
	releaseall
	end

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_5:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_1
	releaseall
	end

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_6:
	checktrainerflag TRAINER_BLUE_FRONTIER
	goto_if 0, BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_5
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_4

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_7:
	checktrainerflag TRAINER_RED_FRONTIER
	goto_if 0, BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_6
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_4

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_12:
	msgbox BattleFrontier_OutsideEast_Text_DraconidTagComeAgain
	releaseall
	end

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_15:
	dynmultipush BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_4, PARTNER_WES
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_14

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_18:
	dynmultipush BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_5, PARTNER_RED
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_17

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_21:
	dynmultipush BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_6, PARTNER_BLUE
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_20

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_24:
	msgbox BattleFrontier_OutsideEast_Text_DraconidTagComeAgain
	releaseall
	end


BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat::
	getplayerxy VAR_TEMP_2, VAR_TEMP_3
	switch VAR_TEMP_2
	case 13, BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat_3
	case 15, BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat_4
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideEast_Movement_DraconidTagFromBelow
BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat_1:
	waitmovement 0
	return

BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat_3:
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideEast_Movement_DraconidTagFromLeft
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat_1

BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat_4:
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideEast_Movement_DraconidTagFromRight
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagWalkToMat_1


BattleFrontier_OutsideEast_Movement_DraconidTagFromLeft:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_right
	face_up
	step_end

BattleFrontier_OutsideEast_Movement_DraconidTagFromRight:
	walk_down
	walk_down
	walk_down
	face_up
	step_end

BattleFrontier_OutsideEast_Movement_DraconidTagFromBelow:
	walk_down
	walk_down
	walk_right
	face_up
	step_end

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle::
	fadescreen FADE_TO_BLACK
	switch VAR_TEMP_1
	case PARTNER_WES, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_3
	case PARTNER_RED, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_4
	setvar VAR_0x8004, LOCALID_FRONTIER_BLUE
	call BattleFrontier_OutsideEast_EventScript_DraconidTagPartnerSpot
	setvar VAR_0x8004, LOCALID_FRONTIER_WES
	call BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentASpot
	setvar VAR_0x8004, LOCALID_FRONTIER_RED
	call BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentBSpot
BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_1:
	delay 20
	fadescreen FADE_FROM_BLACK
	switch VAR_TEMP_1
	case PARTNER_WES, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_8
	case PARTNER_RED, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_9
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_5
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_6
BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_6:
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_12:
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_13
	switch VAR_TEMP_1
	case PARTNER_WES, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_17
	case PARTNER_RED, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_18
	multi_2_vs_2 TRAINER_WES_FRONTIER_MULTI, BattleFrontier_OutsideEast_Text_DraconidWesTagDefeat, TRAINER_RED_FRONTIER_MULTI, BattleFrontier_OutsideEast_Text_DraconidRedTagDefeat, PARTNER_BLUE
BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_15:
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_22
BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_20:
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_26
	switch VAR_TEMP_1
	case PARTNER_WES, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_34
	case PARTNER_RED, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_35
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_12
BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_25:
	closemessage
	fadescreen FADE_TO_BLACK
	call BattleFrontier_OutsideEast_EventScript_DraconidTagSendHome
	fadescreen FADE_FROM_BLACK
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_13
	return

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_3:
	setvar VAR_0x8004, LOCALID_FRONTIER_WES
	call BattleFrontier_OutsideEast_EventScript_DraconidTagPartnerSpot
	setvar VAR_0x8004, LOCALID_FRONTIER_RED
	call BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentASpot
	setvar VAR_0x8004, LOCALID_FRONTIER_BLUE
	call BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentBSpot
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_1

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_4:
	setvar VAR_0x8004, LOCALID_FRONTIER_RED
	call BattleFrontier_OutsideEast_EventScript_DraconidTagPartnerSpot
	setvar VAR_0x8004, LOCALID_FRONTIER_WES
	call BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentASpot
	setvar VAR_0x8004, LOCALID_FRONTIER_BLUE
	call BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentBSpot
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_1

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_8:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_1
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_6

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_9:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_2
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_3
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_4
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_6

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_13:
	special LoadPlayerParty
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_7
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_12

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_17:
	multi_2_vs_2 TRAINER_RED_FRONTIER_MULTI, BattleFrontier_OutsideEast_Text_DraconidRedTagDefeat, TRAINER_BLUE_FRONTIER_MULTI, BattleFrontier_OutsideEast_Text_DraconidBlueTagDefeat, PARTNER_WES
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_15

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_18:
	multi_2_vs_2 TRAINER_WES_FRONTIER_MULTI, BattleFrontier_OutsideEast_Text_DraconidWesTagDefeat, TRAINER_BLUE_FRONTIER_MULTI, BattleFrontier_OutsideEast_Text_DraconidBlueTagDefeat, PARTNER_RED
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_15

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_21:
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagWhiteOut
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_20

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_22:
	goto_if_unset FLAG_DRACONID_NO_WHITEOUT, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_21
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_20

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_26:
	switch VAR_TEMP_1
	case PARTNER_WES, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_30
	case PARTNER_RED, BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_31
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_10
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_25

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_30:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_8
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_25

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_31:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_9
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_25

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_34:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_11
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_25

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_35:
	msgbox BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0
	goto BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_25


BattleFrontier_OutsideEast_EventScript_DraconidTagWhiteOut::
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	end


BattleFrontier_OutsideEast_EventScript_DraconidTagPartnerSpot::
	setobjectxyperm VAR_0x8004, 16, 18
	setobjectxy VAR_0x8004, 16, 18
	addobject VAR_0x8004
	turnobject VAR_0x8004, DIR_NORTH
	return


BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentASpot::
	setobjectxyperm VAR_0x8004, 15, 16
	setobjectxy VAR_0x8004, 15, 16
	addobject VAR_0x8004
	turnobject VAR_0x8004, DIR_SOUTH
	return


BattleFrontier_OutsideEast_EventScript_DraconidTagOpponentBSpot::
	setobjectxyperm VAR_0x8004, 16, 16
	setobjectxy VAR_0x8004, 16, 16
	addobject VAR_0x8004
	turnobject VAR_0x8004, DIR_SOUTH
	return


BattleFrontier_OutsideEast_EventScript_DraconidTagSendHome::
	setobjectxyperm LOCALID_FRONTIER_WES, 58, 22
	setobjectxy LOCALID_FRONTIER_WES, 58, 22
	turnobject LOCALID_FRONTIER_WES, DIR_SOUTH
	setobjectxyperm LOCALID_FRONTIER_RED, 29, 10
	setobjectxy LOCALID_FRONTIER_RED, 29, 10
	turnobject LOCALID_FRONTIER_RED, DIR_SOUTH
	setobjectxyperm LOCALID_FRONTIER_BLUE, 18, 15
	setobjectxy LOCALID_FRONTIER_BLUE, 18, 15
	turnobject LOCALID_FRONTIER_BLUE, DIR_SOUTH
	return


BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_0:
	.string "WES: …Again?$"

BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_1:
	.string "WES: …Suit yourself.$"

BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_2:
	.string "WES: …Good battle. You know where to\n"
	.string "find me.$"

BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_3:
	.string "WES: …\p"
	.string "You're the one who wore the red uniform.\n"
	.string "MAGMA.\p"
	.string "I ran with a gang once, too. Team\n"
	.string "SNAGEM, out in ORRE.\p"
	.string "Walked out on them one night. Took\n"
	.string "their best machine with me.$"

BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_4:
	.string "WES: SCOTT says you're the best\n"
	.string "TRAINER in HOENN.\p"
	.string "…Show me.$"

BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_5:
	.string "WES: …Suit yourself. I'm not going\n"
	.string "anywhere.$"

BattleFrontier_OutsideEast_EventScript_DraconidWes_Text_6:
	.string "WES: You fight like someone with\n"
	.string "something to protect.\p"
	.string "…The attendant by the BATTLE TOWER\n"
	.string "door sets up tag battles.\p"
	.string "If you ever need a partner, I'm around.$"

BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_0:
	.string "RED: …$"

BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_1:
	.string "Battle RED again?$"

BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_2:
	.string "RED gave a small nod.$"

BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_3:
	.string "RED is looking at {PLAYER}'s POKéMON.\p"
	.string "…He seems to want a battle.$"

BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_4:
	.string "Battle RED?$"

BattleFrontier_OutsideEast_EventScript_DraconidRed_Text_5:
	.string "RED looked over at the BATTLE TOWER,\n"
	.string "then back at {PLAYER}.\p"
	.string "…It seems he'd team up with you.$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_0:
	.string "BLUE: Back for more? I've been itching\n"
	.string "for a rematch!$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_1:
	.string "BLUE: Tch. Fine. Smell ya later!$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_2:
	.string "BLUE: This time I win for real!$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_3:
	.string "BLUE: Tch… Next time, for sure. Smell ya\n"
	.string "later!$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_4:
	.string "BLUE: Hey! You're {PLAYER}, right?\n"
	.string "Everybody here keeps talking about\l"
	.string "you.\p"
	.string "Wore a MAGMA uniform, then threw it off\n"
	.string "right in front of their boss. Ha! Gutsy.$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_5:
	.string "BLUE: I'm BLUE. I was the CHAMPION of\n"
	.string "KANTO.\p"
	.string "…For about five minutes. Then RED\n"
	.string "showed up. Don't ask.$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_6:
	.string "BLUE: SCOTT says you're the toughest\n"
	.string "TRAINER in HOENN.\p"
	.string "Well? Think you can take on the best in\n"
	.string "KANTO?$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_7:
	.string "BLUE: Heh. Scared? I'll be right here\n"
	.string "when you're ready.$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_8:
	.string "BLUE: That's more like it! Let's go!$"

BattleFrontier_OutsideEast_EventScript_DraconidBlue_Text_9:
	.string "BLUE: Alright, alright. You're the real\n"
	.string "deal.\p"
	.string "Hey, that attendant by the door runs\n"
	.string "tag battles. Two on two.\p"
	.string "You and me on the same side? Nobody'd\n"
	.string "stand a chance. Smell ya later!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_0:
	.string "Our special guests haven't arrived yet.\n"
	.string "Please come back another time!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_1:
	.string "Welcome to the LEGENDS' TAG!\p"
	.string "SCOTT has invited three legendary\n"
	.string "TRAINERS to the BATTLE FRONTIER.\p"
	.string "WES from the ORRE region, and RED and\n"
	.string "BLUE from KANTO.\p"
	.string "Win a battle against one of them, and\n"
	.string "they may agree to team up with you.\p"
	.string "Then the two of you take on the other\n"
	.string "two in a multi battle!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_2:
	.string "Welcome to the LEGENDS' TAG!\p"
	.string "Would you like to team up with a legend?$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_3:
	.string "Which TRAINER will be your partner?$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_4:
	.string "WES$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_5:
	.string "RED$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_6:
	.string "BLUE$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_7:
	.string "CANCEL$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_8:
	.string "Your POKéMON will be restored first.$"

BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant_Text_9:
	.string "Now, please take your place on the mat\n"
	.string "in front of the TOWER!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_0:
	.string "BLUE: Heh! RED and me on the same side\n"
	.string "for once. You two don't stand a chance!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_1:
	.string "WES: …Stay sharp, {PLAYER}.$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_2:
	.string "BLUE: So I'm stuck with Mr. Sunglasses.\n"
	.string "Fine! Let's finally beat RED!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_3:
	.string "WES: …Just don't get in my way.$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_4:
	.string "RED: …!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_5:
	.string "BLUE: Alright, {PLAYER}! You and me.\n"
	.string "Let's show RED who's boss!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_6:
	.string "WES: …Let's go.$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_7:
	.string "Choose the POKéMON that will battle\n"
	.string "beside your partner!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_8:
	.string "WES: …Not bad. We make a good team.$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_9:
	.string "RED gave {PLAYER} a quiet thumbs-up.$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_10:
	.string "BLUE: Ha! Did you see that?! Smell ya\n"
	.string "later, you two!$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_11:
	.string "WES: …We'll get them next time.$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_12:
	.string "BLUE: Tch! Next time we win, got it?$"

BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_Text_13:
	.string "What a battle! The LEGENDS' TAG is open\n"
	.string "any time.$"

BattleFrontier_OutsideEast_Text_DraconidWesGo::
	.string "WES: ESPEON. UMBREON. We're up.$"

BattleFrontier_OutsideEast_Text_DraconidWesDefeat::
	.string "WES: …Heh. Not bad.$"

BattleFrontier_OutsideEast_Text_DraconidRedGo::
	.string "RED: …!$"

BattleFrontier_OutsideEast_Text_DraconidRedDefeat::
	.string "…$"

BattleFrontier_OutsideEast_Text_DraconidBlueDefeat::
	.string "BLUE: What?! No way… I picked the wrong\n"
	.string "POKéMON again, didn't I?$"

BattleFrontier_OutsideEast_Text_DraconidTagComeAgain::
	.string "Please come again!$"

BattleFrontier_OutsideEast_Text_DraconidWesTagDefeat::
	.string "WES: …Tch. Good teamwork.$"

BattleFrontier_OutsideEast_Text_DraconidRedTagDefeat::
	.string "RED: …$"

BattleFrontier_OutsideEast_Text_DraconidBlueTagDefeat::
	.string "BLUE: Two on two, and I STILL lose?!$"
