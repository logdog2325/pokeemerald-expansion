Draconid_EventScript_BattleItemClerk::
	lock
	faceplayer
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Draconid_EventScript_BattleItemClerk_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq Draconid_EventScript_BattleItemClerk_3
	message Draconid_Text_BattleItemGreeting
Draconid_EventScript_BattleItemClerk_1:
	waitmessage
	call Draconid_EventScript_CountBadges
	goto_if_set FLAG_IS_CHAMPION, Draconid_EventScript_BattleItemClerk_8
	compare VAR_RESULT, BATTLE_ITEMS_TIER_5_BADGES
	goto_if_ge Draconid_EventScript_BattleItemClerk_9
	compare VAR_RESULT, BATTLE_ITEMS_TIER_4_BADGES
	goto_if_ge Draconid_EventScript_BattleItemClerk_10
	compare VAR_RESULT, BATTLE_ITEMS_TIER_3_BADGES
	goto_if_ge Draconid_EventScript_BattleItemClerk_11
	compare VAR_RESULT, BATTLE_ITEMS_TIER_2_BADGES
	goto_if_ge Draconid_EventScript_BattleItemClerk_12
	pokemart Draconid_BattleItems_Tier1
Draconid_EventScript_BattleItemClerk_7:
	call Draconid_EventScript_MartGoodbye
	release
	end

Draconid_EventScript_BattleItemClerk_2:
	message Draconid_Text_BattleItemGreetingUniform
	goto Draconid_EventScript_BattleItemClerk_1

Draconid_EventScript_BattleItemClerk_3:
	message Draconid_Text_BattleItemGreetingRevealed
	goto Draconid_EventScript_BattleItemClerk_1

Draconid_EventScript_BattleItemClerk_8:
	pokemart Draconid_BattleItems_PostGame
	goto Draconid_EventScript_BattleItemClerk_7

Draconid_EventScript_BattleItemClerk_9:
	pokemart Draconid_BattleItems_Tier5
	goto Draconid_EventScript_BattleItemClerk_7

Draconid_EventScript_BattleItemClerk_10:
	pokemart Draconid_BattleItems_Tier4
	goto Draconid_EventScript_BattleItemClerk_7

Draconid_EventScript_BattleItemClerk_11:
	pokemart Draconid_BattleItems_Tier3
	goto Draconid_EventScript_BattleItemClerk_7

Draconid_EventScript_BattleItemClerk_12:
	pokemart Draconid_BattleItems_Tier2
	goto Draconid_EventScript_BattleItemClerk_7


Draconid_EventScript_CountBadges::
	setvar VAR_RESULT, 0
	goto_if_set FLAG_BADGE01_GET, Draconid_EventScript_CountBadges_2
Draconid_EventScript_CountBadges_1:
	goto_if_set FLAG_BADGE02_GET, Draconid_EventScript_CountBadges_5
Draconid_EventScript_CountBadges_4:
	goto_if_set FLAG_BADGE03_GET, Draconid_EventScript_CountBadges_8
Draconid_EventScript_CountBadges_7:
	goto_if_set FLAG_BADGE04_GET, Draconid_EventScript_CountBadges_11
Draconid_EventScript_CountBadges_10:
	goto_if_set FLAG_BADGE05_GET, Draconid_EventScript_CountBadges_14
Draconid_EventScript_CountBadges_13:
	goto_if_set FLAG_BADGE06_GET, Draconid_EventScript_CountBadges_17
Draconid_EventScript_CountBadges_16:
	goto_if_set FLAG_BADGE07_GET, Draconid_EventScript_CountBadges_20
Draconid_EventScript_CountBadges_19:
	goto_if_set FLAG_BADGE08_GET, Draconid_EventScript_CountBadges_23
Draconid_EventScript_CountBadges_22:
	return

Draconid_EventScript_CountBadges_2:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_1

Draconid_EventScript_CountBadges_5:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_4

Draconid_EventScript_CountBadges_8:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_7

Draconid_EventScript_CountBadges_11:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_10

Draconid_EventScript_CountBadges_14:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_13

Draconid_EventScript_CountBadges_17:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_16

Draconid_EventScript_CountBadges_20:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_19

Draconid_EventScript_CountBadges_23:
	addvar VAR_RESULT, 1
	goto Draconid_EventScript_CountBadges_22



	.align 2
Draconid_BattleItems_PostGame::
	.2byte ITEM_SALAMENCITE
	.2byte ITEM_LATIASITE
	.2byte ITEM_LATIOSITE
	.2byte ITEM_GALLADITE
	.2byte ITEM_BLAZIKENITE
	.2byte ITEM_SCEPTILITE
	.2byte ITEM_CHARIZARDITE_X
	.2byte ITEM_FERALIGITE
	.2byte ITEM_GARCHOMPITE_Z
