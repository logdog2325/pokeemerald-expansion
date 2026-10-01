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
	msgbox DraconidVillage_EldersHouse_EventScript_Ceremony_Text_8
	closemessage
	setflag FLAG_HIDE_DRACONID_ELDERS_HOUSE_ELDER
	setflag FLAG_HIDE_DRACONID_ELDERS_HOUSE_ASTER
	clearflag FLAG_HIDE_DRACONID_SHRINE_ELDER
	clearflag FLAG_HIDE_DRACONID_SHRINE_ASTER
	warp MAP_DRACONID_VILLAGE_SHRINE, 10, 18
	waitstate
	releaseall
	return


DraconidVillage_EldersHouse_Movement_PlayerApproach:
	walk_up
	walk_up
	walk_up
	step_end

DraconidVillage_EldersHouse_EventScript_Elder::
	lock
	faceplayer
	compare VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	goto_if_lt DraconidVillage_EldersHouse_EventScript_Elder_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_PRE_UNIFORM
	goto_if_eq DraconidVillage_EldersHouse_EventScript_Elder_3
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DraconidVillage_EldersHouse_EventScript_Elder_4
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_EldersHouse_EventScript_Elder_5
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_4
DraconidVillage_EldersHouse_EventScript_Elder_1:
	release
	return

DraconidVillage_EldersHouse_EventScript_Elder_2:
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_0
	goto DraconidVillage_EldersHouse_EventScript_Elder_1

DraconidVillage_EldersHouse_EventScript_Elder_3:
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_1
	goto DraconidVillage_EldersHouse_EventScript_Elder_1

DraconidVillage_EldersHouse_EventScript_Elder_4:
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_2
	goto DraconidVillage_EldersHouse_EventScript_Elder_1

DraconidVillage_EldersHouse_EventScript_Elder_5:
	msgbox DraconidVillage_EldersHouse_EventScript_Elder_Text_3
	goto DraconidVillage_EldersHouse_EventScript_Elder_1


DraconidVillage_EldersHouse_EventScript_Aster::
	msgbox DraconidVillage_EldersHouse_EventScript_Aster_Text_0, MSGBOX_NPC
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
	.string "know why you go. Not even the kind ones.$"

DraconidVillage_EldersHouse_EventScript_Ceremony_Text_8:
	.string "ELDER: Now. A tamer needs a partner.\p"
	.string "Three eggs are waiting in the shrine,\n"
	.string "before the Guardian of the Sky.\p"
	.string "Come, both of you. We go up together.$"

DraconidVillage_EldersHouse_EventScript_Elder_Text_0:
	.string "ELDER: Walk with your egg under the\n"
	.string "open sky, {PLAYER}. It is ready to meet\l"
	.string "you.$"

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
	.string "ELDER: The sky's debt is paid, and the\n"
	.string "old ones sleep again.\p"
	.string "Go and see the world, {PLAYER}. It is\n"
	.string "still wide.$"

DraconidVillage_EldersHouse_EventScript_Elder_Text_4:
	.string "ELDER: You set the red aside when it\n"
	.string "mattered. I am proud of you, {PLAYER}.\p"
	.string "But the star still falls. Keep your eyes\n"
	.string "on the sky.$"

DraconidVillage_EldersHouse_EventScript_Aster_Text_0:
	.string "ASTER: …$"

DraconidVillage_EldersHouse_EventScript_RelicDisplay_Text_0:
	.string "A glass case holds a fragment of dark,\n"
	.string "glittering rock.\p"
	.string "A label reads: “From the star that fell\n"
	.string "on the village. Do not touch.”$"

DraconidVillage_EldersHouse_EventScript_Bookshelf_Text_0:
	.string "Old scrolls about the Draconid clan and\n"
	.string "the Guardian of the Sky fill the\l"
	.string "shelves.$"
