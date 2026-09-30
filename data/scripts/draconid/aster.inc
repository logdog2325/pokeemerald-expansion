Draconid_EventScript_BattleAsterMeteorFalls::
	trainerbattle_no_intro TRAINER_ASTER_METEOR_FALLS_DEINO, Draconid_Text_AsterDefeat
	return


Draconid_EventScript_ChangeOutfit::
	fadescreen FADE_TO_BLACK
	special SetPlayerOutfit
	playse SE_BIKE_HOP
	delay 20
	fadescreen FADE_FROM_BLACK
	return


MeteorFalls_1F_1R_EventScript_DraconidAster::
	compare VAR_ASTER_STATE, ASTER_STATE_START
	goto_if_ne MeteorFalls_1F_1R_EventScript_DraconidAster_2
	clearflag FLAG_HIDE_METEOR_FALLS_ASTER
	addobject LOCALID_METEOR_FALLS_ASTER
	playbgm MUS_ENCOUNTER_INTENSE, TRUE
	applymovement LOCALID_METEOR_FALLS_ASTER, MeteorFalls_1F_1R_Movement_DraconidAsterApproach
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_DraconidAsterRiddle, MSGBOX_DEFAULT
	call Draconid_EventScript_BattleAsterMeteorFalls
	msgbox MeteorFalls_1F_1R_Text_DraconidAsterAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_METEOR_FALLS_ASTER, MeteorFalls_1F_1R_Movement_DraconidAsterLeave
	waitmovement 0
	removeobject LOCALID_METEOR_FALLS_ASTER
	setflag FLAG_HIDE_METEOR_FALLS_ASTER
	clearflag FLAG_HIDE_CABLE_CAR_STATION_ASTER
	setvar VAR_ASTER_STATE, ASTER_STATE_METEOR_FALLS
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

MeteorFalls_1F_1R_EventScript_DraconidAster_2:
	return


MeteorFalls_1F_1R_Movement_DraconidAsterApproach:
	walk_left
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_DraconidAsterLeave:
	walk_right
	walk_right
	walk_right
	step_end

Route112_CableCarStation_EventScript_DraconidAsterDisguise::
	lockall
	playbgm MUS_ENCOUNTER_INTENSE, TRUE
	applymovement LOCALID_CABLE_CAR_STATION_ASTER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Route112_CableCarStation_Text_DraconidAsterDisguise, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, PLAYER_OUTFIT_MAGMA
	call Draconid_EventScript_ChangeOutfit
	msgbox Route112_CableCarStation_Text_DraconidPutOnDisguise, MSGBOX_DEFAULT
	msgbox Route112_CableCarStation_Text_DraconidAsterGoAhead, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CABLE_CAR_STATION_ASTER, Common_Movement_WalkDown
	waitmovement 0
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_CABLE_CAR_STATION_ASTER
	setflag FLAG_HIDE_CABLE_CAR_STATION_ASTER
	fadescreen FADE_FROM_BLACK
	setvar VAR_ASTER_STATE, ASTER_STATE_DISGUISED
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


MtChimney_EventScript_DraconidDisguiseOff::
	compare VAR_PLAYER_OUTFIT, PLAYER_OUTFIT_MAGMA
	goto_if_eq MtChimney_EventScript_DraconidDisguiseOff_2
MtChimney_EventScript_DraconidDisguiseOff_1:
	compare VAR_ASTER_STATE, ASTER_STATE_CHIMNEY_DONE
	goto_if_lt MtChimney_EventScript_DraconidDisguiseOff_4
	return

MtChimney_EventScript_DraconidDisguiseOff_2:
	setvar VAR_0x8004, PLAYER_OUTFIT_DRACONID
	call Draconid_EventScript_ChangeOutfit
	msgbox MtChimney_Text_DraconidDisguiseOff, MSGBOX_DEFAULT
	goto MtChimney_EventScript_DraconidDisguiseOff_1

MtChimney_EventScript_DraconidDisguiseOff_4:
	setvar VAR_ASTER_STATE, ASTER_STATE_CHIMNEY_DONE
	return


MagmaHideout_1F_EventScript_DraconidCheckDisguise::
	compare VAR_ASTER_STATE, ASTER_STATE_CHIMNEY_DONE
	goto_if_ge MagmaHideout_1F_EventScript_DraconidCheckDisguise_3
	return

MagmaHideout_1F_EventScript_DraconidCheckDisguise_1:
	setvar VAR_TEMP_1, 1
	return

MagmaHideout_1F_EventScript_DraconidCheckDisguise_2:
	compare VAR_PLAYER_OUTFIT, PLAYER_OUTFIT_MAGMA
	goto_if_ne MagmaHideout_1F_EventScript_DraconidCheckDisguise_1
	return

MagmaHideout_1F_EventScript_DraconidCheckDisguise_3:
	compare VAR_ASTER_STATE, ASTER_STATE_HIDEOUT_DONE
	goto_if_lt MagmaHideout_1F_EventScript_DraconidCheckDisguise_2
	return


MagmaHideout_1F_EventScript_DraconidDisguiseOn::
	lockall
	setvar VAR_TEMP_1, 0
	msgbox MagmaHideout_1F_Text_DraconidDisguiseOn, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, PLAYER_OUTFIT_MAGMA
	call Draconid_EventScript_ChangeOutfit
	releaseall
	return


