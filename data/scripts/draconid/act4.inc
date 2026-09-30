PetalburgCity_Gym_EventScript_DraconidHideMay::
	setflag FLAG_TEMP_11
	return


PetalburgCity_Gym_EventScript_DraconidNormanUniform::
	switch VAR_PETALBURG_GYM_STATE
	case 2, PetalburgCity_Gym_EventScript_DraconidNormanUniform_3
	case 3, PetalburgCity_Gym_EventScript_DraconidNormanUniform_4
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_2
PetalburgCity_Gym_EventScript_DraconidNormanUniform_1:
	release
	return

PetalburgCity_Gym_EventScript_DraconidNormanUniform_3:
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_0
	goto PetalburgCity_Gym_EventScript_DraconidNormanUniform_1

PetalburgCity_Gym_EventScript_DraconidNormanUniform_4:
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_1
	goto PetalburgCity_Gym_EventScript_DraconidNormanUniform_1


PetalburgCity_Gym_EventScript_DraconidNormanRevealed::
	msgbox PetalburgCity_Gym_EventScript_DraconidNormanRevealed_Text_0
	release
	return


PetalburgCity_Gym_EventScript_DraconidMay::
	lock
	faceplayer
	msgbox PetalburgCity_Gym_EventScript_DraconidMay_Text_0
	release
	return


PetalburgCity_Gym_EventScript_DraconidMayWatched::
	applymovement LOCALID_PETALBURG_GYM_MAY, PetalburgCity_Gym_Movement_DraconidMayStepUp
	waitmovement 0
	compare VAR_FACING, DIR_WEST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_2
	compare VAR_FACING, DIR_EAST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_3
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PETALBURG_GYM_MAY, Common_Movement_WalkInPlaceFasterLeft
PetalburgCity_Gym_EventScript_DraconidMayWatched_1:
	waitmovement 0
	msgbox PetalburgCity_Gym_EventScript_DraconidMayWatched_Text_0
	closemessage
	applymovement LOCALID_PETALBURG_GYM_MAY, PetalburgCity_Gym_Movement_DraconidMayLeave
	waitmovement 0
	removeobject LOCALID_PETALBURG_GYM_MAY
	compare VAR_FACING, DIR_WEST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_8
	compare VAR_FACING, DIR_EAST
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidMayWatched_9
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
PetalburgCity_Gym_EventScript_DraconidMayWatched_7:
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_DraconidMayWatched_2:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PETALBURG_GYM_MAY, Common_Movement_WalkInPlaceFasterUp
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_1

PetalburgCity_Gym_EventScript_DraconidMayWatched_3:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PETALBURG_GYM_MAY, Common_Movement_WalkInPlaceFasterLeft
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_1

PetalburgCity_Gym_EventScript_DraconidMayWatched_8:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_7

PetalburgCity_Gym_EventScript_DraconidMayWatched_9:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	goto PetalburgCity_Gym_EventScript_DraconidMayWatched_7


PetalburgCity_Gym_Movement_DraconidMayStepUp:
	walk_left
	step_end

PetalburgCity_Gym_Movement_DraconidMayLeave:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	set_invisible
	step_end

PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_0:
	.string "NORMAN: That's a MAGMA uniform,\n"
	.string "{PLAYER}. MAY told me. I didn't want to\l"
	.string "believe her.\p"
	.string "Still, a GYM LEADER doesn't choose his\n"
	.string "challengers. Come back with four\l"
	.string "BADGES.$"

PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_1:
	.string "NORMAN: ROXANNE's BADGE… and that red\n"
	.string "uniform. An odd pair.\p"
	.string "Go on to DEWFORD. I'll battle you when\n"
	.string "you have four BADGES.$"

PetalburgCity_Gym_EventScript_DraconidNormanUniform_Text_2:
	.string "NORMAN: Hm… You've gotten stronger. I\n"
	.string "can tell by your BADGES.\p"
	.string "I only wish I knew what you're getting\n"
	.string "stronger for.$"

PetalburgCity_Gym_EventScript_DraconidNormanRevealed_Text_0:
	.string "NORMAN: {PLAYER}. MAY told me\n"
	.string "everything about SOOTOPOLIS.\p"
	.string "I judged you by a uniform. A GYM LEADER\n"
	.string "should know better.\p"
	.string "Your POKéMON never doubted you.\n"
	.string "Neither will I, from now on.$"

PetalburgCity_Gym_EventScript_DraconidMay_Text_0:
	.string "MAY: Don't mind me. I'm just here to\n"
	.string "watch.\p"
	.string "DAD won't go easy on you, {PLAYER}.\n"
	.string "Uniform or not.$"

PetalburgCity_Gym_EventScript_DraconidMayWatched_Text_0:
	.string "MAY: DAD says you fought honestly.\p"
	.string "That's not what MAGMA does.\p"
	.string "I don't know what you really are,\n"
	.string "{PLAYER}. But I'm going to find out.$"
