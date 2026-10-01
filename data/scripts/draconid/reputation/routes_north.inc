MtChimney_EventScript_DraconidRepBusyMagmaGrunt5::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyMagmaGrunt5_2
	goto MtChimney_EventScript_BusyMagmaGrunt5
	return

MtChimney_EventScript_DraconidRepBusyMagmaGrunt5_2:
	msgbox MtChimney_Text_DraconidRepBusyMagmaGrunt5Uniform, MSGBOX_NPC
	return


MtChimney_EventScript_DraconidRepBusyMagmaGrunt4::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyMagmaGrunt4_2
	goto MtChimney_EventScript_BusyMagmaGrunt4
	return

MtChimney_EventScript_DraconidRepBusyMagmaGrunt4_2:
	msgbox MtChimney_Text_DraconidRepBusyMagmaGrunt4Uniform, MSGBOX_NPC
	return


MtChimney_EventScript_DraconidRepBusyAquaGrunt2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyAquaGrunt2_2
	goto MtChimney_EventScript_BusyAquaGrunt2
	return

MtChimney_EventScript_DraconidRepBusyAquaGrunt2_2:
	msgbox MtChimney_Text_DraconidRepBusyAquaGrunt2Uniform, MSGBOX_NPC
	return


MtChimney_EventScript_DraconidRepBusyAquaGrunt1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyAquaGrunt1_2
	goto MtChimney_EventScript_BusyAquaGrunt1
	return

MtChimney_EventScript_DraconidRepBusyAquaGrunt1_2:
	msgbox MtChimney_Text_DraconidRepBusyAquaGrunt1Uniform, MSGBOX_NPC
	return


MtChimney_EventScript_DraconidRepBusyAquaGrunt3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyAquaGrunt3_2
	goto MtChimney_EventScript_BusyAquaGrunt3
	return

MtChimney_EventScript_DraconidRepBusyAquaGrunt3_2:
	msgbox MtChimney_Text_DraconidRepBusyAquaGrunt3Uniform, MSGBOX_NPC
	return


MtChimney_EventScript_DraconidRepLavaCookieLady::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MtChimney_EventScript_DraconidRepLavaCookieLady_2
MtChimney_EventScript_DraconidRepLavaCookieLady_1:
	goto MtChimney_EventScript_LavaCookieLady
	return

MtChimney_EventScript_DraconidRepLavaCookieLady_2:
	lock
	faceplayer
	msgbox MtChimney_Text_DraconidRepLavaCookieLadyUniform, MSGBOX_DEFAULT
	goto MtChimney_EventScript_DraconidRepLavaCookieLady_1


MtChimney_EventScript_DraconidRepBusyMagmaGrunt6::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyMagmaGrunt6_2
	goto MtChimney_EventScript_BusyMagmaGrunt6
	return

MtChimney_EventScript_DraconidRepBusyMagmaGrunt6_2:
	msgbox MtChimney_Text_DraconidRepBusyMagmaGrunt6Uniform, MSGBOX_NPC
	return


MtChimney_EventScript_DraconidRepBusyMagmaGrunt2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyMagmaGrunt2_2
	goto MtChimney_EventScript_BusyMagmaGrunt2
	return

MtChimney_EventScript_DraconidRepBusyMagmaGrunt2_2:
	msgbox MtChimney_Text_DraconidRepBusyMagmaGrunt2Uniform, MSGBOX_NPC
	return


MtChimney_EventScript_DraconidRepBusyMagmaGrunt1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtChimney_EventScript_DraconidRepBusyMagmaGrunt1_2
	goto MtChimney_EventScript_BusyMagmaGrunt1
	return

MtChimney_EventScript_DraconidRepBusyMagmaGrunt1_2:
	msgbox MtChimney_Text_DraconidRepBusyMagmaGrunt1Uniform, MSGBOX_NPC
	return


MtChimney_CableCarStation_EventScript_DraconidRepAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MtChimney_CableCarStation_EventScript_DraconidRepAttendant_2
MtChimney_CableCarStation_EventScript_DraconidRepAttendant_1:
	goto MtChimney_CableCarStation_EventScript_Attendant
	return

MtChimney_CableCarStation_EventScript_DraconidRepAttendant_2:
	lock
	faceplayer
	msgbox MtChimney_CableCarStation_Text_DraconidRepAttendantUniform, MSGBOX_DEFAULT
	goto MtChimney_CableCarStation_EventScript_DraconidRepAttendant_1


Route112_EventScript_DraconidRepMagmaGrunts::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route112_EventScript_DraconidRepMagmaGrunts_2
Route112_EventScript_DraconidRepMagmaGrunts_1:
	goto Route112_EventScript_MagmaGrunts
	return

Route112_EventScript_DraconidRepMagmaGrunts_2:
	lock
	faceplayer
	msgbox Route112_Text_DraconidRepMagmaGruntsUniform, MSGBOX_DEFAULT
	goto Route112_EventScript_DraconidRepMagmaGrunts_1


Route112_EventScript_DraconidRepMagmaGrunts2::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route112_EventScript_DraconidRepMagmaGrunts2_2
Route112_EventScript_DraconidRepMagmaGrunts2_1:
	goto Route112_EventScript_MagmaGrunts
	return

