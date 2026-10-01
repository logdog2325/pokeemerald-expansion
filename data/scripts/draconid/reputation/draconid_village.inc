DraconidVillage_EventScript_DraconidRepApprentice::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_EventScript_DraconidRepApprentice_2
	case REPUTATION_REVEALED, DraconidVillage_EventScript_DraconidRepApprentice_3
	goto DraconidVillage_EventScript_Apprentice
	return

DraconidVillage_EventScript_DraconidRepApprentice_2:
	msgbox DraconidVillage_Text_DraconidRepApprenticeUniform, MSGBOX_NPC
	return

DraconidVillage_EventScript_DraconidRepApprentice_3:
	msgbox DraconidVillage_Text_DraconidRepApprenticeRevealed, MSGBOX_NPC
	return


DraconidVillage_EventScript_DraconidRepOldWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_EventScript_DraconidRepOldWoman_2
	case REPUTATION_REVEALED, DraconidVillage_EventScript_DraconidRepOldWoman_3
	goto DraconidVillage_EventScript_OldWoman
	return

DraconidVillage_EventScript_DraconidRepOldWoman_2:
	msgbox DraconidVillage_Text_DraconidRepOldWomanUniform, MSGBOX_NPC
	return

DraconidVillage_EventScript_DraconidRepOldWoman_3:
	msgbox DraconidVillage_Text_DraconidRepOldWomanRevealed, MSGBOX_NPC
	return


DraconidVillage_EventScript_DraconidRepPondWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_EventScript_DraconidRepPondWoman_2
	case REPUTATION_REVEALED, DraconidVillage_EventScript_DraconidRepPondWoman_3
	goto DraconidVillage_EventScript_PondWoman
	return

DraconidVillage_EventScript_DraconidRepPondWoman_2:
	msgbox DraconidVillage_Text_DraconidRepPondWomanUniform, MSGBOX_NPC
	return

DraconidVillage_EventScript_DraconidRepPondWoman_3:
	msgbox DraconidVillage_Text_DraconidRepPondWomanRevealed, MSGBOX_NPC
	return


DraconidVillage_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, DraconidVillage_EventScript_DraconidRepBoy_3
	goto DraconidVillage_EventScript_Boy
	return

DraconidVillage_EventScript_DraconidRepBoy_2:
	msgbox DraconidVillage_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return

DraconidVillage_EventScript_DraconidRepBoy_3:
	msgbox DraconidVillage_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


DraconidVillage_EventScript_DraconidRepGatekeeper::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_EventScript_DraconidRepGatekeeper_2
	case REPUTATION_REVEALED, DraconidVillage_EventScript_DraconidRepGatekeeper_3
	goto DraconidVillage_EventScript_Gatekeeper
	return

DraconidVillage_EventScript_DraconidRepGatekeeper_2:
	msgbox DraconidVillage_Text_DraconidRepGatekeeperUniform, MSGBOX_NPC
	return

DraconidVillage_EventScript_DraconidRepGatekeeper_3:
	msgbox DraconidVillage_Text_DraconidRepGatekeeperRevealed, MSGBOX_NPC
	return


DraconidVillage_House1_EventScript_DraconidRepWeaver::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_House1_EventScript_DraconidRepWeaver_2
	case REPUTATION_REVEALED, DraconidVillage_House1_EventScript_DraconidRepWeaver_3
	goto DraconidVillage_House1_EventScript_Weaver
	return

DraconidVillage_House1_EventScript_DraconidRepWeaver_2:
	msgbox DraconidVillage_House1_Text_DraconidRepWeaverUniform, MSGBOX_NPC
	return

DraconidVillage_House1_EventScript_DraconidRepWeaver_3:
	msgbox DraconidVillage_House1_Text_DraconidRepWeaverRevealed, MSGBOX_NPC
	return


DraconidVillage_House1_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_House1_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, DraconidVillage_House1_EventScript_DraconidRepGirl_3
	goto DraconidVillage_House1_EventScript_Girl
	return

DraconidVillage_House1_EventScript_DraconidRepGirl_2:
	msgbox DraconidVillage_House1_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return

DraconidVillage_House1_EventScript_DraconidRepGirl_3:
	msgbox DraconidVillage_House1_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


DraconidVillage_House2_EventScript_DraconidRepHunter::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_House2_EventScript_DraconidRepHunter_2
	case REPUTATION_REVEALED, DraconidVillage_House2_EventScript_DraconidRepHunter_3
	goto DraconidVillage_House2_EventScript_Hunter
	return

DraconidVillage_House2_EventScript_DraconidRepHunter_2:
	msgbox DraconidVillage_House2_Text_DraconidRepHunterUniform, MSGBOX_NPC
	return

DraconidVillage_House2_EventScript_DraconidRepHunter_3:
	msgbox DraconidVillage_House2_Text_DraconidRepHunterRevealed, MSGBOX_NPC
	return


DraconidVillage_House2_EventScript_DraconidRepWife::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, DraconidVillage_House2_EventScript_DraconidRepWife_2
	case REPUTATION_REVEALED, DraconidVillage_House2_EventScript_DraconidRepWife_3
	goto DraconidVillage_House2_EventScript_Wife
	return

