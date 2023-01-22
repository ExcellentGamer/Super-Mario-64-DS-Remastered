// configfile.c - handles loading and saving the configuration options
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "platform.h"
#include "cheats.h"
#include "configfile.h"
#include "cliopts.h"
#include "gfx/gfx_screen_config.h"
#include "gfx/gfx_window_manager_api.h"
#include "controller/controller_api.h"
#include "fs/fs.h"

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

enum ConfigOptionType {
    CONFIG_TYPE_BOOL,
    CONFIG_TYPE_UINT,
    CONFIG_TYPE_FLOAT,
    CONFIG_TYPE_BIND,
};

struct ConfigOption {
    const char *name;
    enum ConfigOptionType type;
    union {
        bool *boolValue;
        unsigned int *uintValue;
        float *floatValue;
    };
};

/*
 *Config options and default values
 */

// Video/audio stuff
ConfigWindow configWindow       = {
    .x = WAPI_WIN_CENTERPOS,
    .y = WAPI_WIN_CENTERPOS,
    .w = DESIRED_SCREEN_WIDTH,
    .h = DESIRED_SCREEN_HEIGHT,
    .vsync = false,
    .reset = false,
    .fullscreen = false,
    .exiting_fullscreen = false,
    .settings_changed = false,
};

unsigned int configLanguage     = 0;
#ifdef TARGET_SWITCH
bool configSwitchHud            = true;
bool configPrecacheRes          = false;
#else
bool configPrecacheRes          = true;
#endif
bool configBillboard            = 0;

unsigned int configFiltering        = 1;          // 0=force nearest, 1=linear, (TODO) 2=three-point
unsigned int configMasterVolume     = MAX_VOLUME; // 0 - MAX_VOLUME
unsigned int configMusicVolume      = MAX_VOLUME;
unsigned int configSfxVolume        = MAX_VOLUME;
unsigned int configEnvVolume        = MAX_VOLUME;
bool         configMusicMute        = 0;
bool         configSfxMute          = 0;
bool         configEnvMute          = 0;

// Keyboard mappings (VK_ values, by default keyboard/gamepad/mouse)
unsigned int configKeyA[MAX_BINDS]          = { 0x0026,   0x1000,     0x1103     };
unsigned int configKeyB[MAX_BINDS]          = { 0x0033,   0x1002,     0x1101     };
unsigned int configKeyStart[MAX_BINDS]      = { 0x0039,   0x1006,     VK_INVALID };
unsigned int configKeyL[MAX_BINDS]          = { 0x002A,   0x1009,     0x1104     };
unsigned int configKeyR[MAX_BINDS]          = { 0x0036,   0x100A,     0x101B     };
unsigned int configKeyZ[MAX_BINDS]          = { 0x0025,   0x1007,     0x101A     };
unsigned int configKeyCUp[MAX_BINDS]        = { 0x0148,   VK_INVALID, VK_INVALID };
unsigned int configKeyCDown[MAX_BINDS]      = { 0x0150,   VK_INVALID, VK_INVALID };
unsigned int configKeyCLeft[MAX_BINDS]      = { 0x014B,   VK_INVALID, VK_INVALID };
unsigned int configKeyCRight[MAX_BINDS]     = { 0x014D,   VK_INVALID, VK_INVALID };
unsigned int configKeyDUp[MAX_BINDS]        = { 0x000C,   0x100B,     VK_INVALID };
unsigned int configKeyDDown[MAX_BINDS]      = { 0x001A,   0x100C,     VK_INVALID };
unsigned int configKeyDLeft[MAX_BINDS]      = { 0x0019,   0x100D,     VK_INVALID };
unsigned int configKeyDRight[MAX_BINDS]     = { 0x001B,   0x100E,     VK_INVALID };
unsigned int configKeyStickUp[MAX_BINDS]    = { 0x0011,   VK_INVALID, VK_INVALID };
unsigned int configKeyStickDown[MAX_BINDS]  = { 0x001F,   VK_INVALID, VK_INVALID };
unsigned int configKeyStickLeft[MAX_BINDS]  = { 0x001E,   VK_INVALID, VK_INVALID };
unsigned int configKeyStickRight[MAX_BINDS] = { 0x0020,   VK_INVALID, VK_INVALID };
unsigned int configStickDeadzone = 16; // 16*DEADZONE_STEP=4960 (the original default deadzone)
unsigned int configRumbleStrength = 50;

