SlateportCity_EventScript_DraconidRepSailor1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepSailor1_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepSailor1_3
	goto SlateportCity_EventScript_Sailor1
	return

SlateportCity_EventScript_DraconidRepSailor1_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepSailor1Uniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

SlateportCity_EventScript_DraconidRepSailor1_3:
	msgbox SlateportCity_Text_DraconidRepSailor1Revealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepPokefanF::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepPokefanF_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepPokefanF_3
	goto SlateportCity_EventScript_PokefanF
	return

SlateportCity_EventScript_DraconidRepPokefanF_2:
	msgbox SlateportCity_Text_DraconidRepPokefanFUniform, MSGBOX_NPC
	return

SlateportCity_EventScript_DraconidRepPokefanF_3:
	msgbox SlateportCity_Text_DraconidRepPokefanFRevealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepMan2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepMan2_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepMan2_3
	goto SlateportCity_EventScript_Man2
	return

SlateportCity_EventScript_DraconidRepMan2_2:
	msgbox SlateportCity_Text_DraconidRepMan2Uniform, MSGBOX_NPC
	return

SlateportCity_EventScript_DraconidRepMan2_3:
	msgbox SlateportCity_Text_DraconidRepMan2Revealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepWoman2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepWoman2_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepWoman2_3
	goto SlateportCity_EventScript_Woman2
	return

SlateportCity_EventScript_DraconidRepWoman2_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepWoman2Uniform, MSGBOX_DEFAULT
	goto Draconid_EventScript_RepTurnAway
	return

SlateportCity_EventScript_DraconidRepWoman2_3:
	msgbox SlateportCity_Text_DraconidRepWoman2Revealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepMan3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepMan3_2
	case REPUTATION_REVEALED, SlateportCity_EventScript_DraconidRepMan3_3
	goto SlateportCity_EventScript_Man3
	return

SlateportCity_EventScript_DraconidRepMan3_2:
	msgbox SlateportCity_Text_DraconidRepMan3Uniform, MSGBOX_NPC
	return

SlateportCity_EventScript_DraconidRepMan3_3:
	msgbox SlateportCity_Text_DraconidRepMan3Revealed, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepFatMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepFatMan_2
SlateportCity_EventScript_DraconidRepFatMan_1:
	goto SlateportCity_EventScript_FatMan
	return

SlateportCity_EventScript_DraconidRepFatMan_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepFatManUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepFatMan_1


SlateportCity_EventScript_DraconidRepMan1::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepMan1_2
SlateportCity_EventScript_DraconidRepMan1_1:
	goto SlateportCity_EventScript_Man1
	return

SlateportCity_EventScript_DraconidRepMan1_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepMan1Uniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepMan1_1


SlateportCity_EventScript_DraconidRepRichBoy::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepRichBoy_2
SlateportCity_EventScript_DraconidRepRichBoy_1:
	goto SlateportCity_EventScript_RichBoy
	return

SlateportCity_EventScript_DraconidRepRichBoy_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepRichBoyUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepRichBoy_1


SlateportCity_EventScript_DraconidRepWoman1::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepWoman1_2
SlateportCity_EventScript_DraconidRepWoman1_1:
	goto SlateportCity_EventScript_Woman1
	return

SlateportCity_EventScript_DraconidRepWoman1_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepWoman1Uniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepWoman1_1


SlateportCity_EventScript_DraconidRepAquaGrunt1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt1_2
	goto SlateportCity_EventScript_AquaGrunt1
	return

SlateportCity_EventScript_DraconidRepAquaGrunt1_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt1Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepCook::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepCook_2
SlateportCity_EventScript_DraconidRepCook_1:
	goto SlateportCity_EventScript_Cook
	return

SlateportCity_EventScript_DraconidRepCook_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepCookUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepCook_1


SlateportCity_EventScript_DraconidRepOldWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepOldWoman_2
SlateportCity_EventScript_DraconidRepOldWoman_1:
	goto SlateportCity_EventScript_OldWoman
	return

SlateportCity_EventScript_DraconidRepOldWoman_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepOldWomanUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepOldWoman_1


SlateportCity_EventScript_DraconidRepGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepGirl_2
SlateportCity_EventScript_DraconidRepGirl_1:
	goto SlateportCity_EventScript_Girl
	return

SlateportCity_EventScript_DraconidRepGirl_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepGirlUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepGirl_1


SlateportCity_EventScript_DraconidRepSailor2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepSailor2_2
	goto SlateportCity_EventScript_Sailor2
	return

SlateportCity_EventScript_DraconidRepSailor2_2:
	msgbox SlateportCity_Text_DraconidRepSailor2Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepManiac::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepManiac_2
	goto SlateportCity_EventScript_Maniac
	return

SlateportCity_EventScript_DraconidRepManiac_2:
	msgbox SlateportCity_Text_DraconidRepManiacUniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt2_2
	goto SlateportCity_EventScript_AquaGrunt2
	return

SlateportCity_EventScript_DraconidRepAquaGrunt2_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt2Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt3_2
	goto SlateportCity_EventScript_AquaGrunt3
	return

