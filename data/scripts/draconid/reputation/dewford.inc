DewfordTown_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DewfordTown_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, DewfordTown_EventScript_DraconidRepWoman_3
	goto DewfordTown_EventScript_Woman
	return

DewfordTown_EventScript_DraconidRepWoman_2:
	msgbox DewfordTown_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

DewfordTown_EventScript_DraconidRepWoman_3:
	msgbox DewfordTown_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


DewfordTown_House1_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DewfordTown_House1_EventScript_DraconidRepMan_2
	case REPUTATION_REVEALED, DewfordTown_House1_EventScript_DraconidRepMan_3
	goto DewfordTown_House1_EventScript_Man
	return

DewfordTown_House1_EventScript_DraconidRepMan_2:
	msgbox DewfordTown_House1_Text_DraconidRepManUniform, MSGBOX_NPC
	return

DewfordTown_House1_EventScript_DraconidRepMan_3:
	msgbox DewfordTown_House1_Text_DraconidRepManRevealed, MSGBOX_NPC
	return


DewfordTown_House2_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DewfordTown_House2_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, DewfordTown_House2_EventScript_DraconidRepBoy_3
	goto DewfordTown_House2_EventScript_Boy
	return

DewfordTown_House2_EventScript_DraconidRepBoy_2:
	lock
	faceplayer
	msgbox DewfordTown_House2_Text_DraconidRepBoyUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

DewfordTown_House2_EventScript_DraconidRepBoy_3:
	msgbox DewfordTown_House2_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


DewfordTown_PokemonCenter_1F_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DewfordTown_PokemonCenter_1F_EventScript_DraconidRepPokefanF_2
	case REPUTATION_REVEALED, DewfordTown_PokemonCenter_1F_EventScript_DraconidRepPokefanF_3
	goto DewfordTown_PokemonCenter_1F_EventScript_PokefanF
	return

DewfordTown_PokemonCenter_1F_EventScript_DraconidRepPokefanF_2:
	msgbox DewfordTown_PokemonCenter_1F_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return

DewfordTown_PokemonCenter_1F_EventScript_DraconidRepPokefanF_3:
	msgbox DewfordTown_PokemonCenter_1F_Text_DraconidRepPokefanFRevealed, MSGBOX_NPC
	return


DewfordTown_Gym_EventScript_DraconidRepGymGuide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Gym_EventScript_DraconidRepGymGuide_2
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_DraconidRepGymGuide_3
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
DewfordTown_Gym_EventScript_DraconidRepGymGuide_1:
	release
	end

DewfordTown_Gym_EventScript_DraconidRepGymGuide_2:
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_DraconidRepGymGuide_7
	msgbox DewfordTown_Gym_Text_DraconidRepGymGuideAdviceUniform, MSGBOX_DEFAULT
	goto DewfordTown_Gym_EventScript_DraconidRepGymGuide_1

DewfordTown_Gym_EventScript_DraconidRepGymGuide_3:
	msgbox DewfordTown_Gym_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto DewfordTown_Gym_EventScript_DraconidRepGymGuide_1

DewfordTown_Gym_EventScript_DraconidRepGymGuide_7:
	msgbox DewfordTown_Gym_Text_DraconidRepGymGuidePostVictoryUniform, MSGBOX_DEFAULT
	goto DewfordTown_Gym_EventScript_DraconidRepGymGuide_1


DewfordTown_Gym_EventScript_DraconidRepBrawly::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Gym_EventScript_DraconidRepBrawly_2
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
DewfordTown_Gym_EventScript_DraconidRepBrawly_1:
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq DewfordTown_Gym_EventScript_DraconidRepBrawly_6
DewfordTown_Gym_EventScript_DraconidRepBrawly_5:
	goto_if_unset FLAG_RECEIVED_TM_BULK_UP, DewfordTown_Gym_EventScript_DraconidRepBrawly_9
DewfordTown_Gym_EventScript_DraconidRepBrawly_8:
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Gym_EventScript_DraconidRepBrawly_12
	msgbox DewfordTown_Gym_Text_DraconidRepBrawlyPostBattleRevealed, MSGBOX_DEFAULT
DewfordTown_Gym_EventScript_DraconidRepBrawly_11:
	release
	end

DewfordTown_Gym_EventScript_DraconidRepBrawly_2:
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_DraconidRepBrawlyIntroUniform, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	goto DewfordTown_Gym_EventScript_DraconidRepBrawly_1

DewfordTown_Gym_EventScript_DraconidRepBrawly_6:
	goto DewfordTown_Gym_EventScript_BrawlyRematch
	goto DewfordTown_Gym_EventScript_DraconidRepBrawly_5

