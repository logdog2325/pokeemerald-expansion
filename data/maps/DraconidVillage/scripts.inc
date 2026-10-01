DraconidVillage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DraconidVillage_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_DRACONID_STATE, DRACONID_STATE_EGG_HATCHED, DraconidVillage_EventScript_RunningShoes
	map_script_2 VAR_TEMP_2, 1, DraconidVillage_EventScript_DraconidArrival
	map_script_2 VAR_TEMP_2, 3, DraconidVillage_EventScript_DraconidFinalIntro
	map_script_2 VAR_TEMP_2, 4, DraconidVillage_EventScript_DraconidGoodbyes
	map_script_2 VAR_TEMP_C, 1, DraconidVillage_EventScript_LanceArrives
	.2byte 0


DraconidVillage_OnTransition::
	setflag FLAG_VISITED_DRACONID_VILLAGE
	compare VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	goto_if_ge DraconidVillage_OnTransition_2
DraconidVillage_OnTransition_1:
	call Draconid_EventScript_FinaleWeather
	call DraconidVillage_EventScript_DraconidAttackOnTransition
	call DraconidVillage_EventScript_LanceOnTransition
	call DraconidVillage_EventScript_DraconidRivalsOnTransition
	call DraconidVillage_EventScript_DrakeOnTransition
	return

DraconidVillage_OnTransition_2:
	setvar VAR_TEMP_1, 1
	goto DraconidVillage_OnTransition_1


DraconidVillage_EventScript_EggHatch::
	lockall
	msgbox DraconidVillage_EventScript_EggHatch_Text_0
	closemessage
	setvar VAR_0x8004, 0
	special EggHatch
	setvar VAR_0x8004, 0
	special DraconidRaiseHatchling
	setflag FLAG_DRACONID_EGG_HATCHED
	clearflag FLAG_HIDE_DRACONID_VILLAGE_SHOES_GIVER
	setvar VAR_DRACONID_STATE, DRACONID_STATE_EGG_HATCHED
	releaseall
	return


DraconidVillage_EventScript_RunningShoes::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	specialvar VAR_0x8006, GetPlayerFacingDirection
	switch VAR_0x8006
	case DIR_NORTH, DraconidVillage_EventScript_RunningShoes_3
	case DIR_SOUTH, DraconidVillage_EventScript_RunningShoes_4
	case DIR_WEST, DraconidVillage_EventScript_RunningShoes_5
	subvar VAR_0x8004, 1
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_SHOES_GIVER, MOVEMENT_TYPE_FACE_RIGHT
DraconidVillage_EventScript_RunningShoes_1:
	setobjectxyperm LOCALID_DRACONID_VILLAGE_SHOES_GIVER, VAR_0x8004, VAR_0x8005
	msgbox DraconidVillage_EventScript_RunningShoes_Text_0
	closemessage
	addobject LOCALID_DRACONID_VILLAGE_SHOES_GIVER
	switch VAR_0x8006
	case DIR_NORTH, DraconidVillage_EventScript_RunningShoes_9
	case DIR_SOUTH, DraconidVillage_EventScript_RunningShoes_10
	case DIR_WEST, DraconidVillage_EventScript_RunningShoes_11
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
DraconidVillage_EventScript_RunningShoes_7:
	waitmovement 0
	msgbox DraconidVillage_EventScript_RunningShoes_Text_1
	playfanfare MUS_OBTAIN_ITEM
	message DraconidVillage_EventScript_RunningShoes_Text_2
	waitfanfare
	waitmessage
	msgbox DraconidVillage_EventScript_RunningShoes_Text_3
	closemessage
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setflag FLAG_HIDE_DRACONID_VILLAGE_SHOES_GIVER
	setvar VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	setvar VAR_TEMP_1, 1
	releaseall
	return

DraconidVillage_EventScript_RunningShoes_3:
	addvar VAR_0x8005, 1
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_SHOES_GIVER, MOVEMENT_TYPE_FACE_UP
	goto DraconidVillage_EventScript_RunningShoes_1

