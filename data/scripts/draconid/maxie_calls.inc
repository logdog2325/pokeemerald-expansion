Draconid_EventScript_MaxieCall::
	lockall
	specialvar VAR_RESULT, Draconid_GetDueMaxieCall
	switch VAR_RESULT
	case MAXIE_CALL_MUSEUM, Draconid_EventScript_MaxieCall_3
	case MAXIE_CALL_METEOR_FALLS, Draconid_EventScript_MaxieCall_4
	case MAXIE_CALL_MT_CHIMNEY, Draconid_EventScript_MaxieCall_5
	case MAXIE_CALL_WEATHER_INSTITUTE, Draconid_EventScript_MaxieCall_6
	case MAXIE_CALL_MT_PYRE, Draconid_EventScript_MaxieCall_7
	case MAXIE_CALL_PROMOTED, Draconid_EventScript_MaxieCall_8
	case MAXIE_CALL_AQUA_HIDEOUT, Draconid_EventScript_MaxieCall_9
	case MAXIE_CALL_SPACE_CENTER, Draconid_EventScript_MaxieCall_10
	case MAXIE_CALL_SEAFLOOR, Draconid_EventScript_MaxieCall_11
	setvar VAR_MAXIE_CALL_STEPS, 0
	releaseall
	end

Draconid_EventScript_MaxieCall_1:
	waitmessage
	copyvar VAR_MAXIE_CALL, VAR_RESULT
	setvar VAR_MAXIE_CALL_STEPS, 0
	releaseall
	return

Draconid_EventScript_MaxieCall_3:
	pokenavcall Draconid_Text_MaxieCallMuseum
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_4:
	pokenavcall Draconid_Text_MaxieCallMeteorFalls
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_5:
	pokenavcall Draconid_Text_MaxieCallMtChimney
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_6:
	pokenavcall Draconid_Text_MaxieCallWeatherInstitute
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_7:
	pokenavcall Draconid_Text_MaxieCallMtPyre
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_8:
	pokenavcall Draconid_Text_MaxieCallPromoted
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_9:
	pokenavcall Draconid_Text_MaxieCallAquaHideout
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_10:
	pokenavcall Draconid_Text_MaxieCallSpaceCenter
	goto Draconid_EventScript_MaxieCall_1

Draconid_EventScript_MaxieCall_11:
	pokenavcall Draconid_Text_MaxieCallSeafloor
	goto Draconid_EventScript_MaxieCall_1


Route104_EventScript_DraconidMaxieCallDewford::
	goto_if_set FLAG_DEVON_GOODS_RETURNED, Route104_EventScript_DraconidMaxieCallDewford_1
	pokenavcall Draconid_Text_MaxieCallDewfordKept
	return

Route104_EventScript_DraconidMaxieCallDewford_1:
	pokenavcall Draconid_Text_MaxieCallDewfordReturned
	return


Draconid_Text_MaxieCallDewfordKept::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: Is this {PLAYER}? I am MAXIE,\n"
	.string "the leader of TEAM MAGMA.\p"
	.string "TABITHA tells me you kept DEVON's\n"
	.string "parts for us.\n"
	.string "Well done.\p"
	.string "DEVON believes the thief got away\n"
	.string "with them. Let them.\p"
	.string "Take MR. STONE's LETTER to DEWFORD,\n"
	.string "then the parts to SLATEPORT.\l"
	.string "TABITHA will be waiting.\p"
	.string "Keep your eyes open.\n"
	.string "We will speak again.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallDewfordReturned::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: Is this {PLAYER}? I am MAXIE,\n"
	.string "the leader of TEAM MAGMA.\p"
	.string "TABITHA tells me DEVON got its\n"
	.string "parts back. Sloppy…\n"
	.string "but no matter.\p"
	.string "They are going to SLATEPORT all the\n"
	.string "same, and so are you.\p"
	.string "Take MR. STONE's LETTER to DEWFORD\n"
	.string "and the parts to SLATEPORT.\p"
	.string "Keep your eyes open.\n"
	.string "We will speak again.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMuseum::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: {PLAYER}. TABITHA told me\n"
	.string "about the museum. You stood up to\l"
	.string "ARCHIE's people without flinching.\p"
	.string "Come north. Earn your BADGE in\n"
	.string "MAUVILLE, then take ROUTE 111 up\l"
	.string "to FALLARBOR.\p"
	.string "I will be at METEOR FALLS, west of\n"
	.string "FALLARBOR. It is time we met.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMeteorFalls::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: You held the stairs well.\n"
	.string "The METEORITE is safe with us.\p"
	.string "Take the cable car on ROUTE 112\n"
	.string "up to MT. CHIMNEY.\p"
	.string "Guard the path while I wake the\n"
	.string "mountain. AQUA will come.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMtChimney::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: The machine failed us. AQUA's\n"
	.string "meddling, no doubt.\p"
	.string "No matter.\n"
	.string "TEAM MAGMA can be patient.\p"
	.string "Win the BADGE in LAVARIDGE, then a\n"
	.string "fifth from NORMAN in PETALBURG.\p"
	.string "Then TABITHA will need you at the\n"
	.string "WEATHER INSTITUTE on ROUTE 119.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallWeatherInstitute::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: Fufufu… The INSTITUTE's\n"
	.string "research was most illuminating.\p"
	.string "The weather answers to two ancient\n"
	.string "ORBS. They rest on MT. PYRE, east of\l"
	.string "LILYCOVE, on ROUTE 122.\p"
	.string "Earn your BADGE in FORTREE, then go\n"
	.string "to LILYCOVE and on to the mountain.\p"
	.string "AQUA will be there too. I am\n"
	.string "counting on you to hold the summit.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMtPyre::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: We have the BLUE ORB. ARCHIE\n"
	.string "took the other one, but no matter.\p"
	.string "It is time you saw our true home.\n"
	.string "Come to our HIDEOUT at JAGGED PASS.\p"
	.string "{PLAYER}, there is something I\n"
	.string "wish to ask of you.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallPromoted::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: GROUDON has slipped away\n"
	.string "from us, but it will surface again.\p"
	.string "ARCHIE is sure to make his move.\n"
	.string "I want to know what he plans.\p"
	.string "AQUA has a hideout on the shore at\n"
	.string "LILYCOVE. Get inside and find out.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallAquaHideout::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: ARCHIE took CAPT. STERN's\n"
	.string "submarine? So he means to search\l"
	.string "under the sea.\p"
	.string "TABITHA is leading a squad to\n"
	.string "MOSSDEEP. The SPACE CENTER has\l"
	.string "rocket fuel we need.\p"
	.string "Earn your BADGE in MOSSDEEP, then\n"
	.string "join him at the SPACE CENTER.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallSpaceCenter::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: So the fuel is lost.\n"
	.string "Never mind that now.\p"
	.string "AQUA's submarine was seen near the\n"
	.string "SEAFLOOR CAVERN, under ROUTE 128.\p"
	.string "DIVE down after them. Whatever\n"
	.string "ARCHIE means to awaken, we must\l"
	.string "find it first.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallSeafloor::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: {PLAYER}.\n"
	.string "I have found GROUDON.\p"
	.string "It has risen in SOOTOPOLIS to meet\n"
	.string "KYOGRE. The two of them will tear\l"
	.string "the city apart.\p"
	.string "Come to SOOTOPOLIS at once.\n"
	.string "I need you at my side.\p"
	.string "… … … … … Click!$"
