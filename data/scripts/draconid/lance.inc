DraconidVillage_EventScript_LanceOnTransition::
	setflag FLAG_TEMP_1E
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_POSTGAME
	goto_if_lt DraconidVillage_EventScript_LanceOnTransition_1
	goto_if_unset FLAG_DRACONID_LANCE_ARMED, DraconidVillage_EventScript_LanceOnTransition_2
	goto_if_set FLAG_HIDE_DRACONID_VILLAGE_LANCE, DraconidVillage_EventScript_LanceOnTransition_3
	return

DraconidVillage_EventScript_LanceOnTransition_1:
	setflag FLAG_HIDE_DRACONID_VILLAGE_LANCE
	return

DraconidVillage_EventScript_LanceOnTransition_2:
	setflag FLAG_DRACONID_LANCE_ARMED
	setflag FLAG_HIDE_DRACONID_VILLAGE_LANCE
	return

DraconidVillage_EventScript_LanceOnTransition_3:
	setvar VAR_TEMP_C, 1
	return


DraconidVillage_EventScript_LanceArrives::
	lockall
	setvar VAR_TEMP_C, 0
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 8
	goto_if_ne DraconidVillage_EventScript_LanceArrives_2
	compare VAR_0x8005, 15
	goto_if_ne DraconidVillage_EventScript_LanceArrives_2
	delay 20
	playmoncry SPECIES_DRAGONITE, CRY_MODE_ENCOUNTER
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	waitmoncry
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	addobject LOCALID_DRACONID_VILLAGE_LANCE_DRAGONITE
	addobject LOCALID_DRACONID_VILLAGE_LANCE
	setobjectxy LOCALID_DRACONID_VILLAGE_LANCE, 13, 11
	playse SE_M_FLY
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_DRAGONITE, DraconidVillage_Movement_LanceFlyDown
	applymovement LOCALID_DRACONID_VILLAGE_LANCE, DraconidVillage_Movement_LanceFlyDown
	waitmovement 0
	clearflag FLAG_HIDE_DRACONID_VILLAGE_LANCE
	playse SE_M_STRENGTH
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_DRAGONITE, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement LOCALID_DRACONID_VILLAGE_LANCE, DraconidVillage_Movement_LanceLeapDown
	waitmovement 0
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	applymovement LOCALID_PLAYER, DraconidVillage_Movement_LancePlayerToSquare
	waitmovement 0
	msgbox DraconidVillage_EventScript_LanceArrives_Text_0
	msgbox DraconidVillage_EventScript_LanceArrives_Text_1
	msgbox DraconidVillage_EventScript_LanceArrives_Text_2
	msgbox DraconidVillage_EventScript_LanceArrives_Text_3
	closemessage
	addobject LOCALID_DRACONID_VILLAGE_LANCE_ELDER
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ELDER, DraconidVillage_Movement_LanceElderArrives
	waitmovement 0
	msgbox DraconidVillage_EventScript_LanceArrives_Text_4
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_LANCE, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox DraconidVillage_EventScript_LanceArrives_Text_5
	msgbox DraconidVillage_EventScript_LanceArrives_Text_6
	msgbox DraconidVillage_EventScript_LanceArrives_Text_7
	msgbox DraconidVillage_EventScript_LanceArrives_Text_8
	msgbox DraconidVillage_EventScript_LanceArrives_Text_9
	msgbox DraconidVillage_EventScript_LanceArrives_Text_10
	msgbox DraconidVillage_EventScript_LanceArrives_Text_11
	msgbox DraconidVillage_EventScript_LanceArrives_Text_12
	msgbox DraconidVillage_EventScript_LanceArrives_Text_13
	closemessage
	addobject LOCALID_DRACONID_VILLAGE_LANCE_ASTER
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ASTER, DraconidVillage_Movement_LanceAsterArrives
	waitmovement 0
	msgbox DraconidVillage_EventScript_LanceArrives_Text_14
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ASTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DRACONID_VILLAGE_LANCE, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox DraconidVillage_EventScript_LanceArrives_Text_15
	msgbox DraconidVillage_EventScript_LanceArrives_Text_16
	msgbox DraconidVillage_EventScript_LanceArrives_Text_17
	msgbox DraconidVillage_EventScript_LanceArrives_Text_18
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_LANCE, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox DraconidVillage_EventScript_LanceArrives_Text_19
	msgbox DraconidVillage_Text_LanceChallenge, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_EventScript_LanceArrives_7
