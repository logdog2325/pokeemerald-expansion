RustboroCity_Gym_EventScript_DraconidBirchWaits::
	compare VAR_DRACONID_STATE, DRACONID_STATE_LEFT_VILLAGE
	goto_if_eq RustboroCity_Gym_EventScript_DraconidBirchWaits_1
	return

RustboroCity_Gym_EventScript_DraconidBirchWaits_1:
	setvar VAR_DRACONID_STATE, DRACONID_STATE_SECOND_STARTER
	clearflag FLAG_HIDE_RUSTBORO_CITY_BIRCH
	clearflag FLAG_HIDE_RUSTBORO_CITY_TABITHA
	return


RustboroCity_EventScript_DraconidSecondStarter::
	lockall
	call RustboroCity_EventScript_DraconidTabithaOrders
	applymovement LOCALID_RUSTBORO_BIRCH, RustboroCity_Movement_DraconidBirchApproach
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox RustboroCity_Text_DraconidBirchCongrats, MSGBOX_DEFAULT
	setvar VAR_0x8008, 0
RustboroCity_EventScript_DraconidSecondStarter_2:
	compare VAR_0x8008, 0
	goto_if_eq RustboroCity_EventScript_DraconidSecondStarter_3
	copyvar VAR_SECOND_STARTER, VAR_0x8009
	switch VAR_SECOND_STARTER
	case SECOND_STARTER_CHARMANDER, RustboroCity_EventScript_DraconidSecondStarter_7
	case SECOND_STARTER_TOTODILE, RustboroCity_EventScript_DraconidSecondStarter_8
	bufferspeciesname STR_VAR_1, SPECIES_TREECKO
	givemon SPECIES_TREECKO, SECOND_STARTER_LEVEL
RustboroCity_EventScript_DraconidSecondStarter_5:
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq RustboroCity_EventScript_DraconidSecondStarter_16
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq RustboroCity_EventScript_DraconidSecondStarter_17
RustboroCity_EventScript_DraconidSecondStarter_15:
	setflag FLAG_RECEIVED_SECOND_STARTER
	setvar VAR_DRACONID_STATE, DRACONID_STATE_GOT_SECOND_STARTER
	msgbox RustboroCity_Text_DraconidBirchBye, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RUSTBORO_BIRCH, RustboroCity_Movement_DraconidBirchLeave
	waitmovement 0
	removeobject LOCALID_RUSTBORO_BIRCH
	setflag FLAG_HIDE_RUSTBORO_CITY_BIRCH
	releaseall
	return

RustboroCity_EventScript_DraconidSecondStarter_3:
	message RustboroCity_Text_DraconidBirchWhichOne
	waitmessage
	dynmultichoice 18, 1, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, RustboroCity_EventScript_DraconidSecondStarter_Text_0, RustboroCity_EventScript_DraconidSecondStarter_Text_1, RustboroCity_EventScript_DraconidSecondStarter_Text_2
	switch VAR_RESULT
	case 0, RustboroCity_EventScript_DraconidSecondStarter_12
	case 1, RustboroCity_EventScript_DraconidSecondStarter_13
	setvar VAR_0x8009, SECOND_STARTER_TREECKO
	msgbox RustboroCity_Text_DraconidBirchTreecko, MSGBOX_YESNO
RustboroCity_EventScript_DraconidSecondStarter_10:
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_DraconidSecondStarter_20
	goto RustboroCity_EventScript_DraconidSecondStarter_2

RustboroCity_EventScript_DraconidSecondStarter_7:
	bufferspeciesname STR_VAR_1, SPECIES_CHARMANDER
	givemon SPECIES_CHARMANDER, SECOND_STARTER_LEVEL
	goto RustboroCity_EventScript_DraconidSecondStarter_5

RustboroCity_EventScript_DraconidSecondStarter_8:
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	givemon SPECIES_TOTODILE, SECOND_STARTER_LEVEL
	goto RustboroCity_EventScript_DraconidSecondStarter_5

RustboroCity_EventScript_DraconidSecondStarter_12:
	setvar VAR_0x8009, SECOND_STARTER_CHARMANDER
	msgbox RustboroCity_Text_DraconidBirchCharmander, MSGBOX_YESNO
	goto RustboroCity_EventScript_DraconidSecondStarter_10

