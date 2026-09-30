DraconidVillage_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_PlayersHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_PlayersHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV
	.2byte 0


DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV::
	lockall
	setvar VAR_0x8008, MALE
	setvar VAR_0x8009, LOCALID_DRACONID_HOUSE_DAD
	setvar VAR_0x800A, LOCALID_DRACONID_HOUSE_ELDER
	goto PlayersHouse_1F_EventScript_SSTicketAndLatiTV
	return


DraconidVillage_PlayersHouse_1F_EventScript_Elder::
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_Elder_Text_0, MSGBOX_NPC
	return


DraconidVillage_PlayersHouse_1F_EventScript_Elder_Text_0:
	.string "ELDER: The sky's debt is paid, {PLAYER}.\n"
	.string "For now.\p"
	.string "Rest while you can. The world beyond\n"
	.string "the mountains still has need of you.$"
