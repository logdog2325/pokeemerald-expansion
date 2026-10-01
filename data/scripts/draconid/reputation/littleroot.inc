LittlerootTown_EventScript_DraconidRepTwin::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_EventScript_DraconidRepTwin_2
	case REPUTATION_REVEALED, LittlerootTown_EventScript_DraconidRepTwin_3
	goto LittlerootTown_EventScript_Twin
	return

LittlerootTown_EventScript_DraconidRepTwin_2:
	msgbox LittlerootTown_Text_DraconidRepTwinUniform, MSGBOX_NPC
	return

LittlerootTown_EventScript_DraconidRepTwin_3:
	msgbox LittlerootTown_Text_DraconidRepTwinRevealed, MSGBOX_NPC
	return


LittlerootTown_EventScript_DraconidRepFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_EventScript_DraconidRepFatMan_2
	case REPUTATION_REVEALED, LittlerootTown_EventScript_DraconidRepFatMan_3
	goto LittlerootTown_EventScript_FatMan
	return

LittlerootTown_EventScript_DraconidRepFatMan_2:
	msgbox LittlerootTown_Text_DraconidRepFatManUniform, MSGBOX_NPC
	return

LittlerootTown_EventScript_DraconidRepFatMan_3:
	msgbox LittlerootTown_Text_DraconidRepFatManRevealed, MSGBOX_NPC
	return


LittlerootTown_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_EventScript_DraconidRepBoy_2
	case REPUTATION_REVEALED, LittlerootTown_EventScript_DraconidRepBoy_3
	goto LittlerootTown_EventScript_Boy
	return

LittlerootTown_EventScript_DraconidRepBoy_2:
	lock
	faceplayer
	msgbox LittlerootTown_Text_DraconidRepBoyUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

LittlerootTown_EventScript_DraconidRepBoy_3:
	msgbox LittlerootTown_Text_DraconidRepBoyRevealed, MSGBOX_NPC
	return


LittlerootTown_BrendansHouse_1F_EventScript_DraconidRepRivalSibling::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_BrendansHouse_1F_EventScript_DraconidRepRivalSibling_2
	case REPUTATION_REVEALED, LittlerootTown_BrendansHouse_1F_EventScript_DraconidRepRivalSibling_3
	goto RivalsHouse_1F_EventScript_RivalSibling
	return

LittlerootTown_BrendansHouse_1F_EventScript_DraconidRepRivalSibling_2:
	msgbox LittlerootTown_BrendansHouse_1F_Text_DraconidRepRivalSiblingUniform, MSGBOX_NPC
	return

LittlerootTown_BrendansHouse_1F_EventScript_DraconidRepRivalSibling_3:
	msgbox LittlerootTown_BrendansHouse_1F_Text_DraconidRepRivalSiblingRevealed, MSGBOX_NPC
	return


LittlerootTown_MaysHouse_1F_EventScript_DraconidRepRivalSibling::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, LittlerootTown_MaysHouse_1F_EventScript_DraconidRepRivalSibling_2
	case REPUTATION_REVEALED, LittlerootTown_MaysHouse_1F_EventScript_DraconidRepRivalSibling_3
	goto RivalsHouse_1F_EventScript_RivalSibling
	return

LittlerootTown_MaysHouse_1F_EventScript_DraconidRepRivalSibling_2:
	msgbox LittlerootTown_MaysHouse_1F_Text_DraconidRepRivalSiblingUniform, MSGBOX_NPC
	return

LittlerootTown_MaysHouse_1F_EventScript_DraconidRepRivalSibling_3:
	msgbox LittlerootTown_MaysHouse_1F_Text_DraconidRepRivalSiblingRevealed, MSGBOX_NPC
	return


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide_3
LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide_1:
	goto LittlerootTown_ProfessorBirchsLab_EventScript_Aide
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide_2:
	lock
	faceplayer
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRepAideUniform, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide_1

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide_3:
	lock
	faceplayer
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRepAideRevealed, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepAide_1


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch_3
LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch_1:
	goto LittlerootTown_ProfessorBirchsLab_EventScript_Birch
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch_2:
	lock
	faceplayer
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRepBirchUniform, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch_1

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch_3:
	lock
	faceplayer
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRepBirchRevealed, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidRepBirch_1


