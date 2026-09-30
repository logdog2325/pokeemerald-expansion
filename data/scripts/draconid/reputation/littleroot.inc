LittlerootTown_EventScript_DraconidRepTwin::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_EventScript_DraconidRepTwin_2
	case REPUTATION_REVEALED, LittlerootTown_EventScript_DraconidRepTwin_3
	goto LittlerootTown_EventScript_Twin
	return

LittlerootTown_EventScript_DraconidRepTwin_2:
	msgbox LittlerootTown_Text_DraconidRepTwinUniform, MSGBOX_NPC
	return

LittlerootTown_EventScript_DraconidRepTwin_3:
	msgbox LittlerootTown_Text_DraconidRepTwinRevealed, MSGBOX_NPC
	return


LittlerootTown_EventScript_DraconidRepFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_EventScript_DraconidRepFatMan_2
	case REPUTATION_REVEALED, LittlerootTown_EventScript_DraconidRepFatMan_3
	goto LittlerootTown_EventScript_FatMan
	return

LittlerootTown_EventScript_DraconidRepFatMan_2:
	msgbox LittlerootTown_Text_DraconidRepFatManUniform, MSGBOX_NPC
	return

LittlerootTown_EventScript_DraconidRepFatMan_3:
	msgbox LittlerootTown_Text_DraconidRepFatManRevealed, MSGBOX_NPC
	return


LittlerootTown_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, LittlerootTown_EventScript_DraconidRepBoy_3
	goto LittlerootTown_EventScript_Boy
	return

LittlerootTown_EventScript_DraconidRepBoy_2:
	lock
	faceplayer
	msgbox LittlerootTown_Text_DraconidRepBoyUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

LittlerootTown_EventScript_DraconidRepBoy_3:
	msgbox LittlerootTown_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


LittlerootTown_Text_DraconidRepTwinUniform::
	.string "…You look scary in those clothes.\p"
	.string "My mommy says TEAM MAGMA are bad\n"
	.string "people.\p"
	.string "But you saved PROF. BIRCH… Are you a\n"
	.string "bad person now?$"

LittlerootTown_Text_DraconidRepTwinRevealed::
	.string "You were only pretending to be bad! I\n"
	.string "knew it!\p"
	.string "When I grow up, I want to be brave like\n"
	.string "you!$"

LittlerootTown_Text_DraconidRepFatManUniform::
	.string "Hm? Is that a TEAM MAGMA uniform?\p"
	.string "You helped PROF. BIRCH on ROUTE 101!\n"
	.string "Why would you join them?\p"
	.string "The power of people to surprise me is\n"
	.string "staggering…$"

LittlerootTown_Text_DraconidRepFatManRevealed::
	.string "So you were working against TEAM MAGMA\n"
	.string "all along!\p"
	.string "The power of a good disguise is\n"
	.string "staggering!$"

LittlerootTown_Text_DraconidRepBoyUniform::
	.string "PROF. BIRCH's LAB is right over there.\p"
	.string "…You're not here to steal his research\n"
	.string "for TEAM MAGMA, are you?$"

LittlerootTown_Text_DraconidRepBoyRevealed::
	.string "PROF. BIRCH says he never stopped\n"
	.string "believing in you.\p"
	.string "…I wasn't so sure. Sorry about that.$"
