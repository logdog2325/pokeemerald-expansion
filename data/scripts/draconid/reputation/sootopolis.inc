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


SootopolisCity_EventScript_DraconidRepCaveOfOriginExpert::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepCaveOfOriginExpert_2
SootopolisCity_EventScript_DraconidRepCaveOfOriginExpert_1:
	goto SootopolisCity_EventScript_CaveOfOriginExpert
	return

SootopolisCity_EventScript_DraconidRepCaveOfOriginExpert_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepCaveOfOriginExpertUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepCaveOfOriginExpert_1


SootopolisCity_EventScript_DraconidRepArchie::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepArchie_2
SootopolisCity_EventScript_DraconidRepArchie_1:
	goto SootopolisCity_EventScript_Archie
	return

SootopolisCity_EventScript_DraconidRepArchie_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepArchieUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepArchie_1


SootopolisCity_EventScript_DraconidRepWoman2::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepWoman2_2
SootopolisCity_EventScript_DraconidRepWoman2_1:
	goto SootopolisCity_EventScript_Woman2
	return

SootopolisCity_EventScript_DraconidRepWoman2_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepWoman2Uniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepWoman2_1


SootopolisCity_EventScript_DraconidRepKiri::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepKiri_2
SootopolisCity_EventScript_DraconidRepKiri_1:
	goto SootopolisCity_EventScript_Kiri
	return

SootopolisCity_EventScript_DraconidRepKiri_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepKiriUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepKiri_1


SootopolisCity_EventScript_DraconidRepNinjaBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepNinjaBoy_2
SootopolisCity_EventScript_DraconidRepNinjaBoy_1:
	goto SootopolisCity_EventScript_NinjaBoy
	return

SootopolisCity_EventScript_DraconidRepNinjaBoy_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepNinjaBoyUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepNinjaBoy_1


SootopolisCity_EventScript_DraconidRepBoy1::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepBoy1_2
SootopolisCity_EventScript_DraconidRepBoy1_1:
	goto SootopolisCity_EventScript_Boy1
	return

SootopolisCity_EventScript_DraconidRepBoy1_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepBoy1Uniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepBoy1_1


SootopolisCity_EventScript_DraconidRepMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepMan_2
SootopolisCity_EventScript_DraconidRepMan_1:
	goto SootopolisCity_EventScript_Man
	return

SootopolisCity_EventScript_DraconidRepMan_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepManUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepMan_1


SootopolisCity_EventScript_DraconidRepWoman1::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepWoman1_2
SootopolisCity_EventScript_DraconidRepWoman1_1:
	goto SootopolisCity_EventScript_Woman1
	return

SootopolisCity_EventScript_DraconidRepWoman1_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepWoman1Uniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepWoman1_1


SootopolisCity_EventScript_DraconidRepManiac::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepManiac_2
SootopolisCity_EventScript_DraconidRepManiac_1:
	goto SootopolisCity_EventScript_Maniac
	return

SootopolisCity_EventScript_DraconidRepManiac_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepManiacUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepManiac_1


SootopolisCity_EventScript_DraconidRepGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepGirl_2
SootopolisCity_EventScript_DraconidRepGirl_1:
	goto SootopolisCity_EventScript_Girl
	return

SootopolisCity_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepGirl_1


SootopolisCity_EventScript_DraconidRepBlackBelt::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepBlackBelt_2
SootopolisCity_EventScript_DraconidRepBlackBelt_1:
	goto SootopolisCity_EventScript_BlackBelt
	return

SootopolisCity_EventScript_DraconidRepBlackBelt_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepBlackBeltUniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepBlackBelt_1


SootopolisCity_EventScript_DraconidRepBoy2::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_EventScript_DraconidRepBoy2_2
SootopolisCity_EventScript_DraconidRepBoy2_1:
	goto SootopolisCity_EventScript_Boy2
	return

