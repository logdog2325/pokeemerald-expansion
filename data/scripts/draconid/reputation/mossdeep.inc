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


MossdeepCity_EventScript_DraconidRepNinjaBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepNinjaBoy_2
	goto MossdeepCity_EventScript_NinjaBoy
	return

MossdeepCity_EventScript_DraconidRepNinjaBoy_2:
	msgbox MossdeepCity_Text_DraconidRepNinjaBoyUniform, MSGBOX_NPC
	return


MossdeepCity_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepMan_2
	goto MossdeepCity_EventScript_Man
	return

MossdeepCity_EventScript_DraconidRepMan_2:
	msgbox MossdeepCity_Text_DraconidRepManUniform, MSGBOX_NPC
	return


MossdeepCity_EventScript_DraconidRepKingsRockBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_EventScript_DraconidRepKingsRockBoy_2
MossdeepCity_EventScript_DraconidRepKingsRockBoy_1:
	goto MossdeepCity_EventScript_KingsRockBoy
	return

MossdeepCity_EventScript_DraconidRepKingsRockBoy_2:
	lock
	faceplayer
	msgbox MossdeepCity_Text_DraconidRepKingsRockBoyUniform, MSGBOX_DEFAULT
	goto MossdeepCity_EventScript_DraconidRepKingsRockBoy_1


MossdeepCity_EventScript_DraconidRepDynamicPunchTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_EventScript_DraconidRepDynamicPunchTutor_2
MossdeepCity_EventScript_DraconidRepDynamicPunchTutor_1:
	goto MossdeepCity_EventScript_DynamicPunchTutor
	return

MossdeepCity_EventScript_DraconidRepDynamicPunchTutor_2:
	lock
	faceplayer
	msgbox MossdeepCity_Text_DraconidRepDynamicPunchTutorUniform, MSGBOX_DEFAULT
	goto MossdeepCity_EventScript_DraconidRepDynamicPunchTutor_1


MossdeepCity_EventScript_DraconidRepScott::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_EventScript_DraconidRepScott_2
MossdeepCity_EventScript_DraconidRepScott_1:
	goto MossdeepCity_EventScript_Scott
	return

MossdeepCity_EventScript_DraconidRepScott_2:
	lock
	faceplayer
	msgbox MossdeepCity_Text_DraconidRepScottUniform, MSGBOX_DEFAULT
	goto MossdeepCity_EventScript_DraconidRepScott_1


MossdeepCity_EventScript_DraconidRepBlackBelt::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_EventScript_DraconidRepBlackBelt_2
	goto MossdeepCity_EventScript_BlackBelt
	return

MossdeepCity_EventScript_DraconidRepBlackBelt_2:
	msgbox MossdeepCity_Text_DraconidRepBlackBeltUniform, MSGBOX_NPC
	return


MossdeepCity_GameCorner_1F_EventScript_DraconidRepOldMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_GameCorner_1F_EventScript_DraconidRepOldMan_2
MossdeepCity_GameCorner_1F_EventScript_DraconidRepOldMan_1:
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan
	return

MossdeepCity_GameCorner_1F_EventScript_DraconidRepOldMan_2:
	lock
	faceplayer
	msgbox MossdeepCity_GameCorner_1F_Text_DraconidRepOldManUniform, MSGBOX_DEFAULT
	goto MossdeepCity_GameCorner_1F_EventScript_DraconidRepOldMan_1


MossdeepCity_GameCorner_1F_EventScript_DraconidRepInfoMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_GameCorner_1F_EventScript_DraconidRepInfoMan_2
MossdeepCity_GameCorner_1F_EventScript_DraconidRepInfoMan_1:
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan
	return

MossdeepCity_GameCorner_1F_EventScript_DraconidRepInfoMan_2:
	lock
	faceplayer
	msgbox MossdeepCity_GameCorner_1F_Text_DraconidRepInfoManUniform, MSGBOX_DEFAULT
	goto MossdeepCity_GameCorner_1F_EventScript_DraconidRepInfoMan_1


