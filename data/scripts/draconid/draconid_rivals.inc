GraniteCave_B1F_EventScript_DraconidOnTransition::
	compare VAR_ASTER_STATE, ASTER_STATE_START
	goto_if_eq GraniteCave_B1F_EventScript_DraconidOnTransition_4
GraniteCave_B1F_EventScript_DraconidOnTransition_2:
	setflag FLAG_TEMP_11
	return

GraniteCave_B1F_EventScript_DraconidOnTransition_1:
	setvar VAR_TEMP_1, 1
	return

GraniteCave_B1F_EventScript_DraconidOnTransition_3:
	checktrainerflag TRAINER_ASTER_GRANITE_CAVE_DEINO
	goto_if 0, GraniteCave_B1F_EventScript_DraconidOnTransition_1
	goto GraniteCave_B1F_EventScript_DraconidOnTransition_2

GraniteCave_B1F_EventScript_DraconidOnTransition_4:
	compare VAR_MAGMA_STATE, MAGMA_STATE_DEVON_GOODS
	goto_if_ge GraniteCave_B1F_EventScript_DraconidOnTransition_3
	goto GraniteCave_B1F_EventScript_DraconidOnTransition_2


GraniteCave_B1F_EventScript_DraconidAster::
	lockall
	setvar VAR_TEMP_1, 0
	playbgm MUS_ENCOUNTER_INTENSE, FALSE
	msgbox GraniteCave_B1F_EventScript_DraconidAster_Text_0
	closemessage
	applymovement LOCALID_GRANITE_CAVE_B1F_ASTER, GraniteCave_B1F_Movement_DraconidAsterApproach
	waitmovement 0
	msgbox GraniteCave_B1F_EventScript_DraconidAster_Text_1
	msgbox GraniteCave_B1F_EventScript_DraconidAster_Text_2
	msgbox GraniteCave_B1F_EventScript_DraconidAster_Text_3
	closemessage
	trainerbattle_no_intro TRAINER_ASTER_GRANITE_CAVE_DEINO, GraniteCave_B1F_Text_DraconidAsterDefeat
	settrainerflag TRAINER_ASTER_GRANITE_CAVE_DEINO
	msgbox GraniteCave_B1F_EventScript_DraconidAster_Text_4
	msgbox GraniteCave_B1F_EventScript_DraconidAster_Text_5
	closemessage
	applymovement LOCALID_GRANITE_CAVE_B1F_ASTER, GraniteCave_B1F_Movement_DraconidAsterLeave
	waitmovement 0
	removeobject LOCALID_GRANITE_CAVE_B1F_ASTER
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


GraniteCave_B1F_Movement_DraconidAsterApproach:
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

GraniteCave_B1F_Movement_DraconidAsterLeave:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route121_EventScript_DraconidOnTransition::
	compare VAR_ASTER_STATE, ASTER_STATE_MEGA_RING
	goto_if_eq Route121_EventScript_DraconidOnTransition_4
Route121_EventScript_DraconidOnTransition_2:
	setflag FLAG_TEMP_14
	return

Route121_EventScript_DraconidOnTransition_1:
	setvar VAR_TEMP_1, 1
	return

Route121_EventScript_DraconidOnTransition_3:
	compare VAR_MAGMA_STATE, MAGMA_STATE_WEATHER_INSTITUTE
	goto_if_ge Route121_EventScript_DraconidOnTransition_8
	goto Route121_EventScript_DraconidOnTransition_2

Route121_EventScript_DraconidOnTransition_4:
	goto_if_set FLAG_BADGE06_GET, Route121_EventScript_DraconidOnTransition_3
	goto Route121_EventScript_DraconidOnTransition_2

Route121_EventScript_DraconidOnTransition_7:
	checktrainerflag TRAINER_ASTER_ROUTE_121_DEINO
	goto_if 0, Route121_EventScript_DraconidOnTransition_1
	goto Route121_EventScript_DraconidOnTransition_2

Route121_EventScript_DraconidOnTransition_8:
	compare VAR_MAGMA_STATE, MAGMA_STATE_MT_PYRE
	goto_if_lt Route121_EventScript_DraconidOnTransition_7
	goto Route121_EventScript_DraconidOnTransition_2