DraconidVillage_EventScript_LanceArrives_6:
	msgbox DraconidVillage_Text_LanceGo
	closemessage
	call DraconidVillage_EventScript_LanceBattle
	msgbox DraconidVillage_Text_LanceBloodRunsHot
	call DraconidVillage_EventScript_LanceGifts
	msgbox DraconidVillage_EventScript_LanceArrives_Text_23
	msgbox DraconidVillage_EventScript_LanceArrives_Text_24
	msgbox DraconidVillage_EventScript_LanceArrives_Text_25
	goto DraconidVillage_EventScript_LanceSceneEnd
	return

DraconidVillage_EventScript_LanceArrives_2:
	releaseall
	end

DraconidVillage_EventScript_LanceArrives_7:
	msgbox DraconidVillage_EventScript_LanceArrives_Text_20
	msgbox DraconidVillage_EventScript_LanceArrives_Text_21
	msgbox DraconidVillage_EventScript_LanceArrives_Text_22
	goto DraconidVillage_EventScript_LanceSceneEnd
	goto DraconidVillage_EventScript_LanceArrives_6


DraconidVillage_EventScript_LanceSceneEnd::
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ASTER, DraconidVillage_Movement_LanceAsterLeaves
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ELDER, DraconidVillage_Movement_LanceElderLeaves
	waitmovement 0
	removeobject LOCALID_DRACONID_VILLAGE_LANCE_ELDER
	removeobject LOCALID_DRACONID_VILLAGE_LANCE_ASTER
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


DraconidVillage_EventScript_Lance::
	lock
	faceplayer
	checktrainerflag TRAINER_LANCE_DRACONID
	goto_if 0, DraconidVillage_EventScript_Lance_2
	goto_if_unset FLAG_RECEIVED_DRAGONINITE, DraconidVillage_EventScript_Lance_5
	msgbox DraconidVillage_EventScript_Lance_Text_3, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_EventScript_Lance_11
	msgbox DraconidVillage_EventScript_Lance_Text_5
	closemessage
	call DraconidVillage_EventScript_LanceBattle
	msgbox DraconidVillage_EventScript_Lance_Text_6
	release
	return

DraconidVillage_EventScript_Lance_2:
	msgbox DraconidVillage_EventScript_Lance_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_EventScript_Lance_8
	msgbox DraconidVillage_Text_LanceGo
	closemessage
	call DraconidVillage_EventScript_LanceBattle
	msgbox DraconidVillage_Text_LanceBloodRunsHot
	call DraconidVillage_EventScript_LanceGifts
	msgbox DraconidVillage_EventScript_Lance_Text_2
	release
	end

DraconidVillage_EventScript_Lance_5:
	call DraconidVillage_EventScript_LanceGifts
	release
	end

DraconidVillage_EventScript_Lance_8:
	msgbox DraconidVillage_EventScript_Lance_Text_1
	release
	end

DraconidVillage_EventScript_Lance_11:
	msgbox DraconidVillage_EventScript_Lance_Text_4
	release
	end


DraconidVillage_EventScript_LanceBattle::
	trainerbattle_no_intro TRAINER_LANCE_DRACONID, DraconidVillage_Text_LanceDefeat
	return


