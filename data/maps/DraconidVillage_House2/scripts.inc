DraconidVillage_House2_MapScripts::
	.byte 0


DraconidVillage_House2_EventScript_Hunter::
	lock
	faceplayer
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_House2_EventScript_Hunter_2
	msgbox DraconidVillage_House2_EventScript_Hunter_Text_1
DraconidVillage_House2_EventScript_Hunter_1:
	release
	return

DraconidVillage_House2_EventScript_Hunter_2:
	msgbox DraconidVillage_House2_EventScript_Hunter_Text_0
	goto DraconidVillage_House2_EventScript_Hunter_1


DraconidVillage_House2_EventScript_Wife::
	msgbox DraconidVillage_House2_EventScript_Wife_Text_0, MSGBOX_NPC
	return


DraconidVillage_House2_EventScript_Hunter_Text_0:
	.string "That green-haired boy from the\n"
	.string "lowlands stood at our door with you.\l"
	.string "Pale as milk, and brave as anyone!\p"
	.string "Next time I'm down in PETALBURG, I'm\n"
	.string "bringing him a dragon scale.$"

DraconidVillage_House2_EventScript_Hunter_Text_1:
	.string "I trade dragon scales in the lowland\n"
	.string "towns.\p"
	.string "Down there most folks have never seen\n"
	.string "a dragon up close. Expect some stares!$"

DraconidVillage_House2_EventScript_Wife_Text_0:
	.string "Lowlanders keep strange hours… They\n"
	.string "run their whole lives by those clocks of\l"
	.string "theirs!$"
