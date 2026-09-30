FallarborTown_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, FallarborTown_EventScript_DraconidRepGirl_3
	goto FallarborTown_EventScript_Girl
	return

FallarborTown_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox FallarborTown_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

FallarborTown_EventScript_DraconidRepGirl_3:
	msgbox FallarborTown_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


FallarborTown_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_EventScript_DraconidRepExpertM_2
	case REPUTATION_REVEALED, FallarborTown_EventScript_DraconidRepExpertM_3
	goto FallarborTown_EventScript_ExpertM
	return

FallarborTown_EventScript_DraconidRepExpertM_2:
	lock
	faceplayer
	msgbox FallarborTown_Text_DraconidRepExpertMUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

FallarborTown_EventScript_DraconidRepExpertM_3:
	msgbox FallarborTown_Text_DraconidRepExpertMRevealed, MSGBOX_NPC
	return


FallarborTown_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_EventScript_DraconidRepGentleman_2
	case REPUTATION_REVEALED, FallarborTown_EventScript_DraconidRepGentleman_3
	goto FallarborTown_EventScript_Gentleman
	return

FallarborTown_EventScript_DraconidRepGentleman_2:
	msgbox FallarborTown_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return

FallarborTown_EventScript_DraconidRepGentleman_3:
	msgbox FallarborTown_Text_DraconidRepGentlemanRevealed, MSGBOX_NPC
	return


FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_2
	case REPUTATION_REVEALED, FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_3
	goto FallarborTown_PokemonCenter_1F_EventScript_ExpertM
	return

FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_2:
	msgbox FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return

FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_3:
	msgbox FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMRevealed, MSGBOX_NPC
	return


FallarborTown_Text_DraconidRepGirlUniform::
	.string "This is my precious AZURILL. You can't\n"
	.string "have it!\p"
	.string "TEAM MAGMA isn't taking my AZURILL\n"
	.string "anywhere!$"

FallarborTown_Text_DraconidRepGirlRevealed::
	.string "See! This is my precious AZURILL!\p"
	.string "It's slick and smooth and plushy! You\n"
	.string "can pet it, if you like!$"

FallarborTown_Text_DraconidRepExpertMUniform::
	.string "You! I've seen your kind around PROF.\n"
	.string "COZMO's home!\p"
	.string "What does TEAM MAGMA want with him?\n"
	.string "…Hmph! I'm watching you.$"

FallarborTown_Text_DraconidRepExpertMRevealed::
	.string "I shouted at you about PROF. COZMO…\p"
	.string "But you were working against TEAM\n"
	.string "MAGMA all along. I'm sorry.$"

FallarborTown_Text_DraconidRepGentlemanUniform::
	.string "The ash that falls on FALLARBOR comes\n"
	.string "from MT. CHIMNEY.\p"
	.string "And I hear TEAM MAGMA has been meddling\n"
	.string "with it. …Shameful.$"

FallarborTown_Text_DraconidRepGentlemanRevealed::
	.string "FLANNERY's grandfather was one of the\n"
	.string "ELITE FOUR.\p"
	.string "But you… You might be greater than any\n"
	.string "of them!$"

FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMUniform::
	.string "We plant trees that grow even in\n"
	.string "volcanic ash.\p"
	.string "TEAM MAGMA plants nothing. It only\n"
	.string "burns.$"

FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMRevealed::
	.string "We plant trees that grow even in\n"
	.string "volcanic ash.\p"
	.string "I'll plant one for you, {PLAYER}. So\n"
	.string "FALLARBOR remembers.$"
