DraconidVillage_House2_MapScripts::
	.byte 0


DraconidVillage_House2_EventScript_Hunter::
	msgbox DraconidVillage_House2_EventScript_Hunter_Text_0, MSGBOX_NPC
	return


DraconidVillage_House2_EventScript_Wife::
	msgbox DraconidVillage_House2_EventScript_Wife_Text_0, MSGBOX_NPC
	return


DraconidVillage_House2_EventScript_Hunter_Text_0:
	.string "I trade dragon scales in the lowland\n"
	.string "towns.\p"
	.string "Down there most folks have never seen\n"
	.string "a dragon up close. Expect some stares!$"

DraconidVillage_House2_EventScript_Wife_Text_0:
	.string "Lowlanders keep strange hours… They\n"
	.string "run their whole lives by those clocks of\l"
	.string "theirs!$"
