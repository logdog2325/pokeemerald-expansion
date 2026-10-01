Draconid_EventScript_FinaleWeather::
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_ALARM
	goto_if_ge Draconid_EventScript_FinaleWeather_8
Draconid_EventScript_FinaleWeather_5:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_ALERT
	goto_if_ge Draconid_EventScript_FinaleWeather_4
	return

Draconid_EventScript_FinaleWeather_1:
	setweather WEATHER_ABNORMAL
	return

Draconid_EventScript_FinaleWeather_2:
	setweather WEATHER_SHADE
	return

Draconid_EventScript_FinaleWeather_3:
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_ALARM
	goto_if_lt Draconid_EventScript_FinaleWeather_2
	return

Draconid_EventScript_FinaleWeather_4:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_lt Draconid_EventScript_FinaleWeather_3
	return

Draconid_EventScript_FinaleWeather_8:
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_PRIMAL_WON
	goto_if_lt Draconid_EventScript_FinaleWeather_1
	goto Draconid_EventScript_FinaleWeather_5


Draconid_EventScript_FinaleHeal::
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	return


SkyPillar_Outside_EventScript_DraconidOnTransition::
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_SUMMONED
	goto_if_eq SkyPillar_Outside_EventScript_DraconidOnTransition_2
	setflag FLAG_TEMP_11
SkyPillar_Outside_EventScript_DraconidOnTransition_1:
	call Draconid_EventScript_FinaleWeather
	return

SkyPillar_Outside_EventScript_DraconidOnTransition_2:
	setflag FLAG_HIDE_SKY_PILLAR_WALLACE
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_NONE
	goto_if_eq SkyPillar_Outside_EventScript_DraconidOnTransition_5
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_REGIDRAGO
	goto_if_ge SkyPillar_Outside_EventScript_DraconidOnTransition_6
	goto SkyPillar_Outside_EventScript_DraconidOnTransition_1

SkyPillar_Outside_EventScript_DraconidOnTransition_5:
	setvar VAR_TEMP_7, 2
	goto SkyPillar_Outside_EventScript_DraconidOnTransition_1

SkyPillar_Outside_EventScript_DraconidOnTransition_6:
	checktrainerflag TRAINER_WALLACE_SKY_PILLAR
	goto_if 0, SkyPillar_Outside_EventScript_DraconidOnTransition_9
	setvar VAR_TEMP_7, 1
	goto SkyPillar_Outside_EventScript_DraconidOnTransition_1

SkyPillar_Outside_EventScript_DraconidOnTransition_9:
	call SkyPillar_Outside_EventScript_DraconidShowWallace
	setvar VAR_TEMP_7, 3
	goto SkyPillar_Outside_EventScript_DraconidOnTransition_1


SkyPillar_Outside_EventScript_DraconidTrialOfThree::
	lockall
	setvar VAR_TEMP_7, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_SKY_PILLAR_OUTSIDE_ASTER, SkyPillar_Outside_Movement_DraconidAsterToPlayer
	applymovement LOCALID_SKY_PILLAR_OUTSIDE_NERINE, SkyPillar_Outside_Movement_DraconidNerineToPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_0
	msgbox SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_1
	msgbox SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_2
	msgbox SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_3
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_4
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_5
	closemessage
	goto SkyPillar_Outside_EventScript_DraconidDoubleBattle
	return


SkyPillar_Outside_Movement_DraconidAsterToPlayer:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_right
	step_end

SkyPillar_Outside_Movement_DraconidNerineToPlayer:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

SkyPillar_Outside_EventScript_DraconidDoubleBattle::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	compare VAR_RESULT, 0
	goto_if_eq SkyPillar_Outside_EventScript_DraconidDoubleBattle_2
	setflag FLAG_DRACONID_NO_WHITEOUT
	multi_2_vs_1 TRAINER_ASTER_SKY_PILLAR_DEINO, SkyPillar_Outside_Text_DraconidAsterDefeat, PARTNER_NERINE_DEINO_CHARMANDER
	clearflag FLAG_DRACONID_NO_WHITEOUT
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne SkyPillar_Outside_EventScript_DraconidDoubleBattle_5
	setvar VAR_ASTER_STATE, ASTER_STATE_SKY_PILLAR
	setvar VAR_NERINE_STATE, NERINE_STATE_SKY_PILLAR
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_3
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_4
	closemessage
	playse SE_M_EARTHQUAKE
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Outside_Movement_DraconidCameraToDoor
	waitmovement 0
	call SkyPillar_Outside_EventScript_OpenDoor
	special DrawWholeMapView
	playse SE_DOOR
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_5
	closemessage
	applymovement LOCALID_CAMERA, SkyPillar_Outside_Movement_DraconidCameraBack
	waitmovement 0
	special RemoveCameraObject
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_6
	call Draconid_EventScript_FinaleHeal
	msgbox Draconid_Text_NerineHeals
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_7
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_CLIMB
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_8
	closemessage
	warpsilent MAP_SKY_PILLAR_3F, 3, 2
	waitstate
	return

SkyPillar_Outside_EventScript_DraconidDoubleBattle_2:
	special LoadPlayerParty
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_0
	releaseall
	end

SkyPillar_Outside_EventScript_DraconidDoubleBattle_5:
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_1
	call Draconid_EventScript_FinaleHeal
	msgbox Draconid_Text_NerineHeals
	msgbox SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_2
	releaseall
	end


SkyPillar_Outside_Movement_DraconidCameraToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

SkyPillar_Outside_Movement_DraconidCameraBack:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SkyPillar_Outside_EventScript_DraconidAster::
	lock
	faceplayer
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_REGIDRAGO
	goto_if_lt SkyPillar_Outside_EventScript_DraconidAster_2
SkyPillar_Outside_EventScript_DraconidAster_1:
	msgbox SkyPillar_Outside_EventScript_DraconidAster_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SkyPillar_Outside_EventScript_DraconidAster_5
	closemessage
	goto SkyPillar_Outside_EventScript_DraconidDoubleBattle
	return

