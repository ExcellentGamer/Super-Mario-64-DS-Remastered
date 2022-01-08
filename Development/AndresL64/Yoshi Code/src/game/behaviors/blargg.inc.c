#include <stdbool.h>
#include "engine/math_util.h"

// Animation ID
#define	ANM_swim	0
#define ANM_attack	1

// Enemy mode
#define MODE_SWIM 0
#define MODE_CHASE 1
#define MODE_KNOCKBACK 2
#define MODE_BACKUP 3

// bully.c.inc

static struct ObjectHitbox sBlaargHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 300,
    /* height:            */ 235,
    /* hurtboxRadius:     */ 300,
    /* hurtboxHeight:     */ 110,
};

void bhv_blargg_init(void) {
    cur_obj_init_animation(ANM_swim);

    o->oHomeX = o->oPosX;
    o->oHomeZ = o->oPosZ;
    o->oGravity = 4.0;
    o->oFriction = 0.91;
    o->oBuoyancy = 1.3;

    obj_set_hitbox(o, &sBlaargHitbox);
}

void blargg_check_mario_collision(void) {
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        cur_obj_play_sound_2(SOUND_MOVING_LAVA_BURN);
        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        o->oAction = MODE_KNOCKBACK;
        o->oFlags &= ~0x8; /* bit 3 */
        cur_obj_init_animation(ANM_swim);
        o->oBullyMarioCollisionAngle = o->oMoveAngleYaw;
    }
}

void blargg_act_swim(){
o->oForwardVel = 5.0;
    if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 800) == 1 && gMarioState->floor->type != 0) {
        o->oAction = MODE_CHASE;
    }
}

void blargg_act_chase_mario(void) {
    f32 homeX = o->oHomeX;
    f32 posY = o->oPosY;
    f32 homeZ = o->oHomeZ;

    o->oFlags |= 0x8;
    o->oMoveAngleYaw = o->oFaceAngleYaw;
    obj_turn_toward_object(o, gMarioObject, 16, 4096);

    o->oForwardVel = (gMarioState->riddenObj == NULL) ? 10 : 40;

    bhv_koopa_shell_flame_spawn();
    if (!is_point_within_radius_of_mario(homeX, posY, homeZ, 5000) || gMarioState->floor->type == 0 || posY < o->oPosY) {
        o->oAction = MODE_SWIM;
        cur_obj_init_animation(ANM_swim);
    }
}

void blargg_act_knockback(void) {
    if (o->oForwardVel < 10.0 && (s32) o->oVelY == 0) {
        o->oForwardVel = 1.0;
        o->oBullyKBTimerAndMinionKOCounter++;
        o->oFlags |= 0x8; /* bit 3 */
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        obj_turn_toward_object(o, gMarioObject, 16, 1280);
    } else
        o->header.gfx.curAnim.animFrame = 0;

    if (o->oBullyKBTimerAndMinionKOCounter == 18) {
        o->oAction = MODE_CHASE;
        o->oBullyKBTimerAndMinionKOCounter = 0;
        cur_obj_init_animation(ANM_attack);
        cur_obj_play_sound_2(SOUND_OBJ2_PIRANHA_PLANT_BITE);
    }
}

void blargg_act_back_up(void) {
    if (o->oTimer == 0) {
        o->oFlags &= ~0x8; /* bit 3 */
        o->oMoveAngleYaw += 0x8000;
    }    

    o->oForwardVel = 5.0;    
   
    if (o->oTimer == 15) {
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        o->oFlags |= 0x8; /* bit 3 */
        o->oAction = MODE_SWIM;
    }
}

void blargg_backup_check(s16 collisionFlags) {
    if (!(collisionFlags & 0x8) && o->oAction != MODE_KNOCKBACK) /* bit 3 */
    {
        o->oPosX = o->oBullyPrevX;
        o->oPosZ = o->oBullyPrevZ;
        o->oAction = MODE_BACKUP;
    }
}

void blargg_step(void) {
    s16 collisionFlags = 0;
    collisionFlags = object_step();
    blargg_backup_check(collisionFlags);
}

void bhv_blargg_loop(void) {
    o->oBullyPrevX = o->oPosX;
    o->oBullyPrevY = o->oPosY;
    o->oBullyPrevZ = o->oPosZ;
    blargg_check_mario_collision();

    switch (o->oAction) {
        case MODE_SWIM:
            blargg_act_swim();
            blargg_step();
            break;

        case MODE_CHASE:
            blargg_act_chase_mario();
            blargg_step();
            break;

        case MODE_KNOCKBACK:
            blargg_act_knockback();
            blargg_step();
            break;

        case MODE_BACKUP:
            o->oForwardVel = 10.0;
            blargg_act_back_up();
            blargg_step();
            break;

        case BULLY_ACT_DEATH_PLANE_DEATH:
            o->activeFlags = 0;
            break;
    }

    set_object_visibility(o, 3000);
}

struct ObjectHitbox sBlarggFriendlyHitbox = {
    /* interactType: */ INTERACT_KOOPA_SHELL,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 4,
    /* health: */ 1,
    /* numLootCoins: */ 1,
    /* radius: */ 50,
    /* height: */ 50,
    /* hurtboxRadius: */ 50,
    /* hurtboxHeight: */ 50,
};

void bhv_friendly_blargg_init(void) {
    cur_obj_init_animation(ANM_swim);
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
}

void blargg_friendly_explode(void) {
    gMarioState->action = ACT_WALKING;
    mario_stop_riding_object(gMarioState);

    obj_mark_for_deletion(o);
    struct Object *explosion;
    if (o->oTimer < 5)
        cur_obj_scale(1.0 + (f32) o->oTimer / 5.0);
    else {
        explosion = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        explosion->oGraphYOffset += 100.0f;

        create_respawner(MODEL_FRIENDLY_BLARGG, bhvFriendlyBlargg, 3000);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_blargg_friendly_loop(void) {
    struct Surface *sp34;
    obj_set_hitbox(o, &sBlarggFriendlyHitbox);
    cur_obj_scale(2.0f);
    switch (o->oAction) {
        case 0:
            cur_obj_update_floor_and_walls();
            cur_obj_if_hit_wall_bounce_away();
            if (o->oInteractStatus & INT_STATUS_INTERACTED)
                o->oAction++;            
            cur_obj_move_standard(-20);
            break;
        case 1:
            obj_copy_pos(o, gMarioObject);
            sp34 = cur_obj_update_floor_height_and_get_floor();
            if (5.0f > absf(o->oPosY - o->oFloorHeight)) {
                if (sp34 != NULL && sp34->type == 1)
                    bhv_koopa_shell_flame_spawn();
                else
                    blargg_friendly_explode();
             } 
             else
                blargg_friendly_explode();
            o->oFaceAngleYaw = gMarioObject->oMoveAngleYaw;
            if (o->oInteractStatus & INT_STATUS_STOP_RIDING) {
                obj_mark_for_deletion(o);
                spawn_mist_particles();
                o->oAction = 0;
            }
            break;
    }
    o->oInteractStatus = 0;
}