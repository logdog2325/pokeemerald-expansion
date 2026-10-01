@ Draconid Emerald: the new-game speech is given by the ELDER of the DRACONID clan, not PROF. BIRCH (D-420).
@ The labels and the tasks in src/main_menu.c stay as they were; only the words (and his dragon) changed.

gText_Birch_Welcome::
	.string "Hohoho… Come in, come in.\n"
	.string "The mountain wind bites tonight.\p"
	.string "I am the ELDER of the DRACONID clan,\n"
	.string "keeper of our mountain's shrine.\p"
	.string "Welcome to the world of POKéMON,\n"
	.string "as our clan has always known it.\p"
	.string "$"

@ Draconid Emerald: his dragon comes out of its ball at the {PAUSE} (NewGameBirchSpeech_WaitForThisIsPokemonText)
gText_Birch_Pokemon::
	.string "Come out, old friend.{PAUSE 96}\p"
	.string "$"

@ Draconid Emerald: ALTARIA is DRACONID_ELDER_DRAGON (include/constants/draconid.h)
gText_Birch_MainSpeech::
	.string "This is my ALTARIA. We have flown\n"
	.string "these peaks together for sixty years.\p"
	.string "Creatures such as this are POKéMON.\n"
	.string "Every sky, sea and stone holds them.\p"
	.string "Down in the lowlands, people live\n"
	.string "beside POKéMON as friends and helpers.\p"
	.string "They work together, play together…\n"
	.string "and sometimes, they battle together.\p"
	.string "Up here, our clan lives beside the\n"
	.string "dragons, as our ancestors did.\p"
	.string "We keep the old ways, and we watch\n"
	.string "the sky. The lowlands have forgotten.\p"
	.string "$"

gText_Birch_AndYouAre::
	.string "Now then. And you are?$"

gText_Birch_BoyOrGirl::
	.string "Come closer. These old eyes\n"
	.string "are not what they once were.\p"
	.string "Are you a boy?\n"
	.string "Or are you a girl?$"

gText_Birch_WhatsYourName::
	.string "Ah, yes.\n"
	.string "And what is your name, child?$"

gText_Birch_SoItsPlayer::
	.string "{PLAYER}…\n"
	.string "Is that right?$"

gText_Birch_YourePlayer::
	.string "Hohoho. Of course it is.\n"
	.string "Forgive an old man his memory.\p"
	.string "You are {PLAYER} of the DRACONID\n"
	.string "clan. I held you the day you were born.\p"
	.string "$"

gText_Birch_AreYouReady::
	.string "Go and rest now, {PLAYER}.\n"
	.string "The hour is late.\p"
	.string "Watch the sky as you fall asleep.\n"
	.string "It has been restless these nights…\p"
	.string "Sleep well, child. When the sky\n"
	.string "speaks, the clan must answer.\p"
	.string "$"