Route112_EventScript_DraconidRepMagmaGrunts2_2:
	lock
	faceplayer
	msgbox Route112_Text_DraconidRepMagmaGrunts2Uniform, MSGBOX_DEFAULT
	goto Route112_EventScript_DraconidRepMagmaGrunts2_1


Route112_EventScript_DraconidRepHiker::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route112_EventScript_DraconidRepHiker_2
	goto Route112_EventScript_Hiker
	return

Route112_EventScript_DraconidRepHiker_2:
	msgbox Route112_Text_DraconidRepHikerUniform, MSGBOX_NPC
	return


Route112_CableCarStation_EventScript_DraconidRepAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route112_CableCarStation_EventScript_DraconidRepAttendant_2
Route112_CableCarStation_EventScript_DraconidRepAttendant_1:
	goto Route112_CableCarStation_EventScript_Attendant
	return

Route112_CableCarStation_EventScript_DraconidRepAttendant_2:
	lock
	faceplayer
	msgbox Route112_CableCarStation_Text_DraconidRepAttendantUniform, MSGBOX_DEFAULT
	goto Route112_CableCarStation_EventScript_DraconidRepAttendant_1


Route113_EventScript_DraconidRepNinjaBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route113_EventScript_DraconidRepNinjaBoy_2
	goto Route113_EventScript_NinjaBoy
	return

Route113_EventScript_DraconidRepNinjaBoy_2:
	msgbox Route113_Text_DraconidRepNinjaBoyUniform, MSGBOX_NPC
	return


Route113_EventScript_DraconidRepGentleman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route113_EventScript_DraconidRepGentleman_2
	goto Route113_EventScript_Gentleman
	return

Route113_EventScript_DraconidRepGentleman_2:
	msgbox Route113_Text_DraconidRepGentlemanUniform, MSGBOX_NPC
	return


Route113_GlassWorkshop_EventScript_DraconidRepGlassWorker::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route113_GlassWorkshop_EventScript_DraconidRepGlassWorker_2
Route113_GlassWorkshop_EventScript_DraconidRepGlassWorker_1:
	goto Route113_GlassWorkshop_EventScript_GlassWorker
	return

Route113_GlassWorkshop_EventScript_DraconidRepGlassWorker_2:
	lock
	faceplayer
	msgbox Route113_GlassWorkshop_Text_DraconidRepGlassWorkerUniform, MSGBOX_DEFAULT
	goto Route113_GlassWorkshop_EventScript_DraconidRepGlassWorker_1


Route113_GlassWorkshop_EventScript_DraconidRepNinjaBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route113_GlassWorkshop_EventScript_DraconidRepNinjaBoy_2
	goto Route113_GlassWorkshop_EventScript_NinjaBoy
	return

Route113_GlassWorkshop_EventScript_DraconidRepNinjaBoy_2:
	msgbox Route113_GlassWorkshop_Text_DraconidRepNinjaBoyUniform, MSGBOX_NPC
	return


Route114_EventScript_DraconidRepRoarGentleman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route114_EventScript_DraconidRepRoarGentleman_2
Route114_EventScript_DraconidRepRoarGentleman_1:
	goto Route114_EventScript_RoarGentleman
	return

Route114_EventScript_DraconidRepRoarGentleman_2:
	lock
	faceplayer
	msgbox Route114_Text_DraconidRepRoarGentlemanUniform, MSGBOX_DEFAULT
	goto Route114_EventScript_DraconidRepRoarGentleman_1


Route114_EventScript_DraconidRepMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route114_EventScript_DraconidRepMan_2
Route114_EventScript_DraconidRepMan_1:
	goto Route114_EventScript_Man
	return

Route114_EventScript_DraconidRepMan_2:
	lock
	faceplayer
	msgbox Route114_Text_DraconidRepManUniform, MSGBOX_DEFAULT
	goto Route114_EventScript_DraconidRepMan_1


Route114_FossilManiacsHouse_EventScript_DraconidRepFossilManiacsBrother::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route114_FossilManiacsHouse_EventScript_DraconidRepFossilManiacsBrother_2
Route114_FossilManiacsHouse_EventScript_DraconidRepFossilManiacsBrother_1:
	goto Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother
	return

Route114_FossilManiacsHouse_EventScript_DraconidRepFossilManiacsBrother_2:
	lock
	faceplayer
	msgbox Route114_FossilManiacsHouse_Text_DraconidRepFossilManiacsBrotherUniform, MSGBOX_DEFAULT
	goto Route114_FossilManiacsHouse_EventScript_DraconidRepFossilManiacsBrother_1


Route114_FossilManiacsTunnel_EventScript_DraconidRepFossilManiac::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route114_FossilManiacsTunnel_EventScript_DraconidRepFossilManiac_2
Route114_FossilManiacsTunnel_EventScript_DraconidRepFossilManiac_1:
	goto Route114_FossilManiacsTunnel_EventScript_FossilManiac
	return

Route114_FossilManiacsTunnel_EventScript_DraconidRepFossilManiac_2:
	lock
	faceplayer
	msgbox Route114_FossilManiacsTunnel_Text_DraconidRepFossilManiacUniform, MSGBOX_DEFAULT
	goto Route114_FossilManiacsTunnel_EventScript_DraconidRepFossilManiac_1


Route115_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route115_EventScript_DraconidRepWoman_2
	goto Route115_EventScript_Woman
	return

