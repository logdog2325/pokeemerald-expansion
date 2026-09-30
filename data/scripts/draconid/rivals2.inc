Route104_EventScript_DraconidBrendan::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 10
	playse SE_DOOR
	addobject LOCALID_ROUTE104_RIVAL
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerBackUp
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalExitBrineysCottage
	waitmovement 0
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	playse SE_PIN
	applymovement LOCALID_ROUTE104_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Route104_EventScript_DraconidBrendan_Text_0
	msgbox Route104_EventScript_DraconidBrendan_Text_1
	msgbox Route104_EventScript_DraconidBrendan_Text_2
	closemessage
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_104, Route104_Text_DraconidBrendanDefeat
	msgbox Route104_EventScript_DraconidBrendan_Text_3
	closemessage
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_DraconidBrendanLeave
	waitmovement 0
	removeobject LOCALID_ROUTE104_RIVAL
	settrainerflag TRAINER_BRENDAN_ROUTE_104
	setvar VAR_ROUTE104_STATE, 2
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


Route104_Movement_DraconidBrendanLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route112_EventScript_DraconidOnTransition::
	compare VAR_MAGMA_STATE, MAGMA_STATE_METEOR_FALLS
	goto_if_eq Route112_EventScript_DraconidOnTransition_4
Route112_EventScript_DraconidOnTransition_2:
	setflag FLAG_TEMP_11
	return

Route112_EventScript_DraconidOnTransition_1:
	setvar VAR_TEMP_2, 1
	return

Route112_EventScript_DraconidOnTransition_3:
	checktrainerflag TRAINER_WALLY_ROUTE_112
	goto_if 0, Route112_EventScript_DraconidOnTransition_1
	goto Route112_EventScript_DraconidOnTransition_2

Route112_EventScript_DraconidOnTransition_4:
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, Route112_EventScript_DraconidOnTransition_3
	goto Route112_EventScript_DraconidOnTransition_2


Route112_EventScript_DraconidWally::
	lockall
	playbgm MUS_ENCOUNTER_MAY, FALSE
	playse SE_PIN
	applymovement LOCALID_ROUTE112_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 26
	goto_if_eq Route112_EventScript_DraconidWally_2
Route112_EventScript_DraconidWally_1:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route112_EventScript_DraconidWally_Text_0
	msgbox Route112_EventScript_DraconidWally_Text_1
	msgbox Route112_EventScript_DraconidWally_Text_2
	closemessage
	trainerbattle_no_intro TRAINER_WALLY_ROUTE_112, Route112_Text_DraconidWallyDefeat
	msgbox Route112_EventScript_DraconidWally_Text_3
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 26
	goto_if_eq Route112_EventScript_DraconidWally_5
	applymovement LOCALID_ROUTE112_WALLY, Route112_Movement_DraconidWallyLeaveLeft
Route112_EventScript_DraconidWally_4:
	waitmovement 0
	removeobject LOCALID_ROUTE112_WALLY
	settrainerflag TRAINER_WALLY_ROUTE_112
	setvar VAR_TEMP_2, 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

Route112_EventScript_DraconidWally_2:
	applymovement LOCALID_ROUTE112_WALLY, Route112_Movement_DraconidWallyStepLeft
	waitmovement 0
	goto Route112_EventScript_DraconidWally_1

Route112_EventScript_DraconidWally_5:
	applymovement LOCALID_ROUTE112_WALLY, Route112_Movement_DraconidWallyLeaveRight
	goto Route112_EventScript_DraconidWally_4


Route112_Movement_DraconidWallyStepLeft:
	walk_left
	face_down
	step_end

Route112_Movement_DraconidWallyLeaveRight:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route112_Movement_DraconidWallyLeaveLeft:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LavaridgeTown_EventScript_DraconidMayBattle::
	msgbox LavaridgeTown_EventScript_DraconidMayBattle_Text_0
	msgbox LavaridgeTown_EventScript_DraconidMayBattle_Text_1
	closemessage
	trainerbattle_earlyrival TRAINER_MAY_LAVARIDGE, RIVAL_BATTLE_HEAL_AFTER, LavaridgeTown_Text_DraconidMayDefeat, LavaridgeTown_Text_DraconidMayVictory
	compare VAR_RESULT, TRUE
	goto_if_eq LavaridgeTown_EventScript_DraconidMayBattle_1
	msgbox LavaridgeTown_EventScript_DraconidMayBattle_Text_3
	return

LavaridgeTown_EventScript_DraconidMayBattle_1:
	msgbox LavaridgeTown_EventScript_DraconidMayBattle_Text_2
	return


