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
