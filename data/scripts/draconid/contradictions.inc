Draconid_EventScript_AfterWhiteOutHomeHeal::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Draconid_Text_WhiteOutOldWomanWelcome
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Draconid_Text_WhiteOutOldWomanAdvice
	fadedefaultbgm
	releaseall
	return


RustboroCity_CuttersHouse_EventScript_DraconidRepCutterUniform::
	msgbox RustboroCity_CuttersHouse_Text_DraconidRepCutterUniform, MSGBOX_DEFAULT
	goto RustboroCity_CuttersHouse_EventScript_DraconidGiveCut
	return


GraniteCave_1F_EventScript_DraconidRepHikerUniform::
	msgbox GraniteCave_1F_Text_DraconidRepHikerUniform, MSGBOX_DEFAULT
	goto GraniteCave_1F_EventScript_DraconidGiveFlash
	return


MauvilleCity_House1_EventScript_DraconidRepRockSmashDudeUniform::
	msgbox MauvilleCity_House1_Text_DraconidRepRockSmashDudeUniform, MSGBOX_DEFAULT
	goto MauvilleCity_House1_EventScript_DraconidGiveRockSmash
	return


MauvilleCity_BikeShop_EventScript_DraconidRepRydelUniform::
	msgbox MauvilleCity_BikeShop_Text_DraconidRepRydelUniform, MSGBOX_DEFAULT
	return


Draconid_Text_WhiteOutOldWomanWelcome::
	.string "OLD WOMAN: There you are. The whole\n"
	.string "village saw you come home limping.\p"
	.string "Rest now. A tamer who falls and gets up\n"
	.string "again is still a tamer.$"

Draconid_Text_WhiteOutOldWomanAdvice::
	.string "OLD WOMAN: The lowlanders' POKéMON\n"
	.string "CENTERS will heal your partners, too.$"

RustboroCity_CuttersHouse_Text_DraconidRepCutterUniform::
	.string "Hm? That red getup…\n"
	.string "TEAM MAGMA, eh?\p"
	.string "No, don't say a word.\n"
	.string "That determined expression…\p"
	.string "A skilled TRAINER is a skilled TRAINER.\p"
	.string "I'm sure that you can put this HIDDEN\n"
	.string "MACHINE to good use. Go on, take it!$"

GraniteCave_1F_Text_DraconidRepHikerUniform::
	.string "Hey, you. Whoa… TEAM MAGMA?\p"
	.string "Well, it gets awfully dark ahead.\n"
	.string "Even a MAGMA kid can get lost in there.\p"
	.string "For us HIKERS, helping out those that\n"
	.string "we meet is our motto. Whoever they are.\p"
	.string "Here you go, I'll pass this on to you.$"

MauvilleCity_House1_Text_DraconidRepRockSmashDudeUniform::
	.string "Woohoo!\p"
	.string "I'm the ROCK SMASH DUDE! Don't call me\n"
	.string "the ROCK SMASH GUY.\p"
	.string "TEAM MAGMA, huh?\n"
	.string "Rocks don't care what you wear!\p"
	.string "Your POKéMON look pretty strong.\n"
	.string "I like that!\p"
	.string "Here, take this HIDDEN MACHINE!$"

MauvilleCity_BikeShop_Text_DraconidRepRydelUniform::
	.string "RYDEL: …Hm? That red uniform.\n"
	.string "TEAM MAGMA, is it?\p"
	.string "Well! A BIKE doesn't ask who's riding it!$"
