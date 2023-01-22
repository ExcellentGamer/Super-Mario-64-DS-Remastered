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
#include "game/print.h"
#include "gfx_dimensions.h"

static void bhv_sm64ds_silver_star_handler_loop() {
    struct Object *o = gCurrentObject;
    o->oPosX = gMarioState->pos[0];
    o->oPosY = gMarioState->pos[1];
    o->oPosZ = gMarioState->pos[2];

    // Count remaining silver stars
    s32 remainingSilverStars = 0;
    struct Object *head = (struct Object *) &gObjectLists[OBJ_LIST_LEVEL];
    for (struct Object *obj = (struct Object *) head->header.next; obj != head; obj = (struct Object *) obj->header.next) {
        if (obj->behavior == bhvSm64DsSilverStar) {
            remainingSilverStars++;
        }
    }

    // Drop a silver star if damaged
    if (remainingSilverStars < 5 && gMarioState->hurtCounter > o->oAction) {
        struct Object *silverStar = spawn_object(o, MODEL_STAR, bhvSm64DsSilverStar);
        silverStar->oVelX = ((random_u16() & 1) ? -1.f : 1.f) * 12.f;
        silverStar->oVelY = 30.f;
        silverStar->oVelZ = ((random_u16() & 1) ? -1.f : 1.f) * 12.f;
        silverStar->oBehParams = 0x00010000;
        silverStar->oBehParams2ndByte = 1;
        remainingSilverStars++;
    }
    o->oAction = gMarioState->hurtCounter;

    // Spawn the power star if Mario collects 5 silver stars,
    // or despawn it if he loses one
    f32 dist;
    struct Object *star = cur_obj_find_nearest_object_with_behavior(bhvSm64DsStarSpawnCondition, &dist);
    if (star) {
        if (star->oAction == 0 && remainingSilverStars == 0) {
            star->oAction = 1;
        } else if (star->oAction == 2 && remainingSilverStars != 0) {
            star->oAction = 3;
        }
    }
    o->oSubAction = remainingSilverStars;

    // Display the number of silver stars collected below the star counter
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(78), 191, "-");
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(78) + 16, 191, "*");
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(78) + 32, 191, "%d", 5 - remainingSilverStars);
}

static const BehaviorScript bhvSm64DsSilverStarHandler[] = {
    0x08000000,
    0x0C000000, (uintptr_t) bhv_sm64ds_silver_star_handler_loop,
    0x09000000,
};

static struct ObjectHitbox sSm64DsSilverStarHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 40,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

static void bhv_sm64ds_silver_star_init() {
    struct Object *o = gCurrentObject;
    obj_scale(o, 0.8f);
    obj_set_hitbox(o, &sSm64DsSilverStarHitbox);
    o->oAction = o->oBehParams2ndByte;
    switch (o->oBehParams2ndByte) {

        // Still
        case 0: {
            o->oHomeX = o->oPosX;
            o->oHomeY = o->oPosY;
            o->oHomeZ = o->oPosZ;
            o->oVelX = 0;
            o->oVelY = 0;
            o->oVelZ = 0;
        } break;
            
        // Roaming
        case 1: {
            o->oHomeX = o->oPosX;
            o->oHomeY = o->oPosY;
            o->oHomeZ = o->oPosZ;
        } break;
        
        // Goomba
        case 2: {
            o->parentObj = spawn_object(o, MODEL_GOOMBA, bhvGoomba);
        } break;
    }
}