LavaridgeTown_EventScript_DraconidFindGoGoggles::
	goto_if_set FLAG_RECEIVED_GO_GOGGLES, LavaridgeTown_EventScript_DraconidFindGoGoggles_2
	delay 20
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox LavaridgeTown_EventScript_DraconidFindGoGoggles_Text_0
	additem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	setvar VAR_0x8006, ITEM_GO_GOGGLES
	bufferitemname STR_VAR_2, ITEM_GO_GOGGLES
	bufferstdstring STR_VAR_3, STDSTRING_KEYITEMS
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_EventScript_DraconidFindGoGoggles_Text_1
	delay 10
	showitemdescription
	waitfanfare
	waitmessage
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	hideitemdescription
	msgbox LavaridgeTown_EventScript_DraconidFindGoGoggles_Text_2
	return

LavaridgeTown_EventScript_DraconidFindGoGoggles_2:
	return


Route120_EventScript_DraconidOnTransition::
	compare VAR_WALLY_STATE, WALLY_STATE_LILYCOVE
	goto_if_eq Route120_EventScript_DraconidOnTransition_3
Route120_EventScript_DraconidOnTransition_2:
	setflag FLAG_TEMP_13
	return

Route120_EventScript_DraconidOnTransition_1:
	setvar VAR_TEMP_2, 1
	return

Route120_EventScript_DraconidOnTransition_3:
	checktrainerflag TRAINER_WALLY_ROUTE_120
	goto_if 0, Route120_EventScript_DraconidOnTransition_1
	goto Route120_EventScript_DraconidOnTransition_2


Route120_EventScript_DraconidWally::
	lockall
	playbgm MUS_ENCOUNTER_MAY, FALSE
	playse SE_PIN
	applymovement LOCALID_ROUTE120_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8005, 68
	goto_if_eq Route120_EventScript_DraconidWally_2
Route120_EventScript_DraconidWally_1:
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route120_EventScript_DraconidWally_Text_0
	msgbox Route120_EventScript_DraconidWally_Text_1
	msgbox Route120_EventScript_DraconidWally_Text_2
	closemessage
	trainerbattle_no_intro TRAINER_WALLY_ROUTE_120, Route120_Text_DraconidWallyDefeat
	msgbox Route120_EventScript_DraconidWally_Text_3
	closemessage
	applymovement LOCALID_ROUTE120_WALLY, Route120_Movement_DraconidWallyLeave
	waitmovement 0
	removeobject LOCALID_ROUTE120_WALLY
	settrainerflag TRAINER_WALLY_ROUTE_120
	setvar VAR_TEMP_2, 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

Route120_EventScript_DraconidWally_2:
	applymovement LOCALID_ROUTE120_WALLY, Route120_Movement_DraconidWallyStepDown
	waitmovement 0
	goto Route120_EventScript_DraconidWally_1


Route120_Movement_DraconidWallyStepDown:
	walk_down
	face_right
	step_end

Route120_Movement_DraconidWallyLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

JaggedPass_EventScript_DraconidOnTransition::
	setflag FLAG_TEMP_11
	compare VAR_MAGMA_STATE, MAGMA_STATE_PROMOTED
	goto_if_eq JaggedPass_EventScript_DraconidOnTransition_2
	return

JaggedPass_EventScript_DraconidOnTransition_1:
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 16
	goto_if_eq JaggedPass_EventScript_DraconidOnTransition_7
	return

JaggedPass_EventScript_DraconidOnTransition_2:
	checktrainerflag TRAINER_BRENDAN_JAGGED_PASS
	goto_if 0, JaggedPass_EventScript_DraconidOnTransition_1
	return

JaggedPass_EventScript_DraconidOnTransition_5:
	setvar VAR_TEMP_2, 1
	return

JaggedPass_EventScript_DraconidOnTransition_6:
	compare VAR_0x8005, 19
	goto_if_le JaggedPass_EventScript_DraconidOnTransition_5
	return

JaggedPass_EventScript_DraconidOnTransition_7:
	compare VAR_0x8005, 18
	goto_if_ge JaggedPass_EventScript_DraconidOnTransition_6
	return


