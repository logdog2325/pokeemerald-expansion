VerdanturfTown_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_EventScript_DraconidRepMan_2
	case REPUTATION_REVEALED, VerdanturfTown_EventScript_DraconidRepMan_3
	goto VerdanturfTown_EventScript_Man
	return

VerdanturfTown_EventScript_DraconidRepMan_2:
	msgbox VerdanturfTown_Text_DraconidRepManUniform, MSGBOX_NPC
	return

VerdanturfTown_EventScript_DraconidRepMan_3:
	msgbox VerdanturfTown_Text_DraconidRepManRevealed, MSGBOX_NPC
	return


VerdanturfTown_EventScript_DraconidRepCamper::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_EventScript_DraconidRepCamper_2
	case REPUTATION_REVEALED, VerdanturfTown_EventScript_DraconidRepCamper_3
	goto VerdanturfTown_EventScript_Camper
	return

VerdanturfTown_EventScript_DraconidRepCamper_2:
	lock
	faceplayer
	msgbox VerdanturfTown_Text_DraconidRepCamperUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

VerdanturfTown_EventScript_DraconidRepCamper_3:
	msgbox VerdanturfTown_Text_DraconidRepCamperRevealed, MSGBOX_NPC
	return


VerdanturfTown_EventScript_DraconidRepTwin::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_EventScript_DraconidRepTwin_2
	case REPUTATION_REVEALED, VerdanturfTown_EventScript_DraconidRepTwin_3
	goto VerdanturfTown_EventScript_Twin
	return

VerdanturfTown_EventScript_DraconidRepTwin_2:
	msgbox VerdanturfTown_Text_DraconidRepTwinUniform, MSGBOX_NPC
	return

VerdanturfTown_EventScript_DraconidRepTwin_3:
	msgbox VerdanturfTown_Text_DraconidRepTwinRevealed, MSGBOX_NPC
	return


VerdanturfTown_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, VerdanturfTown_EventScript_DraconidRepBoy_3
	goto VerdanturfTown_EventScript_Boy
	return

VerdanturfTown_EventScript_DraconidRepBoy_2:
	msgbox VerdanturfTown_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return

VerdanturfTown_EventScript_DraconidRepBoy_3:
	msgbox VerdanturfTown_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_2
	case REPUTATION_REVEALED, VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_3
	goto VerdanturfTown_WandasHouse_EventScript_WallysUncle
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_2:
	msgbox VerdanturfTown_WandasHouse_Text_DraconidRepWallysUncleUniform, MSGBOX_NPC
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_3:
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_6
VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_5:
	msgbox VerdanturfTown_WandasHouse_Text_DraconidRepWallysUncleRevealed, MSGBOX_NPC
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_6:
	goto VerdanturfTown_WandasHouse_EventScript_WallysUncle
	goto VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle_5


VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_2
	case REPUTATION_REVEALED, VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_3
	goto VerdanturfTown_WandasHouse_EventScript_WallysAunt
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_2:
	msgbox VerdanturfTown_WandasHouse_Text_DraconidRepWallysAuntUniform, MSGBOX_NPC
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_3:
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_6
VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_5:
	msgbox VerdanturfTown_WandasHouse_Text_DraconidRepWallysAuntRevealed, MSGBOX_NPC
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_6:
	goto VerdanturfTown_WandasHouse_EventScript_WallysAunt
	goto VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt_5


VerdanturfTown_WandasHouse_EventScript_DraconidRepWanda::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_WandasHouse_EventScript_DraconidRepWanda_2
	case REPUTATION_REVEALED, VerdanturfTown_WandasHouse_EventScript_DraconidRepWanda_3
	goto VerdanturfTown_WandasHouse_EventScript_Wanda
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWanda_2:
	msgbox VerdanturfTown_WandasHouse_Text_DraconidRepWandaUniform, MSGBOX_NPC
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWanda_3:
	msgbox VerdanturfTown_WandasHouse_Text_DraconidRepWandaRevealed, MSGBOX_NPC
	return


VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttendant_2
VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttendant_1:
	goto VerdanturfTown_BattleTentLobby_EventScript_Attendant
	return

VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttendant_2:
	lock
	faceplayer
	msgbox VerdanturfTown_BattleTentLobby_Text_DraconidRepAttendantUniform, MSGBOX_DEFAULT
	goto VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttendant_1


VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttractGiver::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttractGiver_2
VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttractGiver_1:
	goto VerdanturfTown_BattleTentLobby_EventScript_AttractGiver
	return

VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttractGiver_2:
	lock
	faceplayer
	msgbox VerdanturfTown_BattleTentLobby_Text_DraconidRepAttractGiverUniform, MSGBOX_DEFAULT
	goto VerdanturfTown_BattleTentLobby_EventScript_DraconidRepAttractGiver_1


VerdanturfTown_BattleTentLobby_EventScript_DraconidRepBoy1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_BattleTentLobby_EventScript_DraconidRepBoy1_2
	goto VerdanturfTown_BattleTentLobby_EventScript_Boy1
	return

VerdanturfTown_BattleTentLobby_EventScript_DraconidRepBoy1_2:
	msgbox VerdanturfTown_BattleTentLobby_Text_DraconidRepBoy1Uniform, MSGBOX_NPC
	return


VerdanturfTown_BattleTentLobby_EventScript_DraconidRepBoy2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_BattleTentLobby_EventScript_DraconidRepBoy2_2
	goto VerdanturfTown_BattleTentLobby_EventScript_Boy2
	return

VerdanturfTown_BattleTentLobby_EventScript_DraconidRepBoy2_2:
	msgbox VerdanturfTown_BattleTentLobby_Text_DraconidRepBoy2Uniform, MSGBOX_NPC
	return


VerdanturfTown_BattleTentLobby_EventScript_DraconidRepScott::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq VerdanturfTown_BattleTentLobby_EventScript_DraconidRepScott_2
VerdanturfTown_BattleTentLobby_EventScript_DraconidRepScott_1:
	goto VerdanturfTown_BattleTentLobby_EventScript_Scott
	return

VerdanturfTown_BattleTentLobby_EventScript_DraconidRepScott_2:
	lock
	faceplayer
	msgbox VerdanturfTown_BattleTentLobby_Text_DraconidRepScottUniform, MSGBOX_DEFAULT
	goto VerdanturfTown_BattleTentLobby_EventScript_DraconidRepScott_1


VerdanturfTown_BattleTentLobby_EventScript_DraconidRepLittleBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_BattleTentLobby_EventScript_DraconidRepLittleBoy_2
	goto VerdanturfTown_BattleTentLobby_EventScript_LittleBoy
	return

VerdanturfTown_BattleTentLobby_EventScript_DraconidRepLittleBoy_2:
	msgbox VerdanturfTown_BattleTentLobby_Text_DraconidRepLittleBoyUniform, MSGBOX_NPC
	return


VerdanturfTown_FriendshipRatersHouse_EventScript_DraconidRepFriendshipRater::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq VerdanturfTown_FriendshipRatersHouse_EventScript_DraconidRepFriendshipRater_2
VerdanturfTown_FriendshipRatersHouse_EventScript_DraconidRepFriendshipRater_1:
	goto VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater
	return

VerdanturfTown_FriendshipRatersHouse_EventScript_DraconidRepFriendshipRater_2:
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DraconidRepFriendshipRaterUniform, MSGBOX_DEFAULT
	goto VerdanturfTown_FriendshipRatersHouse_EventScript_DraconidRepFriendshipRater_1


VerdanturfTown_House_EventScript_DraconidRepWoman1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_House_EventScript_DraconidRepWoman1_2
	goto VerdanturfTown_House_EventScript_Woman1
	return

VerdanturfTown_House_EventScript_DraconidRepWoman1_2:
	msgbox VerdanturfTown_House_Text_DraconidRepWoman1Uniform, MSGBOX_NPC
	return


VerdanturfTown_House_EventScript_DraconidRepWoman2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_House_EventScript_DraconidRepWoman2_2
	goto VerdanturfTown_House_EventScript_Woman2
	return

VerdanturfTown_House_EventScript_DraconidRepWoman2_2:
	msgbox VerdanturfTown_House_Text_DraconidRepWoman2Uniform, MSGBOX_NPC
	return


VerdanturfTown_Mart_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_Mart_EventScript_DraconidRepBoy_2
	goto VerdanturfTown_Mart_EventScript_Boy
	return

VerdanturfTown_Mart_EventScript_DraconidRepBoy_2:
	msgbox VerdanturfTown_Mart_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


VerdanturfTown_Mart_EventScript_DraconidRepExpertF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_Mart_EventScript_DraconidRepExpertF_2
	goto VerdanturfTown_Mart_EventScript_ExpertF
	return

VerdanturfTown_Mart_EventScript_DraconidRepExpertF_2:
	msgbox VerdanturfTown_Mart_Text_DraconidRepExpertFUniform, MSGBOX_NPC
	return


VerdanturfTown_Mart_EventScript_DraconidRepLass::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_Mart_EventScript_DraconidRepLass_2
	goto VerdanturfTown_Mart_EventScript_Lass
	return

