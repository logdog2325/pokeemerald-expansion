DraconidVillage_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_PlayersHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_PlayersHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_ALERT, DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert
	map_script_2 VAR_DRACONID_FINALE_STATE, FINALE_STATE_HOME, DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV
	.2byte 0


DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV::
	lockall
	applymovement LOCALID_DRACONID_HOUSE_ELDER, DraconidVillage_PlayersHouse_1F_Movement_ElderToStairs
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_1
	giveitem ITEM_SS_TICKET
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_2
	closemessage
	setflag FLAG_RECEIVED_SS_TICKET
	delay 20
	setflag FLAG_SYS_TV_LATIAS_LATIOS
	special TurnOnTVScreen
	delay 60
	applymovement LOCALID_DRACONID_HOUSE_ELDER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_3
	closemessage
	applymovement LOCALID_PLAYER, DraconidVillage_PlayersHouse_1F_Movement_PlayerToTV
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_4
	closemessage
	clearflag FLAG_SYS_TV_LATIAS_LATIOS
	setflag FLAG_LATIOS_OR_LATIAS_ROAMING
	special InitRoamer
	special TurnOffTVScreen
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_5
	closemessage
	applymovement LOCALID_DRACONID_HOUSE_ELDER, DraconidVillage_PlayersHouse_1F_Movement_ElderLeaves
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_DRACONID_HOUSE_ELDER
	clearflag FLAG_HIDE_DRACONID_ELDERS_HOUSE_ELDER
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 4
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_POSTGAME
	releaseall
	return


DraconidVillage_PlayersHouse_1F_Movement_ElderToStairs:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

DraconidVillage_PlayersHouse_1F_Movement_PlayerToTV:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_left
	step_end

DraconidVillage_PlayersHouse_1F_Movement_ElderLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	set_invisible
	step_end

DraconidVillage_PlayersHouse_1F_EventScript_Elder::
	lock
	faceplayer
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_SUMMONED
	goto_if_eq DraconidVillage_PlayersHouse_1F_EventScript_Elder_2
DraconidVillage_PlayersHouse_1F_EventScript_Elder_1:
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_Elder_Text_0
	release
	return

DraconidVillage_PlayersHouse_1F_EventScript_Elder_2:
	goto DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift
	goto DraconidVillage_PlayersHouse_1F_EventScript_Elder_1


DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_0:
	.string "ELDER: You slept through a whole day\n"
	.string "and a night, {PLAYER}. The village did\l"
	.string "not.\p"
	.string "Every roof the old ones cracked is\n"
	.string "mended. The children built a GROUDON\l"
	.string "out of the rubble in the square.$"

DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_1:
	.string "ELDER: A letter came for you, from\n"
	.string "CAPTAIN STERN of SLATEPORT.\p"
	.string "He writes that HOENN owes you a voyage,\n"
	.string "and he sent this with it.$"

DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_2:
	.string "ELDER: A ticket for the S.S. TIDAL. The\n"
	.string "ship sails from SLATEPORT and from\l"
	.string "LILYCOVE.\p"
	.string "The world beyond the mountains is wide.\n"
	.string "Go and see it.\p"
	.string "The sky will call again when it has need\n"
	.string "of you.$"

DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_3:
	.string "ELDER: Hm? The picture box is speaking\n"
	.string "by itself again.$"

DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_4:
	.string "…We interrupt this program with a news\n"
	.string "flash!\p"
	.string "Two dragon-like POKéMON, one red and\n"
	.string "one blue, have been sighted flying over\l"
	.string "HOENN!\p"
	.string "Viewers may remember the pair seen with\n"
	.string "two young TRAINERS from LITTLEROOT\l"
	.string "during the trouble in the mountains.\p"
	.string "Experts say these two are a second\n"
	.string "pair, wild and free. Where they will be\l"
	.string "seen next is anyone's guess!$"

DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_5:
	.string "ELDER: Red and blue, flying together…\n"
	.string "Our songs speak of the EON twins.\p"
	.string "BRENDAN and MAY found theirs when the\n"
	.string "star broke. It seems the sky had more\l"
	.string "to share.\p"
	.string "Perhaps they will cross your path,\n"
	.string "{PLAYER}. Keep your eyes on the sky.$"

DraconidVillage_PlayersHouse_1F_EventScript_Elder_Text_0:
	.string "ELDER: The sky's debt is paid, {PLAYER}.\n"
	.string "For now.\p"
	.string "Rest while you can. The world beyond\n"
	.string "the mountains still has need of you.$"
