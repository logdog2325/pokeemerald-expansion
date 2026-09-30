# Draconid Emerald – reputation dialogue (script review)

What ordinary people say to the player in each reputation state (`VAR_DRACONID_REPUTATION`, D-103):

| State | When | Tone |
|---|---|---|
| `REPUTATION_PRE_UNIFORM` (0) | Act 1, until the recruitment in Petalburg Woods | vanilla lines, untouched |
| `REPUTATION_UNIFORM` (1) | Petalburg Woods to the Sootopolis turn: the Team Magma grunt uniform | whispering, refusing to talk, keeping children away, angry (Lavaridge, Mossdeep) – but every service still works |
| `REPUTATION_REVEALED` (2) | after the Sootopolis turn: the one who stood up to Maxie | grateful, embarrassed, apologetic |

Generated from the scripts in `data/scripts/draconid/reputation/*.pory` (one file per town/area);
" / " marks a new text box. The Pre-uniform column only sums up the vanilla line. Some NPCs turn
their back on the player after a uniform line ("turns away" in the NPC column); the rest face the
player as in vanilla.

How it is wired (details: `docs/hack_changes.md`):
- **Townsfolk**: the object's `script` in `data/maps/<Map>/map.json` points at the new script, which
  goes on to the vanilla script in PRE_UNIFORM.
- **Shared NPCs, Gym Guides, Gym Leaders**: one `@ Draconid Emerald` line in the vanilla script
  jumps to the new one; healing, shopping, linking, the Day Care, battles, badges, TMs and rematches
  stay vanilla.

Not reachable in normal play, so no new line (vanilla is used): a Gym Leader's intro after the
reveal for Roxanne, Brawly, Wattson, Flannery and Tate & Liza (their badges come before the turn;
Winona is the one who can be left for later), anything in uniform at the Sootopolis Gym (locked
until the crisis is over) and in Ever Grande City (Waterfall comes from Juan), and Mr. Briney on the
S.S. Tidal in uniform (post-game). Norman in the Petalburg Gym is the story's (act4.pory); his Gym Guide got
its lines in the contradiction scrub (D-255, [hack_contradictions.md](hack_contradictions.md)), as did PROF. COZMO.

## Shared NPCs (every town)

| NPC | Hook | Uniform | Revealed |
|---|---|---|---|
| Pokémon Center nurse | `Common_EventScript_PkmnCenterNurse` (not the Gold Card "usual") | …That uniform. TEAM MAGMA. / …Fine. We don't turn away POKéMON. Even yours. / Do you want them healed? (YES/NO)<br>**YES:** …Hand them over, then. → heals → They're healed. / …They trust you so much. I hope you deserve it.<br>**NO:** …Suit yourself. | Welcome back, {PLAYER}! / We all heard what you did in SOOTOPOLIS. I'm sorry I was so cold to you. / Would you like to rest your POKéMON? (YES/NO) → vanilla healing lines |
| Poké Mart clerks (all Hoenn marts, Lilycove Department Store, Pokémon League) | greeting / goodbye around the shop menu | …TEAM MAGMA. Hmph. / Your money spends like anyone's, I suppose. What do you want?<br>**Goodbye:** …That's all? Then please go. | Oh! Welcome, {PLAYER}! / Sorry about how I treated you before. What can I get you?<br>**Goodbye:** Thank you so much! Please come again! |
| Cable Club: Union Room and Direct Corner attendants | a line before the vanilla welcome | …A TEAM MAGMA grunt, in the CABLE CLUB. / Our rules say every TRAINER may link here. …Even you. | Oh! It's {PLAYER}, from SOOTOPOLIS! / The CABLE CLUB is honored to have you. |
| Cable Club: TEALA (2F attendant) | replaces "Hello, it's me, TEALA" | …Oh. It's you, {PLAYER}. / I'm TEALA, the 2F attendant. I help every TRAINER. That's my job. / …Did you need to ask me about linking? (YES/NO, vanilla answers) | {PLAYER}! It's me, TEALA! / I'm sorry I was so cold to you. I should have known better. / Is there something you needed to ask me about linking? (YES/NO) |
| Day Care man (Route 117, nothing in the Day Care) | `Route117_EventScript_DaycareMan` | Hm? That red getup… TEAM MAGMA, eh? / I'm too old to be scared of a uniform. / If you want a POKéMON raised, talk to my wife. The POKéMON aren't to blame. | Ah, it's you! We read about SOOTOPOLIS in the paper. / My wife and I would be proud to raise your POKéMON. Talk to her anytime! |
| Day Care woman (offer to raise a POKéMON) | `Route117_PokemonDayCare_EventScript_DaycareWoman` | …Oh my. A TEAM MAGMA grunt. / Well, a POKéMON is a POKéMON, whoever brings it in. / Would you like us to raise one of yours? (YES/NO) | Oh, it's you, dear! My husband told me everything. / To think we were afraid of you! Please forgive two old worriers. / Would you like us to raise one of your POKéMON? (YES/NO) |

## Littleroot Town

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| LittlerootTown | Little girl at (16, 10) | `LittlerootTown_EventScript_DraconidRepTwin` | "Are you going to catch POKéMON? Good luck!" | …You look scary in those clothes. / My mommy says TEAM MAGMA are bad people. / But you saved PROF. BIRCH… Are you a bad person now? | You were only pretending to be bad! I knew it! / When I grow up, I want to be brave like you! |
| LittlerootTown | Man at (12, 13) | `LittlerootTown_EventScript_DraconidRepFatMan` | "The power of science is staggering!" | Hm? Is that a TEAM MAGMA uniform? / You helped PROF. BIRCH on ROUTE 101! Why would you join them? / The power of people to surprise me is staggering… | So you were working against TEAM MAGMA all along! / The power of a good disguise is staggering! |
| LittlerootTown | Boy at (14, 17) – turns away | `LittlerootTown_EventScript_DraconidRepBoy` | "When does PROF. BIRCH spend time at home?" | PROF. BIRCH's LAB is right over there. / …You're not here to steal his research for TEAM MAGMA, are you? | PROF. BIRCH says he never stopped believing in you. / …I wasn't so sure. Sorry about that. |

