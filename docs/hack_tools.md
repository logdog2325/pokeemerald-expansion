# Draconid Emerald – command-line tools

Everything here runs without a GUI and reads the real project data, so metatile IDs,
palettes and sprites are never guessed. Install prerequisites with
`tools/hack/install_tools.sh` (add `--porytiles` for the tileset compiler).

## Maps – `tools/hack/mapgen/`

| Tool | What it does |
|---|---|
| `render.py map <Map> -o out.png [--grid] [--collision] [--border N]` | PNG preview of a map with real sprites, warps (purple), coord events (orange), BG events (cyan) |
| `render.py layout <LAYOUT_ID> -o out.png` | same, layout only |
| `render.py sheet <primary> <secondary> -o out.png` | every metatile with its hex ID |
| `inspect_map.py <Map> --rect x,y,w,h [--full]` | print metatile IDs (`--full`: `id:collision:elevation`) |
| `inspect_map.py <Map> --crop x,y,w,h -o crop.png` | enlarged crop with IDs drawn on each tile |
| `autotile.py learn <brush>` / `stats <brush>` | learn auto-tile rules from vanilla maps |
| `mapbuild.py <spec.json> --preview out.png [--grid --collision --border 2]` | build a map from a spec without touching the project |
| `mapbuild.py <spec.json> --write [--overwrite-events]` | write layout + map + registrations (Porymap-compatible) |
| `export_porymap.py` | export learned rules for the Porymap scripts |

### Brushes and auto-tiling
A brush (`mapgen/brushes/<name>.json`) names a tileset pair, the vanilla maps to learn from
and terrain classes (`tree`, `cliff`, `water`, `path`, `ground`, `grass`, …) as lists of real
metatile IDs. Class members were chosen from review sheets of every metatile the vanilla maps
use (colour-overlap + behaviour + collision proposals, then checked by eye).

`autotile.py learn` labels every cell of the learn-from maps with its class and records which
block (metatile + collision + elevation) the original mappers used for each neighbourhood,
from most to least specific:
`class + 8 neighbour classes + 2×2 phase` → `… without phase` → `4 neighbours` → `same-class
8-mask` → `same-class 4-mask` → `phase only` → brush default.
The 2×2 phase keeps tree patterns whole: every connected tree region is aligned so its
anchor tile (`26B`, a top-left tree quarter) sits on even coordinates. Classes without a 2×2
pattern set `"parity": false`; `"only_near"` bans tiles (e.g. cliff-lip ground) unless a given
class is adjacent. Self-test: re-tiling the vanilla maps from their own class grids reproduces
96% of Fallarbor Town, ~90% of trees/cliffs and ~100% of paths/water.

Brushes: `general_fallarbor` (Fallarbor / Routes 113–115 look: brown dirt, striped cliffs,
round trees, sand paths, ponds, waterfalls, soil plots, olive mountain rock).

### Map specs
`mapgen/specs/<map>.json` is the readable source of a generated map: an ASCII grid (one char per
metatile; chars come from the brush classes or a `legend`), `stamps` copied from vanilla maps
(houses, craters, gardens – real blocks incl. collision/elevation), single `blocks`, `scatter`
decorations, optional elevation grid, header, connections and events. Some specs have a small
`.py` generator next to them that records how the first draft was laid out; after that the JSON
grid can be edited by hand. Specs can instead copy (`copy_layout`) or share (`use_layout`) a
vanilla layout for interiors.

`--write` creates `data/layouts/<Map>/{map,border}.bin`, updates `layouts.json`,
`map_groups.json`, `data/maps/<Map>/map.json`, adds a `scripts.pory` stub and the `.include` in
`data/event_scripts.s`, and adds both directions of each connection. Existing `map.json` events
are kept unless `--overwrite-events`, so Porymap edits survive a re-run.

