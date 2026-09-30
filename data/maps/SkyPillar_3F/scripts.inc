SkyPillar_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_3F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SkyPillar_3F_OnFrame  @ Draconid Emerald
	.byte 0

SkyPillar_3F_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_3F_EventScript_CleanFloor
	call SkyPillar_3F_EventScript_DraconidOnTransition  @ Draconid Emerald: Zinnia waits during the finale (act7.pory)
	end

@ Draconid Emerald: Zinnia's test during the Sky Pillar finale (act7.pory)
SkyPillar_3F_OnFrame:
	map_script_2 VAR_TEMP_7, 1, SkyPillar_3F_EventScript_DraconidZinniaScene
	.2byte 0

SkyPillar_3F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_3F_CLEAN
	return