DraconidVillage_EventScript_LanceGifts::
	msgbox DraconidVillage_EventScript_LanceGifts_Text_0
	checkitemspace ITEM_DRAGONINITE
	compare VAR_RESULT, FALSE
	goto_if_eq DraconidVillage_EventScript_LanceGifts_2
	givemon SPECIES_DRATINI, 15, ITEM_NONE, move1 = MOVE_EXTREME_SPEED, move2 = MOVE_TWISTER, move3 = MOVE_THUNDER_WAVE, move4 = MOVE_WRAP
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq DraconidVillage_EventScript_LanceGifts_5
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq DraconidVillage_EventScript_LanceGifts_6
	msgbox gText_NoMoreRoomForPokemon
	msgbox DraconidVillage_Text_LanceComeBack
	return

DraconidVillage_EventScript_LanceGifts_2:
	msgbox gText_TooBadBagIsFull
	msgbox DraconidVillage_Text_LanceComeBack
	return

DraconidVillage_EventScript_LanceGifts_4:
	msgbox DraconidVillage_EventScript_LanceGifts_Text_1
	giveitem ITEM_DRAGONINITE
	msgbox DraconidVillage_EventScript_LanceGifts_Text_2
	setflag FLAG_RECEIVED_DRAGONINITE
	return

DraconidVillage_EventScript_LanceGifts_5:
	call DraconidVillage_EventScript_LanceReceivedDratini
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DraconidVillage_EventScript_LanceGifts_10
	goto DraconidVillage_EventScript_LanceGifts_4

DraconidVillage_EventScript_LanceGifts_6:
	call DraconidVillage_EventScript_LanceReceivedDratini
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DraconidVillage_EventScript_LanceGifts_13
DraconidVillage_EventScript_LanceGifts_12:
	call Common_EventScript_TransferredToPC
	goto DraconidVillage_EventScript_LanceGifts_4

DraconidVillage_EventScript_LanceGifts_10:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto DraconidVillage_EventScript_LanceGifts_4

DraconidVillage_EventScript_LanceGifts_13:
	call Common_EventScript_NameReceivedBoxMon
	goto DraconidVillage_EventScript_LanceGifts_12


DraconidVillage_EventScript_LanceReceivedDratini::
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	playfanfare MUS_OBTAIN_ITEM
	message DraconidVillage_EventScript_LanceReceivedDratini_Text_0
	waitmessage
	waitfanfare
	return


DraconidVillage_EventScript_LanceDragonite::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	msgbox DraconidVillage_EventScript_LanceDragonite_Text_0
	waitmoncry
	msgbox DraconidVillage_EventScript_LanceDragonite_Text_1
	release
	return


DraconidVillage_Movement_LanceFlyDown:
	fly_down
	step_end

DraconidVillage_Movement_LanceLeapDown:
	jump_2_down
	step_end

DraconidVillage_Movement_LancePlayerToSquare:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

DraconidVillage_Movement_LanceElderArrives:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

DraconidVillage_Movement_LanceElderLeaves:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

DraconidVillage_Movement_LanceAsterArrives:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

DraconidVillage_Movement_LanceAsterLeaves:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DraconidVillage_EventScript_LanceArrives_Text_0:
	.string "LANCE: So this is the DRACONID village.\p"
	.string "The falls, the shrine on the cliff…\n"
	.string "It's just like the old stories.$"

DraconidVillage_EventScript_LanceArrives_Text_1:
	.string "LANCE: And you must be {PLAYER}.\p"
	.string "I'm LANCE, the CHAMPION of the POKéMON\n"
	.string "LEAGUE in JOHTO and KANTO.$"

DraconidVillage_EventScript_LanceArrives_Text_2:
	.string "LANCE: News of you has reached as far\n"
	.string "as BLACKTHORN CITY.\p"
	.string "They say a young DRACONID wore\n"
	.string "TEAM MAGMA's red for the clan's sake.\p"
	.string "And that when the titans of land and\n"
	.string "sea woke, you held your ground.$"

DraconidVillage_EventScript_LanceArrives_Text_3:
	.string "LANCE: They even say you stood beside\n"
	.string "RAYQUAZA when the sky split open.\p"
	.string "My DRAGONITE and I flew a long way to\n"
	.string "see if it was true.$"

