#include "global.h"
#include "draconid.h"
#include "battle.h"
#include "battle_util.h"
#include "credits.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "item.h"
#include "load_save.h"
#include "money.h"
#include "main.h"
#include "new_game.h"
#include "overworld.h"
#include "constants/flags.h"
#include "constants/map_types.h"
#include "constants/maps.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "rayquaza_scene.h"
#include "save.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "constants/battle_partner.h"
#include "constants/draconid.h"
#include "constants/heal_locations.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/species.h"

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

// Draconid Emerald: Nerine's partner team at the Sky Pillar finale follows the same choices (Act 7, D-151);
// Aster's in the attack on the village follows the player's egg, like her trainer teams (Act 7 extension, D-205)
static const struct DraconidVariantTrainer sDraconidVariantPartners[] =
{
    {VARIANT_BY_EGG_AND_STARTER, {PARTNER_NERINE_DEINO_CHARMANDER, PARTNER_NERINE_DEINO_TOTODILE, PARTNER_NERINE_DEINO_TREECKO, PARTNER_NERINE_DREEPY_CHARMANDER, PARTNER_NERINE_DREEPY_TOTODILE, PARTNER_NERINE_DREEPY_TREECKO, PARTNER_NERINE_JANGMO_O_CHARMANDER, PARTNER_NERINE_JANGMO_O_TOTODILE, PARTNER_NERINE_JANGMO_O_TREECKO}},
    {VARIANT_BY_EGG, {PARTNER_ASTER_DEINO, PARTNER_ASTER_DREEPY, PARTNER_ASTER_JANGMO_O}},
};

// The trainer a battle loads after the Hall of Fame, instead of the first one (round 1, D-174; the Champion: D-251)
static const u16 sPostgameRematches[][2] =
{
    { TRAINER_SIDNEY, TRAINER_SIDNEY_REMATCH },
    { TRAINER_PHOEBE, TRAINER_PHOEBE_REMATCH },
    { TRAINER_GLACIA, TRAINER_GLACIA_REMATCH },
    { TRAINER_DRAKE,  TRAINER_DRAKE_REMATCH },
    { TRAINER_STEVEN, TRAINER_STEVEN_REMATCH },
};