## Oldale Town

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| OldaleTown | Girl at (16, 11) – turns away | `OldaleTown_EventScript_DraconidRepGirl` | "I'm saving my progress." | …I'm saving my progress, and then I'm leaving. / I'd rather not be seen near TEAM MAGMA. | Hey, you're the TRAINER from SOOTOPOLIS! / I'm saving my progress right now, so I'll always remember I met you! |
| OldaleTown | Man sketching footprints at (8, 9) | `OldaleTown_EventScript_DraconidRepFootprintsMan` | "they were only my own footprints…" | Stay back! Don't step on my sketches! / These are the footprints of a TEAM MAGMA grunt. I'm keeping records. | I tore up my sketches of your footprints. / It turns out they were a hero's footprints! I'll have to start over. |
| OldaleTown_House2 | Woman at (4, 4) | `OldaleTown_House2_EventScript_DraconidRepWoman` | "POKéMON level up and become stronger." | …Please don't make any trouble in my house. / If you want to battle, you can do it outside. | Oh, it's you! Come in, come in! / I'm sorry I was so rude to you. We all were. |
| OldaleTown_PokemonCenter_1F | Boy in the Pokémon Center at (10, 6) | `OldaleTown_PokemonCenter_1F_EventScript_DraconidRepBoy` | "POKéMON CENTERS are great! It's all for free." | POKéMON CENTERS are free for everyone… / Even for TEAM MAGMA. That doesn't seem fair. | POKéMON CENTERS are free for everyone! / I'm glad they never turned you away. You saved HOENN! |

## Petalburg City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| PetalburgCity | Boy looking into the pond at (8, 22) | `PetalburgCity_EventScript_DraconidRepBoy` | "What do you see reflected in your face?" | My face is reflected in the water. / And behind me… a TEAM MAGMA grunt. / What do you see reflected in your face? …I wonder. | My face is reflected in the water. / And next to me… the hero of SOOTOPOLIS! / What do you see in your face now? A shining grin, I bet! |
| PetalburgCity | Gentleman at (20, 10) | `PetalburgCity_EventScript_DraconidRepGentleman` | a seventh POKéMON goes to a PC BOX | If you catch a seventh POKéMON, it goes to a PC BOX. / Do TEAM MAGMA grunts even use PC BOXES? / …Never mind. I'd rather not know. | Let's say you have six POKéMON… / Oh, pardon me! You don't need my advice. You stood up to MAXIE himself! |
| PetalburgCity | Boy at (12, 15) | `PetalburgCity_EventScript_DraconidRepGymBoy` | "Are you maybe a rookie TRAINER?" | Hiya! Are you maybe… Wait, that uniform! / Our GYM is for honest TRAINERS. NORMAN won't go easy on TEAM MAGMA! | Hiya! You're the one who beat TEAM MAGMA from the inside! / And I thought you were a rookie. Boy, was I wrong! |
| PetalburgCity_House1 | Old traveler at (4, 4) | `PetalburgCity_House1_EventScript_DraconidRepMan` | "Traveling is wonderful!" | Traveling is wonderful… / But in that uniform? Wherever you go, people must be afraid of you. | Traveling is wonderful! / And now, wherever you go, people will greet you with a smile! |
| PetalburgCity_PokemonCenter_1F | Youngster in the Pokémon Center at (9, 6) – turns away | `PetalburgCity_PokemonCenter_1F_EventScript_DraconidRepYoungster` | "My POKéMON ate an ORAN BERRY." | …My ORAN BERRIES are for my POKéMON. / You're not taking them for TEAM MAGMA. | Hey! You're the one who saved HOENN! / If I had any ORAN BERRIES left, I'd give them all to you! |
| PetalburgCity_WallysHouse | Wally's dad at (3, 4) | `PetalburgCity_WallysHouse_EventScript_DraconidRepWallysDad` | thanks for helping WALLY → "WALLY's coming home soon" → the Ever Grande joke | **Before Surf:** You're {PLAYER}, who helped WALLY catch his POKéMON… / …in a TEAM MAGMA uniform? / WALLY talks about you all the time. I don't know what to tell him now.<br>**After Surf:** WALLY's coming home soon. / When he does, I hope he can still call you a friend. I'd like to, too. | {PLAYER}! We heard what you did in SOOTOPOLIS. / WALLY always said you were good. He was right, and I was wrong to doubt you.<br>**After WALLY at VICTORY ROAD:** vanilla |
| PetalburgCity_Gym | Gym Guide (D-255) | `PetalburgCity_Gym_EventScript_DraconidRepGymGuide` | room advice / congratulations | **Advice:** Hey, how's it… Whoa. TEAM MAGMA? / I still have to give you advice. That's the job. / The doors open when you beat the TRAINERS in each room. / Left is the SPEED ROOM. Right is the ACCURACY ROOM. / NORMAN won't go easy on that uniform. …Go on.<br>**After the badge:** Whoa! You beat NORMAN! / In that uniform… I don't even know if I should cheer. | **Advice:** vanilla (not reachable)<br>**After the badge:** {PLAYER}! You beat NORMAN, and then you stood up to MAXIE himself! / Like, whoa! What a stunning turn of events! |
| PetalburgCity_WallysHouse | Wally's mom at (7, 5) | `PetalburgCity_WallysHouse_EventScript_DraconidRepWallysMom` | WALLY smiled again → WALLY left VERDANTURF without telling anyone | **Before Surf:** WALLY was so happy when he caught his POKéMON… / Oh, dear. Is that a TEAM MAGMA uniform? / WALLY looks up to you so much. Please don't let him down.<br>**After Surf:** Keep this a secret from my husband… / WALLY left VERDANTURF TOWN without telling anyone. / If you see him, please… don't drag him into anything dangerous. | {PLAYER}! WALLY told us everything. / We should have trusted you, the way he always did. / Thank you for looking out for him. |