DraconidVillage_EventScript_RunningShoes_4:
	subvar VAR_0x8005, 1
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_SHOES_GIVER, MOVEMENT_TYPE_FACE_DOWN
	goto DraconidVillage_EventScript_RunningShoes_1

DraconidVillage_EventScript_RunningShoes_5:
	addvar VAR_0x8004, 1
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_SHOES_GIVER, MOVEMENT_TYPE_FACE_LEFT
	goto DraconidVillage_EventScript_RunningShoes_1

DraconidVillage_EventScript_RunningShoes_9:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	goto DraconidVillage_EventScript_RunningShoes_7

DraconidVillage_EventScript_RunningShoes_10:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	goto DraconidVillage_EventScript_RunningShoes_7

DraconidVillage_EventScript_RunningShoes_11:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	goto DraconidVillage_EventScript_RunningShoes_7


DraconidVillage_EventScript_ShoesGiver::
	msgbox DraconidVillage_EventScript_ShoesGiver_Text_0, MSGBOX_NPC
	return


DraconidVillage_EventScript_GatekeeperStop::
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_ALARM
	goto_if_ge DraconidVillage_EventScript_GatekeeperStop_3
DraconidVillage_EventScript_GatekeeperStop_1:
	lockall
	applymovement LOCALID_DRACONID_GATEKEEPER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	compare VAR_DRACONID_STATE, DRACONID_STATE_EGG_RECEIVED
	goto_if_lt DraconidVillage_EventScript_GatekeeperStop_7
	msgbox DraconidVillage_EventScript_GatekeeperStop_Text_1
DraconidVillage_EventScript_GatekeeperStop_6:
	closemessage
	applymovement LOCALID_PLAYER, DraconidVillage_Movement_PushBack
	waitmovement 0
	releaseall
	return

DraconidVillage_EventScript_GatekeeperStop_2:
	goto DraconidVillage_EventScript_DraconidGatekeeperAttack
	goto DraconidVillage_EventScript_GatekeeperStop_1

DraconidVillage_EventScript_GatekeeperStop_3:
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_SAVED
	goto_if_lt DraconidVillage_EventScript_GatekeeperStop_2
	goto DraconidVillage_EventScript_GatekeeperStop_1

DraconidVillage_EventScript_GatekeeperStop_7:
	msgbox DraconidVillage_EventScript_GatekeeperStop_Text_0
	goto DraconidVillage_EventScript_GatekeeperStop_6


DraconidVillage_Movement_PushBack:
	walk_up
	step_end

DraconidVillage_EventScript_Gatekeeper::
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_ALARM
	goto_if_ge DraconidVillage_EventScript_Gatekeeper_3
DraconidVillage_EventScript_Gatekeeper_1:
	lock
	faceplayer
	compare VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	goto_if_lt DraconidVillage_EventScript_Gatekeeper_7
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_EventScript_Gatekeeper_8
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DraconidVillage_EventScript_Gatekeeper_9
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq DraconidVillage_EventScript_Gatekeeper_10
	msgbox DraconidVillage_EventScript_Gatekeeper_Text_4
DraconidVillage_EventScript_Gatekeeper_6:
	release
	return

DraconidVillage_EventScript_Gatekeeper_2:
	goto DraconidVillage_EventScript_DraconidGatekeeperTalk
	goto DraconidVillage_EventScript_Gatekeeper_1

DraconidVillage_EventScript_Gatekeeper_3:
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_SAVED
	goto_if_lt DraconidVillage_EventScript_Gatekeeper_2
	goto DraconidVillage_EventScript_Gatekeeper_1

DraconidVillage_EventScript_Gatekeeper_7:
	msgbox DraconidVillage_EventScript_Gatekeeper_Text_0
	goto DraconidVillage_EventScript_Gatekeeper_6

DraconidVillage_EventScript_Gatekeeper_8:
	msgbox DraconidVillage_EventScript_Gatekeeper_Text_1
	goto DraconidVillage_EventScript_Gatekeeper_6

DraconidVillage_EventScript_Gatekeeper_9:
	msgbox DraconidVillage_EventScript_Gatekeeper_Text_2
	goto DraconidVillage_EventScript_Gatekeeper_6

