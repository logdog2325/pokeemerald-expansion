#include "global.h"
#include "draconid.h"

// Draconid Emerald: the debug menu's "Jump to act…" (D-480 - D-489). The menu, the warps and the story state are
// event scripts (data/scripts/draconid/debug_jumps.pory, debug_jumps_state.inc from tools/hack/gen_debug_jumps.py);
// these are the parts a script can't do: the bag counts, the ready team, the supplies, Rayquaza and the roamers.
// Debug builds only: `make release` compiles nothing here (DEBUG_OVERWORLD_MENU is off there).
#if DEBUG_OVERWORLD_MENU

#include "caps.h"
#include "event_data.h"
#include "frontier_util.h"
#include "item.h"
#include "money.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "roamer.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "constants/draconid.h"
#include "constants/items.h"
#include "constants/species.h"

static const u16 sEggSpecies[DRACONID_EGG_COUNT] =
{
    [DRACONID_EGG_DEINO]    = DRACONID_EGG_SPECIES_0,
    [DRACONID_EGG_DREEPY]   = DRACONID_EGG_SPECIES_1,
    [DRACONID_EGG_JANGMO_O] = DRACONID_EGG_SPECIES_2,
};

static const u16 sSecondStarterSpecies[] =
{
    [SECOND_STARTER_NONE]       = SPECIES_NONE,
    [SECOND_STARTER_CHARMANDER] = SPECIES_CHARMANDER,
    [SECOND_STARTER_TOTODILE]   = SPECIES_TOTODILE,
    [SECOND_STARTER_TREECKO]    = SPECIES_TREECKO,
};

// The level a stop's team and supplies are made for: its level cap, or after the Champion (no cap) the stop's own
// level, which the script passes in VAR_0x8006 (DRACONID_JUMP_LEVEL_*; 0 = the cap)
static u32 JumpLevel(void)
{
    u32 level = GetCurrentLevelCap();

    if (level >= MAX_LEVEL && gSpecialVar_0x8006 != 0)
        level = gSpecialVar_0x8006;
    return level;
}

// How far a line gets by its level-up evolutions at `level` (the egg lines at 25 and 50, D-107; the starters'
// own levels); evolutions with conditions (a time of day, a held item) are not taken
static u16 EvolveByLevel(u16 species, u32 level)
{
    bool32 evolved = TRUE;

    while (evolved)
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(species);
        u32 i;

        evolved = FALSE;
        if (evolutions == NULL)
            break;
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            if (evolutions[i].method == EVO_LEVEL && evolutions[i].param <= level && evolutions[i].params == NULL)
            {
                species = evolutions[i].targetSpecies;
                evolved = TRUE;
                break;
            }
        }
    }
    return species;
}

static void TopUpItem(u16 item, u16 count)
{
    u16 have = CountTotalItemQuantityInBag(item);

    if (have < count)
        AddBagItem(item, count - have);
}

// callnative: the bag holds exactly VAR_0x8005 of the item VAR_0x8004 (the story state of a stop, generated)
void Draconid_DebugJumpSetItem(struct ScriptContext *ctx)
{
    u16 item = gSpecialVar_0x8004;
    u16 want = gSpecialVar_0x8005;
    u16 have = CountTotalItemQuantityInBag(item);

    if (have > want)
        RemoveBagItem(item, have - want);
    else if (have < want)
        AddBagItem(item, want - have);
}

// callnative: the party for a stop (D-483). The player's own Pokémon stay. If none of them is within
// DRACONID_JUMP_LEVEL_SLACK levels of the stop's level, the egg dragon (VAR_STARTER_MON) and Prof. Oak's partner
// (VAR_SECOND_STARTER, once he has given it) join at that level, as evolved as their level-up evolutions make them
// there; past six they go to the PC. VAR_0x8006: the stop's level after the Champion (0: the cap).
// VAR_RESULT = TRUE if they joined.
void Draconid_DebugJumpTeam(struct ScriptContext *ctx)
{
    u32 level = JumpLevel();
    u32 egg = VarGet(VAR_STARTER_MON);
    u32 second = VarGet(VAR_SECOND_STARTER);

    gSpecialVar_Result = FALSE;
    if ((u32)GetHighestLevelInPlayerParty() + DRACONID_JUMP_LEVEL_SLACK >= level)
        return;
    if (egg < DRACONID_EGG_COUNT)
        ScriptGiveMon(EvolveByLevel(sEggSpecies[egg], level), level, ITEM_NONE);
    if (second < ARRAY_COUNT(sSecondStarterSpecies) && sSecondStarterSpecies[second] != SPECIES_NONE)
        ScriptGiveMon(EvolveByLevel(sSecondStarterSpecies[second], level), level, ITEM_NONE);
    gSpecialVar_Result = TRUE;
}

// callnative: money, medicine and Poké Balls for the stop's level, topped up (never taken away)
void Draconid_DebugJumpSupplies(struct ScriptContext *ctx)
{
    u32 level = JumpLevel();
    u16 potion = ITEM_SUPER_POTION, ball = ITEM_POKE_BALL;

    if (GetMoney(&gSaveBlock1Ptr->money) < level * DRACONID_JUMP_MONEY_PER_LEVEL)
        SetMoney(&gSaveBlock1Ptr->money, level * DRACONID_JUMP_MONEY_PER_LEVEL);
    if (level >= DRACONID_JUMP_MAX_LEVEL)
    {
        potion = ITEM_MAX_POTION;
        ball = ITEM_ULTRA_BALL;
    }
    else if (level >= DRACONID_JUMP_HYPER_LEVEL)
    {
        potion = ITEM_HYPER_POTION;
        ball = ITEM_GREAT_BALL;
    }
    TopUpItem(potion, DRACONID_JUMP_MEDICINE);
    TopUpItem(ITEM_REVIVE, DRACONID_JUMP_REVIVES);
    TopUpItem(ball, DRACONID_JUMP_BALLS);
}

// callnative: after the summit every playthrough has caught RAYQUAZA (the must-catch battle, D-110): if neither the
// party nor the PC has one, it joins at DRACONID_RAYQUAZA_LEVEL (the script then has the ELDER's
// Draconid_PrepareRayquaza teach it DRAGON ASCENT, as the summit does)
void Draconid_DebugJumpRayquaza(struct ScriptContext *ctx)
{
    u32 i, box, pos;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES_OR_EGG) == SPECIES_RAYQUAZA)
            return;
    }
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            if (GetBoxMonDataAt(box, pos, MON_DATA_SPECIES_OR_EGG) == SPECIES_RAYQUAZA)
                return;
        }
    }
    ScriptGiveMon(SPECIES_RAYQUAZA, DRACONID_RAYQUAZA_LEVEL, ITEM_NONE);
}

// callnative: the Lati roamers (D-209) roam from the SS Ticket's news on: VAR_0x8004 = TRUE starts both afresh, as
// the news does; FALSE (a stop before it) stops them
void Draconid_DebugJumpRoamers(struct ScriptContext *ctx)
{
    DeactivateAllRoamers();
    if (gSpecialVar_0x8004)
        InitRoamer();
}

#endif // DEBUG_OVERWORLD_MENU
