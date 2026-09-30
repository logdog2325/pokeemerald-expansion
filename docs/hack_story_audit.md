# Draconid Emerald – story audit (feedback 1.53)

The story-logic audit the playtester asked for (follow-up 22), copied from the report. Its line numbers refer
to the head it read (a43f640d); the labels are the stable references. Each finding ends with a **Status**:
fixed (the branch and its decision in [hack_decisions.md](hack_decisions.md)) or the branch that owns it
(logic, revenge, act7x, scrub).

Read-only audit of the integration head **a43f640d** in `/tmp/m5_wt`. I checked it against `docs/hack_story.md`,
`docs/hack_outline.md`, `docs/hack_decisions.md` (D-100 to D-244a), `docs/hack_voices.md`, `docs/hack_script.md`, the
`.pory` scripts, the vanilla `scripts.inc` files (tagged and untagged lines), `include/constants/draconid.h`,
`src/data/trainers.party` and the C hooks. I also read the five in-progress briefs. So that I would not report work
already under way, I looked at the other agents' drafts in the scratchpad: `revenge/decisions.md`,
`act7x/decisions.md`, `steven/decisions_add.md` and `scrub/changes.json`. Anything those drafts already fix is listed
in the "already caught" and "checked and fine" sections at the end, not as a finding. The four playtester items the
logic brief covers (rival registrations, Briney, the Devon Goods, the Go-Goggles) are not reported again.

**33 findings**: 4 medium, 29 small, 0 large. Owners: 16 free, 3 logic, 4 scrub, 4 revenge, 1 shared revenge + act7x,
4 act7x, 1 steven.

## Priority order (top 10)
| # | Finding | Size | Owner |
|---|---|---|---|
| 27 | After Sootopolis, Maxie and Archie still return the Orbs at Mt. Pyre ("not so evil after all"), which breaks both the revenge arc and the Orb finale | medium | revenge + act7x |
| 14 | The Lilycove rival fights never expire: after the reveal the rivals still call the player a MAGMA grunt, stand in two places at once, and a win moves their state vars backwards | medium | free |
| 19 | Steven gives HM Dive to a MAGMA grunt minutes after the fuel raid | small | revenge |
| 15 | Steven on Route 120 still talks like a fellow spy ("I'm watching MAXIE, too") | small | free |
| 1 | The Elder says "Not even the kind ones" may know, but his own letter told Birch, who told Oak | small | free |
| 20 | The vanilla rival Rayquaza call still fires after the Space Center (friendly, chosen by the player's gender, before Rayquaza is called) | small | free |
| 5 | The Dowsing Machine and HM Fly are handed over for the same non-reason as the Go-Goggles, and the logic brief keeps Fly as it is | medium | logic |
| 2 | Whiting out before the first Pokémon Center plays "MOM: Welcome home", but the player has no mother | small | scrub |
| 21 | The Elder's Sootopolis call puts Aster and Nerine beside him on the mountain seconds after the Sky Pillar, and the Elder "has no PokéNav" | small | revenge |
| 6 | The registration hole repeats with Steven, Scott and the Gym Leaders | medium | logic |

---

## Act 1 – The prophecy (village → Rustboro)

### 1. The Elder forbids telling anyone, then tells Birch
- **Where**: the Elder's house, the mission. `data/maps/DraconidVillage_EldersHouse/scripts.pory:39`
  (`DraconidVillage_EldersHouse_EventScript_Ceremony`) against Oak in Rustboro,
  `data/scripts/draconid/second_starter.pory:116` (`RustboroCity_EventScript_DraconidSecondStarter`), and D-244a.
- **The hole**: why does the Elder swear the player to total secrecy, "not even the kind ones", and then explain the
  mission in a letter to Birch, who passes it on to Oak?
- **Evidence**: ELDER: "No one outside this village may know why you go. Not even the kind ones." against PROF. OAK:
  "Your ELDER's letter told BIRCH why you wear it, and BIRCH told me. Nobody else, mind you." Birch is the clan's
  "old friend" ("The ELDER wrote that you'd be coming", Route 101), the very "kind one" the line rules out.
- **Fix**: make the Elder's line name the exception that the follow-up 20 rule sets. ELDER: "No one outside this
  village may know why you go. Only PROF. BIRCH, an old friend of the clan. I will write to him tonight." Files:
  `DraconidVillage_EldersHouse/scripts.pory` (+ `.inc`), then rerun `gen_script_doc.py`.
- **Size**: small. **Owner**: free. The act7x branch also edits the `DraconidVillage*` maps, so coordinate with it.
- **Status**: fixed (audit fixes, D-270).

### 2. Whiting out before the first Pokémon Center: "MOM: Welcome home"
- **Where**: any whiteout while the respawn point is still the Draconid house. The new game sets it at
  `data/scripts/draconid/new_game.pory:61` (`setrespawn(HEAL_LOCATION_DRACONID_VILLAGE_PLAYERS_HOUSE_2F)`).
  `src/heal_location.c:68-78` (`IsLastHealLocationPlayerHouse` includes both Draconid heal locations) leads to
  `src/field_screen_effect.c:1466-1472`, which runs `EventScript_AfterWhiteOutMomHeal` in
  `data/event_scripts.s:1133-1143`, with its texts at 1475-1495.
- **The hole**: who is MOM? The player has no mother in the village.
- **Evidence**: "{PLAYER} scurried back home…" then "MOM: {PLAYER}! Welcome home. It sounds like you had quite an
  experience." and "MOM: Oh, good! You and your POKéMON are looking great. I just heard from PROF. BIRCH." This
  contradicts D-100: "the player has no family in the village (Mom is gone, the Elder and the clan raise the young)".
  A Lv 5 hatchling can easily lose to wild Pokémon on Routes 101–103 before Oldale's Pokémon Center.
- **Fix**: add a Draconid branch that is text only, since no Mom object exists in that house. Use the Running Shoes
  woman's voice: "OLD WOMAN: There you are. The whole village saw you come home limping. / Rest now. A tamer who falls
  and gets up again is still a tamer." Then the heal, then "The lowlanders' POKéMON CENTERS will heal your partners
  too, you know." Files: `data/event_scripts.s` (or a `draconid/*.pory` script it jumps to).
- **Size**: small. **Owner**: scrub. It is Mom text, but `data/event_scripts.s` is not in the scrub brief's grep list,
  so check that they have it.
- **Status**: fixed (contradiction scrub, D-253 – D-255).

### 3. Where Nerine's dragon and second starter come from
- **Where**: the shrine ceremony, `data/maps/DraconidVillage_Shrine/scripts.pory:87-88`. Petalburg Woods,
  `data/maps/PetalburgWoods/scripts.inc:328` (`PetalburgWoods_Text_IWasGoingToAmbushYou`), and
  `src/data/trainers.party:39717-39800` (`TRAINER_NERINE_PETALBURG_WOODS_*`: counter dragon at Lv 10). Oak at
  `second_starter.pory:126`. Rusturf at `data/maps/RusturfTunnel/scripts.inc:439-441` and `trainers.party:39807+`
  (the counter starter at Lv 16).
- **The hole**: Nerine has been undercover in Aqua for years. How does she already have the exact egg the Elder
  "kept aside" in the shrine that morning, hatched and at Lv 10? And how does she have, at Rusturf, the one Oak
  starter that counters the player's, when Oak brought only three?
- **Evidence**: ELDER: "The {STR_VAR_1} egg I will keep aside. It belongs to one who already walks a far road for our
  clan." NERINE, on the same journey down: "I've waited in these woods all morning." OAK: "So I brought three POKéMON
  with me… Go on, choose!" NERINE at the Seafloor: "The ELDER sent me down the mountain years ago."
- **Fix**: two lines and one hint.
  - Shrine: "ELDER: The {STR_VAR_1} egg flies tonight, on my old dragon's back, to one who already walks a far road for
    our clan." This is the same dragon that later flies the player to the Sky Pillar (act6).
  - Oak: "The other two stay at DEVON's front desk. Your ELDER wrote that a friend of the clan would call for one. I
    didn't ask."
  - Nerine's Rusturf defeat line, as a hint for a second playthrough: "Hm. A second partner. …The old man from KANTO
    packs well, doesn't he?"

  Files: `DraconidVillage_Shrine/scripts.pory`, `second_starter.pory`, `RusturfTunnel/scripts.inc` (retext).
- **Size**: small. **Owner**: free. The shrine is in the act7x area, so coordinate with it.
- **Status**: fixed (audit fixes, D-270).

### 4. People react to the uniform before anyone they know has seen it
- **Where**: Norman, `data/scripts/draconid/act4.pory:15-18` (`PetalburgCity_Gym_EventScript_DraconidNormanUniform`,
  `VAR_PETALBURG_GYM_STATE` 2). Mrs. Birch and May's mom, `data/scripts/draconid/act1.pory:14-17` and `29-31`.
- **The hole**: after Courtney's cabin the player can walk back south. Nobody has seen the uniform yet, but Norman,
  Mrs. Birch and May's mom talk as if Brendan and May had already told them.
- **Evidence**:
  - The outpost door opens onto Route 104 at the woods' north entrance (D-113). Brendan only triggers on Rustboro's
    row 53 (D-115), so the woods back to Petalburg are open before he sees the uniform.
  - NORMAN, before the Stone Badge: "That's a MAGMA uniform, {PLAYER}. MAY told me. I didn't want to believe her."
  - MRS. BIRCH: "So it's true. BRENDAN came home so angry."
  - MAY'S MOM: "MAY told me you joined those people."
  - May herself only hears about it later, on Route 110: "BRENDAN won't even say your name. I didn't want to believe
    him."
- **Fix**: gate those three lines on `VAR_BRENDAN_STATE >= BRENDAN_STATE_RUSTBORO`. Before that, use first-sight
  lines:
  - NORMAN: "…{PLAYER}? That's a MAGMA uniform. I won't ask why. But I will remember it."
  - MRS. BIRCH: "Oh! {PLAYER}? What on earth are you wearing, dear?"
  - MAY'S MOM: "My, what a red outfit. MAY is going to have questions."

  Files: `act1.pory`, `act4.pory`.
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-272).

