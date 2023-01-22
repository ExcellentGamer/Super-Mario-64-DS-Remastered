#include "data/r96/r96_c_includes.h"
#include "data/r96/system/r96_system.h"

extern s16 gMenuMode;

float softenVolume = 1.0f;
float softenJingleVolume = 1.0f;

s32 gCurrIndex;

u32 onShell = 0;
bool fadeIn = 0;

const char* sR96CurrentCapMusic = NULL;

// Infinite stairs

void r96_play_infinite_stairs_music() {
    /* Infinite stairs? */
    if (gCurrLevelNum == LEVEL_CASTLE && gCurrAreaIndex == 2 && gMarioState->numStars < 70) {
        if (gMarioState->floor != NULL && gMarioState->floor->room == 6) {
            if (gMarioState->pos[2] < 2540.0f) {
                r96_play_jingle(R96_EVENT_ENDLESS_STAIRS, 0.1, 1.0, 1500);
                r96_music_fade(0, -1, 0.0, 1500, 0); // out
            } else {
                dynos_jingle_fade(1, -1, 1.0, 1500);
                r96_music_fade(0, -1, 1.0, 1500, 0);
            }
        }
    }
}

// Action Functions

void r96_play_action_sound(struct MarioState *m, s32 actionSound) {
    if (actionSound == SOUND_ACTION_TERRAIN_JUMP) {
        play_mario_action_sound(
                m, (m->flags & MARIO_METAL_CAP) ? (s32)SOUND_ACTION_METAL_JUMP
                                                : (s32)SOUND_ACTION_TERRAIN_JUMP, 1);
    } else {
        play_sound_if_no_flag(m, actionSound, MARIO_ACTION_SOUND_PLAYED);
    }
}

// Character Functions

void r96_play_character_sound_if_no_flag(struct MarioState *m, const char* R96_MARIO, const char* R96_LUIGI, const char* R96_WARIO, const char* R96_WALUIGI, const char* R96_YOSHI_DS, u32 flags) {
    if ((m->flags & flags) == 0) {
        if (isLuigi()) {
            dynos_sound_play(R96_LUIGI, m->marioObj->header.gfx.cameraToObject);
        } else if (isWario()) {
            dynos_sound_play(R96_WARIO, m->marioObj->header.gfx.cameraToObject);
        } else if (isWaluigi()) {
            dynos_sound_play(R96_WALUIGI, m->marioObj->header.gfx.cameraToObject);
        } else if (isYoshi()) {
            dynos_sound_play(R96_YOSHI_DS, m->marioObj->header.gfx.cameraToObject);
        } else {
            dynos_sound_play(R96_MARIO, m->marioObj->header.gfx.cameraToObject);
        }
        m->flags |= flags;
    }
}

void r96_play_character_sound(struct MarioState *m, const char* R96_MARIO, const char* R96_LUIGI, const char* R96_WARIO, const char* R96_WALUIGI, const char* R96_YOSHI_DS) {
    if (isLuigi()) {
        dynos_sound_play(R96_LUIGI, m->marioObj->header.gfx.cameraToObject);
    } else if (isWario()) {
        dynos_sound_play(R96_WARIO, m->marioObj->header.gfx.cameraToObject);
    } else if (isWaluigi()) {
        dynos_sound_play(R96_WALUIGI, m->marioObj->header.gfx.cameraToObject);
    } else if (isYoshi()) {
        dynos_sound_play(R96_YOSHI_DS, m->marioObj->header.gfx.cameraToObject);
    } else {
        dynos_sound_play(R96_MARIO, m->marioObj->header.gfx.cameraToObject);
    }
}

void r96_play_character_sound_no_arg(const char* R96_MARIO, const char* R96_LUIGI, const char* R96_WARIO, const char* R96_WALUIGI, const char* R96_YOSHI_DS) {
    if (isLuigi()) {
        dynos_sound_play(R96_LUIGI, gDefaultSoundArgs);
    } else if (isWario()) {
        dynos_sound_play(R96_WARIO, gDefaultSoundArgs);
    } else if (isWaluigi()) {
        dynos_sound_play(R96_WALUIGI, gDefaultSoundArgs);
    } else if (isYoshi()) {
        dynos_sound_play(R96_YOSHI_DS, gDefaultSoundArgs);
    } else {
        dynos_sound_play(R96_MARIO, gDefaultSoundArgs);
    }
}

