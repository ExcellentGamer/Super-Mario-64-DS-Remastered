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

static void bhv_sm64ds_star_spawn_condition_init() {
    struct Object *o = gCurrentObject;
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
    struct Surface *s;
    f32 floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &s);
    if (s) {
        o->oPosY = floorHeight + 30.f;
        o->oFloorHeight = floorHeight;
    }
    obj_scale_xyz(o, 1.5f, 1.5f, 0.75f);
}

static void bhv_sm64ds_star_spawn_condition_loop() {
    struct Object *o = gCurrentObject;
    switch (o->oAction) {

        // Star not spawned
        case 0: {
        } break;

        // Spawn star
        case 1: {
            struct Object *star = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStarSpawnCoordinates, o->oHomeX, o->oHomeY, o->oHomeZ, 0, 0, 0);
            star->oBehParams = o->oBehParams;
            star->oHomeX = o->oHomeX;
            star->oHomeY = o->oHomeY;
            star->oHomeZ = o->oHomeZ;
            star->oFaceAnglePitch = 0;
            star->oFaceAngleRoll = 0;
            star->oBehParams2ndByte = 1;
            o->oAction = 2;
            o->parentObj = star;
        } break;

        // Star spawned
        case 2: {
        } break;

        // Despawn star
        case 3: {
            struct Object *star = o->parentObj;
            if (star && star->activeFlags && star->behavior == bhvStarSpawnCoordinates) {
                gCurrentObject = star;
                spawn_mist_particles();
                gCurrentObject = o;
                obj_mark_for_deletion(star);
            }
            o->oAction = 0;
        } break;
    }
    o->oFaceAngleYaw += 0x100;
}

const BehaviorScript bhvSm64DsStarSpawnCondition[] = {
    0x11010001,
    0x10124000,
    0x0C000000, (uintptr_t) bhv_sm64ds_star_spawn_condition_init,
    0x08000000,
    0x0C000000, (uintptr_t) bhv_sm64ds_star_spawn_condition_loop,
    0x09000000,
};