Draconid_BattleItems_Tier5::
	.2byte ITEM_CHARIZARDITE_Y
	.2byte ITEM_SKARMORITE
	.2byte ITEM_STARMINITE
	.2byte ITEM_CHIMECHITE
	.2byte ITEM_PYROARITE
	.2byte ITEM_GOLISOPITE
	.2byte ITEM_BARBARACITE
	.2byte ITEM_DRAGALGITE
	.2byte ITEM_GLIMMORANITE
	.2byte ITEM_GOLURKITE
	.2byte ITEM_RAICHUNITE_X
	.2byte ITEM_RAICHUNITE_Y
	.2byte ITEM_ABSOLITE_Z
	.2byte ITEM_LOADED_DICE
	.2byte ITEM_CLEAR_AMULET
	.2byte ITEM_MIRROR_HERB
	.2byte ITEM_PUNCHING_GLOVE
	.2byte ITEM_THROAT_SPRAY
	.2byte ITEM_BLUNDER_POLICY
	.2byte ITEM_ROOM_SERVICE
	.2byte ITEM_EJECT_PACK
	.2byte ITEM_PROTECTIVE_PADS
	.2byte ITEM_UTILITY_UMBRELLA
	.2byte ITEM_ABILITY_SHIELD
	.2byte ITEM_TERRAIN_EXTENDER
	.2byte ITEM_ELECTRIC_SEED
	.2byte ITEM_GRASSY_SEED
	.2byte ITEM_MISTY_SEED
	.2byte ITEM_PSYCHIC_SEED
	.2byte ITEM_DAMP_ROCK
	.2byte ITEM_HEAT_ROCK
	.2byte ITEM_SMOOTH_ROCK
	.2byte ITEM_ICY_ROCK
	.2byte ITEM_FLAME_ORB
	.2byte ITEM_TOXIC_ORB
	.2byte ITEM_ZOOM_LENS
	.2byte ITEM_RAZOR_CLAW
	.2byte ITEM_BRIGHT_POWDER
	.2byte ITEM_FOCUS_BAND
	.2byte ITEM_SHED_SHELL
	.2byte ITEM_GRIP_CLAW
	.2byte ITEM_BINDING_BAND
	.2byte ITEM_IRON_BALL
	.2byte ITEM_LAGGING_TAIL
	.2byte ITEM_STICKY_BARB
	.2byte ITEM_METRONOME
	.2byte ITEM_ABSORB_BULB
	.2byte ITEM_CELL_BATTERY
	.2byte ITEM_LUMINOUS_MOSS
	.2byte ITEM_SNOWBALL
	.2byte ITEM_ADRENALINE_ORB
Draconid_BattleItems_Tier4::
	.2byte ITEM_ALAKAZITE
	.2byte ITEM_AGGRONITE
	.2byte ITEM_MAWILITE
	.2byte ITEM_SABLENITE
	.2byte ITEM_GARDEVOIRITE
	.2byte ITEM_ALTARIANITE
	.2byte ITEM_PINSIRITE
	.2byte ITEM_HERACRONITE
	.2byte ITEM_EXCADRITE
	.2byte ITEM_STARAPTITE
	.2byte ITEM_HAWLUCHANITE
	.2byte ITEM_CHANDELURITE
	.2byte ITEM_CHOICE_BAND
	.2byte ITEM_CHOICE_SPECS
	.2byte ITEM_CHOICE_SCARF
	.2byte ITEM_LIFE_ORB
	.2byte ITEM_ASSAULT_VEST
	.2byte ITEM_WEAKNESS_POLICY
	.2byte ITEM_HEAVY_DUTY_BOOTS
	.2byte ITEM_SAFETY_GOGGLES
	.2byte ITEM_COVERT_CLOAK
Draconid_BattleItems_Tier3::
	.2byte ITEM_LEFTOVERS
	.2byte ITEM_BLACK_SLUDGE
	.2byte ITEM_ROCKY_HELMET
	.2byte ITEM_EXPERT_BELT
	.2byte ITEM_FOCUS_SASH
	.2byte ITEM_EVIOLITE
	.2byte ITEM_AIR_BALLOON
	.2byte ITEM_EJECT_BUTTON
	.2byte ITEM_RED_CARD
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_POWER_HERB
Draconid_BattleItems_Tier2::
	.2byte ITEM_MUSCLE_BAND
	.2byte ITEM_WISE_GLASSES
	.2byte ITEM_QUICK_CLAW
	.2byte ITEM_SCOPE_LENS
	.2byte ITEM_WIDE_LENS
	.2byte ITEM_SHELL_BELL
	.2byte ITEM_BIG_ROOT
	.2byte ITEM_LIGHT_CLAY
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_DEEP_SEA_TOOTH
	.2byte ITEM_DEEP_SEA_SCALE
	.2byte ITEM_EVERSTONE
