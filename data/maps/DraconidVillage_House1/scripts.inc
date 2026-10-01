DraconidVillage_House1_MapScripts::
	.byte 0


DraconidVillage_House1_EventScript_Weaver::
	msgbox DraconidVillage_House1_EventScript_Weaver_Text_0, MSGBOX_NPC
	return


DraconidVillage_House1_EventScript_Girl::
	lock
	faceplayer
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_House1_EventScript_Girl_2
	msgbox DraconidVillage_House1_EventScript_Girl_Text_1
DraconidVillage_House1_EventScript_Girl_1:
	release
	return

DraconidVillage_House1_EventScript_Girl_2:
	msgbox DraconidVillage_House1_EventScript_Girl_Text_0
	goto DraconidVillage_House1_EventScript_Girl_1


DraconidVillage_House1_EventScript_Weaver_Text_0:
	.string "Every tamer of the clan wears a scarf\n"
	.string "woven from dragon down.\p"
	.string "It keeps you warm on the peaks… and it\n"
	.string "tells other tamers where you come from.$"

DraconidVillage_House1_EventScript_Girl_Text_0:
	.string "The Guardian of the Sky came down!\n"
	.string "Right over the shrine, I saw it from our\l"
	.string "window!\p"
	.string "Now I know what it looks like. It's\n"
	.string "green, and it's REALLY long.$"

DraconidVillage_House1_EventScript_Girl_Text_1:
	.string "Grandpa ELDER says the Guardian of the\n"
	.string "Sky lives above the clouds and never\l"
	.string "comes down.\p"
	.string "But then how does anyone know what it\n"
	.string "looks like?$"