void r96_play_far_fall_sound(struct MarioState *m) {
    u32 action = m->action;
    if (!(action & ACT_FLAG_INVULNERABLE) && action != ACT_TWIRLING && action != ACT_FLYING
        && !(m->flags & MARIO_UNKNOWN_18)) {
        if (m->peakHeight - m->pos[1] > 1150.0f) {
            r96_play_character_sound(m, R96_MARIO_FALLING, R96_LUIGI_FALLING, R96_WARIO_FALLING, R96_WALUIGI_FALLING, R96_YOSHI_DS_FALLING);
            m->flags |= MARIO_UNKNOWN_18;
        }
    }
}

void r96_play_knockback_sound(struct MarioState *m) {
    if (m->actionArg == 0 && (m->forwardVel <= -28.0f || m->forwardVel >= 28.0f))
        r96_play_character_sound_if_no_flag(m, R96_MARIO_DOH, R96_LUIGI_DOH, R96_WARIO_DOH, R96_WALUIGI_DOH, R96_YOSHI_DS_DOH, MARIO_MARIO_SOUND_PLAYED);
    else
        r96_play_character_sound_if_no_flag(m, R96_MARIO_GRUNT, R96_LUIGI_GRUNT, R96_WARIO_GRUNT, R96_WALUIGI_GRUNT, R96_YOSHI_DS_GRUNT, MARIO_MARIO_SOUND_PLAYED);
}

void r96_play_character_charge_sound(struct MarioState *m) {
    if (!(m->flags & MARIO_MARIO_SOUND_PLAYED)) {
        switch (random_u16() % 3) {
            case 0: r96_play_character_sound(m, R96_MARIO_HELLO, R96_LUIGI_HELLO, R96_WARIO_HELLO, R96_WALUIGI_HELLO, R96_YOSHI_DS_HELLO); break;
            case 1: r96_play_character_sound(m, R96_MARIO_THROW, R96_LUIGI_THROW, R96_WARIO_THROW, R96_WALUIGI_THROW, R96_YOSHI_DS_THROW); break;
            case 2: r96_play_character_sound(m, R96_MARIO_WAHA, R96_LUIGI_WAHA, R96_WARIO_WAHA, R96_WALUIGI_WAHA, R96_YOSHI_DS_WAHA); break;
        }
        m->flags |= MARIO_MARIO_SOUND_PLAYED;
    }
}

void r96_play_character_jump_sound(struct MarioState *m) {
    if (!(m->flags & MARIO_MARIO_SOUND_PLAYED)) {
        if (m->action == ACT_TRIPLE_JUMP || m->action == ACT_WARIO_TRIPLE_JUMP) {
            switch (random_u16() % 3) {
                case 0: r96_play_character_sound(m, R96_MARIO_WAHA, R96_LUIGI_WAHA, R96_WARIO_WAHA, R96_WALUIGI_WAHA, R96_YOSHI_DS_WAHA); break;
                case 1: r96_play_character_sound(m, R96_MARIO_YIPPEE, R96_LUIGI_YIPPEE, R96_WARIO_YIPPEE, R96_WALUIGI_YIPPEE, R96_YOSHI_DS_YIPPEE); break;
                case 2: r96_play_character_sound(m, R96_MARIO_YAHOO, R96_LUIGI_YAHOO, R96_WARIO_YAHOO, R96_WALUIGI_YAHOO, R96_YOSHI_DS_YAHOO); break;
            }
        } else {
            switch (random_u16() % 3) {
                case 0: r96_play_character_sound(m, R96_MARIO_YAH, R96_LUIGI_YAH, R96_WARIO_YAH, R96_WALUIGI_YAH, R96_YOSHI_DS_YAH); break;
                case 1: r96_play_character_sound(m, R96_MARIO_WAH, R96_LUIGI_WAH, R96_WARIO_WAH, R96_WALUIGI_WAH, R96_YOSHI_DS_WAH); break;
                case 2: r96_play_character_sound(m, R96_MARIO_HOO, R96_LUIGI_HOO, R96_WARIO_HOO, R96_WALUIGI_HOO, R96_YOSHI_DS_HOO); break;
            }
        }
        m->flags |= MARIO_MARIO_SOUND_PLAYED;
    }
}

