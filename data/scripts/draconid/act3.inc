MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	delay 30
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_WithThisMeteorite
	closemessage
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_Delay48
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_0
	closemessage
	applymovement LOCALID_METEOR_FALLS_MAXIE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_MAXIE, MeteorFalls_1F_1R_Movement_DraconidMaxieApproach
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_1
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_2
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_3
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_4
	closemessage
	delay 20
	msgbox MeteorFalls_1F_1R_Text_HoldItRightThereMagma
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_METEOR_FALLS_MAXIE, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	addobject LOCALID_METEOR_FALLS_ARCHIE
	addobject LOCALID_METEOR_FALLS_AQUA_GRUNT_1
	addobject LOCALID_METEOR_FALLS_AQUA_GRUNT_2
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_METEOR_FALLS_ARCHIE, MeteorFalls_1F_1R_Movement_DraconidArchieArrive
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_DraconidAquaGrunt1Arrive
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_DraconidAquaGrunt2Arrive
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_5
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_6
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_7
	closemessage
	applymovement LOCALID_METEOR_FALLS_MAXIE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_8
	closemessage
	applymovement LOCALID_PLAYER, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_MAXIE, MeteorFalls_1F_1R_Movement_DraconidMaxieExit
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_DraconidMagmaGrunt2Exit
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_DraconidMagmaGrunt1Exit
	waitmovement 0
	removeobject LOCALID_METEOR_FALLS_MAXIE
	removeobject LOCALID_METEOR_FALLS_MAGMA_GRUNT_1
	removeobject LOCALID_METEOR_FALLS_MAGMA_GRUNT_2
	applymovement LOCALID_PLAYER, MeteorFalls_1F_1R_Movement_DraconidPlayerBlockStairs
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_ARCHIE, MeteorFalls_1F_1R_Movement_DraconidArchieToStairs
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_DraconidAquaGrunt1ToStairs
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_DraconidAquaGrunt2ToStairs
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_9
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_10
	closemessage
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_11
	closemessage
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_12
	closemessage
	applymovement LOCALID_METEOR_FALLS_ARCHIE, MeteorFalls_1F_1R_Movement_DraconidArchieExit
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_DraconidAquaGruntExit
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_DraconidAquaGruntExit
	waitmovement 0
	removeobject LOCALID_METEOR_FALLS_ARCHIE
	removeobject LOCALID_METEOR_FALLS_AQUA_GRUNT_1
	removeobject LOCALID_METEOR_FALLS_AQUA_GRUNT_2
	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	setvar VAR_MAGMA_STATE, MAGMA_STATE_METEOR_FALLS
	fadedefaultbgm
	delay 60
	call MeteorFalls_1F_1R_EventScript_DraconidAster
	setvar VAR_METEOR_FALLS_STATE, 1
	releaseall
	return


MeteorFalls_1F_1R_EventScript_DraconidAster::
	clearflag FLAG_HIDE_METEOR_FALLS_ASTER
	addobject LOCALID_METEOR_FALLS_ASTER
	playbgm MUS_ENCOUNTER_INTENSE, FALSE
	applymovement LOCALID_METEOR_FALLS_ASTER, MeteorFalls_1F_1R_Movement_DraconidAsterApproach
	waitmovement 0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_0
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_1
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_2
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_3
	closemessage
	trainerbattle_earlyrival TRAINER_ASTER_METEOR_FALLS_DEINO, RIVAL_BATTLE_HEAL_AFTER, MeteorFalls_1F_1R_Text_DraconidAsterDefeat, MeteorFalls_1F_1R_Text_DraconidAsterVictory
	compare VAR_RESULT, TRUE
	goto_if_eq MeteorFalls_1F_1R_EventScript_DraconidAster_2
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_5
MeteorFalls_1F_1R_EventScript_DraconidAster_1:
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_6
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_7
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_8
	closemessage
	applymovement LOCALID_METEOR_FALLS_ASTER, MeteorFalls_1F_1R_Movement_DraconidAsterLeave
	waitmovement 0
	removeobject LOCALID_METEOR_FALLS_ASTER
	setvar VAR_ASTER_STATE, ASTER_STATE_METEOR_FALLS
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