DraconidVillage_EventScript_Gatekeeper_10:
	msgbox DraconidVillage_EventScript_Gatekeeper_Text_3
	goto DraconidVillage_EventScript_Gatekeeper_6


DraconidVillage_EventScript_Apprentice::
	msgbox DraconidVillage_EventScript_Apprentice_Text_0, MSGBOX_NPC
	return


DraconidVillage_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DRACONID_EGG_HATCHED, DraconidVillage_EventScript_OldWoman_2
	msgbox DraconidVillage_EventScript_OldWoman_Text_1
DraconidVillage_EventScript_OldWoman_1:
	release
	return

DraconidVillage_EventScript_OldWoman_2:
	msgbox DraconidVillage_EventScript_OldWoman_Text_0
	goto DraconidVillage_EventScript_OldWoman_1


DraconidVillage_EventScript_PondWoman::
	lock
	faceplayer
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_EventScript_PondWoman_2
	msgbox DraconidVillage_EventScript_PondWoman_Text_1
DraconidVillage_EventScript_PondWoman_1:
	release
	return

DraconidVillage_EventScript_PondWoman_2:
	msgbox DraconidVillage_EventScript_PondWoman_Text_0
	goto DraconidVillage_EventScript_PondWoman_1


DraconidVillage_EventScript_Boy::
	lock
	faceplayer
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_EventScript_Boy_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq DraconidVillage_EventScript_Boy_3
	msgbox DraconidVillage_EventScript_Boy_Text_2
DraconidVillage_EventScript_Boy_1:
	release
	return

DraconidVillage_EventScript_Boy_2:
	msgbox DraconidVillage_EventScript_Boy_Text_0
	goto DraconidVillage_EventScript_Boy_1

DraconidVillage_EventScript_Boy_3:
	msgbox DraconidVillage_EventScript_Boy_Text_1
	goto DraconidVillage_EventScript_Boy_1


DraconidVillage_EventScript_VillageSign::
	msgbox DraconidVillage_EventScript_VillageSign_Text_0, MSGBOX_SIGN
	return


DraconidVillage_EventScript_PlayersHouseSign::
	msgbox DraconidVillage_EventScript_PlayersHouseSign_Text_0, MSGBOX_SIGN
	return


DraconidVillage_EventScript_EggHatch_Text_0:
	.string "Oh?\p"
	.string "The egg is moving!$"

DraconidVillage_EventScript_RunningShoes_Text_0:
	.string "OLD WOMAN: Oh, my! Was that a dragon's\n"
	.string "cry I heard?$"

DraconidVillage_EventScript_RunningShoes_Text_1:
	.string "OLD WOMAN: So the egg answered the sky.\n"
	.string "Let me see… Oh, what a bright little\l"
	.string "dragon!\p"
	.string "The ELDER told us all. You're going down\n"
	.string "to the lowlands, alone, and in secret.\p"
	.string "Then you'll need to move fast. Take\n"
	.string "these. Every tamer who leaves this\l"
	.string "village gets a pair.$"

DraconidVillage_EventScript_RunningShoes_Text_2:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

DraconidVillage_EventScript_RunningShoes_Text_3:
	.string "OLD WOMAN: Hold the B Button to run\n"
	.string "with them!\p"
	.string "Cross the bridge on DRACONID PASS and\n"
	.string "head east to ROUTE 101. LITTLEROOT is\l"
	.string "just south of it.\p"
	.string "Your house will be waiting when you need\n"
	.string "a rest. The whole village will.$"

DraconidVillage_EventScript_ShoesGiver_Text_0:
	.string "OLD WOMAN: Hold the B Button to run!\p"
	.string "Cross the bridge on DRACONID PASS and\n"
	.string "head east to ROUTE 101.$"

DraconidVillage_EventScript_GatekeeperStop_Text_0:
	.string "GATEKEEPER: Whoa there, {PLAYER}! Isn't\n"
	.string "today your egg ceremony?\p"
	.string "The ELDER is waiting for you. You can't\n"
	.string "leave the village without a partner!$"

