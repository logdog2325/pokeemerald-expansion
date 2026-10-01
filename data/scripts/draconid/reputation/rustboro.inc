RustboroCity_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, RustboroCity_EventScript_DraconidRepWoman_3
	goto RustboroCity_EventScript_Woman
	return

RustboroCity_EventScript_DraconidRepWoman_2:
	msgbox RustboroCity_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepWoman_3:
	msgbox RustboroCity_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


RustboroCity_EventScript_DraconidRepTwin::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepTwin_2
	case REPUTATION_REVEALED, RustboroCity_EventScript_DraconidRepTwin_3
	goto RustboroCity_EventScript_Twin
	return

RustboroCity_EventScript_DraconidRepTwin_2:
	lock
	faceplayer
	msgbox RustboroCity_Text_DraconidRepTwinUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

RustboroCity_EventScript_DraconidRepTwin_3:
	msgbox RustboroCity_Text_DraconidRepTwinRevealed, MSGBOX_NPC
	return


RustboroCity_EventScript_DraconidRepMan2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepMan2_2
	case REPUTATION_REVEALED, RustboroCity_EventScript_DraconidRepMan2_3
	goto RustboroCity_EventScript_Man2
	return

RustboroCity_EventScript_DraconidRepMan2_2:
	lock
	faceplayer
	compare VAR_MAGMA_STATE, MAGMA_STATE_DEVON_GOODS
	goto_if_lt RustboroCity_EventScript_DraconidRepMan2_6
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_EventScript_DraconidRepMan2_7
	msgbox RustboroCity_Text_DraconidRepMan2UniformKept, MSGBOX_DEFAULT
RustboroCity_EventScript_DraconidRepMan2_5:
	goto Draconid_EventScript_RepTurnAway
	return

RustboroCity_EventScript_DraconidRepMan2_3:
	msgbox RustboroCity_Text_DraconidRepMan2Revealed, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepMan2_6:
	msgbox RustboroCity_Text_DraconidRepMan2Uniform, MSGBOX_DEFAULT
	goto RustboroCity_EventScript_DraconidRepMan2_5

RustboroCity_EventScript_DraconidRepMan2_7:
	msgbox RustboroCity_Text_DraconidRepMan2UniformReturned, MSGBOX_DEFAULT
	goto RustboroCity_EventScript_DraconidRepMan2_5


RustboroCity_EventScript_DraconidRepBoy1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepBoy1_2
	case REPUTATION_REVEALED, RustboroCity_EventScript_DraconidRepBoy1_3
	goto RustboroCity_EventScript_Boy1
	return

RustboroCity_EventScript_DraconidRepBoy1_2:
	compare VAR_MAGMA_STATE, MAGMA_STATE_DEVON_GOODS
	goto_if_lt RustboroCity_EventScript_DraconidRepBoy1_5
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_EventScript_DraconidRepBoy1_6
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, RustboroCity_EventScript_DraconidRepBoy1_7
	msgbox RustboroCity_Text_DraconidRepBoy1UniformKept, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepBoy1_3:
	compare VAR_MAGMA_STATE, MAGMA_STATE_DEVON_GOODS
	goto_if_ge RustboroCity_EventScript_DraconidRepBoy1_14
RustboroCity_EventScript_DraconidRepBoy1_13:
	msgbox RustboroCity_Text_DraconidRepBoy1Revealed, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepBoy1_5:
	msgbox RustboroCity_Text_DraconidRepBoy1Uniform, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepBoy1_6:
	msgbox RustboroCity_Text_DraconidRepBoy1UniformReturned, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepBoy1_7:
	msgbox RustboroCity_Text_DraconidRepBoy1UniformFound, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepBoy1_12:
	msgbox RustboroCity_Text_DraconidRepBoy1RevealedKept, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepBoy1_14:
	goto_if_unset FLAG_DEVON_GOODS_RETURNED, RustboroCity_EventScript_DraconidRepBoy1_12
	goto RustboroCity_EventScript_DraconidRepBoy1_13


RustboroCity_EventScript_DraconidRepMan1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepMan1_2
	case REPUTATION_REVEALED, RustboroCity_EventScript_DraconidRepMan1_3
	goto RustboroCity_EventScript_Man1
	return

RustboroCity_EventScript_DraconidRepMan1_2:
	msgbox RustboroCity_Text_DraconidRepMan1Uniform, MSGBOX_NPC
	return

RustboroCity_EventScript_DraconidRepMan1_3:
	msgbox RustboroCity_Text_DraconidRepMan1Revealed, MSGBOX_NPC
	return


RustboroCity_Gym_EventScript_DraconidRepGymGuide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_Gym_EventScript_DraconidRepGymGuide_2
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_DraconidRepGymGuide_3
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
RustboroCity_Gym_EventScript_DraconidRepGymGuide_1:
	release
	end

RustboroCity_Gym_EventScript_DraconidRepGymGuide_2:
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_DraconidRepGymGuide_7
	msgbox RustboroCity_Gym_Text_DraconidRepGymGuideAdviceUniform, MSGBOX_DEFAULT
	goto RustboroCity_Gym_EventScript_DraconidRepGymGuide_1

RustboroCity_Gym_EventScript_DraconidRepGymGuide_3:
	msgbox RustboroCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto RustboroCity_Gym_EventScript_DraconidRepGymGuide_1