MeteorFalls_1F_1R_EventScript_DraconidAster_2:
	msgbox MeteorFalls_1F_1R_EventScript_DraconidAster_Text_4
	goto MeteorFalls_1F_1R_EventScript_DraconidAster_1


MeteorFalls_1F_1R_Movement_DraconidMaxieApproach:
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

MeteorFalls_1F_1R_Movement_DraconidArchieArrive:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_DraconidAquaGrunt1Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_DraconidAquaGrunt2Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_DraconidMaxieExit:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_DraconidMagmaGrunt2Exit:
	delay_16
	delay_16
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_DraconidMagmaGrunt1Exit:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_DraconidPlayerBlockStairs:
	walk_right
	walk_in_place_faster_down
	step_end

MeteorFalls_1F_1R_Movement_DraconidArchieToStairs:
	walk_right
	walk_right
	walk_right
	face_up
	step_end

MeteorFalls_1F_1R_Movement_DraconidAquaGrunt1ToStairs:
	delay_16
	walk_right
	walk_right
	walk_right
	face_up
	step_end

MeteorFalls_1F_1R_Movement_DraconidAquaGrunt2ToStairs:
	delay_16
	walk_right
	walk_right
	face_up
	step_end

MeteorFalls_1F_1R_Movement_DraconidArchieExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_DraconidAquaGruntExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_DraconidAsterApproach:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

MeteorFalls_1F_1R_Movement_DraconidAsterLeave:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MeteorFalls_1F_1R_EventScript_DraconidCozmo::
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_EventScript_DraconidCozmo_Text_0
	release
	return


MtChimney_EventScript_DraconidOnTransition::
	setflag FLAG_TEMP_11
	return


MtChimney_EventScript_DraconidTabitha::
	lock
	faceplayer
	msgbox MtChimney_EventScript_DraconidTabitha_Text_0
	release
	return


MtChimney_EventScript_DraconidMaxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano
	closemessage
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidMaxie_Text_0
	msgbox MtChimney_EventScript_DraconidMaxie_Text_1
	msgbox MtChimney_EventScript_DraconidMaxie_Text_2
	closemessage
	applymovement LOCALID_MT_CHIMNEY_TABITHA, MtChimney_Movement_DraconidTabithaToMaxie
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidMaxie_Text_3
	msgbox MtChimney_EventScript_DraconidMaxie_Text_4
	msgbox MtChimney_EventScript_DraconidMaxie_Text_5
	closemessage
	applymovement LOCALID_MT_CHIMNEY_TABITHA, MtChimney_Movement_DraconidTabithaLeave
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidMaxie_Text_6
	closemessage
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceRight
	waitmovement 0
	compare VAR_FACING, DIR_EAST
	goto_if_eq MtChimney_EventScript_DraconidMaxie_2
	applymovement LOCALID_PLAYER, MtChimney_Movement_DraconidGuardPostFromSouth
MtChimney_EventScript_DraconidMaxie_1:
	waitmovement 0
	savebgm MUS_DUMMY
	fadedefaultbgm
	delay 40
	call MtChimney_EventScript_DraconidNerine
	call MtChimney_EventScript_DraconidBrendan
	call MtChimney_EventScript_DraconidSabotage
	releaseall
	return

MtChimney_EventScript_DraconidMaxie_2:
	applymovement LOCALID_PLAYER, MtChimney_Movement_DraconidGuardPostFromWest
	goto MtChimney_EventScript_DraconidMaxie_1


