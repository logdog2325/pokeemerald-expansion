# CLAUDE.md – Draconid Emerald (pokeemerald-expansion 1.17.1 fork)

ROM hack: Emerald's story + the Draconid clan. Start of any session: read
`docs/hack_status.md` (roadmap / resume point), then `docs/hack_decisions.md`.

## Build & test
```sh
tools/hack/install_tools.sh          # toolchain, Pillow, Poryscript (idempotent; SessionStart hook runs it)
tools/hack/install_tools.sh --porytiles   # + Porytiles (slow, only for custom tilesets)
make -j$(nproc)                      # -> pokeemerald.gba (debug menu: R + Start)
make release -j$(nproc)              # -> pokeemerald-release.gba (no debug menu)
make check -j$(nproc)                # expansion test suite (~40 min on 4 cores); must stay green
make check TESTS="Mega"              # run a subset by name prefix
```
Baseline: `make` has ~212 pre-existing `libpng warning` lines (asset metadata) – no *new*
warnings are allowed. Send long build/test output to a file and check the exit code.

## Conventions
- New events are written in Poryscript (`*.pory`); `make` generates the `.inc` next to it
  (`poryscript_rules.mk`). Commit both. Vanilla scripts being reworked keep their `.inc`; change
  only the lines that must change (comment `@ Draconid Emerald`) and hook in new scenes written in
  `data/scripts/draconid/*.pory` (or the map's own `scripts.pory` for new maps).
- Connected maps with different tilesets: no secondary metatiles within 8 tiles of the seam
  (`check_seams.py`; `mapbuild.py --write` runs it).
- Use constants / config flags, never magic numbers; match nearby style (see docs/STYLEGUIDE.md).
- Every new/changed flag, var, constant, config option, script → `docs/hack_changes.md`.
- Every default design choice → `docs/hack_decisions.md` (decision, alternatives, why).
- Unfinished work: `TODO(art)` / `TODO(dialogue)` markers, never a broken state.
- Brendan/May are rivals: never overwrite their graphics or use them for the player.
- Don't claim a map/sprite looks right without rendering a preview PNG and looking at it.
- Small buildable steps; `make` + `make check` pass before each commit; push to `draconid-emerald`.

## Tools (details: docs/hack_tools.md)
```sh
# maps
python3 tools/hack/mapgen/render.py map <MapName> -o out.png [--grid --collision --border 2]
python3 tools/hack/mapgen/inspect_map.py <MapName> --rect x,y,w,h [--full]   # real metatile IDs
python3 tools/hack/mapgen/inspect_map.py <MapName> --crop x,y,w,h -o crop.png
python3 tools/hack/mapgen/render.py sheet gTileset_General gTileset_Fallarbor -o sheet.png
# art
python3 tools/hack/art/validate.py <png...>          # indexed, <=16 colours, frame layout
python3 tools/hack/art/contact_sheet.py -o sheet.png <png...> [--pal x.pal]
python3 tools/hack/art/kitbash.py tools/hack/art/recipes/<recipe>.json
python3 tools/hack/art/quantize.py in.png out.png [--pal x.pal]
python3 tools/hack/art/recolor.py in.png --show
python3 tools/hack/mapgen/check_seams.py [MapName...]   # tileset seams across connections
python3 tools/hack/mapgen/check_maps.py [MapName...]    # half trees, invisible walls (elevation pockets)
# porymap
python3 tools/hack/porymap_scripts/register.py      # registers the JS tools in porymap.user.cfg
# emulator regression tests (rerun after every build; savestates chain in one -o dir)
python3 tools/hack/emu/play.py tools/hack/emu/tests/opening.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/route103.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/woods.play -o /tmp/emu      # warp hook (debug build)
python3 tools/hack/emu/play.py tools/hack/emu/tests/rustboro.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/act2.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/act3.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/act4.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/maxie_calls.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/elite_four.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/rivals.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/second_starter.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/aster.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/postgame_home.play -o /tmp/emu
python3 tools/hack/emu/play.py tools/hack/emu/tests/hm_free.play -o /tmp/emu    # HM field moves (debug build)
python3 tools/hack/emu/play.py tools/hack/emu/tests/wild.play -o /tmp/emu       # National Dex, wild battles
python3 tools/hack/emu/play.py tools/hack/emu/tests/draconid_pass.play -o /tmp/emu  # Draconid Pass wild table (after opening.play)
python3 tools/hack/emu/play.py tools/hack/emu/tests/zmoves.play -o /tmp/emu     # Z-Ring, crystals, Z-Moves in battle (the chain; see the file header)
python3 tools/hack/emu/play.py tools/hack/emu/tests/draconid_rivals.play -o /tmp/emu  # Aster/Nerine battles of D-279 - D-283 (the chain; see the file header)
python3 tools/hack/emu/play.py tools/hack/emu/tests/rival_calls.play -o /tmp/emu  # rivals' PokéNav calls (expect_text)
python3 tools/hack/emu/play.py tools/hack/emu/tests/gen49_trainers.play -o /tmp/emu  # four trainers' Gen 4-9 send-outs
python3 tools/hack/emu/play.py tools/hack/emu/tests/frontier_legends.play -o /tmp/emu   # Wes, Red, Blue + the tag
python3 tools/hack/emu/play.py tools/hack/emu/tests/title.play -o /tmp/emu      # title screen from power-on (Regidrago, banner)
python3 tools/hack/emu/matrix.py -o /tmp/matrix       # all 18 gender x egg x second-starter flows
python3 tools/hack/check_story.py                     # every new flag / story state set and read
python3 tools/hack/check_pory.py [--fix]               # every committed .inc matches its .pory (run after merges)
python3 tools/hack/check_wild.py [--info X|--doc]     # wild tables: species legal, levels, Hoenn species kept, 1% Beldum
python3 tools/hack/emu/play.py tools/hack/emu/tests/progression.play -o /tmp/emu  # story-lock fixes (Aqua Hideout entrance)
python3 tools/hack/emu/matrix.py -o /tmp/matrix       # all 18 gender x egg x second-starter flows
python3 tools/hack/check_story.py                     # every new flag / story state set and read
python3 tools/hack/check_progression.py [--leg 4.16] [-v]   # story locks: walk every leg, Act 1 to the post-game (table: tools/hack/progression.json, audit: docs/hack_progression.md)
python3 tools/hack/check_hardlock.py [-v] [--battles]       # hard locks: waitstates, OnFrame/coord loops, losable battles + whiteouts, the village's way home, trapped warps, re-entry (~2-5 min)
python3 tools/hack/emu/play.py tools/hack/emu/tests/hardlock.play -o /tmp/emu   # after act7.play: lock, whiteout, retry and lost-multi-battle facts the checker relies on
python3 tools/hack/emu/play.py tools/hack/emu/tests/trade_evos.play -o /tmp/emu   # after rustboro.play
python3 tools/hack/emu/play.py tools/hack/emu/tests/battle_items.play -o /tmp/emu # after rustboro.play
python3 tools/hack/emu/play.py tools/hack/emu/tests/stones.play -o /tmp/emu       # Dawn / Dusk Stone item balls (after opening.play)
python3 tools/hack/emu/play.py tools/hack/emu/tests/multi_teams.play -o /tmp/emu  # multi team-size check after a wild battle (after opening.play)
python3 tools/hack/emu/play.py tools/hack/emu/tests/bag_room.play -o /tmp/emu     # 44 distinct items fit the Items pocket (after opening.play)
python3 tools/hack/check_progression.py [--leg 4.16] [-v]   # story locks: walk every leg of the v2 story (table: tools/hack/progression.json, audit: docs/hack_progression.md)
python3 tools/hack/check_reputation.py [--missing|--skipped|--doc]   # who reacts to the uniform: every person met in uniform (lines: docs/reputation_dialogue.md, rerun --doc after edits)
python3 tools/hack/emu/play.py tools/hack/emu/tests/trade_evos.play -o /tmp/emu   # after rustboro.play
python3 tools/hack/emu/play.py tools/hack/emu/tests/battle_items.play -o /tmp/emu # after rustboro.play
python3 tools/hack/emu/play.py tools/hack/emu/tests/uniform_npcs.play -o /tmp/emu # after rustboro.play: townsfolk's uniform lines (expect_text), a gift after the line
python3 tools/hack/emu/play.py tools/hack/emu/tests/fades.play -o /tmp/emu && python3 tools/hack/emu/fade_check.py /tmp/emu  # same-screen fades (D-278)
python3 tools/hack/emu/matrix.py -o /tmp/matrix       # all 18 gender x egg x second-starter flows
python3 tools/hack/check_story.py                     # every new flag / story state set and read
python3 tools/hack/check_evos.py                      # no trade evolutions left (table: docs/hack_items.md)
python3 tools/hack/check_megas.py [--write|--problems] # every Mega Stone / Z-Crystal: line obtainable?, sources, post-game lists (D-324)
python3 tools/hack/gen_script_doc.py                  # docs/hack_script.md: all dialogue by scene (rerun after edits)
# trainers (rules: docs/hack_trainers.md)
python3 tools/hack/trainers/check_party.py [batch.party] --caps --proc   # legality, caps, headers, trainerproc
python3 tools/hack/trainers/splice_party.py batch.party                  # merge blocks into trainers.party
python3 tools/hack/trainers/build_segments.py [--list S3]                # segments.json (caps from src/caps.c)
python3 tools/hack/trainers/learnset.py Grovyle --level 23 [--all]       # moves for writing sets
python3 tools/hack/trainers/check_tiers.py                               # rematch tiers grow tier to tier
python3 tools/hack/trainers/gen49.py --coverage                          # Gen 4-9 share per segment, gym types, grunts (D-240)
python3 tools/hack/trainers/report.py                                    # trainer table in docs/hack_trainers.md
python3 tools/hack/trainers/check_strength.py [--ref origin/draconid-emerald]  # no trainer got weaker (tests weaken in memory only)
```
Scratch output (previews, sheets) goes to the session scratchpad, not the repo.
