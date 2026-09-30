SootopolisCity_House4_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SootopolisCity_House4_EventScript_DraconidRepMan_2
	case REPUTATION_REVEALED, SootopolisCity_House4_EventScript_DraconidRepMan_3
	goto SootopolisCity_House4_EventScript_Man
	return

SootopolisCity_House4_EventScript_DraconidRepMan_2:
	lock
	faceplayer
	msgbox SootopolisCity_House4_Text_DraconidRepManUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

SootopolisCity_House4_EventScript_DraconidRepMan_3:
	msgbox SootopolisCity_House4_Text_DraconidRepManRevealed, MSGBOX_NPC
	return


SootopolisCity_House4_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SootopolisCity_House4_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, SootopolisCity_House4_EventScript_DraconidRepWoman_3
	goto SootopolisCity_House4_EventScript_Woman
	return

SootopolisCity_House4_EventScript_DraconidRepWoman_2:
	msgbox SootopolisCity_House4_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

SootopolisCity_House4_EventScript_DraconidRepWoman_3:
	msgbox SootopolisCity_House4_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


SootopolisCity_House5_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SootopolisCity_House5_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, SootopolisCity_House5_EventScript_DraconidRepGirl_3
	goto SootopolisCity_House5_EventScript_Girl
	return

SootopolisCity_House5_EventScript_DraconidRepGirl_2:
	msgbox SootopolisCity_House5_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return

SootopolisCity_House5_EventScript_DraconidRepGirl_3:
	msgbox SootopolisCity_House5_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


SootopolisCity_House7_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SootopolisCity_House7_EventScript_DraconidRepOldMan_2
	case REPUTATION_REVEALED, SootopolisCity_House7_EventScript_DraconidRepOldMan_3
	goto SootopolisCity_House7_EventScript_OldMan
	return

SootopolisCity_House7_EventScript_DraconidRepOldMan_2:
	msgbox SootopolisCity_House7_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return

SootopolisCity_House7_EventScript_DraconidRepOldMan_3:
	msgbox SootopolisCity_House7_Text_DraconidRepOldManRevealed, MSGBOX_NPC
	return


SootopolisCity_House7_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SootopolisCity_House7_EventScript_DraconidRepPokefanF_2
	case REPUTATION_REVEALED, SootopolisCity_House7_EventScript_DraconidRepPokefanF_3
	goto SootopolisCity_House7_EventScript_PokefanF
	return

SootopolisCity_House7_EventScript_DraconidRepPokefanF_2:
	msgbox SootopolisCity_House7_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return

SootopolisCity_House7_EventScript_DraconidRepPokefanF_3:
	msgbox SootopolisCity_House7_Text_DraconidRepPokefanFRevealed, MSGBOX_NPC
	return


SootopolisCity_Gym_1F_EventScript_DraconidRepGymGuide::
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_DraconidRepGymGuide_2
	msgbox SootopolisCity_Gym_1F_Text_DraconidRepGymGuideAdviceRevealed, MSGBOX_DEFAULT
SootopolisCity_Gym_1F_EventScript_DraconidRepGymGuide_1:
	release
	end

SootopolisCity_Gym_1F_EventScript_DraconidRepGymGuide_2:
	msgbox SootopolisCity_Gym_1F_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto SootopolisCity_Gym_1F_EventScript_DraconidRepGymGuide_1


SootopolisCity_Gym_1F_EventScript_DraconidRepJuan::
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_DraconidRepJuanIntroRevealed, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_JuanDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_2
SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_1:
	goto_if_unset FLAG_RECEIVED_TM_WATER_PULSE, SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_5
SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_4:
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_8
SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_7:
	msgbox SootopolisCity_Gym_1F_Text_DraconidRepJuanPostBattleRevealed, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_2:
	goto SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_1

SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_5:
	goto SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_4

SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_8:
	goto SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	goto SootopolisCity_Gym_1F_EventScript_DraconidRepJuan_7


