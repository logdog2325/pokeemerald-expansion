# Free Gen 3-style art resources

Places to find community art for Draconid Emerald. **Nothing from these sources is bundled
in this repo.** Before adding any third-party asset, check its credit/licence terms (most
require visible credit, some forbid commercial use or edits) and ask the project owner.
Record every imported asset, its author and its terms in `CREDITS.md` and in
`docs/hack_art_pipeline.md`.

## Where to look

| Source | What's there | Notes |
|---|---|---|
| [PokéCommunity – Resources forum](https://www.pokecommunity.com/forums/resources.197/) | Gen 3 tilesets, overworld sprites, trainer sprites, battle backgrounds, fonts | Each thread states its own credit rules; many ask for credit in the hack's credits screen/readme. |
| [PokéCommunity – Gen III tileset threads](https://www.pokecommunity.com/forums/resources.197/) | Hoenn-style tiles (shrines, mountain villages, statues) | Search "Hoenn tiles", "Gen 3 tileset", "shrine". |
| [Eevee Expo – Resources](https://eeveeexpo.com/resources/) | Overworld sprites, tilesets, trainer sprites (many Gen 3/4 styled) | Built for Pokémon Essentials but sprite sheets are reusable after re-indexing. Check each resource's licence tab. |
| [The Spriters Resource – Pokémon Emerald](https://www.spriters-resource.com/game_boy_advance/pokemonemerald/) | Ripped official sprites for reference | Reference/kitbash source only; official art is Nintendo/Game Freak's. |
| [Pokémon Showdown / PokeAPI sprite repos](https://github.com/PokeAPI/sprites) | Front/back Pokémon sprites (incl. Mega forms) | Official art rips; useful as placeholders for new forms. |
| [rh-hideout Discord – #resources](https://discord.gg/6CzjAG6GZk) | Expansion-ready graphics (Gen 4+ Pokémon, Megas, items) | Linked from README.md; usually already formatted for the expansion. |
| [DeviantArt – "gen 3 overworld" / "HGSS overworld"](https://www.deviantart.com/tag/pokemonoverworld) | Fan-made overworld sprites (e.g. Zinnia, Dragon Tamer) | Always ask the artist; terms vary per post. |

## Useful searches
- "Zinnia overworld sprite gen 3", "Draconid overworld", "dragon tamer overworld emerald"
- "Rayquaza statue tiles", "shrine tileset gen 3", "mountain village tileset hoenn"
- "Mega Feraligatr sprite gen 3" (the expansion already ships a Mega Feraligatr sprite; custom ones are optional)

## Importing
Use `tools/hack/art/quantize.py` (≤16 colours, transparent index 0, GBA colour grid) and
`tools/hack/art/validate.py` before wiring anything into the build. Tiles go through Porytiles
(`docs/hack_tools.md`). Render a contact sheet or map preview and review it before committing.

## Data sources (game data, not art)

| Data | Source | Fetched | Where it's used |
|---|---|---|---|
| ORAS trainer teams (first battle, rematches; species, levels, held items) | [Serebii Pokéarth – Hoenn, Gen VI pages](https://www.serebii.net/pokearth/hoenn/) (`/pokearth/hoenn/<location>.shtml`, 57 locations with trainers) | 2026-09-30 | `tools/hack/trainers/oras/oras_trainers.json` |
| ORAS Elite Four / Champion, first battle and post-game rematch, with moves | [Serebii – ORAS Elite Four](https://www.serebii.net/omegarubyalphasapphire/elitefour.shtml) | 2026-09-30 | same file (`oras_elitefour`) |
| Champion Steven (ORAS: Skarmory, Claydol, Aggron, Cradily, Armaldo 57, Metagross 59 @ Metagrossite; post-game Skarmory, Claydol, Carbink, Aerodactyl, Aggron 77, Metagross 79 @ Metagrossite, with moves) and "Sootopolitan Wallace" (his Emerald Champion roster, Route 131) | [Serebii – ORAS Elite Four](https://www.serebii.net/omegarubyalphasapphire/elitefour.shtml) (the Champion section), [Serebii Pokéarth – Route 131](https://www.serebii.net/pokearth/hoenn/route131.shtml) | 2026-09-30 (the round 1 scrape, `oras_trainers.json`) | `TRAINER_STEVEN` (the Champion, S9 levels), `TRAINER_STEVEN_REMATCH` (ORAS levels), `TRAINER_WALLACE` (post-game, class SOOTOPOLITAN) – `tools/hack/trainers/oras/champion.party` (D-250 – D-252) |
| Red's and Blue's Pokémon World Tournament teams (Black 2 / White 2 Champions Tournament: species, Lv 50, held items, moves; no abilities or natures) | [Serebii – PWT Champions Tournament](https://www.serebii.net/black2white2/pwt/champion.shtml) (linked from [the PWT page](https://www.serebii.net/black2white2/worldtournament.shtml)) | 2026-09-30 | `tools/hack/trainers/pwt/pwt_champions.json` → the Battle Frontier legends (D-226) |
| Zinnia's Sky Pillar team (ORAS Delta Episode: species, levels; held items, natures and EVs are ours, D-155) | [Serebii – ORAS Delta Episode](https://www.serebii.net/omegarubyalphasapphire/deltaepisode.shtml), [Serebii Pokéarth – Sky Pillar](https://www.serebii.net/pokearth/hoenn/skypillar.shtml) | 2026-09-30 | `TRAINER_ZINNIA_SKY_PILLAR` (Goodra 60, Noivern 60, Altaria 60, Tyrantrum 60, Salamence 62 @ Salamencite) |

The PWT page is fetched by `tools/hack/trainers/pwt/scrape_pwt.py` (one request, cached outside the repo; `--offline`
re-parses the cache). Wes's team (Pokémon Colosseum) is the playtester's list; its sets are written here (D-226).

Fetched by `tools/hack/trainers/oras/scrape_serebii.py` (one request at a time, 2 s apart, pages cached outside
the repo; rerun with `--offline` on the cache to rebuild the JSON). Only the extracted team data is committed, not
the pages. Bulbapedia refuses automated requests (HTTP 403), so it is not used. How the data is matched and used:
docs/hack_trainers.md, "ORAS data".
