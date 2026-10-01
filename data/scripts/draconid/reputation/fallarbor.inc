FallarborTown_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_EventScript_DraconidRepGirl_2
	case REPUTATION_REVEALED, FallarborTown_EventScript_DraconidRepGirl_3
	goto FallarborTown_EventScript_Girl
	return

FallarborTown_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox FallarborTown_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

FallarborTown_EventScript_DraconidRepGirl_3:
	msgbox FallarborTown_Text_DraconidRepGirlRevealed, MSGBOX_NPC
	return


FallarborTown_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_EventScript_DraconidRepExpertM_2
	case REPUTATION_REVEALED, FallarborTown_EventScript_DraconidRepExpertM_3
	goto FallarborTown_EventScript_ExpertM
	return

FallarborTown_EventScript_DraconidRepExpertM_2:
	lock
	faceplayer
	msgbox FallarborTown_Text_DraconidRepExpertMUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

FallarborTown_EventScript_DraconidRepExpertM_3:
	msgbox FallarborTown_Text_DraconidRepExpertMRevealed, MSGBOX_NPC
	return


FallarborTown_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_EventScript_DraconidRepGentleman_2
	case REPUTATION_REVEALED, FallarborTown_EventScript_DraconidRepGentleman_3
	goto FallarborTown_EventScript_Gentleman
	return

FallarborTown_EventScript_DraconidRepGentleman_2:
	msgbox FallarborTown_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return

FallarborTown_EventScript_DraconidRepGentleman_3:
	msgbox FallarborTown_Text_DraconidRepGentlemanRevealed, MSGBOX_NPC
	return


FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_2
	case REPUTATION_REVEALED, FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_3
	goto FallarborTown_PokemonCenter_1F_EventScript_ExpertM
	return

FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_2:
	msgbox FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMUniform, MSGBOX_NPC
	return

FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM_3:
	msgbox FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMRevealed, MSGBOX_NPC
	return


FallarborTown_CozmosHouse_EventScript_DraconidRepNoticeMeteoriteUniform::
	msgbox FallarborTown_CozmosHouse_Text_DraconidRepCozmoUniform, MSGBOX_YESNO
	return


FallarborTown_CozmosHouse_EventScript_DraconidRepCozmoRevealed::
	msgbox FallarborTown_CozmosHouse_Text_DraconidRepCozmoRevealed, MSGBOX_DEFAULT
	release
	end


FallarborTown_BattleTentLobby_EventScript_DraconidRepAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FallarborTown_BattleTentLobby_EventScript_DraconidRepAttendant_2
FallarborTown_BattleTentLobby_EventScript_DraconidRepAttendant_1:
	goto FallarborTown_BattleTentLobby_EventScript_Attendant
	return

FallarborTown_BattleTentLobby_EventScript_DraconidRepAttendant_2:
	lock
	faceplayer
	msgbox FallarborTown_BattleTentLobby_Text_DraconidRepAttendantUniform, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_DraconidRepAttendant_1


FallarborTown_BattleTentLobby_EventScript_DraconidRepHiker::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_BattleTentLobby_EventScript_DraconidRepHiker_2
	goto FallarborTown_BattleTentLobby_EventScript_Hiker
	return

FallarborTown_BattleTentLobby_EventScript_DraconidRepHiker_2:
	msgbox FallarborTown_BattleTentLobby_Text_DraconidRepHikerUniform, MSGBOX_NPC
	return


FallarborTown_BattleTentLobby_EventScript_DraconidRepLittleBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_BattleTentLobby_EventScript_DraconidRepLittleBoy_2
	goto FallarborTown_BattleTentLobby_EventScript_LittleBoy
	return

FallarborTown_BattleTentLobby_EventScript_DraconidRepLittleBoy_2:
	msgbox FallarborTown_BattleTentLobby_Text_DraconidRepLittleBoyUniform, MSGBOX_NPC
	return


FallarborTown_BattleTentLobby_EventScript_DraconidRepLass::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_BattleTentLobby_EventScript_DraconidRepLass_2
	goto FallarborTown_BattleTentLobby_EventScript_Lass
	return

FallarborTown_BattleTentLobby_EventScript_DraconidRepLass_2:
	msgbox FallarborTown_BattleTentLobby_Text_DraconidRepLassUniform, MSGBOX_NPC
	return


