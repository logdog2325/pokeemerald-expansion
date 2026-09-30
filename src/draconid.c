#include "global.h"
#include "draconid.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "overworld.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "constants/draconid.h"

// Draconid Emerald: script specials for the Draconid clan storyline.

// Eggs hatch at EGG_HATCH_LEVEL (1 with Gen 4+ rules). After the hatching rite the
// partner in party slot VAR_0x8004 is raised to DRACONID_HATCHLING_LEVEL, relearns the
// level-up moves for that level and is fully healed.
void DraconidRaiseHatchling(void)
{
    struct Pokemon *mon;
    u32 species, exp, level = DRACONID_HATCHLING_LEVEL;
    u16 hp;

    if (gSpecialVar_0x8004 >= PARTY_SIZE)
        return;
    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    species = GetMonData(mon, MON_DATA_SPECIES);
    if (species == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
        return;

    exp = gExperienceTables[gSpeciesInfo[species].growthRate][level];
    SetMonData(mon, MON_DATA_EXP, &exp);
    SetMonData(mon, MON_DATA_LEVEL, &level);
    CalculateMonStats(mon);
    GiveMonInitialMoveset(mon);
    hp = GetMonData(mon, MON_DATA_MAX_HP);
    SetMonData(mon, MON_DATA_HP, &hp);
}

#if DEBUG_OVERWORLD_MENU
// Emulator test hook (tools/hack/emu/play.py "warp"): a test writes a destination here and the
// overworld warps to it the next time the player has control. Not in release builds.
EWRAM_DATA struct DraconidTestWarp gDraconidTestWarp = {0};

bool32 Draconid_TryTestWarp(void)
{
    u32 request = gDraconidTestWarp.active;

    gDraconidTestWarp.active = 0;
    if (request & DRACONID_TEST_HEAL)
        HealPlayerParty();
    if (!(request & DRACONID_TEST_WARP))
        return FALSE;
    SetWarpDestination(gDraconidTestWarp.mapGroup, gDraconidTestWarp.mapNum, WARP_ID_NONE,
                       gDraconidTestWarp.x, gDraconidTestWarp.y);
    DoWarp();
    return TRUE;
}
#endif
