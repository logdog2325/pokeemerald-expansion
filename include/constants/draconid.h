#ifndef GUARD_CONSTANTS_DRACONID_H
#define GUARD_CONSTANTS_DRACONID_H

// Draconid Emerald story constants. See docs/hack_changes.md.

// VAR_DRACONID_STATE: progress through the opening in Draconid Village
#define DRACONID_STATE_NEW_GAME        0 // waking up in the bedroom
#define DRACONID_STATE_SET_CLOCK       1 // Mom asked the player to set the clock
#define DRACONID_STATE_CLOCK_SET       2 // go to the Elder's house
#define DRACONID_STATE_EGG_RECEIVED    3 // egg chosen, hatching rite at the shrine
#define DRACONID_STATE_EGG_HATCHED     4 // hatched; Mom waits outside the shrine
#define DRACONID_STATE_READY_TO_LEAVE  5 // got the Running Shoes, may leave the village
#define DRACONID_STATE_LEFT_VILLAGE    6 // met Aster on Draconid Pass
#define DRACONID_STATE_SECOND_STARTER  7 // Stone Badge: Prof. Birch waits outside the Rustboro Gym
#define DRACONID_STATE_GOT_SECOND_STARTER 8 // second partner received

// VAR_STARTER_MON / VAR_ASTER_EGG: the three Draconid eggs (order of the Elder's choice)
#define DRACONID_EGG_DEINO             0
#define DRACONID_EGG_DREEPY            1
#define DRACONID_EGG_JANGMO_O          2
#define DRACONID_EGG_COUNT             3

#define DRACONID_EGG_SPECIES_0         SPECIES_DEINO
#define DRACONID_EGG_SPECIES_1         SPECIES_DREEPY
#define DRACONID_EGG_SPECIES_2         SPECIES_JANGMO_O

// Level the hatchling is raised to after the rite (eggs hatch at EGG_HATCH_LEVEL = 1)
#define DRACONID_HATCHLING_LEVEL       5
// Route 101: the wild Pokemon chasing Prof. Birch (round 1: Poochyena, as in the story)
#define DRACONID_RESCUE_SPECIES        SPECIES_POOCHYENA
#define DRACONID_RESCUE_LEVEL          2
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

// VAR_SECOND_STARTER: Prof. Birch's gift after the first Gym
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
#define BRENDAN_STATE_ROUTE_119        3 // beaten on Route 119, registered in the PokéNav (Act 4)
#define BRENDAN_STATE_LILYCOVE         4 // Lilycove double battle with May done (Act 4)
#define BRENDAN_STATE_MOSSDEEP         5 // Space Center tag battle done (Act 5, not a must-win)
#define BRENDAN_STATE_SOOTOPOLIS       6 // after the Sootopolis turn: knows the truth (Act 5)
                                         // 7 unused (the v1 Sootopolis Mega battles were removed in round 1 Act 5)
#define BRENDAN_STATE_POSTGAME         8 // post-game battles (Act 7)

// VAR_MAY_STATE: May's scenes (round 1 schedule, D-106; values in story order)
#define MAY_STATE_START                0
#define MAY_STATE_ROUTE_110            1 // beaten on Route 110, registered in the PokéNav (Act 2)
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
#define FINALE_STATE_RAYQUAZA          6 // Rayquaza caught, Dragon Ascent learned; Deoxys attacks
#define FINALE_STATE_METEOR_DESTROYED  7 // Deoxys beaten, Mega Rayquaza broke the meteor: credits, then home
#define FINALE_STATE_HOME              8 // woke up at home after the credits; the Elder waits downstairs
#define FINALE_STATE_POSTGAME          9 // the Elder brought the SS Ticket, the Lati TV news aired

// The finale's wild battles (D-110, D-111)
#define DRACONID_RAYQUAZA_LEVEL        70 // the must-catch Rayquaza at the summit
#define DRACONID_DEOXYS_BOSS_LEVEL     72 // Deoxys attacks right after (no catching, no running)
#define DRACONID_DEOXYS_LEVEL          80 // post-game: Deoxys where it fell, at the summit (as in ORAS)

#endif // GUARD_CONSTANTS_DRACONID_H
