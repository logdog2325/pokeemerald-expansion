PetalburgWoods_EventScript_DraconidRepBoy1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgWoods_EventScript_DraconidRepBoy1_2
	case REPUTATION_REVEALED, PetalburgWoods_EventScript_DraconidRepBoy1_3
	goto PetalburgWoods_EventScript_Boy1
	return

PetalburgWoods_EventScript_DraconidRepBoy1_2:
	msgbox PetalburgWoods_Text_DraconidRepBoy1Uniform, MSGBOX_NPC
	return

PetalburgWoods_EventScript_DraconidRepBoy1_3:
	msgbox PetalburgWoods_Text_DraconidRepBoy1Revealed, MSGBOX_NPC
	return


PetalburgWoods_EventScript_DraconidRepBoy2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, PetalburgWoods_EventScript_DraconidRepBoy2_2
	goto PetalburgWoods_EventScript_Boy2
	return

PetalburgWoods_EventScript_DraconidRepBoy2_2:
	msgbox PetalburgWoods_Text_DraconidRepBoy2Uniform, MSGBOX_NPC
	return


Route101_EventScript_DraconidRepYoungster::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route101_EventScript_DraconidRepYoungster_2
	case REPUTATION_REVEALED, Route101_EventScript_DraconidRepYoungster_3
	goto Route101_EventScript_Youngster
	return

Route101_EventScript_DraconidRepYoungster_2:
	msgbox Route101_Text_DraconidRepYoungsterUniform, MSGBOX_NPC
	return

Route101_EventScript_DraconidRepYoungster_3:
	msgbox Route101_Text_DraconidRepYoungsterRevealed, MSGBOX_NPC
	return


Route101_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route101_EventScript_DraconidRepBoy_2
	goto Route101_EventScript_Boy
	return

Route101_EventScript_DraconidRepBoy_2:
	msgbox Route101_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


Route102_EventScript_DraconidRepLittleBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route102_EventScript_DraconidRepLittleBoy_2
	goto Route102_EventScript_LittleBoy
	return

Route102_EventScript_DraconidRepLittleBoy_2:
	msgbox Route102_Text_DraconidRepLittleBoyUniform, MSGBOX_NPC
	return


Route102_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route102_EventScript_DraconidRepBoy_2
	goto Route102_EventScript_Boy
	return

Route102_EventScript_DraconidRepBoy_2:
	msgbox Route102_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


Route103_EventScript_DraconidRepMan::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route103_EventScript_DraconidRepMan_2
	case REPUTATION_REVEALED, Route103_EventScript_DraconidRepMan_3
	goto Route103_EventScript_Man
	return

Route103_EventScript_DraconidRepMan_2:
	msgbox Route103_Text_DraconidRepManUniform, MSGBOX_NPC
	return

Route103_EventScript_DraconidRepMan_3:
	msgbox Route103_Text_DraconidRepManRevealed, MSGBOX_NPC
	return


Route103_EventScript_DraconidRepBoy::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route103_EventScript_DraconidRepBoy_2
	goto Route103_EventScript_Boy
	return

Route103_EventScript_DraconidRepBoy_2:
	msgbox Route103_Text_DraconidRepBoyUniform, MSGBOX_NPC
	return


Route104_EventScript_DraconidRepBugCatcher::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route104_EventScript_DraconidRepBugCatcher_2
	goto Route104_EventScript_BugCatcher
	return

Route104_EventScript_DraconidRepBugCatcher_2:
	msgbox Route104_Text_DraconidRepBugCatcherUniform, MSGBOX_NPC
	return


Route104_EventScript_DraconidRepGirl1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route104_EventScript_DraconidRepGirl1_2
	goto Route104_EventScript_Girl1
	return

Route104_EventScript_DraconidRepGirl1_2:
	msgbox Route104_Text_DraconidRepGirl1Uniform, MSGBOX_NPC
	return


Route104_EventScript_DraconidRepBoy1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route104_EventScript_DraconidRepBoy1_2
	goto Route104_EventScript_Boy1
	return

Route104_EventScript_DraconidRepBoy1_2:
	msgbox Route104_Text_DraconidRepBoy1Uniform, MSGBOX_NPC
	return


Route104_EventScript_DraconidRepWoman::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route104_EventScript_DraconidRepWoman_2
	goto Route104_EventScript_Woman
	return

Route104_EventScript_DraconidRepWoman_2:
	msgbox Route104_Text_DraconidRepWomanUniform, MSGBOX_NPC
	return


Route104_EventScript_DraconidRepGirl2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route104_EventScript_DraconidRepGirl2_2
	goto Route104_EventScript_Girl2
	return

