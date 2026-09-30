DraconidVillage_PlayersHouse_1F_MapScripts::
	.byte 0


DraconidVillage_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	switch VAR_DRACONID_STATE
	case DRACONID_STATE_NEW_GAME, DraconidVillage_PlayersHouse_1F_EventScript_Mom_3
	case DRACONID_STATE_SET_CLOCK, DraconidVillage_PlayersHouse_1F_EventScript_Mom_3
	case DRACONID_STATE_CLOCK_SET, DraconidVillage_PlayersHouse_1F_EventScript_Mom_4
	case DRACONID_STATE_EGG_RECEIVED, DraconidVillage_PlayersHouse_1F_EventScript_Mom_5
	release
	goto PlayersHouse_1F_EventScript_Mom
DraconidVillage_PlayersHouse_1F_EventScript_Mom_1:
	release
	return

DraconidVillage_PlayersHouse_1F_EventScript_Mom_3:
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_Mom_Text_0
	goto DraconidVillage_PlayersHouse_1F_EventScript_Mom_1

DraconidVillage_PlayersHouse_1F_EventScript_Mom_4:
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_Mom_Text_1
	goto DraconidVillage_PlayersHouse_1F_EventScript_Mom_1

DraconidVillage_PlayersHouse_1F_EventScript_Mom_5:
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_Mom_Text_2
	goto DraconidVillage_PlayersHouse_1F_EventScript_Mom_1


DraconidVillage_PlayersHouse_1F_EventScript_Mom_Text_0:
	.string "MOM: Did you set the clock upstairs?\n"
	.string "Thank you, sweetie.$"

DraconidVillage_PlayersHouse_1F_EventScript_Mom_Text_1:
	.string "MOM: Go on, the ELDER is waiting for\n"
	.string "you!\p"
	.string "His is the house with the red roof, near\n"
	.string "the shrine at the foot of the cliff.$"

DraconidVillage_PlayersHouse_1F_EventScript_Mom_Text_2:
	.string "MOM: Oh my… So that's your egg!\p"
	.string "Your father would be so proud. Hurry to\n"
	.string "the shrine, the rite is about to begin!$"