DraconidVillage_House2_EventScript_DraconidRepWife_2:
	msgbox DraconidVillage_House2_Text_DraconidRepWifeUniform, MSGBOX_NPC
	return

DraconidVillage_House2_EventScript_DraconidRepWife_3:
	msgbox DraconidVillage_House2_Text_DraconidRepWifeRevealed, MSGBOX_NPC
	return


DraconidVillage_Text_DraconidRepApprenticeUniform::
	.string "…{PLAYER}? I nearly didn't know you in\n"
	.string "that red.\p"
	.string "The ELDER told us why you wear it. Keep\n"
	.string "the path up here a secret, all right?$"

DraconidVillage_Text_DraconidRepApprenticeRevealed::
	.string "Word came up from SOOTOPOLIS.\p"
	.string "You threw off the red right in front of\n"
	.string "MAXIE!\p"
	.string "The whole clan is proud of you, {PLAYER}.$"

DraconidVillage_Text_DraconidRepOldWomanUniform::
	.string "Oh, child… Red never suited anyone from\n"
	.string "the mountains.\p"
	.string "Is your little one eating well down\n"
	.string "there?\p"
	.string "Don't let those people make it cruel.$"

DraconidVillage_Text_DraconidRepOldWomanRevealed::
	.string "A dragon raised from the egg never\n"
	.string "forgets the face it saw first.\p"
	.string "Yours saw a brave one. I always knew it\n"
	.string "would.$"

DraconidVillage_Text_DraconidRepPondWomanUniform::
	.string "Drink some of the peak water before you\n"
	.string "go back down.\p"
	.string "You look tired, {PLAYER}. That uniform\n"
	.string "must weigh more than it looks.$"

DraconidVillage_Text_DraconidRepPondWomanRevealed::
	.string "The water from the peaks tastes\n"
	.string "sweeter after good news!\p"
	.string "And the news from SOOTOPOLIS was the\n"
	.string "best we've had in years.$"

DraconidVillage_Text_DraconidRepBoyUniform::
	.string "Whoa! Is that what the red ones down\n"
	.string "there wear?\p"
	.string "When I get my egg, I'm never wearing\n"
	.string "anything that itchy-looking.$"

DraconidVillage_Text_DraconidRepBoyRevealed::
	.string "When I get my egg, I want to be a tamer\n"
	.string "just like you!\p"
	.string "Someone who goes down to the lowlands\n"
	.string "and comes back a hero!$"

DraconidVillage_Text_DraconidRepGatekeeperUniform::
	.string "GATEKEEPER: Halt! Who goes… Oh. It's\n"
	.string "you, {PLAYER}.\p"
	.string "In that red, I almost raised the alarm.\n"
	.string "Welcome home, tamer.$"

DraconidVillage_Text_DraconidRepGatekeeperRevealed::
	.string "GATEKEEPER: Welcome home, {PLAYER}!\p"
	.string "The lowlands finally know what kind of\n"
	.string "tamer we sent them.$"

DraconidVillage_House1_Text_DraconidRepWeaverUniform::
	.string "Where is your scarf, child? Tucked away\n"
	.string "under all that red, I hope.\p"
	.string "Down there it would give you away. Up\n"
	.string "here, it's the first thing I look for.$"

DraconidVillage_House1_Text_DraconidRepWeaverRevealed::
	.string "Your scarf is back where it belongs!\p"
	.string "I'll weave you a new one. One fit for the\n"
	.string "tamer who stood up to MAXIE.$"

DraconidVillage_House1_Text_DraconidRepGirlUniform::
	.string "Grandpa ELDER says you're playing a\n"
	.string "secret game with the people in red.\p"
	.string "I won't tell anyone! Cross my heart!$"

DraconidVillage_House1_Text_DraconidRepGirlRevealed::
	.string "You won the secret game!\p"
	.string "Grandpa ELDER says everybody in HOENN\n"
	.string "knows your name now!$"

DraconidVillage_House2_Text_DraconidRepHunterUniform::
	.string "I trade scales down in the lowland\n"
	.string "towns.\p"
	.string "Folks there talk about a TEAM MAGMA\n"
	.string "grunt with a dragon.\p"
	.string "I just nod and say nothing. Mind you're\n"
	.string "careful down there.$"

DraconidVillage_House2_Text_DraconidRepHunterRevealed::
	.string "Down in the lowland towns, everyone's\n"
	.string "talking about you!\p"
	.string "My scales sell twice as fast since I\n"
	.string "started saying I'm from your village.$"

DraconidVillage_House2_Text_DraconidRepWifeUniform::
	.string "The lowlanders run their whole lives by\n"
	.string "their clocks.\p"
	.string "And now by their colors, too.\p"
	.string "Red, blue… Up here we only ask if your\n"
	.string "dragon trusts you.$"

DraconidVillage_House2_Text_DraconidRepWifeRevealed::
	.string "I bet even the lowlanders' clocks\n"
	.string "stopped for the news from SOOTOPOLIS!\p"
	.string "Welcome home, dear.$"
