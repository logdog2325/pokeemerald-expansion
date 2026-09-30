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
>
> **Round 1 (feedback 1.15):** real ORAS data is now in the repository (scraped from Serebii, see
> [ORAS data](#oras-data-round-1)). Every ORAS rematch trainer that exists in Emerald already has Emerald rematch
> tiers (rule 1 keeps those), so the ORAS rosters used are: the **Elite Four's ORAS post-game rosters** (4,
> `oras-rematch`) and **27 ORAS first-battle teams** richer than the trainer's Emerald team (`oras-first`);
> 362 trainers keep their Emerald rematch roster and 405 their enhanced own team.

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

Each batch records its source per trainer (`oras-rematch`, `oras-first`, `emerald-rematch`, `enhanced`) in a
sidecar file; the table at the end of this page is generated from them. ORAS rosters come from
`tools/hack/trainers/oras/oras_trainers.json` (Serebii, [ORAS data](#oras-data-round-1)); Serebii lists species,
levels and held items (moves only for the Elite Four), so every team is still run through the legality checks
below.

## Species pool

The Hoenn Pokédex (with the cross-generation evolutions the expansion lists there: Gallade, Froslass, Probopass,
Dusknoir, Roserade, Magnezone, …) plus every species some vanilla Emerald trainer uses (Kabuto, Aerodactyl, …).
Round 1 (feedback 1.28, D-195): also the evolution families of every species wild in Hoenn
([hack_wild.md](hack_wild.md), Gens 4–9 included) and of every species on an ORAS Hoenn trainer
(`oras/oras_trainers.json`). Not used: legendaries and mythicals, and the Deino / Dreepy / Jangmo-o lines (reserved
for the player and Aster).
Exception: the Elite Four use their ORAS post-game rosters, which include species from all regions (D-173), and the
Battle Frontier legends and Lance bring their own (Wes's Colosseum team, Red's, Blue's and Lance's PWT teams;
`LEGEND_TRAINERS`, D-226, D-262).
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
  Roxanne's Aerodactyl, Wattson's Manectric, Flannery's Camerupt, Winona's Altaria), the Elite Four's post-game
  rematch (their ORAS Megas: Absol, Sableye, Glalie, Salamence; D-174), the story trainers late in the game, and
  the Battle Frontier legends (Red's Charizard X, Blue's Alakazam; D-226) and Lance (Dragonite; D-262).
  No Tera, Dynamax or Z-Moves.

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
`party.py` (the `.party` reader/writer they share), `gen49.py` + `gen49_plan.py` (the Gen 4–9 swaps, `--coverage`;
[below](#second-pass-round-1-follow-up-feedback-140-d-240--d-242)) and the ORAS tools in `oras/` (below).

## ORAS data (round 1)

Source: Serebii.net, fetched 2026-09-30 (docs/hack_resources.md) – the Pokéarth "Gen VI" location pages
(`https://www.serebii.net/pokearth/hoenn/<location>.shtml`: routes, towns and their gyms, caves, Victory Road,
the League) and the ORAS Elite Four page (`https://www.serebii.net/omegarubyalphasapphire/elitefour.shtml`, with
moves). Files in `tools/hack/trainers/oras/`:

| File | What |
|---|---|
| `scrape_serebii.py --cache DIR` | fetches the pages once (2 s apart, cached in `DIR`, not the repo) and parses them |
| `oras_trainers.json` | every ORAS trainer table (58 pages, 761 tables), and per trainer the first team + later / rematch teams |
| `match_oras.py` (`--list`, `--show ID`, `--tiers`) | Emerald trainer ↔ ORAS trainer → `oras_matches.json` (D-171) |
| `build_oras_batch.py -o DRAFT` (`--check FILES`) | drafts the `oras-first` blocks (D-172); `--check`: every move known at its level under the segment rules |
| `batch_oras_first.party` + `.sources.json` | the 27 `oras-first` teams (reviewed draft) |
| `batch_elite_four.party` + `.sources.json` | the Elite Four's first battle (D-173) |
| `elite_four_rematch.party` | the Elite Four's post-game rematch, ready but **not in the ROM** (no trainer ids yet, D-174) |

**Matching** (D-171): of the 438 named, non-story trainers (first tiers), 228 match exactly (same name and class
on the Serebii page of their map), 4 with another class (ORAS "Teammates": Anna & Meg, Kate & Joy, Kim & Iris,
Tyra & Ivy), 8 only have a namesake elsewhere (not used: Julie, Patricia, Kindra, Melissa, Joshua, Georgia,
Martha – and Shelby, the same Expert moved from Mt. Chimney to Jagged Pass), 8 are ambiguous (Gabby & Ty's six
battles are spread over three route pages; Marlene is a Route 128 Tuber in ORAS; Wallace is not ORAS's Champion)
and 190 have no ORAS counterpart. ORAS replaced the Abandoned Ship with Sea Mauville; its trainers are matched there.

**ORAS rematch teams**: every ORAS trainer with rematch teams that exists in Emerald has Emerald rematch tiers, so
rule 1 keeps their Emerald roster; no regular trainer changes to `oras-rematch`. The ORAS rosters differ as below
(the ORAS post-game tier mostly adds one Pokémon from another region; not applied):

| Trainer | Emerald rematch roster (last tier) | ORAS last rematch | New families in ORAS |
|---|---|---|---|
| ROSE_1 | Breloom, Gloom, Roselia | Bellossom 48, Sunflora 48, Roserade 48 | Sunflora |
| DUSTY_1 | Sandslash | Sandslash 46, Tyrantrum 46, Aurorus 46, Claydol 46, Aerodactyl 46 | Tyrantrum, Aurorus, Claydol, Aerodactyl |
| LOLA_1 | Azumarill, Azumarill | Azumarill 50 | – |
| RICKY_1 | Linoone | Linoone 50 | – |
| WILTON_1 | Manectric, Wailmer, Hariyama | Talonflame 50, Manectric 51, Wailord 51, Hariyama 51, Haxorus 52 | Talonflame, Haxorus |
| BROOKE_1 | Pelipper, Camerupt, Roselia | Purugly 50, Pelipper 51, Camerupt 51, Roserade 51, Lapras 52 | Purugly, Lapras |
| VALERIE_1 | Duskull, Sableye, Grumpig | Sableye 47, Banette 48, Mismagius 49 | Banette, Mismagius |
| CINDY_1 | Linoone | Linoone 49, Pyroar 49 | Pyroar |
| JESSICA_1 | Kecleon, Seviper | Kecleon 47, Seviper 48, Krookodile 49 | Krookodile |
| WINSTON_1 | Linoone | Linoone 49, Pyroar 49 | Pyroar |
| STEVE_1 | Aggron, Rhydon | Ampharos 47, Slowbro 47, Aggron 47, Rhyperior 47 | Ampharos, Slowbro |
| TONY_1 | Starmie, Sharpedo | Tentacruel 49, Jellicent 49 | Tentacruel, Jellicent |
| NOB_1 | Machop, Machoke, Machoke, Machamp | Primeape 50, Hitmonlee 50, Machamp 50 | Primeape, Hitmonlee |
| DALTON_1 | Magneton, Exploud, Magneton | Chatot 48, Exploud 48, Magnezone 48 | Chatot |
| BERNIE_1 | Magcargo, Pelipper | Magcargo 48, Pelipper 50 | – |
| ETHAN_1 | Swellow, Sandslash, Linoone | Swalot 47, Skuntank 47, Crobat 47 | Swalot, Skuntank, Crobat |
| CAMERON_1 | Solrock, Alakazam | Solrock 49, Exeggutor 50, Alakazam 51 | Exeggutor |
| WALTER_1 | Linoone, Golduck, Manectric | Manectric 48, Stoutland 50 | Stoutland |
| JERRY_1 | Kirlia, Banette, Medicham | Gardevoir 48, Medicham 47, Bisharp 46 | Bisharp |
| KAREN_1 | Breloom, Exploud | Breloom 47, Dewgong 47, Exploud 47 | Dewgong |
| ANNA_AND_MEG_1 | Linoone, Hariyama | Linoone 50, Hariyama 51 | – |
| MIGUEL_1 | Delcatty | Delcatty 51 | – |
| ISABEL_1 | Plusle, Minun | Plusle 49, Minun 49 | – |
| TIMOTHY_1 | Hariyama | Hawlucha 54, Hariyama 55, Conkeldurr 56 | Hawlucha, Conkeldurr |
| SHELBY_1 (ORAS: Jagged Pass) | Medicham, Hariyama | Medicham 54, Hariyama 55, Lucario 56 | Lucario |
| CALVIN_1 | Swellow, Linoone, Mightyena | Swellow 47, Linoone 47, Lickilicky 47 | Lickilicky |
| ELLIOT_1 | Gyarados, Sharpedo, Gyarados, Tentacruel | Tentacruel 46, Octillery 47, Whiscash 47, Gyarados 48 | Octillery, Whiscash |
| BENJAMIN_1 | Magneton | Electrode 49, Klinklang 49 | Electrode, Klinklang |
| DYLAN_1 | Dodrio | Dodrio 48, Arcanine 50 | Arcanine |
| ISAIAH_1 | Starmie | Floatzel 49, Starmie 49 | Floatzel |
| NICOLAS_1 | Altaria, Altaria, Shelgon | Noivern 50, Druddigon 50, Flygon 50 | Noivern, Druddigon, Flygon |
| ROBERT_1 | Altaria, Xatu | Fearow 47, Altaria 48, Staraptor 49 | Fearow, Staraptor |
| LAO_1 | Koffing, Koffing, Koffing, Weezing | Weezing 46, Weezing 47, Weezing 48 | – |
| CYNDY_1 | Medicham, Hariyama | Hitmonchan 50, Medicham 52 | Hitmonchan |
| MADELINE_1 | Roselia, Camerupt | Starmie 48, Walrein 48, Camerupt 48 | Starmie, Walrein |
| JENNY_1 | Luvdisc, Wailmer, Starmie | Luvdisc 49, Alomomola 49 | Alomomola |
| DIANA_1 | Breloom, Vileplume, Altaria | Vileplume 48, Altaria 48 | – |
| AMY_AND_LIV_1 | Plusle, Minun | Plusle 50, Minun 50 | – |
| ERNEST_1 | Pelipper, Machoke, Tentacruel | Tentacruel 48, Wailord 48, Machamp 48 | Wailord |
| EDWIN_1 | Ludicolo, Shiftry | Ludicolo 49, Shiftry 49 | – |
| ISAAC_1 | Loudred, Linoone, Lairon, Mightyena, Swellow, Hariyama | Whismur 50, Zigzagoon 50, Aron 50, Poochyena 50, Taillow 50, Makuhita 50 | – |
| LYDIA_1 | Pelipper, Breloom, Azumarill, Roselia, Delcatty, Seaking | Wingull 50, Shroomish 50, Azurill 50, Budew 50, Skitty 50, Goldeen 50 | – |
| JACKSON_1 | Kecleon, Breloom | Seviper 49, Unfezant 49, Slaking 49 | Seviper, Unfezant, Slaking |
| CATHERINE_1 | Bellossom, Roselia | Breloom 49, Raichu 49, Excadrill 49 | Breloom, Raichu, Excadrill |
| HALEY_1 | Swellow, Lombre, Breloom | Whimsicott 47, Breloom 47, Ludicolo 47 | Whimsicott |
| JAMES_1 | Surskit, Ninjask, Dustox, Ninjask | Masquerain 46, Ariados 46, Ninjask 46, Ledian 46 | Ariados, Ledian |
| TRENT_1 | Graveler, Graveler, Graveler, Golem | Golem 48, Golem 48, Golem 48 | – |
| JOHN_AND_JAY_1 | Medicham, Hariyama | Medicham 58, Hariyama 58 | – |

(`python3 tools/hack/trainers/oras/match_oras.py --tiers` prints this table.) No ORAS rematch data for the other
16 trainers with tiers: Sawyer, Gabrielle, Thalia, Fernando, Jeffrey, Jacki, Abigail, Maria, Pablo, Katelyn,
Kira & Dan, Lila & Roy, Andres, Cory, Cristin (no ORAS counterpart) and Koji (one team in ORAS). Gabby & Ty's
six ORAS battles are the same families as their six Emerald ones (ORAS's last one has Magnezone); unchanged.

**`oras-first`** (D-172): an ORAS first-battle team is used when it has more evolution families (from the species
pool) than the trainer's vanilla Emerald team – 29 trainers; Gilbert and Cole already had exactly the ORAS
species, so 27 change. The ORAS roster is scaled to the slot's level (level-up evolutions only: Cacnea →
Cacturne, Zubat → Golbat), filled up with the current team (Emerald families first), the ORAS ace last.

| Trainer | Seg. | Emerald team | ORAS first team | New team (ace last) |
|---|---|---|---|---|
| WARREN | S7 | Graveler, Ludicolo | Lairon 38, Manectric 38, Alakazam 38 | Lairon 39, Manectric 40, Golem 40, Ludicolo 41, Alakazam 41 |
| TASHA | S7 | Shuppet | Shuppet 34, Xatu 34 | Banette 38, Solrock 38, Sableye 38, Xatu 39 |
| BRIANNA | S8 | Seaking | Clamperl 41, Corsola 41 | Clamperl 45, Lanturn 44, Golduck 44, Seaking 46, Corsola 46 |
| TIFFANY | S8 | Carvanha, Sharpedo | Golduck 41, Wailord 41 | Golduck 44, Relicanth 45, Gyarados 45, Sharpedo 46, Wailord 46 |
| JEROME | S6 | Tentacruel | Tentacool 25, Pelipper 25 | Tentacruel 32, Wailmer 32, Crawdaunt 32, Pelipper 33 |
| DEAN | S7 | Carvanha, Wingull, Carvanha | Wailmer 35, Staryu 36, Golduck 37 | Wailmer 37, Staryu 38, Sharpedo 39, Golduck 39 |
| FRANKLIN | S7 | Sealeo | Whiscash 38, Seadra 36 | Seadra 40, Sealeo 39, Pelipper 39, Whiscash 41 |
| JACK | S7 | Gyarados | Staryu 36, Sharpedo 38 | Staryu 40, Tentacruel 40, Gyarados 41, Sharpedo 41 |
| HITOSHI | S7 | Machop, Machoke | Machoke 37, Heracross 39 | Machoke 40, Hitmonchan 39, Hariyama 39, Heracross 41 |
| LARRY | S4 | Nuzleaf | Taillow 16, Zubat 18 | Swellow 22, Nuzleaf 23, Golbat 23 |
| BRENT | S6 | Surskit | Masquerain 28, Ninjask 28 | Masquerain 31, Volbeat 31, Pinsir 31, Ninjask 32 |
| DEREK | S3 | Dustox, Beautifly | Nincada 15, Dustox 15, Beautifly 15 | Ninjask 20, Dustox 20, Beautifly 21 |
| VIRGIL | S7 | Ralts | Kadabra 40, Girafarig 40 | Kadabra 40, Claydol 39, Gardevoir 41, Girafarig 41 |
| WILLIAM | S7 | Ralts, Ralts, Kirlia | Staryu 35, Grumpig 35 | Staryu 37, Xatu 37, Gardevoir 38, Grumpig 38 |
| EDDIE | S3 | Zigzagoon, Zigzagoon | Nincada 14, Geodude 14 | Ninjask 21, Linoone 22, Geodude 22 |
| TIMMY | S3 | Aron, Electrike | Poochyena 12, Aron 13, Electrike 14 | Poochyena 17, Aron 17, Electrike 18 |
| AARON | S7 | Bagon | Shelgon 39, Kingdra 39 | Shelgon 40, Vibrava 39, Dragonair 40, Kingdra 41 |
| CHESTER | S6 | Taillow, Swellow | Swablu 26, Swellow 28 | Swablu 31, Noctowl 31, Pelipper 31, Swellow 32 |
| MISSY | S6 | Goldeen | Wingull 24, Barboach 24, Wailmer 24 | Pelipper 32, Whiscash 32, Seaking 33, Wailmer 33 |
| GRACE | S7 | Marill | Wailmer 36, Azumarill 38 | Wailmer 36, Luvdisc 35, Pelipper 35, Azumarill 37 |
| SHARON | S7 | Seaking | Clamperl 38, Seaking 36 | Seaking 37, Luvdisc 36, Pelipper 36, Clamperl 38 (Deep Sea Tooth) |
| LINDA | S7 | Horsea, Seadra | Pelipper 37, Seaking 37 | Pelipper 39, Lanturn 40, Seadra 41, Seaking 41 |
| EDMOND | S2 | Wingull | Wingull 12, Machop 14 | Wingull 15, Machop 16 |
| SEBASTIAN | S8 | Cacturne | Cacnea 16, Aron 18 | Cacturne 43, Breloom 42, Tropius 43, Aggron 44 |
| DOUG | S6 | Nincada, Ninjask | Volbeat 26, Illumise 28 | Volbeat 31, Pinsir 31, Ninjask 32, Illumise 32 |
| ROGER | S7 | Magikarp, Magikarp, Gyarados | Wailmer 37, Sharpedo 37 | Wailmer 38, Whiscash 37, Gyarados 39, Sharpedo 39 |
| TISHA | S7 | Chinchou | Luvdisc 36, Corsola 36, Azumarill 36 | Luvdisc 38, Corsola 39, Lanturn 40, Azumarill 40 |

**Elite Four** (D-173, D-174): their ORAS post-game rematch rosters, moves from Serebii's ORAS sets made into
full competitive sets (EVs, natures, items; Full Restores as before).

| | First battle (S9, no Mega) | Post-game rematch (ORAS levels, Mega ace; not in the ROM yet) |
|---|---|---|
| Sidney | Scrafty, Shiftry, Sharpedo, Zoroark, Mandibuzz 54, Absol 55 | same, Lv 70, Mega Absol 72 |
| Phoebe | Banette, Mismagius 54, Drifblim, Chandelure, Sableye 55, Dusknoir 56 | Banette … Dusknoir 71, Mega Sableye 73 |
| Glacia | Abomasnow, Beartic 55, Froslass, Vanilluxe, Glalie 56, Walrein 57 | Abomasnow … Walrein 72, Mega Glalie 74 |
| Drake | Altaria, Dragalge 56, Kingdra, Flygon, Haxorus 57, Salamence 58 | Altaria … Haxorus 73, Mega Salamence 75 |

The rematch needs four trainer ids (`TRAINER_SIDNEY_REMATCH` …) and the Elite Four rooms (or a game-clear
variant rule) to pick them after the Champion; then `splice_party.py --append tools/hack/trainers/oras/elite_four_rematch.party`.
**Wallace** keeps his team: ORAS has no Champion Wallace, and the one ORAS Wallace battle outside his gym
("Sootopolitan Wallace", Serebii's Route 131 page) uses exactly the Emerald Champion roster he already has
(Wailord, Tentacruel, Ludicolo, Whiscash, Gyarados, Milotic).

## Gen 4–9 swaps (round 1)

Feedback 1.28, D-195: **122 of the 434 generic trainers** (first battles with the route or gym role – not rivals,
Aster, Nerine, Zinnia, leaders, the Elite Four, Wallace, Steven, admins, bosses, Wally, partners, nor the Magma /
Aqua grunts) swap one Pokémon for a Gen 4–9 species of their class and area, in every rematch tier (214 blocks);
Timothy, Wilton and Nicolas swap two. Batch: `batch_gen49.party` (spliced into `src/data/trainers.party`); the swaps
per block are in `gen49_swaps.json`, and the trainer table below shows them after the source (`enhanced + Nymble`).

- **Which species**: one that lives where the trainer stands ([hack_wild.md](hack_wild.md)) or fits the class
  (Rustboro's rock gym: Nacli, Rolycoly; Lavaridge's kindlers: Litleo, Sizzlipede, Salandit, Carkol; Fortree's bird
  keepers: Staraptor, Hawlucha, Corvisquire, Swanna; Mossdeep's psychics: Bronzong, Drifblim; swimmers: Finizen,
  Alomomola, Mareanie, Clauncher, Skrelp, Floatzel). Rematch trainers take the Gen 4–9 families of **their own ORAS
  roster** where ORAS has one (ORAS data above): Haley Whimsicott, Jerry Bisharp, Cindy and Winston Pyroar, Dalton
  Chatot, Benjamin Klinklang, Ethan Skuntank, Shelby Lucario, Wilton Talonflame + Haxorus, Brooke Purugly, Dusty
  Tyrantrum, Tony Jellicent, Timothy Hawlucha + Conkeldurr, Jackson Unfezant, Catherine Excadrill, Valerie
  Mismagius, Jessica Krookodile, Jenny Alomomola, Isaiah Floatzel, Robert Staraptor, Walter Stoutland, Nicolas
  Noivern + Druddigon.
- **What stays**: the slot, level, IVs, EVs (Atk / SpA swapped for a special attacker), nature (mirrored the same
  way), party size, header, AI; the ace (last Pokémon) except Jerry's, whose ORAS team has Bisharp for Banette.
  Held items carry over; a type booster becomes the new species' booster, set-specific items (Flame Orb, White
  Herb, Choice items, Light Clay …) become a berry / Leftovers or a Life Orb from S7. The ability (where the block
  names one) is the species' first regular ability that does something in battle (no hidden abilities; Cutiefly
  gets Shield Dust, not Honey Gather).
- **Stage**: the one its level allows by level-up (Starly → Staravia 14 → Staraptor 34); stone / trade / friendship
  evolutions at a set level (Whimsicott, Lucario and Mismagius from 30, Tsareena from 29, Chandelure from 50,
  Conkeldurr and Trevenant only post-game).
- **Rematch tiers**: the same slot's family is swapped in every tier, so the new species grows tier to tier
  (Benjamin: Klink in tier 1 for a Magnemite, then Klang / Klinklang for his Ninjask; Dalton's first Magneton line
  becomes Chatot); families introduced in later tiers are swapped from that tier on (Wilton, Brooke, Cindy,
  Winston). `check_tiers.py` stays at 0 errors, 0 warnings.
- **Moves**: level-up moves (plus Emerald's TMs from S4), picked for STAB of each type, one coverage move and a
  status or set-up move (Swords Dance / Nasty Plot / Calm Mind / Bulk Up, Toxic, Thunder Wave …); nothing over
  90 power before S4, no OHKO, self-KO, recharge or two-turn moves. `check_party.py --caps --proc`: 0 errors, the
  13 warnings of before (story teams).

## Battle Frontier legends (round 1 follow-up)

Post-game, on `BattleFrontier_OutsideEast` (D-225 – D-229). Red and Blue: their **Pokémon World Tournament** teams
from Serebii's Champions Tournament page (`tools/hack/trainers/pwt/scrape_pwt.py` → `pwt_champions.json`; species,
items and moves as listed, the Megas' stones instead of a Focus Sash, abilities / natures / EVs chosen here). Wes: the
playtester's Colosseum team (Espeon, Umbreon, Raikou, Entei, Suicune, Ho-Oh) with sets written here. Levels 82–83,
the ace 85 (the post-game's top fights), 3 Full Restores, the Elite Four rematch AI. Each also has a three-Pokémon
**tag team** (`TRAINER_*_FRONTIER_MULTI`, `Multi Party: Half`, the same team as his `PARTNER_*`) for the LEGENDS' TAG
multi battle. Blocks: `tools/hack/trainers/pwt/batch_frontier_legends.party` (+ `.sources.json`: `pwt` /
`colosseum`), spliced with `splice_party.py --append`; the partners are at the end of `src/data/battle_partners.party`.

| Id | Team (ace last) |
|---|---|
| `TRAINER_WES_FRONTIER` | Espeon, Umbreon, Raikou, Entei, Suicune, Ho-Oh (Lv 82–85) |
| `TRAINER_RED_FRONTIER` | Venusaur, Blastoise, Pikachu, Snorlax, Lapras, Charizard @ Charizardite X (Lv 82–85) |
| `TRAINER_BLUE_FRONTIER` | Aerodactyl, Exeggutor, Gyarados, Arcanine, Machamp, Alakazam @ Alakazite (Lv 82–85) |
| `TRAINER_WES_FRONTIER_MULTI` / `PARTNER_WES` | Espeon (Reflect, Light Screen), Umbreon, Ho-Oh |
| `TRAINER_RED_FRONTIER_MULTI` / `PARTNER_RED` | Pikachu (Fake Out), Venusaur, Charizard @ Charizardite X |
| `TRAINER_BLUE_FRONTIER_MULTI` / `PARTNER_BLUE` | Arcanine, Gyarados (two Intimidates), Alakazam @ Alakazite |

Lance (round 1 follow-up 25, D-262) waits in the Draconid village, not at the Frontier, but his team follows the
same rules: his PWT team from the same page, Dragonite's Focus Sash turned into the Dragoninite and Dragonite moved
last; levels 82–84, the ace 86; 3 Full Restores, the same AI. No tag team.

| Id | Team (ace last) |
|---|---|
| `TRAINER_LANCE_DRACONID` | Salamence, Kingdra, Hydreigon, Haxorus, Flygon, Dragonite @ Dragoninite (Lv 82–86) |

### Second pass (round 1 follow-up, feedback 1.40, D-240 – D-242)

"Make sure trainers are getting Gen 4–9 Pokémon too to spice things up." A **Gen 4–9 Pokémon** here is a species
of Gens 4–9 that is not in the Hoenn Pokédex (Roserade, Gallade, Magnezone, Dusknoir … are Hoenn species).
`python3 tools/hack/trainers/gen49.py --coverage` counts them and checks the rules below:

| Segment | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | POST | All |
|---|---|---|---|---|---|---|---|---|---|---|---|
| Generic first battles with one | 17/26 | 14/22 | 26/43 | 39/64 | 12/19 | 43/71 | 85/140 | 11/14 | 15/24 | 7/11 | **269/434 (62%)** |
| Blocks with their rematch tiers | 17/26 | 14/22 | 26/43 | 39/64 | 12/19 | 64/116 | 122/219 | 40/76 | 18/30 | 37/75 | 389/690 |

(D-195: 122 trainers, 28%.) Grunts: 44 of 49.

- **About 60% of the generic trainers** (D-240), 60–65% in every segment (S8 79%: the Sootopolis Gym is most of
  it), in their first battle and every rematch tier; Wilton and Brooke, who had one only from tier 2, now have it
  in tier 1 too (Cindy's and Winston's one-Pokémon first battles keep their Zigzagoon). Picked like D-195: the
  area's wild newcomers ([hack_wild.md](hack_wild.md)), the class's theme, the trainer's ORAS roster where it has
  one (Albert Sigilyph, Thomas Braviary, Leonard Floatzel, Dusty Aurorus), the ace kept.
- **Two from S5 on**: every block from S5 on with 4+ Pokémon that has a Gen 4–9 Pokémon has two – the new
  trainers, D-195's trainers and every rematch tier. In a rematch chain the second one comes in with the first big
  tier and grows from tier to tier (Calvin's Breloom slot becomes Gumshoos from tier 2), taken from a family that
  the earlier tiers don't have, so `check_tiers.py` stays at 0 warnings.
- **Gym trainers** (D-241): all 57 have one of their gym's type, the Petalburg, Fortree, Mossdeep and Sootopolis
  trainers two – Rustboro rock (Nacli, Rolycoly, Roggenrola), Dewford fighting (Sawk, Scraggy, Clobbopus, Throh,
  Croagunk, Timburr), Mauville electric (Pawmo, Luxio, Tadbulb, Joltik; Vivian the Battle Girl gets
  electric/fighting Pawmo), Lavaridge fire (Litleo, Sizzlipede, Salandit, Carkol, Larvesta, Heatmor, Fletchinder;
  Danielle's D-195 Gurdurr became Heatmor), Petalburg normal (Gumshoos, Bewear, Greedent, Diggersby, Glameow,
  Bouffalant, Chatot, Herdier), Fortree flying (Staraptor, Toucannon, Hawlucha, Unfezant, Swanna, Talonflame,
  Chatot, Corvisquire, Kilowattrel, Sigilyph), Mossdeep psychic (Bronzong, Musharna, Swoobat, Sigilyph, Bruxish –
  the only psychic lines in the species pool, so they repeat), Sootopolis water.
- **Grunts** (D-242, reversing D-195's exclusion): one each, never the Poochyena / Zubat / Numel / Carvanha lines
  and never the ace. Magma: fire / ground / rock (Salazzle, Excadrill, Heatmor, Coalossal, Gigalith, Mudsdale,
  Centiskorch, Hippowdon, Pyroar, Garganacl, Krookodile, Sandaconda, Rampardos, Glimmora, Talonflame); Aqua: water /
  dark (Thievul, Barraskewda, Kilowattrel, Floatzel, Zoroark, Clawitzer, Skuntank, Lumineon, Toxapex, Palafin,
  Jellicent, Scrafty, Barbaracle, Drednaw). The five grunts whose teams are only those lines keep them (Museum,
  both Mt. Chimney grunts, Jagged Pass, Aqua Hideout 8). Purrloin is not in the species pool, so the Aqua dark
  types are Thievul, Skuntank, Scrafty and Zoroark.
- **Strength**: the new Pokémon's stage has at least 80% of the base stat total of the one it replaces (no Skrelp
  at 39, Goomy at 35 or Larvesta at 43), except a line that grows through the rematch tiers (Amaura → Aurorus,
  Axew → Fraxure, Corvisquire → Corviknight) and Wishiwashi (Schooling).
- **Moves** as D-195, now written by `gen49.py`; moves over 90 power are held back before S7 (the batches use them
  for 3–4% of moves in S4–S6). Stones, friendship and other evolutions at set levels (`SET_LEVEL`: Lucario,
  Swoobat, Whimsicott, Lilligant, Musharna, Pawmot, Polteageist 30, Tsareena 29, Grapploct and Frosmoth 35,
  Chandelure 50).
- **Evolution levels** (D-216's warnings): the generic trainers 1–2 levels under the new trade-evolution levels are
  pre-evolved – Kira & Dan's Huntail / Gorebyss and Thalia's Gorebyss (tiers 1–2) are Clamperl holding the Deep Sea
  Tooth / Scale they will evolve with, Thalia's tier 3 and Aaron's Kingdra are Seadra (Aaron, a Dragon Tamer, gets
  Fraxure and Druddigon beside it), Nob's Machamp is a Machoke, Trent's and Sawyer's Golem a Graveler.
  `check_party.py --caps --proc`: 0 errors, 13 warnings (the story and leader teams); `check_tiers.py` 0 / 0.

**Workflow.** `tools/hack/trainers/gen49_plan.py` lists every swap (trainer → the family that makes way → the new
line, per tier where needed) and the pre-evolutions; `gen49.py` writes the Pokémon from it into
`batch_gen49.party` (every block with a swap or a fix) and `gen49_swaps.json`, then `splice_party.py
tools/hack/trainers/batch_gen49.party`. A swap whose family is already in the block is skipped, so the script can run
again on the spliced file (it changes nothing); `-v` prints every swap, `--moves Clawitzer 40 S7` the set the rules
give a species. `check_party.py` now resolves species aliases before it takes a wild species' family into the pool
(Sinistea → Polteageist).

## Trainer table
<!-- generated by tools/hack/trainers/report.py -->

### S1 (cap 15) – Draconid Pass to Roxanne

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| CINDY_1 | Route104 | route | 1 | 9–9 | Zigzagoon 9 | emerald-rematch |
| WINSTON_1 | Route104 | route | 1 | 10–10 | Zigzagoon 10 | emerald-rematch |
| ROXANNE_1 | RustboroCity_Gym | leader | 4 | 12–15 | Nosepass 15 | emerald-rematch |
| JERRY_1 | Route116 | route | 2 | 10–11 | Pawniard 11 | emerald-rematch + Pawniard |
| KAREN_1 | Route116 | route | 2 | 10–11 | Whismur 11 | emerald-rematch |
| CALVIN_1 | Route102 | route | 3 | 5–6 | Poochyena 6 | emerald-rematch + Skwovet |
| BILLY | Route104 | route | 2 | 7–8 | Seedot 8 | enhanced + Pikipek |
| JOSH | RustboroCity_Gym | gym | 2 | 11–12 | Aron 12 | enhanced + Nacli |
| TOMMY | RustboroCity_Gym | gym | 2 | 11–12 | Geodude 12 | enhanced + Roggenrola |
| JOEY | Route116 | route | 2 | 10–11 | Machop 11 | enhanced + Starly |
| ALLEN | Route102 | route | 2 | 6–7 | Taillow 7 | enhanced |
| IVAN | Route104 | route | 3 | 9–11 | Tentacool 11 | enhanced |
| GINA_AND_MIA_1 | Route104 | route | 2 | 10–11 | Lotad 11 | enhanced |
| BRENDAN_RUSTBORO | RustboroCity | route | 4 | 10–13 | Treecko 13 | story |
| MAY_ROUTE_103 | Route103 | route | 1 | 5–5 | Torchic 5 | story |
| MARC | RustboroCity_Gym | gym | 2 | 12–13 | Onix 13 | enhanced + Rolycoly |
| TIANA | Route102 | route | 2 | 6–7 | Shroomish 7 | enhanced + Skwovet |
| HALEY_1 | Route104 | route | 3 | 10–11 | Shroomish 11 | emerald-rematch + Cottonee |
| JANICE | Route116 | route | 2 | 10–11 | Marill 11 | enhanced |
| RICK | Route102 | route | 2 | 5–6 | Wurmple 6 | enhanced + Kricketot |
| LYLE | PetalburgWoods | route | 3 | 8–9 | Cascoon 9 | enhanced + Nymble |
| JOSE | Route116 | route | 2 | 10–11 | Beautifly 11 | enhanced |
| JAMES_1 | PetalburgWoods | route | 3 | 9–10 | Dustox 10 | emerald-rematch + Combee |
| CLARK | Route116 | route | 2 | 11–12 | Geodude 12 | enhanced + Timburr |
| DAWSON | Route116 | route | 2 | 11–12 | Poochyena 12 | enhanced + Lillipup |
| SARAH | Route116 | route | 2 | 11–12 | Zigzagoon 12 | enhanced |
| DARIAN | Route104 | route | 2 | 7–8 | Tentacool 8 | enhanced + Chewtle |
| DEVAN | Route116 | route | 2 | 11–12 | Geodude 12 | enhanced + Drilbur |
| JOHNSON | Route116 | route | 2 | 11–12 | Shroomish 12 | enhanced + Bunnelby |
| ASTER_PASS_DEINO | DraconidPass | route | 1 | 5–5 | Dreepy 5 | story |
| ASTER_PASS_DREEPY |  | route | 1 | 5–5 | Jangmo-o 5 | story |
| ASTER_PASS_JANGMO_O |  | route | 1 | 5–5 | Deino 5 | story |
| NERINE_PETALBURG_WOODS_DEINO | PetalburgWoods | route | 2 | 9–10 | Jangmo-o 10 | story |
| NERINE_PETALBURG_WOODS_DREEPY |  | route | 2 | 9–10 | Deino 10 | story |
| NERINE_PETALBURG_WOODS_JANGMO_O |  | route | 2 | 9–10 | Dreepy 10 | story |

### S2 (cap 20) – Rusturf Tunnel, Dewford, Brawly

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| LOLA_1 | Route109 | route | 2 | 15–16 | Marill 16 | emerald-rematch |
| RICKY_1 | Route109 | route | 2 | 15–16 | Zigzagoon 16 | emerald-rematch |
| SIMON | Route109_SeashoreHouse | route | 2 | 15–16 | Marill 16 | enhanced |
| TAKAO | DewfordTown_Gym | gym | 2 | 16–17 | Makuhita 17 | enhanced + Sawk |
| NOB_1 | Route115 | route | 2 | 16–17 | Machop 17 | emerald-rematch |
| BRAWLY_1 | DewfordTown_Gym | leader | 4 | 17–20 | Makuhita 20 | emerald-rematch |
| ELLIOT_1 | Route106 | route | 3 | 13–14 | Tentacool 14 | emerald-rematch |
| NED | Route106 | route | 2 | 12–13 | Tentacool 13 | enhanced + Arrokuda |
| JOCELYN | DewfordTown_Gym | gym | 3 | 17–18 | Meditite 18 | enhanced + Croagunk |
| LAURA | DewfordTown_Gym | gym | 2 | 16–17 | Meditite 17 | enhanced + Scraggy |
| CYNDY_1 | Route115 | route | 2 | 16–17 | Makuhita 17 | emerald-rematch |
| HUEY | Route109 | route | 2 | 16–17 | Machop 17 | enhanced + Wattrel |
| EDMOND | Route109 | route | 2 | 15–16 | Machop 16 | oras-first |
| DWAYNE | Route109_SeashoreHouse | route | 3 | 16–17 | Machop 17 | enhanced + Finneon |
| HECTOR | Route115 | route | 2 | 16–17 | Zangoose 17 | enhanced |
| BRENDEN | DewfordTown_Gym | gym | 2 | 16–17 | Machop 17 | enhanced + Clobbopus |
| LILITH | DewfordTown_Gym | gym | 2 | 17–18 | Meditite 18 | enhanced + Throh |
| CRISTIAN | DewfordTown_Gym | gym | 2 | 17–18 | Makuhita 18 | enhanced + Timburr |
| MIKE_2 | RusturfTunnel | route | 3 | 14–15 | Geodude 15 | enhanced + Roggenrola |
| JOHANNA | Route109_SeashoreHouse | route | 2 | 16–17 | Goldeen 17 | enhanced + Glameow |
| HAILEY | Route109 | route | 2 | 15–16 | Marill 16 | enhanced + Finizen |
| CHANDLER | Route109 | route | 2 | 15–16 | Tentacool 16 | enhanced + Buizel |
| MARLENE | Route115 | route | 2 | 15–16 | Spoink 16 | enhanced + Woobat |
| MAY_RUSTBORO | Route104 | route | 3 | 15–17 | Combusken 17 | story |
| NERINE_RUSTURF_DEINO_CHARMANDER | RusturfTunnel | route | 4 | 14–17 | Jangmo-o 17 | story |
| NERINE_RUSTURF_DEINO_TOTODILE |  | route | 4 | 14–17 | Jangmo-o 17 | story |
| NERINE_RUSTURF_DEINO_TREECKO |  | route | 4 | 14–17 | Jangmo-o 17 | story |
| NERINE_RUSTURF_DREEPY_CHARMANDER |  | route | 4 | 14–17 | Deino 17 | story |
| NERINE_RUSTURF_DREEPY_TOTODILE |  | route | 4 | 14–17 | Deino 17 | story |
| NERINE_RUSTURF_DREEPY_TREECKO |  | route | 4 | 14–17 | Deino 17 | story |
| NERINE_RUSTURF_JANGMO_O_CHARMANDER |  | route | 4 | 14–17 | Dreepy 17 | story |
| NERINE_RUSTURF_JANGMO_O_TOTODILE |  | route | 4 | 14–17 | Dreepy 17 | story |
| NERINE_RUSTURF_JANGMO_O_TREECKO |  | route | 4 | 14–17 | Dreepy 17 | story |
| BRENDAN_ROUTE_104 | Route104 | route | 4 | 17–19 | Grovyle 19 | story |

### S3 (cap 25) – Slateport, Route 110, Mauville, Wattson

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_MUSEUM_1 | SlateportCity_OceanicMuseum_2F | grunt | 2 | 17–18 | Carvanha 18 | enhanced |
| DAISY | Route103 | route | 3 | 17–18 | Roselia 18 | enhanced + Morelull |
| ROSE_1 | Route118 | route | 3 | 20–22 | Roselia 22 | emerald-rematch + Petilil |
| KIRK | MauvilleCity_Gym | gym | 3 | 21–22 | Electrike 22 | enhanced + Pawmo |
| SHAWN | MauvilleCity_Gym | gym | 3 | 22–23 | Magnemite 23 | enhanced + Luxio |
| DALTON_1 | Route118 | route | 2 | 21–22 | Loudred 22 | emerald-rematch + Chatot |
| DEREK | Route117 | route | 3 | 20–21 | Beautifly 21 | oras-first + Cutiefly |
| EDWARD | Route110 | route | 2 | 19–20 | Kadabra 20 | enhanced + Munna |
| JACLYN | Route110 | route | 3 | 20–21 | Kadabra 21 | enhanced + Sigilyph |
| WATTSON_1 | MauvilleCity_Gym | leader | 5 | 22–25 | Manectric 25 | emerald-rematch |
| ANNA_AND_MEG_1 | Route117 | route | 2 | 18–19 | Makuhita 19 | emerald-rematch |
| MIGUEL_1 | Route103 | route | 2 | 18–19 | Skitty 19 | emerald-rematch |
| ISABEL_1 | Route110 | route | 2 | 17–18 | Minun 18 | emerald-rematch |
| BEN | MauvilleCity_Gym | gym | 3 | 21–22 | Linoone 22 | enhanced + Tadbulb |
| EDDIE | Route110_TrickHousePuzzle1 | route | 3 | 21–22 | Geodude 22 | oras-first |
| TIMMY | Route110 | route | 3 | 17–18 | Electrike 18 | oras-first + Nickit |
| ANDREW | Route103 | route | 3 | 18–20 | Gyarados 20 | enhanced + Finneon |
| DALE | Route110 | route | 4 | 19–21 | Wailmer 21 | enhanced + Finneon |
| WADE | Route118 | route | 2 | 20–21 | Carvanha 21 | enhanced + Arrokuda |
| JACOB | Route110 | route | 3 | 20–21 | Magnemite 21 | enhanced + Pawmo |
| ANTHONY | Route110 | route | 2 | 21–22 | Magnemite 22 | enhanced + Luxio |
| BENJAMIN_1 | Route110 | route | 2 | 20–21 | Magnemite 21 | emerald-rematch + Klink |
| ABIGAIL_1 | Route110 | route | 2 | 21–22 | Magnemite 22 | emerald-rematch |
| JASMINE | Route110 | route | 3 | 20–21 | Magnemite 21 | enhanced + Blitzle |
| DYLAN_1 | Route117 | route | 2 | 18–19 | Doduo 19 | emerald-rematch |
| MARIA_1 | Route117 | route | 2 | 19–20 | Doduo 20 | emerald-rematch |
| AMY_AND_LIV_1 | Route103 | route | 2 | 18–19 | Minun 19 | emerald-rematch |
| EDWIN_1 | Route110 | route | 2 | 19–20 | Nuzleaf 20 | emerald-rematch |
| MAY_ROUTE_110 | Route110 | route | 4 | 22–24 | Combusken 24 | story |
| ISAAC_1 | Route117 | route | 4 | 19–20 | Loudred 20 | emerald-rematch |
| LYDIA_1 | Route117 | route | 4 | 20–22 | Roselia 22 | emerald-rematch |
| SALLY | Route110_TrickHousePuzzle1 | route | 2 | 20–21 | Gloom 21 | enhanced |
| ROBIN | Route110_TrickHousePuzzle1 | route | 3 | 20–21 | Azumarill 21 | enhanced + Glameow |
| VIVIAN | MauvilleCity_Gym | gym | 3 | 21–22 | Meditite 22 | enhanced + Pawmo |
| WALLY_MAUVILLE | MauvilleCity | route | 1 | 19–19 | Ralts 19 | story |
| KALEB | Route110 | route | 2 | 17–18 | Plusle 18 | enhanced |
| JOSEPH | Route110 | route | 3 | 19–20 | Electrike 20 | enhanced |
| ALYSSA | Route110 | route | 2 | 21–22 | Magnemite 22 | enhanced |
| MARCOS | Route103 | route | 2 | 17–18 | Voltorb 18 | enhanced |
| RHETT | Route103 | route | 2 | 17–18 | Makuhita 18 | enhanced + Timburr |
| DEANDRE | Route118 | route | 3 | 20–21 | Linoone 21 | enhanced + Luxio |
| PETE | Route103 | route | 2 | 19–20 | Tentacool 20 | enhanced + Wattrel |
| ISABELLE | Route103 | route | 2 | 19–20 | Azumarill 20 | enhanced + Finizen |
| MELINA | Route117 | route | 2 | 20–21 | Doduo 21 | enhanced + Herdier |
| BRANDI | Route117 | route | 2 | 20–21 | Kirlia 21 | enhanced |
| AISHA | Route117 | route | 2 | 19–20 | Meditite 20 | enhanced + Stufful |
| ANGELO | MauvilleCity_Gym | gym | 3 | 21–22 | Volbeat 22 | enhanced + Joltik |
| NERINE_SLATEPORT_DEINO_CHARMANDER | SlateportCity_OceanicMuseum_2F | route | 4 | 21–24 | Jangmo-o 24 | story |
| NERINE_SLATEPORT_DEINO_TOTODILE |  | route | 4 | 21–24 | Jangmo-o 24 | story |
| NERINE_SLATEPORT_DEINO_TREECKO |  | route | 4 | 21–24 | Jangmo-o 24 | story |
| NERINE_SLATEPORT_DREEPY_CHARMANDER |  | route | 4 | 21–24 | Deino 24 | story |
| NERINE_SLATEPORT_DREEPY_TOTODILE |  | route | 4 | 21–24 | Deino 24 | story |
| NERINE_SLATEPORT_DREEPY_TREECKO |  | route | 4 | 21–24 | Deino 24 | story |
| NERINE_SLATEPORT_JANGMO_O_CHARMANDER |  | route | 4 | 21–24 | Dreepy 24 | story |
| NERINE_SLATEPORT_JANGMO_O_TOTODILE |  | route | 4 | 21–24 | Dreepy 24 | story |
| NERINE_SLATEPORT_JANGMO_O_TREECKO |  | route | 4 | 21–24 | Dreepy 24 | story |

### S4 (cap 30) – Routes 111-114, Mt. Chimney, Jagged Pass, Flannery

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| SAWYER_1 | MtChimney | route | 3 | 25–26 | Graveler 26 | emerald-rematch + Carkol |
| GABBY_AND_TY_1 |  | route | 4 | 22–23 | Loudred 23 | enhanced |
| GABBY_AND_TY_2 |  | route | 4 | 26–27 | Loudred 27 | enhanced |
| WILTON_1 | Route111 | route | 3 | 23–24 | Hariyama 24 | emerald-rematch + Fletchinder |
| BROOKE_1 | Route111 | route | 3 | 23–24 | Roselia 24 | emerald-rematch + Glameow |
| MELISSA | MtChimney | route | 3 | 25–26 | Azumarill 26 | enhanced + Ducklett |
| SHEILA | MtChimney | route | 3 | 25–26 | Breloom 26 | enhanced + Ribombee |
| SHIRLEY | MtChimney | route | 3 | 25–26 | Ponyta 26 | enhanced + Salandit |
| STEVE_1 | Route114 | route | 3 | 24–25 | Rhyhorn 25 | emerald-rematch |
| GRUNT_MT_CHIMNEY_1 | MtChimney | grunt | 3 | 25–26 | Mightyena 26 | enhanced |
| DAISUKE | Route111 | route | 3 | 22–23 | Machop 23 | enhanced + Riolu |
| COLE | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Numel 27 | enhanced + Larvesta |
| JEFF | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Slugma 27 | enhanced + Litleo |
| AXLE | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Numel 27 | enhanced + Sizzlipede |
| JACE | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Slugma 27 | enhanced + Salandit |
| KEEGAN | LavaridgeTown_Gym_1F | gym | 3 | 27–28 | Slugma 28 | enhanced + Carkol |
| BERNIE_1 | Route114 | route | 3 | 24–25 | Pelipper 25 | emerald-rematch |
| LARRY | Route112 | route | 3 | 22–23 | Golbat 23 | oras-first + Trumbeak |
| SHANE | Route114 | route | 3 | 24–25 | Nuzleaf 25 | enhanced + Skiddo |
| ETHAN_1 | JaggedPass | route | 3 | 26–27 | Linoone 27 | emerald-rematch + Stunky |
| AUTUMN | JaggedPass | route | 3 | 26–27 | Breloom 27 | enhanced + Steenee |
| TRAVIS | Route111 | route | 3 | 21–22 | Sandslash 22 | enhanced + Diggersby |
| FLANNERY_1 | LavaridgeTown_Gym_1F | leader | 5 | 27–30 | Torkoal 30 | emerald-rematch |
| TED | Route110_TrickHousePuzzle2 | route | 3 | 22–23 | Kirlia 23 | enhanced |
| PAUL | Route110_TrickHousePuzzle2 | route | 3 | 22–23 | Gloom 23 | enhanced |
| GEORGIA | Route110_TrickHousePuzzle2 | route | 3 | 22–23 | Breloom 23 | enhanced |
| VICTOR | Route111 | route | 3 | 21–22 | Swellow 22 | enhanced |
| VICTORIA | Route111 | route | 3 | 22–23 | Roselia 23 | enhanced |
| VICKY | Route111 | route | 3 | 23–24 | Meditite 24 | enhanced |
| SHELBY_1 | MtChimney | route | 3 | 25–26 | Hariyama 26 | emerald-rematch + Riolu |
| JAYLEN | Route113 | route | 3 | 23–24 | Trapinch 24 | enhanced |
| DILLON | Route113 | route | 3 | 23–24 | Aron 24 | enhanced + Carkol |
| CLAUDE | Route114 | route | 3 | 24–25 | Gyarados 25 | enhanced + Buizel |
| NOLAN | Route114 | route | 3 | 24–25 | Barboach 25 | enhanced + Drednaw |
| LAO_1 | Route113 | route | 3 | 23–24 | Koffing 24 | emerald-rematch + Croagunk |
| LUNG | Route113 | route | 3 | 23–24 | Ninjask 24 | enhanced + Salandit |
| MADELINE_1 | Route113 | route | 3 | 23–24 | Numel 24 | emerald-rematch |
| CAROL | Route112 | route | 3 | 22–23 | Lombre 23 | enhanced + Skiddo |
| NANCY | Route114 | route | 3 | 24–25 | Lombre 25 | enhanced |
| DIANA_1 | JaggedPass | route | 3 | 26–27 | Breloom 27 | emerald-rematch |
| IRENE | Route111 | route | 3 | 21–22 | Azumarill 22 | enhanced |
| ELI | LavaridgeTown_Gym_1F | gym | 3 | 26–27 | Graveler 27 | enhanced + Carkol |
| BRENDAN_MT_CHIMNEY | MtChimney | route | 5 | 27–29 | Grovyle 29 | story |
| ASTER_METEOR_FALLS_DEINO | MeteorFalls_1F_1R | route | 5 | 26–28 | Drakloak 28 | story |
| ASTER_METEOR_FALLS_DREEPY |  | route | 5 | 26–28 | Hakamo-o 28 | story |
| ASTER_METEOR_FALLS_JANGMO_O |  | route | 5 | 26–28 | Zweilous 28 | story |
| JULIO | JaggedPass | route | 3 | 26–27 | Manectric 27 | enhanced + Blitzle |
| GRUNT_JAGGED_PASS | JaggedPass | grunt | 3 | 26–27 | Mightyena 27 | enhanced |
| GRUNT_MT_CHIMNEY_2 | MtChimney | grunt | 3 | 25–26 | Golbat 26 | enhanced |
| VIVI | Route111 | route | 3 | 22–23 | Azumarill 23 | enhanced |
| BRICE | Route112 | route | 3 | 22–23 | Machop 23 | enhanced + Nacli |
| TRENT_1 | Route112 | route | 3 | 22–23 | Geodude 23 | emerald-rematch + Carkol |
| LENNY | Route114 | route | 3 | 24–25 | Graveler 25 | enhanced + Roggenrola |
| LUCAS_1 | Route114 | route | 3 | 24–25 | Graveler 25 | enhanced |
| ERIC | JaggedPass | route | 3 | 26–27 | Graveler 27 | enhanced + Mudbray |
| GERALD | LavaridgeTown_Gym_1F | gym | 3 | 27–28 | Kecleon 28 | enhanced + Fletchinder |
| DANIELLE | LavaridgeTown_Gym_1F | gym | 3 | 26–28 | Meditite 28 | enhanced + Heatmor |
| TORI_AND_TIA | Route113 | route | 4 | 23–24 | Minun 24 | enhanced |
| TYRA_AND_IVY | Route114 | route | 4 | 24–25 | Graveler 25 | enhanced |
| TYRON | Route111 | route | 3 | 21–22 | Sandslash 22 | enhanced |
| CELINA | Route111 | route | 3 | 21–22 | Roselia 22 | enhanced |
| BIANCA | Route111 | route | 3 | 21–22 | Shroomish 22 | enhanced |
| HAYDEN | Route111 | route | 3 | 21–22 | Numel 22 | enhanced + Litleo |
| SOPHIE | Route113 | route | 3 | 23–24 | Lombre 24 | enhanced |
| COBY | Route113 | route | 3 | 23–24 | Swellow 24 | enhanced + Corvisquire |
| LAWRENCE | Route113 | route | 3 | 23–24 | Sandslash 24 | enhanced + Hippopotas |
| WYATT | Route113 | route | 3 | 23–24 | Aron 24 | enhanced + Cranidos |
| ANGELINA | Route114 | route | 3 | 24–25 | Azumarill 25 | enhanced |
| KAI | Route114 | route | 3 | 24–25 | Barboach 25 | enhanced |
| CHARLOTTE | Route114 | route | 3 | 24–25 | Nuzleaf 25 | enhanced + Stufful |
| BRYANT | Route112 | route | 3 | 22–23 | Slugma 23 | enhanced + Sizzlipede |
| SHAYLA | Route112 | route | 3 | 22–23 | Roselia 23 | enhanced + Morelull |
| NERINE_MT_CHIMNEY_DEINO_CHARMANDER | MtChimney | route | 5 | 27–29 | Hakamo-o 29 | story |
| NERINE_MT_CHIMNEY_DEINO_TOTODILE |  | route | 5 | 27–29 | Hakamo-o 29 | story |
| NERINE_MT_CHIMNEY_DEINO_TREECKO |  | route | 5 | 27–29 | Hakamo-o 29 | story |
| NERINE_MT_CHIMNEY_DREEPY_CHARMANDER |  | route | 5 | 27–29 | Zweilous 29 | story |
| NERINE_MT_CHIMNEY_DREEPY_TOTODILE |  | route | 5 | 27–29 | Zweilous 29 | story |
| NERINE_MT_CHIMNEY_DREEPY_TREECKO |  | route | 5 | 27–29 | Zweilous 29 | story |
| NERINE_MT_CHIMNEY_JANGMO_O_CHARMANDER |  | route | 5 | 27–29 | Drakloak 29 | story |
| NERINE_MT_CHIMNEY_JANGMO_O_TOTODILE |  | route | 5 | 27–29 | Drakloak 29 | story |
| NERINE_MT_CHIMNEY_JANGMO_O_TREECKO |  | route | 5 | 27–29 | Drakloak 29 | story |
| WALLY_ROUTE_112 | Route112 | route | 3 | 25–27 | Kirlia 27 | story |

### S5 (cap 34) – Desert, Norman

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| DUSTY_1 | Route111 | route | 3 | 28–30 | Sandslash 30 | emerald-rematch + Tyrunt |
| GABBY_AND_TY_3 |  | route | 4 | 29–31 | Loudred 31 | enhanced |
| RANDALL | PetalburgCity_Gym | gym | 4 | 30–31 | Swellow 31 | enhanced + Gumshoos, Vespiquen |
| PARKER | PetalburgCity_Gym | gym | 4 | 30–31 | Spinda 31 | enhanced + Swoobat, Bewear |
| GEORGE | PetalburgCity_Gym | gym | 4 | 31–32 | Vigoroth 32 | enhanced + Greedent, Floatzel |
| BERKE | PetalburgCity_Gym | gym | 4 | 31–32 | Vigoroth 32 | enhanced + Diggersby, Zoroark |
| MARY | PetalburgCity_Gym | gym | 4 | 30–31 | Delcatty 31 | enhanced + Glameow, Whimsicott |
| ALEXIA | PetalburgCity_Gym | gym | 4 | 31–32 | Wigglytuff 32 | enhanced + Bouffalant, Chatot |
| JODY | PetalburgCity_Gym | gym | 4 | 31–32 | Zangoose 32 | enhanced + Lokix, Herdier |
| DREW | Route111 | route | 3 | 28–29 | Sandslash 29 | enhanced + Gabite |
| BEAU | Route111 | route | 3 | 27–28 | Baltoy 28 | enhanced + Hippopotas |
| JUSTIN | Route110_TrickHousePuzzle3 | route | 3 | 29–30 | Kecleon 30 | enhanced |
| NORMAN_1 | PetalburgCity_Gym | leader | 6 | 31–34 | Slaking 34 | emerald-rematch |
| HEIDI | Route111 | route | 3 | 28–29 | Baltoy 29 | enhanced + Sandile |
| BECKY | Route111 | route | 3 | 28–29 | Azumarill 29 | enhanced |
| MARTHA | Route110_TrickHousePuzzle3 | route | 3 | 29–30 | Delcatty 30 | enhanced |
| ALAN | Route110_TrickHousePuzzle3 | route | 3 | 29–30 | Graveler 30 | enhanced |
| CELIA | Route111 | route | 3 | 28–29 | Lombre 29 | enhanced |
| BRYAN | Route111 | route | 3 | 28–29 | Sandslash 29 | enhanced + Sigilyph |
| BRANDEN | Route111 | route | 3 | 28–29 | Nuzleaf 29 | enhanced |
| WALLY_PETALBURG | PetalburgCity | route | 4 | 30–33 | Kirlia 33 | story |
| MAY_LAVARIDGE | LavaridgeTown | route | 5 | 31–33 | Combusken 33 | story |

### S6 (cap 38) – Surf routes, Abandoned Ship, Route 119, Weather Institute, Winona

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_WEATHER_INST_1 | Route119_WeatherInstitute_1F | grunt | 4 | 32–33 | Golbat 33 | enhanced + Thievul |
| GRUNT_WEATHER_INST_2 | Route119_WeatherInstitute_2F | grunt | 4 | 33–34 | Sharpedo 34 | enhanced + Barraskewda |
| GRUNT_WEATHER_INST_3 | Route119_WeatherInstitute_2F | grunt | 5 | 33–34 | Sharpedo 34 | enhanced + Kilowattrel |
| GRUNT_WEATHER_INST_4 | Route119_WeatherInstitute_1F | grunt | 4 | 32–33 | Sharpedo 33 | enhanced + Floatzel |
| SHELLY_WEATHER_INSTITUTE | Route119_WeatherInstitute_2F | admin | 5 | 34–36 | Sharpedo 36 | enhanced |
| ROSE_2 | Route118 | route t2 | 4 | 32–34 | Roselia 34 | emerald-rematch + Lilligant, Shiinotic |
| FOSTER | Route105 | route | 4 | 30–31 | Sandslash 31 | enhanced + Rampardos, Boldore |
| DUSTY_2 | Route111 | route t2 | 4 | 33–35 | Sandslash 35 | emerald-rematch + Tyrunt, Amaura |
| GABBY_AND_TY_4 |  | route | 4 | 32–34 | Magneton 34 | enhanced |
| AUSTINA | Route109 | route | 4 | 31–32 | Azumarill 32 | enhanced + Bruxish, Ducklett |
| GWEN | Route109 | route | 4 | 31–32 | Azumarill 32 | enhanced + Finizen, Kilowattrel |
| LOLA_2 | Route109 | route t2 | 4 | 32–34 | Azumarill 34 | emerald-rematch |
| CHARLIE | AbandonedShip_Corridors_1F | route | 4 | 32–33 | Azumarill 33 | enhanced + Floatzel, Drednaw |
| RICKY_2 | Route109 | route t2 | 4 | 32–34 | Linoone 34 | emerald-rematch |
| WILTON_2 | Route111 | route t2 | 4 | 33–35 | Hariyama 35 | emerald-rematch + Fletchinder, Axew |
| BROOKE_2 | Route111 | route t2 | 4 | 33–35 | Roselia 35 | emerald-rematch + Glameow, Kilowattrel |
| CINDY_3 | Route104 | route t2 | 4 | 32–34 | Linoone 34 | emerald-rematch + Litleo, Whimsicott |
| WINSTON_2 | Route104 | route t2 | 4 | 32–34 | Linoone 34 | emerald-rematch + Litleo, Unfezant |
| THALIA_1 | AbandonedShip_Rooms_1F | route | 4 | 33–34 | Seadra 34 | emerald-rematch |
| STEVE_2 | Route114 | route t2 | 4 | 33–35 | Lairon 35 | emerald-rematch |
| LUIS | Route105 | route | 4 | 30–31 | Sharpedo 31 | enhanced + Kilowattrel, Barraskewda |
| DOMINIK | Route105 | route | 4 | 30–31 | Tentacruel 31 | enhanced + Finneon, Clauncher |
| DOUGLAS | Route106 | route | 4 | 30–31 | Tentacruel 31 | enhanced |
| DARRIN | Route107 | route | 4 | 31–32 | Tentacruel 32 | enhanced |
| TONY_1 | Route107 | route | 4 | 31–32 | Sharpedo 32 | emerald-rematch + Frillish, Lumineon |
| JEROME | Route108 | route | 4 | 32–33 | Pelipper 33 | oras-first |
| MATTHEW | Route108 | route | 4 | 32–33 | Sharpedo 33 | enhanced + Barraskewda, Kilowattrel |
| DAVID | Route109 | route | 4 | 32–33 | Sharpedo 33 | enhanced |
| TONY_2 | Route107 | route t2 | 4 | 33–35 | Sharpedo 35 | emerald-rematch + Frillish, Lumineon |
| KOICHI | Route115 | route | 4 | 31–32 | Machoke 32 | enhanced + Throh, Sawk |
| NOB_2 | Route115 | route t2 | 4 | 32–34 | Machoke 34 | emerald-rematch |
| YUJI | Route110_TrickHousePuzzle4 | route | 4 | 33–34 | Machoke 34 | enhanced |
| DALTON_2 | Route118 | route t2 | 4 | 32–35 | Loudred 35 | emerald-rematch + Chatot, Rotom |
| BERNIE_2 | Route114 | route t2 | 4 | 33–35 | Camerupt 35 | emerald-rematch |
| ETHAN_2 | JaggedPass | route t2 | 4 | 33–35 | Linoone 35 | emerald-rematch + Stunky, Mudsdale |
| BRENT | Route119 | route | 4 | 31–32 | Ninjask 32 | oras-first |
| DONALD | Route119 | route | 4 | 31–32 | Beautifly 32 | enhanced + Centiskorch, Golisopod |
| TAYLOR | Route119 | route | 4 | 32–33 | Dustox 33 | enhanced + Lokix, Ribombee |
| WINONA_1 | FortreeCity_Gym | leader | 6 | 35–38 | Altaria 38 | emerald-rematch |
| JERRY_2 | Route116 | route t2 | 4 | 32–34 | Gardevoir 34 | emerald-rematch + Pawniard, Musharna |
| KAREN_2 | Route116 | route t2 | 4 | 32–34 | Loudred 34 | emerald-rematch |
| ANNA_AND_MEG_2 | Route117 | route t2 | 4 | 32–34 | Hariyama 34 | emerald-rematch |
| MIGUEL_2 | Route103 | route t2 | 4 | 32–34 | Delcatty 34 | emerald-rematch |
| ISABEL_2 | Route110 | route t2 | 4 | 32–34 | Minun 34 | emerald-rematch |
| TIMOTHY_1 | Route115 | route | 4 | 32–33 | Hariyama 33 | emerald-rematch + Hawlucha, Gurdurr |
| TIMOTHY_2 | Route115 | route t2 | 4 | 33–35 | Hariyama 35 | emerald-rematch + Hawlucha, Gurdurr |
| SHELBY_2 | MtChimney | route t2 | 4 | 33–35 | Hariyama 35 | emerald-rematch + Lucario, Hawlucha |
| CALVIN_2 | Route102 | route t2 | 4 | 32–34 | Mightyena 34 | emerald-rematch + Greedent, Gumshoos |
| BARNY | Route118 | route | 4 | 30–31 | Sharpedo 31 | enhanced + Drednaw, Barraskewda |
| CARTER | Route109 | route | 4 | 32–33 | Tentacruel 33 | enhanced + Lumineon, Drednaw |
| ELLIOT_2 | Route106 | route t2 | 4 | 32–34 | Tentacruel 34 | emerald-rematch |
| BENJAMIN_2 | Route110 | route t2 | 4 | 32–34 | Magneton 34 | emerald-rematch + Klink, Zebstrika |
| ABIGAIL_2 | Route110 | route t2 | 4 | 32–34 | Magneton 34 | emerald-rematch |
| DYLAN_2 | Route117 | route t2 | 4 | 32–34 | Dodrio 34 | emerald-rematch |
| MARIA_2 | Route117 | route t2 | 4 | 32–34 | Dodrio 34 | emerald-rematch |
| DEMETRIUS | AbandonedShip_Rooms_1F | route | 4 | 32–33 | Manectric 33 | enhanced + Thievul, Gumshoos |
| PERRY | Route118 | route | 4 | 30–31 | Pelipper 31 | enhanced + Kilowattrel, Hawlucha |
| HUGH | Route119 | route | 4 | 32–33 | Tropius 33 | enhanced + Toucannon, Kilowattrel |
| PHIL | Route119 | route | 4 | 32–33 | Swellow 33 | enhanced + Toucannon, Unfezant |
| JARED | FortreeCity_Gym | gym | 4 | 34–35 | Tropius 35 | enhanced + Staraptor, Toucannon |
| HUMBERTO | FortreeCity_Gym | gym | 4 | 35–36 | Skarmory 36 | enhanced + Hawlucha, Sigilyph |
| EDWARDO | FortreeCity_Gym | gym | 4 | 34–35 | Pelipper 35 | enhanced + Unfezant, Kilowattrel |
| CHESTER | Route118 | route | 4 | 31–32 | Swellow 32 | oras-first |
| YASU | Route119 | route | 4 | 32–33 | Ninjask 33 | enhanced + Croagunk, Zoroark |
| TAKASHI | Route119 | route | 4 | 32–33 | Ninjask 33 | enhanced + Lokix, Hawlucha |
| JANI | AbandonedShip_Rooms2_1F | route | 4 | 32–33 | Azumarill 33 | enhanced + Alomomola, Dhelmise |
| LAO_2 | Route113 | route t2 | 4 | 33–35 | Weezing 35 | emerald-rematch + Croagunk, Stunky |
| CORA | Route110_TrickHousePuzzle4 | route | 4 | 33–34 | Meditite 34 | enhanced |
| PAULA | Route110_TrickHousePuzzle4 | route | 4 | 33–34 | Breloom 34 | enhanced + Lucario, Mienfoo |
| CYNDY_2 | Route115 | route t2 | 4 | 32–34 | Hariyama 34 | emerald-rematch |
| MADELINE_2 | Route113 | route t2 | 4 | 33–35 | Camerupt 35 | emerald-rematch |
| BEVERLY | Route105 | route | 4 | 30–31 | Wailmer 31 | enhanced + Finizen, Kilowattrel |
| IMANI | Route105 | route | 4 | 30–31 | Azumarill 31 | enhanced |
| KYLA | Route106 | route | 4 | 30–31 | Wailmer 31 | enhanced |
| DENISE | Route107 | route | 4 | 31–32 | Pelipper 32 | enhanced + Lumineon, Alomomola |
| BETH | Route107 | route | 4 | 31–33 | Seaking 33 | enhanced |
| TARA | Route108 | route | 4 | 32–33 | Seadra 33 | enhanced + Alomomola, Lumineon |
| MISSY | Route108 | route | 4 | 32–33 | Wailmer 33 | oras-first |
| ALICE | Route109 | route | 4 | 32–34 | Seaking 34 | enhanced |
| DIANA_2 | JaggedPass | route t2 | 4 | 33–35 | Altaria 35 | emerald-rematch |
| AMY_AND_LIV_2 | Route103 | route t2 | 4 | 32–34 | Minun 34 | emerald-rematch |
| DUNCAN | AbandonedShip_Corridors_B1F | route | 4 | 33–34 | Machoke 34 | enhanced + Frillish, Kilowattrel |
| EDWIN_2 | Route110 | route t2 | 4 | 33–34 | Shiftry 34 | emerald-rematch |
| BRENDAN_ROUTE_119 | Route119 | route | 5 | 35–37 | Sceptile 37 | story |
| ISAAC_2 | Route117 | route t2 | 4 | 33–34 | Hariyama 34 | emerald-rematch |
| GARRISON | AbandonedShip_Rooms2_1F | route | 4 | 32–34 | Sandslash 34 | enhanced |
| LYDIA_2 | Route117 | route t2 | 4 | 33–34 | Azumarill 34 | emerald-rematch |
| JACKSON_1 | Route119 | route | 4 | 32–33 | Breloom 33 | emerald-rematch + Unfezant, Toucannon |
| JACKSON_2 | Route119 | route t2 | 4 | 34–35 | Breloom 35 | emerald-rematch + Unfezant, Toucannon |
| CATHERINE_1 | Route119 | route | 4 | 32–33 | Roselia 33 | emerald-rematch + Excadrill, Tsareena |
| CATHERINE_2 | Route119 | route t2 | 4 | 34–35 | Roselia 35 | emerald-rematch + Excadrill, Tsareena |
| GRUNT_WEATHER_INST_5 | Route119_WeatherInstitute_2F | grunt | 4 | 33–34 | Golbat 34 | enhanced + Zoroark |
| HALEY_2 | Route104 | route t2 | 4 | 32–34 | Breloom 34 | emerald-rematch + Whimsicott, Ribombee |
| DOUG | Route119 | route | 4 | 31–32 | Illumise 32 | oras-first |
| GREG | Route119 | route | 4 | 31–32 | Illumise 32 | enhanced + Lokix, Vespiquen |
| KENT | Route119 | route | 4 | 31–32 | Ninjask 32 | enhanced |
| JAMES_2 | PetalburgWoods | route t2 | 4 | 32–34 | Ninjask 34 | emerald-rematch + Vespiquen, Lokix |
| TRENT_2 | Route112 | route t2 | 4 | 33–35 | Graveler 35 | emerald-rematch + Carkol, Boldore |
| KIRA_AND_DAN_1 | AbandonedShip_Rooms2_1F | route | 4 | 33–34 | Illumise 34 | emerald-rematch |
| KIRA_AND_DAN_2 | AbandonedShip_Rooms2_1F | route t2 | 4 | 34–35 | Illumise 35 | emerald-rematch |
| HIDEO | Route119 | route | 4 | 33–35 | Weezing 35 | enhanced |
| FLINT | FortreeCity_Gym | gym | 4 | 35–36 | Xatu 36 | enhanced + Corvisquire, Talonflame |
| ASHLEY | FortreeCity_Gym | gym | 4 | 35–36 | Altaria 36 | enhanced + Swanna, Chatot |
| MEL_AND_PAUL | Route109 | route | 4 | 32–33 | Beautifly 33 | enhanced |
| LISA_AND_RAY | Route107 | route | 4 | 31–33 | Seaking 33 | enhanced |
| CHRIS | Route119 | route | 4 | 32–34 | Gyarados 34 | enhanced |
| ANDRES_1 | Route105 | route | 4 | 30–31 | Sandslash 31 | emerald-rematch |
| JOSUE | Route105 | route | 4 | 30–31 | Swellow 31 | enhanced |
| CAMRON | Route107 | route | 4 | 31–32 | Starmie 32 | enhanced |
| CORY_1 | Route108 | route | 4 | 32–33 | Tentacruel 33 | emerald-rematch |
| CAROLINA | Route108 | route | 5 | 33–34 | Manectric 34 | enhanced + Luxray, Tsareena |
| ELIJAH | Route109 | route | 4 | 32–33 | Skarmory 33 | enhanced + Kilowattrel, Unfezant |
| KYRA | Route115 | route | 4 | 31–32 | Dodrio 32 | enhanced |
| JAIDEN | Route115 | route | 4 | 31–32 | Swalot 32 | enhanced + Thievul, Zoroark |
| ALIX | Route115 | route | 4 | 31–33 | Gardevoir 33 | enhanced + Sigilyph, Swoobat |
| HELENE | Route115 | route | 4 | 31–32 | Hariyama 32 | enhanced + Hawlucha, Lucario |
| FABIAN | Route119 | route | 4 | 32–33 | Manectric 33 | enhanced + Rotom, Luxray |
| DAYTON | Route119 | route | 4 | 32–33 | Camerupt 33 | enhanced + Heatmor, Fletchinder |
| RACHEL | Route119 | route | 4 | 32–33 | Seaking 33 | enhanced + Goomy, Palpitoad |
| DARIUS | FortreeCity_Gym | gym | 5 | 35–36 | Tropius 36 | enhanced + Staraptor, Swanna |
| ANDRES_2 | Route105 | route t2 | 4 | 33–35 | Sandslash 35 | emerald-rematch |
| CORY_2 | Route108 | route t2 | 4 | 33–35 | Tentacruel 35 | emerald-rematch |
| SAWYER_2 | MtChimney | route t2 | 4 | 33–35 | Graveler 35 | emerald-rematch + Coalossal, Mudsdale |
| THALIA_2 | AbandonedShip_Rooms_1F | route t2 | 4 | 34–35 | Seadra 35 | emerald-rematch |
| WALLY_ROUTE_120 | Route120 | route | 5 | 36–38 | Kirlia 38 | story |

### S7 (cap 44) – Routes 120-134, Mt. Pyre, Lilycove, both hideouts, Tate & Liza

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_AQUA_HIDEOUT_1 | AquaHideout_1F | grunt | 4 | 39–40 | Mightyena 40 | enhanced + Toxapex |
| GRUNT_AQUA_HIDEOUT_2 | AquaHideout_B1F | grunt | 4 | 40–41 | Sharpedo 41 | enhanced + Palafin |
| GRUNT_AQUA_HIDEOUT_3 | AquaHideout_B1F | grunt | 4 | 40–41 | Crobat 41 | enhanced + Skuntank |
| GRUNT_AQUA_HIDEOUT_4 | AquaHideout_B2F | grunt | 4 | 40–41 | Sharpedo 41 | enhanced + Jellicent |
| GABRIELLE_1 | MtPyre_3F | route | 4 | 37–38 | Mightyena 38 | emerald-rematch |
| MARCEL | Route121 | route | 4 | 37–38 | Manectric 38 | enhanced + Barraskewda, Zoroark |
| ALBERTO | Route123 | route | 4 | 37–38 | Xatu 38 | enhanced + Kilowattrel, Toucannon |
| ED | Route123 | route | 4 | 37–39 | Zangoose 39 | enhanced + Mimikyu, Rotom |
| DECLAN | Route124 | route | 4 | 35–37 | Gyarados 37 | enhanced + Kilowattrel, Wishiwashi |
| GRUNT_MT_PYRE_1 | MtPyre_Summit | grunt | 4 | 37–38 | Golbat 38 | enhanced + Clawitzer |
| GRUNT_MT_PYRE_2 | MtPyre_Summit | grunt | 4 | 37–38 | Sharpedo 38 | enhanced + Kilowattrel |
| GRUNT_MT_PYRE_3 | MtPyre_Summit | grunt | 4 | 37–38 | Mightyena 38 | enhanced + Skuntank |
| GRUNT_AQUA_HIDEOUT_5 | AquaHideout_B1F | grunt | 4 | 40–41 | Sharpedo 41 | enhanced + Barraskewda |
| GRUNT_AQUA_HIDEOUT_6 | AquaHideout_B2F | grunt | 4 | 40–41 | Crobat 41 | enhanced + Scrafty |
| FREDRICK | Route123 | route | 4 | 37–39 | Machamp 39 | enhanced + Lucario, Conkeldurr |
| MATT | AquaHideout_B2F | admin | 5 | 40–42 | Sharpedo 42 | enhanced |
| ZANDER | MtPyre_2F | route | 4 | 36–37 | Hariyama 37 | enhanced + Conkeldurr, Throh |
| LEAH | MtPyre_2F | route | 4 | 36–37 | Banette 37 | enhanced + Litwick, Houndstone |
| VIOLET | Route123 | route | 4 | 37–39 | Roserade 39 | enhanced + Tsareena, Shiinotic |
| ROSE_3 | Route118 | route t3 | 5 | 37–39 | Roselia 39 | emerald-rematch + Lilligant, Shiinotic |
| CHIP | Route120 | route | 4 | 35–36 | Claydol 36 | enhanced + Golett, Cofagrigus |
| DUSTY_3 | Route111 | route t3 | 4 | 38–40 | Sandslash 40 | emerald-rematch + Tyrunt, Aurorus |
| GABBY_AND_TY_5 |  | route | 4 | 38–39 | Magneton 39 | emerald-rematch |
| LOLA_3 | Route109 | route t3 | 4 | 37–39 | Azumarill 39 | emerald-rematch |
| RICKY_3 | Route109 | route t3 | 4 | 38–39 | Linoone 39 | emerald-rematch |
| BRAXTON | Route123 | route | 5 | 37–39 | Shiftry 39 | enhanced + Staraptor, Barraskewda |
| WILTON_3 | Route111 | route t3 | 5 | 38–40 | Hariyama 40 | emerald-rematch + Fraxure, Talonflame |
| WARREN | Route133 | route | 5 | 39–41 | Alakazam 41 | oras-first |
| WENDY | Route123 | route | 4 | 37–39 | Altaria 39 | enhanced + Swanna, Whimsicott |
| JENNIFER | Route120 | route | 4 | 35–36 | Sableye 36 | enhanced + Trevenant, Luxray |
| BROOKE_3 | Route111 | route t3 | 5 | 38–40 | Roselia 40 | emerald-rematch + Purugly, Kilowattrel |
| KINDRA | Route123 | route | 4 | 37–39 | Dusclops 39 | enhanced + Drifblim, Trevenant |
| TAMMY | Route121 | route | 4 | 36–38 | Dusclops 38 | enhanced + Phantump, Cofagrigus |
| VALERIE_1 | MtPyre_6F | route | 4 | 38–39 | Sableye 39 | emerald-rematch + Mismagius, Polteageist |
| TASHA | MtPyre_5F | route | 4 | 38–39 | Xatu 39 | oras-first |
| VALERIE_2 | MtPyre_6F | route t2 | 4 | 38–40 | Mismagius 40 | emerald-rematch + Mismagius, Polteageist |
| VALERIE_3 | MtPyre_6F | route t3 | 5 | 39–41 | Mismagius 41 | emerald-rematch + Mismagius, Polteageist |
| CINDY_4 | Route104 | route t3 | 4 | 37–39 | Linoone 39 | emerald-rematch + Pyroar, Whimsicott |
| JESSICA_1 | Route121 | route | 4 | 37–38 | Seviper 38 | emerald-rematch + Krokorok, Salazzle |
| JESSICA_2 | Route121 | route t2 | 4 | 37–39 | Seviper 39 | emerald-rematch + Krokorok, Salazzle |
| JESSICA_3 | Route121 | route t3 | 4 | 39–41 | Seviper 41 | emerald-rematch + Krookodile, Salazzle |
| MOLLIE | Route133 | route | 5 | 39–41 | Whiscash 41 | enhanced + Lucario, Hawlucha |
| WINSTON_3 | Route104 | route t3 | 4 | 37–39 | Linoone 39 | emerald-rematch + Pyroar, Unfezant |
| MARK | MtPyre_2F | route | 4 | 36–37 | Rhyhorn 37 | enhanced + Tyrunt, Rampardos |
| STEVE_3 | Route114 | route t3 | 4 | 38–40 | Lairon 40 | emerald-rematch |
| SPENCER | Route124 | route | 4 | 36–38 | Tentacruel 38 | enhanced + Lumineon, Floatzel |
| ROLAND | Route124 | route | 4 | 36–38 | Sharpedo 38 | enhanced + Clawitzer, Alomomola |
| NOLEN | Route125 | route | 4 | 36–38 | Tentacruel 38 | enhanced |
| STAN | Route125 | route | 4 | 37–39 | Seadra 39 | enhanced |
| BARRY | Route126 | route | 4 | 37–39 | Gyarados 39 | enhanced + Alomomola, Barraskewda |
| DEAN | Route126 | route | 4 | 37–39 | Golduck 39 | oras-first |
| RODNEY | Route130 | route | 4 | 38–40 | Gyarados 40 | enhanced + Bruxish, Palafin |
| RICHARD | Route131 | route | 4 | 38–40 | Pelipper 40 | enhanced + Bruxish, Palafin |
| HERMAN | Route131 | route | 4 | 39–40 | Tentacruel 40 | enhanced |
| SANTIAGO | Route130 | route | 4 | 38–40 | Wailord 40 | enhanced |
| GILBERT | Route132 | route | 4 | 39–41 | Sharpedo 41 | enhanced + Clawitzer, Toxapex |
| FRANKLIN | Route133 | route | 4 | 39–41 | Whiscash 41 | oras-first |
| KEVIN | Route131 | route | 4 | 38–40 | Gyarados 40 | enhanced + Palafin, Bruxish |
| JACK | Route134 | route | 4 | 40–41 | Sharpedo 41 | oras-first |
| CHAD | Route124 | route | 4 | 36–38 | Tentacruel 38 | enhanced |
| TONY_3 | Route107 | route t3 | 5 | 38–40 | Sharpedo 40 | emerald-rematch + Frillish, Lumineon |
| HITOSHI | Route134 | route | 4 | 39–41 | Heracross 41 | oras-first |
| KIYO | Route132 | route | 4 | 39–41 | Hariyama 41 | enhanced + Mienfoo, Grapploct |
| NOB_3 | Route115 | route t3 | 5 | 37–39 | Machamp 39 | emerald-rematch |
| ATSUSHI | MtPyre_4F | route | 4 | 37–38 | Hariyama 38 | enhanced + Throh, Sawk |
| GRUNT_AQUA_HIDEOUT_7 | AquaHideout_B1F | grunt | 4 | 40–41 | Mightyena 41 | enhanced + Clawitzer |
| GRUNT_AQUA_HIDEOUT_8 | AquaHideout_B2F | grunt | 4 | 40–41 | Gyarados 41 | enhanced |
| FERNANDO_1 | Route123 | route | 4 | 37–38 | Loudred 38 | emerald-rematch + Luxray, Rotom |
| DALTON_3 | Route118 | route t3 | 5 | 37–40 | Exploud 40 | emerald-rematch + Chatot, Rotom |
| BERNIE_3 | Route114 | route t3 | 5 | 38–40 | Magcargo 40 | emerald-rematch |
| ETHAN_3 | JaggedPass | route t3 | 4 | 38–40 | Linoone 40 | emerald-rematch + Skuntank, Mudsdale |
| JEFFREY_1 | Route120 | route | 4 | 35–36 | Masquerain 36 | emerald-rematch + Golisopod, Larvesta |
| JEFFREY_2 | Route120 | route t2 | 4 | 37–39 | Masquerain 39 | emerald-rematch + Golisopod, Larvesta |
| JEFFREY_3 | Route120 | route t3 | 5 | 39–41 | Masquerain 41 | emerald-rematch + Golisopod, Larvesta |
| PRESTON | MossdeepCity_Gym | gym | 4 | 39–41 | Gallade 41 | enhanced + Musharna, Sigilyph |
| VIRGIL | MossdeepCity_Gym | gym | 4 | 39–41 | Girafarig 41 | oras-first + Bronzong, Swoobat |
| BLAKE | MossdeepCity_Gym | gym | 4 | 39–41 | Girafarig 41 | enhanced + Bronzong, Sigilyph |
| WILLIAM | MtPyre_3F | route | 4 | 37–38 | Grumpig 38 | oras-first |
| CAMERON_1 | Route123 | route | 4 | 37–38 | Solrock 38 | emerald-rematch |
| CAMERON_2 | Route123 | route t2 | 4 | 37–39 | Kadabra 39 | emerald-rematch |
| CAMERON_3 | Route123 | route t3 | 5 | 39–41 | Alakazam 41 | emerald-rematch |
| HANNAH | MossdeepCity_Gym | gym | 4 | 39–41 | Gardevoir 41 | enhanced + Sigilyph, Swoobat |
| SAMANTHA | MossdeepCity_Gym | gym | 4 | 39–41 | Xatu 41 | enhanced + Lucario, Bronzong |
| MAURA | MossdeepCity_Gym | gym | 4 | 39–41 | Alakazam 41 | enhanced + Bruxish, Musharna |
| KAYLA | MtPyre_3F | route | 4 | 37–38 | Alakazam 38 | enhanced |
| JACKI_1 | Route123 | route | 4 | 37–38 | Lunatone 38 | emerald-rematch |
| JACKI_2 | Route123 | route t2 | 4 | 37–39 | Kadabra 39 | emerald-rematch |
| JACKI_3 | Route123 | route t3 | 5 | 39–41 | Alakazam 41 | emerald-rematch |
| WALTER_1 | Route121 | route | 4 | 36–37 | Manectric 37 | emerald-rematch + Stoutland, Pyroar |
| WALTER_2 | Route121 | route t2 | 4 | 37–39 | Manectric 39 | emerald-rematch + Stoutland, Pyroar |
| WALTER_3 | Route121 | route t3 | 5 | 39–41 | Manectric 41 | emerald-rematch + Stoutland, Pyroar |
| TATE_AND_LIZA_1 | MossdeepCity_Gym | leader | 6 | 42–44 | Solrock 44 | emerald-rematch |
| JERRY_3 | Route116 | route t3 | 4 | 38–39 | Gardevoir 39 | emerald-rematch + Pawniard, Musharna |
| KAREN_3 | Route116 | route t3 | 4 | 37–40 | Exploud 40 | emerald-rematch |
| KATE_AND_JOY | Route121 | route | 4 | 36–37 | Slaking 37 | enhanced |
| ANNA_AND_MEG_3 | Route117 | route t3 | 4 | 37–39 | Hariyama 39 | emerald-rematch |
| MIGUEL_3 | Route103 | route t3 | 4 | 37–39 | Delcatty 39 | emerald-rematch |
| VANESSA | Route121 | route | 4 | 36–37 | Pikachu 37 | enhanced + Pawmot, Ribombee |
| ISABEL_3 | Route110 | route t3 | 4 | 38–39 | Minun 39 | emerald-rematch |
| TIMOTHY_3 | Route115 | route t3 | 4 | 38–40 | Hariyama 40 | emerald-rematch + Hawlucha, Gurdurr |
| SHELBY_3 | MtChimney | route t3 | 4 | 38–40 | Hariyama 40 | emerald-rematch + Lucario, Hawlucha |
| CALVIN_3 | Route102 | route t3 | 4 | 37–39 | Mightyena 39 | emerald-rematch + Greedent, Gumshoos |
| ELLIOT_3 | Route106 | route t3 | 5 | 37–39 | Tentacruel 39 | emerald-rematch |
| RONALD | Route132 | route | 5 | 39–41 | Gyarados 41 | enhanced |
| BENJAMIN_3 | Route110 | route t3 | 4 | 37–39 | Magneton 39 | emerald-rematch + Klang, Zebstrika |
| ABIGAIL_3 | Route110 | route t3 | 4 | 37–39 | Magneton 39 | emerald-rematch |
| DYLAN_3 | Route117 | route t3 | 4 | 37–39 | Dodrio 39 | emerald-rematch |
| MARIA_3 | Route117 | route t3 | 4 | 37–39 | Dodrio 39 | emerald-rematch |
| CAMDEN | Route127 | route | 4 | 37–39 | Starmie 39 | enhanced + Floatzel, Barraskewda |
| ISAIAH_1 | Route128 | route | 4 | 38–40 | Starmie 40 | emerald-rematch + Floatzel, Toxapex |
| PABLO_1 | Route126 | route | 4 | 37–39 | Starmie 39 | emerald-rematch |
| CHASE | Route129 | route | 4 | 38–40 | Starmie 40 | enhanced + Bruxish, Palafin |
| ISAIAH_2 | Route128 | route t2 | 4 | 39–41 | Starmie 41 | emerald-rematch + Floatzel, Toxapex |
| ISAIAH_3 | Route128 | route t3 | 5 | 40–42 | Starmie 42 | emerald-rematch + Floatzel, Toxapex |
| ISOBEL | Route126 | route | 4 | 37–39 | Starmie 39 | enhanced |
| DONNY | Route127 | route | 4 | 38–40 | Starmie 40 | enhanced |
| TALIA | Route131 | route | 4 | 38–40 | Starmie 40 | enhanced |
| KATELYN_1 | Route128 | route | 4 | 38–40 | Starmie 40 | emerald-rematch |
| ALLISON | Route129 | route | 4 | 38–40 | Starmie 40 | enhanced |
| KATELYN_2 | Route128 | route t2 | 4 | 39–41 | Starmie 41 | emerald-rematch |
| KATELYN_3 | Route128 | route t3 | 5 | 40–42 | Starmie 42 | emerald-rematch |
| AARON | Route134 | route | 4 | 39–41 | Seadra 41 | oras-first + Fraxure, Druddigon |
| PRESLEY | Route125 | route | 4 | 37–39 | Xatu 39 | enhanced + Toucannon, Kilowattrel |
| COLIN | Route120 | route | 4 | 35–36 | Pelipper 36 | enhanced + Toucannon, Staraptor |
| ROBERT_1 | Route120 | route | 4 | 35–36 | Altaria 36 | emerald-rematch + Staraptor, Corvisquire |
| ROBERT_2 | Route120 | route t2 | 4 | 37–39 | Xatu 39 | emerald-rematch + Staraptor, Corviknight |
| ROBERT_3 | Route120 | route t3 | 5 | 39–41 | Xatu 41 | emerald-rematch + Staraptor, Corviknight |
| ALEX | Route134 | route | 4 | 40–41 | Swellow 41 | enhanced + Kilowattrel, Corviknight |
| BECK | Route133 | route | 4 | 39–41 | Tropius 41 | enhanced + Talonflame, Hawlucha |
| LAO_3 | Route113 | route t3 | 5 | 37–40 | Weezing 40 | emerald-rematch + Toxicroak, Skuntank |
| CYNDY_3 | Route115 | route t3 | 4 | 38–39 | Hariyama 39 | emerald-rematch |
| CLARISSA | Route120 | route | 4 | 35–36 | Ludicolo 36 | enhanced + Goomy, Lurantis |
| ANGELICA | Route120 | route | 4 | 35–36 | Castform 36 | enhanced + Swanna, Palpitoad |
| MADELINE_3 | Route113 | route t3 | 5 | 38–40 | Camerupt 40 | emerald-rematch |
| JENNY_1 | Route124 | route | 4 | 36–38 | Starmie 38 | emerald-rematch + Alomomola, Lumineon |
| GRACE | Route124 | route | 4 | 35–37 | Azumarill 37 | oras-first |
| TANYA | Route125 | route | 4 | 37–39 | Lanturn 39 | enhanced + Alomomola, Lumineon |
| SHARON | Route125 | route | 4 | 36–38 | Clamperl 38 | oras-first |
| NIKKI | Route126 | route | 4 | 37–39 | Azumarill 39 | enhanced + Lumineon, Swanna |
| BRENDA | Route126 | route | 4 | 37–39 | Seaking 39 | enhanced |
| KATIE | Route130 | route | 4 | 38–40 | Seaking 40 | enhanced |
| SUSIE | Route131 | route | 4 | 39–40 | Gorebyss 40 | enhanced |
| KARA | Route131 | route | 4 | 39–40 | Seaking 40 | enhanced |
| DANA | Route132 | route | 4 | 39–41 | Azumarill 41 | enhanced |
| SIENNA | Route126 | route | 4 | 37–39 | Milotic 39 | enhanced + Alomomola, Lumineon |
| DEBRA | Route133 | route | 4 | 39–41 | Seaking 41 | enhanced + Clawitzer, Kilowattrel |
| LINDA | Route133 | route | 4 | 39–41 | Seaking 41 | oras-first |
| LAUREL | Route134 | route | 4 | 39–41 | Lanturn 41 | enhanced + Skrelp, Clawitzer |
| CARLEE | Route128 | route | 4 | 38–40 | Seaking 40 | enhanced |
| JENNY_2 | Route124 | route t2 | 4 | 37–39 | Starmie 39 | emerald-rematch + Alomomola, Lumineon |
| JENNY_3 | Route124 | route t3 | 5 | 39–41 | Starmie 41 | emerald-rematch + Alomomola, Lumineon |
| CEDRIC | MtPyre_6F | route | 4 | 38–39 | Wobbuffet 39 | enhanced |
| DIANA_3 | JaggedPass | route t3 | 4 | 38–40 | Altaria 40 | emerald-rematch |
| MIU_AND_YUKI | Route123 | route | 4 | 37–38 | Illumise 38 | enhanced + Ribombee, Vespiquen |
| AMY_AND_LIV_4 | Route103 | route t3 | 4 | 37–39 | Minun 39 | emerald-rematch |
| ERNEST_1 | Route125 | route | 4 | 36–38 | Machamp 38 | emerald-rematch |
| ERNEST_2 | Route125 | route t2 | 4 | 38–39 | Tentacruel 39 | emerald-rematch |
| ERNEST_3 | Route125 | route t3 | 5 | 39–41 | Tentacruel 41 | emerald-rematch |
| JAZMYN | Route123 | route | 4 | 37–38 | Absol 38 | enhanced + Salazzle, Lurantis |
| JONAS | Route123 | route | 4 | 37–38 | Weezing 38 | enhanced + Toxicroak, Zoroark |
| KAYLEY | Route123 | route | 4 | 37–38 | Castform 38 | enhanced + Tsareena, Drifblim |
| AURON | Route125 | route | 5 | 37–39 | Machamp 39 | enhanced + Hawlucha, Lucario |
| KELVIN | Route134 | route | 4 | 40–41 | Machamp 41 | enhanced + Dhelmise, Clawitzer |
| MARLEY | Route134 | route | 5 | 39–41 | Manectric 41 | enhanced + Tsareena, Clawitzer |
| REYNA | Route134 | route | 4 | 39–41 | Hariyama 41 | enhanced + Lucario, Hawlucha |
| HUDSON | Route134 | route | 4 | 39–41 | Wailord 41 | enhanced + Clawitzer, Grapploct |
| CONOR | Route133 | route | 5 | 39–41 | Hariyama 41 | enhanced |
| EDWIN_3 | Route110 | route t3 | 5 | 37–39 | Shiftry 39 | emerald-rematch |
| DAVIS | Route123 | route | 4 | 37–38 | Pinsir 38 | enhanced + Lokix, Galvantula |
| ISAAC_3 | Route117 | route t3 | 5 | 38–39 | Hariyama 39 | emerald-rematch |
| LYDIA_3 | Route117 | route t3 | 5 | 38–39 | Azumarill 39 | emerald-rematch |
| LORENZO | Route120 | route | 4 | 35–36 | Shiftry 36 | enhanced + Lurantis, Gogoat |
| JACKSON_3 | Route119 | route t3 | 5 | 39–40 | Breloom 40 | emerald-rematch + Unfezant, Toucannon |
| JENNA | Route120 | route | 4 | 35–36 | Ludicolo 36 | enhanced |
| CATHERINE_3 | Route119 | route t3 | 4 | 39–40 | Roselia 40 | emerald-rematch + Excadrill, Tsareena |
| GRUNT_MT_PYRE_4 | MtPyre_Summit | grunt | 4 | 37–38 | Wailmer 38 | enhanced + Lumineon |
| SYLVIA | MossdeepCity_Gym | gym | 4 | 39–41 | Medicham 41 | enhanced + Drifblim, Musharna |
| LEONARDO | Route126 | route | 4 | 36–38 | Sharpedo 38 | enhanced |
| ATHENA | Route127 | route | 5 | 37–39 | Manectric 39 | enhanced + Pyroar, Swanna |
| HARRISON | Route128 | route | 4 | 38–40 | Tentacruel 40 | enhanced + Toxapex, Palafin |
| CLARENCE | Route129 | route | 4 | 38–40 | Sharpedo 40 | enhanced |
| NATE | MossdeepCity_Gym | gym | 4 | 39–41 | Grumpig 41 | enhanced + Bronzong, Sigilyph |
| KATHLEEN | MossdeepCity_Gym | gym | 4 | 39–41 | Alakazam 41 | enhanced + Sigilyph, Cofagrigus |
| CLIFFORD | MossdeepCity_Gym | gym | 4 | 39–41 | Girafarig 41 | enhanced + Sigilyph, Bruxish |
| NICHOLAS | MossdeepCity_Gym | gym | 4 | 39–41 | Wobbuffet 41 | enhanced + Musharna, Bronzong |
| MACEY | MossdeepCity_Gym | gym | 4 | 39–41 | Xatu 41 | enhanced + Swoobat, Bronzong |
| PAXTON | Route132 | route | 5 | 39–41 | Breloom 41 | enhanced |
| ISABELLA | Route124 | route | 4 | 36–38 | Starmie 38 | enhanced |
| JONATHAN | Route132 | route | 5 | 39–41 | Exploud 41 | enhanced |
| HALEY_3 | Route104 | route t3 | 4 | 37–39 | Breloom 39 | emerald-rematch + Whimsicott, Ribombee |
| JAMES_3 | PetalburgWoods | route t3 | 5 | 37–39 | Ninjask 39 | emerald-rematch + Vespiquen, Lokix |
| TRENT_3 | Route112 | route t3 | 5 | 38–40 | Golem 40 | emerald-rematch + Coalossal, Gigalith |
| DEZ_AND_LUKE | MtPyre_2F | route | 4 | 36–37 | Manectric 37 | enhanced |
| KIRA_AND_DAN_3 | AbandonedShip_Rooms2_1F | route t3 | 4 | 39–40 | Illumise 40 | emerald-rematch |
| KEIGO | Route120 | route | 4 | 35–36 | Ninjask 36 | enhanced + Skuntank, Salazzle |
| RILEY | Route120 | route | 4 | 35–36 | Ninjask 36 | enhanced + Zoroark, Skuntank |
| BRENDAN_LILYCOVE | LilycoveCity | route | 5 | 40–43 | Sceptile 43 | story |
| WALLY_LILYCOVE | LilycoveCity | route | 5 | 40–43 | Gallade 43 | story |
| MAY_LILYCOVE | LilycoveCity | route | 5 | 40–43 | Blaziken 43 | story |
| JONAH | Route127 | route | 4 | 37–39 | Sharpedo 39 | enhanced + Wishiwashi, Drednaw |
| HENRY | Route127 | route | 4 | 37–39 | Tentacruel 39 | enhanced + Wishiwashi, Barraskewda |
| ROGER | Route127 | route | 4 | 37–39 | Sharpedo 39 | oras-first |
| ALEXA | Route128 | route | 5 | 38–40 | Azumarill 40 | enhanced + Toxapex, Lilligant |
| RUBEN | Route128 | route | 5 | 38–40 | Shiftry 40 | enhanced |
| KOJI_1 | Route127 | route | 4 | 38–40 | Machamp 40 | emerald-rematch |
| WAYNE | Route128 | route | 4 | 38–40 | Wailord 40 | enhanced + Toxapex, Bruxish |
| AIDAN | Route127 | route | 4 | 37–39 | Skarmory 39 | enhanced + Staraptor, Toucannon |
| REED | Route129 | route | 4 | 38–40 | Sharpedo 40 | enhanced |
| TISHA | Route129 | route | 4 | 38–40 | Azumarill 40 | oras-first |
| KIM_AND_IRIS | Route125 | route | 4 | 36–38 | Camerupt 38 | enhanced |
| RELI_AND_IAN | Route131 | route | 4 | 39–41 | Azumarill 41 | enhanced |
| LILA_AND_ROY_1 | Route124 | route | 4 | 35–37 | Sharpedo 37 | emerald-rematch |
| LILA_AND_ROY_2 | Route124 | route t2 | 4 | 37–39 | Sharpedo 39 | emerald-rematch |
| LILA_AND_ROY_3 | Route124 | route t3 | 4 | 39–41 | Sharpedo 41 | emerald-rematch |
| GRUNT_MAGMA_HIDEOUT_1 | MagmaHideout_1F | grunt | 4 | 38–39 | Golbat 39 | enhanced + Salazzle |
| GRUNT_MAGMA_HIDEOUT_2 | MagmaHideout_1F | grunt | 4 | 38–39 | Mightyena 39 | enhanced + Excadrill |
| GRUNT_MAGMA_HIDEOUT_3 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Camerupt 39 | enhanced + Heatmor |
| GRUNT_MAGMA_HIDEOUT_4 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Claydol 39 | enhanced + Gigalith |
| GRUNT_MAGMA_HIDEOUT_5 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Camerupt 39 | enhanced + Coalossal |
| GRUNT_MAGMA_HIDEOUT_6 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Mightyena 40 | enhanced + Mudsdale |
| GRUNT_MAGMA_HIDEOUT_7 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Crobat 40 | enhanced + Centiskorch |
| GRUNT_MAGMA_HIDEOUT_8 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Mightyena 40 | enhanced + Hippowdon |
| GRUNT_MAGMA_HIDEOUT_9 | MagmaHideout_3F_1R | grunt | 4 | 39–40 | Golbat 40 | enhanced + Pyroar |
| GRUNT_MAGMA_HIDEOUT_10 | MagmaHideout_3F_2R | grunt | 4 | 40–41 | Mightyena 41 | enhanced + Garganacl |
| GRUNT_MAGMA_HIDEOUT_11 | MagmaHideout_4F | grunt | 4 | 40–41 | Claydol 41 | enhanced + Krookodile |
| GRUNT_MAGMA_HIDEOUT_12 | MagmaHideout_4F | grunt | 4 | 40–41 | Camerupt 41 | enhanced + Sandaconda |
| GRUNT_MAGMA_HIDEOUT_13 | MagmaHideout_4F | grunt | 4 | 40–41 | Crobat 41 | enhanced + Rampardos |
| GRUNT_MAGMA_HIDEOUT_14 | MagmaHideout_2F_1R | grunt | 4 | 38–39 | Mightyena 39 | enhanced + Glimmora |
| GRUNT_MAGMA_HIDEOUT_15 | MagmaHideout_2F_2R | grunt | 4 | 39–40 | Camerupt 40 | enhanced + Hippowdon |
| GRUNT_MAGMA_HIDEOUT_16 | MagmaHideout_3F_1R | grunt | 4 | 39–40 | Claydol 40 | enhanced + Talonflame |
| TABITHA_MAGMA_HIDEOUT | MagmaHideout_4F | admin | 5 | 39–42 | Camerupt 42 | enhanced |
| DARCY | Route132 | route | 5 | 39–41 | Camerupt 41 | enhanced + Bewear, Clawitzer |
| MAKAYLA | Route132 | route | 5 | 39–41 | Medicham 41 | enhanced + Hawlucha, Grapploct |
| LEONEL | Route120 | route | 4 | 35–36 | Manectric 36 | enhanced + Palpitoad, Pyroar |
| CALLIE | Route120 | route | 4 | 36–37 | Medicham 37 | enhanced + Lucario, Bewear |
| CALE | Route121 | route | 4 | 36–37 | Dustox 37 | enhanced + Galvantula, Golisopod |
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
| FERNANDO_2 | Route123 | route t2 | 4 | 38–40 | Exploud 40 | emerald-rematch + Luxray, Rotom |
| FERNANDO_3 | Route123 | route t3 | 5 | 39–41 | Exploud 41 | emerald-rematch + Luxray, Rotom |
| SAWYER_3 | MtChimney | route t3 | 5 | 38–40 | Golem 40 | emerald-rematch + Coalossal, Mudsdale |
| GABRIELLE_2 | MtPyre_3F | route t2 | 4 | 38–39 | Mightyena 39 | emerald-rematch |
| GABRIELLE_3 | MtPyre_3F | route t3 | 5 | 40–41 | Swellow 41 | emerald-rematch |
| THALIA_3 | AbandonedShip_Rooms_1F | route t3 | 5 | 38–40 | Seadra 40 | emerald-rematch |
| NERINE_MT_PYRE_DEINO_CHARMANDER | MtPyre_Summit | route | 5 | 40–43 | Feraligatr 43 | story |
| NERINE_MT_PYRE_DEINO_TOTODILE |  | route | 5 | 40–43 | Sceptile 43 | story |
| NERINE_MT_PYRE_DEINO_TREECKO |  | route | 5 | 40–43 | Charizard 43 | story |
| NERINE_MT_PYRE_DREEPY_CHARMANDER |  | route | 5 | 40–43 | Feraligatr 43 | story |
| NERINE_MT_PYRE_DREEPY_TOTODILE |  | route | 5 | 40–43 | Sceptile 43 | story |
| NERINE_MT_PYRE_DREEPY_TREECKO |  | route | 5 | 40–43 | Charizard 43 | story |
| NERINE_MT_PYRE_JANGMO_O_CHARMANDER |  | route | 5 | 40–43 | Feraligatr 43 | story |
| NERINE_MT_PYRE_JANGMO_O_TOTODILE |  | route | 5 | 40–43 | Sceptile 43 | story |
| NERINE_MT_PYRE_JANGMO_O_TREECKO |  | route | 5 | 40–43 | Charizard 43 | story |
| NERINE_AQUA_HIDEOUT_DEINO_CHARMANDER | AquaHideout_B2F | route | 6 | 41–44 | Feraligatr 44 | story |
| NERINE_AQUA_HIDEOUT_DEINO_TOTODILE |  | route | 6 | 41–44 | Sceptile 44 | story |
| NERINE_AQUA_HIDEOUT_DEINO_TREECKO |  | route | 6 | 41–44 | Charizard 44 | story |
| NERINE_AQUA_HIDEOUT_DREEPY_CHARMANDER |  | route | 6 | 41–44 | Feraligatr 44 | story |
| NERINE_AQUA_HIDEOUT_DREEPY_TOTODILE |  | route | 6 | 41–44 | Sceptile 44 | story |
| NERINE_AQUA_HIDEOUT_DREEPY_TREECKO |  | route | 6 | 41–44 | Charizard 44 | story |
| NERINE_AQUA_HIDEOUT_JANGMO_O_CHARMANDER |  | route | 6 | 41–44 | Feraligatr 44 | story |
| NERINE_AQUA_HIDEOUT_JANGMO_O_TOTODILE |  | route | 6 | 41–44 | Sceptile 44 | story |
| NERINE_AQUA_HIDEOUT_JANGMO_O_TREECKO |  | route | 6 | 41–44 | Charizard 44 | story |
| BRENDAN_JAGGED_PASS | JaggedPass | route | 5 | 42–44 | Sceptile 44 | story |

### S8 (cap 48) – Space Center, Seafloor Cavern, Sky Pillar, Juan

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| GRUNT_SEAFLOOR_CAVERN_1 | SeafloorCavern_Room1 | grunt | 4 | 41–42 | Mightyena 42 | enhanced + Barbaracle |
| GRUNT_SEAFLOOR_CAVERN_2 | SeafloorCavern_Room1 | grunt | 4 | 41–42 | Sharpedo 42 | enhanced + Zoroark |
| GRUNT_SEAFLOOR_CAVERN_3 | SeafloorCavern_Room4 | grunt | 4 | 42–43 | Crobat 43 | enhanced + Drednaw |
| GRUNT_SEAFLOOR_CAVERN_4 | SeafloorCavern_Room4 | grunt | 4 | 42–43 | Sharpedo 43 | enhanced + Jellicent |
| GRUNT_SPACE_CENTER_1 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 40–41 | Camerupt 41 | enhanced + Hippowdon |
| SHELLY_SEAFLOOR_CAVERN | SeafloorCavern_Room3 | admin | 6 | 44–46 | Sharpedo 46 | enhanced |
| ARCHIE | SeafloorCavern_Room9 | boss | 6 | 46–48 | Sharpedo 48 | enhanced |
| ROSE_4 | Route118 | route t4 | 4 | 42–45 | Roserade 45 | emerald-rematch + Lilligant, Shiinotic |
| DUSTY_4 | Route111 | route t4 | 4 | 42–45 | Sandslash 45 | emerald-rematch + Tyrantrum, Aurorus |
| GABBY_AND_TY_6 |  | route | 4 | 44–45 | Exploud 45 | emerald-rematch |
| LOLA_4 | Route109 | route t4 | 4 | 42–45 | Azumarill 45 | emerald-rematch |
| RICKY_4 | Route109 | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch |
| WILTON_4 | Route111 | route t4 | 5 | 42–45 | Hariyama 45 | emerald-rematch + Fraxure, Talonflame |
| BROOKE_4 | Route111 | route t4 | 5 | 42–45 | Roserade 45 | emerald-rematch + Purugly, Kilowattrel |
| VALERIE_4 | MtPyre_6F | route t4 | 5 | 42–45 | Mismagius 45 | emerald-rematch + Mismagius, Polteageist |
| DAPHNE | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Starmie 46 | enhanced + Alomomola, Lumineon |
| GRUNT_SPACE_CENTER_2 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 41–42 | Camerupt 42 | enhanced + Pyroar |
| BRIANNA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Corsola 46 | oras-first + Floatzel, Jellicent |
| CINDY_5 | Route104 | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch + Pyroar, Whimsicott |
| CONNIE | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Seaking 46 | enhanced + Swanna, Toxapex |
| BRIDGET | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Azumarill 46 | enhanced + Lumineon, Barbaracle |
| OLIVIA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Ludicolo 46 | enhanced + Barraskewda, Clawitzer |
| TIFFANY | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Wailord 46 | oras-first + Palafin, Drednaw |
| JESSICA_4 | Route121 | route t4 | 4 | 42–45 | Seviper 45 | emerald-rematch + Krookodile, Salazzle |
| WINSTON_4 | Route104 | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch + Pyroar, Unfezant |
| STEVE_4 | Route114 | route t4 | 4 | 42–45 | Rhydon 45 | emerald-rematch |
| TONY_4 | Route107 | route t4 | 5 | 42–45 | Sharpedo 45 | emerald-rematch + Jellicent, Lumineon |
| NOB_4 | Route115 | route t4 | 5 | 42–45 | Machamp 45 | emerald-rematch |
| DALTON_4 | Route118 | route t4 | 5 | 42–45 | Magneton 45 | emerald-rematch + Chatot, Rotom |
| BERNIE_4 | Route114 | route t4 | 5 | 42–45 | Magcargo 45 | emerald-rematch |
| ETHAN_4 | JaggedPass | route t4 | 4 | 42–45 | Linoone 45 | emerald-rematch + Skuntank, Mudsdale |
| JEFFREY_4 | Route120 | route t4 | 5 | 42–45 | Masquerain 45 | emerald-rematch + Golisopod, Larvesta |
| CAMERON_4 | Route123 | route t4 | 5 | 42–45 | Alakazam 45 | emerald-rematch |
| JACKI_4 | Route123 | route t4 | 5 | 42–45 | Alakazam 45 | emerald-rematch |
| WALTER_4 | Route121 | route t4 | 5 | 42–45 | Manectric 45 | emerald-rematch + Stoutland, Pyroar |
| JUAN_1 | SootopolisCity_Gym_1F | leader | 6 | 44–48 | Kingdra 48 | emerald-rematch |
| JERRY_4 | Route116 | route t4 | 4 | 42–45 | Gardevoir 45 | emerald-rematch + Pawniard, Musharna |
| KAREN_4 | Route116 | route t4 | 4 | 42–45 | Breloom 45 | emerald-rematch |
| ANNA_AND_MEG_4 | Route117 | route t4 | 4 | 43–45 | Hariyama 45 | emerald-rematch |
| MIGUEL_4 | Route103 | route t4 | 4 | 42–45 | Delcatty 45 | emerald-rematch |
| BETHANY | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Azumarill 46 | enhanced + Palafin, Wishiwashi |
| ISABEL_4 | Route110 | route t4 | 4 | 42–45 | Minun 45 | emerald-rematch |
| TIMOTHY_4 | Route115 | route t4 | 4 | 42–45 | Hariyama 45 | emerald-rematch + Hawlucha, Gurdurr |
| SHELBY_4 | MtChimney | route t4 | 4 | 42–45 | Hariyama 45 | emerald-rematch + Lucario, Hawlucha |
| CALVIN_4 | Route102 | route t4 | 4 | 42–45 | Mightyena 45 | emerald-rematch + Greedent, Gumshoos |
| ELLIOT_4 | Route106 | route t4 | 5 | 42–45 | Gyarados 45 | emerald-rematch |
| BENJAMIN_4 | Route110 | route t4 | 4 | 42–45 | Magneton 45 | emerald-rematch + Klang, Zebstrika |
| ABIGAIL_4 | Route110 | route t4 | 4 | 42–45 | Magneton 45 | emerald-rematch |
| DYLAN_4 | Route117 | route t4 | 4 | 42–45 | Dodrio 45 | emerald-rematch |
| MARIA_4 | Route117 | route t4 | 4 | 42–45 | Dodrio 45 | emerald-rematch |
| ISAIAH_4 | Route128 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch + Floatzel, Toxapex |
| KATELYN_4 | Route128 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch |
| BENNY | Route110_TrickHousePuzzle6 | route | 4 | 42–44 | Swellow 44 | enhanced + Corviknight, Toucannon |
| ROBERT_4 | Route120 | route t4 | 5 | 42–45 | Altaria 45 | emerald-rematch + Staraptor, Corviknight |
| LAO_4 | Route113 | route t4 | 5 | 42–45 | Weezing 45 | emerald-rematch + Toxicroak, Skuntank |
| CYNDY_4 | Route115 | route t4 | 4 | 42–45 | Hariyama 45 | emerald-rematch |
| MADELINE_4 | Route113 | route t4 | 5 | 42–45 | Camerupt 45 | emerald-rematch |
| JENNY_4 | Route124 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch + Alomomola, Lumineon |
| DIANA_4 | JaggedPass | route t4 | 4 | 42–45 | Altaria 45 | emerald-rematch |
| AMY_AND_LIV_5 | Route103 | route t4 | 4 | 43–45 | Minun 45 | emerald-rematch |
| ERNEST_4 | Route125 | route t4 | 5 | 42–45 | Machamp 45 | emerald-rematch |
| ANNIKA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Milotic 46 | enhanced + Alomomola, Seismitoad |
| EDWIN_4 | Route110 | route t4 | 5 | 42–45 | Shiftry 45 | emerald-rematch |
| BRENDAN_MOSSDEEP | MossdeepCity_SpaceCenter_2F | route | 3 | 46–47 | Sceptile 47 | story |
| MAXIE_SOOTOPOLIS | SootopolisCity | boss | 6 | 46–48 | Camerupt 48 | story |
| MAXIE_SOOTOPOLIS_MULTI | SootopolisCity | boss | 3 | 46–48 | Camerupt 48 | story |
| ARCHIE_SOOTOPOLIS_MULTI | SootopolisCity | boss | 3 | 46–48 | Sharpedo 48 | story |
| ISAAC_4 | Route117 | route t4 | 6 | 42–45 | Hariyama 45 | emerald-rematch |
| LYDIA_4 | Route117 | route t4 | 6 | 42–45 | Azumarill 45 | emerald-rematch |
| SEBASTIAN | Route110_TrickHousePuzzle6 | route | 4 | 42–44 | Aggron 44 | oras-first |
| JACKSON_4 | Route119 | route t4 | 5 | 42–45 | Breloom 45 | emerald-rematch + Unfezant, Toucannon |
| SOPHIA | Route110_TrickHousePuzzle6 | route | 4 | 42–44 | Altaria 44 | enhanced |
| CATHERINE_4 | Route119 | route t4 | 4 | 42–45 | Roserade 45 | emerald-rematch + Excadrill, Tsareena |
| GRUNT_SEAFLOOR_CAVERN_5 | SeafloorCavern_Room3 | grunt | 4 | 43–44 | Mightyena 44 | enhanced + Toxapex |
| GRUNT_SPACE_CENTER_3 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 40–41 | Mightyena 41 | enhanced + Salazzle |
| GRUNT_SPACE_CENTER_4 | MossdeepCity_SpaceCenter_1F | grunt | 4 | 41–42 | Claydol 42 | enhanced + Excadrill |
| GRUNT_SPACE_CENTER_5 | MossdeepCity_SpaceCenter_2F | grunt | 4 | 42–43 | Crobat 43 | enhanced + Centiskorch |
| GRUNT_SPACE_CENTER_6 | MossdeepCity_SpaceCenter_2F | grunt | 4 | 42–43 | Mightyena 43 | enhanced + Coalossal |
| GRUNT_SPACE_CENTER_7 | MossdeepCity_SpaceCenter_2F | grunt | 4 | 42–43 | Claydol 43 | enhanced + Mudsdale |
| HALEY_4 | Route104 | route t4 | 4 | 42–45 | Breloom 45 | emerald-rematch + Whimsicott, Ribombee |
| ANDREA | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Lapras 46 | enhanced + Swanna, Bruxish |
| CRISSY | SootopolisCity_Gym_B1F | gym | 5 | 44–46 | Wailord 46 | enhanced + Basculin, Golisopod |
| JAMES_4 | PetalburgWoods | route t4 | 5 | 42–45 | Ninjask 45 | emerald-rematch + Vespiquen, Lokix |
| TRENT_4 | Route112 | route t4 | 5 | 42–45 | Golem 45 | emerald-rematch + Coalossal, Gigalith |
| KIRA_AND_DAN_4 | AbandonedShip_Rooms2_1F | route t4 | 4 | 43–45 | Gorebyss 45 | emerald-rematch |
| LILA_AND_ROY_4 | Route124 | route t4 | 4 | 43–45 | Sharpedo 45 | emerald-rematch |
| ANDRES_4 | Route105 | route t4 | 5 | 42–45 | Sandslash 45 | emerald-rematch |
| CORY_4 | Route108 | route t4 | 4 | 42–45 | Machamp 45 | emerald-rematch |
| PABLO_4 | Route126 | route t4 | 5 | 42–45 | Starmie 45 | emerald-rematch |
| KOJI_4 | Route127 | route t4 | 5 | 42–45 | Machamp 45 | emerald-rematch |
| CRISTIN_4 | Route121 | route t4 | 5 | 42–45 | Slaking 45 | emerald-rematch |
| FERNANDO_4 | Route123 | route t4 | 5 | 42–45 | Exploud 45 | emerald-rematch + Luxray, Rotom |
| SAWYER_4 | MtChimney | route t4 | 5 | 42–45 | Golem 45 | emerald-rematch + Coalossal, Mudsdale |
| GABRIELLE_4 | MtPyre_3F | route t4 | 6 | 42–45 | Swellow 45 | emerald-rematch |
| THALIA_4 | AbandonedShip_Rooms_1F | route t4 | 5 | 42–45 | Kingdra 45 | emerald-rematch |
| NERINE_SEAFLOOR_DEINO_CHARMANDER | SeafloorCavern_Room9 | route | 6 | 45–48 | Feraligatr 48 | story |
| NERINE_SEAFLOOR_DEINO_TOTODILE |  | route | 6 | 45–48 | Sceptile 48 | story |
| NERINE_SEAFLOOR_DEINO_TREECKO |  | route | 6 | 45–48 | Charizard 48 | story |
| NERINE_SEAFLOOR_DREEPY_CHARMANDER |  | route | 6 | 45–48 | Feraligatr 48 | story |
| NERINE_SEAFLOOR_DREEPY_TOTODILE |  | route | 6 | 45–48 | Sceptile 48 | story |
| NERINE_SEAFLOOR_DREEPY_TREECKO |  | route | 6 | 45–48 | Charizard 48 | story |
| NERINE_SEAFLOOR_JANGMO_O_CHARMANDER |  | route | 6 | 45–48 | Feraligatr 48 | story |
| NERINE_SEAFLOOR_JANGMO_O_TOTODILE |  | route | 6 | 45–48 | Sceptile 48 | story |
| NERINE_SEAFLOOR_JANGMO_O_TREECKO |  | route | 6 | 45–48 | Charizard 48 | story |
| MAY_MOSSDEEP | MossdeepCity | route | 5 | 45–47 | Blaziken 47 | story |

### S9 (cap 60) – Victory Road, Elite Four, Champion

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| FELIX | VictoryRoad_B2F | route | 5 | 53–55 | Medicham 55 | enhanced + Golurk, Barbaracle |
| EDGAR | VictoryRoad_1F | route | 5 | 48–50 | Cacturne 50 | enhanced + Luxray, Bronzong |
| ALBERT | VictoryRoad_1F | route | 5 | 48–50 | Muk 50 | enhanced + Corviknight, Sigilyph |
| SAMUEL | VictoryRoad_B1F | route | 5 | 50–52 | Alakazam 52 | enhanced + Bouffalant, Durant |
| VITO | VictoryRoad_B2F | route | 5 | 52–54 | Shiftry 54 | enhanced + Galvantula, Staraptor |
| OWEN | VictoryRoad_B2F | route | 5 | 52–54 | Wailord 54 | enhanced + Garganacl, Excadrill |
| HOPE | VictoryRoad_1F | route | 5 | 49–51 | Roserade 51 | enhanced + Tsareena, Lurantis |
| SHANNON | VictoryRoad_B1F | route | 5 | 50–52 | Claydol 52 | enhanced + Avalugg, Conkeldurr |
| MICHELLE | VictoryRoad_B1F | route | 5 | 50–52 | Ludicolo 52 | enhanced + Coalossal, Clawitzer |
| CAROLINE | VictoryRoad_B2F | route | 5 | 52–54 | Skarmory 54 | enhanced + Glimmora, Beartic |
| JULIE | VictoryRoad_B2F | route | 5 | 52–54 | Ninetales 54 | enhanced + Garchomp, Hippowdon |
| PATRICIA | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Banette 50 | enhanced |
| JOSHUA | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Alakazam 50 | enhanced |
| ALEXIS | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Gardevoir 50 | enhanced |
| SIDNEY | EverGrandeCity_SidneysRoom | elite | 6 | 54–55 | Absol 55 | oras-rematch |
| PHOEBE | EverGrandeCity_PhoebesRoom | elite | 6 | 54–56 | Dusknoir 56 | oras-rematch |
| GLACIA | EverGrandeCity_GlaciasRoom | elite | 6 | 55–57 | Walrein 57 | oras-rematch |
| DRAKE | EverGrandeCity_DrakesRoom | elite | 6 | 56–58 | Salamence 58 | oras-rematch |
| QUINCY | VictoryRoad_1F | route | 5 | 49–51 | Slaking 51 | enhanced |
| KATELYNN | VictoryRoad_1F | route | 5 | 49–51 | Gardevoir 51 | enhanced |
| WALLACE | EverGrandeCity_ChampionsRoom | elite | 6 | 57–60 | Milotic 60 | enhanced |
| NICOLAS_1 | MeteorFalls_1F_2R | route | 4 | 48–49 | Shelgon 49 | emerald-rematch + Druddigon, Noivern |
| NICOLAS_2 | MeteorFalls_1F_2R | route t2 | 4 | 50–52 | Salamence 52 | emerald-rematch + Druddigon, Noivern |
| NICOLAS_3 | MeteorFalls_1F_2R | route t3 | 5 | 52–54 | Salamence 54 | emerald-rematch + Druddigon, Noivern |
| NICOLAS_4 | MeteorFalls_1F_2R | route t4 | 5 | 54–55 | Salamence 55 | emerald-rematch + Druddigon, Noivern |
| DIANNE | VictoryRoad_B2F | route | 5 | 53–55 | Lanturn 55 | enhanced |
| WALLY_VR_1 | VictoryRoad_1F | route | 5 | 54–57 | Gallade 57 | story |
| MITCHELL | VictoryRoad_B1F | route | 5 | 50–52 | Solrock 52 | enhanced + Bronzong, Sigilyph |
| HALLE | VictoryRoad_B1F | route | 5 | 50–52 | Absol 52 | enhanced + Chandelure, Houndstone |
| JOHN_AND_JAY_1 | MeteorFalls_1F_2R | route | 4 | 48–49 | Hariyama 49 | emerald-rematch |
| JOHN_AND_JAY_2 | MeteorFalls_1F_2R | route t2 | 4 | 50–52 | Hariyama 52 | emerald-rematch |
| JOHN_AND_JAY_3 | MeteorFalls_1F_2R | route t3 | 4 | 52–54 | Hariyama 54 | emerald-rematch |
| JOHN_AND_JAY_4 | MeteorFalls_1F_2R | route t4 | 4 | 54–55 | Hariyama 55 | emerald-rematch |
| MARIELA | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Starmie 50 | enhanced |
| ALVARO | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Alakazam 50 | enhanced |
| EVERETT | Route110_TrickHousePuzzle7 | route | 4 | 48–50 | Arcanine 50 | enhanced + Stoutland, Purugly |

### POST (cap none) – After the Champion (no cap)

| Trainer | Map | Role | Mons | Levels | Ace | Source |
|---|---|---|---|---|---|---|
| ROSE_5 | Route118 | route t5 | 4 | 60–61 | Roserade 61 | emerald-rematch + Lilligant, Shiinotic |
| DUSTY_5 | Route111 | route t5 | 4 | 60–62 | Sandslash 62 | emerald-rematch + Tyrantrum, Aurorus |
| LOLA_5 | Route109 | route t5 | 4 | 60–62 | Azumarill 62 | emerald-rematch |
| RICKY_5 | Route109 | route t5 | 4 | 60–62 | Linoone 62 | emerald-rematch |
| VINCENT | Route110_TrickHousePuzzle8 | route | 5 | 64–66 | Sharpedo 66 | enhanced + Lucario, Zoroark |
| LEROY | Route110_TrickHousePuzzle8 | route | 5 | 65–67 | Starmie 67 | enhanced + Pyroar, Corviknight |
| WILTON_5 | Route111 | route t5 | 5 | 60–62 | Hariyama 62 | emerald-rematch + Haxorus, Talonflame |
| KEIRA | Route110_TrickHousePuzzle8 | route | 5 | 65–67 | Aggron 67 | enhanced |
| BROOKE_5 | Route111 | route t5 | 5 | 60–61 | Roserade 61 | emerald-rematch + Purugly, Kilowattrel |
| VALERIE_5 | MtPyre_6F | route t5 | 5 | 63–65 | Mismagius 65 | emerald-rematch + Mismagius, Polteageist |
| NAOMI | SSTidalCorridor | route | 4 | 65–67 | Roserade 67 | enhanced + Lilligant, Purugly |
| CINDY_6 | Route104 | route t5 | 4 | 60–62 | Linoone 62 | emerald-rematch + Pyroar, Whimsicott |
| JESSICA_5 | Route121 | route t5 | 4 | 64–66 | Seviper 66 | emerald-rematch + Krookodile, Salazzle |
| GARRET | SSTidalCorridor | route | 4 | 65–67 | Azumarill 67 | enhanced |
| WINSTON_5 | Route104 | route t5 | 4 | 60–62 | Linoone 62 | emerald-rematch + Pyroar, Unfezant |
| STEVE_5 | Route114 | route t5 | 4 | 60–62 | Rhyperior 62 | emerald-rematch |
| TONY_5 | Route107 | route t5 | 5 | 62–64 | Sharpedo 64 | emerald-rematch + Jellicent, Lumineon |
| NOB_5 | Route115 | route t5 | 5 | 60–61 | Machamp 61 | emerald-rematch |
| DALTON_5 | Route118 | route t5 | 5 | 60–61 | Magnezone 61 | emerald-rematch + Chatot, Rotom |
| BERNIE_5 | Route114 | route t5 | 5 | 60–62 | Magcargo 62 | emerald-rematch |
| ETHAN_5 | JaggedPass | route t5 | 4 | 60–61 | Linoone 61 | emerald-rematch + Skuntank, Mudsdale |
| JEFFREY_5 | Route120 | route t5 | 6 | 60–63 | Masquerain 63 | emerald-rematch + Golisopod, Volcarona |
| CAMERON_5 | Route123 | route t5 | 5 | 65–67 | Alakazam 67 | emerald-rematch |
| JACKI_5 | Route123 | route t5 | 5 | 64–66 | Alakazam 66 | emerald-rematch |
| MICAH | SSTidalCorridor | route | 5 | 64–66 | Manectric 66 | enhanced + Stoutland, Pyroar |
| THOMAS | SSTidalCorridor | route | 4 | 65–67 | Zangoose 67 | enhanced + Bouffalant, Braviary |
| WALTER_5 | Route121 | route t5 | 5 | 63–65 | Manectric 65 | emerald-rematch + Stoutland, Pyroar |
| JERRY_5 | Route116 | route t5 | 4 | 60–61 | Gardevoir 61 | emerald-rematch + Bisharp, Musharna |
| KAREN_5 | Route116 | route t5 | 4 | 60–62 | Breloom 62 | emerald-rematch |
| ANNA_AND_MEG_5 | Route117 | route t5 | 4 | 61–63 | Hariyama 63 | emerald-rematch |
| COLTON | SSTidalCorridor | route | 5 | 63–65 | Delcatty 65 | enhanced |
| MIGUEL_5 | Route103 | route t5 | 4 | 60–62 | Delcatty 62 | emerald-rematch |
| ISABEL_5 | Route110 | route t5 | 4 | 60–62 | Minun 62 | emerald-rematch |
| TIMOTHY_5 | Route115 | route t5 | 4 | 63–65 | Hariyama 65 | emerald-rematch + Hawlucha, Conkeldurr |
| SHELBY_5 | MtChimney | route t5 | 4 | 62–64 | Hariyama 64 | emerald-rematch + Lucario, Hawlucha |
| CALVIN_5 | Route102 | route t5 | 4 | 60–62 | Mightyena 62 | emerald-rematch + Greedent, Gumshoos |
| ELLIOT_5 | Route106 | route t5 | 5 | 60–62 | Gyarados 62 | emerald-rematch |
| BENJAMIN_5 | Route110 | route t5 | 4 | 62–64 | Magnezone 64 | emerald-rematch + Klinklang, Zebstrika |
| ABIGAIL_5 | Route110 | route t5 | 4 | 61–63 | Magnezone 63 | emerald-rematch |
| DYLAN_5 | Route117 | route t5 | 4 | 61–63 | Dodrio 63 | emerald-rematch |
| MARIA_5 | Route117 | route t5 | 4 | 61–63 | Dodrio 63 | emerald-rematch |
| ISAIAH_5 | Route128 | route t5 | 5 | 66–68 | Starmie 68 | emerald-rematch + Floatzel, Toxapex |
| KATELYN_5 | Route128 | route t5 | 5 | 66–68 | Starmie 68 | emerald-rematch |
| NICOLAS_5 | MeteorFalls_1F_2R | route t5 | 5 | 67–69 | Salamence 69 | emerald-rematch + Druddigon, Noivern |
| ROBERT_5 | Route120 | route t5 | 5 | 63–65 | Altaria 65 | emerald-rematch + Staraptor, Corviknight |
| LAO_5 | Route113 | route t5 | 5 | 60–62 | Weezing 62 | emerald-rematch + Toxicroak, Skuntank |
| CYNDY_5 | Route115 | route t5 | 4 | 60–62 | Hariyama 62 | emerald-rematch |
| MADELINE_5 | Route113 | route t5 | 5 | 61–63 | Camerupt 63 | emerald-rematch |
| JENNY_5 | Route124 | route t5 | 5 | 65–67 | Starmie 67 | emerald-rematch + Alomomola, Lumineon |
| DIANA_5 | JaggedPass | route t5 | 4 | 62–64 | Altaria 64 | emerald-rematch |
| AMY_AND_LIV_6 | Route103 | route t5 | 4 | 60–62 | Minun 62 | emerald-rematch |
| PHILLIP | SSTidalCorridor | route | 4 | 64–66 | Machamp 66 | enhanced + Drednaw, Barraskewda |
| LEONARD | SSTidalCorridor | route | 4 | 64–66 | Machamp 66 | enhanced + Floatzel, Conkeldurr |
| ERNEST_5 | Route125 | route t5 | 5 | 65–67 | Machamp 67 | emerald-rematch |
| EDWIN_5 | Route110 | route t5 | 5 | 60–62 | Shiftry 62 | emerald-rematch |
| STEVEN_MOSSDEEP | MossdeepCity_SpaceCenter_2F | route | 3 | 54–56 | Metagross 56 | story |
| BRENDAN_POSTGAME | LittlerootTown_ProfessorBirchsLab | route | 6 | 75–78 | Sceptile 78 | story |
| MAY_POSTGAME | LittlerootTown_ProfessorBirchsLab | route | 6 | 75–78 | Blaziken 78 | story |
| BRENDAN_POSTGAME_DOUBLE | LittlerootTown_ProfessorBirchsLab | route | 3 | 78–80 | Sceptile 80 | story |
| ASTER_SKY_PILLAR_DEINO | SkyPillar_Outside | route | 6 | 63–65 | Salamence 65 | story |
| ASTER_SKY_PILLAR_DREEPY |  | route | 6 | 63–65 | Salamence 65 | story |
| ISAAC_5 | Route117 | route t5 | 6 | 60–61 | Hariyama 61 | emerald-rematch |
| LYDIA_5 | Route117 | route t5 | 6 | 60–61 | Azumarill 61 | emerald-rematch |
| JACKSON_5 | Route119 | route t5 | 5 | 62–64 | Breloom 64 | emerald-rematch + Unfezant, Toucannon |
| CATHERINE_5 | Route119 | route t5 | 4 | 62–64 | Roserade 64 | emerald-rematch + Excadrill, Tsareena |
| ASTER_SKY_PILLAR_JANGMO_O |  | route | 6 | 63–65 | Salamence 65 | story |
| ASTER_POSTGAME_DEINO | DraconidVillage_Shrine | route | 6 | 75–78 | Salamence 78 | story |
| ASTER_POSTGAME_DREEPY |  | route | 6 | 75–78 | Salamence 78 | story |
| ASTER_POSTGAME_JANGMO_O |  | route | 6 | 75–78 | Salamence 78 | story |
| HALEY_5 | Route104 | route t5 | 4 | 60–61 | Breloom 61 | emerald-rematch + Whimsicott, Ribombee |
| JAMES_5 | PetalburgWoods | route t5 | 5 | 60–61 | Ninjask 61 | emerald-rematch + Vespiquen, Lokix |
| TRENT_5 | Route112 | route t5 | 5 | 60–61 | Golem 61 | emerald-rematch + Coalossal, Gigalith |
| LEA_AND_JED | SSTidalCorridor | route | 4 | 65–67 | Gardevoir 67 | enhanced |
| KIRA_AND_DAN_5 | AbandonedShip_Rooms2_1F | route t5 | 4 | 62–64 | Gorebyss 64 | emerald-rematch |
| WALLY_VR_2 | VictoryRoad_1F | route | 5 | 63–66 | Gallade 66 | story |
| WALLY_VR_3 | VictoryRoad_1F | route t2 | 5 | 67–70 | Gallade 70 | story |
| WALLY_VR_4 | VictoryRoad_1F | route t3 | 5 | 71–74 | Gallade 74 | story |
| WALLY_VR_5 | VictoryRoad_1F | route t4 | 5 | 75–78 | Gallade 78 | story |
| MAY_POSTGAME_DOUBLE | LittlerootTown_ProfessorBirchsLab | route | 3 | 78–80 | Blaziken 80 | story |
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
| FERNANDO_5 | Route123 | route t5 | 5 | 63–65 | Exploud 65 | emerald-rematch + Luxray, Rotom |
| SAWYER_5 | MtChimney | route t5 | 5 | 60–61 | Golem 61 | emerald-rematch + Coalossal, Mudsdale |
| GABRIELLE_5 | MtPyre_3F | route t5 | 6 | 60–63 | Swellow 63 | emerald-rematch |
| THALIA_5 | AbandonedShip_Rooms_1F | route t5 | 5 | 62–64 | Kingdra 64 | emerald-rematch |
| NERINE_POSTGAME_DEINO_CHARMANDER | DraconidVillage | route | 6 | 76–78 | Feraligatr 78 | story |
| NERINE_POSTGAME_DEINO_TOTODILE |  | route | 6 | 76–78 | Sceptile 78 | story |
| NERINE_POSTGAME_DEINO_TREECKO |  | route | 6 | 76–78 | Charizard 78 | story |
| NERINE_POSTGAME_DREEPY_CHARMANDER |  | route | 6 | 76–78 | Feraligatr 78 | story |
| NERINE_POSTGAME_DREEPY_TOTODILE |  | route | 6 | 76–78 | Sceptile 78 | story |
| NERINE_POSTGAME_DREEPY_TREECKO |  | route | 6 | 76–78 | Charizard 78 | story |
| NERINE_POSTGAME_JANGMO_O_CHARMANDER |  | route | 6 | 76–78 | Feraligatr 78 | story |
| NERINE_POSTGAME_JANGMO_O_TOTODILE |  | route | 6 | 76–78 | Sceptile 78 | story |
| NERINE_POSTGAME_JANGMO_O_TREECKO |  | route | 6 | 76–78 | Charizard 78 | story |
| ZINNIA_SKY_PILLAR | SkyPillar_3F | route | 5 | 60–62 | Salamence 62 | story |
| WES_FRONTIER | BattleFrontier_OutsideEast | route | 6 | 82–85 | Ho-Oh 85 | colosseum |
| RED_FRONTIER | BattleFrontier_OutsideEast | route | 6 | 82–85 | Charizard 85 | pwt |
| BLUE_FRONTIER | BattleFrontier_OutsideEast | route | 6 | 82–85 | Alakazam 85 | pwt |
| WES_FRONTIER_MULTI | BattleFrontier_OutsideEast | route | 3 | 82–85 | Ho-Oh 85 | colosseum |
| RED_FRONTIER_MULTI | BattleFrontier_OutsideEast | route | 3 | 82–85 | Charizard 85 | pwt |
| BLUE_FRONTIER_MULTI | BattleFrontier_OutsideEast | route | 3 | 83–85 | Alakazam 85 | pwt |
| LANCE_DRACONID | DraconidVillage | route | 6 | 82–86 | Dragonite 86 | pwt |
