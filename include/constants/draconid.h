#ifndef GUARD_CONSTANTS_DRACONID_H
#define GUARD_CONSTANTS_DRACONID_H

// Draconid Emerald story constants. See docs/hack_changes.md.

// VAR_DRACONID_STATE: progress through the opening in Draconid Village
#define DRACONID_STATE_NEW_GAME        0 // waking up in the bedroom
#define DRACONID_STATE_SET_CLOCK       1 // Mom asked the player to set the clock
#define DRACONID_STATE_CLOCK_SET       2 // go to the Elder's house (the prophecy), then the egg ceremony in the
                                         // shrine (the Elder is there: FLAG_HIDE_DRACONID_SHRINE_ELDER clear, D-230)
#define DRACONID_STATE_EGG_RECEIVED    3 // egg chosen in the shrine; it hatches after DRACONID_EGG_HATCH_STEPS steps
#define DRACONID_STATE_EGG_HATCHED     4 // hatched; the old woman brings the Running Shoes
#define DRACONID_STATE_READY_TO_LEAVE  5 // got the Running Shoes, may leave the village
#define DRACONID_STATE_LEFT_VILLAGE    6 // met Aster on Draconid Pass
#define DRACONID_STATE_SECOND_STARTER  7 // Stone Badge: Prof. Oak waits outside the Rustboro Gym (D-233)
#define DRACONID_STATE_GOT_SECOND_STARTER 8 // second partner received

// VAR_STARTER_MON / VAR_ASTER_EGG: the three Draconid eggs (order of the Elder's choice)
#define DRACONID_EGG_DEINO             0
#define DRACONID_EGG_DREEPY            1
#define DRACONID_EGG_JANGMO_O          2
#define DRACONID_EGG_COUNT             3

#define DRACONID_EGG_SPECIES_0         SPECIES_DEINO
#define DRACONID_EGG_SPECIES_1         SPECIES_DREEPY
#define DRACONID_EGG_SPECIES_2         SPECIES_JANGMO_O

// The ELDER's old dragon: his partner in the new-game speech (src/main_menu.c; named in data/text/birch_speech.inc),
// the dragon that carries the egg and the player in the story (D-421)
#define DRACONID_ELDER_DRAGON          SPECIES_SALAMENCE

