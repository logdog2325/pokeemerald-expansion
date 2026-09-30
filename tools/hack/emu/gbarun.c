// gbarun - headless GBA runner for Draconid Emerald smoke tests (libmgba).
//
//   gcc -O2 -o tools/hack/emu/gbarun tools/hack/emu/gbarun.c -lmgba -lpng
//   tools/hack/emu/gbarun pokeemerald.gba script.txt outdir
//
// Script (one command per line, '#' starts a comment):
//   run N                 run N frames with no keys held
//   press KEYS [H] [R]    hold KEYS (e.g. A, START, DOWN+B) for H frames (default 4), then
//                         release for R frames (default 16)
//   hold KEYS N           hold KEYS for N frames
//   repeat N <command>    repeat a press/hold/run command N times
//   shot NAME             save outdir/NAME.png (240x160)
//   savestate FILE        write a savestate
//   loadstate FILE        load a savestate
//   peek ADDR LEN         print LEN bytes at bus address ADDR (hex) to stdout
//   poke ADDR BYTE        write one byte (hex) at bus address ADDR
//   echo TEXT             print TEXT
// Keys: A B SELECT START RIGHT LEFT UP DOWN R L

#include <mgba/flags.h>
#include <mgba/core/core.h>
#include <mgba/core/log.h>
#include <mgba/core/serialize.h>
#include <mgba-util/png-io.h>
#include <mgba-util/vfs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static struct mCore *core;
static color_t *video;
static unsigned vw, vh;
static const char *outdir;

static uint32_t parse_keys(const char *s)
{
    static const char *names[] = {"A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN", "R", "L"};
    uint32_t keys = 0;
    char buf[128];
    snprintf(buf, sizeof(buf), "%s", s);
    for (char *tok = strtok(buf, "+"); tok; tok = strtok(NULL, "+"))
    {
        int found = 0;
        for (unsigned i = 0; i < sizeof(names) / sizeof(names[0]); i++)
        {
            if (strcmp(tok, names[i]) == 0)
            {
                keys |= 1u << i;
                found = 1;
            }
        }
        if (!found)
            fprintf(stderr, "unknown key '%s'\n", tok);
    }
    return keys;
}

// "0x0300xxxx", "*0x0300xxxx" (read a u32 pointer there) or "*0x0300xxxx+0x1c"
static uint32_t eval_addr(const char *s)
{
    uint32_t base, off = 0;
    const char *plus = strchr(s, '+');
    if (plus)
        off = strtoul(plus + 1, NULL, 16);
    if (s[0] == '*')
    {
        uint32_t p = strtoul(s + 1, NULL, 16);
        base = core->busRead32(core, p);
    }
    else
    {
        base = strtoul(s, NULL, 16);
    }
    return base + off;
}

static uint32_t read_n(uint32_t addr, int size)
{
    if (size == 1)
        return core->busRead8(core, addr);
    if (size == 2)
        return core->busRead16(core, addr);
    return core->busRead32(core, addr);
}

static void frames(uint32_t keys, int n)
{
    core->setKeys(core, keys);
    for (int i = 0; i < n; i++)
        core->runFrame(core);
    core->setKeys(core, 0);
}

static void shot(const char *name)
{
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s.png", outdir, name);
    struct VFile *vf = VFileOpen(path, O_CREAT | O_TRUNC | O_WRONLY);
    if (!vf)
    {
        fprintf(stderr, "cannot write %s\n", path);
        return;
    }
    png_structp png = PNGWriteOpen(vf);
    png_infop info = PNGWriteHeader(png, vw, vh);
    PNGWritePixels(png, vw, vh, vw, video);
    PNGWriteClose(png, info);
    vf->close(vf);
    printf("shot %s\n", path);
}

static void command(char *line);

static void quiet_log(struct mLogger *logger, int category, enum mLogLevel level, const char *format, va_list args)
{
    (void)logger;
    (void)category;
    if (level & (mLOG_FATAL | mLOG_ERROR))
    {
        vfprintf(stderr, format, args);
        fputc('\n', stderr);
    }
}

static struct mLogger sQuietLogger = {.log = quiet_log, .filter = NULL};