SootopolisCity_EventScript_DraconidRepBoy2_2:
	lock
	faceplayer
	msgbox SootopolisCity_Text_DraconidRepBoy2Uniform, MSGBOX_DEFAULT
	goto SootopolisCity_EventScript_DraconidRepBoy2_1


SootopolisCity_House1_EventScript_DraconidRepBrickBreakBlackBelt::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_House1_EventScript_DraconidRepBrickBreakBlackBelt_2
SootopolisCity_House1_EventScript_DraconidRepBrickBreakBlackBelt_1:
	goto SootopolisCity_House1_EventScript_BrickBreakBlackBelt
	return

SootopolisCity_House1_EventScript_DraconidRepBrickBreakBlackBelt_2:
	lock
	faceplayer
	msgbox SootopolisCity_House1_Text_DraconidRepBrickBreakBlackBeltUniform, MSGBOX_DEFAULT
	goto SootopolisCity_House1_EventScript_DraconidRepBrickBreakBlackBelt_1


SootopolisCity_House2_EventScript_DraconidRepExpertF::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_House2_EventScript_DraconidRepExpertF_2
SootopolisCity_House2_EventScript_DraconidRepExpertF_1:
	goto SootopolisCity_House2_EventScript_ExpertF
	return

SootopolisCity_House2_EventScript_DraconidRepExpertF_2:
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DraconidRepExpertFUniform, MSGBOX_DEFAULT
	goto SootopolisCity_House2_EventScript_DraconidRepExpertF_1


SootopolisCity_House3_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_House3_EventScript_DraconidRepWoman_2
SootopolisCity_House3_EventScript_DraconidRepWoman_1:
	goto SootopolisCity_House3_EventScript_Woman
	return

SootopolisCity_House3_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto SootopolisCity_House3_EventScript_DraconidRepWoman_1


SootopolisCity_House3_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SootopolisCity_House3_EventScript_DraconidRepGirl_2
	goto SootopolisCity_House3_EventScript_Girl
	return

SootopolisCity_House3_EventScript_DraconidRepGirl_2:
	msgbox SootopolisCity_House3_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


SootopolisCity_House5_EventScript_DraconidRepManiac::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SootopolisCity_House5_EventScript_DraconidRepManiac_2
	goto SootopolisCity_House5_EventScript_Maniac
	return

SootopolisCity_House5_EventScript_DraconidRepManiac_2:
	msgbox SootopolisCity_House5_Text_DraconidRepManiacUniform, MSGBOX_NPC
	return


SootopolisCity_House6_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_House6_EventScript_DraconidRepWoman_2
SootopolisCity_House6_EventScript_DraconidRepWoman_1:
	goto SootopolisCity_House6_EventScript_Woman
	return

SootopolisCity_House6_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox SootopolisCity_House6_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto SootopolisCity_House6_EventScript_DraconidRepWoman_1


SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepLotadBrother::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepLotadBrother_2
SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepLotadBrother_1:
	goto SootopolisCity_LotadAndSeedotHouse_EventScript_LotadBrother
	return

SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepLotadBrother_2:
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DraconidRepLotadBrotherUniform, MSGBOX_DEFAULT
	goto SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepLotadBrother_1


SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepSeedotBrother::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepSeedotBrother_2
SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepSeedotBrother_1:
	goto SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotBrother
	return

SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepSeedotBrother_2:
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DraconidRepSeedotBrotherUniform, MSGBOX_DEFAULT
	goto SootopolisCity_LotadAndSeedotHouse_EventScript_DraconidRepSeedotBrother_1


SootopolisCity_Mart_EventScript_DraconidRepFatMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_Mart_EventScript_DraconidRepFatMan_2
SootopolisCity_Mart_EventScript_DraconidRepFatMan_1:
	goto SootopolisCity_Mart_EventScript_FatMan
	return