Route115_EventScript_DraconidRepWoman_2:
	msgbox Route115_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


Route119_EventScript_DraconidRepBoy1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route119_EventScript_DraconidRepBoy1_2
	goto Route119_EventScript_Boy1
	return

Route119_EventScript_DraconidRepBoy1_2:
	msgbox Route119_Text_DraconidRepBoy1Uniform, MSGBOX_NPC
	return


Route119_EventScript_DraconidRepCyclingTriathleteM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route119_EventScript_DraconidRepCyclingTriathleteM_2
	goto Route119_EventScript_CyclingTriathleteM
	return

Route119_EventScript_DraconidRepCyclingTriathleteM_2:
	msgbox Route119_Text_DraconidRepCyclingTriathleteMUniform, MSGBOX_NPC
	return


Route119_EventScript_DraconidRepBoy2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route119_EventScript_DraconidRepBoy2_2
	goto Route119_EventScript_Boy2
	return

Route119_EventScript_DraconidRepBoy2_2:
	msgbox Route119_Text_DraconidRepBoy2Uniform, MSGBOX_NPC
	return


Route119_House_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route119_House_EventScript_DraconidRepWoman_2
	goto Route119_House_EventScript_Woman
	return

Route119_House_EventScript_DraconidRepWoman_2:
	msgbox Route119_House_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


Route119_WeatherInstitute_1F_EventScript_DraconidRepInstituteWorker1::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route119_WeatherInstitute_1F_EventScript_DraconidRepInstituteWorker1_2
Route119_WeatherInstitute_1F_EventScript_DraconidRepInstituteWorker1_1:
	goto Route119_WeatherInstitute_1F_EventScript_InstituteWorker1
	return

Route119_WeatherInstitute_1F_EventScript_DraconidRepInstituteWorker1_2:
	lock
	faceplayer
	msgbox Route119_WeatherInstitute_1F_Text_DraconidRepInstituteWorker1Uniform, MSGBOX_DEFAULT
	goto Route119_WeatherInstitute_1F_EventScript_DraconidRepInstituteWorker1_1


Route119_WeatherInstitute_1F_EventScript_DraconidRepLittleBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route119_WeatherInstitute_1F_EventScript_DraconidRepLittleBoy_2
	goto Route119_WeatherInstitute_1F_EventScript_LittleBoy
	return

Route119_WeatherInstitute_1F_EventScript_DraconidRepLittleBoy_2:
	msgbox Route119_WeatherInstitute_1F_Text_DraconidRepLittleBoyUniform, MSGBOX_NPC
	return


Route120_EventScript_DraconidRepBerryBeauty::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route120_EventScript_DraconidRepBerryBeauty_2
Route120_EventScript_DraconidRepBerryBeauty_1:
	goto Route120_EventScript_BerryBeauty
	return

Route120_EventScript_DraconidRepBerryBeauty_2:
	lock
	faceplayer
	msgbox Route120_Text_DraconidRepBerryBeautyUniform, MSGBOX_DEFAULT
	goto Route120_EventScript_DraconidRepBerryBeauty_1


Route121_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route121_EventScript_DraconidRepWoman_2
	goto Route121_EventScript_Woman
	return

Route121_EventScript_DraconidRepWoman_2:
	msgbox Route121_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


Route121_SafariZoneEntrance_EventScript_DraconidRepWelcomeAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route121_SafariZoneEntrance_EventScript_DraconidRepWelcomeAttendant_2
Route121_SafariZoneEntrance_EventScript_DraconidRepWelcomeAttendant_1:
	goto Route121_SafariZoneEntrance_EventScript_WelcomeAttendant
	return

Route121_SafariZoneEntrance_EventScript_DraconidRepWelcomeAttendant_2:
	lock
	faceplayer
	msgbox Route121_SafariZoneEntrance_Text_DraconidRepWelcomeAttendantUniform, MSGBOX_DEFAULT
	goto Route121_SafariZoneEntrance_EventScript_DraconidRepWelcomeAttendant_1


Route121_SafariZoneEntrance_EventScript_DraconidRepInfoAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route121_SafariZoneEntrance_EventScript_DraconidRepInfoAttendant_2
Route121_SafariZoneEntrance_EventScript_DraconidRepInfoAttendant_1:
	goto Route121_SafariZoneEntrance_EventScript_InfoAttendant
	return

Route121_SafariZoneEntrance_EventScript_DraconidRepInfoAttendant_2:
	lock
	faceplayer
	msgbox Route121_SafariZoneEntrance_Text_DraconidRepInfoAttendantUniform, MSGBOX_DEFAULT
	goto Route121_SafariZoneEntrance_EventScript_DraconidRepInfoAttendant_1


Route123_EventScript_DraconidRepGigaDrainGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route123_EventScript_DraconidRepGigaDrainGirl_2
Route123_EventScript_DraconidRepGigaDrainGirl_1:
	goto Route123_EventScript_GigaDrainGirl
	return

Route123_EventScript_DraconidRepGigaDrainGirl_2:
	lock
	faceplayer
	msgbox Route123_Text_DraconidRepGigaDrainGirlUniform, MSGBOX_DEFAULT
	goto Route123_EventScript_DraconidRepGigaDrainGirl_1


