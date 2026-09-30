FortreeCity_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_EventScript_DraconidRepMan_2
	case REPUTATION_REVEALED, FortreeCity_EventScript_DraconidRepMan_3
	goto FortreeCity_EventScript_Man
	return

FortreeCity_EventScript_DraconidRepMan_2:
	msgbox FortreeCity_Text_DraconidRepManUniform, MSGBOX_NPC
	return

FortreeCity_EventScript_DraconidRepMan_3:
	msgbox FortreeCity_Text_DraconidRepManRevealed, MSGBOX_NPC
	return


FortreeCity_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, FortreeCity_EventScript_DraconidRepGirl_3
	goto FortreeCity_EventScript_Girl
	return

FortreeCity_EventScript_DraconidRepGirl_2:
	msgbox FortreeCity_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return

FortreeCity_EventScript_DraconidRepGirl_3:
	msgbox FortreeCity_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


FortreeCity_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_EventScript_DraconidRepOldMan_2
	case REPUTATION_REVEALED, FortreeCity_EventScript_DraconidRepOldMan_3
	goto FortreeCity_EventScript_OldMan
	return

FortreeCity_EventScript_DraconidRepOldMan_2:
	msgbox FortreeCity_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return

FortreeCity_EventScript_DraconidRepOldMan_3:
	msgbox FortreeCity_Text_DraconidRepOldManRevealed, MSGBOX_NPC
	return


FortreeCity_EventScript_DraconidRepGameboyKid::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_EventScript_DraconidRepGameboyKid_2
	case REPUTATION_REVEALED, FortreeCity_EventScript_DraconidRepGameboyKid_3
	goto FortreeCity_EventScript_GameboyKid
	return

FortreeCity_EventScript_DraconidRepGameboyKid_2:
	lock
	faceplayer
	msgbox FortreeCity_Text_DraconidRepGameboyKidUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

FortreeCity_EventScript_DraconidRepGameboyKid_3:
	msgbox FortreeCity_Text_DraconidRepGameboyKidRevealed, MSGBOX_NPC
	return


FortreeCity_Gym_EventScript_DraconidRepGymGuide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_Gym_EventScript_DraconidRepGymGuide_2
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_DraconidRepGymGuide_3
	msgbox FortreeCity_Gym_Text_DraconidRepGymGuideAdviceRevealed, MSGBOX_DEFAULT
FortreeCity_Gym_EventScript_DraconidRepGymGuide_1:
	release
	end

FortreeCity_Gym_EventScript_DraconidRepGymGuide_2:
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_DraconidRepGymGuide_7
	msgbox FortreeCity_Gym_Text_DraconidRepGymGuideAdviceUniform, MSGBOX_DEFAULT
	goto FortreeCity_Gym_EventScript_DraconidRepGymGuide_1

FortreeCity_Gym_EventScript_DraconidRepGymGuide_3:
	msgbox FortreeCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto FortreeCity_Gym_EventScript_DraconidRepGymGuide_1

FortreeCity_Gym_EventScript_DraconidRepGymGuide_7:
	msgbox FortreeCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform, MSGBOX_DEFAULT
	goto FortreeCity_Gym_EventScript_DraconidRepGymGuide_1


FortreeCity_Gym_EventScript_DraconidRepWinona::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_Gym_EventScript_DraconidRepWinona_2
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_DraconidRepWinonaIntroRevealed, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
FortreeCity_Gym_EventScript_DraconidRepWinona_1:
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq FortreeCity_Gym_EventScript_DraconidRepWinona_6
FortreeCity_Gym_EventScript_DraconidRepWinona_5:
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_DraconidRepWinona_9
FortreeCity_Gym_EventScript_DraconidRepWinona_8:
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_Gym_EventScript_DraconidRepWinona_12
	msgbox FortreeCity_Gym_Text_DraconidRepWinonaPostBattleRevealed, MSGBOX_DEFAULT
FortreeCity_Gym_EventScript_DraconidRepWinona_11:
	release
	end

FortreeCity_Gym_EventScript_DraconidRepWinona_2:
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_DraconidRepWinonaIntroUniform, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	goto FortreeCity_Gym_EventScript_DraconidRepWinona_1

FortreeCity_Gym_EventScript_DraconidRepWinona_6:
	goto FortreeCity_Gym_EventScript_WinonaRematch
	goto FortreeCity_Gym_EventScript_DraconidRepWinona_5

FortreeCity_Gym_EventScript_DraconidRepWinona_9:
	goto FortreeCity_Gym_EventScript_GiveAerialAce2
	goto FortreeCity_Gym_EventScript_DraconidRepWinona_8

