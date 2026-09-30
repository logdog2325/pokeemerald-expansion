# Draconid Emerald – trainers, level caps, AI

Every trainer in the game gets an **enhanced rematch team**: the richest roster the trainer has (their ORAS
rematch team where one is known, otherwise their Emerald rematch roster, otherwise their own team made fuller),
scaled to the point of the story where the player meets them, under a **hard level cap**. This page is the
rulebook; `tools/hack/trainers/` checks it.

> **What actually shipped (Phase 6 merge):** no ORAS rematch team is used. There are no ORAS data files in
> this repository and none of the batches could vouch for an ORAS roster from memory, so of the 798 trainers
> the batches rewrote, **362 use their Emerald rematch roster** and **436 an enhanced own team** (0 ORAS).
> `tools/hack/trainers/sources.json` lists the source per trainer; the story trainers (rivals, Aster, Wally)
> have hand-written teams. Swapping in real ORAS rosters later only needs new blocks through the same checks.

## Level caps

`include/config/caps.h`: `B_EXP_CAP_TYPE = EXP_CAP_HARD`, `B_LEVEL_CAP_TYPE = LEVEL_CAP_FLAG_LIST`,
`B_RARE_CANDY_CAP = TRUE`, `B_LEVEL_CAP_EXP_UP = TRUE` (Pokémon under the cap get extra EXP, so a new catch
catches up quickly). The caps are the table in `src/caps.c` (`sLevelCapFlagMap`):

| Segment | Until | Cap | Where |
|---|---|---|---|
| S1 | Stone Badge | 15 | Draconid Pass, Routes 101–104, Petalburg Woods, Rustboro, Route 116 |
| S2 | Knuckle Badge | 20 | Rusturf Tunnel, Dewford, Route 106/109 beaches, Route 115 south |
| S3 | Dynamo Badge | 25 | Slateport, Routes 103 east, 110, 117, 118 west, Mauville, Trick House 1 |
| S4 | Heat Badge | 30 | Routes 111 (not the desert)–114, Mt. Chimney, Jagged Pass, Lavaridge, Trick House 2 |
| S5 | Balance Badge | 34 | Route 111 desert, Petalburg Gym, Trick House 3 |
| S6 | Feather Badge | 38 | Surf routes 105–109, Abandoned Ship, Routes 115 north, 118 east, 119, Weather Institute, Fortree, Trick House 4 |
| S7 | Mind Badge | 44 | Routes 120–134, Mt. Pyre, Lilycove, Magma and Aqua Hideouts, Mossdeep Gym |
| S8 | Rain Badge | 48 | Space Center, Seafloor Cavern, Sky Pillar, Sootopolis Gym, Trick House 6 |
| S9 | Champion | 60 | Meteor Falls (Waterfall), Victory Road, Elite Four, Champion, Trick House 7 |
| POST | – | none | Steven, S.S. Tidal, Trick House 8, gym leader rematches, last rematch tier |

A trainer belongs to the **earliest** segment in which the player can reach it (maps split by Surf, the desert or
Rock Smash are split per trainer), so a trainer's levels never beat the cap in force. The per-trainer table is
generated: `python3 tools/hack/trainers/build_segments.py` → `tools/hack/trainers/segments.json`
(`--list S3` prints one segment). The tests build turns the caps off (`include/config/test.h`), because the
vanilla EXP tests run without badges.

### Rematch tiers
`OW_REMATCH_TIER_BADGES` (`include/config/overworld.h`, `src/battle_setup.c`): rematches still start at 5 badges,
but tier 2 needs 5 badges, tier 3 needs 6, tier 4 needs 7, and the last tier needs the game cleared. Until then
the trainer stays on the last tier the player unlocked. So tier 2 teams are S6 teams (or later if the trainer's
first battle is later), tier 3 S7, tier 4 S8, tier 5 POST. Gym leader and Wally rematches are post-game as in
vanilla.

## Levels inside a segment

| Segment | Route trainers | Gym trainers, admins | Leader / boss ace (= cap) |
|---|---|---|---|
| S1 | 5–12 | 11–13 | 13–15 |
| S2 | 12–17 | 16–18 | 18–20 |
| S3 | 17–22 | 21–23 | 23–25 |
| S4 | 21–27 | 26–28 | 28–30 |
| S5 | 26–31 | 30–32 | 32–34 |
| S6 | 30–35 | 34–36 | 36–38 |
| S7 | 34–41 | 39–42 | 42–44 |
| S8 | 40–45 | 44–46 | 46–48 |
| S9 | 48–55 (Victory Road) | Elite Four aces 55–58 | Champion 60 |
| POST | 60–70 | 66–72 | 70–80 |

- Early on a map path → low in the band, late → high. The last Pokémon is the strongest (the ace).
- Grunts use the route band; Tabitha/Shelly/Matt the gym band; Maxie/Archie the ace band.
- Rematch tiers: each tier is higher than the one before and never lower than tier 1.

## Party size

| Segment | Route / grunt | Gym trainer | Leader, boss, E4 |
|---|---|---|---|
| S1 | 1–3 | 2–3 | 4 |
| S2 | 2–3 | 2–3 | 4 |
| S3 | 2–4 | 3 | 5 |
| S4 | 3–4 | 3–4 | 5 |
| S5 | 3–5 | 4 | 6 |
| S6+ | 4–5 | 4–5 | 6 |
| S8+, POST | 4–6 | 5–6 | 6 |

Double-battle trainers keep `Double Battle: Yes` and have at least 2 (usually 4) Pokémon.

## Where a team comes from

1. **Trainers with Emerald rematch tiers** (`TRAINER_X_1`…`_5`, gym leaders included): the **Emerald rematch
   roster**, i.e. the species of the highest vanilla tier (`_5`, or `_6` for Cindy / Amy & Liv) in
   `src/data/trainers.party` on `master`. *Every* tier uses that roster – tier 1 as the smallest, least evolved
   version, each later tier with more of it (in the roster's order) and further evolved – so the tiers written by
   different batches stay one trainer.
2. **Other trainers**: their **ORAS rematch team** (Omega Ruby / Alpha Sapphire) when it is known with confidence.
3. Otherwise the **enhanced own team**: the trainer's vanilla (or ORAS first-battle) team, evolved where the level
   allows and filled up to the party size with species of the trainer's class and theme.

Scaling down: a species appears at the evolution stage its level allows (Salamence only from 50; Shelgon from
30; the check allows **aces and bosses** up to 3 levels early and reports it as a warning). Keep the roster's
identity: Calvin's Swellow / Linoone / Mightyena become Taillow / Zigzagoon / Poochyena at Lv 5–8.

Each batch records its source per trainer (`oras-rematch`, `emerald-rematch`, `enhanced`) in a sidecar file;
the table at the end of this page is generated from them. ORAS data is from memory (there are no ORAS data files
in this repository), which is why every team is still run through the legality checks below.

## Species pool

The Hoenn Pokédex (with the cross-generation evolutions the expansion lists there: Gallade, Froslass, Probopass,
Dusknoir, Roserade, Magnezone, …) plus every species some vanilla Emerald trainer uses (Kabuto, Aerodactyl, …).
Not used: legendaries and mythicals, and the Deino / Dreepy / Jangmo-o lines (reserved for the player and Aster).
Story trainers (Brendan, May, Wally, Aster) have their own rosters (docs/hack_changes.md, Phase 5).

## Moves, abilities, items

- **Moves**: at most 4, learnable by the species or a pre-evolution (checked). Route trainers in S1–S3 may leave
  moves out (the game uses the last four level-up moves). Gym trainers, leaders and everyone from S4 get full
  sets: STAB + coverage, a status or set-up move where it fits. TM moves for leaders from S1 (their badge TM:
  Rock Tomb, Bulk Up, Shock Wave, Overheat, Facade, Aerial Ace, Calm Mind, Water Pulse), for everyone from S4.
  Egg moves for aces and bosses. Before S4, nothing above 90 base power except a leader's ace. No OHKO moves.
- **Abilities**: one of the species' own (checked); hidden abilities only for leaders, bosses, E4, Champion and
  POST.
- **Natures**: leaders, bosses, E4, Champion, POST get fitting natures; others optional.
- **IVs**: route trainers S1 6, S2 9, S3 12, S4 15, S5 18, S6 20, S7 22, S8 25, S9 28, POST 31; gym trainers +4;
  grunts as route; leaders, admins, bosses, E4, Champion 31 (the default).
- **EVs**: none, except E4 / Champion / POST (any legal spread) and leaders from S5 (≤ 252 in total).
- **Held items**: S1–S3 route trainers none or an Oran Berry on the ace; S4–S6 berries and type-boosters;
  S7+ any sensible competitive item. Leaders and bosses: Oran Berry (S1–S2), Sitrus Berry (S3+), competitive
  items (Leftovers, Life Orb, …) from S5.
- **Bag items** (`Items:`): leaders and bosses 2 – Potion (S1–S2), Super Potion (S3–S4), Hyper Potion (S5–S7),
  Full Restore (S8+); E4 and Champion 2–4 Full Restores. Route trainers keep what they have.
- **Megas** (`MEGA_TRAINERS` in `check_party.py`): only Maxie in the Magma Hideout (Camerupt), Archie in the
  Seafloor Cavern (Sharpedo), Steven (Metagross), gym leaders' last rematch tier (one thematic Mega, e.g.
  Roxanne's Aerodactyl, Wattson's Manectric, Flannery's Camerupt, Winona's Altaria), and the story trainers late
  in the game. No Tera, Dynamax or Z-Moves.

## AI

| Who | AI |
|---|---|
| Route trainers, grunts | `Basic Trainer` (S1–S3); `Basic Trainer / Smart Mon Choices` (S4+) |
| Gym trainers | `Basic Trainer / Smart Mon Choices` |
| Admins, leaders, Maxie/Archie, rivals, Wally, Aster | `Smart Trainer / Ace Pokemon` |
| Elite Four, Champion, Steven, POST leaders, Aster at Sky Pillar | `Smart Trainer / Prediction / Ace Pokemon` |

`Smart Trainer` = omniscient + smart switching + PP-stall prevention; `Ace Pokemon` keeps the last Pokémon for
last, so the ace must be the last entry. Double-battle AI is added by the engine.

## Presentation

`Name`, `Class`, `Pic`, `Gender`, `Music`, `Double Battle` stay as they are (scripts and intros depend on them;
checked).

## Workflow

1. Batches: each covers a list of trainer ids and is written as complete `=== TRAINER_X ===` blocks
   (`batchN.party`) plus `batchN.sources.json` (`{"TRAINER_X": "emerald-rematch", ...}`).
2. `python3 tools/hack/trainers/check_party.py batchN.party --caps --proc` → 0 errors; warnings only for
   under-level aces/bosses.
3. `python3 tools/hack/trainers/splice_party.py batch*.party` replaces the blocks in `src/data/trainers.party`
   (order and every other block unchanged).
4. `python3 tools/hack/trainers/check_tiers.py` → 0 errors: every rematch tier's ace is higher than the last
   tier's, and no tier's top level drops (families dropped between tiers are warnings).
5. `python3 tools/hack/trainers/report.py` rewrites the trainer table below.
6. `make`, `make check`, commit.

Tools: `scan_maps.py` (which map fights which trainer), `build_segments.py` (segments.json),
`check_party.py`, `check_tiers.py`, `splice_party.py` (`--target` to merge into another file), `report.py`,
`party.py` (the `.party` reader/writer they share).

## Trainer table
<!-- generated by tools/hack/trainers/report.py -->

