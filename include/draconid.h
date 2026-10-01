#ifndef GUARD_DRACONID_H
#define GUARD_DRACONID_H

// Draconid Emerald script specials (src/draconid.c)
void DraconidRaiseHatchling(void);
bool32 Draconid_ShouldHatchEgg(void);
u16 Draconid_ResolveVariantTrainer(u16 trainerId);
u16 Draconid_ResolveVariantPartner(u16 partnerId);
bool32 Draconid_ShouldDoMaxieCall(void);
u16 Draconid_GetDueMaxieCall(void);

// Acts 6-7: the Sky Pillar finale (callnative from data/scripts/draconid/act7.pory)
struct ScriptContext;
void Draconid_PrepareRayquaza(struct ScriptContext *ctx);
void Draconid_DoRayquazaFlightScene(struct ScriptContext *ctx);
void Draconid_SaveBeforeCredits(struct ScriptContext *ctx);
void Draconid_StartCredits(struct ScriptContext *ctx);

// Act 7 extension: the attack on the village (data/scripts/draconid/act7x.pory)
struct WarpData;
bool32 Draconid_IsPrimalWeather(void);
bool32 Draconid_IsPrimalMusic(struct WarpData *warp);

#if DEBUG_OVERWORLD_MENU
// Emulator test hook (tools/hack/emu/play.py "warp"), debug builds only
#define DRACONID_TEST_WARP (1 << 0)
#define DRACONID_TEST_HEAL (1 << 1)
#define DRACONID_TEST_GIVE_ITEM (1 << 2)  // play.py "giveitem": one item into the bag
#define DRACONID_TEST_COUNT_HMS (1 << 3)  // play.py "expect_party_hms"
#define DRACONID_TEST_GIVE_MON  (1 << 4)  // play.py "givemon": species at level, holding item

struct DraconidTestWarp
{
    u8 active; // DRACONID_TEST_* bits
    s8 mapGroup;
    s8 mapNum;
    s8 x;
    s8 y;
    u8 partyHMMoves; // DRACONID_TEST_COUNT_HMS: how many HM moves the party knows
    u16 item;        // DRACONID_TEST_GIVE_ITEM; DRACONID_TEST_GIVE_MON: the held item (ITEM_NONE for none)
    u16 species;     // DRACONID_TEST_GIVE_MON
    u8 level;        // DRACONID_TEST_GIVE_MON
};
extern struct DraconidTestWarp gDraconidTestWarp;
bool32 Draconid_TryTestWarp(void);
#endif

#endif // GUARD_DRACONID_H
