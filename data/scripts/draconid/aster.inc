Draconid_EventScript_BattleAsterSkyPillar::
	trainerbattle_no_intro TRAINER_ASTER_SKY_PILLAR_DEINO, Draconid_Text_AsterSkyPillarDefeat
	return


Draconid_EventScript_BattleAsterPostgame::
	trainerbattle_no_intro TRAINER_ASTER_POSTGAME_DEINO, Draconid_Text_AsterDefeat
	return


Draconid_EventScript_ChangeOutfit::
	fadescreen FADE_TO_BLACK
	special SetPlayerOutfit
	playse SE_BIKE_HOP
	delay 20
	fadescreen FADE_FROM_BLACK
	return


SkyPillar_Top_EventScript_DraconidAsterClimax::
	compare VAR_ASTER_STATE, ASTER_STATE_SKY_PILLAR
	goto_if_ge SkyPillar_Top_EventScript_DraconidAsterClimax_2
	clearflag FLAG_HIDE_SKY_PILLAR_TOP_ASTER
	addobject LOCALID_SKY_PILLAR_TOP_ASTER
	playbgm MUS_ENCOUNTER_INTENSE, FALSE
	applymovement LOCALID_SKY_PILLAR_TOP_ASTER, Common_Movement_WalkUp2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SkyPillar_Top_Text_DraconidAsterClimax, MSGBOX_DEFAULT
	call Draconid_EventScript_BattleAsterSkyPillar
	msgbox SkyPillar_Top_Text_DraconidAsterYield, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ASTER_STATE, ASTER_STATE_SKY_PILLAR
	setvar VAR_TEMP_2, 1
	return

SkyPillar_Top_EventScript_DraconidAsterClimax_2:
	return


SkyPillar_Top_EventScript_DraconidAsterAfterRayquaza::
	compare VAR_TEMP_2, 1
	goto_if_ne SkyPillar_Top_EventScript_DraconidAsterAfterRayquaza_2
	setvar VAR_TEMP_2, 0
	msgbox SkyPillar_Top_Text_DraconidAsterAfterRayquaza, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SKY_PILLAR_TOP_ASTER
	setflag FLAG_HIDE_SKY_PILLAR_TOP_ASTER
	fadescreen FADE_FROM_BLACK
	return

SkyPillar_Top_EventScript_DraconidAsterAfterRayquaza_2:
	return


DraconidVillage_Shrine_EventScript_DraconidAsterPostgame::
	goto_if_set FLAG_SYS_GAME_CLEAR, DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_3
	return

DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_1:
	clearflag FLAG_HIDE_DRACONID_SHRINE_ASTER
	setobjectxyperm LOCALID_DRACONID_SHRINE_ASTER, 10, 9
	setobjectmovementtype LOCALID_DRACONID_SHRINE_ASTER, MOVEMENT_TYPE_FACE_UP
	return

DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_2:
	compare VAR_ASTER_STATE, ASTER_STATE_POSTGAME
	goto_if_lt DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_1
	return

DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_3:
	compare VAR_ASTER_STATE, ASTER_STATE_SKY_PILLAR
	goto_if_ge DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_2
	return


DraconidVillage_Shrine_EventScript_Aster::
	lock
	faceplayer
	msgbox DraconidVillage_Shrine_Text_DraconidAsterPostgame, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_Shrine_EventScript_Aster_2
	call Draconid_EventScript_BattleAsterPostgame
	msgbox DraconidVillage_Shrine_Text_DraconidAsterPostgameAfter, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_DRACONID_SHRINE_ASTER
	setflag FLAG_HIDE_DRACONID_SHRINE_ASTER
	setvar VAR_ASTER_STATE, ASTER_STATE_POSTGAME
	fadescreen FADE_FROM_BLACK
	release
	return

DraconidVillage_Shrine_EventScript_Aster_2:
	msgbox DraconidVillage_Shrine_Text_DraconidAsterLater, MSGBOX_DEFAULT
	release
	end


Draconid_Text_AsterDefeat::
	.string "…Hmph. The wind was at your back.$"

SkyPillar_Top_Text_DraconidAsterClimax::
	.string "ASTER: So you found it too.\p"
	.string "Every night since I was small I dreamed\n"
	.string "of this tower. Of the one who sleeps on\l"
	.string "top of it.\p"
	.string "The Lorekeepers say RAYQUAZA answers\n"
	.string "the call of one who is worthy. Only one.\p"
	.string "Last riddle, {PLAYER}: two dragons climb\n"
	.string "the same tower, but only one can reach\l"
	.string "the sky. Which one?\p"
	.string "…The one still standing. SALAMENCE,\n"
	.string "show them what a dragon of the sky\l"
	.string "looks like!$"

Draconid_Text_AsterSkyPillarDefeat::
	.string "…So that's the answer.$"

SkyPillar_Top_Text_DraconidAsterYield::
	.string "ASTER: …Go on. Wake it. It was never\n"
	.string "going to listen to me if I couldn't even\l"
	.string "beat you.$"

SkyPillar_Top_Text_DraconidAsterAfterRayquaza::
	.string "ASTER: It looked at you before it flew.\n"
	.string "Did you see?\p"
	.string "Hmph. Don't let it go to your head,\n"
	.string "{PLAYER}. The sky is big. I'll find my own\l"
	.string "way up.$"

DraconidVillage_Shrine_Text_DraconidAsterPostgame::
	.string "ASTER: CHAMPION of HOENN, back where\n"
	.string "it all started.\p"
	.string "No riddles today. Just you, me, and\n"
	.string "everything we've got. Ready?$"

DraconidVillage_Shrine_Text_DraconidAsterLater::
	.string "ASTER: I'll wait. The statue doesn't\n"
	.string "mind.$"

DraconidVillage_Shrine_Text_DraconidAsterPostgameAfter::
	.string "ASTER: …You know what the answer to all\n"
	.string "my riddles was? The sky. It was always\l"
	.string "the sky.\p"
	.string "See you up there someday, {PLAYER}.$"