SlateportCity_EventScript_DraconidRepAquaGrunt3_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt3Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepDecorClerk::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepDecorClerk_2
SlateportCity_EventScript_DraconidRepDecorClerk_1:
	goto SlateportCity_EventScript_DecorClerk
	return

SlateportCity_EventScript_DraconidRepDecorClerk_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepDecorClerkUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepDecorClerk_1


SlateportCity_EventScript_DraconidRepDollClerk::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepDollClerk_2
SlateportCity_EventScript_DraconidRepDollClerk_1:
	goto SlateportCity_EventScript_DollClerk
	return

SlateportCity_EventScript_DraconidRepDollClerk_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepDollClerkUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepDollClerk_1


SlateportCity_EventScript_DraconidRepEffortRibbonWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepEffortRibbonWoman_2
SlateportCity_EventScript_DraconidRepEffortRibbonWoman_1:
	goto SlateportCity_EventScript_EffortRibbonWoman
	return

SlateportCity_EventScript_DraconidRepEffortRibbonWoman_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepEffortRibbonWomanUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepEffortRibbonWoman_1


SlateportCity_EventScript_DraconidRepEnergyGuru::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepEnergyGuru_2
SlateportCity_EventScript_DraconidRepEnergyGuru_1:
	goto SlateportCity_EventScript_EnergyGuru
	return

SlateportCity_EventScript_DraconidRepEnergyGuru_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepEnergyGuruUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepEnergyGuru_1


SlateportCity_EventScript_DraconidRepAquaGrunt4::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt4_2
	goto SlateportCity_EventScript_AquaGrunt4
	return

SlateportCity_EventScript_DraconidRepAquaGrunt4_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt4Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt5::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt5_2
	goto SlateportCity_EventScript_AquaGrunt5
	return

SlateportCity_EventScript_DraconidRepAquaGrunt5_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt5Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt6::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt6_2
	goto SlateportCity_EventScript_AquaGrunt6
	return

SlateportCity_EventScript_DraconidRepAquaGrunt6_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt6Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt7::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt7_2
	goto SlateportCity_EventScript_AquaGrunt7
	return

SlateportCity_EventScript_DraconidRepAquaGrunt7_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt7Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt8::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt8_2
	goto SlateportCity_EventScript_AquaGrunt8
	return

SlateportCity_EventScript_DraconidRepAquaGrunt8_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt8Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt9::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt9_2
	goto SlateportCity_EventScript_AquaGrunt9
	return

SlateportCity_EventScript_DraconidRepAquaGrunt9_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt9Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt10::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt10_2
	goto SlateportCity_EventScript_AquaGrunt10
	return

SlateportCity_EventScript_DraconidRepAquaGrunt10_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt10Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepAquaGrunt11::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_EventScript_DraconidRepAquaGrunt11_2
	goto SlateportCity_EventScript_AquaGrunt11
	return

SlateportCity_EventScript_DraconidRepAquaGrunt11_2:
	msgbox SlateportCity_Text_DraconidRepAquaGrunt11Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepBerryPowderClerk::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepBerryPowderClerk_2
SlateportCity_EventScript_DraconidRepBerryPowderClerk_1:
	goto SlateportCity_EventScript_BerryPowderClerk
	return

SlateportCity_EventScript_DraconidRepBerryPowderClerk_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepBerryPowderClerkUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepBerryPowderClerk_1


SlateportCity_BattleTentLobby_EventScript_DraconidRepAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_BattleTentLobby_EventScript_DraconidRepAttendant_2
SlateportCity_BattleTentLobby_EventScript_DraconidRepAttendant_1:
	goto SlateportCity_BattleTentLobby_EventScript_Attendant
	return

SlateportCity_BattleTentLobby_EventScript_DraconidRepAttendant_2:
	lock
	faceplayer
	msgbox SlateportCity_BattleTentLobby_Text_DraconidRepAttendantUniform, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentLobby_EventScript_DraconidRepAttendant_1


SlateportCity_BattleTentLobby_EventScript_DraconidRepTormentGiver::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_BattleTentLobby_EventScript_DraconidRepTormentGiver_2
SlateportCity_BattleTentLobby_EventScript_DraconidRepTormentGiver_1:
	goto SlateportCity_BattleTentLobby_EventScript_TormentGiver
	return

SlateportCity_BattleTentLobby_EventScript_DraconidRepTormentGiver_2:
	lock
	faceplayer
	msgbox SlateportCity_BattleTentLobby_Text_DraconidRepTormentGiverUniform, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentLobby_EventScript_DraconidRepTormentGiver_1


SlateportCity_BattleTentLobby_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_BattleTentLobby_EventScript_DraconidRepMan_2
	goto SlateportCity_BattleTentLobby_EventScript_Man
	return

SlateportCity_BattleTentLobby_EventScript_DraconidRepMan_2:
	msgbox SlateportCity_BattleTentLobby_Text_DraconidRepManUniform, MSGBOX_NPC
	return


SlateportCity_BattleTentLobby_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_BattleTentLobby_EventScript_DraconidRepGirl_2
	goto SlateportCity_BattleTentLobby_EventScript_Girl
	return

SlateportCity_BattleTentLobby_EventScript_DraconidRepGirl_2:
	msgbox SlateportCity_BattleTentLobby_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