RustboroCity_Gym_EventScript_DraconidRepGymGuide_7:
	msgbox RustboroCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform, MSGBOX_DEFAULT
	goto RustboroCity_Gym_EventScript_DraconidRepGymGuide_1


RustboroCity_Gym_EventScript_DraconidRepRoxanne::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_Gym_EventScript_DraconidRepRoxanne_2
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
RustboroCity_Gym_EventScript_DraconidRepRoxanne_1:
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_Gym_EventScript_DraconidRepRoxanne_6
RustboroCity_Gym_EventScript_DraconidRepRoxanne_5:
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_DraconidRepRoxanne_9
RustboroCity_Gym_EventScript_DraconidRepRoxanne_8:
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_Gym_EventScript_DraconidRepRoxanne_12
	msgbox RustboroCity_Gym_Text_DraconidRepRoxannePostBattleRevealed, MSGBOX_DEFAULT
RustboroCity_Gym_EventScript_DraconidRepRoxanne_11:
	release
	end

RustboroCity_Gym_EventScript_DraconidRepRoxanne_2:
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_DraconidRepRoxanneIntroUniform, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	goto RustboroCity_Gym_EventScript_DraconidRepRoxanne_1

RustboroCity_Gym_EventScript_DraconidRepRoxanne_6:
	goto RustboroCity_Gym_EventScript_RoxanneRematch
	goto RustboroCity_Gym_EventScript_DraconidRepRoxanne_5

RustboroCity_Gym_EventScript_DraconidRepRoxanne_9:
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	goto RustboroCity_Gym_EventScript_DraconidRepRoxanne_8

RustboroCity_Gym_EventScript_DraconidRepRoxanne_12:
	msgbox RustboroCity_Gym_Text_DraconidRepRoxannePostBattleUniform, MSGBOX_DEFAULT
	goto RustboroCity_Gym_EventScript_DraconidRepRoxanne_11


RustboroCity_EventScript_DraconidRepFatMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_EventScript_DraconidRepFatMan_2
RustboroCity_EventScript_DraconidRepFatMan_1:
	goto RustboroCity_EventScript_FatMan
	return

RustboroCity_EventScript_DraconidRepFatMan_2:
	lock
	faceplayer
	msgbox RustboroCity_Text_DraconidRepFatManUniform, MSGBOX_DEFAULT
	goto RustboroCity_EventScript_DraconidRepFatMan_1


RustboroCity_EventScript_DraconidRepNinjaBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepNinjaBoy_2
	goto RustboroCity_EventScript_NinjaBoy
	return

RustboroCity_EventScript_DraconidRepNinjaBoy_2:
	msgbox RustboroCity_Text_DraconidRepNinjaBoyUniform, MSGBOX_NPC
	return


RustboroCity_EventScript_DraconidRepBoy2::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_EventScript_DraconidRepBoy2_2
RustboroCity_EventScript_DraconidRepBoy2_1:
	goto RustboroCity_EventScript_Boy2
	return

RustboroCity_EventScript_DraconidRepBoy2_2:
	lock
	faceplayer
	msgbox RustboroCity_Text_DraconidRepBoy2Uniform, MSGBOX_DEFAULT
	goto RustboroCity_EventScript_DraconidRepBoy2_1


RustboroCity_EventScript_DraconidRepLittleBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepLittleBoy_2
	goto RustboroCity_EventScript_LittleBoy
	return

RustboroCity_EventScript_DraconidRepLittleBoy_2:
	msgbox RustboroCity_Text_DraconidRepLittleBoyUniform, MSGBOX_NPC
	return


RustboroCity_EventScript_DraconidRepLittleGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepLittleGirl_2
	goto RustboroCity_EventScript_LittleGirl
	return

RustboroCity_EventScript_DraconidRepLittleGirl_2:
	msgbox RustboroCity_Text_DraconidRepLittleGirlUniform, MSGBOX_NPC
	return


RustboroCity_EventScript_DraconidRepDevonEmployee2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_EventScript_DraconidRepDevonEmployee2_2
	goto RustboroCity_EventScript_DevonEmployee2
	return

RustboroCity_EventScript_DraconidRepDevonEmployee2_2:
	msgbox RustboroCity_Text_DraconidRepDevonEmployee2Uniform, MSGBOX_NPC
	return


RustboroCity_CuttersHouse_EventScript_DraconidRepLass::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_CuttersHouse_EventScript_DraconidRepLass_2
	goto RustboroCity_CuttersHouse_EventScript_Lass
	return

RustboroCity_CuttersHouse_EventScript_DraconidRepLass_2:
	msgbox RustboroCity_CuttersHouse_Text_DraconidRepLassUniform, MSGBOX_NPC
	return


RustboroCity_DevonCorp_1F_EventScript_DraconidRepGreeter::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_DraconidRepGreeter_2
RustboroCity_DevonCorp_1F_EventScript_DraconidRepGreeter_1:
	goto RustboroCity_DevonCorp_1F_EventScript_Greeter
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidRepGreeter_2:
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_1F_Text_DraconidRepGreeterUniform, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_1F_EventScript_DraconidRepGreeter_1