## Rustboro City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| RustboroCity | Woman at (22, 34) | `RustboroCity_EventScript_DraconidRepWoman` | FIRE types don't match up against ROXANNE's ROCK types | TEAM MAGMA loves FIRE, doesn't it? / FIRE doesn't match up well against ROCK. I hope ROXANNE teaches you that. | You were on our side all along? / And I glared at you every time you walked past… I'm so embarrassed. |
| RustboroCity | Little girl at (21, 46) – turns away | `RustboroCity_EventScript_DraconidRepTwin` | "When I get bigger, I'm going to go places with POKéMON, too." | Wow, your POKéMON are so cool! / …Oh. Mommy says I can't talk to TEAM MAGMA. Bye-bye! | Mommy says you're a hero now! / When I get bigger, I'm going to go places with POKéMON, just like you! |
| RustboroCity | Man at (19, 27) – turns away | `RustboroCity_EventScript_DraconidRepMan2` | traded POKéMON grow fast but may not obey | …Keep walking. / I've got nothing to say to TEAM MAGMA.<br>**After the Devon Goods (D-258), returned:** …Keep walking. / So you brought DEVON's parcel back. That doesn't change what you're wearing.<br>**Kept:** …Keep walking. / DEVON lost a parcel, and a MAGMA grunt went after the thief. I can guess how that ended. | Hey… I owe you an apology. / I treated you like dirt while you were risking everything for HOENN. |
| RustboroCity | Boy at (31, 36) | `RustboroCity_EventScript_DraconidRepBoy1` | 2-on-2 battles | Did you know? Everyone in town whispers about you. / A MAGMA grunt who raises DRAGON POKéMON… / Nobody knows what to make of you.<br>**After the Devon Goods (D-258), returned:** Did you know? Everyone in town whispers about you. / A MAGMA grunt who brought DEVON's stolen parcel back… / Nobody knows what to make of you.<br>**Kept:** Did you know? DEVON's stolen parcel is gone for good. / The MAGMA grunt who chased the thief came back with nothing. Funny, huh?<br>**Kept, once STERN has them:** Did you know? DEVON's missing parcel turned up in SLATEPORT! / A MAGMA grunt brought it to CAPT. STERN. Said they found it lying around. / …Hey, wait. That was you! | Did you know? You're famous now! / Everyone in RUSTBORO says they knew you were good all along. Hah!<br>**Kept:** Did you know? You're famous now! / Even DEVON forgave you for that parcel. …Mostly. Hah! |
| RustboroCity_DevonCorp_1F | Employee by the door at (2, 6) (`devon_goods.pory`, D-258; vanilla until the goods are back) | `RustboroCity_DevonCorp_1F_EventScript_DraconidEmployee` | "It sounds like they've recovered the DEVON GOODS." | **Returned:** Hey, you're the TEAM MAGMA grunt who brought our GOODS back! / I still can't believe it. …Thanks, I guess.<br>**Kept:** Our stolen GOODS are gone for good. / You chased the thief, didn't you? And came back with nothing? / …Some of us here don't believe that story.<br>**Kept, once STERN has them:** Our missing GOODS turned up in SLATEPORT! / CAPT. STERN says a TEAM MAGMA grunt brought them in. Said they “found” them. / …Found them. Sure. | **Returned:** You brought our GOODS back even while you wore that uniform. / No wonder the PRESIDENT trusted you!<br>**Kept:** So keeping our GOODS was part of your act? / The PRESIDENT says all is forgiven. / …I'm still thinking about it. |
| RustboroCity_DevonCorp_1F | Guard by the stairs at (15, 5) (`devon_goods.pory`) | `RustboroCity_DevonCorp_1F_EventScript_DraconidStairGuard` | "You're always welcome here!" | **Returned:** Hi, there! The PRESIDENT says you're always welcome here. / Uniform and all.<br>**Kept:** The PRESIDENT says to let you through. / …I'll be watching you, though. | **Returned:** vanilla<br>**Kept:** The PRESIDENT says to let you through. / He's forgiven you for the GOODS. So… welcome back, I suppose. |
| RustboroCity_DevonCorp_2F | Scientist who built the POKéNAV at (2, 6) (`devon_goods.pory`) | `RustboroCity_DevonCorp_2F_EventScript_DraconidPokenavScientist` | "Oh, wow! That's a POKéNAV!" | **Returned:** Oh, wow! That's the POKéNAV I built! / You brought our GOODS back, so I suppose you earned it. Even in that uniform.<br>**Kept:** That's the POKéNAV I built. / The PRESIDENT gave one to you, even after what happened to our GOODS? / He trusts people far too easily. | Oh, wow! A DRACONID, using my POKéNAV to fool TEAM MAGMA! / I'd love to hear how it held up out there! |
| RustboroCity_DevonCorp_3F | Employee at (3, 5), until the parts reach STERN (`devon_goods.pory`) | `RustboroCity_DevonCorp_3F_EventScript_DraconidEmployee` | "you should go see CAPT. STERN" | **Returned:** vanilla<br>**Kept:** Poor CAPT. STERN. He's been waiting for those parts for weeks. / If you visit the SHIPYARD in SLATEPORT, please tell him what happened. | not reachable (gone after the delivery) |
| RustboroCity_DevonCorp_3F | MR. STONE at his desk (`devon_goods.pory`; the vanilla script calls it) | `RustboroCity_DevonCorp_3F_EventScript_DraconidMrStoneTalk` | "I'm not familiar with trends" | **Returned:** MR. STONE: My staff are still talking about it. / A TEAM MAGMA grunt who brings back what was stolen! / Since my youth, I've immersed myself in work. I don't understand young people at all. Wahaha!<br>**Kept:** MR. STONE: I'm counting on you! / My LETTER for STEVEN, and the news for poor CAPT. STERN.<br>**Kept, once STERN has them:** MR. STONE: CAPT. STERN tells me our parts reached him after all. / In your hands, {PLAYER}{KUN}. / I'm a patient man. But I do keep count. | **Returned:** MR. STONE: {PLAYER}{KUN}! So you were a DRACONID all along! / A TEAM MAGMA grunt who brought our parts back… I should have guessed! Wahahaha!<br>**Kept:** MR. STONE: {PLAYER}{KUN}! So you were a DRACONID all along! / That's why you kept our parts, then. TEAM MAGMA had to believe you were one of them. / All is forgiven, my friend. Wahahaha! |
| RustboroCity | Man at (26, 23) | `RustboroCity_EventScript_DraconidRepMan1` | "Have you taken the POKéMON GYM challenge?" | A TEAM MAGMA grunt, collecting GYM BADGES? / What does MAGMA want with those? …I don't like it one bit. | So you collected BADGES to get close to TEAM MAGMA's boss? / That's the bravest GYM challenge I've ever heard of! |
| RustboroCity_Gym | Gym Guide | `RustboroCity_Gym_EventScript_DraconidRepGymGuide` | type advice / congratulations | **Advice:** Yo, how's it… Hold on. You're with TEAM MAGMA? / Well… I give advice to every challenger. Rules are rules. / ROXANNE uses ROCK-type POKéMON. They can't stand WATER and GRASS moves. / …There. Now go.<br>**After the badge:** You won the STONE BADGE… in that uniform. / I didn't cheer this time. But I have to admit, that was a real win. | **Advice:** vanilla (not reachable)<br>**After the badge:** Yo, {PLAYER}! I heard everything! / A secret agent, climbing the stairs to the CHAMPIONSHIP… / That's got to feel awesome! |
| RustboroCity_Gym | ROXANNE (Gym Leader) | `RustboroCity_Gym_EventScript_DraconidRepRoxanne` | vanilla intro and post-battle line | **Intro:** Hello, I am ROXANNE, the RUSTBORO POKéMON GYM LEADER. / …That uniform. You are with TEAM MAGMA. / The POKéMON LEAGUE's rules say I must accept every challenger. So I will. / But I will watch closely how you treat your POKéMON. Let us battle!<br>**After:** Your POKéMON trust you completely. / That does not fit the uniform you wear. / I would like to understand why. Perhaps one day, you will tell me. | **Intro:** vanilla (not reachable)<br>**After:** {PLAYER}! I heard what happened in SOOTOPOLIS. / I judged you by your clothes. A good student should look deeper. / Please accept my apology. |

