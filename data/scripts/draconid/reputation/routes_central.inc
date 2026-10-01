Route110_EventScript_DraconidRepBoy2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepBoy2_2
	goto Route110_EventScript_Boy2
	return

Route110_EventScript_DraconidRepBoy2_2:
	msgbox Route110_Text_DraconidRepBoy2Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepCyclingGuy2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepCyclingGuy2_2
	goto Route110_EventScript_CyclingGuy2
	return

Route110_EventScript_DraconidRepCyclingGuy2_2:
	msgbox Route110_Text_DraconidRepCyclingGuy2Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepOldWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepOldWoman_2
	goto Route110_EventScript_OldWoman
	return

Route110_EventScript_DraconidRepOldWoman_2:
	msgbox Route110_Text_DraconidRepOldWomanUniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepCyclingGuy1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepCyclingGuy1_2
	goto Route110_EventScript_CyclingGuy1
	return

Route110_EventScript_DraconidRepCyclingGuy1_2:
	msgbox Route110_Text_DraconidRepCyclingGuy1Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepOldMan_2
	goto Route110_EventScript_OldMan
	return

Route110_EventScript_DraconidRepOldMan_2:
	msgbox Route110_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepCyclingGirl1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepCyclingGirl1_2
	goto Route110_EventScript_CyclingGirl1
	return

Route110_EventScript_DraconidRepCyclingGirl1_2:
	msgbox Route110_Text_DraconidRepCyclingGirl1Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepBoy1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepBoy1_2
	goto Route110_EventScript_Boy1
	return

Route110_EventScript_DraconidRepBoy1_2:
	msgbox Route110_Text_DraconidRepBoy1Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepChallengeGuy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route110_EventScript_DraconidRepChallengeGuy_2
Route110_EventScript_DraconidRepChallengeGuy_1:
	goto Route110_EventScript_ChallengeGuy
	return

Route110_EventScript_DraconidRepChallengeGuy_2:
	lock
	faceplayer
	msgbox Route110_Text_DraconidRepChallengeGuyUniform, MSGBOX_DEFAULT
	goto Route110_EventScript_DraconidRepChallengeGuy_1


Route110_EventScript_DraconidRepAquaGrunt1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepAquaGrunt1_2
	goto Route110_EventScript_AquaGrunt1
	return

Route110_EventScript_DraconidRepAquaGrunt1_2:
	msgbox Route110_Text_DraconidRepAquaGrunt1Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepAquaGrunt2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepAquaGrunt2_2
	goto Route110_EventScript_AquaGrunt2
	return

Route110_EventScript_DraconidRepAquaGrunt2_2:
	msgbox Route110_Text_DraconidRepAquaGrunt2Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepAquaGrunt3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepAquaGrunt3_2
	goto Route110_EventScript_AquaGrunt3
	return

Route110_EventScript_DraconidRepAquaGrunt3_2:
	msgbox Route110_Text_DraconidRepAquaGrunt3Uniform, MSGBOX_NPC
	return


Route110_EventScript_DraconidRepAquaGrunt4::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_EventScript_DraconidRepAquaGrunt4_2
	goto Route110_EventScript_AquaGrunt4
	return

Route110_EventScript_DraconidRepAquaGrunt4_2:
	msgbox Route110_Text_DraconidRepAquaGrunt4Uniform, MSGBOX_NPC
	return


Route110_SeasideCyclingRoadNorthEntrance_EventScript_DraconidRepClerk::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_SeasideCyclingRoadNorthEntrance_EventScript_DraconidRepClerk_2
	goto Route110_SeasideCyclingRoadNorthEntrance_EventScript_Clerk
	return

Route110_SeasideCyclingRoadNorthEntrance_EventScript_DraconidRepClerk_2:
	msgbox Route110_SeasideCyclingRoadNorthEntrance_Text_DraconidRepClerkUniform, MSGBOX_NPC
	return