// Level the hatchling is raised to when it hatches (eggs hatch at EGG_HATCH_LEVEL = 1)
#define DRACONID_HATCHLING_LEVEL       5
// Steps outdoors after the shrine ceremony until the egg hatches (VAR_DRACONID_EGG_STEPS, src/draconid.c, D-231)
#define DRACONID_EGG_HATCH_STEPS       5
// Route 101: the dazed wild Pokemon that fell with last night's star; the hatchling tires it out for Prof. Birch
// (StartBirchRescueBattle, data/scripts/draconid/birch_intro.pory). Round 2 (feedback 2.11, D-400; round 1 had
// Poochyena chasing Birch): a low level, a soft moveset and hurt by the fall, so all three Lv 5 hatchlings can
// win it (Deino is immune to Confusion, Dreepy to Tackle; Jangmo-o's Tackle is resisted by Rock)
#define DRACONID_RESCUE_SPECIES        SPECIES_LUNATONE
#define DRACONID_RESCUE_LEVEL          2
#define DRACONID_RESCUE_MOVE_1         MOVE_TACKLE
#define DRACONID_RESCUE_MOVE_2         MOVE_HARDEN
#define DRACONID_RESCUE_MOVE_3         MOVE_CONFUSION
#define DRACONID_RESCUE_HP_PERCENT     67 // of its max HP when the battle starts
// The three dragon egg lines evolve earlier than in the core games (round 1, D-107)
#define DRACONID_EVO_LEVEL_MIDDLE      25 // Deino -> Zweilous, Dreepy -> Drakloak, Jangmo-o -> Hakamo-o
#define DRACONID_EVO_LEVEL_FINAL       50 // Zweilous -> Hydreigon, Drakloak -> Dragapult, Hakamo-o -> Kommo-o
// No trade evolutions (round 1, D-216): they happen at a level picked by the evolved form's base stat total,
// next to Hoenn's own level-up evolutions of that power and the level caps (src/caps.c); a held item is only
// needed where it picks a branch (D-217). Table: docs/hack_items.md, tools/hack/check_evos.py.
#define DRACONID_TRADE_EVO_LEVEL_LOW   30 // up to ~480 (Sharpedo/Crawdaunt band): Trevenant, Aromatisse, Slurpuff
#define DRACONID_TRADE_EVO_LEVEL_MID   36 // ~485-515 (the Hoenn starters' final stage): Alakazam, Machamp, Golem, Gengar ...
#define DRACONID_TRADE_EVO_LEVEL_HIGH  42 // ~525-540 (Aggron, Glalie): Kingdra, Electivire, Magmortar, Dusknoir, Porygon-Z
#define DRACONID_TRADE_EVO_LEVEL_LATE  48 // Rhyperior (Rhydon itself comes at 42)
// The battle item counter in every Poké Mart (round 1, D-218): its stock grows with the number of Gym Badges
// (data/scripts/draconid/battle_items.pory, docs/hack_items.md). Tier 1 is always open; the post-game tier
// opens with FLAG_IS_CHAMPION.
#define BATTLE_ITEMS_TIER_2_BADGES     2 // + Scope Lens, Muscle Band, Light Clay ..., the branch items (D-217)
#define BATTLE_ITEMS_TIER_3_BADGES     4 // + Leftovers, Rocky Helmet, Focus Sash, Eviolite, the herbs ...
#define BATTLE_ITEMS_TIER_4_BADGES     6 // + Choice items, Life Orb, Assault Vest ...; the first Mega Stones
#define BATTLE_ITEMS_TIER_5_BADGES     8 // + every other competitive item; more Mega Stones

// VAR_SECOND_STARTER: Prof. Oak's gift after the first Gym (D-233)
#define SECOND_STARTER_NONE            0
#define SECOND_STARTER_CHARMANDER      1
#define SECOND_STARTER_TOTODILE        2
#define SECOND_STARTER_TREECKO         3
#define SECOND_STARTER_LEVEL           10

// VAR_ASTER_STATE: Aster's arc after Draconid Pass (round 1 story, D-105; values in story order)
#define ASTER_STATE_START              0 // Draconid Pass battle (FLAG_DEFEATED_ASTER_DRACONID_PASS)
#define ASTER_STATE_METEOR_FALLS       1 // battled deep in Meteor Falls, took Maxie's meteorite shard (Act 3)
                                         // 2-5 unused (v1: the cable car disguise and Mt. Chimney (Act 3),
                                         // the Route 119 battle (round 1), the Magma Hideout (Act 4))
#define ASTER_STATE_MEGA_RING          6 // gave the Mega Ring at Jagged Pass (Act 3)
#define ASTER_STATE_RAYQUAZA_CALLED    7 // called Rayquaza with Nerine at the Sky Pillar (Act 5)
#define ASTER_STATE_SKY_PILLAR         8 // the Sky Pillar finale done (Act 7)
#define ASTER_STATE_POSTGAME           9 // post-game battle at the shrine done

// VAR_BRENDAN_STATE: Brendan's scenes (round 1 schedule, D-106; values in story order)
#define BRENDAN_STATE_START            0 // confronts the player at Rustboro's south edge (Act 1)
#define BRENDAN_STATE_RUSTBORO         1 // beaten at Rustboro
#define BRENDAN_STATE_MT_CHIMNEY       2 // Mt. Chimney battle done (Act 3, not a must-win)
#define BRENDAN_STATE_ROUTE_119        3 // beaten on Route 119, gave HM Fly (Act 4); no PokéNav until Sootopolis (D-256)
#define BRENDAN_STATE_LILYCOVE         4 // Lilycove double battle with May done (Act 4)
#define BRENDAN_STATE_MOSSDEEP         5 // Space Center tag battle done (Act 5, not a must-win)
#define BRENDAN_STATE_SOOTOPOLIS       6 // after the Sootopolis turn: knows the truth (Act 5)
                                         // 7 unused (the v1 Sootopolis Mega battles were removed in round 1 Act 5)