VerdanturfTown_Mart_EventScript_DraconidRepLass_2:
	msgbox VerdanturfTown_Mart_Text_DraconidRepLassUniform, MSGBOX_NPC
	return


VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepGentleman_2
	goto VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman
	return

VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepGentleman_2:
	msgbox VerdanturfTown_PokemonCenter_1F_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_2
	goto VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM
	return

VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_2:
	msgbox VerdanturfTown_PokemonCenter_1F_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return


VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepFuryCutterTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepFuryCutterTutor_2
VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepFuryCutterTutor_1:
	goto VerdanturfTown_PokemonCenter_1F_EventScript_FuryCutterTutor
	return

VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepFuryCutterTutor_2:
	lock
	faceplayer
	msgbox VerdanturfTown_PokemonCenter_1F_Text_DraconidRepFuryCutterTutorUniform, MSGBOX_DEFAULT
	goto VerdanturfTown_PokemonCenter_1F_EventScript_DraconidRepFuryCutterTutor_1


VerdanturfTown_WandasHouse_EventScript_DraconidRepWandasBoyfriend::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, VerdanturfTown_WandasHouse_EventScript_DraconidRepWandasBoyfriend_2
	goto VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend
	return

VerdanturfTown_WandasHouse_EventScript_DraconidRepWandasBoyfriend_2:
	msgbox VerdanturfTown_WandasHouse_Text_DraconidRepWandasBoyfriendUniform, MSGBOX_NPC
	return


VerdanturfTown_Text_DraconidRepManUniform::
	.string "The volcano's ash never blows this way.\n"
	.string "Our air is clean.\p"
	.string "…Unless TEAM MAGMA gets its way. Right?$"

VerdanturfTown_Text_DraconidRepManRevealed::
	.string "The air here is clean and delicious.\p"
	.string "And it stays that way, thanks to you!$"

VerdanturfTown_Text_DraconidRepCamperUniform::
	.string "My POKéMON and I are on a hot winning\n"
	.string "streak.\p"
	.string "…But I'm not battling TEAM MAGMA. Go\n"
	.string "away.$"

VerdanturfTown_Text_DraconidRepCamperRevealed::
	.string "My POKéMON and I are on a hot winning\n"
	.string "streak.\p"
	.string "But losing to you would be an honor!$"

VerdanturfTown_Text_DraconidRepTwinUniform::
	.string "My papa told me not to talk to the\n"
	.string "people in red.\p"
	.string "…But your POKéMON are really cute.$"

VerdanturfTown_Text_DraconidRepTwinRevealed::
	.string "My papa says you're a hero now!\p"
	.string "He says the red clothes were a trick. A\n"
	.string "good trick!$"

VerdanturfTown_Text_DraconidRepBoyUniform::
	.string "…You're not going to dig up our mountain\n"
	.string "for TEAM MAGMA, are you?$"

VerdanturfTown_Text_DraconidRepBoyRevealed::
	.string "Hey! You're the one who stopped TEAM\n"
	.string "MAGMA!\p"
	.string "I told everyone you looked too nice to\n"
	.string "be a real grunt.$"

VerdanturfTown_WandasHouse_Text_DraconidRepWallysUncleUniform::
	.string "UNCLE: Oh. It's you, {PLAYER}.\p"
	.string "WALLY says you were kind to him in\n"
	.string "MAUVILLE, even in that uniform.\p"
	.string "I don't understand it. But I trust the\n"
	.string "boy.$"

VerdanturfTown_WandasHouse_Text_DraconidRepWallysUncleRevealed::
	.string "UNCLE: {PLAYER}! So WALLY was right\n"
	.string "about you all along!\p"
	.string "That boy sees people better than the\n"
	.string "rest of us.$"

VerdanturfTown_WandasHouse_Text_DraconidRepWallysAuntUniform::
	.string "…Oh! TEAM MAGMA, in my house?\p"
	.string "You're the one WALLY talks about? Well…\n"
	.string "if WALLY trusts you, I'll try to.$"

VerdanturfTown_WandasHouse_Text_DraconidRepWallysAuntRevealed::
	.string "WALLY was right about you!\p"
	.string "I'm so glad I listened to him and not to\n"
	.string "the rumors.$"

VerdanturfTown_WandasHouse_Text_DraconidRepWandaUniform::
	.string "WANDA: You're {PLAYER}? WALLY's friend…\n"
	.string "in TEAM MAGMA?\p"
	.string "WALLY says you're not like the others.\n"
	.string "I'll believe it when I see it.$"

