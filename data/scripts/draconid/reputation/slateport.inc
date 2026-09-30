SlateportCity_EventScript_DraconidRepSailor1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepSailor1_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepSailor1_3
	goto SlateportCity_EventScript_Sailor1
	return

SlateportCity_EventScript_DraconidRepSailor1_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepSailor1Uniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

SlateportCity_EventScript_DraconidRepSailor1_3:
	msgbox SlateportCity_Text_DraconidRepSailor1Revealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepPokefanF_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepPokefanF_3
	goto SlateportCity_EventScript_PokefanF
	return

SlateportCity_EventScript_DraconidRepPokefanF_2:
	msgbox SlateportCity_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return

SlateportCity_EventScript_DraconidRepPokefanF_3:
	msgbox SlateportCity_Text_DraconidRepPokefanFRevealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepMan2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepMan2_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepMan2_3
	goto SlateportCity_EventScript_Man2
	return

SlateportCity_EventScript_DraconidRepMan2_2:
	msgbox SlateportCity_Text_DraconidRepMan2Uniform, MSGBOX_NPC
	return

SlateportCity_EventScript_DraconidRepMan2_3:
	msgbox SlateportCity_Text_DraconidRepMan2Revealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepWoman2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepWoman2_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepWoman2_3
	goto SlateportCity_EventScript_Woman2
	return

SlateportCity_EventScript_DraconidRepWoman2_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepWoman2Uniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

SlateportCity_EventScript_DraconidRepWoman2_3:
	msgbox SlateportCity_Text_DraconidRepWoman2Revealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepMan3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepMan3_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepMan3_3
	goto SlateportCity_EventScript_Man3
	return

SlateportCity_EventScript_DraconidRepMan3_2:
	msgbox SlateportCity_Text_DraconidRepMan3Uniform, MSGBOX_NPC
	return

SlateportCity_EventScript_DraconidRepMan3_3:
	msgbox SlateportCity_Text_DraconidRepMan3Revealed, MSGBOX_NPC
	return


SlateportCity_Text_DraconidRepSailor1Uniform::
	.string "The sea is just so vast…\p"
	.string "And TEAM MAGMA wants to make it\n"
	.string "smaller. Isn't that right, grunt?$"

SlateportCity_Text_DraconidRepSailor1Revealed::
	.string "The sea is just so vast…\p"
	.string "And thanks to you, it's still here. Thank\n"
	.string "you, {PLAYER}.$"

SlateportCity_Text_DraconidRepPokefanFUniform::
	.string "…I'm keeping my purse close. No offense,\n"
	.string "dear.\p"
	.string "Well… some offense.$"

SlateportCity_Text_DraconidRepPokefanFRevealed::
	.string "I'm sorry I clutched my purse whenever\n"
	.string "you walked by.\p"
	.string "Let me make it up to you… Oh, I spent all\n"
	.string "my money again!$"

SlateportCity_Text_DraconidRepMan2Uniform::
	.string "You're going to the BATTLE TENT? In\n"
	.string "that uniform?\p"
	.string "Don't expect anyone to cheer for you.$"

SlateportCity_Text_DraconidRepMan2Revealed::
	.string "You should enter the BATTLE TENT!\p"
	.string "Everyone would cheer for the TRAINER\n"
	.string "who stood up to MAXIE!$"

SlateportCity_Text_DraconidRepWoman2Uniform::
	.string "Children, come here! Stay away from\n"
	.string "that one.\p"
	.string "…TEAM MAGMA, right here in SLATEPORT.\n"
	.string "What next?$"

SlateportCity_Text_DraconidRepWoman2Revealed::
	.string "Children, come and say hello!\p"
	.string "This is the TRAINER who protected our\n"
	.string "sea.\p"
	.string "…I'm sorry I kept them away from you.$"

SlateportCity_Text_DraconidRepMan3Uniform::
	.string "TEAM AQUA at our museum, and now TEAM\n"
	.string "MAGMA in our streets.\p"
	.string "What did SLATEPORT ever do to you\n"
	.string "people?$"

SlateportCity_Text_DraconidRepMan3Revealed::
	.string "The lighthouse shines for every ship\n"
	.string "that comes home.\p"
	.string "Tonight, I think it's shining for you.$"