Route121_EventScript_DraconidAster::
	lockall
	setvar VAR_TEMP_1, 0
	getplayerxy VAR_0x8004, VAR_0x8005
	playbgm MUS_ENCOUNTER_INTENSE, FALSE
	applymovement LOCALID_ROUTE121_ASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route121_EventScript_DraconidAster_Text_0
	closemessage
	compare VAR_0x8004, 30
	goto_if_eq Route121_EventScript_DraconidAster_2
	applymovement LOCALID_ROUTE121_ASTER, Route121_Movement_DraconidAsterApproachRight
Route121_EventScript_DraconidAster_1:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route121_EventScript_DraconidAster_Text_1
	msgbox Route121_EventScript_DraconidAster_Text_2
	msgbox Route121_EventScript_DraconidAster_Text_3
	msgbox Route121_EventScript_DraconidAster_Text_4
	closemessage
	trainerbattle_no_intro TRAINER_ASTER_ROUTE_121_DEINO, Route121_Text_DraconidAsterDefeat
	settrainerflag TRAINER_ASTER_ROUTE_121_DEINO
	msgbox Route121_EventScript_DraconidAster_Text_5
	msgbox Route121_EventScript_DraconidAster_Text_6
	closemessage
	applymovement LOCALID_ROUTE121_ASTER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_ROUTE121_ASTER
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

Route121_EventScript_DraconidAster_2:
	applymovement LOCALID_ROUTE121_ASTER, Route121_Movement_DraconidAsterApproachLeft
	goto Route121_EventScript_DraconidAster_1


Route121_Movement_DraconidAsterApproachLeft:
	walk_up
	walk_up
	step_end

Route121_Movement_DraconidAsterApproachRight:
	walk_right
	walk_up
	walk_up
	step_end

DraconidVillage_EventScript_DraconidRivalsOnTransition::
	compare VAR_MAGMA_STATE, MAGMA_STATE_TURNED
	goto_if_ge DraconidVillage_EventScript_DraconidRivalsOnTransition_10
DraconidVillage_EventScript_DraconidRivalsOnTransition_6:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_EventScript_DraconidRivalsOnTransition_5
DraconidVillage_EventScript_DraconidRivalsOnTransition_3:
	setflag FLAG_TEMP_1F
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_lt DraconidVillage_EventScript_DraconidRivalsOnTransition_14
	return

DraconidVillage_EventScript_DraconidRivalsOnTransition_1:
	clearflag FLAG_HIDE_DRACONID_VILLAGE_NERINE
	return

DraconidVillage_EventScript_DraconidRivalsOnTransition_2:
	setobjectxyperm LOCALID_DRACONID_VILLAGE_HOME_ASTER, 27, 7
	setobjectmovementtype LOCALID_DRACONID_VILLAGE_HOME_ASTER, MOVEMENT_TYPE_FACE_RIGHT
	return

DraconidVillage_EventScript_DraconidRivalsOnTransition_4:
	compare VAR_TEMP_C, 1
	goto_if_ne DraconidVillage_EventScript_DraconidRivalsOnTransition_2
	goto DraconidVillage_EventScript_DraconidRivalsOnTransition_3

DraconidVillage_EventScript_DraconidRivalsOnTransition_5:
	compare VAR_ASTER_STATE, ASTER_STATE_POSTGAME
	goto_if_eq DraconidVillage_EventScript_DraconidRivalsOnTransition_4
	goto DraconidVillage_EventScript_DraconidRivalsOnTransition_3

DraconidVillage_EventScript_DraconidRivalsOnTransition_9:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_NONE
	goto_if_eq DraconidVillage_EventScript_DraconidRivalsOnTransition_1
	goto DraconidVillage_EventScript_DraconidRivalsOnTransition_6

DraconidVillage_EventScript_DraconidRivalsOnTransition_10:
	goto_if_unset FLAG_IS_CHAMPION, DraconidVillage_EventScript_DraconidRivalsOnTransition_9
	goto DraconidVillage_EventScript_DraconidRivalsOnTransition_6

DraconidVillage_EventScript_DraconidRivalsOnTransition_14:
	setflag FLAG_HIDE_DRACONID_VILLAGE_NERINE
	return


