#ifndef GUARD_DRACONID_H
#define GUARD_DRACONID_H

// Draconid Emerald script specials (src/draconid.c)
void DraconidRaiseHatchling(void);
u16 Draconid_ResolveVariantTrainer(u16 trainerId);
u16 Draconid_ResolveVariantPartner(u16 partnerId);

// Acts 6-7: the Sky Pillar finale (callnative from data/scripts/draconid/act7.pory)
struct ScriptContext;
void Draconid_PrepareRayquaza(struct ScriptContext *ctx);
void Draconid_DoRayquazaFlightScene(struct ScriptContext *ctx);
void Draconid_SaveBeforeCredits(struct ScriptContext *ctx);
void Draconid_StartCredits(struct ScriptContext *ctx);

#if DEBUG_OVERWORLD_MENU
// Emulator test hook (tools/hack/emu/play.py "warp"), debug builds only
#define DRACONID_TEST_WARP (1 << 0)
#define DRACONID_TEST_HEAL (1 << 1)

struct DraconidTestWarp
{
    u8 active; // DRACONID_TEST_* bits
    s8 mapGroup;
    s8 mapNum;
    s8 x;
    s8 y;
};
extern struct DraconidTestWarp gDraconidTestWarp;
bool32 Draconid_TryTestWarp(void);
#endif

#endif // GUARD_DRACONID_H