DraconidVillage_EventScript_LanceArrives_Text_4:
	.string "ELDER: A DRAGONITE, landing\n"
	.string "in our village…$"

DraconidVillage_EventScript_LanceArrives_Text_5:
	.string "ELDER: Few travellers find this valley,\n"
	.string "and fewer still come on the wind.\p"
	.string "Who are you, young man?$"

DraconidVillage_EventScript_LanceArrives_Text_6:
	.string "LANCE: Forgive me for dropping in\n"
	.string "like this, ELDER.\p"
	.string "My name is LANCE. I come from the\n"
	.string "dragon clan of BLACKTHORN.$"

DraconidVillage_EventScript_LanceArrives_Text_7:
	.string "LANCE: Our clan's elder tells\n"
	.string "an old story.\p"
	.string "Long ago, our ancestors lived in the\n"
	.string "south, below the sky dragon's shrine.$"

DraconidVillage_EventScript_LanceArrives_Text_8:
	.string "LANCE: Then some of them followed their\n"
	.string "dragons north across the sea.\p"
	.string "They settled under a black mountain,\n"
	.string "and that became BLACKTHORN.$"

DraconidVillage_EventScript_LanceArrives_Text_9:
	.string "LANCE: At our shrine, the elders still\n"
	.string "call us by an old name…\p"
	.string "The NORTHERN WING.$"

DraconidVillage_EventScript_LanceArrives_Text_10:
	.string "ELDER: …The NORTHERN WING.$"

DraconidVillage_EventScript_LanceArrives_Text_11:
	.string "ELDER: Our songs remember you.\p"
	.string "“One wing stayed to guard the sky. One\n"
	.string "wing flew north, and did not come back.”$"

DraconidVillage_EventScript_LanceArrives_Text_12:
	.string "ELDER: We have sung that verse for\n"
	.string "generations, and wondered.\p"
	.string "The NORTHERN WING has come home.\n"
	.string "Welcome, LANCE.$"

DraconidVillage_EventScript_LanceArrives_Text_13:
	.string "LANCE: Our elder would give anything to\n"
	.string "hear that song.$"

DraconidVillage_EventScript_LanceArrives_Text_14:
	.string "ASTER: ELDER! Did you see that\n"
	.string "DRAGONITE? It landed right in the…$"

DraconidVillage_EventScript_LanceArrives_Text_15:
	.string "ASTER: LANCE? The DRAGON MASTER of\n"
	.string "BLACKTHORN? Here?!$"

DraconidVillage_EventScript_LanceArrives_Text_16:
	.string "ELDER: He is of the NORTHERN WING,\n"
	.string "ASTER. Family, from far away.$"

DraconidVillage_EventScript_LanceArrives_Text_17:
	.string "ASTER: …Family. Hmph. Of course the\n"
	.string "famous LANCE turns out to be one of us.$"

DraconidVillage_EventScript_LanceArrives_Text_18:
	.string "ASTER: Riddle: what flies across the\n"
	.string "sea to battle someone it has never met?\p"
	.string "A show-off. You're here for {PLAYER},\n"
	.string "aren't you?$"

DraconidVillage_EventScript_LanceArrives_Text_19:
	.string "LANCE: Ha! She's got me.\p"
	.string "A dragon master can't hear a story like\n"
	.string "that and not see it for himself.$"

DraconidVillage_EventScript_LanceArrives_Text_20:
	.string "LANCE: Not yet? Fair enough. A tamer\n"
	.string "should choose the time.\p"
	.string "My DRAGONITE could use a rest after\n"
	.string "that flight. I'll wait here.$"

DraconidVillage_EventScript_LanceArrives_Text_21:
	.string "ELDER: Stay as long as you wish, LANCE.\n"
	.string "This village is yours as much as ours.$"

DraconidVillage_EventScript_LanceArrives_Text_22:
	.string "ASTER: Hmph. Then I'll battle\n"
	.string "him myself!\p"
	.string "…After some more training.$"

