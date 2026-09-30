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
	.2byte 0


DraconidVillage_PlayersHouse_2F_EventScript_WakeUp::
	lockall
	delay 30
	playse SE_EXIT
	addobject LOCALID_DRACONID_HOUSE_2F_MOM
	applymovement LOCALID_DRACONID_HOUSE_2F_MOM, DraconidVillage_PlayersHouse_2F_Movement_MomEnters
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_WakeUp_Text_0
	closemessage
	applymovement LOCALID_DRACONID_HOUSE_2F_MOM, DraconidVillage_PlayersHouse_2F_Movement_MomExits
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_DRACONID_HOUSE_2F_MOM
	setvar VAR_DRACONID_STATE, DRACONID_STATE_SET_CLOCK
	releaseall
	return


DraconidVillage_PlayersHouse_2F_Movement_MomEnters:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

DraconidVillage_PlayersHouse_2F_Movement_MomExits:
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
	.string "MOM: Good morning, {PLAYER}! You're\n"
	.string "finally up!\p"
	.string "Don't tell me you forgot what today is…\n"
	.string "It's your egg ceremony!\p"
	.string "The ELDER will be waiting at his house\n"
	.string "to entrust you with a dragon egg.\p"
	.string "Oh, and before you go… The clock on\n"
	.string "your wall has stopped again.\p"
	.string "Could you set it for me? Then come on\n"
	.string "down!$"

DraconidVillage_PlayersHouse_2F_EventScript_StairsBlocked_Text_0:
	.string "MOM: {PLAYER}, did you set the clock\n"
	.string "yet? It's on the wall next to the\l"
	.string "window!$"

DraconidVillage_PlayersHouse_2F_EventScript_WallClock_Text_0:
	.string "The clock has stopped. Better set it\n"
	.string "and get it going again!$"

DraconidVillage_PlayersHouse_2F_EventScript_WallClock_Text_1:
	.string "Tick… tock… The clock is running again.\p"
	.string "Time to head downstairs!$"