### S1 (cap 15) – Draconid Pass to Roxanne

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_PETALBURG_WOODS | PetalburgWoods | grunt | 2 | 9–10 | Poochyena 10 | enhanced |
| CINDY_1 | Route104 | route | 1 | 9–9 | Zigzagoon 9 | emerald-rematch |
| WINSTON_1 | Route104 | route | 1 | 10–10 | Zigzagoon 10 | emerald-rematch |
| ROXANNE_1 | RustboroCity_Gym | leader | 4 | 12–15 | Nosepass 15 | emerald-rematch |
| JERRY_1 | Route116 | route | 2 | 10–11 | Shuppet 11 | emerald-rematch |
| KAREN_1 | Route116 | route | 2 | 10–11 | Whismur 11 | emerald-rematch |
| CALVIN_1 | Route102 | route | 3 | 5–6 | Poochyena 6 | emerald-rematch |
| BILLY | Route104 | route | 2 | 7–8 | Seedot 8 | enhanced |
| JOSH | RustboroCity_Gym | gym | 2 | 11–12 | Aron 12 | enhanced |
| TOMMY | RustboroCity_Gym | gym | 2 | 11–12 | Geodude 12 | enhanced |
| JOEY | Route116 | route | 2 | 10–11 | Machop 11 | enhanced |
| ALLEN | Route102 | route | 2 | 6–7 | Taillow 7 | enhanced |
| IVAN | Route104 | route | 3 | 9–11 | Tentacool 11 | enhanced |
| GINA_AND_MIA_1 | Route104 | route | 2 | 10–11 | Lotad 11 | enhanced |
| BRENDAN_ROUTE_104 | Route104 | route | 2 | 9–11 | Treecko 11 | story |
| MAY_ROUTE_103 | Route103 | route | 1 | 5–5 | Torchic 5 | story |
| MARC | RustboroCity_Gym | gym | 2 | 12–13 | Onix 13 | enhanced |
| TIANA | Route102 | route | 2 | 6–7 | Shroomish 7 | enhanced |
| HALEY_1 | Route104 | route | 3 | 10–11 | Shroomish 11 | emerald-rematch |
| JANICE | Route116 | route | 2 | 10–11 | Marill 11 | enhanced |
| RICK | Route102 | route | 2 | 5–6 | Wurmple 6 | enhanced |
| LYLE | PetalburgWoods | route | 3 | 8–9 | Cascoon 9 | enhanced |
| JOSE | Route116 | route | 2 | 10–11 | Beautifly 11 | enhanced |
| JAMES_1 | PetalburgWoods | route | 3 | 9–10 | Dustox 10 | emerald-rematch |
| CLARK | Route116 | route | 2 | 11–12 | Geodude 12 | enhanced |
| DAWSON | Route116 | route | 2 | 11–12 | Poochyena 12 | enhanced |
| SARAH | Route116 | route | 2 | 11–12 | Zigzagoon 12 | enhanced |
| DARIAN | Route104 | route | 2 | 7–8 | Tentacool 8 | enhanced |
| DEVAN | Route116 | route | 2 | 11–12 | Geodude 12 | enhanced |
| JOHNSON | Route116 | route | 2 | 11–12 | Shroomish 12 | enhanced |
| ASTER_PASS_DEINO | DraconidPass | route | 1 | 5–5 | Deino 5 | story |
| ASTER_PASS_DREEPY | DraconidPass | route | 1 | 5–5 | Dreepy 5 | story |
| ASTER_PASS_JANGMO_O | DraconidPass | route | 1 | 5–5 | Jangmo-o 5 | story |

### S2 (cap 20) – Rusturf Tunnel, Dewford, Brawly

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_RUSTURF_TUNNEL | RusturfTunnel | grunt | 2 | 13–14 | Carvanha 14 | enhanced |
| LOLA_1 | Route109 | route | 2 | 15–16 | Marill 16 | emerald-rematch |
| RICKY_1 | Route109 | route | 2 | 15–16 | Zigzagoon 16 | emerald-rematch |
| SIMON | Route109_SeashoreHouse | route | 2 | 15–16 | Marill 16 | enhanced |
| TAKAO | DewfordTown_Gym | gym | 2 | 16–17 | Makuhita 17 | enhanced |
| NOB_1 | Route115 | route | 2 | 16–17 | Machop 17 | emerald-rematch |
| BRAWLY_1 | DewfordTown_Gym | leader | 4 | 17–20 | Makuhita 20 | emerald-rematch |
| ELLIOT_1 | Route106 | route | 3 | 13–14 | Tentacool 14 | emerald-rematch |
| NED | Route106 | route | 2 | 12–13 | Tentacool 13 | enhanced |
| JOCELYN | DewfordTown_Gym | gym | 3 | 17–18 | Meditite 18 | enhanced |
| LAURA | DewfordTown_Gym | gym | 2 | 16–17 | Meditite 17 | enhanced |
| CYNDY_1 | Route115 | route | 2 | 16–17 | Makuhita 17 | emerald-rematch |
| HUEY | Route109 | route | 2 | 16–17 | Machop 17 | enhanced |
| EDMOND | Route109 | route | 2 | 15–16 | Wingull 16 | enhanced |
| DWAYNE | Route109_SeashoreHouse | route | 3 | 16–17 | Machop 17 | enhanced |
| HECTOR | Route115 | route | 2 | 16–17 | Zangoose 17 | enhanced |
| BRENDEN | DewfordTown_Gym | gym | 2 | 16–17 | Machop 17 | enhanced |
| LILITH | DewfordTown_Gym | gym | 2 | 17–18 | Meditite 18 | enhanced |
| CRISTIAN | DewfordTown_Gym | gym | 2 | 17–18 | Makuhita 18 | enhanced |
| MIKE_2 | RusturfTunnel | route | 3 | 14–15 | Geodude 15 | enhanced |
| JOHANNA | Route109_SeashoreHouse | route | 2 | 16–17 | Goldeen 17 | enhanced |
| HAILEY | Route109 | route | 2 | 15–16 | Marill 16 | enhanced |
| CHANDLER | Route109 | route | 2 | 15–16 | Tentacool 16 | enhanced |
| MARLENE | Route115 | route | 2 | 15–16 | Spoink 16 | enhanced |
| MAY_RUSTBORO | Route104 | route | 3 | 15–17 | Combusken 17 | story |

### S3 (cap 25) – Slateport, Route 110, Mauville, Wattson

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_MUSEUM_1 | SlateportCity_OceanicMuseum_2F | grunt | 2 | 17–18 | Carvanha 18 | enhanced |
| GRUNT_MUSEUM_2 | SlateportCity_OceanicMuseum_2F | grunt | 3 | 17–19 | Carvanha 19 | enhanced |
| DAISY | Route103 | route | 3 | 17–18 | Roselia 18 | enhanced |
| ROSE_1 | Route118 | route | 3 | 20–22 | Roselia 22 | emerald-rematch |
| KIRK | MauvilleCity_Gym | gym | 3 | 21–22 | Electrike 22 | enhanced |
| SHAWN | MauvilleCity_Gym | gym | 3 | 22–23 | Magnemite 23 | enhanced |
| DALTON_1 | Route118 | route | 2 | 21–22 | Loudred 22 | emerald-rematch |
| DEREK | Route117 | route | 3 | 20–21 | Beautifly 21 | enhanced |
| EDWARD | Route110 | route | 2 | 19–20 | Kadabra 20 | enhanced |
| JACLYN | Route110 | route | 3 | 20–21 | Kadabra 21 | enhanced |
| WATTSON_1 | MauvilleCity_Gym | leader | 5 | 22–25 | Manectric 25 | emerald-rematch |
| ANNA_AND_MEG_1 | Route117 | route | 2 | 18–19 | Makuhita 19 | emerald-rematch |
| MIGUEL_1 | Route103 | route | 2 | 18–19 | Skitty 19 | emerald-rematch |
| ISABEL_1 | Route110 | route | 2 | 17–18 | Minun 18 | emerald-rematch |
| BEN | MauvilleCity_Gym | gym | 3 | 21–22 | Linoone 22 | enhanced |
| EDDIE | Route110_TrickHousePuzzle1 | route | 2 | 21–22 | Linoone 22 | enhanced |
| TIMMY | Route110 | route | 3 | 17–18 | Aron 18 | enhanced |
| ANDREW | Route103 | route | 3 | 18–20 | Gyarados 20 | enhanced |
| DALE | Route110 | route | 4 | 19–21 | Wailmer 21 | enhanced |
| WADE | Route118 | route | 2 | 20–21 | Carvanha 21 | enhanced |
| JACOB | Route110 | route | 3 | 20–21 | Magnemite 21 | enhanced |
| ANTHONY | Route110 | route | 2 | 21–22 | Magnemite 22 | enhanced |
| BENJAMIN_1 | Route110 | route | 2 | 20–21 | Magnemite 21 | emerald-rematch |
| ABIGAIL_1 | Route110 | route | 2 | 21–22 | Magnemite 22 | emerald-rematch |
| JASMINE | Route110 | route | 3 | 20–21 | Magnemite 21 | enhanced |
| DYLAN_1 | Route117 | route | 2 | 18–19 | Doduo 19 | emerald-rematch |
| MARIA_1 | Route117 | route | 2 | 19–20 | Doduo 20 | emerald-rematch |
| AMY_AND_LIV_1 | Route103 | route | 2 | 18–19 | Minun 19 | emerald-rematch |
| EDWIN_1 | Route110 | route | 2 | 19–20 | Nuzleaf 20 | emerald-rematch |
| BRENDAN_ROUTE_110 | Route110 | route | 4 | 20–23 | Grovyle 23 | story |
| MAY_SLATEPORT | SlateportCity | route | 4 | 20–22 | Combusken 22 | story |
| ISAAC_1 | Route117 | route | 4 | 19–20 | Loudred 20 | emerald-rematch |
| LYDIA_1 | Route117 | route | 4 | 20–22 | Roselia 22 | emerald-rematch |
| SALLY | Route110_TrickHousePuzzle1 | route | 2 | 20–21 | Gloom 21 | enhanced |
| ROBIN | Route110_TrickHousePuzzle1 | route | 3 | 20–21 | Azumarill 21 | enhanced |
| VIVIAN | MauvilleCity_Gym | gym | 3 | 21–22 | Meditite 22 | enhanced |
| WALLY_MAUVILLE | MauvilleCity | route | 1 | 19–19 | Ralts 19 | story |
| KALEB | Route110 | route | 2 | 17–18 | Plusle 18 | enhanced |
| JOSEPH | Route110 | route | 3 | 19–20 | Electrike 20 | enhanced |
| ALYSSA | Route110 | route | 2 | 21–22 | Magnemite 22 | enhanced |
| MARCOS | Route103 | route | 2 | 17–18 | Voltorb 18 | enhanced |
| RHETT | Route103 | route | 2 | 17–18 | Makuhita 18 | enhanced |
| DEANDRE | Route118 | route | 3 | 20–21 | Linoone 21 | enhanced |
| PETE | Route103 | route | 2 | 19–20 | Tentacool 20 | enhanced |
| ISABELLE | Route103 | route | 2 | 19–20 | Azumarill 20 | enhanced |
| MELINA | Route117 | route | 2 | 20–21 | Doduo 21 | enhanced |
| BRANDI | Route117 | route | 2 | 20–21 | Kirlia 21 | enhanced |
| AISHA | Route117 | route | 2 | 19–20 | Meditite 20 | enhanced |
| ANGELO | MauvilleCity_Gym | gym | 3 | 21–22 | Volbeat 22 | enhanced |