extern int detect_object_hitbox_overlap(struct Object *, struct Object *);
static void bhv_sm64ds_silver_star_loop() {
    struct Object *o = gCurrentObject;
    o->oFaceAngleYaw += 0x800;
    switch (o->oAction) {

        // Still
        case 0: {
            cur_obj_unhide();
            cur_obj_become_tangible();
        } break;
            
        // Roaming
        case 1: {
            cur_obj_unhide();
            cur_obj_become_tangible();
            o->oVelY = MAX(o->oVelY - 1.5f, -30.f);
            o->oPosX += o->oVelX;
            o->oPosY += o->oVelY;
            o->oPosZ += o->oVelZ;

            // Wall detection
            struct WallCollisionData wallbox;
            wallbox.x = o->oPosX;
            wallbox.y = o->oPosY - o->hitboxDownOffset;
            wallbox.z = o->oPosZ;
            wallbox.offsetY = o->hitboxHeight / 2;
            wallbox.radius = o->hitboxRadius;
            if (find_wall_collisions(&wallbox) != 0) {
                o->oPosX = wallbox.x;
                o->oPosY = wallbox.y;
                o->oPosZ = wallbox.z;
                o->oVelX = -o->oVelX;
                o->oVelZ = -o->oVelZ;
            }

            // Floor collision
            struct Surface *floor = NULL;
            f32 posY = o->oPosY - o->hitboxDownOffset;
            f32 floorY = find_floor(o->oPosX, posY, o->oPosZ, &floor);
            if (!floor) {
    
                // Out of bounds
                // Respawn at home
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;

            } else if (posY < floorY) {
                if (floor->type == SURFACE_DEATH_PLANE) {
        
                    // Death barrier reached
                    // Respawn at home
                    o->oPosX = o->oHomeX;
                    o->oPosY = o->oHomeY;
                    o->oPosZ = o->oHomeZ;
                } else {
        
                    // If the silver star hits the floor,
                    // bounces it up in a random horizontal direction
                    play_sound(SOUND_GENERAL_SHORT_STAR, o->header.gfx.cameraToObject);
                    o->oVelX = ((random_u16() & 1) ? -1.f : 1.f) * random_float() * 8.f;
                    o->oVelY = 30.f;
                    o->oVelZ = ((random_u16() & 1) ? -1.f : 1.f) * random_float() * 8.f;
                    o->oPosY = floorY + o->hitboxDownOffset;
                }
            }
        } break;
        
        // Goomba
        case 2: {
            cur_obj_hide();
            cur_obj_become_intangible();
            struct Object *goomba = o->parentObj;
            if (!goomba->activeFlags) {
                o->oAction = 1;
                o->oPosX = goomba->oPosX;
                o->oPosY = goomba->oPosY + 100.f;
                o->oPosZ = goomba->oPosZ;
                o->oHomeX = o->oPosX;
                o->oHomeY = o->oPosY;
                o->oHomeZ = o->oPosZ;
                o->oVelX = ((random_u16() & 1) ? -1.f : 1.f) * 12.f;
                o->oVelY = 30.f;
                o->oVelZ = ((random_u16() & 1) ? -1.f : 1.f) * 12.f;
            } else {
                o->oPosX = goomba->oPosX;
                o->oPosY = goomba->oPosY;
                o->oPosZ = goomba->oPosZ;
            }
        } break;
    }

    // Spawn handler if it doesn't exist
    f32 dist;
    struct Object *handler = cur_obj_find_nearest_object_with_behavior(bhvSm64DsSilverStarHandler, &dist);
    if (!handler) {
        handler = spawn_object(gMarioObject, MODEL_NONE, bhvSm64DsSilverStarHandler);
    }

    // Check collision with Mario
    if (o->oTimer >= 30 && o->oIntangibleTimer == 0 && detect_object_hitbox_overlap(o, gMarioObject)) {
        struct Object *orangeNumber = spawn_object_relative(6 - handler->oSubAction, 0, 0, 0, o, MODEL_NUMBER, bhvOrangeNumber);
        orangeNumber->oPosY += 25.0f;
        spawn_mist_particles_with_sound(SOUND_MENU_STAR_SOUND);
        mark_obj_for_deletion(o);
    }
}

const BehaviorScript bhvSm64DsSilverStar[] = {
    0x00060000,
    0x11010001,
    0x0C000000, (uintptr_t) bhv_sm64ds_silver_star_init,
    0x08000000,
    0x0C000000, (uintptr_t) bhv_sm64ds_silver_star_loop,
    0x09000000,
};
