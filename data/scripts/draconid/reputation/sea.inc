Route109_EventScript_DraconidRepMrBriney::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route109_EventScript_DraconidRepMrBriney_2
Route109_EventScript_DraconidRepMrBriney_1:
	goto Route109_EventScript_MrBriney
	return

Route109_EventScript_DraconidRepMrBriney_2:
	lock
	faceplayer
	msgbox Route109_Text_DraconidRepMrBrineyUniform, MSGBOX_DEFAULT
	goto Route109_EventScript_DraconidRepMrBriney_1


Route109_EventScript_DraconidRepSeashoreHouseGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route109_EventScript_DraconidRepSeashoreHouseGirl_2
	goto Route109_EventScript_SeashoreHouseGirl
	return

Route109_EventScript_DraconidRepSeashoreHouseGirl_2:
	msgbox Route109_Text_DraconidRepSeashoreHouseGirlUniform, MSGBOX_NPC
	return


Route109_EventScript_DraconidRepSandCastleBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route109_EventScript_DraconidRepSandCastleBoy_2
	goto Route109_EventScript_SandCastleBoy
	return

Route109_EventScript_DraconidRepSandCastleBoy_2:
	msgbox Route109_Text_DraconidRepSandCastleBoyUniform, MSGBOX_NPC
	return


Route109_EventScript_DraconidRepSoftSandGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route109_EventScript_DraconidRepSoftSandGirl_2
Route109_EventScript_DraconidRepSoftSandGirl_1:
	goto Route109_EventScript_SoftSandGirl
	return

Route109_EventScript_DraconidRepSoftSandGirl_2:
	lock
	faceplayer
	msgbox Route109_Text_DraconidRepSoftSandGirlUniform, MSGBOX_DEFAULT
	goto Route109_EventScript_DraconidRepSoftSandGirl_1


Route109_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route109_EventScript_DraconidRepWoman_2
	goto Route109_EventScript_Woman
	return

Route109_EventScript_DraconidRepWoman_2:
	msgbox Route109_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


Route109_EventScript_DraconidRepOldMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route109_EventScript_DraconidRepOldMan_2
	goto Route109_EventScript_OldMan
	return

Route109_EventScript_DraconidRepOldMan_2:
	msgbox Route109_Text_DraconidRepOldManUniform, MSGBOX_NPC
	return


Route109_SeashoreHouse_EventScript_DraconidRepOwner::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route109_SeashoreHouse_EventScript_DraconidRepOwner_2
Route109_SeashoreHouse_EventScript_DraconidRepOwner_1:
	goto Route109_SeashoreHouse_EventScript_Owner
	return

Route109_SeashoreHouse_EventScript_DraconidRepOwner_2:
	lock
	faceplayer
	msgbox Route109_SeashoreHouse_Text_DraconidRepOwnerUniform, MSGBOX_DEFAULT
	goto Route109_SeashoreHouse_EventScript_DraconidRepOwner_1


AbandonedShip_CaptainsOffice_EventScript_DraconidRepCaptSternAide::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq AbandonedShip_CaptainsOffice_EventScript_DraconidRepCaptSternAide_2
AbandonedShip_CaptainsOffice_EventScript_DraconidRepCaptSternAide_1:
	goto AbandonedShip_CaptainsOffice_EventScript_CaptSternAide
	return

AbandonedShip_CaptainsOffice_EventScript_DraconidRepCaptSternAide_2:
	lock
	faceplayer
	msgbox AbandonedShip_CaptainsOffice_Text_DraconidRepCaptSternAideUniform, MSGBOX_DEFAULT
	goto AbandonedShip_CaptainsOffice_EventScript_DraconidRepCaptSternAide_1


AbandonedShip_Corridors_1F_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, AbandonedShip_Corridors_1F_EventScript_DraconidRepYoungster_2
	goto AbandonedShip_Corridors_1F_EventScript_Youngster
	return

AbandonedShip_Corridors_1F_EventScript_DraconidRepYoungster_2:
	msgbox AbandonedShip_Corridors_1F_Text_DraconidRepYoungsterUniform, MSGBOX_NPC
	return


