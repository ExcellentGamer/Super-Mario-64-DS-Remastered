#include "mario_cheats.h"
#include "data/r96/r96_c_includes.h"
#include "text/text-loader.h"
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "levels/hmc/header.h"
#include "levels/ssl/header.h"
#include "geo_commands.h"
extern u64 sCapFlickerFrames;

//
// Cheats
//

static const s32 sModifierValues[] = { 1, 2, 3, 4, 5 };
static const f32 sSizeValues[] = { 1.f, 2.f, 3.f, 4.f, 0.f, 0.25f, 0.5f, 0.75f };

u32 gKeyPressed = VK_INVALID;

s32 cheats_update(struct MarioState *m) {
    gKeyPressed = controller_get_raw_key();
    return Cheats.EnableCheats;
}

s32 cheats_moon_jump(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.MoonJump && !Cheats.ChaosMode))) {
        if (gPlayer1Controller->buttonDown & L_TRIG) {
            m->vel[1] = 25.f;
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_moon_gravity(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.MoonGravity && !Cheats.ChaosMode))) {
        if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_AIRBORNE) {
            if (m->action == ACT_FREEFALL || m->action == ACT_LONG_JUMP) {
                m->vel[1] += 1.f;
            } else {
                m->vel[1] += 2.f;
            }
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_super_copter(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.SuperCopter && !Cheats.ChaosMode))) {
        if (gPlayer1Controller->buttonDown & A_BUTTON) {
            m->vel[1] = 30.f;
            set_mario_action(m, ACT_TWIRLING, 0);
            return TRUE;
        }
        
        // You can break free by starting a groud pound with Z
        if (m->action == ACT_TWIRLING && (gPlayer1Controller->buttonPressed & Z_TRIG)) {
            set_mario_action(m, ACT_GROUND_POUND, 0);
        }
    }
    return FALSE;
}

s32 cheats_debug_move(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.DebugMove && !Cheats.ChaosMode))) {
        set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
        Cheats.DebugMove = false;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_god_mode(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.GodMode && !Cheats.ChaosMode))) {
        m->health = 0x880;
        m->healCounter = 0;
        m->hurtCounter = 0;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_infinite_lives(struct MarioState *m) {
    // Always set infinite lives if Chaos mode is enabled
    if (Cheats.EnableCheats && (Cheats.InfiniteLives || Cheats.ChaosMode)) {
        m->numLives = 99;
    }
    return FALSE;
}

s32 cheats_responsive(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.Responsive && !Cheats.ChaosMode) || ((Cheats.ChaosControls >> 0) & 1))) {
        m->faceAngle[1] = m->intendedYaw;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_speed_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        if (!Cheats.ChaosMode) {
            return sModifierValues[Cheats.SpeedModifier];
        }
        return sModifierValues[Cheats.ChaosSpeedModifier];
    }
    return 1;
}

s32 cheats_jump_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        if (!Cheats.ChaosMode) {
            return sModifierValues[Cheats.JumpModifier];
        }
        return sModifierValues[Cheats.ChaosJumpModifier];
    }
    return 1;
}

s32 cheats_swim_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        if (!Cheats.ChaosMode) {
            return sModifierValues[Cheats.SwimModifier];
        }
        return sModifierValues[Cheats.ChaosSwimModifier];
    }
    return 1;
}

s32 cheats_size_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        f32 size = 1.f;
        if (!Cheats.ChaosMode) {
            size = sSizeValues[Cheats.SizeModifier];
        } else {
            size = sSizeValues[Cheats.ChaosSizeModifier];
        }
        s32 playAsIndex;
        if (Cheats.ChaosMode) {
            playAsIndex = Cheats.ChaosPlayAs;
        } else {
            playAsIndex = Cheats.PlayAs;
        }
        if (playAsIndex == 3 || playAsIndex == 5) {
            size *= 1.5f;
        }
        m->marioObj->header.gfx.scale[0] *= size;
        m->marioObj->header.gfx.scale[1] *= size;
        m->marioObj->header.gfx.scale[2] *= size;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_hurt_mario(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.HurtMario && !Cheats.ChaosMode))) {
        if ((gPlayer1Controller->buttonDown & L_TRIG) && (gPlayer1Controller->buttonPressed & A_BUTTON)) {
            switch (Cheats.HurtMario) {
                
                // Knockbacks
                case 1: {
                    spawn_object(m->marioObj, MODEL_EXPLOSION, bhvExplosion);
                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION | 0xFF00, m->marioObj->header.gfx.cameraToObject);
                    if (m->action & ACT_FLAG_AIR) {
                        drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_HARD_FORWARD_AIR_KB : ACT_HARD_BACKWARD_AIR_KB, 1);
                    } else if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
                        drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_FORWARD_WATER_KB : ACT_BACKWARD_WATER_KB, 1);
                    } else {
                        drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_HARD_FORWARD_GROUND_KB : ACT_HARD_BACKWARD_GROUND_KB, 1);
                    }
                } break;
                
                // Shocked
                case 2: {
                    if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
                        drop_and_set_mario_action(m, ACT_WATER_SHOCKED, 0);
                    } else {
                        u32 actionArg = (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) == 0;
                        drop_and_set_mario_action(m, ACT_SHOCKED, actionArg);
                    }
                } break;

                // Burnt
                case 3: {
                    if (!(m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER))) {
                        m->marioObj->oMarioBurnTimer = 0;
                        update_mario_sound_and_camera(m);
                        r96_play_character_sound(m, R96_MARIO_ON_FIRE, R96_LUIGI_ON_FIRE, R96_WARIO_ON_FIRE);
                        if ((m->action & ACT_FLAG_AIR) && m->vel[1] <= 0.f) {
                            drop_and_set_mario_action(m, ACT_BURNING_FALL, 1);
                        } else {
                            drop_and_set_mario_action(m, ACT_BURNING_JUMP, 1);
                        }
                    }
                } break;
                
                // Lava boost
                case 4: {
                    if (!(m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER))) {
                        drop_and_set_mario_action(m, ACT_LAVA_BOOST, 0);
                    }
                } break;
                
                // Squished
                case 5: {
                    drop_and_set_mario_action(m, ACT_SQUISHED, 0);
                    r96_play_character_sound(m, R96_MARIO_ATTACKED, R96_LUIGI_ATTACKED, R96_WARIO_ATTACKED);
                    vec3f_set(m->marioObj->header.gfx.scale, 1.8f, 0.05f, 1.8f);
                    m->particleFlags |= PARTICLE_MIST_CIRCLE;
                    m->squishTimer = 0xFF;
                    m->actionState = 1;
                } break;
                
                // Stuck
                case 6: {
                    switch (random_u16() % 3) {
                        case 0: drop_and_set_mario_action(m, ACT_HEAD_STUCK_IN_GROUND, 0); break;
                        case 1: drop_and_set_mario_action(m, ACT_BUTT_STUCK_IN_GROUND, 0); break;
                        case 2: drop_and_set_mario_action(m, ACT_FEET_STUCK_IN_GROUND, 0); break;
                    }
                    r96_play_character_sound(m, R96_MARIO_OOOF, R96_LUIGI_OOOF, R96_WARIO_OOOF);
                    m->particleFlags |= PARTICLE_MIST_CIRCLE;
                } break;

                // 1 HP
                case 7: {
                    m->health = 0x1FF;
                    m->healCounter = 0;
                    m->hurtCounter = 0;
                } break;
            }
        }
        return TRUE;
    }
    return FALSE;
}

s32 cheats_blj_anywhere(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.BLJAnywhere && !Cheats.ChaosMode))) {
        if (m->forwardVel < 1.f) {
            if (m->action == ACT_LONG_JUMP_LAND && Cheats.BLJAnywhere >= 7 && (gPlayer1Controller->buttonDown & A_BUTTON)) {
                set_jumping_action(m, ACT_LONG_JUMP, 0);
            } else if (m->action == ACT_LONG_JUMP && m->pos[1] - 50.f < m->floorHeight) {
                if (Cheats.BLJAnywhere < 7) {
                    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                        m->forwardVel -= (Cheats.BLJAnywhere - 1) * 2.5f;
                        m->vel[1] = -50.f;
                    }
                } else if (gPlayer1Controller->buttonDown & A_BUTTON) {
                    m->forwardVel -= (Cheats.BLJAnywhere - 7) * 2.5f;
                    m->vel[1] = -50.f;
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_swim_anywhere(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.SwimAnywhere && !Cheats.ChaosMode) || Cheats.ChaosSwimAnywhere)) {
        m->waterLevel = m->pos[1] + 300;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_exit_anywhere(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.ExitAnywhere && !Cheats.ChaosMode))) {
        return TRUE;
    }
    return FALSE;
}

s32 cheats_cap_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.CapModifier && !Cheats.ChaosMode))) {
        if (gPlayer1Controller->buttonDown & L_TRIG) {
            switch (gPlayer1Controller->buttonPressed & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {

                // Wing cap
                case U_JPAD: {
                    m->flags |= MARIO_WING_CAP;
                    m->capTimer = 0;
                    r96_play_cap_music(R96_EVENT_CAP_WING);
                } break;

                // Vanish cap
                case L_JPAD: {
                    m->flags |= MARIO_VANISH_CAP;
                    m->capTimer = 0;
                    r96_play_cap_music(R96_EVENT_CAP_VANISH);
                } break;

                // Metal cap
                case R_JPAD: {
                    m->flags |= MARIO_METAL_CAP;
                    m->capTimer = 0;
                    r96_play_cap_music(R96_EVENT_CAP_METAL);
                } break;

                // Normal cap
                case D_JPAD: {
                    m->flags &= ~(MARIO_WING_CAP | MARIO_VANISH_CAP | MARIO_METAL_CAP | MARIO_CAP_IN_HAND);
                    m->flags |= (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);
                    m->capTimer = 0;
                    r96_stop_cap_music();
                } break;
            }
        }
    }
    return FALSE;
}

s32 cheats_super_wing_cap(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.SuperWingCap && !Cheats.ChaosMode))) {
        if (m->action == ACT_FLYING) {
            if (m->forwardVel < 40.f) {
                m->forwardVel += 2.f;
            }
            if (gPlayer1Controller->buttonDown & A_BUTTON) {
                m->particleFlags |= PARTICLE_SPARKLES;
                if (m->forwardVel < 80.f) {
                    m->forwardVel += 4.f;
                }
            }
        }
    }
    return FALSE;
}

s32 cheats_auto_wall_kick(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.AutoWallKick && !Cheats.ChaosMode) || Cheats.ChaosWallKicks)) {
        if (m->action == ACT_AIR_HIT_WALL) {
            m->vel[1] = 52.f;
            m->faceAngle[1] += 0x8000;
            m->wallKickTimer = 0;
            set_mario_action(m, ACT_WALL_KICK_AIR, 0);
            set_mario_animation(m, MARIO_ANIM_START_WALLKICK);
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_walk_on_hazards(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.WalkOnHazards && !Cheats.ChaosMode))) {
        return TRUE;
    }
    return FALSE;
}

s32 cheats_no_death_barrier(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.NoDeathBarrier && !Cheats.ChaosMode))) {
        return TRUE;
    }
    return FALSE;
}

s32 cheats_no_bounds(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.NoBounds && !Cheats.ChaosMode) || Cheats.ChaosNoBounds)) {
        if (gCurrentObject == m->marioObj) {
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_no_hold_heavy(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.NoHoldHeavy && !Cheats.ChaosMode))) {
        if (m->action == ACT_HOLD_HEAVY_IDLE) {
            set_mario_action(m, ACT_HOLD_IDLE, 0);
        } else if (m->action == ACT_HOLD_HEAVY_WALKING) {
            set_mario_action(m, ACT_HOLD_WALKING, 0);
        }
        return TRUE;
    }
    return FALSE;
}

void mario_attract_nearby_coins(struct MarioState *m, f32 range) {
    if (!(gTimeStopState & TIME_STOP_ENABLED)) {
        static const s32 sCoinLists[] = {
            OBJ_LIST_GENACTOR,
            OBJ_LIST_LEVEL,
            -1
        };
        for (s32 *list = sCoinLists; *list != -1; list++) {
            struct Object *head = (struct Object *) &gObjectLists[*list];
            for (struct Object *obj = (struct Object *) head->header.next; obj != head; obj = (struct Object *) obj->header.next) {
                if (obj->oIntangibleTimer == 0 && obj->oInteractType == INTERACT_COIN) {
                    Vec3f dv = {
                        obj->oPosX - m->pos[0],
                        obj->oPosY - m->pos[1] - 60.f,
                        obj->oPosZ - m->pos[2],
                    };
                    f32 distToObj = vec3f_length(dv);
                    if (distToObj > 0.f && distToObj < range) {
                        vec3f_normalize(dv);
                        obj->oPosX -= dv[0] * 40.f;
                        obj->oPosY -= dv[1] * 40.f;
                        obj->oPosZ -= dv[2] * 40.f;
                    }
                }
            }
        }
    }
}