DraconidVillage_EventScript_DraconidAsterHome::
	lock
	faceplayer
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_EventScript_DraconidAsterHome_2
DraconidVillage_EventScript_DraconidAsterHome_1:
	checktrainerflag TRAINER_ASTER_VILLAGE_DEINO
	goto_if 1, DraconidVillage_EventScript_DraconidAsterHome_5
	goto_if_unset FLAG_BADGE08_GET, DraconidVillage_EventScript_DraconidAsterHome_8
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_3
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_4
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_5
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_6, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_EventScript_DraconidAsterHome_11
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_8
	closemessage
	trainerbattle_no_intro TRAINER_ASTER_VILLAGE_DEINO, DraconidVillage_Text_DraconidAsterHomeDefeat
	settrainerflag TRAINER_ASTER_VILLAGE_DEINO
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_9
	release
	return

DraconidVillage_EventScript_DraconidAsterHome_2:
	goto DraconidVillage_EventScript_DraconidRivalsDouble
	goto DraconidVillage_EventScript_DraconidAsterHome_1

DraconidVillage_EventScript_DraconidAsterHome_5:
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_0
	release
	end

DraconidVillage_EventScript_DraconidAsterHome_8:
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_1
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_2
	release
	end

DraconidVillage_EventScript_DraconidAsterHome_11:
	msgbox DraconidVillage_EventScript_DraconidAsterHome_Text_7
	release
	end


DraconidVillage_EventScript_DraconidNerineHome::
	checktrainerflag TRAINER_NERINE_VILLAGE_DEINO_CHARMANDER
	goto_if 1, DraconidVillage_EventScript_DraconidNerineHome_2
	goto_if_unset FLAG_BADGE08_GET, DraconidVillage_EventScript_DraconidNerineHome_5
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_3
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_4, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_EventScript_DraconidNerineHome_8
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_6
	closemessage
	trainerbattle_no_intro TRAINER_NERINE_VILLAGE_DEINO_CHARMANDER, DraconidVillage_Text_DraconidNerineHomeDefeat
	settrainerflag TRAINER_NERINE_VILLAGE_DEINO_CHARMANDER
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_7
	release
	return

DraconidVillage_EventScript_DraconidNerineHome_2:
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_0
	release
	end

DraconidVillage_EventScript_DraconidNerineHome_5:
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_1
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_2
	release
	end

DraconidVillage_EventScript_DraconidNerineHome_8:
	msgbox DraconidVillage_EventScript_DraconidNerineHome_Text_5
	release
	end


DraconidVillage_EventScript_DraconidRivalsDouble::
	compare VAR_NERINE_STATE, NERINE_STATE_POSTGAME
	goto_if_ne DraconidVillage_EventScript_DraconidRivalsDouble_2
	goto_if_set FLAG_DAILY_DRACONID_RIVALS_DOUBLE, DraconidVillage_EventScript_DraconidRivalsDouble_5
	checktrainerflag TRAINER_ASTER_DOUBLE_DEINO
	goto_if 0, DraconidVillage_EventScript_DraconidRivalsDouble_8
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_4, MSGBOX_YESNO
DraconidVillage_EventScript_DraconidRivalsDouble_7:
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_EventScript_DraconidRivalsDouble_12
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne DraconidVillage_EventScript_DraconidRivalsDouble_15
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_7
	closemessage
	trainerbattle_two_trainers_no_intro TRAINER_ASTER_DOUBLE_DEINO, DraconidVillage_Text_DraconidAsterDoubleDefeat, TRAINER_NERINE_DOUBLE_DEINO_CHARMANDER, DraconidVillage_Text_DraconidNerineDoubleDefeat
	settrainerflag TRAINER_ASTER_DOUBLE_DEINO
	settrainerflag TRAINER_NERINE_DOUBLE_DEINO_CHARMANDER
	setflag FLAG_DAILY_DRACONID_RIVALS_DOUBLE
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_8
	release
	return

DraconidVillage_EventScript_DraconidRivalsDouble_2:
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_0
	release
	end

DraconidVillage_EventScript_DraconidRivalsDouble_5:
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_1
	release
	end

DraconidVillage_EventScript_DraconidRivalsDouble_8:
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_2
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_3, MSGBOX_YESNO
	goto DraconidVillage_EventScript_DraconidRivalsDouble_7

DraconidVillage_EventScript_DraconidRivalsDouble_12:
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_5
	release
	end

DraconidVillage_EventScript_DraconidRivalsDouble_15:
	msgbox DraconidVillage_EventScript_DraconidRivalsDouble_Text_6
	release
	end