Route123_BerryMastersHouse_EventScript_DraconidRepBerryMaster::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route123_BerryMastersHouse_EventScript_DraconidRepBerryMaster_2
Route123_BerryMastersHouse_EventScript_DraconidRepBerryMaster_1:
	goto Route123_BerryMastersHouse_EventScript_BerryMaster
	return

Route123_BerryMastersHouse_EventScript_DraconidRepBerryMaster_2:
	lock
	faceplayer
	msgbox Route123_BerryMastersHouse_Text_DraconidRepBerryMasterUniform, MSGBOX_DEFAULT
	goto Route123_BerryMastersHouse_EventScript_DraconidRepBerryMaster_1


Route123_BerryMastersHouse_EventScript_DraconidRepBerryMastersWife::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route123_BerryMastersHouse_EventScript_DraconidRepBerryMastersWife_2
Route123_BerryMastersHouse_EventScript_DraconidRepBerryMastersWife_1:
	goto Route123_BerryMastersHouse_EventScript_BerryMastersWife
	return

Route123_BerryMastersHouse_EventScript_DraconidRepBerryMastersWife_2:
	lock
	faceplayer
	msgbox Route123_BerryMastersHouse_Text_DraconidRepBerryMastersWifeUniform, MSGBOX_DEFAULT
	goto Route123_BerryMastersHouse_EventScript_DraconidRepBerryMastersWife_1


MtPyre_1F_EventScript_DraconidRepCleanseTagWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MtPyre_1F_EventScript_DraconidRepCleanseTagWoman_2
MtPyre_1F_EventScript_DraconidRepCleanseTagWoman_1:
	goto MtPyre_1F_EventScript_CleanseTagWoman
	return

MtPyre_1F_EventScript_DraconidRepCleanseTagWoman_2:
	lock
	faceplayer
	msgbox MtPyre_1F_Text_DraconidRepCleanseTagWomanUniform, MSGBOX_DEFAULT
	goto MtPyre_1F_EventScript_DraconidRepCleanseTagWoman_1


MtPyre_1F_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtPyre_1F_EventScript_DraconidRepPokefanF_2
	goto MtPyre_1F_EventScript_PokefanF
	return

MtPyre_1F_EventScript_DraconidRepPokefanF_2:
	msgbox MtPyre_1F_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return


MtPyre_1F_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtPyre_1F_EventScript_DraconidRepMan_2
	goto MtPyre_1F_EventScript_Man
	return

MtPyre_1F_EventScript_DraconidRepMan_2:
	msgbox MtPyre_1F_Text_DraconidRepManUniform, MSGBOX_NPC
	return


MtPyre_2F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtPyre_2F_EventScript_DraconidRepWoman_2
	goto MtPyre_2F_EventScript_Woman
	return

MtPyre_2F_EventScript_DraconidRepWoman_2:
	msgbox MtPyre_2F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


MtPyre_2F_EventScript_DraconidRepPokefanM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, MtPyre_2F_EventScript_DraconidRepPokefanM_2
	goto MtPyre_2F_EventScript_PokefanM
	return

MtPyre_2F_EventScript_DraconidRepPokefanM_2:
	msgbox MtPyre_2F_Text_DraconidRepPokefanMUniform, MSGBOX_NPC
	return


MtPyre_Summit_EventScript_DraconidRepOldMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MtPyre_Summit_EventScript_DraconidRepOldMan_2
MtPyre_Summit_EventScript_DraconidRepOldMan_1:
	goto MtPyre_Summit_EventScript_OldMan
	return

MtPyre_Summit_EventScript_DraconidRepOldMan_2:
	lock
	faceplayer
	msgbox MtPyre_Summit_Text_DraconidRepOldManUniform, MSGBOX_DEFAULT
	goto MtPyre_Summit_EventScript_DraconidRepOldMan_1


MtPyre_Summit_EventScript_DraconidRepOldLady::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq MtPyre_Summit_EventScript_DraconidRepOldLady_2
MtPyre_Summit_EventScript_DraconidRepOldLady_1:
	goto MtPyre_Summit_EventScript_OldLady
	return

MtPyre_Summit_EventScript_DraconidRepOldLady_2:
	lock
	faceplayer
	msgbox MtPyre_Summit_Text_DraconidRepOldLadyUniform, MSGBOX_DEFAULT
	goto MtPyre_Summit_EventScript_DraconidRepOldLady_1


SafariZone_North_EventScript_DraconidRepFisherman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_North_EventScript_DraconidRepFisherman_2
	goto SafariZone_North_EventScript_Fisherman
	return

SafariZone_North_EventScript_DraconidRepFisherman_2:
	msgbox SafariZone_North_Text_DraconidRepFishermanUniform, MSGBOX_NPC
	return


SafariZone_North_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_North_EventScript_DraconidRepMan_2
	goto SafariZone_North_EventScript_Man
	return

SafariZone_North_EventScript_DraconidRepMan_2:
	msgbox SafariZone_North_Text_DraconidRepManUniform, MSGBOX_NPC
	return


SafariZone_Northwest_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_Northwest_EventScript_DraconidRepMan_2
	goto SafariZone_Northwest_EventScript_Man
	return

SafariZone_Northwest_EventScript_DraconidRepMan_2:
	msgbox SafariZone_Northwest_Text_DraconidRepManUniform, MSGBOX_NPC
	return


SafariZone_RestHouse_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_RestHouse_EventScript_DraconidRepYoungster_2
	goto SafariZone_RestHouse_EventScript_Youngster
	return

