EverGrandeCity_HallOfFame_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_HallOfFame_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_HallOfFame_OnWarp
	.byte 0

EverGrandeCity_HallOfFame_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_HallOfFame_EventScript_TurnPlayerNorth
	.2byte 0

EverGrandeCity_HallOfFame_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_HallOfFame_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_HallOfFame_EventScript_EnterHallOfFame
	.2byte 0

EverGrandeCity_HallOfFame_EventScript_EnterHallOfFame::
	lockall
	applymovement LOCALID_HALL_OF_FAME_STEVEN, EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame1  @ Draconid Emerald
	applymovement LOCALID_PLAYER, EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame1
	waitmovement 0
	applymovement LOCALID_HALL_OF_FAME_STEVEN, Common_Movement_WalkInPlaceFasterRight  @ Draconid Emerald
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox EverGrandeCity_HallOfFame_Text_HereWeHonorLeagueChampions, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HALL_OF_FAME_STEVEN, EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame2  @ Draconid Emerald
	applymovement LOCALID_PLAYER, EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame2
	waitmovement 0
	delay 20
	applymovement LOCALID_HALL_OF_FAME_STEVEN, Common_Movement_WalkInPlaceFasterRight  @ Draconid Emerald
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox EverGrandeCity_HallOfFame_Text_LetsRecordYouAndYourPartnersNames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HALL_OF_FAME_STEVEN, Common_Movement_WalkInPlaceFasterUp  @ Draconid Emerald
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD
	delay 40
	setvar VAR_TEMP_1, 1
	call EverGrandeCity_HallOfFame_EventScript_SetGameClearFlags
	@ Draconid Emerald: the player's home is in Draconid Village for both genders
	setrespawn HEAL_LOCATION_DRACONID_VILLAGE_PLAYERS_HOUSE_2F
	call EverGrandeCity_HallOfFame_EventScript_DraconidFinaleStart  @ Draconid Emerald: no credits; the meteor alert waits at home (act6.pory)
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	releaseall
	end

EverGrandeCity_HallOfFame_EventScript_GameClearMale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	releaseall
	end

EverGrandeCity_HallOfFame_EventScript_GameClearFemale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	releaseall
	end

EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeCity_HallOfFame_Text_HereWeHonorLeagueChampions:  @ Draconid Emerald
	.string "STEVEN: This room…\p"
	.string "This is where we keep records of\n"
	.string "POKéMON that prevailed through harsh\l"
	.string "battles.\p"
	.string "It is here that the LEAGUE CHAMPIONS\n"
	.string "are honored.$"

EverGrandeCity_HallOfFame_Text_LetsRecordYouAndYourPartnersNames:  @ Draconid Emerald
	.string "STEVEN: Come on, let's record your name\n"
	.string "as a TRAINER who triumphed over the\l"
	.string "POKéMON LEAGUE, and the names of the\l"
	.string "partners who battled with you.$"

