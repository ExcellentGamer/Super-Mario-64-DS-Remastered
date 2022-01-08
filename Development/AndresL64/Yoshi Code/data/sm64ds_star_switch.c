#include "sm64ds_behaviors.h"
#include "actors/common0.h"
#include "game/object_list_processor.h"
#include "object_fields.h"
#include "object_constants.h"
#include "game/object_helpers.h"
#include "engine/surface_load.h"
#include "model_ids.h"
#include "game/level_update.h"
#include "course_table.h"
#include "game/spawn_sound.h"
#include "game/spawn_object.h"
#include "audio/external.h"
#include "engine/behavior_script.h"
#include "engine/surface_collision.h"
#include "behavior_data.h"
#include "game/interaction.h"
#include "sm64.h"

static void bhv_sm64ds_star_switch_loop() {
    struct Object *o = gCurrentObject;
    switch (o->oAction) {
        case PURPLE_SWITCH_IDLE: {
            cur_obj_scale(1.f);
            if (gMarioObject->platform == o && !(gMarioStates->action & MARIO_UNKNOWN_13)) {
                if (lateral_dist_between_objects(o, gMarioObject) < 80.f) {
                    o->oAction = PURPLE_SWITCH_PRESSED;
                }
            }
        } break;

        case PURPLE_SWITCH_PRESSED: {
            cur_obj_scale_over_time(2, 3, 1.f, 0.2f);
            if (o->oTimer >= 3) {
                f32 dist;
                struct Object *star = cur_obj_find_nearest_object_with_behavior(bhvSm64DsStarSpawnCondition, &dist);
                if (star) {
                    star->oAction = 1;
                }
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
                o->oAction = PURPLE_SWITCH_TICKING;
                o->oTimer = 0;
            }
        } break;

        case PURPLE_SWITCH_TICKING: {
            s32 maxDuration = (o->oBehParams2ndByte * 30);
            if (o->oTimer >= maxDuration) {
                f32 dist;
                struct Object *star = cur_obj_find_nearest_object_with_behavior(bhvSm64DsStarSpawnCondition, &dist);
                if (star) {
                    star->oAction = 3;
                }
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF;
            } else if (o->oTimer >= maxDuration - 60) {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gDefaultSoundArgs);
            } else if (o->oTimer > 10) {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gDefaultSoundArgs);
            }
        } break;

        case PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF: {
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_UNPRESSED;
            }
        } break;

        case PURPLE_SWITCH_UNPRESSED: {
            cur_obj_scale_over_time(2, 3, 0.2f, 1.f);
            if (o->oTimer >= 3) {
                o->oAction = PURPLE_SWITCH_IDLE;
            }
        } break;
    }
}

const BehaviorScript bhvSm64DsStarSwitch[] = {
    0x00090000,
    0x11010001,
    0x2A000000, (uintptr_t) purple_switch_seg8_collision_0800C7A8,
    0x08000000,
    0x0C000000, (uintptr_t) bhv_sm64ds_star_switch_loop,
    0x0C000000, (uintptr_t) load_object_collision_model,
    0x09000000,
};
