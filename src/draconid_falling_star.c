// Draconid Emerald: the falling star of the opening (round 2, feedback 2.17, D-460).
//
// The new game's first night (data/maps/DraconidVillage_PlayersHouse_2F/scripts.pory): a star tears
// across the night sky and drops behind the clan's peaks, lighting the ridge for a moment. A scene of
// its own, like the Rayquaza flight (rayquaza_scene.c): it takes over the screen while the bedroom is
// faded to black, and returns to the field with the screen still black and the script waiting for it
// (callnative + waitstate), so the narration goes on over the dark bedroom as before.
//
// Art: the sky and the mountains are drawn by tools/hack/art/falling_star/build_falling_star.py
// (graphics/falling_star/); the star and its sparkles are Game Freak's - the star and the small and
// big sparkles of the FRLG Game Freak intro (src/intro_frlg.c), and Emerald's own intro sparkle
// (src/intro.c) for the bright stars' glints.

#include "global.h"
#include "draconid.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "main.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "random.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// Backgrounds: BG3 the sky, BG1 the mountains in front of the star (sprites at priority 2)
#define SKY_BG_CHARBASE        0
#define SKY_BG_SCREENBASE      31
#define MOUNTAIN_BG_CHARBASE   1
#define MOUNTAIN_BG_SCREENBASE 30
#define SKY_BG_PAL             0
#define MOUNTAIN_BG_PAL        1
#define SPRITE_PRIORITY        2 // over the sky, behind the mountains

// The sky palette's animated entries (build_falling_star.py: SKY_TWINKLE)
#define SKY_TWINKLE_FIRST      11
#define SKY_TWINKLE_COUNT      4
#define TWINKLE_PERIOD         64 // frames per twinkle (a triangle wave)
#define TWINKLE_STEPS          16
#define TWINKLE_SKEW           7  // frames added to each entry's phase step, so the four don't pulse in a rhythm
#define TWINKLE_DIM            RGB(6, 7, 12)
#define TWINKLE_BRIGHT         RGB(27, 28, 31)

// The mountain palette's glow entries (build_falling_star.py: M_GLOW_SHADE, M_GLOW_LIT): ring 1-3 on
// the shadowed and on the lit faces of the far ridge, by distance from the landing point
#define RIDGE_GLOW_SHADE_FIRST 9
#define RIDGE_GLOW_LIT_FIRST   12
#define RIDGE_GLOW_RINGS       3

// Where the star drops behind the far ridge (build_falling_star.py: LAND_X, LAND_Y)
#define LAND_X 128
#define LAND_Y 107

// The star's flight: from above the top-left corner down to the saddle and on behind the ridge,
// speeding up as it falls (progress t(t + T) / 2T^2: three times as fast at the end as at the start)
#define STAR_START_X       (-12)
#define STAR_START_Y       18
#define STAR_END_X         (LAND_X + (LAND_X - STAR_START_X) / 10)
#define STAR_END_Y         (LAND_Y + (LAND_Y - STAR_START_Y) / 10)
#define STAR_FLIGHT_FRAMES 58
#define STAR_HIDDEN_Y      (LAND_Y + 4) // most of the star is behind the ridge: it lands

// The trail: a sparkle every frame just behind the star, spread across the path, drifting back and
// sinking a little before it flickers out (FRLG's star trail, shorter-lived so it tapers)
#define TRAIL_INTERVAL      1
#define TRAIL_BACK_X        (-5) // behind the star, along its path
#define TRAIL_BACK_Y        (-3)
#define TRAIL_SPREAD        7    // across the path: -3..3 px
#define TRAIL_ACROSS_X      (-8) // the path's normal, in 1/16: (-8, 13) for a path going (13, 8)
#define TRAIL_ACROSS_Y      13
#define TRAIL_FIXED_SHIFT   6    // sparkle positions in 1/64 px
#define TRAIL_DRIFT_X       (-8) // 1/64 px per frame: drift back along the path
#define TRAIL_DRIFT_RANDOM  7    // and up to 7/64 px per frame more
#define TRAIL_FAN           16   // and apart, across the path: -16..16 / 64 px per frame (the wake fans out)
#define TRAIL_GRAVITY       1    // 1/64 px per frame, every frame: sinks slowly
#define TRAIL_FLICKER_FRAME 14
#define TRAIL_LIFE_FRAMES   24
#define TRAIL_SEED          0x24600D7A // the trail's own random sequence: the same sparkles every time