Draconid_BattleItems_Tier1::
	.2byte ITEM_SILK_SCARF
	.2byte ITEM_CHARCOAL
	.2byte ITEM_MYSTIC_WATER
	.2byte ITEM_MIRACLE_SEED
	.2byte ITEM_MAGNET
	.2byte ITEM_NEVER_MELT_ICE
	.2byte ITEM_BLACK_BELT
	.2byte ITEM_POISON_BARB
	.2byte ITEM_SOFT_SAND
	.2byte ITEM_SHARP_BEAK
	.2byte ITEM_TWISTED_SPOON
	.2byte ITEM_SILVER_POWDER
	.2byte ITEM_HARD_STONE
	.2byte ITEM_SPELL_TAG
	.2byte ITEM_DRAGON_FANG
	.2byte ITEM_BLACK_GLASSES
	.2byte ITEM_METAL_COAT
	.2byte ITEM_FAIRY_FEATHER
	.2byte ITEM_NONE

Draconid_EventScript_GymBoosterRoxanne::
	msgbox Draconid_EventScript_GymBoosterRoxanne_Text_0
	giveitem ITEM_HARD_STONE
	return


Draconid_EventScript_GymBoosterBrawly::
	msgbox Draconid_EventScript_GymBoosterBrawly_Text_0
	giveitem ITEM_BLACK_BELT
	return


Draconid_EventScript_GymBoosterWattson::
	msgbox Draconid_EventScript_GymBoosterWattson_Text_0
	giveitem ITEM_MAGNET
	return


Draconid_EventScript_GymBoosterFlannery::
	msgbox Draconid_EventScript_GymBoosterFlannery_Text_0
	giveitem ITEM_CHARCOAL
	return


Draconid_EventScript_GymBoosterNorman::
	msgbox Draconid_EventScript_GymBoosterNorman_Text_0
	giveitem ITEM_SILK_SCARF
	return


Draconid_EventScript_GymBoosterWinona::
	msgbox Draconid_EventScript_GymBoosterWinona_Text_0
	giveitem ITEM_SHARP_BEAK
	return


Draconid_EventScript_GymBoosterTateAndLiza::
	msgbox Draconid_EventScript_GymBoosterTateAndLiza_Text_0
	giveitem ITEM_TWISTED_SPOON
	return


Draconid_EventScript_GymBoosterJuan::
	msgbox Draconid_EventScript_GymBoosterJuan_Text_0
	giveitem ITEM_MYSTIC_WATER
	return


Draconid_EventScript_GymBoosterRoxanne_Text_0:
	.string "ROXANNE: Please take this HARD STONE\n"
	.string "as well.\p"
	.string "Held by a POKéMON, it strengthens\n"
	.string "ROCK-type moves.$"

Draconid_EventScript_GymBoosterBrawly_Text_0:
	.string "BRAWLY: Oh, and grab this BLACK BELT,\n"
	.string "too!\p"
	.string "Hold it, and your FIGHTING-type moves\n"
	.string "hit like a big wave!$"

Draconid_EventScript_GymBoosterWattson_Text_0:
	.string "WATTSON: Wahahahaha! Take this MAGNET\n"
	.string "as well!\p"
	.string "It charges up ELECTRIC-type moves.\n"
	.string "Zap!$"

Draconid_EventScript_GymBoosterFlannery_Text_0:
	.string "FLANNERY: And… take this CHARCOAL,\n"
	.string "too.\p"
	.string "It makes FIRE-type moves burn hotter.\n"
	.string "Use it well!$"

Draconid_EventScript_GymBoosterNorman_Text_0:
	.string "NORMAN: Take this SILK SCARF, too.\p"
	.string "It strengthens NORMAL-type moves.\n"
	.string "Simple, and strong.$"

Draconid_EventScript_GymBoosterWinona_Text_0:
	.string "WINONA: Please accept this SHARP BEAK\n"
	.string "as well.\p"
	.string "It lends strength to FLYING-type\n"
	.string "moves.$"

Draconid_EventScript_GymBoosterTateAndLiza_Text_0:
	.string "TATE: We have one more gift for you…\p"
	.string "LIZA: …a TWISTED SPOON! It sharpens\n"
	.string "PSYCHIC-type moves!$"

Draconid_EventScript_GymBoosterJuan_Text_0:
	.string "JUAN: Please, accept this MYSTIC WATER\n"
	.string "as well.\p"
	.string "It lends grace to WATER-type moves.$"

Draconid_Text_BattleItemGreeting::
	.string "Welcome to the BATTLE ITEM counter!\p"
	.string "The more GYM BADGES you carry, the\n"
	.string "stronger the items I'm allowed to sell\l"
	.string "you.$"

Draconid_Text_BattleItemGreetingUniform::
	.string "…Battle items for TEAM MAGMA.\n"
	.string "Wonderful.\p"
	.string "Rules are rules. Your BADGES decide\n"
	.string "what I sell you. Not your uniform.$"

Draconid_Text_BattleItemGreetingRevealed::
	.string "{PLAYER}! Everyone's talking about what\n"
	.string "you did in SOOTOPOLIS!\p"
	.string "Here, have a look. Everything your\n"
	.string "BADGES allow!$"