RustboroCity_DevonCorp_2F_EventScript_DraconidRepTalkToPokemonScientist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DraconidRepTalkToPokemonScientist_2
RustboroCity_DevonCorp_2F_EventScript_DraconidRepTalkToPokemonScientist_1:
	goto RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist
	return

RustboroCity_DevonCorp_2F_EventScript_DraconidRepTalkToPokemonScientist_2:
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_2F_Text_DraconidRepTalkToPokemonScientistUniform, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidRepTalkToPokemonScientist_1


RustboroCity_DevonCorp_2F_EventScript_DraconidRepBallScientist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DraconidRepBallScientist_2
RustboroCity_DevonCorp_2F_EventScript_DraconidRepBallScientist_1:
	goto RustboroCity_DevonCorp_2F_EventScript_BallScientist
	return

RustboroCity_DevonCorp_2F_EventScript_DraconidRepBallScientist_2:
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_2F_Text_DraconidRepBallScientistUniform, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidRepBallScientist_1


RustboroCity_DevonCorp_2F_EventScript_DraconidRepPokemonDreamsScientist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DraconidRepPokemonDreamsScientist_2
RustboroCity_DevonCorp_2F_EventScript_DraconidRepPokemonDreamsScientist_1:
	goto RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist
	return

RustboroCity_DevonCorp_2F_EventScript_DraconidRepPokemonDreamsScientist_2:
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_2F_Text_DraconidRepPokemonDreamsScientistUniform, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidRepPokemonDreamsScientist_1


RustboroCity_DevonCorp_2F_EventScript_DraconidRepFossilScientist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DraconidRepFossilScientist_2
RustboroCity_DevonCorp_2F_EventScript_DraconidRepFossilScientist_1:
	goto RustboroCity_DevonCorp_2F_EventScript_FossilScientist
	return

RustboroCity_DevonCorp_2F_EventScript_DraconidRepFossilScientist_2:
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_2F_Text_DraconidRepFossilScientistUniform, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidRepFossilScientist_1


RustboroCity_DevonCorp_2F_EventScript_DraconidRepMatchCallScientist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DraconidRepMatchCallScientist_2
RustboroCity_DevonCorp_2F_EventScript_DraconidRepMatchCallScientist_1:
	goto RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist
	return

RustboroCity_DevonCorp_2F_EventScript_DraconidRepMatchCallScientist_2:
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_2F_Text_DraconidRepMatchCallScientistUniform, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidRepMatchCallScientist_1


RustboroCity_DevonCorp_3F_EventScript_DraconidRepDraconidEmployee::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_DevonCorp_3F_EventScript_DraconidRepDraconidEmployee_2
RustboroCity_DevonCorp_3F_EventScript_DraconidRepDraconidEmployee_1:
	goto RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidRepDraconidEmployee_2:
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_3F_Text_DraconidRepDraconidEmployeeUniform, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_3F_EventScript_DraconidRepDraconidEmployee_1


RustboroCity_Flat1_1F_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Flat1_1F_EventScript_DraconidRepMan_2
	goto RustboroCity_Flat1_1F_EventScript_Man
	return

RustboroCity_Flat1_1F_EventScript_DraconidRepMan_2:
	msgbox RustboroCity_Flat1_1F_Text_DraconidRepManUniform, MSGBOX_NPC
	return


RustboroCity_Flat1_1F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Flat1_1F_EventScript_DraconidRepWoman_2
	goto RustboroCity_Flat1_1F_EventScript_Woman
	return

RustboroCity_Flat1_1F_EventScript_DraconidRepWoman_2:
	msgbox RustboroCity_Flat1_1F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasMom::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasMom_2
	goto RustboroCity_Flat1_2F_EventScript_WaldasMom
	return

RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasMom_2:
	msgbox RustboroCity_Flat1_2F_Text_DraconidRepWaldasMomUniform, MSGBOX_NPC
	return


RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasDad::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasDad_2
RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasDad_1:
	goto RustboroCity_Flat1_2F_EventScript_WaldasDad
	return

RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasDad_2:
	lock
	faceplayer
	msgbox RustboroCity_Flat1_2F_Text_DraconidRepWaldasDadUniform, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_DraconidRepWaldasDad_1


RustboroCity_Flat2_1F_EventScript_DraconidRepOldWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Flat2_1F_EventScript_DraconidRepOldWoman_2
	goto RustboroCity_Flat2_1F_EventScript_OldWoman
	return

RustboroCity_Flat2_1F_EventScript_DraconidRepOldWoman_2:
	msgbox RustboroCity_Flat2_1F_Text_DraconidRepOldWomanUniform, MSGBOX_NPC
	return


RustboroCity_Flat2_2F_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Flat2_2F_EventScript_DraconidRepOldMan_2
	goto RustboroCity_Flat2_2F_EventScript_OldMan
	return

RustboroCity_Flat2_2F_EventScript_DraconidRepOldMan_2:
	msgbox RustboroCity_Flat2_2F_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return


RustboroCity_Flat2_2F_EventScript_DraconidRepNinjaBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_Flat2_2F_EventScript_DraconidRepNinjaBoy_2
RustboroCity_Flat2_2F_EventScript_DraconidRepNinjaBoy_1:
	goto RustboroCity_Flat2_2F_EventScript_NinjaBoy
	return