DraconidVillage_EventScript_LanceArrives_Text_23:
	.string "ELDER: Both wings of the clan, meeting\n"
	.string "in battle at last.\p"
	.string "The old songs never\n"
	.string "dared hope for this.$"

DraconidVillage_EventScript_LanceArrives_Text_24:
	.string "ASTER: …Okay. I'm next.\p"
	.string "Don't you dare fly off before I get my\n"
	.string "turn, LANCE.$"

DraconidVillage_EventScript_LanceArrives_Text_25:
	.string "LANCE: Ha ha! I'm not going anywhere\n"
	.string "just yet.\p"
	.string "{PLAYER}, come and battle me whenever\n"
	.string "you like.$"

DraconidVillage_EventScript_Lance_Text_0:
	.string "LANCE: {PLAYER}! Ready to show me the\n"
	.string "tamer RAYQUAZA chose?$"

DraconidVillage_EventScript_Lance_Text_1:
	.string "LANCE: Take your time.\n"
	.string "I'm enjoying the view.$"

DraconidVillage_EventScript_Lance_Text_2:
	.string "LANCE: Come and battle me whenever you\n"
	.string "like, {PLAYER}. I'll be here a while.$"

DraconidVillage_EventScript_Lance_Text_3:
	.string "LANCE: My dragons are still fired up\n"
	.string "from our last battle.\p"
	.string "How about another round?$"

DraconidVillage_EventScript_Lance_Text_4:
	.string "LANCE: The ELDER is teaching me the old\n"
	.string "songs. I'll be here a while.$"

DraconidVillage_EventScript_Lance_Text_5:
	.string "LANCE: Then let's go! DRAGONITE and I\n"
	.string "won't hold back!$"

DraconidVillage_EventScript_Lance_Text_6:
	.string "LANCE: Ha! Every battle with you\n"
	.string "teaches me something new.$"

DraconidVillage_EventScript_LanceGifts_Text_0:
	.string "LANCE: A tamer who earns our clan's\n"
	.string "respect receives a DRATINI.\p"
	.string "I brought one from the DRAGON'S DEN, in\n"
	.string "case the stories were true.$"

DraconidVillage_EventScript_LanceGifts_Text_1:
	.string "LANCE: And take this, too.$"

DraconidVillage_EventScript_LanceGifts_Text_2:
	.string "LANCE: That's a DRAGONINITE, a MEGA\n"
	.string "STONE.\p"
	.string "Raise your DRATINI into a DRAGONITE,\n"
	.string "and the two of you can MEGA EVOLVE.$"

DraconidVillage_EventScript_LanceReceivedDratini_Text_0:
	.string "{PLAYER} received a DRATINI from LANCE!$"

DraconidVillage_EventScript_LanceDragonite_Text_0:
	.string "DRAGONITE: Grooh!$"

DraconidVillage_EventScript_LanceDragonite_Text_1:
	.string "LANCE's DRAGONITE is gazing up at the\n"
	.string "cliffs, as if it remembers them.$"

DraconidVillage_Text_LanceChallenge::
	.string "LANCE: {PLAYER}! As a CHAMPION, and as a\n"
	.string "DRACONID of the NORTHERN WING…\p"
	.string "I, LANCE the dragon master, challenge\n"
	.string "you! Will you battle me?$"

DraconidVillage_Text_LanceGo::
	.string "LANCE: That's the spirit! Show me the\n"
	.string "tamer RAYQUAZA chose!$"

DraconidVillage_Text_LanceDefeat::
	.string "…It's over. The stories didn't\n"
	.string "do you justice.$"

DraconidVillage_Text_LanceBloodRunsHot::
	.string "LANCE: It's been a long time since a\n"
	.string "battle made my blood run this hot.$"

DraconidVillage_Text_LanceComeBack::
	.string "LANCE: Come back when you have room.\n"
	.string "I'll hold on to my gifts until then.$"