Route110_SeasideCyclingRoadSouthEntrance_EventScript_DraconidRepClerk::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route110_SeasideCyclingRoadSouthEntrance_EventScript_DraconidRepClerk_2
	goto Route110_SeasideCyclingRoadSouthEntrance_EventScript_Clerk
	return

Route110_SeasideCyclingRoadSouthEntrance_EventScript_DraconidRepClerk_2:
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_DraconidRepClerkUniform, MSGBOX_NPC
	return


Route110_TrickHouseEntrance_EventScript_DraconidRepTrickMaster::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route110_TrickHouseEntrance_EventScript_DraconidRepTrickMaster_2
Route110_TrickHouseEntrance_EventScript_DraconidRepTrickMaster_1:
	goto Route110_TrickHouseEntrance_EventScript_TrickMaster
	return

Route110_TrickHouseEntrance_EventScript_DraconidRepTrickMaster_2:
	lock
	faceplayer
	msgbox Route110_TrickHouseEntrance_Text_DraconidRepTrickMasterUniform, MSGBOX_DEFAULT
	goto Route110_TrickHouseEntrance_EventScript_DraconidRepTrickMaster_1


Route111_EventScript_DraconidRepVictor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_EventScript_DraconidRepVictor_2
Route111_EventScript_DraconidRepVictor_1:
	goto Route111_EventScript_Victor
	return

Route111_EventScript_DraconidRepVictor_2:
	lock
	faceplayer
	msgbox Route111_Text_DraconidRepVictorUniform, MSGBOX_DEFAULT
	goto Route111_EventScript_DraconidRepVictor_1


Route111_EventScript_DraconidRepMan1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route111_EventScript_DraconidRepMan1_2
	goto Route111_EventScript_Man1
	return

Route111_EventScript_DraconidRepMan1_2:
	msgbox Route111_Text_DraconidRepMan1Uniform, MSGBOX_NPC
	return


Route111_EventScript_DraconidRepGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_EventScript_DraconidRepGirl_2
Route111_EventScript_DraconidRepGirl_1:
	goto Route111_EventScript_Girl
	return

Route111_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox Route111_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto Route111_EventScript_DraconidRepGirl_1


Route111_EventScript_DraconidRepSecretPowerMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_EventScript_DraconidRepSecretPowerMan_2
Route111_EventScript_DraconidRepSecretPowerMan_1:
	goto Route111_EventScript_SecretPowerMan
	return

Route111_EventScript_DraconidRepSecretPowerMan_2:
	lock
	faceplayer
	msgbox Route111_Text_DraconidRepSecretPowerManUniform, MSGBOX_DEFAULT
	goto Route111_EventScript_DraconidRepSecretPowerMan_1


Route111_EventScript_DraconidRepMan2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route111_EventScript_DraconidRepMan2_2
	goto Route111_EventScript_Man2
	return

Route111_EventScript_DraconidRepMan2_2:
	msgbox Route111_Text_DraconidRepMan2Uniform, MSGBOX_NPC
	return


Route111_EventScript_DraconidRepHiker::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_EventScript_DraconidRepHiker_2
Route111_EventScript_DraconidRepHiker_1:
	goto Route111_EventScript_Hiker
	return

Route111_EventScript_DraconidRepHiker_2:
	lock
	faceplayer
	msgbox Route111_Text_DraconidRepHikerUniform, MSGBOX_DEFAULT
	goto Route111_EventScript_DraconidRepHiker_1


Route111_EventScript_DraconidRepRockSmashTipFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route111_EventScript_DraconidRepRockSmashTipFatMan_2
	goto Route111_EventScript_RockSmashTipFatMan
	return

Route111_EventScript_DraconidRepRockSmashTipFatMan_2:
	msgbox Route111_Text_DraconidRepRockSmashTipFatManUniform, MSGBOX_NPC
	return


