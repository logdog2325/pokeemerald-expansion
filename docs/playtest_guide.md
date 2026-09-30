# Draconid Emerald – playtest guide

What to play, what to look for, and how to report it. Write findings in
[hack_feedback.md](hack_feedback.md); each one gets fixed and ticked off there.

## Getting the ROM
| Build | Command | File | Use it for |
|---|---|---|---|
| Release | `make release -j$(nproc)` | `pokeemerald-release.gba` | a real playthrough (no debug menu) |
| Debug | `make -j$(nproc)` | `pokeemerald.gba` | jumping around: hold **R** and press **START** in the overworld for the debug menu (warp, flags, vars, give Pokémon/items) |

Any GBA emulator works (mGBA recommended). Savestates from one build don't carry over to another build;
in-game saves do as long as the save layout hasn't changed (every change to it is listed in
[hack_changes.md](hack_changes.md)).

## What's different from Emerald
- You're a **Draconid dragon tamer** from Draconid Village (west of Route 101), not a new kid in
  Littleroot. Pick male or female; the sprites, trainer card and battle back pic are your own.
- **Starter**: a dragon **egg** from the Elder (Deino, Dreepy or Jangmo-o). It hatches at the shrine at Lv 5.
- **Second partner** after the Stone Badge: Prof. Birch waits outside the Rustboro Gym with Charmander,
  Totodile or Treecko (Lv 10).