s32 cheats_coins_magnet(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.CoinsMagnet && !Cheats.ChaosMode))) {
        if (!Cheats.TimeStop) {
            mario_attract_nearby_coins(m, 1000.f);
        }
        return TRUE;
    }
    return FALSE;
}

s32 cheats_time_stop(struct MarioState *m) {
    static u32 sPrevTimeStopState = 0;
    static bool sPrevTimeStopEnabled = false;

    // Button shortcut
    if (gKeyPressed != VK_INVALID && (
        gKeyPressed == CheatsControls.TimeStopButton[0] ||
        gKeyPressed == CheatsControls.TimeStopButton[1] ||
        gKeyPressed == CheatsControls.TimeStopButton[2])) {
        Cheats.TimeStop = !Cheats.TimeStop;
    }
    
    // Time stop is enabled, back-up the current state
    if (Cheats.EnableCheats && ((Cheats.TimeStop && !Cheats.ChaosMode))) {
        if (!sPrevTimeStopEnabled) {
            sPrevTimeStopEnabled = true;
            sPrevTimeStopState = gTimeStopState;
        }
        gTimeStopState |= TIME_STOP_ENABLED;
        return TRUE;
    }
    
    // Time stop is disabled, retrieve the saved state
    if (sPrevTimeStopEnabled) {
        sPrevTimeStopEnabled = false;
        gTimeStopState = sPrevTimeStopState;
        sPrevTimeStopState = 0;
    }
    return FALSE;
}

s32 cheats_quick_ending(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.QuickEnding && !Cheats.ChaosMode))) {
        level_trigger_warp(m, WARP_OP_CREDITS_START);
        Cheats.QuickEnding = false;
        save_file_do_save(gCurrSaveFileNum - 1);
        return TRUE;
    }
    return FALSE;
}

s32 cheats_water_control(struct MarioState *m) {
    if (Cheats.EnableCheats && ((!Cheats.ChaosMode))) {
        static u32 sPrevCheatWaterLevel = 0;
        static s16 *sDefaultWaterLevels = NULL;
        if (!sDefaultWaterLevels) {
            sDefaultWaterLevels = calloc(LEVEL_COUNT * 8 * 8 * 6, sizeof(16));
            memset(sDefaultWaterLevels, 0xFF, LEVEL_COUNT * 8 * 8 * 6 * sizeof(s16));
        }

        s16 *p = gEnvironmentRegions;
        if (p != NULL) {
            s32 n = p[0];
            for (s32 i = 0; i != n && i < 8; ++i) {
                s16 *env = &p[1 + (i * 6)];
                s16 *def = &sDefaultWaterLevels[((((gCurrLevelNum * 8) + gCurrAreaIndex) * 8) + i) * 6];

                // Init default environment data
                if (def[0] == (s16) 0xFFFF) {
                    memcpy(def, env, 6 * sizeof(s16));
                }

                // Change environment level
                switch (Cheats.WaterLevel) {

                    // Default
                    case 0: {
                        if (sPrevCheatWaterLevel != 0) {
                            memcpy(env, def, 6 * sizeof(s16));
                        } else {
                            memcpy(def, env, 6 * sizeof(s16));
                        }
                    } break;
                    
                    // Drained
                    case 1: {
                        if (env[0] < 50 && sPrevCheatWaterLevel != 1) {
                            set_mario_action(m, ACT_FREEFALL, 0);
                            m->waterLevel = -0x3FFF;
                            m->prevAction = m->action;
                        }
                        env[1] = -0x7FFF;
                        env[2] = -0x7FFF;
                        env[3] = +0x7FFF;
                        env[4] = +0x7FFF;
                        env[5] = -0x3FFF;
                    } break;

                    // Flooded
                    case 2: {
                        if (env[0] < 50 && sPrevCheatWaterLevel != 2) {
                            set_mario_action(m, ACT_WATER_IDLE, 0);
                            m->waterLevel = +0x3FFF;
                            m->prevAction = m->action;
                        }
                        env[1] = -0x7FFF;
                        env[2] = -0x7FFF;
                        env[3] = +0x7FFF;
                        env[4] = +0x7FFF;
                        env[5] = +0x3FFF;
                    } break;
                }
            }
        }
        sPrevCheatWaterLevel = Cheats.WaterLevel;
    }
    return FALSE;
}

s32 cheats_speed_display(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.SpeedDisplay && !Cheats.ChaosMode))) {
        f32 hSpeed = m->forwardVel;
        f32 ySpeed = m->vel[1];
        if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
            hSpeed *= (f32) sModifierValues[Cheats.SwimModifier];
            ySpeed *= (f32) sModifierValues[Cheats.SwimModifier];
        } else {
            hSpeed *= (f32) sModifierValues[Cheats.SpeedModifier];
            if (ySpeed > 0.f) {
                ySpeed *= (f32) sModifierValues[Cheats.JumpModifier];
            }
        }
        print_text_fmt_int(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 44, "H SPD %d", (s32) hSpeed);
        print_text_fmt_int(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 28, "Y SPD %d", (s32) ySpeed);
        return TRUE;
    }
    return FALSE;
}

static void cheats_play_as_set_model_and_anims(struct MarioState *m, s32 modelId, const void *anim) {
    m->marioObj->header.gfx.sharedChild = gLoadedGraphNodes[modelId];
    if (modelId == MODEL_PLAYER) {
        if (isLuigi())      gMarioState->animation = (struct MarioAnimation *) &Data_LuigiAnims;
        else if (isWario()) gMarioState->animation = (struct MarioAnimation *) &Data_WarioAnims;
        else                gMarioState->animation = (struct MarioAnimation *) &Data_MarioAnims;
    } else {
        m->marioObj->header.gfx.curAnim.curAnim = (struct Animation *) anim;
    }
}

s32 cheats_play_as(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        s32 playAsIndex;
        if (Cheats.ChaosMode) {
            playAsIndex = Cheats.ChaosPlayAs;
        } else {
            playAsIndex = Cheats.PlayAs;
        }
        switch(playAsIndex) {
            case 0: cheats_play_as_set_model_and_anims(m, MODEL_PLAYER, NULL); break;
            case 1: cheats_play_as_set_model_and_anims(m, MODEL_BLACK_BOBOMB, bobomb_seg8_anims_0802396C[0]); break;
            case 2: cheats_play_as_set_model_and_anims(m, MODEL_BOBOMB_BUDDY, bobomb_seg8_anims_0802396C[0]); break;
            case 3: cheats_play_as_set_model_and_anims(m, MODEL_GOOMBA, goomba_seg8_anims_0801DA4C[0]); break;
            case 4: cheats_play_as_set_model_and_anims(m, MODEL_KOOPA_SHELL, amp_seg8_anims_08004034[0]); break;
            case 5: cheats_play_as_set_model_and_anims(m, MODEL_CHUCKYA, chuckya_seg8_anims_0800C070[0]); break;
            case 6: cheats_play_as_set_model_and_anims(m, MODEL_FLYGUY, flyguy_seg8_anims_08011A64[0]); break;
            case 7: {
                switch (gCurrLevelNum) {
                    case LEVEL_BOB: cheats_play_as_set_model_and_anims(m, MODEL_KOOPA_WITH_SHELL, koopa_seg6_anims_06011364[0]); break;
                    case LEVEL_WF: cheats_play_as_set_model_and_anims(m, MODEL_WHOMP, whomp_seg6_anims_06020A04[0]); break;
                    case LEVEL_JRB: cheats_play_as_set_model_and_anims(m, MODEL_CLAM_SHELL, clam_shell_seg5_anims_05001744[0]); break;
                    case LEVEL_CCM: cheats_play_as_set_model_and_anims(m, MODEL_PENGUIN, penguin_seg5_anims_05008B74[0]); break;
                    case LEVEL_BBH: cheats_play_as_set_model_and_anims(m, MODEL_MAD_PIANO, mad_piano_seg5_anims_05009B14[0]); break;
                    case LEVEL_HMC: cheats_play_as_set_model_and_anims(m, MODEL_HMC_ROLLING_ROCK, NULL); break;
                    case LEVEL_LLL: cheats_play_as_set_model_and_anims(m, MODEL_BULLY, bully_seg5_anims_0500470C[0]); break;
                    case LEVEL_SSL: cheats_play_as_set_model_and_anims(m, MODEL_KLEPTO, klepto_seg5_anims_05008CFC[0]); break;
                    case LEVEL_DDD: cheats_play_as_set_model_and_anims(m, MODEL_SUSHI, sushi_seg5_anims_0500AE54[0]); break;
                    case LEVEL_SL: cheats_play_as_set_model_and_anims(m, MODEL_SPINDRIFT, spindrift_seg5_anims_05002D68[0]); break;
                    case LEVEL_WDW: cheats_play_as_set_model_and_anims(m, MODEL_SKEETER, skeeter_seg6_anims_06007DE0[0]); break;
                    case LEVEL_TTM: cheats_play_as_set_model_and_anims(m, MODEL_UKIKI, ukiki_seg5_anims_05015784[0]); break;
                    case LEVEL_THI: cheats_play_as_set_model_and_anims(m, MODEL_SPINY, spiny_seg5_anims_05016EAC[0]); break;
                    case LEVEL_TTC: cheats_play_as_set_model_and_anims(m, MODEL_THWOMP, NULL); break;
                    case LEVEL_RR: cheats_play_as_set_model_and_anims(m, MODEL_ENEMY_LAKITU, lakitu_enemy_seg5_anims_050144D4[0]); break;
                    case LEVEL_BITDW: cheats_play_as_set_model_and_anims(m, MODEL_GOOMBA, goomba_seg8_anims_0801DA4C[0]); break;
                    case LEVEL_BITFS: cheats_play_as_set_model_and_anims(m, MODEL_BULLY, bully_seg5_anims_0500470C[0]); break;
                    case LEVEL_BITS: cheats_play_as_set_model_and_anims(m, MODEL_WHOMP, whomp_seg6_anims_06020A04[0]); break;
                    case LEVEL_TOTWC: cheats_play_as_set_model_and_anims(m, MODEL_EXCLAMATION_BOX, NULL); break;
                    case LEVEL_VCUTM: cheats_play_as_set_model_and_anims(m, MODEL_RED_FLAME, NULL); break;
                    case LEVEL_COTMC: cheats_play_as_set_model_and_anims(m, MODEL_SNUFIT, NULL); break;
                    case LEVEL_PSS: cheats_play_as_set_model_and_anims(m, MODEL_WOODEN_SIGNPOST, NULL); break;
                    case LEVEL_SA: cheats_play_as_set_model_and_anims(m, MODEL_MANTA_RAY, manta_seg5_anims_05008EB4[0]); break;
                    case LEVEL_WMOTR: cheats_play_as_set_model_and_anims(m, MODEL_STAR, manta_seg5_anims_05008EB4[0]); break;
                    case LEVEL_CASTLE_GROUNDS: cheats_play_as_set_model_and_anims(m, MODEL_YOSHI, yoshi_seg5_anims_05024100[0]); break;
                    case LEVEL_CASTLE: cheats_play_as_set_model_and_anims(m, MODEL_TOAD, toad_seg6_anims_0600FB58[6]); break;
                    case LEVEL_CASTLE_COURTYARD: cheats_play_as_set_model_and_anims(m, MODEL_BOO, NULL); break;
                    default: cheats_play_as_set_model_and_anims(m, MODEL_PLAYER, NULL); break;
                }
            } break;
        }
        if (playAsIndex > 0) {

            // Prevent a softlock when dying
            if (m->action == ACT_STANDING_DEATH) {
                level_trigger_warp(m, WARP_OP_DEATH);
                m->numLives += 1;
            }

            // F*ck doors. Make them explode. Thanks s4ys.
            if (m->collidedObjInteractTypes & INTERACT_DOOR) {
                obj_mark_for_deletion(m->usedObj);
                spawn_object(m->marioObj, MODEL_SMOKE, bhvBobombBullyDeathSmoke);
                play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION, m->marioObj->header.gfx.cameraToObject);
                m->particleFlags |= PARTICLE_TRIANGLE;
            }
        }
    }
    return FALSE;
}

