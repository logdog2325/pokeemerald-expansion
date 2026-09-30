LilycoveCity_EventScript_DraconidRepRichBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LilycoveCity_EventScript_DraconidRepRichBoy_2
	case REPUTATION_REVEALED, LilycoveCity_EventScript_DraconidRepRichBoy_3
	goto LilycoveCity_EventScript_RichBoy
	return

LilycoveCity_EventScript_DraconidRepRichBoy_2:
	msgbox LilycoveCity_Text_DraconidRepRichBoyUniform, MSGBOX_NPC
	return

LilycoveCity_EventScript_DraconidRepRichBoy_3:
	msgbox LilycoveCity_Text_DraconidRepRichBoyRevealed, MSGBOX_NPC
	return


LilycoveCity_EventScript_DraconidRepMan3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LilycoveCity_EventScript_DraconidRepMan3_2
	case REPUTATION_REVEALED, LilycoveCity_EventScript_DraconidRepMan3_3
	goto LilycoveCity_EventScript_Man3
	return

LilycoveCity_EventScript_DraconidRepMan3_2:
	msgbox LilycoveCity_Text_DraconidRepMan3Uniform, MSGBOX_NPC
	return

LilycoveCity_EventScript_DraconidRepMan3_3:
	msgbox LilycoveCity_Text_DraconidRepMan3Revealed, MSGBOX_NPC
	return


LilycoveCity_EventScript_DraconidRepSailor1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LilycoveCity_EventScript_DraconidRepSailor1_2
	case REPUTATION_REVEALED, LilycoveCity_EventScript_DraconidRepSailor1_3
	goto LilycoveCity_EventScript_Sailor1
	return

LilycoveCity_EventScript_DraconidRepSailor1_2:
	lock
	faceplayer
	msgbox LilycoveCity_Text_DraconidRepSailor1Uniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

LilycoveCity_EventScript_DraconidRepSailor1_3:
	msgbox LilycoveCity_Text_DraconidRepSailor1Revealed, MSGBOX_NPC
	return


LilycoveCity_EventScript_DraconidRepFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LilycoveCity_EventScript_DraconidRepFatMan_2
	case REPUTATION_REVEALED, LilycoveCity_EventScript_DraconidRepFatMan_3
	goto LilycoveCity_EventScript_FatMan
	return

LilycoveCity_EventScript_DraconidRepFatMan_2:
	msgbox LilycoveCity_Text_DraconidRepFatManUniform, MSGBOX_NPC
	return

LilycoveCity_EventScript_DraconidRepFatMan_3:
	msgbox LilycoveCity_Text_DraconidRepFatManRevealed, MSGBOX_NPC
	return


LilycoveCity_EventScript_DraconidRepExpertF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LilycoveCity_EventScript_DraconidRepExpertF_2
	case REPUTATION_REVEALED, LilycoveCity_EventScript_DraconidRepExpertF_3
	goto LilycoveCity_EventScript_ExpertF
	return

LilycoveCity_EventScript_DraconidRepExpertF_2:
	msgbox LilycoveCity_Text_DraconidRepExpertFUniform, MSGBOX_SIGN
	return

LilycoveCity_EventScript_DraconidRepExpertF_3:
	msgbox LilycoveCity_Text_DraconidRepExpertFRevealed, MSGBOX_SIGN
	return


LilycoveCity_Text_DraconidRepRichBoyUniform::
	.string "I came from KANTO. We had TEAM ROCKET\n"
	.string "there.\p"
	.string "I didn't think I'd see their kind in\n"
	.string "HOENN, too.$"

LilycoveCity_Text_DraconidRepRichBoyRevealed::
	.string "I came from KANTO. We had TEAM ROCKET\n"
	.string "there.\p"
	.string "I wish KANTO had a TRAINER like you!$"

LilycoveCity_Text_DraconidRepMan3Uniform::
	.string "Well-raised POKéMON come from all over\n"
	.string "for the CONTEST HALL.\p"
	.string "Yours look well-raised, too… That's\n"
	.string "what makes me nervous.$"

LilycoveCity_Text_DraconidRepMan3Revealed::
	.string "Well-raised POKéMON come from all over\n"
	.string "for the CONTEST HALL.\p"
	.string "You'd win the SMART contest. You\n"
	.string "outsmarted TEAM MAGMA!$"

LilycoveCity_Text_DraconidRepSailor1Uniform::
	.string "There's a tower out on the sea routes…\p"
	.string "No. I'm not telling TEAM MAGMA anything.$"

LilycoveCity_Text_DraconidRepSailor1Revealed::
	.string "Sailors say a great green POKéMON came\n"
	.string "down over SOOTOPOLIS.\p"
	.string "And you were right there! Is it true?$"

LilycoveCity_Text_DraconidRepFatManUniform::
	.string "…Don't look at me like that. I'm not\n"
	.string "saying anything.\p"
	.string "Not to TEAM MAGMA.$"

LilycoveCity_Text_DraconidRepFatManRevealed::
	.string "That tall tower around ROUTE 131…\p"
	.string "I hear it's tied to the POKéMON that\n"
	.string "saved SOOTOPOLIS. And you were there!$"

LilycoveCity_Text_DraconidRepExpertFUniform::
	.string "Sixty years I've watched this sea.\p"
	.string "I never thought I'd see children in gang\n"
	.string "uniforms on this shore.$"

LilycoveCity_Text_DraconidRepExpertFRevealed::
	.string "Sixty years ago, my husband proposed\n"
	.string "to me here.\p"
	.string "Thanks to you, the sea will stay this\n"
	.string "beautiful. Mufufufu…$"