GraniteCave_B1F_EventScript_DraconidAster_Text_0:
	.string "ASTER: Don't bother looking for a light.$"

GraniteCave_B1F_EventScript_DraconidAster_Text_1:
	.string "ASTER: The dark suits a dragon. Every\n"
	.string "DRACONID apprentice spends a night in\l"
	.string "a cave like this one.$"

GraniteCave_B1F_EventScript_DraconidAster_Text_2:
	.string "ASTER: Hmph. So it's true. You look good\n"
	.string "in red, traitor.\p"
	.string "I know, I know. The ELDER told you to\n"
	.string "wear it. He told me to leave you alone,\l"
	.string "too.$"

GraniteCave_B1F_EventScript_DraconidAster_Text_3:
	.string "ASTER: I came down the mountain to see\n"
	.string "what the lowlands are doing to you.\p"
	.string "Let's find out!$"

GraniteCave_B1F_EventScript_DraconidAster_Text_4:
	.string "ASTER: …Fine. They haven't made you\n"
	.string "soft. Yet.$"

GraniteCave_B1F_EventScript_DraconidAster_Text_5:
	.string "ASTER: Remember who you are under all\n"
	.string "that red, {PLAYER}.\p"
	.string "And don't follow me. I know the way out\n"
	.string "in the dark. You don't.$"

Route121_EventScript_DraconidAster_Text_0:
	.string "ASTER: {PLAYER}. Over here.$"

Route121_EventScript_DraconidAster_Text_1:
	.string "ASTER: Look at that mountain. MT. PYRE.\p"
	.string "The ELDER says the old ones are\n"
	.string "stirring, under the land and under the\l"
	.string "sea.\p"
	.string "Have you felt the weather lately? All\n"
	.string "over HOENN, it's gone wrong.$"

Route121_EventScript_DraconidAster_Text_2:
	.string "ASTER: Now MAGMA and AQUA are both on\n"
	.string "their way up there.\p"
	.string "You know what they want. Don't tell me.\n"
	.string "I can see it on your face.$"

Route121_EventScript_DraconidAster_Text_3:
	.string "ASTER: Riddle: two dragons climbed the\n"
	.string "same tower. Only one could reach the\l"
	.string "sky. Which one?\p"
	.string "…The one still standing. The sky doesn't\n"
	.string "care about anything else.$"

Route121_EventScript_DraconidAster_Text_4:
	.string "ASTER: So, {PLAYER}. Which of us is still\n"
	.string "standing?$"

Route121_EventScript_DraconidAster_Text_5:
	.string "ASTER: Go on, then. Up the mountain.\p"
	.string "Whatever MAXIE finds up there, don't\n"
	.string "let him keep it.$"

Route121_EventScript_DraconidAster_Text_6:
	.string "ASTER: If the old ones wake, the ELDER\n"
	.string "says only the sky can put them back to\l"
	.string "sleep.\p"
	.string "Remember that.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_0:
	.string "ASTER: What are you still doing here?\n"
	.string "The LEAGUE won't wait forever.\p"
	.string "Neither will the sky.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_1:
	.string "ASTER: There you are. Out of the red at\n"
	.string "last.\p"
	.string "Hear that? The whole village has been\n"
	.string "cheering since the news came up the\l"
	.string "pass.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_2:
	.string "ASTER: Don't get comfortable. Go and\n"
	.string "win JUAN's BADGE first.\p"
	.string "Then come back, and we settle METEOR\n"
	.string "FALLS. Properly.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_3:
	.string "ASTER: Eight BADGES. Hmph. Not bad, for\n"
	.string "a former traitor.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_4:
	.string "ASTER: METEOR FALLS never counted. You\n"
	.string "were wearing their colors, and I was too\l"
	.string "angry to see straight.\p"
	.string "Now there's nothing in the way. No red,\n"
	.string "no secrets. Just two DRACONIDS.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_5:
	.string "ASTER: And look. The night we called\n"
	.string "RAYQUAZA, the ELDER gave me a KEY\l"
	.string "STONE of my own.\p"
	.string "And a crystal from the keepers in\n"
	.string "ALOLA. You're the first one I get to try\l"
	.string "them on.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_6:
	.string "ASTER: Ready?$"

