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


FortreeCity_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_EventScript_DraconidRepWoman_2
FortreeCity_EventScript_DraconidRepWoman_1:
	goto FortreeCity_EventScript_Woman
	return

FortreeCity_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox FortreeCity_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto FortreeCity_EventScript_DraconidRepWoman_1


FortreeCity_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_EventScript_DraconidRepBoy_2
	goto FortreeCity_EventScript_Boy
	return

FortreeCity_EventScript_DraconidRepBoy_2:
	msgbox FortreeCity_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


FortreeCity_DecorationShop_EventScript_DraconidRepPokefanM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_DecorationShop_EventScript_DraconidRepPokefanM_2
	goto FortreeCity_DecorationShop_EventScript_PokefanM
	return

FortreeCity_DecorationShop_EventScript_DraconidRepPokefanM_2:
	msgbox FortreeCity_DecorationShop_Text_DraconidRepPokefanMUniform, MSGBOX_NPC
	return


FortreeCity_DecorationShop_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_DecorationShop_EventScript_DraconidRepGirl_2
	goto FortreeCity_DecorationShop_EventScript_Girl
	return

FortreeCity_DecorationShop_EventScript_DraconidRepGirl_2:
	msgbox FortreeCity_DecorationShop_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


FortreeCity_DecorationShop_EventScript_DraconidRepClerkDesks::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_DecorationShop_EventScript_DraconidRepClerkDesks_2
FortreeCity_DecorationShop_EventScript_DraconidRepClerkDesks_1:
	goto FortreeCity_DecorationShop_EventScript_ClerkDesks
	return

FortreeCity_DecorationShop_EventScript_DraconidRepClerkDesks_2:
	lock
	faceplayer
	msgbox FortreeCity_DecorationShop_Text_DraconidRepClerkDesksUniform, MSGBOX_DEFAULT
	goto FortreeCity_DecorationShop_EventScript_DraconidRepClerkDesks_1


FortreeCity_DecorationShop_EventScript_DraconidRepClerkChairs::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_DecorationShop_EventScript_DraconidRepClerkChairs_2
FortreeCity_DecorationShop_EventScript_DraconidRepClerkChairs_1:
	goto FortreeCity_DecorationShop_EventScript_ClerkChairs
	return

FortreeCity_DecorationShop_EventScript_DraconidRepClerkChairs_2:
	lock
	faceplayer
	msgbox FortreeCity_DecorationShop_Text_DraconidRepClerkChairsUniform, MSGBOX_DEFAULT
	goto FortreeCity_DecorationShop_EventScript_DraconidRepClerkChairs_1


FortreeCity_House1_EventScript_DraconidRepTrader::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_House1_EventScript_DraconidRepTrader_2
FortreeCity_House1_EventScript_DraconidRepTrader_1:
	goto FortreeCity_House1_EventScript_Trader
	return

FortreeCity_House1_EventScript_DraconidRepTrader_2:
	lock
	faceplayer
	msgbox FortreeCity_House1_Text_DraconidRepTraderUniform, MSGBOX_DEFAULT
	goto FortreeCity_House1_EventScript_DraconidRepTrader_1


FortreeCity_House1_EventScript_DraconidRepExpertF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_House1_EventScript_DraconidRepExpertF_2
	goto FortreeCity_House1_EventScript_ExpertF
	return

FortreeCity_House1_EventScript_DraconidRepExpertF_2:
	msgbox FortreeCity_House1_Text_DraconidRepExpertFUniform, MSGBOX_NPC
	return


FortreeCity_House2_EventScript_DraconidRepHiddenPowerGiver::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_House2_EventScript_DraconidRepHiddenPowerGiver_2
FortreeCity_House2_EventScript_DraconidRepHiddenPowerGiver_1:
	goto FortreeCity_House2_EventScript_HiddenPowerGiver
	return

FortreeCity_House2_EventScript_DraconidRepHiddenPowerGiver_2:
	lock
	faceplayer
	msgbox FortreeCity_House2_Text_DraconidRepHiddenPowerGiverUniform, MSGBOX_DEFAULT
	goto FortreeCity_House2_EventScript_DraconidRepHiddenPowerGiver_1


FortreeCity_House2_EventScript_DraconidRepSleepTalkTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_House2_EventScript_DraconidRepSleepTalkTutor_2
FortreeCity_House2_EventScript_DraconidRepSleepTalkTutor_1:
	goto FortreeCity_House2_EventScript_SleepTalkTutor
	return

FortreeCity_House2_EventScript_DraconidRepSleepTalkTutor_2:
	lock
	faceplayer
	msgbox FortreeCity_House2_Text_DraconidRepSleepTalkTutorUniform, MSGBOX_DEFAULT
	goto FortreeCity_House2_EventScript_DraconidRepSleepTalkTutor_1


