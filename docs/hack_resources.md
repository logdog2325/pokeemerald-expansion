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

## Game data sources
Teams copied from the official games (species, levels, abilities, moves and items as listed there; our own
natures, EVs and held items are added on top and recorded in `docs/hack_decisions.md`).

| Trainer | Source | Notes |
|---|---|---|
| `TRAINER_ZINNIA_SKY_PILLAR` (Act 7, D-155) | [Serebii – ORAS Delta Episode](https://www.serebii.net/omegarubyalphasapphire/deltaepisode.shtml) (Zinnia at the Sky Pillar; also [pokearth Sky Pillar](https://www.serebii.net/pokearth/hoenn/skypillar.shtml)) | Goodra 60, Noivern 60, Altaria 60, Tyrantrum 60, Salamence 62 @ Salamencite |