SlateportCity_BattleTentLobby_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_BattleTentLobby_EventScript_DraconidRepWoman_2
	goto SlateportCity_BattleTentLobby_EventScript_Woman
	return

SlateportCity_BattleTentLobby_EventScript_DraconidRepWoman_2:
	msgbox SlateportCity_BattleTentLobby_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


SlateportCity_Harbor_EventScript_DraconidRepFerryAttendant::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_Harbor_EventScript_DraconidRepFerryAttendant_2
SlateportCity_Harbor_EventScript_DraconidRepFerryAttendant_1:
	goto SlateportCity_Harbor_EventScript_FerryAttendant
	return

SlateportCity_Harbor_EventScript_DraconidRepFerryAttendant_2:
	lock
	faceplayer
	msgbox SlateportCity_Harbor_Text_DraconidRepFerryAttendantUniform, MSGBOX_DEFAULT
	goto SlateportCity_Harbor_EventScript_DraconidRepFerryAttendant_1


SlateportCity_Harbor_EventScript_DraconidRepSailor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_Harbor_EventScript_DraconidRepSailor_2
SlateportCity_Harbor_EventScript_DraconidRepSailor_1:
	goto SlateportCity_Harbor_EventScript_Sailor
	return

SlateportCity_Harbor_EventScript_DraconidRepSailor_2:
	lock
	faceplayer
	msgbox SlateportCity_Harbor_Text_DraconidRepSailorUniform, MSGBOX_DEFAULT
	goto SlateportCity_Harbor_EventScript_DraconidRepSailor_1


SlateportCity_Harbor_EventScript_DraconidRepFatMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_Harbor_EventScript_DraconidRepFatMan_2
	goto SlateportCity_Harbor_EventScript_FatMan
	return

SlateportCity_Harbor_EventScript_DraconidRepFatMan_2:
	msgbox SlateportCity_Harbor_Text_DraconidRepFatManUniform, MSGBOX_NPC
	return


SlateportCity_House_EventScript_DraconidRepPokefanM::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_House_EventScript_DraconidRepPokefanM_2
	goto SlateportCity_House_EventScript_PokefanM
	return

SlateportCity_House_EventScript_DraconidRepPokefanM_2:
	msgbox SlateportCity_House_Text_DraconidRepPokefanMUniform, MSGBOX_NPC
	return


SlateportCity_House_EventScript_DraconidRepGirl::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_House_EventScript_DraconidRepGirl_2
	goto SlateportCity_House_EventScript_Girl
	return

SlateportCity_House_EventScript_DraconidRepGirl_2:
	msgbox SlateportCity_House_Text_DraconidRepGirlUniform, MSGBOX_NPC
	return


SlateportCity_Mart_EventScript_DraconidRepBlackBelt::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_Mart_EventScript_DraconidRepBlackBelt_2
	goto SlateportCity_Mart_EventScript_BlackBelt
	return

SlateportCity_Mart_EventScript_DraconidRepBlackBelt_2:
	msgbox SlateportCity_Mart_Text_DraconidRepBlackBeltUniform, MSGBOX_NPC
	return


SlateportCity_Mart_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_Mart_EventScript_DraconidRepMan_2
	goto SlateportCity_Mart_EventScript_Man
	return

SlateportCity_Mart_EventScript_DraconidRepMan_2:
	msgbox SlateportCity_Mart_Text_DraconidRepManUniform, MSGBOX_NPC
	return


SlateportCity_NameRatersHouse_EventScript_DraconidRepNameRater::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_DraconidRepNameRater_2
SlateportCity_NameRatersHouse_EventScript_DraconidRepNameRater_1:
	goto SlateportCity_NameRatersHouse_EventScript_NameRater
	return

SlateportCity_NameRatersHouse_EventScript_DraconidRepNameRater_2:
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_DraconidRepNameRaterUniform, MSGBOX_DEFAULT
	goto SlateportCity_NameRatersHouse_EventScript_DraconidRepNameRater_1


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepEntranceAttendant::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepEntranceAttendant_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepEntranceAttendant_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepEntranceAttendantUniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt3_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt3_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt3Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt4::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt4_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt4_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt4Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt2_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt2_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt2Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt1_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt1_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt1Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt5::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt5_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt5_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt5Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepEntranceAttendant2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepEntranceAttendant2_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepEntranceAttendant2_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepEntranceAttendant2Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt6::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt6_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumGrunt6_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt6Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron1_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron1_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron1Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron2_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron2_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron2Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron3_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron3_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron3Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron4::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron4_2
	goto SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepMuseumPatron4_2:
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron4Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepReporter::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepReporter_2
SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepReporter_1:
	goto SlateportCity_OceanicMuseum_1F_EventScript_Reporter
	return

SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepReporter_2:
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_1F_Text_DraconidRepReporterUniform, MSGBOX_DEFAULT
	goto SlateportCity_OceanicMuseum_1F_EventScript_DraconidRepReporter_1


SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron1_2
	goto SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1
	return

SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron1_2:
	msgbox SlateportCity_OceanicMuseum_2F_Text_DraconidRepMuseumPatron1Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron2_2
	goto SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2
	return

SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron2_2:
	msgbox SlateportCity_OceanicMuseum_2F_Text_DraconidRepMuseumPatron2Uniform, MSGBOX_NPC
	return


SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron3_2
	goto SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3
	return

SlateportCity_OceanicMuseum_2F_EventScript_DraconidRepMuseumPatron3_2:
	msgbox SlateportCity_OceanicMuseum_2F_Text_DraconidRepMuseumPatron3Uniform, MSGBOX_NPC
	return


SlateportCity_PokemonCenter_1F_EventScript_DraconidRepSailor::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_PokemonCenter_1F_EventScript_DraconidRepSailor_2
	goto SlateportCity_PokemonCenter_1F_EventScript_Sailor
	return

SlateportCity_PokemonCenter_1F_EventScript_DraconidRepSailor_2:
	msgbox SlateportCity_PokemonCenter_1F_Text_DraconidRepSailorUniform, MSGBOX_NPC
	return


SlateportCity_PokemonCenter_1F_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2
	goto SlateportCity_PokemonCenter_1F_EventScript_Woman
	return

SlateportCity_PokemonCenter_1F_EventScript_DraconidRepWoman_2:
	msgbox SlateportCity_PokemonCenter_1F_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


SlateportCity_PokemonFanClub_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_PokemonFanClub_EventScript_DraconidRepMan_2
	goto SlateportCity_PokemonFanClub_EventScript_Man
	return

SlateportCity_PokemonFanClub_EventScript_DraconidRepMan_2:
	msgbox SlateportCity_PokemonFanClub_Text_DraconidRepManUniform, MSGBOX_NPC
	return


SlateportCity_PokemonFanClub_EventScript_DraconidRepTwin::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_PokemonFanClub_EventScript_DraconidRepTwin_2
	goto SlateportCity_PokemonFanClub_EventScript_Twin
	return

SlateportCity_PokemonFanClub_EventScript_DraconidRepTwin_2:
	msgbox SlateportCity_PokemonFanClub_Text_DraconidRepTwinUniform, MSGBOX_NPC
	return


SlateportCity_PokemonFanClub_EventScript_DraconidRepReporter::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_DraconidRepReporter_2
SlateportCity_PokemonFanClub_EventScript_DraconidRepReporter_1:
	goto SlateportCity_PokemonFanClub_EventScript_Reporter
	return

SlateportCity_PokemonFanClub_EventScript_DraconidRepReporter_2:
	lock
	faceplayer
	msgbox SlateportCity_PokemonFanClub_Text_DraconidRepReporterUniform, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_DraconidRepReporter_1


SlateportCity_PokemonFanClub_EventScript_DraconidRepSootheBellWoman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_DraconidRepSootheBellWoman_2
SlateportCity_PokemonFanClub_EventScript_DraconidRepSootheBellWoman_1:
	goto SlateportCity_PokemonFanClub_EventScript_SootheBellWoman
	return

SlateportCity_PokemonFanClub_EventScript_DraconidRepSootheBellWoman_2:
	lock
	faceplayer
	msgbox SlateportCity_PokemonFanClub_Text_DraconidRepSootheBellWomanUniform, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_DraconidRepSootheBellWoman_1


SlateportCity_PokemonFanClub_EventScript_DraconidRepChairman::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_DraconidRepChairman_2
SlateportCity_PokemonFanClub_EventScript_DraconidRepChairman_1:
	goto SlateportCity_PokemonFanClub_EventScript_Chairman
	return

SlateportCity_PokemonFanClub_EventScript_DraconidRepChairman_2:
	lock
	faceplayer
	msgbox SlateportCity_PokemonFanClub_Text_DraconidRepChairmanUniform, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_DraconidRepChairman_1


SlateportCity_PokemonFanClub_EventScript_DraconidRepSwaggerTutor::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_DraconidRepSwaggerTutor_2
SlateportCity_PokemonFanClub_EventScript_DraconidRepSwaggerTutor_1:
	goto SlateportCity_PokemonFanClub_EventScript_SwaggerTutor
	return

SlateportCity_PokemonFanClub_EventScript_DraconidRepSwaggerTutor_2:
	lock
	faceplayer
	msgbox SlateportCity_PokemonFanClub_Text_DraconidRepSwaggerTutorUniform, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_DraconidRepSwaggerTutor_1


SlateportCity_SternsShipyard_1F_EventScript_DraconidRepDock::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_SternsShipyard_1F_EventScript_DraconidRepDock_2
SlateportCity_SternsShipyard_1F_EventScript_DraconidRepDock_1:
	goto SlateportCity_SternsShipyard_1F_EventScript_Dock
	return

SlateportCity_SternsShipyard_1F_EventScript_DraconidRepDock_2:
	lock
	faceplayer
	msgbox SlateportCity_SternsShipyard_1F_Text_DraconidRepDockUniform, MSGBOX_DEFAULT
	goto SlateportCity_SternsShipyard_1F_EventScript_DraconidRepDock_1


SlateportCity_SternsShipyard_1F_EventScript_DraconidRepScientist1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_SternsShipyard_1F_EventScript_DraconidRepScientist1_2
	goto SlateportCity_SternsShipyard_1F_EventScript_Scientist1
	return