SkyPillar_Outside_EventScript_DraconidAster_2:
	goto SkyPillar_Outside_EventScript_DraconidGoHomeFirst
	goto SkyPillar_Outside_EventScript_DraconidAster_1

SkyPillar_Outside_EventScript_DraconidAster_5:
	msgbox SkyPillar_Outside_EventScript_DraconidAster_Text_1
	release
	end


SkyPillar_Outside_EventScript_DraconidNerine::
	lock
	faceplayer
	compare VAR_DRACONID_VILLAGE_STATE, VILLAGE_STATE_REGIDRAGO
	goto_if_lt SkyPillar_Outside_EventScript_DraconidNerine_2
SkyPillar_Outside_EventScript_DraconidNerine_1:
	msgbox SkyPillar_Outside_EventScript_DraconidNerine_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SkyPillar_Outside_EventScript_DraconidNerine_5
	closemessage
	goto SkyPillar_Outside_EventScript_DraconidDoubleBattle
	return

SkyPillar_Outside_EventScript_DraconidNerine_2:
	goto SkyPillar_Outside_EventScript_DraconidGoHomeFirst
	goto SkyPillar_Outside_EventScript_DraconidNerine_1

SkyPillar_Outside_EventScript_DraconidNerine_5:
	msgbox SkyPillar_Outside_EventScript_DraconidNerine_Text_1
	release
	end


SkyPillar_3F_EventScript_DraconidOnTransition::
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_CLIMB
	goto_if_eq SkyPillar_3F_EventScript_DraconidOnTransition_1
	setflag FLAG_TEMP_11
	return

SkyPillar_3F_EventScript_DraconidOnTransition_1:
	setvar VAR_TEMP_7, 1
	return


SkyPillar_3F_EventScript_DraconidZinniaScene::
	lockall
	setvar VAR_TEMP_7, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 20
	applymovement LOCALID_SKY_PILLAR_3F_ZINNIA, Common_Movement_WalkUp
	waitmovement 0
	msgbox SkyPillar_3F_EventScript_DraconidZinniaScene_Text_0
	msgbox SkyPillar_3F_EventScript_DraconidZinniaScene_Text_1
	applymovement LOCALID_SKY_PILLAR_3F_ASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SkyPillar_3F_EventScript_DraconidZinniaScene_Text_2
	msgbox SkyPillar_3F_EventScript_DraconidZinniaScene_Text_3
	msgbox SkyPillar_3F_EventScript_DraconidZinniaScene_Text_4
	msgbox SkyPillar_3F_EventScript_DraconidZinniaScene_Text_5
	goto SkyPillar_3F_EventScript_DraconidBattleZinnia
	return


SkyPillar_3F_EventScript_DraconidBattleZinnia::
	setflag FLAG_DRACONID_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_ZINNIA_SKY_PILLAR, SkyPillar_3F_Text_DraconidZinniaDefeat
	clearflag FLAG_DRACONID_NO_WHITEOUT
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne SkyPillar_3F_EventScript_DraconidBattleZinnia_2
	msgbox SkyPillar_3F_EventScript_DraconidBattleZinnia_Text_1
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_SUMMIT
	msgbox SkyPillar_3F_EventScript_DraconidBattleZinnia_Text_2
	closemessage
	warpsilent MAP_SKY_PILLAR_TOP, 14, 12
	waitstate
	return

SkyPillar_3F_EventScript_DraconidBattleZinnia_2:
	msgbox SkyPillar_3F_EventScript_DraconidBattleZinnia_Text_0
	call Draconid_EventScript_FinaleHeal
	msgbox Draconid_Text_NerineHeals
	releaseall
	end


SkyPillar_3F_EventScript_DraconidZinnia::
	lock
	faceplayer
	msgbox SkyPillar_3F_EventScript_DraconidZinnia_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SkyPillar_3F_EventScript_DraconidZinnia_2
	closemessage
	goto SkyPillar_3F_EventScript_DraconidBattleZinnia
	return

SkyPillar_3F_EventScript_DraconidZinnia_2:
	msgbox SkyPillar_3F_EventScript_DraconidZinnia_Text_1
	release
	end


SkyPillar_3F_EventScript_DraconidAster::
	msgbox SkyPillar_3F_EventScript_DraconidAster_Text_0, MSGBOX_NPC
	return


SkyPillar_3F_EventScript_DraconidNerine::
	msgbox SkyPillar_3F_EventScript_DraconidNerine_Text_0, MSGBOX_NPC
	return


SkyPillar_Top_EventScript_DraconidOnTransition::
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_SUMMONED
	goto_if_ge SkyPillar_Top_EventScript_DraconidOnTransition_2
SkyPillar_Top_EventScript_DraconidOnTransition_1:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_SUMMONED
	goto_if_ge SkyPillar_Top_EventScript_DraconidOnTransition_6
SkyPillar_Top_EventScript_DraconidOnTransition_4:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_SUMMIT
	goto_if_eq SkyPillar_Top_EventScript_DraconidOnTransition_10
	setflag FLAG_TEMP_11
SkyPillar_Top_EventScript_DraconidOnTransition_9:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_lt SkyPillar_Top_EventScript_DraconidOnTransition_14
	goto_if_set FLAG_BATTLED_DEOXYS, SkyPillar_Top_EventScript_DraconidOnTransition_14
	goto_if_set FLAG_DEFEATED_DEOXYS, SkyPillar_Top_EventScript_DraconidOnTransition_14
SkyPillar_Top_EventScript_DraconidOnTransition_13:
	call Draconid_EventScript_FinaleWeather
	return

SkyPillar_Top_EventScript_DraconidOnTransition_2:
	setvar VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 1
	setflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA
	goto SkyPillar_Top_EventScript_DraconidOnTransition_1

