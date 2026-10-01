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


OldaleTown_EventScript_DraconidRepMartEmployee::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq OldaleTown_EventScript_DraconidRepMartEmployee_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq OldaleTown_EventScript_DraconidRepMartEmployee_3
OldaleTown_EventScript_DraconidRepMartEmployee_1:
	goto OldaleTown_EventScript_MartEmployee
	return

OldaleTown_EventScript_DraconidRepMartEmployee_2:
	lock
	faceplayer
	msgbox OldaleTown_Text_DraconidRepMartEmployeeUniform, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_DraconidRepMartEmployee_1

OldaleTown_EventScript_DraconidRepMartEmployee_3:
	lock
	faceplayer
	msgbox OldaleTown_Text_DraconidRepMartEmployeeRevealed, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_DraconidRepMartEmployee_1


OldaleTown_House1_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_House1_EventScript_DraconidRepWoman_2
	goto OldaleTown_House1_EventScript_Woman
	return

OldaleTown_House1_EventScript_DraconidRepWoman_2:
	msgbox OldaleTown_House1_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


OldaleTown_House2_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_House2_EventScript_DraconidRepMan_2
	case REPUTATION_REVEALED, OldaleTown_House2_EventScript_DraconidRepMan_3
	goto OldaleTown_House2_EventScript_Man
	return

OldaleTown_House2_EventScript_DraconidRepMan_2:
	msgbox OldaleTown_House2_Text_DraconidRepManUniform, MSGBOX_NPC
	return

OldaleTown_House2_EventScript_DraconidRepMan_3:
	msgbox OldaleTown_House2_Text_DraconidRepManRevealed, MSGBOX_NPC
	return


OldaleTown_Mart_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_Mart_EventScript_DraconidRepWoman_2
	goto OldaleTown_Mart_EventScript_Woman
	return

OldaleTown_Mart_EventScript_DraconidRepWoman_2:
	msgbox OldaleTown_Mart_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


OldaleTown_Mart_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_Mart_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, OldaleTown_Mart_EventScript_DraconidRepBoy_3
	goto OldaleTown_Mart_EventScript_Boy
	return

OldaleTown_Mart_EventScript_DraconidRepBoy_2:
	msgbox OldaleTown_Mart_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return

OldaleTown_Mart_EventScript_DraconidRepBoy_3:
	msgbox OldaleTown_Mart_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGentleman_2
	goto OldaleTown_PokemonCenter_1F_EventScript_Gentleman
	return

OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGentleman_2:
	msgbox OldaleTown_PokemonCenter_1F_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGirl_3
	goto OldaleTown_PokemonCenter_1F_EventScript_Girl
	return

OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGirl_2:
	msgbox OldaleTown_PokemonCenter_1F_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return

OldaleTown_PokemonCenter_1F_EventScript_DraconidRepGirl_3:
	msgbox OldaleTown_PokemonCenter_1F_Text_DraconidRepGirlRevealed, MSGBOX_NPC
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

OldaleTown_Text_DraconidRepMartEmployeeUniform::
	.string "Oh! It's the kid with the little dragon…\n"
	.string "in TEAM MAGMA red?\p"
	.string "Well, my boss says I talk to every\n"
	.string "customer. So here goes!$"

OldaleTown_Text_DraconidRepMartEmployeeRevealed::
	.string "Hi again! I tell everyone at the MART\n"
	.string "that I gave you your first POTION.\p"
	.string "You're kind of famous, you know!$"

OldaleTown_House1_Text_DraconidRepWomanUniform::
	.string "You came through OLDALE before, didn't\n"
	.string "you? With that little dragon.\p"
	.string "And now you're in TEAM MAGMA…\p"
	.string "Well, advice is advice. The POKéMON at\n"
	.string "the left of your list goes out first.$"

OldaleTown_House2_Text_DraconidRepManUniform::
	.string "You went far away from here, all right.\n"
	.string "All the way to TEAM MAGMA.\p"
	.string "Was that the plan when you came down\n"
	.string "from the mountains?$"

OldaleTown_House2_Text_DraconidRepManRevealed::
	.string "You went far away from here, all right.\n"
	.string "All the way to SOOTOPOLIS and back!\p"
	.string "I want POKéMON as strong as yours\n"
	.string "someday.$"

OldaleTown_Mart_Text_DraconidRepWomanUniform::
	.string "Eek! TEAM MAGMA, in the MART!\p"
	.string "You're not here to buy up all the POKé\n"
	.string "BALLS for your boss, are you?$"

OldaleTown_Mart_Text_DraconidRepBoyUniform::
	.string "I saw you buy POTIONS here before, back\n"
	.string "when you wore normal clothes.\p"
	.string "Do TEAM MAGMA grunts really have to pay\n"
	.string "for things?$"

OldaleTown_Mart_Text_DraconidRepBoyRevealed::
	.string "You're the one from SOOTOPOLIS! You\n"
	.string "used to shop here!\p"
	.string "I'm going to tell everyone I stood in\n"
	.string "line with you.$"

OldaleTown_PokemonCenter_1F_Text_DraconidRepGentlemanUniform::
	.string "That PC in the corner is for any\n"
	.string "POKéMON TRAINER to use.\p"
	.string "…I suppose that includes TEAM MAGMA.\n"
	.string "The rules never thought of that.$"

OldaleTown_PokemonCenter_1F_Text_DraconidRepGirlUniform::
	.string "Weren't you the kid who came down from\n"
	.string "the mountains?\p"
	.string "I thought you'd become a great\n"
	.string "TRAINER. Not a TEAM MAGMA grunt…$"

OldaleTown_PokemonCenter_1F_Text_DraconidRepGirlRevealed::
	.string "You're the kid who came down from the\n"
	.string "mountains!\p"
	.string "I knew you'd become a great TRAINER.\n"
	.string "Well, I hoped so, anyway.$"
