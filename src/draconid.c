#include "global.h"
#include "draconid.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "overworld.h"
#include "constants/flags.h"
#include "constants/map_types.h"
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

// The trainer a battle loads after the Hall of Fame, instead of the first one (round 1, D-174)
static const u16 sPostgameRematches[][2] =
{
    { TRAINER_SIDNEY, TRAINER_SIDNEY_REMATCH },
    { TRAINER_PHOEBE, TRAINER_PHOEBE_REMATCH },
    { TRAINER_GLACIA, TRAINER_GLACIA_REMATCH },
    { TRAINER_DRAKE,  TRAINER_DRAKE_REMATCH },
};

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
    // Once the game is cleared, the Elite Four bring their ORAS post-game rematch teams (D-174)
    if (FlagGet(FLAG_SYS_GAME_CLEAR))
    {
        for (i = 0; i < ARRAY_COUNT(sPostgameRematches); i++)
        {
            if (sPostgameRematches[i][0] == trainerId)
                return sPostgameRematches[i][1];
        }
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

// Step hook (TryStartStepCountScript): the egg from the shrine ceremony hatches after DRACONID_EGG_HATCH_STEPS
// steps outdoors (round 1, D-231), so the scene always plays in the open village.
bool32 Draconid_ShouldHatchEgg(void)
{
    if (VarGet(VAR_DRACONID_STATE) != DRACONID_STATE_EGG_RECEIVED || FlagGet(FLAG_DRACONID_EGG_HATCHED))
        return FALSE;
    if (!IsMapTypeOutdoors(gMapHeader.mapType))
        return FALSE;
    return ++(*GetVarPointer(VAR_DRACONID_EGG_STEPS)) >= DRACONID_EGG_HATCH_STEPS;
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

// Maxie's PokéNav calls (round 1, D-186): the story state that makes each call due, in story order.
struct MaxieCall
{
    u16 var;
    u16 value;
    u16 call;
};

static const struct MaxieCall sMaxieCalls[] =
{
    { VAR_MAGMA_STATE,  MAGMA_STATE_MUSEUM,            MAXIE_CALL_MUSEUM },
    { VAR_MAGMA_STATE,  MAGMA_STATE_METEOR_FALLS,      MAXIE_CALL_METEOR_FALLS },
    { VAR_MAGMA_STATE,  MAGMA_STATE_MT_CHIMNEY,        MAXIE_CALL_MT_CHIMNEY },
    { VAR_MAGMA_STATE,  MAGMA_STATE_WEATHER_INSTITUTE, MAXIE_CALL_WEATHER_INSTITUTE },
    { VAR_MAGMA_STATE,  MAGMA_STATE_MT_PYRE,           MAXIE_CALL_MT_PYRE },
    { VAR_MAGMA_STATE,  MAGMA_STATE_PROMOTED,          MAXIE_CALL_PROMOTED },
    { VAR_NERINE_STATE, NERINE_STATE_AQUA_HIDEOUT,     MAXIE_CALL_AQUA_HIDEOUT },
    { VAR_MAGMA_STATE,  MAGMA_STATE_SPACE_CENTER,      MAXIE_CALL_SPACE_CENTER },
    { VAR_MAGMA_STATE,  MAGMA_STATE_SEAFLOOR,          MAXIE_CALL_SEAFLOOR },
};

// The latest call the story has reached that the player hasn't had yet (older missed ones are skipped),
// or MAXIE_CALL_NONE. Maxie stops calling once the player turns on him at Sootopolis.
static u16 GetDueMaxieCall(void)
{
    u32 i;
    u16 due = MAXIE_CALL_NONE;

    if (VarGet(VAR_DRACONID_REPUTATION) != REPUTATION_UNIFORM || VarGet(VAR_MAGMA_STATE) >= MAGMA_STATE_TURNED)
        return MAXIE_CALL_NONE;
    for (i = 0; i < ARRAY_COUNT(sMaxieCalls); i++)
    {
        if (VarGet(sMaxieCalls[i].var) >= sMaxieCalls[i].value)
            due = sMaxieCalls[i].call;
    }
    return due > VarGet(VAR_MAXIE_CALL) ? due : MAXIE_CALL_NONE;
}

// Step hook (TryStartStepCountScript): a due call rings after MAXIE_CALL_STEPS steps on an outdoor map.
bool32 Draconid_ShouldDoMaxieCall(void)
{
    if (!FlagGet(FLAG_SYS_POKENAV_GET) || GetDueMaxieCall() == MAXIE_CALL_NONE)
        return FALSE;
    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
    case MAP_TYPE_OCEAN_ROUTE:
        if (++(*GetVarPointer(VAR_MAXIE_CALL_STEPS)) < MAXIE_CALL_STEPS)
            return FALSE;
        return TRUE;
    default:
        return FALSE;
    }
}

// specialvar: the call to play (Draconid_EventScript_MaxieCall)
u16 Draconid_GetDueMaxieCall(void)
{
    return GetDueMaxieCall();
}