JaggedPass_EventScript_DraconidBrendan::
	lockall
	setvar VAR_TEMP_2, 0
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	addobject LOCALID_JAGGED_PASS_BRENDAN
	applymovement LOCALID_JAGGED_PASS_BRENDAN, JaggedPass_Movement_DraconidBrendanApproach
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox JaggedPass_EventScript_DraconidBrendan_Text_0
	msgbox JaggedPass_EventScript_DraconidBrendan_Text_1
	msgbox JaggedPass_EventScript_DraconidBrendan_Text_2
	closemessage
	trainerbattle_earlyrival TRAINER_BRENDAN_JAGGED_PASS, RIVAL_BATTLE_HEAL_AFTER, JaggedPass_Text_DraconidBrendanDefeat, JaggedPass_Text_DraconidBrendanVictory
	compare VAR_RESULT, TRUE
	goto_if_eq JaggedPass_EventScript_DraconidBrendan_2
	msgbox JaggedPass_EventScript_DraconidBrendan_Text_4
JaggedPass_EventScript_DraconidBrendan_1:
	msgbox JaggedPass_EventScript_DraconidBrendan_Text_5
	closemessage
	applymovement LOCALID_JAGGED_PASS_BRENDAN, JaggedPass_Movement_DraconidBrendanLeave
	waitmovement 0
	removeobject LOCALID_JAGGED_PASS_BRENDAN
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

JaggedPass_EventScript_DraconidBrendan_2:
	msgbox JaggedPass_EventScript_DraconidBrendan_Text_3
	goto JaggedPass_EventScript_DraconidBrendan_1


JaggedPass_Movement_DraconidBrendanApproach:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

JaggedPass_Movement_DraconidBrendanLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_EventScript_DraconidOnTransition::
	setflag FLAG_TEMP_11
	compare VAR_MAGMA_STATE, MAGMA_STATE_SPACE_CENTER
	goto_if_eq MossdeepCity_EventScript_DraconidOnTransition_2
	return

MossdeepCity_EventScript_DraconidOnTransition_1:
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 64
	goto_if_eq MossdeepCity_EventScript_DraconidOnTransition_6
	return

MossdeepCity_EventScript_DraconidOnTransition_2:
	checktrainerflag TRAINER_MAY_MOSSDEEP
	goto_if 0, MossdeepCity_EventScript_DraconidOnTransition_1
	return

MossdeepCity_EventScript_DraconidOnTransition_5:
	setvar VAR_TEMP_2, 1
	return

MossdeepCity_EventScript_DraconidOnTransition_6:
	compare VAR_0x8005, 16
	goto_if_le MossdeepCity_EventScript_DraconidOnTransition_5
	return


MossdeepCity_EventScript_DraconidMay::
	lockall
	setvar VAR_TEMP_2, 0
	playbgm MUS_ENCOUNTER_MAY, FALSE
	addobject LOCALID_MOSSDEEP_MAY
	applymovement LOCALID_MOSSDEEP_MAY, MossdeepCity_Movement_DraconidMayApproach
	waitmovement 0
	msgbox MossdeepCity_EventScript_DraconidMay_Text_0
	msgbox MossdeepCity_EventScript_DraconidMay_Text_1
	msgbox MossdeepCity_EventScript_DraconidMay_Text_2
	closemessage
	trainerbattle_earlyrival TRAINER_MAY_MOSSDEEP, RIVAL_BATTLE_HEAL_AFTER, MossdeepCity_Text_DraconidMayDefeat, MossdeepCity_Text_DraconidMayVictory
	compare VAR_RESULT, TRUE
	goto_if_eq MossdeepCity_EventScript_DraconidMay_2
	msgbox MossdeepCity_EventScript_DraconidMay_Text_4
MossdeepCity_EventScript_DraconidMay_1:
	msgbox MossdeepCity_EventScript_DraconidMay_Text_5
	closemessage
	applymovement LOCALID_MOSSDEEP_MAY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_MOSSDEEP_MAY
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return

MossdeepCity_EventScript_DraconidMay_2:
	msgbox MossdeepCity_EventScript_DraconidMay_Text_3
	goto MossdeepCity_EventScript_DraconidMay_1


MossdeepCity_Movement_DraconidMayApproach:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_3
	goto RivalsHouse_2F_EventScript_Rival
	return

LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_2:
	lock
	faceplayer
	msgbox LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_0
	msgbox LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_1
	release
	end

LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_3:
	lock
	faceplayer
	msgbox LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_2
	msgbox LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_3
	release
	end


LittlerootTown_MaysHouse_2F_EventScript_DraconidMay::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_3
	goto RivalsHouse_2F_EventScript_Rival
	return

LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_2:
	lock
	faceplayer
	msgbox LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_0
	msgbox LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_1
	release
	end

LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_3:
	lock
	faceplayer
	msgbox LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_2
	msgbox LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_3
	release
	end


Route104_EventScript_DraconidBrendan_Text_0:
	.string "BRENDAN: There you are, {PLAYER}.\p"
	.string "I figured you'd come for MR. BRINEY's\n"
	.string "boat sooner or later.$"

