Draconid_EventScript_RepTurnAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceAwayPlayer
	waitmovement 0
	release
	end


Draconid_EventScript_NurseGreeting::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Draconid_EventScript_NurseGreeting_2
	msgbox Draconid_Text_NurseGreetingRevealed, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Draconid_EventScript_NurseGreeting_5
Draconid_EventScript_NurseGreeting_4:
	goto EventScript_PkmnCenterNurse_Goodbye
	return

Draconid_EventScript_NurseGreeting_2:
	msgbox Draconid_Text_NurseGreetingUniform, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Draconid_EventScript_NurseGreeting_8
Draconid_EventScript_NurseGreeting_7:
	message Draconid_Text_NurseGoodbyeUniform
	return

Draconid_EventScript_NurseGreeting_5:
	goto EventScript_PkmnCenterNurse_HealPkmn
	goto Draconid_EventScript_NurseGreeting_4

Draconid_EventScript_NurseGreeting_8:
	goto EventScript_PkmnCenterNurse_HealPkmn
	goto Draconid_EventScript_NurseGreeting_7


Draconid_EventScript_NurseTakePkmnUniform::
	message Draconid_Text_NurseTakePkmnUniform
	return


Draconid_EventScript_NurseReturnPkmnUniform::
	message Draconid_Text_NurseReturnPkmnUniform
	return


Draconid_EventScript_MartGreeting::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Draconid_EventScript_MartGreeting_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq Draconid_EventScript_MartGreeting_3
	message gText_HowMayIServeYou
Draconid_EventScript_MartGreeting_1:
	return

Draconid_EventScript_MartGreeting_2:
	message Draconid_Text_MartGreetingUniform
	goto Draconid_EventScript_MartGreeting_1

Draconid_EventScript_MartGreeting_3:
	message Draconid_Text_MartGreetingRevealed
	goto Draconid_EventScript_MartGreeting_1


Draconid_EventScript_MartGoodbye::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Draconid_EventScript_MartGoodbye_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq Draconid_EventScript_MartGoodbye_3
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
Draconid_EventScript_MartGoodbye_1:
	return

Draconid_EventScript_MartGoodbye_2:
	msgbox Draconid_Text_MartGoodbyeUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_MartGoodbye_1

Draconid_EventScript_MartGoodbye_3:
	msgbox Draconid_Text_MartGoodbyeRevealed, MSGBOX_DEFAULT
	goto Draconid_EventScript_MartGoodbye_1


Draconid_EventScript_CableClubAside::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Draconid_EventScript_CableClubAside_2
	msgbox Draconid_Text_CableClubAsideRevealed, MSGBOX_DEFAULT
Draconid_EventScript_CableClubAside_1:
	return

Draconid_EventScript_CableClubAside_2:
	msgbox Draconid_Text_CableClubAsideUniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_CableClubAside_1


Draconid_EventScript_WirelessClubAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Draconid_EventScript_WirelessClubAttendant_2
	msgbox Draconid_Text_TealaAskRevealed, MSGBOX_YESNO
Draconid_EventScript_WirelessClubAttendant_1:
	compare VAR_RESULT, NO
	goto_if_eq Draconid_EventScript_WirelessClubAttendant_6
Draconid_EventScript_WirelessClubAttendant_5:
	msgbox CableClub_Text_ExplainWirelessClub, MSGBOX_DEFAULT
	release
	return

Draconid_EventScript_WirelessClubAttendant_2:
	msgbox Draconid_Text_TealaAskUniform, MSGBOX_YESNO
	goto Draconid_EventScript_WirelessClubAttendant_1

Draconid_EventScript_WirelessClubAttendant_6:
	goto CableClub_EventScript_DontAskAboutLinking
	goto Draconid_EventScript_WirelessClubAttendant_5


Route117_EventScript_DraconidDaycareMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route117_EventScript_DraconidDaycareMan_2
	msgbox Route117_Text_DraconidDaycareManRevealed, MSGBOX_DEFAULT
Route117_EventScript_DraconidDaycareMan_1:
	release
	end

Route117_EventScript_DraconidDaycareMan_2:
	msgbox Route117_Text_DraconidDaycareManUniform, MSGBOX_DEFAULT
	goto Route117_EventScript_DraconidDaycareMan_1


