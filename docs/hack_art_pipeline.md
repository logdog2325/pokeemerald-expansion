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
4. `derived` sheets (acro, underwater, watering, decorating, icon) are composed from built frames.
5. A water-reflection palette is generated (`0.58·c + (106, 112, 116)`, like `brendan_reflection.pal`).

After changing a spec: rebuild the PNGs, then `python3 tools/hack/art/player/gen_outfit_code.py`
(regenerates the C data between `DRACONID PLAYER OUTFITS` markers), then `make`. Validate with
`python3 tools/hack/art/validate.py --manifest tools/hack/art/manifests/draconid.json`.

### Look
- **Draconid tamer**: black hair (spiky for M, long for F), a teal headband with two ivory
  dragon horns, teal jacket/top, red scarf/bag (M) or red skirt and gold bag (F).
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
- The watering can is a small red blob.
- The male front pic's Poké Ball came out teal (shares the jacket colour).
- The opening movie and the credits still show Brendan/May on bikes (`graphics/intro/`).
- Magma F back pic: the hood still has Leaf's hat silhouette.
