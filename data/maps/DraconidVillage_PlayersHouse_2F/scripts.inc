DraconidVillage_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	return

DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0
	.2byte 0

DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0:
	call SecretBase_EventScript_InitDecorations
	return

DraconidVillage_PlayersHouse_2F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_DRACONID_STATE, DRACONID_STATE_NEW_GAME, DraconidVillage_PlayersHouse_2F_EventScript_WakeUp
	map_script_2 VAR_DRACONID_FINALE_STATE, FINALE_STATE_HALL_OF_FAME, DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming
	map_script_2 VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED, DraconidVillage_PlayersHouse_2F_EventScript_DraconidWakeUpAfterFinale
	.2byte 0


DraconidVillage_PlayersHouse_2F_EventScript_WakeUp::
	lockall
	delay 60
	fadescreen FADE_TO_BLACK
	delay 30
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_0
	closemessage
	playse SE_M_DETECT
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_1
	closemessage
	delay 40
	fadescreen FADE_FROM_BLACK
	delay 30
	playse SE_EXIT
	clearflag FLAG_HIDE_DRACONID_HOUSE_2F_ASTER
	addobject LOCALID_DRACONID_HOUSE_2F_ASTER
	applymovement LOCALID_DRACONID_HOUSE_2F_ASTER, DraconidVillage_PlayersHouse_2F_Movement_AsterEnters
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_2
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_3
	closemessage
	applymovement LOCALID_DRACONID_HOUSE_2F_ASTER, DraconidVillage_PlayersHouse_2F_Movement_AsterExits
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_DRACONID_HOUSE_2F_ASTER
	setvar VAR_DRACONID_STATE, DRACONID_STATE_SET_CLOCK
	releaseall
	return


DraconidVillage_PlayersHouse_2F_Movement_AsterEnters:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

DraconidVillage_PlayersHouse_2F_Movement_AsterExits:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

DraconidVillage_PlayersHouse_2F_EventScript_StairsBlocked::
	lockall
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_StairsBlocked_Text_0
	closemessage
	applymovement LOCALID_PLAYER, DraconidVillage_PlayersHouse_2F_Movement_StepAwayFromStairs
	waitmovement 0
	releaseall
	return


DraconidVillage_PlayersHouse_2F_Movement_StepAwayFromStairs:
	walk_down
	step_end

DraconidVillage_PlayersHouse_2F_EventScript_WallClock::
	lockall
	compare VAR_DRACONID_STATE, DRACONID_STATE_SET_CLOCK
	goto_if_le DraconidVillage_PlayersHouse_2F_EventScript_WallClock_2
	incrementgamestat GAME_STAT_CHECKED_CLOCK
	fadescreen FADE_TO_BLACK
	special Special_ViewWallClock
	releaseall
	return

DraconidVillage_PlayersHouse_2F_EventScript_WallClock_2:
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_WallClock_Text_0
	checkplayergender
	copyvar VAR_0x8004, VAR_RESULT
	fadescreen FADE_TO_BLACK
	special StartWallClock
	delay 30
	setvar VAR_DRACONID_STATE, DRACONID_STATE_CLOCK_SET
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_WallClock_Text_1
	releaseall
	end


DraconidVillage_PlayersHouse_2F_EventScript_PC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC
	special BedroomPC
	releaseall
	return


DraconidVillage_PlayersHouse_2F_EventScript_TurnOffPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	return


DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_0:
	.string "That night, the DRACONID village slept\n"
	.string "under a clear, cold sky…$"

DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_1:
	.string "A falling star tore across the heavens\n"
	.string "and vanished beyond the mountains.\p"
	.string "In the ELDER's house, a lamp was lit, and\n"
	.string "it burned until dawn.$"

DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_2:
	.string "ASTER: So you're awake. Finally.\p"
	.string "The ELDER wants you. Now. He didn't\n"
	.string "sleep at all last night.\p"
	.string "Did you see it? The star that fell? No…\n"
	.string "of course you didn't.\p"
	.string "Hmph. And he calls for you, not me.$"

DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_3:
	.string "ASTER: Set that clock of yours before\n"
	.string "you come. It's been dead for a week.\p"
	.string "The ELDER's house is the one with the\n"
	.string "red roof, by the shrine. Don't make him\l"
	.string "wait.$"

DraconidVillage_PlayersHouse_2F_EventScript_StairsBlocked_Text_0:
	.string "{PLAYER} glanced at the stopped clock\n"
	.string "on the wall. Better set it first, like\l"
	.string "ASTER said.$"

DraconidVillage_PlayersHouse_2F_EventScript_WallClock_Text_0:
	.string "The clock has stopped. Better set it\n"
	.string "and get it going again!$"

DraconidVillage_PlayersHouse_2F_EventScript_WallClock_Text_1:
	.string "Tick… tock… The clock is running again.\p"
	.string "Time to head downstairs!$"