// The glints on the sky's bright stars (build_falling_star.py: BRIGHT_STARS), one every GLINT_INTERVAL frames
#define GLINT_INTERVAL 26

// The glow behind the ridge: an alpha-blended sprite over the sky and the ridge's glow entries
#define GLOW_HEIGHT      32 // the glow sprite: 64x32, brightest at the middle of its bottom row
#define GLOW_SINK        4  // rows of it hidden behind the ridge
#define BURST_RISE       2  // FRLG's big sparkle flashes this far above the landing point
#define GLOW_RISE_FRAMES 6
#define GLOW_HOLD_FRAMES 8
#define GLOW_FADE_FRAMES 54
#define GLOW_PEAK_EVA    11 // the sprite's blend coefficient at its brightest (the sky stays at 16: additive)
#define GLOW_LEVELS      16 // ridge glow level 0..16
#define RIDGE_GLOW_1     RGB(31, 27, 19)
#define RIDGE_GLOW_2     RGB(25, 19, 15)
#define RIDGE_GLOW_3     RGB(16, 12, 13)

// Timeline (frames from the scene's start)
#define FADE_IN_DELAY      1  // palette fade speed: 16 frames
#define STAR_APPEAR_FRAME  28
#define FADE_OUT_FRAME     142 // the star lands at about 82; the glow's last frames fade out with the screen
#define FADE_OUT_DELAY     1

#define SE_STREAK SE_M_DETECT
#define SE_LAND   SE_THUNDER2 // vanilla's rumble for the Deoxys rock on Birth Island: low and distant

enum
{
    TAG_STAR = 0x2460, // Draconid Emerald: D-460
    TAG_SPARKLES_SMALL,
    TAG_SPARKLES_BIG,
    TAG_GLINT,
    TAG_GLOW,
};

static const u32 sSky_Gfx[]           = INCGFX_U32("graphics/falling_star/sky.png", ".4bpp.smol");
static const u32 sSky_Tilemap[]       = INCGFX_U32("graphics/falling_star/sky.bin", ".smolTM");
static const u16 sSky_Pal[]           = INCGFX_U16("graphics/falling_star/sky.png", ".gbapal");
static const u32 sMountains_Gfx[]     = INCGFX_U32("graphics/falling_star/mountains.png", ".4bpp.smol");
static const u32 sMountains_Tilemap[] = INCGFX_U32("graphics/falling_star/mountains.bin", ".smolTM");
static const u16 sMountains_Pal[]     = INCGFX_U16("graphics/falling_star/mountains.png", ".gbapal");
static const u32 sGlow_Gfx[]          = INCGFX_U32("graphics/falling_star/glow.png", ".4bpp.smol");
static const u16 sGlow_Pal[]          = INCGFX_U16("graphics/falling_star/glow.png", ".gbapal");
// Game Freak's star from the FRLG Game Freak intro, in a white-gold palette (build_falling_star.py)
static const u32 sStar_Gfx[]          = INCGFX_U32("graphics/intro_frlg/game_freak/star.png", ".4bpp.smol");
static const u16 sStar_Pal[]          = INCGFX_U16("graphics/falling_star/star.pal", ".gbapal");
static const u32 sSparklesSmall_Gfx[] = INCGFX_U32("graphics/intro_frlg/game_freak/sparkles_small.png", ".4bpp.smol");
static const u32 sSparklesBig_Gfx[]   = INCGFX_U32("graphics/intro_frlg/game_freak/sparkles_big.png", ".4bpp.smol");
static const u16 sSparkles_Pal[]      = INCGFX_U16("graphics/intro_frlg/game_freak/sparkles.pal", ".gbapal");

static const struct CompressedSpriteSheet sSpriteSheets[] =
{
    {sStar_Gfx,          0x80,  TAG_STAR},
    {sSparklesSmall_Gfx, 0x80,  TAG_SPARKLES_SMALL},
    {sSparklesBig_Gfx,   0x800, TAG_SPARKLES_BIG},
    {gIntroSparkle_Gfx,  0x400, TAG_GLINT},
    {sGlow_Gfx,          0x400, TAG_GLOW},
};

