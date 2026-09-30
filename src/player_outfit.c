#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "player_outfit.h"
#include "constants/event_objects.h"
#include "constants/outfits.h"
#include "constants/trainers.h"

// Draconid Emerald: player outfits. VAR_PLAYER_OUTFIT picks the row; the avatar code asks
// here for every graphics id instead of using Brendan's and May's. The sprite sets are built
// by tools/hack/art/player (see docs/hack_art_pipeline.md).

#define PLAYER_AVATAR_STATE_COUNT (PLAYER_AVATAR_STATE_VSSEEKER + 1)

#define OUTFIT_GFX(prefix)                                                                         \
{                                                                                                  \
    [PLAYER_AVATAR_STATE_NORMAL]     = {OBJ_EVENT_GFX_##prefix##_M_NORMAL,     OBJ_EVENT_GFX_##prefix##_F_NORMAL},     \
    [PLAYER_AVATAR_STATE_MACH_BIKE]  = {OBJ_EVENT_GFX_##prefix##_M_MACH_BIKE,  OBJ_EVENT_GFX_##prefix##_F_MACH_BIKE},  \
    [PLAYER_AVATAR_STATE_ACRO_BIKE]  = {OBJ_EVENT_GFX_##prefix##_M_ACRO_BIKE,  OBJ_EVENT_GFX_##prefix##_F_ACRO_BIKE},  \
    [PLAYER_AVATAR_STATE_SURFING]    = {OBJ_EVENT_GFX_##prefix##_M_SURFING,    OBJ_EVENT_GFX_##prefix##_F_SURFING},    \
    [PLAYER_AVATAR_STATE_UNDERWATER] = {OBJ_EVENT_GFX_##prefix##_M_UNDERWATER, OBJ_EVENT_GFX_##prefix##_F_UNDERWATER}, \
    [PLAYER_AVATAR_STATE_FIELD_MOVE] = {OBJ_EVENT_GFX_##prefix##_M_FIELD_MOVE, OBJ_EVENT_GFX_##prefix##_F_FIELD_MOVE}, \
    [PLAYER_AVATAR_STATE_FISHING]    = {OBJ_EVENT_GFX_##prefix##_M_FISHING,    OBJ_EVENT_GFX_##prefix##_F_FISHING},    \
    [PLAYER_AVATAR_STATE_WATERING]   = {OBJ_EVENT_GFX_##prefix##_M_WATERING,   OBJ_EVENT_GFX_##prefix##_F_WATERING},   \
    [PLAYER_AVATAR_STATE_VSSEEKER]   = {OBJ_EVENT_GFX_##prefix##_M_FIELD_MOVE, OBJ_EVENT_GFX_##prefix##_F_FIELD_MOVE}, \
}

static const u16 sOutfitAvatarGfx[PLAYER_OUTFIT_COUNT][PLAYER_AVATAR_STATE_COUNT][GENDER_COUNT] =
{
    [PLAYER_OUTFIT_DRACONID] = OUTFIT_GFX(DRACONID),
    [PLAYER_OUTFIT_MAGMA]    = OUTFIT_GFX(MAGMA),
};

static const u16 sOutfitDecoratingGfx[PLAYER_OUTFIT_COUNT][GENDER_COUNT] =
{
    [PLAYER_OUTFIT_DRACONID] = {OBJ_EVENT_GFX_DRACONID_M_DECORATING, OBJ_EVENT_GFX_DRACONID_F_DECORATING},
    [PLAYER_OUTFIT_MAGMA]    = {OBJ_EVENT_GFX_MAGMA_M_DECORATING, OBJ_EVENT_GFX_MAGMA_F_DECORATING},
};

// Trainer front + back pic per outfit and gender
static const enum TrainerPicID sOutfitTrainerPics[PLAYER_OUTFIT_COUNT][GENDER_COUNT] =
{
    [PLAYER_OUTFIT_DRACONID] = {TRAINER_PIC_DRACONID_M, TRAINER_PIC_DRACONID_F},
    [PLAYER_OUTFIT_MAGMA]    = {TRAINER_PIC_PLAYER_MAGMA_M, TRAINER_PIC_PLAYER_MAGMA_F},
};

u32 GetPlayerOutfit(void)
{
    u32 outfit = VarGet(VAR_PLAYER_OUTFIT);
    return outfit < PLAYER_OUTFIT_COUNT ? outfit : PLAYER_OUTFIT_DRACONID;
}

u16 GetPlayerOutfitAvatarGfx(u8 state, enum Gender gender)
{
    if (state >= PLAYER_AVATAR_STATE_COUNT)
        state = PLAYER_AVATAR_STATE_NORMAL;
    return sOutfitAvatarGfx[GetPlayerOutfit()][state][gender];
}

u16 GetPlayerOutfitDecoratingGfx(enum Gender gender)
{
    return sOutfitDecoratingGfx[GetPlayerOutfit()][gender];
}

bool32 IsFemaleOutfitAvatarGfx(u16 gfxId)
{
    u32 outfit, state;

    for (outfit = 0; outfit < PLAYER_OUTFIT_COUNT; outfit++)
    {
        for (state = 0; state < PLAYER_AVATAR_STATE_COUNT; state++)
        {
            if (sOutfitAvatarGfx[outfit][state][FEMALE] == gfxId)
                return TRUE;
        }
    }
    return FALSE;
}

// special GetPlayerOutfitNormalGfx: the player's standing sprite in the current outfit, for scripted
// stand-ins of the player (battle tents and Frontier rooms, the contest hall, Southern Island, Route 111).
u16 GetPlayerOutfitNormalGfx(void)
{
    return GetPlayerOutfitAvatarGfx(PLAYER_AVATAR_STATE_NORMAL, gSaveBlock2Ptr->playerGender);
}

// special SetPlayerOutfit: VAR_0x8004 = PLAYER_OUTFIT_*. Changes the player's sprite at once.
void SetPlayerOutfit(void)
{
    struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];

    VarSet(VAR_PLAYER_OUTFIT, gSpecialVar_0x8004 < PLAYER_OUTFIT_COUNT ? gSpecialVar_0x8004 : PLAYER_OUTFIT_DRACONID);
    ObjectEventSetGraphicsId(player, GetPlayerAvatarGraphicsIdByCurrentState());
    ObjectEventTurn(player, player->movementDirection);
}

enum TrainerPicID GetPlayerOutfitTrainerPic(enum Gender gender)
{
    return sOutfitTrainerPics[GetPlayerOutfit()][gender];
}
