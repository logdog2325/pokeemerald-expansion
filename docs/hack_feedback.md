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
| 1.6 | story | Dialogue with the evil teams matches the disguise; Brendan and May battle the player as a Magma grunt, react after losing and walk off | [~] Rustboro Brendan done; the rest per act |
| 1.7 | story | Fourth rival **Nerine**: Draconid undercover in Team Aqua, counters the egg and the Mega starter (9 team variants), reveal at Seafloor Cavern, schedule of 9 fights | [~] all 75 teams; Petalburg Woods fight scripted |
| 1.8 | story | **Aster** raises the leftover third egg (neither the player's nor Nerine's); the Elder's apprentice | [ ] |
| 1.9 | story | Story add-on Acts 1–7 (village prophecy without Mom, Petalburg Woods recruitment by Courtney, Magma uniform until the Sootopolis turn, Maxie's promotion, reversed Space Center tag battle, uniform removal, Rayquaza ritual, meteor finale with Rayquaza catch, Deoxys boss and Mega Rayquaza, credits after the finale) | [~] Act 1 done (village, rescue, families, woods recruitment + outpost, Rustboro); Petalburg Gym (Act 4) done |
| 1.10 | story | Reputation system (`pre_uniform` / `uniform` / `revealed`): shared NPC scripts, key NPCs, 3–5 townsfolk per town | [ ] |
| 1.11 | story | The Mossdeep battle against Brendan / Steven is not a must-win; Steven is overlevelled | [ ] |
| 1.12 | art | Before the Magma outfit the overworld sprite is the dragon tamer, never Brendan or May | [x] audit: the name-entry screen still drew the rival Brendan/May – fixed; link players too |
| 1.13 | art | Nerine: Aqua-disguise and true Draconid outfit (overworld + front pic), trainer class, music; Courtney | [ ] |
| 1.14 | art | Brief asks for a Zinnia-like scarf/cape with dragon-scale details on the tamer outfit (v1 has a horned headband, D-051) | [ ] |
| 1.15 | balance | Teams from real ORAS rematch data (Serebii is reachable now; v1 had none), Elite Four from their ORAS post-game rematches | [ ] |
| 1.16 | bug | Check that every Mega used exists (Mega Feraligatr included) and record the data source | [x] all 14 exist with sprites; source in D-010 |
| 1.17 | other | `docs/hack_script.md` (all dialogue by scene), playtest guide per act with debug warps | [ ] |