// BetterCamera settings
unsigned int configCameraXSens   = 50;
unsigned int configCameraYSens   = 50;
unsigned int configCameraAggr    = 0;
unsigned int configCameraPan     = 0;
unsigned int configCameraDegrade = 10; // 0 - 100%
bool         configCameraInvertX = true;
bool         configCameraInvertY = false;
bool         configEnableCamera  = false;
bool         configCameraAnalog  = true;
bool         configCameraMouse   = false;
bool         configSkipIntro     = 0;
bool         configHUD           = true;
unsigned int configDrawDistance  = 100;
#ifdef DISCORDRPC
bool         configDiscordRPC    = true;
#endif
#ifdef RAPI_RT64
unsigned int configRT64TargetFPS = 30;
unsigned int configRT64ResScale = 100;
unsigned int configRT64MaxLights = 6;
unsigned int configRT64MotionBlurStrength = 0;
unsigned int configRT64UpscalerSharpness = 0;
bool         configRT64SphereLights = false;
bool         configRT64GI = false;
unsigned int configRT64Upscaler = 1;
unsigned int configRT64UpscalerMode = 0;
bool         configRT64Denoiser = false;
bool         configRT64StaticMeshCache = true;
#endif

// 60fps init
bool         config60FPS         = true; 

// Resolution settings, thanks to Mors!
bool         configInternalResolutionBool       = true;
unsigned int configCustomInternalResolution     = 1;
unsigned int configInternalResolutionWidth;
unsigned int configInternalResolutionHeight;
//unsigned int configCustomWindowResolution       = 2;
bool         configForce4by3                    = false;