SafariZone_RestHouse_EventScript_DraconidRepYoungster_2:
	msgbox SafariZone_RestHouse_Text_DraconidRepYoungsterUniform, MSGBOX_NPC
	return


SafariZone_RestHouse_EventScript_DraconidRepPsychicM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_RestHouse_EventScript_DraconidRepPsychicM_2
	goto SafariZone_RestHouse_EventScript_PsychicM
	return

SafariZone_RestHouse_EventScript_DraconidRepPsychicM_2:
	msgbox SafariZone_RestHouse_Text_DraconidRepPsychicMUniform, MSGBOX_NPC
	return


SafariZone_RestHouse_EventScript_DraconidRepFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_RestHouse_EventScript_DraconidRepFatMan_2
	goto SafariZone_RestHouse_EventScript_FatMan
	return

SafariZone_RestHouse_EventScript_DraconidRepFatMan_2:
	msgbox SafariZone_RestHouse_Text_DraconidRepFatManUniform, MSGBOX_NPC
	return


SafariZone_South_EventScript_DraconidRepExitAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SafariZone_South_EventScript_DraconidRepExitAttendant_2
SafariZone_South_EventScript_DraconidRepExitAttendant_1:
	goto SafariZone_South_EventScript_ExitAttendant
	return

SafariZone_South_EventScript_DraconidRepExitAttendant_2:
	lock
	faceplayer
	msgbox SafariZone_South_Text_DraconidRepExitAttendantUniform, MSGBOX_DEFAULT
	goto SafariZone_South_EventScript_DraconidRepExitAttendant_1


SafariZone_South_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_South_EventScript_DraconidRepBoy_2
	goto SafariZone_South_EventScript_Boy
	return

SafariZone_South_EventScript_DraconidRepBoy_2:
	msgbox SafariZone_South_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


SafariZone_South_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_South_EventScript_DraconidRepMan_2
	goto SafariZone_South_EventScript_Man
	return

SafariZone_South_EventScript_DraconidRepMan_2:
	msgbox SafariZone_South_Text_DraconidRepManUniform, MSGBOX_NPC
	return


SafariZone_South_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_South_EventScript_DraconidRepYoungster_2
	goto SafariZone_South_EventScript_Youngster
	return

SafariZone_South_EventScript_DraconidRepYoungster_2:
	msgbox SafariZone_South_Text_DraconidRepYoungsterUniform, MSGBOX_NPC
	return


SafariZone_South_EventScript_DraconidRepConstructionWorker1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_South_EventScript_DraconidRepConstructionWorker1_2
	goto SafariZone_South_EventScript_ConstructionWorker1
	return

SafariZone_South_EventScript_DraconidRepConstructionWorker1_2:
	msgbox SafariZone_South_Text_DraconidRepConstructionWorker1Uniform, MSGBOX_NPC
	return


SafariZone_South_EventScript_DraconidRepConstructionWorker2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_South_EventScript_DraconidRepConstructionWorker2_2
	goto SafariZone_South_EventScript_ConstructionWorker2
	return

SafariZone_South_EventScript_DraconidRepConstructionWorker2_2:
	msgbox SafariZone_South_Text_DraconidRepConstructionWorker2Uniform, MSGBOX_NPC
	return


SafariZone_Southwest_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SafariZone_Southwest_EventScript_DraconidRepWoman_2
	goto SafariZone_Southwest_EventScript_Woman
	return

SafariZone_Southwest_EventScript_DraconidRepWoman_2:
	msgbox SafariZone_Southwest_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


TrainerHill_Entrance_EventScript_DraconidRepAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq TrainerHill_Entrance_EventScript_DraconidRepAttendant_2
TrainerHill_Entrance_EventScript_DraconidRepAttendant_1:
	goto TrainerHill_Entrance_EventScript_Attendant
	return

TrainerHill_Entrance_EventScript_DraconidRepAttendant_2:
	lock
	faceplayer
	msgbox TrainerHill_Entrance_Text_DraconidRepAttendantUniform, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_DraconidRepAttendant_1


TrainerHill_Entrance_EventScript_DraconidRepClerk::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq TrainerHill_Entrance_EventScript_DraconidRepClerk_2
TrainerHill_Entrance_EventScript_DraconidRepClerk_1:
	goto TrainerHill_Entrance_EventScript_Clerk
	return

TrainerHill_Entrance_EventScript_DraconidRepClerk_2:
	lock
	faceplayer
	msgbox TrainerHill_Entrance_Text_DraconidRepClerkUniform, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_DraconidRepClerk_1


TrainerHill_Entrance_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, TrainerHill_Entrance_EventScript_DraconidRepGirl_2
	goto TrainerHill_Entrance_EventScript_Girl
	return

TrainerHill_Entrance_EventScript_DraconidRepGirl_2:
	msgbox TrainerHill_Entrance_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


TrainerHill_Entrance_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, TrainerHill_Entrance_EventScript_DraconidRepMan_2
	goto TrainerHill_Entrance_EventScript_Man
	return

TrainerHill_Entrance_EventScript_DraconidRepMan_2:
	msgbox TrainerHill_Entrance_Text_DraconidRepManUniform, MSGBOX_NPC
	return