## Dewford Town

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| DewfordTown | Woman at (7, 12) | `DewfordTown_EventScript_DraconidRepWoman` | "DEWFORD is a tiny island community." | DEWFORD is a tiny island. Word gets around fast. / Everyone already knows a TEAM MAGMA grunt came ashore. | DEWFORD is a tiny island. Word gets around fast. / And the word is, you saved HOENN! It's the biggest trend ever! |
| DewfordTown_House1 | Man at (3, 3) | `DewfordTown_House1_EventScript_DraconidRepMan` | living in harmony with POKéMON and the family | We live in peace here, with our POKéMON and our family. / Please don't bring TEAM MAGMA's trouble to our island. | We live in peace here, with our POKéMON and our family. / That peace is thanks to you. Please, visit anytime. |
| DewfordTown_House2 | Boy who idolizes Brawly at (2, 3) – turns away | `DewfordTown_House2_EventScript_DraconidRepBoy` | "He's so cool… Everyone idolizes him." | You crossed the sea to visit DEWFORD? / Is TEAM MAGMA after something on our island? …BRAWLY will stop you! | BRAWLY is cool… but you're even cooler! / A secret agent who beat TEAM MAGMA from the inside! |
| DewfordTown_PokemonCenter_1F | Woman in the Pokémon Center at (10, 6) | `DewfordTown_PokemonCenter_1F_EventScript_DraconidRepPokefanF` | the stone cavern at the edge of town | There's a stone cavern at the edge of town. / …Is TEAM MAGMA digging for something in there? Leave our cave alone. | There's a stone cavern at the edge of town. / They say a certain famous TRAINER once explored it. That was you, wasn't it? |
| DewfordTown_Gym | Gym Guide | `DewfordTown_Gym_EventScript_DraconidRepGymGuide` | type advice / congratulations | **Advice:** Hey, how's it… Whoa. TEAM MAGMA? / I still have to give you advice. That's the job. / BRAWLY uses FIGHTING types. They lay a smack down on NORMAL types. / The GYM is dark, too. It gets brighter as you beat the TRAINERS. …Go on.<br>**After the badge:** Whoah! It's turned too bright in here! / …Your future might be bright, too. If you ever take off that uniform. | **Advice:** vanilla (not reachable)<br>**After the badge:** Hey, {PLAYER}! You lit up more than this GYM. / You lit up all of HOENN! Your future is bright! |
| DewfordTown_Gym | BRAWLY (Gym Leader) | `DewfordTown_Gym_EventScript_DraconidRepBrawly` | vanilla intro and post-battle line | **Intro:** I'm BRAWLY! DEWFORD's GYM LEADER! / Whoa, a TEAM MAGMA grunt, out here on my island? / Doesn't matter! In my GYM, all that counts is how hard you fight! / Let me see what you're made of!<br>**After:** You fight clean. Cleaner than I expected from TEAM MAGMA. / Something about you doesn't add up… I'll let the waves sort it out! | **Intro:** vanilla (not reachable)<br>**After:** Hey, {PLAYER}! The whole island's talking about you! / You rode that wave all the way to TEAM MAGMA's boss! Respect! |

## Slateport City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| SlateportCity | Sailor at (37, 41) – turns away | `SlateportCity_EventScript_DraconidRepSailor1` | "Could the sea have been made by the tears shed by POKéMON?" | The sea is just so vast… / And TEAM MAGMA wants to make it smaller. Isn't that right, grunt? | The sea is just so vast… / And thanks to you, it's still here. Thank you, {PLAYER}. |
| SlateportCity | Woman at (9, 50) | `SlateportCity_EventScript_DraconidRepPokefanF` | "I get carried away and buy too much." | …I'm keeping my purse close. No offense, dear. / Well… some offense. | I'm sorry I clutched my purse whenever you walked by. / Let me make it up to you… Oh, I spent all my money again! |
| SlateportCity | Man at (16, 46) | `SlateportCity_EventScript_DraconidRepMan2` | "the BATTLE TENT's awesome in its own way." | You're going to the BATTLE TENT? In that uniform? / Don't expect anyone to cheer for you. | You should enter the BATTLE TENT! / Everyone would cheer for the TRAINER who stood up to MAXIE! |
| SlateportCity | Woman at (15, 31) – turns away | `SlateportCity_EventScript_DraconidRepWoman2` | a traded POKéMON's nickname can't be changed | Children, come here! Stay away from that one. / …TEAM MAGMA, right here in SLATEPORT. What next? | Children, come and say hello! / This is the TRAINER who protected our sea. / …I'm sorry I kept them away from you. |
| SlateportCity | Man at (34, 51) | `SlateportCity_EventScript_DraconidRepMan3` | the lighthouse light reaches dozens of miles | TEAM AQUA at our museum, and now TEAM MAGMA in our streets. / What did SLATEPORT ever do to you people? | The lighthouse shines for every ship that comes home. / Tonight, I think it's shining for you. |

## Mauville City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| MauvilleCity | Boy at (29, 16) | `MauvilleCity_EventScript_DraconidRepBoy` | "you have to nurse it back to health." | If your POKéMON gets hurt, you have to nurse it back to health. / …Do TEAM MAGMA grunts do that? Yours look really healthy. Weird. | Your POKéMON always looked so healthy and happy. / I should have known you weren't really a bad guy! |
| MauvilleCity | Rich boy at (24, 10) – turns away | `MauvilleCity_EventScript_DraconidRepRichBoy` | wild POKéMON can jump you on a BIKE | …I'm going to ride my BIKE the other way now. / Nothing personal. Okay, a little personal. | You're the one from SOOTOPOLIS! / Can I ride my BIKE next to you for a bit? That'd be so cool! |
| MauvilleCity | Man at (14, 11) | `MauvilleCity_EventScript_DraconidRepManiac` | all sorts of people come through MAUVILLE | We get all sorts of people coming through MAUVILLE. / But TEAM MAGMA is one sort I could do without. | We get all sorts of people coming through MAUVILLE. / But a real hero? That's a first! |
| MauvilleCity | Woman at (18, 6) – turns away | `MauvilleCity_EventScript_DraconidRepWoman` | "RYDEL, the owner, is a very generous man." | RYDEL is a very generous man. More generous than me. / …I have nothing to say to TEAM MAGMA. | RYDEL is a very generous man. / But you gave HOENN something far greater. Thank you. |
| MauvilleCity_Gym | Gym Guide | `MauvilleCity_Gym_EventScript_DraconidRepGymGuide` | type advice / congratulations | **Advice:** Hey, how's it… Oh. TEAM MAGMA. / Fine. WATTSON uses ELECTRIC types. They'll zap WATER types. Bzzt. / He's put switch-controlled doors all over his GYM. …Good luck, I guess.<br>**After the badge:** You powered the door open… / I don't know if I should cheer. But that was electrifying. | **Advice:** vanilla (not reachable)<br>**After the badge:** Whoa, it's {PLAYER}! You're electrifying! / You short-circuited TEAM MAGMA's whole plan! |
| MauvilleCity_Gym | WATTSON (Gym Leader) | `MauvilleCity_Gym_EventScript_DraconidRepWattson` | vanilla intro and post-battle line | **Intro:** Wahahahah! A TEAM MAGMA grunt, is it? / If you've come to make trouble in my city, you'll get a nasty shock! / But you got past all my doors fair and square. So we'll battle fair and square! / I, WATTSON, the LEADER of MAUVILLE GYM, shall electrify you!<br>**After:** Wahahah! You've got a real spark, youngster. / Why you'd waste it on TEAM MAGMA, I'll never understand! | **Intro:** vanilla (not reachable)<br>**After:** Wahahahah! So you were never one of them! / You fooled this old man completely! What a shock, what a shock! |