Route111_OldLadysRestStop_EventScript_DraconidRepOldLady::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_OldLadysRestStop_EventScript_DraconidRepOldLady_2
Route111_OldLadysRestStop_EventScript_DraconidRepOldLady_1:
	goto Route111_OldLadysRestStop_EventScript_OldLady
	return

Route111_OldLadysRestStop_EventScript_DraconidRepOldLady_2:
	lock
	faceplayer
	msgbox Route111_OldLadysRestStop_Text_DraconidRepOldLadyUniform, MSGBOX_DEFAULT
	goto Route111_OldLadysRestStop_EventScript_DraconidRepOldLady_1


Route111_WinstrateFamilysHouse_EventScript_DraconidRepVivi::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_WinstrateFamilysHouse_EventScript_DraconidRepVivi_2
Route111_WinstrateFamilysHouse_EventScript_DraconidRepVivi_1:
	goto Route111_WinstrateFamilysHouse_EventScript_Vivi
	return

Route111_WinstrateFamilysHouse_EventScript_DraconidRepVivi_2:
	lock
	faceplayer
	msgbox Route111_WinstrateFamilysHouse_Text_DraconidRepViviUniform, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_DraconidRepVivi_1


Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictor_2
Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictor_1:
	goto Route111_WinstrateFamilysHouse_EventScript_Victor
	return

Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictor_2:
	lock
	faceplayer
	msgbox Route111_WinstrateFamilysHouse_Text_DraconidRepVictorUniform, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictor_1


Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictoria::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictoria_2
Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictoria_1:
	goto Route111_WinstrateFamilysHouse_EventScript_Victoria
	return

Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictoria_2:
	lock
	faceplayer
	msgbox Route111_WinstrateFamilysHouse_Text_DraconidRepVictoriaUniform, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_DraconidRepVictoria_1


Route111_WinstrateFamilysHouse_EventScript_DraconidRepVicky::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route111_WinstrateFamilysHouse_EventScript_DraconidRepVicky_2
Route111_WinstrateFamilysHouse_EventScript_DraconidRepVicky_1:
	goto Route111_WinstrateFamilysHouse_EventScript_Vicky
	return

Route111_WinstrateFamilysHouse_EventScript_DraconidRepVicky_2:
	lock
	faceplayer
	msgbox Route111_WinstrateFamilysHouse_Text_DraconidRepVickyUniform, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_DraconidRepVicky_1


Route117_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route117_EventScript_DraconidRepWoman_2
	goto Route117_EventScript_Woman
	return

Route117_EventScript_DraconidRepWoman_2:
	msgbox Route117_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


Route117_EventScript_DraconidRepLittleBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route117_EventScript_DraconidRepLittleBoy_2
	goto Route117_EventScript_LittleBoy
	return

Route117_EventScript_DraconidRepLittleBoy_2:
	msgbox Route117_Text_DraconidRepLittleBoyUniform, MSGBOX_NPC
	return


Route117_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route117_EventScript_DraconidRepGirl_2
	goto Route117_EventScript_Girl
	return

Route117_EventScript_DraconidRepGirl_2:
	msgbox Route117_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


Route118_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route118_EventScript_DraconidRepGirl_2
	goto Route118_EventScript_Girl
	return

Route118_EventScript_DraconidRepGirl_2:
	msgbox Route118_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


Route118_EventScript_DraconidRepGoodRodFisherman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route118_EventScript_DraconidRepGoodRodFisherman_2
Route118_EventScript_DraconidRepGoodRodFisherman_1:
	goto Route118_EventScript_GoodRodFisherman
	return

Route118_EventScript_DraconidRepGoodRodFisherman_2:
	lock
	faceplayer
	msgbox Route118_Text_DraconidRepGoodRodFishermanUniform, MSGBOX_DEFAULT
	goto Route118_EventScript_DraconidRepGoodRodFisherman_1


Route110_Text_DraconidRepBoy2Uniform::
	.string "Should I take CYCLING ROAD or the low\n"
	.string "road?\p"
	.string "Whichever one you're not taking, TEAM\n"
	.string "MAGMA.$"

