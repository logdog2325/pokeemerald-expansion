DraconidVillage_Shrine_EventScript_DraconidZRing::
	msgbox DraconidVillage_Shrine_EventScript_DraconidZRing_Text_0
	msgbox DraconidVillage_Shrine_EventScript_DraconidZRing_Text_1
	giveitem ITEM_Z_POWER_RING
	msgbox DraconidVillage_Shrine_EventScript_DraconidZRing_Text_2
	giveitem DRACONID_Z_CRYSTAL_FIRST
	setflag FLAG_RECEIVED_Z_POWER_RING
	msgbox DraconidVillage_Shrine_EventScript_DraconidZRing_Text_3
	msgbox DraconidVillage_Shrine_EventScript_DraconidZRing_Text_4
	msgbox DraconidVillage_Shrine_EventScript_DraconidZRing_Text_5
	msgbox DraconidVillage_Shrine_EventScript_DraconidZRing_Text_6
	return


SlateportCity_EventScript_DraconidOakOnTransition::
	compare VAR_SECOND_STARTER, SECOND_STARTER_NONE
	goto_if_eq SlateportCity_EventScript_DraconidOakOnTransition_1
	goto_if_set FLAG_RECEIVED_OAK_Z_CRYSTAL, SlateportCity_EventScript_DraconidOakOnTransition_1
	return

SlateportCity_EventScript_DraconidOakOnTransition_1:
	setflag FLAG_TEMP_11
	return


SlateportCity_EventScript_DraconidOak::
	lock
	faceplayer
	msgbox SlateportCity_EventScript_DraconidOak_Text_0
	msgbox SlateportCity_EventScript_DraconidOak_Text_1
	checkitemspace DRACONID_Z_CRYSTAL_CHARMANDER
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_EventScript_DraconidOak_2
SlateportCity_EventScript_DraconidOak_1:
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_EventScript_DraconidOak_5
SlateportCity_EventScript_DraconidOak_4:
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_EventScript_DraconidOak_8
	switch VAR_SECOND_STARTER
	case SECOND_STARTER_CHARMANDER, SlateportCity_EventScript_DraconidOak_12
	case SECOND_STARTER_TOTODILE, SlateportCity_EventScript_DraconidOak_13
	giveitem DRACONID_Z_CRYSTAL_TREECKO
SlateportCity_EventScript_DraconidOak_10:
	setflag FLAG_RECEIVED_OAK_Z_CRYSTAL
	msgbox SlateportCity_EventScript_DraconidOak_Text_3
	msgbox SlateportCity_EventScript_DraconidOak_Text_4
	checkitem DRACONID_Z_CRYSTAL_CHARMANDER
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_EventScript_DraconidOak_16
SlateportCity_EventScript_DraconidOak_15:
	checkitem DRACONID_Z_CRYSTAL_TOTODILE
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_EventScript_DraconidOak_19
SlateportCity_EventScript_DraconidOak_18:
	checkitem DRACONID_Z_CRYSTAL_TREECKO
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_EventScript_DraconidOak_22
SlateportCity_EventScript_DraconidOak_21:
	msgbox SlateportCity_EventScript_DraconidOak_Text_5
	msgbox SlateportCity_EventScript_DraconidOak_Text_6
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SLATEPORT_OAK
	fadescreen FADE_FROM_BLACK
	release
	return

SlateportCity_EventScript_DraconidOak_2:
	checkitemspace DRACONID_Z_CRYSTAL_TOTODILE
	goto SlateportCity_EventScript_DraconidOak_1

SlateportCity_EventScript_DraconidOak_5:
	checkitemspace DRACONID_Z_CRYSTAL_TREECKO
	goto SlateportCity_EventScript_DraconidOak_4

SlateportCity_EventScript_DraconidOak_8:
	msgbox SlateportCity_EventScript_DraconidOak_Text_2
	release
	end

SlateportCity_EventScript_DraconidOak_12:
	giveitem DRACONID_Z_CRYSTAL_CHARMANDER
	goto SlateportCity_EventScript_DraconidOak_10

SlateportCity_EventScript_DraconidOak_13:
	giveitem DRACONID_Z_CRYSTAL_TOTODILE
	goto SlateportCity_EventScript_DraconidOak_10

SlateportCity_EventScript_DraconidOak_16:
	giveitem DRACONID_Z_CRYSTAL_CHARMANDER
	goto SlateportCity_EventScript_DraconidOak_15