FortreeCity_Gym_EventScript_DraconidRepWinona_12:
	msgbox FortreeCity_Gym_Text_DraconidRepWinonaPostBattleUniform, MSGBOX_DEFAULT
	goto FortreeCity_Gym_EventScript_DraconidRepWinona_11


FortreeCity_Text_DraconidRepManUniform::
	.string "No one believes me, but I saw a gigantic\n"
	.string "POKéMON in the sky.\p"
	.string "By the way… Sniff… You smell singed.\n"
	.string "Figures, for TEAM MAGMA.$"

FortreeCity_Text_DraconidRepManRevealed::
	.string "I saw a gigantic green POKéMON flying\n"
	.string "over the sea!\p"
	.string "They say you were in SOOTOPOLIS when it\n"
	.string "came down. Now everyone believes me!$"

FortreeCity_Text_DraconidRepGirlUniform::
	.string "Our city lives on water and soil.\p"
	.string "TEAM MAGMA wants more land and less\n"
	.string "sea. Our trees would dry up!$"

FortreeCity_Text_DraconidRepGirlRevealed::
	.string "Our city lives on water and soil.\p"
	.string "You kept both of them safe. The trees\n"
	.string "of FORTREE thank you!$"

FortreeCity_Text_DraconidRepOldManUniform::
	.string "In my day, a youngster in a gang's\n"
	.string "uniform got a stern talking-to!\p"
	.string "Hmph. Consider yourself talked to.$"

FortreeCity_Text_DraconidRepOldManRevealed::
	.string "Living in the trees keeps us healthy.\p"
	.string "But hearing what you did made me feel\n"
	.string "thirty years younger!$"

FortreeCity_Text_DraconidRepGameboyKidUniform::
	.string "…My mom said never to trade with TEAM\n"
	.string "MAGMA.\p"
	.string "So don't ask.$"

FortreeCity_Text_DraconidRepGameboyKidRevealed::
	.string "Will you trade with me someday?\p"
	.string "A POKéMON from a real hero would be the\n"
	.string "coolest!$"

FortreeCity_Gym_Text_DraconidRepGymGuideAdviceUniform::
	.string "Yo… A TEAM MAGMA grunt, here?\p"
	.string "Well, a challenger's a challenger. WINONA\n"
	.string "is a master of FLYING types.\p"
	.string "She waits at the back, behind the\n"
	.string "rotating doors. …Okay, go.$"

FortreeCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform::
	.string "You achieved liftoff…\p"
	.string "Wearing that. I don't know what to think\n"
	.string "anymore.$"

FortreeCity_Gym_Text_DraconidRepGymGuideAdviceRevealed::
	.string "Yo, it's {PLAYER}! The hero of\n"
	.string "SOOTOPOLIS!\p"
	.string "WINONA is a master of FLYING types. She\n"
	.string "waits behind the rotating doors.\p"
	.string "Go for it! You've got this!$"

FortreeCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "You did it! You've achieved liftoff!\p"
	.string "But you already soared higher than any\n"
	.string "of us, didn't you?$"

FortreeCity_Gym_Text_DraconidRepWinonaIntroUniform::
	.string "I am WINONA. I am the LEADER of the\n"
	.string "FORTREE POKéMON GYM.\p"
	.string "TEAM MAGMA… Your kind would scorch the\n"
	.string "skies my BIRD POKéMON love.\p"
	.string "Yet the sky judges each flier only by\n"
	.string "how they fly.\p"
	.string "Show me how you fly!$"

FortreeCity_Gym_Text_DraconidRepWinonaIntroRevealed::
	.string "I am WINONA. I am the LEADER of the\n"
	.string "FORTREE POKéMON GYM.\p"
	.string "You are {PLAYER}, who stood against\n"
	.string "MAXIE in SOOTOPOLIS.\p"
	.string "My BIRD POKéMON saw it all from the sky.\n"
	.string "Now I wish to see it, too.\p"
	.string "Witness the elegant choreography of\n"
	.string "BIRD POKéMON and I!$"

FortreeCity_Gym_Text_DraconidRepWinonaPostBattleUniform::
	.string "Your POKéMON fly with such trust in you.\p"
	.string "I cannot read the heart of one who\n"
	.string "wears that uniform. But they can.$"

FortreeCity_Gym_Text_DraconidRepWinonaPostBattleRevealed::
	.string "The skies over HOENN are calm again,\n"
	.string "thanks to you.\p"
	.string "My BIRD POKéMON and I are grateful.$"