static void command(char *line)
{
    char cmd[64] = {0}, a[512] = {0}, b[64] = {0}, c[64] = {0};
    int n = sscanf(line, "%63s %511s %63s %63s", cmd, a, b, c);
    if (n <= 0 || cmd[0] == '#')
        return;
    if (!strcmp(cmd, "run"))
        frames(0, atoi(a));
    else if (!strcmp(cmd, "press"))
    {
        frames(parse_keys(a), n > 2 ? atoi(b) : 4);
        frames(0, n > 3 ? atoi(c) : 16);
    }
    else if (!strcmp(cmd, "hold"))
        frames(parse_keys(a), atoi(b));
    else if (!strcmp(cmd, "repeat"))
    {
        int times = atoi(a);
        char *rest = strstr(line, a) + strlen(a);
        while (*rest && isspace((unsigned char)*rest))
            rest++;
        char sub[512];
        for (int i = 0; i < times; i++)
        {
            snprintf(sub, sizeof(sub), "%s", rest);
            command(sub);
        }
    }
    else if (!strcmp(cmd, "shot"))
        shot(a);
    else if (!strcmp(cmd, "savestate") || !strcmp(cmd, "loadstate"))
    {
        int save = !strcmp(cmd, "savestate");
        struct VFile *vf = VFileOpen(a, save ? (O_CREAT | O_TRUNC | O_RDWR) : O_RDONLY);
        if (!vf)
        {
            fprintf(stderr, "cannot open %s\n", a);
            return;
        }
        bool ok = save ? mCoreSaveStateNamed(core, vf, SAVESTATE_SAVEDATA | SAVESTATE_RTC)
                       : mCoreLoadStateNamed(core, vf, SAVESTATE_SAVEDATA | SAVESTATE_RTC);
        vf->close(vf);
        printf("%s %s %s\n", cmd, a, ok ? "ok" : "FAILED");
    }
    else if (!strcmp(cmd, "until"))
    {
        // until ADDR SIZE VALUE MAXFRAMES [KEYS PERIOD]: run until *(ADDR) == VALUE (or != VALUE when
        // VALUE is written !VALUE), tapping KEYS for 2 frames every PERIOD frames while waiting
        char addr_s[128], value_s[32], keys_s[64] = "";
        unsigned size, maxf, period = 0;
        int got = sscanf(line, "%*s %127s %u %31s %u %63s %u", addr_s, &size, value_s, &maxf, keys_s, &period);
        int negate = value_s[0] == '!';
        unsigned long value = strtoul(value_s + negate, NULL, 16);
        // KEYS may be a comma-separated cycle, e.g. "A,UP": each tap uses the next entry
        uint32_t cycle[8];
        int ncycle = 0, next = 0;
        if (got >= 6)
        {
            for (char *tok = strtok(keys_s, ","); tok && ncycle < 8; tok = strtok(NULL, ","))
                cycle[ncycle++] = parse_keys(tok);
        }
        unsigned f = 0;
        while (f < maxf && (read_n(eval_addr(addr_s), size) == (uint32_t)value) == negate)
        {
            if (ncycle && period && f % period == 0)
            {
                frames(cycle[next], 2);
                next = (next + 1) % ncycle;
                f += 2;
            }
            else
            {
                frames(0, 1);
                f++;
            }
        }
        printf("until %s %s %lx: %s after %u frames\n", addr_s, negate ? "!=" : "==", value, f < maxf ? "ok" : "TIMEOUT", f);
    }
    else if (!strcmp(cmd, "untilhold"))
    {
        // untilhold ADDR SIZE VALUE MAXFRAMES KEYS: hold KEYS until *(ADDR) == VALUE
        char addr_s[128], keys_s[64];
        unsigned size, maxf, f = 0;
        unsigned long value;
        sscanf(line, "%*s %127s %u %lx %u %63s", addr_s, &size, &value, &maxf, keys_s);
        uint32_t keys = parse_keys(keys_s);
        core->setKeys(core, keys);
        while (f < maxf && read_n(eval_addr(addr_s), size) != (uint32_t)value)
        {
            core->runFrame(core);
            f++;
        }
        core->setKeys(core, 0);
        // let the current step finish so the player is centred on the tile
        for (int i = 0; i < 16; i++)
            core->runFrame(core);
        printf("untilhold %s == %lx: %s after %u frames\n", addr_s, value, f < maxf ? "ok" : "TIMEOUT", f);
    }
    else if (!strcmp(cmd, "read"))
    {
        // read ADDR SIZE LABEL
        char addr_s[128];
        unsigned size;
        char label[128] = "";
        sscanf(line, "%*s %127s %u %127s", addr_s, &size, label);
        printf("read %s = 0x%X\n", label[0] ? label : addr_s, read_n(eval_addr(addr_s), size));
    }
    else if (!strcmp(cmd, "peek"))
    {
        uint32_t addr = eval_addr(a);
        int len = atoi(b);
        printf("peek %08X:", addr);
        for (int i = 0; i < len; i++)
            printf(" %02X", core->busRead8(core, addr + i));
        printf("\n");
    }
    else if (!strcmp(cmd, "poke"))
        core->busWrite8(core, eval_addr(a), strtoul(b, NULL, 16));
    else if (!strcmp(cmd, "pokebit"))
    {
        // pokebit ADDR BIT 0|1: set or clear one bit of a byte (save-block flags)
        char addr_s[128];
        unsigned bit, val;
        sscanf(line, "%*s %127s %u %u", addr_s, &bit, &val);
        uint32_t addr = eval_addr(addr_s);
        uint8_t v = core->busRead8(core, addr);
        v = val ? (v | (1u << bit)) : (v & ~(1u << bit));
        core->busWrite8(core, addr, v);
    }
    else if (!strcmp(cmd, "echo"))
        printf("%s", line + 5);
    else
        fprintf(stderr, "unknown command '%s'\n", cmd);
    fflush(stdout);
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "usage: %s rom.gba script.txt outdir\n", argv[0]);
        return 2;
    }
    outdir = argv[3];
    mLogSetDefaultLogger(&sQuietLogger);
    core = mCoreFind(argv[1]);
    if (!core || !core->init(core))
    {
        fprintf(stderr, "cannot create core for %s\n", argv[1]);
        return 1;
    }
    mCoreInitConfig(core, NULL);
    core->desiredVideoDimensions(core, &vw, &vh);
    video = calloc(vw * vh, sizeof(color_t));
    core->setVideoBuffer(core, video, vw);
    if (!mCoreLoadFile(core, argv[1]))
    {
        fprintf(stderr, "cannot load %s\n", argv[1]);
        return 1;
    }
    core->reset(core);

    FILE *f = fopen(argv[2], "r");
    if (!f)
    {
        fprintf(stderr, "cannot open script %s\n", argv[2]);
        return 1;
    }
    char line[1024];
    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\r\n")] = 0;
        command(line);
    }
    fclose(f);
    core->deinit(core);
    free(video);
    return 0;
}