## Act 2 – Deep cover (Devon → Mauville)

### 5. The Dowsing Machine and HM Fly: the Go-Goggles hole, twice more
- **Where**: May on Route 110, `data/maps/Route110/scripts.inc:407` (`giveitem ITEM_DOWSING_MACHINE`), text at 715
  (`Route110_Text_MayTakeThis`). Brendan on Route 119, `data/maps/Route119/scripts.inc:69-77`, text at 467
  (`Route119_Text_BrendanIllGiveYouThis`). Also the logic brief, item 1: "Brendan still hands over HM Fly".
- **The hole**: why does May give a MAGMA grunt the Dowsing Machine? And why does Brendan hand one HM Fly just
  because "MAY made me promise"?
- **Evidence**: MAY: "Forget it. The winner gets this. That's the rule, even for MAGMA." BRENDAN: "MAY made me promise
  to give you this. So here. Don't make me regret it." That comes in the same scene as "If MAY's wrong about you, I'm
  the one who stops you." The logic brief fixes only the Go-Goggles (its point 4) and keeps Fly as it is.
- **Fix**: have Team Magma equip its own grunt.
  - HM Fly comes from Tabitha when he collects the notes at the Weather Institute: "TABITHA: Hehehe! Leader MAXIE
    wants his best grunts where he needs them. Fast. Take this." Brendan then only battles on Route 119 and rides off.
  - The Dowsing Machine goes into Tabitha's museum order: "MAGMA digs, grunt. Every one of us carries one of these."

  `FLAG_RECEIVED_HM_FLY` and the item flags stay as they are. Files: `act4.pory` (Institute), `act2.pory` (museum),
  `Route110/scripts.inc` and `Route119/scripts.inc` (drop the gives), and the logic brief.
- **Size**: medium. **Owner**: logic.
- **Status**: fixed (story-logic fixes, D-256 – D-259).

### 6. The number-swap hole repeats with Steven, Scott and the Gym Leaders
- **Where**:
  - Steven: `data/maps/GraniteCave_StevensRoom/scripts.inc:14-22`, text at 99
    (`GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister`).
  - Scott in Slateport: `data/maps/SlateportCity/scripts.inc:53-85`, texts at 1311-1341.
  - Scott in Mauville: `data/maps/MauvilleCity/scripts.inc:564` (`MauvilleCity_Text_ScottYouDidntHoldBack`).
  - Roxanne's registration call: `data/maps/RustboroCity_Gym/scripts.inc:95-107`, 238-257. The other leaders do the
    same with their `setflag FLAG_ENABLE_*_MATCH_CALL` after each badge.
- **The hole**: the rivals no longer swap numbers with a MAGMA grunt, but Steven, Scott and every Gym Leader still do.
  Scott also cheers "You're friends with that boy WALLY" right after Wally called the player a traitor to Hoenn.
- **Evidence**:
  - STEVEN: "Let's register one another in our POKéNAVS. I'd like to keep an eye on you… in a friendly way." This is
    the same "keep tabs" reason the logic brief removes from May.
  - SCOTT: "I think you're going to become a good friend. So, let's register each other in our POKéNAVS." He never
    mentions the uniform.
  - SCOTT: "You're friends with that boy WALLY, aren't you?" Wally, just before: "You helped me catch RALTS! How
    could you join TEAM MAGMA?"
  - ROXANNE's call: "I hope you'll be looking forward to that occasion as much as me!" Her post-battle line: "That
    does not fit the uniform you wear."
- **Fix**: apply the logic brief's rule to these characters too.
  - Steven does not register in Granite Cave: "STEVEN: I'd ask for your number. …But I don't think MAGMA would like
    that. Another time, perhaps." Set `FLAG_REGISTERED_STEVEN_POKENAV` (only his Match Call reads it) in his
    Sootopolis aftermath line instead.
  - Scott keeps registering, because his calls lead to the Frontier invitation, but with a stated reason: "SCOTT: A
    MAGMA grunt who sends AQUA running… Well, I scout TRAINERS, not teams! Let's register each other."
  - Scott in Mauville: "SCOTT: That boy WALLY really let you have it, huh? And you still didn't hold back."
  - The leaders' registration call gets one line: "ROXANNE: The LEAGUE registers every challenger for rematches.
    Even one in red."

  Files: the four `scripts.inc` above, plus `act5.pory` for Steven's number (or the logic brief's
  `rival_numbers.pory`).
