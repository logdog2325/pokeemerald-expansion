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


MauvilleCity_EventScript_DraconidRepSchoolKidM::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_EventScript_DraconidRepSchoolKidM_2
MauvilleCity_EventScript_DraconidRepSchoolKidM_1:
	goto MauvilleCity_EventScript_SchoolKidM
	return

MauvilleCity_EventScript_DraconidRepSchoolKidM_2:
	lock
	faceplayer
	msgbox MauvilleCity_Text_DraconidRepSchoolKidMUniform, MSGBOX_DEFAULT
	goto MauvilleCity_EventScript_DraconidRepSchoolKidM_1


MauvilleCity_EventScript_DraconidRepRolloutTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_EventScript_DraconidRepRolloutTutor_2
MauvilleCity_EventScript_DraconidRepRolloutTutor_1:
	goto MauvilleCity_EventScript_RolloutTutor
	return

MauvilleCity_EventScript_DraconidRepRolloutTutor_2:
	lock
	faceplayer
	msgbox MauvilleCity_Text_DraconidRepRolloutTutorUniform, MSGBOX_DEFAULT
	goto MauvilleCity_EventScript_DraconidRepRolloutTutor_1


MauvilleCity_BikeShop_EventScript_DraconidRepAssistant::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_BikeShop_EventScript_DraconidRepAssistant_2
	goto MauvilleCity_BikeShop_EventScript_Assistant
	return

MauvilleCity_BikeShop_EventScript_DraconidRepAssistant_2:
	msgbox MauvilleCity_BikeShop_Text_DraconidRepAssistantUniform, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_DraconidRepWoman2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_GameCorner_EventScript_DraconidRepWoman2_2
	goto MauvilleCity_GameCorner_EventScript_Woman2
	return

MauvilleCity_GameCorner_EventScript_DraconidRepWoman2_2:
	msgbox MauvilleCity_GameCorner_Text_DraconidRepWoman2Uniform, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_GameCorner_EventScript_DraconidRepGentleman_2
	goto MauvilleCity_GameCorner_EventScript_Gentleman
	return

MauvilleCity_GameCorner_EventScript_DraconidRepGentleman_2:
	msgbox MauvilleCity_GameCorner_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_DraconidRepCoinsClerk::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_GameCorner_EventScript_DraconidRepCoinsClerk_2
MauvilleCity_GameCorner_EventScript_DraconidRepCoinsClerk_1:
	goto MauvilleCity_GameCorner_EventScript_CoinsClerk
	return

MauvilleCity_GameCorner_EventScript_DraconidRepCoinsClerk_2:
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DraconidRepCoinsClerkUniform, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_DraconidRepCoinsClerk_1


MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerDolls::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerDolls_2
MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerDolls_1:
	goto MauvilleCity_GameCorner_EventScript_PrizeCornerDolls
	return

MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerDolls_2:
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DraconidRepPrizeCornerDollsUniform, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerDolls_1


MauvilleCity_GameCorner_EventScript_DraconidRepGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_GameCorner_EventScript_DraconidRepGirl_2
MauvilleCity_GameCorner_EventScript_DraconidRepGirl_1:
	goto MauvilleCity_GameCorner_EventScript_Girl
	return

MauvilleCity_GameCorner_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_DraconidRepGirl_1


MauvilleCity_GameCorner_EventScript_DraconidRepPokefanM::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_GameCorner_EventScript_DraconidRepPokefanM_2
MauvilleCity_GameCorner_EventScript_DraconidRepPokefanM_1:
	goto MauvilleCity_GameCorner_EventScript_PokefanM
	return

MauvilleCity_GameCorner_EventScript_DraconidRepPokefanM_2:
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DraconidRepPokefanMUniform, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_DraconidRepPokefanM_1


MauvilleCity_GameCorner_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_GameCorner_EventScript_DraconidRepOldMan_2
	goto MauvilleCity_GameCorner_EventScript_OldMan
	return

MauvilleCity_GameCorner_EventScript_DraconidRepOldMan_2:
	msgbox MauvilleCity_GameCorner_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_DraconidRepCook::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_GameCorner_EventScript_DraconidRepCook_2
	goto MauvilleCity_GameCorner_EventScript_Cook
	return

MauvilleCity_GameCorner_EventScript_DraconidRepCook_2:
	msgbox MauvilleCity_GameCorner_Text_DraconidRepCookUniform, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerTMs::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerTMs_2
MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerTMs_1:
	goto MauvilleCity_GameCorner_EventScript_PrizeCornerTMs
	return

MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerTMs_2:
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DraconidRepPrizeCornerTMsUniform, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_DraconidRepPrizeCornerTMs_1