Route104_EventScript_DraconidRepGirl2_2:
	msgbox Route104_Text_DraconidRepGirl2Uniform, MSGBOX_NPC
	return


Route104_EventScript_DraconidRepExpertF::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route104_EventScript_DraconidRepExpertF_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq Route104_EventScript_DraconidRepExpertF_3
Route104_EventScript_DraconidRepExpertF_1:
	goto Route104_EventScript_ExpertF
	return

Route104_EventScript_DraconidRepExpertF_2:
	lock
	faceplayer
	msgbox Route104_Text_DraconidRepExpertFUniform, MSGBOX_DEFAULT
	goto Route104_EventScript_DraconidRepExpertF_1

Route104_EventScript_DraconidRepExpertF_3:
	lock
	faceplayer
	msgbox Route104_Text_DraconidRepExpertFRevealed, MSGBOX_DEFAULT
	goto Route104_EventScript_DraconidRepExpertF_1


Route104_EventScript_DraconidRepBoy2::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route104_EventScript_DraconidRepBoy2_2
Route104_EventScript_DraconidRepBoy2_1:
	goto Route104_EventScript_Boy2
	return

Route104_EventScript_DraconidRepBoy2_2:
	lock
	faceplayer
	msgbox Route104_Text_DraconidRepBoy2Uniform, MSGBOX_DEFAULT
	goto Route104_EventScript_DraconidRepBoy2_1


Route104_MrBrineysHouse_EventScript_DraconidRepBriney::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route104_MrBrineysHouse_EventScript_DraconidRepBriney_3
Route104_MrBrineysHouse_EventScript_DraconidRepBriney_1:
	goto Route104_MrBrineysHouse_EventScript_Briney
	return

Route104_MrBrineysHouse_EventScript_DraconidRepBriney_2:
	lock
	faceplayer
	msgbox Route104_MrBrineysHouse_Text_DraconidRepBrineyUniform, MSGBOX_DEFAULT
	goto Route104_MrBrineysHouse_EventScript_DraconidRepBriney_1

Route104_MrBrineysHouse_EventScript_DraconidRepBriney_3:
	goto_if_set FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_DraconidRepBriney_2
	goto Route104_MrBrineysHouse_EventScript_DraconidRepBriney_1


Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner_2
	compare VAR_DRACONID_REPUTATION, REPUTATION_REVEALED
	goto_if_eq Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner_3
Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner_1:
	goto Route104_PrettyPetalFlowerShop_EventScript_ShopOwner
	return

Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner_2:
	lock
	faceplayer
	msgbox Route104_PrettyPetalFlowerShop_Text_DraconidRepShopOwnerUniform, MSGBOX_DEFAULT
	goto Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner_1

Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner_3:
	lock
	faceplayer
	msgbox Route104_PrettyPetalFlowerShop_Text_DraconidRepShopOwnerRevealed, MSGBOX_DEFAULT
	goto Route104_PrettyPetalFlowerShop_EventScript_DraconidRepShopOwner_1


Route104_PrettyPetalFlowerShop_EventScript_DraconidRepWailmerPailGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route104_PrettyPetalFlowerShop_EventScript_DraconidRepWailmerPailGirl_2
Route104_PrettyPetalFlowerShop_EventScript_DraconidRepWailmerPailGirl_1:
	goto Route104_PrettyPetalFlowerShop_EventScript_WailmerPailGirl
	return

Route104_PrettyPetalFlowerShop_EventScript_DraconidRepWailmerPailGirl_2:
	lock
	faceplayer
	msgbox Route104_PrettyPetalFlowerShop_Text_DraconidRepWailmerPailGirlUniform, MSGBOX_DEFAULT
	goto Route104_PrettyPetalFlowerShop_EventScript_DraconidRepWailmerPailGirl_1


Route104_PrettyPetalFlowerShop_EventScript_DraconidRepRandomBerryGirl::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route104_PrettyPetalFlowerShop_EventScript_DraconidRepRandomBerryGirl_2
Route104_PrettyPetalFlowerShop_EventScript_DraconidRepRandomBerryGirl_1:
	goto Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl
	return

Route104_PrettyPetalFlowerShop_EventScript_DraconidRepRandomBerryGirl_2:
	lock
	faceplayer
	msgbox Route104_PrettyPetalFlowerShop_Text_DraconidRepRandomBerryGirlUniform, MSGBOX_DEFAULT
	goto Route104_PrettyPetalFlowerShop_EventScript_DraconidRepRandomBerryGirl_1


