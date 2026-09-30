#ifndef GUARD_PLAYER_OUTFIT_H
#define GUARD_PLAYER_OUTFIT_H

// Draconid Emerald: player outfits (VAR_PLAYER_OUTFIT, constants/outfits.h).
// Each outfit has its own overworld graphics per avatar state and gender.

u32 GetPlayerOutfit(void);
u16 GetPlayerOutfitAvatarGfx(u8 state, enum Gender gender);
u16 GetPlayerOutfitNormalGfx(void);
u16 GetOutfitAvatarGfx(u32 outfit, u8 state, enum Gender gender);
u16 GetPlayerOutfitDecoratingGfx(enum Gender gender);
bool32 IsFemaleOutfitAvatarGfx(u16 gfxId);
void SetPlayerOutfit(void);
enum TrainerPicID GetPlayerOutfitTrainerPic(enum Gender gender);

#endif // GUARD_PLAYER_OUTFIT_H