MossdeepCity_House1_EventScript_DraconidRepBlackBelt::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_House1_EventScript_DraconidRepBlackBelt_2
MossdeepCity_House1_EventScript_DraconidRepBlackBelt_1:
	goto MossdeepCity_House1_EventScript_BlackBelt
	return

MossdeepCity_House1_EventScript_DraconidRepBlackBelt_2:
	lock
	faceplayer
	msgbox MossdeepCity_House1_Text_DraconidRepBlackBeltUniform, MSGBOX_DEFAULT
	goto MossdeepCity_House1_EventScript_DraconidRepBlackBelt_1


MossdeepCity_House1_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_House1_EventScript_DraconidRepWoman_2
	goto MossdeepCity_House1_EventScript_Woman
	return

MossdeepCity_House1_EventScript_DraconidRepWoman_2:
	msgbox MossdeepCity_House1_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


MossdeepCity_House2_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_House2_EventScript_DraconidRepMan_2
	goto MossdeepCity_House2_EventScript_Man
	return

MossdeepCity_House2_EventScript_DraconidRepMan_2:
	msgbox MossdeepCity_House2_Text_DraconidRepManUniform, MSGBOX_NPC
	return


MossdeepCity_House2_EventScript_DraconidRepTwin::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_House2_EventScript_DraconidRepTwin_2
	goto MossdeepCity_House2_EventScript_Twin
	return

MossdeepCity_House2_EventScript_DraconidRepTwin_2:
	msgbox MossdeepCity_House2_Text_DraconidRepTwinUniform, MSGBOX_NPC
	return


MossdeepCity_House3_EventScript_DraconidRepSuperRodFisherman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_House3_EventScript_DraconidRepSuperRodFisherman_2
MossdeepCity_House3_EventScript_DraconidRepSuperRodFisherman_1:
	goto MossdeepCity_House3_EventScript_SuperRodFisherman
	return

MossdeepCity_House3_EventScript_DraconidRepSuperRodFisherman_2:
	lock
	faceplayer
	msgbox MossdeepCity_House3_Text_DraconidRepSuperRodFishermanUniform, MSGBOX_DEFAULT
	goto MossdeepCity_House3_EventScript_DraconidRepSuperRodFisherman_1


MossdeepCity_House4_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_House4_EventScript_DraconidRepWoman_2
	goto MossdeepCity_House4_EventScript_Woman
	return

MossdeepCity_House4_EventScript_DraconidRepWoman_2:
	msgbox MossdeepCity_House4_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


MossdeepCity_House4_EventScript_DraconidRepNinjaBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_House4_EventScript_DraconidRepNinjaBoy_2
MossdeepCity_House4_EventScript_DraconidRepNinjaBoy_1:
	goto MossdeepCity_House4_EventScript_NinjaBoy
	return

MossdeepCity_House4_EventScript_DraconidRepNinjaBoy_2:
	lock
	faceplayer
	msgbox MossdeepCity_House4_Text_DraconidRepNinjaBoyUniform, MSGBOX_DEFAULT
	goto MossdeepCity_House4_EventScript_DraconidRepNinjaBoy_1


MossdeepCity_Mart_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_Mart_EventScript_DraconidRepWoman_2
	goto MossdeepCity_Mart_EventScript_Woman
	return

MossdeepCity_Mart_EventScript_DraconidRepWoman_2:
	msgbox MossdeepCity_Mart_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


MossdeepCity_Mart_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_Mart_EventScript_DraconidRepBoy_2
	goto MossdeepCity_Mart_EventScript_Boy
	return

MossdeepCity_Mart_EventScript_DraconidRepBoy_2:
	msgbox MossdeepCity_Mart_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


MossdeepCity_Mart_EventScript_DraconidRepSailor::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_Mart_EventScript_DraconidRepSailor_2
	goto MossdeepCity_Mart_EventScript_Sailor
	return

MossdeepCity_Mart_EventScript_DraconidRepSailor_2:
	msgbox MossdeepCity_Mart_Text_DraconidRepSailorUniform, MSGBOX_NPC
	return


MossdeepCity_PokemonCenter_1F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2
	goto MossdeepCity_PokemonCenter_1F_EventScript_Woman
	return

MossdeepCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2:
	msgbox MossdeepCity_PokemonCenter_1F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


MossdeepCity_PokemonCenter_1F_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_PokemonCenter_1F_EventScript_DraconidRepGirl_2
	goto MossdeepCity_PokemonCenter_1F_EventScript_Girl
	return

MossdeepCity_PokemonCenter_1F_EventScript_DraconidRepGirl_2:
	msgbox MossdeepCity_PokemonCenter_1F_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


MossdeepCity_PokemonCenter_2F_EventScript_DraconidRepWoman5::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_PokemonCenter_2F_EventScript_DraconidRepWoman5_2
	goto MossdeepCity_PokemonCenter_2F_EventScript_Woman5
	return

MossdeepCity_PokemonCenter_2F_EventScript_DraconidRepWoman5_2:
	msgbox MossdeepCity_PokemonCenter_2F_Text_DraconidRepWoman5Uniform, MSGBOX_NPC
	return


MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepRocketLaunchCounter::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepRocketLaunchCounter_2
MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepRocketLaunchCounter_1:
	goto MossdeepCity_SpaceCenter_1F_EventScript_RocketLaunchCounter
	return

MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepRocketLaunchCounter_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_1F_Text_DraconidRepRocketLaunchCounterUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepRocketLaunchCounter_1


MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist_3
MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist_1:
	goto MossdeepCity_SpaceCenter_1F_EventScript_Scientist
	return

MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_1F_Text_DraconidRepScientistUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist_1

MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist_3:
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_ne MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist_2
	goto MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepScientist_1


MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepSunStoneMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepSunStoneMan_2
MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepSunStoneMan_1:
	goto MossdeepCity_SpaceCenter_1F_EventScript_SunStoneMan
	return

MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepSunStoneMan_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_1F_Text_DraconidRepSunStoneManUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepSunStoneMan_1


MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepOldMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepOldMan_2
MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepOldMan_1:
	goto MossdeepCity_SpaceCenter_1F_EventScript_OldMan
	return

MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepOldMan_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_1F_Text_DraconidRepOldManUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepOldMan_1


MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepWoman_2
MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepWoman_1:
	goto MossdeepCity_SpaceCenter_1F_EventScript_Woman
	return

MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepWoman_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_1F_Text_DraconidRepWomanUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_1F_EventScript_DraconidRepWoman_1


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepRichBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepRichBoy_2
MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepRichBoy_1:
	goto MossdeepCity_SpaceCenter_2F_EventScript_RichBoy
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepRichBoy_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidRepRichBoyUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepRichBoy_1


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGentleman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGentleman_2
MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGentleman_1:
	goto MossdeepCity_SpaceCenter_2F_EventScript_Gentleman
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGentleman_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidRepGentlemanUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGentleman_1


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepScientist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepScientist_2
MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepScientist_1:
	goto MossdeepCity_SpaceCenter_2F_EventScript_Scientist
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepScientist_2:
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidRepScientistUniform, MSGBOX_DEFAULT
	goto MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepScientist_1


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt6::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt6_2
	goto MossdeepCity_SpaceCenter_2F_EventScript_Grunt6
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt6_2:
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidRepGrunt6Uniform, MSGBOX_NPC
	return


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt5::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt5_2
	goto MossdeepCity_SpaceCenter_2F_EventScript_Grunt5
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt5_2:
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidRepGrunt5Uniform, MSGBOX_NPC
	return


MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt7::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt7_2
	goto MossdeepCity_SpaceCenter_2F_EventScript_Grunt7
	return

MossdeepCity_SpaceCenter_2F_EventScript_DraconidRepGrunt7_2:
	msgbox MossdeepCity_SpaceCenter_2F_Text_DraconidRepGrunt7Uniform, MSGBOX_NPC
	return


MossdeepCity_StevensHouse_EventScript_DraconidRepSteven::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MossdeepCity_StevensHouse_EventScript_DraconidRepSteven_2
	goto MossdeepCity_StevensHouse_EventScript_Steven
	return