AbandonedShip_Corridors_B1F_EventScript_DraconidRepTuberM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, AbandonedShip_Corridors_B1F_EventScript_DraconidRepTuberM_2
	goto AbandonedShip_Corridors_B1F_EventScript_TuberM
	return

AbandonedShip_Corridors_B1F_EventScript_DraconidRepTuberM_2:
	msgbox AbandonedShip_Corridors_B1F_Text_DraconidRepTuberMUniform, MSGBOX_NPC
	return


AbandonedShip_Rooms2_B1F_EventScript_DraconidRepCamper::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, AbandonedShip_Rooms2_B1F_EventScript_DraconidRepCamper_2
	goto AbandonedShip_Rooms2_B1F_EventScript_Camper
	return

AbandonedShip_Rooms2_B1F_EventScript_DraconidRepCamper_2:
	msgbox AbandonedShip_Rooms2_B1F_Text_DraconidRepCamperUniform, MSGBOX_NPC
	return


AbandonedShip_Rooms_1F_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, AbandonedShip_Rooms_1F_EventScript_DraconidRepGentleman_2
	goto AbandonedShip_Rooms_1F_EventScript_Gentleman
	return

AbandonedShip_Rooms_1F_EventScript_DraconidRepGentleman_2:
	msgbox AbandonedShip_Rooms_1F_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


AbandonedShip_Rooms_B1F_EventScript_DraconidRepFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, AbandonedShip_Rooms_B1F_EventScript_DraconidRepFatMan_2
	goto AbandonedShip_Rooms_B1F_EventScript_FatMan
	return

AbandonedShip_Rooms_B1F_EventScript_DraconidRepFatMan_2:
	msgbox AbandonedShip_Rooms_B1F_Text_DraconidRepFatManUniform, MSGBOX_NPC
	return


Route124_DivingTreasureHuntersHouse_EventScript_DraconidRepTreasureHunter::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route124_DivingTreasureHuntersHouse_EventScript_DraconidRepTreasureHunter_2
Route124_DivingTreasureHuntersHouse_EventScript_DraconidRepTreasureHunter_1:
	goto Route124_DivingTreasureHuntersHouse_EventScript_TreasureHunter
	return

Route124_DivingTreasureHuntersHouse_EventScript_DraconidRepTreasureHunter_2:
	lock
	faceplayer
	msgbox Route124_DivingTreasureHuntersHouse_Text_DraconidRepTreasureHunterUniform, MSGBOX_DEFAULT
	goto Route124_DivingTreasureHuntersHouse_EventScript_DraconidRepTreasureHunter_1


ShoalCave_LowTideEntranceRoom_EventScript_DraconidRepShellBellExpert::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq ShoalCave_LowTideEntranceRoom_EventScript_DraconidRepShellBellExpert_2
ShoalCave_LowTideEntranceRoom_EventScript_DraconidRepShellBellExpert_1:
	goto ShoalCave_LowTideEntranceRoom_EventScript_ShellBellExpert
	return

ShoalCave_LowTideEntranceRoom_EventScript_DraconidRepShellBellExpert_2:
	lock
	faceplayer
	msgbox ShoalCave_LowTideEntranceRoom_Text_DraconidRepShellBellExpertUniform, MSGBOX_DEFAULT
	goto ShoalCave_LowTideEntranceRoom_EventScript_DraconidRepShellBellExpert_1


ShoalCave_LowTideLowerRoom_EventScript_DraconidRepBlackBelt::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq ShoalCave_LowTideLowerRoom_EventScript_DraconidRepBlackBelt_2
ShoalCave_LowTideLowerRoom_EventScript_DraconidRepBlackBelt_1:
	goto ShoalCave_LowTideLowerRoom_EventScript_BlackBelt
	return

ShoalCave_LowTideLowerRoom_EventScript_DraconidRepBlackBelt_2:
	lock
	faceplayer
	msgbox ShoalCave_LowTideLowerRoom_Text_DraconidRepBlackBeltUniform, MSGBOX_DEFAULT
	goto ShoalCave_LowTideLowerRoom_EventScript_DraconidRepBlackBelt_1


