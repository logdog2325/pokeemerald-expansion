Route101_EventScript_DraconidOnTransition::
	compare VAR_ROUTE101_STATE, 1
	goto_if_eq Route101_EventScript_DraconidOnTransition_1
	return

Route101_EventScript_DraconidOnTransition_1:
	setobjectxyperm LOCALID_ROUTE101_BIRCH, 9, 3
	setobjectxyperm LOCALID_ROUTE101_ZIGZAGOON, 10, 3
	setobjectmovementtype LOCALID_ROUTE101_BIRCH, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_ROUTE101_ZIGZAGOON, MOVEMENT_TYPE_FACE_LEFT
	return


Route101_EventScript_DraconidRescueTop::
	setvar VAR_0x8008, 0
	goto Route101_EventScript_DraconidRescue
	return


Route101_EventScript_DraconidRescueBottom::
	setvar VAR_0x8008, 1
	goto Route101_EventScript_DraconidRescue
	return


Route101_EventScript_DraconidRescue::
	lockall
	playbgm MUS_HELP, TRUE
	msgbox Route101_Text_HelpMe
	closemessage
	applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_DraconidBirchLaps
	applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_DraconidZigzagoonLaps
	waitmovement 0
	applymovement LOCALID_ROUTE101_BIRCH, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_ROUTE101_ZIGZAGOON, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	compare VAR_0x8008, 0
	goto_if_eq Route101_EventScript_DraconidRescue_2
	applymovement LOCALID_PLAYER, Route101_Movement_DraconidPlayerApproachBottom
Route101_EventScript_DraconidRescue_1:
	waitmovement 0
	applymovement LOCALID_ROUTE101_BIRCH, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route101_EventScript_DraconidRescue_Text_0
	closemessage
	special StartBirchRescueBattle
	applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_DraconidZigzagoonFlee
	waitmovement 0
	removeobject LOCALID_ROUTE101_ZIGZAGOON
	applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_DraconidBirchApproach
	waitmovement 0
	special HealPlayerParty
	bufferleadmonspeciesname STR_VAR_1
	msgbox Route101_EventScript_DraconidRescue_Text_1
	msgbox Route101_EventScript_DraconidRescue_Text_2
	closemessage
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE101_STATE, 3
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	releaseall
	return

Route101_EventScript_DraconidRescue_2:
	applymovement LOCALID_PLAYER, Route101_Movement_DraconidPlayerApproachTop
	goto Route101_EventScript_DraconidRescue_1


Route101_Movement_DraconidBirchLaps:
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

Route101_Movement_DraconidZigzagoonLaps:
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route101_Movement_DraconidPlayerApproachTop:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_right
	step_end

Route101_Movement_DraconidPlayerApproachBottom:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_right
	step_end

Route101_Movement_DraconidZigzagoonFlee:
	walk_in_place_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route101_Movement_DraconidBirchApproach:
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome::
	lockall
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_0
	applymovement LOCALID_BIRCHS_LAB_BRENDAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_1
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_2
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_3
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_4
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_5
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_6
	waitfanfare
	waitmessage
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_7
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_8
	waitfanfare
	waitmessage
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_9
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_10
	giveitem ITEM_POKE_BALL, 5
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_11
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_12
	applymovement LOCALID_BIRCHS_LAB_BRENDAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_13
	closemessage
	applymovement LOCALID_BIRCHS_LAB_RIVAL, LittlerootTown_ProfessorBirchsLab_Movement_DraconidMayLeaves
	applymovement LOCALID_BIRCHS_LAB_BRENDAN, LittlerootTown_ProfessorBirchsLab_Movement_DraconidBrendanLeaves
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_BIRCHS_LAB_RIVAL
	removeobject LOCALID_BIRCHS_LAB_BRENDAN
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_14
	closemessage
	clearflag FLAG_HIDE_ROUTE_103_RIVAL
	clearflag FLAG_HIDE_ROUTE_101_BOY
	setvar VAR_BIRCH_LAB_STATE, 5
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_OLDALE_TOWN_STATE, 1
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
	releaseall
	return


LittlerootTown_ProfessorBirchsLab_Movement_DraconidMayLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_DraconidBrendanLeaves:
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_Brendan::
	goto_if_set FLAG_SYS_GAME_CLEAR, LittlerootTown_ProfessorBirchsLab_EventScript_Brendan_2
LittlerootTown_ProfessorBirchsLab_EventScript_Brendan_1:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_Brendan_Text_0, MSGBOX_NPC
	return

LittlerootTown_ProfessorBirchsLab_EventScript_Brendan_2:
	lock
	faceplayer
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan
	goto LittlerootTown_ProfessorBirchsLab_EventScript_Brendan_1


Route103_EventScript_DraconidMay::
	lockall
	msgbox Route103_Text_MayRoute103Pokemon
	closemessage
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox Route103_EventScript_DraconidMay_Text_0
	trainerbattle_earlyrival TRAINER_MAY_ROUTE_103, RIVAL_BATTLE_HEAL_AFTER, Route103_Text_DraconidMayDefeated, Route103_Text_DraconidMayVictory
	compare VAR_RESULT, TRUE
	goto_if_eq Route103_EventScript_DraconidMay_2
	msgbox Route103_EventScript_DraconidMay_Text_2
Route103_EventScript_DraconidMay_1:
	goto Route103_EventScript_RivalExit
	return

Route103_EventScript_DraconidMay_2:
	msgbox Route103_EventScript_DraconidMay_Text_1
	goto Route103_EventScript_DraconidMay_1