#define BRENDAN_STATE_POSTGAME         8 // post-game battles (Act 7)

// VAR_MAY_STATE: May's scenes (round 1 schedule, D-106; values in story order)
#define MAY_STATE_START                0
#define MAY_STATE_ROUTE_110            1 // beaten on Route 110 (Act 2); no PokéNav until Sootopolis (D-256)
#define MAY_STATE_WEATHER_INSTITUTE    2 // covered for the player at the Weather Institute (Act 4)
#define MAY_STATE_LILYCOVE             3 // Lilycove double battle done (Act 4)
#define MAY_STATE_SOOTOPOLIS           4 // after the Sootopolis turn: knows the truth (Act 5)
#define MAY_STATE_POSTGAME             5 // post-game battles (Act 7)

// VAR_WALLY_STATE: Wally's battles that vanilla doesn't have
#define WALLY_STATE_START              0
#define WALLY_STATE_PETALBURG          1 // Heat Badge: Wally waits outside the Petalburg Gym
#define WALLY_STATE_LILYCOVE           2 // beaten in Petalburg: Wally waits in Lilycove
#define WALLY_STATE_LILYCOVE_DONE      3

// VAR_DRACONID_REPUTATION: how Hoenn sees the player (round 1, D-103); VAR_PLAYER_OUTFIT follows it
#define REPUTATION_PRE_UNIFORM         0 // Act 1: a young tamer from the mountains
#define REPUTATION_UNIFORM             1 // Petalburg Woods to the Sootopolis turn: a Team Magma grunt
#define REPUTATION_REVEALED            2 // after the Sootopolis turn: the one who stood up to Maxie

// VAR_NERINE_STATE: Nerine's arc (round 1, D-104); each value = that fight is done
#define NERINE_STATE_START             0
#define NERINE_STATE_PETALBURG_WOODS   1
#define NERINE_STATE_RUSTURF           2
#define NERINE_STATE_SLATEPORT         3
#define NERINE_STATE_MT_CHIMNEY        4
#define NERINE_STATE_MT_PYRE           5
#define NERINE_STATE_AQUA_HIDEOUT      6
#define NERINE_STATE_REVEALED          7 // Seafloor Cavern: the Aqua disguise comes off
#define NERINE_STATE_SKY_PILLAR        8
#define NERINE_STATE_POSTGAME          9

// VAR_MAGMA_STATE: the player's Team Magma career (round 1 story, docs/hack_story.md); each value = that
// step is done. VAR_DRACONID_REPUTATION says how Hoenn sees the player, this says how far in they are.
#define MAGMA_STATE_NONE               0
#define MAGMA_STATE_RECRUITED          1 // Petalburg Woods: Courtney, the uniform (Act 1)
#define MAGMA_STATE_ORDERS             2 // Stone Badge: Tabitha's order outside the Rustboro Gym
#define MAGMA_STATE_DEVON_GOODS        3 // Rusturf Tunnel: the goods taken from Nerine (FLAG_DEVON_GOODS_RETURNED)
#define MAGMA_STATE_MUSEUM             4 // Slateport: the Oceanic Museum raid (Act 2)
#define MAGMA_STATE_METEOR_FALLS       5 // Meteor Falls: Maxie meets the player (Act 3)
#define MAGMA_STATE_MT_CHIMNEY         6 // Mt. Chimney: the meteorite sabotage
#define MAGMA_STATE_WEATHER_INSTITUTE  7 // Weather Institute raid (Act 4)
#define MAGMA_STATE_MT_PYRE            8 // Mt. Pyre summit
#define MAGMA_STATE_PROMOTED           9 // Magma Hideout: Maxie's promotion
#define MAGMA_STATE_SPACE_CENTER      10 // Mossdeep: the tag battle with Tabitha (Act 5)
#define MAGMA_STATE_SEAFLOOR          11 // Seafloor Cavern: Nerine's reveal
#define MAGMA_STATE_TURNED            12 // Sootopolis: the uniform comes off (reputation REVEALED)