Route116_EventScript_DraconidRepBriney::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route116_EventScript_DraconidRepBriney_2
Route116_EventScript_DraconidRepBriney_1:
	goto Route116_EventScript_Briney
	return

Route116_EventScript_DraconidRepBriney_2:
	lock
	faceplayer
	msgbox Route116_Text_DraconidRepBrineyUniform, MSGBOX_DEFAULT
	goto Route116_EventScript_DraconidRepBriney_1


Route116_EventScript_DraconidRepDevonEmployee::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route116_EventScript_DraconidRepDevonEmployee_2
Route116_EventScript_DraconidRepDevonEmployee_1:
	goto Route116_EventScript_DevonEmployee
	return

Route116_EventScript_DraconidRepDevonEmployee_2:
	lock
	faceplayer
	msgbox Route116_Text_DraconidRepDevonEmployeeUniform, MSGBOX_DEFAULT
	goto Route116_EventScript_DraconidRepDevonEmployee_1


Route116_EventScript_DraconidRepWandasBoyfriend::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route116_EventScript_DraconidRepWandasBoyfriend_2
Route116_EventScript_DraconidRepWandasBoyfriend_1:
	goto Route116_EventScript_WandasBoyfriend
	return

Route116_EventScript_DraconidRepWandasBoyfriend_2:
	lock
	faceplayer
	msgbox Route116_Text_DraconidRepWandasBoyfriendUniform, MSGBOX_DEFAULT
	goto Route116_EventScript_DraconidRepWandasBoyfriend_1


Route116_EventScript_DraconidRepGlassesMan::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route116_EventScript_DraconidRepGlassesMan_2
Route116_EventScript_DraconidRepGlassesMan_1:
	goto Route116_EventScript_GlassesMan
	return

Route116_EventScript_DraconidRepGlassesMan_2:
	lock
	faceplayer
	msgbox Route116_Text_DraconidRepGlassesManUniform, MSGBOX_DEFAULT
	goto Route116_EventScript_DraconidRepGlassesMan_1


Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler1::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler1_2
	goto Route116_TunnelersRestHouse_EventScript_Tunneler1
	return

Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler1_2:
	msgbox Route116_TunnelersRestHouse_Text_DraconidRepTunneler1Uniform, MSGBOX_NPC
	return


Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler3::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler3_2
	goto Route116_TunnelersRestHouse_EventScript_Tunneler3
	return

Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler3_2:
	msgbox Route116_TunnelersRestHouse_Text_DraconidRepTunneler3Uniform, MSGBOX_NPC
	return


Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler2::
	switch VAR_DRACONID_REPUTATION
	case REPUTATION_UNIFORM, Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler2_2
	goto Route116_TunnelersRestHouse_EventScript_Tunneler2
	return

Route116_TunnelersRestHouse_EventScript_DraconidRepTunneler2_2:
	msgbox Route116_TunnelersRestHouse_Text_DraconidRepTunneler2Uniform, MSGBOX_NPC
	return


RusturfTunnel_EventScript_DraconidRepWandasBoyfriend::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RusturfTunnel_EventScript_DraconidRepWandasBoyfriend_2
RusturfTunnel_EventScript_DraconidRepWandasBoyfriend_1:
	goto RusturfTunnel_EventScript_WandasBoyfriend
	return

RusturfTunnel_EventScript_DraconidRepWandasBoyfriend_2:
	lock
	faceplayer
	msgbox RusturfTunnel_Text_DraconidRepWandasBoyfriendUniform, MSGBOX_DEFAULT
	goto RusturfTunnel_EventScript_DraconidRepWandasBoyfriend_1


RusturfTunnel_EventScript_DraconidRepWanda::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq RusturfTunnel_EventScript_DraconidRepWanda_2
RusturfTunnel_EventScript_DraconidRepWanda_1:
	goto RusturfTunnel_EventScript_Wanda
	return

RusturfTunnel_EventScript_DraconidRepWanda_2:
	lock
	faceplayer
	msgbox RusturfTunnel_Text_DraconidRepWandaUniform, MSGBOX_DEFAULT
	goto RusturfTunnel_EventScript_DraconidRepWanda_1


Route104_EventScript_DraconidRepWhiteHerbFlorist::
	compare VAR_DRACONID_REPUTATION, REPUTATION_UNIFORM
	goto_if_eq Route104_EventScript_DraconidRepWhiteHerbFlorist_2
Route104_EventScript_DraconidRepWhiteHerbFlorist_1:
	goto Route104_EventScript_WhiteHerbFlorist
	return

Route104_EventScript_DraconidRepWhiteHerbFlorist_2:
	lock
	faceplayer
	msgbox Route104_Text_DraconidRepWhiteHerbFloristUniform, MSGBOX_DEFAULT
	goto Route104_EventScript_DraconidRepWhiteHerbFlorist_1