### S4 (cap 30) – Routes 111-114, Mt. Chimney, Jagged Pass, Flannery

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| SAWYER_1 | MtChimney | route | 3 | 25–26 | Graveler 26 | emerald-rematch |
| GABBY_AND_TY_1 |  | route | 4 | 22–23 | Loudred 23 | enhanced |
| GABBY_AND_TY_2 |  | route | 4 | 26–27 | Loudred 27 | enhanced |
| WILTON_1 | Route111 | route | 3 | 23–24 | Hariyama 24 | emerald-rematch |
| BROOKE_1 | Route111 | route | 3 | 23–24 | Roselia 24 | emerald-rematch |
| MELISSA | MtChimney | route | 3 | 25–26 | Azumarill 26 | enhanced |
| SHEILA | MtChimney | route | 3 | 25–26 | Breloom 26 | enhanced |
| SHIRLEY | MtChimney | route | 3 | 25–26 | Ponyta 26 | enhanced |
| STEVE_1 | Route114 | route | 3 | 24–25 | Rhyhorn 25 | emerald-rematch |
| GRUNT_MT_CHIMNEY_1 | MtChimney | grunt | 3 | 25–26 | Mightyena 26 | enhanced |
| DAISUKE | Route111 | route | 3 | 22–23 | Machop 23 | enhanced |
| COLE | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Numel 27 | enhanced |
| JEFF | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Slugma 27 | enhanced |
| AXLE | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Numel 27 | enhanced |
| JACE | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Slugma 27 | enhanced |
| KEEGAN | LavaridgeTown_Gym_1F | gym | 3 | 27–28 | Slugma 28 | enhanced |
| BERNIE_1 | Route114 | route | 3 | 24–25 | Pelipper 25 | emerald-rematch |
| LARRY | Route112 | route | 3 | 22–23 | Nuzleaf 23 | enhanced |
| SHANE | Route114 | route | 3 | 24–25 | Nuzleaf 25 | enhanced |
| ETHAN_1 | JaggedPass | route | 3 | 26–27 | Linoone 27 | emerald-rematch |
| AUTUMN | JaggedPass | route | 3 | 26–27 | Breloom 27 | enhanced |
| TRAVIS | Route111 | route | 3 | 21–22 | Sandslash 22 | enhanced |
| FLANNERY_1 | LavaridgeTown_Gym_1F | leader | 5 | 27–30 | Torkoal 30 | emerald-rematch |
| TED | Route110_TrickHousePuzzle2 | route | 3 | 22–23 | Kirlia 23 | enhanced |
| PAUL | Route110_TrickHousePuzzle2 | route | 3 | 22–23 | Gloom 23 | enhanced |
| GEORGIA | Route110_TrickHousePuzzle2 | route | 3 | 22–23 | Breloom 23 | enhanced |
| VICTOR | Route111 | route | 3 | 21–22 | Swellow 22 | enhanced |
| VICTORIA | Route111 | route | 3 | 22–23 | Roselia 23 | enhanced |
| VICKY | Route111 | route | 3 | 23–24 | Meditite 24 | enhanced |
| SHELBY_1 | MtChimney | route | 3 | 25–26 | Hariyama 26 | emerald-rematch |
| JAYLEN | Route113 | route | 3 | 23–24 | Trapinch 24 | enhanced |
| DILLON | Route113 | route | 3 | 23–24 | Aron 24 | enhanced |
| CLAUDE | Route114 | route | 3 | 24–25 | Gyarados 25 | enhanced |
| NOLAN | Route114 | route | 3 | 24–25 | Barboach 25 | enhanced |
| LAO_1 | Route113 | route | 3 | 23–24 | Koffing 24 | emerald-rematch |
| LUNG | Route113 | route | 3 | 23–24 | Ninjask 24 | enhanced |
| MADELINE_1 | Route113 | route | 3 | 23–24 | Numel 24 | emerald-rematch |
| CAROL | Route112 | route | 3 | 22–23 | Lombre 23 | enhanced |
| NANCY | Route114 | route | 3 | 24–25 | Lombre 25 | enhanced |
| DIANA_1 | JaggedPass | route | 3 | 26–27 | Breloom 27 | emerald-rematch |
| IRENE | Route111 | route | 3 | 21–22 | Azumarill 22 | enhanced |
| ELI | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Graveler 27 | enhanced |
| ASTER_METEOR_FALLS_DEINO |  | route | 4 | 24–27 | Jangmo-o 27 | story |
| ASTER_METEOR_FALLS_DREEPY |  | route | 4 | 24–27 | Deino 27 | story |
| ASTER_METEOR_FALLS_JANGMO_O |  | route | 4 | 24–27 | Dreepy 27 | story |
| JULIO | JaggedPass | route | 3 | 26–27 | Manectric 27 | enhanced |
| GRUNT_JAGGED_PASS | JaggedPass | grunt | 3 | 26–27 | Mightyena 27 | enhanced |
| GRUNT_MT_CHIMNEY_2 | MtChimney | grunt | 3 | 25–26 | Golbat 26 | enhanced |
| TABITHA_MT_CHIMNEY | MtChimney | admin | 5 | 26–28 | Numel 28 | enhanced |
| MAXIE_MT_CHIMNEY | MtChimney | boss | 5 | 28–30 | Camerupt 30 | enhanced |
| VIVI | Route111 | route | 3 | 22–23 | Azumarill 23 | enhanced |
| BRICE | Route112 | route | 3 | 22–23 | Machop 23 | enhanced |
| TRENT_1 | Route112 | route | 3 | 22–23 | Geodude 23 | emerald-rematch |
| LENNY | Route114 | route | 3 | 24–25 | Graveler 25 | enhanced |
| LUCAS_1 | Route114 | route | 3 | 24–25 | Graveler 25 | enhanced |
| ERIC | JaggedPass | route | 3 | 26–27 | Graveler 27 | enhanced |
| GERALD | LavaridgeTown_Gym_1F | gym | 3 | 27–28 | Kecleon 28 | enhanced |
| DANIELLE | LavaridgeTown_Gym_1F | gym | 3 | 26–28 | Meditite 28 | enhanced |
| TORI_AND_TIA | Route113 | route | 4 | 23–24 | Minun 24 | enhanced |
| TYRA_AND_IVY | Route114 | route | 4 | 24–25 | Graveler 25 | enhanced |
| TYRON | Route111 | route | 3 | 21–22 | Sandslash 22 | enhanced |
| CELINA | Route111 | route | 3 | 21–22 | Roselia 22 | enhanced |
| BIANCA | Route111 | route | 3 | 21–22 | Shroomish 22 | enhanced |
| HAYDEN | Route111 | route | 3 | 21–22 | Numel 22 | enhanced |
| SOPHIE | Route113 | route | 3 | 23–24 | Lombre 24 | enhanced |
| COBY | Route113 | route | 3 | 23–24 | Swellow 24 | enhanced |
| LAWRENCE | Route113 | route | 3 | 23–24 | Sandslash 24 | enhanced |
| WYATT | Route113 | route | 3 | 23–24 | Aron 24 | enhanced |
| ANGELINA | Route114 | route | 3 | 24–25 | Azumarill 25 | enhanced |
| KAI | Route114 | route | 3 | 24–25 | Barboach 25 | enhanced |
| CHARLOTTE | Route114 | route | 3 | 24–25 | Nuzleaf 25 | enhanced |
| BRYANT | Route112 | route | 3 | 22–23 | Slugma 23 | enhanced |
| SHAYLA | Route112 | route | 3 | 22–23 | Roselia 23 | enhanced |

### S5 (cap 34) – Desert, Norman

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| DUSTY_1 | Route111 | route | 3 | 28–30 | Sandslash 30 | emerald-rematch |
| GABBY_AND_TY_3 |  | route | 4 | 29–31 | Loudred 31 | enhanced |
| RANDALL | PetalburgCity_Gym | gym | 4 | 30–31 | Swellow 31 | enhanced |
| PARKER | PetalburgCity_Gym | gym | 4 | 30–31 | Spinda 31 | enhanced |
| GEORGE | PetalburgCity_Gym | gym | 4 | 31–32 | Vigoroth 32 | enhanced |
| BERKE | PetalburgCity_Gym | gym | 4 | 31–32 | Vigoroth 32 | enhanced |
| MARY | PetalburgCity_Gym | gym | 4 | 30–31 | Delcatty 31 | enhanced |
| ALEXIA | PetalburgCity_Gym | gym | 4 | 31–32 | Wigglytuff 32 | enhanced |
| JODY | PetalburgCity_Gym | gym | 4 | 31–32 | Zangoose 32 | enhanced |
| DREW | Route111 | route | 3 | 28–29 | Sandslash 29 | enhanced |
| BEAU | Route111 | route | 3 | 27–28 | Baltoy 28 | enhanced |
| JUSTIN | Route110_TrickHousePuzzle3 | route | 3 | 29–30 | Kecleon 30 | enhanced |
| NORMAN_1 | PetalburgCity_Gym | leader | 6 | 31–34 | Slaking 34 | emerald-rematch |
| HEIDI | Route111 | route | 3 | 28–29 | Baltoy 29 | enhanced |
| BECKY | Route111 | route | 3 | 28–29 | Azumarill 29 | enhanced |
| MARTHA | Route110_TrickHousePuzzle3 | route | 3 | 29–30 | Delcatty 30 | enhanced |
| ALAN | Route110_TrickHousePuzzle3 | route | 3 | 29–30 | Graveler 30 | enhanced |
| CELIA | Route111 | route | 3 | 28–29 | Lombre 29 | enhanced |
| BRYAN | Route111 | route | 3 | 28–29 | Sandslash 29 | enhanced |
| BRANDEN | Route111 | route | 3 | 28–29 | Nuzleaf 29 | enhanced |
| WALLY_PETALBURG | PetalburgCity | route | 4 | 30–33 | Kirlia 33 | story |