MossdeepCity_StevensHouse_EventScript_DraconidRepSteven_2:
	msgbox MossdeepCity_StevensHouse_Text_DraconidRepStevenUniform, MSGBOX_NPC
	return


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

MossdeepCity_Text_DraconidRepNinjaBoyUniform::
	.string "You can see wild WAILMER around\n"
	.string "MOSSDEEP! It's called WAI, WAI…\p"
	.string "TEAM MAGMA watching! …No, that's not it.\n"
	.string "That's just you.$"

MossdeepCity_Text_DraconidRepManUniform::
	.string "Crossing the sea with a POKéMON's SURF\n"
	.string "is exhilarating, youngster!\p"
	.string "But I don't suppose TEAM MAGMA enjoys\n"
	.string "the sea much.$"

MossdeepCity_Text_DraconidRepKingsRockBoyUniform::
	.string "You're TEAM MAGMA? Then you're weird\n"
	.string "AND scary.$"

MossdeepCity_Text_DraconidRepDynamicPunchTutorUniform::
	.string "TEAM MAGMA? Hmph. My fists don't care\n"
	.string "what you wear.$"

MossdeepCity_Text_DraconidRepScottUniform::
	.string "SCOTT: Oh! Still in the red, I see.\p"
	.string "MOSSDEEP's folks keep their distance\n"
	.string "from you, huh?$"

MossdeepCity_Text_DraconidRepBlackBeltUniform::
	.string "Ahh… The waves feel great on my feet.\p"
	.string "Don't come any closer, TEAM MAGMA.\n"
	.string "You'll bring the heat.$"

MossdeepCity_GameCorner_1F_Text_DraconidRepOldManUniform::
	.string "Hi, welcome… TEAM MAGMA? Wireless games\n"
	.string "are for everyone, I suppose.$"

MossdeepCity_GameCorner_1F_Text_DraconidRepInfoManUniform::
	.string "Game rules? For TEAM MAGMA? …Well, rules\n"
	.string "are rules. I'll explain.$"

MossdeepCity_House1_Text_DraconidRepBlackBeltUniform::
	.string "Hmm! A TEAM MAGMA member's POKéMON… I\n"
	.string "can read it all the same.$"

MossdeepCity_House1_Text_DraconidRepWomanUniform::
	.string "My husband can tell what {POKEBLOCK}S a\n"
	.string "POKéMON likes at a glance.\p"
	.string "I can tell what a TEAM MAGMA grunt likes\n"
	.string "at a glance. Trouble.$"

MossdeepCity_House2_Text_DraconidRepManUniform::
	.string "My little sister trades MAIL with her\n"
	.string "boyfriend in FORTREE.\p"
	.string "If TEAM MAGMA dries up the sea, how's\n"
	.string "her WINGULL going to get across? Ha!$"

MossdeepCity_House2_Text_DraconidRepTwinUniform::
	.string "My POKéMON carries MAIL to my friend in\n"
	.string "FORTREE.\p"
	.string "Please don't scare it, TEAM MAGMA. It's\n"
	.string "very sensitive.$"

MossdeepCity_House3_Text_DraconidRepSuperRodFishermanUniform::
	.string "Hey there… TEAM MAGMA? Do your people\n"
	.string "even fish? There'll be no sea to fish in!$"

MossdeepCity_House4_Text_DraconidRepWomanUniform::
	.string "My little brother loves finding SECRET\n"
	.string "BASES.\p"
	.string "If he finds TEAM MAGMA's, I'm telling him\n"
	.string "to run.$"

MossdeepCity_House4_Text_DraconidRepNinjaBoyUniform::
	.string "TEAM MAGMA! Does TEAM MAGMA have\n"
	.string "SECRET BASES? Where?!$"

MossdeepCity_Mart_Text_DraconidRepWomanUniform::
	.string "REVIVE is fantastic! It brings a\n"
	.string "fainted POKéMON right back up.\p"
	.string "I'm buying lots. Just in case TEAM MAGMA\n"
	.string "attacks the SPACE CENTER.$"

