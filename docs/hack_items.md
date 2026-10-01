# Draconid Emerald – evolutions, battle items, Mega Stones and Z-Crystals

Round 1, follow-up 3 (feedback 1.31, 1.33 and the Mega Stone addition; decisions D-216 – D-222 in
[hack_decisions.md](hack_decisions.md)) and feedback 2.5 (every Mega Stone reachable in the story, every stone and
Z-Crystal for sale after the Champion; D-320 – D-325). Every change is listed in [hack_changes.md](hack_changes.md).

## No trade evolutions (D-216, D-217)

Every trade evolution is a level evolution. The level follows the evolved form's base stat total (BST), next to
Hoenn's own level-up evolutions of that power, so it lands in the matching level-cap segment (`src/caps.c`):

| Evolved form's BST | Level | Constant | Hoenn neighbours | Cap segment |
|---|---|---|---|---|
| up to ~480 | 30 | `DRACONID_TRADE_EVO_LEVEL_LOW` | Sharpedo, Crawdaunt (30) | before Flannery (cap 30) |
| ~485–515 | 36 | `DRACONID_TRADE_EVO_LEVEL_MID` | the Hoenn starters' final stage (36) | before Winona (cap 38) |
| ~525–540 | 42 | `DRACONID_TRADE_EVO_LEVEL_HIGH` | Aggron, Glalie (42) | before Tate & Liza (cap 44) |
| third stage after a 42 | 48 | `DRACONID_TRADE_EVO_LEVEL_LATE` | – | before Juan (cap 48) |

Exceptions: Slowking at 37 (Slowbro's level, so the branch is a real choice); Milotic at 36 although it is a
540 – Feebas lives only on Route 119 (cap 38), and like Magikarp its weak first stage is the price (the Beauty
evolution still works too).

The table below is printed by `python3 tools/hack/check_evos.py --markdown` (the script also fails if a trade
evolution comes back, or if an earlier level entry would hide a held-item branch):

<!-- check_evos.py --markdown -->
| From | To | Level | Held item | BST from → to |
|---|---|---|---|---|
| Phantump | Trevenant | 30 | – | 309 → 474 |
| Spritzee | Aromatisse | 30 | – | 341 → 462 |
| Swirlix | Slurpuff | 30 | – | 341 → 480 |
| Boldore | Gigalith | 36 | – | 390 → 515 |
| Clamperl | Huntail | 36 | Deep Sea Tooth | 345 → 485 |
| Clamperl | Gorebyss | 36 | Deep Sea Scale | 345 → 485 |
| Feebas | Milotic | 36 | – | 200 → 540 |
| Graveler | Golem | 36 | – | 390 → 495 |
| Graveler Alola | Golem Alola | 36 | – | 390 → 495 |
| Gurdurr | Conkeldurr | 36 | – | 405 → 505 |
| Haunter | Gengar | 36 | – | 405 → 500 |
| Kadabra | Alakazam | 36 | – | 400 → 500 |
| Karrablast | Escavalier | 36 | – | 315 → 495 |
| Machoke | Machamp | 36 | – | 405 → 505 |
| Onix | Steelix | 36 | – | 385 → 510 |
| Poliwhirl | Politoed | 36 | Kings Rock | 385 → 500 |
| Porygon | Porygon2 | 36 | – | 395 → 515 |
| Pumpkaboo Average | Gourgeist Average | 36 | – | 335 → 494 |
| Pumpkaboo Large | Gourgeist Large | 36 | – | 335 → 494 |
| Pumpkaboo Small | Gourgeist Small | 36 | – | 335 → 494 |
| Pumpkaboo Super | Gourgeist Super | 36 | – | 335 → 494 |
| Scyther | Scizor | 36 | – | 500 → 500 |
| Shelmet | Accelgor | 36 | – | 305 → 495 |
| Slowpoke | Slowking | 37 | Kings Rock | 315 → 490 |
| Dusclops | Dusknoir | 42 | – | 455 → 525 |
| Electabuzz | Electivire | 42 | – | 490 → 540 |
| Magmar | Magmortar | 42 | – | 495 → 540 |
| Porygon2 | Porygon Z | 42 | – | 515 → 535 |
| Seadra | Kingdra | 42 | – | 440 → 540 |
| Rhydon | Rhyperior | 48 | – | 485 → 535 |

**Branches** keep their item, now held while levelling up (`EVO_LEVEL` + `IF_HOLD_ITEM`; the item is used up
like the trade used it):

| Base | With the item | Without it | Where to get the item |
|---|---|---|---|
| Poliwhirl | Politoed at 36 holding a **King's Rock** | Poliwrath (Water Stone, any level) | Mossdeep (the boy by Steven's house, vanilla); battle item counter from 2 badges |
| Slowpoke | Slowking at 37 holding a **King's Rock** | Slowbro at 37 | as above |
| Clamperl | Huntail / Gorebyss at 36 holding the **Deep Sea Tooth / Scale** | no evolution | Captain Stern's Scanner trade (one of the two, vanilla); the counter from 2 badges (both) |