SkyPillar_Top_EventScript_DraconidOnTransition_5:
	setflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL
	goto SkyPillar_Top_EventScript_DraconidOnTransition_4

SkyPillar_Top_EventScript_DraconidOnTransition_6:
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_lt SkyPillar_Top_EventScript_DraconidOnTransition_5
	goto SkyPillar_Top_EventScript_DraconidOnTransition_4

SkyPillar_Top_EventScript_DraconidOnTransition_10:
	setvar VAR_TEMP_7, 1
	clearflag FLAG_HIDE_SKY_PILLAR_TOP_ASTER
	setobjectxyperm LOCALID_SKY_PILLAR_TOP_ASTER, 13, 11
	setobjectmovementtype LOCALID_SKY_PILLAR_TOP_ASTER, MOVEMENT_TYPE_FACE_UP
	goto SkyPillar_Top_EventScript_DraconidOnTransition_9

SkyPillar_Top_EventScript_DraconidOnTransition_14:
	setflag FLAG_TEMP_12
	goto SkyPillar_Top_EventScript_DraconidOnTransition_13


SkyPillar_Top_EventScript_DraconidSummit::
	lockall
	setvar VAR_TEMP_7, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 30
	applymovement LOCALID_SKY_PILLAR_TOP_ELDER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_0
	applymovement LOCALID_SKY_PILLAR_TOP_ELDER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_1
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_2
	applymovement LOCALID_SKY_PILLAR_TOP_ELDER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_3
	call Draconid_EventScript_FinaleHeal
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_4
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_5
	closemessage
	applymovement LOCALID_SKY_PILLAR_TOP_ELDER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	call Draconid_EventScript_FinaleQuake
	playse SE_M_EXPLOSION
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_6
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_7
	closemessage
	playse SE_M_DRAGON_RAGE
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 30
	setobjectxyperm LOCALID_RAYQUAZA_SLEEPING, 14, 1
	addobject LOCALID_RAYQUAZA_SLEEPING
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_DraconidRayquazaDescends
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	call Draconid_EventScript_FinaleQuake
	waitmoncry
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_8
	applymovement LOCALID_SKY_PILLAR_TOP_ELDER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_9
	closemessage
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	call SkyPillar_Top_EventScript_DraconidCatchRayquaza
	call SkyPillar_Top_EventScript_DraconidDragonAscent
	call SkyPillar_Top_EventScript_DraconidDeoxysAttacks
	goto SkyPillar_Top_EventScript_DraconidMeteor
	return


SkyPillar_Top_Movement_DraconidRayquazaDescends:
	walk_in_place_faster_up
	lock_facing_direction
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	unlock_facing_direction
	delay_16
	walk_in_place_right
	delay_16
	step_end

SkyPillar_Top_Movement_DraconidRayquazaLeaves:
	walk_in_place_right
	delay_8
	walk_faster_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

SkyPillar_Top_EventScript_DraconidCatchRayquaza::
	call SkyPillar_Top_EventScript_DraconidGiveBalls
	closemessage
	setflag FLAG_DRACONID_NO_WHITEOUT
	setflag FLAG_DRACONID_NO_RUNNING
SkyPillar_Top_EventScript_DraconidCatchRayquaza_3:
	setwildbattle SPECIES_RAYQUAZA, DRACONID_RAYQUAZA_LEVEL
	special BattleSetup_StartLegendaryBattle
	specialvar VAR_TEMP_8, GetBattleOutcome
	compare VAR_TEMP_8, B_OUTCOME_WON
	goto_if_eq SkyPillar_Top_EventScript_DraconidCatchRayquaza_5
	compare VAR_TEMP_8, B_OUTCOME_CAUGHT
	goto_if_ne SkyPillar_Top_EventScript_DraconidCatchRayquaza_6
SkyPillar_Top_EventScript_DraconidCatchRayquaza_2:
	compare VAR_TEMP_8, B_OUTCOME_CAUGHT
	goto_if_ne SkyPillar_Top_EventScript_DraconidCatchRayquaza_3
	clearflag FLAG_DRACONID_NO_RUNNING
	clearflag FLAG_DRACONID_NO_WHITEOUT
	removeobject LOCALID_RAYQUAZA_SLEEPING
	setflag FLAG_DEFEATED_RAYQUAZA
	return

SkyPillar_Top_EventScript_DraconidCatchRayquaza_5:
	msgbox SkyPillar_Top_EventScript_DraconidCatchRayquaza_Text_0
	call Draconid_EventScript_FinaleHeal
	call SkyPillar_Top_EventScript_DraconidGiveBalls
	closemessage
	goto SkyPillar_Top_EventScript_DraconidCatchRayquaza_2

SkyPillar_Top_EventScript_DraconidCatchRayquaza_6:
	msgbox SkyPillar_Top_EventScript_DraconidCatchRayquaza_Text_1
	call Draconid_EventScript_FinaleHeal
	call SkyPillar_Top_EventScript_DraconidGiveBalls
	closemessage
	goto SkyPillar_Top_EventScript_DraconidCatchRayquaza_2


SkyPillar_Top_EventScript_DraconidGiveBalls::
	checkitem ITEM_ULTRA_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq SkyPillar_Top_EventScript_DraconidGiveBalls_1
	return

SkyPillar_Top_EventScript_DraconidGiveBalls_1:
	msgbox SkyPillar_Top_EventScript_DraconidGiveBalls_Text_0
	giveitem ITEM_ULTRA_BALL, 5
	return


SkyPillar_Top_EventScript_DraconidDragonAscent::
	msgbox SkyPillar_Top_EventScript_DraconidDragonAscent_Text_0
	callnative Draconid_PrepareRayquaza
	compare VAR_RESULT, FALSE
	goto_if_eq SkyPillar_Top_EventScript_DraconidDragonAscent_2
	bufferpartymonnick STR_VAR_1, 0
	msgbox SkyPillar_Top_EventScript_DraconidDragonAscent_Text_1
	closemessage
	playse SE_M_DRAGON_RAGE
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	compare VAR_0x8005, MOVE_NONE
	goto_if_ne SkyPillar_Top_EventScript_DraconidDragonAscent_5