s32 cheats_jukebox(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.Jukebox && !Cheats.ChaosMode))) {
        return Cheats.JukeboxMusic;
    }
    return -1;
}

s32 cheats_instant_death(struct MarioState *m) {
    if (Cheats.EnableCheats && ((gPlayer1Controller->buttonDown & (A_BUTTON | B_BUTTON | L_TRIG | Z_TRIG)) == (A_BUTTON | B_BUTTON | L_TRIG | Z_TRIG))) {
        level_trigger_warp(m, WARP_OP_DEATH);
        return TRUE;
    }
    return FALSE;
}

//
// Spamba
//

enum {
    SPAMBA_YELLOW_COIN,
    SPAMBA_RED_COIN,
    SPAMBA_BLUE_COIN,
    SPAMBA_MUSHROOM_1UP,
    SPAMBA_STAR_1,
    SPAMBA_STAR_2,
    SPAMBA_STAR_3,
    SPAMBA_STAR_4,
    SPAMBA_STAR_5,
    SPAMBA_STAR_6,
    SPAMBA_STAR_7,
    SPAMBA_WING_CAP,
    SPAMBA_VANISH_CAP,
    SPAMBA_METAL_CAP,
    SPAMBA_NORMAL_CAP,
    SPAMBA_RECOVERY_HEART,

    SPAMBA_GOOMBA,
    SPAMBA_GOOMBA_TRIPLET,
    SPAMBA_KOOPA,
    SPAMBA_KOOPA_SHELL,
    SPAMBA_BOBOMB,
    SPAMBA_BOBOMB_BUDDY,
    SPAMBA_CHAIN_CHOMP,
    SPAMBA_PIRANHA_PLANT,
    SPAMBA_PIRANHA_PLANT_FIRE,
    SPAMBA_WHOMP,
    SPAMBA_SPINDRIFT,
    SPAMBA_BOO,
    SPAMBA_MR_I,
    SPAMBA_BOOK,
    SPAMBA_SCUTTLEBUG,
    SPAMBA_SWOOP,
    SPAMBA_SNUFIT,
    SPAMBA_BULLY,
    SPAMBA_CHILL_BULLY,
    SPAMBA_MOTOS,
    SPAMBA_BLARGG,
    SPAMBA_POKEY,
    SPAMBA_FLYGUY,
    SPAMBA_MONEYBAG,
    SPAMBA_CHUCKYA,
    SPAMBA_SKEETER,
    SPAMBA_LAKITU,
    SPAMBA_SPINY,
    
    SPAMBA_BOWLING_BALL,
    SPAMBA_CLAM,
    SPAMBA_MR_BLIZZARD,
    SPAMBA_HAUNTED_CHAIR,
    SPAMBA_MAD_PIANO,
    SPAMBA_BIG_BOULDER,
    SPAMBA_FIRE_SPITTER,
    SPAMBA_FLAMETHROWER,
    SPAMBA_BOUNCING_FIREBALL,
    SPAMBA_CIRCLING_AMP,
    SPAMBA_HOMING_AMP,
    SPAMBA_HEAVE_HO,
    
    SPAMBA_KING_BOBOMB,
    SPAMBA_KING_WHOMP,
    SPAMBA_BIG_BOO,
    SPAMBA_BIG_BULLY,
    SPAMBA_BIG_CHILL_BULLY,
    SPAMBA_EYEROCK,
    SPAMBA_WIGGLER,
    SPAMBA_BOWSER,

    SPAMBA_HOOT,
    SPAMBA_PENGUIN,
    SPAMBA_MOTHER_PENGUIN,
    SPAMBA_KLEPTO,
    SPAMBA_UKIKI,
    SPAMBA_TOAD,
    SPAMBA_SIGNPOST,
    
    SPAMBA_CANNON,
    SPAMBA_BREAKABLE_BOX,
    SPAMBA_BREAKABLE_BOX_SMALL,
    SPAMBA_CRAZY_BOX,
    SPAMBA_EXCLAMATION_BOX_WING_CAP, // 0
    SPAMBA_EXCLAMATION_BOX_METAL_CAP, // 1
    SPAMBA_EXCLAMATION_BOX_VANISH_CAP, // 2
    SPAMBA_EXCLAMATION_BOX_KOOPA_SHELL, // 3
    SPAMBA_EXCLAMATION_BOX_ONE_COIN, // 4 
    SPAMBA_EXCLAMATION_BOX_THREE_COINS, // 5
    SPAMBA_EXCLAMATION_BOX_TEN_COINS, // 6 
    SPAMBA_EXCLAMATION_BOX_MUSHROOM_1UP, // 7
    SPAMBA_EXCLAMATION_BOX_STAR_1, // 8 
    SPAMBA_EXCLAMATION_BOX_STAR_2, // 10 
    SPAMBA_EXCLAMATION_BOX_STAR_3, // 11 
    SPAMBA_EXCLAMATION_BOX_STAR_4, // 12 
    SPAMBA_EXCLAMATION_BOX_STAR_5, // 13 
    SPAMBA_EXCLAMATION_BOX_STAR_6, // 14
    SPAMBA_METAL_BOX,
    SPAMBA_THWOMP,
    SPAMBA_GRINDEL,
    SPAMBA_GRINDEL_HORIZONTAL,
    SPAMBA_SPINDEL,
    SPAMBA_TOX_BOX,

    SPAMBA_COUNT
};

struct SpambaData {
    const BehaviorScript *behavior;
    const GeoLayout *geo;
    const char *name;
    f32 relX, relY, relZ;
    s32 behParams;
    bool dropToFloor;
    bool faceMario;
    s32 model0, model1, model2;
};