DraconidVillage_EventScript_DraconidAsterHome_Text_7:
	.string "ASTER: Then hurry up and get ready. I'm\n"
	.string "not going anywhere.$"

DraconidVillage_EventScript_DraconidAsterHome_Text_8:
	.string "ASTER: Good. Don't hold back!$"

DraconidVillage_EventScript_DraconidAsterHome_Text_9:
	.string "ASTER: …Fine. That one counted.\p"
	.string "Go and win your LEAGUE, {PLAYER}. The\n"
	.string "ELDER says the sky isn't finished with\l"
	.string "us.$"

DraconidVillage_EventScript_DraconidNerineHome_Text_0:
	.string "NERINE: Go on, {PLAYER}. The LEAGUE is\n"
	.string "waiting.\p"
	.string "The pond and I will still be here when\n"
	.string "you come home.$"

DraconidVillage_EventScript_DraconidNerineHome_Text_1:
	.string "NERINE: Home. After all those years at\n"
	.string "sea, I keep expecting the water to\l"
	.string "taste of salt.$"

DraconidVillage_EventScript_DraconidNerineHome_Text_2:
	.string "NERINE: When you have JUAN's BADGE,\n"
	.string "come and see me.\p"
	.string "I'd like to battle you at your\n"
	.string "strongest.$"

DraconidVillage_EventScript_DraconidNerineHome_Text_3:
	.string "NERINE: Every time we battled, I was\n"
	.string "someone else. A TEAM AQUA grunt. The\l"
	.string "ELDER's test.\p"
	.string "I never got to battle you as myself.$"

DraconidVillage_EventScript_DraconidNerineHome_Text_4:
	.string "NERINE: No AQUA POKéMON this time. Only\n"
	.string "my own.\p"
	.string "And the crystal the ELDER gave me when\n"
	.string "we called RAYQUAZA. Will you?$"

DraconidVillage_EventScript_DraconidNerineHome_Text_5:
	.string "NERINE: Whenever you're ready. The\n"
	.string "water isn't going anywhere.$"

DraconidVillage_EventScript_DraconidNerineHome_Text_6:
	.string "NERINE: Then let the sky watch.$"

DraconidVillage_EventScript_DraconidNerineHome_Text_7:
	.string "NERINE: So that's what it feels like.\n"
	.string "Losing as myself.\p"
	.string "…I think I like it better. Thank you,\n"
	.string "{PLAYER}.$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_0:
	.string "ASTER: Battle NERINE first. After that,\n"
	.string "the two of us. Together.$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_1:
	.string "ASTER: Once a day is plenty. Come back\n"
	.string "tomorrow.$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_2:
	.string "ASTER: Riddle: what's harder than\n"
	.string "beating one DRACONID?\p"
	.string "…Two of us at once.$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_3:
	.string "NERINE: She's been saving that one all\n"
	.string "week.\p"
	.string "We'd like to battle you together,\n"
	.string "{PLAYER}. Will you?$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_4:
	.string "ASTER: Back again? NERINE and I have\n"
	.string "been practicing.\p"
	.string "NERINE: Two against your two, {PLAYER}.\n"
	.string "Ready?$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_5:
	.string "ASTER: Hmph. We'll be here.$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_6:
	.string "NERINE: You'll need two POKéMON who can\n"
	.string "battle for this one.$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_7:
	.string "ASTER: NERINE, keep up!\p"
	.string "NERINE: I always do.$"

DraconidVillage_EventScript_DraconidRivalsDouble_Text_8:
	.string "ASTER: Again tomorrow. Same pond.\p"
	.string "NERINE: The sky isn't going anywhere.\n"
	.string "Neither are we.$"

GraniteCave_B1F_Text_DraconidAsterDefeat::
	.string "Hmph. Still a DRACONID in there.$"

Route121_Text_DraconidAsterDefeat::
	.string "…You're still standing. Hmph.$"

DraconidVillage_Text_DraconidAsterHomeDefeat::
	.string "…Fine. You win this round.$"

DraconidVillage_Text_DraconidNerineHomeDefeat::
	.string "NERINE: …There you are. The real you.$"

DraconidVillage_Text_DraconidAsterDoubleDefeat::
	.string "ASTER: Both of us, and still…$"

DraconidVillage_Text_DraconidNerineDoubleDefeat::
	.string "NERINE: The sky chose well. Again.$"
