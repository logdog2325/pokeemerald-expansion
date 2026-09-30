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