DraconidVillage_EventScript_GatekeeperStop_Text_1:
	.string "GATEKEEPER: That egg of yours is about\n"
	.string "to hatch, {PLAYER}!\p"
	.string "Stay in the village until it does. The\n"
	.string "lowlands are no place for an egg.$"

DraconidVillage_EventScript_Gatekeeper_Text_0:
	.string "GATEKEEPER: Beyond this path lies\n"
	.string "DRACONID PASS, and past the river, the\l"
	.string "lowlands.\p"
	.string "Wild Pokémon live out there. Only tamers\n"
	.string "with a partner may pass.$"

DraconidVillage_EventScript_Gatekeeper_Text_1:
	.string "GATEKEEPER: They came up my path in\n"
	.string "the dark, and I couldn't hold them. You\l"
	.string "did.\p"
	.string "The gate is yours, CHAMPION. Come home\n"
	.string "whenever you like.$"

DraconidVillage_EventScript_Gatekeeper_Text_2:
	.string "GATEKEEPER: …Is that you under the red\n"
	.string "hood, {PLAYER}?\p"
	.string "The ELDER said you'd come home looking\n"
	.string "like one of them. The gate is still\l"
	.string "yours.$"

DraconidVillage_EventScript_Gatekeeper_Text_3:
	.string "GATEKEEPER: The hero of SOOTOPOLIS, at\n"
	.string "my gate!\p"
	.string "I'll never tell the young ones you once\n"
	.string "dressed like a MAGMA grunt.$"

DraconidVillage_EventScript_Gatekeeper_Text_4:
	.string "GATEKEEPER: So you're off to see the\n"
	.string "lowlands! The clan's blessings go with\l"
	.string "you.\p"
	.string "Follow the path over the bridge and\n"
	.string "head east to ROUTE 101. LITTLEROOT\l"
	.string "TOWN is south of there.$"

DraconidVillage_EventScript_Apprentice_Text_0:
	.string "That crater was made by the star that\n"
	.string "fell here long ago.\p"
	.string "The clan's KEY STONES were carved from\n"
	.string "its heart. Only the ELDER may give one\l"
	.string "away.$"

DraconidVillage_EventScript_OldWoman_Text_0:
	.string "A dragon raised from the egg never\n"
	.string "forgets the face it saw first.\p"
	.string "Be good to your little one.$"

DraconidVillage_EventScript_OldWoman_Text_1:
	.string "Every child of the clan receives a\n"
	.string "dragon egg when they come of age.\p"
	.string "I was your age when I received mine.\n"
	.string "Seems like only yesterday…$"

DraconidVillage_EventScript_PondWoman_Text_0:
	.string "KYOGRE sat right there in our pool, as\n"
	.string "big as a house!\p"
	.string "The water's still cloudy. I'm not\n"
	.string "drinking a drop of it until it clears.$"

DraconidVillage_EventScript_PondWoman_Text_1:
	.string "The water here comes from the peaks,\n"
	.string "where the sky dragon is said to rest.\p"
	.string "Drinking it is supposed to make dragons\n"
	.string "grow strong!$"

DraconidVillage_EventScript_Boy_Text_0:
	.string "I saw a GROUDON and a KYOGRE, and\n"
	.string "RAYQUAZA too!\p"
	.string "Nobody down in the lowlands is ever\n"
	.string "going to believe me.$"

DraconidVillage_EventScript_Boy_Text_1:
	.string "Why are you dressed like the bad\n"
	.string "lowlanders?\p"
	.string "…It's a trick, isn't it! I won't tell\n"
	.string "anyone!$"

DraconidVillage_EventScript_Boy_Text_2:
	.string "When I get my egg, I want a dragon that\n"
	.string "can fly all the way up to the sky!$"

DraconidVillage_EventScript_VillageSign_Text_0:
	.string "DRACONID VILLAGE\n"
	.string "“Where the clan keeps the sky.”$"

DraconidVillage_EventScript_PlayersHouseSign_Text_0:
	.string "{PLAYER}'s house$"