static const struct SpritePalette sSpritePalettes[] =
{
    {sStar_Pal,           TAG_STAR},
    {sSparkles_Pal,       TAG_SPARKLES_SMALL},
    {gIntroLightning_Pal, TAG_GLINT}, // as in Emerald's intro
    {sGlow_Pal,           TAG_GLOW},
    {0},
};

static const struct OamData sOam_Star =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .matrixNum = ST_OAM_HFLIP, // the star's point leads: FRLG's flew to the left, this one to the right
    .priority = SPRITE_PRIORITY,
};

static const struct OamData sOam_SparkleSmall =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .size = SPRITE_SIZE(8x8),
    .priority = SPRITE_PRIORITY,
};

static const struct OamData sOam_SparkleBig =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = SPRITE_PRIORITY,
};

static const struct OamData sOam_Glint =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = SPRITE_PRIORITY,
};

static const struct OamData sOam_Glow =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_BLEND,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .size = SPRITE_SIZE(64x32),
    .priority = SPRITE_PRIORITY,
};

// FRLG's small sparkle loop (intro_frlg.c: sAnim_SparklesSmall_Loop)
static const union AnimCmd sAnim_SparkleSmall[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_JUMP(0),
};

// FRLG's big sparkle (intro_frlg.c: sAnim_SparklesBig)
static const union AnimCmd sAnim_SparkleBig[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(16, 6),
    ANIMCMD_FRAME(32, 6),
    ANIMCMD_FRAME(48, 6),
    ANIMCMD_END,
};

