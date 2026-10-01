GraniteCave_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, GraniteCave_B1F_OnTransition @ Draconid Emerald: was CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, GraniteCave_B1F_SetHoleWarp
	.byte 0

@ Draconid Emerald: Aster waits in the dark in Act 2 (data/scripts/draconid/draconid_rivals.pory), then the vanilla script
GraniteCave_B1F_OnTransition:
	call GraniteCave_B1F_EventScript_DraconidOnTransition
	goto CaveHole_FixCrackedGround

GraniteCave_B1F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_GRANITE_CAVE_B2F
	end