SkyPillar_Top_EventScript_DraconidDragonAscent_4:
	playfanfare MUS_LEVEL_UP
	message SkyPillar_Top_EventScript_DraconidDragonAscent_Text_3
	waitmessage
	waitfanfare
	msgbox SkyPillar_Top_EventScript_DraconidDragonAscent_Text_4
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_RAYQUAZA
	return

SkyPillar_Top_EventScript_DraconidDragonAscent_2:
	return

SkyPillar_Top_EventScript_DraconidDragonAscent_5:
	buffermovename STR_VAR_2, VAR_0x8005
	msgbox SkyPillar_Top_EventScript_DraconidDragonAscent_Text_2
	goto SkyPillar_Top_EventScript_DraconidDragonAscent_4


SkyPillar_Top_EventScript_DraconidDeoxysAttacks::
	closemessage
	playse SE_M_TELEPORT
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	call Draconid_EventScript_FinaleQuake
	msgbox SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_0
	closemessage
	playbgm MUS_RG_ENCOUNTER_DEOXYS, FALSE
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	setobjectxyperm LOCALID_SKY_PILLAR_TOP_DEOXYS, 14, 1
	addobject LOCALID_SKY_PILLAR_TOP_DEOXYS
	applymovement LOCALID_SKY_PILLAR_TOP_DEOXYS, SkyPillar_Top_Movement_DraconidDeoxysDescends
	waitmovement 0
	playse SE_M_EXPLOSION
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	waitse
	playmoncry SPECIES_DEOXYS_NORMAL, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_1
	msgbox SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_2
	msgbox SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_3
	closemessage
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setflag FLAG_DRACONID_NO_WHITEOUT
	setflag FLAG_DRACONID_NO_RUNNING
	setflag FLAG_DRACONID_NO_CATCHING
SkyPillar_Top_EventScript_DraconidDeoxysAttacks_3:
	setwildbattle SPECIES_DEOXYS_NORMAL, DRACONID_DEOXYS_BOSS_LEVEL
	special BattleSetup_StartLegendaryBattle
	specialvar VAR_TEMP_8, GetBattleOutcome
	compare VAR_TEMP_8, B_OUTCOME_WON
	goto_if_ne SkyPillar_Top_EventScript_DraconidDeoxysAttacks_5
SkyPillar_Top_EventScript_DraconidDeoxysAttacks_2:
	compare VAR_TEMP_8, B_OUTCOME_WON
	goto_if_ne SkyPillar_Top_EventScript_DraconidDeoxysAttacks_3
	clearflag FLAG_DRACONID_NO_CATCHING
	clearflag FLAG_DRACONID_NO_RUNNING
	clearflag FLAG_DRACONID_NO_WHITEOUT
	return

SkyPillar_Top_EventScript_DraconidDeoxysAttacks_5:
	msgbox SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_4
	call Draconid_EventScript_FinaleHeal
	msgbox SkyPillar_Top_EventScript_DraconidSummit_Text_4
	closemessage
	goto SkyPillar_Top_EventScript_DraconidDeoxysAttacks_2


SkyPillar_Top_Movement_DraconidCameraBackDown:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

SkyPillar_Top_Movement_DraconidDeoxysDescends:
	face_down
	lock_facing_direction
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	unlock_facing_direction
	step_end

SkyPillar_Top_EventScript_DraconidMeteor::
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	playse SE_M_TELEPORT
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_SKY_PILLAR_TOP_DEOXYS
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_0
	closemessage
	call Draconid_EventScript_FinaleQuake
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_1
	closemessage
	bufferpartymonnick STR_VAR_1, 0
	setobjectxyperm LOCALID_RAYQUAZA_SLEEPING, 14, 7
	playse SE_BALL_OPEN
	addobject LOCALID_RAYQUAZA_SLEEPING
	applymovement LOCALID_RAYQUAZA_SLEEPING, Common_Movement_WalkInPlaceRight
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_2
	closemessage
	playse SE_M_SKY_UPPERCUT
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_M_SKY_UPPERCUT
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	waitse
	playmoncry SPECIES_RAYQUAZA_MEGA, CRY_MODE_ENCOUNTER
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_3
	waitmoncry
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_4
	closemessage
	playse SE_M_FLY
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_DraconidRayquazaLeaves
	waitmovement 0
	removeobject LOCALID_RAYQUAZA_SLEEPING
	fadescreen FADE_TO_BLACK
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_DraconidCameraBackDown
	waitmovement 0
	special RemoveCameraObject
	callnative Draconid_DoRayquazaFlightScene
	waitstate
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_5
	closemessage
	playse SE_M_HYPER_BEAM
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 20
	playse SE_THUNDER
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 20
	playse SE_M_EXPLOSION
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	call Draconid_EventScript_FinaleQuake
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_6
	closemessage
	setweather WEATHER_NONE
	doweather
	special WaitWeather
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_7
	closemessage
	setobjectxyperm LOCALID_RAYQUAZA_SLEEPING, 14, 1
	addobject LOCALID_RAYQUAZA_SLEEPING
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_DraconidRayquazaDescends
	waitmovement 0
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_8
	closemessage
	playse SE_BALL
	removeobject LOCALID_RAYQUAZA_SLEEPING
	delay 30
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_9
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_10
	applymovement LOCALID_SKY_PILLAR_TOP_ASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_11
	applymovement LOCALID_SKY_PILLAR_TOP_NERINE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_12
	msgbox SkyPillar_Top_EventScript_DraconidMeteor_Text_13
	closemessage
	goto SkyPillar_Top_EventScript_DraconidAlarm
	return


DraconidVillage_PlayersHouse_2F_EventScript_DraconidWakeUpAfterFinale::
	lockall
	delay 30
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_DraconidWakeUpAfterFinale_Text_0
	closemessage
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_HOME
	releaseall
	return