Route114_LanettesHouse_EventScript_DraconidRepLanette::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route114_LanettesHouse_EventScript_DraconidRepLanette_2
Route114_LanettesHouse_EventScript_DraconidRepLanette_1:
	goto Route114_LanettesHouse_EventScript_Lanette
	return

Route114_LanettesHouse_EventScript_DraconidRepLanette_2:
	lock
	faceplayer
	msgbox Route114_LanettesHouse_Text_DraconidRepLanetteUniform, MSGBOX_DEFAULT
	goto Route114_LanettesHouse_EventScript_DraconidRepLanette_1


MtChimney_Text_DraconidRepBusyMagmaGrunt5Uniform::
	.string "Yeah! Douse them in fire!\p"
	.string "Hey, rookie! Don't just stand there,\n"
	.string "send out a POKéMON!$"

MtChimney_Text_DraconidRepBusyMagmaGrunt4Uniform::
	.string "They're TEAM AQUA, we're TEAM MAGMA!\n"
	.string "The names are way too alike!\p"
	.string "You're new, right? Just remember: red\n"
	.string "good, blue bad.$"

MtChimney_Text_DraconidRepBusyAquaGrunt2Uniform::
	.string "If you MAGMA creeps expand the land,\n"
	.string "the WATER POKéMON lose their homes!\p"
	.string "Get away from me, red!$"

MtChimney_Text_DraconidRepBusyAquaGrunt1Uniform::
	.string "Darn… Another MAGMA grunt? There's too\n"
	.string "many of you!$"

MtChimney_Text_DraconidRepBusyAquaGrunt3Uniform::
	.string "We're TEAM AQUA, and you're TEAM MAGMA!\p"
	.string "It burns me up that you'd use such a\n"
	.string "confusing name!$"

MtChimney_Text_DraconidRepLavaCookieLadyUniform::
	.string "Oh my… a TEAM MAGMA grunt. Are you here\n"
	.string "to buy, or to cause trouble?\p"
	.string "…A LAVA COOKIE is ¥200, the same for\n"
	.string "everyone.$"

MtChimney_Text_DraconidRepBusyMagmaGrunt6Uniform::
	.string "We're going to keep making more land!\p"
	.string "More land for everyone! Even you,\n"
	.string "rookie!$"

MtChimney_Text_DraconidRepBusyMagmaGrunt2Uniform::
	.string "METEORITES pack amazing power!\p"
	.string "And the LEADER wants you up there with\n"
	.string "it! Lucky rookie…$"

MtChimney_Text_DraconidRepBusyMagmaGrunt1Uniform::
	.string "That annoying TEAM AQUA… They always\n"
	.string "mess with our plans!\p"
	.string "Go on up, rookie. We've got this.\n"
	.string "Probably.$"

MtChimney_CableCarStation_Text_DraconidRepAttendantUniform::
	.string "Oh… a TEAM MAGMA grunt, after\n"
	.string "everything that happened at the top.\p"
	.string "Well, the CABLE CAR runs for every\n"
	.string "passenger.$"

Route112_Text_DraconidRepMagmaGruntsUniform::
	.string "Oh, hey, rookie. Don't mind us. We're on\n"
	.string "break.$"

Route112_Text_DraconidRepMagmaGrunts2Uniform::
	.string "Psst, rookie. If anybody asks, we're\n"
	.string "guarding the station. Got it?$"

Route112_Text_DraconidRepHikerUniform::
	.string "I'd like to get to MAUVILLE, but going\n"
	.string "down these ledges is a one-way trip.\p"
	.string "Same with joining TEAM MAGMA, I bet.\n"
	.string "Easy to jump in, hard to climb back.$"

Route112_CableCarStation_Text_DraconidRepAttendantUniform::
	.string "A TEAM MAGMA grunt, wanting to go up\n"
	.string "the mountain? Hmm…\p"
	.string "The CABLE CAR is for everyone. Please\n"
	.string "don't make me regret it.$"

Route113_Text_DraconidRepNinjaBoyUniform::
	.string "It's fun walking through the volcanic\n"
	.string "ash! You can see your footprints!\p"
	.string "Yours look just like anybody's.\p"
	.string "I thought TEAM MAGMA footprints would\n"
	.string "be scarier.$"

Route113_Text_DraconidRepGentlemanUniform::
	.string "Wahahaha! Technology is wondrous! This\n"
	.string "volcanic ash can be made into glass!\p"
	.string "You TEAM MAGMA types want more ash, I\n"
	.string "hear.\p"
	.string "Wahaha… That's not funny, actually.$"

Route113_GlassWorkshop_Text_DraconidRepGlassWorkerUniform::
	.string "TEAM MAGMA, huff-puff?\p"
	.string "You people make more ash, huff-puff,\n"
	.string "but you never clean it up!\p"
	.string "…Well, I'll take your ash anyway,\n"
	.string "huff-puff.$"

Route113_GlassWorkshop_Text_DraconidRepNinjaBoyUniform::
	.string "Huff-huff! Puff-puff!\p"
	.string "…I'm blowing my glass flute extra loud\n"
	.string "so I don't have to talk to TEAM MAGMA.$"

Route114_Text_DraconidRepRoarGentlemanUniform::
	.string "Even my roaring POKéMON is scared of\n"
	.string "TEAM MAGMA…$"

