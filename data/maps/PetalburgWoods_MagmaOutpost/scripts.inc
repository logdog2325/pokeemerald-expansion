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
	.string "ASHER: Whoa! COURTNEY! Who's the kid?$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_1:
	.string "COURTNEY: Ahaha… Breathe, ASHER.\p"
	.string "That troublesome AQUA grunt. The one\n"
	.string "sneaking around the woods, picking\l"
	.string "DEVON's pockets?\p"
	.string "This one flattened her. With a dragon. A\n"
	.string "real one.\p"
	.string "I watched the whole thing. …I enjoyed\n"
	.string "it. Ahahahaha!$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_2:
	.string "ASHER: A dragon? At that age?\p"
	.string "…Ha! Fine by me. We could use the muscle.$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_3:
	.string "COURTNEY: So I picked it up. Mine now.\n"
	.string "…Ours, I mean.\p"
	.string "Uniform. Put it on. …Go on. I want to see.$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_4:
	.string "{PLAYER} put on the TEAM MAGMA uniform.$"

PetalburgWoods_MagmaOutpost_EventScript_Uniform_Text_5:
	.string "COURTNEY: …Red. Ahaha. It suits you.\p"
	.string "TABITHA leads the grunts in the field.\n"
	.string "He'll come looking for you.\p"
	.string "Until then… RUSTBORO. Get strong.\p"
	.string "Leader MAXIE likes strong. And I like\n"
	.string "whatever Leader MAXIE likes.$"

PetalburgWoods_MagmaOutpost_EventScript_Courtney_Text_0:
	.string "COURTNEY: Still here? Ahaha…\p"
	.string "RUSTBORO. Get strong. TABITHA will find\n"
	.string "you.$"

PetalburgWoods_MagmaOutpost_EventScript_GruntM_Text_0:
	.string "ASHER: Welcome to the team, kid.\p"
	.string "Folks in town will stare at the uniform.\n"
	.string "Let 'em.$"

PetalburgWoods_MagmaOutpost_EventScript_GruntF_Text_0:
	.string "GRUNT: A dragon, huh? Where are you\n"
	.string "from, anyway?\p"
	.string "…The mountains? Never heard of a\n"
	.string "village up there.$"
