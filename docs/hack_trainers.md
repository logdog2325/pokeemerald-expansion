# Draconid Emerald – trainers, level caps, AI

Every trainer in the game gets an **enhanced rematch team**: the richest roster the trainer has (their ORAS
rematch team where one is known, otherwise their Emerald rematch roster, otherwise their own team made fuller),
scaled to the point of the story where the player meets them, under a **hard level cap**. This page is the
rulebook; `tools/hack/trainers/` checks it.

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
4. `make`, `make check`, commit.

Tools: `scan_maps.py` (which map fights which trainer), `build_segments.py` (segments.json),
`check_party.py`, `splice_party.py`, `party.py` (the `.party` reader/writer they share).

## Trainer table
<!-- generated by tools/hack/trainers/report.py: segment, levels, party size, source -->
_Filled in once the batches are merged._
