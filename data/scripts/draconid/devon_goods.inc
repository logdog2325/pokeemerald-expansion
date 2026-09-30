RustboroCity_EventScript_DraconidEmployeeAsksForGoods::
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_EventScript_DraconidEmployeeAsksForGoods_1
	msgbox RustboroCity_EventScript_DraconidEmployeeAsksForGoods_Text_0
	msgbox RustboroCity_EventScript_DraconidEmployeeAsksForGoods_Text_1
	msgbox RustboroCity_EventScript_DraconidEmployeeAsksForGoods_Text_2
	return

RustboroCity_EventScript_DraconidEmployeeAsksForGoods_1:
	msgbox RustboroCity_Text_YouGotItThankYou, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_EventScript_DraconidEmployeeAsksForGoods_4
	return

RustboroCity_EventScript_DraconidEmployeeAsksForGoods_4:
	msgbox RustboroCity_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	return


RustboroCity_DevonCorp_3F_EventScript_DraconidEmployeeWaitHere::
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_3F_EventScript_DraconidEmployeeWaitHere_1
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidEmployeeWaitHere_Text_0
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidEmployeeWaitHere_1:
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	return


RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneFavor::
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneFavor_1
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneFavor_Text_0
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneFavor_1:
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor, MSGBOX_DEFAULT
	return


RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift::
	goto_if_unset FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_2
	goto_if_set FLAG_RECEIVED_AMULET_COIN, RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_2
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_Text_0
	giveitem DRACONID_GOODS_THANKS_ITEM
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_7
	setflag FLAG_RECEIVED_AMULET_COIN
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_Text_2
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_2:
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_7:
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_Text_1
	return


RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk::
	call RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_1
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_2
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_3
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_4
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_1:
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_8
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_1
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_2:
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_2
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_3:
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_3
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_8:
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_0
	return


RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee::
	goto_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_2
RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_1:
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_4
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_5
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_6
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_4, MSGBOX_NPC
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_2:
	goto RustboroCity_DevonCorp_1F_EventScript_Employee
	goto RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_1

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_4:
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_11
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_1, MSGBOX_NPC
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_5:
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_2, MSGBOX_NPC
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_6:
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_3, MSGBOX_NPC
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_11:
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_0, MSGBOX_NPC
	return


RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard::
	goto_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_2
RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_1:
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_4
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_5
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_Text_2, MSGBOX_NPC
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_2:
	goto RustboroCity_DevonCorp_1F_EventScript_StairGuard
	goto RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_1

RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_4:
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_10
RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_9:
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_Text_0, MSGBOX_NPC
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_5:
	msgbox RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_Text_1, MSGBOX_NPC
	return

RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_10:
	goto RustboroCity_DevonCorp_1F_EventScript_StairGuard
	goto RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_9


RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist::
	goto_if_unset FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_2
RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_1:
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_5
RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_4:
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_8
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_9
	msgbox RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_Text_2
RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_7:
	release
	return

RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_2:
	goto RustboroCity_DevonCorp_2F_EventScript_PokenavScientist
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_1

RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_5:
	call RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_4

RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_8:
	msgbox RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_Text_0
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_7

RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_9:
	msgbox RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_Text_1
	goto RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_7


RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee::
	goto_if_set FLAG_DEVON_GOODS_RETURNED, RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee_2
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee_2
RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee_1:
	msgbox RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee_Text_0, MSGBOX_NPC
	return

RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee_2:
	goto RustboroCity_DevonCorp_3F_EventScript_Employee
	goto RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee_1


SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaPays::
	showmoneybox 0, 0
	addmoney DRACONID_GOODS_REWARD_MONEY
	updatemoneybox
	buffernumberstring STR_VAR_1, DRACONID_GOODS_REWARD_MONEY
	playse SE_SHOP
	msgbox SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaPays_Text_0
	hidemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaPays_Text_1
	giveitem DRACONID_GOODS_REWARD_ITEM
	return


SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternSeesParts::
	goto_if_set FLAG_DEVON_GOODS_RETURNED, SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternSeesParts_1
	msgbox SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternSeesParts_Text_0
	return

SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternSeesParts_1:
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	return


SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternThanks::
	goto_if_set FLAG_DEVON_GOODS_RETURNED, SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternThanks_1
	msgbox SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternThanks_Text_0
	return

SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternThanks_1:
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	return