Route109_Text_DraconidRepMrBrineyUniform::
	.string "MR. BRINEY: The beach folk give your\n"
	.string "red getup funny looks.\p"
	.string "Let 'em look! PEEKO and I know who you\n"
	.string "are.$"

Route109_Text_DraconidRepSeashoreHouseGirlUniform::
	.string "Yo, TRAINERS! Chill at my papa's spot!\p"
	.string "…Except you, TEAM MAGMA. You're too hot\n"
	.string "to chill. Papa said so.$"

Route109_Text_DraconidRepSandCastleBoyUniform::
	.string "Our sand castle's taking a long time to\n"
	.string "make.\p"
	.string "Don't stomp on it, TEAM MAGMA! You want\n"
	.string "land? Make your own castle!$"

Route109_Text_DraconidRepSoftSandGirlUniform::
	.string "A TEAM MAGMA grunt at the beach? Are\n"
	.string "you going to take all our sand?$"

Route109_Text_DraconidRepWomanUniform::
	.string "Little kids dart around so quickly. You\n"
	.string "can't take your eyes off them.\p"
	.string "Especially not with TEAM MAGMA on the\n"
	.string "beach.$"

Route109_Text_DraconidRepOldManUniform::
	.string "The water around here is clean. My\n"
	.string "ZIGZAGOON helps pick up litter.\p"
	.string "TEAM MAGMA wants less sea, they say.\p"
	.string "Then what would we have left to keep\n"
	.string "clean?$"

Route109_SeashoreHouse_Text_DraconidRepOwnerUniform::
	.string "Whoa! A TEAM MAGMA grunt in my SEASHORE\n"
	.string "HOUSE?\p"
	.string "You'd better not start any fires!\p"
	.string "…Well, hot battles are hot battles. I\n"
	.string "don't care who's fighting!$"

AbandonedShip_CaptainsOffice_Text_DraconidRepCaptSternAideUniform::
	.string "A TEAM MAGMA grunt on the ABANDONED\n"
	.string "SHIP? What could you want here?$"

AbandonedShip_Corridors_1F_Text_DraconidRepYoungsterUniform::
	.string "Isn't it fun here? I get excited just\n"
	.string "being here!\p"
	.string "And now there's TEAM MAGMA! This is like\n"
	.string "an adventure movie!$"

AbandonedShip_Corridors_B1F_Text_DraconidRepTuberMUniform::
	.string "Yay! It's a ship!\p"
	.string "Boo! It's TEAM MAGMA!$"

AbandonedShip_Rooms2_B1F_Text_DraconidRepCamperUniform::
	.string "There must be amazing treasures on\n"
	.string "board!\p"
	.string "You're not after the treasure too, are\n"
	.string "you, TEAM MAGMA?$"

AbandonedShip_Rooms_1F_Text_DraconidRepGentlemanUniform::
	.string "Ships like this are rare, so I'm taking a\n"
	.string "look around.\p"
	.string "TEAM MAGMA grunts on a ship are rare,\n"
	.string "too. I'll keep my distance.$"

AbandonedShip_Rooms_B1F_Text_DraconidRepFatManUniform::
	.string "Urrrrppp… I'm getting queasy on this\n"
	.string "ship.\p"
	.string "Seeing a TEAM MAGMA grunt isn't\n"
	.string "helping…$"

Route124_DivingTreasureHuntersHouse_Text_DraconidRepTreasureHunterUniform::
	.string "Whoa, TEAM MAGMA! You don't dive, do\n"
	.string "you? Your people hate the sea!$"

ShoalCave_LowTideEntranceRoom_Text_DraconidRepShellBellExpertUniform::
	.string "TEAM MAGMA, in SHOAL CAVE? Brr… You\n"
	.string "won't find any fire in here.$"

ShoalCave_LowTideLowerRoom_Text_DraconidRepBlackBeltUniform::
	.string "Hmph. A TEAM MAGMA grunt, watching me\n"
	.string "train?\p"
	.string "Focus… Focus…$"
