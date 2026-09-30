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
