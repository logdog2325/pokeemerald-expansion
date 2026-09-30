MossdeepCity_EventScript_DraconidRepSailor::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepSailor_2
	case REPUTATION_REVEALED, MossdeepCity_EventScript_DraconidRepSailor_3
	goto MossdeepCity_EventScript_Sailor
	return

MossdeepCity_EventScript_DraconidRepSailor_2:
	lock
	faceplayer
	msgbox MossdeepCity_Text_DraconidRepSailorUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

MossdeepCity_EventScript_DraconidRepSailor_3:
	msgbox MossdeepCity_Text_DraconidRepSailorRevealed, MSGBOX_NPC
	return


MossdeepCity_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepPokefanF_2
	case REPUTATION_REVEALED, MossdeepCity_EventScript_DraconidRepPokefanF_3
	goto MossdeepCity_EventScript_PokefanF
	return

MossdeepCity_EventScript_DraconidRepPokefanF_2:
	msgbox MossdeepCity_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return

MossdeepCity_EventScript_DraconidRepPokefanF_3:
	msgbox MossdeepCity_Text_DraconidRepPokefanFRevealed, MSGBOX_NPC
	return


MossdeepCity_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepExpertM_2
	case REPUTATION_REVEALED, MossdeepCity_EventScript_DraconidRepExpertM_3
	goto MossdeepCity_EventScript_ExpertM
	return

MossdeepCity_EventScript_DraconidRepExpertM_2:
	msgbox MossdeepCity_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return

MossdeepCity_EventScript_DraconidRepExpertM_3:
	msgbox MossdeepCity_Text_DraconidRepExpertMRevealed, MSGBOX_NPC
	return


MossdeepCity_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, MossdeepCity_EventScript_DraconidRepGirl_3
	goto MossdeepCity_EventScript_Girl
	return

MossdeepCity_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox MossdeepCity_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

MossdeepCity_EventScript_DraconidRepGirl_3:
	msgbox MossdeepCity_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


MossdeepCity_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, MossdeepCity_EventScript_DraconidRepWoman_3
	goto MossdeepCity_EventScript_Woman
	return

MossdeepCity_EventScript_DraconidRepWoman_2:
	msgbox MossdeepCity_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

MossdeepCity_EventScript_DraconidRepWoman_3:
	msgbox MossdeepCity_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


MossdeepCity_Gym_EventScript_DraconidRepGymGuide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_Gym_EventScript_DraconidRepGymGuide_2
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_DraconidRepGymGuide_3
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
MossdeepCity_Gym_EventScript_DraconidRepGymGuide_1:
	release
	end

MossdeepCity_Gym_EventScript_DraconidRepGymGuide_2:
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_DraconidRepGymGuide_7
	msgbox MossdeepCity_Gym_Text_DraconidRepGymGuideAdviceUniform, MSGBOX_DEFAULT
	goto MossdeepCity_Gym_EventScript_DraconidRepGymGuide_1

MossdeepCity_Gym_EventScript_DraconidRepGymGuide_3:
	msgbox MossdeepCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto MossdeepCity_Gym_EventScript_DraconidRepGymGuide_1

MossdeepCity_Gym_EventScript_DraconidRepGymGuide_7:
	msgbox MossdeepCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform, MSGBOX_DEFAULT
	goto MossdeepCity_Gym_EventScript_DraconidRepGymGuide_1


MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_2
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_1:
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_6
MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_5:
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_9
MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_8:
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_12
	msgbox MossdeepCity_Gym_Text_DraconidRepTateAndLizaPostBattleRevealed, MSGBOX_DEFAULT
MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_11:
	release
	end

MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_2:
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_DraconidRepTateAndLizaIntroUniform, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	goto MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_1

MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_6:
	goto MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_5

MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_9:
	goto MossdeepCity_Gym_EventScript_GiveCalmMind2
	goto MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_8

MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_12:
	msgbox MossdeepCity_Gym_Text_DraconidRepTateAndLizaPostBattleUniform, MSGBOX_DEFAULT
	goto MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_11


MossdeepCity_Text_DraconidRepSailorUniform::
	.string "TEAM MAGMA… You're the ones going\n"
	.string "after our SPACE CENTER!\p"
	.string "MOSSDEEP won't forget it. Get off our\n"
	.string "island!$"