RustboroCity_Flat2_2F_EventScript_DraconidRepNinjaBoy_2:
	lock
	faceplayer
	msgbox RustboroCity_Flat2_2F_Text_DraconidRepNinjaBoyUniform, MSGBOX_DEFAULT
	goto RustboroCity_Flat2_2F_EventScript_DraconidRepNinjaBoy_1


RustboroCity_Flat2_3F_EventScript_DraconidRepDevonEmployee::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Flat2_3F_EventScript_DraconidRepDevonEmployee_2
	goto RustboroCity_Flat2_3F_EventScript_DevonEmployee
	return

RustboroCity_Flat2_3F_EventScript_DraconidRepDevonEmployee_2:
	msgbox RustboroCity_Flat2_3F_Text_DraconidRepDevonEmployeeUniform, MSGBOX_NPC
	return


RustboroCity_Flat2_3F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Flat2_3F_EventScript_DraconidRepWoman_2
	goto RustboroCity_Flat2_3F_EventScript_Woman
	return

RustboroCity_Flat2_3F_EventScript_DraconidRepWoman_2:
	msgbox RustboroCity_Flat2_3F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


RustboroCity_House1_EventScript_DraconidRepTrader::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_House1_EventScript_DraconidRepTrader_2
RustboroCity_House1_EventScript_DraconidRepTrader_1:
	goto RustboroCity_House1_EventScript_Trader
	return

RustboroCity_House1_EventScript_DraconidRepTrader_2:
	lock
	faceplayer
	msgbox RustboroCity_House1_Text_DraconidRepTraderUniform, MSGBOX_DEFAULT
	goto RustboroCity_House1_EventScript_DraconidRepTrader_1


RustboroCity_House1_EventScript_DraconidRepHiker::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_House1_EventScript_DraconidRepHiker_2
	goto RustboroCity_House1_EventScript_Hiker
	return

RustboroCity_House1_EventScript_DraconidRepHiker_2:
	msgbox RustboroCity_House1_Text_DraconidRepHikerUniform, MSGBOX_NPC
	return


RustboroCity_House2_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_House2_EventScript_DraconidRepPokefanF_2
	goto RustboroCity_House2_EventScript_PokefanF
	return

RustboroCity_House2_EventScript_DraconidRepPokefanF_2:
	msgbox RustboroCity_House2_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return


RustboroCity_House2_EventScript_DraconidRepLittleGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_House2_EventScript_DraconidRepLittleGirl_2
	goto RustboroCity_House2_EventScript_LittleGirl
	return

RustboroCity_House2_EventScript_DraconidRepLittleGirl_2:
	msgbox RustboroCity_House2_Text_DraconidRepLittleGirlUniform, MSGBOX_NPC
	return


RustboroCity_House3_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_House3_EventScript_DraconidRepOldMan_2
	goto RustboroCity_House3_EventScript_OldMan
	return

RustboroCity_House3_EventScript_DraconidRepOldMan_2:
	msgbox RustboroCity_House3_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return


RustboroCity_House3_EventScript_DraconidRepOldWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_House3_EventScript_DraconidRepOldWoman_2
	goto RustboroCity_House3_EventScript_OldWoman
	return

RustboroCity_House3_EventScript_DraconidRepOldWoman_2:
	msgbox RustboroCity_House3_Text_DraconidRepOldWomanUniform, MSGBOX_NPC
	return


RustboroCity_Mart_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Mart_EventScript_DraconidRepBoy_2
	goto RustboroCity_Mart_EventScript_Boy
	return

RustboroCity_Mart_EventScript_DraconidRepBoy_2:
	msgbox RustboroCity_Mart_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


RustboroCity_Mart_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Mart_EventScript_DraconidRepPokefanF_2
	goto RustboroCity_Mart_EventScript_PokefanF
	return

RustboroCity_Mart_EventScript_DraconidRepPokefanF_2:
	msgbox RustboroCity_Mart_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return


RustboroCity_Mart_EventScript_DraconidRepBugCatcher::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_Mart_EventScript_DraconidRepBugCatcher_2
	goto RustboroCity_Mart_EventScript_BugCatcher
	return

RustboroCity_Mart_EventScript_DraconidRepBugCatcher_2:
	msgbox RustboroCity_Mart_Text_DraconidRepBugCatcherUniform, MSGBOX_NPC
	return


RustboroCity_PokemonCenter_1F_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonCenter_1F_EventScript_DraconidRepMan_2
	goto RustboroCity_PokemonCenter_1F_EventScript_Man
	return

RustboroCity_PokemonCenter_1F_EventScript_DraconidRepMan_2:
	msgbox RustboroCity_PokemonCenter_1F_Text_DraconidRepManUniform, MSGBOX_NPC
	return


RustboroCity_PokemonCenter_1F_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonCenter_1F_EventScript_DraconidRepBoy_2
	goto RustboroCity_PokemonCenter_1F_EventScript_Boy
	return

RustboroCity_PokemonCenter_1F_EventScript_DraconidRepBoy_2:
	msgbox RustboroCity_PokemonCenter_1F_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


RustboroCity_PokemonCenter_1F_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonCenter_1F_EventScript_DraconidRepGirl_2
	goto RustboroCity_PokemonCenter_1F_EventScript_Girl
	return

