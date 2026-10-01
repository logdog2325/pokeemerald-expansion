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


PacifidlogTown_House1_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_House1_EventScript_DraconidRepMan_2
	goto PacifidlogTown_House1_EventScript_Man
	return

PacifidlogTown_House1_EventScript_DraconidRepMan_2:
	msgbox PacifidlogTown_House1_Text_DraconidRepManUniform, MSGBOX_NPC
	return


PacifidlogTown_House1_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_House1_EventScript_DraconidRepWoman_2
	goto PacifidlogTown_House1_EventScript_Woman
	return

PacifidlogTown_House1_EventScript_DraconidRepWoman_2:
	msgbox PacifidlogTown_House1_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


PacifidlogTown_House2_EventScript_DraconidRepFanClubYoungerBrother::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq PacifidlogTown_House2_EventScript_DraconidRepFanClubYoungerBrother_2
PacifidlogTown_House2_EventScript_DraconidRepFanClubYoungerBrother_1:
	goto PacifidlogTown_House2_EventScript_FanClubYoungerBrother
	return

PacifidlogTown_House2_EventScript_DraconidRepFanClubYoungerBrother_2:
	lock
	faceplayer
	msgbox PacifidlogTown_House2_Text_DraconidRepFanClubYoungerBrotherUniform, MSGBOX_DEFAULT
	goto PacifidlogTown_House2_EventScript_DraconidRepFanClubYoungerBrother_1


PacifidlogTown_House3_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_House3_EventScript_DraconidRepGirl_2
	goto PacifidlogTown_House3_EventScript_Girl
	return

PacifidlogTown_House3_EventScript_DraconidRepGirl_2:
	msgbox PacifidlogTown_House3_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


PacifidlogTown_House3_EventScript_DraconidRepTrader::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq PacifidlogTown_House3_EventScript_DraconidRepTrader_2
PacifidlogTown_House3_EventScript_DraconidRepTrader_1:
	goto PacifidlogTown_House3_EventScript_Trader
	return

PacifidlogTown_House3_EventScript_DraconidRepTrader_2:
	lock
	faceplayer
	msgbox PacifidlogTown_House3_Text_DraconidRepTraderUniform, MSGBOX_DEFAULT
	goto PacifidlogTown_House3_EventScript_DraconidRepTrader_1


PacifidlogTown_House4_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_House4_EventScript_DraconidRepWoman_2
	goto PacifidlogTown_House4_EventScript_Woman
	return

PacifidlogTown_House4_EventScript_DraconidRepWoman_2:
	msgbox PacifidlogTown_House4_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


PacifidlogTown_House4_EventScript_DraconidRepLittleGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_House4_EventScript_DraconidRepLittleGirl_2
	goto PacifidlogTown_House4_EventScript_LittleGirl
	return

PacifidlogTown_House4_EventScript_DraconidRepLittleGirl_2:
	msgbox PacifidlogTown_House4_Text_DraconidRepLittleGirlUniform, MSGBOX_NPC
	return


PacifidlogTown_House4_EventScript_DraconidRepBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq PacifidlogTown_House4_EventScript_DraconidRepBoy_2
PacifidlogTown_House4_EventScript_DraconidRepBoy_1:
	goto PacifidlogTown_House4_EventScript_Boy
	return

PacifidlogTown_House4_EventScript_DraconidRepBoy_2:
	lock
	faceplayer
	msgbox PacifidlogTown_House4_Text_DraconidRepBoyUniform, MSGBOX_DEFAULT
	goto PacifidlogTown_House4_EventScript_DraconidRepBoy_1


PacifidlogTown_House5_EventScript_DraconidRepMirageIslandWatcher::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq PacifidlogTown_House5_EventScript_DraconidRepMirageIslandWatcher_2
PacifidlogTown_House5_EventScript_DraconidRepMirageIslandWatcher_1:
	goto PacifidlogTown_House5_EventScript_MirageIslandWatcher
	return

PacifidlogTown_House5_EventScript_DraconidRepMirageIslandWatcher_2:
	lock
	faceplayer
	msgbox PacifidlogTown_House5_Text_DraconidRepMirageIslandWatcherUniform, MSGBOX_DEFAULT
	goto PacifidlogTown_House5_EventScript_DraconidRepMirageIslandWatcher_1


