# Draconid Emerald – art pipeline

How the hack's sprites are made, so they can be rebuilt, polished or extended. No third-party
art is bundled: everything is either drawn here or derived from art already in this repository
(Game Freak's own sprites shipped with pokeemerald-expansion). Brendan's and May's graphics are
never used for the player and never modified (they are the rivals).

Tools: `tools/hack/art/` (validate, contact sheet, quantize, recolor, kitbash) and
`tools/hack/art/player/` (player outfits). Previews go to the scratchpad, not the repo.

## Player outfits (Phase 2)

Four sets: Draconid tamer M/F (`draconid_m`, `draconid_f`) and Team Magma disguise M/F
(`magma_m`, `magma_f`). Each set has every avatar state the engine uses.

| Sheet | Frames | Source |
|---|---|---|
| `walking.png` | 9 × 16×32 | FRLG `red_normal` / `green_normal` |
| `running.png` | 9 × 16×32 | FRLG `*_surf_run` frames 3,6,9,4,5,7,8,10,11 (Emerald order) |
| `surfing.png` | 3 × 16×32 (sitting; the surf blob is a field effect) | `*_surf_run` 0–2 |
| `bike.png` (Mach) | 9 × 32×32 | `*_bike` |
| `acro_bike.png` | 27 × 32×32 | bike frames 0–8 + wheelie/hop frames made by shifting/shearing them – `TODO(art)` hand polish |
| `field_move.png` | 5 × 16×32 | `*_item` 0–4 |
| `fishing.png` | 12 × 32×32 | `*_fish` |
| `underwater.png` | 4 × 32×32 | surfing frames, recoloured by brightness into the shared `player_underwater.pal` |
| `watering.png` | 6 × 32×32 | walk frames + a drawn watering can – `TODO(art)` |
| `decorating.png` | 1 × 16×32 | walk frame 2 |
| region map icon | 16×16 | head of walk frame 0 → `graphics/pokenav/region_map/<set>_icon.png` |
| trainer front pic | 64×64 | FRLG Red/Leaf front pic (Magma disguise: the vanilla Magma Grunt front pics) |
| trainer back pic | 5 × 64×64 (idle + throw) | FRLG Red/Leaf back pic, `sBackAnims_Kanto` |

### How a set is built
`tools/hack/art/player/build_player.py <set>.json` (overworld) and `build_pics.py <set>_pics.json`
(trainer pics):
1. Copy the base frames (Red for M, Leaf for F).
2. Swap the palette. The new palette keeps the base's **index roles** (e.g. Red's jacket indices
   8/B/C become the Draconid teal, the Magma red), so bodies recolour for free.