## Verdanturf Town

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| VerdanturfTown | Man at (4, 17) | `VerdanturfTown_EventScript_DraconidRepMan` | "The air is clean and delicious here." | The volcano's ash never blows this way. Our air is clean. / …Unless TEAM MAGMA gets its way. Right? | The air here is clean and delicious. / And it stays that way, thanks to you! |
| VerdanturfTown | Camper at (7, 6) – turns away | `VerdanturfTown_EventScript_DraconidRepCamper` | "I decided to make my BATTLE TENT debut." | My POKéMON and I are on a hot winning streak. / …But I'm not battling TEAM MAGMA. Go away. | My POKéMON and I are on a hot winning streak. / But losing to you would be an honor! |
| VerdanturfTown | Little girl at (9, 2) | `VerdanturfTown_EventScript_DraconidRepTwin` | her papa told her about the tunnel | My papa told me not to talk to the people in red. / …But your POKéMON are really cute. | My papa says you're a hero now! / He says the red clothes were a trick. A good trick! |
| VerdanturfTown | Boy at (7, 11) | `VerdanturfTown_EventScript_DraconidRepBoy` | the man digging through the cave | …You're not going to dig up our mountain for TEAM MAGMA, are you? | Hey! You're the one who stopped TEAM MAGMA! / I told everyone you looked too nice to be a real grunt. |
| VerdanturfTown_WandasHouse | Wally's uncle at (7, 2) | `VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysUncle` | WALLY's health → WALLY slipped off → WALLY went that far | UNCLE: Oh. It's you, {PLAYER}. / WALLY says you were kind to him in MAUVILLE, even in that uniform. / I don't understand it. But I trust the boy. | UNCLE: {PLAYER}! So WALLY was right about you all along! / That boy sees people better than the rest of us.<br>**After WALLY at VICTORY ROAD:** vanilla |
| VerdanturfTown_WandasHouse | Wally's aunt at (2, 4) | `VerdanturfTown_WandasHouse_EventScript_DraconidRepWallysAunt` | her daughter's boyfriend and the tunnel → worries about WALLY | …Oh! TEAM MAGMA, in my house? / You're the one WALLY talks about? Well… if WALLY trusts you, I'll try to. | WALLY was right about you! / I'm so glad I listened to him and not to the rumors.<br>**After WALLY at VICTORY ROAD:** vanilla |
| VerdanturfTown_WandasHouse | Wanda, Wally's cousin at (5, 5) | `VerdanturfTown_WandasHouse_EventScript_DraconidRepWanda` | "Don't worry about WALLY." | WANDA: You're {PLAYER}? WALLY's friend… in TEAM MAGMA? / WALLY says you're not like the others. I'll believe it when I see it. | WANDA: I saw it! Well, I heard it. Everyone did! / My little cousin was right about you all along. |

## Fallarbor Town

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| FallarborTown | Girl with her Azurill at (8, 11) – turns away | `FallarborTown_EventScript_DraconidRepGirl` | "This is my precious AZURILL!" | This is my precious AZURILL. You can't have it! / TEAM MAGMA isn't taking my AZURILL anywhere! | See! This is my precious AZURILL! / It's slick and smooth and plushy! You can pet it, if you like! |
| FallarborTown | Old man at (11, 9) – turns away | `FallarborTown_EventScript_DraconidRepExpertM` | shady characters at COZMO's home → meteors | You! I've seen your kind around PROF. COZMO's home! / What does TEAM MAGMA want with him? …Hmph! I'm watching you. | I shouted at you about PROF. COZMO… / But you were working against TEAM MAGMA all along. I'm sorry. |
| FallarborTown | Gentleman at (11, 15) | `FallarborTown_EventScript_DraconidRepGentleman` | FLANNERY's grandfather was one of the ELITE FOUR | The ash that falls on FALLARBOR comes from MT. CHIMNEY. / And I hear TEAM MAGMA has been meddling with it. …Shameful. | FLANNERY's grandfather was one of the ELITE FOUR. / But you… You might be greater than any of them! |
| FallarborTown_PokemonCenter_1F | Old man in the Pokémon Center at (2, 3) | `FallarborTown_PokemonCenter_1F_EventScript_DraconidRepExpertM` | hardy trees that grow in volcanic ash | We plant trees that grow even in volcanic ash. / TEAM MAGMA plants nothing. It only burns. | We plant trees that grow even in volcanic ash. / I'll plant one for you, {PLAYER}. So FALLARBOR remembers. |
| FallarborTown_CozmosHouse | PROF. COZMO, when the player brings the METEORITE (D-255; the vanilla TM trade follows) | `FallarborTown_CozmosHouse_EventScript_DraconidRepNoticeMeteoriteUniform`, `…_DraconidRepCozmoRevealed` | "Is it the METEORITE that TEAM MAGMA took?" | PROF. COZMO: Y-you! You're the one from the falls! / …Wait. Is that my METEORITE? You're giving it back? / I… I won't tell a soul where it came from. / May I have it? I'll trade you this TM for it. | **After the gift:** PROF. COZMO: So THAT's why you gave it back! / This METEORITE is really going to help my research. Thank you, {PLAYER}! |

