# Draconid Emerald – evolutions, battle items and Mega Stones

Round 1, follow-up 3 (feedback 1.31, 1.33 and the Mega Stone addition; decisions D-216 – D-222 in
[hack_decisions.md](hack_decisions.md)). Every change is listed in [hack_changes.md](hack_changes.md).

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
opens with the Champion. The script is `Draconid_EventScript_BattleItemClerk` in
`data/scripts/draconid/battle_items.pory`; the tier badge counts are `BATTLE_ITEMS_TIER_*_BADGES` in
`include/constants/draconid.h`. The stock is **one list, newest tier first**: each tier's label starts its own new
items and runs on through every lower tier to a single `ITEM_NONE`, so a tier sells everything below it, nothing is
listed twice, and what just unlocked is at the top of the shop. The clerk greets by reputation (D-103: polite, cold
to the uniform, warm after Sootopolis) and says goodbye like the Mart clerks. Booster Energy is not sold (no Paradox
Pokémon to hold it).

<!-- tier table: prices from src/data/items.h -->
| Tier | Opens | New items (price) | New Mega Stones (₽50,000 each) |
|---|---|---|---|
| 1 | always (0 badges) | Silk Scarf 1,000, Charcoal 1,000, Mystic Water 1,000, Miracle Seed 1,000, Magnet 1,000, Never-Melt Ice 1,000, Black Belt 1,000, Poison Barb 1,000, Soft Sand 1,000, Sharp Beak 1,000, Twisted Spoon 1,000, Silver Powder 1,000, Hard Stone 1,000, Spell Tag 1,000, Dragon Fang 1,000, Black Glasses 1,000, Metal Coat 1,000, Fairy Feather 1,000 | – |
| 2 | 2 badges | Muscle Band 4,000, Wise Glasses 4,000, Quick Claw 4,000, Scope Lens 5,000, Wide Lens 5,000, Shell Bell 6,000, Big Root 4,000, Light Clay 6,000, King's Rock 5,000, Deep Sea Tooth 2,000, Deep Sea Scale 2,000, Everstone 3,000 | – |
| 3 | 4 badges | Leftovers 15,000, Black Sludge 10,000, Rocky Helmet 12,000, Expert Belt 12,000, Focus Sash 10,000, Eviolite 12,000, Air Balloon 5,000, Eject Button 8,000, Red Card 3,000, White Herb 5,000, Mental Herb 5,000, Power Herb 8,000 | – |
| 4 | 6 badges | Choice Band 40,000, Choice Specs 40,000, Choice Scarf 40,000, Life Orb 30,000, Assault Vest 30,000, Weakness Policy 20,000, Heavy-Duty Boots 20,000, Safety Goggles 20,000, Covert Cloak 20,000 | Alakazite, Aggronite, Mawilite, Sablenite, Gardevoirite, Altarianite, Pinsirite, Heracronite, Excadrite, Staraptite, Hawluchanite, Chandelurite |
| 5 | 8 badges | Loaded Dice 20,000, Clear Amulet 30,000, Mirror Herb 30,000, Punching Glove 15,000, Throat Spray 20,000, Blunder Policy 30,000, Room Service 20,000, Eject Pack 30,000, Protective Pads 15,000, Utility Umbrella 15,000, Ability Shield 20,000, Terrain Extender 15,000, Electric Seed 20,000, Grassy Seed 20,000, Misty Seed 20,000, Psychic Seed 20,000, Damp Rock 8,000, Heat Rock 8,000, Smooth Rock 8,000, Icy Rock 8,000, Flame Orb 15,000, Toxic Orb 15,000, Zoom Lens 10,000, Razor Claw 15,000, Bright Powder 30,000, Focus Band 10,000, Shed Shell 20,000, Grip Claw 10,000, Binding Band 20,000, Iron Ball 20,000, Lagging Tail 20,000, Sticky Barb 10,000, Metronome 15,000, Absorb Bulb 5,000, Cell Battery 5,000, Luminous Moss 5,000, Snowball 5,000, Adrenaline Orb 5,000 | Charizardite Y, Skarmorite, Starminite, Chimechite, Pyroarite, Golisopite, Barbaracite, Dragalgite, Glimmoranite, Golurkite, Raichunite X, Raichunite Y, Absolite Z |
| post-game | after the Champion (`FLAG_IS_CHAMPION`) | – | Salamencite, Latiasite, Latiosite, Galladite, Blazikenite, Sceptilite, Charizardite X, Feraligite, Garchompite Z |

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
held items); tier 5 keeps the Gen 9 prices (5,000–30,000); every Mega Stone the counter sells costs 50,000
(`MEGA_STONE_PRICE`). Only the Gen 9 branch of each `#if I_PRICE` block changed. Stones that are only found or
given stay at price 0 (they can't be sold).

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

- **Nine stones lie on maps the story opens later**, at the ORAS spot where Emerald has it, each in place of a
  low-value vanilla item (the pickup flag keeps its number and is renamed after the stone);
- **the counter sells more** from six badges, eight badges and after the Champion (₽50,000 each).

Source for the ORAS spots: Serebii, "Omega Ruby & Alpha Sapphire – Mega Evolutions"
(https://www.serebii.net/omegarubyalphasapphire/megaevolutions.shtml), read 2026-09-30.

| Stone | Pokémon (how the player gets it) | Where / when | ORAS |
|---|---|---|---|
| Manectite | Electrike (Route 110) | item ball, New Mauville (2, 11), was a Paralyze Heal – after Surf | Route 110 Cycling Road (passed before the Ring) |
| Banettite | Shuppet (Mt. Pyre) | item ball, Mt. Pyre 3F (0, 7), was a Super Repel | Mt. Pyre |
| Cameruptite | Numel (Route 112, Fiery Path) | item ball, Magma Hideout 3F room 3 (9, 19), was an Escape Rope | Magma Hideout (Delta, OR) |
| Absolite | Absol (Route 120) | item ball, Safari Zone NE (8, 17), was a Nugget | Safari Zone |
| Gyaradosite | Magikarp | item ball, Route 123 (27, 18), was an Ultra Ball | Route 123 |
| Sharpedonite | Carvanha | item ball, Aqua Hideout B2F (3, 13), was a Nest Ball | Aqua Hideout (Delta, AS) |
| Metagrossite | Beldum (Granite Cave 1%; Steven's post-game gift) | item ball, Mossdeep City (62, 35), was a Net Ball – Steven's town | Steven (League rematch, after the Delta Episode) |
| Glalitite | Snorunt (Shoal Cave) | item ball, Shoal Cave stairs room (13, 12), was an Ice Heal | Shoal Cave basement |
| Garchompite | Gible (Route 111 1%), Gabite (Victory Road) | item ball, Victory Road B2F (13, 8), was a Full Heal | Aarune (Secret Base Platinum Rank) |
| Alakazite, Aggronite, Mawilite, Sablenite, Gardevoirite, Altarianite, Pinsirite, Heracronite | Abra, Aron, Mawile, Sableye, Ralts, Swablu, Pinsir, Heracross | counter, 6 badges | Slateport Market, Rusturf Tunnel, Verdanturf, Sootopolis, Verdanturf (Wanda), Lilycove, Route 124, Route 127 |
| Excadrite, Staraptite, Hawluchanite, Chandelurite | Drilbur, Starly, Hawlucha, Litwick (new wild species) | counter, 6 badges | – (Legends Z-A) |
| Charizardite Y | Charmander (second starter) | counter, 8 badges | Scorched Slab |
| Skarmorite, Starminite, Chimechite, Raichunite X / Y, Absolite Z | Skarmory, Staryu, Chingling / Chimecho, Pikachu, Absol | counter, 8 badges | – (Legends Z-A) |
| Pyroarite, Golisopite, Barbaracite, Dragalgite, Glimmoranite, Golurkite | Litleo, Wimpod, Binacle, Skrelp, Glimmet, Golett (new wild species) | counter, 8 badges | – (Legends Z-A) |
| Salamencite | Bagon (Meteor Falls) | counter, post-game | Meteor Falls (after the Delta Episode) |
| Latiasite, Latiosite | the roaming Latis (post-game) | counter, post-game | Littleroot / on the Lati (Delta) |
| Galladite | Wally's signature (Gallade needs a Dawn Stone, not in the game yet) | counter, post-game | Cozmo (Delta) |
| Blazikenite, Sceptilite, Charizardite X, Feraligite | the rivals' and Nerine's / Aster's signature Megas (Sceptilite and the Charizardite / Feraligite also for the second starter) | counter, post-game | Route 120 / Route 114 (Blazikenite, Sceptilite); Fiery Path (Charizardite X) |
| Garchompite Z | Gible (second Mega form) | counter, post-game | – (Legends Z-A) |

**Not in the game** – no species the player can get (recheck against the wild tables at merge time,
[hack_wild.md](hack_wild.md), and add a stone to a counter tier if its species became obtainable): Venusaurite,
Blastoisinite, Beedrillite, Pidgeotite, Slowbronite, Gengarite, Kangaskhanite, Aerodactylite, Mewtwonite X / Y,
Ampharosite, Steelixite, Scizorite, Houndoominite, Tyranitarite, Swampertite, Medichamite, Lopunnite, Lucarionite
(+ Z: Riolu is on trainers only), Abomasite, Audinite, Froslassite (Snorunt needs a Dawn Stone), Diancite and the
other Legends Z-A stones (Clefable, Victreebel, Dragonite, Meganium, Emboar, Scolipede, Scrafty, Eelektross,
Chesnaught, Delphox, Greninja, Floette, Malamar, Zygarde, Drampa, Falinks, Heatran, Darkrai, Zeraora, Meowstic,
Crabominable, Magearna, Scovillain, Baxcalibur, Tatsugiri).