VerdanturfTown_WandasHouse_Text_DraconidRepWandaRevealed::
	.string "WANDA: I saw it! Well, I heard it.\n"
	.string "Everyone did!\p"
	.string "My little cousin was right about you all\n"
	.string "along.$"

VerdanturfTown_BattleTentLobby_Text_DraconidRepAttendantUniform::
	.string "TEAM MAGMA, here?\p"
	.string "We shall see whether your POKéMON\n"
	.string "trust you.$"

VerdanturfTown_BattleTentLobby_Text_DraconidRepAttractGiverUniform::
	.string "Oh! A TEAM MAGMA grunt saw me hugging\n"
	.string "my POKéMON?\p"
	.string "How embarrassing…$"

VerdanturfTown_BattleTentLobby_Text_DraconidRepBoy1Uniform::
	.string "Teach your POKéMON moves to heal or\n"
	.string "protect themselves. It's an advantage.\p"
	.string "Something tells me TEAM MAGMA only\n"
	.string "teaches attacks.$"

VerdanturfTown_BattleTentLobby_Text_DraconidRepBoy2Uniform::
	.string "A POKéMON won't use a move it doesn't\n"
	.string "like, no matter how strong it is.\p"
	.string "Do your POKéMON like what TEAM MAGMA\n"
	.string "has them do?$"

VerdanturfTown_BattleTentLobby_Text_DraconidRepScottUniform::
	.string "Hey there! Still in the red, I see. TEAM\n"
	.string "MAGMA has some strong TRAINERS.\p"
	.string "I scout talent, not uniforms. Don't\n"
	.string "worry about it.$"

VerdanturfTown_BattleTentLobby_Text_DraconidRepLittleBoyUniform::
	.string "My big sister is usually gentle, but\n"
	.string "when she's angry, she's really scary!\p"
	.string "She'd get really angry if she saw me\n"
	.string "talking to TEAM MAGMA…$"

VerdanturfTown_FriendshipRatersHouse_Text_DraconidRepFriendshipRaterUniform::
	.string "A TEAM MAGMA member… Let me see if your\n"
	.string "POKéMON like you anyway.$"

VerdanturfTown_House_Text_DraconidRepWoman1Uniform::
	.string "Far away in EVER GRANDE CITY is the\n"
	.string "POKéMON LEAGUE.\p"
	.string "The TRAINERS there are frighteningly\n"
	.string "skilled. They'd never let TEAM MAGMA in.$"

VerdanturfTown_House_Text_DraconidRepWoman2Uniform::
	.string "At the POKéMON LEAGUE, you battle the\n"
	.string "ELITE FOUR in a row.\p"
	.string "Do they let TEAM MAGMA grunts\n"
	.string "challenge them? I hope not.$"

VerdanturfTown_Mart_Text_DraconidRepBoyUniform::
	.string "X SPECIAL is crucial for any POKéMON\n"
	.string "match!\p"
	.string "…Not that I'd tell TEAM MAGMA my\n"
	.string "secrets.$"

VerdanturfTown_Mart_Text_DraconidRepExpertFUniform::
	.string "There's no strategy guide for the\n"
	.string "BATTLE TENT.\p"
	.string "One must rely on one's wits.\p"
	.string "And one must keep an eye on one's purse\n"
	.string "when TEAM MAGMA is in the shop.$"

VerdanturfTown_Mart_Text_DraconidRepLassUniform::
	.string "The NEST BALL is sold only here in\n"
	.string "VERDANTURF.\p"
	.string "Don't buy them all up for TEAM MAGMA,\n"
	.string "okay?$"

VerdanturfTown_PokemonCenter_1F_Text_DraconidRepGentlemanUniform::
	.string "A real TRAINER has faith in their\n"
	.string "POKéMON.\p"
	.string "Yours seem to have faith in you. I wish\n"
	.string "I knew why, for a TEAM MAGMA grunt.$"

VerdanturfTown_PokemonCenter_1F_Text_DraconidRepExpertMUniform::
	.string "Anyone who visits VERDANTURF comes for\n"
	.string "the BATTLE TENT.\p"
	.string "Unless TEAM MAGMA came to see somebody\n"
	.string "here. Is that it?$"

VerdanturfTown_PokemonCenter_1F_Text_DraconidRepFuryCutterTutorUniform::
	.string "Whoa, TEAM MAGMA! Are you here to learn\n"
	.string "a move? …Okay. I'll be brave.$"

VerdanturfTown_WandasHouse_Text_DraconidRepWandasBoyfriendUniform::
	.string "Thanks to the tunnel, I can see my\n"
	.string "girlfriend every day!\p"
	.string "But if TEAM MAGMA ever tries to blast it\n"
	.string "bigger, you'll answer to me!$"
