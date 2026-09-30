LilycoveCity_EventScript_DraconidRivals::
	lock
	faceplayer
	playbgm MUS_ENCOUNTER_MAY, TRUE
	goto_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_DraconidRivals_2
	msgbox LilycoveCity_Text_DraconidRivalsAsk, MSGBOX_YESNO
LilycoveCity_EventScript_DraconidRivals_1:
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_EventScript_DraconidRivals_6
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne LilycoveCity_EventScript_DraconidRivals_9
	msgbox LilycoveCity_Text_DraconidRivalsGo, MSGBOX_DEFAULT
	trainerbattle_two_trainers_no_intro TRAINER_BRENDAN_LILYCOVE, LilycoveCity_Text_DraconidBrendanDefeat, TRAINER_MAY_LILYCOVE, LilycoveCity_Text_DraconidMayDefeat
	msgbox LilycoveCity_Text_DraconidRivalsAfter, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	call LilycoveCity_EventScript_DraconidFlyAway
	setflag FLAG_MET_RIVAL_LILYCOVE
	setflag FLAG_HIDE_LILYCOVE_CITY_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	return

LilycoveCity_EventScript_DraconidRivals_2:
	msgbox LilycoveCity_Text_DraconidRivalsAskAgain, MSGBOX_YESNO
	goto LilycoveCity_EventScript_DraconidRivals_1

LilycoveCity_EventScript_DraconidRivals_6:
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_DraconidRivalsDeclined, MSGBOX_DEFAULT
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


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameLayout::
	goto_if_set FLAG_SYS_GAME_CLEAR, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameLayout_1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameLayout_1:
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BRENDAN
	setobjectxyperm LOCALID_BIRCHS_LAB_BRENDAN, 8, 10
	setobjectmovementtype LOCALID_BIRCHS_LAB_BRENDAN, MOVEMENT_TYPE_FACE_DOWN
	return


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay::
	checktrainerflag TRAINER_MAY_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_2
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_2:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameAsk, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_5
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime, MSGBOX_DEFAULT
LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_4:
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_5:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameGo, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAY_POSTGAME, LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameDefeat
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameAfter, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_4


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan::
	checktrainerflag TRAINER_BRENDAN_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_2
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_2:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameAsk, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_5
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime, MSGBOX_DEFAULT
LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_4:
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_5:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameGo, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BRENDAN_POSTGAME, LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameDefeat
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameAfter, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_4


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble::
	checktrainerflag TRAINER_MAY_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_2
	checktrainerflag TRAINER_BRENDAN_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_2
	checktrainerflag TRAINER_BRENDAN_POSTGAME_DOUBLE
	goto_if 1, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_7
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidDoubleAsk, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_10
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_13
	msgbox LilycoveCity_Text_DraconidRivalsGo, MSGBOX_DEFAULT
	trainerbattle_two_trainers_no_intro TRAINER_BRENDAN_POSTGAME_DOUBLE, LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameDefeat, TRAINER_MAY_POSTGAME_DOUBLE, LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameDefeat
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidPostgameDone, MSGBOX_DEFAULT
	release
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_2:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidBattleTheOtherOne, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_7:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidPostgameDone, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_10:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_13:
	msgbox LilycoveCity_Text_DraconidRivalsNeedTwo, MSGBOX_DEFAULT
	release
	end


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
	msgbox PetalburgCity_Text_DraconidWallyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_PETALBURG, PetalburgCity_Text_DraconidWallyDefeat
	msgbox PetalburgCity_Text_DraconidWallyAfter, MSGBOX_DEFAULT
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

LilycoveCity_EventScript_DraconidWally::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DraconidWallyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_LILYCOVE, LilycoveCity_Text_DraconidWallyDefeat
	msgbox LilycoveCity_Text_DraconidWallyAfter, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_LILYCOVE_WALLY
	setflag FLAG_HIDE_LILYCOVE_CITY_WALLY
	setvar VAR_WALLY_STATE, WALLY_STATE_LILYCOVE_DONE
	fadescreen FADE_FROM_BLACK
	release
	return