MtChimney_EventScript_DraconidNerine::
	addobject LOCALID_MT_CHIMNEY_NERINE
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_MT_CHIMNEY_NERINE, MtChimney_Movement_DraconidNerineApproach
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidNerine_Text_0
	msgbox MtChimney_EventScript_DraconidNerine_Text_1
	msgbox MtChimney_EventScript_DraconidNerine_Text_2
	closemessage
	trainerbattle_no_intro TRAINER_NERINE_MT_CHIMNEY_DEINO_CHARMANDER, MtChimney_Text_DraconidNerineDefeat
	msgbox MtChimney_EventScript_DraconidNerine_Text_3
	closemessage
	applymovement LOCALID_MT_CHIMNEY_NERINE, MtChimney_Movement_DraconidNerineLeave
	waitmovement 0
	removeobject LOCALID_MT_CHIMNEY_NERINE
	setvar VAR_NERINE_STATE, NERINE_STATE_MT_CHIMNEY
	delay 30
	return


MtChimney_EventScript_DraconidBrendan::
	addobject LOCALID_MT_CHIMNEY_BRENDAN
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	applymovement LOCALID_MT_CHIMNEY_BRENDAN, MtChimney_Movement_DraconidBrendanApproach
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MT_CHIMNEY_BRENDAN, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidBrendan_Text_0
	msgbox MtChimney_EventScript_DraconidBrendan_Text_1
	msgbox MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_10
	msgbox MtChimney_EventScript_DraconidBrendan_Text_2
	closemessage
	trainerbattle_earlyrival TRAINER_BRENDAN_MT_CHIMNEY, RIVAL_BATTLE_HEAL_AFTER, MtChimney_Text_DraconidBrendanDefeat, MtChimney_Text_DraconidBrendanVictory
	compare VAR_RESULT, TRUE
	goto_if_eq MtChimney_EventScript_DraconidBrendan_2
	msgbox MtChimney_EventScript_DraconidBrendan_Text_4
MtChimney_EventScript_DraconidBrendan_1:
	msgbox MtChimney_EventScript_DraconidBrendan_Text_5
	closemessage
	applymovement LOCALID_MT_CHIMNEY_BRENDAN, MtChimney_Movement_DraconidBrendanLeave
	waitmovement 0
	removeobject LOCALID_MT_CHIMNEY_BRENDAN
	setvar VAR_BRENDAN_STATE, BRENDAN_STATE_MT_CHIMNEY
	delay 40
	return

MtChimney_EventScript_DraconidBrendan_2:
	msgbox MtChimney_EventScript_DraconidBrendan_Text_3
	goto MtChimney_EventScript_DraconidBrendan_1


MtChimney_EventScript_DraconidSabotage::
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidSabotage_Text_0
	closemessage
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_PLAYER, MtChimney_Movement_DraconidPlayerToMachine
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidSabotage_Text_1
	closemessage
	playse SE_CLICK
	delay 20
	msgbox MtChimney_EventScript_DraconidSabotage_Text_2
	giveitem ITEM_METEORITE
	compare VAR_RESULT, TRUE
	goto_if_eq MtChimney_EventScript_DraconidSabotage_2
MtChimney_EventScript_DraconidSabotage_1:
	closemessage
	playse SE_FAILURE
	waitse
	delay 30
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceRight
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidSabotage_Text_3
	closemessage
	playse SE_PIN
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidSabotage_Text_4
	closemessage
	applymovement LOCALID_MT_CHIMNEY_MAXIE, MtChimney_Movement_DraconidMaxieToPlayer
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_EventScript_DraconidSabotage_Text_5
	msgbox MtChimney_EventScript_DraconidSabotage_Text_6
	msgbox MtChimney_EventScript_DraconidSabotage_Text_7
	msgbox MtChimney_EventScript_DraconidSabotage_Text_8
	msgbox MtChimney_EventScript_DraconidSabotage_Text_9
	msgbox MtChimney_EventScript_DraconidSabotage_Text_10
	closemessage
	delay 30
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_CHIMNEY_MAXIE
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1
	removeobject LOCALID_MT_CHIMNEY_TABITHA
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_2
	removeobject LOCALID_MT_CHIMNEY_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox MtChimney_EventScript_DraconidSabotage_Text_11
	closemessage
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	clearflag FLAG_HIDE_JAGGED_PASS_ASTER
	setvar VAR_MAGMA_STATE, MAGMA_STATE_MT_CHIMNEY
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

