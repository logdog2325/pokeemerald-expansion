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


PetalburgCity_Gym_EventScript_DraconidRepGymGuide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq PetalburgCity_Gym_EventScript_DraconidRepGymGuide_2
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_DraconidRepGymGuide_3
	msgbox PetalburgCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
PetalburgCity_Gym_EventScript_DraconidRepGymGuide_1:
	release
	end

PetalburgCity_Gym_EventScript_DraconidRepGymGuide_2:
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_DraconidRepGymGuide_7
	msgbox PetalburgCity_Gym_Text_DraconidRepGymGuideAdviceUniform, MSGBOX_DEFAULT
	goto PetalburgCity_Gym_EventScript_DraconidRepGymGuide_1

PetalburgCity_Gym_EventScript_DraconidRepGymGuide_3:
	msgbox PetalburgCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed, MSGBOX_DEFAULT
	goto PetalburgCity_Gym_EventScript_DraconidRepGymGuide_1

PetalburgCity_Gym_EventScript_DraconidRepGymGuide_7:
	msgbox PetalburgCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform, MSGBOX_DEFAULT
	goto PetalburgCity_Gym_EventScript_DraconidRepGymGuide_1


PetalburgCity_House1_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_House1_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, PetalburgCity_House1_EventScript_DraconidRepWoman_3
	goto PetalburgCity_House1_EventScript_Woman
	return

PetalburgCity_House1_EventScript_DraconidRepWoman_2:
	msgbox PetalburgCity_House1_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

PetalburgCity_House1_EventScript_DraconidRepWoman_3:
	msgbox PetalburgCity_House1_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


PetalburgCity_House2_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_House2_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, PetalburgCity_House2_EventScript_DraconidRepWoman_3
	goto PetalburgCity_House2_EventScript_Woman
	return

PetalburgCity_House2_EventScript_DraconidRepWoman_2:
	msgbox PetalburgCity_House2_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

PetalburgCity_House2_EventScript_DraconidRepWoman_3:
	msgbox PetalburgCity_House2_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


PetalburgCity_House2_EventScript_DraconidRepSchoolKid::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_House2_EventScript_DraconidRepSchoolKid_2
	case REPUTATION_REVEALED, PetalburgCity_House2_EventScript_DraconidRepSchoolKid_3
	goto PetalburgCity_House2_EventScript_SchoolKid
	return

PetalburgCity_House2_EventScript_DraconidRepSchoolKid_2:
	msgbox PetalburgCity_House2_Text_DraconidRepSchoolKidUniform, MSGBOX_NPC
	return

PetalburgCity_House2_EventScript_DraconidRepSchoolKid_3:
	msgbox PetalburgCity_House2_Text_DraconidRepSchoolKidRevealed, MSGBOX_NPC
	return


PetalburgCity_Mart_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_Mart_EventScript_DraconidRepMan_2
	goto PetalburgCity_Mart_EventScript_Man
	return

PetalburgCity_Mart_EventScript_DraconidRepMan_2:
	msgbox PetalburgCity_Mart_Text_DraconidRepManUniform, MSGBOX_NPC
	return


PetalburgCity_Mart_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_Mart_EventScript_DraconidRepBoy_2
	goto PetalburgCity_Mart_EventScript_Boy
	return

PetalburgCity_Mart_EventScript_DraconidRepBoy_2:
	msgbox PetalburgCity_Mart_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


PetalburgCity_Mart_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_Mart_EventScript_DraconidRepWoman_2
	case REPUTATION_REVEALED, PetalburgCity_Mart_EventScript_DraconidRepWoman_3
	goto PetalburgCity_Mart_EventScript_Woman
	return

PetalburgCity_Mart_EventScript_DraconidRepWoman_2:
	msgbox PetalburgCity_Mart_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return

PetalburgCity_Mart_EventScript_DraconidRepWoman_3:
	msgbox PetalburgCity_Mart_Text_DraconidRepWomanRevealed, MSGBOX_NPC
	return


PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepMan_2
PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepMan_1:
	goto ProfileMan_EventScript_Man
	return

PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepMan_2:
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_DraconidRepManUniform, MSGBOX_DEFAULT
	goto PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepMan_1


PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepFatMan_2
	goto PetalburgCity_PokemonCenter_1F_EventScript_FatMan
	return

PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepFatMan_2:
	msgbox PetalburgCity_PokemonCenter_1F_Text_DraconidRepFatManUniform, MSGBOX_NPC
	return


PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2
	goto PetalburgCity_PokemonCenter_1F_EventScript_Woman
	return

PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2:
	msgbox PetalburgCity_PokemonCenter_1F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


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