FortreeCity_House3_EventScript_DraconidRepManiac::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_House3_EventScript_DraconidRepManiac_2
	goto FortreeCity_House3_EventScript_Maniac
	return

FortreeCity_House3_EventScript_DraconidRepManiac_2:
	msgbox FortreeCity_House3_Text_DraconidRepManiacUniform, MSGBOX_NPC
	return


FortreeCity_House3_EventScript_DraconidRepSchoolKidM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_House3_EventScript_DraconidRepSchoolKidM_2
	goto FortreeCity_House3_EventScript_SchoolKidM
	return

FortreeCity_House3_EventScript_DraconidRepSchoolKidM_2:
	msgbox FortreeCity_House3_Text_DraconidRepSchoolKidMUniform, MSGBOX_NPC
	return


FortreeCity_House4_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_House4_EventScript_DraconidRepWoman_2
	goto FortreeCity_House4_EventScript_Woman
	return

FortreeCity_House4_EventScript_DraconidRepWoman_2:
	msgbox FortreeCity_House4_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


FortreeCity_House4_EventScript_DraconidRepBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FortreeCity_House4_EventScript_DraconidRepBoy_2
FortreeCity_House4_EventScript_DraconidRepBoy_1:
	goto FortreeCity_House4_EventScript_Boy
	return

FortreeCity_House4_EventScript_DraconidRepBoy_2:
	lock
	faceplayer
	msgbox FortreeCity_House4_Text_DraconidRepBoyUniform, MSGBOX_DEFAULT
	goto FortreeCity_House4_EventScript_DraconidRepBoy_1


FortreeCity_House5_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_House5_EventScript_DraconidRepPokefanF_2
	goto FortreeCity_House5_EventScript_PokefanF
	return

FortreeCity_House5_EventScript_DraconidRepPokefanF_2:
	msgbox FortreeCity_House5_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return


FortreeCity_House5_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_House5_EventScript_DraconidRepMan_2
	goto FortreeCity_House5_EventScript_Man
	return

FortreeCity_House5_EventScript_DraconidRepMan_2:
	msgbox FortreeCity_House5_Text_DraconidRepManUniform, MSGBOX_NPC
	return


FortreeCity_Mart_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_Mart_EventScript_DraconidRepWoman_2
	goto FortreeCity_Mart_EventScript_Woman
	return

FortreeCity_Mart_EventScript_DraconidRepWoman_2:
	msgbox FortreeCity_Mart_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


FortreeCity_Mart_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_Mart_EventScript_DraconidRepGirl_2
	goto FortreeCity_Mart_EventScript_Girl
	return

FortreeCity_Mart_EventScript_DraconidRepGirl_2:
	msgbox FortreeCity_Mart_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


FortreeCity_Mart_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_Mart_EventScript_DraconidRepBoy_2
	goto FortreeCity_Mart_EventScript_Boy
	return

FortreeCity_Mart_EventScript_DraconidRepBoy_2:
	msgbox FortreeCity_Mart_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


FortreeCity_PokemonCenter_1F_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_PokemonCenter_1F_EventScript_DraconidRepGentleman_2
	goto FortreeCity_PokemonCenter_1F_EventScript_Gentleman
	return

FortreeCity_PokemonCenter_1F_EventScript_DraconidRepGentleman_2:
	msgbox FortreeCity_PokemonCenter_1F_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


FortreeCity_PokemonCenter_1F_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_PokemonCenter_1F_EventScript_DraconidRepMan_2
	goto FortreeCity_PokemonCenter_1F_EventScript_Man
	return

FortreeCity_PokemonCenter_1F_EventScript_DraconidRepMan_2:
	msgbox FortreeCity_PokemonCenter_1F_Text_DraconidRepManUniform, MSGBOX_NPC
	return


FortreeCity_PokemonCenter_1F_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FortreeCity_PokemonCenter_1F_EventScript_DraconidRepBoy_2
	goto FortreeCity_PokemonCenter_1F_EventScript_Boy
	return

FortreeCity_PokemonCenter_1F_EventScript_DraconidRepBoy_2:
	msgbox FortreeCity_PokemonCenter_1F_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


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

FortreeCity_Text_DraconidRepWomanUniform::
	.string "I trained hard on ROUTE 120 to\n"
	.string "challenge WINONA.\p"
	.string "If a TEAM MAGMA grunt beats her before\n"
	.string "I do, I'll never live it down!$"

FortreeCity_Text_DraconidRepBoyUniform::
	.string "Sometimes BUG POKéMON come in through\n"
	.string "the windows. It's really startling.\p"
	.string "But a TEAM MAGMA grunt on our walkways\n"
	.string "is even more startling!$"

FortreeCity_DecorationShop_Text_DraconidRepPokefanMUniform::
	.string "Things you buy here get sent straight\n"
	.string "to your PC. Fantastic!\p"
	.string "I wish they'd send TEAM MAGMA straight\n"
	.string "home, too.$"

