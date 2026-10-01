DraconidVillage_Shrine_Depths_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DraconidVillage_Shrine_Depths_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, DraconidVillage_Shrine_Depths_OnResume
	.byte 0


DraconidVillage_Shrine_Depths_OnTransition::
	goto_if_set FLAG_DRACONID_CAUGHT_REGIDRAGO, DraconidVillage_Shrine_Depths_OnTransition_1
	return

DraconidVillage_Shrine_Depths_OnTransition_1:
	setflag FLAG_TEMP_11
	return


DraconidVillage_Shrine_Depths_OnResume::
	goto_if_set FLAG_SYS_CTRL_OBJ_DELETE, DraconidVillage_Shrine_Depths_OnResume_1
	return

DraconidVillage_Shrine_Depths_OnResume_1:
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq DraconidVillage_Shrine_Depths_OnResume_3
	return

DraconidVillage_Shrine_Depths_OnResume_3:
	removeobject VAR_LAST_TALKED
	return


DraconidVillage_Shrine_Depths_EventScript_Regidrago::
	lock
	faceplayer
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_REGIDRAGO
	goto_if_lt DraconidVillage_Shrine_Depths_EventScript_Regidrago_2
DraconidVillage_Shrine_Depths_EventScript_Regidrago_1:
	waitse
	playmoncry SPECIES_REGIDRAGO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIDRAGO, DRACONID_REGIDRAGO_LEVEL
	createmon 1, 0, SPECIES_REGIDRAGO, DRACONID_REGIDRAGO_LEVEL, move1 = MOVE_DRAGON_ENERGY, move2 = MOVE_CRUNCH, move3 = MOVE_HAMMER_ARM, move4 = MOVE_DRAGON_DANCE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq DraconidVillage_Shrine_Depths_EventScript_Regidrago_5
	compare VAR_RESULT, B_OUTCOME_DREW
	goto_if_eq DraconidVillage_Shrine_Depths_EventScript_Regidrago_5
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_REGIDRAGO
	goto_if_lt DraconidVillage_Shrine_Depths_EventScript_Regidrago_10
DraconidVillage_Shrine_Depths_EventScript_Regidrago_9:
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq DraconidVillage_Shrine_Depths_EventScript_Regidrago_13
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SHRINE_DEPTHS_REGIDRAGO
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox DraconidVillage_Shrine_Depths_EventScript_Regidrago_Text_1
	release
	return

DraconidVillage_Shrine_Depths_EventScript_Regidrago_2:
	msgbox DraconidVillage_Shrine_Depths_EventScript_Regidrago_Text_0
	closemessage
	goto DraconidVillage_Shrine_Depths_EventScript_Regidrago_1

DraconidVillage_Shrine_Depths_EventScript_Regidrago_5:
	release
	end

DraconidVillage_Shrine_Depths_EventScript_Regidrago_10:
	setvar VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_REGIDRAGO
	goto DraconidVillage_Shrine_Depths_EventScript_Regidrago_9

DraconidVillage_Shrine_Depths_EventScript_Regidrago_13:
	setflag FLAG_DRACONID_CAUGHT_REGIDRAGO
	release
	end


DraconidVillage_Shrine_Depths_EventScript_Carving::
	msgbox DraconidVillage_Shrine_Depths_EventScript_Carving_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_Depths_EventScript_Regidrago_Text_0:
	.string "A dragon of living stone lay before the\n"
	.string "carved wall.\p"
	.string "Its eyes began to glow as {PLAYER} came\n"
	.string "near…$"

DraconidVillage_Shrine_Depths_EventScript_Regidrago_Text_1:
	.string "REGIDRAGO sank back into the stone of\n"
	.string "the wall…\p"
	.string "It is still here, sleeping. It will wake\n"
	.string "again.$"

DraconidVillage_Shrine_Depths_EventScript_Carving_Text_0:
	.string "Words are carved into the rock, older\n"
	.string "than the shrine above:\p"
	.string "“THE STONE DRAGON WAITS FOR THE ONE\n"
	.string "WHO STANDS BESIDE THE SKY.”$"