// The variant of a fight (first id in the table) for the player's egg and second starter; id if it has none
static u16 ResolveVariant(const struct DraconidVariantTrainer *variants, u32 count, u16 id)
{
    u32 i, egg, starter;

    for (i = 0; i < count; i++)
    {
        const struct DraconidVariantTrainer *variant = &variants[i];
        if (variant->ids[0] != id)
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
    return id;
}

// A script names the first variant of a fight; this returns the variant for the player's egg and second starter.
u16 Draconid_ResolveVariantTrainer(u16 trainerId)
{
    u32 i;
    u16 resolved = ResolveVariant(sDraconidVariantTrainers, ARRAY_COUNT(sDraconidVariantTrainers), trainerId);

    if (resolved != trainerId)
        return resolved;
    // Once the game is cleared, the Elite Four and the Champion bring their ORAS post-game rematch teams (D-174, D-251)
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

// The same for a multi battle partner (PARTNER_*): the script names PARTNER_NERINE_DEINO_CHARMANDER.
u16 Draconid_ResolveVariantPartner(u16 partnerId)
{
    return ResolveVariant(sDraconidVariantPartners, ARRAY_COUNT(sDraconidVariantPartners), partnerId);
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

// Route 101's first battle (SetUpBattleVarsAndBirchZigzagoon, after CreateWildMon): the LUNATONE that fell with
// the star knows a soft moveset and is hurt by the fall, so every egg's hatchling can tire it out (round 2, D-400).
void Draconid_SetUpRescueMon(struct Pokemon *mon)
{
    static const u16 sMoves[] = {DRACONID_RESCUE_MOVE_1, DRACONID_RESCUE_MOVE_2, DRACONID_RESCUE_MOVE_3};
    u32 i;
    u16 hp;

    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, i < ARRAY_COUNT(sMoves) ? sMoves[i] : MOVE_NONE, i);
    hp = GetMonData(mon, MON_DATA_MAX_HP) * DRACONID_RESCUE_HP_PERCENT / 100;
    if (hp == 0)
        hp = 1;
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

// ---------------------------------------------------------------------------
// Acts 6-7: the Sky Pillar finale (called from data/scripts/draconid/act7.pory with callnative)
// ---------------------------------------------------------------------------

static bool32 IsRayquaza(u32 species)
{
    return species == SPECIES_RAYQUAZA;
}

// After the must-catch battle (D-110): RAYQUAZA leads the party for the Deoxys battle, fetched from the PC
// if the party was full (the lead takes its place in the box), and the Elder teaches it DRAGON ASCENT, which its
// Mega Evolution needs: into an empty move slot, else over REST, else over the last move.
// VAR_RESULT = TRUE if a RAYQUAZA was found; VAR_0x8005 = the move it forgot (MOVE_NONE if none).
void Draconid_PrepareRayquaza(struct ScriptContext *ctx)
{
    struct Pokemon *lead = &gParties[B_TRAINER_PLAYER][0];
    u32 i, box, pos, slot;
    enum Move move;

    gSpecialVar_Result = FALSE;
    gSpecialVar_0x8005 = MOVE_NONE;
    for (i = 0; i < PARTY_SIZE && !gSpecialVar_Result; i++)
    {
        if (IsRayquaza(GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES)) && !GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG))
        {
            if (i != 0)
            {
                struct Pokemon temp = gParties[B_TRAINER_PLAYER][0];
                gParties[B_TRAINER_PLAYER][0] = gParties[B_TRAINER_PLAYER][i];
                gParties[B_TRAINER_PLAYER][i] = temp;
            }
            gSpecialVar_Result = TRUE;
        }
    }
    for (box = 0; box < TOTAL_BOXES_COUNT && !gSpecialVar_Result; box++)
    {
        for (pos = 0; pos < IN_BOX_COUNT && !gSpecialVar_Result; pos++)
        {
            if (IsRayquaza(GetBoxMonDataAt(box, pos, MON_DATA_SPECIES)) && !GetBoxMonDataAt(box, pos, MON_DATA_IS_EGG))
            {
                struct BoxPokemon oldLead = lead->box;
                BoxMonToMon(GetBoxedMonPtr(box, pos), lead);
                SetBoxMonAt(box, pos, &oldLead);
                gSpecialVar_Result = TRUE;
            }
        }
    }
    if (!gSpecialVar_Result)
        return;

    slot = MAX_MON_MOVES;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = GetMonData(lead, MON_DATA_MOVE1 + i);
        if (move == MOVE_DRAGON_ASCENT)
            return;
        if (move == MOVE_NONE && slot == MAX_MON_MOVES)
            slot = i;
    }
    for (i = 0; i < MAX_MON_MOVES && slot == MAX_MON_MOVES; i++)
    {
        if (GetMonData(lead, MON_DATA_MOVE1 + i) == MOVE_REST)
            slot = i;
    }
    if (slot == MAX_MON_MOVES)
        slot = MAX_MON_MOVES - 1;
    gSpecialVar_0x8005 = GetMonData(lead, MON_DATA_MOVE1 + slot);
    SetMonMoveSlot(lead, MOVE_DRAGON_ASCENT, slot);
}

// Mega Rayquaza flies up to the meteor: the "Rayquaza takes flight" shot of the Sootopolis cutscene, on its own.
// The script waits (waitstate) and goes on when the field comes back.
void Draconid_DoRayquazaFlightScene(struct ScriptContext *ctx)
{
    DoRayquazaTakesFlightScene(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

// Before the credits (D-152): save like the Hall of Fame does, with the game continuing in the bedroom, so the
// post-game starts at home even if the credits are cut short. VAR_RESULT = the save status.
void Draconid_SaveBeforeCredits(struct ScriptContext *ctx)
{
    SetContinueGameWarpStatus();
    SetContinueGameWarpToHealLocation(HEAL_LOCATION_DRACONID_VILLAGE_PLAYERS_HOUSE_2F);
    if (gDifferentSaveFile == TRUE)
    {
        gSpecialVar_Result = TrySavingData(SAVE_OVERWRITE_DIFFERENT_FILE);
        gDifferentSaveFile = FALSE;
    }
    else
    {
        gSpecialVar_Result = TrySavingData(SAVE_NORMAL);
    }
}

// The credits roll after the finale (not after the Hall of Fame); they end in the bedroom (CB2_ReturnHomeDraconid).
// The script waits (waitstate) and never resumes: the bedroom's map load starts a fresh script context.
void Draconid_StartCredits(struct ScriptContext *ctx)
{
    SetMainCallback2(CB2_StartCreditsSequence);
}

#if DEBUG_OVERWORLD_MENU
// Emulator test hook (tools/hack/emu/play.py "warp"): a test writes a destination here and the
// overworld warps to it the next time the player has control. Not in release builds.
EWRAM_DATA struct DraconidTestWarp gDraconidTestWarp = {0};

static u32 CountPartyHMMoves(void)
{
    u32 i, j, count = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            if (IsMoveHM(GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_MOVE1 + j)))
                count++;
        }
    }
    return count;
}

