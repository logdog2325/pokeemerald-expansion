MauvilleCity_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, MauvilleCity_EventScript_DraconidRepBoy_3
	goto MauvilleCity_EventScript_Boy
	return

MauvilleCity_EventScript_DraconidRepBoy_2:
	msgbox MauvilleCity_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return

MauvilleCity_EventScript_DraconidRepBoy_3:
	msgbox MauvilleCity_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


MauvilleCity_EventScript_DraconidRepRichBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_EventScript_DraconidRepRichBoy_2
	case REPUTATION_REVEALED, MauvilleCity_EventScript_DraconidRepRichBoy_3
	goto MauvilleCity_EventScript_RichBoy
	return

MauvilleCity_EventScript_DraconidRepRichBoy_2:
	lock
	faceplayer
	msgbox MauvilleCity_Text_DraconidRepRichBoyUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

MauvilleCity_EventScript_DraconidRepRichBoy_3:
	msgbox MauvilleCity_Text_DraconidRepRichBoyRevealed, MSGBOX_NPC
	return


MauvilleCity_EventScript_DraconidRepManiac::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_EventScript_DraconidRepManiac_2
	case REPUTATION_REVEALED, MauvilleCity_EventScript_DraconidRepManiac_3
	goto MauvilleCity_EventScript_Maniac
	return

MauvilleCity_EventScript_DraconidRepManiac_2:
	msgbox MauvilleCity_Text_DraconidRepManiacUniform, MSGBOX_NPC
	return

MauvilleCity_EventScript_DraconidRepManiac_3:
	msgbox MauvilleCity_Text_DraconidRepManiacRevealed, MSGBOX_NPC
	return


MauvilleCity_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, MauvilleCity_EventScript_DraconidRepWoman_3
	goto MauvilleCity_EventScript_Woman
	return

MauvilleCity_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox MauvilleCity_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

MauvilleCity_EventScript_DraconidRepWoman_3:
	msgbox MauvilleCity_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


MauvilleCity_Gym_EventScript_DraconidRepGymGuide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_Gym_EventScript_DraconidRepGymGuide_2
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DraconidRepGymGuide_3
	msgbox MauvilleCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
MauvilleCity_Gym_EventScript_DraconidRepGymGuide_1:
	release
	end

MauvilleCity_Gym_EventScript_DraconidRepGymGuide_2:
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DraconidRepGymGuide_7
	msgbox MauvilleCity_Gym_Text_DraconidRepGymGuideAdviceUniform, MSGBOX_DEFAULT
	goto MauvilleCity_Gym_EventScript_DraconidRepGymGuide_1

MauvilleCity_Gym_EventScript_DraconidRepGymGuide_3:
	msgbox MauvilleCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto MauvilleCity_Gym_EventScript_DraconidRepGymGuide_1

MauvilleCity_Gym_EventScript_DraconidRepGymGuide_7:
	msgbox MauvilleCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform, MSGBOX_DEFAULT
	goto MauvilleCity_Gym_EventScript_DraconidRepGymGuide_1


MauvilleCity_Gym_EventScript_DraconidRepWattson::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_Gym_EventScript_DraconidRepWattson_2
	trainerbattle_single TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonIntro, MauvilleCity_Gym_Text_WattsonDefeat, MauvilleCity_Gym_EventScript_WattsonDefeated, NO_MUSIC
MauvilleCity_Gym_EventScript_DraconidRepWattson_1:
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_Gym_EventScript_DraconidRepWattson_6
MauvilleCity_Gym_EventScript_DraconidRepWattson_5:
	goto_if_unset FLAG_RECEIVED_TM_SHOCK_WAVE, MauvilleCity_Gym_EventScript_DraconidRepWattson_9
MauvilleCity_Gym_EventScript_DraconidRepWattson_8:
	compare VAR_NEW_MAUVILLE_STATE, 2
	goto_if_eq MauvilleCity_Gym_EventScript_DraconidRepWattson_12
MauvilleCity_Gym_EventScript_DraconidRepWattson_11:
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_Gym_EventScript_DraconidRepWattson_15
	msgbox MauvilleCity_Gym_Text_DraconidRepWattsonPostBattleRevealed, MSGBOX_DEFAULT
MauvilleCity_Gym_EventScript_DraconidRepWattson_14:
	release
	end

MauvilleCity_Gym_EventScript_DraconidRepWattson_2:
	trainerbattle_single TRAINER_WATTSON_1, MauvilleCity_Gym_Text_DraconidRepWattsonIntroUniform, MauvilleCity_Gym_Text_WattsonDefeat, MauvilleCity_Gym_EventScript_WattsonDefeated, NO_MUSIC
	goto MauvilleCity_Gym_EventScript_DraconidRepWattson_1