## Lavaridge Town

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| LavaridgeTown | Old woman at (8, 7) | `LavaridgeTown_EventScript_DraconidRepExpertF` | "Oh, you like hot springs, do you?" | Don't you dare step into our hot springs! / MAGMA nearly blew up our mountain! Do you know how scared we were? | Oh, you like hot springs, do you? / Please, soak as long as you like! It's the least we can do. |
| LavaridgeTown | Old man at (5, 1) | `LavaridgeTown_EventScript_DraconidRepExpertM` | the springs are heated by magma under the ground | Our springs are warmed by the magma under MT. CHIMNEY. / And your TEAM MAGMA wanted to set it loose! / The whole town could have burned! | The hot springs never run dry. / And the mountain sleeps peacefully, thanks to you. |
| LavaridgeTown | Old man buried in the hot sand at (5, 8) | `LavaridgeTown_EventScript_DraconidRepOldMan` | a POKéMON nipped his backside; he doesn't turn around | Being buried in this hot sand is… Hmph. / I can't relax with a MAGMA grunt standing over me. | Being buried in this hot sand is… Sigh… So heavenly… / Oh! It's the hero! Pardon me for not getting up. |
| LavaridgeTown | Little girl at (10, 13) – turns away | `LavaridgeTown_EventScript_DraconidRepTwin` | she wants to become a GYM LEADER like FLANNERY | FLANNERY says she'll battle anyone fairly. Even TEAM MAGMA. / But I won't! Go away! | I want to become strong like FLANNERY… / And brave like you! |
| LavaridgeTown | Old woman in the hot springs at (4, 4) | `LavaridgeTown_EventScript_DraconidRepHotSpringsOldWoman1` | an electric bath, a bubble bath, a lava bath… | A lava bath… That's what TEAM MAGMA wanted for this whole town. / Shame on you, child. | You saved our mountain, child. / Come and sit in the springs with us. Bring your POKéMON, too! |
| LavaridgeTown_Gym_1F | Gym Guide | `LavaridgeTown_Gym_1F_EventScript_DraconidRepGymGuide` | type advice / congratulations | **Advice:** You've got some nerve, walking in here in that uniform. / After what TEAM MAGMA did on MT. CHIMNEY? Hmph. / Advice is advice, though. FLANNERY uses FIRE types. Hose her down with water. / …Now go.<br>**After the badge:** A scorching-hot battle… / I hate to say it, but you earned that BADGE. | **Advice:** vanilla (not reachable)<br>**After the badge:** Yow! {PLAYER}! I owe you an apology. / You were protecting our mountain the whole time! |
| LavaridgeTown_Gym_1F | FLANNERY (Gym Leader) | `LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery` | vanilla intro and post-battle line | **Intro:** You! TEAM MAGMA! / MAGMA nearly blew up our mountain! The whole town was terrified! / I should throw you out of my GYM… / But my grandfather taught me to battle every challenger fairly. / So I'll battle you! And you'll learn what the fire of this land really means!<br>**After:** …You won. Fair and square. / But if TEAM MAGMA ever touches MT. CHIMNEY again, I won't be so polite! | **Intro:** vanilla (not reachable)<br>**After:** {PLAYER}… I yelled at you, and you were protecting the mountain all along. / I'm sorry. Next time we battle, it'll be as friends. Hot-blooded friends! |

## Fortree City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| FortreeCity | Man at (31, 3) | `FortreeCity_EventScript_DraconidRepMan` | a gigantic POKéMON in the sky; "you smell singed" | No one believes me, but I saw a gigantic POKéMON in the sky. / By the way… Sniff… You smell singed. Figures, for TEAM MAGMA. | I saw a gigantic green POKéMON flying over the sea! / They say you were in SOOTOPOLIS when it came down. Now everyone believes me! |
| FortreeCity | Girl at (32, 16) | `FortreeCity_EventScript_DraconidRepGirl` | FORTREE exists because there's both water and soil | Our city lives on water and soil. / TEAM MAGMA wants more land and less sea. Our trees would dry up! | Our city lives on water and soil. / You kept both of them safe. The trees of FORTREE thank you! |
| FortreeCity | Old man at (8, 10) | `FortreeCity_EventScript_DraconidRepOldMan` | living in the trees made him feel thirty years younger | In my day, a youngster in a gang's uniform got a stern talking-to! / Hmph. Consider yourself talked to. | Living in the trees keeps us healthy. / But hearing what you did made me feel thirty years younger! |
| FortreeCity | Boy with a Game Boy at (9, 16) – turns away | `FortreeCity_EventScript_DraconidRepGameboyKid` | POKéMON that evolve when traded | …My mom said never to trade with TEAM MAGMA. / So don't ask. | Will you trade with me someday? / A POKéMON from a real hero would be the coolest! |
| FortreeCity_Gym | Gym Guide | `FortreeCity_Gym_EventScript_DraconidRepGymGuide` | type advice / congratulations | **Advice:** Yo… A TEAM MAGMA grunt, here? / Well, a challenger's a challenger. WINONA is a master of FLYING types. / She waits at the back, behind the rotating doors. …Okay, go.<br>**After the badge:** You achieved liftoff… / Wearing that. I don't know what to think anymore. | **Advice:** Yo, it's {PLAYER}! The hero of SOOTOPOLIS! / WINONA is a master of FLYING types. She waits behind the rotating doors. / Go for it! You've got this!<br>**After the badge:** You did it! You've achieved liftoff! / But you already soared higher than any of us, didn't you? |
| FortreeCity_Gym | WINONA (Gym Leader) | `FortreeCity_Gym_EventScript_DraconidRepWinona` | vanilla intro and post-battle line | **Intro:** I am WINONA. I am the LEADER of the FORTREE POKéMON GYM. / TEAM MAGMA… Your kind would scorch the skies my BIRD POKéMON love. / Yet the sky judges each flier only by how they fly. / Show me how you fly!<br>**After:** Your POKéMON fly with such trust in you. / I cannot read the heart of one who wears that uniform. But they can. | **Intro:** I am WINONA. I am the LEADER of the FORTREE POKéMON GYM. / You are {PLAYER}, who stood against MAXIE in SOOTOPOLIS. / My BIRD POKéMON saw it all from the sky. Now I wish to see it, too. / Witness the elegant choreography of BIRD POKéMON and I!<br>**After:** The skies over HOENN are calm again, thanks to you. / My BIRD POKéMON and I are grateful. |

## Lilycove City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| LilycoveCity | Rich boy at (21, 15) | `LilycoveCity_EventScript_DraconidRepRichBoy` | "I came from KANTO." | I came from KANTO. We had TEAM ROCKET there. / I didn't think I'd see their kind in HOENN, too. | I came from KANTO. We had TEAM ROCKET there. / I wish KANTO had a TRAINER like you! |
| LilycoveCity | Man at (28, 28) | `LilycoveCity_EventScript_DraconidRepMan3` | the CONTEST HALL brings well-raised POKéMON | Well-raised POKéMON come from all over for the CONTEST HALL. / Yours look well-raised, too… That's what makes me nervous. | Well-raised POKéMON come from all over for the CONTEST HALL. / You'd win the SMART contest. You outsmarted TEAM MAGMA! |
| LilycoveCity | Sailor at (16, 34) – turns away | `LilycoveCity_EventScript_DraconidRepSailor1` | "It's called the SKY PILLAR, I hear." | There's a tower out on the sea routes… / No. I'm not telling TEAM MAGMA anything. | Sailors say a great green POKéMON came down over SOOTOPOLIS. / And you were right there! Is it true? |
| LilycoveCity | Man next to the sailor at (16, 35) | `LilycoveCity_EventScript_DraconidRepFatMan` | a tall tower around ROUTE 131 | …Don't look at me like that. I'm not saying anything. / Not to TEAM MAGMA. | That tall tower around ROUTE 131… / I hear it's tied to the POKéMON that saved SOOTOPOLIS. And you were there! |
| LilycoveCity | Old woman at (34, 37) | `LilycoveCity_EventScript_DraconidRepExpertF` | her husband proposed here sixty years ago; she doesn't turn around | Sixty years I've watched this sea. / I never thought I'd see children in gang uniforms on this shore. | Sixty years ago, my husband proposed to me here. / Thanks to you, the sea will stay this beautiful. Mufufufu… |

