SlateportCity_SternsShipyard_1F_EventScript_DraconidRepBriney::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_SternsShipyard_1F_EventScript_DraconidRepBriney_2
	case REPUTATION_REVEALED, SlateportCity_SternsShipyard_1F_EventScript_DraconidRepBriney_3
	goto SlateportCity_SternsShipyard_1F_EventScript_Briney
	return

SlateportCity_SternsShipyard_1F_EventScript_DraconidRepBriney_2:
	msgbox SlateportCity_SternsShipyard_1F_Text_DraconidRepBrineyUniform, MSGBOX_NPC
	return

SlateportCity_SternsShipyard_1F_EventScript_DraconidRepBriney_3:
	msgbox SlateportCity_SternsShipyard_1F_Text_DraconidRepBrineyRevealed, MSGBOX_NPC
	return


SSTidalCorridor_EventScript_DraconidRepBriney::
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_ne SSTidalCorridor_EventScript_DraconidRepBriney_2
SSTidalCorridor_EventScript_DraconidRepBriney_1:
	msgbox SSTidalCorridor_Text_DraconidRepBrineyRevealed, MSGBOX_NPC
	return

SSTidalCorridor_EventScript_DraconidRepBriney_2:
	goto SSTidalCorridor_EventScript_Briney
	goto SSTidalCorridor_EventScript_DraconidRepBriney_1


SlateportCity_SternsShipyard_1F_Text_DraconidRepBrineyUniform::
	.string "MR. BRINEY: Ah, {PLAYER}! It's been too\n"
	.string "long!\p"
	.string "Still in that red getup, I see. Well, I\n"
	.string "told you before. I don't care what\l"
	.string "colors you wear.\p"
	.string "PEEKO doesn't mind it, so neither will I.\p"
	.string "I'm helping DOCK build a ferry, aye! Mind\n"
	.string "you don't sink it.$"

SlateportCity_SternsShipyard_1F_Text_DraconidRepBrineyRevealed::
	.string "MR. BRINEY: Ah, {PLAYER}! The whole port\n"
	.string "is talking about you!\p"
	.string "I knew there was a good heart under\n"
	.string "that red getup, aye!\p"
	.string "DOCK and I are still building our ferry.\n"
	.string "You'll be our first passenger!$"

SSTidalCorridor_Text_DraconidRepBrineyRevealed::
	.string "MR. BRINEY: Welcome aboard, {PLAYER}!\p"
	.string "They made me honorary captain of the\n"
	.string "S.S. TIDAL!\p"
	.string "And the hero of SOOTOPOLIS is sailing\n"
	.string "with me!\p"
	.string "This old sea dog couldn't be prouder,\n"
	.string "aye!$"
