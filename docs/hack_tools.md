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
| `contact_sheet.py -o out.png <png…> [--pal x.pal]` | enlarged frames on a checkerboard, one row per sheet |
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
comma-separated cycle – until memory equals VALUE, or differs from it when written `!VALUE`),
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
| `setvar NAME V`, `gender M/F`, `default NAME V` (+ `-D NAME=V`) | change a var, the player's gender, script defaults |
| `setflag NAME`, `clearflag NAME` | change a save-block flag, e.g. `setflag FLAG_DEBUG_NO_ENCOUNTER` to walk without wild battles |
| `choose N [MAX]` | tap A until a `dynmultichoice` menu opens, then pick entry N (0 = first) |
| `expect_opponent TRAINER_X` | the last trainer battle's opponent (kept until the next battle; works for lost battles) |
| `expect_trainer TRAINER_X 0/1` | the trainer's defeated flag (only set when the battle is won) |
| `expect_item ITEM_X 0/1` | whether the item is anywhere in the bag |
| `expect_gfx OBJ_EVENT_GFX_X` | the player's current sprite (outfit, gender, avatar state) |

`matrix.py` runs the flow tests for every gender × egg × second starter (18 combinations, 6 chains in
parallel) and prints one line per run:
```sh
python3 tools/hack/emu/matrix.py -o /tmp/matrix [-j 3] [--only F_DREEPY]
```
`opening.play` takes `-D EGG=0|1|2`, `second_starter.play` `-D PICK=… -D SECOND=…`, `aster.play`
`-D EGGNAME=… -D SECOND=… -D STONE=… -D GFX=… -D MAGMA=…` (see the comments at the top of each).

## Story checks – `tools/hack/check_story.py`
```sh
python3 tools/hack/check_story.py
```
Static checks over the compiled scripts, map.json files and C: every Draconid flag is written and read,
every `FLAG_HIDE_*` flag hides an object and toggles (new game sets it and a script clears it, or the
other way round), every story state (`DRACONID_STATE_*`, `ASTER_STATE_*`, …) other than 0 is written.
Record-only flags are warnings; states nothing compares against are notes.
| `savestate F`, `loadstate F` | relative paths are inside the `-o` output directory |

Regression tests live in `tools/hack/emu/tests/` and chain through savestates in one output dir:
```sh
python3 tools/hack/emu/play.py tools/hack/emu/tests/opening.play  -o /tmp/emu   # new game -> Birch's lab
python3 tools/hack/emu/play.py tools/hack/emu/tests/route103.play -o /tmp/emu   # lab -> May on Route 103
python3 tools/hack/emu/play.py tools/hack/emu/tests/woods.play -o /tmp/emu      # warp -> Nerine, Courtney, the uniform
python3 tools/hack/emu/play.py tools/hack/emu/tests/rustboro.play -o /tmp/emu   # Brendan at Rustboro's south edge
python3 tools/hack/emu/play.py tools/hack/emu/tests/rivals.play   -o /tmp/emu   # the other new rival scenes
python3 tools/hack/emu/play.py tools/hack/emu/tests/second_starter.play -o /tmp/emu   # Birch in Rustboro
python3 tools/hack/emu/play.py tools/hack/emu/tests/aster.play          -o /tmp/emu   # Aster arc, disguise, Mega Ring
python3 tools/hack/emu/play.py tools/hack/emu/tests/postgame_home.play  -o /tmp/emu   # SS Ticket / Lati TV at home
python3 tools/hack/emu/play.py tools/hack/emu/tests/release_boot.play   -o /tmp/rel --rom pokeemerald-release.gba
```
`release_boot.play` goes through the real title and new-game menus, since release builds have neither Quickstart
(`newgame`) nor the warp hook; `play.py` maps LTO-renamed symbols (`name.lto_priv.N`) back to their names.
Flow tests set `FLAG_DRACONID_NO_WHITEOUT` so a battle lost by mashing A doesn't end the scene.
Savestates only work with the ROM build that made them; rerun the chain after every rebuild.
Tips: the wall clock needs exact presses (`press A 2 450; press A 2 150; press A 2 40; press UP 2 20;
press A 2 60; mash A 3000`); indoor door mats need an extra `hold DOWN 20`. Exit code 1 on any failed
expectation or `until` timeout, so scripts double as regression tests.