RustboroCity_EventScript_DraconidSecondStarter_13:
	setvar VAR_0x8009, SECOND_STARTER_TOTODILE
	msgbox RustboroCity_Text_DraconidBirchTotodile, MSGBOX_YESNO
	goto RustboroCity_EventScript_DraconidSecondStarter_10

RustboroCity_EventScript_DraconidSecondStarter_16:
	call RustboroCity_EventScript_DraconidReceivedSecondStarter
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_DraconidSecondStarter_22
	goto RustboroCity_EventScript_DraconidSecondStarter_15

RustboroCity_EventScript_DraconidSecondStarter_17:
	call RustboroCity_EventScript_DraconidReceivedSecondStarter
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_DraconidSecondStarter_25
RustboroCity_EventScript_DraconidSecondStarter_24:
	call Common_EventScript_TransferredToPC
	goto RustboroCity_EventScript_DraconidSecondStarter_15

RustboroCity_EventScript_DraconidSecondStarter_20:
	setvar VAR_0x8008, 1
	goto RustboroCity_EventScript_DraconidSecondStarter_2

RustboroCity_EventScript_DraconidSecondStarter_22:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_EventScript_DraconidSecondStarter_15

RustboroCity_EventScript_DraconidSecondStarter_25:
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_EventScript_DraconidSecondStarter_24


RustboroCity_EventScript_DraconidReceivedSecondStarter::
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_Text_DraconidReceivedMon
	waitmessage
	waitfanfare
	return


RustboroCity_Movement_DraconidBirchApproach:
	walk_up
	walk_left
	walk_up
	face_up
	step_end

RustboroCity_Movement_DraconidBirchLeave:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_EventScript_DraconidSecondStarter_Text_0:
	.string "CHARMANDER$"

RustboroCity_EventScript_DraconidSecondStarter_Text_1:
	.string "TOTODILE$"

RustboroCity_EventScript_DraconidSecondStarter_Text_2:
	.string "TREECKO$"

RustboroCity_Text_DraconidBirchCongrats::
	.string "PROF. BIRCH: {PLAYER}! I watched your\n"
	.string "battle through the window. Your first\l"
	.string "GYM BADGE!\p"
	.string "…But that uniform. And the man you were\n"
	.string "just talking to…\p"
	.string "BRENDAN told me. I didn't want to\n"
	.string "believe him.\p"
	.string "Your ELDER wrote to me before you came\n"
	.string "down the mountain. Draconid tamers\l"
	.string "raise a second partner from a faraway\l"
	.string "land, to learn balance.\p"
	.string "I brought three POKéMON for you. On the\n"
	.string "way here, I nearly turned back.\p"
	.string "But I saw how you protected me on\n"
	.string "ROUTE 101.\p"
	.string "Whatever you're doing… I'll trust that\n"
	.string "version of you. Pick the one you like.$"

RustboroCity_Text_DraconidBirchWhichOne::
	.string "Which POKéMON will you take?$"

RustboroCity_Text_DraconidBirchCharmander::
	.string "CHARMANDER, the Fire-type from KANTO.\n"
	.string "They say the flame on its tail shows its\l"
	.string "spirit.\p"
	.string "Will you take CHARMANDER?$"

RustboroCity_Text_DraconidBirchTotodile::
	.string "TOTODILE, the Water-type from JOHTO.\n"
	.string "It bites anything that moves, even its\l"
	.string "TRAINER!\p"
	.string "Will you take TOTODILE?$"

RustboroCity_Text_DraconidBirchTreecko::
	.string "TREECKO, the Grass-type from right\n"
	.string "here in HOENN. BRENDAN's partner has a\l"
	.string "sibling!\p"
	.string "Will you take TREECKO?$"

RustboroCity_Text_DraconidReceivedMon::
	.string "{PLAYER} received the {STR_VAR_1}\n"
	.string "from PROF. BIRCH!$"

RustboroCity_Text_DraconidBirchBye::
	.string "PROF. BIRCH: Raise it well, alongside\n"
	.string "your dragon.\p"
	.string "And {PLAYER}… be careful. Whatever\n"
	.string "those people want, it isn't good.$"