// The Devon Goods choice (FLAG_DEVON_GOODS_RETURNED, D-258): kept for Magma, Tabitha pays at the Oceanic
// Museum; returned to Devon, Mr. Stone adds a thank-you gift (FLAG_RECEIVED_AMULET_COIN)
#define DRACONID_GOODS_REWARD_MONEY    5000             // Tabitha's pay: about one tier-2 battle item (D-219)
#define DRACONID_GOODS_REWARD_ITEM     ITEM_FIRE_STONE  // "from Mt. Chimney"; its only early user is Vulpix (Mt. Pyre)
#define DRACONID_GOODS_THANKS_ITEM     ITEM_AMULET_COIN // Mom's gift in vanilla (Mom is gone, D-100)

// VAR_MAXIE_CALL: Maxie phones the Magma recruit after key story points and names the next place to go
// (D-186). The first call is scripted on Mr. Briney's boat; the others ring after MAXIE_CALL_STEPS steps
// outdoors once their story state is reached (src/draconid.c, data/scripts/draconid/maxie_calls.pory).
#define MAXIE_CALL_NONE                0
#define MAXIE_CALL_DEWFORD             1  // on the boat to Dewford, just after the PokéNav
#define MAXIE_CALL_MUSEUM              2  // MAGMA_STATE_MUSEUM: Mauville, then Meteor Falls
#define MAXIE_CALL_METEOR_FALLS        3  // MAGMA_STATE_METEOR_FALLS: Mt. Chimney by the cable car
#define MAXIE_CALL_MT_CHIMNEY          4  // MAGMA_STATE_MT_CHIMNEY: Lavaridge, Petalburg, the Weather Institute
#define MAXIE_CALL_WEATHER_INSTITUTE   5  // MAGMA_STATE_WEATHER_INSTITUTE: Fortree, Lilycove, Mt. Pyre
#define MAXIE_CALL_MT_PYRE             6  // MAGMA_STATE_MT_PYRE: the Magma Hideout
#define MAXIE_CALL_PROMOTED            7  // MAGMA_STATE_PROMOTED: infiltrate the Aqua Hideout
#define MAXIE_CALL_AQUA_HIDEOUT        8  // NERINE_STATE_AQUA_HIDEOUT: Mossdeep, the Space Center
#define MAXIE_CALL_SPACE_CENTER        9  // MAGMA_STATE_SPACE_CENTER: follow Aqua to the Seafloor Cavern
#define MAXIE_CALL_SEAFLOOR           10  // MAGMA_STATE_SEAFLOOR: Sootopolis, now
#define MAXIE_CALL_STEPS              10  // steps outdoors before a due call rings

// VAR_DRACONID_FINALE_STATE: Acts 6-7, from the first Hall of Fame to the post-game (docs/hack_story.md
// steps 30-34, D-150); each value = that step is done
#define FINALE_STATE_NONE              0
#define FINALE_STATE_HALL_OF_FAME      1 // first Hall of Fame: the new Champion is home (no credits yet)
#define FINALE_STATE_METEOR_ALERT      2 // the sky darkened over the village; the TV and the Elder wait downstairs
#define FINALE_STATE_SUMMONED          3 // the Elder sent the player to the Sky Pillar (open; Aster and Nerine wait)
#define FINALE_STATE_CLIMB             4 // the player + Nerine beat Aster; Zinnia waits on the Sky Pillar 3F
#define FINALE_STATE_SUMMIT            5 // Zinnia beaten; the Elder and Rayquaza at the summit
#define FINALE_STATE_RAYQUAZA          6 // Rayquaza caught, Dragon Ascent learned; Deoxys attacks, the meteor breaks, and
                                         // then the attack on the village (VAR_DRACONID_VILLAGE_STATE, D-200)
