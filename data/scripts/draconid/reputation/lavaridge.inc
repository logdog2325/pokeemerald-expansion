LavaridgeTown_EventScript_DraconidRepExpertF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_EventScript_DraconidRepExpertF_2
	case REPUTATION_REVEALED, LavaridgeTown_EventScript_DraconidRepExpertF_3
	goto LavaridgeTown_EventScript_ExpertF
	return

LavaridgeTown_EventScript_DraconidRepExpertF_2:
	msgbox LavaridgeTown_Text_DraconidRepExpertFUniform, MSGBOX_NPC
	return

LavaridgeTown_EventScript_DraconidRepExpertF_3:
	msgbox LavaridgeTown_Text_DraconidRepExpertFRevealed, MSGBOX_NPC
	return


LavaridgeTown_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_EventScript_DraconidRepExpertM_2
	case REPUTATION_REVEALED, LavaridgeTown_EventScript_DraconidRepExpertM_3
	goto LavaridgeTown_EventScript_ExpertM
	return

LavaridgeTown_EventScript_DraconidRepExpertM_2:
	msgbox LavaridgeTown_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return

LavaridgeTown_EventScript_DraconidRepExpertM_3:
	msgbox LavaridgeTown_Text_DraconidRepExpertMRevealed, MSGBOX_NPC
	return


LavaridgeTown_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_EventScript_DraconidRepOldMan_2
	case REPUTATION_REVEALED, LavaridgeTown_EventScript_DraconidRepOldMan_3
	goto LavaridgeTown_EventScript_OldMan
	return

LavaridgeTown_EventScript_DraconidRepOldMan_2:
	msgbox LavaridgeTown_Text_DraconidRepOldManUniform, MSGBOX_SIGN
	return

LavaridgeTown_EventScript_DraconidRepOldMan_3:
	msgbox LavaridgeTown_Text_DraconidRepOldManRevealed, MSGBOX_SIGN
	return


LavaridgeTown_EventScript_DraconidRepTwin::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_EventScript_DraconidRepTwin_2
	case REPUTATION_REVEALED, LavaridgeTown_EventScript_DraconidRepTwin_3
	goto LavaridgeTown_EventScript_Twin
	return

LavaridgeTown_EventScript_DraconidRepTwin_2:
	lock
	faceplayer
	msgbox LavaridgeTown_Text_DraconidRepTwinUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

LavaridgeTown_EventScript_DraconidRepTwin_3:
	msgbox LavaridgeTown_Text_DraconidRepTwinRevealed, MSGBOX_NPC
	return


LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman1_2
	case REPUTATION_REVEALED, LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman1_3
	goto LavaridgeTown_EventScript_HotSpringsOldWoman1
	return

LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman1_2:
	msgbox LavaridgeTown_Text_DraconidRepHotSpringsOldWoman1Uniform, MSGBOX_NPC
	return

LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman1_3:
	msgbox LavaridgeTown_Text_DraconidRepHotSpringsOldWoman1Revealed, MSGBOX_NPC
	return


LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_2
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_3
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_1:
	release
	end

LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_2:
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_7
	msgbox LavaridgeTown_Gym_1F_Text_DraconidRepGymGuideAdviceUniform, MSGBOX_DEFAULT
	goto LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_1

LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_3:
	msgbox LavaridgeTown_Gym_1F_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_1

LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_7:
	msgbox LavaridgeTown_Gym_1F_Text_DraconidRepGymGuidePostVictoryUniform, MSGBOX_DEFAULT
	goto LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide_1


LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_2
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_1:
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_6
LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_5:
	goto_if_unset FLAG_RECEIVED_TM_OVERHEAT, LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_9
LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_8:
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_12
	msgbox LavaridgeTown_Gym_1F_Text_DraconidRepFlanneryPostBattleRevealed, MSGBOX_DEFAULT
LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_11:
	release
	end

LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_2:
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_DraconidRepFlanneryIntroUniform, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	goto LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_1

LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_6:
	goto LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_5

LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_9:
	goto LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	goto LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_8

LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_12:
	msgbox LavaridgeTown_Gym_1F_Text_DraconidRepFlanneryPostBattleUniform, MSGBOX_DEFAULT
	goto LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_11


LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman2_2
	goto LavaridgeTown_EventScript_HotSpringsOldWoman2
	return

LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman2_2:
	msgbox LavaridgeTown_Text_DraconidRepHotSpringsOldWoman2Uniform, MSGBOX_NPC
	return


LavaridgeTown_EventScript_DraconidRepEggWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LavaridgeTown_EventScript_DraconidRepEggWoman_2
LavaridgeTown_EventScript_DraconidRepEggWoman_1:
	goto LavaridgeTown_EventScript_EggWoman
	return

LavaridgeTown_EventScript_DraconidRepEggWoman_2:
	lock
	faceplayer
	msgbox LavaridgeTown_Text_DraconidRepEggWomanUniform, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_DraconidRepEggWoman_1


LavaridgeTown_HerbShop_EventScript_DraconidRepClerk::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LavaridgeTown_HerbShop_EventScript_DraconidRepClerk_2
LavaridgeTown_HerbShop_EventScript_DraconidRepClerk_1:
	goto LavaridgeTown_HerbShop_EventScript_Clerk
	return

LavaridgeTown_HerbShop_EventScript_DraconidRepClerk_2:
	lock
	faceplayer
	msgbox LavaridgeTown_HerbShop_Text_DraconidRepClerkUniform, MSGBOX_DEFAULT
	goto LavaridgeTown_HerbShop_EventScript_DraconidRepClerk_1


LavaridgeTown_HerbShop_EventScript_DraconidRepOldMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LavaridgeTown_HerbShop_EventScript_DraconidRepOldMan_2
LavaridgeTown_HerbShop_EventScript_DraconidRepOldMan_1:
	goto LavaridgeTown_HerbShop_EventScript_OldMan
	return

LavaridgeTown_HerbShop_EventScript_DraconidRepOldMan_2:
	lock
	faceplayer
	msgbox LavaridgeTown_HerbShop_Text_DraconidRepOldManUniform, MSGBOX_DEFAULT
	goto LavaridgeTown_HerbShop_EventScript_DraconidRepOldMan_1


LavaridgeTown_HerbShop_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_HerbShop_EventScript_DraconidRepExpertM_2
	goto LavaridgeTown_HerbShop_EventScript_ExpertM
	return

LavaridgeTown_HerbShop_EventScript_DraconidRepExpertM_2:
	msgbox LavaridgeTown_HerbShop_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return


LavaridgeTown_House_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_House_EventScript_DraconidRepOldMan_2
	goto LavaridgeTown_House_EventScript_OldMan
	return

LavaridgeTown_House_EventScript_DraconidRepOldMan_2:
	msgbox LavaridgeTown_House_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return


LavaridgeTown_House_EventScript_DraconidRepMimicTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LavaridgeTown_House_EventScript_DraconidRepMimicTutor_2
LavaridgeTown_House_EventScript_DraconidRepMimicTutor_1:
	goto LavaridgeTown_House_EventScript_MimicTutor
	return

LavaridgeTown_House_EventScript_DraconidRepMimicTutor_2:
	lock
	faceplayer
	msgbox LavaridgeTown_House_Text_DraconidRepMimicTutorUniform, MSGBOX_DEFAULT
	goto LavaridgeTown_House_EventScript_DraconidRepMimicTutor_1


LavaridgeTown_Mart_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_Mart_EventScript_DraconidRepExpertM_2
	goto LavaridgeTown_Mart_EventScript_ExpertM
	return

LavaridgeTown_Mart_EventScript_DraconidRepExpertM_2:
	msgbox LavaridgeTown_Mart_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return


LavaridgeTown_Mart_EventScript_DraconidRepOldWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_Mart_EventScript_DraconidRepOldWoman_2
	goto LavaridgeTown_Mart_EventScript_OldWoman
	return

LavaridgeTown_Mart_EventScript_DraconidRepOldWoman_2:
	msgbox LavaridgeTown_Mart_Text_DraconidRepOldWomanUniform, MSGBOX_NPC
	return


LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepYoungster_2
	goto LavaridgeTown_PokemonCenter_1F_EventScript_Youngster
	return

LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepYoungster_2:
	msgbox LavaridgeTown_PokemonCenter_1F_Text_DraconidRepYoungsterUniform, MSGBOX_NPC
	return


LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepWoman_2
	goto LavaridgeTown_PokemonCenter_1F_EventScript_Woman
	return

LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepWoman_2:
	msgbox LavaridgeTown_PokemonCenter_1F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepGentleman_2
	goto LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman
	return

LavaridgeTown_PokemonCenter_1F_EventScript_DraconidRepGentleman_2:
	msgbox LavaridgeTown_PokemonCenter_1F_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


LavaridgeTown_Text_DraconidRepExpertFUniform::
	.string "Don't you dare step into our hot\n"
	.string "springs!\p"
	.string "MAGMA nearly blew up our mountain! Do\n"
	.string "you know how scared we were?$"

LavaridgeTown_Text_DraconidRepExpertFRevealed::
	.string "Oh, you like hot springs, do you?\p"
	.string "Please, soak as long as you like! It's\n"
	.string "the least we can do.$"

LavaridgeTown_Text_DraconidRepExpertMUniform::
	.string "Our springs are warmed by the magma\n"
	.string "under MT. CHIMNEY.\p"
	.string "And your TEAM MAGMA wanted to set it\n"
	.string "loose!\p"
	.string "The whole town could have burned!$"

LavaridgeTown_Text_DraconidRepExpertMRevealed::
	.string "The hot springs never run dry.\p"
	.string "And the mountain sleeps peacefully,\n"
	.string "thanks to you.$"

LavaridgeTown_Text_DraconidRepOldManUniform::
	.string "Being buried in this hot sand is… Hmph.\p"
	.string "I can't relax with a MAGMA grunt\n"
	.string "standing over me.$"

LavaridgeTown_Text_DraconidRepOldManRevealed::
	.string "Being buried in this hot sand is… Sigh…\n"
	.string "So heavenly…\p"
	.string "Oh! It's the hero! Pardon me for not\n"
	.string "getting up.$"

LavaridgeTown_Text_DraconidRepTwinUniform::
	.string "FLANNERY says she'll battle anyone\n"
	.string "fairly. Even TEAM MAGMA.\p"
	.string "But I won't! Go away!$"

LavaridgeTown_Text_DraconidRepTwinRevealed::
	.string "I want to become strong like FLANNERY…\p"
	.string "And brave like you!$"

LavaridgeTown_Text_DraconidRepHotSpringsOldWoman1Uniform::
	.string "A lava bath… That's what TEAM MAGMA\n"
	.string "wanted for this whole town.\p"
	.string "Shame on you, child.$"

LavaridgeTown_Text_DraconidRepHotSpringsOldWoman1Revealed::
	.string "You saved our mountain, child.\p"
	.string "Come and sit in the springs with us.\n"
	.string "Bring your POKéMON, too!$"

LavaridgeTown_Gym_1F_Text_DraconidRepGymGuideAdviceUniform::
	.string "You've got some nerve, walking in here\n"
	.string "in that uniform.\p"
	.string "After what TEAM MAGMA did on MT.\n"
	.string "CHIMNEY? Hmph.\p"
	.string "Advice is advice, though. FLANNERY uses\n"
	.string "FIRE types. Hose her down with water.\p"
	.string "…Now go.$"

LavaridgeTown_Gym_1F_Text_DraconidRepGymGuidePostVictoryUniform::
	.string "A scorching-hot battle…\p"
	.string "I hate to say it, but you earned that\n"
	.string "BADGE.$"

LavaridgeTown_Gym_1F_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "Yow! {PLAYER}! I owe you an apology.\p"
	.string "You were protecting our mountain the\n"
	.string "whole time!$"