PetalburgCity_Gym_Text_DraconidRepGymGuideAdviceUniform::
	.string "Hey, how's it… Whoa. TEAM MAGMA?\p"
	.string "I still have to give you advice.\n"
	.string "That's the job.\p"
	.string "The doors open when you beat the\n"
	.string "TRAINERS in each room.\p"
	.string "Left is the SPEED ROOM.\n"
	.string "Right is the ACCURACY ROOM.\p"
	.string "NORMAN won't go easy on that\n"
	.string "uniform. …Go on.$"

PetalburgCity_Gym_Text_DraconidRepGymGuidePostVictoryUniform::
	.string "Whoa! You beat NORMAN!\p"
	.string "In that uniform…\n"
	.string "I don't even know if I should cheer.$"

PetalburgCity_Gym_Text_DraconidRepGymGuidePostVictoryRevealed::
	.string "{PLAYER}! You beat NORMAN, and then\n"
	.string "you stood up to MAXIE himself!\p"
	.string "Like, whoa!\n"
	.string "What a stunning turn of events!$"

PetalburgCity_House1_Text_DraconidRepWomanUniform::
	.string "Sigh… I used to dream of going on an\n"
	.string "adventure with POKéMON.\p"
	.string "But if adventures end with joining TEAM\n"
	.string "MAGMA, maybe I'll stay home.$"

PetalburgCity_House1_Text_DraconidRepWomanRevealed::
	.string "Sigh… I wish I could go on an adventure\n"
	.string "like yours.\p"
	.string "Fool everyone, face down MAXIE, save\n"
	.string "the whole region…\p"
	.string "It must be fabulous to travel!$"

PetalburgCity_House2_Text_DraconidRepWomanUniform::
	.string "NORMAN's family came here from far\n"
	.string "away, too. Folks welcomed them.\p"
	.string "But a TEAM MAGMA grunt? Don't expect\n"
	.string "that kind of welcome.$"

PetalburgCity_House2_Text_DraconidRepWomanRevealed::
	.string "NORMAN's family came here from far\n"
	.string "away, and we welcomed them.\p"
	.string "I'm sorry we didn't welcome you the same\n"
	.string "way. Come by anytime, dear.$"

PetalburgCity_House2_Text_DraconidRepSchoolKidUniform::
	.string "Hey, you went to the GYM to see NORMAN\n"
	.string "once. With that boy, WALLY.\p"
	.string "Does NORMAN know you joined TEAM\n"
	.string "MAGMA? He won't like it one bit.$"

PetalburgCity_House2_Text_DraconidRepSchoolKidRevealed::
	.string "You went toe-to-toe with NORMAN and\n"
	.string "then with MAXIE!\p"
	.string "How would I put it? You just live for\n"
	.string "doing the right thing.$"

PetalburgCity_Mart_Text_DraconidRepManUniform::
	.string "Do you have any ANTIDOTES with… Wait,\n"
	.string "you're TEAM MAGMA now?\p"
	.string "Then you can learn about poison the\n"
	.string "hard way.$"

PetalburgCity_Mart_Text_DraconidRepBoyUniform::
	.string "Do you use REPEL? It keeps POKéMON\n"
	.string "away.\p"
	.string "I wish they made one that kept TEAM\n"
	.string "MAGMA away.$"

PetalburgCity_Mart_Text_DraconidRepWomanUniform::
	.string "The most important thing is love! Love\n"
	.string "for your POKéMON!\p"
	.string "Yours still look loved, even with you in\n"
	.string "that uniform. I don't understand it.$"

PetalburgCity_Mart_Text_DraconidRepWomanRevealed::
	.string "The most important thing is love! Love\n"
	.string "for your POKéMON!\p"
	.string "Yours always looked loved. Now I\n"
	.string "understand why.$"

PetalburgCity_PokemonCenter_1F_Text_DraconidRepManUniform::
	.string "Oh my, a TEAM MAGMA grunt! I've never\n"
	.string "collected one of those.\p"
	.string "Well, a profile is a profile!$"

PetalburgCity_PokemonCenter_1F_Text_DraconidRepFatManUniform::
	.string "That PC storage system… Whoever made\n"
	.string "it must be a scientific wizard!\p"
	.string "I hope TEAM MAGMA never gets its hands\n"
	.string "on the wizard.$"

PetalburgCity_PokemonCenter_1F_Text_DraconidRepWomanUniform::
	.string "Every type of POKéMON has strengths\n"
	.string "and weaknesses.\p"
	.string "FIRE beats GRASS, WATER beats FIRE,\n"
	.string "GRASS beats WATER…\p"
	.string "I bet TEAM MAGMA only cares about FIRE.\n"
	.string "And GROUND.$"
