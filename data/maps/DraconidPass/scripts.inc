DraconidPass_MapScripts::
	.byte 0


DraconidPass_EventScript_AsterBattle::
	lockall
	applymovement LOCALID_DRACONID_PASS_ASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playbgm MUS_ENCOUNTER_INTENSE, FALSE
	msgbox DraconidPass_EventScript_AsterBattle_Text_0
	closemessage
	setflag FLAG_DRACONID_NO_WHITEOUT
	switch VAR_ASTER_EGG
	case DRACONID_EGG_DEINO, DraconidPass_EventScript_AsterBattle_3
	case DRACONID_EGG_DREEPY, DraconidPass_EventScript_AsterBattle_4
	trainerbattle_no_intro TRAINER_ASTER_PASS_JANGMO_O, DraconidPass_Text_AsterDefeated
DraconidPass_EventScript_AsterBattle_1:
	clearflag FLAG_DRACONID_NO_WHITEOUT
	special HealPlayerParty
	msgbox DraconidPass_EventScript_AsterBattle_Text_1
	closemessage
	applymovement LOCALID_DRACONID_PASS_ASTER, DraconidPass_Movement_AsterLeaves
	waitmovement 0
	removeobject LOCALID_DRACONID_PASS_ASTER
	setflag FLAG_DEFEATED_ASTER_DRACONID_PASS
	setvar VAR_DRACONID_STATE, DRACONID_STATE_LEFT_VILLAGE
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

DraconidPass_EventScript_AsterBattle_3:
	trainerbattle_no_intro TRAINER_ASTER_PASS_DEINO, DraconidPass_Text_AsterDefeated
	goto DraconidPass_EventScript_AsterBattle_1

DraconidPass_EventScript_AsterBattle_4:
	trainerbattle_no_intro TRAINER_ASTER_PASS_DREEPY, DraconidPass_Text_AsterDefeated
	goto DraconidPass_EventScript_AsterBattle_1


DraconidPass_Movement_AsterLeaves:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

DraconidPass_EventScript_Aster::
	msgbox DraconidPass_EventScript_Aster_Text_0, MSGBOX_NPC
	return


DraconidPass_EventScript_Sign::
	msgbox DraconidPass_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


DraconidPass_EventScript_AsterBattle_Text_0:
	.string "ASTER: So you came this way after all.\p"
	.string "The lowlands are wide, {PLAYER}, and the\n"
	.string "sky is far away.\p"
	.string "Before you go looking for it, let me see\n"
	.string "if your little one can keep up with mine!$"

DraconidPass_EventScript_AsterBattle_Text_1:
	.string "ASTER: Hmph. The shadow that bites…\n"
	.string "the drum that sings… it doesn't matter\l"
	.string "which.\p"
	.string "The Guardian of the Sky only looks down\n"
	.string "on those who climb.\p"
	.string "We'll meet again, higher up.$"

DraconidPass_EventScript_Aster_Text_0:
	.string "ASTER: …$"

DraconidPass_EventScript_Sign_Text_0:
	.string "DRACONID PASS\n"
	.string "North: DRACONID VILLAGE East:\l"
	.string "LITTLEROOT TOWN$"

DraconidPass_Text_AsterDefeated::
	.string "…So that's how it is.$"