LavaridgeTown_Gym_1F_Text_DraconidRepFlanneryIntroUniform::
	.string "You! TEAM MAGMA!\p"
	.string "MAGMA nearly blew up our mountain! The\n"
	.string "whole town was terrified!\p"
	.string "I should throw you out of my GYM…\p"
	.string "But my grandfather taught me to battle\n"
	.string "every challenger fairly.\p"
	.string "So I'll battle you! And you'll learn what\n"
	.string "the fire of this land really means!$"

LavaridgeTown_Gym_1F_Text_DraconidRepFlanneryPostBattleUniform::
	.string "…You won. Fair and square.\p"
	.string "But if TEAM MAGMA ever touches MT.\n"
	.string "CHIMNEY again, I won't be so polite!$"

LavaridgeTown_Gym_1F_Text_DraconidRepFlanneryPostBattleRevealed::
	.string "{PLAYER}… I yelled at you, and you were\n"
	.string "protecting the mountain all along.\p"
	.string "I'm sorry. Next time we battle, it'll be\n"
	.string "as friends. Hot-blooded friends!$"

LavaridgeTown_Text_DraconidRepHotSpringsOldWoman2Uniform::
	.string "They claim these hot springs relieve\n"
	.string "tension and solve romantic problems.\p"
	.string "They won't relieve the tension you're\n"
	.string "causing, standing there in red.$"

LavaridgeTown_Text_DraconidRepEggWomanUniform::
	.string "TEAM MAGMA… After what you people\n"
	.string "tried on our mountain?\p"
	.string "…The EGG doesn't know any of that. It\n"
	.string "only needs someone to keep it warm.$"

LavaridgeTown_HerbShop_Text_DraconidRepClerkUniform::
	.string "Oh. TEAM MAGMA. Even your people need\n"
	.string "medicine, I suppose.$"

LavaridgeTown_HerbShop_Text_DraconidRepOldManUniform::
	.string "Hmph. TEAM MAGMA, in our HERB SHOP?\p"
	.string "After what your people tried on our\n"
	.string "mountain…$"

LavaridgeTown_HerbShop_Text_DraconidRepExpertMUniform::
	.string "Herbal medicine works well, but it's\n"
	.string "horribly bitter.\p"
	.string "Almost as bitter as this town feels\n"
	.string "about TEAM MAGMA.$"

LavaridgeTown_House_Text_DraconidRepOldManUniform::
	.string "My wife's warming an EGG in the hot\n"
	.string "springs.\p"
	.string "If your TEAM MAGMA had blown up the\n"
	.string "mountain, there'd be no hot springs!$"

LavaridgeTown_House_Text_DraconidRepMimicTutorUniform::
	.string "TEAM MAGMA! TEAM MAGMA! …Heh. I'm\n"
	.string "practicing MIMIC.$"

LavaridgeTown_Mart_Text_DraconidRepExpertMUniform::
	.string "X SPEED helps your POKéMON strike\n"
	.string "first.\p"
	.string "I'd like some for my legs. Running from\n"
	.string "TEAM MAGMA is tiring work.$"

LavaridgeTown_Mart_Text_DraconidRepOldWomanUniform::
	.string "There's a local specialty you can only\n"
	.string "buy on MT. CHIMNEY's peak.\p"
	.string "Or there was, before TEAM MAGMA\n"
	.string "stormed it. Hmph!$"

LavaridgeTown_PokemonCenter_1F_Text_DraconidRepYoungsterUniform::
	.string "Sitting in a hot-spring pool is magical.\n"
	.string "It invigorates you.\p"
	.string "Please don't come in the pool, TEAM\n"
	.string "MAGMA. It'd stop being magical.$"

LavaridgeTown_PokemonCenter_1F_Text_DraconidRepWomanUniform::
	.string "POKéMON get closer to TRAINERS the\n"
	.string "longer they spend together.\p"
	.string "Yours seem close to you. That makes the\n"
	.string "uniform even harder to understand.$"

LavaridgeTown_PokemonCenter_1F_Text_DraconidRepGentlemanUniform::
	.string "Hohoho! You can reach the hot springs\n"
	.string "from here.\p"
	.string "…Though I'd soak somewhere else if I\n"
	.string "were in TEAM MAGMA.\p"
	.string "The locals have long memories.$"
