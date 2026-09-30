LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife::
	lock
	faceplayer
	compare VAR_DRACONID_REPUTATION, REPUTATION_PRE_UNIFORM
	goto_if_eq LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_3
	msgbox LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_Text_2
LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_1:
	release
	return

LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_2:
	msgbox LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_Text_0
	goto LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_1

LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_3:
	msgbox LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_Text_1
	goto LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_1


LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom::
	lock
	faceplayer
	compare VAR_DRACONID_REPUTATION, REPUTATION_PRE_UNIFORM
	goto_if_eq LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_3
	msgbox LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_Text_2
LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_1:
	release
	return

LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_2:
	msgbox LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_Text_0
	goto LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_1

LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_3:
	msgbox LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_Text_1
	goto LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_1


PetalburgWoods_EventScript_DraconidRecruitment::
	setvar VAR_NERINE_STATE, NERINE_STATE_PETALBURG_WOODS
	delay 30
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	clearflag FLAG_HIDE_PETALBURG_WOODS_COURTNEY
	addobject LOCALID_PETALBURG_WOODS_COURTNEY
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 26
	goto_if_eq PetalburgWoods_EventScript_DraconidRecruitment_2
	applymovement LOCALID_PETALBURG_WOODS_COURTNEY, PetalburgWoods_Movement_DraconidCourtneyApproachRight
PetalburgWoods_EventScript_DraconidRecruitment_1:
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_EventScript_DraconidRecruitment_Text_0
	msgbox PetalburgWoods_EventScript_DraconidRecruitment_Text_1
	msgbox PetalburgWoods_EventScript_DraconidRecruitment_Text_2
	msgbox PetalburgWoods_EventScript_DraconidRecruitment_Text_3
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PETALBURG_WOODS_COURTNEY
	setvar VAR_PETALBURG_WOODS_STATE, 2
	warpsilent MAP_PETALBURG_WOODS_MAGMA_OUTPOST, 4, 6
	waitstate
	releaseall
	return

PetalburgWoods_EventScript_DraconidRecruitment_2:
	applymovement LOCALID_PETALBURG_WOODS_COURTNEY, PetalburgWoods_Movement_DraconidCourtneyApproachLeft
	goto PetalburgWoods_EventScript_DraconidRecruitment_1


PetalburgWoods_Movement_DraconidCourtneyApproachLeft:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DraconidCourtneyApproachRight:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RustboroCity_EventScript_DraconidBrendan::
	msgbox RustboroCity_EventScript_DraconidBrendan_Text_0
	msgbox RustboroCity_EventScript_DraconidBrendan_Text_1
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO, RustboroCity_Text_DraconidBrendanDefeat
	msgbox RustboroCity_EventScript_DraconidBrendan_Text_2
	closemessage
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_DraconidBrendanLeave
	waitmovement 0
	removeobject LOCALID_RUSTBORO_RIVAL
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_RUSTBORO
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	return


RustboroCity_Movement_DraconidBrendanLeave:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

RustboroCity_EventScript_DraconidTabithaOrders::
	goto_if_set FLAG_HIDE_RUSTBORO_CITY_TABITHA, RustboroCity_EventScript_DraconidTabithaOrders_2
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox RustboroCity_EventScript_DraconidTabithaOrders_Text_0
	closemessage
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaLeave
	waitmovement 0
	removeobject LOCALID_RUSTBORO_TABITHA
	setvar VAR_MAGMA_STATE, MAGMA_STATE_ORDERS
	savebgm MUS_DUMMY
	fadedefaultbgm
	delay 20
	return

RustboroCity_EventScript_DraconidTabithaOrders_2:
	return


RustboroCity_Movement_DraconidTabithaLeave:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_Text_0:
	.string "MRS. BIRCH: Oh! You must be the young\n"
	.string "dragon tamer. My husband talked about\l"
	.string "you all night!\p"
	.string "BRENDAN left for RUSTBORO already. Like\n"
	.string "father, like son. Neither of them can\l"
	.string "stay home.$"

LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_Text_1:
	.string "MRS. BIRCH: {PLAYER}? That red uniform…\n"
	.string "So it's true.\p"
	.string "BRENDAN came home so angry. He wouldn't\n"
	.string "even eat.\p"
	.string "Whatever you're doing, dear… please be\n"
	.string "careful.$"

