RustboroCity_Gym_EventScript_DraconidOakWaits::
	compare VAR_DRACONID_STATE, DRACONID_STATE_LEFT_VILLAGE
	goto_if_eq RustboroCity_Gym_EventScript_DraconidOakWaits_1
	return

RustboroCity_Gym_EventScript_DraconidOakWaits_1:
	setvar VAR_DRACONID_STATE, DRACONID_STATE_SECOND_STARTER
	clearflag FLAG_HIDE_RUSTBORO_CITY_OAK
	clearflag FLAG_HIDE_RUSTBORO_CITY_TABITHA
	return


RustboroCity_EventScript_DraconidSecondStarter::
	lockall
	call RustboroCity_EventScript_DraconidTabithaOrders
	applymovement LOCALID_RUSTBORO_OAK, RustboroCity_Movement_DraconidOakApproach
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox RustboroCity_Text_DraconidOakHello, MSGBOX_DEFAULT
	msgbox RustboroCity_Text_DraconidOakUniform, MSGBOX_DEFAULT
	msgbox RustboroCity_Text_DraconidOakGift, MSGBOX_DEFAULT
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
	msgbox RustboroCity_Text_DraconidOakBye, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RUSTBORO_OAK, RustboroCity_Movement_DraconidOakLeave
	waitmovement 0
	removeobject LOCALID_RUSTBORO_OAK
	setflag FLAG_HIDE_RUSTBORO_CITY_OAK
	releaseall
	return

RustboroCity_EventScript_DraconidSecondStarter_3:
	message RustboroCity_Text_DraconidOakWhichOne
	waitmessage
	dynmultichoice 18, 1, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, RustboroCity_EventScript_DraconidSecondStarter_Text_0, RustboroCity_EventScript_DraconidSecondStarter_Text_1, RustboroCity_EventScript_DraconidSecondStarter_Text_2
	switch VAR_RESULT
	case 0, RustboroCity_EventScript_DraconidSecondStarter_12
	case 1, RustboroCity_EventScript_DraconidSecondStarter_13
	setvar VAR_0x8009, SECOND_STARTER_TREECKO
	msgbox RustboroCity_Text_DraconidOakTreecko, MSGBOX_YESNO
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
	msgbox RustboroCity_Text_DraconidOakCharmander, MSGBOX_YESNO
	goto RustboroCity_EventScript_DraconidSecondStarter_10

RustboroCity_EventScript_DraconidSecondStarter_13:
	setvar VAR_0x8009, SECOND_STARTER_TOTODILE
	msgbox RustboroCity_Text_DraconidOakTotodile, MSGBOX_YESNO
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


RustboroCity_Movement_DraconidOakApproach:
	walk_up
	walk_left
	walk_up
	face_up
	step_end

RustboroCity_Movement_DraconidOakLeave:
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

RustboroCity_Text_DraconidOakHello::
	.string "PROF. OAK: Ah, {PLAYER}! So you're the\n"
	.string "young dragon tamer BIRCH told me\l"
	.string "about!\p"
	.string "I'm OAK. I study POKéMON in PALLET TOWN,\n"
	.string "far away in KANTO.\p"
	.string "I'm in HOENN visiting my old friend\n"
	.string "BIRCH. And I watched your GYM battle\l"
	.string "through the window. Splendid!$"

RustboroCity_Text_DraconidOakUniform::
	.string "PROF. OAK: …And that red uniform. Ahem.\n"
	.string "Yes.\p"
	.string "Your ELDER's letter told BIRCH why you\n"
	.string "wear it. BIRCH needed my help with your\l"
	.string "second partner, so he told me.\p"
	.string "Nobody else knows, mind you.\n"
	.string "Your secret is safe with two old men!\p"
	.string "BRENDAN came home terribly upset about\n"
	.string "it. He doesn't know, and for now he\l"
	.string "mustn't.\p"
	.string "It won't be easy, letting your friends\n"
	.string "think the worst of you. But your dragon\l"
	.string "knows your heart.\p"
	.string "That's good enough for me!$"

RustboroCity_Text_DraconidOakGift::
	.string "PROF. OAK: Now then! Your ELDER wrote\n"
	.string "to BIRCH before you came down the\l"
	.string "mountain.\p"
	.string "Draconid tamers raise a second partner\n"
	.string "from a faraway land, to learn balance.\p"
	.string "So I brought three POKéMON with me,\n"
	.string "each from a land I know well. Go on,\l"
	.string "choose!$"

RustboroCity_Text_DraconidOakWhichOne::
	.string "Which POKéMON will you take?$"

RustboroCity_Text_DraconidOakCharmander::
	.string "CHARMANDER, the Fire-type from my\n"
	.string "home, KANTO. The flame on its tail shows\l"
	.string "how it feels.\p"
	.string "Will you take CHARMANDER?$"

RustboroCity_Text_DraconidOakTotodile::
	.string "TOTODILE, the Water-type from JOHTO.\n"
	.string "It bites anything that moves. Even its\l"
	.string "TRAINER!\p"
	.string "Will you take TOTODILE?$"

RustboroCity_Text_DraconidOakTreecko::
	.string "TREECKO, the Grass-type from right\n"
	.string "here in HOENN. BIRCH picked it out\l"
	.string "himself.\p"
	.string "Will you take TREECKO?$"

RustboroCity_Text_DraconidReceivedMon::
	.string "{PLAYER} received the {STR_VAR_1}\n"
	.string "from PROF. OAK!$"

RustboroCity_Text_DraconidOakBye::
	.string "PROF. OAK: Raise it well, side by side\n"
	.string "with your dragon. POKéMON and people\l"
	.string "grow strong together.\p"
	.string "The other two? I'm leaving them\n"
	.string "at DEVON's front desk.\p"
	.string "Your ELDER wrote that a friend of your\n"
	.string "clan would call for one. I didn't ask!\p"
	.string "And {PLAYER}… don't let that uniform\n"
	.string "change who you are.\p"
	.string "Well! BIRCH is waiting for me at DEVON.\n"
	.string "Take care, now!$"