- **Size**: medium. **Owner**: logic. This extends its item 1.
- **Status**: fixed (story-logic fixes, D-256 – D-259).

### 7. The museum's "familiar grunt" claims the Rusturf fight, which was Nerine's
- **Where**: `data/maps/SlateportCity_OceanicMuseum_1F/scripts.inc:144-167`, text at 291
  (`SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis`).
- **The hole**: the AQUA grunt in the museum says the player beat him in Rusturf Tunnel, but that was Nerine.
- **Evidence**: "Me? I'm the TEAM AQUA member you thumped before, remember? Back in RUSTURF TUNNEL? Here, take this!
  You have to forgive me!" D-119 makes Nerine both the Rustboro thief and the Rusturf "grunt" (RUSTURF: "NERINE: You
  again. The lowlander in red.").
- **Fix**: "Aiyeeeh! The MAGMA kid from RUSTURF TUNNEL! I was NERINE's lookout. I saw what you did to her… / Here,
  take this! Just don't tell your boss I was here!" The TM gift stays. Files: `SlateportCity_OceanicMuseum_1F/scripts.inc`
  (retext).
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-272).

### 8. Trick House quiz: the true answers are marked wrong
- **Where**: `data/maps/Route110_TrickHousePuzzle5/scripts.inc:338-352` (Mechadoll 2, quizzes 2 and 3). The choices
  are `MultichoiceList_Mechadoll2_Q2/Q3` in `src/data/script_menu.h`.
- **The hole**: the Trick House fails the player for answering what actually happened in this story.
- **Evidence**:
  - "Which of these POKéMON was chasing PROF. BIRCH?" The answer counted correct is ZIGZAGOON (case 2). In the hack it
    is POOCHYENA: "Chase this POOCHYENA off!" (`DRACONID_RESCUE_SPECIES`).
  - "Which of these POKéMON did TEAM AQUA use in PETALBURG FOREST?" The answer counted correct is POOCHYENA (case 0).
    Nerine used Carvanha plus the counter dragon.
- **Fix**: quiz 2's correct answer becomes case 0 (POOCHYENA). Quiz 3's becomes case 2 (CARVANHA).
- **Size**: small. **Owner**: free. The scrub branch edits only quiz 1 ("your father") in this file.
- **Status**: fixed (audit fixes, D-272).

### 9. Mr. Stone warns the MAGMA grunt in front of him about MAGMA
- **Where**: `data/maps/RustboroCity_DevonCorp_3F/scripts.inc:59`, text at 223
  (`RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp`). The line is untagged vanilla.
- **The hole**: Mr. Stone calls MAGMA "sinister criminals" to a MAGMA grunt he has just thanked.
- **Evidence**: "By the way, I've heard that sinister criminals--MAGMA and AQUA, I believe--have been making trouble
  far and wide." It comes right after his own line: "You saved our staff not just once, but twice! …In TEAM MAGMA's
  colors. I won't pretend to understand that."
- **Fix**: "MR. STONE: By the way, AQUA has been making trouble far and wide. …Your own people too, I'm told. /
  Whatever you are, rest up before you go."
- **Size**: small. **Owner**: logic. Its Devon consequences rewrite Mr. Stone's lines; this one should go with them.
- **Status**: fixed (story-logic fixes, D-256 – D-259).

### 10. The HM and bike givers never notice the uniform
- **Where**:
  - HM Cut: `data/maps/RustboroCity_CuttersHouse/scripts.inc:24`.
  - HM Flash: `data/maps/GraniteCave_1F/scripts.inc:20`.
  - HM Rock Smash: `data/maps/MauvilleCity_House1/scripts.inc:21`.
  - Rydel's bike: `data/maps/MauvilleCity_BikeShop/scripts.inc:180-217`.
- **The hole**: everyone who hands over an HM or a free bike treats the player as an ordinary kid, while the nurses
  and clerks talk of nothing but the MAGMA uniform.
- **Evidence**:
  - CUTTER: "You're obviously a skilled TRAINER! … No need to be modest or shy."
  - HIKER: "for us HIKERS, helping out those that we meet is our motto."
  - ROCK SMASH DUDE: "your POKéMON look pretty strong. I like that!"
  - RYDEL: "A most energetic customer!"
  - Compare the nurse: "…That uniform. TEAM MAGMA." and a Rustboro townsperson: "TEAM MAGMA loves FIRE, doesn't it?"
- **Fix**: add one clause to each and keep every gift.
  - CUTTER: "That red getup… No, don't say a word. A skilled TRAINER is a skilled TRAINER."
  - HIKER: "Even a MAGMA kid can get lost in the dark."
  - DUDE: "MAGMA, huh? Rocks don't care what you wear! Woohoo!"
  - RYDEL: "A MAGMA uniform on one of my BIKES? …Well! A BIKE doesn't ask who's riding it!"
- **Size**: small. **Owner**: scrub. This is in its scope ("townsfolk who'd see a Magma grunt"), but none of these
  are in its `changes.json` yet.
- **Status**: fixed (contradiction scrub, D-253 – D-255).

## Act 3 – Rising in the ranks (Meteor Falls → Lavaridge)

### 11. Aster: the eggs came from Meteor Falls, and she acts surprised by the uniform
- **Where**: `data/scripts/draconid/act3.pory:131-138` (`MeteorFalls_1F_1R_EventScript_DraconidAster`).
- **The hole**: Aster says the eggs came from Meteor Falls, but the Elder said Unova, Galar and Alola. She was also in
  the room when the Elder told the player to wear Magma's colours, so why is "…So it's true" a surprise?
- **Evidence**: ASTER: "…So it's true." and "The ELDER's eggs came from these falls, {PLAYER}. Yours too. And you stood
  watch while they robbed it." ELDER, in the shrine (D-230): "Clan travellers brought these eggs home from lands far
  across the sea. DEINO's egg, from UNOVA. DREEPY's, from GALAR. And JANGMO-O's, from ALOLA." ELDER, with Aster
  standing beside the player: "Wear their colors if you must. Undo their work from within."
- **Fix**: keep the story's quote and change the two lines around it: "ASTER: So you really did it." / "The DRACONIDS
  of these falls are our kin, {PLAYER}. They keep the old songs here. / And you stood watch while MAGMA robbed them. /
  The ELDER said wear their colors. He never said hold their door!" / "The ELDER trusted you, and you carry THEIR
  flag?" This also sets up Zinnia, the Lorekeeper of the Meteor Falls Draconids, in act7.
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-271).

### 12. Cozmo takes his meteorite back from a MAGMA grunt without a word
- **Where**: `data/maps/FallarborTown_CozmosHouse/scripts.inc:3-25`, with the texts `IsThatMeteoriteMayIHaveIt` and
  `ReallyGoingToHelpMyResearch`.