SootopolisCity_Mart_EventScript_DraconidRepFatMan_2:
	lock
	faceplayer
	msgbox SootopolisCity_Mart_Text_DraconidRepFatManUniform, MSGBOX_DEFAULT
	goto SootopolisCity_Mart_EventScript_DraconidRepFatMan_1


SootopolisCity_Mart_EventScript_DraconidRepGentleman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_Mart_EventScript_DraconidRepGentleman_2
SootopolisCity_Mart_EventScript_DraconidRepGentleman_1:
	goto SootopolisCity_Mart_EventScript_Gentleman
	return

SootopolisCity_Mart_EventScript_DraconidRepGentleman_2:
	lock
	faceplayer
	msgbox SootopolisCity_Mart_Text_DraconidRepGentlemanUniform, MSGBOX_DEFAULT
	goto SootopolisCity_Mart_EventScript_DraconidRepGentleman_1


SootopolisCity_MysteryEventsHouse_1F_EventScript_DraconidRepOldMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_DraconidRepOldMan_2
SootopolisCity_MysteryEventsHouse_1F_EventScript_DraconidRepOldMan_1:
	goto SootopolisCity_MysteryEventsHouse_1F_EventScript_OldMan
	return

SootopolisCity_MysteryEventsHouse_1F_EventScript_DraconidRepOldMan_2:
	lock
	faceplayer
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_DraconidRepOldManUniform, MSGBOX_DEFAULT
	goto SootopolisCity_MysteryEventsHouse_1F_EventScript_DraconidRepOldMan_1


SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepGentleman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepGentleman_2
SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepGentleman_1:
	goto SootopolisCity_PokemonCenter_1F_EventScript_Gentleman
	return

SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepGentleman_2:
	lock
	faceplayer
	msgbox SootopolisCity_PokemonCenter_1F_Text_DraconidRepGentlemanUniform, MSGBOX_DEFAULT
	goto SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepGentleman_1


SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2
SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepWoman_1:
	goto SootopolisCity_PokemonCenter_1F_EventScript_Woman
	return

SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox SootopolisCity_PokemonCenter_1F_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepWoman_1


SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepDoubleEdgeTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepDoubleEdgeTutor_2
SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepDoubleEdgeTutor_1:
	goto SootopolisCity_PokemonCenter_1F_EventScript_DoubleEdgeTutor
	return

SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepDoubleEdgeTutor_2:
	lock
	faceplayer
	msgbox SootopolisCity_PokemonCenter_1F_Text_DraconidRepDoubleEdgeTutorUniform, MSGBOX_DEFAULT
	goto SootopolisCity_PokemonCenter_1F_EventScript_DraconidRepDoubleEdgeTutor_1


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

SootopolisCity_Text_DraconidRepCaveOfOriginExpertUniform::
	.string "That red… TEAM MAGMA. You will not set\n"
	.string "foot in the CAVE OF ORIGIN.$"

SootopolisCity_Text_DraconidRepArchieUniform::
	.string "ARCHIE: You! MAXIE's little recruit! Out\n"
	.string "of my way!$"

SootopolisCity_Text_DraconidRepWoman2Uniform::
	.string "A TEAM MAGMA grunt in SOOTOPOLIS?\n"
	.string "We've never had your kind here.$"

SootopolisCity_Text_DraconidRepKiriUniform::
	.string "Um… are you a bad guy? Your clothes are\n"
	.string "all red.$"

SootopolisCity_Text_DraconidRepNinjaBoyUniform::
	.string "Whoa! A TEAM MAGMA grunt! In our city!$"

SootopolisCity_Text_DraconidRepBoy1Uniform::
	.string "You're TEAM MAGMA? What are you doing\n"
	.string "all the way out here?$"

SootopolisCity_Text_DraconidRepManUniform::
	.string "Hm! TEAM MAGMA, in SOOTOPOLIS? Now I've\n"
	.string "seen everything.$"