Route117_PokemonDayCare_EventScript_DraconidDaycareWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_2
	msgbox Route117_PokemonDayCare_Text_DraconidDaycareWomanRevealed, MSGBOX_YESNO
Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_1:
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_6
Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_5:
	msgbox Route117_PokemonDayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_2:
	msgbox Route117_PokemonDayCare_Text_DraconidDaycareWomanUniform, MSGBOX_YESNO
	goto Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_1

Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_6:
	goto Route117_PokemonDayCare_EventScript_GiveMonToRaise
	goto Route117_PokemonDayCare_EventScript_DraconidDaycareWoman_5


Draconid_Text_NurseGreetingUniform::
	.string "…That uniform. TEAM MAGMA.\p"
	.string "…Fine. We don't turn away POKéMON. Even\n"
	.string "yours.\p"
	.string "Do you want them healed?$"

Draconid_Text_NurseGoodbyeUniform::
	.string "…Suit yourself.$"

Draconid_Text_NurseTakePkmnUniform::
	.string "…Hand them over, then.$"

Draconid_Text_NurseReturnPkmnUniform::
	.string "They're healed.\p"
	.string "…They trust you so much. I hope you\n"
	.string "deserve it.$"

Draconid_Text_NurseGreetingRevealed::
	.string "Welcome back, {PLAYER}!\p"
	.string "We all heard what you did in SOOTOPOLIS.\n"
	.string "I'm sorry I was so cold to you.\p"
	.string "Would you like to rest your POKéMON?$"

Draconid_Text_MartGreetingUniform::
	.string "…TEAM MAGMA. Hmph.\p"
	.string "Your money spends like anyone's, I\n"
	.string "suppose. What do you want?$"

Draconid_Text_MartGoodbyeUniform::
	.string "…That's all? Then please go.$"

Draconid_Text_MartGreetingRevealed::
	.string "Oh! Welcome, {PLAYER}!\p"
	.string "Sorry about how I treated you before.\n"
	.string "What can I get you?$"

Draconid_Text_MartGoodbyeRevealed::
	.string "Thank you so much! Please come again!$"

Draconid_Text_CableClubAsideUniform::
	.string "…A TEAM MAGMA grunt, in the CABLE CLUB.\p"
	.string "Our rules say every TRAINER may link\n"
	.string "here. …Even you.$"

Draconid_Text_CableClubAsideRevealed::
	.string "Oh! It's {PLAYER}, from SOOTOPOLIS!\p"
	.string "The CABLE CLUB is honored to have you.$"

Draconid_Text_TealaAskUniform::
	.string "…Oh. It's you, {PLAYER}.\p"
	.string "I'm TEALA, the 2F attendant. I help\n"
	.string "every TRAINER. That's my job.\p"
	.string "…Did you need to ask me about linking?$"

Draconid_Text_TealaAskRevealed::
	.string "{PLAYER}! It's me, TEALA!\p"
	.string "I'm sorry I was so cold to you. I should\n"
	.string "have known better.\p"
	.string "Is there something you needed to ask\n"
	.string "me about linking?$"

Route117_Text_DraconidDaycareManUniform::
	.string "Hm? That red getup… TEAM MAGMA, eh?\p"
	.string "I'm too old to be scared of a uniform.\p"
	.string "If you want a POKéMON raised, talk to my\n"
	.string "wife. The POKéMON aren't to blame.$"

Route117_Text_DraconidDaycareManRevealed::
	.string "Ah, it's you! We read about SOOTOPOLIS\n"
	.string "in the paper.\p"
	.string "My wife and I would be proud to raise\n"
	.string "your POKéMON. Talk to her anytime!$"

Route117_PokemonDayCare_Text_DraconidDaycareWomanUniform::
	.string "…Oh my. A TEAM MAGMA grunt.\p"
	.string "Well, a POKéMON is a POKéMON, whoever\n"
	.string "brings it in.\p"
	.string "Would you like us to raise one of yours?$"

Route117_PokemonDayCare_Text_DraconidDaycareWomanRevealed::
	.string "Oh, it's you, dear! My husband told me\n"
	.string "everything.\p"
	.string "To think we were afraid of you! Please\n"
	.string "forgive two old worriers.\p"
	.string "Would you like us to raise one of your\n"
	.string "POKéMON?$"
