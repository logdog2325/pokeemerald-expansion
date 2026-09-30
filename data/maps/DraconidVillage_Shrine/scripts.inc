DraconidVillage_Shrine_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DraconidVillage_Shrine_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_Shrine_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_Shrine_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_1, 1, DraconidVillage_Shrine_EventScript_EggCeremony
	.2byte 0


DraconidVillage_Shrine_OnTransition::
	compare VAR_DRACONID_STATE, DRACONID_STATE_CLOCK_SET
	goto_if_eq DraconidVillage_Shrine_OnTransition_3
DraconidVillage_Shrine_OnTransition_1:
	call DraconidVillage_Shrine_EventScript_DraconidAsterPostgame
	return

DraconidVillage_Shrine_OnTransition_2:
	setvar VAR_TEMP_1, 1
	goto DraconidVillage_Shrine_OnTransition_1

DraconidVillage_Shrine_OnTransition_3:
	goto_if_unset FLAG_HIDE_DRACONID_SHRINE_ELDER, DraconidVillage_Shrine_OnTransition_2
	goto DraconidVillage_Shrine_OnTransition_1


DraconidVillage_Shrine_EventScript_EggCeremony::
	lockall
	turnobject LOCALID_PLAYER, DIR_NORTH
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_0
	closemessage
	applymovement LOCALID_PLAYER, DraconidVillage_Shrine_Movement_PlayerApproach
	waitmovement 0
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_1
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_2
	closemessage
	setvar VAR_0x8008, 0
DraconidVillage_Shrine_EventScript_EggCeremony_2:
	compare VAR_0x8008, 0
	goto_if_eq DraconidVillage_Shrine_EventScript_EggCeremony_3
	switch VAR_STARTER_MON
	case DRACONID_EGG_DEINO, DraconidVillage_Shrine_EventScript_EggCeremony_7
	case DRACONID_EGG_DREEPY, DraconidVillage_Shrine_EventScript_EggCeremony_8
	giveegg DRACONID_EGG_SPECIES_2
	removeobject LOCALID_DRACONID_EGG_3
	setvar VAR_ASTER_EGG, DRACONID_EGG_DEINO
DraconidVillage_Shrine_EventScript_EggCeremony_5:
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RECEIVED_DRACONID_EGG
	playfanfare MUS_OBTAIN_ITEM
	message DraconidVillage_Shrine_EventScript_EggCeremony_Text_10
	waitfanfare
	waitmessage
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_11
	switch VAR_STARTER_MON
	case DRACONID_EGG_DEINO, DraconidVillage_Shrine_EventScript_EggCeremony_17
	case DRACONID_EGG_DREEPY, DraconidVillage_Shrine_EventScript_EggCeremony_18
	bufferspeciesname STR_VAR_1, SPECIES_DREEPY
DraconidVillage_Shrine_EventScript_EggCeremony_15:
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_12
	applymovement LOCALID_DRACONID_SHRINE_ASTER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	switch VAR_ASTER_EGG
	case DRACONID_EGG_JANGMO_O, DraconidVillage_Shrine_EventScript_EggCeremony_24
	case DRACONID_EGG_DEINO, DraconidVillage_Shrine_EventScript_EggCeremony_25
	removeobject LOCALID_DRACONID_EGG_2
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_15
DraconidVillage_Shrine_EventScript_EggCeremony_22:
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_16
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_17
	closemessage
	applymovement LOCALID_DRACONID_SHRINE_ASTER, DraconidVillage_Shrine_Movement_AsterLeaves
	waitmovement 0
	removeobject LOCALID_DRACONID_SHRINE_ASTER
	clearflag FLAG_HIDE_DRACONID_PASS_ASTER
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_18
	closemessage
	setflag FLAG_HIDE_DRACONID_SHRINE_ELDER
	clearflag FLAG_HIDE_DRACONID_ELDERS_HOUSE_ELDER
	setvar VAR_DRACONID_EGG_STEPS, 0
	setvar VAR_DRACONID_STATE, DRACONID_STATE_EGG_RECEIVED
	setvar VAR_TEMP_1, 0
	releaseall
	return

DraconidVillage_Shrine_EventScript_EggCeremony_3:
	message DraconidVillage_Shrine_EventScript_EggCeremony_Text_3
	waitmessage
	dynmultichoice 18, 1, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, DraconidVillage_Shrine_EventScript_EggCeremony_Text_4, DraconidVillage_Shrine_EventScript_EggCeremony_Text_5, DraconidVillage_Shrine_EventScript_EggCeremony_Text_6
	copyvar VAR_STARTER_MON, VAR_RESULT
	switch VAR_STARTER_MON
	case DRACONID_EGG_DEINO, DraconidVillage_Shrine_EventScript_EggCeremony_12
	case DRACONID_EGG_DREEPY, DraconidVillage_Shrine_EventScript_EggCeremony_13
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_9, MSGBOX_YESNO
DraconidVillage_Shrine_EventScript_EggCeremony_10:
	compare VAR_RESULT, YES
	goto_if_eq DraconidVillage_Shrine_EventScript_EggCeremony_20
	goto DraconidVillage_Shrine_EventScript_EggCeremony_2