void r96_play_character_flying_sound(struct MarioState *m) {
    switch (random_u16() % 3) {
        case 0: r96_play_character_sound(m, R96_MARIO_WAHA, R96_LUIGI_WAHA, R96_WARIO_WAHA, R96_WALUIGI_WAHA, R96_YOSHI_DS_WAHA); break;
        case 1: r96_play_character_sound(m, R96_MARIO_YIPPEE, R96_LUIGI_YIPPEE, R96_WARIO_YIPPEE, R96_WALUIGI_YIPPEE, R96_YOSHI_DS_YIPPEE); break;
        case 2: r96_play_character_sound(m, R96_MARIO_YAHOO, R96_LUIGI_YAHOO, R96_WARIO_YAHOO, R96_WALUIGI_YAHOO, R96_YOSHI_DS_YAHOO); break;
    }
}

// Shell Functions 

void r96_play_shell_music() {
    onShell = 1;
    dynos_music_stop();
    dynos_music_play(R96_EVENT_SHELL, 0.1, 1.0, 2500);
}

void r96_stop_shell_music() {
    onShell = 0;
    if (dynos_music_is_playing(R96_EVENT_SHELL))
        dynos_music_stop();
}

// Cap Functions

void r96_play_cap_music(const char* R96_CAP_MUSIC) {
    if (R96_CAP_MUSIC != NULL) {
        dynos_music_stop();
        dynos_music_play(R96_CAP_MUSIC, 1.0, 1.0, 2500);
    }
    sR96CurrentCapMusic = R96_CAP_MUSIC;
}

void r96_fadeout_cap_music() {
    if (sR96CurrentCapMusic != NULL) {
        r96_music_fade(1, -1, 0.0, 2500, 0);
    }
}

void r96_stop_cap_music() {
    if (sR96CurrentCapMusic != NULL &&
        !dynos_music_is_playing(R96_EVENT_BOSS_INTRO) &&
        !dynos_music_is_playing(R96_EVENT_BOSS_THEME)) {
        dynos_music_stop();
    }
    sR96CurrentCapMusic = NULL;
}

void r96_cap_music_boss_fix() {
    // Scenario where boss music is done but mario has power up
    if (gMarioState->flags & MARIO_METAL_CAP) r96_play_cap_music(R96_EVENT_CAP_METAL);
    if (gMarioState->flags & MARIO_VANISH_CAP) r96_play_cap_music(R96_EVENT_CAP_VANISH);
    if (gMarioState->flags & MARIO_WING_CAP) r96_play_cap_music(R96_EVENT_CAP_WING);
}

// Jingle Functions

void r96_play_menu_jingle(const char* R96_JINGLE, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    dynos_music_stop();
    if (!dynos_jingle_is_playing(R96_JINGLE)) {
        dynos_jingle_stop();
        dynos_jingle_play(R96_JINGLE, aVolumeBegin, aVolumeEnd, aDelaytime);
    }
}

void r96_play_jingle(const char* R96_JINGLE, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    if (!dynos_jingle_is_playing(R96_JINGLE)) {
        dynos_jingle_stop();
        dynos_jingle_play(R96_JINGLE, aVolumeBegin, aVolumeEnd, aDelaytime);
    }
}

void r96_play_collect_jingle(const char* R96_JINGLE, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    if (!dynos_jingle_is_playing(R96_JINGLE)) {
        dynos_jingle_stop();
        dynos_jingle_play(R96_JINGLE, aVolumeBegin, aVolumeEnd, aDelaytime);
    }
}

void r96_stop_jingle() {
    dynos_jingle_stop();
}

void r96_jingle_fade(bool aEnd, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    dynos_jingle_fade(aEnd, aVolumeBegin, aVolumeEnd, aDelaytime);
}

// Music Functions

void r96_play_music(const char* R96_MUSIC, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    if (!dynos_music_is_playing(R96_MUSIC)) {
        dynos_music_stop();
        dynos_music_play(R96_MUSIC, aVolumeBegin, aVolumeEnd, aDelaytime);
    }
}

void r96_play_multi_music(const char* R96_MUSIC, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    if (!dynos_music_is_playing(R96_MUSIC)) {
        dynos_music_multi_play(R96_MUSIC, aVolumeBegin, aVolumeEnd, aDelaytime);
    }
}

void r96_stop_music() {
    dynos_music_stop();
}

void r96_music_fade(bool aEnd, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime, bool fadein) {
    dynos_music_fade(aEnd, aVolumeBegin, aVolumeEnd, aDelaytime);
    fadeIn = fadein;
}