### S6 (cap 38) – Surf routes, Abandoned Ship, Route 119, Weather Institute, Winona

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_WEATHER_INST_1 | Route119_WeatherInstitute_1F | grunt | 4 | 32–33 | Golbat 33 | enhanced |
| GRUNT_WEATHER_INST_2 | Route119_WeatherInstitute_2F | grunt | 4 | 33–34 | Sharpedo 34 | enhanced |
| GRUNT_WEATHER_INST_3 | Route119_WeatherInstitute_2F | grunt | 5 | 33–34 | Sharpedo 34 | enhanced |
| GRUNT_WEATHER_INST_4 | Route119_WeatherInstitute_1F | grunt | 4 | 32–33 | Sharpedo 33 | enhanced |
| SHELLY_WEATHER_INSTITUTE | Route119_WeatherInstitute_2F | admin | 5 | 34–36 | Sharpedo 36 | enhanced |
| ROSE_2 | Route118 | route t2 | 4 | 32–34 | Roselia 34 | emerald-rematch |
| FOSTER | Route105 | route | 4 | 30–31 | Sandslash 31 | enhanced |
| DUSTY_2 | Route111 | route t2 | 4 | 33–35 | Sandslash 35 | emerald-rematch |
| GABBY_AND_TY_4 |  | route | 4 | 32–34 | Magneton 34 | enhanced |
| AUSTINA | Route109 | route | 4 | 31–32 | Azumarill 32 | enhanced |
| GWEN | Route109 | route | 4 | 31–32 | Azumarill 32 | enhanced |
| LOLA_2 | Route109 | route t2 | 4 | 32–34 | Azumarill 34 | emerald-rematch |
| CHARLIE | AbandonedShip_Corridors_1F | route | 4 | 32–33 | Azumarill 33 | enhanced |
| RICKY_2 | Route109 | route t2 | 4 | 32–34 | Linoone 34 | emerald-rematch |
| WILTON_2 | Route111 | route t2 | 4 | 33–35 | Hariyama 35 | emerald-rematch |
| BROOKE_2 | Route111 | route t2 | 4 | 33–35 | Roselia 35 | emerald-rematch |
| CINDY_3 | Route104 | route t2 | 4 | 32–34 | Linoone 34 | emerald-rematch |
| WINSTON_2 | Route104 | route t2 | 4 | 32–34 | Linoone 34 | emerald-rematch |
| THALIA_1 | AbandonedShip_Rooms_1F | route | 4 | 33–34 | Seadra 34 | emerald-rematch |
| STEVE_2 | Route114 | route t2 | 4 | 33–35 | Lairon 35 | emerald-rematch |
| LUIS | Route105 | route | 4 | 30–31 | Sharpedo 31 | enhanced |
| DOMINIK | Route105 | route | 4 | 30–31 | Tentacruel 31 | enhanced |
| DOUGLAS | Route106 | route | 4 | 30–31 | Tentacruel 31 | enhanced |
| DARRIN | Route107 | route | 4 | 31–32 | Tentacruel 32 | enhanced |
| TONY_1 | Route107 | route | 4 | 31–32 | Sharpedo 32 | emerald-rematch |
| JEROME | Route108 | route | 4 | 32–33 | Tentacruel 33 | enhanced |
| MATTHEW | Route108 | route | 4 | 32–33 | Sharpedo 33 | enhanced |
| DAVID | Route109 | route | 4 | 32–33 | Sharpedo 33 | enhanced |
| TONY_2 | Route107 | route t2 | 4 | 33–35 | Sharpedo 35 | emerald-rematch |
| KOICHI | Route115 | route | 4 | 31–32 | Machoke 32 | enhanced |
| NOB_2 | Route115 | route t2 | 4 | 32–34 | Machamp 34 | emerald-rematch |
| YUJI | Route110_TrickHousePuzzle4 | route | 4 | 33–34 | Machoke 34 | enhanced |
| DALTON_2 | Route118 | route t2 | 4 | 32–35 | Loudred 35 | emerald-rematch |
| BERNIE_2 | Route114 | route t2 | 4 | 33–35 | Camerupt 35 | emerald-rematch |
| ETHAN_2 | JaggedPass | route t2 | 4 | 33–35 | Linoone 35 | emerald-rematch |
| BRENT | Route119 | route | 4 | 31–32 | Masquerain 32 | enhanced |
| DONALD | Route119 | route | 4 | 31–32 | Beautifly 32 | enhanced |
| TAYLOR | Route119 | route | 4 | 32–33 | Dustox 33 | enhanced |
| WINONA_1 | FortreeCity_Gym | leader | 6 | 35–38 | Altaria 38 | emerald-rematch |
| JERRY_2 | Route116 | route t2 | 4 | 32–34 | Gardevoir 34 | emerald-rematch |
| KAREN_2 | Route116 | route t2 | 4 | 32–34 | Loudred 34 | emerald-rematch |
| ANNA_AND_MEG_2 | Route117 | route t2 | 4 | 32–34 | Hariyama 34 | emerald-rematch |
| MIGUEL_2 | Route103 | route t2 | 4 | 32–34 | Delcatty 34 | emerald-rematch |
| ISABEL_2 | Route110 | route t2 | 4 | 32–34 | Minun 34 | emerald-rematch |
| TIMOTHY_1 | Route115 | route | 4 | 32–33 | Hariyama 33 | emerald-rematch |
| TIMOTHY_2 | Route115 | route t2 | 4 | 33–35 | Hariyama 35 | emerald-rematch |
| SHELBY_2 | MtChimney | route t2 | 4 | 33–35 | Hariyama 35 | emerald-rematch |
| CALVIN_2 | Route102 | route t2 | 4 | 32–34 | Mightyena 34 | emerald-rematch |
| BARNY | Route118 | route | 4 | 30–31 | Sharpedo 31 | enhanced |
| CARTER | Route109 | route | 4 | 32–33 | Tentacruel 33 | enhanced |
| ELLIOT_2 | Route106 | route t2 | 4 | 32–34 | Tentacruel 34 | emerald-rematch |
| BENJAMIN_2 | Route110 | route t2 | 4 | 32–34 | Magneton 34 | emerald-rematch |
| ABIGAIL_2 | Route110 | route t2 | 4 | 32–34 | Magneton 34 | emerald-rematch |
| DYLAN_2 | Route117 | route t2 | 4 | 32–34 | Dodrio 34 | emerald-rematch |
| MARIA_2 | Route117 | route t2 | 4 | 32–34 | Dodrio 34 | emerald-rematch |
| DEMETRIUS | AbandonedShip_Rooms_1F | route | 4 | 32–33 | Manectric 33 | enhanced |
| PERRY | Route118 | route | 4 | 30–31 | Pelipper 31 | enhanced |
| HUGH | Route119 | route | 4 | 32–33 | Tropius 33 | enhanced |
| PHIL | Route119 | route | 4 | 32–33 | Swellow 33 | enhanced |
| JARED | FortreeCity_Gym | gym | 4 | 34–35 | Tropius 35 | enhanced |
| HUMBERTO | FortreeCity_Gym | gym | 4 | 35–36 | Skarmory 36 | enhanced |
| EDWARDO | FortreeCity_Gym | gym | 4 | 34–35 | Pelipper 35 | enhanced |
| CHESTER | Route118 | route | 4 | 31–32 | Swellow 32 | enhanced |
| YASU | Route119 | route | 4 | 32–33 | Ninjask 33 | enhanced |
| TAKASHI | Route119 | route | 4 | 32–33 | Ninjask 33 | enhanced |
| JANI | AbandonedShip_Rooms2_1F | route | 4 | 32–33 | Azumarill 33 | enhanced |
| LAO_2 | Route113 | route t2 | 4 | 33–35 | Weezing 35 | emerald-rematch |
| CORA | Route110_TrickHousePuzzle4 | route | 4 | 33–34 | Meditite 34 | enhanced |
| PAULA | Route110_TrickHousePuzzle4 | route | 4 | 33–34 | Breloom 34 | enhanced |
| CYNDY_2 | Route115 | route t2 | 4 | 32–34 | Hariyama 34 | emerald-rematch |
| MADELINE_2 | Route113 | route t2 | 4 | 33–35 | Camerupt 35 | emerald-rematch |
| BEVERLY | Route105 | route | 4 | 30–31 | Wailmer 31 | enhanced |
| IMANI | Route105 | route | 4 | 30–31 | Azumarill 31 | enhanced |
| KYLA | Route106 | route | 4 | 30–31 | Wailmer 31 | enhanced |
| DENISE | Route107 | route | 4 | 31–32 | Pelipper 32 | enhanced |
| BETH | Route107 | route | 4 | 31–33 | Seaking 33 | enhanced |
| TARA | Route108 | route | 4 | 32–33 | Seadra 33 | enhanced |
| MISSY | Route108 | route | 4 | 32–33 | Seaking 33 | enhanced |
| ALICE | Route109 | route | 4 | 32–34 | Seaking 34 | enhanced |
| DIANA_2 | JaggedPass | route t2 | 4 | 33–35 | Altaria 35 | emerald-rematch |
| AMY_AND_LIV_2 | Route103 | route t2 | 4 | 32–34 | Minun 34 | emerald-rematch |
| DUNCAN | AbandonedShip_Corridors_B1F | route | 4 | 33–34 | Machoke 34 | enhanced |
| EDWIN_2 | Route110 | route t2 | 4 | 33–34 | Shiftry 34 | emerald-rematch |
| BRENDAN_ROUTE_119 | Route119 | route | 5 | 34–37 | Sceptile 37 | story |
| ASTER_ROUTE_119_DEINO |  | route | 5 | 34–37 | Altaria 37 | story |
| ASTER_ROUTE_119_DREEPY |  | route | 5 | 34–37 | Altaria 37 | story |
| ASTER_ROUTE_119_JANGMO_O |  | route | 5 | 34–37 | Altaria 37 | story |
| ISAAC_2 | Route117 | route t2 | 4 | 33–34 | Hariyama 34 | emerald-rematch |
| GARRISON | AbandonedShip_Rooms2_1F | route | 4 | 32–34 | Sandslash 34 | enhanced |
| LYDIA_2 | Route117 | route t2 | 4 | 33–34 | Azumarill 34 | emerald-rematch |
| JACKSON_1 | Route119 | route | 4 | 32–33 | Breloom 33 | emerald-rematch |
| JACKSON_2 | Route119 | route t2 | 4 | 34–35 | Breloom 35 | emerald-rematch |
| CATHERINE_1 | Route119 | route | 4 | 32–33 | Roselia 33 | emerald-rematch |
| CATHERINE_2 | Route119 | route t2 | 4 | 34–35 | Roselia 35 | emerald-rematch |
| GRUNT_WEATHER_INST_5 | Route119_WeatherInstitute_2F | grunt | 4 | 33–34 | Golbat 34 | enhanced |
| HALEY_2 | Route104 | route t2 | 4 | 32–34 | Breloom 34 | emerald-rematch |
| DOUG | Route119 | route | 4 | 31–32 | Ninjask 32 | enhanced |
| GREG | Route119 | route | 4 | 31–32 | Illumise 32 | enhanced |
| KENT | Route119 | route | 4 | 31–32 | Ninjask 32 | enhanced |
| JAMES_2 | PetalburgWoods | route t2 | 4 | 32–34 | Ninjask 34 | emerald-rematch |
| TRENT_2 | Route112 | route t2 | 4 | 33–35 | Golem 35 | emerald-rematch |
| KIRA_AND_DAN_1 | AbandonedShip_Rooms2_1F | route | 4 | 33–34 | Illumise 34 | emerald-rematch |
| KIRA_AND_DAN_2 | AbandonedShip_Rooms2_1F | route t2 | 4 | 34–35 | Illumise 35 | emerald-rematch |
| HIDEO | Route119 | route | 4 | 33–35 | Weezing 35 | enhanced |
| FLINT | FortreeCity_Gym | gym | 4 | 35–36 | Xatu 36 | enhanced |
| ASHLEY | FortreeCity_Gym | gym | 4 | 35–36 | Altaria 36 | enhanced |
| MEL_AND_PAUL | Route109 | route | 4 | 32–33 | Beautifly 33 | enhanced |
| LISA_AND_RAY | Route107 | route | 4 | 31–33 | Seaking 33 | enhanced |
| CHRIS | Route119 | route | 4 | 32–34 | Gyarados 34 | enhanced |
| ANDRES_1 | Route105 | route | 4 | 30–31 | Sandslash 31 | emerald-rematch |
| JOSUE | Route105 | route | 4 | 30–31 | Swellow 31 | enhanced |
| CAMRON | Route107 | route | 4 | 31–32 | Starmie 32 | enhanced |
| CORY_1 | Route108 | route | 4 | 32–33 | Tentacruel 33 | emerald-rematch |
| CAROLINA | Route108 | route | 5 | 33–34 | Manectric 34 | enhanced |
| ELIJAH | Route109 | route | 4 | 32–33 | Skarmory 33 | enhanced |
| KYRA | Route115 | route | 4 | 31–32 | Dodrio 32 | enhanced |
| JAIDEN | Route115 | route | 4 | 31–32 | Swalot 32 | enhanced |
| ALIX | Route115 | route | 4 | 31–33 | Gardevoir 33 | enhanced |
| HELENE | Route115 | route | 4 | 31–32 | Hariyama 32 | enhanced |
| FABIAN | Route119 | route | 4 | 32–33 | Manectric 33 | enhanced |
| DAYTON | Route119 | route | 4 | 32–33 | Camerupt 33 | enhanced |
| RACHEL | Route119 | route | 4 | 32–33 | Seaking 33 | enhanced |
| DARIUS | FortreeCity_Gym | gym | 5 | 35–36 | Tropius 36 | enhanced |
| ANDRES_2 | Route105 | route t2 | 4 | 33–35 | Sandslash 35 | emerald-rematch |
| CORY_2 | Route108 | route t2 | 4 | 33–35 | Tentacruel 35 | emerald-rematch |
| SAWYER_2 | MtChimney | route t2 | 4 | 33–35 | Golem 35 | emerald-rematch |
| THALIA_2 | AbandonedShip_Rooms_1F | route t2 | 4 | 34–35 | Seadra 35 | emerald-rematch |

