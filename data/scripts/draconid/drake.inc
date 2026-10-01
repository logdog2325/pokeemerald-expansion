EverGrandeCity_DrakesRoom_EventScript_DraconidIntro::
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_SAVED
	goto_if_ge EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_1
	goto_if_set FLAG_DRACONID_DRAKE_TOLD, EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_2
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_4
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_5
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_6
	return

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_1:
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_0
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_1
	return

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_2:
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_2
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_3
	return


EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle::
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_SAVED
	goto_if_ge EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_1
	goto_if_set FLAG_DRACONID_DRAKE_TOLD, EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_2
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_2
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_3
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_4
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_5
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_6
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_7
	setflag FLAG_DRACONID_DRAKE_TOLD
	return

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_1:
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_0
	return

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_2:
	msgbox EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_1
	return


DraconidVillage_EventScript_DrakeOnTransition::
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_FINAL
	goto_if_eq DraconidVillage_EventScript_DrakeOnTransition_1
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_SAVED
	goto_if_lt DraconidVillage_EventScript_DrakeOnTransition_2
	return

DraconidVillage_EventScript_DrakeOnTransition_1:
	setobjectxyperm LOCALID_DRACONID_VILLAGE_DRAKE, 19, 7
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_DRAKE, MOVEMENT_TYPE_FACE_DOWN
	setobjectxyperm LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE, 19, 9
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE, MOVEMENT_TYPE_FACE_LEFT
	setobjectxyperm LOCALID_DRACONID_VILLAGE_MAXIE, 17, 8
	setobjectxyperm LOCALID_DRACONID_VILLAGE_ARCHIE, 21, 8
	return

DraconidVillage_EventScript_DrakeOnTransition_2:
	setflag FLAG_TEMP_1F
	return


DraconidVillage_EventScript_DrakeComesHome::
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, DraconidVillage_Movement_DrakeCameraUp
	waitmovement 0
	applymovement LOCALID_DRACONID_VILLAGE_MAXIE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_0
	closemessage
	playmoncry SPECIES_GROUDON_PRIMAL, CRY_MODE_ENCOUNTER
	call Draconid_EventScript_FinaleQuake
	waitmoncry
	playmoncry SPECIES_SALAMENCE, CRY_MODE_ENCOUNTER
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	waitmoncry
	setobjectxyperm LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE, 19, 9
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE, MOVEMENT_TYPE_FACE_LEFT
	setobjectxyperm LOCALID_DRACONID_VILLAGE_DRAKE, 19, 8
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_DRAKE, MOVEMENT_TYPE_FACE_LEFT
	clearflag FLAG_TEMP_1F
	addobject LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE
	addobject LOCALID_DRACONID_VILLAGE_DRAKE
	playse SE_M_FLY
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE, DraconidVillage_Movement_DrakeFlyDown
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, DraconidVillage_Movement_DrakeFlyDown
	waitmovement 0
	playse SE_M_DRAGON_RAGE
	fadescreenswapbuffers FADE_TO_WHITE
	setobjectxyperm LOCALID_DRACONID_VILLAGE_MAXIE, 17, 8
	setobjectxyperm LOCALID_DRACONID_VILLAGE_ARCHIE, 21, 8
	setobjectxy LOCALID_DRACONID_VILLAGE_MAXIE, 17, 8
	setobjectxy LOCALID_DRACONID_VILLAGE_ARCHIE, 21, 8
	turnobject LOCALID_DRACONID_VILLAGE_MAXIE, DIR_EAST
	turnobject LOCALID_DRACONID_VILLAGE_ARCHIE, DIR_WEST
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_SALAMENCE, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_1
	closemessage
	setobjectxyperm LOCALID_DRACONID_VILLAGE_DRAKE, 19, 7
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_DRAKE, MOVEMENT_TYPE_FACE_DOWN
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, DraconidVillage_Movement_DrakeLeapsToTheDoor
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_2
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_3
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_4
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_5
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_6
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_7
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_ASTER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_8
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeComesHome_Text_9
	closemessage
	turnobject LOCALID_DRACONID_VILLAGE_MAXIE, DIR_SOUTH
	turnobject LOCALID_DRACONID_VILLAGE_ARCHIE, DIR_SOUTH
	applymovement LOCALID_CAMERA, DraconidVillage_Movement_DrakeCameraDown
	waitmovement 0
	special RemoveCameraObject
	return