void r96_level_music_update() {

// When the fanfare is playing and the pause window opens
    if (gMenuMode != -1) {
        softenVolume = 0.20f;
    } 

    else {
        softenVolume = 1.0f;
    }

    s32 jukebox = cheats_jukebox(gMarioState);
    if (jukebox != -1) {
        if (jukebox >= 57) {
            const char *jingle = *CheatJukeboxMusics[jukebox];
            dynos_music_stop();
            if (!dynos_jingle_is_playing(jingle)) {
                dynos_jingle_stop();
                dynos_jingle_play(jingle, 0.1, 1.0, 1500);
            }
        } else {
            const char *music = *CheatJukeboxMusics[jukebox];
            dynos_jingle_stop();
            if (!dynos_music_is_playing(music)) {
                dynos_music_stop();
                dynos_music_play(music, 0.1, 1.0, 2500);
            }
        }
        return;
    }

    const char *music = r96_get_intended_level_music();

    if (dynos_jingle_is_playing(R96_MENU_FILE_SELECT) ||
        dynos_jingle_is_playing(R96_EVENT_STAR_SELECT)) {
        r96_jingle_fade(1, -1, 0.0, 2000);
    }

    if (!dynos_jingle_is_playing(R96_EVENT_CREDITS) &&
        !dynos_jingle_is_playing(R96_EVENT_TITLE_SCREEN) &&
        !dynos_jingle_is_playing(R96_EVENT_GAME_OVER) &&
        !dynos_jingle_is_playing(R96_EVENT_PEACH_ENDING) &&
        !dynos_jingle_is_playing(R96_EVENT_PEACH_MESSAGE) &&
        !dynos_jingle_is_playing(R96_EVENT_INTRO)) {
        r96_play_infinite_stairs_music();

        // Keeps event music if meant to be playing
        if (music == NULL) {
            r96_music_fade(1, -1, 0.0, 1, 0);
        }
        if (music != NULL) {
            if (dynos_jingle_is_playing(R96_EVENT_STAR_COLLECT) ||
                dynos_jingle_is_playing(R96_EVENT_KEY_COLLECT)) {
                r96_music_fade(1, -1, 0.0, 1, 0);
            }
            else if (!dynos_music_is_playing(music) &&
                !dynos_music_is_playing(R96_EVENT_BOSS_INTRO) &&
                !dynos_music_is_playing(R96_EVENT_BOSS_THEME) &&
                !dynos_music_is_playing(R96_EVENT_CAP_METAL) &&
                !dynos_music_is_playing(R96_EVENT_RACE) &&
                !dynos_music_is_playing(R96_EVENT_GOT_MILK) &&
                !dynos_jingle_is_playing(R96_EVENT_VICTORY) &&
                !dynos_music_is_playing(R96_EVENT_CAP_VANISH) &&
                !dynos_music_is_playing(R96_EVENT_CAP_WING) &&
                !dynos_music_is_playing(R96_EVENT_SHELL)) {
                if (gCurrLevelNum == LEVEL_JRB ||
                    gCurrLevelNum == LEVEL_DDD ||
                    gCurrLevelNum == LEVEL_WDW ||
                    gCurrLevelNum == LEVEL_HMC ||
                    gCurrLevelNum == LEVEL_BBH)
                    r96_play_multi_music(music, 1.0, 1.0, 2500);
                else if (gCurrLevelNum == LEVEL_CASTLE)
                    r96_play_multi_music(music, 1.0, 1.0, 1);
                else
                    r96_play_music(music, 1.0, 1.0, 2500);
            }
            // Special Jingle cases
            else if (!dynos_jingle_is_playing(R96_EVENT_MERRY_GO_ROUND) &&
                !dynos_jingle_is_playing(R96_EVENT_STAR_APPEAR)  &&
                !dynos_jingle_is_playing(R96_EVENT_TOAD_MESSAGE) &&
                !dynos_jingle_is_playing(R96_EVENT_RACE_FANFARE) &&
                !dynos_jingle_is_playing(R96_EVENT_SOLVE_PUZZLE) &&
                !dynos_jingle_is_playing(R96_EVENT_KOOPA_MESSAGE) &&
                !dynos_jingle_is_playing(R96_EVENT_ENDLESS_STAIRS) &&
                !dynos_jingle_is_playing(R96_EVENT_PIRANHA_PLANT) &&
                fadeIn) {
                r96_music_fade(0, -1, 1.0, 1500, 0);
                fadeIn = 0;
            }
        }
    }
}