SlateportCity_EventScript_DraconidOak_19:
	giveitem DRACONID_Z_CRYSTAL_TOTODILE
	goto SlateportCity_EventScript_DraconidOak_18

SlateportCity_EventScript_DraconidOak_22:
	giveitem DRACONID_Z_CRYSTAL_TREECKO
	goto SlateportCity_EventScript_DraconidOak_21


MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ::
	goto_if_set FLAG_RECEIVED_DRAGONIUM_Z, MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_2
	msgbox MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_Text_0
	giveitem DRACONID_Z_CRYSTAL_FALLS
	compare VAR_RESULT, FALSE
	goto_if_eq MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_5
	setflag FLAG_RECEIVED_DRAGONIUM_Z
	msgbox MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_Text_2
	return

MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_2:
	return

MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_5:
	msgbox MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_Text_1
	return


JaggedPass_EventScript_DraconidDragoniumZAgain::
	goto_if_set FLAG_RECEIVED_DRAGONIUM_Z, JaggedPass_EventScript_DraconidDragoniumZAgain_2
	msgbox JaggedPass_EventScript_DraconidDragoniumZAgain_Text_0
	giveitem DRACONID_Z_CRYSTAL_FALLS
	compare VAR_RESULT, TRUE
	goto_if_eq JaggedPass_EventScript_DraconidDragoniumZAgain_4
	return

JaggedPass_EventScript_DraconidDragoniumZAgain_2:
	return

JaggedPass_EventScript_DraconidDragoniumZAgain_4:
	setflag FLAG_RECEIVED_DRAGONIUM_Z
	return


MtPyre_Summit_EventScript_DraconidKommoniumZ::
	compare VAR_STARTER_MON, DRACONID_EGG_JANGMO_O
	goto_if_ne MtPyre_Summit_EventScript_DraconidKommoniumZ_2
	msgbox MtPyre_Summit_EventScript_DraconidKommoniumZ_Text_0
	msgbox MtPyre_Summit_EventScript_DraconidKommoniumZ_Text_1
	clearflag FLAG_TEMP_12
	addobject LOCALID_MT_PYRE_SUMMIT_KOMMONIUM_Z
	msgbox MtPyre_Summit_EventScript_DraconidKommoniumZ_Text_2
	return

MtPyre_Summit_EventScript_DraconidKommoniumZ_2:
	return


MtPyre_Summit_EventScript_DraconidKommoniumZOnTransition::
	compare VAR_STARTER_MON, DRACONID_EGG_JANGMO_O
	goto_if_ne MtPyre_Summit_EventScript_DraconidKommoniumZOnTransition_1
	compare VAR_NERINE_STATE, NERINE_STATE_MT_PYRE
	goto_if_lt MtPyre_Summit_EventScript_DraconidKommoniumZOnTransition_1
	goto_if_set FLAG_RECEIVED_KOMMONIUM_Z, MtPyre_Summit_EventScript_DraconidKommoniumZOnTransition_1
	return

MtPyre_Summit_EventScript_DraconidKommoniumZOnTransition_1:
	setflag FLAG_TEMP_12
	return


MtPyre_Summit_EventScript_DraconidKommoniumZBall::
	checkitemspace DRACONID_Z_CRYSTAL_JANGMO_O
	compare VAR_RESULT, TRUE
	goto_if_eq MtPyre_Summit_EventScript_DraconidKommoniumZBall_2
MtPyre_Summit_EventScript_DraconidKommoniumZBall_1:
	finditem DRACONID_Z_CRYSTAL_JANGMO_O
	return

MtPyre_Summit_EventScript_DraconidKommoniumZBall_2:
	setflag FLAG_RECEIVED_KOMMONIUM_Z
	goto MtPyre_Summit_EventScript_DraconidKommoniumZBall_1


DraconidVillage_Shrine_EventScript_DraconidZRing_Text_0:
	.string "ELDER: Wait, {PLAYER}. Something else\n"
	.string "came to us with the egg from ALOLA.$"

DraconidVillage_Shrine_EventScript_DraconidZRing_Text_1:
	.string "ELDER: The dragon keepers of VAST PONI\n"
	.string "CANYON sent this, “for the one who\l"
	.string "carries the prophecy.”\p"
	.string "That is you now.$"

DraconidVillage_Shrine_EventScript_DraconidZRing_Text_2:
	.string "ELDER: And the first of their crystals.\n"
	.string "The simplest one, so that any partner\l"
	.string "can use it.$"