## Dialogue rewrites – `tools/hack/retext.py`
Replaces the `.string` body of vanilla text labels in a `scripts.inc` (the label keeps its name and gets an
`@ Draconid Emerald` comment); used for every reworked vanilla scene (round 1). New scenes are written in
Poryscript instead (`data/scripts/draconid/act*.pory`).
```sh
python3 tools/hack/retext.py data/maps/PetalburgCity_Gym/scripts.inc changes.json   # {"Label": [".string lines"]}
```

## Script document – `tools/hack/gen_script_doc.py`
Writes `docs/hack_script.md`: every new scene's dialogue (the `.pory` files in story order, one bullet per text
box) and every vanilla text reworked in place (`@ Draconid Emerald` labels), so the text can be reviewed in one
place. Rerun it after dialogue edits; `--check` fails when the document is stale.

## Porymap scripts – `tools/hack/porymap_scripts/`
Register once with `python3 tools/hack/porymap_scripts/register.py` (writes `custom_scripts`
into `porymap.user.cfg` and `use_poryscript=1` into `porymap.project.cfg`), then reopen the
project. Tools menu entries:
- **Draconid: Auto-tile while painting** (toggle, Ctrl+Shift+A) – re-tiles the 5×5 area around
  every painted block of a known class (trees, cliffs, water, paths, ground…).
- **Draconid: Re-auto-tile whole map / rectangle…**
- **Draconid: Fill rectangle with terrain…** – fill with a class, then auto-tile the edges.
- **Draconid: Scatter grass tufts / flowers…**, **Scatter meteorite rocks…**, **Tree border…**

**Seams** – the game draws the cells across a map connection with the *current* map's tilesets.
`check_seams.py [MAP…]` lists every secondary metatile that can be drawn across a seam where the two
maps' tilesets differ (window: 16×16 metatiles around each walkable cell). `mapbuild.py --write`
runs it for the map it wrote. Vanilla has a few such seams already (Route 113/112, Route 134/Slateport…);
new maps must be clean.

They share `autotile_rules.js` (generated by `export_porymap.py`) with `mapbuild.py`; the JS
resolver was checked to give identical output to the Python one.

## Art – `tools/hack/art/`
| Tool | What it does |
|---|---|
| `validate.py <png…> [--profile P] [--manifest m.json]` | indexed PNG, ≤16 colours, index 0 transparent corners, frame size/count per profile |
| `contact_sheet.py -o out.png <png…> [--pal x.pal] [--cols N]` | enlarged frames on a checkerboard, one row per sheet (`--cols N`: N inputs per row); emulator screenshots are shown as they are |
| `quantize.py in.png out.png [--pal x.pal] [--key r,g,b]` | RGBA → indexed, GBA 15-bit colours, index 0 transparent |
| `recolor.py in.png out.png --pal/--set/--remap`, `recolor.py in.png --show` | palette swaps and index remaps |
| `kitbash.py recipe.json` | reproducible sprite builds: load, palette, remap, paste regions, ASCII pixel overlays, frame reorder, save |
Profiles: `ow_walk` (9× 16×32), `ow_mach_bike` (9× 32×32), `ow_acro_bike` (27×), `ow_surf` (6×),
`ow_field_move` (5×), `ow_fishing` (12×), `ow_underwater` (4×), `ow_watering` (6×),
`ow_decorating` (1× 16×32), `trainer_front` (64×64), `trainer_back` (4× 64×64 stacked).

## Scripts – Poryscript
`poryscript_rules.mk` compiles every `data/**/*.pory` to the `.inc` next to it
(`tools/poryscript/poryscript`, configs in `tools/poryscript/`). The generated `.inc` is committed;
if a `.pory` is newer and Poryscript is missing, the build stops with a hint.

## Tilesets – Porytiles
`tools/porytiles/porytiles` (2.0.0, built from source by `install_tools.sh --porytiles`).
See `docs/hack_art_pipeline.md` for the custom tileset workflow.