LittlerootTown_Text_DraconidRepTwinUniform::
	.string "…You look scary in those clothes.\p"
	.string "My mommy says TEAM MAGMA are bad\n"
	.string "people.\p"
	.string "But you saved PROF. BIRCH… Are you a\n"
	.string "bad person now?$"

LittlerootTown_Text_DraconidRepTwinRevealed::
	.string "You were only pretending to be bad! I\n"
	.string "knew it!\p"
	.string "When I grow up, I want to be brave like\n"
	.string "you!$"

LittlerootTown_Text_DraconidRepFatManUniform::
	.string "Hm? Is that a TEAM MAGMA uniform?\p"
	.string "You helped PROF. BIRCH on ROUTE 101!\n"
	.string "Why would you join them?\p"
	.string "The power of people to surprise me is\n"
	.string "staggering…$"

LittlerootTown_Text_DraconidRepFatManRevealed::
	.string "So you were working against TEAM MAGMA\n"
	.string "all along!\p"
	.string "The power of a good disguise is\n"
	.string "staggering!$"

LittlerootTown_Text_DraconidRepBoyUniform::
	.string "PROF. BIRCH's LAB is right over there.\p"
	.string "…You're not here to steal his research\n"
	.string "for TEAM MAGMA, are you?$"

LittlerootTown_Text_DraconidRepBoyRevealed::
	.string "PROF. BIRCH says he never stopped\n"
	.string "believing in you.\p"
	.string "…I wasn't so sure. Sorry about that.$"

LittlerootTown_BrendansHouse_1F_Text_DraconidRepRivalSiblingUniform::
	.string "Whoa, a real TEAM MAGMA uniform!\p"
	.string "Mom says I'm not allowed to talk to\n"
	.string "people in red. …Is it itchy?$"

LittlerootTown_BrendansHouse_1F_Text_DraconidRepRivalSiblingRevealed::
	.string "My big brother says he was wrong about\n"
	.string "you.\p"
	.string "He made me promise never to tell you he\n"
	.string "said that!$"

LittlerootTown_MaysHouse_1F_Text_DraconidRepRivalSiblingUniform::
	.string "You're the one with the dragon!\p"
	.string "Why are you dressed like the bad guys\n"
	.string "on TV? Is it a costume?$"

LittlerootTown_MaysHouse_1F_Text_DraconidRepRivalSiblingRevealed::
	.string "MAY says she knew you were good the\n"
	.string "whole time.\p"
	.string "She won't stop saying it. Even at\n"
	.string "dinner!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidRepAideUniform::
	.string "You're the kid who saved PROF. BIRCH on\n"
	.string "ROUTE 101!\p"
	.string "But that's… a TEAM MAGMA uniform.\p"
	.string "I asked the PROF about you. All he said\n"
	.string "was, “Don't judge a book by its cover.”$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidRepAideRevealed::
	.string "PROF. BIRCH was right about you.\p"
	.string "He kept saying, “Wait and see.” Well, now\n"
	.string "we've seen!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidRepBirchUniform::
	.string "PROF. BIRCH: {PLAYER}{KUN}! …Ahem. My aide is\n"
	.string "right there, so I'll keep my voice down.\p"
	.string "Whatever that red uniform says, I know\n"
	.string "what I saw on ROUTE 101.\p"
	.string "Take care of yourself out there.$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidRepBirchRevealed::
	.string "PROF. BIRCH: {PLAYER}{KUN}! Now the whole\n"
	.string "region knows!\p"
	.string "I had to bite my tongue for so long.\n"
	.string "Hahaha!$"