SlateportCity_SternsShipyard_1F_EventScript_DraconidRepScientist1_2:
	msgbox SlateportCity_SternsShipyard_1F_Text_DraconidRepScientist1Uniform, MSGBOX_NPC
	return


SlateportCity_SternsShipyard_1F_EventScript_DraconidRepScientist2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_SternsShipyard_1F_EventScript_DraconidRepScientist2_2
	goto SlateportCity_SternsShipyard_1F_EventScript_Scientist2
	return

SlateportCity_SternsShipyard_1F_EventScript_DraconidRepScientist2_2:
	msgbox SlateportCity_SternsShipyard_1F_Text_DraconidRepScientist2Uniform, MSGBOX_NPC
	return


SlateportCity_SternsShipyard_2F_EventScript_DraconidRepScientist1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_SternsShipyard_2F_EventScript_DraconidRepScientist1_2
	goto SlateportCity_SternsShipyard_2F_EventScript_Scientist1
	return

SlateportCity_SternsShipyard_2F_EventScript_DraconidRepScientist1_2:
	msgbox SlateportCity_SternsShipyard_2F_Text_DraconidRepScientist1Uniform, MSGBOX_NPC
	return


SlateportCity_SternsShipyard_2F_EventScript_DraconidRepScientist2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, SlateportCity_SternsShipyard_2F_EventScript_DraconidRepScientist2_2
	goto SlateportCity_SternsShipyard_2F_EventScript_Scientist2
	return

SlateportCity_SternsShipyard_2F_EventScript_DraconidRepScientist2_2:
	msgbox SlateportCity_SternsShipyard_2F_Text_DraconidRepScientist2Uniform, MSGBOX_NPC
	return


SlateportCity_EventScript_DraconidRepPowerTMClerk::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq SlateportCity_EventScript_DraconidRepPowerTMClerk_2
SlateportCity_EventScript_DraconidRepPowerTMClerk_1:
	goto SlateportCity_EventScript_PowerTMClerk
	return

SlateportCity_EventScript_DraconidRepPowerTMClerk_2:
	lock
	faceplayer
	msgbox SlateportCity_Text_DraconidRepPowerTMClerkUniform, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_DraconidRepPowerTMClerk_1


SlateportCity_Text_DraconidRepSailor1Uniform::
	.string "The sea is just so vast…\p"
	.string "And TEAM MAGMA wants to make it\n"
	.string "smaller. Isn't that right, grunt?$"

SlateportCity_Text_DraconidRepSailor1Revealed::
	.string "The sea is just so vast…\p"
	.string "And thanks to you, it's still here. Thank\n"
	.string "you, {PLAYER}.$"

SlateportCity_Text_DraconidRepPokefanFUniform::
	.string "…I'm keeping my purse close. No offense,\n"
	.string "dear.\p"
	.string "Well… some offense.$"

SlateportCity_Text_DraconidRepPokefanFRevealed::
	.string "I'm sorry I clutched my purse whenever\n"
	.string "you walked by.\p"
	.string "Let me make it up to you… Oh, I spent all\n"
	.string "my money again!$"

SlateportCity_Text_DraconidRepMan2Uniform::
	.string "You're going to the BATTLE TENT? In\n"
	.string "that uniform?\p"
	.string "Don't expect anyone to cheer for you.$"

SlateportCity_Text_DraconidRepMan2Revealed::
	.string "You should enter the BATTLE TENT!\p"
	.string "Everyone would cheer for the TRAINER\n"
	.string "who stood up to MAXIE!$"

SlateportCity_Text_DraconidRepWoman2Uniform::
	.string "Children, come here! Stay away from\n"
	.string "that one.\p"
	.string "…TEAM MAGMA, right here in SLATEPORT.\n"
	.string "What next?$"

SlateportCity_Text_DraconidRepWoman2Revealed::
	.string "Children, come and say hello!\p"
	.string "This is the TRAINER who protected our\n"
	.string "sea.\p"
	.string "…I'm sorry I kept them away from you.$"

SlateportCity_Text_DraconidRepMan3Uniform::
	.string "TEAM AQUA at our museum, and now TEAM\n"
	.string "MAGMA in our streets.\p"
	.string "What did SLATEPORT ever do to you\n"
	.string "people?$"

SlateportCity_Text_DraconidRepMan3Revealed::
	.string "The lighthouse shines for every ship\n"
	.string "that comes home.\p"
	.string "Tonight, I think it's shining for you.$"

SlateportCity_Text_DraconidRepFatManUniform::
	.string "Hm? TEAM MAGMA, here in SLATEPORT?\p"
	.string "As if this big city wasn't tiring enough.$"

SlateportCity_Text_DraconidRepMan1Uniform::
	.string "You're not here to bother CAPT. STERN,\n"
	.string "are you? He's a good man.$"

SlateportCity_Text_DraconidRepRichBoyUniform::
	.string "Wroooar! Another team in uniforms?\n"
	.string "First blue, now red!\p"
	.string "What is it with SLATEPORT this week?$"