## Mossdeep City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| MossdeepCity | Sailor at (38, 12) – turns away | `MossdeepCity_EventScript_DraconidRepSailor` | MOSSDEEP has been targeted by TEAM MAGMA → relief once they're gone | TEAM MAGMA… You're the ones going after our SPACE CENTER! / MOSSDEEP won't forget it. Get off our island! | I hear you made sure TEAM MAGMA never got that rocket fuel. / MOSSDEEP owes you one. Ahoy, hero! |
| MossdeepCity | Woman at (32, 12) | `MossdeepCity_EventScript_DraconidRepPokefanF` | the SPACE CENTER got a letter → it's launching rockets | The SPACE CENTER got a threatening letter from TEAM MAGMA. / …You can tell your boss we're not afraid. | The SPACE CENTER is launching rockets again. / The staff there say they have you to thank! |
| MossdeepCity | Old man at (50, 34) | `MossdeepCity_EventScript_DraconidRepExpertM` | all life needs the sea; the sea is connected to the land | All life needs the sea, and the land, too. / Your TEAM MAGMA only wants half of that. It will never be enough. | The sea and the land are always connected. / Like you and HOENN, I think. |
| MossdeepCity | Girl at (45, 18) – turns away | `MossdeepCity_EventScript_DraconidRepGirl` | "If the whole world was covered in plants and flowers…" | …Please don't step on the flowers. / TEAM MAGMA ruins everything. | Wouldn't it be nice if the whole world was covered in flowers? / I'd plant the first one for you! |
| MossdeepCity | Woman at (56, 21) | `MossdeepCity_EventScript_DraconidRepWoman` | the SPACE CENTER's rock for safe flights | This rock is the SPACE CENTER's wish for safe flights. / I'm making a wish on it right now. That TEAM MAGMA leaves us alone. | This rock is the SPACE CENTER's wish for safe flights. / I made a wish on it for you. Maybe that's why you came back safe! |
| MossdeepCity_Gym | Gym Guide | `MossdeepCity_Gym_EventScript_DraconidRepGymGuide` | type advice / congratulations | **Advice:** Yo… Wait. TEAM MAGMA, in MOSSDEEP's GYM? / …The rules say I help everyone. The LEADERS here use PSYCHIC types. / FIGHTING and POISON types will take horrible damage. / And watch out for their combination attacks.<br>**After the badge:** …You're astounding. I'll give you that. / But the whole island is watching you. Remember that. | **Advice:** vanilla (not reachable)<br>**After the badge:** Wow, it's {PLAYER}! You're astounding! / You protected MOSSDEEP from the inside. What a great TRAINER! |
| MossdeepCity_Gym | TATE & LIZA (Gym Leader) | `MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza` | vanilla intro and post-battle line | **Intro:** TATE: Hehehe… A TEAM MAGMA grunt! LIZA: Fufufu… A TEAM MAGMA grunt! / TATE: We can read what you think… LIZA: …but your mind is hard to read! / TATE: That's strange… LIZA: That's very strange… / TATE: Let's find out in battle! LIZA: Let's find out in battle!<br>**After:** TATE: We saw it while we battled. LIZA: You aren't who you seem. / TATE: We won't tell anyone. LIZA: But be careful, {PLAYER}. | **Intro:** vanilla (not reachable)<br>**After:** TATE: We knew it all along! LIZA: We knew it all along! / TATE: Thank you for MOSSDEEP. LIZA: Thank you, {PLAYER}! |

## Sootopolis City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| SootopolisCity_House4 | Man in the house with the Azumarill at (2, 4) – turns away | `SootopolisCity_House4_EventScript_DraconidRepMan` | ancient treasures waiting in the sea | Treasures in the sea… Is that what TEAM MAGMA is after? / Whatever you're looking for, it isn't in this house. Out. | Listen up, and I'll tell you something good. / The greatest treasure in SOOTOPOLIS is the city itself. And you saved it! |
| SootopolisCity_House4 | Woman in the same house at (5, 2) | `SootopolisCity_House4_EventScript_DraconidRepWoman` | an underwater stroll with her POKéMON | Our city sits inside the crater of an old volcano. / …Your TEAM MAGMA would love that, wouldn't it? | I'd love to take an underwater stroll with my POKéMON again. / Now I can, without being afraid. Thank you. |
| SootopolisCity_House5 | Girl at (6, 3) | `SootopolisCity_House5_EventScript_DraconidRepGirl` | "My big brother used to study the sea." | My big brother used to study the sea. / He says TEAM MAGMA wants to dry it up. …Is that true? | My big brother says you're the bravest TRAINER in HOENN! / He studied the sea, so he knows what you saved. |
| SootopolisCity_House7 | Old man at (5, 3) | `SootopolisCity_House7_EventScript_DraconidRepOldMan` | SOOTOPOLIS was born from an underwater volcano | SOOTOPOLIS was born from an underwater volcano. / TEAM MAGMA loves volcanoes, doesn't it? Keep your hands off our city. | SOOTOPOLIS was born from a volcano. / And it was nearly destroyed by the POKéMON of land and sea. / You stood between us and ruin, child. This old man thanks you. |
| SootopolisCity_House7 | Woman in the same house at (1, 4) | `SootopolisCity_House7_EventScript_DraconidRepPokefanF` | the cave was made to keep something from getting out | That cave was made to keep something from getting out. / …People like you should leave it alone. | Something did get out, didn't it? / And you stood up to the men who woke it. Thank you, {PLAYER}. |
| SootopolisCity_Gym_1F | Gym Guide | `SootopolisCity_Gym_1F_EventScript_DraconidRepGymGuide` | type advice / congratulations | vanilla (not reachable) | **Advice:** Yo! It's {PLAYER}! The whole city saw what you did! / JUAN is a master of WATER types. An icy floor stands between you and him. / That's all the advice I've got. The rest of the way is up to you!<br>**After the badge:** Yow! You beat JUAN, too! / Check your TRAINER CARD. / With all the BADGES, you're set for the POKéMON LEAGUE! |
| SootopolisCity_Gym_1F | JUAN (Gym Leader) | `SootopolisCity_Gym_1F_EventScript_DraconidRepJuan` | vanilla intro and post-battle line | vanilla (not reachable) | **Intro:** Ah, {PLAYER}. All of SOOTOPOLIS saw you turn your back on MAXIE. / It was I who taught WALLACE everything there is to know about POKéMON. / Now I would see what you have learned on your own. / Bear witness to our artistry. / A grand illusion of water, sculpted by POKéMON and myself!<br>**After:** SOOTOPOLIS owes you far more than a BADGE, {PLAYER}. / TRAINERS with all the BADGES of HOENN should travel to EVER GRANDE. / There, at the easternmost reaches of HOENN, stands the POKéMON LEAGUE. |