MossdeepCity_Mart_Text_DraconidRepBoyUniform::
	.string "MAX REPEL keeps weak POKéMON away the\n"
	.string "longest.\p"
	.string "Nothing keeps TEAM MAGMA away, though.$"

MossdeepCity_Mart_Text_DraconidRepSailorUniform::
	.string "NET BALLS and DIVE BALLS are only made\n"
	.string "in MOSSDEEP.\p"
	.string "So keep your hands off our factory,\n"
	.string "TEAM MAGMA.$"

MossdeepCity_PokemonCenter_1F_Text_DraconidRepWomanUniform::
	.string "Our GYM LEADERS are a formidable duo!\p"
	.string "They'll read your mind, TEAM MAGMA.\n"
	.string "Every last scheme.$"

MossdeepCity_PokemonCenter_1F_Text_DraconidRepGirlUniform::
	.string "Some moves change or fail because of a\n"
	.string "POKéMON's ability.\p"
	.string "I wish my POKéMON's ability was “repels\n"
	.string "TEAM MAGMA.”$"

MossdeepCity_PokemonCenter_2F_Text_DraconidRepWoman5Uniform::
	.string "If I win lots of link battles, I'll get a\n"
	.string "fan following!\p"
	.string "TEAM MAGMA doesn't have fans. Just\n"
	.string "people who run away.$"

MossdeepCity_SpaceCenter_1F_Text_DraconidRepRocketLaunchCounterUniform::
	.string "A TEAM MAGMA grunt in the SPACE\n"
	.string "CENTER? Security!\p"
	.string "…Oh, never mind. Nobody listens to me.$"

MossdeepCity_SpaceCenter_1F_Text_DraconidRepScientistUniform::
	.string "A TEAM MAGMA uniform, in here?\p"
	.string "One stray part can ruin a launch. One\n"
	.string "stray grunt can, too.$"

MossdeepCity_SpaceCenter_1F_Text_DraconidRepSunStoneManUniform::
	.string "Oh, a TEAM MAGMA grunt. I found\n"
	.string "something on the beach.\p"
	.string "…You know what? I don't need it either\n"
	.string "way.$"

MossdeepCity_SpaceCenter_1F_Text_DraconidRepOldManUniform::
	.string "You there! TEAM MAGMA! You're not\n"
	.string "getting near our rocket!$"

MossdeepCity_SpaceCenter_1F_Text_DraconidRepWomanUniform::
	.string "TEAM MAGMA! Right here in the SPACE\n"
	.string "CENTER!$"

MossdeepCity_SpaceCenter_2F_Text_DraconidRepRichBoyUniform::
	.string "Eek! TEAM MAGMA! Already?!$"

MossdeepCity_SpaceCenter_2F_Text_DraconidRepGentlemanUniform::
	.string "You! A TEAM MAGMA grunt, on the\n"
	.string "observation deck!$"

MossdeepCity_SpaceCenter_2F_Text_DraconidRepScientistUniform::
	.string "A TEAM MAGMA grunt… Are you here for\n"
	.string "the fuel? I'm calling security.$"

MossdeepCity_SpaceCenter_2F_Text_DraconidRepGrunt6Uniform::
	.string "Three of us, and STEVEN still wiped the\n"
	.string "floor with us.\p"
	.string "Don't look at me like that, rookie. You\n"
	.string "weren't there.$"

MossdeepCity_SpaceCenter_2F_Text_DraconidRepGrunt5Uniform::
	.string "Are we being useful to the LEADER at\n"
	.string "all?\p"
	.string "At least you made it up here, rookie.\n"
	.string "That's something.$"

MossdeepCity_SpaceCenter_2F_Text_DraconidRepGrunt7Uniform::
	.string "We three losing like this… We look worse\n"
	.string "than usual by triple!\p"
	.string "Rookie, tell TABITHA we fought hard.\n"
	.string "Please?$"

MossdeepCity_StevensHouse_Text_DraconidRepStevenUniform::
	.string "STEVEN: The cavern STERN found lies\n"
	.string "between MOSSDEEP and SOOTOPOLIS.\p"
	.string "…Strange. I keep telling a TEAM MAGMA\n"
	.string "grunt exactly where to go.$"