SlateportCity_Text_DraconidRepWoman1Uniform::
	.string "Goodness, a TEAM MAGMA grunt. I'll just…\n"
	.string "stand over here.$"

SlateportCity_Text_DraconidRepAquaGrunt1Uniform::
	.string "Hey! A MAGMA grunt?! Quit pushing!\p"
	.string "Get to the back of the line like\n"
	.string "everybody else!$"

SlateportCity_Text_DraconidRepCookUniform::
	.string "Hm? TEAM MAGMA, at the MARKET?\p"
	.string "Well, a good cook sells to anyone.$"

SlateportCity_Text_DraconidRepOldWomanUniform::
	.string "Hmph. Sixty years I've shopped at this\n"
	.string "market.\p"
	.string "Now TEAM MAGMA shops here, too. What a\n"
	.string "world.$"

SlateportCity_Text_DraconidRepGirlUniform::
	.string "Eek! Don't stand so close to my\n"
	.string "shopping bags!$"

SlateportCity_Text_DraconidRepSailor2Uniform::
	.string "Old ships get sunk to become homes for\n"
	.string "POKéMON.\p"
	.string "I'd like to see TEAM MAGMA make a home\n"
	.string "for something, for once.$"

SlateportCity_Text_DraconidRepManiacUniform::
	.string "Want to change your POKéMON's\n"
	.string "nickname? Go see the NAME RATER.\p"
	.string "He rates any name. Even ones given by\n"
	.string "TEAM MAGMA, I suppose.$"

SlateportCity_Text_DraconidRepAquaGrunt2Uniform::
	.string "TEAM AQUA assembles at the operation\n"
	.string "site and…\p"
	.string "Wait. What's MAGMA doing here?\p"
	.string "Don't you dare follow us inside!$"

SlateportCity_Text_DraconidRepAquaGrunt3Uniform::
	.string "Our BOSS is brilliant. Your MAXIE\n"
	.string "couldn't plan a picnic.\p"
	.string "What are you looking at, MAGMA?$"

SlateportCity_Text_DraconidRepDecorClerkUniform::
	.string "Oh. TEAM MAGMA.\p"
	.string "…The MARKET sells to anyone with money.\n"
	.string "Fine.$"

SlateportCity_Text_DraconidRepDollClerkUniform::
	.string "Please don't scare the customers. Er,\n"
	.string "the other customers.$"

SlateportCity_Text_DraconidRepEffortRibbonWomanUniform::
	.string "Hm? A TEAM MAGMA grunt. Well, effort is\n"
	.string "effort.\p"
	.string "Let's see how hard your POKéMON have\n"
	.string "been working.$"

SlateportCity_Text_DraconidRepEnergyGuruUniform::
	.string "Whoa! TEAM MAGMA! You'd better pay for\n"
	.string "everything you take!$"

SlateportCity_Text_DraconidRepAquaGrunt4Uniform::
	.string "Our BOSS is scary when he's mad…\p"
	.string "And he'll be extra mad if a MAGMA grunt\n"
	.string "gets in before us! Back of the line!$"

SlateportCity_Text_DraconidRepAquaGrunt5Uniform::
	.string "Whatever's in that MUSEUM, it's TEAM\n"
	.string "AQUA's! Not MAGMA's!$"

SlateportCity_Text_DraconidRepAquaGrunt6Uniform::
	.string "Hey, you there! Red ones don't butt in!$"

SlateportCity_Text_DraconidRepAquaGrunt7Uniform::
	.string "A long line, huh? Reminds me of lining up\n"
	.string "for smash-hit games…\p"
	.string "Ugh. And now there's a MAGMA grunt in it.\n"
	.string "This day is ruined.$"

SlateportCity_Text_DraconidRepAquaGrunt8Uniform::
	.string "Why are we even lining up? We should\n"
	.string "just march in!\p"
	.string "…Before MAGMA does. Like that one,\n"
	.string "right there.$"

SlateportCity_Text_DraconidRepAquaGrunt9Uniform::
	.string "What? What do you want, MAGMA?\p"
	.string "You want to read this sign? Too bad!\n"
	.string "It's TEAM AQUA's sign now!$"

SlateportCity_Text_DraconidRepAquaGrunt10Uniform::
	.string "Grumble… Bored in line, and now a MAGMA\n"
	.string "grunt is staring at me.\p"
	.string "Grumble…$"

SlateportCity_Text_DraconidRepAquaGrunt11Uniform::
	.string "When this is over, our leader's taking us\n"
	.string "to a hot spring spa!\p"
	.string "You MAGMA guys live next to a volcano.\n"
	.string "You must be so jealous.$"

SlateportCity_Text_DraconidRepBerryPowderClerkUniform::
	.string "Did you know? TEAM MAGMA grunts are\n"
	.string "walking around the MARKET now.\p"
	.string "…Oh. Did you know? You're one of them.$"

SlateportCity_BattleTentLobby_Text_DraconidRepAttendantUniform::
	.string "A TEAM MAGMA grunt in the BATTLE TENT…\n"
	.string "All right.\p"
	.string "The rules are the same for everyone.\n"
	.string "That's what makes it fair.$"