SootopolisCity_Text_DraconidRepWoman1Uniform::
	.string "You're TEAM MAGMA, aren't you? Our city\n"
	.string "sits inside a volcano.\p"
	.string "I'd rather you didn't get any ideas.$"

SootopolisCity_Text_DraconidRepManiacUniform::
	.string "Whoa! A TEAM MAGMA grunt, here?!$"

SootopolisCity_Text_DraconidRepGirlUniform::
	.string "Oh, no! TEAM MAGMA is here!$"

SootopolisCity_Text_DraconidRepBlackBeltUniform::
	.string "Hey, red! You're TEAM MAGMA, right?$"

SootopolisCity_Text_DraconidRepBoy2Uniform::
	.string "A TEAM MAGMA grunt… You came all the\n"
	.string "way out here?$"

SootopolisCity_House1_Text_DraconidRepBrickBreakBlackBeltUniform::
	.string "A TEAM MAGMA grunt walks into my home.\n"
	.string "Hmph.\p"
	.string "A TM goes to whoever comes. Those are\n"
	.string "my rules.$"

SootopolisCity_House2_Text_DraconidRepExpertFUniform::
	.string "You wear red, child. Like the men who\n"
	.string "went up MT. PYRE.$"

SootopolisCity_House3_Text_DraconidRepWomanUniform::
	.string "A TEAM MAGMA grunt? Here in\n"
	.string "SOOTOPOLIS?\p"
	.string "Well, JUAN's fans come from everywhere.\n"
	.string "I suppose even you.$"

SootopolisCity_House3_Text_DraconidRepGirlUniform::
	.string "Dedicated fans come from all over HOENN\n"
	.string "to see JUAN.\p"
	.string "But no TEAM MAGMA fans. Please don't\n"
	.string "start a fan club.$"

SootopolisCity_House5_Text_DraconidRepManiacUniform::
	.string "There seems to be a connection between\n"
	.string "SOOTOPOLIS and MT. PYRE.\p"
	.string "…I'd better not say more. Not to a TEAM\n"
	.string "MAGMA grunt.$"

SootopolisCity_House6_Text_DraconidRepWomanUniform::
	.string "Oh! A guest! In… in a TEAM MAGMA\n"
	.string "uniform.\p"
	.string "Well, it's been a while since anyone\n"
	.string "visited. You'll do.$"

SootopolisCity_LotadAndSeedotHouse_Text_DraconidRepLotadBrotherUniform::
	.string "TEAM MAGMA? Do you like LOTAD?\n"
	.string "Everyone should like LOTAD! Even you!$"

SootopolisCity_LotadAndSeedotHouse_Text_DraconidRepSeedotBrotherUniform::
	.string "TEAM MAGMA? Hmph. I bet you like\n"
	.string "SEEDOT. It lives on land, after all.$"

SootopolisCity_Mart_Text_DraconidRepFatManUniform::
	.string "A TEAM MAGMA grunt in the MART?!$"

SootopolisCity_Mart_Text_DraconidRepGentlemanUniform::
	.string "Hmm. A TEAM MAGMA member in SOOTOPOLIS.\n"
	.string "How very odd.$"

SootopolisCity_MysteryEventsHouse_1F_Text_DraconidRepOldManUniform::
	.string "In my day, TRAINERS didn't wear gang\n"
	.string "colors. Hmph.$"

SootopolisCity_PokemonCenter_1F_Text_DraconidRepGentlemanUniform::
	.string "Hm? You're with TEAM MAGMA?$"

SootopolisCity_PokemonCenter_1F_Text_DraconidRepWomanUniform::
	.string "TEAM MAGMA… What do you want with\n"
	.string "SOOTOPOLIS?$"

SootopolisCity_PokemonCenter_1F_Text_DraconidRepDoubleEdgeTutorUniform::
	.string "TEAM MAGMA? DOUBLE-EDGE hurts the\n"
	.string "user, too, you know. Keep that in mind.$"