MagmaHideout_4F_EventScript_DraconidAfterMaxie::
	setvar VAR_0x8004, PLAYER_OUTFIT_DRACONID
	call Draconid_EventScript_ChangeOutfit
	msgbox MtChimney_Text_DraconidDisguiseOff, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_MAGMA_HIDEOUT_ASTER
	addobject LOCALID_MAGMA_HIDEOUT_4F_ASTER
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MagmaHideout_4F_Text_DraconidAsterGoHome, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAGMA_HIDEOUT_4F_ASTER
	setflag FLAG_HIDE_MAGMA_HIDEOUT_ASTER
	fadescreen FADE_FROM_BLACK
	setvar VAR_ASTER_STATE, ASTER_STATE_HIDEOUT_DONE
	return


DraconidVillage_EldersHouse_EventScript_DraconidMegaRing::
	msgbox DraconidVillage_EldersHouse_Text_DraconidMegaRing, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	switch VAR_SECOND_STARTER
	case SECOND_STARTER_CHARMANDER, DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_3
	case SECOND_STARTER_TOTODILE, DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_4
	case SECOND_STARTER_TREECKO, DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_5
DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_1:
	setflag FLAG_RECEIVED_MEGA_RING
	setvar VAR_ASTER_STATE, ASTER_STATE_MEGA_RING
	msgbox DraconidVillage_EldersHouse_Text_DraconidSkyPillar, MSGBOX_DEFAULT
	return

DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_3:
	msgbox DraconidVillage_EldersHouse_Text_DraconidMegaStone, MSGBOX_DEFAULT
	giveitem ITEM_CHARIZARDITE_X
	goto DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_1

DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_4:
	msgbox DraconidVillage_EldersHouse_Text_DraconidMegaStone, MSGBOX_DEFAULT
	giveitem ITEM_FERALIGITE
	goto DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_1

DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_5:
	msgbox DraconidVillage_EldersHouse_Text_DraconidMegaStone, MSGBOX_DEFAULT
	giveitem ITEM_SCEPTILITE
	goto DraconidVillage_EldersHouse_EventScript_DraconidMegaRing_1


Draconid_Text_AsterDefeat::
	.string "…Hmph. The wind was at your back.$"

MeteorFalls_1F_1R_Text_DraconidAsterRiddle::
	.string "ASTER: Riddle me this, {PLAYER}. What\n"
	.string "falls from the sky but is never caught,\l"
	.string "and burns but is never lit?\p"
	.string "…A meteor. And those fools in red just\n"
	.string "carried one off like a sack of coal.\p"
	.string "Our clan guards the stones that fall\n"
	.string "from the sky. You swore that oath too.\l"
	.string "So show me you meant it!$"

MeteorFalls_1F_1R_Text_DraconidAsterAfter::
	.string "ASTER: MAGMA is taking that meteorite\n"
	.string "to MT. CHIMNEY. I heard them.\p"
	.string "Meet me at the cable car on ROUTE 112. I\n"
	.string "have an idea… you won't like it.$"

Route112_CableCarStation_Text_DraconidAsterDisguise::
	.string "ASTER: There you are. Riddle: how do you\n"
	.string "walk into a volcano without getting\l"
	.string "burned?\p"
	.string "…You wear the fire. Here. I took it off a\n"
	.string "MAGMA grunt who was sleeping on the\l"
	.string "job.\p"
	.string "Up on the mountain they'll think you're\n"
	.string "one of them until it's too late.$"

Route112_CableCarStation_Text_DraconidPutOnDisguise::
	.string "{PLAYER} put on the TEAM MAGMA uniform!$"

Route112_CableCarStation_Text_DraconidAsterGoAhead::
	.string "ASTER: Ha! You look ridiculous. Perfect.\p"
	.string "Stop MAXIE before that meteorite goes\n"
	.string "into the crater. I'll watch the path\l"
	.string "from the pass.$"

MtChimney_Text_DraconidDisguiseOff::
	.string "{PLAYER} took off the TEAM MAGMA\n"
	.string "uniform and packed it away.$"

MagmaHideout_1F_Text_DraconidDisguiseOn::
	.string "{PLAYER} put the TEAM MAGMA uniform\n"
	.string "back on before going in.$"

MagmaHideout_4F_Text_DraconidAsterGoHome::
	.string "ASTER: I saw it from the tunnels.\n"
	.string "GROUDON is awake… and the sky will\l"
	.string "answer. It always does.\p"
	.string "Go home, {PLAYER}. Grandfather is\n"
	.string "waiting for you at the village. He has\l"
	.string "something for you.\p"
	.string "I'm going to find out where the one in\n"
	.string "the sky sleeps.$"

DraconidVillage_EldersHouse_Text_DraconidMegaRing::
	.string "ELDER: {PLAYER}. You went into the\n"
	.string "mountain wearing the enemy's colours\l"
	.string "and came back yourself.\p"
	.string "That takes a steadier heart than\n"
	.string "strength. Take this.\p"
	.string "Our clan's KEY STONE, set in a ring. With\n"
	.string "it, a POKéMON that trusts you can MEGA\l"
	.string "EVOLVE.$"

DraconidVillage_EldersHouse_Text_DraconidMegaStone::
	.string "ELDER: And this stone is for the\n"
	.string "partner PROF. BIRCH gave you. Its MEGA\l"
	.string "form carries a dragon's blood.$"

DraconidVillage_EldersHouse_Text_DraconidSkyPillar::
	.string "ELDER: The two ancient POKéMON will not\n"
	.string "stay asleep for long. When the sky\l"
	.string "itself grows angry,\p"
	.string "seek the pillar that reaches the\n"
	.string "clouds, far to the east over the sea.\l"
	.string "ASTER is already looking for it.$"