PetalburgWoods_Text_DraconidRepBoy1Uniform::
	.string "Yo, there! Your POKéMON… Whoa, TEAM\n"
	.string "MAGMA?\p"
	.string "You came through here before without\n"
	.string "that uniform.\p"
	.string "What happened to you in these woods?$"

PetalburgWoods_Text_DraconidRepBoy1Revealed::
	.string "Yo, there! You're the one from\n"
	.string "SOOTOPOLIS!\p"
	.string "So these woods are where your secret\n"
	.string "mission started? Cool!$"

PetalburgWoods_Text_DraconidRepBoy2Uniform::
	.string "I always watch where I'm walking in\n"
	.string "these woods.\p"
	.string "That's how I spotted red uniforms going\n"
	.string "in and out of the trees by the edge.\p"
	.string "You're one of them now, huh?$"

Route101_Text_DraconidRepYoungsterUniform::
	.string "You're the kid who saved PROF. BIRCH\n"
	.string "right here!\p"
	.string "Everybody in LITTLEROOT heard about\n"
	.string "it. So why are you in TEAM MAGMA now?$"

Route101_Text_DraconidRepYoungsterRevealed::
	.string "You saved PROF. BIRCH right here… and\n"
	.string "then all of HOENN!\p"
	.string "I always tell people I saw it first.$"

Route101_Text_DraconidRepBoyUniform::
	.string "Wild POKéMON jump out at you in the tall\n"
	.string "grass.\p"
	.string "But nothing ever scared me like a TEAM\n"
	.string "MAGMA grunt walking out of it!$"

Route102_Text_DraconidRepLittleBoyUniform::
	.string "Fwa… Fwatchoo!\p"
	.string "Oh no, I sneezed on TEAM MAGMA!\p"
	.string "Please don't tell your boss!$"

Route102_Text_DraconidRepBoyUniform::
	.string "I'm going to catch a whole bunch of\n"
	.string "POKéMON!\p"
	.string "And keep every one of them far away\n"
	.string "from TEAM MAGMA.$"

Route103_Text_DraconidRepManUniform::
	.string "Fufufu, I remember you. You battled\n"
	.string "that girl, MAY, right here.\p"
	.string "And now you wear TEAM MAGMA red? I\n"
	.string "never saw that coming. Fufufu…$"

Route103_Text_DraconidRepManRevealed::
	.string "Fufufu, I remember you. You battled MAY\n"
	.string "right here.\p"
	.string "Who knew that kid would end up saving\n"
	.string "HOENN? Fufufu!$"

Route103_Text_DraconidRepBoyUniform::
	.string "My POKéMON is staggeringly tired…\p"
	.string "Don't look at it like that! TEAM MAGMA\n"
	.string "isn't getting my POKéMON!$"

Route104_Text_DraconidRepBugCatcherUniform::
	.string "The sea, huh?\p"
	.string "I heard TEAM MAGMA wants more land and\n"
	.string "less sea. Is that true? I like the sea…$"

Route104_Text_DraconidRepGirl1Uniform::
	.string "That seaside cottage is MR. BRINEY's.\p"
	.string "He was a mighty sailor who never feared\n"
	.string "a storm.\p"
	.string "But I bet he'd never let TEAM MAGMA set\n"
	.string "foot on his boat.$"

Route104_Text_DraconidRepBoy1Uniform::
	.string "If you throw a POKé BALL, weaken the\n"
	.string "wild POKéMON first.\p"
	.string "That's for WILD POKéMON. Don't you dare\n"
	.string "throw one at mine!$"

Route104_Text_DraconidRepWomanUniform::
	.string "You're a thief if you try to steal\n"
	.string "someone else's POKéMON.\p"
	.string "I hope TEAM MAGMA taught you that\n"
	.string "much.$"

Route104_Text_DraconidRepGirl2Uniform::
	.string "Oh, no, I'm not a TRAINER. Please don't\n"
	.string "look at me!\p"
	.string "When TRAINERS lock eyes, it's a battle.\p"
	.string "When TEAM MAGMA locks eyes… I don't\n"
	.string "want to find out.$"

Route104_Text_DraconidRepExpertFUniform::
	.string "My, my. I've seen you pass this way\n"
	.string "before, child.\p"
	.string "You've changed your clothes, I see.\n"
	.string "Well, BERRIES don't care who picks them.$"

Route104_Text_DraconidRepExpertFRevealed::
	.string "My, my. The child from the mountains,\n"
	.string "back again!\p"
	.string "I hear you've done great things.\n"
	.string "BERRIES still don't care, but I do.$"

