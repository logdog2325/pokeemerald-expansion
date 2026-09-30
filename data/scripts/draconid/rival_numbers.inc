SootopolisCity_EventScript_DraconidRivalNumbers::
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_0
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_1
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_2
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_3
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	setflag FLAG_ENABLE_BRENDAN_MATCH_CALL
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_4
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_5
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_REGISTERED_STEVEN_POKENAV
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_6
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_7
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_8
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	msgbox SootopolisCity_EventScript_DraconidRivalNumbers_Text_9
	return


SootopolisCity_EventScript_DraconidRivalNumbers_Text_0:
	.string "MAY: Oh! Before we go…\p"
	.string "{PLAYER}, let's register each other in\n"
	.string "our POKéNAVS!$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_1:
	.string "MAY: I wasn't going to give my number to\n"
	.string "a MAGMA grunt.\p"
	.string "But you were never really one of them.\n"
	.string "Hehe!$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_2:
	.string "BRENDAN: Yeah, fine. Mine, too.\p"
	.string "Somebody's got to tell you when you're\n"
	.string "slacking off.$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_3:
	.string "Registered MAY and BRENDAN\n"
	.string "in the POKéNAV.$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_4:
	.string "BRENDAN: Oh, right. STEVEN gave me his\n"
	.string "number for you.\p"
	.string "He said he'd like to talk to you without\n"
	.string "a battle in the way.$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_5:
	.string "Registered STEVEN in the POKéNAV.$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_6:
	.string "MAY: And here's WALLY's number, too. My\n"
	.string "dad gave it to me.$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_7:
	.string "MAY: WALLY's been so angry at MAGMA.\n"
	.string "At you, too.\p"
	.string "Once he hears the truth, he'll want to\n"
	.string "say sorry. Let him, okay?$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_8:
	.string "Registered WALLY in the POKéNAV.$"

SootopolisCity_EventScript_DraconidRivalNumbers_Text_9:
	.string "MAY: Okay! Now we're really going.\n"
	.string "See you, {PLAYER}!$"