DraconidVillage_Shrine_EventScript_DraconidZRing_Text_3:
	.string "ELDER: In ALOLA they call it Z-POWER.\p"
	.string "A trainer's whole strength and a\n"
	.string "POKéMON's, made one for a single move.$"

DraconidVillage_Shrine_EventScript_DraconidZRing_Text_4:
	.string "ELDER: Once in a battle, and it takes\n"
	.string "everything you both have.\p"
	.string "Do not lean on it, {PLAYER}.$"

DraconidVillage_Shrine_EventScript_DraconidZRing_Text_5:
	.string "ELDER: Let your partner hold the\n"
	.string "crystal. In battle, choose a move of the\l"
	.string "crystal's type and press START.$"

DraconidVillage_Shrine_EventScript_DraconidZRing_Text_6:
	.string "ELDER: The keepers' other crystals will\n"
	.string "come to you as the road goes on.$"

SlateportCity_EventScript_DraconidOak_Text_0:
	.string "PROF. OAK: Ah, {PLAYER}! I came down to\n"
	.string "meet a ship from ALOLA. It just came in.$"

SlateportCity_EventScript_DraconidOak_Text_1:
	.string "PROF. OAK: My cousin SAMSON studies\n"
	.string "POKéMON over there.\p"
	.string "I wrote to him about the partner I gave\n"
	.string "you in RUSTBORO, and look what he sent!$"

SlateportCity_EventScript_DraconidOak_Text_2:
	.string "PROF. OAK: Oh! Your BAG is full. Make\n"
	.string "some room, and I'll wait right here.$"

SlateportCity_EventScript_DraconidOak_Text_3:
	.string "PROF. OAK: A Z-CRYSTAL! With the ring\n"
	.string "your ELDER gave you, your partner can\l"
	.string "put everything into one move.\p"
	.string "SAMSON says to use it wisely. Coming\n"
	.string "from him, that's saying something!$"

SlateportCity_EventScript_DraconidOak_Text_4:
	.string "PROF. OAK: He sent one for each of the\n"
	.string "three POKéMON I brought to HOENN.\p"
	.string "The other two are coming home to KANTO\n"
	.string "with me, and they hardly need crystals\l"
	.string "in a lab!$"

SlateportCity_EventScript_DraconidOak_Text_5:
	.string "PROF. OAK: A crystal isn't tied to one\n"
	.string "POKéMON, you know. Any POKéMON of its\l"
	.string "type can hold it.$"

SlateportCity_EventScript_DraconidOak_Text_6:
	.string "PROF. OAK: Now, I'd best not be seen\n"
	.string "chatting with a TEAM MAGMA grunt for\l"
	.string "too long. Take care, {PLAYER}!$"

MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_Text_0:
	.string "ASTER: …And this. Don't look at me like\n"
	.string "that. It isn't from me.\p"
	.string "The DRACONIDS of these falls heard the\n"
	.string "ELDER gave you a Z-POWER RING. They\l"
	.string "sent you a DRAGONIUM Z.$"

MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_Text_1:
	.string "ASTER: Your BAG's full? Then I'll hold on\n"
	.string "to it. You'll see me again.$"

MeteorFalls_1F_1R_EventScript_DraconidDragoniumZ_Text_2:
	.string "ASTER: A dragon's crystal, for the\n"
	.string "ELDER's chosen. Don't waste it on\l"
	.string "MAGMA's errands.$"

JaggedPass_EventScript_DraconidDragoniumZAgain_Text_0:
	.string "ASTER: And the falls' crystal. You'd\n"
	.string "better have room for it this time.$"

MtPyre_Summit_EventScript_DraconidKommoniumZ_Text_0:
	.string "NERINE: …Wait. Your partner's scales\n"
	.string "ring like a war drum.\p"
	.string "That line comes from ALOLA. I'd know\n"
	.string "that sound anywhere.$"

MtPyre_Summit_EventScript_DraconidKommoniumZ_Text_1:
	.string "NERINE: This came off a ship from\n"
	.string "there. It belongs with your dragon more\l"
	.string "than with me.$"

MtPyre_Summit_EventScript_DraconidKommoniumZ_Text_2:
	.string "NERINE: I'll leave it by the lantern. An\n"
	.string "AQUA grunt doesn't hand things to a\l"
	.string "MAGMA uniform.\p"
	.string "And don't ask where I got it.$"
