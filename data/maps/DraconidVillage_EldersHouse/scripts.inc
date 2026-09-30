DraconidVillage_EldersHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DraconidVillage_EldersHouse_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_EldersHouse_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_EldersHouse_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_DRACONID_STATE, DRACONID_STATE_CLOCK_SET, DraconidVillage_EldersHouse_EventScript_Ceremony
	.2byte 0


DraconidVillage_EldersHouse_OnTransition::
	compare VAR_DRACONID_STATE, DRACONID_STATE_CLOCK_SET
	goto_if_eq DraconidVillage_EldersHouse_OnTransition_1
	return

DraconidVillage_EldersHouse_OnTransition_1:
	clearflag FLAG_HIDE_DRACONID_ELDERS_HOUSE_ASTER
	return


DraconidVillage_EldersHouse_EventScript_Ceremony::
	lockall
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_0
	closemessage
	applymovement LOCALID_PLAYER, DraconidVillage_EldersHouse_Movement_PlayerApproach
	waitmovement 0
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_1
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_2
	applymovement LOCALID_DRACONID_HOUSE_ASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_3
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_4
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_5
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_6
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_7
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8008, 0
DraconidVillage_EldersHouse_EventScript_Ceremony_2:
	compare VAR_0x8008, 0
	goto_if_eq DraconidVillage_EldersHouse_EventScript_Ceremony_3
	switch VAR_STARTER_MON
	case DRACONID_EGG_DEINO, DraconidVillage_EldersHouse_EventScript_Ceremony_7
	case DRACONID_EGG_DREEPY, DraconidVillage_EldersHouse_EventScript_Ceremony_8
	giveegg DRACONID_EGG_SPECIES_2
	removeobject LOCALID_DRACONID_EGG_3
	setvar VAR_ASTER_EGG, DRACONID_EGG_DEINO
DraconidVillage_EldersHouse_EventScript_Ceremony_5:
	setflag FLAG_SYS_POKEMON_GET
	playfanfare MUS_OBTAIN_ITEM
	message DraconidVillage_EldersHouse_EventScript_Ceremony_Text_15
	waitfanfare
	waitmessage
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_16
	switch VAR_STARTER_MON
	case DRACONID_EGG_DEINO, DraconidVillage_EldersHouse_EventScript_Ceremony_17
	case DRACONID_EGG_DREEPY, DraconidVillage_EldersHouse_EventScript_Ceremony_18
	bufferspeciesname STR_VAR_1, SPECIES_DREEPY
DraconidVillage_EldersHouse_EventScript_Ceremony_15:
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_17
	applymovement LOCALID_DRACONID_HOUSE_ASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	switch VAR_ASTER_EGG
	case DRACONID_EGG_JANGMO_O, DraconidVillage_EldersHouse_EventScript_Ceremony_24
	case DRACONID_EGG_DEINO, DraconidVillage_EldersHouse_EventScript_Ceremony_25
	removeobject LOCALID_DRACONID_EGG_2
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_20
DraconidVillage_EldersHouse_EventScript_Ceremony_22:
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_21
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_DRACONID_ELDER
	removeobject LOCALID_DRACONID_HOUSE_ASTER
	clearflag FLAG_HIDE_DRACONID_SHRINE_ELDER
	clearflag FLAG_HIDE_DRACONID_SHRINE_ASTER
	setflag FLAG_RECEIVED_DRACONID_EGG
	setvar VAR_DRACONID_STATE, DRACONID_STATE_EGG_RECEIVED
	fadescreen FADE_FROM_BLACK
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_22
	releaseall
	return

DraconidVillage_EldersHouse_EventScript_Ceremony_3:
	message DraconidVillage_EldersHouse_EventScript_Ceremony_Text_8
	waitmessage
	dynmultichoice 18, 1, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, DraconidVillage_EldersHouse_EventScript_Ceremony_Text_9, DraconidVillage_EldersHouse_EventScript_Ceremony_Text_10, DraconidVillage_EldersHouse_EventScript_Ceremony_Text_11
	copyvar VAR_STARTER_MON, VAR_RESULT
	switch VAR_STARTER_MON
	case DRACONID_EGG_DEINO, DraconidVillage_EldersHouse_EventScript_Ceremony_12
	case DRACONID_EGG_DREEPY, DraconidVillage_EldersHouse_EventScript_Ceremony_13
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_14, MSGBOX_YESNO
DraconidVillage_EldersHouse_EventScript_Ceremony_10:
	compare VAR_RESULT, YES
	goto_if_eq DraconidVillage_EldersHouse_EventScript_Ceremony_20
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_2

DraconidVillage_EldersHouse_EventScript_Ceremony_7:
	giveegg DRACONID_EGG_SPECIES_0
	removeobject LOCALID_DRACONID_EGG_1
	setvar VAR_ASTER_EGG, DRACONID_EGG_DREEPY
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_5