### S7 (cap 44) – Routes 120-134, Mt. Pyre, Lilycove, both hideouts, Tate & Liza

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_AQUA_HIDEOUT_1 | AquaHideout_1F | grunt | 4 | 39–40 | Mightyena 40 | enhanced |
| GRUNT_AQUA_HIDEOUT_2 | AquaHideout_B1F | grunt | 4 | 40–41 | Sharpedo 41 | enhanced |
| GRUNT_AQUA_HIDEOUT_3 | AquaHideout_B1F | grunt | 4 | 40–41 | Crobat 41 | enhanced |
| GRUNT_AQUA_HIDEOUT_4 | AquaHideout_B2F | grunt | 4 | 40–41 | Sharpedo 41 | enhanced |
| GABRIELLE_1 | MtPyre_3F | route | 4 | 37–38 | Mightyena 38 | emerald-rematch |
| MARCEL | Route121 | route | 4 | 37–38 | Manectric 38 | enhanced |
| ALBERTO | Route123 | route | 4 | 37–38 | Xatu 38 | enhanced |
| ED | Route123 | route | 4 | 37–39 | Zangoose 39 | enhanced |
| DECLAN | Route124 | route | 4 | 35–37 | Gyarados 37 | enhanced |
| GRUNT_MT_PYRE_1 | MtPyre_Summit | grunt | 4 | 37–38 | Golbat 38 | enhanced |
| GRUNT_MT_PYRE_2 | MtPyre_Summit | grunt | 4 | 37–38 | Sharpedo 38 | enhanced |
| GRUNT_MT_PYRE_3 | MtPyre_Summit | grunt | 4 | 37–38 | Mightyena 38 | enhanced |
| GRUNT_AQUA_HIDEOUT_5 | AquaHideout_B1F | grunt | 4 | 40–41 | Sharpedo 41 | enhanced |
| GRUNT_AQUA_HIDEOUT_6 | AquaHideout_B2F | grunt | 4 | 40–41 | Crobat 41 | enhanced |
| FREDRICK | Route123 | route | 4 | 37–39 | Machamp 39 | enhanced |
| MATT | AquaHideout_B2F | admin | 5 | 40–42 | Sharpedo 42 | enhanced |
| ZANDER | MtPyre_2F | route | 4 | 36–37 | Hariyama 37 | enhanced |
| LEAH | MtPyre_2F | route | 4 | 36–37 | Banette 37 | enhanced |
| VIOLET | Route123 | route | 4 | 37–39 | Roserade 39 | enhanced |
| ROSE_3 | Route118 | route t3 | 5 | 37–39 | Roselia 39 | emerald-rematch |
| CHIP | Route120 | route | 4 | 35–36 | Claydol 36 | enhanced |
| DUSTY_3 | Route111 | route t3 | 4 | 38–40 | Sandslash 40 | emerald-rematch |
| GABBY_AND_TY_5 |  | route | 4 | 38–39 | Magneton 39 | emerald-rematch |
| LOLA_3 | Route109 | route t3 | 4 | 37–39 | Azumarill 39 | emerald-rematch |
| RICKY_3 | Route109 | route t3 | 4 | 38–39 | Linoone 39 | emerald-rematch |
| BRAXTON | Route123 | route | 5 | 37–39 | Shiftry 39 | enhanced |
| WILTON_3 | Route111 | route t3 | 5 | 38–40 | Hariyama 40 | emerald-rematch |
| WARREN | Route133 | route | 5 | 39–41 | Ludicolo 41 | enhanced |
| WENDY | Route123 | route | 4 | 37–39 | Altaria 39 | enhanced |
| JENNIFER | Route120 | route | 4 | 35–36 | Sableye 36 | enhanced |
| BROOKE_3 | Route111 | route t3 | 5 | 38–40 | Roselia 40 | emerald-rematch |
| KINDRA | Route123 | route | 4 | 37–39 | Dusclops 39 | enhanced |
| TAMMY | Route121 | route | 4 | 36–38 | Dusclops 38 | enhanced |
| VALERIE_1 | MtPyre_6F | route | 4 | 38–39 | Sableye 39 | emerald-rematch |
| TASHA | MtPyre_5F | route | 4 | 38–39 | Banette 39 | enhanced |
| VALERIE_2 | MtPyre_6F | route t2 | 4 | 38–40 | Grumpig 40 | emerald-rematch |
| VALERIE_3 | MtPyre_6F | route t3 | 5 | 39–41 | Grumpig 41 | emerald-rematch |
| CINDY_4 | Route104 | route t3 | 4 | 37–39 | Linoone 39 | emerald-rematch |
| JESSICA_1 | Route121 | route | 4 | 37–38 | Seviper 38 | emerald-rematch |
| JESSICA_2 | Route121 | route t2 | 4 | 37–39 | Seviper 39 | emerald-rematch |
| JESSICA_3 | Route121 | route t3 | 4 | 39–41 | Seviper 41 | emerald-rematch |
| MOLLIE | Route133 | route | 5 | 39–41 | Whiscash 41 | enhanced |
| WINSTON_3 | Route104 | route t3 | 4 | 37–39 | Linoone 39 | emerald-rematch |
| MARK | MtPyre_2F | route | 4 | 36–37 | Rhyhorn 37 | enhanced |
| STEVE_3 | Route114 | route t3 | 4 | 38–40 | Lairon 40 | emerald-rematch |
| SPENCER | Route124 | route | 4 | 36–38 | Tentacruel 38 | enhanced |
| ROLAND | Route124 | route | 4 | 36–38 | Sharpedo 38 | enhanced |
| NOLEN | Route125 | route | 4 | 36–38 | Tentacruel 38 | enhanced |
| STAN | Route125 | route | 4 | 37–39 | Seadra 39 | enhanced |
| BARRY | Route126 | route | 4 | 37–39 | Gyarados 39 | enhanced |
| DEAN | Route126 | route | 4 | 37–39 | Sharpedo 39 | enhanced |
| RODNEY | Route130 | route | 4 | 38–40 | Gyarados 40 | enhanced |
| RICHARD | Route131 | route | 4 | 38–40 | Pelipper 40 | enhanced |
| HERMAN | Route131 | route | 4 | 39–40 | Tentacruel 40 | enhanced |
| SANTIAGO | Route130 | route | 4 | 38–40 | Wailord 40 | enhanced |
| GILBERT | Route132 | route | 4 | 39–41 | Sharpedo 41 | enhanced |
| FRANKLIN | Route133 | route | 4 | 39–41 | Wailord 41 | enhanced |
| KEVIN | Route131 | route | 4 | 38–40 | Gyarados 40 | enhanced |
| JACK | Route134 | route | 4 | 40–41 | Gyarados 41 | enhanced |
| CHAD | Route124 | route | 4 | 36–38 | Tentacruel 38 | enhanced |
| TONY_3 | Route107 | route t3 | 5 | 38–40 | Sharpedo 40 | emerald-rematch |
| HITOSHI | Route134 | route | 4 | 39–41 | Machamp 41 | enhanced |
| KIYO | Route132 | route | 4 | 39–41 | Hariyama 41 | enhanced |
| NOB_3 | Route115 | route t3 | 5 | 37–39 | Machamp 39 | emerald-rematch |
| ATSUSHI | MtPyre_4F | route | 4 | 37–38 | Hariyama 38 | enhanced |
| GRUNT_AQUA_HIDEOUT_7 | AquaHideout_B1F | grunt | 4 | 40–41 | Mightyena 41 | enhanced |
| GRUNT_AQUA_HIDEOUT_8 | AquaHideout_B2F | grunt | 4 | 40–41 | Gyarados 41 | enhanced |
| FERNANDO_1 | Route123 | route | 4 | 37–38 | Loudred 38 | emerald-rematch |
| DALTON_3 | Route118 | route t3 | 5 | 37–40 | Exploud 40 | emerald-rematch |
| BERNIE_3 | Route114 | route t3 | 5 | 38–40 | Magcargo 40 | emerald-rematch |
| ETHAN_3 | JaggedPass | route t3 | 4 | 38–40 | Linoone 40 | emerald-rematch |
| JEFFREY_1 | Route120 | route | 4 | 35–36 | Masquerain 36 | emerald-rematch |
| JEFFREY_2 | Route120 | route t2 | 4 | 37–39 | Masquerain 39 | emerald-rematch |
| JEFFREY_3 | Route120 | route t3 | 5 | 39–41 | Masquerain 41 | emerald-rematch |
| PRESTON | MossdeepCity_Gym | gym | 4 | 39–41 | Gallade 41 | enhanced |
| VIRGIL | MossdeepCity_Gym | gym | 4 | 39–41 | Gardevoir 41 | enhanced |
| BLAKE | MossdeepCity_Gym | gym | 4 | 39–41 | Girafarig 41 | enhanced |
| WILLIAM | MtPyre_3F | route | 4 | 37–38 | Gardevoir 38 | enhanced |
| CAMERON_1 | Route123 | route | 4 | 37–38 | Solrock 38 | emerald-rematch |
| CAMERON_2 | Route123 | route t2 | 4 | 37–39 | Kadabra 39 | emerald-rematch |
| CAMERON_3 | Route123 | route t3 | 5 | 39–41 | Alakazam 41 | emerald-rematch |
| HANNAH | MossdeepCity_Gym | gym | 4 | 39–41 | Gardevoir 41 | enhanced |
| SAMANTHA | MossdeepCity_Gym | gym | 4 | 39–41 | Xatu 41 | enhanced |
| MAURA | MossdeepCity_Gym | gym | 4 | 39–41 | Alakazam 41 | enhanced |
| KAYLA | MtPyre_3F | route | 4 | 37–38 | Alakazam 38 | enhanced |
| JACKI_1 | Route123 | route | 4 | 37–38 | Lunatone 38 | emerald-rematch |
| JACKI_2 | Route123 | route t2 | 4 | 37–39 | Kadabra 39 | emerald-rematch |
| JACKI_3 | Route123 | route t3 | 5 | 39–41 | Alakazam 41 | emerald-rematch |
| WALTER_1 | Route121 | route | 4 | 36–37 | Manectric 37 | emerald-rematch |
| WALTER_2 | Route121 | route t2 | 4 | 37–39 | Manectric 39 | emerald-rematch |
| WALTER_3 | Route121 | route t3 | 5 | 39–41 | Manectric 41 | emerald-rematch |
| TATE_AND_LIZA_1 | MossdeepCity_Gym | leader | 6 | 42–44 | Solrock 44 | emerald-rematch |
| JERRY_3 | Route116 | route t3 | 4 | 38–39 | Gardevoir 39 | emerald-rematch |
| KAREN_3 | Route116 | route t3 | 4 | 37–40 | Exploud 40 | emerald-rematch |
| KATE_AND_JOY | Route121 | route | 4 | 36–37 | Slaking 37 | enhanced |
| ANNA_AND_MEG_3 | Route117 | route t3 | 4 | 37–39 | Hariyama 39 | emerald-rematch |
| MIGUEL_3 | Route103 | route t3 | 4 | 37–39 | Delcatty 39 | emerald-rematch |
| VANESSA | Route121 | route | 4 | 36–37 | Pikachu 37 | enhanced |
| ISABEL_3 | Route110 | route t3 | 4 | 38–39 | Minun 39 | emerald-rematch |
| TIMOTHY_3 | Route115 | route t3 | 4 | 38–40 | Hariyama 40 | emerald-rematch |
| SHELBY_3 | MtChimney | route t3 | 4 | 38–40 | Hariyama 40 | emerald-rematch |
| CALVIN_3 | Route102 | route t3 | 4 | 37–39 | Mightyena 39 | emerald-rematch |
| ELLIOT_3 | Route106 | route t3 | 5 | 37–39 | Tentacruel 39 | emerald-rematch |
| RONALD | Route132 | route | 5 | 39–41 | Gyarados 41 | enhanced |
| BENJAMIN_3 | Route110 | route t3 | 4 | 37–39 | Magneton 39 | emerald-rematch |
| ABIGAIL_3 | Route110 | route t3 | 4 | 37–39 | Magneton 39 | emerald-rematch |
| DYLAN_3 | Route117 | route t3 | 4 | 37–39 | Dodrio 39 | emerald-rematch |
| MARIA_3 | Route117 | route t3 | 4 | 37–39 | Dodrio 39 | emerald-rematch |
| CAMDEN | Route127 | route | 4 | 37–39 | Starmie 39 | enhanced |
| ISAIAH_1 | Route128 | route | 4 | 38–40 | Starmie 40 | emerald-rematch |
| PABLO_1 | Route126 | route | 4 | 37–39 | Starmie 39 | emerald-rematch |
| CHASE | Route129 | route | 4 | 38–40 | Starmie 40 | enhanced |
| ISAIAH_2 | Route128 | route t2 | 4 | 39–41 | Starmie 41 | emerald-rematch |
| ISAIAH_3 | Route128 | route t3 | 5 | 40–42 | Starmie 42 | emerald-rematch |
| ISOBEL | Route126 | route | 4 | 37–39 | Starmie 39 | enhanced |
| DONNY | Route127 | route | 4 | 38–40 | Starmie 40 | enhanced |
| TALIA | Route131 | route | 4 | 38–40 | Starmie 40 | enhanced |
| KATELYN_1 | Route128 | route | 4 | 38–40 | Starmie 40 | emerald-rematch |
| ALLISON | Route129 | route | 4 | 38–40 | Starmie 40 | enhanced |
| KATELYN_2 | Route128 | route t2 | 4 | 39–41 | Starmie 41 | emerald-rematch |
| KATELYN_3 | Route128 | route t3 | 5 | 40–42 | Starmie 42 | emerald-rematch |
| AARON | Route134 | route | 4 | 39–41 | Shelgon 41 | enhanced |
| PRESLEY | Route125 | route | 4 | 37–39 | Xatu 39 | enhanced |
| COLIN | Route120 | route | 4 | 35–36 | Pelipper 36 | enhanced |
| ROBERT_1 | Route120 | route | 4 | 35–36 | Altaria 36 | emerald-rematch |
| ROBERT_2 | Route120 | route t2 | 4 | 37–39 | Xatu 39 | emerald-rematch |
| ROBERT_3 | Route120 | route t3 | 5 | 39–41 | Xatu 41 | emerald-rematch |
| ALEX | Route134 | route | 4 | 40–41 | Swellow 41 | enhanced |
| BECK | Route133 | route | 4 | 39–41 | Tropius 41 | enhanced |
| LAO_3 | Route113 | route t3 | 5 | 37–40 | Weezing 40 | emerald-rematch |
| CYNDY_3 | Route115 | route t3 | 4 | 38–39 | Hariyama 39 | emerald-rematch |
| CLARISSA | Route120 | route | 4 | 35–36 | Ludicolo 36 | enhanced |
| ANGELICA | Route120 | route | 4 | 35–36 | Castform 36 | enhanced |
| MADELINE_3 | Route113 | route t3 | 5 | 38–40 | Camerupt 40 | emerald-rematch |
| JENNY_1 | Route124 | route | 4 | 36–38 | Starmie 38 | emerald-rematch |
| GRACE | Route124 | route | 4 | 35–37 | Azumarill 37 | enhanced |
| TANYA | Route125 | route | 4 | 37–39 | Lanturn 39 | enhanced |
| SHARON | Route125 | route | 4 | 36–38 | Seaking 38 | enhanced |
| NIKKI | Route126 | route | 4 | 37–39 | Azumarill 39 | enhanced |
| BRENDA | Route126 | route | 4 | 37–39 | Seaking 39 | enhanced |
| KATIE | Route130 | route | 4 | 38–40 | Seaking 40 | enhanced |
| SUSIE | Route131 | route | 4 | 39–40 | Gorebyss 40 | enhanced |
| KARA | Route131 | route | 4 | 39–40 | Seaking 40 | enhanced |
| DANA | Route132 | route | 4 | 39–41 | Azumarill 41 | enhanced |
| SIENNA | Route126 | route | 4 | 37–39 | Milotic 39 | enhanced |
| DEBRA | Route133 | route | 4 | 39–41 | Seaking 41 | enhanced |
| LINDA | Route133 | route | 4 | 39–41 | Seadra 41 | enhanced |
| LAUREL | Route134 | route | 4 | 39–41 | Lanturn 41 | enhanced |
| CARLEE | Route128 | route | 4 | 38–40 | Seaking 40 | enhanced |
| JENNY_2 | Route124 | route t2 | 4 | 37–39 | Starmie 39 | emerald-rematch |
| JENNY_3 | Route124 | route t3 | 5 | 39–41 | Starmie 41 | emerald-rematch |
| CEDRIC | MtPyre_6F | route | 4 | 38–39 | Wobbuffet 39 | enhanced |
| DIANA_3 | JaggedPass | route t3 | 4 | 38–40 | Altaria 40 | emerald-rematch |
| MIU_AND_YUKI | Route123 | route | 4 | 37–38 | Illumise 38 | enhanced |
| AMY_AND_LIV_4 | Route103 | route t3 | 4 | 37–39 | Minun 39 | emerald-rematch |
| ERNEST_1 | Route125 | route | 4 | 36–38 | Machamp 38 | emerald-rematch |
| ERNEST_2 | Route125 | route t2 | 4 | 38–39 | Tentacruel 39 | emerald-rematch |
| ERNEST_3 | Route125 | route t3 | 5 | 39–41 | Tentacruel 41 | emerald-rematch |
| JAZMYN | Route123 | route | 4 | 37–38 | Absol 38 | enhanced |
| JONAS | Route123 | route | 4 | 37–38 | Weezing 38 | enhanced |
| KAYLEY | Route123 | route | 4 | 37–38 | Castform 38 | enhanced |
| AURON | Route125 | route | 5 | 37–39 | Machamp 39 | enhanced |
| KELVIN | Route134 | route | 4 | 40–41 | Machamp 41 | enhanced |
| MARLEY | Route134 | route | 5 | 39–41 | Manectric 41 | enhanced |
| REYNA | Route134 | route | 4 | 39–41 | Hariyama 41 | enhanced |
| HUDSON | Route134 | route | 4 | 39–41 | Wailord 41 | enhanced |
| CONOR | Route133 | route | 5 | 39–41 | Hariyama 41 | enhanced |
| EDWIN_3 | Route110 | route t3 | 5 | 37–39 | Shiftry 39 | emerald-rematch |
| DAVIS | Route123 | route | 4 | 37–38 | Pinsir 38 | enhanced |
| ISAAC_3 | Route117 | route t3 | 5 | 38–39 | Hariyama 39 | emerald-rematch |
| LYDIA_3 | Route117 | route t3 | 5 | 38–39 | Azumarill 39 | emerald-rematch |
| LORENZO | Route120 | route | 4 | 35–36 | Shiftry 36 | enhanced |
| JACKSON_3 | Route119 | route t3 | 5 | 39–40 | Breloom 40 | emerald-rematch |
| JENNA | Route120 | route | 4 | 35–36 | Ludicolo 36 | enhanced |
| CATHERINE_3 | Route119 | route t3 | 4 | 39–40 | Roselia 40 | emerald-rematch |
| GRUNT_MT_PYRE_4 | MtPyre_Summit | grunt | 4 | 37–38 | Wailmer 38 | enhanced |
| SYLVIA | MossdeepCity_Gym | gym | 4 | 39–41 | Medicham 41 | enhanced |
| LEONARDO | Route126 | route | 4 | 36–38 | Sharpedo 38 | enhanced |
| ATHENA | Route127 | route | 5 | 37–39 | Manectric 39 | enhanced |
| HARRISON | Route128 | route | 4 | 38–40 | Tentacruel 40 | enhanced |
| CLARENCE | Route129 | route | 4 | 38–40 | Sharpedo 40 | enhanced |
| NATE | MossdeepCity_Gym | gym | 4 | 39–41 | Grumpig 41 | enhanced |
| KATHLEEN | MossdeepCity_Gym | gym | 4 | 39–41 | Alakazam 41 | enhanced |
| CLIFFORD | MossdeepCity_Gym | gym | 4 | 39–41 | Girafarig 41 | enhanced |
| NICHOLAS | MossdeepCity_Gym | gym | 4 | 39–41 | Wobbuffet 41 | enhanced |
| MACEY | MossdeepCity_Gym | gym | 4 | 39–41 | Xatu 41 | enhanced |
| PAXTON | Route132 | route | 5 | 39–41 | Breloom 41 | enhanced |
| ISABELLA | Route124 | route | 4 | 36–38 | Starmie 38 | enhanced |
| JONATHAN | Route132 | route | 5 | 39–41 | Exploud 41 | enhanced |
| MAXIE_MAGMA_HIDEOUT | MagmaHideout_4F | boss | 6 | 42–44 | Camerupt 44 | enhanced |
| HALEY_3 | Route104 | route t3 | 4 | 37–39 | Breloom 39 | emerald-rematch |
| JAMES_3 | PetalburgWoods | route t3 | 5 | 37–39 | Ninjask 39 | emerald-rematch |
| TRENT_3 | Route112 | route t3 | 5 | 38–40 | Golem 40 | emerald-rematch |
| DEZ_AND_LUKE | MtPyre_2F | route | 4 | 36–37 | Manectric 37 | enhanced |
| KIRA_AND_DAN_3 | AbandonedShip_Rooms2_1F | route t3 | 4 | 39–40 | Illumise 40 | emerald-rematch |
| KEIGO | Route120 | route | 4 | 35–36 | Ninjask 36 | enhanced |
| RILEY | Route120 | route | 4 | 35–36 | Ninjask 36 | enhanced |
| BRENDAN_LILYCOVE | LilycoveCity | route | 3 | 41–43 | Sceptile 43 | story |
| WALLY_LILYCOVE | LilycoveCity | route | 5 | 40–43 | Gallade 43 | story |
| MAY_LILYCOVE | LilycoveCity | route | 3 | 41–43 | Blaziken 43 | story |
| JONAH | Route127 | route | 4 | 37–39 | Sharpedo 39 | enhanced |
| HENRY | Route127 | route | 4 | 37–39 | Tentacruel 39 | enhanced |
| ROGER | Route127 | route | 4 | 37–39 | Gyarados 39 | enhanced |
| ALEXA | Route128 | route | 5 | 38–40 | Azumarill 40 | enhanced |
| RUBEN | Route128 | route | 5 | 38–40 | Shiftry 40 | enhanced |
| KOJI_1 | Route127 | route | 4 | 38–40 | Machamp 40 | emerald-rematch |
| WAYNE | Route128 | route | 4 | 38–40 | Wailord 40 | enhanced |
| AIDAN | Route127 | route | 4 | 37–39 | Skarmory 39 | enhanced |
| REED | Route129 | route | 4 | 38–40 | Sharpedo 40 | enhanced |
| TISHA | Route129 | route | 4 | 38–40 | Lanturn 40 | enhanced |
| KIM_AND_IRIS | Route125 | route | 4 | 36–38 | Camerupt 38 | enhanced |
| RELI_AND_IAN | Route131 | route | 4 | 39–41 | Azumarill 41 | enhanced |
| LILA_AND_ROY_1 | Route124 | route | 4 | 35–37 | Sharpedo 37 | emerald-rematch |
| LILA_AND_ROY_2 | Route124 | route t2 | 4 | 37–39 | Sharpedo 39 | emerald-rematch |
| LILA_AND_ROY_3 | Route124 | route t3 | 4 | 39–41 | Sharpedo 41 | emerald-rematch |
| GRUNT_MAGMA_HIDEOUT_1 | MagmaHideout_1F | grunt | 4 | 38–39 | Golbat 39 | enhanced |
| GRUNT_MAGMA_HIDEOUT_2 | MagmaHideout_1F | grunt | 4 | 38–39 | Mightyena 39 | enhanced |
| GRUNT_MAGMA_HIDEOUT_3 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Camerupt 39 | enhanced |
| GRUNT_MAGMA_HIDEOUT_4 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Claydol 39 | enhanced |
| GRUNT_MAGMA_HIDEOUT_5 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Camerupt 39 | enhanced |
| GRUNT_MAGMA_HIDEOUT_6 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Mightyena 40 | enhanced |
| GRUNT_MAGMA_HIDEOUT_7 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Crobat 40 | enhanced |
| GRUNT_MAGMA_HIDEOUT_8 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Mightyena 40 | enhanced |
| GRUNT_MAGMA_HIDEOUT_9 | MagmaHideout_3F_1R | grunt | 4 | 39–40 | Golbat 40 | enhanced |
| GRUNT_MAGMA_HIDEOUT_10 | MagmaHideout_3F_2R | grunt | 4 | 40–41 | Mightyena 41 | enhanced |
| GRUNT_MAGMA_HIDEOUT_11 | MagmaHideout_4F | grunt | 4 | 40–41 | Claydol 41 | enhanced |
| GRUNT_MAGMA_HIDEOUT_12 | MagmaHideout_4F | grunt | 4 | 40–41 | Camerupt 41 | enhanced |
| GRUNT_MAGMA_HIDEOUT_13 | MagmaHideout_4F | grunt | 4 | 40–41 | Crobat 41 | enhanced |
| GRUNT_MAGMA_HIDEOUT_14 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Mightyena 39 | enhanced |
| GRUNT_MAGMA_HIDEOUT_15 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Camerupt 40 | enhanced |
| GRUNT_MAGMA_HIDEOUT_16 | MagmaHideout_3F_1R | grunt | 4 | 39–40 | Claydol 40 | enhanced |
| TABITHA_MAGMA_HIDEOUT | MagmaHideout_4F | admin | 5 | 39–42 | Camerupt 42 | enhanced |
| DARCY | Route132 | route | 5 | 39–41 | Camerupt 41 | enhanced |
| MAKAYLA | Route132 | route | 5 | 39–41 | Medicham 41 | enhanced |
| LEONEL | Route120 | route | 4 | 35–36 | Manectric 36 | enhanced |
| CALLIE | Route120 | route | 4 | 36–37 | Medicham 37 | enhanced |
| CALE | Route121 | route | 4 | 36–37 | Dustox 37 | enhanced |
| MYLES | Route121 | route | 5 | 36–37 | Hariyama 37 | enhanced |
| PAT | Route121 | route | 5 | 36–37 | Breloom 37 | enhanced |
| CRISTIN_1 | Route121 | route | 4 | 36–38 | Vigoroth 38 | emerald-rematch |
| ANDRES_3 | Route105 | route t3 | 5 | 38–40 | Sandslash 40 | emerald-rematch |
| CORY_3 | Route108 | route t3 | 4 | 38–40 | Tentacruel 40 | emerald-rematch |
| PABLO_2 | Route126 | route t2 | 4 | 38–40 | Starmie 40 | emerald-rematch |
| PABLO_3 | Route126 | route t3 | 5 | 39–41 | Starmie 41 | emerald-rematch |
| KOJI_2 | Route127 | route t2 | 4 | 39–41 | Machamp 41 | emerald-rematch |
| KOJI_3 | Route127 | route t3 | 5 | 40–42 | Machamp 42 | emerald-rematch |
| CRISTIN_2 | Route121 | route t2 | 4 | 37–39 | Slaking 39 | emerald-rematch |
| CRISTIN_3 | Route121 | route t3 | 5 | 39–41 | Slaking 41 | emerald-rematch |
| FERNANDO_2 | Route123 | route t2 | 4 | 38–40 | Exploud 40 | emerald-rematch |
| FERNANDO_3 | Route123 | route t3 | 5 | 39–41 | Exploud 41 | emerald-rematch |
| SAWYER_3 | MtChimney | route t3 | 5 | 38–40 | Golem 40 | emerald-rematch |
| GABRIELLE_2 | MtPyre_3F | route t2 | 4 | 38–39 | Mightyena 39 | emerald-rematch |
| GABRIELLE_3 | MtPyre_3F | route t3 | 5 | 40–41 | Swellow 41 | emerald-rematch |
| THALIA_3 | AbandonedShip_Rooms_1F | route t3 | 5 | 38–40 | Kingdra 40 | emerald-rematch |