FallarborTown_Mart_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_Mart_EventScript_DraconidRepWoman_2
	goto FallarborTown_Mart_EventScript_Woman
	return

FallarborTown_Mart_EventScript_DraconidRepWoman_2:
	msgbox FallarborTown_Mart_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


FallarborTown_Mart_EventScript_DraconidRepPokefanM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_Mart_EventScript_DraconidRepPokefanM_2
	goto FallarborTown_Mart_EventScript_PokefanM
	return

FallarborTown_Mart_EventScript_DraconidRepPokefanM_2:
	msgbox FallarborTown_Mart_Text_DraconidRepPokefanMUniform, MSGBOX_NPC
	return


FallarborTown_Mart_EventScript_DraconidRepMetronomeTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FallarborTown_Mart_EventScript_DraconidRepMetronomeTutor_2
FallarborTown_Mart_EventScript_DraconidRepMetronomeTutor_1:
	goto FallarborTown_Mart_EventScript_MetronomeTutor
	return

FallarborTown_Mart_EventScript_DraconidRepMetronomeTutor_2:
	lock
	faceplayer
	msgbox FallarborTown_Mart_Text_DraconidRepMetronomeTutorUniform, MSGBOX_DEFAULT
	goto FallarborTown_Mart_EventScript_DraconidRepMetronomeTutor_1


FallarborTown_MoveRelearnersHouse_EventScript_DraconidRepMoveRelearner::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FallarborTown_MoveRelearnersHouse_EventScript_DraconidRepMoveRelearner_2
FallarborTown_MoveRelearnersHouse_EventScript_DraconidRepMoveRelearner_1:
	goto FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner
	return

FallarborTown_MoveRelearnersHouse_EventScript_DraconidRepMoveRelearner_2:
	lock
	faceplayer
	msgbox FallarborTown_MoveRelearnersHouse_Text_DraconidRepMoveRelearnerUniform, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_DraconidRepMoveRelearner_1


FallarborTown_PokemonCenter_1F_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, FallarborTown_PokemonCenter_1F_EventScript_DraconidRepGirl_2
	goto FallarborTown_PokemonCenter_1F_EventScript_Girl
	return

FallarborTown_PokemonCenter_1F_EventScript_DraconidRepGirl_2:
	msgbox FallarborTown_PokemonCenter_1F_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


FallarborTown_PokemonCenter_1F_EventScript_DraconidRepLanette::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq FallarborTown_PokemonCenter_1F_EventScript_DraconidRepLanette_2
FallarborTown_PokemonCenter_1F_EventScript_DraconidRepLanette_1:
	goto FallarborTown_PokemonCenter_1F_EventScript_Lanette
	return

FallarborTown_PokemonCenter_1F_EventScript_DraconidRepLanette_2:
	lock
	faceplayer
	msgbox FallarborTown_PokemonCenter_1F_Text_DraconidRepLanetteUniform, MSGBOX_DEFAULT
	goto FallarborTown_PokemonCenter_1F_EventScript_DraconidRepLanette_1


FallarborTown_Text_DraconidRepGirlUniform::
	.string "This is my precious AZURILL. You can't\n"
	.string "have it!\p"
	.string "TEAM MAGMA isn't taking my AZURILL\n"
	.string "anywhere!$"

FallarborTown_Text_DraconidRepGirlRevealed::
	.string "See! This is my precious AZURILL!\p"
	.string "It's slick and smooth and plushy! You\n"
	.string "can pet it, if you like!$"

FallarborTown_Text_DraconidRepExpertMUniform::
	.string "You! I've seen your kind around PROF.\n"
	.string "COZMO's home!\p"
	.string "What does TEAM MAGMA want with him?\n"
	.string "…Hmph! I'm watching you.$"

FallarborTown_Text_DraconidRepExpertMRevealed::
	.string "I shouted at you about PROF. COZMO…\p"
	.string "But you were working against TEAM\n"
	.string "MAGMA all along. I'm sorry.$"

FallarborTown_Text_DraconidRepGentlemanUniform::
	.string "The ash that falls on FALLARBOR comes\n"
	.string "from MT. CHIMNEY.\p"
	.string "And I hear TEAM MAGMA has been meddling\n"
	.string "with it. …Shameful.$"

