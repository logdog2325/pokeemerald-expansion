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


Draconid_Text_MaxieCallDewford::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: Is this {PLAYER}? My name is\n"
	.string "MAXIE. I lead TEAM MAGMA.\p"
	.string "TABITHA tells me our newest recruit\n"
	.string "carries a dragon and wins BADGES.\p"
	.string "DEVON trusts you now. Good. Deliver\n"
	.string "MR. STONE's LETTER in DEWFORD, and\l"
	.string "the parts to SLATEPORT.\p"
	.string "Keep your eyes open. We'll speak\n"
	.string "again.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMuseum::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: {PLAYER}. TABITHA told me\n"
	.string "about the museum. You faced\l"
	.string "ARCHIE's people and didn't flinch.\p"
	.string "Come north. Win your BADGE in\n"
	.string "MAUVILLE, then take ROUTE 111 up\l"
	.string "to FALLARBOR.\p"
	.string "I'll be at METEOR FALLS, west of\n"
	.string "FALLARBOR. It's time we met.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMeteorFalls::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: You covered our retreat\n"
	.string "well. The meteorite is safe in our\l"
	.string "hands.\p"
	.string "With it, the mountain will wake. Take\n"
	.string "the cable car on ROUTE 112 up MT.\l"
	.string "CHIMNEY.\p"
	.string "Guard the path while I work. AQUA\n"
	.string "will come.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMtChimney::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: …The machine failed. AQUA's\n"
	.string "meddling, no doubt.\p"
	.string "No matter. Ours is patient work.\p"
	.string "Win the BADGE in LAVARIDGE, then a\n"
	.string "fifth from NORMAN in PETALBURG.\p"
	.string "After that, TABITHA will need you at\n"
	.string "the WEATHER INSTITUTE on ROUTE\l"
	.string "119.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallWeatherInstitute::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: The research says the\n"
	.string "weather answers to two ancient\l"
	.string "ORBS.\p"
	.string "They rest on MT. PYRE, east of\n"
	.string "LILYCOVE, on ROUTE 122.\p"
	.string "Win your BADGE in FORTREE, then go\n"
	.string "to LILYCOVE and on to the mountain.\p"
	.string "Hold the summit against AQUA. I'm\n"
	.string "counting on you.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallMtPyre::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: We have what we came for.\n"
	.string "ARCHIE has the other ORB.\p"
	.string "It's time you saw our true home.\n"
	.string "Come to our HIDEOUT at JAGGED PASS.\p"
	.string "…I have something to ask of you,\n"
	.string "{PLAYER}.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallPromoted::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: GROUDON slipped from us…\n"
	.string "but it will rise again. I can feel it.\p"
	.string "ARCHIE will make his move. I want to\n"
	.string "know what he plans.\p"
	.string "AQUA has a hideout on the shore of\n"
	.string "LILYCOVE. Get inside and find out.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallAquaHideout::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: ARCHIE took CAPT. STERN's\n"
	.string "submarine? He means to go under the\l"
	.string "sea.\p"
	.string "TABITHA is leading a team to\n"
	.string "MOSSDEEP. The SPACE CENTER has\l"
	.string "fuel we need.\p"
	.string "Win your BADGE in MOSSDEEP, then\n"
	.string "join him at the SPACE CENTER.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallSpaceCenter::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: No fuel. …Never mind that\n"
	.string "now.\p"
	.string "AQUA's submarine was seen by the\n"
	.string "SEAFLOOR CAVERN, under ROUTE 128.\p"
	.string "DIVE after them. Whatever ARCHIE\n"
	.string "means to wake, we must see it first.\p"
	.string "… … … … … Click!$"

Draconid_Text_MaxieCallSeafloor::
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MAXIE: KYOGRE is awake. The sky\n"
	.string "over SOOTOPOLIS has gone black.\p"
	.string "{PLAYER}, I need you in SOOTOPOLIS.\n"
	.string "Now.\p"
	.string "Together, we can still set this\n"
	.string "right. Hurry.\p"
	.string "… … … … … Click!$"
