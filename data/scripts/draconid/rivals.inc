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


LilycoveCity_Text_DraconidRivalsNeedTwo::
	.string "MAY: Oh! You need at least two POKéMON\n"
	.string "that can battle for this.$"

LilycoveCity_Text_DraconidRivalsGo::
	.string "BRENDAN: Here we come!\p"
	.string "MAY: Don't hold back, {PLAYER}!$"

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