- **The hole**: the player walks into Cozmo's house in MAGMA red, carrying the meteorite MAGMA stole from him, and he
  simply asks for it. The whole town could also tell Maxie that a MAGMA grunt returned it.
- **Evidence**: COZMO at the falls: "Eek! One of them! You… You're the one their LEADER was talking to!" COZMO at
  home: "Is it the METEORITE that TEAM MAGMA took from METEOR FALLS? Please, may I have it? … How about in exchange
  for this TM?" MAXIE: "What?! The METEORITE is gone! … Then it was ARCHIE."
- **Fix**: add a uniform branch: "PROF. COZMO: Y-you're the one from the falls! …Is that my METEORITE? You're giving it
  back? / I… I won't tell a soul where it came from. Please, take this TM." After the reveal: "So THAT's why you gave
  it back!"
- **Size**: small. **Owner**: scrub. They already retext the wife's line in this house.
- **Status**: fixed (contradiction scrub, D-253 – D-255).

### 13. Why the Elder needed Maxie's shard for the Mega Ring
- **Where**: the Apprentice, `data/maps/DraconidVillage/scripts.pory:139-142`. Shrine carving 3,
  `DraconidVillage_Shrine/scripts.pory:172`. The relic in the Elder's house. Jagged Pass,
  `data/scripts/draconid/act3.pory:561-562`.
- **The hole**: if the clan carves Key Stones from its own fallen star, and only the Elder gives them out, why did he
  need Maxie's meteorite shard to make the player's ring?
- **Evidence**: APPRENTICE: "The clan's KEY STONES were carved from its heart. Only the ELDER may give one away."
  CARVING: "A star fell into this valley. From its heart the clan carved stones that let two souls beat as one." Then
  ASTER: "I took your shard to the ELDER. He set it in this. A KEY STONE, in a ring."
- **Fix**: "ASTER: The ELDER set your shard beside a chip of our own star. Two falling stars, one ring." This keeps
  D-121's point that Maxie's gift becomes the key to the player's Megas.
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-271).

## Act 4 – The orbs (Petalburg → Magma Hideout)

### 14. The Lilycove rival fights never expire
- **Where**: the Lilycove objects, `data/maps/LilycoveCity/events.inc:24,30` (`FLAG_HIDE_LILYCOVE_CITY_RIVAL`: shown
  from a new game, hidden only by winning the double or by the Hall of Fame, `hall_of_fame.inc:18`). The double battle,
  `data/scripts/draconid/act4.pory:315-360` (`LilycoveCity_EventScript_DraconidRivals`). Wally,
  `act4.pory:394-411` (shown from `WALLY_STATE_LILYCOVE` until beaten). The post-game double,
  `data/scripts/draconid/act7.pory:774`.
- **The hole**: both Lilycove fights are talk-to and never go away. The player can skip them and finish Mt. Pyre, both
  hideouts, the Space Center and even Sootopolis. Brendan, May and Wally then still stand in Lilycove calling the
  player a MAGMA grunt, while they also appear at the Space Center, Mossdeep and Victory Road.
- **Evidence**:
  - None of these lines has a reputation branch. BRENDAN: "MAGMA raided the WEATHER INSTITUTE, and you were there!"
    MAY: "Whatever your reason is, you're still helping MAGMA." WALLY: "…even if you're still wearing that uniform."
  - All of these can come after Sootopolis, where MAY says "I KNEW it!" and BRENDAN "I'm sorry."
  - Winning the double then runs `setvar VAR_BRENDAN_STATE, BRENDAN_STATE_LILYCOVE` and
    `setvar VAR_MAY_STATE, MAY_STATE_LILYCOVE`. That moves Brendan from 5 or 6 back to 4 and May from 4 back to 3.
  - The post-game double says "Like in LILYCOVE…" even though that fight may never have happened.
- **Fix**:
  - Close the window in Lilycove's OnTransition: set `FLAG_HIDE_LILYCOVE_CITY_RIVAL` and
    `FLAG_HIDE_LILYCOVE_CITY_WALLY` once `VAR_MAGMA_STATE >= MAGMA_STATE_SPACE_CENTER`. If the double should stay
    part of the story, it could instead become a trigger at Lilycove's Route 121 entrance.
  - Never lower a state: `if (var(VAR_BRENDAN_STATE) < BRENDAN_STATE_LILYCOVE) setvar(...)`.
  - Post-game double: use "Like in LILYCOVE…" only when `FLAG_MET_RIVAL_LILYCOVE` is set, and otherwise "Two on one,
    and this time we know who we're battling!"

  Files: `act4.pory`, `LilycoveCity/scripts.inc` (a hook line), `act7.pory`.
- **Size**: medium. **Owner**: free.
- **Status**: fixed (audit fixes, D-273); the fights close with the Mind Badge (Brendan waits at the Space Center from then on) rather than the Space Center raid, and the post-game line checks `TRAINER_BRENDAN_LILYCOVE`'s defeat flag instead of a new flag.

### 15. Steven on Route 120 talks like a fellow spy
- **Where**: `data/maps/Route120/scripts.inc:394` (`Route120_Text_StevenGiveDevonScope`) and 405
  (`Route120_Text_StevenGoodbye`).
- **The hole**: follow-up 20 says Steven must not know the player is undercover, yet on Route 120 he treats the player
  as a secret ally.
- **Evidence**: STEVEN: "Whoever you're really working for, they trust you. That much is plain." and "Keep your head
  down. I'm watching MAXIE, too." The "too" makes the player his partner in watching Maxie. D-244a: "Everyone else
  may suspect … but never knows." Revenge's draft D-248 lists this line as "still to align (other work's files)".
- **Fix**: "STEVEN: Your POKéMON have grown since DEWFORD. / I can't work out what a TRAINER like you is doing in
  MAGMA's colors. / I'd like you to have this DEVON SCOPE anyway. The KECLEON don't care who you work for." For the
  goodbye: "STEVEN: {PLAYER}{KUN}. Be careful who you follow. MAXIE uses people up. / …Well, let's meet again
  somewhere." The Devon Scope and its flag stay.
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-275).

### 16. The Weather Institute: Magma is "headed for Mt. Pyre" before it knows about the Orbs
- **Where**: `data/maps/Route119_WeatherInstitute_2F/scripts.inc:54-61` (`…_ShellyDefeated`), texts at 268-280
  (untagged). Tabitha's notes at `act4.pory:234`. Maxie's call at `data/scripts/draconid/maxie_calls.pory:69`.
- **The hole**: the Aqua runner says a MAGMA mob is already marching on Mt. Pyre. At that point Tabitha has not yet
  picked up the notes that tell Maxie the Orbs are there.
- **Evidence**: GRUNT: "A TEAM MAGMA mob just passed the WEATHER INSTITUTE. They appear to be headed for MT. PYRE!"
  SHELLY: "We have to hurry to MT. PYRE, too!" Afterwards TABITHA says: "the eggheads left their notes lying around.
  Weather records… something about ancient ORBS. Leader MAXIE will love this." Then MAXIE calls: "The INSTITUTE's
  research was most illuminating. The weather answers to two ancient ORBS. They rest on MT. PYRE". Aqua's "hurry" also
  waits two Gyms.
