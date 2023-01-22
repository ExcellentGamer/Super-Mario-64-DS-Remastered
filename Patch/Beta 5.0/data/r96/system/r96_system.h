#ifndef R96_SYSTEM_H
#define R96_SYSTEM_H

#include "data/dynos.c.h"
#include "game/camera.h"
#include "include/types.h"

/* Character Swap */
void set_notification_status(s8 newState);
s8 get_notification_status();

s32 getCharacterType();
void setCharacterModel(s32 type);
f32 getCharacterMultiplier();
void triggerLuigiNotification();
//Todo: To be removed
s32 isYoshi();
s32 isLuigi();
s32 isWario();
s32 isWaluigi();

// Wario moves
s32 check_wario_pile_driver_jump_cancel(struct MarioState *m);
s32 check_wario_spin_light_idle_cancel(struct MarioState *m);
s32 check_wario_spin_heavy_idle_cancel(struct MarioState *m);
s32 act_wario_pile_driver(struct MarioState *m);
s32 act_wario_pile_driver_land(struct MarioState *m);
s32 act_wario_charge(struct MarioState *m);
s32 act_wario_triple_jump(struct MarioState *m);
s32 act_walking_wario_spin(struct MarioState *m);
s32 act_picking_up_enemies(struct MarioState *m);
s32 act_holding_enemies(struct MarioState *m);
s32 act_releasing_enemies(struct MarioState *m);

/* Audio */

extern float softenVolume;
extern float softenJingleVolume;

// Infinite stairs

void r96_play_infinite_stairs_music();

// Action Functions

void r96_play_action_sound(struct MarioState *m, s32 actionSound);

// Character Functions

void r96_play_character_sound_if_no_flag(struct MarioState *m, const char* R96_MARIO, const char* R96_LUIGI, const char* R96_WARIO, const char* R96_WALUIGI, const char* R96_YOSHI_DS, u32 flags);
void r96_play_character_sound(struct MarioState *m, const char* R96_MARIO, const char* R96_LUIGI, const char* R96_WARIO, const char* R96_WALUIGI, const char* R96_YOSHI_DS);
void r96_play_character_sound_no_arg(const char* R96_MARIO, const char* R96_LUIGI, const char* R96_WARIO, const char* R96_WALUIGI, const char* R96_YOSHI_DS);
void r96_play_far_fall_sound(struct MarioState *m);
void r96_play_knockback_sound(struct MarioState *m);
void r96_play_character_charge_sound(struct MarioState *m);
void r96_play_character_jump_sound(struct MarioState *m);
void r96_play_character_flying_sound(struct MarioState *m);

// Shell Functions

void r96_play_shell_music();
void r96_stop_shell_music();

// Cap Functions

void r96_play_cap_music(const char* R96_CAP_MUSIC);
void r96_fadeout_cap_music();
void r96_stop_cap_music();
void r96_cap_music_boss_fix();

// Jingle Functions

void r96_play_menu_jingle(const char* R96_JINGLE, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime);
void r96_play_jingle(const char* R96_JINGLE, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime);
void r96_play_collect_jingle(const char* R96_JINGLE, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime);
void r96_stop_jingle();
void r96_jingle_fade(bool aEnd, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime);

// Music Functions

void r96_play_music(const char* R96_MUSIC, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime);
void r96_play_multi_music(const char* R96_MUSIC, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime);
void r96_stop_music();
void r96_music_fade(bool aEnd, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime, bool fadein);

const char *r96_get_intended_level_music();
void r96_level_music_update();

extern void internal_resolution();

typedef struct {
    const char* name;
    f32 roomSize;
    f32 damping;
    f32 width;
    f32 wetVolume;
    f32 dryVolume;
    f32 mode;
} EffectData;

extern EffectData R96_EffectData[LEVEL_MAX+1][5];

extern void R96_Effect_Init();

extern s32 gCurrIndex;

extern int R96_SoundCount[LEVEL_MAX+1];
#endif // R96_SYSTEM_H