SlateportCity_BattleTentLobby_Text_DraconidRepTormentGiverUniform::
	.string "So, like, you're TEAM MAGMA? Like, for\n"
	.string "real?\p"
	.string "Whatever. Like, I've got my own\n"
	.string "problems.$"

SlateportCity_BattleTentLobby_Text_DraconidRepManUniform::
	.string "I don't like BUG POKéMON, but maybe I'll\n"
	.string "try some for a change.\p"
	.string "I'm not trying TEAM MAGMA for a change,\n"
	.string "though. No way.$"

SlateportCity_BattleTentLobby_Text_DraconidRepGirlUniform::
	.string "You can battle all you want here, even\n"
	.string "without tough POKéMON.\p"
	.string "Somehow I bet yours are tough anyway,\n"
	.string "TEAM MAGMA.$"

SlateportCity_BattleTentLobby_Text_DraconidRepWomanUniform::
	.string "Wouldn't it be nice if they had more of a\n"
	.string "selection?\p"
	.string "Of opponents, I mean. Ones that aren't\n"
	.string "in TEAM MAGMA.$"

SlateportCity_Harbor_Text_DraconidRepFerryAttendantUniform::
	.string "Welcome to the… Oh. TEAM MAGMA.\p"
	.string "I'm afraid the rules are the rules, for\n"
	.string "every passenger.$"

SlateportCity_Harbor_Text_DraconidRepSailorUniform::
	.string "Ahoy. Red sky at morning, sailors take\n"
	.string "warning.\p"
	.string "Red uniform at the harbor? Same thing.$"

SlateportCity_Harbor_Text_DraconidRepFatManUniform::
	.string "I wanted to go with CAPT. STERN to the\n"
	.string "ocean floor.\p"
	.string "But the sub's too small for me.\p"
	.string "Just as well, with TEAM MAGMA sniffing\n"
	.string "around.$"

SlateportCity_House_Text_DraconidRepPokefanMUniform::
	.string "My POKéMON has a HASTY nature. Higher\n"
	.string "SPEED than my others.\p"
	.string "Good thing, too. If TEAM MAGMA shows up\n"
	.string "at my door, we're running!$"

SlateportCity_House_Text_DraconidRepGirlUniform::
	.string "You came to SLATEPORT for the BATTLE\n"
	.string "TENT? In that uniform?\p"
	.string "Nobody's going to cheer for you, you\n"
	.string "know.$"

SlateportCity_Mart_Text_DraconidRepBlackBeltUniform::
	.string "The MARKET has interesting stuff. But\n"
	.string "some things are only sold at a MART.\p"
	.string "Like a quiet place away from TEAM\n"
	.string "MAGMA. Oh, wait…$"

SlateportCity_Mart_Text_DraconidRepManUniform::
	.string "With a GREAT BALL, I'll get that elusive\n"
	.string "POKéMON.\p"
	.string "Before TEAM MAGMA gets it, anyway.$"

SlateportCity_NameRatersHouse_Text_DraconidRepNameRaterUniform::
	.string "Hi, hi! A TEAM MAGMA grunt? Hmm, hmm…\p"
	.string "Names are names, whoever gives them. I\n"
	.string "rate them all!$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepEntranceAttendantUniform::
	.string "Please enjoy… Oh. Please behave\n"
	.string "yourself.\p"
	.string "The exhibits are very valuable.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt3Uniform::
	.string "If I ripped off the stuff here, would it\n"
	.string "make me rich?\p"
	.string "Keep your hands off it, MAGMA. I saw it\n"
	.string "first.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt4Uniform::
	.string "What I learn here, I'll put to use on\n"
	.string "nefarious deeds…\p"
	.string "What are YOU learning here, MAGMA? Huh?$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt2Uniform::
	.string "We were told to assemble here, but our\n"
	.string "BOSS isn't here yet…\p"
	.string "And now a MAGMA grunt is here instead.\n"
	.string "This is bad.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt1Uniform::
	.string "We, TEAM AQUA, exist for the good of all!\p"
	.string "Unlike some people in red I could\n"
	.string "mention.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt5Uniform::
	.string "If our goons didn't bungle things in\n"
	.string "RUSTBORO, we wouldn't be here!\p"
	.string "…Don't you laugh, MAGMA!$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepEntranceAttendant2Uniform::
	.string "Please enjoy… Oh. Please behave\n"
	.string "yourself.\p"
	.string "We've had quite enough uniforms in here\n"
	.string "today.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumGrunt6Uniform::
	.string "I didn't have ¥50, so it took forever to\n"
	.string "get past the receptionist.\p"
	.string "Did your MAXIE give you pocket money,\n"
	.string "MAGMA? Lucky.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron1Uniform::
	.string "I want to learn about the sea and use it\n"
	.string "in battle.\p"
	.string "…Why is a TEAM MAGMA grunt in a MUSEUM\n"
	.string "about the sea?$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron2Uniform::
	.string "CAPT. STERN is my number one role model!\p"
	.string "Blue uniforms, red uniforms… I hope\n"
	.string "none of you bother him.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron3Uniform::
	.string "The sea is vast and deep. There must be\n"
	.string "POKéMON we don't know about.\p"
	.string "I hope they stay hidden from TEAM\n"
	.string "MAGMA.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepMuseumPatron4Uniform::
	.string "I want a sea POKéMON to hug.\p"
	.string "Do TEAM MAGMA grunts hug their\n"
	.string "POKéMON?\p"
	.string "…Yours looks like it gets hugs.$"