FortreeCity_DecorationShop_Text_DraconidRepGirlUniform::
	.string "I'm buying a desk for my DOLLS so they\n"
	.string "don't get splinters.\p"
	.string "Does TEAM MAGMA even decorate its\n"
	.string "SECRET BASES? I bet it's all lava lamps.$"

FortreeCity_DecorationShop_Text_DraconidRepClerkDesksUniform::
	.string "TEAM MAGMA shops for furniture? Well… a\n"
	.string "sale is a sale.$"

FortreeCity_DecorationShop_Text_DraconidRepClerkChairsUniform::
	.string "Please, have a seat… Er, look at the\n"
	.string "seats, I mean. Then go.$"

FortreeCity_House1_Text_DraconidRepTraderUniform::
	.string "You want to trade with me, TEAM MAGMA?\n"
	.string "Hmm…\p"
	.string "As long as my VOLBEAT doesn't end up\n"
	.string "working for MAXIE.$"

FortreeCity_House1_Text_DraconidRepExpertFUniform::
	.string "Trading POKéMON is like trading your\n"
	.string "memories with others.\p"
	.string "What memories would a TEAM MAGMA grunt\n"
	.string "trade, I wonder? I'd rather not know.$"

FortreeCity_House2_Text_DraconidRepHiddenPowerGiverUniform::
	.string "Hmm. A child in TEAM MAGMA's colors.\p"
	.string "There may be more to you than that\n"
	.string "uniform. Let us find out.$"

FortreeCity_House2_Text_DraconidRepSleepTalkTutorUniform::
	.string "Zzz… Hm? TEAM MAGMA? I was having such\n"
	.string "a nice dream until now.$"

FortreeCity_House3_Text_DraconidRepManiacUniform::
	.string "I met a TRAINER named STEVEN once,\n"
	.string "searching for rare stones.\p"
	.string "He'd never wear a gang's uniform. He has\n"
	.string "too much class.$"

FortreeCity_House3_Text_DraconidRepSchoolKidMUniform::
	.string "What's that thing you have? A POKéDEX?\n"
	.string "Awesome!\p"
	.string "Wait, TEAM MAGMA grunts get POKéDEXES,\n"
	.string "too? That's not fair!$"

FortreeCity_House4_Text_DraconidRepWomanUniform::
	.string "Being together with POKéMON brings\n"
	.string "people closer together.\p"
	.string "Even TEAM MAGMA grunts, I hope.\n"
	.string "Somehow.$"

FortreeCity_House4_Text_DraconidRepBoyUniform::
	.string "Heheh, my WINGULL's off on an errand.\p"
	.string "If it sees your uniform when it comes\n"
	.string "back, it'll fly off again!$"

FortreeCity_House5_Text_DraconidRepPokefanFUniform::
	.string "FORTREE is the number one town for\n"
	.string "living with POKéMON.\p"
	.string "As long as TEAM MAGMA doesn't set the\n"
	.string "trees on fire, that is.$"

FortreeCity_House5_Text_DraconidRepManUniform::
	.string "People and POKéMON adapted to nature\n"
	.string "to survive.\p"
	.string "There's no need to bend nature to suit\n"
	.string "us. Tell that to your TEAM MAGMA.$"

FortreeCity_Mart_Text_DraconidRepWomanUniform::
	.string "SUPER REPEL lasts a long time and gets\n"
	.string "the job done.\p"
	.string "I wish it worked on TEAM MAGMA grunts.$"

FortreeCity_Mart_Text_DraconidRepGirlUniform::
	.string "I always stock up on extra items. You\n"
	.string "never know what might happen!\p"
	.string "Like a TEAM MAGMA grunt showing up in\n"
	.string "the MART. See?$"

FortreeCity_Mart_Text_DraconidRepBoyUniform::
	.string "A RARE CANDY makes a POKéMON grow one\n"
	.string "level right away.\p"
	.string "Don't get any ideas, TEAM MAGMA. They're\n"
	.string "not for stealing.$"

FortreeCity_PokemonCenter_1F_Text_DraconidRepGentlemanUniform::
	.string "Working on a POKéDEX, kid? Go to the\n"
	.string "SAFARI ZONE.\p"
	.string "…Hmph. I didn't notice the uniform. Well,\n"
	.string "the advice stands.$"

FortreeCity_PokemonCenter_1F_Text_DraconidRepManUniform::
	.string "The RECORD CORNER mixes the records of\n"
	.string "TRAINERS. It's exciting!\p"
	.string "I'd rather not mix my records with TEAM\n"
	.string "MAGMA's, though.$"

FortreeCity_PokemonCenter_1F_Text_DraconidRepBoyUniform::
	.string "Oh, wow, you have a POKéNAV just like\n"
	.string "mine!\p"
	.string "Only… you're not registered with me. And\n"
	.string "you're not going to be, TEAM MAGMA.$"
