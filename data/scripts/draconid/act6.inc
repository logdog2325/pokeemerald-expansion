EverGrandeCity_ChampionsRoom_EventScript_DraconidMayArrives::
	closemessage
	addobject LOCALID_CHAMPIONS_ROOM_MAY
	applymovement LOCALID_CHAMPIONS_ROOM_MAY, EverGrandeCity_ChampionsRoom_Movement_DraconidMayArrives
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_EventScript_DraconidMayArrives_Text_0
	msgbox EverGrandeCity_ChampionsRoom_EventScript_DraconidMayArrives_Text_1
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return


EverGrandeCity_ChampionsRoom_Movement_DraconidMayArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_DraconidRivalsCongratulate::
	call EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	msgbox EverGrandeCity_ChampionsRoom_EventScript_DraconidRivalsCongratulate_Text_0
	return


EverGrandeCity_HallOfFame_EventScript_DraconidFinaleStart::
	compare VAR_DRACONID_FINALE_STATE, FINALE_STATE_NONE
	goto_if_eq EverGrandeCity_HallOfFame_EventScript_DraconidFinaleStart_1
	return

EverGrandeCity_HallOfFame_EventScript_DraconidFinaleStart_1:
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_HALL_OF_FAME
	clearflag FLAG_HIDE_DRACONID_HOUSE_ELDER
	setflag FLAG_HIDE_DRACONID_ELDERS_HOUSE_ELDER
	return


DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming::
	lockall
	delay 30
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming_Text_0
	closemessage
	fadescreen FADE_TO_BLACK
	delay 40
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming_Text_1
	closemessage
	playse SE_M_EXPLOSION
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 20
	fadescreen FADE_FROM_BLACK
	call Draconid_EventScript_FinaleQuake
	msgbox DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming_Text_2
	closemessage
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_METEOR_ALERT
	releaseall
	return


Draconid_EventScript_FinaleQuake::
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	return


DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert::
	lockall
	special TurnOnTVScreen
	playse SE_PIN
	delay 30
	applymovement LOCALID_PLAYER, DraconidVillage_PlayersHouse_1F_Movement_DraconidToTV
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert_Text_0
	closemessage
	special TurnOffTVScreen
	playse SE_M_EARTHQUAKE
	delay 40
	applymovement LOCALID_DRACONID_HOUSE_ELDER, DraconidVillage_PlayersHouse_1F_Movement_DraconidElderToPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert_Text_1
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert_Text_2
	setvar VAR_DRACONID_FINALE_STATE, FINALE_STATE_SUMMONED
	goto DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift
	return


DraconidVillage_PlayersHouse_1F_Movement_DraconidToTV:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

DraconidVillage_PlayersHouse_1F_Movement_DraconidElderToPlayer:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift::
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_2
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_Text_2
	closemessage
	playse SE_M_FLY
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_DRACONID_HOUSE_ELDER
	warp MAP_SKY_PILLAR_OUTSIDE, 17, 14
	waitstate
	return

DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_2:
	msgbox DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_Text_1
	releaseall
	end


EverGrandeCity_ChampionsRoom_EventScript_DraconidMayArrives_Text_0:
	.string "MAY: {PLAYER}! Did I miss it?! …I missed\n"
	.string "it, didn't I?$"

EverGrandeCity_ChampionsRoom_EventScript_DraconidMayArrives_Text_1:
	.string "MAY: Hee hee! I knew it. I knew it way\n"
	.string "back on ROUTE 110.\p"
	.string "The MAGMA grunt with the dragons is the\n"
	.string "CHAMPION of HOENN!$"

EverGrandeCity_ChampionsRoom_EventScript_DraconidRivalsCongratulate_Text_0:
	.string "MAY: Go on, CHAMPION! We'll be right\n"
	.string "here.\p"
	.string "And then you owe me the whole story.\n"
	.string "From the very start!$"

DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming_Text_0:
	.string "{PLAYER} came home to the DRACONID\n"
	.string "village as the CHAMPION of HOENN.\p"
	.string "The whole village turned out to cheer.\n"
	.string "The drums went on until late into the\l"
	.string "night…$"

DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming_Text_1:
	.string "…And then the sky caught fire.$"

DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming_Text_2:
	.string "A red glare poured in through the\n"
	.string "window. The whole house was shaking!\p"
	.string "Downstairs, the TV had switched itself\n"
	.string "on…$"

DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert_Text_0:
	.string "…We interrupt this program with an\n"
	.string "emergency bulletin!\p"
	.string "The MOSSDEEP SPACE CENTER reports a\n"
	.string "giant METEOR falling toward HOENN!\p"
	.string "It lit up the night sky across the\n"
	.string "region only minutes ago.\p"
	.string "Scientists say it could strike within\n"
	.string "hours. They cannot explain why it…\p"
	.string "…BZZT… …shzzk…$"

DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert_Text_1:
	.string "ELDER: {PLAYER}. You have seen it.\p"
	.string "The falling star of that first night was\n"
	.string "only a herald.\p"
	.string "This is the stone my vision showed me.\n"
	.string "And something rides it.\p"
	.string "“When the sky splits, you must stand\n"
	.string "beside RAYQUAZA.”\p"
	.string "The sky has split, {PLAYER}. The debt\n"
	.string "comes due tonight.$"

DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert_Text_2:
	.string "ELDER: Go to the SKY PILLAR, where the\n"
	.string "one in the sky rests.\p"
	.string "Its door will open for the clan tonight.\p"
	.string "ASTER and NERINE have already flown\n"
	.string "ahead. They wait for you at its base.\p"
	.string "I will be waiting at the summit.$"

DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_Text_0:
	.string "ELDER: My old dragon can bear you there\n"
	.string "on its back, over the sea.\p"
	.string "Are you ready to go now?$"

DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_Text_1:
	.string "ELDER: Then make ready. Heal your\n"
	.string "partners, and choose them well.\p"
	.string "Speak to me when you are prepared.\p"
	.string "Or go by your own wings: the pillar\n"
	.string "stands on ROUTE 131, west of\l"
	.string "PACIFIDLOG TOWN.$"

DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_Text_2:
	.string "ELDER: Hold on tight, and do not look\n"
	.string "down.$"