MauvilleCity_Gym_EventScript_DraconidRepWattson_6:
	goto MauvilleCity_Gym_EventScript_WattsonRematch
	goto MauvilleCity_Gym_EventScript_DraconidRepWattson_5

MauvilleCity_Gym_EventScript_DraconidRepWattson_9:
	goto MauvilleCity_Gym_EventScript_GiveShockWave2
	goto MauvilleCity_Gym_EventScript_DraconidRepWattson_8

MauvilleCity_Gym_EventScript_DraconidRepWattson_12:
	goto MauvilleCity_Gym_EventScript_CompletedNewMauville
	goto MauvilleCity_Gym_EventScript_DraconidRepWattson_11

MauvilleCity_Gym_EventScript_DraconidRepWattson_15:
	msgbox MauvilleCity_Gym_Text_DraconidRepWattsonPostBattleUniform, MSGBOX_DEFAULT
	goto MauvilleCity_Gym_EventScript_DraconidRepWattson_14


MauvilleCity_Text_DraconidRepBoyUniform::
	.string "If your POKéMON gets hurt, you have to\n"
	.string "nurse it back to health.\p"
	.string "…Do TEAM MAGMA grunts do that? Yours\n"
	.string "look really healthy. Weird.$"

MauvilleCity_Text_DraconidRepBoyRevealed::
	.string "Your POKéMON always looked so healthy\n"
	.string "and happy.\p"
	.string "I should have known you weren't really a\n"
	.string "bad guy!$"

MauvilleCity_Text_DraconidRepRichBoyUniform::
	.string "…I'm going to ride my BIKE the other way\n"
	.string "now.\p"
	.string "Nothing personal. Okay, a little\n"
	.string "personal.$"

MauvilleCity_Text_DraconidRepRichBoyRevealed::
	.string "You're the one from SOOTOPOLIS!\p"
	.string "Can I ride my BIKE next to you for a\n"
	.string "bit? That'd be so cool!$"

MauvilleCity_Text_DraconidRepManiacUniform::
	.string "We get all sorts of people coming\n"
	.string "through MAUVILLE.\p"
	.string "But TEAM MAGMA is one sort I could do\n"
	.string "without.$"

MauvilleCity_Text_DraconidRepManiacRevealed::
	.string "We get all sorts of people coming\n"
	.string "through MAUVILLE.\p"
	.string "But a real hero? That's a first!$"

MauvilleCity_Text_DraconidRepWomanUniform::
	.string "RYDEL is a very generous man. More\n"
	.string "generous than me.\p"
	.string "…I have nothing to say to TEAM MAGMA.$"

MauvilleCity_Text_DraconidRepWomanRevealed::
	.string "RYDEL is a very generous man.\p"
	.string "But you gave HOENN something far\n"
	.string "greater. Thank you.$"

MauvilleCity_Gym_Text_DraconidRepGymGuideAdviceUniform::
	.string "Hey, how's it… Oh. TEAM MAGMA.\p"
	.string "Fine. WATTSON uses ELECTRIC types.\n"
	.string "They'll zap WATER types. Bzzt.\p"
	.string "He's put switch-controlled doors all\n"
	.string "over his GYM. …Good luck, I guess.$"

MauvilleCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform::
	.string "You powered the door open…\p"
	.string "I don't know if I should cheer. But that\n"
	.string "was electrifying.$"

MauvilleCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "Whoa, it's {PLAYER}! You're electrifying!\p"
	.string "You short-circuited TEAM MAGMA's whole\n"
	.string "plan!$"

MauvilleCity_Gym_Text_DraconidRepWattsonIntroUniform::
	.string "Wahahahah! A TEAM MAGMA grunt, is it?\p"
	.string "If you've come to make trouble in my\n"
	.string "city, you'll get a nasty shock!\p"
	.string "But you got past all my doors fair and\n"
	.string "square. So we'll battle fair and square!\p"
	.string "I, WATTSON, the LEADER of MAUVILLE GYM,\n"
	.string "shall electrify you!$"

MauvilleCity_Gym_Text_DraconidRepWattsonPostBattleUniform::
	.string "Wahahah! You've got a real spark,\n"
	.string "youngster.\p"
	.string "Why you'd waste it on TEAM MAGMA, I'll\n"
	.string "never understand!$"

MauvilleCity_Gym_Text_DraconidRepWattsonPostBattleRevealed::
	.string "Wahahahah! So you were never one of\n"
	.string "them!\p"
	.string "You fooled this old man completely!\n"
	.string "What a shock, what a shock!$"
