DraconidVillage_Shrine_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DraconidVillage_Shrine_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DraconidVillage_Shrine_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DraconidVillage_Shrine_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_DRACONID_STATE, DRACONID_STATE_EGG_RECEIVED, DraconidVillage_Shrine_EventScript_HatchingRite
	.2byte 0


DraconidVillage_Shrine_OnTransition::
	call DraconidVillage_Shrine_EventScript_DraconidAsterPostgame
	return


DraconidVillage_Shrine_EventScript_HatchingRite::
	lockall
	msgbox DraconidVillage_Shrine_EventScript_HatchingRite_Text_0
	closemessage
	applymovement LOCALID_PLAYER, DraconidVillage_Shrine_Movement_PlayerApproach
	waitmovement 0
	msgbox DraconidVillage_Shrine_EventScript_HatchingRite_Text_1
	closemessage
	playse SE_M_DRAGON_RAGE
	fadescreen FADE_TO_WHITE
	delay 20
	fadescreen FADE_FROM_WHITE
	waitse
	msgbox DraconidVillage_Shrine_EventScript_HatchingRite_Text_2
	closemessage
	setvar VAR_0x8004, 0
	special EggHatch
	setvar VAR_0x8004, 0
	special DraconidRaiseHatchling
	setflag FLAG_DRACONID_EGG_HATCHED
	applymovement LOCALID_DRACONID_SHRINE_ASTER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	switch VAR_ASTER_EGG
	case DRACONID_EGG_DEINO, DraconidVillage_Shrine_EventScript_HatchingRite_3
	case DRACONID_EGG_DREEPY, DraconidVillage_Shrine_EventScript_HatchingRite_4
	bufferspeciesname STR_VAR_1, DRACONID_EGG_SPECIES_2
DraconidVillage_Shrine_EventScript_HatchingRite_1:
	msgbox DraconidVillage_Shrine_EventScript_HatchingRite_Text_3
	msgbox DraconidVillage_Shrine_EventScript_HatchingRite_Text_4
	closemessage
	applymovement LOCALID_DRACONID_SHRINE_ASTER, DraconidVillage_Shrine_Movement_AsterLeaves
	waitmovement 0
	removeobject LOCALID_DRACONID_SHRINE_ASTER
	clearflag FLAG_HIDE_DRACONID_PASS_ASTER
	applymovement LOCALID_DRACONID_SHRINE_ELDER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox DraconidVillage_Shrine_EventScript_HatchingRite_Text_5
	closemessage
	setflag FLAG_HIDE_DRACONID_SHRINE_ELDER
	clearflag FLAG_HIDE_DRACONID_ELDERS_HOUSE_ELDER
	clearflag FLAG_HIDE_DRACONID_VILLAGE_MOM
	setvar VAR_DRACONID_STATE, DRACONID_STATE_EGG_HATCHED
	releaseall
	return

DraconidVillage_Shrine_EventScript_HatchingRite_3:
	bufferspeciesname STR_VAR_1, DRACONID_EGG_SPECIES_0
	goto DraconidVillage_Shrine_EventScript_HatchingRite_1

DraconidVillage_Shrine_EventScript_HatchingRite_4:
	bufferspeciesname STR_VAR_1, DRACONID_EGG_SPECIES_1
	goto DraconidVillage_Shrine_EventScript_HatchingRite_1


DraconidVillage_Shrine_Movement_PlayerApproach:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DraconidVillage_Shrine_Movement_AsterLeaves:
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

DraconidVillage_Shrine_EventScript_Statue::
	msgbox DraconidVillage_Shrine_EventScript_Statue_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_BackWall::
	msgbox DraconidVillage_Shrine_EventScript_BackWall_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore1::
	msgbox DraconidVillage_Shrine_EventScript_Lore1_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore2::
	msgbox DraconidVillage_Shrine_EventScript_Lore2_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore3::
	msgbox DraconidVillage_Shrine_EventScript_Lore3_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore4::
	msgbox DraconidVillage_Shrine_EventScript_Lore4_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore5::
	msgbox DraconidVillage_Shrine_EventScript_Lore5_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_Lore6::
	msgbox DraconidVillage_Shrine_EventScript_Lore6_Text_0, MSGBOX_SIGN
	return