SkyPillar_Top_EventScript_DraconidDeoxys::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DEOXYS_NORMAL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DEOXYS_NORMAL, DRACONID_DEOXYS_LEVEL
	special BattleSetup_StartLegendaryBattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq SkyPillar_Top_EventScript_DraconidDeoxys_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq SkyPillar_Top_EventScript_DraconidDeoxys_5
SkyPillar_Top_EventScript_DraconidDeoxys_4:
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SKY_PILLAR_TOP_DEOXYS
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_0x8004, SPECIES_DEOXYS_NORMAL
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway
	release
	return

SkyPillar_Top_EventScript_DraconidDeoxys_2:
	setflag FLAG_BATTLED_DEOXYS
	removeobject LOCALID_SKY_PILLAR_TOP_DEOXYS
	release
	end

SkyPillar_Top_EventScript_DraconidDeoxys_5:
	setflag FLAG_DEFEATED_DEOXYS
	goto SkyPillar_Top_EventScript_DraconidDeoxys_4


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameLayout::
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameLayout_1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameLayout_1:
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BRENDAN
	setobjectxyperm LOCALID_BIRCHS_LAB_BRENDAN, 8, 10
	setobjectmovementtype LOCALID_BIRCHS_LAB_BRENDAN, MOVEMENT_TYPE_FACE_DOWN
	return


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay::
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_lt LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_2
	checktrainerflag TRAINER_MAY_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_5
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_2:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_0
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_5:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_8
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime
LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_7:
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_8:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_2
	trainerbattle_no_intro TRAINER_MAY_POSTGAME, LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameDefeat
	setvar VAR_MAY_STATE, MAY_STATE_POSTGAME
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_3
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_7


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan::
	checktrainerflag TRAINER_BRENDAN_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_2
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_2:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_5
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime
LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_4:
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_5:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_Text_1
	trainerbattle_no_intro TRAINER_BRENDAN_POSTGAME, LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameDefeat
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_POSTGAME
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_Text_2
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_4


LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble::
	checktrainerflag TRAINER_MAY_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_2
	checktrainerflag TRAINER_BRENDAN_POSTGAME
	goto_if 0, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_2
	checktrainerflag TRAINER_BRENDAN_POSTGAME_DOUBLE
	goto_if 1, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_7
	checktrainerflag TRAINER_BRENDAN_LILYCOVE
	goto_if 1, LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_10
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_2, MSGBOX_YESNO
LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_9:
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_14
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_17
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_4
	trainerbattle_two_trainers_no_intro TRAINER_BRENDAN_POSTGAME_DOUBLE, LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameDefeat, TRAINER_MAY_POSTGAME_DOUBLE, LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameDefeat
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidPostgameDone
	release
	return

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_2:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_0
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_7:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidPostgameDone
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_10:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_1, MSGBOX_YESNO
	goto LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_9

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_14:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_17:
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_3
	release
	end


DraconidVillage_Shrine_EventScript_DraconidAsterPostgame::
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_DESTROYED
	goto_if_ge DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_2
	return

DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_1:
	clearflag FLAG_HIDE_DRACONID_SHRINE_ASTER
	setobjectxyperm LOCALID_DRACONID_SHRINE_ASTER, 10, 11
	setobjectmovementtype LOCALID_DRACONID_SHRINE_ASTER, MOVEMENT_TYPE_FACE_UP
	return

DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_2:
	compare VAR_ASTER_STATE, ASTER_STATE_SKY_PILLAR
	goto_if_eq DraconidVillage_Shrine_EventScript_DraconidAsterPostgame_1
	return


DraconidVillage_Shrine_EventScript_Aster::
	lock
	faceplayer
	msgbox DraconidVillage_Shrine_EventScript_Aster_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_Shrine_EventScript_Aster_2
	trainerbattle_no_intro TRAINER_ASTER_POSTGAME_DEINO, DraconidVillage_Shrine_Text_DraconidAsterPostgameDefeat
	msgbox DraconidVillage_Shrine_EventScript_Aster_Text_2
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_DRACONID_SHRINE_ASTER
	setflag FLAG_HIDE_DRACONID_SHRINE_ASTER
	setvar VAR_ASTER_STATE, ASTER_STATE_POSTGAME
	fadescreen FADE_FROM_BLACK
	release
	return

DraconidVillage_Shrine_EventScript_Aster_2:
	msgbox DraconidVillage_Shrine_EventScript_Aster_Text_1
	release
	end


DraconidVillage_EventScript_DraconidNerine::
	lock
	faceplayer
	compare VAR_NERINE_STATE, NERINE_STATE_POSTGAME
	goto_if_eq DraconidVillage_EventScript_DraconidNerine_2
	msgbox DraconidVillage_EventScript_DraconidNerine_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_EventScript_DraconidNerine_5
	msgbox DraconidVillage_EventScript_DraconidNerine_Text_3
	trainerbattle_no_intro TRAINER_NERINE_POSTGAME_DEINO_CHARMANDER, DraconidVillage_Text_DraconidNerinePostgameDefeat
	setvar VAR_NERINE_STATE, NERINE_STATE_POSTGAME
	msgbox DraconidVillage_EventScript_DraconidNerine_Text_4
	release
	return

DraconidVillage_EventScript_DraconidNerine_2:
	msgbox DraconidVillage_EventScript_DraconidNerine_Text_0
	release
	end

DraconidVillage_EventScript_DraconidNerine_5:
	msgbox DraconidVillage_EventScript_DraconidNerine_Text_2
	release
	end


SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_0:
	.string "ASTER: There you are, CHAMPION. You\n"
	.string "took your time.$"

SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_1:
	.string "NERINE: Don't listen to her. She's been\n"
	.string "pacing since dusk.\p"
	.string "The sky went dark hours ago. Even the\n"
	.string "sea went quiet.$"

SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_2:
	.string "ASTER: Riddle: what falls for a\n"
	.string "thousand years and lands in a single\l"
	.string "night?\p"
	.string "…Don't answer. We'll all find out soon\n"
	.string "enough.$"

SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_3:
	.string "ASTER: The door won't open for us yet.\n"
	.string "Not before the last rite: the TRIAL OF\l"
	.string "THREE.\p"
	.string "Two stand together, one stands alone.\n"
	.string "The sky watches how we fight.\p"
	.string "I'll stand alone. I always have.$"

SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_4:
	.string "NERINE: Then I'll stand with {PLAYER}.\p"
	.string "I've stood alone long enough, dressed\n"
	.string "in blue.$"

SkyPillar_Outside_EventScript_DraconidTrialOfThree_Text_5:
	.string "ASTER: Hmph. Pick your three, {PLAYER}.\n"
	.string "Don't hold back. I won't.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_0:
	.string "ASTER: Not ready? Hmph. We'll be right\n"
	.string "here.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_1:
	.string "ASTER: …Hmph. The sky doesn't wait for\n"
	.string "tamers who fall. NERINE, patch them up.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_2:
	.string "ASTER: Talk to me when you want to try\n"
	.string "again.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_3:
	.string "ASTER: …Two dragons climbed the same\n"
	.string "tower. Remember that riddle?\p"
	.string "I said only one could reach the sky. The\n"
	.string "one still standing.\p"
	.string "I was wrong. This time we all reach the\n"
	.string "top.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_4:
	.string "NERINE: Listen. The pillar heard us.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_5:
	.string "The great door of the SKY PILLAR\n"
	.string "rumbled open!$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_6:
	.string "NERINE: Wait. Let me see to your\n"
	.string "partners first. It's a long way up.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_7:
	.string "ASTER: Then let's climb. Together.$"

SkyPillar_Outside_EventScript_DraconidDoubleBattle_Text_8:
	.string "{PLAYER}, ASTER and NERINE climbed the\n"
	.string "SKY PILLAR together…$"

SkyPillar_Outside_EventScript_DraconidAster_Text_0:
	.string "ASTER: Ready for the TRIAL OF THREE?$"

SkyPillar_Outside_EventScript_DraconidAster_Text_1:
	.string "ASTER: Take your time. Just not too\n"
	.string "much of it. Look at the sky.$"

SkyPillar_Outside_EventScript_DraconidNerine_Text_0:
	.string "NERINE: I'm with you, {PLAYER}. Shall we\n"
	.string "try again?$"

SkyPillar_Outside_EventScript_DraconidNerine_Text_1:
	.string "NERINE: When you're ready. The sky is\n"
	.string "patient. Barely.$"

SkyPillar_3F_EventScript_DraconidZinniaScene_Text_0:
	.string "???: Heh. So the ELDER's chosen one\n"
	.string "finally shows up.$"

SkyPillar_3F_EventScript_DraconidZinniaScene_Text_1:
	.string "ZINNIA: The name's ZINNIA.\p"
	.string "I'm the LOREKEEPER of the DRACONIDS of\n"
	.string "METEOR FALLS.$"

SkyPillar_3F_EventScript_DraconidZinniaScene_Text_2:
	.string "ASTER: The sister clan… The\n"
	.string "LOREKEEPER? I thought she was a story\l"
	.string "the ELDER told us to keep us quiet!$"

SkyPillar_3F_EventScript_DraconidZinniaScene_Text_3:
	.string "NERINE: The ones who keep the old\n"
	.string "songs. When the sky went red, you came.\p"
	.string "The ELDER said you would.$"

SkyPillar_3F_EventScript_DraconidZinniaScene_Text_4:
	.string "ZINNIA: Your ELDER and I read the same\n"
	.string "stars. When they went dark tonight, I\l"
	.string "came running.\p"
	.string "RAYQUAZA doesn't answer to just\n"
	.string "anyone, you know.\p"
	.string "The one who stands beside it has to be\n"
	.string "ready for anything. Even the end of the\l"
	.string "world.$"

SkyPillar_3F_EventScript_DraconidZinniaScene_Text_5:
	.string "ZINNIA: So before you go up there,\n"
	.string "{PLAYER}, show me.\p"
	.string "Show me you're worth the whole sky!$"

SkyPillar_3F_EventScript_DraconidBattleZinnia_Text_0:
	.string "ZINNIA: Not yet, huh? Rest up. I'm not\n"
	.string "going anywhere.$"

SkyPillar_3F_EventScript_DraconidBattleZinnia_Text_1:
	.string "ZINNIA: Hah! That's the stuff! Now I\n"
	.string "see why the old man picked you.\p"
	.string "Go on up. The summit's waiting, and so is\n"
	.string "your ELDER.\p"
	.string "I'll be right behind you. I wouldn't miss\n"
	.string "this for anything.$"

SkyPillar_3F_EventScript_DraconidBattleZinnia_Text_2:
	.string "…At last, they reached the top of the\n"
	.string "SKY PILLAR.$"

SkyPillar_3F_EventScript_DraconidZinnia_Text_0:
	.string "ZINNIA: Ready for round two, chosen\n"
	.string "one?$"

SkyPillar_3F_EventScript_DraconidZinnia_Text_1:
	.string "ZINNIA: Take a breath. The stars can\n"
	.string "wait a little longer.$"

SkyPillar_3F_EventScript_DraconidAster_Text_0:
	.string "ASTER: A LOREKEEPER, testing us. The\n"
	.string "ELDER never tells us anything.\p"
	.string "Beat her, {PLAYER}. I'm not climbing all\n"
	.string "the way back down.$"

SkyPillar_3F_EventScript_DraconidNerine_Text_0:
	.string "NERINE: Her dragons are old and wise,\n"
	.string "like her songs.\p"
	.string "Listen to them, and you'll win.$"

SkyPillar_Top_EventScript_DraconidSummit_Text_0:
	.string "ELDER: {PLAYER}. ASTER. NERINE. You\n"
	.string "came together. Good.$"