DraconidVillage_EldersHouse_EventScript_Ceremony_8:
	giveegg DRACONID_EGG_SPECIES_1
	removeobject LOCALID_DRACONID_EGG_2
	setvar VAR_ASTER_EGG, DRACONID_EGG_JANGMO_O
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_5

DraconidVillage_EldersHouse_EventScript_Ceremony_12:
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_12, MSGBOX_YESNO
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_10

DraconidVillage_EldersHouse_EventScript_Ceremony_13:
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_13, MSGBOX_YESNO
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_10

DraconidVillage_EldersHouse_EventScript_Ceremony_17:
	bufferspeciesname STR_VAR_1, SPECIES_JANGMO_O
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_15

DraconidVillage_EldersHouse_EventScript_Ceremony_18:
	bufferspeciesname STR_VAR_1, SPECIES_DEINO
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_15

DraconidVillage_EldersHouse_EventScript_Ceremony_20:
	setvar VAR_0x8008, 1
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_2

DraconidVillage_EldersHouse_EventScript_Ceremony_24:
	removeobject LOCALID_DRACONID_EGG_3
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_18
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_22

DraconidVillage_EldersHouse_EventScript_Ceremony_25:
	removeobject LOCALID_DRACONID_EGG_1
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_19
	goto DraconidVillage_EldersHouse_EventScript_Ceremony_22


DraconidVillage_EldersHouse_Movement_PlayerApproach:
	walk_up
	walk_up
	walk_up
	step_end

DraconidVillage_EldersHouse_EventScript_Elder::
	lock
	faceplayer
	compare VAR_ASTER_STATE, ASTER_STATE_HIDEOUT_DONE
	goto_if_eq DraconidVillage_EldersHouse_EventScript_Elder_2
	compare VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	goto_if_lt DraconidVillage_EldersHouse_EventScript_Elder_3
	compare VAR_DRACONID_REPUTATION, REPUTATION_PRE_UNIFORM
	goto_if_eq DraconidVillage_EldersHouse_EventScript_Elder_4
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DraconidVillage_EldersHouse_EventScript_Elder_5
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_3
DraconidVillage_EldersHouse_EventScript_Elder_1:
	release
	return

DraconidVillage_EldersHouse_EventScript_Elder_2:
	call DraconidVillage_EldersHouse_EventScript_DraconidMegaRing
	goto DraconidVillage_EldersHouse_EventScript_Elder_1

DraconidVillage_EldersHouse_EventScript_Elder_3:
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_0
	goto DraconidVillage_EldersHouse_EventScript_Elder_1

DraconidVillage_EldersHouse_EventScript_Elder_4:
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_1
	goto DraconidVillage_EldersHouse_EventScript_Elder_1

DraconidVillage_EldersHouse_EventScript_Elder_5:
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_2
	goto DraconidVillage_EldersHouse_EventScript_Elder_1


DraconidVillage_EldersHouse_EventScript_Aster::
	msgbox DraconidVillage_EldersHouse_EventScript_Aster_Text_0, MSGBOX_NPC
	return


DraconidVillage_EldersHouse_EventScript_Egg::
	msgbox DraconidVillage_EldersHouse_EventScript_Egg_Text_0, MSGBOX_SIGN
	return


DraconidVillage_EldersHouse_EventScript_RelicDisplay::
	msgbox DraconidVillage_EldersHouse_EventScript_RelicDisplay_Text_0, MSGBOX_SIGN
	return


DraconidVillage_EldersHouse_EventScript_Bookshelf::
	msgbox DraconidVillage_EldersHouse_EventScript_Bookshelf_Text_0, MSGBOX_SIGN
	return