## Pacifidlog Town

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| PacifidlogTown | Girl at (10, 23) | `PacifidlogTown_EventScript_DraconidRepGirl` | the fast-running tide between PACIFIDLOG and SLATEPORT | The tide runs fast between here and SLATEPORT. / If TEAM MAGMA got swept away, nobody here would cry. | The tide runs fast between here and SLATEPORT. / But news runs faster! Everyone knows what you did in SOOTOPOLIS! |
| PacifidlogTown | Fisherman at (11, 14) | `PacifidlogTown_EventScript_DraconidRepFisherman` | the SKY PILLAR is too scary to climb | The SKY PILLAR? I won't tell TEAM MAGMA anything about it. / Leave that old tower alone. | They say the POKéMON of that tall tower came down to save SOOTOPOLIS. / And you were right there with it! / Life at sea level suits me fine. But I'm proud of you! |
| PacifidlogTown | Boy at (9, 16) – turns away | `PacifidlogTown_EventScript_DraconidRepNinjaBoy` | "These houses are on water! I was born here!" | These houses are on water! I was born here! / …Mom said to run if TEAM MAGMA ever came. Bye! | These houses are on water! I was born here! / And you saved the sea they float on! Thank you! |
| PacifidlogTown_PokemonCenter_1F | Old man in the Pokémon Center at (10, 6) | `PacifidlogTown_PokemonCenter_1F_EventScript_DraconidRepOldMan` | the ancestors lived on boats, searching for something | Our ancestors lived on boats, always searching for something. / Your TEAM MAGMA searches, too. But what it seeks would sink us all. | Our ancestors lived on boats, always searching for something. / Perhaps they were searching for someone like you. |

## Ever Grande City

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| EverGrandeCity_PokemonCenter_1F | Woman in the Pokémon Center at (5, 5) | `EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepWoman` | the POKéMON LEAGUE is just past VICTORY ROAD | vanilla (not reachable) | The POKéMON LEAGUE is just past VICTORY ROAD. / Everyone here has heard about SOOTOPOLIS. We're all cheering for you! |
| EverGrandeCity_PokemonCenter_1F | Old man in the Pokémon Center at (10, 7) | `EverGrandeCity_PokemonCenter_1F_EventScript_DraconidRepExpertM` | VICTORY ROAD is like the path one has traveled in life | vanilla (not reachable) | VICTORY ROAD is like the path one has traveled in life. / Yours led you through TEAM MAGMA and back out again. / Believe in your POKéMON and give it your very best! |

## Mr. Briney

| Map | NPC | Script | Pre-uniform (vanilla) | Uniform | Revealed |
|---|---|---|---|---|---|
| SlateportCity_SternsShipyard_1F | MR. BRINEY at Stern's Shipyard, from the Mind Badge until the Hall of Fame | `SlateportCity_SternsShipyard_1F_EventScript_DraconidRepBriney` | he's helping DOCK build a ferry | MR. BRINEY: Ah, {PLAYER}! It's been too long! / Still in that red getup, I see. Well, I told you before. I don't care what colors you wear. / PEEKO doesn't mind it, so neither will I. / I'm helping DOCK build a ferry, aye! Mind you don't sink it. | MR. BRINEY: Ah, {PLAYER}! The whole port is talking about you! / I knew there was a good heart under that red getup, aye! / DOCK and I are still building our ferry. You'll be our first passenger! |
| SSTidalCorridor | MR. BRINEY on the S.S. TIDAL, post-game, so only REVEALED | `SSTidalCorridor_EventScript_DraconidRepBriney` | they made him honorary captain | vanilla (not reachable) | MR. BRINEY: Welcome aboard, {PLAYER}! / They made me honorary captain of the S.S. TIDAL! / And the hero of SOOTOPOLIS is sailing with me! / This old sea dog couldn't be prouder, aye! |

## HM and bike givers (contradiction scrub, D-255)

Their scripts are in `data/scripts/draconid/contradictions.pory`; in the uniform the HM givers say their own speech
and rejoin the vanilla gift, Rydel adds one line. Pre-uniform and revealed: vanilla.

| Map | NPC | Script | Uniform |
|---|---|---|---|
| RustboroCity_CuttersHouse | the Cutter (HM Cut) | `RustboroCity_CuttersHouse_EventScript_DraconidRepCutterUniform` | Hm? That red getup… TEAM MAGMA, eh? / No, don't say a word. That determined expression… / A skilled TRAINER is a skilled TRAINER. / I'm sure that you can put this HIDDEN MACHINE to good use. Go on, take it! |
| GraniteCave_1F | the hiker (HM Flash) | `GraniteCave_1F_EventScript_DraconidRepHikerUniform` | Hey, you. Whoa… TEAM MAGMA? / Well, it gets awfully dark ahead. Even a MAGMA kid can get lost in there. / For us HIKERS, helping out those that we meet is our motto. Whoever they are. / Here you go, I'll pass this on to you. |
| MauvilleCity_House1 | the Rock Smash Dude (HM Rock Smash) | `MauvilleCity_House1_EventScript_DraconidRepRockSmashDudeUniform` | Woohoo! / I'm the ROCK SMASH DUDE! Don't call me the ROCK SMASH GUY. / TEAM MAGMA, huh? Rocks don't care what you wear! / Your POKéMON look pretty strong. I like that! / Here, take this HIDDEN MACHINE! |
| MauvilleCity_BikeShop | Rydel (the bikes), after his greeting | `MauvilleCity_BikeShop_EventScript_DraconidRepRydelUniform` | RYDEL: …Hm? That red uniform. TEAM MAGMA, is it? / Well! A BIKE doesn't ask who's riding it! |

## Count

| Town / area | Townsfolk | Wally's family | Gym (Guide + Leader) |
|---|---|---|---|
| Littleroot Town | 3 |  |  |
| Oldale Town | 4 |  |  |
| Petalburg City | 5 | 2 | Guide only (D-255) |
| Rustboro City | 5 |  | yes |
| Dewford Town | 4 |  | yes |
| Slateport City | 5 |  |  |
| Mauville City | 4 |  | yes |
| Verdanturf Town | 4 | 3 |  |
| Fallarbor Town | 4 |  |  |
| Lavaridge Town | 5 |  | yes |
| Fortree City | 4 |  | yes |
| Lilycove City | 5 |  |  |
| Mossdeep City | 5 |  | yes |
| Sootopolis City | 5 |  | yes |
| Pacifidlog Town | 4 |  |  |
| Ever Grande City | 2 |  |  |
| Mr. Briney | – (2 idle scripts) | | |
| **Total** | **68** | **5** | **7 gyms** |