LilycoveCity_Text_DraconidRivalsAsk::
	.string "MAY: {PLAYER}! BRENDAN and I came to\n"
	.string "shop at the DEPARTMENT STORE…\p"
	.string "BRENDAN: …but this is way better. Two\n"
	.string "on two: you against both of us!\p"
	.string "MAY: What do you say?$"

LilycoveCity_Text_DraconidRivalsAskAgain::
	.string "BRENDAN: Ready for our tag battle now?$"

LilycoveCity_Text_DraconidRivalsDeclined::
	.string "BRENDAN: Aw, come on! We'll be right\n"
	.string "here.$"

LilycoveCity_Text_DraconidRivalsNeedTwo::
	.string "MAY: Oh! You need at least two POKéMON\n"
	.string "that can battle for this.$"

LilycoveCity_Text_DraconidRivalsGo::
	.string "BRENDAN: Here we come!\p"
	.string "MAY: Don't hold back, {PLAYER}!$"

LilycoveCity_Text_DraconidBrendanDefeat::
	.string "BRENDAN: No way!$"

LilycoveCity_Text_DraconidMayDefeat::
	.string "MAY: Even together?!$"

LilycoveCity_Text_DraconidRivalsAfter::
	.string "MAY: That was amazing, {PLAYER}! We're\n"
	.string "going back to LITTLEROOT to tell Dad\l"
	.string "everything.\p"
	.string "BRENDAN: Don't slow down now. You've\n"
	.string "still got GYMS to beat!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameAsk::
	.string "MAY: The new CHAMPION of HOENN, back in\n"
	.string "LITTLEROOT!\p"
	.string "You promised, remember? One more\n"
	.string "battle, everything we've got!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameGo::
	.string "MAY: BLAZIKEN, let's go all out!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameDefeat::
	.string "MAY: That's our CHAMPION!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameAfter::
	.string "MAY: I'm not giving up. I'll catch up to\n"
	.string "you someday!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameAsk::
	.string "BRENDAN: {PLAYER}! I've been training\n"
	.string "nonstop since SOOTOPOLIS.\p"
	.string "Battle me, CHAMPION?$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameGo::
	.string "BRENDAN: SCEPTILE, MEGA EVOLVE!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameDefeat::
	.string "BRENDAN: Unbelievable…$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameAfter::
	.string "BRENDAN: Next time, I'm winning. Count\n"
	.string "on it!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime::
	.string "Any time you're ready!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidBattleTheOtherOne::
	.string "Did you battle both of us yet? Then we\n"
	.string "can team up for a real two-on-two!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidDoubleAsk::
	.string "BRENDAN: You beat us both one at a\n"
	.string "time…\p"
	.string "MAY: So how about both of us at once?\n"
	.string "Like in LILYCOVE, but for real this time!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidPostgameDone::
	.string "MAY: Dad says the BATTLE FRONTIER is\n"
	.string "full of strong TRAINERS.\p"
	.string "BRENDAN: Let's all go some time!$"

PetalburgCity_Text_DraconidWallyIntro::
	.string "WALLY: {PLAYER}! I came to thank your\n"
	.string "dad for helping me catch RALTS.\p"
	.string "But I think the best way to thank him is\n"
	.string "to show how strong we've become.\p"
	.string "Before you challenge him… battle me!$"

PetalburgCity_Text_DraconidWallyDefeat::
	.string "I lost… but I didn't cough once!$"

PetalburgCity_Text_DraconidWallyAfter::
	.string "WALLY: I'm going to travel around HOENN\n"
	.string "too, like you.\p"
	.string "Good luck against your dad, {PLAYER}!$"

LilycoveCity_Text_DraconidWallyIntro::
	.string "WALLY: {PLAYER}! My RALTS evolved into\n"
	.string "GALLADE on the way here.\p"
	.string "And a man by the sea gave me this KEY\n"
	.string "STONE and a GALLADITE.\p"
	.string "Watch us, {PLAYER}!$"

LilycoveCity_Text_DraconidWallyDefeat::
	.string "Still not enough…$"

LilycoveCity_Text_DraconidWallyAfter::
	.string "WALLY: Next time we battle, it'll be at\n"
	.string "the POKéMON LEAGUE. I promise!$"