DraconidVillage_EventScript_DrakeAndTheElder::
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, DraconidVillage_Movement_DrakeCameraUp
	waitmovement 0
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeAndTheElder_Text_0
	msgbox DraconidVillage_EventScript_DrakeAndTheElder_Text_1
	msgbox DraconidVillage_EventScript_DrakeAndTheElder_Text_2
	msgbox DraconidVillage_EventScript_DrakeAndTheElder_Text_3
	msgbox DraconidVillage_EventScript_DrakeAndTheElder_Text_4
	msgbox DraconidVillage_EventScript_DrakeAndTheElder_Text_5
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeAndTheElder_Text_6
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, DraconidVillage_Movement_DrakeMounts
	waitmovement 0
	playse SE_M_FLY
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE, DraconidVillage_Movement_DrakeFlyUp
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, DraconidVillage_Movement_DrakeFlyUp
	waitmovement 0
	removeobject LOCALID_DRACONID_VILLAGE_DRAKE
	removeobject LOCALID_DRACONID_VILLAGE_DRAKE_SALAMENCE
	applymovement LOCALID_CAMERA, DraconidVillage_Movement_DrakeCameraDown
	waitmovement 0
	special RemoveCameraObject
	return


DraconidVillage_EventScript_Drake::
	lock
	faceplayer
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_SAVED
	goto_if_lt DraconidVillage_EventScript_Drake_2
	goto_if_unset FLAG_DRACONID_DRAKE_RECONCILED, DraconidVillage_EventScript_Drake_5
DraconidVillage_EventScript_Drake_4:
	goto_if_unset FLAG_HIDE_DRACONID_VILLAGE_LANCE, DraconidVillage_EventScript_Drake_8
	msgbox DraconidVillage_EventScript_Drake_Text_2
DraconidVillage_EventScript_Drake_7:
	goto DraconidVillage_EventScript_DrakeTutor
	return

DraconidVillage_EventScript_Drake_2:
	msgbox DraconidVillage_EventScript_Drake_Text_0
	release
	end

DraconidVillage_EventScript_Drake_5:
	goto DraconidVillage_EventScript_DrakeMakesPeace
	goto DraconidVillage_EventScript_Drake_4

DraconidVillage_EventScript_Drake_8:
	msgbox DraconidVillage_EventScript_Drake_Text_1
	goto DraconidVillage_EventScript_Drake_7


DraconidVillage_EventScript_DrakeMakesPeace::
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_0
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_1
	closemessage
	playse SE_DOOR
	setobjectxyperm LOCALID_DRACONID_VILLAGE_LANCE_ELDER, 24, 11
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_LANCE_ELDER, MOVEMENT_TYPE_FACE_DOWN
	addobject LOCALID_DRACONID_VILLAGE_LANCE_ELDER
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ELDER, DraconidVillage_Movement_DrakeElderComesOut
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_2
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_3
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_4
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_5
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_6
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_7
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_8
	closemessage
	applymovement LOCALID_DRACONID_VILLAGE_LANCE_ELDER, DraconidVillage_Movement_DrakeElderGoesIn
	waitmovement 0
	playse SE_DOOR
	removeobject LOCALID_DRACONID_VILLAGE_LANCE_ELDER
	setflag FLAG_DRACONID_DRAKE_RECONCILED
	applymovement LOCALID_DRACONID_VILLAGE_DRAKE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox DraconidVillage_EventScript_DrakeMakesPeace_Text_9
	goto DraconidVillage_EventScript_DrakeTutor
	return


