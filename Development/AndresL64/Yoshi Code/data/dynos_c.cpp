#include "dynos.cpp.h"
extern "C" {

//
// Options menu
//

s32 dynos_opt_get_value(const char *name) {
    return DynOS_Opt_GetValue(name);
}

void dynos_opt_set_value(const char *name, s32 value) {
    return DynOS_Opt_SetValue(name, value);
}

void dynos_opt_add_action(const char *funcname, bool (*funcptr)(const char *), bool overwrite) {
    return DynOS_Opt_AddAction(funcname, funcptr, overwrite);
}

//
// Update
//

void *dynos_update_cmd(void *cmd) {
    return DynOS_UpdateCmd(cmd);
}

void dynos_update_gfx() {
    return DynOS_UpdateGfx();
}

void dynos_update_opt(void *pad) {
    return DynOS_UpdateOpt(pad);
}

//
// Gfx
//

s32 dynos_gfx_import_texture(void **output, void *ptr, s32 tile, void *grapi, void **hashmap, void *pool, s32 *poolpos, s32 poolsize) {
    return DynOS_Gfx_ImportTexture(output, ptr, tile, grapi, hashmap, pool, (u32 *) poolpos, (u32) poolsize);
}

void dynos_gfx_swap_animations(void *ptr) {
    return DynOS_Gfx_SwapAnimations(ptr);
}

//
// Musics
//


bool dynos_music_load_presets_from_dynos_folder(const char *filename, const char *folder) {
    char filepath[256];
    char wavpath[256];
    snprintf(filepath, 256, "%s/%s/%s", DYNOS_EXE_FOLDER, DYNOS_AUDIO_FOLDER, filename);
    snprintf(wavpath, 256, "%s/%s/%s", DYNOS_EXE_FOLDER, DYNOS_AUDIO_FOLDER, folder);
    return DynOS_Music_LoadPresets(filepath, wavpath);
}

void dynos_music_play(const char *name) {
    return DynOS_Music_Play(name);
}

void dynos_music_multi_play(const char *name) {
    return DynOS_Music_Multi_Play(name);
}

void dynos_music_stop() {
    return DynOS_Music_Stop();
}

void dynos_music_pause() {
    return DynOS_Music_Pause();
}

void dynos_music_resume() {
    return DynOS_Music_Resume();
}

bool dynos_music_is_playing(const char *name) {
    return DynOS_Music_IsPlaying(name);
}

//
// Sounds
//

bool dynos_sound_load_presets_from_dynos_folder(const char *filename, const char *folder) {
    char filepath[256];
    char wavpath[256];
    snprintf(filepath, 256, "%s/%s/%s", DYNOS_EXE_FOLDER, DYNOS_AUDIO_FOLDER, filename);
    snprintf(wavpath, 256, "%s/%s/%s", DYNOS_EXE_FOLDER, DYNOS_AUDIO_FOLDER, folder);
    return DynOS_Sound_LoadPresets(filepath, wavpath);
}

void dynos_sound_play(const char *name, f32 *pos) {
    return DynOS_Sound_Play(name, pos);
}

void dynos_sound_stop(u8 bank) {
    return DynOS_Sound_Stop(bank);
}

bool dynos_sound_is_playing(const char *name) {
    return DynOS_Sound_IsPlaying(name);
}

//
// Jingles
//

bool dynos_jingle_load_presets_from_dynos_folder(const char *filename, const char *folder) {
    char filepath[256];
    char wavpath[256];
    snprintf(filepath, 256, "%s/%s/%s", DYNOS_EXE_FOLDER, DYNOS_AUDIO_FOLDER, filename);
    snprintf(wavpath, 256, "%s/%s/%s", DYNOS_EXE_FOLDER, DYNOS_AUDIO_FOLDER, folder);
    return DynOS_Jingle_LoadPresets(filepath, wavpath);
}

void dynos_jingle_play(const char *name) {
    return DynOS_Jingle_Play(name);
}

void dynos_jingle_stop() {
    return DynOS_Jingle_Stop();
}

void dynos_jingle_pause() {
    return DynOS_Jingle_Pause();
}

void dynos_jingle_resume() {
    return DynOS_Jingle_Resume();
}

bool dynos_jingle_is_playing(const char *name) {
    return DynOS_Jingle_IsPlaying(name);
}

//
// Warps
//

bool dynos_warp_to_level(s32 level, s32 area, s32 act) {
    return DynOS_Warp_ToLevel(level, area, act);
}

bool dynos_warp_restart_level() {
    return DynOS_Warp_RestartLevel();
}

bool dynos_warp_exit_level(s32 delay) {
    return DynOS_Warp_ExitLevel(delay);
}

bool dynos_warp_to_castle(s32 level) {
    return DynOS_Warp_ToCastle(level);
}

bool dynos_warp_return_to_main_menu() {
    return DynOS_Warp_ReturnToMainMenu();
}

}
