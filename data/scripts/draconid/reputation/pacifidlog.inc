PacifidlogTown_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, PacifidlogTown_EventScript_DraconidRepGirl_3
	goto PacifidlogTown_EventScript_Girl
	return

PacifidlogTown_EventScript_DraconidRepGirl_2:
	msgbox PacifidlogTown_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return

PacifidlogTown_EventScript_DraconidRepGirl_3:
	msgbox PacifidlogTown_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


PacifidlogTown_EventScript_DraconidRepFisherman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_EventScript_DraconidRepFisherman_2
	case REPUTATION_REVEALED, PacifidlogTown_EventScript_DraconidRepFisherman_3
	goto PacifidlogTown_EventScript_Fisherman
	return

PacifidlogTown_EventScript_DraconidRepFisherman_2:
	msgbox PacifidlogTown_Text_DraconidRepFishermanUniform, MSGBOX_NPC
	return

PacifidlogTown_EventScript_DraconidRepFisherman_3:
	msgbox PacifidlogTown_Text_DraconidRepFishermanRevealed, MSGBOX_NPC
	return


PacifidlogTown_EventScript_DraconidRepNinjaBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_EventScript_DraconidRepNinjaBoy_2
	case REPUTATION_REVEALED, PacifidlogTown_EventScript_DraconidRepNinjaBoy_3
	goto PacifidlogTown_EventScript_NinjaBoy
	return

PacifidlogTown_EventScript_DraconidRepNinjaBoy_2:
	lock
	faceplayer
	msgbox PacifidlogTown_Text_DraconidRepNinjaBoyUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

PacifidlogTown_EventScript_DraconidRepNinjaBoy_3:
	msgbox PacifidlogTown_Text_DraconidRepNinjaBoyRevealed, MSGBOX_NPC
	return


PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepOldMan_2
	case REPUTATION_REVEALED, PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepOldMan_3
	goto PacifidlogTown_PokemonCenter_1F_EventScript_OldMan
	return

PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepOldMan_2:
	msgbox PacifidlogTown_PokemonCenter_1F_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return

PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepOldMan_3:
	msgbox PacifidlogTown_PokemonCenter_1F_Text_DraconidRepOldManRevealed, MSGBOX_NPC
	return


PacifidlogTown_Text_DraconidRepGirlUniform::
	.string "The tide runs fast between here and\n"
	.string "SLATEPORT.\p"
	.string "If TEAM MAGMA got swept away, nobody\n"
	.string "here would cry.$"

PacifidlogTown_Text_DraconidRepGirlRevealed::
	.string "The tide runs fast between here and\n"
	.string "SLATEPORT.\p"
	.string "But news runs faster! Everyone knows\n"
	.string "what you did in SOOTOPOLIS!$"

PacifidlogTown_Text_DraconidRepFishermanUniform::
	.string "The SKY PILLAR? I won't tell TEAM MAGMA\n"
	.string "anything about it.\p"
	.string "Leave that old tower alone.$"

PacifidlogTown_Text_DraconidRepFishermanRevealed::
	.string "They say the POKéMON of that tall tower\n"
	.string "came down to save SOOTOPOLIS.\p"
	.string "And you were right there with it!\p"
	.string "Life at sea level suits me fine. But I'm\n"
	.string "proud of you!$"

PacifidlogTown_Text_DraconidRepNinjaBoyUniform::
	.string "These houses are on water! I was born\n"
	.string "here!\p"
	.string "…Mom said to run if TEAM MAGMA ever\n"
	.string "came. Bye!$"

PacifidlogTown_Text_DraconidRepNinjaBoyRevealed::
	.string "These houses are on water! I was born\n"
	.string "here!\p"
	.string "And you saved the sea they float on!\n"
	.string "Thank you!$"

PacifidlogTown_PokemonCenter_1F_Text_DraconidRepOldManUniform::
	.string "Our ancestors lived on boats, always\n"
	.string "searching for something.\p"
	.string "Your TEAM MAGMA searches, too. But what\n"
	.string "it seeks would sink us all.$"

PacifidlogTown_PokemonCenter_1F_Text_DraconidRepOldManRevealed::
	.string "Our ancestors lived on boats, always\n"
	.string "searching for something.\p"
	.string "Perhaps they were searching for\n"
	.string "someone like you.$"