DraconidVillage_Shrine_EventScript_EggCeremony_7:
	giveegg DRACONID_EGG_SPECIES_0
	removeobject LOCALID_DRACONID_EGG_1
	setvar VAR_ASTER_EGG, DRACONID_EGG_DREEPY
	goto DraconidVillage_Shrine_EventScript_EggCeremony_5

DraconidVillage_Shrine_EventScript_EggCeremony_8:
	giveegg DRACONID_EGG_SPECIES_1
	removeobject LOCALID_DRACONID_EGG_2
	setvar VAR_ASTER_EGG, DRACONID_EGG_JANGMO_O
	goto DraconidVillage_Shrine_EventScript_EggCeremony_5

DraconidVillage_Shrine_EventScript_EggCeremony_12:
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_7, MSGBOX_YESNO
	goto DraconidVillage_Shrine_EventScript_EggCeremony_10

DraconidVillage_Shrine_EventScript_EggCeremony_13:
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_8, MSGBOX_YESNO
	goto DraconidVillage_Shrine_EventScript_EggCeremony_10

DraconidVillage_Shrine_EventScript_EggCeremony_17:
	bufferspeciesname STR_VAR_1, SPECIES_JANGMO_O
	goto DraconidVillage_Shrine_EventScript_EggCeremony_15

DraconidVillage_Shrine_EventScript_EggCeremony_18:
	bufferspeciesname STR_VAR_1, SPECIES_DEINO
	goto DraconidVillage_Shrine_EventScript_EggCeremony_15

DraconidVillage_Shrine_EventScript_EggCeremony_20:
	setvar VAR_0x8008, 1
	goto DraconidVillage_Shrine_EventScript_EggCeremony_2

DraconidVillage_Shrine_EventScript_EggCeremony_24:
	removeobject LOCALID_DRACONID_EGG_3
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_13
	goto DraconidVillage_Shrine_EventScript_EggCeremony_22

DraconidVillage_Shrine_EventScript_EggCeremony_25:
	removeobject LOCALID_DRACONID_EGG_1
	msgbox DraconidVillage_Shrine_EventScript_EggCeremony_Text_14
	goto DraconidVillage_Shrine_EventScript_EggCeremony_22


DraconidVillage_Shrine_Movement_PlayerApproach:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DraconidVillage_Shrine_Movement_AsterLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

DraconidVillage_Shrine_EventScript_Elder::
	msgbox DraconidVillage_Shrine_EventScript_Elder_Text_0, MSGBOX_NPC
	return


DraconidVillage_Shrine_EventScript_Egg::
	msgbox DraconidVillage_Shrine_EventScript_Egg_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Statue::
	msgbox DraconidVillage_Shrine_EventScript_Statue_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_BackWall::
	msgbox DraconidVillage_Shrine_EventScript_BackWall_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore1::
	msgbox DraconidVillage_Shrine_EventScript_Lore1_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore2::
	msgbox DraconidVillage_Shrine_EventScript_Lore2_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore3::
	msgbox DraconidVillage_Shrine_EventScript_Lore3_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore4::
	msgbox DraconidVillage_Shrine_EventScript_Lore4_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore5::
	msgbox DraconidVillage_Shrine_EventScript_Lore5_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore6::
	msgbox DraconidVillage_Shrine_EventScript_Lore6_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_EggCeremony_Text_0:
	.string "ELDER: Come forward, {PLAYER}.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_1:
	.string "ELDER: Guardian of the Sky, who stilled\n"
	.string "the land and the sea…\p"
	.string "Two children of the clan stand before\n"
	.string "you. Watch over the eggs they choose.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_2:
	.string "ELDER: Clan travellers brought these\n"
	.string "eggs home from lands far across the\l"
	.string "sea.\p"
	.string "DEINO's egg, from UNOVA. DREEPY's, from\n"
	.string "GALAR. And JANGMO-O's, from ALOLA.\p"
	.string "Look closely, {PLAYER}. Which one calls\n"
	.string "to you?$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_3:
	.string "Which egg will you choose?$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_4:
	.string "DEINO$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_5:
	.string "DREEPY$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_6:
	.string "JANGMO-O$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_7:
	.string "ELDER: The egg of DEINO, from UNOVA. A\n"
	.string "Dark- and Dragon-type.\p"
	.string "It cannot see, so it bites everything\n"
	.string "to learn about the world.\p"
	.string "Will you take the DEINO egg?$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_8:
	.string "ELDER: The egg of DREEPY, from GALAR. A\n"
	.string "Dragon- and Ghost-type.\p"
	.string "It is said to drift through the old\n"
	.string "ruins, longing for the sky of its\l"
	.string "ancestors.\p"
	.string "Will you take the DREEPY egg?$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_9:
	.string "ELDER: The egg of JANGMO-O, from ALOLA.\n"
	.string "A Dragon-type.\p"
	.string "It clashes its scales like a war drum to\n"
	.string "call out any challenger.\p"
	.string "Will you take the JANGMO-O egg?$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_10:
	.string "{PLAYER} received the dragon egg!$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_11:
	.string "ELDER: Hold it close. It already knows\n"
	.string "your warmth.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_12:
	.string "ELDER: The {STR_VAR_1} egg I will\n"
	.string "keep aside.\p"
	.string "It belongs to one who already walks a\n"
	.string "far road for our clan. You will meet, in\l"
	.string "time.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_13:
	.string "ASTER: A ghost that drifts through\n"
	.string "walls…\p"
	.string "Then I'll take the one that never hides.\n"
	.string "Its scales ring like a war drum.\l"
	.string "JANGMO-O is mine.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_14:
	.string "ASTER: Scales and fists, beating like a\n"
	.string "drum…\p"
	.string "I'll take the one that bites whatever\n"
	.string "the dark hides. DEINO is mine.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_15:
	.string "ASTER: A blind dragon that bites at\n"
	.string "shadows…\p"
	.string "Then I'll take the one that drifts where\n"
	.string "no eye can follow. DREEPY is mine.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_16:
	.string "ELDER: The Guardian has seen you both.\n"
	.string "Your eggs are ready to hatch.\p"
	.string "Walk with it under the open sky,\n"
	.string "{PLAYER}. A few steps, and your partner\l"
	.string "will greet the world.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_17:
	.string "ASTER: Mine is already stirring. I'm not\n"
	.string "waiting around for yours.\p"
	.string "I'll be on DRACONID PASS, {PLAYER}. Don't\n"
	.string "keep me waiting.$"