Route104_EventScript_DraconidBrendan_Text_1:
	.string "BRENDAN: I told my dad about you, like I\n"
	.string "said I would.\p"
	.string "You know what he said? “Give {PLAYER} a\n"
	.string "chance.”\p"
	.string "A chance?! You're wearing THEIR\n"
	.string "uniform!$"

Route104_EventScript_DraconidBrendan_Text_2:
	.string "BRENDAN: So where's MAGMA sending you\n"
	.string "now?\p"
	.string "…Fine, don't tell me. Then battle me!$"

Route104_EventScript_DraconidBrendan_Text_3:
	.string "BRENDAN: Tch… Go on, then. Get on your\n"
	.string "boat.\p"
	.string "But if MAGMA hurts anyone in DEWFORD,\n"
	.string "I'm coming after you.$"

Route112_EventScript_DraconidWally_Text_0:
	.string "WALLY: {PLAYER}! Stop right there!$"

Route112_EventScript_DraconidWally_Text_1:
	.string "WALLY: MAGMA grunts blocked this\n"
	.string "station for days.\p"
	.string "My uncle and I were going up to the hot\n"
	.string "springs in LAVARIDGE. They're good for\l"
	.string "my lungs.$"

Route112_EventScript_DraconidWally_Text_2:
	.string "WALLY: Now everyone says MAGMA is up\n"
	.string "on MT. CHIMNEY.\p"
	.string "Something terrible is going to happen,\n"
	.string "isn't it?\p"
	.string "I won't let you go up there!$"

Route112_EventScript_DraconidWally_Text_3:
	.string "WALLY: …Go, then. I can't stop you.\p"
	.string "But if anything happens to LAVARIDGE,\n"
	.string "I'll never forgive you, {PLAYER}!$"

LavaridgeTown_EventScript_DraconidMayBattle_Text_0:
	.string "MAY: {PLAYER}. So you're still wearing\n"
	.string "that uniform.\p"
	.string "The whole town is talking about what\n"
	.string "MAGMA tried on MT. CHIMNEY.$"

LavaridgeTown_EventScript_DraconidMayBattle_Text_1:
	.string "MAY: People here nearly lost their\n"
	.string "homes!\p"
	.string "I'm not letting a MAGMA grunt walk away\n"
	.string "from that. Battle me!$"

LavaridgeTown_EventScript_DraconidMayBattle_Text_2:
	.string "MAY: See? MAGMA can't win every time.$"

LavaridgeTown_EventScript_DraconidMayBattle_Text_3:
	.string "MAY: Tch… You're even stronger than on\n"
	.string "ROUTE 110.$"

LavaridgeTown_EventScript_DraconidFindGoGoggles_Text_0:
	.string "MAY dropped something as she stormed\n"
	.string "off…$"

LavaridgeTown_EventScript_DraconidFindGoGoggles_Text_1:
	.string "{PLAYER} found the {STR_VAR_2}!$"

LavaridgeTown_EventScript_DraconidFindGoGoggles_Text_2:
	.string "There's a tag on the strap.\p"
	.string "“Property of MAY. For the sandstorm on\n"
	.string "ROUTE 111!”$"

Route120_EventScript_DraconidWally_Text_0:
	.string "WALLY: {PLAYER}. I knew you'd come this\n"
	.string "way.$"

Route120_EventScript_DraconidWally_Text_1:
	.string "WALLY: The people at the WEATHER\n"
	.string "INSTITUTE were tied up in their own\l"
	.string "building!\p"
	.string "Everyone on ROUTE 119 says MAGMA was\n"
	.string "there, too.$"

Route120_EventScript_DraconidWally_Text_2:
	.string "WALLY: I'm not the boy who needed help\n"
	.string "catching RALTS anymore.\p"
	.string "This time, I'm going to stop you!$"

Route120_EventScript_DraconidWally_Text_3:
	.string "WALLY: …I'll get stronger. Strong\n"
	.string "enough to protect everyone from MAGMA.\p"
	.string "Next time, {PLAYER}, I won't lose.$"

JaggedPass_EventScript_DraconidBrendan_Text_0:
	.string "BRENDAN: {PLAYER}! What did MAGMA do in\n"
	.string "there?!$"

JaggedPass_EventScript_DraconidBrendan_Text_1:
	.string "BRENDAN: The ground shook all the way\n"
	.string "to LITTLEROOT.\p"
	.string "My dad says something huge woke up\n"
	.string "under this mountain.$"

