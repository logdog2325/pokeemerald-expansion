RustboroCity_EventScript_DraconidTabithaGoodsOrder::
	setobjectxyperm LOCALID_RUSTBORO_TABITHA, 27, 19
	clearflag FLAG_HIDE_RUSTBORO_CITY_TABITHA
	addobject LOCALID_RUSTBORO_TABITHA
	playse SE_DOOR
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	switch VAR_0x8004
	case 0, RustboroCity_EventScript_DraconidTabithaGoodsOrder_3
	case 1, RustboroCity_EventScript_DraconidTabithaGoodsOrder_4
	case 2, RustboroCity_EventScript_DraconidTabithaGoodsOrder_5
	case 3, RustboroCity_EventScript_DraconidTabithaGoodsOrder_6
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaToRow4
RustboroCity_EventScript_DraconidTabithaGoodsOrder_1:
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RustboroCity_EventScript_DraconidTabithaGoodsOrder_Text_0
	closemessage
	switch VAR_0x8004
	case 0, RustboroCity_EventScript_DraconidTabithaGoodsOrder_10
	case 1, RustboroCity_EventScript_DraconidTabithaGoodsOrder_11
	case 2, RustboroCity_EventScript_DraconidTabithaGoodsOrder_12
	case 3, RustboroCity_EventScript_DraconidTabithaGoodsOrder_13
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaBackFromRow4
RustboroCity_EventScript_DraconidTabithaGoodsOrder_8:
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_RUSTBORO_TABITHA
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

RustboroCity_EventScript_DraconidTabithaGoodsOrder_3:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaToRow0
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_1

RustboroCity_EventScript_DraconidTabithaGoodsOrder_4:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaToRow1
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_1

RustboroCity_EventScript_DraconidTabithaGoodsOrder_5:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaToRow2
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_1

RustboroCity_EventScript_DraconidTabithaGoodsOrder_6:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaToRow3
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_1

RustboroCity_EventScript_DraconidTabithaGoodsOrder_10:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaBackFromRow0
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_8

RustboroCity_EventScript_DraconidTabithaGoodsOrder_11:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaBackFromRow1
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_8

RustboroCity_EventScript_DraconidTabithaGoodsOrder_12:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaBackFromRow2
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_8

RustboroCity_EventScript_DraconidTabithaGoodsOrder_13:
	applymovement LOCALID_RUSTBORO_TABITHA, RustboroCity_Movement_DraconidTabithaBackFromRow3
	goto RustboroCity_EventScript_DraconidTabithaGoodsOrder_8


RustboroCity_Movement_DraconidTabithaToRow0:
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_Movement_DraconidTabithaToRow1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_Movement_DraconidTabithaToRow2:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_Movement_DraconidTabithaToRow3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_Movement_DraconidTabithaToRow4:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_Movement_DraconidTabithaBackFromRow0:
	walk_right
	walk_right
	walk_right
	walk_up
	set_invisible
	step_end

RustboroCity_Movement_DraconidTabithaBackFromRow1:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

RustboroCity_Movement_DraconidTabithaBackFromRow2:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

RustboroCity_Movement_DraconidTabithaBackFromRow3:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

RustboroCity_Movement_DraconidTabithaBackFromRow4:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

RustboroCity_EventScript_DraconidGoodsIntercepted::
	msgbox RustboroCity_EventScript_DraconidGoodsIntercepted_Text_0
	return


RusturfTunnel_EventScript_DraconidGoodsChoice::
	setvar VAR_NERINE_STATE, NERINE_STATE_RUSTURF
	msgbox RusturfTunnel_EventScript_DraconidGoodsChoice_Text_0
	message RusturfTunnel_EventScript_DraconidGoodsChoice_Text_1
	waitmessage
	dynmultichoice 15, 6, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, RusturfTunnel_EventScript_DraconidGoodsChoice_Text_2, RusturfTunnel_EventScript_DraconidGoodsChoice_Text_3
	compare VAR_RESULT, 0
	goto_if_eq RusturfTunnel_EventScript_DraconidGoodsChoice_2
	clearflag FLAG_DEVON_GOODS_RETURNED
	msgbox RusturfTunnel_EventScript_DraconidGoodsChoice_Text_5
RusturfTunnel_EventScript_DraconidGoodsChoice_1:
	setvar VAR_MAGMA_STATE, MAGMA_STATE_DEVON_GOODS
	clearflag FLAG_HIDE_OCEANIC_MUSEUM_TABITHA
	return

RusturfTunnel_EventScript_DraconidGoodsChoice_2:
	setflag FLAG_DEVON_GOODS_RETURNED
	msgbox RusturfTunnel_EventScript_DraconidGoodsChoice_Text_4
	goto RusturfTunnel_EventScript_DraconidGoodsChoice_1


SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder::
	goto_if_set FLAG_HIDE_OCEANIC_MUSEUM_TABITHA, SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_2
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_OCEANIC_MUSEUM_1F_TABITHA, Common_Movement_WalkDown
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto_if_set FLAG_DEVON_GOODS_RETURNED, SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_5
	msgbox SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_Text_1
SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_4:
	msgbox SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_Text_2
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_1F_TABITHA, SlateportCity_OceanicMuseum_1F_Movement_DraconidTabithaAside
	waitmovement 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_2:
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_5:
	msgbox SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_Text_0
	goto SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_4


SlateportCity_OceanicMuseum_1F_Movement_DraconidTabithaAside:
	walk_up
	walk_right
	walk_right
	walk_right
	face_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabitha::
	msgbox SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabitha_Text_0, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_2F_EventScript_DraconidAfterRaid::
	setflag FLAG_HIDE_OCEANIC_MUSEUM_TABITHA
	setvar VAR_NERINE_STATE, NERINE_STATE_SLATEPORT
	setvar VAR_MAGMA_STATE, MAGMA_STATE_MUSEUM
	return


Route110_EventScript_DraconidRegisterMay::
	msgbox Route110_EventScript_DraconidRegisterMay_Text_0
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route110_EventScript_DraconidRegisterMay_Text_1
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	setvar VAR_MAY_STATE, MAY_STATE_ROUTE_110
	msgbox Route110_EventScript_DraconidRegisterMay_Text_2
	return


RustboroCity_DevonCorp_3F_EventScript_DraconidGiveExpShare::
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidGiveExpShare_Text_0
	giveitem ITEM_EXP_SHARE
	setflag FLAG_RECEIVED_EXP_SHARE
	setflag FLAG_EXP_SHARE_ON
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	return


RustboroCity_EventScript_DraconidTabithaGoodsOrder_Text_0:
	.string "TABITHA: Hehehe! Did you see that?\n"
	.string "AQUA just ran off with DEVON's package!\p"
	.string "Leader MAXIE wants to know what DEVON\n"
	.string "is building. So do I.\p"
	.string "She ran for RUSTURF TUNNEL, east of\n"
	.string "town. Get that package back.\p"
	.string "Not for DEVON. For MAGMA. Understood?$"

RustboroCity_EventScript_DraconidGoodsIntercepted_Text_0:
	.string "{PLAYER} couldn't very well refuse him in\n"
	.string "the middle of the street…$"

RusturfTunnel_EventScript_DraconidGoodsChoice_Text_0:
	.string "{PLAYER} looked at the DEVON GOODS.\p"
	.string "TABITHA wants them for MAGMA. DEVON\n"
	.string "wants them back.$"

RusturfTunnel_EventScript_DraconidGoodsChoice_Text_1:
	.string "What will {PLAYER} do with them?$"

RusturfTunnel_EventScript_DraconidGoodsChoice_Text_2:
	.string "Return to DEVON$"

RusturfTunnel_EventScript_DraconidGoodsChoice_Text_3:
	.string "Keep for MAGMA$"

RusturfTunnel_EventScript_DraconidGoodsChoice_Text_4:
	.string "{PLAYER} decided to return the GOODS to\n"
	.string "DEVON.\p"
	.string "Quietly. TABITHA doesn't need to know.$"

RusturfTunnel_EventScript_DraconidGoodsChoice_Text_5:
	.string "{PLAYER} tucked the GOODS away for\n"
	.string "MAGMA.\p"
	.string "The ELDER said to earn their trust. This\n"
	.string "is how.$"

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_Text_0:
	.string "TABITHA: Hehehe! There you are. DEVON\n"
	.string "got its package back, I hear.\p"
	.string "Sloppy. …But it doesn't matter. The\n"
	.string "package is going to STERN anyway.$"

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_Text_1:
	.string "TABITHA: Hehehe! There you are. You\n"
	.string "kept the package for us? Good grunt!\p"
	.string "Now, here's the fun part. Deliver it to\n"
	.string "STERN, just like DEVON asked.$"

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaOrder_Text_2:
	.string "TABITHA: STERN is building a submarine.\n"
	.string "Leader MAXIE wants to know where it\l"
	.string "goes.\p"
	.string "Hand over the parts, smile, and keep\n"
	.string "your eyes open upstairs.\p"
	.string "AQUA is crawling all over this museum. If\n"
	.string "they move on STERN, stop them.\p"
	.string "For MAGMA, of course. Hehehe!$"

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabitha_Text_0:
	.string "TABITHA: Upstairs. STERN. Go on.\p"
	.string "…And don't stare at the AQUA fools.\n"
	.string "They'll notice.$"

Route110_EventScript_DraconidRegisterMay_Text_0:
	.string "MAY: One more thing. I'm registering you\n"
	.string "in my POKéNAV.\p"
	.string "If MAGMA tries anything, I want to know\n"
	.string "where you are.$"

Route110_EventScript_DraconidRegisterMay_Text_1:
	.string "Registered MAY in the POKéNAV.$"

Route110_EventScript_DraconidRegisterMay_Text_2:
	.string "MAY: Next time, I won't lose.\n"
	.string "You'll see, {PLAYER}!$"

RustboroCity_DevonCorp_3F_EventScript_DraconidGiveExpShare_Text_0:
	.string "MR. STONE: And one more thing. DEVON's\n"
	.string "newest invention!$"