### S8 (cap 48) – Space Center, Seafloor Cavern, Sky Pillar, Juan

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_SEAFLOOR_CAVERN_1 | SeafloorCavern_Room1 | grunt | 4 | 41–42 | Mightyena 42 | enhanced |
| GRUNT_SEAFLOOR_CAVERN_2 | SeafloorCavern_Room1 | grunt | 4 | 41–42 | Sharpedo 42 | enhanced |
| GRUNT_SEAFLOOR_CAVERN_3 | SeafloorCavern_Room4 | grunt | 4 | 42–43 | Crobat 43 | enhanced |
| GRUNT_SEAFLOOR_CAVERN_4 | SeafloorCavern_Room4 | grunt | 4 | 42–43 | Sharpedo 43 | enhanced |
| GRUNT_SPACE_CENTER_1 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 40–41 | Camerupt 41 | enhanced |
| SHELLY_SEAFLOOR_CAVERN | SeafloorCavern_Room3 | admin | 6 | 44–46 | Sharpedo 46 | enhanced |
| ARCHIE | SeafloorCavern_Room9 | boss | 6 | 46–48 | Sharpedo 48 | enhanced |
| ROSE_4 | Route118 | route t4 | 4 | 42–45 | Roserade 45 | emerald-rematch |
| DUSTY_4 | Route111 | route t4 | 4 | 42–45 | Sandslash 45 | emerald-rematch |
| GABBY_AND_TY_6 |  | route | 4 | 44–45 | Exploud 45 | emerald-rematch |
| LOLA_4 | Route109 | route t4 | 4 | 42–45 | Azumarill 45 | emerald-rematch |
| RICKY_4 | Route109 | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch |
| WILTON_4 | Route111 | route t4 | 5 | 42–45 | Hariyama 45 | emerald-rematch |
| BROOKE_4 | Route111 | route t4 | 5 | 42–45 | Roserade 45 | emerald-rematch |
| VALERIE_4 | MtPyre_6F | route t4 | 5 | 42–45 | Grumpig 45 | emerald-rematch |
| DAPHNE | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Starmie 46 | enhanced |
| GRUNT_SPACE_CENTER_2 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 41–42 | Camerupt 42 | enhanced |
| BRIANNA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Seaking 46 | enhanced |
| CINDY_5 | Route104 | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch |
| CONNIE | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Seaking 46 | enhanced |
| BRIDGET | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Azumarill 46 | enhanced |
| OLIVIA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Ludicolo 46 | enhanced |
| TIFFANY | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Sharpedo 46 | enhanced |
| JESSICA_4 | Route121 | route t4 | 4 | 42–45 | Seviper 45 | emerald-rematch |
| WINSTON_4 | Route104 | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch |
| STEVE_4 | Route114 | route t4 | 4 | 42–45 | Rhydon 45 | emerald-rematch |
| TONY_4 | Route107 | route t4 | 5 | 42–45 | Sharpedo 45 | emerald-rematch |
| NOB_4 | Route115 | route t4 | 5 | 42–45 | Machamp 45 | emerald-rematch |
| DALTON_4 | Route118 | route t4 | 5 | 42–45 | Magneton 45 | emerald-rematch |
| BERNIE_4 | Route114 | route t4 | 5 | 42–45 | Magcargo 45 | emerald-rematch |
| ETHAN_4 | JaggedPass | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch |
| JEFFREY_4 | Route120 | route t4 | 5 | 42–45 | Masquerain 45 | emerald-rematch |
| CAMERON_4 | Route123 | route t4 | 5 | 42–45 | Alakazam 45 | emerald-rematch |
| JACKI_4 | Route123 | route t4 | 5 | 42–45 | Alakazam 45 | emerald-rematch |
| WALTER_4 | Route121 | route t4 | 5 | 42–45 | Manectric 45 | emerald-rematch |
| JUAN_1 | SootopolisCity_Gym_1F | leader | 6 | 44–48 | Kingdra 48 | emerald-rematch |
| JERRY_4 | Route116 | route t4 | 4 | 42–45 | Gardevoir 45 | emerald-rematch |
| KAREN_4 | Route116 | route t4 | 4 | 42–45 | Breloom 45 | emerald-rematch |
| ANNA_AND_MEG_4 | Route117 | route t4 | 4 | 43–45 | Hariyama 45 | emerald-rematch |
| MIGUEL_4 | Route103 | route t4 | 4 | 42–45 | Delcatty 45 | emerald-rematch |
| BETHANY | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Azumarill 46 | enhanced |
| ISABEL_4 | Route110 | route t4 | 4 | 42–45 | Minun 45 | emerald-rematch |
| TIMOTHY_4 | Route115 | route t4 | 4 | 42–45 | Hariyama 45 | emerald-rematch |
| SHELBY_4 | MtChimney | route t4 | 4 | 42–45 | Hariyama 45 | emerald-rematch |
| CALVIN_4 | Route102 | route t4 | 4 | 42–45 | Mightyena 45 | emerald-rematch |
| ELLIOT_4 | Route106 | route t4 | 5 | 42–45 | Gyarados 45 | emerald-rematch |
| BENJAMIN_4 | Route110 | route t4 | 4 | 42–45 | Magneton 45 | emerald-rematch |
| ABIGAIL_4 | Route110 | route t4 | 4 | 42–45 | Magneton 45 | emerald-rematch |
| DYLAN_4 | Route117 | route t4 | 4 | 42–45 | Dodrio 45 | emerald-rematch |
| MARIA_4 | Route117 | route t4 | 4 | 42–45 | Dodrio 45 | emerald-rematch |
| ISAIAH_4 | Route128 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch |
| KATELYN_4 | Route128 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch |
| BENNY | Route110_TrickHousePuzzle6 | route | 4 | 42–44 | Swellow 44 | enhanced |
| ROBERT_4 | Route120 | route t4 | 5 | 42–45 | Altaria 45 | emerald-rematch |
| LAO_4 | Route113 | route t4 | 5 | 42–45 | Weezing 45 | emerald-rematch |
| CYNDY_4 | Route115 | route t4 | 4 | 42–45 | Hariyama 45 | emerald-rematch |
| MADELINE_4 | Route113 | route t4 | 5 | 42–45 | Camerupt 45 | emerald-rematch |
| JENNY_4 | Route124 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch |
| DIANA_4 | JaggedPass | route t4 | 4 | 42–45 | Altaria 45 | emerald-rematch |
| AMY_AND_LIV_5 | Route103 | route t4 | 4 | 43–45 | Minun 45 | emerald-rematch |
| ERNEST_4 | Route125 | route t4 | 5 | 42–45 | Machamp 45 | emerald-rematch |
| ANNIKA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Milotic 46 | enhanced |
| TABITHA_MOSSDEEP | MossdeepCity_SpaceCenter_2F | admin | 3 | 44–46 | Camerupt 46 | enhanced |
| EDWIN_4 | Route110 | route t4 | 5 | 42–45 | Shiftry 45 | emerald-rematch |
| ASTER_SKY_PILLAR_DEINO |  | route | 5 | 45–48 | Salamence 48 | story |
| ASTER_SKY_PILLAR_DREEPY |  | route | 5 | 45–48 | Salamence 48 | story |
| ISAAC_4 | Route117 | route t4 | 6 | 42–45 | Hariyama 45 | emerald-rematch |
| LYDIA_4 | Route117 | route t4 | 6 | 42–45 | Azumarill 45 | emerald-rematch |
| SEBASTIAN | Route110_TrickHousePuzzle6 | route | 4 | 42–44 | Cacturne 44 | enhanced |
| JACKSON_4 | Route119 | route t4 | 5 | 42–45 | Breloom 45 | emerald-rematch |
| SOPHIA | Route110_TrickHousePuzzle6 | route | 4 | 42–44 | Altaria 44 | enhanced |
| CATHERINE_4 | Route119 | route t4 | 4 | 42–45 | Roserade 45 | emerald-rematch |
| GRUNT_SEAFLOOR_CAVERN_5 | SeafloorCavern_Room3 | grunt | 4 | 43–44 | Mightyena 44 | enhanced |
| GRUNT_SPACE_CENTER_3 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 40–41 | Mightyena 41 | enhanced |
| GRUNT_SPACE_CENTER_4 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 41–42 | Claydol 42 | enhanced |
| GRUNT_SPACE_CENTER_5 | MossdeepCity_SpaceCenter_2F | grunt | 4 | 42–43 | Crobat 43 | enhanced |
| GRUNT_SPACE_CENTER_6 | MossdeepCity_SpaceCenter_2F | grunt | 4 | 42–43 | Mightyena 43 | enhanced |
| GRUNT_SPACE_CENTER_7 | MossdeepCity_SpaceCenter_2F | grunt | 4 | 42–43 | Claydol 43 | enhanced |
| ASTER_SKY_PILLAR_JANGMO_O |  | route | 5 | 45–48 | Salamence 48 | story |
| HALEY_4 | Route104 | route t4 | 4 | 42–45 | Breloom 45 | emerald-rematch |
| ANDREA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Lapras 46 | enhanced |
| CRISSY | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Wailord 46 | enhanced |
| JAMES_4 | PetalburgWoods | route t4 | 5 | 42–45 | Ninjask 45 | emerald-rematch |
| TRENT_4 | Route112 | route t4 | 5 | 42–45 | Golem 45 | emerald-rematch |
| KIRA_AND_DAN_4 | AbandonedShip_Rooms2_1F | route t4 | 4 | 43–45 | Gorebyss 45 | emerald-rematch |
| LILA_AND_ROY_4 | Route124 | route t4 | 4 | 43–45 | Sharpedo 45 | emerald-rematch |
| MAXIE_MOSSDEEP | MossdeepCity_SpaceCenter_2F | boss | 3 | 46–48 | Camerupt 48 | enhanced |
| ANDRES_4 | Route105 | route t4 | 5 | 42–45 | Sandslash 45 | emerald-rematch |
| CORY_4 | Route108 | route t4 | 4 | 42–45 | Machamp 45 | emerald-rematch |
| PABLO_4 | Route126 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch |
| KOJI_4 | Route127 | route t4 | 5 | 42–45 | Machamp 45 | emerald-rematch |
| CRISTIN_4 | Route121 | route t4 | 5 | 42–45 | Slaking 45 | emerald-rematch |
| FERNANDO_4 | Route123 | route t4 | 5 | 42–45 | Exploud 45 | emerald-rematch |
| SAWYER_4 | MtChimney | route t4 | 5 | 42–45 | Golem 45 | emerald-rematch |
| GABRIELLE_4 | MtPyre_3F | route t4 | 6 | 42–45 | Swellow 45 | emerald-rematch |
| THALIA_4 | AbandonedShip_Rooms_1F | route t4 | 5 | 42–45 | Kingdra 45 | emerald-rematch |