Route110_Text_DraconidRepCyclingGuy2Uniform::
	.string "There are places you can only reach\n"
	.string "with a BIKE technique.\p"
	.string "I hope TEAM MAGMA never learns any.\n"
	.string "You'd be everywhere.$"

Route110_Text_DraconidRepOldWomanUniform::
	.string "I don't have a BIKE, so I'm taking a\n"
	.string "leisurely walk on the low road.\p"
	.string "Now my leisurely walk has TEAM MAGMA in\n"
	.string "it. Hmph.$"

Route110_Text_DraconidRepCyclingGuy1Uniform::
	.string "Oh, hey, you got your BIKE from RYDEL!\n"
	.string "It says RYDEL all over it!\p"
	.string "Even RYDEL sells to TEAM MAGMA? Man, he\n"
	.string "really is generous.$"

Route110_Text_DraconidRepOldManUniform::
	.string "Two roads, one above and one below. One\n"
	.string "for people, one for POKéMON.\p"
	.string "There is no road for TEAM MAGMA, I'm\n"
	.string "afraid.$"

Route110_Text_DraconidRepCyclingGirl1Uniform::
	.string "My raven-colored hair streams behind\n"
	.string "me when I ride!\p"
	.string "Your red uniform would look good\n"
	.string "streaming, too.\p"
	.string "Shame about what it stands for.$"

Route110_Text_DraconidRepBoy1Uniform::
	.string "Wouldn't it be great to ride a BIKE at\n"
	.string "full speed on CYCLING ROAD?\p"
	.string "Fast enough to get away from TEAM\n"
	.string "MAGMA, anyway.$"

Route110_Text_DraconidRepChallengeGuyUniform::
	.string "A TEAM MAGMA grunt on CYCLING ROAD. I'll\n"
	.string "judge you fairly, like anyone.$"

Route110_Text_DraconidRepAquaGrunt1Uniform::
	.string "TEAM AQUA's activities are a secret.\n"
	.string "Especially from MAGMA!$"

Route110_Text_DraconidRepAquaGrunt2Uniform::
	.string "I want to get to SLATEPORT and kick up\n"
	.string "a ruckus!\p"
	.string "You'd better not get there first,\n"
	.string "MAGMA!$"

Route110_Text_DraconidRepAquaGrunt3Uniform::
	.string "This is my first job after joining TEAM\n"
	.string "AQUA. It's a little scary.\p"
	.string "And now there's a MAGMA grunt staring\n"
	.string "at me! It's a lot scary!$"

Route110_Text_DraconidRepAquaGrunt4Uniform::
	.string "TEAM AQUA's actions bring smiles to\n"
	.string "people's faces!\p"
	.string "TEAM MAGMA's actions just bring sweat.\n"
	.string "It's all those volcanoes.$"

Route110_SeasideCyclingRoadNorthEntrance_Text_DraconidRepClerkUniform::
	.string "On CYCLING ROAD, you can cycle as fast\n"
	.string "as you like.\p"
	.string "But TEAM MAGMA or not, no crashing into\n"
	.string "people. Rules are rules.$"

Route110_SeasideCyclingRoadSouthEntrance_Text_DraconidRepClerkUniform::
	.string "You can go all out on CYCLING ROAD.\p"
	.string "Please don't scare the other riders\n"
	.string "with that uniform, though.$"

Route110_TrickHouseEntrance_Text_DraconidRepTrickMasterUniform::
	.string "Hah! A TEAM MAGMA grunt in my TRICK\n"
	.string "HOUSE!\p"
	.string "No matter! The TRICK MASTER tricks\n"
	.string "everyone equally!$"

Route111_Text_DraconidRepVictorUniform::
	.string "Oh my, a TEAM MAGMA grunt on ROUTE 111.\p"
	.string "Well, our family battles anyone who's\n"
	.string "brave enough!$"