static const struct ConfigOption options[] = {
    {.name = "fullscreen",           .type = CONFIG_TYPE_BOOL, .boolValue = &configWindow.fullscreen},
    {.name = "window_x",             .type = CONFIG_TYPE_UINT, .uintValue = &configWindow.x},
    {.name = "window_y",             .type = CONFIG_TYPE_UINT, .uintValue = &configWindow.y},
    {.name = "window_w",             .type = CONFIG_TYPE_UINT, .uintValue = &configWindow.w},
    {.name = "window_h",             .type = CONFIG_TYPE_UINT, .uintValue = &configWindow.h},
    {.name = "vsync",                .type = CONFIG_TYPE_BOOL, .boolValue = &configWindow.vsync},
    {.name = "60fps",                .type = CONFIG_TYPE_BOOL, .boolValue = &config60FPS },
    {.name = "internal_bool",        .type = CONFIG_TYPE_BOOL, .boolValue = &configInternalResolutionBool},
    {.name = "internal_swap",        .type = CONFIG_TYPE_UINT, .uintValue = &configCustomInternalResolution},
    {.name = "internal_w",           .type = CONFIG_TYPE_UINT, .uintValue = &configInternalResolutionWidth},
    {.name = "internal_h",           .type = CONFIG_TYPE_UINT, .uintValue = &configInternalResolutionHeight},
//    {.name = "window_swap",          .type = CONFIG_TYPE_UINT, .uintValue = &configCustomWindowResolution},
    {.name = "force4by3",            .type = CONFIG_TYPE_BOOL, .boolValue = &configForce4by3},
    {.name = "texture_filtering",    .type = CONFIG_TYPE_UINT, .uintValue = &configFiltering},
    {.name = "drawing_distance",     .type = CONFIG_TYPE_UINT, .uintValue = &configDrawDistance},
    {.name = "master_volume",        .type = CONFIG_TYPE_UINT, .uintValue = &configMasterVolume},
    {.name = "music_volume",         .type = CONFIG_TYPE_UINT, .uintValue = &configMusicVolume},
    {.name = "sfx_volume",           .type = CONFIG_TYPE_UINT, .uintValue = &configSfxVolume},
    {.name = "env_volume",           .type = CONFIG_TYPE_UINT, .uintValue = &configEnvVolume},
    {.name = "key_a",                .type = CONFIG_TYPE_BIND, .uintValue = configKeyA},
    {.name = "key_b",                .type = CONFIG_TYPE_BIND, .uintValue = configKeyB},
    {.name = "key_start",            .type = CONFIG_TYPE_BIND, .uintValue = configKeyStart},
    {.name = "key_l",                .type = CONFIG_TYPE_BIND, .uintValue = configKeyL},
    {.name = "key_r",                .type = CONFIG_TYPE_BIND, .uintValue = configKeyR},
    {.name = "key_z",                .type = CONFIG_TYPE_BIND, .uintValue = configKeyZ},
    {.name = "key_cup",              .type = CONFIG_TYPE_BIND, .uintValue = configKeyCUp},
    {.name = "key_cdown",            .type = CONFIG_TYPE_BIND, .uintValue = configKeyCDown},
    {.name = "key_cleft",            .type = CONFIG_TYPE_BIND, .uintValue = configKeyCLeft},
    {.name = "key_cright",           .type = CONFIG_TYPE_BIND, .uintValue = configKeyCRight},
    {.name = "key_dup",              .type = CONFIG_TYPE_BIND, .uintValue = configKeyDUp},
    {.name = "key_ddown",            .type = CONFIG_TYPE_BIND, .uintValue = configKeyDDown},
    {.name = "key_dleft",            .type = CONFIG_TYPE_BIND, .uintValue = configKeyDLeft},
    {.name = "key_dright",           .type = CONFIG_TYPE_BIND, .uintValue = configKeyDRight},
    {.name = "key_stickup",          .type = CONFIG_TYPE_BIND, .uintValue = configKeyStickUp},
    {.name = "key_stickdown",        .type = CONFIG_TYPE_BIND, .uintValue = configKeyStickDown},
    {.name = "key_stickleft",        .type = CONFIG_TYPE_BIND, .uintValue = configKeyStickLeft},
    {.name = "key_stickright",       .type = CONFIG_TYPE_BIND, .uintValue = configKeyStickRight},
    {.name = "stick_deadzone",       .type = CONFIG_TYPE_UINT, .uintValue = &configStickDeadzone},
    {.name = "rumble_strength",      .type = CONFIG_TYPE_UINT, .uintValue = &configRumbleStrength},
    {.name = "precache",             .type = CONFIG_TYPE_BOOL, .boolValue = &configPrecacheRes},
    {.name = "language",             .type = CONFIG_TYPE_UINT, .uintValue = &configLanguage},
    #ifdef TARGET_SWITCH
    {.name = "nx_hud",               .type = CONFIG_TYPE_BOOL, .boolValue = &configSwitchHud},
    #endif
    {.name = "disable_billboard",    .type = CONFIG_TYPE_BOOL, .boolValue = &configBillboard},
    {.name = "bettercam_enable",     .type = CONFIG_TYPE_BOOL, .boolValue = &configEnableCamera},
    {.name = "bettercam_analog",     .type = CONFIG_TYPE_BOOL, .boolValue = &configCameraAnalog},
    {.name = "bettercam_mouse_look", .type = CONFIG_TYPE_BOOL, .boolValue = &configCameraMouse},
    {.name = "bettercam_invertx",    .type = CONFIG_TYPE_BOOL, .boolValue = &configCameraInvertX},
    {.name = "bettercam_inverty",    .type = CONFIG_TYPE_BOOL, .boolValue = &configCameraInvertY},
    {.name = "bettercam_xsens",      .type = CONFIG_TYPE_UINT, .uintValue = &configCameraXSens},
    {.name = "bettercam_ysens",      .type = CONFIG_TYPE_UINT, .uintValue = &configCameraYSens},
    {.name = "bettercam_aggression", .type = CONFIG_TYPE_UINT, .uintValue = &configCameraAggr},
    {.name = "bettercam_pan_level",  .type = CONFIG_TYPE_UINT, .uintValue = &configCameraPan},
    {.name = "bettercam_degrade",    .type = CONFIG_TYPE_UINT, .uintValue = &configCameraDegrade},
    {.name = "skip_intro",           .type = CONFIG_TYPE_BOOL, .boolValue = &configSkipIntro},
    {.name = "cheats_enable",               .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.EnableCheats},
    {.name = "cheats_moon_jump",            .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.MoonJump},
    {.name = "cheats_god_mode",             .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.GodMode},
    {.name = "cheats_infinite_lives",       .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.InfiniteLives},
    {.name = "cheats_responsive",           .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.Responsive},
    {.name = "cheats_moon_gravity",         .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.MoonGravity},
    // {.name = "cheats_debug_move",           .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.DebugMove},
    {.name = "cheats_super_copter",         .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.SuperCopter},
    {.name = "cheats_auto_wall_kick",       .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.AutoWallKick},
    {.name = "cheats_no_hold_heavy",        .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.NoHoldHeavy},
    {.name = "cheats_speed_modifier",       .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.SpeedModifier},
    {.name = "cheats_jump_modifier",        .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.JumpModifier},
    {.name = "cheats_swim_modifier",        .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.SwimModifier},
    {.name = "cheats_size_modifier",        .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.SizeModifier},
    {.name = "cheats_cap_modifier",         .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.CapModifier},
    {.name = "cheats_super_wing_cap",       .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.SuperWingCap},
    // {.name = "cheats_play_as",              .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.PlayAs},
    // {.name = "cheats_jukebox",              .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.Jukebox},
    // {.name = "cheats_jukebox_music",        .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.JukeboxMusic},
    {.name = "cheats_speed_display",        .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.SpeedDisplay},
    {.name = "cheats_blj_anywhere",         .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.BLJAnywhere},
    {.name = "cheats_swim_anywhere",        .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.SwimAnywhere},
    {.name = "cheats_exit_anywhere",        .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.ExitAnywhere},
    {.name = "cheats_walk_on_hazards",      .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.WalkOnHazards},
    {.name = "cheats_no_death_barrier",     .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.NoDeathBarrier},
    {.name = "cheats_no_bounds",            .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.NoBounds},
    {.name = "cheats_water_level",          .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.WaterLevel},
    {.name = "cheats_coins_magnet",         .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.CoinsMagnet},
    // {.name = "cheats_time_stop",            .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.TimeStop},
    // {.name = "cheats_quick_ending",         .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.QuickEnding},
    {.name = "cheats_hurt_mario",           .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.HurtMario},
    {.name = "cheats_spamba",               .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.Spamba},
    {.name = "cheats_spamba_index",         .type = CONFIG_TYPE_UINT, .uintValue = &Cheats.SpambaIndex},
    // {.name = "cheats_chaos_mode",           .type = CONFIG_TYPE_BOOL, .boolValue = &Cheats.ChaosMode},
    {.name = "cheats_key_time_stop",        .type = CONFIG_TYPE_BIND, .uintValue = CheatsControls.TimeStopButton},
    {.name = "cheats_key_spamba_controls",  .type = CONFIG_TYPE_BIND, .uintValue = CheatsControls.SpambaControls},
    #ifdef DISCORDRPC
    {.name = "discordrpc_enable",    .type = CONFIG_TYPE_BOOL, .boolValue = &configDiscordRPC},
    #endif 
    #ifdef RAPI_RT64
    {.name = "rt64_target_fps",                .type = CONFIG_TYPE_UINT, .uintValue = &configRT64TargetFPS},
    {.name = "rt64_res_scale",                 .type = CONFIG_TYPE_UINT, .uintValue = &configRT64ResScale},
    {.name = "rt64_max_lights",                .type = CONFIG_TYPE_UINT, .uintValue = &configRT64MaxLights},
    {.name = "rt64_sphere_lights",             .type = CONFIG_TYPE_BOOL, .boolValue = &configRT64SphereLights},
    {.name = "rt64_gi",                        .type = CONFIG_TYPE_BOOL, .boolValue = &configRT64GI},
    {.name = "rt64_upscaler",                  .type = CONFIG_TYPE_UINT, .uintValue = &configRT64Upscaler},
    {.name = "rt64_upscaler_mode_common",      .type = CONFIG_TYPE_UINT, .uintValue = &configRT64UpscalerMode},
    {.name = "rt64_upscaler_sharpness",        .type = CONFIG_TYPE_UINT, .uintValue = &configRT64UpscalerSharpness},
    {.name = "rt64_denoiser",                  .type = CONFIG_TYPE_BOOL, .boolValue = &configRT64Denoiser},
    {.name = "rt64_static_mesh_cache",         .type = CONFIG_TYPE_BOOL, .boolValue = &configRT64StaticMeshCache},
    {.name = "rt64_motion_blur_strength",      .type = CONFIG_TYPE_UINT, .uintValue = &configRT64MotionBlurStrength},
    #endif
};