## Emulator smoke tests – `tools/hack/emu/`
`gbarun` (built by `install_tools.sh` from `gbarun.c` against libmgba) runs the ROM headless from
a text script – `run N`, `press KEYS [hold] [release]`, `hold KEYS N`, `repeat N …`, `shot NAME`,
`savestate/loadstate FILE`, `peek ADDR LEN`, `poke ADDR BYTE` – and writes 240×160 screenshots.
About 3000 frames per second, so a full intro takes seconds.
```sh
tools/hack/emu/gbarun pokeemerald.gba script.txt outdir/
```
More gbarun commands: `until ADDR SIZE VALUE MAX [KEYS PERIOD]` (run, optionally tapping KEYS – a
comma-separated cycle, each entry may be a combination like `A+UP` – until memory equals VALUE, or differs from
it when written `!VALUE`),
`untilhold ADDR SIZE VALUE MAX KEYS`, `read ADDR SIZE LABEL`.
Addresses may be `HEX`, `*HEX` (pointer) or `*HEX+HEX`.

`play.py` wraps gbarun with symbols from `pokeemerald.elf` and constants from the headers:
```sh
python3 tools/hack/emu/play.py test.play -o /tmp/out
```
| `.play` command | Meaning |
|---|---|
| `@SYM`, `@@SYM` | address of an ELF symbol (`@@` = Thumb function pointer) |
| `newgame [MAX]` | Quickstart a new game (tap SELECT until the overworld runs) |
| `mash KEY MAX` | tap KEY (or a cycle `A,UP`) until the player regains control |
| `wait_free MAX` | run until the player regains control |
| `flag NAME`, `var NAME`, `expect_flag NAME 0/1`, `expect_var NAME V` | read the save block; `expect_*` fail the run |
| `walk DIR COORD [MAX]` | hold DIR until the player's x (LEFT/RIGHT) or y (UP/DOWN) equals COORD |
| `pos`, `mapid` | print player coordinates / map group+num |
| `path MAP X0 Y0 X1 Y1` | shortest walk on MAP's collision grid (avoids tall grass, water, warps; jumps down ledges; ignores NPCs) |
| `warp MAP_X X Y [MAX]` | debug builds: warp to (X, Y) on MAP_X the next time the player is free (`gDraconidTestWarp`) |
| `heal` | debug builds: heal the party the next time the player is free |
| `givemon SPECIES_X LEVEL [ITEM_X]`, `giveitem ITEM_X [N]` | debug builds: add a Pokémon (holding ITEM_X) to the party / N items (default 1) to the bag the next time the player is free |
| `expect_party SLOT SPECIES_X` | the species in party slot SLOT (0 = first), decrypted from the box data |
| `expect_text LABEL [BUFFER]` | the text in BUFFER (default `gStringVar4`) starts like the ROM text LABEL (up to 24 bytes, stopping at its first placeholder); e.g. a PokéNav call |
| `settrainer TRAINER_X 0/1` | set or clear a trainer's defeated flag |
| `setvar NAME V`, `gender M/F`, `default NAME V` (+ `-D NAME=V`) | change a var, the player's gender, script defaults |
| `setflag NAME`, `clearflag NAME` | change a save-block flag, e.g. `setflag FLAG_DEBUG_NO_ENCOUNTER` to walk without wild battles |
| `choose N [MAX]` | tap A until a `dynmultichoice` menu opens, then pick entry N (0 = first) |
| `expect_opponent TRAINER_X` | the last trainer battle's opponent (kept until the next battle; works for lost battles) |
| `expect_trainer TRAINER_X 0/1` | the trainer's defeated flag (only set when the battle is won) |
| `expect_item ITEM_X 0/1` | whether the item is anywhere in the bag |
| `expect_gfx OBJ_EVENT_GFX_X` | the player's current sprite (outfit, gender, avatar state) |
| `expect_pos X Y`, `expect_map MAP_X` | the player's map coordinates / the current map |
| `expect_party_hms N` | debug builds: how many HM moves the party's Pokémon know |
| `bagcursor POCKET_X N` | the bag opens on POCKET_X at entry N and the start menu on its first entry (then START, DOWN, DOWN, A opens the bag) |
| `expect_opponent_b TRAINER_X`, `expect_partner PARTNER_X` | opponent B and the in-game partner of the last two-trainer / multi battle |
| `wait_species N SPECIES_X [MAX] [KEY]` | tap KEY (default A) until battler N (`gBattleMons[N]`, 1 = the single-battle opponent) is SPECIES_X, e.g. `SPECIES_CHARIZARD_MEGA_X` after a Mega Evolution |