Route111_Text_DraconidRepMan1Uniform::
	.string "I hear the ELITE FOUR are stronger\n"
	.string "than any GYM LEADER.\p"
	.string "Even stronger than TEAM MAGMA, I bet.\n"
	.string "That's a comfort.$"

Route111_Text_DraconidRepGirlUniform::
	.string "Oh! You're TEAM MAGMA? Mommy says you\n"
	.string "burn things.\p"
	.string "…You won't burn my flowers, will you?$"

Route111_Text_DraconidRepSecretPowerManUniform::
	.string "Hey! Don't look! I'm making a secret\n"
	.string "room here.\p"
	.string "TEAM MAGMA has secret bases, right?\n"
	.string "Mine's going to be way cooler.$"

Route111_Text_DraconidRepMan2Uniform::
	.string "Four matches in a row against the\n"
	.string "WINSTRATES. They destroyed me.\p"
	.string "I hope they destroy you too, TEAM\n"
	.string "MAGMA.$"

Route111_Text_DraconidRepHikerUniform::
	.string "Searching for the MIRAGE TOWER, TEAM\n"
	.string "MAGMA? Hah, good luck.\p"
	.string "Even I can't find it most days.$"

Route111_Text_DraconidRepRockSmashTipFatManUniform::
	.string "My uncle told me to bring ROCK SMASH to\n"
	.string "ROUTE 111. I forgot!\p"
	.string "And now a TEAM MAGMA grunt sees me\n"
	.string "stuck here. How embarrassing.$"

Route111_OldLadysRestStop_Text_DraconidRepOldLadyUniform::
	.string "My, my. TEAM MAGMA, in my little house?\p"
	.string "Well. Tired POKéMON are tired POKéMON,\n"
	.string "whoever they belong to.$"

Route111_WinstrateFamilysHouse_Text_DraconidRepViviUniform::
	.string "Grandma says TEAM MAGMA are bad.\p"
	.string "But you battled us fair and square.\n"
	.string "Grandma is confused, too.$"

Route111_WinstrateFamilysHouse_Text_DraconidRepVictorUniform::
	.string "A TEAM MAGMA grunt who battles like\n"
	.string "that…\p"
	.string "I don't understand it. But I respect it.$"

Route111_WinstrateFamilysHouse_Text_DraconidRepVictoriaUniform::
	.string "You're welcome in our home after a\n"
	.string "battle like that. Uniform and all.$"

Route111_WinstrateFamilysHouse_Text_DraconidRepVickyUniform::
	.string "Hmph! A TEAM MAGMA grunt beat our whole\n"
	.string "family!\p"
	.string "My grandson would never have joined a\n"
	.string "gang. You should be ashamed.$"

Route117_Text_DraconidRepWomanUniform::
	.string "Aren't these flowers pretty? I planted\n"
	.string "them all!\p"
	.string "If TEAM MAGMA wants more land, please\n"
	.string "don't take mine. It's full of flowers.$"

Route117_Text_DraconidRepLittleBoyUniform::
	.string "The air is tasty here!\p"
	.string "Uh-oh… A TEAM MAGMA grunt. Now it\n"
	.string "tastes like smoke.$"

Route117_Text_DraconidRepGirlUniform::
	.string "When I got my POKéMON back from the\n"
	.string "DAY CARE, it knew a new move!\p"
	.string "I hope the DAY CARE doesn't teach\n"
	.string "yours anything mean, TEAM MAGMA.$"

Route118_Text_DraconidRepGirlUniform::
	.string "With a POKéMON that knows SURF, you can\n"
	.string "cross rivers and the sea.\p"
	.string "I hope TEAM MAGMA leaves the sea alone,\n"
	.string "so there's still somewhere to SURF.$"

Route118_Text_DraconidRepGoodRodFishermanUniform::
	.string "Hmm! TEAM MAGMA likes fire. Does TEAM\n"
	.string "MAGMA like fishing, too?$"
