#ifndef DYNOS_C_H
#define DYNOS_C_H
#ifndef __cplusplus

#include "dynos.h"

// The action signature is "bool (*) (const char *)"
// The input is the button internal name (not label)
// The output is the result of the action
#define DYNOS_DEFINE_ACTION(func) \
DYNOS_AT_STARTUP static void dynos_opt_add_action_##func() { \
    dynos_opt_add_action(#func, func, false); \
}

//
// Options menu
//

s32 dynos_opt_get_value(const char *name);
void dynos_opt_set_value(const char *name, s32 value);
void dynos_opt_add_action(const char *funcname, bool (*funcptr)(const char *), bool overwrite);
//
// Update
//

void *dynos_update_cmd(void *cmd);
void dynos_update_gfx();
void dynos_update_opt(void *pad);

//
// Gfx
//

s32 dynos_gfx_import_texture(void **output, void *ptr, s32 tile, void *grapi, void **hashmap, void *pool, s32 *poolpos, s32 poolsize);
void dynos_gfx_swap_animations(void *ptr);

//
// Musics
//

bool dynos_music_load_presets_from_dynos_folder(const char *filename, const char *folder);
void dynos_music_play(const char *name);
void dynos_music_multi_play(const char *name);
void dynos_music_stop();
void dynos_music_pause();
void dynos_music_resume();
bool dynos_music_is_playing(const char *name);

//
// Sounds
//

bool dynos_sound_load_presets_from_dynos_folder(const char *filename, const char *folder);
void dynos_sound_play(const char *name, f32 *pos);
void dynos_sound_stop(u8 bank);
bool dynos_sound_is_playing(const char *name);

//
// Jingles
//

bool dynos_jingle_load_presets_from_dynos_folder(const char *filename, const char *folder);
void dynos_jingle_play(const char *name);
void dynos_jingle_stop();
void dynos_jingle_pause();
void dynos_jingle_resume();
bool dynos_jingle_is_playing(const char *name);

//
// Warps
//

bool dynos_warp_to_level(s32 level, s32 area, s32 act);
bool dynos_warp_restart_level();
bool dynos_warp_exit_level(s32 delay);
bool dynos_warp_to_castle(s32 level);
bool dynos_warp_return_to_main_menu();

//
// Sanity checks
//

bool dynos_sanity_check_geo(s16 graphNodeType);
bool dynos_sanity_check_seq(u8 loBits);

#endif
#endif