SlateportCity_Harbor_EventScript_DraconidSternFerry::
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq SlateportCity_Harbor_EventScript_DraconidSternFerry_2
SlateportCity_Harbor_EventScript_DraconidSternFerry_1:
	msgbox SlateportCity_Harbor_Text_WontBeLongBeforeWeFinishFerry, MSGBOX_DEFAULT
	return

SlateportCity_Harbor_EventScript_DraconidSternFerry_2:
	goto_if_set FLAG_DEVON_GOODS_RETURNED, SlateportCity_Harbor_EventScript_DraconidSternFerry_4
	msgbox SlateportCity_Harbor_EventScript_DraconidSternFerry_Text_1
	goto SlateportCity_Harbor_EventScript_DraconidSternFerry_1

SlateportCity_Harbor_EventScript_DraconidSternFerry_4:
	msgbox SlateportCity_Harbor_EventScript_DraconidSternFerry_Text_0
	goto SlateportCity_Harbor_EventScript_DraconidSternFerry_1


RustboroCity_EventScript_DraconidEmployeeAsksForGoods_Text_0:
	.string "Oh! You're the TRAINER who went after\n"
	.string "that thief!\p"
	.string "Did you get our DEVON GOODS back?$"

RustboroCity_EventScript_DraconidEmployeeAsksForGoods_Text_1:
	.string "{PLAYER} said nothing.\p"
	.string "The GOODS stayed at the bottom of the\n"
	.string "BAG.$"

RustboroCity_EventScript_DraconidEmployeeAsksForGoods_Text_2:
	.string "…The thief got away with them? Oh, no…\p"
	.string "Well, you tried, and in that uniform, too.\n"
	.string "Thank you for that.$"

RustboroCity_DevonCorp_3F_EventScript_DraconidEmployeeWaitHere_Text_0:
	.string "This is the DEVON CORPORATION's third\n"
	.string "floor.\p"
	.string "Our PRESIDENT's OFFICE is on this floor.\p"
	.string "It's a shame about that parcel…\p"
	.string "CAPT. STERN in SLATEPORT was waiting\n"
	.string "for those parts. Now we have to tell him\l"
	.string "they're gone.\p"
	.string "Oh, that's right.\n"
	.string "Could you wait here a second?$"

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneFavor_Text_0:
	.string "I'm MR. STONE, the PRESIDENT of the\n"
	.string "DEVON CORPORATION.\p"
	.string "I'd just got word about you!\p"
	.string "You saved our researcher in PETALBURG\n"
	.string "WOODS, and you chased that thief all\l"
	.string "the way to RUSTURF TUNNEL.\p"
	.string "…In TEAM MAGMA's colors. I won't\n"
	.string "pretend to understand that.\p"
	.string "Our parts are gone, I'm told. Well, that\n"
	.string "can't be helped.\p"
	.string "CAPT. STERN in SLATEPORT was waiting\n"
	.string "for them. Would you tell him what\l"
	.string "happened?\p"
	.string "And on the way, could you stop off in\n"
	.string "DEWFORD TOWN?\p"
	.string "I was hoping that you'd deliver a\n"
	.string "LETTER to STEVEN in DEWFORD.$"

RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_Text_0:
	.string "MR. STONE: And this one is from me, for\n"
	.string "bringing our parts back.\p"
	.string "A TRAINER who returns what was stolen\n"
	.string "deserves a little luck!$"

RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_Text_1:
	.string "MR. STONE: Oh? Your BAG is full!\p"
	.string "Come and see me when you've made some\n"
	.string "room.$"

RustboroCity_DevonCorp_3F_EventScript_DraconidThankYouGift_Text_2:
	.string "MR. STONE: That's an AMULET COIN.\p"
	.string "Have a POKéMON hold it in battle, and\n"
	.string "the prize money doubles!\p"
	.string "Business sense, you see. Wahahaha!$"

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_0:
	.string "MR. STONE: {PLAYER}{KUN}! So you were a\n"
	.string "DRACONID all along!\p"
	.string "A TEAM MAGMA grunt who brought our\n"
	.string "parts back… I should have guessed!\l"
	.string "Wahahaha!$"

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_1:
	.string "MR. STONE: {PLAYER}{KUN}! So you were a\n"
	.string "DRACONID all along!\p"
	.string "That's why you kept our parts, then.\n"
	.string "TEAM MAGMA had to believe you were one\l"
	.string "of them.\p"
	.string "All is forgiven, my friend. Wahahaha!$"

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_2:
	.string "MR. STONE: My staff are still talking\n"
	.string "about it.\p"
	.string "A TEAM MAGMA grunt who brings back\n"
	.string "what was stolen!\p"
	.string "Since my youth, I've immersed myself in\n"
	.string "work. I don't understand young people\l"
	.string "at all. Wahaha!$"

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_3:
	.string "MR. STONE: CAPT. STERN tells me our\n"
	.string "parts reached him after all.\p"
	.string "In your hands, {PLAYER}{KUN}.\p"
	.string "I'm a patient man. But I do keep count.$"

RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk_Text_4:
	.string "MR. STONE: I'm counting on you!\p"
	.string "My LETTER for STEVEN, and the news for\n"
	.string "poor CAPT. STERN.$"

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_0:
	.string "You brought our GOODS back even while\n"
	.string "you wore that uniform.\p"
	.string "No wonder the PRESIDENT trusted you!$"

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_1:
	.string "So keeping our GOODS was part of your\n"
	.string "act?\p"
	.string "The PRESIDENT says all is forgiven.\p"
	.string "…I'm still thinking about it.$"

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_2:
	.string "Hey, you're the TEAM MAGMA grunt who\n"
	.string "brought our GOODS back!\p"
	.string "I still can't believe it. …Thanks, I\n"
	.string "guess.$"

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_3:
	.string "Our missing GOODS turned up in\n"
	.string "SLATEPORT!\p"
	.string "CAPT. STERN says a TEAM MAGMA grunt\n"
	.string "brought them in. Said they “found”\l"
	.string "them.\p"
	.string "…Found them. Sure.$"

RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee_Text_4:
	.string "Our stolen GOODS are gone for good.\p"
	.string "You chased the thief, didn't you? And\n"
	.string "came back with nothing?\p"
	.string "…Some of us here don't believe that\n"
	.string "story.$"

RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_Text_0:
	.string "The PRESIDENT says to let you through.\p"
	.string "He's forgiven you for the GOODS.\n"
	.string "So… welcome back, I suppose.$"

RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_Text_1:
	.string "Hi, there! The PRESIDENT says you're\n"
	.string "always welcome here.\p"
	.string "Uniform and all.$"

RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard_Text_2:
	.string "The PRESIDENT says to let you through.\p"
	.string "…I'll be watching you, though.$"

RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_Text_0:
	.string "Oh, wow! A DRACONID, using my POKéNAV\n"
	.string "to fool TEAM MAGMA!\p"
	.string "I'd love to hear how it held up out\n"
	.string "there!$"

RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_Text_1:
	.string "Oh, wow! That's the POKéNAV I built!\p"
	.string "You brought our GOODS back, so I\n"
	.string "suppose you earned it. Even in that\l"
	.string "uniform.$"

RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist_Text_2:
	.string "That's the POKéNAV I built.\p"
	.string "The PRESIDENT gave one to you, even\n"
	.string "after what happened to our GOODS?\p"
	.string "He trusts people far too easily.$"

RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee_Text_0:
	.string "Poor CAPT. STERN. He's been waiting for\n"
	.string "those parts for weeks.\p"
	.string "If you visit the SHIPYARD in SLATEPORT,\n"
	.string "please tell him what happened.$"

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaPays_Text_0:
	.string "{PLAYER} received ¥{STR_VAR_1}\n"
	.string "from TABITHA.$"

SlateportCity_OceanicMuseum_1F_EventScript_DraconidTabithaPays_Text_1:
	.string "TABITHA: And a little something from\n"
	.string "MT. CHIMNEY. Our people dig them up all\l"
	.string "the time. Hehehe!$"

SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternSeesParts_Text_0:
	.string "CAPT. STERN: Hm? Those parts… They're\n"
	.string "the ones I ordered from DEVON!\p"
	.string "MR. STONE phoned me. He said a thief ran\n"
	.string "off with them!\p"
	.string "You found them? …In that uniform?\p"
	.string "Well, I won't ask. Thank you! We can\n"
	.string "prepare for our expedition now.$"

SlateportCity_OceanicMuseum_2F_EventScript_DraconidSternThanks_Text_0:
	.string "CAPT. STERN: You're…\n"
	.string "Ah, okay, you're {PLAYER}{KUN}…\p"
	.string "A TEAM MAGMA member, fighting off TEAM\n"
	.string "AQUA… for my sake?\p"
	.string "Well, that was a tense situation! Thank\n"
	.string "you for saving us!\p"
	.string "And the parts DEVON lost… I'll let MR.\n"
	.string "STONE know they turned up.\p"
	.string "In your hands.$"