// Reads an entire line from a file (excluding the newline character) and returns an allocated string
// Returns NULL if no lines could be read from the file
static char *read_file_line(fs_file_t *file) {
    char *buffer;
    size_t bufferSize = 8;
    size_t offset = 0; // offset in buffer to write

    buffer = malloc(bufferSize);
    while (1) {
        // Read a line from the file
        if (fs_readline(file, buffer + offset, bufferSize - offset) == NULL) {
            free(buffer);
            return NULL; // Nothing could be read.
        }
        offset = strlen(buffer);
        assert(offset > 0);

        // If a newline was found, remove the trailing newline and exit
        if (buffer[offset - 1] == '\n') {
            buffer[offset - 1] = '\0';
            break;
        }

        if (fs_eof(file)) // EOF was reached
            break;

        // If no newline or EOF was reached, then the whole line wasn't read.
        bufferSize *= 2; // Increase buffer size
        buffer = realloc(buffer, bufferSize);
        assert(buffer != NULL);
    }

    return buffer;
}

// Returns the position of the first non-whitespace character
static char *skip_whitespace(char *str) {
    while (isspace(*str))
        str++;
    return str;
}

// NULL-terminates the current whitespace-delimited word, and returns a pointer to the next word
static char *word_split(char *str) {
    // Precondition: str must not point to whitespace
    assert(!isspace(*str));

    // Find either the next whitespace char or end of string
    while (!isspace(*str) && *str != '\0')
        str++;
    if (*str == '\0') // End of string
        return str;

    // Terminate current word
    *(str++) = '\0';

    // Skip whitespace to next word
    return skip_whitespace(str);
}