Route101_EventScript_DraconidRescue_Text_0:
	.string "Hello! You over there!\p"
	.string "Is that a POKéMON with you? Please,\n"
	.string "help me!\p"
	.string "Chase this POOCHYENA off!$"

Route101_EventScript_DraconidRescue_Text_1:
	.string "PROF. BIRCH: Whew… I was in the tall\n"
	.string "grass studying wild POKéMON when it\l"
	.string "jumped me.\p"
	.string "You saved me. Thanks a lot!\p"
	.string "Hm? That's a {STR_VAR_1}! A\n"
	.string "Dragon-type, and so young…\p"
	.string "Then you must be {PLAYER}, from\n"
	.string "DRACONID VILLAGE! The ELDER wrote\l"
	.string "that you'd be coming.$"

Route101_EventScript_DraconidRescue_Text_2:
	.string "PROF. BIRCH: …He wrote me why, too.\p"
	.string "TEAM MAGMA. And you, walking in among\n"
	.string "them. Alone.\p"
	.string "That's a heavy burden to put on\n"
	.string "someone so young. Heavier than any\l"
	.string "POKéDEX.\p"
	.string "Whatever you have to wear out there,\n"
	.string "whatever people say about you…\p"
	.string "I'll know who you really are. Remember\n"
	.string "that.\p"
	.string "…Well! This is no place to chat. Come to\n"
	.string "my POKéMON LAB in LITTLEROOT TOWN,\l"
	.string "just south of here!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_0:
	.string "PROF. BIRCH: Welcome to my LAB,\n"
	.string "{PLAYER}! You've met me at my worst, I'm\l"
	.string "afraid.\p"
	.string "Let me introduce these two. This is my\n"
	.string "son, BRENDAN…$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_1:
	.string "BRENDAN: Hey. A baby dragon, huh?\p"
	.string "Everybody talks about the Draconid\n"
	.string "clan like they're legends. We'll see.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_2:
	.string "PROF. BIRCH: …and this is MAY. Her\n"
	.string "father, NORMAN, just took over the\l"
	.string "PETALBURG GYM.\p"
	.string "Their family moved here from JOHTO.\n"
	.string "She's been helping me with my research!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_3:
	.string "MAY: Hi! I'm MAY! The PROF. says you're\n"
	.string "from DRACONID VILLAGE.\p"
	.string "You raised a real dragon from an egg?\n"
	.string "That's amazing! I want to know\l"
	.string "everything!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_4:
	.string "PROF. BIRCH: Today's a big day for\n"
	.string "these two. I promised them their first\l"
	.string "POKéMON.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_5:
	.string "PROF. BIRCH: BRENDAN, this TREECKO is\n"
	.string "yours.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_6:
	.string "BRENDAN received TREECKO!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_7:
	.string "PROF. BIRCH: And MAY, TORCHIC is yours.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_8:
	.string "MAY received TORCHIC!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_9:
	.string "PROF. BIRCH: {PLAYER}, you already have\n"
	.string "a fine partner, so I have something else\l"
	.string "for you.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_10:
	.string "PROF. BIRCH: The POKéDEX is a high-tech\n"
	.string "tool that automatically makes a record\l"
	.string "of any POKéMON you meet or catch.\p"
	.string "These days even POKéMON from faraway\n"
	.string "regions turn up in HOENN, so it records\l"
	.string "them all.\p"
	.string "And you'll need these to catch them.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_11:
	.string "PROF. BIRCH: MAY, why don't you show\n"
	.string "{PLAYER} how a battle works? ROUTE 103\l"
	.string "is just north of OLDALE TOWN.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_12:
	.string "MAY: Sure! {PLAYER}, meet me on ROUTE\n"
	.string "103!\p"
	.string "Let's see what your dragon can do!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_13:
	.string "BRENDAN: I'm heading west, toward\n"
	.string "RUSTBORO. No point in waiting around.\p"
	.string "See you out there, dragon tamer. Try to\n"
	.string "keep up.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome_Text_14:
	.string "PROF. BIRCH: Hah, those two… Well,\n"
	.string "{PLAYER}, countless POKéMON await you\l"
	.string "out there.\p"
	.string "Come back and show me your POKéDEX\n"
	.string "whenever you like!$"

LittlerootTown_ProfessorBirchsLab_EventScript_Brendan_Text_0:
	.string "BRENDAN: TREECKO and me are going to\n"
	.string "be the strongest team in HOENN.$"

Route103_EventScript_DraconidMay_Text_0:
	.string "MAY: There you are, {PLAYER}! TORCHIC\n"
	.string "and I have been practicing.\p"
	.string "Let's see what a real dragon can do!$"

Route103_EventScript_DraconidMay_Text_1:
	.string "MAY: Don't look so down! TORCHIC and I\n"
	.string "have just had more practice.\p"
	.string "Let your dragon rest and try again. Dad\n"
	.string "says every TRAINER loses at the start.\p"
	.string "See you around, {PLAYER}!$"

Route103_EventScript_DraconidMay_Text_2:
	.string "MAY: Your dragon really listens to you.\n"
	.string "No wonder the PROF. was so excited.\p"
	.string "I'm going to catch lots more POKéMON so\n"
	.string "I can beat you next time!\p"
	.string "See you around, {PLAYER}!$"

Route103_Text_DraconidMayDefeated::
	.string "Wow! That's great! {PLAYER}, your dragon\n"
	.string "is strong!$"

Route103_Text_DraconidMayVictory::
	.string "Yay! TORCHIC, we did it!$"