SkyPillar_Top_EventScript_DraconidSummit_Text_1:
	.string "ELDER: And the LOREKEEPER of the\n"
	.string "FALLS. It has been many years, ZINNIA.$"

SkyPillar_Top_EventScript_DraconidSummit_Text_2:
	.string "ZINNIA: Too many, old man! Your kids are\n"
	.string "all right, you know.\p"
	.string "This one especially.$"

SkyPillar_Top_EventScript_DraconidSummit_Text_3:
	.string "ELDER: Rest a moment, {PLAYER}. Let the\n"
	.string "clan tend to your partners.$"

SkyPillar_Top_EventScript_DraconidSummit_Text_4:
	.string "{PLAYER}'s POKéMON were restored to\n"
	.string "full health!$"

SkyPillar_Top_EventScript_DraconidSummit_Text_5:
	.string "ELDER: Now. Look up, all of you.$"

SkyPillar_Top_EventScript_DraconidSummit_Text_6:
	.string "Above the clouds, a second sun was\n"
	.string "burning.\p"
	.string "The meteor. So close now, it filled half\n"
	.string "the sky.$"

SkyPillar_Top_EventScript_DraconidSummit_Text_7:
	.string "ELDER: Call it, as our clan has always\n"
	.string "called it.\p"
	.string "Guardian of the Sky, who stilled the\n"
	.string "land and the sea…\p"
	.string "The sky's debt has come due. Come down\n"
	.string "to us!$"

SkyPillar_Top_EventScript_DraconidSummit_Text_8:
	.string "RAYQUAZA came down from the sky!$"

SkyPillar_Top_EventScript_DraconidSummit_Text_9:
	.string "ELDER: It has come to see who stands\n"
	.string "beside it.\p"
	.string "Show it, {PLAYER}. Show it who you are!$"

SkyPillar_Top_EventScript_DraconidCatchRayquaza_Text_0:
	.string "RAYQUAZA fell… but it rose again, higher\n"
	.string "than before!\p"
	.string "ELDER: It is not defeat it wants from\n"
	.string "you, {PLAYER}. It is trust.\p"
	.string "Again!$"

SkyPillar_Top_EventScript_DraconidCatchRayquaza_Text_1:
	.string "ELDER: Rise, {PLAYER}. The sky is not\n"
	.string "lost while you still stand.\p"
	.string "Again!$"

SkyPillar_Top_EventScript_DraconidGiveBalls_Text_0:
	.string "ELDER: Take these. A POKé BALL is a\n"
	.string "promise, not a cage.$"

SkyPillar_Top_EventScript_DraconidDragonAscent_Text_0:
	.string "ELDER: RAYQUAZA has chosen you,\n"
	.string "{PLAYER}. As the stars said it would.$"

SkyPillar_Top_EventScript_DraconidDragonAscent_Text_1:
	.string "ELDER: Now let it remember the oldest\n"
	.string "song of our clan.\p"
	.string "The song of the dragon that rises to\n"
	.string "meet the falling star.$"

SkyPillar_Top_EventScript_DraconidDragonAscent_Text_2:
	.string "{STR_VAR_1} forgot {STR_VAR_2}…$"

SkyPillar_Top_EventScript_DraconidDragonAscent_Text_3:
	.string "{STR_VAR_1} learned DRAGON ASCENT!$"

SkyPillar_Top_EventScript_DraconidDragonAscent_Text_4:
	.string "ELDER: With DRAGON ASCENT and your\n"
	.string "MEGA RING, RAYQUAZA can take its true\l"
	.string "form.$"

SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_0:
	.string "ASTER: Wait… something's coming down!\n"
	.string "Fast!$"

SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_1:
	.string "ELDER: DEOXYS… It rode the stone down\n"
	.string "from the dark between the stars.$"

SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_2:
	.string "NERINE: It wants RAYQUAZA! It came for\n"
	.string "the guardian of the sky!$"

SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_3:
	.string "ZINNIA: Then don't let it have it!\n"
	.string "{PLAYER}, RAYQUAZA leads! Go!$"

SkyPillar_Top_EventScript_DraconidDeoxysAttacks_Text_4:
	.string "ELDER: Rise, {PLAYER}! The stone still\n"
	.string "falls. We cannot fall with it!$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_0:
	.string "DEOXYS came apart into shards of light…\n"
	.string "and was gone.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_1:
	.string "ELDER: The stone still falls! {PLAYER},\n"
	.string "now! Call on RAYQUAZA!$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_2:
	.string "{PLAYER}'s MEGA RING began to shine, and\n"
	.string "{STR_VAR_1} answered!$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_3:
	.string "{STR_VAR_1} MEGA EVOLVED into MEGA\n"
	.string "RAYQUAZA!$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_4:
	.string "ELDER: Go, guardian of the sky. DRAGON\n"
	.string "ASCENT!$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_5:
	.string "Beyond the clouds, beyond the sky\n"
	.string "itself, MEGA RAYQUAZA met the falling\l"
	.string "star.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_6:
	.string "A light brighter than the sun… and the\n"
	.string "meteor broke apart!$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_7:
	.string "Its pieces burned across the sky: a\n"
	.string "rain of falling stars from one end of\l"
	.string "HOENN to the other.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_8:
	.string "{STR_VAR_1} came back down from the\n"
	.string "edge of the sky.\p"
	.string "It looked at {PLAYER} for a long moment…\n"
	.string "and returned to its POKé BALL.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_9:
	.string "ELDER: It is done.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_10:
	.string "ELDER: The sky's debt is paid… for now.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_11:
	.string "ASTER: Riddle: what's red, falls from\n"
	.string "the sky, and ends up in a thousand\l"
	.string "pieces?\p"
	.string "…Ha. Don't answer that one either.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_12:
	.string "NERINE: The sky is blue again.\p"
	.string "I never did like red, you know. Even on\n"
	.string "you.$"

