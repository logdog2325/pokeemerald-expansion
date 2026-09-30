#include "global.h"
#include "draconid.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "overworld.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "constants/draconid.h"
#include "constants/opponents.h"

// Trainers whose team depends on the player's choices (round 1, D-101)
enum
{
    VARIANT_BY_EGG,             // 3 ids: the player's egg (VAR_STARTER_MON)
    VARIANT_BY_EGG_AND_STARTER, // 9 ids: egg * SECOND_STARTER_CHOICES + second starter
};

#define SECOND_STARTER_CHOICES 3

struct DraconidVariantTrainer
{
    u16 kind;
    u16 ids[DRACONID_EGG_COUNT * SECOND_STARTER_CHOICES];
};

#include "data/draconid_variant_trainers.h"

// A script names the first variant of a fight; this returns the variant for the player's egg and second starter.
u16 Draconid_ResolveVariantTrainer(u16 trainerId)
{
    u32 i, egg, starter;

    for (i = 0; i < ARRAY_COUNT(sDraconidVariantTrainers); i++)
    {
        const struct DraconidVariantTrainer *variant = &sDraconidVariantTrainers[i];
        if (variant->ids[0] != trainerId)
            continue;
        egg = VarGet(VAR_STARTER_MON);
        if (egg >= DRACONID_EGG_COUNT)
            egg = DRACONID_EGG_DEINO;
        if (variant->kind == VARIANT_BY_EGG)
            return variant->ids[egg];
        starter = VarGet(VAR_SECOND_STARTER);
        starter = (starter >= SECOND_STARTER_CHARMANDER && starter <= SECOND_STARTER_TREECKO) ? starter - SECOND_STARTER_CHARMANDER : 0;
        return variant->ids[egg * SECOND_STARTER_CHOICES + starter];
    }
    return trainerId;
}

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
