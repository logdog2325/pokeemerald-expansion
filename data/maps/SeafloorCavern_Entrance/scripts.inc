SeafloorCavern_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SeafloorCavern_Entrance_OnResume
	.byte 0

SeafloorCavern_Entrance_OnResume:
	setdivewarp MAP_UNDERWATER_SEAFLOOR_CAVERN, 6, 5
	setescapewarp MAP_UNDERWATER_SEAFLOOR_CAVERN, 6, 5
	end

SeafloorCavern_Entrance_EventScript_Grunt::
	lockall
	goto_if_eq VAR_HAS_TALKED_TO_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, 1, SeafloorCavern_Entrance_EventScript_GruntSpeechShort
	waitse
	playse SE_PIN
	applymovement LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, Common_Movement_Delay48
	waitmovement 0
	delay 20
	call_if_eq VAR_FACING, DIR_WEST, SeafloorCavern_Entrance_EventScript_GruntFacePlayerWest
	call_if_eq VAR_FACING, DIR_EAST, SeafloorCavern_Entrance_EventScript_GruntFacePlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, SeafloorCavern_Entrance_EventScript_GruntFacePlayerNorth
	delay 30
	setvar VAR_HAS_TALKED_TO_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, 1
	copyobjectxytoperm LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT
	msgbox SeafloorCavern_Entrance_Text_HearMagmaNearMossdeep, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	releaseall
	end

SeafloorCavern_Entrance_EventScript_GruntSpeechShort::
	call_if_eq VAR_FACING, DIR_WEST, SeafloorCavern_Entrance_EventScript_GruntFacePlayerWest
	call_if_eq VAR_FACING, DIR_EAST, SeafloorCavern_Entrance_EventScript_GruntFacePlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, SeafloorCavern_Entrance_EventScript_GruntFacePlayerNorth
	msgbox SeafloorCavern_Entrance_Text_HearMagmaNearMossdeepShort, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	releaseall
	end

SeafloorCavern_Entrance_EventScript_GruntFacePlayerEast::
	applymovement LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SeafloorCavern_Entrance_EventScript_GruntFacePlayerWest::
	applymovement LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

SeafloorCavern_Entrance_EventScript_GruntFacePlayerNorth::
	applymovement LOCALID_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SeafloorCavern_Entrance_Text_HearMagmaNearMossdeep:  @ Draconid Emerald
	.string "Hey!\n"
	.string "I remember your face!\p"
	.string "You're the MAGMA brat from the\n"
	.string "SPACE CENTER!\p"
	.string "Your whole team couldn't steal one\n"
	.string "tank of fuel, and now you follow us\l"
	.string "down here?\p"
	.string "A punk like you, do you really think\n"
	.string "you can take on TEAM AQUA?\p"
	.string "I'd say you're too early by about\n"
	.string "a trillion years!$"

SeafloorCavern_Entrance_Text_HearMagmaNearMossdeepShort:  @ Draconid Emerald
	.string "A MAGMA punk like you, do you really\n"
	.string "think you can take on TEAM AQUA?\p"
	.string "I'd say you're too early by about\n"
	.string "a trillion years!\p"
	.string "Go back to your volcano!\n"
	.string "Your bunch sure doesn't look good\l"
	.string "near the sea!$"