DraconidVillage_EventScript_DrakeTutor::
	move_tutor MOVE_DRACO_METEOR, DraconidVillage_Text_DrakeTutorTeach, DraconidVillage_Text_DrakeTutorWhichMon, DraconidVillage_EventScript_DrakeTutorDeclined, DraconidVillage_EventScript_DrakeTutorTaught
	release
	end


DraconidVillage_EventScript_DrakeTutorDeclined::
	msgbox DraconidVillage_EventScript_DrakeTutorDeclined_Text_0
	release
	end


DraconidVillage_EventScript_DrakeTutorTaught::
	msgbox DraconidVillage_EventScript_DrakeTutorTaught_Text_0
	release
	end


DraconidVillage_EventScript_DrakeSalamence::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SALAMENCE, CRY_MODE_NORMAL
	msgbox DraconidVillage_EventScript_DrakeSalamence_Text_0
	waitmoncry
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_SAVED
	goto_if_lt DraconidVillage_EventScript_DrakeSalamence_2
	msgbox DraconidVillage_EventScript_DrakeSalamence_Text_2
DraconidVillage_EventScript_DrakeSalamence_1:
	release
	return

DraconidVillage_EventScript_DrakeSalamence_2:
	msgbox DraconidVillage_EventScript_DrakeSalamence_Text_1
	goto DraconidVillage_EventScript_DrakeSalamence_1


DraconidVillage_Movement_DrakeFlyDown:
	fly_down
	step_end

DraconidVillage_Movement_DrakeFlyUp:
	fly_up
	step_end

DraconidVillage_Movement_DrakeLeapsToTheDoor:
	face_up
	jump_up
	face_down
	step_end

DraconidVillage_Movement_DrakeMounts:
	jump_down
	face_left
	step_end

DraconidVillage_Movement_DrakeCameraUp:
	walk_up
	walk_up
	walk_up
	step_end

DraconidVillage_Movement_DrakeCameraDown:
	walk_down
	walk_down
	walk_down
	step_end

DraconidVillage_Movement_DrakeElderComesOut:
	walk_down
	face_right
	step_end

DraconidVillage_Movement_DrakeElderGoesIn:
	walk_up
	step_end

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_0:
	.string "Ah, {PLAYER}! These days I keep the\n"
	.string "LEAGUE's door by day, and fly home to\l"
	.string "the village by night.\p"
	.string "My brother says it took me forty years\n"
	.string "to learn the way back.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_1:
	.string "But in this room, I am still the last of\n"
	.string "the ELITE FOUR.\p"
	.string "Show me again what is needed!$"

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_2:
	.string "You again, {PLAYER}. I take it you have\n"
	.string "said nothing to my brother.\p"
	.string "Good. Then let our POKéMON\n"
	.string "do the talking.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_3:
	.string "I am the last of the POKéMON LEAGUE\n"
	.string "ELITE FOUR, DRAKE the DRAGON master!\p"
	.string "Show me again what is needed!$"

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_4:
	.string "I am the last of the POKéMON LEAGUE\n"
	.string "ELITE FOUR, DRAKE the DRAGON master!$"

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_5:
	.string "…Hm? That band on your brow.\n"
	.string "Teal cloth, two horns of ivory.\p"
	.string "I have not seen one of those\n"
	.string "in forty years.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidIntro_Text_6:
	.string "For us to battle with POKéMON as\n"
	.string "partners, do you know what it takes?\p"
	.string "Do you know what is needed?\p"
	.string "If you don't, then you will never\n"
	.string "prevail over me!$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_0:
	.string "Go onwards, {PLAYER}.\n"
	.string "The CHAMPION is waiting.\p"
	.string "I will see you at home.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_1:
	.string "Go! Go onwards!\n"
	.string "The CHAMPION is waiting!\p"
	.string "…And not a word to my brother.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_2:
	.string "You deserve every credit for coming\n"
	.string "this far, {PLAYER}.\p"
	.string "You do seem to know what is needed.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_3:
	.string "And that dragon of yours fought like\n"
	.string "one hatched below the shrine, from one\l"
	.string "of the ELDER's eggs.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_4:
	.string "Yes. I know that band, and I know that\n"
	.string "shrine. I was born below it.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_5:
	.string "The ELDER who gave you your egg\n"
	.string "is my older brother.\p"
	.string "We hatched our BAGON the same spring.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_6:
	.string "Forty years ago, I flew mine down off\n"
	.string "the mountain to see the sea.\p"
	.string "Our clan keeps to its mountain. My\n"
	.string "brother told me that if I left, I need\l"
	.string "not come back.\p"
	.string "I never did.$"

