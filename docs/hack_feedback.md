# Draconid Emerald – playtest feedback

One numbered checklist per round, newest round at the top. Categories: **bug / balance / story / art / map**
(plus **other** for handoff items). If a note conflicts with an earlier decision, the latest note wins and
[hack_decisions.md](hack_decisions.md) is updated. How to play and what to look for:
[playtest_guide.md](playtest_guide.md).

Status: `[ ]` open · `[~]` in progress · `[x]` done (commit) · `[-]` won't do (why)

## Round 1 (after v1, commit 94f937d3)

The round came with the full story add-on (saved as [hack_story.md](hack_story.md), source of truth) and the
main brief re-sent with a fourth rival (Nerine). Items:

| # | Category | Item | Status |
|---|---|---|---|
| 1.1 | other | Provide the v1 ROM for phone / AYN Thor testing | [x] zipped release ROM sent (v1) |
| 1.2 | other | Make the session reachable from the laptop | [x] cloud session: claude.ai/code on any device signed in to the account |
| 1.3 | balance | Brendan: Sceptile, Mightyena, Swellow, Slaking, Magcargo, Latios, gained over the story like the ORAS rival | [~] teams written for all 7 fights; scenes per act |
| 1.4 | balance | May: Blaziken, Beautifly, Wailord, Tropius, Delcatty, Latias, same staging | [~] teams written for all 5 fights; scenes per act |
| 1.5 | balance | Starter evolutions at 25 (second stage) and 50 (final) – Hydreigon evolves too late | [x] the three dragon lines (D-107) |
| 1.6 | story | Dialogue with the evil teams matches the disguise; Brendan and May battle the player as a Magma grunt, react after losing and walk off | [~] Rustboro Brendan, Route 110 May, Mauville Wally, Aqua/Magma lines in Acts 1–2 done; the rest per act |
| 1.7 | story | Fourth rival **Nerine**: Draconid undercover in Team Aqua, counters the egg and the Mega starter (9 team variants), reveal at Seafloor Cavern, schedule of 9 fights | [~] all 75 teams; Petalburg Woods, Rusturf and Slateport fights scripted |
| 1.8 | story | **Aster** raises the leftover third egg (neither the player's nor Nerine's); the Elder's apprentice | [ ] |
| 1.9 | story | Story add-on Acts 1–7 (village prophecy without Mom, Petalburg Woods recruitment by Courtney, Magma uniform until the Sootopolis turn, Maxie's promotion, reversed Space Center tag battle, uniform removal, Rayquaza ritual, meteor finale with Rayquaza catch, Deoxys boss and Mega Rayquaza, credits after the finale) | [~] Act 1 done (village, rescue, families, woods recruitment + outpost, Rustboro); Petalburg Gym (Act 4) done |
| 1.10 | story | Reputation system (`pre_uniform` / `uniform` / `revealed`): shared NPC scripts, key NPCs, 3–5 townsfolk per town | [x] 75 NPCs, services, gyms (D-117); key NPCs per act |
| 1.11 | story | The Mossdeep battle against Brendan / Steven is not a must-win; Steven is overlevelled | [ ] |
| 1.12 | art | Before the Magma outfit the overworld sprite is the dragon tamer, never Brendan or May | [x] audit: the name-entry screen still drew the rival Brendan/May – fixed; link players too |
| 1.13 | art | Nerine: Aqua-disguise and true Draconid outfit (overworld + front pic), trainer class, music; Courtney | [ ] |
| 1.14 | art | Brief asks for a Zinnia-like scarf/cape with dragon-scale details on the tamer outfit (v1 has a horned headband, D-051) | [ ] |
| 1.15 | balance | Teams from real ORAS rematch data (Serebii is reachable now; v1 had none), Elite Four from their ORAS post-game rematches | [x] Serebii data scraped and recorded; 27 ORAS first-battle teams, Elite Four ORAS rosters (D-170–D-175); every ORAS rematch trainer already has Emerald tiers (rule 1); Elite Four post-game rematch teams (Megas) used after the Hall of Fame |
| 1.16 | bug | Check that every Mega used exists (Mega Feraligatr included) and record the data source | [x] all 14 exist with sprites; source in D-010 |
| 1.17 | other | `docs/hack_script.md` (all dialogue by scene), playtest guide per act with debug warps | [ ] |
| 1.18 | story | (follow-up note) A battle with **Zinnia** at the Sky Pillar, with her ORAS team (Delta Episode: Goodra, Noivern, Altaria, Tyrantrum Lv 60, Mega Salamence Lv 62) | [~] team from Serebii; scene in the Acts 6–7 finale (Lorekeeper of the Meteor Falls Draconids, mid-climb); sprites being drawn |
| 1.19 | balance | (follow-up) Make sure the levels scale properly | [x] every story fight and variant placed on the round 1 schedule; `check_party.py --caps` 0 errors (D-187) |
| 1.20 | balance | (follow-up) Gen 6 style Exp. Share | [x] key item, party-wide, toggleable; Mr. Stone gives it with the PokéNav (D-185) |
| 1.21 | story | (follow-up) Maxie calls after key story points to point the way | [x] 10 calls, first one on Mr. Briney's boat (replacing "Dad" Norman's) (D-186) |
| 1.22 | balance | (follow-up) Rival teams scale: Brendan's first fight Treecko, Poochyena, Taillow (+ Slakoth past Petalburg Woods) | [x] Rustboro: all four; later fights grow like ORAS (D-187) |
| 1.23 | bug | (follow-up 2) No story locks: every vanilla blocker opens in the v2 order, and every scene that moves the player drops them where nothing blocks the way on | [~] Acts 1–5: `check_progression.py` walks 79 legs, one lock fixed (the Aqua Hideout grunts, D-213); Acts 6–7 legs to add |
| 1.24 | story | (follow-up 2) Maxie stops calling once the player is outed | [x] calls only while `REPUTATION_UNIFORM` and before `MAGMA_STATE_TURNED` (D-186); `maxie_calls.play` checks none after the turn |
| 1.25 | story | (follow-up 2) The real final battle comes after the Sky Pillar: Maxie succeeds, the player + Brendan or May (Mega Latios/Latias) vs Maxie (Primal Groudon) and Archie (Primal Kyogre); the rivals only get their Latis close to the climax | [ ] |
| 1.26 | story | (follow-up 2) Maxie talks like he does in the games (tone, mannerisms); Brendan and May smooth, not clunky or AI-sounding | [~] Acts 1–5 and Maxie's calls rewritten against the vanilla lines, voice sheet `docs/hack_voices.md` (D-210–D-212); Acts 6–7 and the new rival scenes follow it |
| 1.27 | other | (follow-up 2) HMs not needed: once the HM is obtained its field move works without a Pokémon knowing it | [x] HM in the bag + its badge: obstacles work with a stand-in Pokémon, Fly/Flash from the bag, HMs can be forgotten (D-190–D-192); `hm_free.play` |
| 1.28 | balance | (follow-up 2) Wild Pokémon from Gens 4–9 where they fit, and in generic trainers' teams; a 1% Beldum in Granite Cave | [x] 95 species in 281 wild slots, Beldum 1% on every Granite Cave floor, National Dex from the start, 122 generic trainers swap one Pokémon (D-193–D-197, docs/hack_wild.md) |
| 1.29 | story | (follow-up 2) After Maxie and Archie are beaten, Groudon and Kyogre can be found and caught in accessible places; the Latis roam (the rivals release theirs or new ones are spotted) | [ ] |
| 1.30 | story | (follow-up 2) Before the Sky Pillar the Elder calls the player home to catch **Regidrago** in a once-sealed part of the cave where they got their egg | [ ] |
| 1.31 | balance | (follow-up 3) No trade evolutions: those Pokémon evolve at a set level | [x] 30 trade evolutions → level 30/36/42/48 by power, held-item branches kept as level + item (D-216/D-217); `check_evos.py`, `trade_evos.play` |
| 1.32 | story | (follow-up 3) A few more Brendan and May battles | [ ] |
| 1.33 | balance | (follow-up 3) Battle items through the story, scaling with the game: type boosters (Black Glasses, Spell Tag …) early, Choice Band / Choice Scarf / Rocky Helmet … later, maybe sold in stores | [x] a battle-item counter in every Mart, stock by badges (type boosters → Leftovers/Rocky Helmet → Choice items/Life Orb → post-game), Gym Leaders give their booster (D-218–D-220) |
| 1.34 | story | (follow-up 4) More Wally battles; while the player wears the uniform Wally (and Brendan and May) are openly hostile – they're trying to stop Team Magma and protect Hoenn, not knowing the player's true mission | [ ] |
| 1.35 | story | (follow-up 5) Post-game at the Battle Frontier: Wes (Colosseum; Espeon, Umbreon, Raikou, Entei, Suicune, Ho-Oh), Red (PWT team, Mega Charizard X), Blue (PWT team, Mega Alakazam); all three can also be multi-battle partners | [x] at the Battle Frontier after the Hall of Fame, Lv 82–85, rematchable; the Legends' Tag: team with a beaten legend against the other two (D-225–D-229) |
| 1.36 | balance | (follow-up 6) Mega Stones obtainable throughout the story | [x] none before the Mega Ring; 9 item balls at ORAS spots, the counter sells more at 6 and 8 badges, the rest post-game (D-221/D-222, `docs/hack_items.md`) |
| 1.37 | story | (follow-up 7) Prof. Oak (he has an in-game sprite) gives the **second starter** (Charmander / Totodile / Treecko) instead of Birch; the Elder still gives the egg; the Lavaridge traveller keeps giving the Mega Stone | [ ] |
| 1.38 | story | (follow-up 8) The Elder says the eggs come from Galar, Unova and Alola; the egg selection scene and choice are scripted; the egg hatches after about 5 steps | [ ] the choice moves into the shrine (the cave where you got your egg, where Regidrago will wait) |
| 1.39 | bug | (follow-up 9) Once Acts 6–7 are in, no story locks all the way to the post-game | [ ] extend `check_progression.py` after the Acts 6–7 merge |
| 1.40 | balance | (follow-up 9) Trainers get Gen 4–9 Pokémon too, to spice things up | [~] 122 generic trainers swap one (1.28); a second, wider pass (grunts, gym trainers, about half of all generic trainers) |