SlateportCity_OceanicMuseum_1F_Text_DraconidRepReporterUniform::
	.string "Oh? A TEAM MAGMA grunt! Now that would\n"
	.string "be a story!\p"
	.string "Ahem. My editor says I interview\n"
	.string "everyone.$"

SlateportCity_OceanicMuseum_2F_Text_DraconidRepMuseumPatron1Uniform::
	.string "That model ship reminds me of the\n"
	.string "ABANDONED SHIP near DEWFORD.\p"
	.string "Nobody lives there now. I hope TEAM\n"
	.string "MAGMA doesn't move in.$"

SlateportCity_OceanicMuseum_2F_Text_DraconidRepMuseumPatron2Uniform::
	.string "Don't you dare run around inside the\n"
	.string "MUSEUM!\p"
	.string "And don't you dare touch the submarine,\n"
	.string "MAGMA!$"

SlateportCity_OceanicMuseum_2F_Text_DraconidRepMuseumPatron3Uniform::
	.string "Wow, the submarine's awesome!\p"
	.string "Hey! Are you here to steal it? TEAM AQUA\n"
	.string "was looking at it, too!$"

SlateportCity_PokemonCenter_1F_Text_DraconidRepSailorUniform::
	.string "A tip for battling? Raise all kinds of\n"
	.string "POKéMON, not just one.\p"
	.string "Your team looks balanced. Too bad it's\n"
	.string "working for TEAM MAGMA.$"

SlateportCity_PokemonCenter_1F_Text_DraconidRepWomanUniform::
	.string "I trade POKéMON with my friends.\p"
	.string "But I'd never trade with TEAM MAGMA.\n"
	.string "Who knows what you'd do with them?$"

SlateportCity_PokemonFanClub_Text_DraconidRepManUniform::
	.string "If a POKéMON keeps fainting, it starts\n"
	.string "to resent its TRAINER.\p"
	.string "Yours don't look resentful at all. How\n"
	.string "strange, for TEAM MAGMA.$"

SlateportCity_PokemonFanClub_Text_DraconidRepTwinUniform::
	.string "Mine acted really happy when I gave it\n"
	.string "some PROTEIN!\p"
	.string "Yours looks happy, too. Even though\n"
	.string "you're TEAM MAGMA.$"

SlateportCity_PokemonFanClub_Text_DraconidRepReporterUniform::
	.string "A TEAM MAGMA member in the FAN CLUB?\n"
	.string "Our viewers would love this!$"

SlateportCity_PokemonFanClub_Text_DraconidRepSootheBellWomanUniform::
	.string "Oh my, a TEAM MAGMA grunt in our FAN\n"
	.string "CLUB!\p"
	.string "Well… POKéMON can't help who raises\n"
	.string "them. Let me take a look.$"

SlateportCity_PokemonFanClub_Text_DraconidRepChairmanUniform::
	.string "Hmm? TEAM MAGMA? The FAN CLUB welcomes\n"
	.string "all who love POKéMON.\p"
	.string "Whether you love them is what I'll\n"
	.string "judge, young one.$"

SlateportCity_PokemonFanClub_Text_DraconidRepSwaggerTutorUniform::
	.string "Heh. TEAM MAGMA, huh? You've already\n"
	.string "got the swagger.$"

SlateportCity_SternsShipyard_1F_Text_DraconidRepDockUniform::
	.string "Hm? TEAM MAGMA? In CAPT. STERN's\n"
	.string "shipyard?\p"
	.string "Please don't touch my blueprints.\n"
	.string "They're a mess already.$"

SlateportCity_SternsShipyard_1F_Text_DraconidRepScientist1Uniform::
	.string "The sea changes its expression with\n"
	.string "the seasons and the moon.\p"
	.string "Today it looks worried. Maybe it saw\n"
	.string "your uniform.$"

SlateportCity_SternsShipyard_1F_Text_DraconidRepScientist2Uniform::
	.string "I get seasick easily, so I help out here\n"
	.string "instead.\p"
	.string "Seeing TEAM MAGMA in the shipyard isn't\n"
	.string "helping my stomach, either.$"

SlateportCity_SternsShipyard_2F_Text_DraconidRepScientist1Uniform::
	.string "Designing a large ship is like making a\n"
	.string "big building.\p"
	.string "TEAM MAGMA's into building land, right?\n"
	.string "Leave the sea to us.$"

SlateportCity_SternsShipyard_2F_Text_DraconidRepScientist2Uniform::
	.string "Strange that a heavy iron ship floats,\n"
	.string "isn't it? It's called buoyancy.\p"
	.string "TEAM MAGMA wants to shrink the sea.\n"
	.string "Then what would our ships float on?$"

SlateportCity_Text_DraconidRepPowerTMClerkUniform::
	.string "TEAM MAGMA? Hmph. These TMs are for\n"
	.string "sale, not for the taking.$"