DraconidVillage_Shrine_EventScript_HatchingRite_Text_0:
	.string "ELDER: Come forward, {PLAYER}.$"

DraconidVillage_Shrine_EventScript_HatchingRite_Text_1:
	.string "ELDER: Guardian of the Sky, who stilled\n"
	.string "the land and the sea…\p"
	.string "Two children of the clan stand before\n"
	.string "you with their eggs.\p"
	.string "Let the young dragons hear your call!$"

DraconidVillage_Shrine_EventScript_HatchingRite_Text_2:
	.string "Huh?\p"
	.string "The egg is moving!$"

DraconidVillage_Shrine_EventScript_HatchingRite_Text_3:
	.string "ASTER's egg hatched too! A\n"
	.string "{STR_VAR_1} blinked up at her.$"

DraconidVillage_Shrine_EventScript_HatchingRite_Text_4:
	.string "ASTER: …Hello, little one. We have a long\n"
	.string "way to climb, you and I.\p"
	.string "{PLAYER}. They say the Guardian only\n"
	.string "answers those who reach the top of the\l"
	.string "sky.\p"
	.string "I intend to be the one it answers. Don't\n"
	.string "fall behind.$"

DraconidVillage_Shrine_EventScript_HatchingRite_Text_5:
	.string "ELDER: Hohoho… That girl. She has been\n"
	.string "reading the old scrolls again.\p"
	.string "{PLAYER}, there is a man in LITTLEROOT\n"
	.string "TOWN, PROF. BIRCH, who studies Pokémon.\p"
	.string "Our clan and his family have shared our\n"
	.string "knowledge for many years.\p"
	.string "Go to him, and show him your partner. He\n"
	.string "will know what a young tamer needs.\p"
	.string "Your mother is waiting outside. Go on,\n"
	.string "now.$"

DraconidVillage_Shrine_EventScript_Statue_Text_0:
	.string "A statue of a great serpent coiled\n"
	.string "around a fallen star.\p"
	.string "Its eyes seem to follow you, watching\n"
	.string "from somewhere far above the clouds.$"

DraconidVillage_Shrine_EventScript_BackWall_Text_0:
	.string "Words are carved deep into the rock:\p"
	.string "“HERE THE CLAN SPEAKS TO THE SKY. HERE\n"
	.string "THE SKY ANSWERS.”$"

DraconidVillage_Shrine_EventScript_Lore1_Text_0:
	.string "An old carving:\p"
	.string "“Long ago the land and the sea made\n"
	.string "war, and the world burned and drowned\l"
	.string "by turns. The people had no strength\l"
	.string "left, so they cried out to the sky.”$"

DraconidVillage_Shrine_EventScript_Lore2_Text_0:
	.string "An old carving:\p"
	.string "“From beyond the clouds came the\n"
	.string "Guardian of the Sky, and its roar\l"
	.string "stilled both land and sea.”$"

DraconidVillage_Shrine_EventScript_Lore3_Text_0:
	.string "An old carving:\p"
	.string "“A star fell into this valley. From its\n"
	.string "heart the clan carved stones that let\l"
	.string "two souls beat as one.”$"

DraconidVillage_Shrine_EventScript_Lore4_Text_0:
	.string "An old carving:\p"
	.string "“Whoever raises a dragon from the egg,\n"
	.string "and whose bond is true, may borrow the\l"
	.string "light of the fallen star.”$"

DraconidVillage_Shrine_EventScript_Lore5_Text_0:
	.string "An old carving:\p"
	.string "“The Lorekeeper keeps the words. The\n"
	.string "Tamers keep the dragons. Together they\l"
	.string "keep the sky.”$"

DraconidVillage_Shrine_EventScript_Lore6_Text_0:
	.string "An old carving:\p"
	.string "“Should anyone seek to bend land or sea\n"
	.string "to their will, the clan shall stand\l"
	.string "against them, as the Guardian once\l"
	.string "did.”$"
