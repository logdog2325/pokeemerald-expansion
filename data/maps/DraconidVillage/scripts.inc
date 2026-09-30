DraconidVillage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DraconidVillage_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_DRACONID_STATE, DRACONID_STATE_EGG_HATCHED, DraconidVillage_EventScript_RunningShoes
	.2byte 0


DraconidVillage_OnTransition::
	setflag FLAG_VISITED_DRACONID_VILLAGE
	compare VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	goto_if_ge DraconidVillage_OnTransition_1
	return

DraconidVillage_OnTransition_1:
	setvar VAR_TEMP_1, 1
	return


DraconidVillage_EventScript_RunningShoes::
	lockall
	addobject LOCALID_DRACONID_VILLAGE_SHOES_GIVER
	applymovement LOCALID_DRACONID_VILLAGE_SHOES_GIVER, DraconidVillage_Movement_ShoesGiverApproach
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DraconidVillage_EventScript_RunningShoes_Text_0
	playfanfare MUS_OBTAIN_ITEM
	message DraconidVillage_EventScript_RunningShoes_Text_1
	waitfanfare
	waitmessage
	msgbox DraconidVillage_EventScript_RunningShoes_Text_2
	closemessage
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	applymovement LOCALID_DRACONID_VILLAGE_SHOES_GIVER, DraconidVillage_Movement_ShoesGiverLeave
	waitmovement 0
	removeobject LOCALID_DRACONID_VILLAGE_SHOES_GIVER
	setvar VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	setvar VAR_TEMP_1, 1
	releaseall
	return


DraconidVillage_Movement_ShoesGiverApproach:
	walk_up
	step_end

DraconidVillage_Movement_ShoesGiverLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

DraconidVillage_EventScript_GatekeeperStop::
	lockall
	applymovement LOCALID_DRACONID_GATEKEEPER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	compare VAR_DRACONID_STATE, DRACONID_STATE_EGG_RECEIVED
	goto_if_lt DraconidVillage_EventScript_GatekeeperStop_2
	msgbox DraconidVillage_EventScript_GatekeeperStop_Text_1
DraconidVillage_EventScript_GatekeeperStop_1:
	closemessage
	applymovement LOCALID_PLAYER, DraconidVillage_Movement_PushBack
	waitmovement 0
	releaseall
	return

DraconidVillage_EventScript_GatekeeperStop_2:
	msgbox DraconidVillage_EventScript_GatekeeperStop_Text_0
	goto DraconidVillage_EventScript_GatekeeperStop_1


DraconidVillage_Movement_PushBack:
	walk_up
	step_end

DraconidVillage_EventScript_Gatekeeper::
	lock
	faceplayer
	compare VAR_DRACONID_STATE, DRACONID_STATE_READY_TO_LEAVE
	goto_if_lt DraconidVillage_EventScript_Gatekeeper_2
	msgbox DraconidVillage_EventScript_Gatekeeper_Text_1
DraconidVillage_EventScript_Gatekeeper_1:
	release
	return

DraconidVillage_EventScript_Gatekeeper_2:
	msgbox DraconidVillage_EventScript_Gatekeeper_Text_0
	goto DraconidVillage_EventScript_Gatekeeper_1


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
	msgbox DraconidVillage_EventScript_PondWoman_Text_0, MSGBOX_NPC
	return


DraconidVillage_EventScript_Boy::
	msgbox DraconidVillage_EventScript_Boy_Text_0, MSGBOX_NPC
	return


DraconidVillage_EventScript_VillageSign::
	msgbox DraconidVillage_EventScript_VillageSign_Text_0, MSGBOX_SIGN
	return


DraconidVillage_EventScript_PlayersHouseSign::
	msgbox DraconidVillage_EventScript_PlayersHouseSign_Text_0, MSGBOX_SIGN
	return


DraconidVillage_EventScript_RunningShoes_Text_0:
	.string "OLD WOMAN: So the egg answered the sky.\n"
	.string "Let me see… Oh, what a bright little\l"
	.string "dragon!\p"
	.string "The ELDER told us all. You're going down\n"
	.string "to the lowlands, alone, and in secret.\p"
	.string "Then you'll need to move fast. Take\n"
	.string "these. Every tamer who leaves this\l"
	.string "village gets a pair.$"

DraconidVillage_EventScript_RunningShoes_Text_1:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

DraconidVillage_EventScript_RunningShoes_Text_2:
	.string "OLD WOMAN: Hold the B Button to run\n"
	.string "with them!\p"
	.string "Cross the bridge on DRACONID PASS and\n"
	.string "head east to ROUTE 101. LITTLEROOT is\l"
	.string "just south of it.\p"
	.string "Your house will be waiting when you need\n"
	.string "a rest. The whole village will.$"

DraconidVillage_EventScript_GatekeeperStop_Text_0:
	.string "GATEKEEPER: Whoa there, {PLAYER}! Isn't\n"
	.string "today your egg ceremony?\p"
	.string "The ELDER is waiting for you. You can't\n"
	.string "leave the village without a partner!$"

DraconidVillage_EventScript_GatekeeperStop_Text_1:
	.string "GATEKEEPER: That egg needs the\n"
	.string "shrine's blessing before it can hatch.\p"
	.string "Go on up to the shrine in the cliff!$"

DraconidVillage_EventScript_Gatekeeper_Text_0:
	.string "GATEKEEPER: Beyond this path lies\n"
	.string "DRACONID PASS, and past the river, the\l"
	.string "lowlands.\p"
	.string "Wild Pokémon live out there. Only tamers\n"
	.string "with a partner may pass.$"

DraconidVillage_EventScript_Gatekeeper_Text_1:
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
	.string "The water here comes from the peaks,\n"
	.string "where the sky dragon is said to rest.\p"
	.string "Drinking it is supposed to make dragons\n"
	.string "grow strong!$"

DraconidVillage_EventScript_Boy_Text_0:
	.string "When I get my egg, I want a dragon that\n"
	.string "can fly all the way up to the sky!$"

DraconidVillage_EventScript_VillageSign_Text_0:
	.string "DRACONID VILLAGE\n"
	.string "“Where the clan keeps the sky.”$"

DraconidVillage_EventScript_PlayersHouseSign_Text_0:
	.string "{PLAYER}'s house$"