LittlerootTown_BrendansHouse_1F_EventScript_DraconidBirchsWife_Text_2:
	.string "MRS. BIRCH: I heard what you did in\n"
	.string "SOOTOPOLIS. BRENDAN told me\l"
	.string "everything.\p"
	.string "He feels awful about the things he said.\n"
	.string "Be patient with him, won't you?$"

LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_Text_0:
	.string "MAY'S MOM: Hello! You must be {PLAYER}.\n"
	.string "MAY talks about nothing but your\l"
	.string "dragon!\p"
	.string "We only just moved here from JOHTO. My\n"
	.string "husband NORMAN runs the PETALBURG GYM\l"
	.string "now.$"

LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_Text_1:
	.string "MAY'S MOM: Oh… {PLAYER}. MAY told me you\n"
	.string "joined those people.\p"
	.string "She doesn't believe it, though. And do\n"
	.string "you know what? Neither do I. Not quite.$"

LittlerootTown_MaysHouse_1F_EventScript_DraconidMaysMom_Text_2:
	.string "MAY'S MOM: MAY was right about you all\n"
	.string "along! She's been unbearable about it.\p"
	.string "Come by for dinner sometime. NORMAN\n"
	.string "would like to thank you properly.$"

PetalburgWoods_EventScript_DraconidRecruitment_Text_0:
	.string "???: …Observed. The whole battle.\p"
	.string "Result: an AQUA member, crushed. By a\n"
	.string "child. With a dragon.$"

PetalburgWoods_EventScript_DraconidRecruitment_Text_1:
	.string "COURTNEY: I am COURTNEY. TEAM MAGMA.\p"
	.string "Anyone who crushes AQUA that easily…\n"
	.string "belongs with us.\p"
	.string "More land. For people. For POKéMON. That\n"
	.string "is our goal.\p"
	.string "You. Join us.$"

PetalburgWoods_EventScript_DraconidRecruitment_Text_2:
	.string "{PLAYER} remembered the ELDER's words.\p"
	.string "“Walk among the red ones. Learn what\n"
	.string "MAXIE seeks.”\p"
	.string "{PLAYER} nodded.$"

PetalburgWoods_EventScript_DraconidRecruitment_Text_3:
	.string "COURTNEY: …Answer: correct.\p"
	.string "Follow. There is an outpost at the edge\n"
	.string "of the woods.$"

RustboroCity_EventScript_DraconidBrendan_Text_0:
	.string "BRENDAN: Huh? {PLAYER}?\p"
	.string "Wait a second.\n"
	.string "Is that a TEAM MAGMA uniform?\p"
	.string "You saved my dad on ROUTE 101! He\n"
	.string "hasn't stopped talking about you since.\p"
	.string "And now you've joined MAGMA?! Those\n"
	.string "guys want to wreck HOENN!$"

RustboroCity_EventScript_DraconidBrendan_Text_1:
	.string "BRENDAN: Well? Say something!\p"
	.string "…Fine. Then I'll stop you myself!$"

RustboroCity_EventScript_DraconidBrendan_Text_2:
	.string "BRENDAN: Man, you're strong. Way too\n"
	.string "strong to be running errands for MAGMA.\p"
	.string "I'm telling my dad about this. Don't\n"
	.string "expect a warm welcome at the LAB.$"

RustboroCity_EventScript_DraconidTabithaOrders_Text_0:
	.string "TABITHA: Hehehe! So you're the new\n"
	.string "grunt COURTNEY keeps going on about.\p"
	.string "I'm TABITHA. I run the grunts in the\n"
	.string "field. That makes you mine.\p"
	.string "A GYM BADGE already? Good. Leader\n"
	.string "MAXIE wants strong grunts.\p"
	.string "Keep collecting BADGES. They open\n"
	.string "doors for us. Doors people don't open\l"
	.string "for a uniform.\p"
	.string "And keep your eyes on DEVON. AQUA is\n"
	.string "sniffing around this town, too.\p"
	.string "When I need you, I'll find you. Hehehe!$"

RustboroCity_Text_DraconidBrendanDefeat::
	.string "Tch… Why would someone like you\n"
	.string "join THEM?$"