MtChimney_EventScript_DraconidSabotage_2:
	setflag FLAG_RECEIVED_METEORITE
	goto MtChimney_EventScript_DraconidSabotage_1


MtChimney_Movement_DraconidTabithaToMaxie:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	face_right
	step_end

MtChimney_Movement_DraconidTabithaLeave:
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	set_invisible
	step_end

MtChimney_Movement_DraconidGuardPostFromSouth:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_DraconidGuardPostFromWest:
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_DraconidNerineApproach:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

MtChimney_Movement_DraconidNerineLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_DraconidBrendanApproach:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

MtChimney_Movement_DraconidBrendanLeave:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

MtChimney_Movement_DraconidPlayerToMachine:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MtChimney_Movement_DraconidMaxieToPlayer:
	walk_down
	walk_in_place_faster_right
	step_end

JaggedPass_EventScript_DraconidAster::
	lockall
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	msgbox JaggedPass_EventScript_DraconidAster_Text_0
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	compare VAR_TEMP_0, 13
	goto_if_eq JaggedPass_EventScript_DraconidAster_2
	applymovement LOCALID_JAGGED_PASS_ASTER, JaggedPass_Movement_DraconidAsterApproachNear
JaggedPass_EventScript_DraconidAster_1:
	waitmovement 0
	msgbox JaggedPass_EventScript_DraconidAster_Text_1
	msgbox JaggedPass_EventScript_DraconidAster_Text_2
	giveitem ITEM_MEGA_RING
	setflag FLAG_RECEIVED_MEGA_RING
	msgbox JaggedPass_EventScript_DraconidAster_Text_3
	msgbox JaggedPass_EventScript_DraconidAster_Text_4
	closemessage
	applymovement LOCALID_JAGGED_PASS_ASTER, JaggedPass_Movement_DraconidAsterLeave
	waitmovement 0
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_JAGGED_PASS_ASTER
	fadescreen FADE_FROM_BLACK
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_DRACONID_TRAVELLER
	setvar VAR_ASTER_STATE, ASTER_STATE_MEGA_RING
	releaseall
	return

JaggedPass_EventScript_DraconidAster_2:
	applymovement LOCALID_JAGGED_PASS_ASTER, JaggedPass_Movement_DraconidAsterApproachFar
	goto JaggedPass_EventScript_DraconidAster_1


JaggedPass_Movement_DraconidAsterApproachFar:
	walk_left
	walk_left
	walk_left
	step_end

JaggedPass_Movement_DraconidAsterApproachNear:
	walk_left
	walk_left
	step_end

JaggedPass_Movement_DraconidAsterLeave:
	face_right
	delay_16
	walk_right
	walk_right
	step_end

LavaridgeTown_EventScript_DraconidTraveller::
	lock
	faceplayer
	switch VAR_SECOND_STARTER
	case SECOND_STARTER_CHARMANDER, LavaridgeTown_EventScript_DraconidTraveller_3
	case SECOND_STARTER_TOTODILE, LavaridgeTown_EventScript_DraconidTraveller_4
	case SECOND_STARTER_TREECKO, LavaridgeTown_EventScript_DraconidTraveller_5
	setvar VAR_0x8004, ITEM_NONE
LavaridgeTown_EventScript_DraconidTraveller_1:
	compare VAR_0x8004, ITEM_NONE
	goto_if_eq LavaridgeTown_EventScript_DraconidTraveller_8
	msgbox LavaridgeTown_EventScript_DraconidTraveller_Text_1
	giveitem VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq LavaridgeTown_EventScript_DraconidTraveller_11
	msgbox LavaridgeTown_EventScript_DraconidTraveller_Text_3
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_LAVARIDGE_DRACONID_TRAVELLER
	fadescreen FADE_FROM_BLACK
	release
	return