### S9 (cap 60) – Victory Road, Elite Four, Champion

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| FELIX | VictoryRoad_B2F | route | 5 | 53–55 | Medicham 55 | enhanced |
| EDGAR | VictoryRoad_1F | route | 5 | 48–50 | Cacturne 50 | enhanced |
| ALBERT | VictoryRoad_1F | route | 5 | 48–50 | Muk 50 | enhanced |
| SAMUEL | VictoryRoad_B1F | route | 5 | 50–52 | Alakazam 52 | enhanced |
| VITO | VictoryRoad_B2F | route | 5 | 52–54 | Shiftry 54 | enhanced |
| OWEN | VictoryRoad_B2F | route | 5 | 52–54 | Wailord 54 | enhanced |
| HOPE | VictoryRoad_1F | route | 5 | 49–51 | Roserade 51 | enhanced |
| SHANNON | VictoryRoad_B1F | route | 5 | 50–52 | Claydol 52 | enhanced |
| MICHELLE | VictoryRoad_B1F | route | 5 | 50–52 | Ludicolo 52 | enhanced |
| CAROLINE | VictoryRoad_B2F | route | 5 | 52–54 | Skarmory 54 | enhanced |
| JULIE | VictoryRoad_B2F | route | 5 | 52–54 | Ninetales 54 | enhanced |
| PATRICIA | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Banette 50 | enhanced |
| JOSHUA | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Alakazam 50 | enhanced |
| ALEXIS | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Gardevoir 50 | enhanced |
| SIDNEY | EverGrandeCity_SidneysRoom | elite | 6 | 54–55 | Absol 55 | enhanced |
| PHOEBE | EverGrandeCity_PhoebesRoom | elite | 6 | 54–56 | Dusknoir 56 | enhanced |
| GLACIA | EverGrandeCity_GlaciasRoom | elite | 6 | 55–57 | Walrein 57 | enhanced |
| DRAKE | EverGrandeCity_DrakesRoom | elite | 6 | 56–58 | Salamence 58 | enhanced |
| QUINCY | VictoryRoad_1F | route | 5 | 49–51 | Slaking 51 | enhanced |
| KATELYNN | VictoryRoad_1F | route | 5 | 49–51 | Gardevoir 51 | enhanced |
| WALLACE | EverGrandeCity_ChampionsRoom | elite | 6 | 57–60 | Milotic 60 | enhanced |
| NICOLAS_1 | MeteorFalls_1F_2R | route | 4 | 48–49 | Shelgon 49 | emerald-rematch |
| NICOLAS_2 | MeteorFalls_1F_2R | route t2 | 4 | 50–52 | Salamence 52 | emerald-rematch |
| NICOLAS_3 | MeteorFalls_1F_2R | route t3 | 5 | 52–54 | Salamence 54 | emerald-rematch |
| NICOLAS_4 | MeteorFalls_1F_2R | route t4 | 5 | 54–55 | Salamence 55 | emerald-rematch |
| DIANNE | VictoryRoad_B2F | route | 5 | 53–55 | Lanturn 55 | enhanced |
| WALLY_VR_1 | VictoryRoad_1F | route | 5 | 54–57 | Gallade 57 | story |
| BRENDAN_SOOTOPOLIS | SootopolisCity | route | 6 | 50–53 | Sceptile 53 | story |
| MAY_SOOTOPOLIS | SootopolisCity | route | 6 | 50–53 | Blaziken 53 | story |
| MITCHELL | VictoryRoad_B1F | route | 5 | 50–52 | Solrock 52 | enhanced |
| HALLE | VictoryRoad_B1F | route | 5 | 50–52 | Absol 52 | enhanced |
| JOHN_AND_JAY_1 | MeteorFalls_1F_2R | route | 4 | 48–49 | Hariyama 49 | emerald-rematch |
| JOHN_AND_JAY_2 | MeteorFalls_1F_2R | route t2 | 4 | 50–52 | Hariyama 52 | emerald-rematch |
| JOHN_AND_JAY_3 | MeteorFalls_1F_2R | route t3 | 4 | 52–54 | Hariyama 54 | emerald-rematch |
| JOHN_AND_JAY_4 | MeteorFalls_1F_2R | route t4 | 4 | 54–55 | Hariyama 55 | emerald-rematch |
| MARIELA | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Starmie 50 | enhanced |
| ALVARO | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Alakazam 50 | enhanced |
| EVERETT | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Arcanine 50 | enhanced |