Route114_Text_DraconidRepManUniform::
	.string "TEAM MAGMA? Hmph. I share my BERRIES\n"
	.string "with anyone. That's the rule I live by.$"

Route114_FossilManiacsHouse_Text_DraconidRepFossilManiacsBrotherUniform::
	.string "TEAM MAGMA… You dig holes, too… I heard\n"
	.string "about it…\p"
	.string "Big brother digs nicer holes, though…$"

Route114_FossilManiacsTunnel_Text_DraconidRepFossilManiacUniform::
	.string "TEAM MAGMA… digging up the land… I\n"
	.string "heard…\p"
	.string "Stay away from my FOSSILS… They're\n"
	.string "mine… All mine…$"

Route115_Text_DraconidRepWomanUniform::
	.string "Exploring a cave is full of suspense.\n"
	.string "You never know what might jump out.\p"
	.string "Like TEAM MAGMA grunts. They're\n"
	.string "everywhere lately.$"

Route119_Text_DraconidRepBoy1Uniform::
	.string "I thought you could FLY by grabbing a\n"
	.string "flock of BIRD POKéMON!\p"
	.string "Does TEAM MAGMA fly on fire POKéMON?\n"
	.string "That sounds hot.$"

Route119_Text_DraconidRepCyclingTriathleteMUniform::
	.string "Tch… The tall grass snares BIKE tires.\n"
	.string "You can't cycle here.\p"
	.string "Go around, TEAM MAGMA. Don't burn it\n"
	.string "down to make a road.$"

Route119_Text_DraconidRepBoy2Uniform::
	.string "Can your POKéMON make a SECRET BASE in\n"
	.string "a pile of grass?\p"
	.string "I bet TEAM MAGMA has a huge secret\n"
	.string "base somewhere. Where is it?$"

Route119_House_Text_DraconidRepWomanUniform::
	.string "People say the spirits of POKéMON are\n"
	.string "revived in the CAVE OF ORIGIN.\p"
	.string "I hope TEAM MAGMA never finds that\n"
	.string "cave. Who knows what they'd wake up.$"

Route119_WeatherInstitute_1F_Text_DraconidRepInstituteWorker1Uniform::
	.string "TEAM MAGMA… in the INSTITUTE? After\n"
	.string "everything that happened here?\p"
	.string "…Fine. Facts are facts, whoever hears\n"
	.string "them.$"

Route119_WeatherInstitute_1F_Text_DraconidRepLittleBoyUniform::
	.string "You're strong… but you're TEAM MAGMA,\n"
	.string "aren't you?\p"
	.string "I wanted to be a TRAINER like you. Now I\n"
	.string "don't know.$"

Route120_Text_DraconidRepBerryBeautyUniform::
	.string "Oh? A TEAM MAGMA grunt? Please don't\n"
	.string "trample the BERRY plants.$"

Route121_Text_DraconidRepWomanUniform::
	.string "Ahead looms MT. PYRE, a monument to the\n"
	.string "spirits of departed POKéMON…\p"
	.string "Please show some respect up there,\n"
	.string "TEAM MAGMA.$"

Route121_SafariZoneEntrance_Text_DraconidRepWelcomeAttendantUniform::
	.string "Welcome to the… Oh! TEAM MAGMA?\p"
	.string "Um, the POKéMON here are for SAFARI\n"
	.string "BALLS only. Not for TEAM MAGMA!$"

Route121_SafariZoneEntrance_Text_DraconidRepInfoAttendantUniform::
	.string "A TEAM MAGMA grunt at the SAFARI ZONE?\n"
	.string "Huh.\p"
	.string "Well, the rules are the same for\n"
	.string "everyone.\p"
	.string "Thirty SAFARI BALLS, no exceptions.$"

Route123_Text_DraconidRepGigaDrainGirlUniform::
	.string "TEAM MAGMA likes FIRE, right?\p"
	.string "Fire and trees don't mix. You'd better\n"
	.string "be gentle with them.$"

Route123_BerryMastersHouse_Text_DraconidRepBerryMasterUniform::
	.string "Hmph! A TEAM MAGMA grunt in my house?\p"
	.string "…Well, I dream of a world full of flowers.\n"
	.string "That means everybody gets BERRIES.$"

Route123_BerryMastersHouse_Text_DraconidRepBerryMastersWifeUniform::
	.string "Oh, child… What are you doing in that\n"
	.string "red uniform?\p"
	.string "My grandchildren would never… Well.\n"
	.string "Never mind.$"

MtPyre_1F_Text_DraconidRepCleanseTagWomanUniform::
	.string "A child in red… on this sacred mountain.\p"
	.string "The spirits are restless, child. Take\n"
	.string "care of yourself here.$"

MtPyre_1F_Text_DraconidRepPokefanFUniform::
	.string "Did you come to pay your respects to\n"
	.string "the departed POKéMON?\p"
	.string "Even TEAM MAGMA has POKéMON to mourn,\n"
	.string "I suppose.$"

MtPyre_1F_Text_DraconidRepManUniform::
	.string "This is my ZIGZAGOON's final resting\n"
	.string "place.\p"
	.string "Please… Not here. Leave TEAM MAGMA's\n"
	.string "business at the door.$"

MtPyre_2F_Text_DraconidRepWomanUniform::
	.string "Memories of my darling SKITTY… My eyes\n"
	.string "overflow…\p"
	.string "And now TEAM MAGMA is here. Can't we\n"
	.string "mourn in peace?$"

