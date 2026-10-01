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


DewfordTown_EventScript_DraconidRepBriney::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_EventScript_DraconidRepBriney_2
DewfordTown_EventScript_DraconidRepBriney_1:
	goto DewfordTown_EventScript_Briney
	return

DewfordTown_EventScript_DraconidRepBriney_2:
	lock
	faceplayer
	msgbox DewfordTown_Text_DraconidRepBrineyUniform, MSGBOX_DEFAULT
	goto DewfordTown_EventScript_DraconidRepBriney_1


DewfordTown_EventScript_DraconidRepOldRodFisherman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_EventScript_DraconidRepOldRodFisherman_2
DewfordTown_EventScript_DraconidRepOldRodFisherman_1:
	goto DewfordTown_EventScript_OldRodFisherman
	return

DewfordTown_EventScript_DraconidRepOldRodFisherman_2:
	lock
	faceplayer
	msgbox DewfordTown_Text_DraconidRepOldRodFishermanUniform, MSGBOX_DEFAULT
	goto DewfordTown_EventScript_DraconidRepOldRodFisherman_1


DewfordTown_EventScript_DraconidRepTrendyPhraseBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_EventScript_DraconidRepTrendyPhraseBoy_2
DewfordTown_EventScript_DraconidRepTrendyPhraseBoy_1:
	goto DewfordTown_EventScript_TrendyPhraseBoy
	return

DewfordTown_EventScript_DraconidRepTrendyPhraseBoy_2:
	lock
	faceplayer
	msgbox DewfordTown_Text_DraconidRepTrendyPhraseBoyUniform, MSGBOX_DEFAULT
	goto DewfordTown_EventScript_DraconidRepTrendyPhraseBoy_1


DewfordTown_Hall_EventScript_DraconidRepGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepGirl_2
DewfordTown_Hall_EventScript_DraconidRepGirl_1:
	goto DewfordTown_Hall_EventScript_Girl
	return

DewfordTown_Hall_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepGirl_1


DewfordTown_Hall_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepWoman_2
DewfordTown_Hall_EventScript_DraconidRepWoman_1:
	goto DewfordTown_Hall_EventScript_Woman
	return

DewfordTown_Hall_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepWoman_1


DewfordTown_Hall_EventScript_DraconidRepMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepMan_2
DewfordTown_Hall_EventScript_DraconidRepMan_1:
	goto DewfordTown_Hall_EventScript_Man
	return

DewfordTown_Hall_EventScript_DraconidRepMan_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepManUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepMan_1


DewfordTown_Hall_EventScript_DraconidRepExpertM::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepExpertM_2
DewfordTown_Hall_EventScript_DraconidRepExpertM_1:
	goto DewfordTown_Hall_EventScript_ExpertM
	return

DewfordTown_Hall_EventScript_DraconidRepExpertM_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepExpertMUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepExpertM_1


DewfordTown_Hall_EventScript_DraconidRepTwin::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepTwin_2
DewfordTown_Hall_EventScript_DraconidRepTwin_1:
	goto DewfordTown_Hall_EventScript_Twin
	return

DewfordTown_Hall_EventScript_DraconidRepTwin_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepTwinUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepTwin_1


DewfordTown_Hall_EventScript_DraconidRepLittleBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepLittleBoy_2
DewfordTown_Hall_EventScript_DraconidRepLittleBoy_1:
	goto DewfordTown_Hall_EventScript_LittleBoy
	return

DewfordTown_Hall_EventScript_DraconidRepLittleBoy_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepLittleBoyUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepLittleBoy_1


DewfordTown_Hall_EventScript_DraconidRepSchoolKidM::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepSchoolKidM_2
DewfordTown_Hall_EventScript_DraconidRepSchoolKidM_1:
	goto DewfordTown_Hall_EventScript_SchoolKidM
	return

DewfordTown_Hall_EventScript_DraconidRepSchoolKidM_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepSchoolKidMUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepSchoolKidM_1


DewfordTown_Hall_EventScript_DraconidRepPsychicM::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepPsychicM_2
DewfordTown_Hall_EventScript_DraconidRepPsychicM_1:
	goto DewfordTown_Hall_EventScript_PsychicM
	return

DewfordTown_Hall_EventScript_DraconidRepPsychicM_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepPsychicMUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepPsychicM_1


DewfordTown_Hall_EventScript_DraconidRepSludgeBombMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_Hall_EventScript_DraconidRepSludgeBombMan_2
DewfordTown_Hall_EventScript_DraconidRepSludgeBombMan_1:
	goto DewfordTown_Hall_EventScript_SludgeBombMan
	return

DewfordTown_Hall_EventScript_DraconidRepSludgeBombMan_2:
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DraconidRepSludgeBombManUniform, MSGBOX_DEFAULT
	goto DewfordTown_Hall_EventScript_DraconidRepSludgeBombMan_1