LavaridgeTown_EventScript_DraconidTraveller_3:
	setvar VAR_0x8004, ITEM_CHARIZARDITE_X
	goto LavaridgeTown_EventScript_DraconidTraveller_1

LavaridgeTown_EventScript_DraconidTraveller_4:
	setvar VAR_0x8004, ITEM_FERALIGITE
	goto LavaridgeTown_EventScript_DraconidTraveller_1

LavaridgeTown_EventScript_DraconidTraveller_5:
	setvar VAR_0x8004, ITEM_SCEPTILITE
	goto LavaridgeTown_EventScript_DraconidTraveller_1

LavaridgeTown_EventScript_DraconidTraveller_8:
	msgbox LavaridgeTown_EventScript_DraconidTraveller_Text_0
	release
	end

LavaridgeTown_EventScript_DraconidTraveller_11:
	msgbox LavaridgeTown_EventScript_DraconidTraveller_Text_2
	release
	end


MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_0:
	.string "Heh? Who's that… Oh! That uniform!\p"
	.string "You're the new one! The recruit TABITHA\n"
	.string "keeps bragging about!\p"
	.string "LEADER! The kid made it!$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_1:
	.string "MAXIE: So you are {PLAYER}. We meet at\n"
	.string "last.\p"
	.string "A voice on the POKéNAV tells me very\n"
	.string "little. TABITHA tells me more.\p"
	.string "She speaks well of you. She rarely\n"
	.string "speaks well of anyone.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_2:
	.string "MAXIE: Look at it, {PLAYER}.\p"
	.string "This stone fell from the sky long ago.\n"
	.string "It still burns with a power our world has\l"
	.string "forgotten.\p"
	.string "With it, we will wake the heart of\n"
	.string "MT. CHIMNEY. Its fire will cool into new\l"
	.string "land.\p"
	.string "Land for people with nowhere to live.\n"
	.string "For POKéMON driven from their homes.\p"
	.string "For children like you, {PLAYER}.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_3:
	.string "MAXIE: A shard broke away when we cut\n"
	.string "it from the rock. Here.\p"
	.string "Keep it. Every great work begins with a\n"
	.string "small stone.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_4:
	.string "MAXIE pressed a small shard of the\n"
	.string "METEORITE into {PLAYER}'s hand.\p"
	.string "It was still warm.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_5:
	.string "MAXIE: ARCHIE. Late, as always.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_6:
	.string "ARCHIE: MAXIE! Hand over that\n"
	.string "METEORITE! You have no idea what you're\l"
	.string "playing with!$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_7:
	.string "MAXIE: I know exactly what I am playing\n"
	.string "with. That is the difference between\l"
	.string "us.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_8:
	.string "MAXIE: {PLAYER}. Hold the stairs. We go\n"
	.string "to MT. CHIMNEY.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_9:
	.string "ARCHIE: Out of the way, kid.\p"
	.string "…Hold on. I know that face. The MAGMA\n"
	.string "grunt from SLATEPORT's MUSEUM!\p"
	.string "I told you to stay out of TEAM AQUA's\n"
	.string "way. Did you think I was joking?$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_10:
	.string "{PLAYER} didn't move.$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_11:
	.string "BOSS! MAGMA's getting away with the\n"
	.string "METEORITE!$"