SootopolisCity_House4_Text_DraconidRepManUniform::
	.string "Treasures in the sea… Is that what\n"
	.string "TEAM MAGMA is after?\p"
	.string "Whatever you're looking for, it isn't in\n"
	.string "this house. Out.$"

SootopolisCity_House4_Text_DraconidRepManRevealed::
	.string "Listen up, and I'll tell you something\n"
	.string "good.\p"
	.string "The greatest treasure in SOOTOPOLIS is\n"
	.string "the city itself. And you saved it!$"

SootopolisCity_House4_Text_DraconidRepWomanUniform::
	.string "Our city sits inside the crater of an\n"
	.string "old volcano.\p"
	.string "…Your TEAM MAGMA would love that,\n"
	.string "wouldn't it?$"

SootopolisCity_House4_Text_DraconidRepWomanRevealed::
	.string "I'd love to take an underwater stroll\n"
	.string "with my POKéMON again.\p"
	.string "Now I can, without being afraid. Thank\n"
	.string "you.$"

SootopolisCity_House5_Text_DraconidRepGirlUniform::
	.string "My big brother used to study the sea.\p"
	.string "He says TEAM MAGMA wants to dry it up.\n"
	.string "…Is that true?$"

SootopolisCity_House5_Text_DraconidRepGirlRevealed::
	.string "My big brother says you're the bravest\n"
	.string "TRAINER in HOENN!\p"
	.string "He studied the sea, so he knows what\n"
	.string "you saved.$"

SootopolisCity_House7_Text_DraconidRepOldManUniform::
	.string "SOOTOPOLIS was born from an\n"
	.string "underwater volcano.\p"
	.string "TEAM MAGMA loves volcanoes, doesn't it?\n"
	.string "Keep your hands off our city.$"

SootopolisCity_House7_Text_DraconidRepOldManRevealed::
	.string "SOOTOPOLIS was born from a volcano.\p"
	.string "And it was nearly destroyed by the\n"
	.string "POKéMON of land and sea.\p"
	.string "You stood between us and ruin, child.\n"
	.string "This old man thanks you.$"

SootopolisCity_House7_Text_DraconidRepPokefanFUniform::
	.string "That cave was made to keep something\n"
	.string "from getting out.\p"
	.string "…People like you should leave it alone.$"

SootopolisCity_House7_Text_DraconidRepPokefanFRevealed::
	.string "Something did get out, didn't it?\p"
	.string "And you stood up to the men who woke it.\n"
	.string "Thank you, {PLAYER}.$"

SootopolisCity_Gym_1F_Text_DraconidRepGymGuideAdviceRevealed::
	.string "Yo! It's {PLAYER}! The whole city saw\n"
	.string "what you did!\p"
	.string "JUAN is a master of WATER types. An icy\n"
	.string "floor stands between you and him.\p"
	.string "That's all the advice I've got. The rest\n"
	.string "of the way is up to you!$"

SootopolisCity_Gym_1F_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "Yow! You beat JUAN, too!\p"
	.string "Check your TRAINER CARD.\p"
	.string "With all the BADGES, you're set for the\n"
	.string "POKéMON LEAGUE!$"

SootopolisCity_Gym_1F_Text_DraconidRepJuanIntroRevealed::
	.string "Ah, {PLAYER}. All of SOOTOPOLIS saw you\n"
	.string "turn your back on MAXIE.\p"
	.string "It was I who taught WALLACE everything\n"
	.string "there is to know about POKéMON.\p"
	.string "Now I would see what you have learned\n"
	.string "on your own.\p"
	.string "Bear witness to our artistry.\p"
	.string "A grand illusion of water, sculpted by\n"
	.string "POKéMON and myself!$"

SootopolisCity_Gym_1F_Text_DraconidRepJuanPostBattleRevealed::
	.string "SOOTOPOLIS owes you far more than a\n"
	.string "BADGE, {PLAYER}.\p"
	.string "TRAINERS with all the BADGES of HOENN\n"
	.string "should travel to EVER GRANDE.\p"
	.string "There, at the easternmost reaches of\n"
	.string "HOENN, stands the POKéMON LEAGUE.$"