- **Fix**: this also pays off Tabitha's "I'll round up the others". GRUNT: "BOSS! A MAGMA squad is coming up ROUTE
  119! A big one!" SHELLY: "Tch. Not worth a brawl in a building full of eggheads. TEAM AQUA, pull out!" Files:
  `Route119_WeatherInstitute_2F/scripts.inc` (retext).
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-272).

### 17. Wattson hands a MAGMA grunt the key to his city's power plant
- **Where**: `data/maps/MauvilleCity/scripts.inc:414-426` (`MauvilleCity_EventScript_Wattson`), texts at 577-598. This
  can only be reached with Surf, so in Act 4 and in uniform.
- **The hole**: why does Wattson give a MAGMA grunt the key to Mauville's generator?
- **Evidence**: WATTSON: "I'd like you to go there and switch off the GENERATOR. … Here, this is the KEY to get into
  NEW MAUVILLE. … That's it, then, you have my trust!" His own uniform intro says: "A TEAM MAGMA grunt, is it? If
  you've come to make trouble in my city, you'll get a nasty shock!"
- **Fix**: add a uniform branch: "WATTSON: Wahahah! You again, in that red. / My GENERATOR's running wild under the
  city, and nobody else will go down there. / You battled my GYM fair and square, so I'll take the gamble. Break
  anything and I'll know where to find you!" The Basement Key, the Manectite (D-221) and TM Thunderbolt stay.
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-275).

### 18. Rivals in two places at once
- **Where**: the bedrooms are shown from the Lilycove double until the Hall of Fame (`act4.pory:352-356`, D-239).
  Brendan is shown on the Space Center 2F from the Mind Badge (`data/maps/MossdeepCity_Gym/scripts.inc:82-83`). Wally
  on Route 112 is at `rivals2.pory:73-80` and 95-97. Wally in Wanda's house is shown from Mauville
  (`MauvilleCity/scripts.inc:156`) until the Heat Badge (`LavaridgeTown_Gym_1F/scripts.inc:69`).