MeteorFalls_1F_1R_EventScript_DraconidMeteoriteScene_Text_12:
	.string "ARCHIE: …Hah! Look at that stubborn\n"
	.string "face. MAXIE doesn't deserve grunts like\l"
	.string "you.\p"
	.string "Fine. A brawl on these stairs costs more\n"
	.string "time than we've got.\p"
	.string "We know where they're going.\n"
	.string "MT. CHIMNEY. We'll take the long way\l"
	.string "round.\p"
	.string "TEAM AQUA, move out!$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_0:
	.string "ASTER: …So it's true.$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_1:
	.string "ASTER: I followed MAGMA's trail from\n"
	.string "FALLARBOR. I thought I'd find the\l"
	.string "ELDER's chosen one stopping them.\p"
	.string "Instead I watched you guard the stairs\n"
	.string "so MAXIE could run!$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_2:
	.string "ASTER: The ELDER's eggs came from\n"
	.string "these falls, {PLAYER}. Yours too.\p"
	.string "And you stood watch while they robbed\n"
	.string "it.\p"
	.string "The ELDER trusted you, and you carry\n"
	.string "THEIR flag?$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_3:
	.string "ASTER: …Show me there's still a Draconid\n"
	.string "under all that red!$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_4:
	.string "ASTER: Weak. And wearing their colors.\p"
	.string "…The ELDER must see something in you\n"
	.string "that I can't.$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_5:
	.string "ASTER: …Fine. You haven't forgotten\n"
	.string "everything.$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_6:
	.string "ASTER: …What's that in your hand?\p"
	.string "A piece of the METEORITE? MAXIE handed\n"
	.string "you a piece of the sky like it was a\l"
	.string "sweet?\p"
	.string "Give it here. The ELDER should see what\n"
	.string "MAGMA is playing with.$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_7:
	.string "{PLAYER} handed the shard to ASTER.$"

MeteorFalls_1F_1R_EventScript_DraconidAster_Text_8:
	.string "ASTER: Don't follow me. And don't get\n"
	.string "too comfortable in red.$"

MeteorFalls_1F_1R_EventScript_DraconidCozmo_Text_0:
	.string "PROF. COZMO: Eek! One of them!\p"
	.string "You… You're the one their LEADER was\n"
	.string "talking to!\p"
	.string "P-please… I have nothing left. You\n"
	.string "already took my METEORITE.\p"
	.string "I only wanted to study it. Now I'll never\n"
	.string "know what it could have told us…$"

MtChimney_EventScript_DraconidTabitha_Text_0:
	.string "TABITHA: Hehehe! Took your time, didn't\n"
	.string "you?\p"
	.string "Leader MAXIE is up at the crater with\n"
	.string "the METEORITE. He asked for you. By\l"
	.string "name!\p"
	.string "Don't keep him waiting. Hehehe!$"

MtChimney_EventScript_DraconidMaxie_Text_0:
	.string "MAXIE: Ah, {PLAYER}. You came, as I\n"
	.string "asked.$"

MtChimney_EventScript_DraconidMaxie_Text_1:
	.string "MAXIE: Look. The METEORITE's energy\n"
	.string "flows into the machine, and from the\l"
	.string "machine into the mountain.\p"
	.string "When MT. CHIMNEY wakes, its fire will\n"
	.string "pour out and cool into new land.\p"
	.string "ARCHIE calls that destruction. Every\n"
	.string "birth looks like destruction to those\l"
	.string "who fear change.\p"
	.string "The town below will have time to leave. I\n"
	.string "am not a monster, {PLAYER}.$"

MtChimney_EventScript_DraconidMaxie_Text_2:
	.string "MAXIE: TABITHA!$"

MtChimney_EventScript_DraconidMaxie_Text_3:
	.string "TABITHA: Hehehe! Yes, LEADER?$"

MtChimney_EventScript_DraconidMaxie_Text_4:
	.string "MAXIE: Take the grunts down the east\n"
	.string "slope. Keep ARCHIE busy.$"

MtChimney_EventScript_DraconidMaxie_Text_5:
	.string "TABITHA: With pleasure! Hehehe!$"

MtChimney_EventScript_DraconidMaxie_Text_6:
	.string "MAXIE: {PLAYER}. Guard the path below\n"
	.string "us, as I told you. AQUA will come.\p"
	.string "No one reaches this machine until it is\n"
	.string "done. I am trusting you with this.$"

