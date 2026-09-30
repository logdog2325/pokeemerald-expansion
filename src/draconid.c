#include "global.h"
#include "draconid.h"
#include "credits.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "load_save.h"
#include "main.h"
#include "new_game.h"
#include "overworld.h"
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

// Draconid Emerald: Nerine's partner team at the Sky Pillar finale follows the same choices (Act 7, D-151)
static const struct DraconidVariantTrainer sDraconidVariantPartners[] =
{
    {VARIANT_BY_EGG_AND_STARTER, {PARTNER_NERINE_DEINO_CHARMANDER, PARTNER_NERINE_DEINO_TOTODILE, PARTNER_NERINE_DEINO_TREECKO, PARTNER_NERINE_DREEPY_CHARMANDER, PARTNER_NERINE_DREEPY_TOTODILE, PARTNER_NERINE_DREEPY_TREECKO, PARTNER_NERINE_JANGMO_O_CHARMANDER, PARTNER_NERINE_JANGMO_O_TOTODILE, PARTNER_NERINE_JANGMO_O_TREECKO}},
};

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
    return ResolveVariant(sDraconidVariantTrainers, ARRAY_COUNT(sDraconidVariantTrainers), trainerId);
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