Route104_Text_DraconidRepBoy2Uniform::
	.string "Whoa, a TEAM MAGMA grunt! You're not\n"
	.string "here to take my seeds, are you?\p"
	.string "…Phew. Okay. But I'm keeping an eye on\n"
	.string "you.$"

Route104_MrBrineysHouse_Text_DraconidRepBrineyUniform::
	.string "MR. BRINEY: Hm? Folks in PETALBURG\n"
	.string "grumble about that red getup of yours.\p"
	.string "Let 'em grumble! PEEKO knows who saved\n"
	.string "her, and so do I.$"

Route104_PrettyPetalFlowerShop_Text_DraconidRepShopOwnerUniform::
	.string "Oh! A TEAM MAGMA uniform… in my flower\n"
	.string "shop?\p"
	.string "Well, flowers bloom for everyone. Even\n"
	.string "for you.$"

Route104_PrettyPetalFlowerShop_Text_DraconidRepShopOwnerRevealed::
	.string "Oh! It's {PLAYER}{KUN}! Everyone's talking\n"
	.string "about you!\p"
	.string "I'll put a flower in the window for you.\n"
	.string "Welcome back!$"

Route104_PrettyPetalFlowerShop_Text_DraconidRepWailmerPailGirlUniform::
	.string "Um… Are you going to stomp on our\n"
	.string "flowers?\p"
	.string "TEAM MAGMA wants more land, right?\p"
	.string "…Okay. Just be gentle with them.$"

Route104_PrettyPetalFlowerShop_Text_DraconidRepRandomBerryGirlUniform::
	.string "My big sisters told me to be careful\n"
	.string "around people in red.\p"
	.string "But you look like someone who'd water a\n"
	.string "flower properly.$"

Route116_Text_DraconidRepBrineyUniform::
	.string "MR. BRINEY: You there! In the red… No\n"
	.string "matter, no matter!\p"
	.string "I've no time to be choosy about who I\n"
	.string "ask for help!$"

Route116_Text_DraconidRepDevonEmployeeUniform::
	.string "Oh! Ahem. I never thought I'd owe a TEAM\n"
	.string "MAGMA grunt this much.\p"
	.string "But a debt is a debt. DEVON pays its\n"
	.string "debts.$"

Route116_Text_DraconidRepWandasBoyfriendUniform::
	.string "Hey! Another one in a uniform!\p"
	.string "Red this time? I don't care what color\n"
	.string "you wear.\p"
	.string "Just don't scare the tunnel POKéMON!$"

Route116_Text_DraconidRepGlassesManUniform::
	.string "Who's there? Everything's a blur\n"
	.string "without my glasses.\p"
	.string "Is that a red uniform? Please tell me\n"
	.string "you're not TEAM MAGMA…$"

Route116_TunnelersRestHouse_Text_DraconidRepTunneler1Uniform::
	.string "We stopped digging RUSTURF TUNNEL so\n"
	.string "we wouldn't hurt the wild POKéMON.\p"
	.string "TEAM MAGMA would've just blasted\n"
	.string "through, huh? Not on my watch.$"

Route116_TunnelersRestHouse_Text_DraconidRepTunneler3Uniform::
	.string "Without the tunnel, you'd have to sail\n"
	.string "to DEWFORD and SLATEPORT.\p"
	.string "Then you'd still have to go through\n"
	.string "MAUVILLE.\p"
	.string "Long way around. Maybe long enough to\n"
	.string "think about that uniform of yours.$"

Route116_TunnelersRestHouse_Text_DraconidRepTunneler2Uniform::
	.string "There's a man digging to VERDANTURF by\n"
	.string "hand, so he won't harm the POKéMON.\p"
	.string "Your TEAM MAGMA should take a lesson\n"
	.string "from him.$"

RusturfTunnel_Text_DraconidRepWandasBoyfriendUniform::
	.string "TEAM MAGMA, in my tunnel?\p"
	.string "If you've come to blast through, forget\n"
	.string "it!\p"
	.string "The POKéMON in here can't stand loud\n"
	.string "noises.$"

RusturfTunnel_Text_DraconidRepWandaUniform::
	.string "Oh! A TEAM MAGMA grunt… You're not here\n"
	.string "to stop him digging, are you?$"

Route104_Text_DraconidRepWhiteHerbFloristUniform::
	.string "Oh! A TEAM MAGMA grunt, by the flower\n"
	.string "shop…\p"
	.string "Well, flowers make everyone gentler.\n"
	.string "Maybe even you.$"