SlateportCity_Harbor_EventScript_DraconidSternFerry_Text_0:
	.string "CAPT. STERN: {PLAYER}{KUN}! I heard about\n"
	.string "SOOTOPOLIS!\p"
	.string "Undercover in TEAM MAGMA, and you still\n"
	.string "brought DEVON's parts to me at the\l"
	.string "MUSEUM.\p"
	.string "I'm proud to have met you!$"

SlateportCity_Harbor_EventScript_DraconidSternFerry_Text_1:
	.string "CAPT. STERN: {PLAYER}{KUN}! I heard about\n"
	.string "SOOTOPOLIS!\p"
	.string "So that's why a MAGMA grunt “found” my\n"
	.string "parts from DEVON.\p"
	.string "MR. STONE laughed when I told him. I\n"
	.string "think he's forgiven you!$"

Draconid_Text_MrStoneCallErrandReturned::
	.string "MR. STONE: Oh? {PLAYER}{KUN}!\p"
	.string "Since you called me, the POKéNAV\n"
	.string "must be working properly!\p"
	.string "Now, don't forget my errand. My\n"
	.string "LETTER goes to STEVEN in DEWFORD.\p"
	.string "And our parcel goes to CAPT. STERN\n"
	.string "in SLATEPORT.\p"
	.string "Since I am a busy PRESIDENT, I have\n"
	.string "to go! Bye-bye!$"

Draconid_Text_MrStoneCallErrandKept::
	.string "MR. STONE: Oh? {PLAYER}{KUN}!\p"
	.string "Since you called me, the POKéNAV\n"
	.string "must be working properly!\p"
	.string "Now, don't forget my errand. My\n"
	.string "LETTER goes to STEVEN in DEWFORD.\p"
	.string "And please tell CAPT. STERN in\n"
	.string "SLATEPORT about his parts. He'll be\l"
	.string "so disappointed…\p"
	.string "Since I am a busy PRESIDENT, I have\n"
	.string "to go! Bye-bye!$"

Draconid_Text_MrStoneCallLetterReturned::
	.string "MR. STONE: Oh! {PLAYER}{KUN}!\p"
	.string "Ah, so you've met STEVEN! Thank you\n"
	.string "kindly!\p"
	.string "Now there's only our parcel for\n"
	.string "CAPT. STERN. I'm counting on you!$"

Draconid_Text_MrStoneCallLetterKept::
	.string "MR. STONE: Oh! {PLAYER}{KUN}!\p"
	.string "Ah, so you've met STEVEN! Thank you\n"
	.string "kindly!\p"
	.string "Have you been to SLATEPORT yet?\n"
	.string "Poor CAPT. STERN…$"

Draconid_Text_MrStoneCallSternReturned::
	.string "MR. STONE: {PLAYER}{KUN}! CAPT. STERN\n"
	.string "just called me!\p"
	.string "Our parts reached him safe and\n"
	.string "sound, and you fought off TEAM\l"
	.string "AQUA, too!\p"
	.string "A TEAM MAGMA grunt, protecting\n"
	.string "DEVON's parts… I'll never\l"
	.string "understand it. Wahaha!$"

Draconid_Text_MrStoneCallSternKept::
	.string "MR. STONE: …{PLAYER}{KUN}. CAPT. STERN\n"
	.string "just called me.\p"
	.string "It seems our missing parts turned\n"
	.string "up in SLATEPORT. In your hands.\p"
	.string "He says you “found” them.\p"
	.string "I won't ask. But I will remember.$"

Draconid_Text_MrStoneCallRevealedReturned::
	.string "MR. STONE: {PLAYER}{KUN}! It's me!\p"
	.string "I heard everything! A DRACONID,\n"
	.string "undercover in TEAM MAGMA!\p"
	.string "And even then, you brought our\n"
	.string "parts back to DEVON.\p"
	.string "I always said I could spot a good\n"
	.string "TRAINER. Wahahaha!$"

Draconid_Text_MrStoneCallRevealedKept::
	.string "MR. STONE: {PLAYER}{KUN}! It's me!\p"
	.string "I heard everything! A DRACONID,\n"
	.string "undercover in TEAM MAGMA!\p"
	.string "So that's why you kept our parts.\n"
	.string "TEAM MAGMA had to believe you were\l"
	.string "theirs.\p"
	.string "All is forgiven. But I did count\n"
	.string "every screw! Wahahaha!$"