// Emerald's intro sparkle (intro.c: sAnim_Sparkle), played once: only its small frames (dot, cross, small
// x) - the long diagonal and the big X would read as strokes beside a star
static const union AnimCmd sAnim_Glint[] =
{
    ANIMCMD_FRAME(0, 3),
    ANIMCMD_FRAME(8, 3),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(8, 3),
    ANIMCMD_FRAME(0, 3),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnims_SparkleSmall[] = {sAnim_SparkleSmall};
static const union AnimCmd *const sAnims_SparkleBig[] = {sAnim_SparkleBig};
static const union AnimCmd *const sAnims_Glint[] = {sAnim_Glint};

static void SpriteCB_Star(struct Sprite *sprite);
static void SpriteCB_Trail(struct Sprite *sprite);
static void SpriteCB_DestroyAtAnimEnd(struct Sprite *sprite);

static const struct SpriteTemplate sSpriteTemplate_Star =
{
    .tileTag = TAG_STAR,
    .paletteTag = TAG_STAR,
    .oam = &sOam_Star,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Star,
};

static const struct SpriteTemplate sSpriteTemplate_Trail =
{
    .tileTag = TAG_SPARKLES_SMALL,
    .paletteTag = TAG_SPARKLES_SMALL,
    .oam = &sOam_SparkleSmall,
    .anims = sAnims_SparkleSmall,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Trail,
};

static const struct SpriteTemplate sSpriteTemplate_Burst =
{
    .tileTag = TAG_SPARKLES_BIG,
    .paletteTag = TAG_SPARKLES_SMALL,
    .oam = &sOam_SparkleBig,
    .anims = sAnims_SparkleBig,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_DestroyAtAnimEnd,
};

static const struct SpriteTemplate sSpriteTemplate_Glint =
{
    .tileTag = TAG_GLINT,
    .paletteTag = TAG_GLINT,
    .oam = &sOam_Glint,
    .anims = sAnims_Glint,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_DestroyAtAnimEnd,
};

static const struct SpriteTemplate sSpriteTemplate_Glow =
{
    .tileTag = TAG_GLOW,
    .paletteTag = TAG_GLOW,
    .oam = &sOam_Glow,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

// The sky's bright stars (build_falling_star.py: BRIGHT_STARS)
static const s16 sGlintCoords[][2] =
{
    { 30, 20},
    {147, 12},
    {211, 34},
    { 88, 52},
};

static const u16 sRidgeGlowColors[RIDGE_GLOW_RINGS] = {RIDGE_GLOW_1, RIDGE_GLOW_2, RIDGE_GLOW_3};

static void CB2_InitFallingStarScene(void);
static void CB2_FallingStarScene(void);
static void VBlankCB_FallingStarScene(void);
static void Task_FallingStarScene(u8 taskId);
static void CB2_ReturnToFieldInTheDark(void);
static void FieldCB_ContinueScriptInTheDark(void);

// Task data
#define tTimer     data[0]
#define tState     data[1]
#define tLanded    data[2] // set by the star's sprite callback
#define tLandFrame data[3]
#define tGlowId    data[4]
#define tGlintIdx  data[5]
#define tRngLo     data[6] // TRAIL_SEED's sequence (repeatable screenshots)
#define tRngHi     data[7]

enum
{
    STATE_FADE_IN,
    STATE_SKY,
    STATE_FADE_OUT,
    STATE_EXIT,
};

// Sprite data: the star
#define sTime   data[0]
#define sTaskId data[1]

// Sprite data: a trail sparkle
#define sPosX  data[0] // 1/64 px
#define sPosY  data[1]
#define sVelX  data[2]
#define sVelY  data[3]
#define sAge   data[4]

// callnative from the script, then waitstate: the scene ends in gMain.savedCallback (as the wall clock does),
// back on the field in the dark, where the script goes on
void Draconid_DoFallingStarScene(struct ScriptContext *ctx)
{
    gMain.savedCallback = CB2_ReturnToFieldInTheDark;
    SetMainCallback2(CB2_InitFallingStarScene);
}

static void SetSceneColor(u32 index, u16 color)
{
    gPlttBufferUnfaded[index] = color;
    if (!gPaletteFade.active)
        gPlttBufferFaded[index] = color;
}

static u16 BlendColor(u16 from, u16 to, u32 level, u32 levels)
{
    s32 r = GET_R(from) + (GET_R(to) - GET_R(from)) * (s32)level / (s32)levels;
    s32 g = GET_G(from) + (GET_G(to) - GET_G(from)) * (s32)level / (s32)levels;
    s32 b = GET_B(from) + (GET_B(to) - GET_B(from)) * (s32)level / (s32)levels;
    return RGB(r, g, b);
}

static void InitFallingStarScene(void)
{
    u32 i;

    SetVBlankHBlankCallbacksToNull();
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetVramOamAndBgCntRegs();

    DecompressDataWithHeaderVram(sSky_Gfx, (void *)BG_CHAR_ADDR(SKY_BG_CHARBASE));
    DecompressDataWithHeaderVram(sSky_Tilemap, (void *)BG_SCREEN_ADDR(SKY_BG_SCREENBASE));
    DecompressDataWithHeaderVram(sMountains_Gfx, (void *)BG_CHAR_ADDR(MOUNTAIN_BG_CHARBASE));
    DecompressDataWithHeaderVram(sMountains_Tilemap, (void *)BG_SCREEN_ADDR(MOUNTAIN_BG_SCREENBASE));
    LoadPalette(sSky_Pal, BG_PLTT_ID(SKY_BG_PAL), PLTT_SIZE_4BPP);
    LoadPalette(sMountains_Pal, BG_PLTT_ID(MOUNTAIN_BG_PAL), PLTT_SIZE_4BPP);
    for (i = 0; i < ARRAY_COUNT(sSpriteSheets); i++)
        LoadCompressedSpriteSheet(&sSpriteSheets[i]);
    LoadSpritePalettes(sSpritePalettes);

    SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3) | BGCNT_CHARBASE(SKY_BG_CHARBASE) | BGCNT_SCREENBASE(SKY_BG_SCREENBASE) | BGCNT_16COLOR | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(MOUNTAIN_BG_CHARBASE) | BGCNT_SCREENBASE(MOUNTAIN_BG_SCREENBASE) | BGCNT_16COLOR | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    // the glow sprite is semi-transparent: it adds its light to the sky (BG3) under it
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG1_ON | DISPCNT_BG3_ON | DISPCNT_OBJ_ON);

    BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
}

static void CB2_InitFallingStarScene(void)
{
    u8 taskId;

    InitFallingStarScene();
    taskId = CreateTask(Task_FallingStarScene, 0);
    gTasks[taskId].tGlowId = MAX_SPRITES;
    gTasks[taskId].tRngLo = TRAIL_SEED & 0xFFFF;
    gTasks[taskId].tRngHi = TRAIL_SEED >> 16;
    BeginNormalPaletteFade(PALETTES_ALL, FADE_IN_DELAY, 16, 0, RGB_BLACK);
    SetVBlankCallback(VBlankCB_FallingStarScene);
    SetMainCallback2(CB2_FallingStarScene);
}

