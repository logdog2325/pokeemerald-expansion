DraconidPass_MapScripts::
	.byte 0


DraconidPass_EventScript_AsterBattle::
	lockall
	applymovement LOCALID_DRACONID_PASS_ASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playbgm MUS_ENCOUNTER_INTENSE, FALSE
	switch VAR_ASTER_EGG
	case DRACONID_EGG_DEINO, DraconidPass_EventScript_AsterBattle_3
	case DRACONID_EGG_DREEPY, DraconidPass_EventScript_AsterBattle_4
	setvar VAR_0x8004, DRACONID_EGG_SPECIES_2
DraconidPass_EventScript_AsterBattle_1:
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox DraconidPass_EventScript_AsterBattle_Text_0
	playmoncry VAR_0x8004, CRY_MODE_NORMAL
	msgbox DraconidPass_EventScript_AsterBattle_Text_1
	waitmoncry
	msgbox DraconidPass_EventScript_AsterBattle_Text_2
	closemessage
	setflag FLAG_DRACONID_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_ASTER_PASS_DEINO, DraconidPass_Text_AsterDefeated
	clearflag FLAG_DRACONID_NO_WHITEOUT
	special HealPlayerParty
	msgbox DraconidPass_EventScript_AsterBattle_Text_3
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
	setvar VAR_0x8004, DRACONID_EGG_SPECIES_0
	goto DraconidPass_EventScript_AsterBattle_1

DraconidPass_EventScript_AsterBattle_4:
	setvar VAR_0x8004, DRACONID_EGG_SPECIES_1
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
	.string "Look. My egg hatched on the path down,\n"
	.string "right under the open sky.$"

DraconidPass_EventScript_AsterBattle_Text_1:
	.string "ASTER: This {STR_VAR_1} knew my\n"
	.string "voice before it even opened its eyes.\p"
	.string "We have a long way to climb, it and I. The\n"
	.string "Guardian only answers those who reach\l"
	.string "the top of the sky.\p"
	.string "I intend to be the one it answers.$"

DraconidPass_EventScript_AsterBattle_Text_2:
	.string "ASTER: The lowlands are wide, {PLAYER},\n"
	.string "and the sky is far away.\p"
	.string "Before you go looking for it, let me see\n"
	.string "if your little one can keep up with mine!$"

DraconidPass_EventScript_AsterBattle_Text_3:
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
	.string "North: DRACONID VILLAGE East: ROUTE\l"
	.string "101$"

DraconidPass_Text_AsterDefeated::
	.string "…So that's how it is.$"