The expansion's "use the item from the bag" shortcuts on these lines (Linking Cord, Metal Coat, King's Rock,
Dragon Scale, Up-Grade, Protector, Electirizer, Magmarizer, Reaper Cloth, Dubious Disc, Prism Scale, Sachet,
Whipped Dream, Deep Sea Tooth / Scale) are gone, so an item bought early can't skip the level. An Everstone stops
Kadabra like any other Pokémon (`P_KADABRA_EVERSTONE` = `GEN_3`). In-game and link trades simply never evolve.

## The battle item counter (D-218)

A second clerk stands behind the counter of every Poké Mart, at (1, 2) beside the vanilla clerk: Oldale,
Petalburg, Rustboro, Slateport, Mauville, Verdanturf, Fallarbor, Lavaridge, Fortree, Mossdeep, Sootopolis and the
Battle Frontier Mart (the player talks across the counter from (3, 2); in Verdanturf the Lass who stood there moved
one tile right). The Lilycove Department Store has a third clerk between the two on its 3F (the battle floor), at
(9, 2). The Pokémon League 1F has none (one talkable counter tile, and it belongs to the Acts 6–7 work).

The stock grows with the **number of Gym Badges** (in any order), so it follows the level caps; the post-game tier
opens with the Champion (`FLAG_IS_CHAMPION`, set at the Hall of Fame). The script is `Draconid_EventScript_BattleItemClerk` in
`data/scripts/draconid/battle_items.pory`; the tier badge counts are `BATTLE_ITEMS_TIER_*_BADGES` in
`include/constants/draconid.h`. The stock is **one list, newest tier first**: each tier's label starts its own new
items and runs on through every lower tier to a single `ITEM_NONE`, so a tier sells everything below it, nothing is
listed twice, and what just unlocked is at the top of the shop. The clerk greets by reputation (D-103: polite, cold
to the uniform, warm after Sootopolis) and says goodbye like the Mart clerks. Booster Energy is not sold (no Paradox
Pokémon to hold it).

**After the Champion** (D-320) the clerk asks which list – **BATTLE ITEMS / MEGA STONES / Z-CRYSTALS / CANCEL** – and
comes back to the question after each one ("Would you like to see another list?") until CANCEL or B:

- **BATTLE ITEMS**: the tier 5 list, i.e. everything of tiers 1–5 (126 entries; tier 5's stones on top as before);
- **MEGA STONES**: every Mega Stone of the build, **92**, in National Dex order of the Pokémon (X before Y, a second
  Mega form's stone – Absolite Z, Garchompite Z, Lucarionite Z – right after the first);
- **Z-CRYSTALS**: every Z-Crystal, **35**: the 18 type crystals in type order (Normalium Z … Fairium Z), then the 17
  species crystals (Pikanium Z … Ultranecrozium Z).

The two last lists (`Draconid_MegaStones_PostGame`, `Draconid_ZCrystals_PostGame`) are written by
`python3 tools/hack/check_megas.py --write` from `src/data/items.h` (every `HOLD_EFFECT_MEGA_STONE` /
`HOLD_EFFECT_Z_CRYSTAL` item), and `check_megas.py` fails while a stone or crystal is missing or out of order, so one
the build adds later can't be left out. Each list is an ordinary mart (BUY / SELL / QUIT); in every mart LEFT and
RIGHT now turn a page of the list (D-321), so the 92 stones are 12 pages.

<!-- tier table: prices from src/data/items.h -->
| Tier | Opens | New items (price) | New Mega Stones (₽50,000 each) |
|---|---|---|---|
| 1 | always (0 badges) | Silk Scarf 1,000, Charcoal 1,000, Mystic Water 1,000, Miracle Seed 1,000, Magnet 1,000, Never-Melt Ice 1,000, Black Belt 1,000, Poison Barb 1,000, Soft Sand 1,000, Sharp Beak 1,000, Twisted Spoon 1,000, Silver Powder 1,000, Hard Stone 1,000, Spell Tag 1,000, Dragon Fang 1,000, Black Glasses 1,000, Metal Coat 1,000, Fairy Feather 1,000 | – |
| 2 | 2 badges | Muscle Band 4,000, Wise Glasses 4,000, Quick Claw 4,000, Scope Lens 5,000, Wide Lens 5,000, Shell Bell 6,000, Big Root 4,000, Light Clay 6,000, King's Rock 5,000, Deep Sea Tooth 2,000, Deep Sea Scale 2,000, Everstone 3,000 | – |
| 3 | 4 badges | Leftovers 15,000, Black Sludge 10,000, Rocky Helmet 12,000, Expert Belt 12,000, Focus Sash 10,000, Eviolite 12,000, Air Balloon 5,000, Eject Button 8,000, Red Card 3,000, White Herb 5,000, Mental Herb 5,000, Power Herb 8,000 | – |
| 4 | 6 badges | Choice Band 40,000, Choice Specs 40,000, Choice Scarf 40,000, Life Orb 30,000, Assault Vest 30,000, Weakness Policy 20,000, Heavy-Duty Boots 20,000, Safety Goggles 20,000, Covert Cloak 20,000 | Alakazite, Aggronite, Mawilite, Sablenite, Gardevoirite, Galladite, Altarianite, Pinsirite, Heracronite, Absolite, Pidgeotite, Steelixite, Scizorite, Houndoominite, Gengarite, Kangaskhanite, Excadrite, Staraptite, Hawluchanite, Chandelurite, Clefablite |
| 5 | 8 badges | Loaded Dice 20,000, Clear Amulet 30,000, Mirror Herb 30,000, Punching Glove 15,000, Throat Spray 20,000, Blunder Policy 30,000, Room Service 20,000, Eject Pack 30,000, Protective Pads 15,000, Utility Umbrella 15,000, Ability Shield 20,000, Terrain Extender 15,000, Electric Seed 20,000, Grassy Seed 20,000, Misty Seed 20,000, Psychic Seed 20,000, Damp Rock 8,000, Heat Rock 8,000, Smooth Rock 8,000, Icy Rock 8,000, Flame Orb 15,000, Toxic Orb 15,000, Zoom Lens 10,000, Razor Claw 15,000, Bright Powder 30,000, Focus Band 10,000, Shed Shell 20,000, Grip Claw 10,000, Binding Band 20,000, Iron Ball 20,000, Lagging Tail 20,000, Sticky Barb 10,000, Metronome 15,000, Absorb Bulb 5,000, Cell Battery 5,000, Luminous Moss 5,000, Snowball 5,000, Adrenaline Orb 5,000 | Charizardite Y, Salamencite, Skarmorite, Starminite, Chimechite, Froslassite, Pyroarite, Golisopite, Barbaracite, Dragalgite, Glimmoranite, Golurkite, Raichunite X, Raichunite Y, Absolite Z, Garchompite Z |
| post-game | after the Champion (`FLAG_IS_CHAMPION`) | – (BATTLE ITEMS = the tier 5 list) | **every** Mega Stone (92, MEGA STONES) and **every** Z-Crystal (35 at 30,000, Z-CRYSTALS) |

Vanilla item balls and hidden items that hold battle items (the Shoal Cave Never-Melt Ice, the Granite Cave
Everstones, the Mt. Pyre incenses, …) stay where they are.

### Prices (D-219)

Prices climb with the tiers and follow the prize money a player earns (the first battle of every trainer in
`tools/hack/trainers/segments.json` – Gym Leaders and admins included, rematches and the rivals' story fights
not – at `4 × last Pokémon's level × class money`):

| Segment (cap) | Prize money in the segment | Total at its end |
|---|---|---|
| S1 to Roxanne (15) | ~15,000 | ~15,000 |
| S2 to Brawly (20) | ~12,000 | ~27,000 |
| S3 to Wattson (25) | ~34,000 | ~61,000 |
| S4 to Flannery (30) | ~56,000 | ~117,000 |
| S5 to Norman (34) | ~22,000 | ~140,000 |
| S6 to Winona (38) | ~69,000 | ~209,000 |
| S7 to Tate & Liza (44) | ~189,000 | ~397,000 |
| S8 to Juan (48) | ~66,000 | ~463,000 |
| S9 to the Champion (60) | ~91,000 | ~554,000 |

Type boosters cost 1,000 (`TYPE_BOOSTING_PRICE`, the Gen 7 price, down from Gen 9's 3,000); tier 2 items
4,000–6,000; tier 3 5,000–15,000; tier 4 20,000–40,000 (the three Choice items at 40,000 are the most expensive
held items); tier 5 keeps the Gen 9 prices (5,000–30,000); every Mega Stone costs 50,000 (`MEGA_STONE_PRICE`) and
every Z-Crystal 30,000 (`Z_CRYSTAL_PRICE`, D-320). Only the Gen 9 branch of each `#if I_PRICE` block changed.

After the Champion the money comes from rematches: a League run (the Elite Four's post-game teams and Steven's
rematch) pays 45,200 (Sidney 7,200, Phoebe 7,300, Glacia 7,400, Drake 7,500, Steven 15,800; twice that with the
Amulet Coin), Lance about 17,200 a win. A stone is about one League run, a crystal two thirds of one: a Z-Move is
once per battle where a Mega lasts the whole battle, but a type crystal fits every Pokémon with a move of its type.

Every stone and crystal has its price **because the post-game lists sell them all**: a 0-price item in a mart is
free (`Task_BuyHowManyDialogueInit` then allows up to 999 for nothing). Stones and crystals that are found or given
in the story stay found or given there. **Shops never buy a stone or crystal back** (D-322,
`I_SELL_MEGA_STONES_Z_CRYSTALS` FALSE: `GetItemSellPrice` is 0 for them, and the bag's SELL checks the sell price):
so the price doesn't turn the story's found stones into ₽12,500 each, as D-222 had it with price 0.

## Gym Leader gifts (D-220)

Each Gym Leader hands over their type's booster right after their TM (a `call` in both vanilla TM paths: straight
after the battle, and on the later visit when the bag was full). A full bag only costs the booster; the counter
sells it too.

| Leader | TM | Booster |
|---|---|---|
| Roxanne | Rock Tomb | Hard Stone |
| Brawly | Bulk Up | Black Belt |
| Wattson | Shock Wave | Magnet |
| Flannery | Overheat | Charcoal |
| Norman | Facade | Silk Scarf |
| Winona | Aerial Ace | Sharp Beak |
| Tate & Liza | Calm Mind | Twisted Spoon |
| Juan | Water Pulse | Mystic Water |

## Mega Stones (D-221, D-222)

Nothing before the **Mega Ring** (Aster, Jagged Pass, Act 3). The second starter's own stone (Charizardite X /
Feraligite / Sceptilite) stays the Lavaridge traveller's gift right after it (D-126). After that:

- **Eleven stones lie on maps the story opens later**, at the ORAS spot where Emerald has it, each in place of a
  low-value vanilla item (the pickup flag keeps its number and is renamed after the stone) – ten before the
  Champion; the Safari Zone's north-east area (Absolite) opens only with the Hall of Fame (D-323);
- **the counter sells more** from six and eight badges (₽50,000 each), and **every** stone after the Champion.

**Every stone whose Pokémon line the player can get before the post-game has a source before it** (D-323; 50 of the
92 with the round 2 wild tables). `python3 tools/hack/check_megas.py` checks it: each stone's line (every species linked to its Mega's species by
evolutions), where and when the player gets the line (the wild tables, gifts, eggs, trades, static encounters), the
stone's sources (item balls, gifts, counter tiers), and it fails when an obtainable line's stone has nothing before
the post-game, or a stone or crystal is missing from the post-game lists. Rerun it whenever the wild tables or the
gifts change.

Source for the ORAS spots: Serebii, "Omega Ruby & Alpha Sapphire – Mega Evolutions"
(https://www.serebii.net/omegarubyalphasapphire/megaevolutions.shtml), read 2026-09-30.

| Stone | Pokémon (how the player gets it) | Where / when | ORAS |
|---|---|---|---|
| Manectite | Electrike (Route 110) | item ball, New Mauville (2, 11), was a Paralyze Heal – after Surf | Route 110 Cycling Road (passed before the Ring) |
| Banettite | Shuppet (Mt. Pyre) | item ball, Mt. Pyre 3F (0, 7), was a Super Repel | Mt. Pyre |
| Cameruptite | Numel (Route 112, Fiery Path) | item ball, Magma Hideout 3F room 3 (9, 19), was an Escape Rope | Magma Hideout (Delta, OR) |
| Absolite | Absol (Route 120) | counter, 6 badges (D-323); the item ball in the Safari Zone NE (8, 17), was a Nugget, is post-game (the construction workers stand in the way until the Hall of Fame) | Safari Zone |
| Gyaradosite | Magikarp | item ball, Route 123 (27, 18), was an Ultra Ball | Route 123 |
| Sharpedonite | Carvanha | item ball, Aqua Hideout B2F (3, 13), was a Nest Ball | Aqua Hideout (Delta, AS) |
| Metagrossite | Beldum (Granite Cave 1%; Steven's post-game gift) | item ball, Mossdeep City (62, 35), was a Net Ball – Steven's town | Steven (League rematch, after the Delta Episode) |
| Glalitite | Snorunt (Shoal Cave) | item ball, Shoal Cave stairs room (13, 12), was an Ice Heal | Shoal Cave basement |
| Garchompite | Gible (Route 111 1%), Gabite (Victory Road) | item ball, Victory Road B2F (13, 8), was a Full Heal | Aarune (Secret Base Platinum Rank) |
| Ampharosite | Mareep (Draconid Pass; round 2 wild tables) | item ball, New Mauville (32, 25), was an Ultra Ball (D-323) | New Mauville |
| Slowbronite | Slowpoke (surfing, Route 103 and the seas; round 2) | item ball, Shoal Cave entrance room (30, 3), was a Big Pearl (D-323) – the Shell Bell man's room | Shoal Cave (the Shoal Salt / Shell man) |
| Alakazite, Aggronite, Mawilite, Sablenite, Gardevoirite, Altarianite, Pinsirite, Heracronite | Abra, Aron, Mawile, Sableye, Ralts, Swablu, Pinsir, Heracross | counter, 6 badges | Slateport Market, Rusturf Tunnel, Verdanturf, Sootopolis, Verdanturf (Wanda), Lilycove, Route 124, Route 127 |
| Galladite | Ralts (Gallade: a Kirlia ♂ with a Dawn Stone – the Abandoned Ship's, from the Dawn / Dusk Stone work) | counter, 6 badges (D-323; was post-game) | Prof. Cozmo, Fallarbor (Delta) |
| Pidgeotite, Steelixite, Scizorite, Houndoominite | Pidgey (Draconid Pass), Onix (Granite Cave), Scyther (Safari Zone 1%), Houndour (Route 113) – round 2 wild tables | counter, 6 badges (D-323) | Rustboro (Mr. Stone), Granite Cave, Petalburg Woods, Lavaridge – all passed before the Ring |
| Gengarite, Kangaskhanite | Gastly (Mt. Pyre), Kangaskhan (Safari Zone 1%) – round 2 | counter, 6 badges (D-323) | Battle Resort; Pacifidlog (no item to replace there) |
| Excadrite, Staraptite, Hawluchanite, Chandelurite, Clefablite | Drilbur, Starly, Hawlucha, Litwick (Chandelure: a Dusk Stone, the Mt. Pyre exterior – the Dawn / Dusk Stone work), Clefairy (Meteor Falls, round 2) | counter, 6 badges (Clefablite D-323) | – (Legends Z-A) |
| Charizardite X, Feraligite, Sceptilite | the second starter (Charmander, Totodile, Treecko; Prof. Oak, Act 1) | the Lavaridge traveller's gift for the one chosen (D-126); counter, post-game (all three) | Fiery Path (Charizardite X); Route 120 / Route 114 (Sceptilite) |
| Charizardite Y | Charmander (second starter) | counter, 8 badges | Scorched Slab |
| Salamencite | Bagon (Meteor Falls B1F 2R: Waterfall and the Rain Badge) | counter, 8 badges (D-323; was post-game) | Meteor Falls (Zinnia's grandmother, after the Delta Episode) |
| Froslassite, Garchompite Z | Snorunt (Shoal Cave; Froslass: a Snorunt ♀ with a Dawn Stone), Gible | counter, 8 badges (D-323; Garchompite Z was post-game) | – (Legends Z-A) |
| Skarmorite, Starminite, Chimechite, Raichunite X / Y, Absolite Z | Skarmory, Staryu, Chingling / Chimecho, Pikachu, Absol | counter, 8 badges | – (Legends Z-A) |
| Pyroarite, Golisopite, Barbaracite, Dragalgite, Glimmoranite, Golurkite | Litleo, Wimpod, Binacle, Skrelp, Glimmet, Golett (new wild species) | counter, 8 badges | – (Legends Z-A) |
| Latiasite, Latiosite | the roaming Latis (post-game) | counter, post-game | Littleroot / on the Lati (Delta) |
| Meganiumite | Chikorita (Birch's Johto starters, post-game) | counter, post-game | – (Legends Z-A) |
| Dragoninite | Dratini (Lance's gift with it) | Lance's gift after his first defeat, Draconid village, post-game (D-262); counter, post-game | – (Legends Z-A) |
| every other stone | no Pokémon line the player can get (see below) | counter, post-game | |

**No line in the game** – sold after the Champion only, with nothing in the story (38 stones with the round 2 wild
tables; `check_megas.py` lists them as "not in the game" and fails as soon as the wild tables or a gift make one of
these lines obtainable before the post-game, so the stone then needs a story source): Venusaurite, Blastoisinite,
Beedrillite, Victreebelite, Aerodactylite, Mewtwonite X / Y, Tyranitarite, Blazikenite and Swampertite (the player
gets no Torchic or Mudkip: May keeps hers, Mudkip isn't handed out), Medichamite, Lopunnite, Lucarionite and
Lucarionite Z (Riolu is on trainers only), Abomasite, Audinite, Diancite and the other Legends Z-A stones (Heatran,
Darkrai, Emboar, Scolipede, Scrafty, Eelektross, Chesnaught, Delphox, Greninja, Floette, Meowstic, Malamar, Zygarde,
Crabominable, Drampa, Magearna, Zeraora, Falinks, Scovillain, Tatsugiri, Baxcalibur).

## Z-Crystals (D-267 – D-269)

The **Z-Power Ring** and the first crystal come at the egg ceremony (Act 1): Alola's dragon keepers sent them with
their egg "for the one who carries the prophecy" (D-267). After that the crystals come along the road – **all 18
type crystals during the story**, one to four per act, from people with a reason or in item balls where their type
lives (`data/scripts/draconid/zmoves.pory`, the maps' `map.json`). A ball crystal replaces a low-value vanilla item
and its pickup flag keeps its number under the crystal's name (D-222's way). One Z-Move per battle, under the level
caps, so no early crystal decides a gym: the table says which gym each one meets first. Among the opponents only
Aster and Nerine hold one, from the night they call Rayquaza down (D-268, `check_party.py` `Z_TRAINERS`).

How to use one: a Pokémon holds the crystal; in battle choose a move of its type and press START in the move menu
(the Elder says so at the ceremony).

| Crystal | Where | When (act / segment) | Why there | First gym it meets |
|---|---|---|---|---|
| Normalium Z | the Elder, with the Z-Power Ring (egg ceremony, shrine) | Act 1 / S1 | the simplest crystal: every partner knows a Normal move | Roxanne (Rock resists it) |
| Buginium Z | item ball, Petalburg Woods (4, 26), was a Paralyze Heal | Act 1 / S1 | the bug forest | Roxanne (resists it) |
| Rockium Z | item ball, Granite Cave 1F (17, 7), was an Escape Rope | Act 2 / S2 | Granite Cave | Brawly (Fighting resists it) |
| Fightinium Z | item ball, Granite Cave B1F (15, 21), was a Poké Ball | Act 2 / S2 | Makuhita's cave, a step from Brawly's town | Brawly (neutral) |
| Firium Z, Waterium Z, Grassium Z | Prof. Oak by Stern's shipyard, Slateport (23, 39): his cousin Samson Oak's crystals from Alola for the three starters he brought to Hoenn, the second partner's first | Act 2 / S3 | Oak gave the second partner (D-233); the other two starters go back to his lab, so their crystals are the player's too (any Pokémon of the type can hold one) | Wattson (all three neutral) |
| Fairium Z | item ball, Route 117 (16, 18), was a Great Ball | Act 2 / S3 | the flower meadows by the Day Care | Wattson (neutral) |
| Poisonium Z | item ball, Route 112 (14, 43), was a Nugget | Act 3 / S4 | the volcanic gas below Mt. Chimney | Flannery (neutral) |
| Dragonium Z | Aster at Meteor Falls, from the falls' Draconids (Jagged Pass after the Mega Ring if the bag was full) | Act 3 / S4 | the clan's kin (D-155, D-271); every egg dragon is part Dragon | Flannery (Fire doesn't resist Dragon; one hit) |
| Groundium Z | item ball, the Route 111 desert (12, 54), was a Stardust | Act 3–4 / S5 (Go-Goggles) | the sand, after Flannery – not on Jagged Pass, right before her Fire gym | Norman (neutral) |
| Electrium Z | item ball, New Mauville (16, 22), was an Escape Rope | Act 4 / S6 (Surf) | the power plant | Winona (Flying is weak to it; one hit under the cap) |
| Steelium Z | item ball, New Mauville (17, 10), was a Full Heal | Act 4 / S6 (Surf) | the machines | Winona (neutral) |
| Flyinium Z | item ball, Route 119 (12, 121), was a Super Repel | Act 4 / S6 | the long route of birds before Fortree | Winona (her Skarmory resists it) |
| Ghostium Z | item ball, Mt. Pyre 2F (0, 10), was an Ultra Ball | Act 4 / S7 | the mountain of graves | Tate & Liza (weak to it; one hit in a double) |
| Darkinium Z | item ball, Aqua Hideout B1F (15, 10), was a Nugget | Act 5 / S7 | Team Aqua's den | Tate & Liza (as Ghostium; still one Z-Move per battle) |
| Psychium Z | item ball, Route 127 (14, 6), was a Zinc | Act 5 / S7 | the open sea off Mossdeep, the twins' city | Juan (neutral) |
| Icium Z | item ball, Shoal Cave ice room (12, 21), was a Never-Melt Ice | Act 5 / S7–S8 (low tide) | the ice room | Juan (Water resists it) |
| Kommonium Z (species) | **a Jangmo-o egg only**: Nerine leaves it by the lantern on the Mt. Pyre summit (21, 9) after her fight 4; the ball waits there until picked up | Act 4 / S7 | she knows the Alolan line's "war drum" (a hint, D-269); Kommo-o's own crystal (Clanging Scales → Clangorous Soulblaze) | – |
| Pikanium Z (species) | item ball, Safari Zone south-west (0, 37), was a Max Revive | Act 4 / S7 | wild Pikachu live in this Safari Zone (Catastropika needs Volt Tackle: breed a Pichu holding a Light Ball – wild Pikachu may hold one) | – |
| Mimikium Z (species) | hidden, Mt. Pyre Exterior (9, 8), was an Ultra Ball | Act 4 / S7 | wild Mimikyu live on Mt. Pyre's slopes (Play Rough → Let's Snuggle Forever) | – |

**Post-game only** (no species for them in the story; the post-game shop is a separate task): Kommonium Z for
the players whose egg wasn't Jangmo-o (Kommo-o has no other source), Aloraichium Z (Alolan Raichu doesn't evolve
in Hoenn), Pikashunium Z (no cap Pikachu), Eevium Z, Snorlium Z, Mewnium Z, Decidium Z, Incinium Z, Primarium Z,
Lycanium Z, Tapunium Z, Solganium Z, Lunalium Z, Marshadium Z, Ultranecrozium Z.

**Who else holds one** (trainer data, D-268, D-282): Aster's and Nerine's ace from the village battles before the
League on (Act 5½) – Aster: Ghostium Z (Dragapult) / Kommonium Z (Kommo-o) / Darkinium Z (Hydreigon) by her leftover
egg, next to her Mega Salamence (the Elder's Key Stone); Nerine: the same crystals on the egg the Elder kept aside,
Kommonium Z with "Clanging Scales" on the Kommo-o teams, next to her Mega from the Seafloor. Nobody else
(`check_party.py`: a Z-Crystal outside `Z_TRAINERS` is an error).

## Dawn Stone and Dusk Stone (D-342)

Vanilla Emerald has neither stone, so Gallade, Froslass, Chandelure, Honchkrow, Mismagius and Aegislash could not be
evolved. Four item balls now hold them, at the ORAS spots where Emerald has a counterpart (Serebii's Item Dex, read
2026-10-01: Dusk Stone on Mt. Pyre; Dawn Stone in Victory Road and Sea Mauville – Emerald's sunken-ship stand-in is
the Abandoned Ship). Each replaces a low-value vanilla item (the Mt. Pyre 2F ball went to the Ghostium Z, D-269); the pickup flag keeps its number and is renamed after
the stone. Tested by `tests/stones.play`.

| Stone | Where (was) | Opens | For |
|---|---|---|---|
| Dawn Stone | Abandoned Ship, Rooms 1F (4, 5) (Harbor Mail) | Surf, Route 108 (S6) | Kirlia ♂ → Gallade (Ralts, Route 102), Snorunt ♀ → Froslass (Shoal Cave) |
| Dawn Stone | Victory Road 1F (40, 26) (Max Elixir) | eight badges (S9) | the second of the two |
| Dusk Stone | Mt. Pyre exterior (16, 22), hidden by a grave (Max Ether) | Mt. Pyre (S7) | Lampent → Chandelure (Litwick, Mt. Pyre), Murkrow → Honchkrow (Route 120), Misdreavus → Mismagius (Mt. Pyre 4F–6F) |
| Dusk Stone | Mt. Pyre exterior (27, 15) (Max Potion) | Mt. Pyre (S7) | a second one; Doublade → Aegislash if Honedge becomes obtainable |

Not added here: a shop or repeatable source (the battle-item counter stays battle items), and the Shiny Stone /
Ice Stone evolutions (Roselia → Roserade still has no stone).


## Z-Crystals (D-320)

The Z-Move work (feedback 1.58 / 1.62) gives the Z-Ring and spreads crystals through Acts 1–5; the battle item
counter sells **every** Z-Crystal after the Champion (Z-CRYSTALS, 30,000 each). `check_megas.py` lists each
crystal's story sources (type crystals) or the Pokémon of a species crystal and when the player can get it;
species crystals are post-game only by design.