- **The hole**: after the Mind Badge, Brendan waits beside Steven at the Space Center and also sits in his Littleroot
  bedroom (and possibly also in Lilycove, #14). On Route 112, Wally blocks the cable car saying he came "with my
  uncle", while he and his uncle are also in Wanda's house in Verdanturf.
- **Evidence**: BRENDAN on 2F: "I came to help STEVEN protect this place." BRENDAN in his bedroom: "I was just checking
  my POKéDEX." WALLY on Route 112: "My uncle and I were going up to the hot springs in LAVARIDGE."
- **Fix**: hide both bedrooms from the Mind Badge until the Sootopolis aftermath, where they say "We're going home to
  tell our dads everything!", then show them again. Hide Wanda's-house Wally under the same condition Route 112 uses
  (`VAR_MAGMA_STATE == MAGMA_STATE_METEOR_FALLS && !defeated(TRAINER_WALLY_ROUTE_112)`).
- **Size**: small. **Owner**: free.
- **Status**: fixed (audit fixes, D-274).

## Act 5 – The betrayal (Aqua Hideout → Sootopolis)

### 19. Steven gives HM Dive to a MAGMA grunt
- **Where**: `data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc:271`, text at 467
  (`…_StevenThankYouComeSeeMeAtHome`). `data/maps/MossdeepCity_StevensHouse/scripts.inc:39-40`, text at 150-158
  (`…_YouveEarnedHMDive`).
- **The hole**: Steven has just fought the player for trying to steal rocket fuel for MAGMA, and does not know they
  are undercover. Why does he invite them home and give them the HM to follow ARCHIE under the sea?
- **Evidence**: STEVEN: "please come see me at home after this. I have something you'll need, wherever ARCHIE has
  gone." / "I won't ask who you really work for. Not yet. But wherever ARCHIE's submarine went, you'll need this to
  follow." Under D-244a and revenge's D-248 draft, Steven only says the player is "the strongest TEAM MAGMA grunt I
  have ever faced … Strange." Maxie's next call says "DIVE down after them".
- **Fix**: pick one.
  - Keep the gift but give Steven a reason he would say out loud: "STEVEN: I can't chase MAXIE and ARCHIE both. /
    Whatever sleeps under the sea, I'd rather it was you who got there first. / Don't make me regret it."
  - Or move the HM to Magma. Tabitha, on leaving: "Leader MAXIE sent this. DIVE after ARCHIE. Hehehe!" Steven's house
    then keeps only the post-game Beldum.

  `FLAG_RECEIVED_HM_DIVE` stays where it is set.
- **Size**: small. **Owner**: revenge for the Space Center aftermath; Steven's house is free.
- **Status**: fixed (Team Magma's revenge, D-244 – D-249).

### 20. The vanilla Rayquaza call still fires
- **Where**: `src/field_specials.c:504-526` (`ShouldDoRivalRayquazaCall`), `src/field_control_avatar.c:817-821`,
  `data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc:305-323`, `data/text/match_call.inc:2309-2336`.
- **The hole**: 250 steps after the Space Center, a rival phones the player, friendly as can be, about a "giant green
  POKéMON". Rayquaza has not even been called yet.
- **Evidence**:
  - The call fires after 250 outdoor steps once the raid sets `FLAG_DEFEATED_MAGMA_SPACE_CENTER`.
  - Male players get "MAY: Hi, {PLAYER}{KUN}! I was just in PACIFIDLOG … I saw a giant green POKéMON flying high in
    the sky. … I wonder what it was." Female players get Brendan: "I wish you could've seen it, {PLAYER}."
  - This comes just after BRENDAN's "I give up trying to figure you out" and MAY's "that means stopping you, too".
  - The rival is chosen by the player's gender, although D-100 made Brendan and May fixed characters.
  - Rayquaza only rises when Aster and Nerine call it at Sootopolis (D-145), and there MAY says "That was RAYQUAZA! A
    real, live RAYQUAZA!"
  - After the logic fix, neither rival is even registered yet.
- **Fix**: make `ShouldDoRivalRayquazaCall` return FALSE (tag it `// Draconid Emerald` and record a decision). The
  logic brief names this function, but only to check the flags it reads. It reads none of them, so that check will
  pass and the call will stay.
- **Size**: small. **Owner**: free.
- **Status**: fixed (story-logic fixes, D-256 – D-259).

### 21. The Elder's Sootopolis call: Aster and Nerine in two places, and the Elder "has no PokéNav"
- **Where**: `data/scripts/draconid/act5.pory:567` ("Far away, at the SKY PILLAR…") and 651-671
  (`SootopolisCity_Text_DraconidElderCall`). The Magma Hideout letter at `act4.pory:632`
  (`MagmaHideout_4F_EventScript_DraconidSendWord`). D-134: "a call to the Elder (he has no PokéNav)".
- **The hole**: Aster and Nerine are at the Sky Pillar calling Rayquaza. A minute later they are chatting beside the
  Elder, who says he is on the mountain. And how can he phone the player, when the player had to write him a letter
  because he has no PokéNav?
- **Evidence**: "Far away, at the SKY PILLAR… ASTER and NERINE raised their voices to the sky", then ELDER: "I felt it
  from the mountain. … ASTER and NERINE called from the SKY PILLAR". ASTER: "We did." ELDER: "Hush, both of you."
  Against the hideout: "{PLAYER} took out paper and wrote to the ELDER. … The next traveler bound for the mountains
  would carry it home."
- **Fix**: put the Elder where the two of them are, and borrow Nerine's device, since she spent years among the
  lowlanders. "ELDER: {PLAYER}. It is the ELDER. / I came down to the SKY PILLAR when the sky turned black. NERINE lent
  me her little talking box." This also prepares act7x's Elder call.
- **Size**: small. **Owner**: revenge (`act5.pory`). The logic branch adds one line nearby.
- **Status**: fixed (Team Magma's revenge, D-244 – D-249).

### 22. May still says Steven is "sticking up for" the player
- **Where**: `data/scripts/draconid/rivals2.pory:336` (`MossdeepCity_EventScript_DraconidMay`).
- **The hole**: May says Steven is sticking up for the player, but after the rewrite Steven only calls the player the
  strongest MAGMA grunt he has faced.
- **Evidence**: MAY: "He says STEVEN is sticking up for you. …Why would he?" This was written for the old line "I know
  you let us win". Revenge's D-248 draft has Steven say "You're the strongest TEAM MAGMA grunt I have ever faced …
  Strange. You battle like someone with something to protect." Brendan's call now quotes that.
- **Fix**: "MAY: He says STEVEN called you the strongest MAGMA grunt he's ever faced. / …Then why do you battle like
  you've got something to protect?" This keeps May's one crack.
- **Size**: small. **Owner**: free. Follow revenge's final D-248 wording.
- **Status**: fixed (audit fixes, D-275).

### 23. Brendan and May Mega Evolve without Key Stones
- **Where**: `src/data/trainers.party:24043` (`TRAINER_BRENDAN_MOSSDEEP`, Sceptile @ Sceptilite) and 34982
  (`TRAINER_MAY_MOSSDEEP`, Blaziken @ Blazikenite).
- **The hole**: both rivals Mega Evolve at Mossdeep. Where did they get Key Stones? In this story the Elder makes them,
  and "only the ELDER may give one away".
- **Evidence**: no line explains it anywhere. Wally explains his: "a man by the sea gave me this KEY STONE". The player
  gets theirs from the Elder, through Aster.
- **Fix**: at the Space Center, "BRENDAN: STEVEN lent me a KEY STONE for today. Let's see how MAGMA likes this!"
  (Steven, a Mega user, is standing right there). May at Mossdeep: "MAY: My dad gave me his KEY STONE. He says I'm
  ready."
- **Size**: small. **Owner**: revenge (Space Center). May's line is free (`rivals2.pory`).
- **Status**: May's line fixed (audit fixes, D-275); Brendan's fixed (Team Magma's revenge, D-248).

### 24. Maxie phones news the player saw in person
- **Where**: `data/scripts/draconid/maxie_calls.pory:109` (`MAXIE_CALL_SEAFLOOR`).
  `data/maps/SeafloorCavern_Room9/scripts.inc:104-120` and `data/maps/Route128/scripts.inc:35`, 262.
- **The hole**: Maxie phones to say Kyogre has woken. The player was standing next to him when it happened and has
  just talked with him on Route 128.
- **Evidence**: SEAFLOOR: "MAXIE: What have you wrought? ARCHIE… You've finally awoken KYOGRE" / "{PLAYER}, come on,
  you have to get out of here, too!" ROUTE 128: "This rain is KYOGRE's doing… I will find it and make it obey." Ten
  steps later: "MAXIE: KYOGRE has awakened. The sky over SOOTOPOLIS is black."
- **Fix**: "MAXIE: {PLAYER}. I have found GROUDON. It rose in SOOTOPOLIS to meet KYOGRE. / Come at once. I need you."
- **Size**: small. **Owner**: free. The logic branch edits only the first call in this file.
- **Status**: fixed (audit fixes, D-272).

### 25. Nerine's Seafloor "reveal" repeats what she said at Mt. Chimney
- **Where**: `data/scripts/draconid/act5.pory:279-300` (`SeafloorCavern_Room9_EventScript_DraconidNerineReveal`) and
  `act3.pory:339`.
- **The hole**: at the Seafloor, Nerine "reveals" she is Draconid, but she already told the player at Mt. Chimney.
- **Evidence**: MT. CHIMNEY: "NERINE: …Your village is Draconid. Mine is too. Don't look so surprised." SEAFLOOR:
  "My name really is NERINE. That part was never a lie. I'm DRACONID, like you." The story has both beats (steps 13
  and 25), so keep both but make the second build on the first.
- **Fix**: "NERINE: You've known what I am since MT. CHIMNEY. / Now you'll see who I am." Then the costume change, then
  "The ELDER sent me down the mountain years ago…" as before.
- **Size**: small. **Owner**: revenge (the `act5.pory` file).
- **Status**: fixed (Team Magma's revenge, D-244 – D-249).

### 26. Aqua lines that don't see the uniform
- **Where**: `data/maps/SeafloorCavern_Entrance/scripts.inc:59` (`…_HearMagmaNearMossdeep`, untagged) and
  `data/maps/Route119/scripts.inc:509` (the bridge lookouts).
- **The hole**: AQUA grunts talk to the player as if they weren't wearing MAGMA red.
- **Evidence**: SEAFLOOR GRUNT: "You're a perfect fit for the likes of TEAM MAGMA! Speaking of TEAM MAGMA, I hear they
  were spotted near MOSSDEEP." The player led that raid. LOOKOUT: "Hey, you! Stay away from the WEATHER INSTITUTE.
  It's not safe."
- **Fix**: "Hey! The MAGMA brat from MOSSDEEP! Your whole team couldn't steal one tank of fuel, and you followed us
  down here?" / "A MAGMA grunt? Beat it! This INSTITUTE is AQUA business!"
- **Size**: small. **Owner**: scrub.
- **Status**: fixed (contradiction scrub, D-253 – D-255).

## After the turn (Act 5½ – Act 6)

### 27. Maxie and Archie still return the Orbs at Mt. Pyre
- **Where**:
  - `data/maps/SootopolisCity/scripts.inc:1361-1370` (`SootopolisCity_EventScript_MaxieArchieLeave`: it clears
    `FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE/ARCHIE` and sets `VAR_MT_PYRE_STATE` to 2).
  - `SootopolisCity/scripts.inc:1660` (`SootopolisCity_Text_MaxieArchieLeft`).
  - `data/maps/MtPyre_Summit/scripts.inc:161-230` (`…_ArchieMaxieReturnOrbs`, the old lady), texts at 541
    (`ThoseTwoMenReturnedOrbs`) and 593 (`MaxieSilence`).
  - `prompt_revenge.md` (Maxie battle 2) and `prompt_act7x_full.md` step 4 (the Orbs at the village).
- **The hole**: at Sootopolis, Maxie swears the player will pay and Archie sides with him. Then the two quietly walk up
  Mt. Pyre, hand the Orbs back, and the old lady decides they are "not so evil". How do they then have the Orbs for
  the village attack? Maxie also stands on the summit (until the player walks up) at the same time as he waits at
  Victory Road and attacks the village.
- **Evidence**:
  - STEVEN at Sootopolis: "Perhaps they've gone to MT. PYRE to return those ORBS…"
  - SUMMIT: "MAXIE: {PLAYER}… … …", then they leave.
  - OLD LADY: "The two men who took the ORBS came back to return them on their own. Those men… Perhaps they are not so
    evil after all…"
  - Revenge's D-244 draft: MAXIE "Do not think this is over … I will not forgive it", and Maxie battle 2 ("You have a
    home, do you not?").
  - Act7x's D-206 draft: the Orbs are traded between them and used at the village.
- **Fix**:
  - Cut the return: `MaxieArchieLeave` keeps the Mt. Pyre hide flags set and leaves `VAR_MT_PYRE_STATE` as it is.
  - STEVEN: "MAXIE and ARCHIE left together, and the ORBS went with them. / That worries me more than either of them
    alone."
  - OLD LADY, after the turn: "The ORBS have not come back… Those two men still hold them. / I fear the land and the
    sea have not had their last word."
  - After act7x's finale, the old lady can let the player keep the Orbs: "Keep them. The one who calmed the old ones
    should hold them."
- **Size**: medium. **Owner**: shared. Revenge owns the Sootopolis aftermath, act7x the Orbs' route, and
  `MtPyre_Summit` is free. Neither draft mentions the return.
- **Status**: fixed (Team Magma's revenge, D-244 – D-249).

### 28. Wally at Victory Road: "I was scared of you"
- **Where**: `data/maps/VictoryRoad_1F/scripts.inc:121` (`VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore`).
- **The hole**: Wally says he was scared of the player in Mauville. He wasn't; he was furious, and he fought the player
  four more times after that.
- **Evidence**: WALLY at Victory Road: "In MAUVILLE, I was scared of you. I'm sorry, {PLAYER}." WALLY in Mauville:
  "Battle me! I'm not scared of TEAM MAGMA!" D-236: "normally gentle, now angry and brave". Route 112: "I'll never
  forgive you". Route 120: "This time, I'm going to stop you!"
- **Fix**: "WALLY: In MAUVILLE, I said you'd forgotten what a TRAINER is for. / I kept saying it, all over HOENN. I'm
  sorry, {PLAYER}."
- **Size**: small. **Owner**: free (`VictoryRoad_1F`). Revenge edits B1F and B2F, so coordinate.
- **Status**: fixed (audit fixes, D-272).

## Act 7 and the post-game

### 29. The act7x brief: a Regidrago detour while the meteor "could strike within hours"
- **Where**: `prompt_act7x_full.md`, "New order of Act 7" items 1–2. `data/scripts/draconid/act6.pory:112` and 126 (the
  meteor alert).
- **The hole**: the meteor "could strike within hours" and "the debt comes due tonight", yet the Elder sends the
  player home to open a wall and battle a stone dragon first.
- **Evidence**: TV: "Scientists say it could strike within hours." ELDER: "The sky has split, {PLAYER}. The debt comes
  due tonight." The brief: "Then the Elder calls … before the Sky Pillar, come home – the shrine's old seal has
  woken". Act7x's draft D-200 moves the call to the foot of the Sky Pillar, which fixes "the Elder is already at the
  table", but not the urgency. Its D-203 also adds a Wallace battle on the way back.
- **Fix**: state why it has to happen now. "ELDER: Do not climb yet. When the star caught fire, the seal in our shrine
  broke. / The stone dragon wakes only when the sky is in danger. No tamer climbs to RAYQUAZA without its blessing. /
  My dragon is fast. Go, and come back quickly." Alternatively, open the wall during the meteor alert itself (the
  shrine is next door), so the order is simply alert → shrine → lift to the Sky Pillar.
- **Size**: small. **Owner**: act7x.
- **Status**: open – the Act 7 extension (being built).

### 30. Post-game village lines still assume the old, quiet ending
- **Where**: `data/maps/DraconidVillage_PlayersHouse_1F/scripts.pory:20-21` (the S.S. Ticket scene),
  `data/scripts/draconid/act7.pory:824-830` (Aster at the shrine) and 856-861 (Nerine by the pond),
  `data/maps/DraconidVillage_EldersHouse/scripts.pory:70-71` (the Elder in his house after the finale).
- **The hole**: Primal Groudon and Kyogre have just wrecked the village, yet the post-game talks about children
  counting stars and how still the pond is. The Elder also still says the star is falling, which is already wrong
  today since the finale destroyed it.
- **Evidence**: ELDER: "The children counted falling stars until dawn. They are still arguing about the total." ASTER:
  "The sky is quiet again. Too quiet, if you ask me." NERINE: "I'd forgotten how still the water is here." ELDER, in
  his house: "But the star still falls. Keep your eyes on the sky." Against act7x (brief step 4, draft D-204–207):
  grunts at every house, the Elder knocked down, Primal Kyogre in the waterfall pool.
- **Fix**:
  - ELDER: "You slept a whole day. The village did not. / Every roof the old ones cracked is mended, and the children
    have built a GROUDON out of rubble in the square."
  - ASTER: "The shrine held. …So did you."
  - NERINE: "The pond's still muddy from KYOGRE. It'll clear. Most things do."
  - ELDER, in his house: "The sky's debt is paid. Go and see the world, {PLAYER}. It is still wide."
- **Size**: small. **Owner**: act7x.
- **Status**: open – the Act 7 extension (being built).

### 31. The post-game lab rivals: a third apology, and a "traitor" that was never said
- **Where**: `data/scripts/draconid/act7.pory:715-790` (`…_DraconidPostgameMay/Brendan/Double`), `act5.pory:689-691`,
  `rivals2.pory:394-397`.
- **The hole**: Brendan apologizes for the third time, after joking he'd never say it twice, and for calling the
  player a "traitor" at Rustboro, which he never did.
- **Evidence**: SOOTOPOLIS: "I'm sorry. …Don't make me say that twice." BEDROOM: "Don't make me say sorry twice, okay?"
  LAB: "…I called you a traitor at RUSTBORO. … You were fighting for all of us the whole time. I just couldn't see
  it." At Rustboro he actually said "And now you've joined MAGMA?! Those guys want to wreck HOENN!", and the voice
  rules forbid narrating feelings. MAY: "I told BRENDAN you were one of the good guys. Way back on ROUTE 110!", but
  Brendan wasn't there. With act7x, the rivals have also just defended the village beside the player.
- **Fix**: "BRENDAN: {PLAYER}. After the village… Man, I still owe you a real battle. / No holding back. And don't make
  it weird." "MAY: I KNEW it on ROUTE 110, and I'm never going to stop saying so! One more battle?"
- **Size**: small. **Owner**: act7x (`act7.pory`).
- **Status**: open – the Act 7 extension (being built).

### 32. The villagers never notice anything
- **Where**: `data/maps/DraconidVillage/scripts.pory:122-133` (the gatekeeper) and 139-165 (the villagers), plus
  `DraconidVillage_House1/2`.
- **The hole**: the village is a Fly destination from Act 1 and the villagers know the mission, yet nobody reacts to
  the MAGMA uniform. The gatekeeper even tells the Champion to go "see the lowlands" by Route 101.
- **Evidence**: OLD WOMAN: "The ELDER told us all. You're going down to the lowlands, alone, and in secret."
  GATEKEEPER, in every state after the start: "So you're off to see the lowlands! … head east to ROUTE 101." Only the
  Elder has uniform and revealed lines (`EldersHouse/scripts.pory:63-72`).
- **Fix**: reputation lines for the gatekeeper and two villagers.
  - GATEKEEPER, in uniform: "…Is that you under the red hood, {PLAYER}? The ELDER said you'd come home looking like
    one of them. The gate is still yours."
  - GATEKEEPER, after the reveal: "The hero of SOOTOPOLIS, at my gate! I'll never tell the young ones you once
    dressed like a MAGMA grunt."
  - BOY, in uniform: "Why are you dressed like the bad lowlanders? …It's a trick, isn't it!"
- **Size**: small. **Owner**: act7x (the `DraconidVillage` map).
- **Status**: open – the Act 7 extension (being built).

### 33. Steven's post-game letter contradicts Champion Steven
- **Where**: `data/maps/MossdeepCity_StevensHouse/scripts.inc:195-209` (`…_LetterFromSteven`, with the Beldum ball,
  after the Hall of Fame).
- **The hole**: on the steven branch, Steven is the Champion and waits at the League for rematches, yet his letter says
  he has gone to "train on the road" and won't be home for a long time.
- **Evidence**: "I've decided to do a little soul-searching and train on the road. I don't plan to return home for some
  time." Against the steven draft, D-251/252: Steven's rematch at the League and a chat in Meteor Falls.
- **Fix**: "To {PLAYER}{KUN}… / A CHAMPION can't sit in the LEAGUE every day. When I'm not there, look for me among the
  stones in METEOR FALLS. / Please take the POKé BALL on the desk…"
- **Size**: small. **Owner**: steven.
- **Status**: fixed (audit fixes, D-275).

---

## Contradictions in the briefs themselves (mostly already caught in the agents' drafts)
- **`prompt_revenge.md` §1**: Maxie's realization lists "STEVEN's 'you let us win'". Maxie never heard that line, and
  D-244a / D-248 remove it. Revenge's D-244 draft already leaves it out; confirm this in the final text.
- **`prompt_steven.md` §1**: "he said 'I know you let us win' at the Space Center". This contradicts follow-up 20. The
  steven draft D-250 has him not know ("your POKéMON trusted you far too much"), which is correct; confirm the final
  lines.
- **`prompt_act7x_full.md` §1**: "the Elder calls … come home", although the merged Act 6 already has the Elder at the
  player's table during the meteor alert. The draft D-200 moves the call to the foot of the Sky Pillar. The urgency
  problem is still open: see #29.
- **`prompt_act7x_full.md` §4**: "Groudon holding the Red Orb, … Kyogre holding the Blue Orb" is the reverse of what
  each villain took at Mt. Pyre. The draft D-206 explains it with a pact to trade Orbs, which works, but the vanilla
  Mt. Pyre return (#27) has them hand both Orbs back first.
- **`prompt_logic.md` item 1**: "Brendan still hands over HM Fly" keeps the Go-Goggles hole alive for Fly (#5). "Check
  nothing else reads those flags … `ShouldDoRivalRayquazaCall`": that function reads none of the registration flags,
  so the check will pass and the call will stay (#20).

## Checked and fine (no need to check again)
- **Magma grunts who battle the player**: every grunt trainer at Mt. Chimney, Jagged Pass, the Magma Hideout and the
  Space Center has a rank-test line. All of Magma leaves Mt. Chimney after the sabotage. The hideout empties at the
  promotion: `FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS` covers all 18 objects, Tabitha and Maxie included. So no rank-test
  line survives into the post-game, and act7x's Groudon visit is safe.
- **Weather Institute**: Castform is a thank-you for the rescue. The Institute can't be skipped, because the Aqua
  lookouts block the bridge at (13, 33/34) until Shelly is beaten, so Brendan's "MAY told me what happened" on Route
  119 always comes after it.
- **Dead vanilla branches**: the Meteor Falls vanilla scene (a `goto` at the top skips it) and the vanilla Maxie battle
  and Archie thank-you at Mt. Chimney are unreachable. The Aqua Hideout entrance grunts are gone after the promotion
  (D-213). The Seafloor Shelly, Archie and Maxie lines fit, and so do Route 128's Maxie and Steven lines.
- **Mt. Pyre, first visit**: Maxie hands over the Emblem, and the old lady's "You wear the same red…" fits.
- **Who knows the secret**: Birch and Oak never slip in front of Brendan or May. Oak says "He doesn't know, and for now
  he mustn't", and Birch only says "Give {PLAYER} a chance". Nobody outside the clan, Birch and Oak states the
  mission before Sootopolis, apart from #15 and #19.
- **Services and gyms**: nurses, Mart clerks, the battle-item clerk, the Cable Club, the Day Care, Gym Guides and
  Leaders all have reputation lines (D-117). The Gym boosters are reputation-neutral.
- **Megas and Latis**: no trainer Mega appears before the player's Mega Ring (Jagged Pass).
  Latios and Latias appear only in `*_POSTGAME*` rival teams. Wally's Lilycove Mega is explained.
- **Maxie's calls**: all ten name the next place in story order and stop at the turn. The only issue is #24.
- **Steven as Champion**: Tabitha's "The CHAMPION of HOENN himself" becomes correct on the steven branch. Wallace's
  Sootopolis lines and Juan's lines fit either Champion.
- **Act 6 staging**: the order Hall of Fame → home → meteor alert holds, and the Elder's-house Elder is hidden while he
  stands in the player's house.
- **Lilycove and Mossdeep townsfolk**: "someone punted TEAM AQUA" and "someone busted the HIDEOUT" never name the
  player.
- **Already in another branch's work, not re-reported**:
  - Scrub (`changes.json`): Wally's father's Surf speech ("…I see you're wearing that uniform"), Wanda's-house Wally,
    Cozmo's wife, Trick House quiz 1, Mr. Stone calls 5 and 6, Petalburg Gym trainers, the Fan Club "your father".
  - Revenge (drafts D-244 and D-248): Maxie's aftermath line "Perhaps it is for the best that someone was watching
    me", Archie's aftermath line, Steven's Space Center "I know you let us win" and his heal after a loss.
  - Steven (draft D-250): Steven's Hall of Fame Match Call.
  - Logic brief: the rival registrations, Briney, the Devon Goods, the Go-Goggles.