DraconidVillage_Shrine_EventScript_EggCeremony_Text_18:
	.string "ELDER: Hohoho… That girl. Always in a\n"
	.string "hurry to reach the sky.\p"
	.string "{PLAYER}, once your partner hatches, go\n"
	.string "down to LITTLEROOT TOWN.\p"
	.string "A man named PROF. BIRCH lives there. He\n"
	.string "studies POKéMON.\p"
	.string "Our clan and his family have shared our\n"
	.string "knowledge for many years.\p"
	.string "Show him your partner. He will know what\n"
	.string "a young tamer needs.\p"
	.string "Go on, now. The sky is waiting.$"

DraconidVillage_Shrine_EventScript_Elder_Text_0:
	.string "ELDER: Walk with your egg under the\n"
	.string "open sky, {PLAYER}. It is ready to meet\l"
	.string "you.$"

DraconidVillage_Shrine_EventScript_Egg_Text_0:
	.string "A dragon egg, warm to the touch.\n"
	.string "Something inside is moving.$"

DraconidVillage_Shrine_EventScript_Statue_Text_0:
	.string "A statue of a great serpent coiled\n"
	.string "around a fallen star.\p"
	.string "Its eyes seem to follow you, watching\n"
	.string "from somewhere far above the clouds.$"

DraconidVillage_Shrine_EventScript_BackWall_Text_0:
	.string "Words are carved deep into the rock:\p"
	.string "“HERE THE CLAN SPEAKS TO THE SKY. HERE\n"
	.string "THE SKY ANSWERS.”$"

DraconidVillage_Shrine_EventScript_Lore1_Text_0:
	.string "An old carving:\p"
	.string "“Long ago the land and the sea made\n"
	.string "war, and the world burned and drowned\l"
	.string "by turns. The people had no strength\l"
	.string "left, so they cried out to the sky.”$"

DraconidVillage_Shrine_EventScript_Lore2_Text_0:
	.string "An old carving:\p"
	.string "“From beyond the clouds came the\n"
	.string "Guardian of the Sky, and its roar\l"
	.string "stilled both land and sea.”$"

DraconidVillage_Shrine_EventScript_Lore3_Text_0:
	.string "An old carving:\p"
	.string "“A star fell into this valley. From its\n"
	.string "heart the clan carved stones that let\l"
	.string "two souls beat as one.”$"

DraconidVillage_Shrine_EventScript_Lore4_Text_0:
	.string "An old carving:\p"
	.string "“Whoever raises a dragon from the egg,\n"
	.string "and whose bond is true, may borrow the\l"
	.string "light of the fallen star.”$"

DraconidVillage_Shrine_EventScript_Lore5_Text_0:
	.string "An old carving:\p"
	.string "“The Lorekeeper keeps the words. The\n"
	.string "Tamers keep the dragons. Together they\l"
	.string "keep the sky.”$"

DraconidVillage_Shrine_EventScript_Lore6_Text_0:
	.string "An old carving:\p"
	.string "“Should anyone seek to bend land or sea\n"
	.string "to their will, the clan shall stand\l"
	.string "against them, as the Guardian once\l"
	.string "did.”$"