FallarborTown_Text_DraconidRepGentlemanRevealed::
	.string "FLANNERY's grandfather was one of the\n"
	.string "ELITE FOUR.\p"
	.string "But you… You might be greater than any\n"
	.string "of them!$"

FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMUniform::
	.string "We plant trees that grow even in\n"
	.string "volcanic ash.\p"
	.string "TEAM MAGMA plants nothing. It only\n"
	.string "burns.$"

FallarborTown_PokemonCenter_1F_Text_DraconidRepExpertMRevealed::
	.string "We plant trees that grow even in\n"
	.string "volcanic ash.\p"
	.string "I'll plant one for you, {PLAYER}. So\n"
	.string "FALLARBOR remembers.$"

FallarborTown_CozmosHouse_Text_DraconidRepCozmoUniform::
	.string "PROF. COZMO: Y-you!\n"
	.string "You're the one from the falls!\p"
	.string "…Wait. Is that my METEORITE?\n"
	.string "You're giving it back?\p"
	.string "I… I won't tell a soul\n"
	.string "where it came from.\p"
	.string "May I have it?\n"
	.string "I'll trade you this TM for it.$"

FallarborTown_CozmosHouse_Text_DraconidRepCozmoRevealed::
	.string "PROF. COZMO: So THAT's why\n"
	.string "you gave it back!\p"
	.string "This METEORITE is really going to help\n"
	.string "my research. Thank you, {PLAYER}!$"

FallarborTown_BattleTentLobby_Text_DraconidRepAttendantUniform::
	.string "Hm. TEAM MAGMA. Your people dropped ash\n"
	.string "all over this town, you know.\p"
	.string "…But the Set KO Tourney is open to\n"
	.string "everyone. I am bound by its rules.$"

FallarborTown_BattleTentLobby_Text_DraconidRepHikerUniform::
	.string "I came to camp out in the luxurious\n"
	.string "tent!\p"
	.string "Didn't expect to share it with TEAM\n"
	.string "MAGMA, though.$"

FallarborTown_BattleTentLobby_Text_DraconidRepLittleBoyUniform::
	.string "Fufufufufu. Everyone thinks I'm just a\n"
	.string "kid.\p"
	.string "Everyone thinks you're just a TEAM\n"
	.string "MAGMA grunt. We should both show them!$"

FallarborTown_BattleTentLobby_Text_DraconidRepLassUniform::
	.string "FALLARBOR's BATTLE TENT is my favorite.\n"
	.string "TRAINERS try so hard to win!\p"
	.string "Though I don't know who'd root for a\n"
	.string "TEAM MAGMA grunt.$"

FallarborTown_Mart_Text_DraconidRepWomanUniform::
	.string "Should I make my SKITTY evolve with\n"
	.string "this MOON STONE?\p"
	.string "It's so hard to decide…\p"
	.string "I'll decide later, once TEAM MAGMA stops\n"
	.string "reading over my shoulder.$"

FallarborTown_Mart_Text_DraconidRepPokefanMUniform::
	.string "I found this NUGGET and I suppose I'll\n"
	.string "have to sell it.\p"
	.string "Don't even think about it, TEAM MAGMA.\n"
	.string "It's mine.$"

FallarborTown_Mart_Text_DraconidRepMetronomeTutorUniform::
	.string "TEAM MAGMA? Hmm… METRONOME is a\n"
	.string "gamble, and so is talking to you.$"

FallarborTown_MoveRelearnersHouse_Text_DraconidRepMoveRelearnerUniform::
	.string "A TEAM MAGMA grunt? I've taught moves\n"
	.string "to all sorts…\p"
	.string "Never to one of you, though. Well,\n"
	.string "there's a first time for everything.$"

FallarborTown_PokemonCenter_1F_Text_DraconidRepGirlUniform::
	.string "I wonder what POKéMON looked like long\n"
	.string "ago.\p"
	.string "TEAM MAGMA wants to bring back ancient\n"
	.string "things, I hear.\p"
	.string "Like the land from long ago.$"

FallarborTown_PokemonCenter_1F_Text_DraconidRepLanetteUniform::
	.string "TEAM MAGMA? In the POKéMON CENTER?\n"
	.string "…Hmm.$"