EverGrandeCity_DrakesRoom_EventScript_DraconidPostBattle_Text_7:
	.string "…Say nothing of me to him. Forty years\n"
	.string "is too long for a message.\p"
	.string "Go! Go onwards!\n"
	.string "The CHAMPION is waiting!$"

DraconidVillage_EventScript_DrakeComesHome_Text_0:
	.string "MAXIE: GROUDON! Bury that shrine, and\n"
	.string "the old man in its door!$"

DraconidVillage_EventScript_DrakeComesHome_Text_1:
	.string "A SALAMENCE plunged out of the storm\n"
	.string "and took GROUDON's blow on its wings!$"

DraconidVillage_EventScript_DrakeComesHome_Text_2:
	.string "DRAKE: Hmph. Is that how you knock on a\n"
	.string "door, MAXIE?$"

DraconidVillage_EventScript_DrakeComesHome_Text_3:
	.string "MAXIE: DRAKE… The ELITE FOUR's\n"
	.string "DRAGON master.\p"
	.string "This is no concern of the LEAGUE's.$"

DraconidVillage_EventScript_DrakeComesHome_Text_4:
	.string "DRAKE: The LEAGUE didn't send me. I was\n"
	.string "born on this mountain.$"

DraconidVillage_EventScript_DrakeComesHome_Text_5:
	.string "ARCHIE: Born up here? Fufufu… So the\n"
	.string "old sea dog is a sky-watcher too!$"

DraconidVillage_EventScript_DrakeComesHome_Text_6:
	.string "ELDER: …DRAKE.$"

DraconidVillage_EventScript_DrakeComesHome_Text_7:
	.string "DRAKE: Forty years, brother.\n"
	.string "And still you guard the door yourself.$"

DraconidVillage_EventScript_DrakeComesHome_Text_8:
	.string "ASTER: B-BROTHER?!$"

DraconidVillage_EventScript_DrakeComesHome_Text_9:
	.string "DRAKE: {PLAYER}!\n"
	.string "MAXIE and ARCHIE are yours.\p"
	.string "Nothing touches this door\n"
	.string "while I stand in it.$"

DraconidVillage_EventScript_DrakeAndTheElder_Text_0:
	.string "ELDER: You came home.$"

DraconidVillage_EventScript_DrakeAndTheElder_Text_1:
	.string "DRAKE: The sky split open over half of\n"
	.string "HOENN, brother. Even an old sailor knows\l"
	.string "what that means.$"

DraconidVillage_EventScript_DrakeAndTheElder_Text_2:
	.string "ELDER: The traders spoke of a dragon\n"
	.string "master in the lowlanders' LEAGUE, with a\l"
	.string "SALAMENCE.\p"
	.string "I knew it was you. I never said your\n"
	.string "name aloud.$"

DraconidVillage_EventScript_DrakeAndTheElder_Text_3:
	.string "DRAKE: And I never once flew over these\n"
	.string "mountains, for fear you would see me.$"

DraconidVillage_EventScript_DrakeAndTheElder_Text_4:
	.string "ELDER: Forty years, DRAKE.$"