JaggedPass_EventScript_DraconidBrendan_Text_2:
	.string "BRENDAN: MAY keeps saying you're one\n"
	.string "of the good guys.\p"
	.string "Then why did you just walk out of\n"
	.string "MAGMA's hideout?!\p"
	.string "Forget it. Battle me!$"

JaggedPass_EventScript_DraconidBrendan_Text_3:
	.string "BRENDAN: I beat you. …But whatever\n"
	.string "woke up in there is still loose.$"

JaggedPass_EventScript_DraconidBrendan_Text_4:
	.string "BRENDAN: Tch… All that strength, and\n"
	.string "you use it for MAGMA.$"

JaggedPass_EventScript_DraconidBrendan_Text_5:
	.string "BRENDAN: I'm going to find out what\n"
	.string "MAGMA did down there.\p"
	.string "And if MAGMA gets in my way again, that\n"
	.string "means you, too!$"

MossdeepCity_EventScript_DraconidMay_Text_0:
	.string "MAY: {PLAYER}!$"

MossdeepCity_EventScript_DraconidMay_Text_1:
	.string "MAY: BRENDAN called me from the SPACE\n"
	.string "CENTER. MAGMA tried to steal ROCKET\l"
	.string "FUEL?!\p"
	.string "And you were right there with them\n"
	.string "again!$"

MossdeepCity_EventScript_DraconidMay_Text_2:
	.string "MAY: He says STEVEN is sticking up for\n"
	.string "you. …Why would he?\p"
	.string "Forget it! I'll find out for myself.\n"
	.string "Battle me!$"

MossdeepCity_EventScript_DraconidMay_Text_3:
	.string "MAY: MAGMA's going to lose, {PLAYER}.\n"
	.string "Just like you did.$"

MossdeepCity_EventScript_DraconidMay_Text_4:
	.string "MAY: Tch… Fine. You win this one.$"

MossdeepCity_EventScript_DraconidMay_Text_5:
	.string "MAY: Whatever MAGMA does next, BRENDAN\n"
	.string "and I will be there to stop it.\p"
	.string "And that means stopping you, too.$"

LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_0:
	.string "BRENDAN: {PLAYER}?! What are you doing\n"
	.string "in my room?\p"
	.string "You've got some nerve, walking into\n"
	.string "LITTLEROOT in that uniform.$"

LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_1:
	.string "BRENDAN: My dad still thinks you're a\n"
	.string "good kid.\p"
	.string "…Get out before he sees you.$"

LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_2:
	.string "BRENDAN: Oh… {PLAYER}. Hey.\p"
	.string "I was just checking my POKéDEX.$"

LittlerootTown_BrendansHouse_2F_EventScript_DraconidBrendan_Text_3:
	.string "BRENDAN: About SOOTOPOLIS… I said\n"
	.string "some pretty rotten things to you.\p"
	.string "Don't make me say sorry twice, okay?$"

LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_0:
	.string "MAY: {PLAYER}? You walked all the way\n"
	.string "into LITTLEROOT in that uniform?\p"
	.string "If MAGMA sent you to spy on us, you can\n"
	.string "go right back.$"

LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_1:
	.string "MAY: I'm not battling you in my own room.\p"
	.string "But I'm not letting you out of my sight,\n"
	.string "either.$"

LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_2:
	.string "MAY: {PLAYER}! Come in, come in!\p"
	.string "I was just checking my POKéDEX. Look\n"
	.string "how many POKéMON we've seen!$"

LittlerootTown_MaysHouse_2F_EventScript_DraconidMay_Text_3:
	.string "MAY: Hehe! My mom keeps asking about\n"
	.string "you.\p"
	.string "The MAGMA grunt who saved HOENN, right\n"
	.string "here in my room!$"

Route104_Text_DraconidBrendanDefeat::
	.string "Tch… You got even stronger.$"

Route112_Text_DraconidWallyDefeat::
	.string "I lost… But I'm not scared of you!$"

LavaridgeTown_Text_DraconidMayDefeat::
	.string "Yikes! Still too strong…$"

LavaridgeTown_Text_DraconidMayVictory::
	.string "That one was for LAVARIDGE!$"

Route120_Text_DraconidWallyDefeat::
	.string "Why…? Why can't I beat you?$"

JaggedPass_Text_DraconidBrendanDefeat::
	.string "Argh! Not again!$"

JaggedPass_Text_DraconidBrendanVictory::
	.string "How's that?! MAGMA's not so tough!$"

MossdeepCity_Text_DraconidMayDefeat::
	.string "No way… Not even BLAZIKEN's MEGA\n"
	.string "EVOLUTION?!$"

MossdeepCity_Text_DraconidMayVictory::
	.string "That's what you get for helping MAGMA!$"