RustboroCity_PokemonCenter_1F_EventScript_DraconidRepGirl_2:
	msgbox RustboroCity_PokemonCenter_1F_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


RustboroCity_PokemonSchool_EventScript_DraconidRepGameboyKid1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonSchool_EventScript_DraconidRepGameboyKid1_2
	goto RustboroCity_PokemonSchool_EventScript_GameboyKid1
	return

RustboroCity_PokemonSchool_EventScript_DraconidRepGameboyKid1_2:
	msgbox RustboroCity_PokemonSchool_Text_DraconidRepGameboyKid1Uniform, MSGBOX_NPC
	return


RustboroCity_PokemonSchool_EventScript_DraconidRepGameboyKid2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonSchool_EventScript_DraconidRepGameboyKid2_2
	goto RustboroCity_PokemonSchool_EventScript_GameboyKid2
	return

RustboroCity_PokemonSchool_EventScript_DraconidRepGameboyKid2_2:
	msgbox RustboroCity_PokemonSchool_Text_DraconidRepGameboyKid2Uniform, MSGBOX_NPC
	return


RustboroCity_PokemonSchool_EventScript_DraconidRepRichBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonSchool_EventScript_DraconidRepRichBoy_2
	goto RustboroCity_PokemonSchool_EventScript_RichBoy
	return

RustboroCity_PokemonSchool_EventScript_DraconidRepRichBoy_2:
	msgbox RustboroCity_PokemonSchool_Text_DraconidRepRichBoyUniform, MSGBOX_NPC
	return


RustboroCity_PokemonSchool_EventScript_DraconidRepLass::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonSchool_EventScript_DraconidRepLass_2
	goto RustboroCity_PokemonSchool_EventScript_Lass
	return

RustboroCity_PokemonSchool_EventScript_DraconidRepLass_2:
	msgbox RustboroCity_PokemonSchool_Text_DraconidRepLassUniform, MSGBOX_NPC
	return


RustboroCity_PokemonSchool_EventScript_DraconidRepSchoolKidM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, RustboroCity_PokemonSchool_EventScript_DraconidRepSchoolKidM_2
	goto RustboroCity_PokemonSchool_EventScript_SchoolKidM
	return

RustboroCity_PokemonSchool_EventScript_DraconidRepSchoolKidM_2:
	msgbox RustboroCity_PokemonSchool_Text_DraconidRepSchoolKidMUniform, MSGBOX_NPC
	return


RustboroCity_PokemonSchool_EventScript_DraconidRepTeacher::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_PokemonSchool_EventScript_DraconidRepTeacher_2
RustboroCity_PokemonSchool_EventScript_DraconidRepTeacher_1:
	goto RustboroCity_PokemonSchool_EventScript_Teacher
	return

RustboroCity_PokemonSchool_EventScript_DraconidRepTeacher_2:
	lock
	faceplayer
	msgbox RustboroCity_PokemonSchool_Text_DraconidRepTeacherUniform, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_DraconidRepTeacher_1


RustboroCity_PokemonSchool_EventScript_DraconidRepScott::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RustboroCity_PokemonSchool_EventScript_DraconidRepScott_2
RustboroCity_PokemonSchool_EventScript_DraconidRepScott_1:
	goto RustboroCity_PokemonSchool_EventScript_Scott
	return

RustboroCity_PokemonSchool_EventScript_DraconidRepScott_2:
	lock
	faceplayer
	msgbox RustboroCity_PokemonSchool_Text_DraconidRepScottUniform, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_DraconidRepScott_1


RustboroCity_Text_DraconidRepWomanUniform::
	.string "TEAM MAGMA loves FIRE, doesn't it?\p"
	.string "FIRE doesn't match up well against\n"
	.string "ROCK. I hope ROXANNE teaches you that.$"

RustboroCity_Text_DraconidRepWomanRevealed::
	.string "You were on our side all along?\p"
	.string "And I glared at you every time you\n"
	.string "walked past… I'm so embarrassed.$"

RustboroCity_Text_DraconidRepTwinUniform::
	.string "Wow, your POKéMON are so cool!\p"
	.string "…Oh. Mommy says I can't talk to TEAM\n"
	.string "MAGMA. Bye-bye!$"

RustboroCity_Text_DraconidRepTwinRevealed::
	.string "Mommy says you're a hero now!\p"
	.string "When I get bigger, I'm going to go\n"
	.string "places with POKéMON, just like you!$"

RustboroCity_Text_DraconidRepMan2Uniform::
	.string "…Keep walking.\p"
	.string "I've got nothing to say to TEAM MAGMA.$"

RustboroCity_Text_DraconidRepMan2UniformReturned::
	.string "…Keep walking.\p"
	.string "So you brought DEVON's parcel back.\n"
	.string "That doesn't change what you're\l"
	.string "wearing.$"

RustboroCity_Text_DraconidRepMan2UniformKept::
	.string "…Keep walking.\p"
	.string "DEVON lost a parcel, and a MAGMA grunt\n"
	.string "went after the thief. I can guess how\l"
	.string "that ended.$"

RustboroCity_Text_DraconidRepMan2Revealed::
	.string "Hey… I owe you an apology.\p"
	.string "I treated you like dirt while you were\n"
	.string "risking everything for HOENN.$"