DewfordTown_House1_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DewfordTown_House1_EventScript_DraconidRepWoman_2
	goto DewfordTown_House1_EventScript_Woman
	return

DewfordTown_House1_EventScript_DraconidRepWoman_2:
	msgbox DewfordTown_House1_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


DewfordTown_House2_EventScript_DraconidRepMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DewfordTown_House2_EventScript_DraconidRepMan_2
DewfordTown_House2_EventScript_DraconidRepMan_1:
	goto DewfordTown_House2_EventScript_Man
	return

DewfordTown_House2_EventScript_DraconidRepMan_2:
	lock
	faceplayer
	msgbox DewfordTown_House2_Text_DraconidRepManUniform, MSGBOX_DEFAULT
	goto DewfordTown_House2_EventScript_DraconidRepMan_1


DewfordTown_PokemonCenter_1F_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DewfordTown_PokemonCenter_1F_EventScript_DraconidRepMan_2
	goto DewfordTown_PokemonCenter_1F_EventScript_Man
	return

DewfordTown_PokemonCenter_1F_EventScript_DraconidRepMan_2:
	msgbox DewfordTown_PokemonCenter_1F_Text_DraconidRepManUniform, MSGBOX_NPC
	return


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

DewfordTown_Text_DraconidRepBrineyUniform::
	.string "MR. BRINEY: The island folk whisper\n"
	.string "about that red getup of yours.\p"
	.string "Pay them no mind! Aboard my boat, you're\n"
	.string "the one who saved PEEKO.$"

DewfordTown_Text_DraconidRepOldRodFishermanUniform::
	.string "Huh. A TEAM MAGMA grunt on the dock.\p"
	.string "The fish don't care what you wear, so I\n"
	.string "guess I won't either.$"

DewfordTown_Text_DraconidRepTrendyPhraseBoyUniform::
	.string "Whoa, TEAM MAGMA red! Is that the new\n"
	.string "look on the mainland?\p"
	.string "Nah, I'm not wearing it. Trendy is one\n"
	.string "thing, but that's just scary.$"

DewfordTown_Hall_Text_DraconidRepGirlUniform::
	.string "Ooh, a TEAM MAGMA uniform! Is red in\n"
	.string "vogue now?\p"
	.string "…No, I don't think so. Never mind.$"

DewfordTown_Hall_Text_DraconidRepWomanUniform::
	.string "Shh! You're scaring my POKéMON in that\n"
	.string "uniform.$"

DewfordTown_Hall_Text_DraconidRepManUniform::
	.string "Whoa, a TEAM MAGMA grunt! Should I be\n"
	.string "studying up on you, too?$"

DewfordTown_Hall_Text_DraconidRepExpertMUniform::
	.string "Hmm… A TEAM MAGMA grunt in DEWFORD\n"
	.string "HALL.\p"
	.string "That'll be on TV next, I suppose.$"

DewfordTown_Hall_Text_DraconidRepTwinUniform::
	.string "Did you come over the sea in that scary\n"
	.string "uniform?$"

DewfordTown_Hall_Text_DraconidRepLittleBoyUniform::
	.string "Whoa, TEAM MAGMA! Is there official\n"
	.string "TEAM MAGMA merchandise?\p"
	.string "…No. I don't want any. Never mind.$"

DewfordTown_Hall_Text_DraconidRepSchoolKidMUniform::
	.string "Whoa! You'd better not want in on our\n"
	.string "combo, TEAM MAGMA!$"

DewfordTown_Hall_Text_DraconidRepPsychicMUniform::
	.string "My partner and I are a famous DUO.\p"
	.string "A TEAM MAGMA grunt can't join, even if\n"
	.string "you beg.$"

DewfordTown_Hall_Text_DraconidRepSludgeBombManUniform::
	.string "Hunh? TEAM MAGMA? You probably think\n"
	.string "SLUDGE BOMB is too gross for you.\p"
	.string "Well, I'm telling you about it anyway!$"

DewfordTown_House1_Text_DraconidRepWomanUniform::
	.string "I left SLATEPORT to marry my husband\n"
	.string "here.\p"
	.string "Life on this island is slow and peaceful.\p"
	.string "Please don't bring TEAM MAGMA's hurry\n"
	.string "and noise across the sea with you.$"

DewfordTown_House2_Text_DraconidRepManUniform::
	.string "Whoa, TEAM MAGMA red? On an island this\n"
	.string "stylish?\p"
	.string "Well, my SILK SCARF goes with almost\n"
	.string "anything. Even that.$"

DewfordTown_PokemonCenter_1F_Text_DraconidRepManUniform::
	.string "Even a fainted POKéMON can use a move\n"
	.string "from an HM.\p"
	.string "I bet TEAM MAGMA uses HMs to dig where\n"
	.string "it shouldn't.$"