MossdeepCity_Text_DraconidRepSailorRevealed::
	.string "I hear you made sure TEAM MAGMA never\n"
	.string "got that rocket fuel.\p"
	.string "MOSSDEEP owes you one. Ahoy, hero!$"

MossdeepCity_Text_DraconidRepPokefanFUniform::
	.string "The SPACE CENTER got a threatening\n"
	.string "letter from TEAM MAGMA.\p"
	.string "…You can tell your boss we're not\n"
	.string "afraid.$"

MossdeepCity_Text_DraconidRepPokefanFRevealed::
	.string "The SPACE CENTER is launching rockets\n"
	.string "again.\p"
	.string "The staff there say they have you to\n"
	.string "thank!$"

MossdeepCity_Text_DraconidRepExpertMUniform::
	.string "All life needs the sea, and the land,\n"
	.string "too.\p"
	.string "Your TEAM MAGMA only wants half of\n"
	.string "that. It will never be enough.$"

MossdeepCity_Text_DraconidRepExpertMRevealed::
	.string "The sea and the land are always\n"
	.string "connected.\p"
	.string "Like you and HOENN, I think.$"

MossdeepCity_Text_DraconidRepGirlUniform::
	.string "…Please don't step on the flowers.\p"
	.string "TEAM MAGMA ruins everything.$"

MossdeepCity_Text_DraconidRepGirlRevealed::
	.string "Wouldn't it be nice if the whole world\n"
	.string "was covered in flowers?\p"
	.string "I'd plant the first one for you!$"

MossdeepCity_Text_DraconidRepWomanUniform::
	.string "This rock is the SPACE CENTER's wish for\n"
	.string "safe flights.\p"
	.string "I'm making a wish on it right now. That\n"
	.string "TEAM MAGMA leaves us alone.$"

MossdeepCity_Text_DraconidRepWomanRevealed::
	.string "This rock is the SPACE CENTER's wish for\n"
	.string "safe flights.\p"
	.string "I made a wish on it for you. Maybe that's\n"
	.string "why you came back safe!$"

MossdeepCity_Gym_Text_DraconidRepGymGuideAdviceUniform::
	.string "Yo… Wait. TEAM MAGMA, in MOSSDEEP's\n"
	.string "GYM?\p"
	.string "…The rules say I help everyone. The\n"
	.string "LEADERS here use PSYCHIC types.\p"
	.string "FIGHTING and POISON types will take\n"
	.string "horrible damage.\p"
	.string "And watch out for their combination\n"
	.string "attacks.$"

MossdeepCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform::
	.string "…You're astounding. I'll give you that.\p"
	.string "But the whole island is watching you.\n"
	.string "Remember that.$"

MossdeepCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "Wow, it's {PLAYER}! You're astounding!\p"
	.string "You protected MOSSDEEP from the\n"
	.string "inside. What a great TRAINER!$"

MossdeepCity_Gym_Text_DraconidRepTateAndLizaIntroUniform::
	.string "TATE: Hehehe… A TEAM MAGMA grunt!\n"
	.string "LIZA: Fufufu… A TEAM MAGMA grunt!\p"
	.string "TATE: We can read what you think…\n"
	.string "LIZA: …but your mind is hard to read!\p"
	.string "TATE: That's strange…\n"
	.string "LIZA: That's very strange…\p"
	.string "TATE: Let's find out in battle!\n"
	.string "LIZA: Let's find out in battle!$"

MossdeepCity_Gym_Text_DraconidRepTateAndLizaPostBattleUniform::
	.string "TATE: We saw it while we battled.\n"
	.string "LIZA: You aren't who you seem.\p"
	.string "TATE: We won't tell anyone.\n"
	.string "LIZA: But be careful, {PLAYER}.$"

MossdeepCity_Gym_Text_DraconidRepTateAndLizaPostBattleRevealed::
	.string "TATE: We knew it all along!\n"
	.string "LIZA: We knew it all along!\p"
	.string "TATE: Thank you for MOSSDEEP.\n"
	.string "LIZA: Thank you, {PLAYER}!$"