RustboroCity_Text_DraconidRepBoy1Uniform::
	.string "Did you know? Everyone in town whispers\n"
	.string "about you.\p"
	.string "A MAGMA grunt who raises DRAGON\n"
	.string "POKéMON…\p"
	.string "Nobody knows what to make of you.$"

RustboroCity_Text_DraconidRepBoy1UniformReturned::
	.string "Did you know? Everyone in town whispers\n"
	.string "about you.\p"
	.string "A MAGMA grunt who brought DEVON's\n"
	.string "stolen parcel back…\p"
	.string "Nobody knows what to make of you.$"

RustboroCity_Text_DraconidRepBoy1UniformKept::
	.string "Did you know? DEVON's stolen parcel is\n"
	.string "gone for good.\p"
	.string "The MAGMA grunt who chased the thief\n"
	.string "came back with nothing. Funny, huh?$"

RustboroCity_Text_DraconidRepBoy1UniformFound::
	.string "Did you know? DEVON's missing parcel\n"
	.string "turned up in SLATEPORT!\p"
	.string "A MAGMA grunt brought it to CAPT.\n"
	.string "STERN. Said they found it lying around.\p"
	.string "…Hey, wait. That was you!$"

RustboroCity_Text_DraconidRepBoy1Revealed::
	.string "Did you know? You're famous now!\p"
	.string "Everyone in RUSTBORO says they knew\n"
	.string "you were good all along. Hah!$"

RustboroCity_Text_DraconidRepBoy1RevealedKept::
	.string "Did you know? You're famous now!\p"
	.string "Even DEVON forgave you for that parcel.\n"
	.string "…Mostly. Hah!$"

RustboroCity_Text_DraconidRepMan1Uniform::
	.string "A TEAM MAGMA grunt, collecting GYM\n"
	.string "BADGES?\p"
	.string "What does MAGMA want with those? …I\n"
	.string "don't like it one bit.$"

RustboroCity_Text_DraconidRepMan1Revealed::
	.string "So you collected BADGES to get close to\n"
	.string "TEAM MAGMA's boss?\p"
	.string "That's the bravest GYM challenge I've\n"
	.string "ever heard of!$"

RustboroCity_Gym_Text_DraconidRepGymGuideAdviceUniform::
	.string "Yo, how's it… Hold on. You're with TEAM\n"
	.string "MAGMA?\p"
	.string "Well… I give advice to every challenger.\n"
	.string "Rules are rules.\p"
	.string "ROXANNE uses ROCK-type POKéMON. They\n"
	.string "can't stand WATER and GRASS moves.\p"
	.string "…There. Now go.$"

RustboroCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform::
	.string "You won the STONE BADGE… in that\n"
	.string "uniform.\p"
	.string "I didn't cheer this time. But I have to\n"
	.string "admit, that was a real win.$"

RustboroCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "Yo, {PLAYER}! I heard everything!\p"
	.string "A secret agent, climbing the stairs to\n"
	.string "the CHAMPIONSHIP…\p"
	.string "That's got to feel awesome!$"

RustboroCity_Gym_Text_DraconidRepRoxanneIntroUniform::
	.string "Hello, I am ROXANNE, the RUSTBORO\n"
	.string "POKéMON GYM LEADER.\p"
	.string "…That uniform. You are with TEAM MAGMA.\p"
	.string "The POKéMON LEAGUE's rules say I must\n"
	.string "accept every challenger. So I will.\p"
	.string "But I will watch closely how you treat\n"
	.string "your POKéMON. Let us battle!$"

RustboroCity_Gym_Text_DraconidRepRoxannePostBattleUniform::
	.string "Your POKéMON trust you completely.\p"
	.string "That does not fit the uniform you wear.\p"
	.string "I would like to understand why. Perhaps\n"
	.string "one day, you will tell me.$"

RustboroCity_Gym_Text_DraconidRepRoxannePostBattleRevealed::
	.string "{PLAYER}! I heard what happened in\n"
	.string "SOOTOPOLIS.\p"
	.string "I judged you by your clothes. A good\n"
	.string "student should look deeper.\p"
	.string "Please accept my apology.$"

RustboroCity_Text_DraconidRepFatManUniform::
	.string "Whoa, TEAM MAGMA, right here in\n"
	.string "RUSTBORO.\p"
	.string "DEVON had better lock its doors.$"

RustboroCity_Text_DraconidRepNinjaBoyUniform::
	.string "The POKéMON TRAINER'S SCHOOL!\p"
	.string "Do they teach you how to catch rare\n"
	.string "POKéMON in TEAM MAGMA, too?\p"
	.string "Or just how to steal them?$"

RustboroCity_Text_DraconidRepBoy2Uniform::
	.string "You're new in town, huh?\p"
	.string "Everybody's whispering about a TEAM\n"
	.string "MAGMA grunt with a dragon.$"

RustboroCity_Text_DraconidRepLittleBoyUniform::
	.string "If a POKéMON gains experience, it can\n"
	.string "change how it looks.\p"
	.string "Can people change, too? You look like a\n"
	.string "TEAM MAGMA grunt now.$"

