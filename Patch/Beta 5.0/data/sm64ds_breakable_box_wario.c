#include "sm64ds_behaviors.h"
#include "data/r96/r96_defines.h"
#include "data/r96/system/r96_system.h"
#include "audio_defines.h"
#include "object_fields.h"
#include "actors/common0.h"
#include "engine/surface_load.h"
#include "game/behavior_actions.h"
#include "game/interaction.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "game/spawn_sound.h"

static void bhv_sm64ds_breakable_box_wario_init() {
    struct Object *o = gCurrentObject;
    if (o->oBehParams2ndByte == 0) {
        obj_scale(o, 1.5f);
    } else {
        obj_scale(o, o->oBehParams2ndByte / 16.f);
    }
    o->oCollisionDistance = 500.f * o->header.gfx.scale[0];
    o->oAnimState = 1;
}

extern struct ObjectHitbox sBreakableBoxHitbox;
static void bhv_sm64ds_breakable_box_wario_loop() {
    struct Object *o = gCurrentObject;
    obj_set_hitbox(o, &sBreakableBoxHitbox);
    if (cur_obj_was_attacked_or_ground_pounded() != 0) {
        if (getCharacterType() == WARIO) {
            obj_explode_and_spawn_coins(46.f, 0);
            create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        } else {
            create_sound_spawner(SOUND_ACTION_HIT);
        }
    }
}

const BehaviorScript bhvSm64DsBreakableBoxWario[] = {
    0x00090000,
    0x11010001,
    0x2A000000, (uintptr_t) breakable_box_seg8_collision_08012D70,
    0x0C000000, (uintptr_t) bhv_sm64ds_breakable_box_wario_init,
    0x0C000000, (uintptr_t) bhv_init_room,
    0x08000000,
    0x0C000000, (uintptr_t) bhv_sm64ds_breakable_box_wario_loop,
    0x0C000000, (uintptr_t) load_object_collision_model,
    0x09000000,
};
