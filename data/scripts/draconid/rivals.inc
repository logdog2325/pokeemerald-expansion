MossdeepCity_SpaceCenter_2F_EventScript_DraconidRival::
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidRivalsHelp, MSGBOX_DEFAULT
	release
	return


MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner::
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidPickPartner, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_2
	setvar VAR_0x8009, PARTNER_BRENDAN
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidBrendanJoins, MSGBOX_DEFAULT
MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_1:
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	compare VAR_RESULT, 0
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_6
MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_5:
	compare VAR_0x8009, PARTNER_MAY
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_9
	multi_2_vs_2 TRAINER_MAXIE_MOSSDEEP, MossdeepCity_SpaceCenter_2F_Text_JustWantToExpandLand, TRAINER_TABITHA_MOSSDEEP, MossdeepCity_SpaceCenter_Text_TabithaDefeat, PARTNER_BRENDAN
MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_8:
	compare VAR_RESULT, 1
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_13
MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_12:
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_2:
	setvar VAR_0x8009, PARTNER_MAY
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidMayJoins, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_1

MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_6:
	special LoadPlayerParty
	goto MossdeepCity_SpaceCenter_2F_EventScript_ReadyForBattlePrompt
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_5

MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_9:
	multi_2_vs_2 TRAINER_MAXIE_MOSSDEEP, MossdeepCity_SpaceCenter_2F_Text_JustWantToExpandLand, TRAINER_TABITHA_MOSSDEEP, MossdeepCity_SpaceCenter_Text_TabithaDefeat, PARTNER_MAY
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_8

MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_13:
	goto MossdeepCity_SpaceCenter_2F_EventScript_DefeatedMaxieTabitha
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidChoosePartner_12


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRivalsLeave::
	setflag FLAG_HIDE_MOSSDEEP_SPACE_CENTER_RIVALS
	removeobject LOCALID_SPACE_CENTER_2F_MAY
	removeobject LOCALID_SPACE_CENTER_2F_BRENDAN
	return


SootopolisCity_Gym_1F_EventScript_DraconidRivalsWait::
	compare VAR_BRENDAN_STATE, BRENDAN_STATE_SOOTOPOLIS
	goto_if_lt SootopolisCity_Gym_1F_EventScript_DraconidRivalsWait_1
	return

SootopolisCity_Gym_1F_EventScript_DraconidRivalsWait_1:
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_SOOTOPOLIS
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_RIVALS
	return


SootopolisCity_EventScript_DraconidMegaRivals::
	lockall
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_SOOTOPOLIS_MAY, Common_Movement_ExclamationMark
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_MAY, Common_Movement_WalkUp
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, Common_Movement_WalkUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SootopolisCity_Text_DraconidMegaRivalsIntro, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SootopolisCity_Text_DraconidBrendanMegaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BRENDAN_MOSSDEEP, SootopolisCity_Text_DraconidBrendanMegaDefeat
	special HealPlayerParty
	msgbox SootopolisCity_Text_DraconidMayHeals, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_MAY, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SootopolisCity_Text_DraconidMayMegaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN_MOSSDEEP, SootopolisCity_Text_DraconidMayMegaDefeat
	special HealPlayerParty
	msgbox SootopolisCity_Text_DraconidMegaRivalsAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SOOTOPOLIS_MAY, SootopolisCity_Movement_DraconidRivalLeave
	applymovement LOCALID_SOOTOPOLIS_BRENDAN, SootopolisCity_Movement_DraconidRivalLeave
	waitmovement 0
	removeobject LOCALID_SOOTOPOLIS_MAY
	removeobject LOCALID_SOOTOPOLIS_BRENDAN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RIVALS
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_MEGAS_DONE
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


SootopolisCity_Movement_DraconidRivalLeave:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

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

MossdeepCity_SpaceCenter_2F_Text_DraconidRivalsHelp::
	.string "MAY: We came as soon as we heard TEAM\n"
	.string "MAGMA was here!\p"
	.string "Talk to STEVEN when you're ready. One\n"
	.string "of us will fight with you!$"

MossdeepCity_SpaceCenter_2F_Text_DraconidPickPartner::
	.string "STEVEN: MAY and BRENDAN came to help.\n"
	.string "One of them fights beside you; the\l"
	.string "other holds the stairs with me.\p"
	.string "Will you team up with MAY?$"

MossdeepCity_SpaceCenter_2F_Text_DraconidMayJoins::
	.string "MAY: Leave it to me, {PLAYER}!$"

MossdeepCity_SpaceCenter_2F_Text_DraconidBrendanJoins::
	.string "BRENDAN: Then it's you and me, {PLAYER}!$"

SootopolisCity_Text_DraconidMegaRivalsIntro::
	.string "MAY: {PLAYER}! You beat JUAN! That's all\n"
	.string "eight BADGES!\p"
	.string "BRENDAN: We saw everything. RAYQUAZA,\n"
	.string "the storm… you were right there in the\l"
	.string "middle of it.\p"
	.string "MAY: Dad sent us these before we came.\n"
	.string "KEY STONES!\p"
	.string "BRENDAN: Our partners can MEGA EVOLVE\n"
	.string "now, just like your friends can. Want to\l"
	.string "see?$"

SootopolisCity_Text_DraconidBrendanMegaIntro::
	.string "BRENDAN: Me first! SCEPTILE's been\n"
	.string "waiting for this!$"

SootopolisCity_Text_DraconidBrendanMegaDefeat::
	.string "BRENDAN: Even with MEGA EVOLUTION…$"

SootopolisCity_Text_DraconidMayHeals::
	.string "MAY: My turn! Here, let me heal your\n"
	.string "team first. It's only fair.\p"
	.string "{PLAYER}'s POKéMON were fully healed!$"

SootopolisCity_Text_DraconidMayMegaIntro::
	.string "MAY: BLAZIKEN and I trained on every\n"
	.string "route in HOENN for this!$"

SootopolisCity_Text_DraconidMayMegaDefeat::
	.string "MAY: Wow… you really are the strongest.$"

SootopolisCity_Text_DraconidMegaRivalsAfter::
	.string "MAY: VICTORY ROAD is past EVER GRANDE\n"
	.string "CITY, east of here.\p"
	.string "BRENDAN: Beat the POKéMON LEAGUE,\n"
	.string "{PLAYER}. Then come back to LITTLEROOT\l"
	.string "and battle us again!$"

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