MtChimney_EventScript_DraconidNerine_Text_0:
	.string "NERINE: …Keep your voice down. Your\n"
	.string "LEADER is busy with his toy.\p"
	.string "Your friends at the bottom of the path\n"
	.string "are taking a nap. Don't worry. They'll\l"
	.string "wake up.$"

MtChimney_EventScript_DraconidNerine_Text_1:
	.string "NERINE: So. Just the two of us. A grunt\n"
	.string "in red and a grunt in blue, guarding a\l"
	.string "mountain.\p"
	.string "Neither of us belongs here, do we?$"

MtChimney_EventScript_DraconidNerine_Text_2:
	.string "NERINE: …Your village is Draconid. Mine\n"
	.string "is too.\p"
	.string "Don't look so surprised. I knew the\n"
	.string "first time I saw your dragon in the\l"
	.string "woods.\p"
	.string "Show me you're worth the ELDER's trust.$"

MtChimney_EventScript_DraconidNerine_Text_3:
	.string "NERINE: Not a word of this. Not to\n"
	.string "MAGMA. Not to anyone.\p"
	.string "Keep your eyes on the sky, {PLAYER}. Not\n"
	.string "on the fire.$"

MtChimney_EventScript_DraconidBrendan_Text_0:
	.string "BRENDAN: {PLAYER}!\p"
	.string "Let me through! Your boss is going to\n"
	.string "make the volcano erupt!\p"
	.string "LAVARIDGE is right below us! Do you\n"
	.string "know how many people live there?!$"

MtChimney_EventScript_DraconidBrendan_Text_1:
	.string "BRENDAN: …You're not moving.\p"
	.string "After RUSTBORO I kept telling myself\n"
	.string "you had a reason. That there had to be\l"
	.string "one.\p"
	.string "Then tell me what it is! Or get out of my\n"
	.string "way!$"

MtChimney_EventScript_DraconidBrendan_Text_2:
	.string "BRENDAN: …Fine. Then I'll go through\n"
	.string "you!$"

MtChimney_EventScript_DraconidBrendan_Text_3:
	.string "BRENDAN: I beat you, and you still won't\n"
	.string "move.\p"
	.string "…What happened to you, {PLAYER}?$"

MtChimney_EventScript_DraconidBrendan_Text_4:
	.string "BRENDAN: I can't get past you. Not like\n"
	.string "this.$"

MtChimney_EventScript_DraconidBrendan_Text_5:
	.string "BRENDAN: Forget it. I'm going down to\n"
	.string "warn LAVARIDGE. Somebody has to.\p"
	.string "Don't follow me.$"

MtChimney_EventScript_DraconidSabotage_Text_0:
	.string "MAXIE: Fufufu… Do you feel it? The\n"
	.string "mountain is waking!$"

MtChimney_EventScript_DraconidSabotage_Text_1:
	.string "MAXIE stood with his back to the\n"
	.string "machine, staring up at the smoke.\p"
	.string "{PLAYER} reached into the machine…$"

MtChimney_EventScript_DraconidSabotage_Text_2:
	.string "…and quietly pulled the METEORITE free!$"

MtChimney_EventScript_DraconidSabotage_Text_3:
	.string "MAXIE: …The rumbling. It's fading?$"

MtChimney_EventScript_DraconidSabotage_Text_4:
	.string "MAXIE: The METEORITE… It's gone!$"

MtChimney_EventScript_DraconidSabotage_Text_5:
	.string "MAXIE: {PLAYER}! Did anyone get past\n"
	.string "you?$"

MtChimney_EventScript_DraconidSabotage_Text_6:
	.string "{PLAYER} shook their head.$"

MtChimney_EventScript_DraconidSabotage_Text_7:
	.string "MAXIE: …No. Of course not. I watched\n"
	.string "you hold that path. Twice.\p"
	.string "Then it was ARCHIE. His grunts were\n"
	.string "crawling over every slope of this\l"
	.string "mountain.\p"
	.string "One of them slipped up the cliff in the\n"
	.string "smoke while we were busy.$"