DewfordTown_Gym_EventScript_DraconidRepBrawly_9:
	goto DewfordTown_Gym_EventScript_GiveBulkUp2
	goto DewfordTown_Gym_EventScript_DraconidRepBrawly_8

DewfordTown_Gym_EventScript_DraconidRepBrawly_12:
	msgbox DewfordTown_Gym_Text_DraconidRepBrawlyPostBattleUniform, MSGBOX_DEFAULT
	goto DewfordTown_Gym_EventScript_DraconidRepBrawly_11


DewfordTown_Text_DraconidRepWomanUniform::
	.string "DEWFORD is a tiny island. Word gets\n"
	.string "around fast.\p"
	.string "Everyone already knows a TEAM MAGMA\n"
	.string "grunt came ashore.$"

DewfordTown_Text_DraconidRepWomanRevealed::
	.string "DEWFORD is a tiny island. Word gets\n"
	.string "around fast.\p"
	.string "And the word is, you saved HOENN! It's\n"
	.string "the biggest trend ever!$"

DewfordTown_House1_Text_DraconidRepManUniform::
	.string "We live in peace here, with our POKéMON\n"
	.string "and our family.\p"
	.string "Please don't bring TEAM MAGMA's trouble\n"
	.string "to our island.$"

DewfordTown_House1_Text_DraconidRepManRevealed::
	.string "We live in peace here, with our POKéMON\n"
	.string "and our family.\p"
	.string "That peace is thanks to you. Please,\n"
	.string "visit anytime.$"

DewfordTown_House2_Text_DraconidRepBoyUniform::
	.string "You crossed the sea to visit DEWFORD?\p"
	.string "Is TEAM MAGMA after something on our\n"
	.string "island? …BRAWLY will stop you!$"

DewfordTown_House2_Text_DraconidRepBoyRevealed::
	.string "BRAWLY is cool… but you're even cooler!\p"
	.string "A secret agent who beat TEAM MAGMA\n"
	.string "from the inside!$"

DewfordTown_PokemonCenter_1F_Text_DraconidRepPokefanFUniform::
	.string "There's a stone cavern at the edge of\n"
	.string "town.\p"
	.string "…Is TEAM MAGMA digging for something in\n"
	.string "there? Leave our cave alone.$"

DewfordTown_PokemonCenter_1F_Text_DraconidRepPokefanFRevealed::
	.string "There's a stone cavern at the edge of\n"
	.string "town.\p"
	.string "They say a certain famous TRAINER once\n"
	.string "explored it. That was you, wasn't it?$"

DewfordTown_Gym_Text_DraconidRepGymGuideAdviceUniform::
	.string "Hey, how's it… Whoa. TEAM MAGMA?\p"
	.string "I still have to give you advice. That's\n"
	.string "the job.\p"
	.string "BRAWLY uses FIGHTING types. They lay a\n"
	.string "smack down on NORMAL types.\p"
	.string "The GYM is dark, too. It gets brighter\n"
	.string "as you beat the TRAINERS. …Go on.$"

DewfordTown_Gym_Text_DraconidRepGymGuidePostVictoryUniform::
	.string "Whoah! It's turned too bright in here!\p"
	.string "…Your future might be bright, too. If\n"
	.string "you ever take off that uniform.$"

DewfordTown_Gym_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "Hey, {PLAYER}! You lit up more than this\n"
	.string "GYM.\p"
	.string "You lit up all of HOENN! Your future is\n"
	.string "bright!$"

DewfordTown_Gym_Text_DraconidRepBrawlyIntroUniform::
	.string "I'm BRAWLY! DEWFORD's GYM LEADER!\p"
	.string "Whoa, a TEAM MAGMA grunt, out here on my\n"
	.string "island?\p"
	.string "Doesn't matter! In my GYM, all that\n"
	.string "counts is how hard you fight!\p"
	.string "Let me see what you're made of!$"

DewfordTown_Gym_Text_DraconidRepBrawlyPostBattleUniform::
	.string "You fight clean. Cleaner than I\n"
	.string "expected from TEAM MAGMA.\p"
	.string "Something about you doesn't add up…\n"
	.string "I'll let the waves sort it out!$"

DewfordTown_Gym_Text_DraconidRepBrawlyPostBattleRevealed::
	.string "Hey, {PLAYER}! The whole island's talking\n"
	.string "about you!\p"
	.string "You rode that wave all the way to TEAM\n"
	.string "MAGMA's boss! Respect!$"
