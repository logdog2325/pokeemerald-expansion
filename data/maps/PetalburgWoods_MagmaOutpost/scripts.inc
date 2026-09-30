PetalburgWoods_MagmaOutpost_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgWoods_MagmaOutpost_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgWoods_MagmaOutpost_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

PetalburgWoods_MagmaOutpost_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_PETALBURG_WOODS_STATE, 2, PetalburgWoods_MagmaOutpost_EventScript_FaceCourtney
	.2byte 0

PetalburgWoods_MagmaOutpost_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_PETALBURG_WOODS_STATE, 2, PetalburgWoods_MagmaOutpost_EventScript_Uniform
	.2byte 0


PetalburgWoods_MagmaOutpost_EventScript_FaceCourtney::
	turnobject LOCALID_PLAYER, DIR_NORTH
	return


PetalburgWoods_MagmaOutpost_EventScript_Uniform::
	lockall
	delay 30
	applymovement LOCALID_MAGMA_OUTPOST_GRUNT_M, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_0, MSGBOX_DEFAULT
	msgbox PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_1, MSGBOX_DEFAULT
	msgbox PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_2, MSGBOX_DEFAULT
	msgbox PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_3, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, PLAYER_OUTFIT_MAGMA
	call Draconid_EventScript_ChangeOutfit
	setvar VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	setvar VAR_MAGMA_STATE, MAGMA_STATE_RECRUITED
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	msgbox PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_4, MSGBOX_DEFAULT
	msgbox PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_5, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_WOODS_STATE, 3
	releaseall
	return


PetalburgWoods_MagmaOutpost_EventScript_Courtney::
	msgbox PetalburgWoods_MagmaOutpost_EventScript_Courtney_Text_0, MSGBOX_NPC
	return


PetalburgWoods_MagmaOutpost_EventScript_GruntM::
	msgbox PetalburgWoods_MagmaOutpost_EventScript_GruntM_Text_0, MSGBOX_NPC
	return


PetalburgWoods_MagmaOutpost_EventScript_GruntF::
	msgbox PetalburgWoods_MagmaOutpost_EventScript_GruntF_Text_0, MSGBOX_NPC
	return


PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_0:
	.string "GRUNT: COURTNEY! Who's the kid?$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_1:
	.string "COURTNEY: New member. Beat an AQUA\n"
	.string "woman in the woods. Alone.$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_2:
	.string "GRUNT: Alone? At that age?\n"
	.string "…Well, we could use the muscle.$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_3:
	.string "COURTNEY: Uniform. Put it on.$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_4:
	.string "{PLAYER} put on the TEAM MAGMA uniform.$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_5:
	.string "COURTNEY: …Red. It suits you.\p"
	.string "TABITHA leads the grunts in the field.\n"
	.string "He will find you.\p"
	.string "Until then: RUSTBORO. Get strong.\p"
	.string "Leader MAXIE… likes strong.$"

PetalburgWoods_MagmaOutpost_EventScript_Courtney_Text_0:
	.string "COURTNEY: RUSTBORO. Get strong.\n"
	.string "TABITHA will find you.$"

PetalburgWoods_MagmaOutpost_EventScript_GruntM_Text_0:
	.string "GRUNT: Welcome to the team, kid.\p"
	.string "Folks in town will stare at the uniform.\n"
	.string "Let 'em.$"

PetalburgWoods_MagmaOutpost_EventScript_GruntF_Text_0:
	.string "GRUNT: A dragon, huh? Where are you\n"
	.string "from, anyway?\p"
	.string "…The mountains? Never heard of a\n"
	.string "village up there.$"