MtChimney_EventScript_DraconidSabotage_Text_8:
	.string "MAXIE: ARCHIE… You would drown the\n"
	.string "whole world just to spite me.$"

MtChimney_EventScript_DraconidSabotage_Text_9:
	.string "MAXIE: …Enough. A key can be stolen.\n"
	.string "The door is still there.\p"
	.string "TEAM MAGMA! We withdraw!$"

MtChimney_EventScript_DraconidSabotage_Text_10:
	.string "MAXIE: {PLAYER}. You did well today.\n"
	.string "Better than anyone had a right to\l"
	.string "expect.\p"
	.string "I will remember it.$"

MtChimney_EventScript_DraconidSabotage_Text_11:
	.string "TEAM MAGMA left the summit.\p"
	.string "Far below, TEAM AQUA was pulling back,\n"
	.string "too.$"

JaggedPass_EventScript_DraconidAster_Text_0:
	.string "ASTER: Over here, {PLAYER}.$"

JaggedPass_EventScript_DraconidAster_Text_1:
	.string "ASTER: I watched from the ridge.\n"
	.string "MAXIE's machine sputtered out like a\l"
	.string "wet match.\p"
	.string "And I saw who was standing next to it\n"
	.string "when it died.\p"
	.string "…Not bad. For a traitor.$"

JaggedPass_EventScript_DraconidAster_Text_2:
	.string "ASTER: I took your shard to the ELDER.\n"
	.string "He set it in this.\p"
	.string "A KEY STONE, in a ring. When a POKéMON\n"
	.string "trusts you with its whole heart, the\l"
	.string "stone lets it MEGA EVOLVE.$"

JaggedPass_EventScript_DraconidAster_Text_3:
	.string "ASTER: The ELDER says you're doing well.\p"
	.string "I say we'll see.$"

JaggedPass_EventScript_DraconidAster_Text_4:
	.string "ASTER: One more thing. Someone from the\n"
	.string "village is waiting in LAVARIDGE.\p"
	.string "He has something for the partner\n"
	.string "PROF. OAK gave you.\p"
	.string "Don't make me regret this.$"

LavaridgeTown_EventScript_DraconidTraveller_Text_0:
	.string "{PLAYER}! The ELDER sent me to find you.\p"
	.string "Come back when PROF. OAK has given you\n"
	.string "a partner.$"

LavaridgeTown_EventScript_DraconidTraveller_Text_1:
	.string "Ah! {PLAYER}! ASTER said you'd come down\n"
	.string "the pass.\p"
	.string "Don't mind the looks you're getting\n"
	.string "here. Mountain folk have long memories.\p"
	.string "The ELDER sent me with this. A MEGA\n"
	.string "STONE, for the partner PROF. OAK gave\l"
	.string "you.\p"
	.string "Its MEGA form carries a dragon's blood.$"

LavaridgeTown_EventScript_DraconidTraveller_Text_2:
	.string "Your BAG is too full for it? Make some\n"
	.string "room, then. I'll wait here.$"

LavaridgeTown_EventScript_DraconidTraveller_Text_3:
	.string "With the ring ASTER gave you, your\n"
	.string "partner can MEGA EVOLVE once it is\l"
	.string "fully grown.\p"
	.string "Safe travels, {PLAYER}. The whole village\n"
	.string "is rooting for you.\p"
	.string "…Well. Most of it.$"

MeteorFalls_1F_1R_Text_DraconidAsterDefeat::
	.string "…Hmph. You still battle like one of us.$"

MeteorFalls_1F_1R_Text_DraconidAsterVictory::
	.string "Is this who the ELDER chose over me?$"

MtChimney_Text_DraconidNerineDefeat::
	.string "…Good. The ELDER wasn't wrong about\n"
	.string "you.$"

MtChimney_Text_DraconidBrendanDefeat::
	.string "Why?! Why are you protecting HIM?$"

MtChimney_Text_DraconidBrendanVictory::
	.string "…I won. So why does it feel like I lost?$"