DraconidVillage_EventScript_DrakeAndTheElder_Text_5:
	.string "DRAKE: …I know. We will talk, brother.\n"
	.string "There is a great deal to say.$"

DraconidVillage_EventScript_DrakeAndTheElder_Text_6:
	.string "DRAKE: Tonight I will watch the pass,\n"
	.string "in case MAXIE's people come back.\p"
	.string "{PLAYER}… Thank you.\n"
	.string "You brought an old fool home.$"

DraconidVillage_EventScript_Drake_Text_0:
	.string "DRAKE: Nothing touches this door\n"
	.string "while I stand in it.\p"
	.string "Go, {PLAYER}!\n"
	.string "MAXIE and ARCHIE are yours.$"

DraconidVillage_EventScript_Drake_Text_1:
	.string "DRAKE: So the NORTHERN WING came home\n"
	.string "this year, too.\p"
	.string "The old songs will need a new verse.$"

DraconidVillage_EventScript_Drake_Text_2:
	.string "DRAKE: My brother and I have forty\n"
	.string "years of stories to trade.\p"
	.string "Some of mine are even true.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_0:
	.string "DRAKE: {PLAYER}. I asked you to say\n"
	.string "nothing of me to my brother.\p"
	.string "And then I flew home and told him\n"
	.string "everything myself.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_1:
	.string "DRAKE: Forty years I kept away. In the\n"
	.string "end, it took MAXIE and ARCHIE knocking\l"
	.string "on our door.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_2:
	.string "ELDER: DRAKE.\n"
	.string "Your tea has gone cold again.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_3:
	.string "DRAKE: I was telling {PLAYER} how I ran\n"
	.string "off to sea, brother.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_4:
	.string "ELDER: And how I told you\n"
	.string "never to come back.\p"
	.string "I said it in anger, and then I was too\n"
	.string "proud to take it back.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_5:
	.string "DRAKE: And I was too proud to ask.\n"
	.string "Two stubborn old dragons.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_6:
	.string "ELDER: Our songs say that one wing flew\n"
	.string "north and did not come back.\p"
	.string "I never wanted to sing that verse for\n"
	.string "my own brother.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_7:
	.string "ELDER: Now I will not have to.\n"
	.string "Welcome home, DRAKE.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_8:
	.string "DRAKE: …It is good to be home.$"

DraconidVillage_EventScript_DrakeMakesPeace_Text_9:
	.string "DRAKE: Before I left, our father taught\n"
	.string "us both the clan's oldest move.\p"
	.string "It is time someone else learned it.$"

DraconidVillage_EventScript_DrakeTutorDeclined_Text_0:
	.string "DRAKE: Come back whenever you like.\n"
	.string "I am not going anywhere now.$"

DraconidVillage_EventScript_DrakeTutorTaught_Text_0:
	.string "DRAKE: Every time the stars fall, they\n"
	.string "take something from the TRAINER who\l"
	.string "called them.\p"
	.string "Use it wisely.$"

DraconidVillage_EventScript_DrakeSalamence_Text_0:
	.string "SALAMENCE: Grrooaah!$"

DraconidVillage_EventScript_DrakeSalamence_Text_1:
	.string "DRAKE's SALAMENCE kept its eyes on\n"
	.string "GROUDON, its wings spread before the\l"
	.string "shrine.$"

DraconidVillage_EventScript_DrakeSalamence_Text_2:
	.string "DRAKE's SALAMENCE has curled up by the\n"
	.string "ELDER's door, as if it had never left.$"

DraconidVillage_Text_DrakeTutorTeach::
	.string "DRAKE: DRACO METEOR calls the stars\n"
	.string "down on the foe, as the sky once fell on\l"
	.string "this mountain.\p"
	.string "Shall I teach it to one of\n"
	.string "your POKéMON?$"

DraconidVillage_Text_DrakeTutorWhichMon::
	.string "DRAKE: Which one? Only a POKéMON with a\n"
	.string "dragon's heart can bear it.$"