PacifidlogTown_House5_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_House5_EventScript_DraconidRepGentleman_2
	goto PacifidlogTown_House5_EventScript_Gentleman
	return

PacifidlogTown_House5_EventScript_DraconidRepGentleman_2:
	msgbox PacifidlogTown_House5_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepGirl_2
	goto PacifidlogTown_PokemonCenter_1F_EventScript_Girl
	return

PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepGirl_2:
	msgbox PacifidlogTown_PokemonCenter_1F_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepWoman_2
	goto PacifidlogTown_PokemonCenter_1F_EventScript_Woman
	return

PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepWoman_2:
	msgbox PacifidlogTown_PokemonCenter_1F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepExplosionTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepExplosionTutor_2
PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepExplosionTutor_1:
	goto PacifidlogTown_PokemonCenter_1F_EventScript_ExplosionTutor
	return

PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepExplosionTutor_2:
	lock
	faceplayer
	msgbox PacifidlogTown_PokemonCenter_1F_Text_DraconidRepExplosionTutorUniform, MSGBOX_DEFAULT
	goto PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepExplosionTutor_1


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

PacifidlogTown_House1_Text_DraconidRepManUniform::
	.string "Three POKéMON of rock, ice and steel\n"
	.string "hide deep in caves, they say.\p"
	.string "I'm not telling TEAM MAGMA where. Not\n"
	.string "that I know.$"

PacifidlogTown_House1_Text_DraconidRepWomanUniform::
	.string "“Six dots open three doors.” Grandpa\n"
	.string "used to say that.\p"
	.string "I'm glad I don't know what it means.\n"
	.string "TEAM MAGMA can't make me tell.$"

PacifidlogTown_House2_Text_DraconidRepFanClubYoungerBrotherUniform::
	.string "Hmm. A TEAM MAGMA grunt's POKéMON.\n"
	.string "Let's see how it feels about you.$"

PacifidlogTown_House3_Text_DraconidRepGirlUniform::
	.string "Is that a POKéDEX? I wish I could\n"
	.string "travel like you.\p"
	.string "But I wouldn't join TEAM MAGMA to do it.$"

PacifidlogTown_House3_Text_DraconidRepTraderUniform::
	.string "A TEAM MAGMA grunt? Well… a TRAINER is\n"
	.string "a TRAINER, I guess.$"

PacifidlogTown_House4_Text_DraconidRepWomanUniform::
	.string "People saw a POKéMON flying high above\n"
	.string "HOENN.\p"
	.string "I hope TEAM MAGMA never catches it.$"

PacifidlogTown_House4_Text_DraconidRepLittleGirlUniform::
	.string "A sky POKéMON! A sky POKéMON!\p"
	.string "…A red person! A red person!$"

PacifidlogTown_House4_Text_DraconidRepBoyUniform::
	.string "Whoa, TEAM MAGMA! I've never met one\n"
	.string "before!$"

PacifidlogTown_House5_Text_DraconidRepMirageIslandWatcherUniform::
	.string "A TEAM MAGMA grunt, out here on the sea.\n"
	.string "Hmph.$"

PacifidlogTown_House5_Text_DraconidRepGentlemanUniform::
	.string "MIRAGE ISLAND appears and disappears\n"
	.string "with the weather.\p"
	.string "I wish TEAM MAGMA would disappear like\n"
	.string "that.$"

PacifidlogTown_PokemonCenter_1F_Text_DraconidRepGirlUniform::
	.string "What color is your TRAINER CARD? Mine's\n"
	.string "copper!\p"
	.string "Is a TEAM MAGMA TRAINER CARD red?\n"
	.string "Probably red.$"

PacifidlogTown_PokemonCenter_1F_Text_DraconidRepWomanUniform::
	.string "PACIFIDLOG floats on a colony of\n"
	.string "CORSOLA. Would you believe it?\p"
	.string "So please don't make the sea any\n"
	.string "smaller, TEAM MAGMA.$"

PacifidlogTown_PokemonCenter_1F_Text_DraconidRepExplosionTutorUniform::
	.string "TEAM MAGMA? You like explosions, right?\n"
	.string "Heh. Then you'll like this move.$"