const char *r96_get_intended_level_music() { 
    gCurrIndex = gCurrentArea->index;
    s32 gCurrAreaIndex = gCurrentArea->index;
    // Bowser Time!
    if (Cheats.EnableCheats && Cheats.ChaosBowserTime) {
        return R96_LEVEL_BOWSER_3;
    }

    // Big Boo's Haunt
    if (gCurrLevelNum == LEVEL_BBH) {
        if (gMarioCurrentRoom == BBH_OUTSIDE_ROOM ||
            gMarioCurrentRoom == BBH_NEAR_MERRY_GO_ROUND_ROOM) 
            gCurrIndex = 2;
    }

    // Inside Castle
    if (gCurrLevelNum == LEVEL_CASTLE) {
        // Stops wing cap from playing inside the castle
        if (dynos_music_is_playing(R96_EVENT_CAP_WING) ||
            dynos_music_is_playing(R96_LEVEL_CASTLE_GROUNDS) ||
            dynos_music_is_playing(R96_LEVEL_CASTLE_COURTYARD))
            r96_music_fade(1, -1, 0.0, 1, 0);
        if (gShouldNotPlayCastleMusic) {
            return NULL;
        }
    }

    // Hazy Maze Cave
    if (gCurrLevelNum == LEVEL_HMC) {
        if ((((s16) gMarioStates[0].pos[0]) <= 0) && (((s16) gMarioStates[0].pos[1]) <= -203))
            gCurrIndex = 2;
        else if ((((s16) gMarioStates[0].pos[0]) > 0) && (((s16) gMarioStates[0].pos[1]) <= -2400))
            gCurrIndex = 2;
        else
            gCurrIndex = 1;
    }

    // Shifting Sand Land
    if (gCurrLevelNum == LEVEL_SSL) {
        if (gCurrAreaIndex == 2) {
            if (!dynos_music_is_playing(R96_LEVEL_SSL_PYRAMID)) {
                r96_stop_cap_music();
            }
        }
    }

    // Bowser in the Sky
    if (gCurrLevelNum == LEVEL_BITS) {
        r96_stop_jingle();
    }

    // Castle Grounds
    if (gCurrLevelNum == LEVEL_CASTLE_GROUNDS) {
        if (gCurrAreaIndex == 1) {
            if (dynos_jingle_is_playing(R96_EVENT_INTRO) ||
                dynos_jingle_is_playing(R96_EVENT_PEACH_MESSAGE) ||
                dynos_jingle_is_playing(R96_EVENT_PEACH_ENDING)  ||
                dynos_jingle_is_playing(R96_EVENT_CREDITS)) {
                r96_music_fade(1, -1, 0.0, 1, 0);
            }
        }
    }

    // Jolly Roger Bay
    if (gCurrLevelNum == LEVEL_JRB) {
        if ((((s16) gMarioStates[0].pos[1]) > -3100) && (((s16) gMarioStates[0].pos[2]) <= -900))
            gCurrIndex = 3;
        else if ((((s16) gMarioStates[0].pos[1]) > 945) && (((s16) gMarioStates[0].pos[0]) <= -5260))
            gCurrIndex = 1;
        else if ((((s16) gMarioStates[0].pos[1]) > 1000))
            gCurrIndex = 1;
        else
            gCurrIndex = 2;
        if (gCurrAreaIndex == 2)
            gCurrIndex = 4;
    }

    // Dire Dire Docks
    if (gCurrLevelNum == LEVEL_DDD) {
        if (gCurrAreaIndex == 1) {
            if ((((s16) gMarioStates[0].pos[0]) <= -800) || ((((s16) gMarioStates[0].pos[0]) <= 470) && (((s16) gMarioStates[0].pos[1]) > -2000)))
                gCurrIndex = 1;
            else 
                gCurrIndex = 2;
        }
        if (gCurrAreaIndex == 2) {
            if ((((s16) gMarioStates[0].pos[1]) > 100))
                gCurrIndex = 3;
            else 
                gCurrIndex = 2;
        }
    }

    // Wet Dry World 
    if (gCurrLevelNum == LEVEL_WDW) {
        if (gCurrIndex == 2) {
            if (dynos_music_is_playing(R96_EVENT_GOT_MILK))
                r96_stop_music();
        }
    }

    return R96_EffectData[gCurrLevelNum][gCurrIndex].name;
}

