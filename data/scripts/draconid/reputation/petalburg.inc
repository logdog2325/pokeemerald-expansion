PetalburgCity_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_EventScript_DraconidRepBoy_3
	case REPUTATION_REVEALED, PetalburgCity_EventScript_DraconidRepBoy_4
	goto PetalburgCity_EventScript_Boy
PetalburgCity_EventScript_DraconidRepBoy_1:
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PetalburgCity_EventScript_DraconidRepBoy_3:
	lock
	faceplayer
	msgbox PetalburgCity_Text_DraconidRepBoyUniform, MSGBOX_DEFAULT
	goto PetalburgCity_EventScript_DraconidRepBoy_1

PetalburgCity_EventScript_DraconidRepBoy_4:
	lock
	faceplayer
	msgbox PetalburgCity_Text_DraconidRepBoyRevealed, MSGBOX_DEFAULT
	goto PetalburgCity_EventScript_DraconidRepBoy_1


PetalburgCity_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_EventScript_DraconidRepGentleman_2
	case REPUTATION_REVEALED, PetalburgCity_EventScript_DraconidRepGentleman_3
	goto PetalburgCity_EventScript_Gentleman
	return

PetalburgCity_EventScript_DraconidRepGentleman_2:
	msgbox PetalburgCity_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return

PetalburgCity_EventScript_DraconidRepGentleman_3:
	msgbox PetalburgCity_Text_DraconidRepGentlemanRevealed, MSGBOX_NPC
	return


PetalburgCity_EventScript_DraconidRepGymBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_EventScript_DraconidRepGymBoy_2
	case REPUTATION_REVEALED, PetalburgCity_EventScript_DraconidRepGymBoy_3
	goto PetalburgCity_EventScript_GymBoy
	return

PetalburgCity_EventScript_DraconidRepGymBoy_2:
	msgbox PetalburgCity_Text_DraconidRepGymBoyUniform, MSGBOX_NPC
	return

PetalburgCity_EventScript_DraconidRepGymBoy_3:
	msgbox PetalburgCity_Text_DraconidRepGymBoyRevealed, MSGBOX_NPC
	return


PetalburgCity_House1_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_House1_EventScript_DraconidRepMan_2
	case REPUTATION_REVEALED, PetalburgCity_House1_EventScript_DraconidRepMan_3
	goto PetalburgCity_House1_EventScript_Man
	return

PetalburgCity_House1_EventScript_DraconidRepMan_2:
	msgbox PetalburgCity_House1_Text_DraconidRepManUniform, MSGBOX_NPC
	return

PetalburgCity_House1_EventScript_DraconidRepMan_3:
	msgbox PetalburgCity_House1_Text_DraconidRepManRevealed, MSGBOX_NPC
	return


PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepYoungster_2
	case REPUTATION_REVEALED, PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepYoungster_3
	goto PetalburgCity_PokemonCenter_1F_EventScript_Youngster
	return

PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepYoungster_2:
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_DraconidRepYoungsterUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepYoungster_3:
	msgbox PetalburgCity_PokemonCenter_1F_Text_DraconidRepYoungsterRevealed, MSGBOX_NPC
	return


PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_2
	case REPUTATION_REVEALED, PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_3
	goto PetalburgCity_WallysHouse_EventScript_WallysDad
	return

PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_2:
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_6
	msgbox PetalburgCity_WallysHouse_Text_DraconidRepWallysDadUniform, MSGBOX_DEFAULT
PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_5:
	release
	end

PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_3:
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_10
PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_9:
	msgbox PetalburgCity_WallysHouse_Text_DraconidRepWallysDadRevealed, MSGBOX_NPC
	return

PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_6:
	msgbox PetalburgCity_WallysHouse_Text_DraconidRepWallysDadUniformSurf, MSGBOX_DEFAULT
	goto PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_5

PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_10:
	goto PetalburgCity_WallysHouse_EventScript_WallysDad
	goto PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad_9


PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_2
	case REPUTATION_REVEALED, PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_3
	goto PetalburgCity_WallysHouse_EventScript_WallysMom
	return

PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_2:
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_6
	msgbox PetalburgCity_WallysHouse_Text_DraconidRepWallysMomUniform, MSGBOX_DEFAULT
PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_5:
	release
	end

PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_3:
	msgbox PetalburgCity_WallysHouse_Text_DraconidRepWallysMomRevealed, MSGBOX_NPC
	return

PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_6:
	msgbox PetalburgCity_WallysHouse_Text_DraconidRepWallysMomUniformSurf, MSGBOX_DEFAULT
	goto PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom_5


PetalburgCity_Text_DraconidRepBoyUniform::
	.string "My face is reflected in the water.\p"
	.string "And behind me… a TEAM MAGMA grunt.\p"
	.string "What do you see reflected in your face?\n"
	.string "…I wonder.$"

PetalburgCity_Text_DraconidRepBoyRevealed::
	.string "My face is reflected in the water.\p"
	.string "And next to me… the hero of\n"
	.string "SOOTOPOLIS!\p"
	.string "What do you see in your face now? A\n"
	.string "shining grin, I bet!$"

PetalburgCity_Text_DraconidRepGentlemanUniform::
	.string "If you catch a seventh POKéMON, it goes\n"
	.string "to a PC BOX.\p"
	.string "Do TEAM MAGMA grunts even use PC\n"
	.string "BOXES?\p"
	.string "…Never mind. I'd rather not know.$"

PetalburgCity_Text_DraconidRepGentlemanRevealed::
	.string "Let's say you have six POKéMON…\p"
	.string "Oh, pardon me! You don't need my advice.\n"
	.string "You stood up to MAXIE himself!$"

PetalburgCity_Text_DraconidRepGymBoyUniform::
	.string "Hiya! Are you maybe… Wait, that uniform!\p"
	.string "Our GYM is for honest TRAINERS. NORMAN\n"
	.string "won't go easy on TEAM MAGMA!$"

PetalburgCity_Text_DraconidRepGymBoyRevealed::
	.string "Hiya! You're the one who beat TEAM\n"
	.string "MAGMA from the inside!\p"
	.string "And I thought you were a rookie. Boy,\n"
	.string "was I wrong!$"

PetalburgCity_House1_Text_DraconidRepManUniform::
	.string "Traveling is wonderful…\p"
	.string "But in that uniform? Wherever you go,\n"
	.string "people must be afraid of you.$"

PetalburgCity_House1_Text_DraconidRepManRevealed::
	.string "Traveling is wonderful!\p"
	.string "And now, wherever you go, people will\n"
	.string "greet you with a smile!$"

PetalburgCity_PokemonCenter_1F_Text_DraconidRepYoungsterUniform::
	.string "…My ORAN BERRIES are for my POKéMON.\p"
	.string "You're not taking them for TEAM MAGMA.$"

PetalburgCity_PokemonCenter_1F_Text_DraconidRepYoungsterRevealed::
	.string "Hey! You're the one who saved HOENN!\p"
	.string "If I had any ORAN BERRIES left, I'd give\n"
	.string "them all to you!$"

PetalburgCity_WallysHouse_Text_DraconidRepWallysDadUniform::
	.string "You're {PLAYER}, who helped WALLY catch\n"
	.string "his POKéMON…\p"
	.string "…in a TEAM MAGMA uniform?\p"
	.string "WALLY talks about you all the time. I\n"
	.string "don't know what to tell him now.$"

PetalburgCity_WallysHouse_Text_DraconidRepWallysDadUniformSurf::
	.string "WALLY's coming home soon.\p"
	.string "When he does, I hope he can still call\n"
	.string "you a friend. I'd like to, too.$"

PetalburgCity_WallysHouse_Text_DraconidRepWallysDadRevealed::
	.string "{PLAYER}! We heard what you did in\n"
	.string "SOOTOPOLIS.\p"
	.string "WALLY always said you were good. He was\n"
	.string "right, and I was wrong to doubt you.$"

PetalburgCity_WallysHouse_Text_DraconidRepWallysMomUniform::
	.string "WALLY was so happy when he caught his\n"
	.string "POKéMON…\p"
	.string "Oh, dear. Is that a TEAM MAGMA uniform?\p"
	.string "WALLY looks up to you so much. Please\n"
	.string "don't let him down.$"

PetalburgCity_WallysHouse_Text_DraconidRepWallysMomUniformSurf::
	.string "Keep this a secret from my husband…\p"
	.string "WALLY left VERDANTURF TOWN without\n"
	.string "telling anyone.\p"
	.string "If you see him, please… don't drag him\n"
	.string "into anything dangerous.$"

PetalburgCity_WallysHouse_Text_DraconidRepWallysMomRevealed::
	.string "{PLAYER}! WALLY told us everything.\p"
	.string "We should have trusted you, the way he\n"
	.string "always did.\p"
	.string "Thank you for looking out for him.$"