SkyPillar_Top_EventScript_DraconidMeteor_Text_13:
	.string "ZINNIA: Heh. The stars got it right for\n"
	.string "once. See you around, CHAMPION.$"

DraconidVillage_PlayersHouse_2F_EventScript_DraconidWakeUpAfterFinale_Text_0:
	.string "{PLAYER} slept through a whole day and a\n"
	.string "night.\p"
	.string "Downstairs, someone was humming an old\n"
	.string "DRACONID song…$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_0:
	.string "MAY: Have you seen the sky?\n"
	.string "Something's burning up there!\p"
	.string "If it has anything to do with dragons,\n"
	.string "{PLAYER}, it has to do with you. Go!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_1:
	.string "MAY: {PLAYER}! The CHAMPION who saved\n"
	.string "the sky, right here in the lab!\p"
	.string "I KNEW it way back on ROUTE 110, and I'm\n"
	.string "never going to stop saying so!\p"
	.string "Now, you promised me one more battle.\n"
	.string "Everything we've got, okay?$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_2:
	.string "MAY: BLAZIKEN, let's show {PLAYER} what\n"
	.string "we learned!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_Text_3:
	.string "MAY: I'm writing all of this down, you\n"
	.string "know.\p"
	.string "Someday people will want to hear the\n"
	.string "true story.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_Text_0:
	.string "BRENDAN: {PLAYER}! You came! After your\n"
	.string "village… Man, we never did get that real\l"
	.string "battle.\p"
	.string "Just you and me this time. Ready,\n"
	.string "CHAMPION?$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_Text_1:
	.string "BRENDAN: SCEPTILE, MEGA EVOLVE! No\n"
	.string "holding back this time!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_Text_2:
	.string "BRENDAN: Next time, I'm winning. Count\n"
	.string "on it.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_0:
	.string "Did you battle both of us yet? Then we\n"
	.string "can team up for a real two-on-two!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_1:
	.string "BRENDAN: You beat us both, one at a\n"
	.string "time…\p"
	.string "MAY: So how about both of us at once?\n"
	.string "Like in LILYCOVE…\p"
	.string "…except this time, we know who we're\n"
	.string "battling!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_2:
	.string "BRENDAN: One at a time wasn't\n"
	.string "enough, huh?\p"
	.string "MAY: Then how about both of us\n"
	.string "at once?\p"
	.string "Two on one, and this time we know who\n"
	.string "we're battling!$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_3:
	.string "MAY: Oh! You need at least two POKéMON\n"
	.string "that can battle for this one.$"

LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameDouble_Text_4:
	.string "BRENDAN: MAY, let's go!\p"
	.string "MAY: Right behind you!$"

DraconidVillage_Shrine_EventScript_Aster_Text_0:
	.string "ASTER: The CHAMPION of HOENN, back\n"
	.string "where it all started.\p"
	.string "The shrine held. …So did you.\p"
	.string "No riddles today. Just you, me, and\n"
	.string "everything we've got. Ready?$"

DraconidVillage_Shrine_EventScript_Aster_Text_1:
	.string "ASTER: I'll wait. The statue doesn't\n"
	.string "mind.$"

DraconidVillage_Shrine_EventScript_Aster_Text_2:
	.string "ASTER: …You know what the answer to all\n"
	.string "my riddles was? The sky. It was always\l"
	.string "the sky.\p"
	.string "The ELDER chose right, {PLAYER}. Don't\n"
	.string "you dare tell him I said so.$"

DraconidVillage_EventScript_DraconidNerine_Text_0:
	.string "NERINE: The pond's still muddy from\n"
	.string "KYOGRE. It'll clear. Most things do.\p"
	.string "When the sky calls again, we'll answer it\n"
	.string "together.$"

DraconidVillage_EventScript_DraconidNerine_Text_1:
	.string "NERINE: After years of salt water, even\n"
	.string "this muddy little pond feels like a\l"
	.string "dream.\p"
	.string "I spent all that time in blue,\n"
	.string "pretending. And I watched you in red,\l"
	.string "pretending.\p"
	.string "No more pretending, {PLAYER}. One\n"
	.string "battle, as ourselves. Will you?$"

DraconidVillage_EventScript_DraconidNerine_Text_2:
	.string "NERINE: I'll be here. The water isn't\n"
	.string "going anywhere, and neither am I.$"

DraconidVillage_EventScript_DraconidNerine_Text_3:
	.string "NERINE: Then let the sky watch.$"

DraconidVillage_EventScript_DraconidNerine_Text_4:
	.string "NERINE: …Yes. That's the tamer the\n"
	.string "ELDER saw, all those years ago.\p"
	.string "I think I'll stay a while. It's good to be\n"
	.string "home.$"

Draconid_Text_NerineHeals::
	.string "NERINE tended to {PLAYER}'s POKéMON.\n"
	.string "They're ready to battle again!$"

SkyPillar_Outside_Text_DraconidAsterDefeat::
	.string "…So that's the answer.$"

SkyPillar_3F_Text_DraconidZinniaDefeat::
	.string "Now THAT is a dragon tamer!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidMayPostgameDefeat::
	.string "MAY: That's our CHAMPION!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidBrendanPostgameDefeat::
	.string "BRENDAN: Unbelievable… Still, that felt\n"
	.string "good.$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidRivalAnytime::
	.string "Any time you're ready!$"

LittlerootTown_ProfessorBirchsLab_Text_DraconidPostgameDone::
	.string "MAY: Dad says the BATTLE FRONTIER is\n"
	.string "full of strong TRAINERS.\p"
	.string "BRENDAN: Let's all go some time! All\n"
	.string "three of us!$"

DraconidVillage_Shrine_Text_DraconidAsterPostgameDefeat::
	.string "…Hmph. The wind was at your back again.$"

DraconidVillage_Text_DraconidNerinePostgameDefeat::
	.string "NERINE: The sky chose well.$"