#define FINALE_STATE_METEOR_DESTROYED  7 // the meteor broken and the village saved from Maxie and Archie: credits, then
                                         // home (set before the credits, D-200)
#define FINALE_STATE_HOME              8 // woke up at home after the credits; the Elder waits downstairs
#define FINALE_STATE_POSTGAME          9 // the Elder brought the SS Ticket, the Lati TV news aired

// The finale's wild battles (D-110, D-111)
#define DRACONID_RAYQUAZA_LEVEL        70 // the must-catch Rayquaza at the summit
#define DRACONID_DEOXYS_BOSS_LEVEL     72 // Deoxys attacks right after (no catching, no running)
#define DRACONID_DEOXYS_LEVEL          80 // post-game: Deoxys where it fell, at the summit (as in ORAS)

// VAR_DRACONID_VILLAGE_STATE: the Act 7 extension (feedback 1.25, 1.29, 1.30; D-200 - D-209,
// data/scripts/draconid/act7x.pory): the Elder's call and Regidrago before the Sky Pillar trial, then the attack on
// the village after the meteor breaks (the Primal finale); each value = that step is done
#define VILLAGE_STATE_NONE             0
#define VILLAGE_STATE_ELDER_CALLED     1 // the Elder called at the Sky Pillar's foot: the shrine's seal woke; flown home
#define VILLAGE_STATE_SEAL_OPEN        2 // the shrine wall opened (DraconidVillage_Shrine_Depths: Regidrago waits)
#define VILLAGE_STATE_REGIDRAGO        3 // Regidrago faced once (caught or not); the Elder's lift back to the Sky Pillar
#define VILLAGE_STATE_ALARM            4 // the meteor broken; May's call: Magma and Aqua attack the village
#define VILLAGE_STATE_ATTACK           5 // home with Brendan, May and Wally: the three house doubles (trainer flags)
#define VILLAGE_STATE_SHRINE_PATH      6 // the houses freed; Tabitha and Shelly hold the way up to the shrine
#define VILLAGE_STATE_SHRINE           7 // the admins beaten with Aster; Maxie and Archie come to the shrine (a scene)
#define VILLAGE_STATE_FINAL            8 // the Primal multi battle is on (after a loss: talk to Maxie or Archie)
#define VILLAGE_STATE_PRIMAL_WON       9 // Maxie and Archie beaten: Groudon and Kyogre calm, the Orbs handed over
#define VILLAGE_STATE_SAVED           10 // the village saved, goodbyes said: the credits (FINALE_STATE_METEOR_DESTROYED)

// The Act 7 extension's wild Pokemon (D-203, D-207, D-208)
#define DRACONID_REGIDRAGO_LEVEL       65 // the shrine depths: above the League (cap 60), below the finale's Rayquaza
#define DRACONID_PRIMAL_LEGEND_LEVEL   72 // post-game Groudon and Kyogre, the level of Maxie's and Archie's in the finale
#define DRACONID_LATI_ROAMER_LEVEL     60 // post-game: both Latios and Latias roam Hoenn (ROAMER_COUNT 2)

