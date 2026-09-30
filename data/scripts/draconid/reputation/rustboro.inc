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