static void CB2_FallingStarScene(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_FallingStarScene(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void UpdateTwinkles(s16 timer)
{
    u32 i, phase, level;

    for (i = 0; i < SKY_TWINKLE_COUNT; i++)
    {
        phase = (timer + i * (TWINKLE_PERIOD / SKY_TWINKLE_COUNT + TWINKLE_SKEW)) % TWINKLE_PERIOD;
        level = phase < TWINKLE_PERIOD / 2 ? phase : TWINKLE_PERIOD - 1 - phase;
        level = level * TWINKLE_STEPS / (TWINKLE_PERIOD / 2);
        SetSceneColor(BG_PLTT_ID(SKY_BG_PAL) + SKY_TWINKLE_FIRST + i, BlendColor(TWINKLE_DIM, TWINKLE_BRIGHT, level, TWINKLE_STEPS));
    }
}

// level: 0 (dark) .. GLOW_LEVELS (brightest)
static void SetRidgeGlow(u32 level)
{
    u32 i, entry;

    for (i = 0; i < RIDGE_GLOW_RINGS; i++)
    {
        entry = RIDGE_GLOW_SHADE_FIRST + i;
        SetSceneColor(BG_PLTT_ID(MOUNTAIN_BG_PAL) + entry, BlendColor(sMountains_Pal[entry], sRidgeGlowColors[i], level, GLOW_LEVELS));
        entry = RIDGE_GLOW_LIT_FIRST + i;
        SetSceneColor(BG_PLTT_ID(MOUNTAIN_BG_PAL) + entry, BlendColor(sMountains_Pal[entry], sRidgeGlowColors[i], level, GLOW_LEVELS));
    }
}

// 0 .. GLOW_LEVELS, from the frame the star landed
static u32 GetGlowLevel(s16 sinceLanding)
{
    if (sinceLanding < GLOW_RISE_FRAMES)
        return (sinceLanding + 1) * GLOW_LEVELS / GLOW_RISE_FRAMES;
    sinceLanding -= GLOW_RISE_FRAMES;
    if (sinceLanding < GLOW_HOLD_FRAMES)
        return GLOW_LEVELS;
    sinceLanding -= GLOW_HOLD_FRAMES;
    if (sinceLanding < GLOW_FADE_FRAMES)
        return (GLOW_FADE_FRAMES - sinceLanding) * GLOW_LEVELS / GLOW_FADE_FRAMES;
    return 0;
}

static void UpdateGlow(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u32 level;

    if (!tLanded)
        return;
    if (tLandFrame == 0)
    {
        tLandFrame = tTimer;
        PlaySE(SE_LAND);
        tGlowId = CreateSprite(&sSpriteTemplate_Glow, LAND_X, LAND_Y + GLOW_SINK - GLOW_HEIGHT / 2, 0);
        CreateSprite(&sSpriteTemplate_Burst, LAND_X, LAND_Y - BURST_RISE, 0);
    }
    level = GetGlowLevel(tTimer - tLandFrame);
    SetRidgeGlow(level);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(level * GLOW_PEAK_EVA / GLOW_LEVELS, 16));
    if (level == 0 && tGlowId != MAX_SPRITES)
    {
        DestroySprite(&gSprites[tGlowId]);
        tGlowId = MAX_SPRITES;
    }
}

static void Task_FallingStarScene(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 spriteId;

    UpdateTwinkles(tTimer);
    if (tTimer % GLINT_INTERVAL == GLINT_INTERVAL / 2)
    {
        CreateSprite(&sSpriteTemplate_Glint, sGlintCoords[tGlintIdx][0], sGlintCoords[tGlintIdx][1], 1);
        tGlintIdx = (tGlintIdx + 1) % ARRAY_COUNT(sGlintCoords);
    }
    if (tTimer == STAR_APPEAR_FRAME)
    {
        spriteId = CreateSprite(&sSpriteTemplate_Star, STAR_START_X, STAR_START_Y, 0);
        if (spriteId != MAX_SPRITES)
            gSprites[spriteId].sTaskId = taskId;
        PlaySE(SE_STREAK);
    }
    UpdateGlow(taskId);

    switch (tState)
    {
    case STATE_FADE_IN:
        if (!gPaletteFade.active)
            tState = STATE_SKY;
        break;
    case STATE_SKY:
        if (tTimer >= FADE_OUT_FRAME)
        {
            BeginNormalPaletteFade(PALETTES_ALL, FADE_OUT_DELAY, 0, 16, RGB_BLACK);
            tState = STATE_FADE_OUT;
        }
        break;
    case STATE_FADE_OUT:
        if (!gPaletteFade.active)
            tState = STATE_EXIT;
        break;
    case STATE_EXIT:
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetVBlankCallback(NULL);
        ResetSpriteData();
        FreeAllSpritePalettes();
        DestroyTask(taskId);
        SetMainCallback2(gMain.savedCallback);
        return;
    }
    tTimer++;
}

static u32 NextTrailRandom(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u32 seed = ((u32)(u16)tRngHi << 16) | (u16)tRngLo;

    seed = ISO_RANDOMIZE1(seed);
    tRngLo = seed;
    tRngHi = seed >> 16;
    return seed >> 16;
}

static void CreateTrailSparkle(u8 taskId, s16 x, s16 y)
{
    u32 random = NextTrailRandom(taskId);
    s32 across = (s32)(random % TRAIL_SPREAD) - TRAIL_SPREAD / 2;
    s32 fan;
    u8 spriteId;

    x += TRAIL_BACK_X + across * TRAIL_ACROSS_X / 16;
    y += TRAIL_BACK_Y + across * TRAIL_ACROSS_Y / 16;
    spriteId = CreateSprite(&sSpriteTemplate_Trail, x, y, 1);
    if (spriteId == MAX_SPRITES)
        return;
    gSprites[spriteId].sPosX = x << TRAIL_FIXED_SHIFT;
    gSprites[spriteId].sPosY = y << TRAIL_FIXED_SHIFT;
    fan = (s32)((random >> 11) % (2 * TRAIL_FAN + 1)) - TRAIL_FAN;
    gSprites[spriteId].sVelX = TRAIL_DRIFT_X - (s32)((random >> 4) % (TRAIL_DRIFT_RANDOM + 1)) + fan * TRAIL_ACROSS_X / 16;
    gSprites[spriteId].sVelY = fan * TRAIL_ACROSS_Y / 16;
    // start the twinkle at a random frame so the trail doesn't flash in step
    SeekSpriteAnim(&gSprites[spriteId], (random >> 8) & 3);
}

static void SpriteCB_Star(struct Sprite *sprite)
{
    s32 t = ++sprite->sTime;
    s32 progress = t * (t + STAR_FLIGHT_FRAMES);
    s32 total = 2 * STAR_FLIGHT_FRAMES * STAR_FLIGHT_FRAMES;

    sprite->x = STAR_START_X + (STAR_END_X - STAR_START_X) * progress / total;
    sprite->y = STAR_START_Y + (STAR_END_Y - STAR_START_Y) * progress / total;
    if (sprite->y < STAR_HIDDEN_Y && t % TRAIL_INTERVAL == 0)
        CreateTrailSparkle(sprite->sTaskId, sprite->x, sprite->y);
    if (sprite->y >= STAR_HIDDEN_Y)
        gTasks[sprite->sTaskId].tLanded = TRUE;
    if (t >= STAR_FLIGHT_FRAMES)
        DestroySprite(sprite);
}

static void SpriteCB_Trail(struct Sprite *sprite)
{
    sprite->sVelY += TRAIL_GRAVITY;
    sprite->sPosX += sprite->sVelX;
    sprite->sPosY += sprite->sVelY;
    sprite->x = sprite->sPosX >> TRAIL_FIXED_SHIFT;
    sprite->y = sprite->sPosY >> TRAIL_FIXED_SHIFT;
    if (++sprite->sAge > TRAIL_FLICKER_FRAME)
        sprite->invisible ^= TRUE;
    if (sprite->sAge > TRAIL_LIFE_FRAMES)
        DestroySprite(sprite);
}

static void SpriteCB_DestroyAtAnimEnd(struct Sprite *sprite)
{
    if (sprite->animEnded)
        DestroySprite(sprite);
}

// Back on the field with the screen still black: the script goes on over the dark bedroom (its next
// box), and its own fadescreen(FADE_FROM_BLACK) brings the room back
static void CB2_ReturnToFieldInTheDark(void)
{
    gFieldCallback = FieldCB_ContinueScriptInTheDark;
    CB2_ReturnToField();
}

static void FieldCB_ContinueScriptInTheDark(void)
{
    LockPlayerFieldControls();
    CpuFastFill16(RGB_BLACK, gPlttBufferFaded, PLTT_SIZE);
    ScriptContext_Enable();
}
