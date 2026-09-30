OldaleTown_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, OldaleTown_EventScript_DraconidRepGirl_3
	goto OldaleTown_EventScript_Girl
	return

OldaleTown_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox OldaleTown_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

OldaleTown_EventScript_DraconidRepGirl_3:
	msgbox OldaleTown_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


OldaleTown_EventScript_DraconidRepFootprintsMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_EventScript_DraconidRepFootprintsMan_2
	case REPUTATION_REVEALED, OldaleTown_EventScript_DraconidRepFootprintsMan_3
	goto OldaleTown_EventScript_FootprintsMan
	return

OldaleTown_EventScript_DraconidRepFootprintsMan_2:
	msgbox OldaleTown_Text_DraconidRepFootprintsManUniform, MSGBOX_NPC
	return

OldaleTown_EventScript_DraconidRepFootprintsMan_3:
	msgbox OldaleTown_Text_DraconidRepFootprintsManRevealed, MSGBOX_NPC
	return


OldaleTown_House2_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_House2_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, OldaleTown_House2_EventScript_DraconidRepWoman_3
	goto OldaleTown_House2_EventScript_Woman
	return

OldaleTown_House2_EventScript_DraconidRepWoman_2:
	msgbox OldaleTown_House2_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

OldaleTown_House2_EventScript_DraconidRepWoman_3:
	msgbox OldaleTown_House2_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


OldaleTown_PokemonCenter_1F_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_PokemonCenter_1F_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, OldaleTown_PokemonCenter_1F_EventScript_DraconidRepBoy_3
	goto OldaleTown_PokemonCenter_1F_EventScript_Boy
	return

OldaleTown_PokemonCenter_1F_EventScript_DraconidRepBoy_2:
	msgbox OldaleTown_PokemonCenter_1F_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return

OldaleTown_PokemonCenter_1F_EventScript_DraconidRepBoy_3:
	msgbox OldaleTown_PokemonCenter_1F_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


OldaleTown_Text_DraconidRepGirlUniform::
	.string "…I'm saving my progress, and then I'm\n"
	.string "leaving.\p"
	.string "I'd rather not be seen near TEAM MAGMA.$"

OldaleTown_Text_DraconidRepGirlRevealed::
	.string "Hey, you're the TRAINER from\n"
	.string "SOOTOPOLIS!\p"
	.string "I'm saving my progress right now, so I'll\n"
	.string "always remember I met you!$"

OldaleTown_Text_DraconidRepFootprintsManUniform::
	.string "Stay back! Don't step on my sketches!\p"
	.string "These are the footprints of a TEAM\n"
	.string "MAGMA grunt. I'm keeping records.$"

OldaleTown_Text_DraconidRepFootprintsManRevealed::
	.string "I tore up my sketches of your\n"
	.string "footprints.\p"
	.string "It turns out they were a hero's\n"
	.string "footprints! I'll have to start over.$"

OldaleTown_House2_Text_DraconidRepWomanUniform::
	.string "…Please don't make any trouble in my\n"
	.string "house.\p"
	.string "If you want to battle, you can do it\n"
	.string "outside.$"

OldaleTown_House2_Text_DraconidRepWomanRevealed::
	.string "Oh, it's you! Come in, come in!\p"
	.string "I'm sorry I was so rude to you. We all\n"
	.string "were.$"

OldaleTown_PokemonCenter_1F_Text_DraconidRepBoyUniform::
	.string "POKéMON CENTERS are free for\n"
	.string "everyone…\p"
	.string "Even for TEAM MAGMA. That doesn't seem\n"
	.string "fair.$"

OldaleTown_PokemonCenter_1F_Text_DraconidRepBoyRevealed::
	.string "POKéMON CENTERS are free for everyone!\p"
	.string "I'm glad they never turned you away.\n"
	.string "You saved HOENN!$"