### POST (cap none) – After the Champion (no cap)

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| ROSE_5 | Route118 | route t5 | 4 | 60–61 | Roserade 61 | emerald-rematch |
| DUSTY_5 | Route111 | route t5 | 4 | 60–62 | Sandslash 62 | emerald-rematch |
| LOLA_5 | Route109 | route t5 | 4 | 60–62 | Azumarill 62 | emerald-rematch |
| RICKY_5 | Route109 | route t5 | 4 | 60–62 | Linoone 62 | emerald-rematch |
| VINCENT | Route110_TrickHousePuzzle8 | route | 5 | 64–66 | Sharpedo 66 | enhanced |
| LEROY | Route110_TrickHousePuzzle8 | route | 5 | 65–67 | Starmie 67 | enhanced |
| WILTON_5 | Route111 | route t5 | 5 | 60–62 | Hariyama 62 | emerald-rematch |
| KEIRA | Route110_TrickHousePuzzle8 | route | 5 | 65–67 | Aggron 67 | enhanced |
| BROOKE_5 | Route111 | route t5 | 5 | 60–61 | Roserade 61 | emerald-rematch |
| VALERIE_5 | MtPyre_6F | route t5 | 5 | 63–65 | Grumpig 65 | emerald-rematch |
| NAOMI | SSTidalCorridor | route | 4 | 65–67 | Roserade 67 | enhanced |
| CINDY_6 | Route104 | route t5 | 4 | 60–62 | Linoone 62 | emerald-rematch |
| JESSICA_5 | Route121 | route t5 | 4 | 64–66 | Seviper 66 | emerald-rematch |
| GARRET | SSTidalCorridor | route | 4 | 65–67 | Azumarill 67 | enhanced |
| WINSTON_5 | Route104 | route t5 | 4 | 60–62 | Linoone 62 | emerald-rematch |
| STEVE_5 | Route114 | route t5 | 4 | 60–62 | Rhyperior 62 | emerald-rematch |
| TONY_5 | Route107 | route t5 | 5 | 62–64 | Sharpedo 64 | emerald-rematch |
| NOB_5 | Route115 | route t5 | 5 | 60–61 | Machamp 61 | emerald-rematch |
| DALTON_5 | Route118 | route t5 | 5 | 60–61 | Magnezone 61 | emerald-rematch |
| BERNIE_5 | Route114 | route t5 | 5 | 60–62 | Magcargo 62 | emerald-rematch |
| ETHAN_5 | JaggedPass | route t5 | 4 | 60–61 | Linoone 61 | emerald-rematch |
| JEFFREY_5 | Route120 | route t5 | 6 | 60–63 | Masquerain 63 | emerald-rematch |
| CAMERON_5 | Route123 | route t5 | 5 | 65–67 | Alakazam 67 | emerald-rematch |
| JACKI_5 | Route123 | route t5 | 5 | 64–66 | Alakazam 66 | emerald-rematch |
| MICAH | SSTidalCorridor | route | 5 | 64–66 | Manectric 66 | enhanced |
| THOMAS | SSTidalCorridor | route | 4 | 65–67 | Zangoose 67 | enhanced |
| WALTER_5 | Route121 | route t5 | 5 | 63–65 | Manectric 65 | emerald-rematch |
| JERRY_5 | Route116 | route t5 | 4 | 60–61 | Gardevoir 61 | emerald-rematch |
| KAREN_5 | Route116 | route t5 | 4 | 60–62 | Breloom 62 | emerald-rematch |
| ANNA_AND_MEG_5 | Route117 | route t5 | 4 | 61–63 | Hariyama 63 | emerald-rematch |
| COLTON | SSTidalCorridor | route | 5 | 63–65 | Delcatty 65 | enhanced |
| MIGUEL_5 | Route103 | route t5 | 4 | 60–62 | Delcatty 62 | emerald-rematch |
| ISABEL_5 | Route110 | route t5 | 4 | 60–62 | Minun 62 | emerald-rematch |
| TIMOTHY_5 | Route115 | route t5 | 4 | 63–65 | Hariyama 65 | emerald-rematch |
| SHELBY_5 | MtChimney | route t5 | 4 | 62–64 | Hariyama 64 | emerald-rematch |
| CALVIN_5 | Route102 | route t5 | 4 | 60–62 | Mightyena 62 | emerald-rematch |
| ELLIOT_5 | Route106 | route t5 | 5 | 60–62 | Gyarados 62 | emerald-rematch |
| BENJAMIN_5 | Route110 | route t5 | 4 | 62–64 | Magnezone 64 | emerald-rematch |
| ABIGAIL_5 | Route110 | route t5 | 4 | 61–63 | Magnezone 63 | emerald-rematch |
| DYLAN_5 | Route117 | route t5 | 4 | 61–63 | Dodrio 63 | emerald-rematch |
| MARIA_5 | Route117 | route t5 | 4 | 61–63 | Dodrio 63 | emerald-rematch |
| ISAIAH_5 | Route128 | route t5 | 5 | 66–68 | Starmie 68 | emerald-rematch |
| KATELYN_5 | Route128 | route t5 | 5 | 66–68 | Starmie 68 | emerald-rematch |
| NICOLAS_5 | MeteorFalls_1F_2R | route t5 | 5 | 67–69 | Salamence 69 | emerald-rematch |
| ROBERT_5 | Route120 | route t5 | 5 | 63–65 | Altaria 65 | emerald-rematch |
| LAO_5 | Route113 | route t5 | 5 | 60–62 | Weezing 62 | emerald-rematch |
| CYNDY_5 | Route115 | route t5 | 4 | 60–62 | Hariyama 62 | emerald-rematch |
| MADELINE_5 | Route113 | route t5 | 5 | 61–63 | Camerupt 63 | emerald-rematch |
| JENNY_5 | Route124 | route t5 | 5 | 65–67 | Starmie 67 | emerald-rematch |
| DIANA_5 | JaggedPass | route t5 | 4 | 62–64 | Altaria 64 | emerald-rematch |
| AMY_AND_LIV_6 | Route103 | route t5 | 4 | 60–62 | Minun 62 | emerald-rematch |
| PHILLIP | SSTidalCorridor | route | 4 | 64–66 | Machamp 66 | enhanced |
| LEONARD | SSTidalCorridor | route | 4 | 64–66 | Machamp 66 | enhanced |
| ERNEST_5 | Route125 | route t5 | 5 | 65–67 | Machamp 67 | emerald-rematch |
| EDWIN_5 | Route110 | route t5 | 5 | 60–62 | Shiftry 62 | emerald-rematch |
| BRENDAN_POSTGAME | LittlerootTown_ProfessorBirchsLab | route | 6 | 72–76 | Sceptile 76 | story |
| MAY_POSTGAME | LittlerootTown_ProfessorBirchsLab | route | 6 | 72–76 | Blaziken 76 | story |
| BRENDAN_POSTGAME_DOUBLE | LittlerootTown_ProfessorBirchsLab | route | 3 | 72–76 | Sceptile 76 | story |
| ISAAC_5 | Route117 | route t5 | 6 | 60–61 | Hariyama 61 | emerald-rematch |
| LYDIA_5 | Route117 | route t5 | 6 | 60–61 | Azumarill 61 | emerald-rematch |
| JACKSON_5 | Route119 | route t5 | 5 | 62–64 | Breloom 64 | emerald-rematch |
| CATHERINE_5 | Route119 | route t5 | 4 | 62–64 | Roserade 64 | emerald-rematch |
| ASTER_POSTGAME_DEINO |  | route | 6 | 74–78 | Salamence 78 | story |
| ASTER_POSTGAME_DREEPY |  | route | 6 | 74–78 | Salamence 78 | story |
| ASTER_POSTGAME_JANGMO_O |  | route | 6 | 74–78 | Salamence 78 | story |
| HALEY_5 | Route104 | route t5 | 4 | 60–61 | Breloom 61 | emerald-rematch |
| JAMES_5 | PetalburgWoods | route t5 | 5 | 60–61 | Ninjask 61 | emerald-rematch |
| TRENT_5 | Route112 | route t5 | 5 | 60–61 | Golem 61 | emerald-rematch |
| LEA_AND_JED | SSTidalCorridor | route | 4 | 65–67 | Gardevoir 67 | enhanced |
| KIRA_AND_DAN_5 | AbandonedShip_Rooms2_1F | route t5 | 4 | 62–64 | Gorebyss 64 | emerald-rematch |
| WALLY_VR_2 | VictoryRoad_1F | route | 5 | 63–66 | Gallade 66 | story |
| WALLY_VR_3 | VictoryRoad_1F | route t2 | 5 | 67–70 | Gallade 70 | story |
| WALLY_VR_4 | VictoryRoad_1F | route t3 | 5 | 71–74 | Gallade 74 | story |
| WALLY_VR_5 | VictoryRoad_1F | route t4 | 5 | 75–78 | Gallade 78 | story |
| MAY_POSTGAME_DOUBLE | LittlerootTown_ProfessorBirchsLab | route | 3 | 72–76 | Blaziken 76 | story |
| JOHN_AND_JAY_5 | MeteorFalls_1F_2R | route t5 | 4 | 68–70 | Hariyama 70 | emerald-rematch |
| LILA_AND_ROY_5 | Route124 | route t5 | 4 | 68–70 | Sharpedo 70 | emerald-rematch |
| ROXANNE_2 | RustboroCity_Gym | leader t2 | 6 | 66–70 | Probopass 70 | emerald-rematch |
| ROXANNE_3 | RustboroCity_Gym | leader t3 | 6 | 69–73 | Probopass 73 | emerald-rematch |
| ROXANNE_4 | RustboroCity_Gym | leader t4 | 6 | 72–76 | Probopass 76 | emerald-rematch |
| ROXANNE_5 | RustboroCity_Gym | leader t5 | 6 | 75–79 | Probopass 79 | emerald-rematch |
| BRAWLY_2 | DewfordTown_Gym | leader t2 | 6 | 66–70 | Hariyama 70 | emerald-rematch |
| BRAWLY_3 | DewfordTown_Gym | leader t3 | 6 | 69–73 | Hariyama 73 | emerald-rematch |
| BRAWLY_4 | DewfordTown_Gym | leader t4 | 6 | 72–76 | Hariyama 76 | emerald-rematch |
| BRAWLY_5 | DewfordTown_Gym | leader t5 | 6 | 75–79 | Hariyama 79 | emerald-rematch |
| WATTSON_2 | MauvilleCity_Gym | leader t2 | 6 | 66–70 | Manectric 70 | emerald-rematch |
| WATTSON_3 | MauvilleCity_Gym | leader t3 | 6 | 69–73 | Manectric 73 | emerald-rematch |
| WATTSON_4 | MauvilleCity_Gym | leader t4 | 6 | 72–76 | Manectric 76 | emerald-rematch |
| WATTSON_5 | MauvilleCity_Gym | leader t5 | 6 | 75–79 | Manectric 79 | emerald-rematch |
| FLANNERY_2 | LavaridgeTown_Gym_1F | leader t2 | 6 | 66–70 | Torkoal 70 | emerald-rematch |
| FLANNERY_3 | LavaridgeTown_Gym_1F | leader t3 | 6 | 69–73 | Torkoal 73 | emerald-rematch |
| FLANNERY_4 | LavaridgeTown_Gym_1F | leader t4 | 6 | 72–76 | Torkoal 76 | emerald-rematch |
| FLANNERY_5 | LavaridgeTown_Gym_1F | leader t5 | 6 | 75–79 | Torkoal 79 | emerald-rematch |
| NORMAN_2 | PetalburgCity_Gym | leader t2 | 6 | 67–71 | Slaking 71 | emerald-rematch |
| NORMAN_3 | PetalburgCity_Gym | leader t3 | 6 | 70–74 | Slaking 74 | emerald-rematch |
| NORMAN_4 | PetalburgCity_Gym | leader t4 | 6 | 73–77 | Slaking 77 | emerald-rematch |
| NORMAN_5 | PetalburgCity_Gym | leader t5 | 6 | 76–80 | Slaking 80 | emerald-rematch |
| WINONA_2 | FortreeCity_Gym | leader t2 | 6 | 67–71 | Altaria 71 | emerald-rematch |
| WINONA_3 | FortreeCity_Gym | leader t3 | 6 | 70–74 | Altaria 74 | emerald-rematch |
| WINONA_4 | FortreeCity_Gym | leader t4 | 6 | 73–77 | Altaria 77 | emerald-rematch |
| WINONA_5 | FortreeCity_Gym | leader t5 | 6 | 76–80 | Altaria 80 | emerald-rematch |
| TATE_AND_LIZA_2 | MossdeepCity_Gym | leader t2 | 6 | 67–71 | Solrock 71 | emerald-rematch |
| TATE_AND_LIZA_3 | MossdeepCity_Gym | leader t3 | 6 | 70–74 | Solrock 74 | emerald-rematch |
| TATE_AND_LIZA_4 | MossdeepCity_Gym | leader t4 | 6 | 73–77 | Solrock 77 | emerald-rematch |
| TATE_AND_LIZA_5 | MossdeepCity_Gym | leader t5 | 6 | 76–80 | Solrock 80 | emerald-rematch |
| JUAN_2 | SootopolisCity_Gym_1F | leader t2 | 6 | 67–71 | Kingdra 71 | emerald-rematch |
| JUAN_3 | SootopolisCity_Gym_1F | leader t3 | 6 | 70–74 | Kingdra 74 | emerald-rematch |
| JUAN_4 | SootopolisCity_Gym_1F | leader t4 | 6 | 73–77 | Kingdra 77 | emerald-rematch |
| JUAN_5 | SootopolisCity_Gym_1F | leader t5 | 6 | 76–80 | Kingdra 80 | emerald-rematch |
| STEVEN | MeteorFalls_StevensCave | elite | 6 | 77–80 | Metagross 80 | enhanced |
| ANDRES_5 | Route105 | route t5 | 5 | 61–63 | Sandslash 63 | emerald-rematch |
| CORY_5 | Route108 | route t5 | 4 | 60–62 | Machamp 62 | emerald-rematch |
| PABLO_5 | Route126 | route t5 | 5 | 64–66 | Starmie 66 | emerald-rematch |
| KOJI_5 | Route127 | route t5 | 5 | 64–66 | Machamp 66 | emerald-rematch |
| CRISTIN_5 | Route121 | route t5 | 5 | 63–65 | Slaking 65 | emerald-rematch |
| FERNANDO_5 | Route123 | route t5 | 5 | 63–65 | Exploud 65 | emerald-rematch |
| SAWYER_5 | MtChimney | route t5 | 5 | 60–61 | Golem 61 | emerald-rematch |
| GABRIELLE_5 | MtPyre_3F | route t5 | 6 | 60–63 | Swellow 63 | emerald-rematch |
| THALIA_5 | AbandonedShip_Rooms_1F | route t5 | 5 | 62–64 | Kingdra 64 | emerald-rematch |
