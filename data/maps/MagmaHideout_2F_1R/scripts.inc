MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:  @ Draconid Emerald
	.string "What, what, what?\p"
	.string "A face I don't know, in a TEAM MAGMA\n"
	.string "uniform?\p"
	.string "They say the LEADER gave some new\n"
	.string "grunt his own EMBLEM…\p"
	.string "You rouse my suspicion! Rank test!\n"
	.string "Battle with me!$"

MagmaHideout_2F_1R_Text_Grunt14Defeat:
	.string "Aiyiyi…\n"
	.string "My pride as a TEAM MAGMA member…$"

MagmaHideout_2F_1R_Text_Grunt14PostBattle:  @ Draconid Emerald
	.string "If you suffer from chills, you've come\n"
	.string "to the right TEAM.\p"
	.string "Welcome to the HIDEOUT, I guess.$"

MagmaHideout_2F_1R_Text_Grunt3Intro:  @ Draconid Emerald
	.string "Hold it right there!\p"
	.string "New face, shiny EMBLEM… You don't\n"
	.string "really expect me to let you waltz by\l"
	.string "without a rank test?$"

MagmaHideout_2F_1R_Text_Grunt3Defeat:
	.string "Ooh wow!\n"
	.string "I concede!$"

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
	.string "Maybe it would've been better if I did\n"
	.string "just let you go unchallenged…$"

MagmaHideout_2F_1R_Text_Grunt4Intro:  @ Draconid Emerald
	.string "Ahah!\n"
	.string "A grunt I've never seen! Rank test!$"

MagmaHideout_2F_1R_Text_Grunt4Defeat:
	.string "Graaah!$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
	.string "I've already lost.\p"
	.string "Do I really need to keep running\n"
	.string "around in a circle?$"

MagmaHideout_2F_1R_Text_Grunt5Intro:  @ Draconid Emerald
	.string "Oh, oh!\n"
	.string "You're the new one everybody's talking\l"
	.string "about!$"

MagmaHideout_2F_1R_Text_Grunt5Defeat:
	.string "Mutter…$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
	.string "Actually, I'm no expert at battling…$"