// Splits a string into words, and stores the words into the 'tokens' array
// 'maxTokens' is the length of the 'tokens' array
// Returns the number of tokens parsed
static unsigned int tokenize_string(char *str, int maxTokens, char **tokens) {
    int count = 0;

    str = skip_whitespace(str);
    while (str[0] != '\0' && count < maxTokens) {
        tokens[count] = str;
        str = word_split(str);
        count++;
    }
    return count;
}

// Gets the config file path and caches it
const char *configfile_name(void) {
    return (gCLIOpts.ConfigFile[0]) ? gCLIOpts.ConfigFile : CONFIGFILE_DEFAULT;
}

// Loads the config file specified by 'filename'
void configfile_load(const char *filename) {
    fs_file_t *file;
    char *line;

    printf("Loading configuration from '%s'\n", filename);

    file = fs_open(filename);
    if (file == NULL) {
        // Create a new config file and save defaults
        printf("Config file '%s' not found. Creating it.\n", filename);
        configfile_save(filename);
        return;
    }

    // Go through each line in the file
    while ((line = read_file_line(file)) != NULL) {
        char *p = line;
        char *tokens[1 + MAX_BINDS];
        int numTokens;

        while (isspace(*p))
            p++;

        if (!*p || *p == '#') // comment or empty line
            continue;

        numTokens = tokenize_string(p, sizeof(tokens) / sizeof(tokens[0]), tokens);
        if (numTokens != 0) {
            if (numTokens >= 2) {
                const struct ConfigOption *option = NULL;

                for (unsigned int i = 0; i < ARRAY_LEN(options); i++) {
                    if (strcmp(tokens[0], options[i].name) == 0) {
                        option = &options[i];
                        break;
                    }
                }
                if (option == NULL)
                    printf("unknown option '%s'\n", tokens[0]);
                else {
                    switch (option->type) {
                        case CONFIG_TYPE_BOOL:
                            if (strcmp(tokens[1], "true") == 0)
                                *option->boolValue = true;
                            else
                                *option->boolValue = false;
                            break;
                        case CONFIG_TYPE_UINT:
                            sscanf(tokens[1], "%u", option->uintValue);
                            break;
                        case CONFIG_TYPE_BIND:
                            for (int i = 0; i < MAX_BINDS && i < numTokens - 1; ++i)
                                sscanf(tokens[i + 1], "%x", option->uintValue + i);
                            break;
                        case CONFIG_TYPE_FLOAT:
                            sscanf(tokens[1], "%f", option->floatValue);
                            break;
                        default:
                            assert(0); // bad type
                    }
                    printf("option: '%s', value:", tokens[0]);
                    for (int i = 1; i < numTokens; ++i) printf(" '%s'", tokens[i]);
                    printf("\n");
                }
            } else
                puts("error: expected value");
        }
        free(line);
    }

    fs_close(file);
}

// Writes the config file to 'filename'
void configfile_save(const char *filename) {
    FILE *file;

    printf("Saving configuration to '%s'\n", filename);

    file = fopen(fs_get_write_path(filename), "w");
    if (file == NULL) {
        // error
        return;
    }

    for (unsigned int i = 0; i < ARRAY_LEN(options); i++) {
        const struct ConfigOption *option = &options[i];

        switch (option->type) {
            case CONFIG_TYPE_BOOL:
                fprintf(file, "%s %s\n", option->name, *option->boolValue ? "true" : "false");
                break;
            case CONFIG_TYPE_UINT:
                fprintf(file, "%s %u\n", option->name, *option->uintValue);
                break;
            case CONFIG_TYPE_FLOAT:
                fprintf(file, "%s %f\n", option->name, *option->floatValue);
                break;
            case CONFIG_TYPE_BIND:
                fprintf(file, "%s ", option->name);
                for (int i = 0; i < MAX_BINDS; ++i)
                    fprintf(file, "%04x ", option->uintValue[i]);
                fprintf(file, "\n");
                break;
            default:
                assert(0); // unknown type
        }
    }

    fclose(file);
}