static const struct SpambaData sSpambaData[] = {
    { bhvSpambaYellowCoin,          yellow_coin_geo,        "YELLOW_COIN",                  0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_YELLOW_COIN,
    { bhvSpambaRedCoin,             red_coin_geo,           "RED_COIN",                     0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_RED_COIN,
    { bhvSpambaBlueCoin,            blue_coin_geo,          "BLUE_COIN",                    0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_BLUE_COIN,
    { bhvHidden1upInPole,           mushroom_1up_geo,       "MUSHROOM_1UP",                 0,  200,   0, 0x00000000, 0, 0 }, // SPAMBA_MUSHROOM_1UP,
    { bhvSpawnedStarNoLevelExit,    star_geo,               "STAR_1",                       0,  300,   0, 0x00000000, 0, 0 }, // SPAMBA_STAR_1,
    { bhvSpawnedStarNoLevelExit,    star_geo,               "STAR_2",                       0,  300,   0, 0x01000000, 0, 0 }, // SPAMBA_STAR_2,
    { bhvSpawnedStarNoLevelExit,    star_geo,               "STAR_3",                       0,  300,   0, 0x02000000, 0, 0 }, // SPAMBA_STAR_3,
    { bhvSpawnedStarNoLevelExit,    star_geo,               "STAR_4",                       0,  300,   0, 0x03000000, 0, 0 }, // SPAMBA_STAR_4,
    { bhvSpawnedStarNoLevelExit,    star_geo,               "STAR_5",                       0,  300,   0, 0x04000000, 0, 0 }, // SPAMBA_STAR_5,
    { bhvSpawnedStarNoLevelExit,    star_geo,               "STAR_6",                       0,  300,   0, 0x05000000, 0, 0 }, // SPAMBA_STAR_6,
    { bhvSpawnedStarNoLevelExit,    star_geo,               "STAR_7",                       0,  300,   0, 0x06000000, 0, 0 }, // SPAMBA_STAR_7,
    { bhvWingCap,                   marios_wing_cap_geo,    "WING_CAP",                     0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_WING_CAP,
    { bhvVanishCap,                 marios_cap_geo,         "VANISH_CAP",                   0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_VANISH_CAP,
    { bhvMetalCap,                  marios_metal_cap_geo,   "METAL_CAP",                    0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_METAL_CAP,
    { bhvNormalCap,                 marios_cap_geo,         "NORMAL_CAP",                   0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_NORMAL_CAP,
    { bhvRecoveryHeart,             heart_geo,              "RECOVERY_HEART",               0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_RECOVERY_HEART,

    { bhvGoomba,                    goomba_geo,             "GOOMBA",                       0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_GOOMBA,
    { bhvGoombaTripletSpawner,      NULL,                   "GOOMBA_TRIPLET",               0,   40,   0, 0x00000000, 1, 0 }, // SPAMBA_GOOMBA_TRIPLET,
    { bhvKoopa,                     koopa_with_shell_geo,   "KOOPA",                        0,   40, 300, 0x00010000, 1, 1, 1, 2, 3 }, // SPAMBA_KOOPA,
    { bhvKoopaShell,                koopa_shell_geo,        "KOOPA_SHELL",                  0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_KOOPA_SHELL,
    { bhvBobomb,                    black_bobomb_geo,       "BOBOMB",                       0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_BOBOMB,
    { bhvBobombBuddy,               bobomb_buddy_geo,       "BOBOMB_BUDDY",                 0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_BOBOMB_BUDDY,
    { bhvChainChomp,                chain_chomp_geo,        "CHAIN_CHOMP",                  0,   40, 500, 0x00000000, 1, 1, 4, 5 }, // SPAMBA_CHAIN_CHOMP,
    { bhvPiranhaPlant,              piranha_plant_geo,      "PIRANHA_PLANT",                0,   40, 400, 0x00000000, 1, 1, 6, 7 }, // SPAMBA_PIRANHA_PLANT,
    { bhvFirePiranhaPlant,          piranha_plant_geo,      "PIRANHA_PLANT_FIRE",           0,   40, 300, 0x00000000, 1, 1, 8 }, // SPAMBA_PIRANHA_PLANT_FIRE,
    { bhvSmallWhomp,                whomp_geo,              "WHOMP",                        0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_WHOMP,
    { bhvSpindrift,                 spindrift_geo,          "SPINDRIFT",                    0,   40, 300, 0x00000000, 0, 1 }, // SPAMBA_SPINDRIFT,
    { bhvBoo,                       boo_geo,                "BOO",                          0,   40, 300, 0x00000000, 0, 1, 9, 10 }, // SPAMBA_BOO,
    { bhvMrI,                       mr_i_geo,               "MR_I",                         0,   40, 300, 0x00000000, 1, 1, 11, 12 }, // SPAMBA_MR_I,
    { bhvFlyingBookend,             bookend_geo,            "BOOK",                         0,   40, 400, 0x00000000, 0, 1, 13 }, // SPAMBA_BOOK,
    { bhvScuttlebug,                scuttlebug_geo,         "SCUTTLEBUG",                   0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_SCUTTLEBUG,
    { bhvSwoop,                     swoop_geo,              "SWOOP",                        0,  120, 300, 0x00000000, 0, 1 }, // SPAMBA_SWOOP,
    { bhvSnufit,                    snufit_geo,             "SNUFIT",                       0,  120, 300, 0x00000000, 0, 1, 14 }, // SPAMBA_SNUFIT,
    { bhvSmallBully,                bully_geo,              "BULLY",                        0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_BULLY,
    { bhvSmallBully,                chilly_chief_geo,       "CHILL_BULLY",                  0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_CHILL_BULLY,
    { bhvMotos,                     motos_geo,              "MOTOS",                        0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_MOTOS,
    { bhvFriendlyBlargg,            friendly_blargg_geo,    "BLARGG",                       0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_BLARGG,
    { bhvPokey,                     NULL,                   "POKEY",                        0,   40, 300, 0x00000000, 1, 1, 15, 16 }, // SPAMBA_POKEY,
    { bhvFlyGuy,                    flyguy_geo,             "FLYGUY",                       0,   80, 300, 0x00000000, 0, 0, 8 }, // SPAMBA_FLYGUY,
    { bhvMoneybagHidden,            yellow_coin_geo,        "MONEYBAG",                     0,   40, 300, 0x00000000, 1, 0, 17, 9 }, // SPAMBA_MONEYBAG,
    { bhvChuckya,                   chuckya_geo,            "CHUCKYA",                      0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_CHUCKYA,
    { bhvSkeeter,                   skeeter_geo,            "SKEETER",                      0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_SKEETER,
    { bhvEnemyLakitu,               enemy_lakitu_geo,       "LAKITU",                       0,  120, 300, 0x00000000, 0, 1, 18, 19, 20 }, // SPAMBA_LAKITU,
    { bhvSpiny,                     spiny_geo,              "SPINY",                        0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_SPINY,
    
    { bhvFreeBowlingBall,           bowling_ball_geo,       "BOWLING_BALL",                 0,   40, 400, 0x00000000, 0, 0 }, // SPAMBA_BOWLING_BALL,
    { bhvClamShell,                 clam_shell_geo,         "CLAM",                         0,   40, 400, 0x00000000, 1, 1, 21 }, // SPAMBA_CLAM,
    { bhvMrBlizzard,                mr_blizzard_geo,        "MR_BLIZZARD",                  0,   40, 300, 0x00000000, 1, 1, 22 }, // SPAMBA_MR_BLIZZARD,
    { bhvHauntedChair,              haunted_chair_geo,      "HAUNTED_CHAIR",                0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_HAUNTED_CHAIR,
    { bhvMadPiano,                  mad_piano_geo,          "MAD_PIANO",                    0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_MAD_PIANO,
    { bhvBigBoulder,                hmc_geo_000548,         "BIG_BOULDER",                  0,   40, 600, 0x00000000, 0, 0 }, // SPAMBA_BIG_BOULDER,
    { bhvFireSpitter,               bowling_ball_geo,       "FIRE_SPITTER",                 0,   40, 300, 0x00000000, 0, 1, 8 }, // SPAMBA_FIRE_SPITTER,
    { bhvFlamethrower,              NULL,                   "FLAMETHROWER",                 0,   80, 300, 0x00000000, 0, 0, 23, 24 }, // SPAMBA_FLAMETHROWER,
    { bhvBouncingFireball,          NULL,                   "BOUNCING_FIREBALL",            0,   40, 300, 0x00000000, 0, 0, 23 }, // SPAMBA_BOUNCING_FIREBALL,
    { bhvCirclingAmp,               amp_geo,                "CIRCLING_AMP",                 0,   80, 400, 0x00000000, 0, 1 }, // SPAMBA_CIRCLING_AMP,
    { bhvHomingAmp,                 amp_geo,                "HOMING_AMP",                   0,   80, 300, 0x00000000, 0, 1 }, // SPAMBA_HOMING_AMP,
    { bhvHeaveHo,                   heave_ho_geo,           "HEAVE_HO",                     0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_HEAVE_HO,
    
    { bhvKingBobomb,                king_bobomb_geo,        "KING_BOBOMB",                  0,   40, 600, 0x00000000, 1, 1 }, // SPAMBA_KING_BOBOMB,
    { bhvWhompKingBoss,             whomp_geo,              "KING_WHOMP",                   0,   40, 600, 0x01000000, 1, 1 }, // SPAMBA_KING_WHOMP,
    { bhvBalconyBigBoo,             boo_geo,                "BIG_BOO",                      0,   40, 600, 0x02000000, 0, 1 }, // SPAMBA_BIG_BOO,
    { bhvBigBully,                  bully_boss_geo,         "BIG_BULLY",                    0,   40, 600, 0x03000000, 1, 1 }, // SPAMBA_BIG_BULLY,
    { bhvBigBully,                  chilly_chief_big_geo,   "BIG_CHILL_BULLY",              0,   40, 600, 0x04000000, 1, 1 }, // SPAMBA_BIG_CHILL_BULLY,
    { bhvEyerokBoss,                NULL,                   "EYEROCK",                      0,   40, 600, 0x05000000, 1, 1, 25, 26 }, // SPAMBA_EYEROCK,
    { bhvWigglerHead,               wiggler_head_geo,       "WIGGLER",                      0,   40, 600, 0x05000000, 1, 1, 27 }, // SPAMBA_WIGGLER,
    { bhvBowser,                    bowser_geo,             "BOWSER",                       0,   40, 600, 0x00000000, 1, 1, 28, 29, 30 }, // SPAMBA_BOWSER,

    { bhvHoot,                      hoot_geo,               "HOOT",                         0,  200, 300, 0x00000000, 0, 1 }, // SPAMBA_HOOT,
    { bhvSmallPenguin,              penguin_geo,            "PENGUIN",                      0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_PENGUIN,
    { bhvTuxiesMother,              penguin_geo,            "MOTHER_PENGUIN",               0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_MOTHER_PENGUIN,
    { bhvKlepto,                    klepto_geo,             "KLEPTO",                       0,  200, 300, 0x00000000, 0, 1 }, // SPAMBA_KLEPTO,
    { bhvUkiki,                     ukiki_geo,              "UKIKI",                        0,   40, 300, 0x00010000, 1, 1 }, // SPAMBA_UKIKI,
    { bhvToadMessage,               toad_geo,               "TOAD",                         0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_TOAD,
    { bhvMessagePanel,              wooden_signpost_geo,    "SIGNPOST",                     0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_SIGNPOST,

    { bhvCannon,                    NULL,                   "CANNON",                       0,  200,   0, 0x00000000, 0, 0, 31 }, // SPAMBA_CANNON,
    { bhvBreakableBox,              breakable_box_geo,      "BREAKABLE_BOX",                0, -200,   0, 0x00000000, 0, 0 }, // SPAMBA_BREAKABLE_BOX,
    { bhvBreakableBoxSmall,         breakable_box_geo,      "BREAKABLE_BOX_SMALL",          0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_BREAKABLE_BOX_SMALL,
    { bhvJumpingBox,                breakable_box_geo,      "CRAZY_BOX",                    0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_CRAZY_BOX,
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_WING_CAP",     0,  300,   0, 0x00000000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_WING_CAP, // 0
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_METAL_CAP",    0,  300,   0, 0x00010000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_METAL_CAP, // 1
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_VANISH_CAP",   0,  300,   0, 0x00020000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_VANISH_CAP, // 2
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_KOOPA_SHELL",  0,  300,   0, 0x00030000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_KOOPA_SHELL, // 3
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_ONE_COIN",     0,  300,   0, 0x00040000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_ONE_COIN, // 4 
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_THREE_COINS",  0,  300,   0, 0x00050000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_THREE_COINS, // 5
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_TEN_COINS",    0,  300,   0, 0x00060000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_TEN_COINS, // 6 
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_MUSHROOM_1UP", 0,  300,   0, 0x00070000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_MUSHROOM_1UP, // 7
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_STAR_1",       0,  300,   0, 0x00080000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_1, // 8 
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_STAR_2",       0,  300,   0, 0x000A0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_2, // 10 
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_STAR_3",       0,  300,   0, 0x000B0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_3, // 11 
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_STAR_4",       0,  300,   0, 0x000C0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_4, // 12 
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_STAR_5",       0,  300,   0, 0x000D0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_5, // 13 
    { bhvExclamationBox,            exclamation_box_geo,    "EXCLAMATION_BOX_STAR_6",       0,  300,   0, 0x000E0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_6, // 14
    { bhvPushableMetalBox,          metal_box_geo,          "METAL_BOX",                    0, -307,   0, 0x00000000, 0, 0 }, // SPAMBA_METAL_BOX,
    { bhvThwomp,                    thwomp_geo,             "THWOMP",                       0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_THWOMP,
    { bhvGrindel,                   ssl_geo_000734,         "GRINDEL",                      0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_GRINDEL,
    { bhvHorizontalGrindel,         ssl_geo_000734,         "GRINDEL_HORIZONTAL",           0,   40, 400, 0x00000000, 1, 0 }, // SPAMBA_GRINDEL_HORIZONTAL,
    { bhvSpindel,                   ssl_geo_000764,         "SPINDEL",                      0,  180, 300, 0x00010000, 0, 0 }, // SPAMBA_SPINDEL,
    { bhvToxBox,                    ssl_geo_000630,         "TOX_BOX",                      0,    0, 300, 0x00000000, 0, 0 }, // SPAMBA_TOX_BOX,
};


// Exclamation point geo layout
static const GeoLayout exclamation_point_geo[] = {
    GEO_NODE_START(),
    GEO_OPEN_NODE(),
        GEO_DISPLAY_LIST(LAYER_ALPHA, exclamation_box_outline_seg8_dl_08025F08),
    GEO_CLOSE_NODE(),
    GEO_END(),
};

static void cheats_spamba_load_model_graph_node(s32 model) {
    const GeoLayout *geo = NULL;
    if (model != 0) {
        s32 modelId = 0xFF;
        switch (model) {
            case  1: modelId = MODEL_KOOPA_WITHOUT_SHELL;       geo = koopa_without_shell_geo; break;
            case  2: modelId = MODEL_KOOPA_WITH_SHELL;          geo = koopa_with_shell_geo; break;
            case  3: modelId = MODEL_KOOPA_SHELL;               geo = koopa_shell_geo; break;
            case  4: modelId = MODEL_METALLIC_BALL;             geo = metallic_ball_geo; break;
            case  5: modelId = MODEL_WOODEN_POST;               geo = wooden_post_geo; break;
            case  6: modelId = MODEL_BUBBLE;                    geo = bubble_geo; break;
            case  7: modelId = MODEL_PURPLE_MARBLE;             geo = purple_marble_geo; break;
            case  8: modelId = MODEL_RED_FLAME_SHADOW;          geo = red_flame_shadow_geo; break;
            case  9: modelId = MODEL_YELLOW_COIN;               geo = yellow_coin_geo; break;
            case 10: modelId = MODEL_BLUE_COIN;                 geo = blue_coin_geo; break;
            case 11: modelId = MODEL_MR_I;                      geo = mr_i_geo; break;
            case 12: modelId = MODEL_MR_I_IRIS;                 geo = mr_i_iris_geo; break;
            case 13: modelId = MODEL_BOOKEND_PART;              geo = bookend_part_geo; break;
            case 14: modelId = MODEL_BOWLING_BALL;              geo = bowling_ball_geo; break;
            case 15: modelId = MODEL_POKEY_HEAD;                geo = pokey_head_geo; break;
            case 16: modelId = MODEL_POKEY_BODY_PART;           geo = pokey_body_part_geo; break;
            case 17: modelId = MODEL_MONEYBAG;                  geo = moneybag_geo; break;
            case 18: modelId = MODEL_MIST;                      geo = mist_geo; break;
            case 19: modelId = MODEL_SPINY_BALL;                geo = spiny_ball_geo; break;
            case 20: modelId = MODEL_SPINY;                     geo = spiny_geo; break;
            case 21: modelId = MODEL_BUBBLE;                    geo = bubble_geo; break;
            case 22: modelId = MODEL_WHITE_PARTICLE;            geo = white_particle_geo; break;
            case 23: modelId = MODEL_RED_FLAME;                 geo = red_flame_geo; break;
            case 24: modelId = MODEL_BLUE_FLAME;                geo = blue_flame_geo; break;
            case 25: modelId = MODEL_EYEROK_LEFT_HAND;          geo = eyerok_left_hand_geo; break;
            case 26: modelId = MODEL_EYEROK_RIGHT_HAND;         geo = eyerok_right_hand_geo; break;
            case 27: modelId = MODEL_WIGGLER_BODY;              geo = wiggler_body_geo; break;
            case 28: modelId = MODEL_BOWSER_BOMB_CHILD_OBJ;     geo = bowser_bomb_geo; break;
            case 29: modelId = MODEL_BOWSER_FLAMES;             geo = bowser_flames_geo; break;
            case 30: modelId = MODEL_BOWSER_WAVE;               geo = invisible_bowser_accessory_geo; break;
            case 31: modelId = MODEL_CANNON_BARREL;             geo = cannon_barrel_geo; break;
            case 32: modelId = MODEL_EXCLAMATION_BOX;           geo = exclamation_box_geo; break;
            case 33: modelId = MODEL_EXCLAMATION_BOX_OUTLINE;   geo = exclamation_box_outline_geo; break;
            case 34: modelId = MODEL_EXCLAMATION_POINT;         geo = exclamation_point_geo; break;
        }
        gLoadedGraphNodes[modelId] = dynos_geo_get_graph_node(geo, true);
    }
}

static struct Object *cheats_spamba_spawn_object(struct MarioState *m, u32 index, f32 relX, f32 relY, f32 relZ, bool faceMario) {
    struct Object *obj = spawn_object_relative(
        0, relX, relY, relZ,
        m->marioObj, MODEL_NONE,
        sSpambaData[index].behavior
    );
    obj->oBehParams = sSpambaData[index].behParams;
    obj->oBehParams2ndByte = ((sSpambaData[index].behParams >> 16) & 0xFF);
    obj->header.gfx.sharedChild = dynos_geo_get_graph_node(sSpambaData[index].geo, true);
    if (faceMario) {
        obj_set_angle(obj, 0, obj_angle_to_object(obj, m->marioObj), 0);
    } else {
        obj_set_angle(obj, 0, obj_angle_to_object(m->marioObj, obj), 0);
    }
    if (sSpambaData[index].dropToFloor) {
        obj->oPosY = find_floor_height(obj->oPosX, obj->oPosY + 160.f, obj->oPosZ);
        obj->oMoveFlags |= OBJ_MOVE_ON_GROUND;
    }
    cheats_spamba_load_model_graph_node(sSpambaData[index].model0);
    cheats_spamba_load_model_graph_node(sSpambaData[index].model1);
    cheats_spamba_load_model_graph_node(sSpambaData[index].model2);
    
    switch (index) {
        case SPAMBA_YELLOW_COIN:
        case SPAMBA_RED_COIN:
        case SPAMBA_BLUE_COIN: {
            obj->oForwardVel = random_float() * 15.f;
            obj->oVelY = random_float() * 30.f + 20.f;
            obj->oMoveAngleYaw = random_u16();
        } break;

        case SPAMBA_STAR_1:
        case SPAMBA_STAR_2:
        case SPAMBA_STAR_3:
        case SPAMBA_STAR_4:
        case SPAMBA_STAR_5:
        case SPAMBA_STAR_6:
        case SPAMBA_STAR_7: {
            obj->oHomeX = obj->oPosX;
            obj->oHomeY = obj->oPosY;
            obj->oHomeZ = obj->oPosZ;
            obj->oInteractionSubtype = INT_SUBTYPE_NO_EXIT;
        } break;

        case SPAMBA_WING_CAP: {
            if (isLuigi()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(luigis_wing_cap_geo, true);
            if (isWario()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(warios_wing_cap_geo, true);
        } break;

        case SPAMBA_VANISH_CAP:
        case SPAMBA_NORMAL_CAP: {
            if (isLuigi()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(luigis_cap_geo, true);
            if (isWario()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(warios_cap_geo, true);
        } break;

        case SPAMBA_METAL_CAP: {
            if (isLuigi()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(luigis_metal_cap_geo, true);
            if (isWario()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(warios_metal_cap_geo, true);
        } break;
        
        case SPAMBA_BOBOMB_BUDDY:
        case SPAMBA_SIGNPOST: {
            obj->oBehParams2ndByte = (u8) (random_u16() % DIALOG_COUNT);
            obj->oBehParams = obj->oBehParams2ndByte << 16;
        } break;

        case SPAMBA_PIRANHA_PLANT_FIRE: {
            obj->oTimer = 100;
        } break;

        case SPAMBA_HAUNTED_CHAIR:
        case SPAMBA_SPINY: {
            obj->parentObj = obj;
        } break;
        
        // Init Bowser here to prevent triggering the cutscene (and setting other params)
        case SPAMBA_BOWSER: {
            obj->hitboxRadius = 400;
            obj->hitboxHeight = 400;
            obj->oWallHitboxRadius = 100;
            obj->oInteractType = INTERACT_DAMAGE; // Grabbing and releasing him crashes the game (there is no bomb outside Bowser stages anyway)
            obj->oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE);
            obj->oHomeX = obj->oPosX;
            obj->oHomeY = obj->oPosY;
            obj->oHomeZ = obj->oPosZ;
            obj->oAnimations = (struct Animation **) bowser_seg6_anims_06057690;
            obj->oGravity = -4.f;
            obj->oBounciness = -0.7f;
            obj->oDragStrength = 10.f;
            obj->oFriction = 10.f;
            obj->oBuoyancy = 2.f;
            obj->oBowserUnk110 = 1;
            obj->oOpacity = 0xFF;
            obj->oBowserUnk1AC = 0xFF;
            obj->oBehParams2ndByte = 2;
            obj->oBowserUnk1B2 = 0;
            obj->oHealth = 3;
            obj->oAction = 0;
            obj->oBowserUnk1AE = 0;
            obj->oBowserEyesShut = 0;
            obj->curBhvCommand = bhvBowser + 27;
            spawn_object(obj, MODEL_NONE, bhvBowserBodyAnchor);
            spawn_object(obj, MODEL_NONE, bhvBowserTailAnchor);
        } break;

        // Init Hoot here to skip the dialog and make it directly visible and tangible (no need for a tree)
        case SPAMBA_HOOT: {
            obj->hitboxRadius = 75;
            obj->hitboxHeight = 75;
            obj->oWallHitboxRadius = 25;
            obj->oIntangibleTimer = 0;
            obj->oInteractType = INTERACT_HOOT;
            obj->oHootAvailability = HOOT_AVAIL_READY_TO_FLY;
            obj->oHootMarioReleaseTime = 0;
            obj->oFlags = (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE);
            obj->oHomeX = obj->oPosX;
            obj->oHomeY = obj->oPosY;
            obj->oHomeZ = obj->oPosZ;
            obj->oAnimations = (struct Animation **) hoot_seg5_anims_05005768;
            geo_obj_init_animation(&obj->header.gfx, &obj->oAnimations[0]);
            obj->curBhvCommand = bhvHoot + 9;
            m->usedObj = obj; // It's needed to not crash
        } break;
        
        case SPAMBA_TOAD: {
            obj->oBehParams = (random_u16() % DIALOG_COUNT) << 24;
        } break;
        
        case SPAMBA_CANNON: {
            obj->oBehParams2ndByte = (u8) ((m->faceAngle[1] - 0x4000) >> 8);
            obj->oBehParams = obj->oBehParams2ndByte << 16;
        } break;

        case SPAMBA_TOX_BOX: {
            obj->oBehParams2ndByte = (u8) (random_u16() % 3);
            obj->oBehParams = obj->oBehParams2ndByte << 16;
        } break;
    }
    return obj;
}

static const char *cheats_spamba_u8str_to_charstr(const u8 *str64) {
    static char sTextBuffers[256][8];
    static s32 sTextIndex = 0;
    char *buffer = sTextBuffers[sTextIndex];
    sTextIndex = (sTextIndex + 1) % 8;
    memset(buffer, 0, 256);
    for (s32 i = 0; str64[i] != 0xFF; ++i) {
        u8 c = str64[i];
        if (c < 10) {
            buffer[i] = '0' + c;
        } else if (c < 36) {
            buffer[i] = 'A' + (c - 10);
        } else {
            buffer[i] = ' ';
        }
    }
    return buffer;
}

s32 cheats_spamba(struct MarioState *m) {
    if (Cheats.EnableCheats && ((Cheats.Spamba && !Cheats.ChaosMode))) {
        if (gKeyPressed != VK_INVALID) {

            // Select previous object
            if (gKeyPressed == CheatsControls.SpambaControls[0]) {
                Cheats.SpambaIndex = (Cheats.SpambaIndex + SPAMBA_COUNT - 1) % SPAMBA_COUNT;
                play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
            }

            // Select next object
            if (gKeyPressed == CheatsControls.SpambaControls[1]) {
                Cheats.SpambaIndex = (Cheats.SpambaIndex + SPAMBA_COUNT + 1) % SPAMBA_COUNT;
                play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
            }

            // Spawn selected object
            if (gKeyPressed == CheatsControls.SpambaControls[2]) {
                cheats_spamba_spawn_object(
                    m, Cheats.SpambaIndex,
                    sSpambaData[Cheats.SpambaIndex].relX,
                    sSpambaData[Cheats.SpambaIndex].relY,
                    sSpambaData[Cheats.SpambaIndex].relZ,
                    sSpambaData[Cheats.SpambaIndex].faceMario
                );
            }
        }

        // Display selected object
        char key[64]; sprintf(key, "TEXT_OPT_CHEAT_SPAMBA_%s", sSpambaData[Cheats.SpambaIndex].name);
        char str[64]; sprintf(str, "SPAMBA %s", cheats_spamba_u8str_to_charstr(get_key_string(key)));
        print_text(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 8, str);
        return TRUE;
    }
    return FALSE;
}

//
// Chaos mode
//

static const char *sChaosNames[] = {
    "LIFE_DRAIN",
    "CONTROLS",
    "GRAVITY",
    "WALL_KICKS",
    "HOLD_MODIFIER",
    "SPEED_MODIFIER",
    "JUMP_MODIFIER",
    "SWIM_MODIFIER",
    "SIZE_MODIFIER",
    "CAP_MODIFIER",
    "PLAY_AS",
    "RELEASIO",
    "SWIM_ANYWHERE",
    "FLOOR_IS_LAVA",
    "DEADLY_OBJECTS",
    "NO_BOUNDS",
    "WATER_LEVEL",
    "OBJECT_MAGNET",
    "SLOW_TIME",
    "HURT_MARIO",
    "DISPLAY",
    "RAINBOW",
    "INVERTED_SCREEN",
    "WIREFRAME",
    "JACKPOT",
    "GREEN_DEMON",
    "STAR",
    "GOOMBA_PLAGUE",
    "BOBOMB_RAIN",
    "CHAIRS",
    "STALKERS",
    "SHOOTERS",
    "CHUCKSTERS",
    "DODGEBALL",
    "BOSS_FIGHT",
    "BOWSER_TIME",
    "HOOT",
    "NPCS",
    "MINECRAFT",
    "SURPRISE",
};

struct ChaosEffect {
    s32 index;
    s32 duration;
    s32 timer;
    s32 value;
    bool initialized;
};

static struct ChaosEffect sChaosEffects[8];
static s32 sChaosNextEffect = -1;
static s32 sChaosCooldown = 0;

#define CHEATS_CHAOS_COOLDOWN_MIN 300  // 10 seconds
#define CHEATS_CHAOS_COOLDOWN_MAX 450  // 15 seconds
#define CHEATS_CHAOS_DURATION_MIN 750  // 25 seconds
#define CHEATS_CHAOS_DURATION_MAX 1050 // 35 seconds

#define cheats_chaos_init_effect(...) \
if (!effect->initialized) { \
    effect->initialized = true; \
    __VA_ARGS__ \
}

static s32 cheats_chaos_get_new_effect_index() {
    s32 index = (s32) (random_u16() % CHAOS_COUNT);
    for (s32 i = 0; i != 8; ++i) {
        if (sChaosEffects[i].index == index) {
            return cheats_chaos_get_new_effect_index();
        }
    }
    return index;
}

s32 cheats_chaos_mode(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.ChaosMode) {

        // If the player collects a star or a key, the next effect will always be 'Chaos Display'
        if (dynos_jingle_is_playing(R96_EVENT_STAR_COLLECT) ||
            dynos_jingle_is_playing(R96_EVENT_KEY_COLLECT)) {
            sChaosCooldown = 1;
            sChaosNextEffect = CHAOS_DISPLAY;
        }
        
        // If ready, add the next effect to list and select a new effect
        if (sChaosCooldown-- == 0) {

            // Activate the next effect for a duration between 25 and 35 seconds
            if (sChaosNextEffect != -1) {
                for (s32 i = 0; i != 8; ++i) {
                    if (sChaosEffects[i].duration == 0) {
                        memset(&sChaosEffects[i], 0, sizeof(sChaosEffects[i]));
                        sChaosEffects[i].index = sChaosNextEffect;
                        sChaosEffects[i].duration = CHEATS_CHAOS_DURATION_MIN + random_float() * (CHEATS_CHAOS_DURATION_MAX - CHEATS_CHAOS_DURATION_MIN);
                        break;
                    }
                }
            }
            
            // Select a new effect and set a 10~15 seconds cooldown
            sChaosNextEffect = cheats_chaos_get_new_effect_index();
            sChaosCooldown = CHEATS_CHAOS_COOLDOWN_MIN + random_float() * (CHEATS_CHAOS_COOLDOWN_MAX - CHEATS_CHAOS_COOLDOWN_MIN);
        }

        // Flags
        bool insideCastle = (
            gCurrLevelNum == LEVEL_CASTLE ||
            gCurrLevelNum == LEVEL_CASTLE_GROUNDS ||
            gCurrLevelNum == LEVEL_CASTLE_COURTYARD ||
            gCurrLevelNum == LEVEL_FOURTH_FLOOR
        );
        bool onGround = (
            !(m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) &&
            !(m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING))
        );
        
        // Update activated effects
        memset(Cheats.Chaos, 0, sizeof(Cheats.Chaos));
        for (s32 i = 0; i != 8; ++i) {
            struct ChaosEffect *effect = &sChaosEffects[i];
            if (effect->duration > 0) {
                effect->duration--;
                switch (effect->index) {

                    // Drain Mario's health by a random amount every frame
                    case CHAOS_LIFE_DRAIN: {
                        if (!insideCastle) {
                            m->health -= 1 + (random_u16() % 4);
                        }
                    } break;

                    // Can make controls super responsive, but can also invert them
                    // Duration is reduced to 15~25 seconds
                    case CHAOS_CONTROLS: {
                        cheats_chaos_init_effect(
                            effect->duration -= 300;
                            effect->value = (
                                ((random_u16() & 1) << 0) | // Bit for responsive controls
                                ((random_u16() & 1) << 1) | // Bit for inverted stick X
                                ((random_u16() & 1) << 2)   // Bit for inverted stick Y
                            );
                        );
                        Cheats.ChaosControls = (u32) effect->value;
                    } break;

                    // Alter the gravity
                    case CHAOS_GRAVITY: {
                        cheats_chaos_init_effect(
                            effect->value = (s32) random_sign();
                        );
                        if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_AIRBORNE) {
                            if (m->action == ACT_FREEFALL || m->action == ACT_LONG_JUMP) {
                                m->vel[1] += 1.f * effect->value;
                            } else {
                                m->vel[1] += 2.f * effect->value;
                            }
                        }
                    } break;

                    // Perfect wall-kicks or bonks when touching a wall
                    case CHAOS_WALL_KICKS: {
                        cheats_chaos_init_effect(
                            effect->value = (s32) (random_u16() & 1);
                        );
                        if (effect->value) {
                            Cheats.ChaosWallKicks = TRUE;
                        } else {
                            Cheats.ChaosWallKicks = FALSE;
                            if (m->action == ACT_AIR_HIT_WALL ||
                                m->action == ACT_WALL_KICK_AIR) {
                                m->wallKickTimer = 0;
                                m->vel[1] = min(m->vel[1], 0.f);
                                m->particleFlags |= PARTICLE_VERTICAL_STAR;
                                set_mario_action(m, ACT_BACKWARD_AIR_KB, 0);
                            }
                        }
                    } break;

                    // Light hold, Heavy hold or squish Mario when he tries to hold something
                    case CHAOS_HOLD_MODIFIER: {
                        cheats_chaos_init_effect(
                            effect->value = (s32) (random_u16() % 3);
                        );
                        switch (effect->value) {

                            // Light
                            case 0: {
                                if (m->action == ACT_HOLD_HEAVY_IDLE) {
                                    set_mario_action(m, ACT_HOLD_IDLE, 0);
                                } else if (m->action == ACT_HOLD_HEAVY_WALKING) {
                                    set_mario_action(m, ACT_HOLD_WALKING, 0);
                                }
                                m->marioBodyState->grabPos = GRAB_POS_LIGHT_OBJ;
                            } break;
                            
                            // Heavy
                            case 1: {
                                if (m->action == ACT_HOLD_IDLE) {
                                    set_mario_action(m, ACT_HOLD_HEAVY_IDLE, 0);
                                } else if (m->action == ACT_HOLD_WALKING) {
                                    set_mario_action(m, ACT_HOLD_HEAVY_WALKING, 0);
                                }
                                m->marioBodyState->grabPos = GRAB_POS_HEAVY_OBJ;
                            } break;
                            
                            // Too heavy...
                            case 2: {
                                if (m->heldObj) {
                                    drop_and_set_mario_action(m, ACT_SQUISHED, 0);
                                    r96_play_character_sound(m, R96_MARIO_ATTACKED, R96_LUIGI_ATTACKED, R96_WARIO_ATTACKED);
                                    vec3f_set(m->marioObj->header.gfx.scale, 1.8f, 0.05f, 1.8f);
                                    m->particleFlags |= PARTICLE_MIST_CIRCLE;
                                    m->squishTimer = 0xFF;
                                    m->actionState = 1;
                                    m->hurtCounter += 12;
                                }
                                if (m->action == ACT_SQUISHED && m->actionState == 1) {
                                    vec3f_set(m->marioObj->header.gfx.scale, 1.8f, 0.05f, 1.8f);
                                    m->squishTimer = 0xFF;
                                }
                            } break;
                        }
                    } break;

                    // Random modifier between x2 and x5
                    case CHAOS_SPEED_MODIFIER: {
                        cheats_chaos_init_effect(
                            effect->value = (s32) (1 + (random_u16() % 4));
                        );
                        Cheats.ChaosSpeedModifier = effect->value;
                    } break;

                    // Random modifier between x2 and x5
                    case CHAOS_JUMP_MODIFIER: {
                        cheats_chaos_init_effect(
                            effect->value = (s32) (1 + (random_u16() % 4));
                        );
                        Cheats.ChaosJumpModifier = effect->value;
                    } break;

                    // Random modifier between x2 and x5
                    case CHAOS_SWIM_MODIFIER: {
                        cheats_chaos_init_effect(
                            effect->value = (s32) (1 + (random_u16() % 4));
                        );
                        Cheats.ChaosSwimModifier = effect->value;
                    } break;

                    // Random modifier between x0.25 and x4 (except x1), change every 5 seconds
                    case CHAOS_SIZE_MODIFIER: {
                        if (effect->timer-- == 0) {
                            effect->value = (s32) (1 + (random_u16() % 7));
                            effect->timer = 149;
                        }
                        Cheats.ChaosSizeModifier = effect->value;
                    } break;

                    // Every 5 seconds, change Mario's cap
                    // Doesn't start or change the music
                    case CHAOS_CAP_MODIFIER: {
                        if (effect->timer-- == 0) {
                            m->capTimer = 150;
                            m->flags &= ~(MARIO_NORMAL_CAP | MARIO_VANISH_CAP | MARIO_METAL_CAP | MARIO_WING_CAP | MARIO_CAP_ON_HEAD | MARIO_CAP_IN_HAND);
                            m->flags |= (random_u16() & (MARIO_NORMAL_CAP | MARIO_VANISH_CAP | MARIO_METAL_CAP | MARIO_WING_CAP));
                            m->flags |= ((random_u16() & 1) ? MARIO_CAP_ON_HEAD : MARIO_CAP_IN_HAND);
                            effect->timer = 149;
                        }
                    } break;

                    // Every 3 seconds, change Mario's model
                    case CHAOS_PLAY_AS: {
                        if (effect->timer-- == 0) {
                            effect->value = (s32) (1 + (random_u16() % 7));
                            effect->timer = 89;
                        }
                        Cheats.ChaosPlayAs = effect->value;
                    } break;

                    // Releasio physics
                    // If forward vel > 15, set it to 200
                    // If B or Z is pressed, set forward vel to -4000
                    case CHAOS_RELEASIO: {
                        if (gPlayer1Controller->buttonDown & (B_BUTTON | Z_TRIG)) {
                            m->forwardVel = -4000.f;
                        } else if (m->forwardVel > 15.f) {
                            m->forwardVel = 200.f;
                        }
                    } break;

                    // Swim anywhere
                    case CHAOS_SWIM_ANYWHERE: {
                        if (!insideCastle) {
                            Cheats.ChaosSwimAnywhere = TRUE;
                        }
                    } break;

                    // Every non-object floor is lava
                    // Does only the lava boost, don't deal damage
                    case CHAOS_FLOOR_IS_LAVA: {
                        if (!insideCastle) {
                            if (m->floor && !m->floor->object && m->pos[1] < m->floorHeight + 8.f) {
                                if ((m->action & ACT_GROUP_MASK) != ACT_GROUP_SUBMERGED &&
                                    (m->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE &&
                                    (m->action & ACT_GROUP_MASK) != ACT_GROUP_AUTOMATIC &&
                                    (!(m->action & ACT_FLAG_AIR) || (m->action == ACT_LAVA_BOOST))) {
                                    drop_and_set_mario_action(m, ACT_LAVA_BOOST, 0);
                                }
                            }
                        }
                    } break;

                    // Colliding with an object results in instant quicksand
                    // Doors, warps, wind, poles, trees, hoot, NPCs and stars are not affected
                    case CHAOS_DEADLY_OBJECTS: {
                        if (!insideCastle) {
                            static const u32 deadlyTypes = (
                                INTERACT_GRABBABLE |
                                INTERACT_DAMAGE |
                                INTERACT_COIN |
                                INTERACT_CAP |
                                INTERACT_KOOPA |
                                INTERACT_UNKNOWN_08 |
                                INTERACT_BREAKABLE |
                                INTERACT_CANNON_BASE |
                                INTERACT_BOUNCE_TOP |
                                INTERACT_BULLY |
                                INTERACT_FLAME |
                                INTERACT_KOOPA_SHELL |
                                INTERACT_BOUNCE_TOP2 |
                                INTERACT_MR_BLIZZARD |
                                INTERACT_HIT_FROM_BELOW |
                                INTERACT_CLAM_OR_BUBBA |
                                INTERACT_SNUFIT_BULLET |
                                INTERACT_SHOCK
                            );
                            if (m->action != ACT_QUICKSAND_DEATH && (m->collidedObjInteractTypes & deadlyTypes) != 0) {
                                drop_and_set_mario_action(m, ACT_QUICKSAND_DEATH, 0);
                            }
                        }
                    } break;

                    // No bounds
                    case CHAOS_NO_BOUNDS: {
                        Cheats.ChaosNoBounds = TRUE;
                    } break;

                    // Randomly lower or raise the water level
                    case CHAOS_WATER_LEVEL: {
                        if (effect->timer-- == 0) {
                            effect->value = (s32) (random_sign() * (2.01f + random_float()) * 5.f);
                            effect->timer = 90 + (random_u16() % 90);
                        }
                        s16 *p = gEnvironmentRegions;
                        if (p != NULL) {
                            s32 n = p[0];
                            for (s32 i = 0; i != n; ++i) {
                                s16 *env = &p[1 + (i * 6)];
                                env[1] = -0x7FFF;
                                env[2] = -0x7FFF;
                                env[3] = +0x7FFF;
                                env[4] = +0x7FFF;
                                env[5] += effect->value;
                            }
                        }
                    } break;

                    // Attract all objects to Mario
                    case CHAOS_OBJECT_MAGNET: {
                        if (!(gTimeStopState & TIME_STOP_ENABLED)) {
                            static const s32 sObjectLists[] = {
                                OBJ_LIST_DESTRUCTIVE,
                                OBJ_LIST_GENACTOR,
                                OBJ_LIST_PUSHABLE,
                                OBJ_LIST_LEVEL,
                                OBJ_LIST_DEFAULT,
                                OBJ_LIST_SURFACE,
                                OBJ_LIST_POLELIKE,
                                -1
                            };
                            for (s32 *list = sObjectLists; *list != -1; list++) {
                                struct Object *head = (struct Object *) &gObjectLists[*list];
                                for (struct Object *obj = (struct Object *) head->header.next; obj != head; obj = (struct Object *) obj->header.next) {
                                    Vec3f dv = {
                                        obj->oPosX - m->pos[0],
                                        obj->oPosY - m->pos[1],
                                        obj->oPosZ - m->pos[2],
                                    };
                                    f32 distToObj = vec3f_length(dv);
                                    if (distToObj > 0.f) {
                                        vec3f_normalize(dv);
                                        obj->oPosX -= dv[0] * 15.f;
                                        obj->oPosY -= dv[1] * 15.f;
                                        obj->oPosZ -= dv[2] * 15.f;
                                    }
                                }
                            }
                        }
                    } break;

                    // During Slow time, the whole world (except Mario) is running at half speed
                    case CHAOS_SLOW_TIME: {
                        Cheats.ChaosSlowTime = TRUE;
                    } break;

                    // Trigger a random 'Hurt Mario' effect when B is pressed
                    // Deal damage corresponding to the effect
                    case CHAOS_HURT_MARIO: {
                        if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                            static const s32 sHurtRandoms[3][6] = {
                                { 0, 3, 6, 7, 8, 9 }, // Ground
                                { 1, 4, 6, 7, 8, 9 }, // Airborne
                                { 2, 5, 2, 5, 8, 9 }, // Underwater
                            };
                            s32 hurtEffect;
                            if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
                                hurtEffect = sHurtRandoms[2][random_u16() % 6];
                            } else if (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) {
                                hurtEffect = sHurtRandoms[1][random_u16() % 6];
                            } else {
                                hurtEffect = sHurtRandoms[0][random_u16() % 6];
                            }
                            switch (hurtEffect) {

                                // Knockback ground
                                case 0: {
                                    m->hurtCounter += 8;
                                    spawn_object(m->marioObj, MODEL_EXPLOSION, bhvExplosion);
                                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION | 0xFF00, m->marioObj->header.gfx.cameraToObject);
                                    drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_HARD_FORWARD_GROUND_KB : ACT_HARD_BACKWARD_GROUND_KB, 1);
                                } break;

                                // Knockback airborne
                                case 1: {
                                    m->hurtCounter += 8;
                                    spawn_object(m->marioObj, MODEL_EXPLOSION, bhvExplosion);
                                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION | 0xFF00, m->marioObj->header.gfx.cameraToObject);
                                    drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_HARD_FORWARD_AIR_KB : ACT_HARD_BACKWARD_AIR_KB, 1);
                                } break;

                                // Knockback underwater
                                case 2: {
                                    m->hurtCounter += 8;
                                    spawn_object(m->marioObj, MODEL_EXPLOSION, bhvExplosion);
                                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION | 0xFF00, m->marioObj->header.gfx.cameraToObject);
                                    drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_FORWARD_WATER_KB : ACT_BACKWARD_WATER_KB, 1);
                                } break;
                                
                                // Shocked ground
                                case 3: {
                                    m->hurtCounter += 4;
                                    drop_and_set_mario_action(m, ACT_SHOCKED, 1);
                                } break;
                                
                                // Shocked airborne
                                case 4: {
                                    m->hurtCounter += 4;
                                    drop_and_set_mario_action(m, ACT_SHOCKED, 0);
                                } break;
                                
                                // Shocked underwater
                                case 5: {
                                    m->hurtCounter += 4;
                                    drop_and_set_mario_action(m, ACT_WATER_SHOCKED, 0);
                                } break;

                                // Burnt
                                case 6: {
                                    m->marioObj->oMarioBurnTimer = 0;
                                    update_mario_sound_and_camera(m);
                                    r96_play_character_sound(m, R96_MARIO_ON_FIRE, R96_LUIGI_ON_FIRE, R96_WARIO_ON_FIRE);
                                    drop_and_set_mario_action(m, ACT_BURNING_JUMP, 1);
                                } break;
                                
                                // Lava boost
                                case 7: {
                                    m->hurtCounter += 12;
                                    drop_and_set_mario_action(m, ACT_LAVA_BOOST, 0);
                                } break;
                                
                                // Squished
                                case 8: {
                                    m->hurtCounter += 12;
                                    drop_and_set_mario_action(m, ACT_SQUISHED, 0);
                                    r96_play_character_sound(m, R96_MARIO_ATTACKED, R96_LUIGI_ATTACKED, R96_WARIO_ATTACKED);
                                    vec3f_set(m->marioObj->header.gfx.scale, 1.8f, 0.05f, 1.8f);
                                    m->particleFlags |= PARTICLE_MIST_CIRCLE;
                                    m->squishTimer = 0xFF;
                                    m->actionState = 1;
                                } break;
                                
                                // Stuck in ground
                                case 9: {
                                    switch (random_u16() % 3) {
                                        case 0: drop_and_set_mario_action(m, ACT_HEAD_STUCK_IN_GROUND, 0); break;
                                        case 1: drop_and_set_mario_action(m, ACT_BUTT_STUCK_IN_GROUND, 0); break;
                                        case 2: drop_and_set_mario_action(m, ACT_FEET_STUCK_IN_GROUND, 0); break;
                                    }
                                    r96_play_character_sound(m, R96_MARIO_OOOF, R96_LUIGI_OOOF, R96_WARIO_OOOF);
                                    m->particleFlags |= PARTICLE_MIST_CIRCLE;
                                } break;
                            }
                        }
                    } break;

                    // Display the current effects
                    // Duration is always 120 seconds
                    case CHAOS_DISPLAY: {
                        cheats_chaos_init_effect(
                            play_sound(SOUND_MENU_MARIO_CASTLE_WARP2 | 0xFF00, gDefaultSoundArgs);
                            effect->duration = 3600;
                        );
                        if (effect->duration > 0 && (effect->duration >= 64 || ((1ULL << effect->duration) & sCapFlickerFrames) == 0)) {
                            s32 y = 48;
                            for (s32 duration = CHEATS_CHAOS_DURATION_MAX; duration > 0; --duration) {
                                for (s32 i = 0; i != 8; ++i) {
                                    if (sChaosEffects[i].index != CHAOS_DISPLAY && sChaosEffects[i].duration == duration) {
                                        char key[64]; sprintf(key, "TEXT_OPT_CHEAT_CHAOS_%s", sChaosNames[sChaosEffects[i].index]);
                                        char str[64]; sprintf(str, "%2d %s", (sChaosEffects[i].duration + 29) / 30, cheats_spamba_u8str_to_charstr(get_key_string(key)));
                                        print_text(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), y, str);
                                        y += 16;
                                    }
                                }
                            }
                        }
                    } break;

                    // Turn off G_LIGHTING to interpret vertex normals as colors
                    case CHAOS_RAINBOW: {
                        Cheats.ChaosRainbow = TRUE;
                    } break;

                    // Invert the screen horizontally (1), vertically (2), or both (3)
                    // Duration is reduced to 15~25 seconds
                    case CHAOS_INVERTED_SCREEN: {
                        cheats_chaos_init_effect(
                            effect->duration -= 300;
                            effect->value = (1 + (random_u16() % 3));
                        );
                        Cheats.ChaosInvertedScreen = effect->value;
                    } break;

                    // Turn on wireframe mode
                    case CHAOS_WIREFRAME: {
                        Cheats.ChaosWireframe = TRUE;
                    } break;

                    // Spurt yellow/red/blue coins every 5 frames
                    // Duration is reduced to 5~15 seconds
                    case CHAOS_JACKPOT: {
                        cheats_chaos_init_effect(
                            effect->duration -= 600;
                        );
                        if (effect->timer-- == 0) {
                            play_sound(SOUND_GENERAL_COIN_SPURT, m->marioObj->header.gfx.cameraToObject);
                            switch (random_u16() % 9) {
                                case 0: cheats_spamba_spawn_object(m, SPAMBA_YELLOW_COIN, 0, 160, 0, 0); break;
                                case 1: cheats_spamba_spawn_object(m, SPAMBA_BLUE_COIN, 0, 160, 0, 0); break;
                                case 2: cheats_spamba_spawn_object(m, SPAMBA_YELLOW_COIN, 0, 160, 0, 0); break;
                                case 3: cheats_spamba_spawn_object(m, SPAMBA_YELLOW_COIN, 0, 160, 0, 0); break;
                                case 4: cheats_spamba_spawn_object(m, SPAMBA_RED_COIN, 0, 160, 0, 0); break;
                                case 5: cheats_spamba_spawn_object(m, SPAMBA_YELLOW_COIN, 0, 160, 0, 0); break;
                                case 6: cheats_spamba_spawn_object(m, SPAMBA_YELLOW_COIN, 0, 160, 0, 0); break;
                                case 7: cheats_spamba_spawn_object(m, SPAMBA_BLUE_COIN, 0, 160, 0, 0); break;
                                case 8: cheats_spamba_spawn_object(m, SPAMBA_YELLOW_COIN, 0, 160, 0, 0); break;
                            }
                            effect->timer = 4;
                        }
                    } break;

                    // Every 6 seconds, spawn a mushroom that follows Mario and kills him if he collects it
                    // When Green Demon ends, the mushrooms turn back into 1-ups
                    case CHAOS_GREEN_DEMON: {
                        if (!insideCastle) {
                            if (effect->timer-- == 0) {
                                cheats_spamba_spawn_object(m, SPAMBA_MUSHROOM_1UP, 0, 200, 0, 0);
                                effect->timer = 179;
                            }
                            Cheats.ChaosGreenDemon = TRUE;
                        }
                    } break;

                    // Spawn a random star in a random location of the map
                    // The star despawns when the effect ends
                    case CHAOS_STAR: {
                        if (!insideCastle) {
                            static struct Object *sChaosStar = NULL;
                            cheats_chaos_init_effect(
                                f32 x, z, y;
                                struct Surface *floor = NULL;
                                while (!floor) {
                                    x = random_float() * random_sign() * LEVEL_BOUNDARY_MAX;
                                    z = random_float() * random_sign() * LEVEL_BOUNDARY_MAX;
                                    y = find_floor(x, 20000.f, z, &floor);
                                    if (floor && (
                                        floor->type == SURFACE_BURNING ||
                                        floor->type == SURFACE_DEATH_PLANE ||
                                        floor->type == SURFACE_VERTICAL_WIND)) {
                                        floor = NULL;
                                    }
                                }
                                
                                sChaosStar = spawn_object(m->marioObj, MODEL_NONE, bhvStarSpawnCoordinates);
                                sChaosStar->oPosX = m->pos[0];
                                sChaosStar->oPosY = m->pos[1] + 200.f;
                                sChaosStar->oPosZ = m->pos[2];
                                sChaosStar->oHomeX = x;
                                sChaosStar->oHomeY = y + 500.f + 500.f * random_float();
                                sChaosStar->oHomeZ = z;
                                sChaosStar->oBehParams = ((random_u16() % 7) << 24);
                                sChaosStar->oBehParams2ndByte = 0;
                                sChaosStar->oInteractionSubtype = INT_SUBTYPE_NO_EXIT;
                                obj_set_angle(sChaosStar, 0, 0, 0);
                            );
                            if (sChaosStar) {
                                if (effect->duration >= 64) {
                                    sChaosStar->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                                } else if (effect->duration == 0) {
                                    if (sChaosStar->behavior == bhvStarSpawnCoordinates) {
                                        obj_mark_for_deletion(sChaosStar);
                                        sChaosStar = NULL;
                                    }
                                } else if ((1ULL << effect->duration) & sCapFlickerFrames) {
                                    sChaosStar->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                                } else {
                                    sChaosStar->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                                }
                            }
                        }
                    } break;

                    // Spawn 3 Goombas around Mario every second
                    case CHAOS_GOOMBA_PLAGUE: {
                        if (effect->timer-- == 0) {
                            for (s32 i = 0; i != 3; ++i) {
                                s16 a = m->faceAngle[1] + (i * 0x5555);
                                f32 dx = 300.f * sins(a);
                                f32 dz = 300.f * coss(a);
                                cheats_spamba_spawn_object(m, SPAMBA_GOOMBA, dx, 40.f, dz, 1);
                            }
                            effect->timer = 29;
                        }
                    } break;

                    // Spawn falling bob-ombs every 15 frames
                    case CHAOS_BOBOMB_RAIN: {
                        if (effect->timer-- == 0) {
                            s16 a = (s16) random_u16();
                            f32 r = random_float() * 400.f;
                            f32 dx = r * sins(a);
                            f32 dz = r * coss(a);
                            struct Object *bobomb = cheats_spamba_spawn_object(m, SPAMBA_BOBOMB, dx, 500, dz, 1);
                            bobomb->oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE);
                            bobomb->oIntangibleTimer = 0;
                            bobomb->oGravity = 5.f;
                            bobomb->oFriction = 0.8f;
                            bobomb->oBuoyancy = 1.5f;
                            bobomb->oForwardVel = 0.f;
                            bobomb->oVelY = 0.f;
                            bobomb->oAction = BOBOMB_ACT_LAUNCHED;
                            bobomb->oBobombFuseTimer = 0;
                            bobomb->oBobombFuseLit = 1;
                            bobomb->oAnimations = (struct Animation **) bobomb_seg8_anims_0802396C;
                            geo_obj_init_animation(&bobomb->header.gfx, &bobomb->oAnimations[1]);
                            bobomb->curBhvCommand = bhvBobomb + 10;
                            effect->timer = 14;
                        }
                    } break;

                    // Spawn haunted chairs every 15 frames
                    case CHAOS_CHAIRS: {
                        if (effect->timer-- == 0) {
                            cheats_spamba_spawn_object(m, SPAMBA_HAUNTED_CHAIR, 0, 40, -50, 1);
                            effect->timer = 14;
                        }
                    } break;

                    // Spawn Boos/Lakitus behind Mario every 2 seconds
                    case CHAOS_STALKERS: {
                        if (effect->timer-- == 0) {
                            if (random_u16() % 3 == 0) {
                                cheats_spamba_spawn_object(m, SPAMBA_BOO, 0, 100, -100, 1);
                            } else {
                                cheats_spamba_spawn_object(m, SPAMBA_LAKITU, 0, 300, -200, 1);
                            }
                            effect->timer = 59;
                        }
                    } break;

                    // Spawn Snufits/Flyguys around Mario every 1.5 second
                    case CHAOS_SHOOTERS: {
                        if (effect->timer-- == 0) {
                            s16 a = (s16) random_u16();
                            f32 dx = 300.f * sins(a);
                            f32 dz = 300.f * coss(a);
                            if (random_u16() % 3 == 0) {
                                cheats_spamba_spawn_object(m, SPAMBA_FLYGUY, dx, 200, dz, 1);
                            } else {
                                cheats_spamba_spawn_object(m, SPAMBA_SNUFIT, dx, 150, dz, 1);
                            }
                            effect->timer = 44;
                        }
                    } break;

                    // If Mario stays more than 1 second on ground, spawn a Chuckya/Heave-ho
                    case CHAOS_CHUCKSTERS: {
                        if (onGround && !(m->action & ACT_FLAG_INVULNERABLE)) {
                            if (++effect->timer >= 30) {
                                s16 a = (s16) random_u16();
                                f32 dx = 100.f * sins(a);
                                f32 dz = 100.f * coss(a);
                                if (random_u16() & 1) {
                                    cheats_spamba_spawn_object(m, SPAMBA_HEAVE_HO, dx, 40.f, dz + m->forwardVel, true);
                                } else {
                                    cheats_spamba_spawn_object(m, SPAMBA_CHUCKYA, dx, 40.f, dz + m->forwardVel, true);
                                }
                                effect->timer = 0;
                            }
                        } else {
                            effect->timer = 0;
                        }
                    } break;

                    // Every 2 seconds, spawn one of the following: Bowling ball, HMC rock, Circling Amp
                    case CHAOS_DODGEBALL: {
                        if (effect->timer-- == 0) {
                            switch (random_u16() % 3) {
                                case 0: cheats_spamba_spawn_object(m, SPAMBA_BOWLING_BALL, 0, 400, 0, 0); break;
                                case 1: cheats_spamba_spawn_object(m, SPAMBA_BIG_BOULDER, 0, 40, -600, 1); break;
                                case 2: cheats_spamba_spawn_object(m, SPAMBA_CIRCLING_AMP, 0, 120, 0, 0); break;
                            }
                            effect->timer = 59;
                        }
                    } break;

                    // Spawn King Bob-omb, King Whomp, Big Boo, Big Bully, Big Chill Bully, Eyerock and Wiggler around Mario
                    case CHAOS_BOSS_FIGHT: {
                        if (onGround && !insideCastle) {
                            cheats_chaos_init_effect(
                                cheats_spamba_spawn_object(m, SPAMBA_KING_BOBOMB,     400 * sins(0x0000), 40, 400 * coss(0x0000), true);
                                cheats_spamba_spawn_object(m, SPAMBA_KING_WHOMP,      500 * sins(0x2492), 40, 500 * coss(0x2492), true);
                                cheats_spamba_spawn_object(m, SPAMBA_BIG_BOO,         400 * sins(0x4924), 40, 400 * coss(0x4924), true);
                                cheats_spamba_spawn_object(m, SPAMBA_BIG_BULLY,       500 * sins(0x6DB6), 40, 500 * coss(0x6DB6), true);
                                cheats_spamba_spawn_object(m, SPAMBA_BIG_CHILL_BULLY, 500 * sins(0x9248), 40, 500 * coss(0x9248), true);
                                cheats_spamba_spawn_object(m, SPAMBA_EYEROCK,         400 * sins(0xB6DA), 40, 400 * coss(0xB6DA), true);
                                cheats_spamba_spawn_object(m, SPAMBA_WIGGLER,         500 * sins(0xDB6C), 40, 500 * coss(0xDB6C), true);
                            );
                        }
                    } break;

                    // Spawn Bowser every 5 seconds in front of Mario
                    case CHAOS_BOWSER_TIME: {
                        if (effect->timer-- == 0) {
                            cheats_spamba_spawn_object(m, SPAMBA_BOWSER, 0, 40, 600, 1);
                            effect->timer = 149;
                        }
                        Cheats.ChaosBowserTime = TRUE;
                    } break;

                    // Spawn Hoot and make Mario instantly grab it, but he cannot release it during the ascending state
                    case CHAOS_HOOT: {
                        if (!insideCastle) {
                            cheats_chaos_init_effect(
                                mario_stop_riding_and_holding(m);
                                struct Object *hoot = cheats_spamba_spawn_object(m, SPAMBA_HOOT, 0, 160, 0, 0);
                                hoot->oInteractStatus = INT_STATUS_HOOT_GRABBED_BY_MARIO;
                                m->interactObj = hoot;
                                m->usedObj = hoot;
                                update_mario_sound_and_camera(m);
                                set_mario_action(m, ACT_RIDING_HOOT, 0);
                            );
                        }
                        if (m->action == ACT_RIDING_HOOT && m->usedObj && m->usedObj->behavior == bhvHoot && m->usedObj->oAction == HOOT_ACT_ASCENT) {
                            m->controller->buttonDown |= A_BUTTON;
                            m->input |= INPUT_A_DOWN;
                        }
                    } break;

                    // Spawn 6 random NPCs (Bob-omb buddy, Toad, signpost), then force Mario to talk to them if he's on ground
                    case CHAOS_NPCS: {
                        static struct Object *sChaosNPCs[6];
                        if (onGround &&
                            m->action != ACT_READING_SIGN &&
                            m->action != ACT_WAITING_FOR_DIALOG &&
                            m->action != ACT_READING_NPC_DIALOG &&
                            m->action != ACT_READING_AUTOMATIC_DIALOG) {

                            // Init: spawn 6 NPCs around Mario
                            cheats_chaos_init_effect(
                                for (s32 i = 0; i != 6; ++i) {
                                    s16 a = i * 0x2AAA;
                                    f32 dx = 200.f * sins(a);
                                    f32 dz = 200.f * coss(a);
                                    switch (random_u16() % 3) {
                                        case 0: sChaosNPCs[i] = cheats_spamba_spawn_object(m, SPAMBA_BOBOMB_BUDDY, dx, 40, dz, 1); break;
                                        case 1: sChaosNPCs[i] = cheats_spamba_spawn_object(m, SPAMBA_SIGNPOST, dx, 40, dz, 1); break;
                                        case 2: sChaosNPCs[i] = cheats_spamba_spawn_object(m, SPAMBA_TOAD, dx, 40, dz, 1); break;
                                    }
                                }
                                effect->value = 0;
                                break;
                            );
                            
                            // Force Mario to talk to each NPC
                            if (effect->value < 6) {
                                struct Object *npc = sChaosNPCs[effect->value++];
                                mario_stop_riding_and_holding(m);
                                if (npc->behavior == bhvMessagePanel) {
                                    s16 facingDYaw = (s16) (npc->oFaceAngleYaw + 0x8000) - m->faceAngle[1];
                                    f32 targetX = npc->oPosX + 105.0f * sins(npc->oFaceAngleYaw);
                                    f32 targetZ = npc->oPosZ + 105.0f * coss(npc->oFaceAngleYaw);
                                    m->marioObj->oMarioReadingSignDYaw  = facingDYaw;
                                    m->marioObj->oMarioReadingSignDPosX = targetX - m->pos[0];
                                    m->marioObj->oMarioReadingSignDPosZ = targetZ - m->pos[2];
                                    m->interactObj = npc;
                                    m->usedObj = npc;
                                    set_mario_action(m, ACT_READING_SIGN, 0);
                                } else {
                                    npc->oInteractStatus = INT_STATUS_INTERACTED;
                                    npc->oToadMessageState = 4;
                                    m->interactObj = npc;
                                    m->usedObj = npc;
                                    set_mario_action(m, ACT_WAITING_FOR_DIALOG, 0);
                                }
                            }
                        }

                        // Anti-softlock
                        if (m->action == ACT_WAITING_FOR_DIALOG) {
                            effect->timer++;
                            if (effect->timer > 60) {
                                effect->timer = 0;
                                set_mario_action(m, ACT_IDLE, 0);
                            }
                        } else {
                            effect->timer = 0;
                        }
                    } break;

                    // Spawn a breakable box below Mario every time A is pressed
                    case CHAOS_MINECRAFT: {
                        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                            cheats_spamba_spawn_object(m, SPAMBA_BREAKABLE_BOX, 0, -200, 0, 0);
                        }
                    } break;

                    // Spawn a random exclamation box (or a Thwomp/Grindel) above Mario every time A is pressed, only if there is no floor above his head
                    case CHAOS_SURPRISE: {
                        if (!insideCastle) {
                            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                                if (find_floor_height(m->pos[0], m->pos[1] + 1000.f, m->pos[2]) <= m->pos[1]) {
                                    switch (random_u16() % 10) {

                                        // Coins (40%)
                                        case 0: case 1: case 2: case 3: {
                                            switch (random_u16() % 6) {
                                                case 0: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_ONE_COIN, 0, 250, 0, 0); break;
                                                case 1: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_ONE_COIN, 0, 250, 0, 0); break;
                                                case 2: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_ONE_COIN, 0, 250, 0, 0); break;
                                                case 3: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_THREE_COINS, 0, 250, 0, 0); break;
                                                case 4: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_THREE_COINS, 0, 250, 0, 0); break;
                                                case 5: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_TEN_COINS, 0, 250, 0, 0); break;
                                            }
                                        } break;

                                        // Items (30%)
                                        case 4: case 5: case 6: {
                                            switch (random_u16() % 5) {
                                                case 0: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_WING_CAP, 0, 250, 0, 0); break;
                                                case 1: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_METAL_CAP, 0, 250, 0, 0); break;
                                                case 2: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_VANISH_CAP, 0, 250, 0, 0); break;
                                                case 3: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_KOOPA_SHELL, 0, 250, 0, 0); break;
                                                case 4: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_MUSHROOM_1UP, 0, 250, 0, 0); break;
                                            }
                                        } break;

                                        // Crushers (20%)
                                        case 7: case 8: {
                                            switch (random_u16() % 2) {
                                                case 0: cheats_spamba_spawn_object(m, SPAMBA_THWOMP, 0, 250, 0, 0)->oAction = 2; break;
                                                case 1: cheats_spamba_spawn_object(m, SPAMBA_GRINDEL, 0, 250, 0, 0)->oAction = 2; break;
                                            }
                                        } break;

                                        // Stars (10%)
                                        case 9: {
                                            switch (random_u16() % 6) {
                                                case 0: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_STAR_1, 0, 250, 0, 0); break;
                                                case 1: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_STAR_2, 0, 250, 0, 0); break;
                                                case 2: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_STAR_3, 0, 250, 0, 0); break;
                                                case 3: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_STAR_4, 0, 250, 0, 0); break;
                                                case 4: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_STAR_5, 0, 250, 0, 0); break;
                                                case 5: cheats_spamba_spawn_object(m, SPAMBA_EXCLAMATION_BOX_STAR_6, 0, 250, 0, 0); break;
                                            }
                                        } break;
                                    }
                                }
                            }
                        }
                    } break;
                }
            }
        }
        
        // Display next effect and remaining time before this effect activates
        if (sChaosCooldown <= 150 && sChaosNextEffect != -1) {
            char key[64]; sprintf(key, "TEXT_OPT_CHEAT_CHAOS_%s", sChaosNames[sChaosNextEffect]);
            char str[64]; sprintf(str, "%s %d", cheats_spamba_u8str_to_charstr(get_key_string("TEXT_OPT_CHEAT_CHAOS_TEXT")), (sChaosCooldown + 29) / 30);
            print_text(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 24, str);
            print_text(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 8, cheats_spamba_u8str_to_charstr(get_key_string(key)));
        }
    } else {
        memset(Cheats.Chaos, 0, sizeof(Cheats.Chaos));
        memset(sChaosEffects, 0, sizeof(sChaosEffects));
        sChaosNextEffect = -1;
        sChaosCooldown = 0;
    }
    return FALSE;
}