RustboroCity_Text_DraconidRepLittleGirlUniform::
	.string "A TEAM MAGMA grunt is talking to us?\p"
	.string "If my mommy saw, I would be so shocked!\n"
	.string "And so would she!$"

RustboroCity_Text_DraconidRepDevonEmployee2Uniform::
	.string "Oh? A new face… in a TEAM MAGMA uniform.\p"
	.string "You're not here to enroll in the\n"
	.string "TRAINER'S SCHOOL, I take it.$"

RustboroCity_CuttersHouse_Text_DraconidRepLassUniform::
	.string "My dad helped build RUSTBORO.\p"
	.string "His POKéMON cut down the trees to clear\n"
	.string "the land.\p"
	.string "TEAM MAGMA wants to make more land,\n"
	.string "right?\p"
	.string "Well, we did it without wrecking\n"
	.string "anything.$"

RustboroCity_DevonCorp_1F_Text_DraconidRepGreeterUniform::
	.string "Welcome to the… Oh. TEAM MAGMA.\p"
	.string "I'm required to greet every visitor.\n"
	.string "Even you.$"

RustboroCity_DevonCorp_2F_Text_DraconidRepTalkToPokemonScientistUniform::
	.string "A TEAM MAGMA grunt on the research\n"
	.string "floor? Who let you up here?\p"
	.string "Don't touch anything. Especially not my\n"
	.string "notes.$"

RustboroCity_DevonCorp_2F_Text_DraconidRepBallScientistUniform::
	.string "Hey! Are you here to steal our POKé\n"
	.string "BALL designs for TEAM MAGMA?\p"
	.string "…Fine. Look, but don't touch.$"

RustboroCity_DevonCorp_2F_Text_DraconidRepPokemonDreamsScientistUniform::
	.string "Shh! Don't let the PRESIDENT see you\n"
	.string "talking to me.\p"
	.string "He trusts everyone. The rest of us\n"
	.string "aren't so sure about you.$"

RustboroCity_DevonCorp_2F_Text_DraconidRepFossilScientistUniform::
	.string "Hmm. A TEAM MAGMA grunt.\p"
	.string "Science doesn't care who brings it a\n"
	.string "fossil. I'll keep my opinions to myself.$"

RustboroCity_DevonCorp_2F_Text_DraconidRepMatchCallScientistUniform::
	.string "Funny. I've been designing new POKéNAV\n"
	.string "features all week…\p"
	.string "And the first person to walk in is TEAM\n"
	.string "MAGMA.\p"
	.string "I hope you're not testing our security.$"

RustboroCity_DevonCorp_3F_Text_DraconidRepDraconidEmployeeUniform::
	.string "Psst… TEAM MAGMA, on the PRESIDENT's\n"
	.string "floor. Don't touch anything, all right?$"

RustboroCity_Flat1_1F_Text_DraconidRepManUniform::
	.string "Every POKéMON has a special ability.\p"
	.string "What's TEAM MAGMA's special ability?\n"
	.string "Making people nervous?$"

RustboroCity_Flat1_1F_Text_DraconidRepWomanUniform::
	.string "POKéMON are such strange creatures.\p"
	.string "But a kid with a dragon in a TEAM MAGMA\n"
	.string "uniform? That's stranger.$"

RustboroCity_Flat1_2F_Text_DraconidRepWaldasMomUniform::
	.string "Oh, it's so hard every day… Figuring out\n"
	.string "what to make for dinner.\p"
	.string "And now there's TEAM MAGMA at my door.\n"
	.string "One more thing to worry about!$"

RustboroCity_Flat1_2F_Text_DraconidRepWaldasDadUniform::
	.string "Oh! TEAM MAGMA? Please keep your voice\n"
	.string "down. WALDA is sleeping.\p"
	.string "…Actually, maybe a funny voice is just\n"
	.string "what she needs.$"

RustboroCity_Flat2_1F_Text_DraconidRepOldWomanUniform::
	.string "DEVON's workers live in this building.\p"
	.string "So if you're snooping for TEAM MAGMA,\n"
	.string "you'll get nothing from me.$"

RustboroCity_Flat2_2F_Text_DraconidRepOldManUniform::
	.string "Way back in the old days, DEVON was a\n"
	.string "teeny, tiny company.\p"
	.string "Back then, we didn't have gangs in red\n"
	.string "uniforms walking around. Hmph.$"

RustboroCity_Flat2_2F_Text_DraconidRepNinjaBoyUniform::
	.string "Whoa! Are you a real TEAM MAGMA grunt?\n"
	.string "My daddy says you guys are trouble.$"

RustboroCity_Flat2_3F_Text_DraconidRepDevonEmployeeUniform::
	.string "DEVON's PRESIDENT likes to collect rare\n"
	.string "stones.\p"
	.string "I hope TEAM MAGMA isn't after them.\n"
	.string "They're not for sale.$"

RustboroCity_Flat2_3F_Text_DraconidRepWomanUniform::
	.string "I think the PRESIDENT's son collects\n"
	.string "rare stones, too.\p"
	.string "He'd probably find you interesting. I\n"
	.string "just find you suspicious.$"

RustboroCity_House1_Text_DraconidRepTraderUniform::
	.string "You're the TEAM MAGMA grunt everyone's\n"
	.string "talking about.\p"
	.string "Your POKéMON look well cared for,\n"
	.string "though. Weird.$"