- **Rivals**: May (Birch's daughter, Blaziken) and Brendan (Sceptile) are separate characters, and you fight
  both of them. **Aster**, the Elder's granddaughter, is a third rival: she speaks in riddles, is obsessed with
  Rayquaza, and her dragon counter-picks your egg. Wally has two extra battles.
- **Team Magma disguise** from the Route 112 cable car to Maxie on Mt. Chimney, and again in the Magma Hideout.
- **Mega Evolution**: the Elder gives you the **Mega Ring** and your second partner's Mega Stone after the
  Magma Hideout. Your dragon has no Mega (Hydreigon, Dragapult and Kommo-o don't have one).
- **Hard level caps** (EXP stops at the cap; Rare Candies too): 15 → 20 → 25 → 30 → 34 → 38 → 44 → 48 by
  badge, then 60 until you're Champion, none after. Trainers are rebuilt around those caps (see
  [hack_trainers.md](hack_trainers.md)); rematches unlock with badges.

## Route with checkpoints
Tick each checkpoint as you pass it; note anything odd with where it happened.

| # | Where | What should happen | Check |
|---|---|---|---|
| 1 | Bedroom, Draconid Village | Mom wakes you; set the wall clock; go downstairs | sprites, clock, stairs |
| 2 | Elder's house | Egg ceremony: pick an egg; Aster reacts to your pick | the three eggs, her counter-pick line |
| 3 | Shrine | Hatching rite (normal hatch animation), partner at Lv 5 | hatch, level, moves |
| 4 | Outside the shrine | Mom gives the Running Shoes | B to run |
| 5 | Draconid Pass | First Aster battle (can't white out; you're healed after) | her Pokémon counters yours |
| 6 | Route 101 | Birch chased by Zigzagoon; your hatchling fights it | battle, warp to the lab |
| 7 | Birch's lab | Birch gives Brendan Treecko and May Torchic; you get the Pokédex and 5 Poké Balls | text, Pokédex works |
| 8 | Route 103 | May battle (losing heals you and the story goes on) | May sends out Torchic |
| 9 | Route 104 (Petalburg Woods entrance) | Brendan battle | |
| 10 | Rustboro | May battle; after the Stone Badge, **Birch outside the Gym** with the second partner | pick, nickname, Lv 10 |
| 11 | Slateport (north exit, after the Oceanic Museum) | May battle | |
| 12 | Mauville / Route 110 | Wally (vanilla); Brendan on Route 110, then he registers in the PokéNav | |
| 13 | Meteor Falls | After Magma takes the meteorite: Aster's riddle and battle | |
| 14 | Route 112 cable car station | Aster hands over the **Team Magma disguise** | your sprite turns into a grunt |
| 15 | Mt. Chimney summit | Beat Maxie: the disguise comes off | sprite back to normal |
| 16 | Petalburg Gym door (after the Heat Badge) | Wally battle before Norman | |
| 17 | Route 119, on the path to Fortree | Brendan (vanilla spot), then Aster further north: she heals you, then Mega Altaria | you can't slip past her |
| 18 | Lilycove | Wally (Mega Gallade) by the Pokémon Center; May and Brendan double battle (needs 2 Pokémon) | |
| 19 | Magma Hideout | The disguise goes back on at the entrance; after Maxie, Aster sends you home | |
| 20 | Draconid Village, Elder | **Mega Ring** + your second partner's Mega Stone | Mega Evolve in the next battle |
| 21 | Mossdeep Space Center | Choose May (YES) or Brendan (NO) as your multi-battle partner vs Maxie and Tabitha | |
| 22 | Sootopolis (after the Rain Badge) | Brendan and May with Megas, one after the other (healed in between) | |
| 23 | Sky Pillar top | Aster's climax (Mega Salamence) before Rayquaza wakes | |
| 24 | Champion's room | May congratulates you | |
| 25 | After the credits | You wake in the Draconid bedroom; downstairs Norman brings the **SS Ticket** and the Lati TV news airs | |
| 26 | Birch's lab (post-game) | May and Brendan singles, then their double; Johto starters as in vanilla | |
| 27 | Draconid shrine (post-game) | Aster rematch | |
| 28 | Battle Frontier (post-game, S.S. Tidal) | **Wes** in the Battle Pyramid's sands, **Red** below Artisan Cave, **Blue** by the Battle Tower door; each battles again whenever asked. After beating one, the attendant by the Tower door runs the **LEGENDS' TAG**: that legend as your partner against the other two (debug: warp to `MAP_BATTLE_FRONTIER_OUTSIDE_EAST` with `FLAG_SYS_GAME_CLEAR` set) | Mega Charizard X, Mega Alakazam, all three partners |

## Things worth pushing on
- **Difficulty**: does each gym leader and ace trainer feel beatable at the cap without grinding past it?
  Note the fight, your team and levels when something feels unfair or too easy.
- **Level caps**: does EXP stop at the cap and pick up again after the next badge? Do Rare Candies refuse
  to go over it?
- **Rematches**: tiers unlock with badges (the PokéNav match call); are rematch teams bigger each time?
- **Both genders**: the male and female tamers have their own sprites everywhere – running, biking, surfing,
  fishing, underwater, contests, the trainer card and the Hall of Fame. Brendan and May never stand in for you.
- **Sequence breaks**: anything you can skip, anyone who stays standing around after their scene, any scene
  that plays twice.
- **Text**: lines that still assume you just moved to Littleroot, or that call the rival by the wrong name.

## Known placeholders (don't report)
- Opening movie and credits bike scenes still show Brendan and May (`TODO(art)`).
- The Rayquaza statue in the shrine and the meteorites use vanilla graphics (`TODO(art)`).
- Magma grunts don't comment on your disguise; they battle you as usual (`TODO(dialogue)`, D-044).
- No ORAS rematch rosters: trainers use their Emerald rematch roster or an enhanced own team
  ([hack_trainers.md](hack_trainers.md)).

## Reporting
Add an entry to [hack_feedback.md](hack_feedback.md): where (map + what you were doing), what happened, what
you expected, and a screenshot or save if you have one. One finding per entry.

## Automated checks (for whoever fixes things)
- `python3 tools/hack/emu/matrix.py -o /tmp/matrix` plays the scripted flow for every gender × egg × second
  starter (18 combinations) in the emulator and checks the opponents, items, sprites and state flags.
- `python3 tools/hack/check_story.py` checks that every new flag and story state is set and read somewhere.
- `python3 tools/hack/trainers/check_party.py --caps --proc` and `check_tiers.py` check the trainer teams.
- `make check` runs the expansion's battle test suite.