bool32 Draconid_TryTestWarp(void)
{
    u32 request = gDraconidTestWarp.active;

    gDraconidTestWarp.active = 0;
    if (request & DRACONID_TEST_HEAL)
        HealPlayerParty();
    if (request & DRACONID_TEST_GIVE_ITEM)
        AddBagItem(gDraconidTestWarp.item, 1);
    if (request & DRACONID_TEST_GIVE_MON)
        ScriptGiveMon(gDraconidTestWarp.species, gDraconidTestWarp.level, gDraconidTestWarp.item);
    if (request & DRACONID_TEST_COUNT_HMS)
        gDraconidTestWarp.partyHMMoves = CountPartyHMMoves();
    if (request & DRACONID_TEST_MAX_MONEY)
        SetMoney(&gSaveBlock1Ptr->money, MAX_MONEY);
    if ((request & DRACONID_TEST_SCRIPT) && gDraconidTestWarp.script != NULL)
    {
        ScriptContext_SetupScript(gDraconidTestWarp.script);
        return TRUE;
    }
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

// ---------------------------------------------------------------------------
// Act 7 extension: the attack on the village (data/scripts/draconid/act7x.pory, D-204)
// ---------------------------------------------------------------------------

// From the alarm at the summit until Maxie and Archie are beaten, Primal Groudon and Kyogre are awake
static bool32 IsPrimalSequence(void)
{
    u16 state = VarGet(VAR_DRACONID_VILLAGE_STATE);

    return state >= VILLAGE_STATE_ALARM && state < VILLAGE_STATE_PRIMAL_WON;
}

static bool32 IsMapTypeUnderOpenSky(enum MapType mapType)
{
    switch (mapType)
    {
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
    case MAP_TYPE_OCEAN_ROUTE:
        return TRUE;
    default:
        return FALSE;
    }
}

// SetSavedWeatherFromCurrMapHeader: while Primal Groudon and Kyogre are awake, every map under the open sky shows
// Emerald's alternating drought and downpour of the Sootopolis clash (WEATHER_ABNORMAL) whenever it is loaded:
// a warp, Fly, a whiteout, a saved game. Underwater, indoor and cave maps keep their own (D-204).
bool32 Draconid_IsPrimalWeather(void)
{
    return IsPrimalSequence() && IsMapTypeUnderOpenSky(gMapHeader.mapType);
}

// GetLocationMusic: the abnormal weather theme plays with that weather
bool32 Draconid_IsPrimalMusic(struct WarpData *warp)
{
    const struct MapHeader *header = Overworld_GetMapHeaderByGroupAndId(warp->mapGroup, warp->mapNum);

    return IsPrimalSequence() && IsMapTypeUnderOpenSky(header->mapType);
}

// multi_do (the scripted multi battles: the Space Center raid, the Sootopolis multi, the Sky Pillar trial, the
// village doubles) asks whether both sides bring full teams before BattleSetup_StartMultiBattle sets
// gBattleTypeFlags for the new battle, so the flags may still be the last battle's. After a wild battle
// AreMultiPartiesFullTeams saw no BATTLE_TYPE_TRAINER, answered "full teams" and the player's pick of three was
// skipped (D-343). setmultitrainerbattle has just set up a trainer battle: ask about that one. The in-battle
// callers keep using the real flags.
void Draconid_ScriptAreMultiPartiesFullTeams(void)
{
    u32 flags = gBattleTypeFlags;

    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    AreMultiPartiesFullTeams(); // sets gSpecialVar_Result
    gBattleTypeFlags = flags;
}