// Z-Power (D-267 - D-269, data/scripts/draconid/zmoves.pory): the dragon keepers of Alola sent their egg with a
// Z-Power Ring "for the one who carries the prophecy"; the Elder gives it at the egg ceremony with the first and
// simplest crystal, and the others come along the road (the list: docs/hack_items.md, "Z-Crystals").
#define DRACONID_Z_CRYSTAL_FIRST       ITEM_NORMALIUM_Z  // the egg ceremony (Act 1): any partner has a Normal move
#define DRACONID_Z_CRYSTAL_FALLS       ITEM_DRAGONIUM_Z  // Aster, from the Meteor Falls Draconids (Act 3)
#define DRACONID_Z_CRYSTAL_JANGMO_O    ITEM_KOMMONIUM_Z  // Nerine, for a Jangmo-o tamer: the Alolan line's own (Act 4)
#define DRACONID_Z_CRYSTAL_CHARMANDER  ITEM_FIRIUM_Z     // Prof. Oak in Slateport, from his cousin Samson in Alola (Act 2)
#define DRACONID_Z_CRYSTAL_TOTODILE    ITEM_WATERIUM_Z
#define DRACONID_Z_CRYSTAL_TREECKO     ITEM_GRASSIUM_Z

// The debug menu's "Jump to act…" (debug builds only, D-480 - D-489): the menu and the warps in
// data/scripts/draconid/debug_jumps.pory, the story state at each stop from tools/hack/gen_debug_jumps.py
// (data/scripts/draconid/debug_jumps_state.inc), the party and the supplies in src/draconid_debug_jumps.c.
// The stops in story order (gen_debug_jumps.py checks these numbers against its own list):
#define DRACONID_JUMP_STOP_WOODS       0 // Act 1: Petalburg Woods, before Nerine robs the researcher (leg 1.13)
#define DRACONID_JUMP_STOP_ACT2        1 // Act 2: Rustboro, before Nerine steals the Devon Goods (2.01)
#define DRACONID_JUMP_STOP_ACT3        2 // Act 3: Meteor Falls, before Maxie takes the meteorite (3.01)
#define DRACONID_JUMP_STOP_ACT4        3 // Act 4: Petalburg, before Wally at the Gym door (4.01)
#define DRACONID_JUMP_STOP_ACT5        4 // Act 5: the Aqua Hideout B2F, before Nerine fight 5 and Matt (5.01)
#define DRACONID_JUMP_STOP_REVENGE     5 // the Sootopolis aftermath: out of Juan's Gym into Magma's revenge (6.R1)
#define DRACONID_JUMP_STOP_LEAGUE      6 // Act 6: the Pokemon League's door guards (6.02)
#define DRACONID_JUMP_STOP_ELDER       7 // Act 7: the Elder's call at the foot of the Sky Pillar (7.01)
#define DRACONID_JUMP_STOP_VILLAGE     8 // Act 7: the attack on the village (7.09)
#define DRACONID_JUMP_STOP_POSTGAME    9 // the post-game: home after the SS Ticket (P.01)
#define DRACONID_JUMP_STOP_COUNT      10
// The ready team's level: the stop's level cap (src/caps.c); after the Champion there is none, so these:
#define DRACONID_JUMP_LEVEL_ELDER      60 // the Champion's cap: the team that has just beaten STEVEN
#define DRACONID_JUMP_LEVEL_VILLAGE    DRACONID_REGIDRAGO_LEVEL     // after the Sky Pillar's battles
#define DRACONID_JUMP_LEVEL_POSTGAME   DRACONID_PRIMAL_LEGEND_LEVEL // the level of the finale's Primal legends
#define DRACONID_JUMP_LEVEL_SLACK       5 // a party this close to the stop's level keeps playing as it is
#define DRACONID_JUMP_MONEY_PER_LEVEL 1000 // the wallet is topped up to this times the stop's level
#define DRACONID_JUMP_MEDICINE         10 // potions of the stop's kind, topped up to this many
#define DRACONID_JUMP_REVIVES           5
#define DRACONID_JUMP_BALLS            10 // Poke Balls of the stop's kind
#define DRACONID_JUMP_HYPER_LEVEL      30 // from this level on: Hyper Potions and Great Balls
#define DRACONID_JUMP_MAX_LEVEL        48 // from this level on: Max Potions and Ultra Balls

#endif // GUARD_CONSTANTS_DRACONID_H