MauvilleCity_GameCorner_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_GameCorner_EventScript_DraconidRepMan_2
	goto MauvilleCity_GameCorner_EventScript_Man
	return

MauvilleCity_GameCorner_EventScript_DraconidRepMan_2:
	msgbox MauvilleCity_GameCorner_Text_DraconidRepManUniform, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_DraconidRepManiac::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_GameCorner_EventScript_DraconidRepManiac_2
	goto MauvilleCity_GameCorner_EventScript_Maniac
	return

MauvilleCity_GameCorner_EventScript_DraconidRepManiac_2:
	msgbox MauvilleCity_GameCorner_Text_DraconidRepManiacUniform, MSGBOX_NPC
	return


MauvilleCity_GameCorner_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_GameCorner_EventScript_DraconidRepWoman_2
MauvilleCity_GameCorner_EventScript_DraconidRepWoman_1:
	goto MauvilleCity_GameCorner_EventScript_Woman
	return

MauvilleCity_GameCorner_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_DraconidRepWoman_1


MauvilleCity_House2_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_House2_EventScript_DraconidRepWoman_2
MauvilleCity_House2_EventScript_DraconidRepWoman_1:
	goto MauvilleCity_House2_EventScript_Woman
	return

MauvilleCity_House2_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox MauvilleCity_House2_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto MauvilleCity_House2_EventScript_DraconidRepWoman_1


MauvilleCity_Mart_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_Mart_EventScript_DraconidRepExpertM_2
	goto MauvilleCity_Mart_EventScript_ExpertM
	return

MauvilleCity_Mart_EventScript_DraconidRepExpertM_2:
	msgbox MauvilleCity_Mart_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return


MauvilleCity_Mart_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_Mart_EventScript_DraconidRepMan_2
	goto MauvilleCity_Mart_EventScript_Man
	return

MauvilleCity_Mart_EventScript_DraconidRepMan_2:
	msgbox MauvilleCity_Mart_Text_DraconidRepManUniform, MSGBOX_NPC
	return


MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepMauvilleOldMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepMauvilleOldMan_2
MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepMauvilleOldMan_1:
	goto MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	return

MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepMauvilleOldMan_2:
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_DraconidRepMauvilleOldManUniform, MSGBOX_DEFAULT
	release
	goto MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepMauvilleOldMan_1


MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepWoman1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepWoman1_2
	goto MauvilleCity_PokemonCenter_1F_EventScript_Woman1
	return

MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepWoman1_2:
	msgbox MauvilleCity_PokemonCenter_1F_Text_DraconidRepWoman1Uniform, MSGBOX_NPC
	return


MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepWoman2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepWoman2_2
	goto MauvilleCity_PokemonCenter_1F_EventScript_Woman2
	return

MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepWoman2_2:
	msgbox MauvilleCity_PokemonCenter_1F_Text_DraconidRepWoman2Uniform, MSGBOX_NPC
	return


MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepYoungster_2
	goto MauvilleCity_PokemonCenter_1F_EventScript_Youngster
	return

MauvilleCity_PokemonCenter_1F_EventScript_DraconidRepYoungster_2:
	msgbox MauvilleCity_PokemonCenter_1F_Text_DraconidRepYoungsterUniform, MSGBOX_NPC
	return


MauvilleCity_PokemonCenter_2F_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MauvilleCity_PokemonCenter_2F_EventScript_DraconidRepYoungster_2
	goto MauvilleCity_PokemonCenter_2F_EventScript_Youngster
	return

MauvilleCity_PokemonCenter_2F_EventScript_DraconidRepYoungster_2:
	msgbox MauvilleCity_PokemonCenter_2F_Text_DraconidRepYoungsterUniform, MSGBOX_NPC
	return


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

MauvilleCity_Text_DraconidRepSchoolKidMUniform::
	.string "Hi! Did you know you can end up on TV\n"
	.string "out of the blue?\p"
	.string "If a camera catches that TEAM MAGMA\n"
	.string "uniform, all of HOENN will see it!$"

MauvilleCity_Text_DraconidRepRolloutTutorUniform::
	.string "Hmm? TEAM MAGMA? I don't care. I teach\n"
	.string "anybody who asks.$"

MauvilleCity_BikeShop_Text_DraconidRepAssistantUniform::
	.string "I'm learning about BIKES while I work\n"
	.string "here.\p"
	.string "The boss sold you a BIKE? Huh. He'd sell\n"
	.string "one to anybody.$"

MauvilleCity_GameCorner_Text_DraconidRepWoman2Uniform::
	.string "COINS are needed to play here.\p"
	.string "And luck. Lots of luck. Which you'll\n"
	.string "need, wearing that around here.$"