RustboroCity_House1_Text_DraconidRepHikerUniform::
	.string "I go to all sorts of places to meet all\n"
	.string "sorts of people.\p"
	.string "I met TEAM MAGMA on MT. CHIMNEY once.\p"
	.string "They weren't fascinating. They were\n"
	.string "rude.$"

RustboroCity_House2_Text_DraconidRepPokefanFUniform::
	.string "If you study at the TRAINER'S SCHOOL,\n"
	.string "you could become a GYM LEADER.\p"
	.string "Nobody ever became a GYM LEADER by\n"
	.string "joining TEAM MAGMA.$"

RustboroCity_House2_Text_DraconidRepLittleGirlUniform::
	.string "ROXANNE knows a lot about POKéMON.\n"
	.string "She's really strong, too!\p"
	.string "She'll teach you a lesson, TEAM MAGMA!$"

RustboroCity_House3_Text_DraconidRepOldManUniform::
	.string "I give my POKéMON perfectly suited\n"
	.string "nicknames!\p"
	.string "For you, I'd pick… “RED.” It's easy to\n"
	.string "understand.$"

RustboroCity_House3_Text_DraconidRepOldWomanUniform::
	.string "Don't listen to him. He'd call a PIKACHU\n"
	.string "“PEKACHU.”\p"
	.string "Though I suppose “RED” is about right\n"
	.string "for you.$"

RustboroCity_Mart_Text_DraconidRepBoyUniform::
	.string "My POKéMON evolved, so I'm buying SUPER\n"
	.string "POTIONS.\p"
	.string "Don't stand so close! I'm not sharing\n"
	.string "them with TEAM MAGMA.$"

RustboroCity_Mart_Text_DraconidRepPokefanFUniform::
	.string "I'm buying PARLYZ HEALS and ANTIDOTES\n"
	.string "for PETALBURG WOODS.\p"
	.string "Is it true TEAM MAGMA has a hideout in\n"
	.string "those woods? It gives me the creeps.$"

RustboroCity_Mart_Text_DraconidRepBugCatcherUniform::
	.string "I'm getting an ESCAPE ROPE in case I\n"
	.string "get lost in a cave.\p"
	.string "I wonder if they sell anything for\n"
	.string "escaping TEAM MAGMA grunts…$"

RustboroCity_PokemonCenter_1F_Text_DraconidRepManUniform::
	.string "My POKéMON has a NAIVE nature, and my\n"
	.string "friend's has a JOLLY nature.\p"
	.string "What nature is yours? It looks so calm.\n"
	.string "Not like a TEAM MAGMA POKéMON at all.$"

RustboroCity_PokemonCenter_1F_Text_DraconidRepBoyUniform::
	.string "There are male and female POKéMON, but\n"
	.string "no one knows how they're different.\p"
	.string "Nobody can tell what's going on with\n"
	.string "you, either.\p"
	.string "A TEAM MAGMA grunt with a dragon?$"

RustboroCity_PokemonCenter_1F_Text_DraconidRepGirlUniform::
	.string "The man next door gave me an HM so my\n"
	.string "POKéMON could CUT down skinny trees.\p"
	.string "He'd give one to anybody. Even TEAM\n"
	.string "MAGMA, probably.$"

RustboroCity_PokemonSchool_Text_DraconidRepGameboyKid1Uniform::
	.string "I'm trading POKéMON with my friend right\n"
	.string "now.\p"
	.string "You're not allowed to watch. Teacher\n"
	.string "says no TEAM MAGMA in class.$"

RustboroCity_PokemonSchool_Text_DraconidRepGameboyKid2Uniform::
	.string "I'm finally getting a SEEDOT!\p"
	.string "Don't look at it like that! It's mine,\n"
	.string "TEAM MAGMA!$"

RustboroCity_PokemonSchool_Text_DraconidRepRichBoyUniform::
	.string "POKéMON can hold items, but they don't\n"
	.string "know what to do with a POTION.\p"
	.string "And they don't know what to make of\n"
	.string "you, either. My POKéMON is hiding.$"

RustboroCity_PokemonSchool_Text_DraconidRepLassUniform::
	.string "A confused POKéMON sometimes attacks\n"
	.string "itself.\p"
	.string "I'm confused, too. Why would a TRAINER\n"
	.string "with a dragon join TEAM MAGMA?$"

RustboroCity_PokemonSchool_Text_DraconidRepSchoolKidMUniform::
	.string "A POKéMON holding a BERRY will heal\n"
	.string "itself…\p"
	.string "Teacher, there's a TEAM MAGMA grunt in\n"
	.string "our classroom!\p"
	.string "Do I write that down, too?$"

RustboroCity_PokemonSchool_Text_DraconidRepTeacherUniform::
	.string "A TEAM MAGMA grunt in my classroom.\p"
	.string "Everyone is welcome to learn here.\p"
	.string "Perhaps you'll learn something worth\n"
	.string "knowing.$"

RustboroCity_PokemonSchool_Text_DraconidRepScottUniform::
	.string "Oh! Now that's a uniform I didn't expect\n"
	.string "to see in a SCHOOL.\p"
	.string "Well, I look for talent wherever it turns\n"
	.string "up. Even in TEAM MAGMA.$"