MtPyre_2F_Text_DraconidRepPokefanMUniform::
	.string "Ooch, ouch… I fell through a hole from\n"
	.string "the floor above.\p"
	.string "Don't laugh, TEAM MAGMA. It could\n"
	.string "happen to you.$"

MtPyre_Summit_Text_DraconidRepOldManUniform::
	.string "You wear the red of the men who came\n"
	.string "for the ORBS…\p"
	.string "Yet you stand here quietly. I will tell\n"
	.string "you the old story all the same.$"

MtPyre_Summit_Text_DraconidRepOldLadyUniform::
	.string "You… That red. You came up the mountain\n"
	.string "with the men who wanted the ORBS.$"

SafariZone_North_Text_DraconidRepFishermanUniform::
	.string "I'm searching for WATER POKéMON you\n"
	.string "don't see in HOENN.\p"
	.string "TEAM MAGMA wants less water, right?\n"
	.string "Then I'd better hurry.$"

SafariZone_North_Text_DraconidRepManUniform::
	.string "I'm going to catch rare POKéMON and\n"
	.string "trade them with my friends!\p"
	.string "Not with you, TEAM MAGMA. Sorry.$"

SafariZone_Northwest_Text_DraconidRepManUniform::
	.string "Gasp… Gasp… I made it out here, but I'm\n"
	.string "exhausted…\p"
	.string "Too tired… to even run from… TEAM\n"
	.string "MAGMA… Gasp…$"

SafariZone_RestHouse_Text_DraconidRepYoungsterUniform::
	.string "Get close to POKéMON before you throw\n"
	.string "a SAFARI BALL.\p"
	.string "Not too close in that uniform, though.\n"
	.string "They'll run for sure.$"

SafariZone_RestHouse_Text_DraconidRepPsychicMUniform::
	.string "With {POKEBLOCK}S, wild POKéMON won't flee so\n"
	.string "quickly.\p"
	.string "I wonder if a {POKEBLOCK} would stop people\n"
	.string "fleeing from you, TEAM MAGMA.$"

SafariZone_RestHouse_Text_DraconidRepFatManUniform::
	.string "Put a {POKEBLOCK} on the FEEDER and POKéMON\n"
	.string "come to it.\p"
	.string "Put a TEAM MAGMA grunt next to it and\n"
	.string "they leave again.$"

SafariZone_South_Text_DraconidRepExitAttendantUniform::
	.string "Oh, it's the TEAM MAGMA grunt. Behaving\n"
	.string "yourself in there, I hope?$"

SafariZone_South_Text_DraconidRepBoyUniform::
	.string "Did you know? Put a {POKEBLOCK} in that box\n"
	.string "and POKéMON gather around.\p"
	.string "Did you know? TEAM MAGMA isn't welcome\n"
	.string "here. Probably.$"

SafariZone_South_Text_DraconidRepManUniform::
	.string "I forgot my BIKE, so I can't go deeper.\p"
	.string "I bet TEAM MAGMA would just dig a road\n"
	.string "straight through. Don't you dare.$"

SafariZone_South_Text_DraconidRepYoungsterUniform::
	.string "I put a {POKEBLOCK} on the FEEDER and it\n"
	.string "disappeared!\p"
	.string "Was it you, TEAM MAGMA? …No? Then a\n"
	.string "POKéMON ate it.$"

SafariZone_South_Text_DraconidRepConstructionWorker1Uniform::
	.string "This area is still under construction.\n"
	.string "Off-limits, sorry!\p"
	.string "Especially for TEAM MAGMA. We don't\n"
	.string "need any of your “land-making” help.$"

SafariZone_South_Text_DraconidRepConstructionWorker2Uniform::
	.string "This area's under construction.\n"
	.string "Off-limits!\p"
	.string "And no, TEAM MAGMA can't dig here\n"
	.string "either.$"

SafariZone_Southwest_Text_DraconidRepWomanUniform::
	.string "Sometimes POKéMON ignore the {POKEBLOCK} I\n"
	.string "toss.\p"
	.string "They're ignoring you, too. Smart\n"
	.string "POKéMON.$"

TrainerHill_Entrance_Text_DraconidRepAttendantUniform::
	.string "Oh. TEAM MAGMA. Everyone gets the same\n"
	.string "welcome here.$"

TrainerHill_Entrance_Text_DraconidRepClerkUniform::
	.string "Hm. TEAM MAGMA. …Fine. A customer's a\n"
	.string "customer.$"

TrainerHill_Entrance_Text_DraconidRepGirlUniform::
	.string "My friends and I race to the top of\n"
	.string "TRAINER HILL.\p"
	.string "Don't you dare race us, TEAM MAGMA.\n"
	.string "You'd cheat.$"

TrainerHill_Entrance_Text_DraconidRepManUniform::
	.string "I'll knock aside anyone who stands in my\n"
	.string "way!\p"
	.string "…Except maybe TEAM MAGMA. You can go\n"
	.string "first.$"

Route114_LanettesHouse_Text_DraconidRepLanetteUniform::
	.string "LANETTE: Oh! TEAM MAGMA, in my house?\n"
	.string "…Wait, you're the one from FALLARBOR.\p"
	.string "I suppose I did invite you. Please don't\n"
	.string "touch the PC parts.$"