`matrix.py` runs the flow tests for every gender × egg × second starter (18 combinations, 6 chains in
parallel) and prints one line per run:
```sh
python3 tools/hack/emu/matrix.py -o /tmp/matrix [-j 3] [--only F_DREEPY]
```
`opening.play` takes `-D EGG=0|1|2`, `second_starter.play` `-D PICK=… -D SECOND=… -D MAGMA=…`, `aster.play`
`-D EGGNAME=… -D SECOND=…`, `act2.play` `-D EGGNAME=… -D SECOND=… -D SECONDNAME=… -D GOODS=… -D RETURNED=…`,
`act3.play` `-D EGGNAME=… -D SECOND=… -D SECONDNAME=… -D STONE=…`, `act4.play`
`-D EGGNAME=… -D SECOND=… -D SECONDNAME=… -D MAGMA=…` (see the comments at the top of each).
`frontier_legends.play` (the Battle Frontier legends and the LEGENDS' TAG, post-game) needs only `rustboro_done.ss`
and runs in the Deino chains.
`title.play` (the title screen: the movie into the title, the banner, Regidrago's glow, START → main menu) boots
from power-on, needs no savestate and runs in the Deino chains.

## Story checks – `tools/hack/check_story.py`
```sh
python3 tools/hack/check_story.py
```
Static checks over the compiled scripts, map.json files and C: every Draconid flag is written and read,
every `FLAG_HIDE_*` flag hides an object and toggles (new game sets it and a script clears it, or the
other way round), every story state (`DRACONID_STATE_*`, `ASTER_STATE_*`, …) other than 0 is written.
Record-only flags are warnings; states nothing compares against are notes.

## Wild tables – `tools/hack/check_wild.py`
```sh
python3 tools/hack/check_wild.py                  # checks src/data/wild_encounters.json against master's
python3 tools/hack/check_wild.py --info Beldum    # generation, types, evolutions, flags as this build has them
python3 tools/hack/check_wild.py --changes        # every Hoenn slot that differs from vanilla (Markdown)
python3 tools/hack/check_wild.py --doc            # the same table at the end of docs/hack_wild.md
```
Species data comes from the preprocessed `species_info.h`, so disabled families count as missing. Rules and
the level check (area → story segment, cap + 3 for changed slots) are in docs/hack_wild.md (D-197).
## Story locks – `tools/hack/check_progression.py`
```sh
python3 tools/hack/check_progression.py                 # every leg + the warp check; exit 1 on a lock
python3 tools/hack/check_progression.py --leg 4.16 -v   # one leg (id or a word of its name): path, notes, guesses
python3 tools/hack/check_progression.py --list          # the story table
python3 tools/hack/check_progression.py --markdown      # the leg table for docs/hack_progression.md
python3 tools/hack/check_progression.py --state 4.16 --grep SLATEPORT   # simulated flags/vars/items at a leg
```
Walks the v2 story leg by leg, Act 1 to the post-game (`tools/hack/progression.json`: scene labels in story order,
badges/HMs by then, side trips for the ways back). A static simulator runs the scenes' flag/var/item commands from
the new game on (unknown branches taken both ways, listed with `-v`; enums, the player's scripted movement and the
Hall of Fame's / credits' way home included), checks that each scene can start and that OnFrame scenes move their
var on, then searches the tiles to the next scene across maps: collision, elevation, ledges, doors, arrow/step
warps, dive/emerge, holes, Fly; objects whose flag is clear, turn-back coord triggers, water / waterfalls /
boulders / rocks / trees without the HM **and** badge, bike tiles without a bike. A blocked leg names its first
obstacle and what clears it; a way that opens only through a scene off the path is a detour (DTOR). Also checks
every round 1 and table scene warp destination (walkable, not a closed pocket). ~45 s. Table fields: `to`, `via`,
`then`, `expect`, `pre` + `why` (what C does), `side`, `from`, `at`/`map`/`talk`/`enter`, `assume`, `puzzles`,
`no_heal_ok`. An OnFrame scene a walk passes is only noted: one the story needs gets its own leg (2.06a). A warp
after a branch on `VAR_RESULT` (Poryscript's `compare` + `goto_if` too) is a "may warp": say where with `then`. The
audit and how to extend it: [hack_progression.md](hack_progression.md).
## Hard locks – `tools/hack/check_hardlock.py`
```sh
python3 tools/hack/check_hardlock.py                    # every check; exit 1 on a LOCK (~2 min)
python3 tools/hack/check_hardlock.py -v                 # with the notes: retries, whiteouts, by-design spots
python3 tools/hack/check_hardlock.py --only battle,trap # some checks: lock, wait, frame, coord, battle, trap, reentry
python3 tools/hack/check_hardlock.py --battles [--markdown]   # every round 1 battle and what a loss does
```
Follows every path of the round 1 scripts on its own (no merging; branches it took are remembered) from each place
the game starts one, story-table scenes from the table's simulated state. LOCK / CHECK / NOTE findings with
file:line label: a `waitstate` nothing resumes, a movement without `step_end`, an OnFrame path that changes neither
its var nor the map, a coord trigger the player can't step off, a whiteout whose scene can't start again or can't be
walked back to from the Pokémon Centers passed (rides and Mr. Briney included), a scene warp landing with no heal
location or next scene in reach, an early way out of a story scene that can't be retried, a loss that sends the
player elsewhere (the village's `Draconid_EventScript_VillageLost`) with no way back to the fight; an unreleased
`lock`/`lockall` is only a CHECK (the engine frees the player when a script ends – D-264). A loss that goes on is its
own path (no trainer flags, `GetBattleOutcome` lost), and multi battles never white out (D-265a). The emulator side
is `tests/hardlock.play`; details and the findings in [hack_progression.md](hack_progression.md).
## Evolution check – `tools/hack/check_evos.py`
```sh
python3 tools/hack/check_evos.py [--markdown]
```
No species may keep a trade evolution (D-216), and no held-item level branch may be hidden behind an earlier
unconditional level entry (the first matching entry wins). Prints the former trade evolutions with level, held
item and base stat totals; `--markdown` gives the table in [hack_items.md](hack_items.md).
| `savestate F`, `loadstate F` | relative paths are inside the `-o` output directory |

Regression tests live in `tools/hack/emu/tests/` and chain through savestates in one output dir:
```sh
python3 tools/hack/emu/play.py tools/hack/emu/tests/opening.play  -o /tmp/emu   # new game -> Birch's lab
python3 tools/hack/emu/play.py tools/hack/emu/tests/route103.play -o /tmp/emu   # lab -> May on Route 103
python3 tools/hack/emu/play.py tools/hack/emu/tests/woods.play -o /tmp/emu      # warp -> Nerine, Courtney, the uniform
python3 tools/hack/emu/play.py tools/hack/emu/tests/rustboro.play -o /tmp/emu   # Brendan at Rustboro's south edge
python3 tools/hack/emu/play.py tools/hack/emu/tests/rivals.play   -o /tmp/emu   # the other new rival scenes
python3 tools/hack/emu/play.py tools/hack/emu/tests/second_starter.play -o /tmp/emu   # Prof. Oak in Rustboro
python3 tools/hack/emu/play.py tools/hack/emu/tests/aster.play          -o /tmp/emu   # Aster at Meteor Falls, Sky Pillar, post-game
python3 tools/hack/emu/play.py tools/hack/emu/tests/act2.play           -o /tmp/emu   # Devon Goods, museum, Route 110, Mr. Briney
python3 tools/hack/emu/play.py tools/hack/emu/tests/act3.play           -o /tmp/emu   # Meteor Falls, Mt. Chimney, Mega Ring, Lavaridge
python3 tools/hack/emu/play.py tools/hack/emu/tests/act4.play           -o /tmp/emu   # Weather Institute … Maxie's promotion
python3 tools/hack/emu/play.py tools/hack/emu/tests/maxie_calls.play    -o /tmp/emu   # Maxie's PokéNav calls
python3 tools/hack/emu/play.py tools/hack/emu/tests/elite_four.play     -o /tmp/emu   # E4 post-game rematch swap
python3 tools/hack/emu/play.py tools/hack/emu/tests/postgame_home.play  -o /tmp/emu   # SS Ticket / Lati TV at home
python3 tools/hack/emu/play.py tools/hack/emu/tests/hm_free.play        -o /tmp/emu   # HM field moves without a Pokémon (D-190)
python3 tools/hack/emu/play.py tools/hack/emu/tests/wild.play           -o /tmp/emu   # National Dex, wild battles, a Gen 4-9 trainer swap
python3 tools/hack/emu/play.py tools/hack/emu/tests/progression.play    -o /tmp/emu   # story-lock fixes: the Aqua Hideout opens with Maxie's order
python3 tools/hack/emu/play.py tools/hack/emu/tests/hardlock.play       -o /tmp/emu   # after act7.play: an unreleased lock, a whiteout, a retry, a lost village multi battle (D-264, D-265a)
python3 tools/hack/emu/play.py tools/hack/emu/tests/trade_evos.play     -o /tmp/emu   # Kadabra -> Alakazam, Slowpoke + King's Rock -> Slowking
python3 tools/hack/emu/play.py tools/hack/emu/tests/battle_items.play   -o /tmp/emu   # battle item counter by badges, a Gym booster, a Mega Stone ball
python3 tools/hack/emu/play.py tools/hack/emu/tests/rival_calls.play    -o /tmp/emu   # after act5.play: the rivals' and Mr. Stone's PokéNav calls (D-243, D-256, D-258)
python3 tools/hack/emu/play.py tools/hack/emu/tests/release_boot.play   -o /tmp/rel --rom pokeemerald-release.gba
```
`release_boot.play` goes through the real title and new-game menus, since release builds have neither Quickstart
(`newgame`) nor the warp hook; `play.py` maps LTO-renamed symbols (`name.lto_priv.N`) back to their names.
Flow tests set `FLAG_DRACONID_NO_WHITEOUT` so a battle lost by mashing A doesn't end the scene.
Savestates only work with the ROM build that made them; rerun the chain after every rebuild.
`battlepp N [VALUE]` refills battler N's PP mid-battle (a long mashed battle otherwise loops on "There's no PP left").
`callscript LABEL` (debug builds) starts any event script the next time the player is free (the test hook in
`include/draconid.h`). `tests/fades.play` + `fade_check.py OUTDIR` check that same-screen fades bring the picture back
unchanged under weather and the day/night tint (D-278); the matrix runs both.
`play.py` stamps each savestate it writes with the ROM's SHA-1 (`F.ss.rom`) and prints a WARNING when a test loads
one made by another build (or an unstamped one older than the ROM). A stale savestate either resets the game to the
intro (the test then times out) or crashes it: mGBA logs "Jumped to invalid address: …" on every instruction.
`gbarun` prints only the first 10 emulator errors, and after 100 it stops with exit code 3 and one line
("gbarun: GAME CRASHED … is the savestate from an older ROM build?"), which `play.py` reports as
"FAIL: the game crashed during …". (Before this, the error flood grew play.py's captured output by ~16 MB/s until
the OOM killer stepped in – killing parallel runs.) A healthy run logs no emulator errors at all.
Tips: the wall clock needs exact presses (`press A 2 450; press A 2 150; press A 2 40; press UP 2 20;
press A 2 60; mash A 3000`); indoor door mats need an extra `hold DOWN 20`. Exit code 1 on any failed
expectation or `until` timeout, so scripts double as regression tests.