3. Replace the headwear: the largest blob of the old hat's colours anchors a **head template**
   (ASCII rows, one per view: `down`, `up`, `left`; `.` keeps a pixel, `_` clears it). Old hat pixels
   in those rows are cleared first. `clear_above`, per-frame `fix` nudges and `pixels` touch-ups
   handle the odd frames (fishing rods, Leaf's flying hair).
   Body `overlays` (the Draconid scarf, below) are drawn next, anchored on the head template's top-left.
4. `derived` sheets (acro, underwater, watering, decorating, icon) are composed from built frames.
5. A water-reflection palette is generated (`0.58·c + (106, 112, 116)`, like `brendan_reflection.pal`).

After changing a spec: rebuild the PNGs, then `python3 tools/hack/art/player/gen_outfit_code.py`
(regenerates the C data between `DRACONID PLAYER OUTFITS` markers), then `make`. Validate with
`python3 tools/hack/art/validate.py --manifest tools/hack/art/manifests/draconid.json`.

### Look
- **Draconid tamer**: black hair (spiky for M, long for F), a teal headband with two ivory
  dragon horns, teal jacket/top, red skirt and gold bag (F), and a long red **dragon-scale scarf** (round 1,
  below): wrapped at the neck, its ends a short cape down the back (M, where Red's backpack was) or two tails
  over the long hair (F), streaming behind when running or cycling.
- **Magma disguise**: the grunt's red hood with its two ear points, charcoal and red uniform.

### Engine side
`src/player_outfit.c`: `VAR_PLAYER_OUTFIT` → object event graphics per avatar state and gender,
decorating sprite, trainer pic (`TRAINER_PIC_DRACONID_M/F`, `TRAINER_PIC_PLAYER_MAGMA_M/F`).
`special SetPlayerOutfit` (VAR_0x8004 = `PLAYER_OUTFIT_*`) changes the sprite immediately; the var
is saved, so the outfit survives saving and map changes.

## Draconid NPCs and objects (Phase 3)

| Sprite | Built by | Base |
|---|---|---|
| Elder, old woman, villager man/woman/boy, gatekeeper (`pics/people/draconid/*.png`) | `tools/hack/art/recipes/draconid_*.json` (`kitbash.py`) | `expert_m` (+ ivory horned circlet), `expert_f`, `man_2`, `woman_2`, `boy_1`, `black_belt` |
| Aster overworld (`draconid/aster.png`) | `tools/hack/art/player/aster.json` (`build_player.py`) | Leaf walk frames, own head (crimson band, gold horns) |
| Aster front pic | `tools/hack/art/player/aster_pics.json` (`build_pics.py`) | Cooltrainer F front pic, recoloured + band/horns |
| Dragon eggs (`pics/misc/draconid_egg_*.png`) | `tools/hack/art/objects/draconid_eggs.py` | drawn from scratch |

All villagers share **one palette** (`graphics/object_events/palettes/draconid_npc.pal`: skin 1–4, teal 5–7,
red 8–10, ivory/grey/charcoal 11–13), so a village map never runs out of sprite palettes; the recipes only
move the bases' indices onto those roles. Aster and the eggs have their own palettes. The C data comes from
`gen_outfit_code.py` (`NPCS`, `OBJECTS`, `NPC_PALETTES`).

### Known gaps (`TODO(art)`)
- Acro Bike wheelies and hops are shifted/sheared Mach Bike frames.
- The watering can is a small teal blob (the Wailmer Pail; it was red, like the scarf).
- The opening movie still shows Brendan/May on bikes (`graphics/intro/`). It plays before a save exists, so it
  is read as the two rivals; the credits already use the player (below).

### Credits run cycles
`graphics/intro/scene_2/draconid_{m,f}_credits.png` (6 frames of 64×64) come from the FRLG credits run cycles
(`graphics/credits_frlg/player_{male,female}.png`, Red and Leaf) through `build_pics.py` and
`tools/hack/art/player/draconid_credits.json`: the palette keeps the index roles (jacket/top → teal, pack → red for
M, hair → dark navy), and a side-view head (spiky hair or a smooth top over the long hair, teal band, one horn
leaning back) is drawn over the cap. The head rows were laid out from shapes (hair dome, spikes, horn line, band)
with a 1 px outline, then checked at 1× and in the emulator.
- Magma F back pic: the hood still has Leaf's hat silhouette.

## Round 1: Nerine, Courtney and the partner back pics

Files under `graphics/object_events/pics/people/`, `graphics/object_events/palettes/` and `graphics/trainers/`;
specs under `tools/hack/art/`.

| Sprite | File(s) | Spec (tool) | Base | Look |
|---|---|---|---|---|
| Nerine in Team Aqua, overworld | `draconid/nerine_aqua.png`, `nerine_aqua{,_reflection}.pal` | `recipes/nerine_aqua.json` (kitbash) | Aqua grunt F walk sheet | unchanged but her **silver-blue hair** (D-160) |
| Nerine in Team Aqua, front pic | `front_pics/nerine_aqua.png` | `recipes/nerine_aqua_front_pic.json` (kitbash) | Aqua grunt F pic | same hair |
| Nerine, overworld | `draconid/nerine.png`, `nerine{,_reflection}.pal` | `recipes/nerine.json` (kitbash) | Frontier Brain Lucy's walk sheet | long silver-blue hair, navy, teal shawl, gold sash, one gold horn clip (D-161) |
| Nerine, front pic | `front_pics/nerine.png` | `recipes/nerine_front_pic.json` (kitbash) | Winona's pic | same, with a scale-lattice shawl and gold cuffs |
| Nerine, back pic (5 frames) | `back_pics/nerine.png` | `player/nerine_pics.json` (`build_pics.py`) | FRLG Leaf's back pic | own crown + horn clip, shawl, navy sleeves |
| Courtney, overworld | `draconid/courtney.png`, `courtney{,_reflection}.pal` | `recipes/courtney.json` (kitbash) | Magma grunt F walk sheet | lilac hair, crimson admin jacket, gold emblem (D-162) |
| Tabitha, back pic (5 frames) | `back_pics/magma_admin.png` | `player/tabitha_pics.json` (`build_pics.py`) | Magma disguise back pic (Red) | recoloured into his crimson hooded jacket (D-163) |

Rebuild: `python3 tools/hack/art/kitbash.py tools/hack/art/recipes/{nerine_aqua,nerine_aqua_front_pic,nerine,nerine_front_pic,courtney}.json`
and `python3 tools/hack/art/player/build_pics.py tools/hack/art/player/{nerine,tabitha}_pics.json`, then `make`. The
overworld recipes also write the palette and its water-reflection version (`save_pal`). No C regeneration is needed:
the object events were registered with the placeholders; the back pics are `.backPic` entries of
`TRAINER_PIC_NERINE` / `TRAINER_PIC_MAGMA_ADMIN` in `src/data/graphics/trainers.h` (yOffset 5, `sBackAnims_Kanto`).

How they were made:
- **Disguise**: the grunt's hair indices are moved to free palette slots inside a box above the body (the boots
  share the hair's indices, so a global recolour would have turned them silver); the front pic keeps the red mouth
  pixel and the Poké Ball.
- **Nerine overworld**: Lucy's hair (C/D) stays as the hair's light/mid; the same indices below the hair become the
  navy trousers (per view: `DOWN`/`UP`/`LEFT` steps with `shift` for the walk frames, drawn 1 px lower);
  `remap_inner` turns the black shading inside the hair into a hair-dark blue while keeping the outline and the
  eyes; the bare midriff becomes a navy top and a gold sash, the shoulders the teal shawl; the horn clip is a
  4-row `pixels` overlay per view (her left: viewer's right from the front, left from behind).
- **Nerine front pic**: Winona's winged headpiece is removed, her cap and thin hair replaced by a new crown with a
  side-swept fringe (`pixels`), and long hair painted *behind* the body (`pixels` with `under`), then `outline`
  gives the hair a black edge and `remap_inner` merges old edges that now lie inside the hair. The purple scarf is
  recoloured teal and tiled with a diamond lattice (`pattern`) for the scales; the white forearms become navy with
  gold cuffs. The remap order matters (index 9 is Winona's light grey *and* the new hair mid) – see the recipe.
- **Nerine back pic**: like the Draconid F back pic (head template anchored on Leaf's hat, `[-16, -4]`), but a round
  silver crown without a band and a crescent horn clip; the arms get navy sleeves through per-frame `remap` rects
  (face kept), the wristbands gold cuffs, the top the teal lattice shawl (`pattern`).
- **Courtney**: brown hair → lilac by palette; `remap_inner` turns the black inside the torso (rows 21–26) into the
  hood's dark red, so the outline stays and the top reads as an admin jacket; the white emblem pixels → gold.
- **Checks**: `validate.py --manifest tools/hack/art/manifests/draconid.json` (all 7 files added); contact sheets
  and in-context strips at 3×; in the emulator (temporary debug scripts, not committed) the five overworld sprites
  side by side with the real grunts in all four facings, both Nerine front pics in battle, and both partners'
  back pics through the multi-battle intro and throw.

Known gaps (`TODO(art)`): Tabitha's back pic keeps Red's slim build (he is heavier in his front pic); Courtney has
no trainer pic (she does not battle yet); Nerine's shawl pattern is only a hint at 16×32.

## Round 1: Zinnia, the Lorekeeper

Zinnia (ORAS Delta Episode) for the Sky Pillar battle. Only the art lives here; the object event and the trainer pic
are registered by the Sky Pillar branch at the same paths (it shipped placeholders there). Her ORAS / Masters EX art
was looked at for reference only; nothing of it is copied or bundled. Look and bases: D-180, D-181.

| Sprite | File(s) | Spec (tool) | Base | Look |
|---|---|---|---|---|
| Zinnia, overworld | `draconid/zinnia.png`, `zinnia{,_reflection}.pal` | `recipes/zinnia.json` (kitbash) | Frontier Brain Anabel's walk sheet | black bob with blunt bangs, red bead on her left side, cream collar and ragged cream cloak, olive shoulder pads, black top, red crescents and rope belt, olive shorts and boots, cream socks |
| Zinnia, front pic | `front_pics/zinnia.png` | `recipes/zinnia_front_pic.json` (kitbash) | Psychic F's pic | same, arms spread, red eyes, the cloak open behind her, blue-grey Mega Anklet on her right leg |

Rebuild: `python3 tools/hack/art/kitbash.py tools/hack/art/recipes/zinnia.json tools/hack/art/recipes/zinnia_front_pic.json`,
then `make` (the overworld recipe also writes both palettes). No back pic: she never fights beside the player.

How they were made:
- **Overworld**: the new palette keeps Anabel's index roles for skin (1–4), hair (8–10) and outline (15), so the palette
  alone turns her pink hair into the black bob; the other slots are olive 5–6, red 7 / dark red 14, cream 11–13. Each
  frame then has one `pixels` step ('.' = Anabel's pixel, '0' = clear) that squares the bangs, covers the ears,
  adds the bead, and redraws the body over Anabel's poses: collar, pads, top, belt, shorts, socks, boots, and the
  cloak – two shaded panels behind her legs from the front (a ragged tooth at each hem), a cream back with vertical
  folds from behind, a trailing panel from the side. The walk frames sit 1 px lower and move the lifted leg and the
  hem; the side walk frames spread the legs and flare the cloak further back. Right = the left frames flipped, so the
  bead sits at the back of her head from both sides.
- **Front pic**: `remap_region` steps erase the psychic rings and the floating Poké Ball, turn the sleeves into bare
  arms, the blue top black, the shorts olive, the shins cream socks and the sandals olive boots. `pixels` steps then
  flatten the old sleeve highlight on the upper torso, mend the wrists the rings ran through, redraw the head (hair
  tuft removed, bob with blunt bangs, open eyes with a dark red iris, a small smile, the bead), wind the cream collar
  round the neck, add the leaf-shaped pads, the crescents, the rope belt with cream ends and the anklet. The cloak is
  one `pixels` block with `under` (only transparent pixels change): it flares from the shoulders to a ragged hem, light
  outside with fold lines, shadowed where it shows between the legs; `outline` then gives it (and the collar and socks)
  a black edge.
- **Checks**: `validate.py --manifest` (both files added); contact sheets next to Nerine, Aster and the player (overworld
  with the game palettes, front pics side by side); in the emulator (a temporary build, not committed, that pointed
  Nerine's disguise sprite and pic at Zinnia's files) she walks down in Petalburg Woods, runs right and up in Rustboro,
  faces left in Rusturf Tunnel, and her front pic slides in on the battle intro.

Known gaps (`TODO(art)`, polish only): the front pic keeps the psychic's short, foreshortened arms (her right hand sits
close to the pad); at 16×32 the crescents are single red pixels and the anklet is left out.
## Round 1: the Draconid tamer's scarf (feedback 1.14)

The playtester asked for "a scarf/cape like Zinnia's, with dragon-scale details" on the tamer outfit (D-164 … D-167).
Both genders, every state the outfit system draws; the Magma disguise is untouched.

| State / asset | File(s) | Scarf |
|---|---|---|
| walk, run, surf, field move, fishing, Mach Bike (+ derived Acro Bike, underwater, watering, decorating) | `graphics/object_events/pics/people/draconid_{m,f}/*.png` | red wrap at the neck; facing down, one end hangs on the chest and the other shows beside the body; from behind the ends are a short cape (M, over Red's backpack) or two tails over the long hair (F); from the side they trail behind, streaming out further on the bike; a dot hint of scales |
| water reflection | `graphics/object_events/palettes/draconid_{m,f}_reflection.pal` | regenerated, unchanged (no palette colour changed) |
| region map / PokéNav icon | `graphics/pokenav/region_map/draconid_{m,f}_icon.png` | the wrap shows in the bottom row (derived from walk frame 0) |
| trainer front pic (trainer card, link) | `graphics/trainers/front_pics/draconid_{m,f}.png` | wrap + two long ends with a fish-scale pattern streaming out (M: behind his right shoulder, over the old backpack; F: over her left shoulder and the long hair); the male's Poké Ball is red now |
| trainer back pic (5 frames, idle + throw) | `graphics/trainers/back_pics/draconid_{m,f}.png` | M: the backpack becomes the scaled cape, wrap at the neck; F: a band across the hair and two scaled ends streaming out |
| credits run cycle (6 frames) | `graphics/intro/scene_2/draconid_{m,f}_credits.png` | the ends stream out behind the runner (M: over the backpack), the tips flutter a pixel from frame to frame |
| Wailmer Pail (watering) | `draconid_{m,f}/watering.png` | the can is teal now (it was red, like the scarf) |

Colours: only palette slots that were already there – M the backpack's reds (`R`/`r` = 13/14 on the overworld,
back pic and credits, 10/11 on the front pic); F the bright red 11 (unused on the overworld sheets before) with 12
as its shade (overworld, back pic, credits) and the skirt's reds 12/13 on the front pic – so no palette, reflection
palette or C data changed and the colour count stays ≤ 16.

How it is built (all through the specs, rebuildable):
- **Overworld** (`build_player.py`): a spec's `"overlays"` holds ASCII body templates (`scarf_down`, `scarf_up`,
  `scarf_left`, plus `_run`/`_short`/`_bike`/`_fly` variants for the shorter running and sitting bodies and the
  bike); each sheet lists one per frame (`"overlays": [...]`, nudges in `"overlay_fix"`). A template is anchored
  on the head template's top-left after the head swap, so it follows the walk bob and the head `fix` nudges;
  `"under"` rows only paint transparent pixels (the tail behind the body), `"rows"` paint over (the wrap, the cape
  over the backpack). Right-facing frames are the left ones flipped by the engine, so the tail trails the right way.
- **Pics and credits** (`build_pics.py`): `"overlays"` entries (`at`, `rows`, `under`, `frames`) are drawn
  after the remaps, in frame coordinates. The large shapes are not typed by hand:
  `tools/hack/art/player/scarf_pics.py` holds them as polygons and region fills (the backpack's pixels, strap lines
  included, become the cape; the arm and hand are kept in front) and writes the ASCII overlays into the three pic
  specs, filled with the fish-scale tile (`SCALES`: U-shaped scales 4 px wide, rows offset by half a scale),
  outlined and shaded on one side. The specs stay the source of truth; rerun `scarf_pics.py` only to redo a shape.

Rebuild:
```sh
python3 tools/hack/art/player/build_player.py tools/hack/art/player/draconid_m.json   # and draconid_f.json
python3 tools/hack/art/player/scarf_pics.py        # only after changing a pic shape (writes the pic specs)
python3 tools/hack/art/player/build_pics.py tools/hack/art/player/draconid_m_pics.json   # draconid_f_pics, draconid_credits
python3 tools/hack/art/validate.py --manifest tools/hack/art/manifests/draconid.json      # now includes the credits (credits_run profile)
```
No C regeneration is needed (same sheets, frame counts and palettes). Rebuilding every player spec (Magma, Aster,
Nerine, Tabitha included) gives byte-identical files, so the overlay code changes nothing for specs without overlays.

Checks: `validate.py` (70 files, 0 failed); contact sheets of every sheet at 3–8×; in the emulator (temporary
`.play` scripts, not committed) for both genders: walking and running in all four directions in Petalburg City,
the pond reflection, the Mach Bike in four directions, the Acro Bike (ride, wheelie, hop, sheared wheelie frame),
fishing with the Old Rod, the surfing / underwater sheets in context (sprite swapped in memory), a wild battle on
Route 102 (back pic slide-in and throw frames), the trainer card, the Fly map icon and the credits run. The
regression chain (`opening` … `act2`) passes for both genders.

Known gaps (`TODO(art)`): the scale pattern is only a dot hint on the overworld sprites (16×32 has no room for more);
the Acro Bike's wheelie/hop frames still shear the Mach Bike frames, scarf included; the M throw frames show the
cape with the backpack's rounded outline.

## Round 1: the Battle Frontier legends (Wes; Blue's partner back pic)

Wes (Pokémon Colosseum) has no sprites in the repository, and Blue's FRLG champion pic has no back pic (he fights
beside the player in the LEGENDS' TAG). Both are kitbashed from **Steven's** sprites (D-228); Red uses his FRLG
sprites as they are, and Blue's overworld sprite is the FRLG `blue.png` sheet with `npc_green.pal`, registered for
Emerald as `OBJ_EVENT_GFX_FRONTIER_BLUE` (vanilla registers `OBJ_EVENT_GFX_BLUE` only in FRLG builds).

| Sprite | File(s) | Spec (tool) | Base | Look |
|---|---|---|---|---|
| Wes, overworld (9 × 16×32) | `frontier_legends/wes.png`, `wes{,_reflection}.pal` | `recipes/wes.json` (kitbash) | Steven's walk sheet | white spiky hair, black sunglasses, a long navy coat to the knees with light lapels, dark shirt, grey trousers |
| Wes, front pic | `front_pics/wes.png` | `recipes/wes_front_pic.json` (kitbash) | Steven's pic | the same; the coat's tails drawn over the legs down to a hem, charcoal trousers below, glints on the lenses |
| Wes, back pic (4 frames) | `back_pics/wes.png` | `recipes/wes_back_pic.json` (kitbash) | Steven's back pic (`sBackAnims_Hoenn`) | white hair, the lens over the visible eye, navy coat with the light collar and cuffs |
| Blue, back pic (4 frames) | `back_pics/blue.png` | `recipes/blue_back_pic.json` (kitbash) | Steven's back pic | Blue's orange-brown hair and slate shirt (colours from `champion_rival_frlg.pal`) |

Rebuild: `python3 tools/hack/art/kitbash.py tools/hack/art/recipes/{wes,wes_front_pic,wes_back_pic,blue_back_pic}.json`,
then `make` (the overworld recipe also writes both palettes). The object events come from `gen_outfit_code.py`
(`NPCS`: `Wes`, `FrontierBlue`; `NPC_PALETTES`: tags 0x1150, 0x1151); the pics are `TRAINER_PIC_WES` and the new
`.backPic` of `TRAINER_PIC_CHAMPION_RIVAL_FRLG` in `src/data/graphics/trainers.h` (yOffset 4, `sBackAnims_Hoenn`, own
back-pic palettes).

How they were made:
- **Overworld**: a new palette keeps Steven's index roles (skin 1–4; hair B/C/D whiter; the purple stripes 9 → a
  pale blue for the lapels, the tie A and the white shirt E → navy / a dark shirt). The coat is the suit inside the
  outline: in rows 20–28 (down to the knees; the walk frames 1 px lower) the grey shading → coat highlight and the
  black inner pixels → navy (`remap_inner` keeps the black outline), so the coat ends where the grey legs start.
  The shades are a `pixels` band over both eyes (front) and a lens + arm (side).
- **Front pic**: the palette turns the suit navy, the stripes into light lapels and the hair white; the red tie and
  shirt become a dark shirt. The coat's tails are computed from Steven's leg outline (rows 43–53: one panel over
  both legs that flares a pixel every four rows, a light left edge, a black front opening with shadow either side,
  a black hem) and written into the recipe as plain `pixels` rows; the trousers below the hem are remapped to
  charcoal. The lenses are black with one light glint each.
- **Back pics**: from the shoulders down (rows 36–63 of each frame) the suit's grey/dark → the new clothes; the
  hair recolours by palette. Wes keeps Steven's light collar and cuffs (his light collar) and gets a lens over the
  eye in every frame (the eye's position per frame is in the recipe); Blue's collar and cuffs become shirt.
- **Checks**: `validate.py --manifest` (the four files added); contact sheets at 3–6× next to Steven's sprites; in the
  emulator (`frontier_legends.play`) Wes in the Pyramid's sands, Blue by the Tower door and Red below Artisan Cave,
  the intros with Blue's and Wes's front pics, and the partner back pics in the tag battles' intro.

Known gaps (`TODO(art)`, polish only): Wes shares Steven's pose and build (he is recognisable by the shades, coat and
colours, not by a new silhouette); there is no Snag Machine on his arm (2–3 px at 16×32); the lens on the back pic
is only a darker eye.
