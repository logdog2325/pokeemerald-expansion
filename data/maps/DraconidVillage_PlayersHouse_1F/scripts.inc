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
	msgbox PlayersHouse_1F_Text_LatiEmergencyNewsFlash
	closemessage
	clearflag FLAG_SYS_TV_LATIAS_LATIOS
	setflag FLAG_LATIOS_OR_LATIAS_ROAMING
	special TurnOffTVScreen
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_4
	multichoice 22, 8, MULTI_TV_LATI, TRUE
	copyvar VAR_0x8004, VAR_RESULT
	special InitRoamer
	copyvar VAR_ROAMER_POKEMON, VAR_RESULT
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
	.string "and a night, {PLAYER}. You earned every\l"
	.string "hour of it.\p"
	.string "The children counted falling stars\n"
	.string "until dawn. They are still arguing about\l"
	.string "the total.$"

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
	.string "ELDER: A dragon in flight, over HOENN…\n"
	.string "Did you catch its colour, {PLAYER}?$"

DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV_Text_5:
	.string "ELDER: A dragon of the sky, roaming\n"
	.string "free. Our songs speak of the EON twins.\p"
	.string "Perhaps one will cross your path. Keep\n"
	.string "your eyes on the sky, {PLAYER}.$"

DraconidVillage_PlayersHouse_1F_EventScript_Elder_Text_0:
	.string "ELDER: The sky's debt is paid, {PLAYER}.\n"
	.string "For now.\p"
	.string "Rest while you can. The world beyond\n"
	.string "the mountains still has need of you.$"
