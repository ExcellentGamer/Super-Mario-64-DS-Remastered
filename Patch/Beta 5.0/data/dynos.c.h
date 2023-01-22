#ifndef DYNOS_C_H
#define DYNOS_C_H
#ifndef __cplusplus

#include "dynos.h"

//
// Options menu
//

int dynos_opt_get_value(const char *name);
void dynos_opt_set_value(const char *name, int value);
void dynos_opt_add_action(const char *funcname, bool (*funcptr)(const char *), bool overwrite);
void dynos_opt_enable_model_pack_by_name(const char *packname, bool enable);

//
// Update
//

void *dynos_update_cmd(void *cmd);
void dynos_update_gfx();
void dynos_update_opt(void *pad);

//
// Gfx
//

int dynos_gfx_import_texture(void **output, void *ptr, int tile, void *grapi, void **hashmap, void *pool, int *poolpos, int poolsize);
void dynos_gfx_swap_animations(void *ptr);
void *dynos_geo_get_graph_node(const void *geoLayout, bool keepInMemory);

//
// Musics
//

void dynos_audio_init();
bool dynos_music_load_presets_from_dynos_folder(const char *filename, const char *folder);
void dynos_music_play(const char *name, float volume_begin, float volume_end, int delay_time);
void dynos_music_multi_play(const char *name, float volume_begin, float volume_end, int delay_time);
void dynos_music_stop();
void dynos_music_pause();
void dynos_music_resume();
void dynos_music_fade(bool end, float volume_begin, float volume_end, int delay_time);
bool dynos_music_is_playing(const char *name);

//
// Sounds
//

bool dynos_sound_load_presets_from_dynos_folder(const char *filename, const char *folder);
void dynos_sound_play(const char *name, float *pos);
void dynos_sound_stop(unsigned char bank);
bool dynos_sound_is_playing(const char *name);

//
// Jingles
//

bool dynos_jingle_load_presets_from_dynos_folder(const char *filename, const char *folder);
void dynos_jingle_play(const char *name, float volume_begin, float volume_end, int delay_time);
void dynos_jingle_stop();
void dynos_jingle_pause();
void dynos_jingle_resume();
void dynos_jingle_fade(bool end, float volume_begin, float volume_end, int delay_time);
bool dynos_jingle_is_playing(const char *name);

#endif
#endif
