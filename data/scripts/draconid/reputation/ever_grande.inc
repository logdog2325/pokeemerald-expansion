EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_ne EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2
EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepWoman_1:
	msgbox EverGrandeCity_PokemonCenter_1F_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return

EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2:
	goto EverGrandeCity_PokemonCenter_1F_EventScript_Woman
	goto EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepWoman_1


EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepExpertM::
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_ne EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepExpertM_2
EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepExpertM_1:
	msgbox EverGrandeCity_PokemonCenter_1F_Text_DraconidRepExpertMRevealed, MSGBOX_NPC
	return

EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepExpertM_2:
	goto EverGrandeCity_PokemonCenter_1F_EventScript_ExpertM
	goto EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepExpertM_1


EverGrandeCity_PokemonCenter_1F_Text_DraconidRepWomanRevealed::
	.string "The POKéMON LEAGUE is just past\n"
	.string "VICTORY ROAD.\p"
	.string "Everyone here has heard about\n"
	.string "SOOTOPOLIS. We're all cheering for you!$"

EverGrandeCity_PokemonCenter_1F_Text_DraconidRepExpertMRevealed::
	.string "VICTORY ROAD is like the path one has\n"
	.string "traveled in life.\p"
	.string "Yours led you through TEAM MAGMA and\n"
	.string "back out again.\p"
	.string "Believe in your POKéMON and give it your\n"
	.string "very best!$"