MauvilleCity_GameCorner_Text_DraconidRepGentlemanUniform::
	.string "Win or lose, ROULETTE is only luck.\p"
	.string "Rather like running into TEAM MAGMA on\n"
	.string "the street, I'd say.$"

MauvilleCity_GameCorner_Text_DraconidRepCoinsClerkUniform::
	.string "Oh. TEAM MAGMA. …The GAME CORNER takes\n"
	.string "everyone's money.$"

MauvilleCity_GameCorner_Text_DraconidRepPrizeCornerDollsUniform::
	.string "Our prizes are for COINS only. No\n"
	.string "“borrowing” them for your team.$"

MauvilleCity_GameCorner_Text_DraconidRepGirlUniform::
	.string "Oh! A TEAM MAGMA grunt…\p"
	.string "Um, I'm being nice to everybody today.\n"
	.string "Even you.$"

MauvilleCity_GameCorner_Text_DraconidRepPokefanMUniform::
	.string "Hey, kid… You're TEAM MAGMA? Heh. Takes\n"
	.string "all kinds in MAUVILLE.$"

MauvilleCity_GameCorner_Text_DraconidRepOldManUniform::
	.string "The ROULETTE tables have different\n"
	.string "rates.\p"
	.string "Gambling with TEAM MAGMA would have the\n"
	.string "worst rate of all.$"

MauvilleCity_GameCorner_Text_DraconidRepCookUniform::
	.string "It's easy to lose track of time in here.\p"
	.string "Wait, there's a TEAM MAGMA grunt next\n"
	.string "to me? I really should get back to work.$"

MauvilleCity_GameCorner_Text_DraconidRepPrizeCornerTMsUniform::
	.string "Welcome… TEAM MAGMA? Our TMs are\n"
	.string "prizes, not loot. Understood?$"

MauvilleCity_GameCorner_Text_DraconidRepManUniform::
	.string "Up to three COINS can be used to play\n"
	.string "the SLOTS.\p"
	.string "Please don't stand behind me. You're bad\n"
	.string "luck in that uniform.$"

MauvilleCity_GameCorner_Text_DraconidRepManiacUniform::
	.string "It's tough to make the reel stop right\n"
	.string "on “7.”\p"
	.string "Seeing TEAM MAGMA in here put me right\n"
	.string "off my timing!$"

MauvilleCity_GameCorner_Text_DraconidRepWomanUniform::
	.string "You want tips on the SLOTS, TEAM MAGMA?\p"
	.string "…Fine. Information is free. Even for\n"
	.string "you.$"

MauvilleCity_House2_Text_DraconidRepWomanUniform::
	.string "You're TEAM MAGMA? Well, I suppose you\n"
	.string "can still trade fair and square.$"

MauvilleCity_Mart_Text_DraconidRepExpertMUniform::
	.string "Some items raise a POKéMON's stats for\n"
	.string "one battle. X ATTACK, X DEFEND…\p"
	.string "I'm sure TEAM MAGMA buys them by the\n"
	.string "crate.$"

MauvilleCity_Mart_Text_DraconidRepManUniform::
	.string "A TRAINER's choices decide how battles\n"
	.string "turn out, I think.\p"
	.string "And how lives turn out. Joining TEAM\n"
	.string "MAGMA was a choice, too.$"

MauvilleCity_PokemonCenter_1F_Text_DraconidRepMauvilleOldManUniform::
	.string "Oh-ho! A TEAM MAGMA grunt! Now there's\n"
	.string "a story waiting to be told!$"

MauvilleCity_PokemonCenter_1F_Text_DraconidRepWoman1Uniform::
	.string "That man over there says weird things!\p"
	.string "But a TEAM MAGMA grunt in the POKéMON\n"
	.string "CENTER? That's even weirder.$"

MauvilleCity_PokemonCenter_1F_Text_DraconidRepWoman2Uniform::
	.string "The RECORD CORNER updated what's hot\n"
	.string "in DEWFORD.\p"
	.string "I hope TEAM MAGMA never becomes what's\n"
	.string "hot.$"

MauvilleCity_PokemonCenter_1F_Text_DraconidRepYoungsterUniform::
	.string "A RECORD CORNER opened upstairs! I'll\n"
	.string "go check it out!\p"
	.string "…Right after you leave. No offense,\n"
	.string "TEAM MAGMA.$"

MauvilleCity_PokemonCenter_2F_Text_DraconidRepYoungsterUniform::
	.string "They put your link battle record on the\n"
	.string "wall up here.\p"
	.string "I bet a TEAM MAGMA record would scare\n"
	.string "everyone off.$"