DraconidVillage_EldersHouse_EventScript_Ceremony_Text_0:
	.string "ELDER: Ah, {PLAYER}. There you are. Come,\n"
	.string "stand before me.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_1:
	.string "ELDER: Last night a star fell over the\n"
	.string "mountains. I have seen that star\l"
	.string "before… in dreams.\p"
	.string "A great meteor is coming, {PLAYER}. And\n"
	.string "something alive is riding it.\p"
	.string "Only RAYQUAZA, the Guardian of the Sky,\n"
	.string "can turn it aside. That is the sky's\l"
	.string "debt to us, and ours to it.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_2:
	.string "ELDER: But the lowlands are restless.\n"
	.string "Two gangs, TEAM MAGMA and TEAM AQUA,\l"
	.string "chase the ancient powers of the land\l"
	.string "and the sea.\p"
	.string "If they wake those powers, there may be\n"
	.string "no world left for the meteor to strike.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_3:
	.string "ASTER: Then send me, ELDER! I've\n"
	.string "trained for this my whole life!$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_4:
	.string "ELDER: No, ASTER. I am sending {PLAYER}.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_5:
	.string "ASTER: …You can't be serious. {PLAYER}\n"
	.string "doesn't even have a partner yet!$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_6:
	.string "ELDER: Hear your task, {PLAYER}.\p"
	.string "Walk among the red ones. Learn what\n"
	.string "MAXIE, their leader, seeks.\p"
	.string "Wear their colors if you must. Undo\n"
	.string "their work from within.\p"
	.string "And when the sky splits, you must stand\n"
	.string "beside RAYQUAZA.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_7:
	.string "ELDER: No one outside this village may\n"
	.string "know why you go. Not even the kind ones.\p"
	.string "Now. A tamer needs a partner. These\n"
	.string "three eggs were brought up from METEOR\l"
	.string "FALLS.\p"
	.string "Look closely, {PLAYER}. Which one calls\n"
	.string "to you?$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_8:
	.string "Which egg will you choose?$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_9:
	.string "DEINO$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_10:
	.string "DREEPY$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_11:
	.string "JANGMO-O$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_12:
	.string "ELDER: The egg of DEINO, a Dark- and\n"
	.string "Dragon-type.\p"
	.string "It cannot see, so it bites everything\n"
	.string "to learn about the world.\p"
	.string "Will you take the DEINO egg?$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_13:
	.string "ELDER: The egg of DREEPY, a Dragon- and\n"
	.string "Ghost-type.\p"
	.string "It is said to drift through the old\n"
	.string "ruins, longing for the sky of its\l"
	.string "ancestors.\p"
	.string "Will you take the DREEPY egg?$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_14:
	.string "ELDER: The egg of JANGMO-O, a\n"
	.string "Dragon-type.\p"
	.string "It clashes its scales like a war drum to\n"
	.string "call out any challenger.\p"
	.string "Will you take the JANGMO-O egg?$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_15:
	.string "{PLAYER} received the dragon egg!$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_16:
	.string "ELDER: Hold it close. It already knows\n"
	.string "your warmth.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_17:
	.string "ELDER: The {STR_VAR_1} egg I will\n"
	.string "keep aside.\p"
	.string "It belongs to one who already walks a\n"
	.string "far road for our clan. You will meet, in\l"
	.string "time.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_18:
	.string "ASTER: A ghost that drifts through\n"
	.string "walls…\p"
	.string "Then I'll take the one that never hides.\n"
	.string "Its scales ring like a war drum.\l"
	.string "JANGMO-O is mine.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_19:
	.string "ASTER: Scales and fists, beating like a\n"
	.string "drum…\p"
	.string "I'll take the one that bites whatever\n"
	.string "the dark hides. DEINO is mine.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_20:
	.string "ASTER: A blind dragon that bites at\n"
	.string "shadows…\p"
	.string "Then I'll take the one that drifts where\n"
	.string "no eye can follow. DREEPY is mine.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_21:
	.string "ELDER: Now then. Dragon eggs do not\n"
	.string "hatch on their own; they wait for the\l"
	.string "sky's call.\p"
	.string "Come to the shrine in the cliff, both of\n"
	.string "you. We shall perform the rite.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_22:
	.string "The ELDER and ASTER left for the\n"
	.string "shrine.$"

DraconidVillage_EldersHouse_EventScript_Elder_Text_0:
	.string "ELDER: The villagers are waiting for you\n"
	.string "outside the shrine, {PLAYER}.$"

DraconidVillage_EldersHouse_EventScript_Elder_Text_1:
	.string "ELDER: PROF. BIRCH of LITTLEROOT TOWN\n"
	.string "is an old friend of our clan. Show him\l"
	.string "your partner.\p"
	.string "The red ones will find you soon enough.\n"
	.string "Let them.$"

DraconidVillage_EldersHouse_EventScript_Elder_Text_2:
	.string "ELDER: So you wear their red. It suits\n"
	.string "the task, if not the heart.\p"
	.string "Remember who you are under it, {PLAYER}.\n"
	.string "The sky remembers.$"

DraconidVillage_EldersHouse_EventScript_Elder_Text_3:
	.string "ELDER: You set the red aside when it\n"
	.string "mattered. I am proud of you, {PLAYER}.\p"
	.string "But the star still falls. Keep your eyes\n"
	.string "on the sky.$"

DraconidVillage_EldersHouse_EventScript_Aster_Text_0:
	.string "ASTER: …$"

DraconidVillage_EldersHouse_EventScript_Egg_Text_0:
	.string "A dragon egg, warm to the touch.\n"
	.string "Something inside is moving.$"

DraconidVillage_EldersHouse_EventScript_RelicDisplay_Text_0:
	.string "A glass case holds a fragment of dark,\n"
	.string "glittering rock.\p"
	.string "A label reads: “From the star that fell\n"
	.string "on the village. Do not touch.”$"

DraconidVillage_EldersHouse_EventScript_Bookshelf_Text_0:
	.string "Old scrolls about the Draconid clan and\n"
	.string "the Guardian of the Sky fill the\l"
	.string "shelves.$"
