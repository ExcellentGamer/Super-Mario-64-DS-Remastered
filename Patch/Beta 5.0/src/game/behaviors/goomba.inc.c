#include "pc/configfile.h"

/* oAction */
#define GOOMBA_ACT_GRAB 3
#define GOOMBA_ACT_GRAB_INIT 4

/**
 * Behavior for bhvGoomba and bhvGoombaTripletSpawner,
 * Goombas can either be spawned individually, or spawned by a triplet spawner.
 * The triplet spawner comes before its spawned goombas in processing order.
 */

/**
 * Hitbox for goomba.
 */
static struct ObjectHitbox sGoombaHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 72,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 42,
    /* hurtboxHeight:     */ 40,
};

/**
 * Properties that vary based on goomba size.
 */
struct GoombaProperties {
    f32 scale;
    u32 deathSound;
    s16 drawDistance;
    s8 damage;
};

/**
 * Properties for regular, huge, and tiny goombas.
 */
static struct GoombaProperties sGoombaProperties[] = {
    { 1.5f, SOUND_OBJ_ENEMY_DEATH_HIGH, 4000, 1 },
    { 3.5f, SOUND_OBJ_ENEMY_DEATH_LOW, 4000, 2 },
    { 0.5f, SOUND_OBJ_ENEMY_DEATH_HIGH, 1500, 0 },
};

/**
 * Attack handlers for goombas.
 */
static u8 sGoombaAttackHandlers[][6] = {
    // regular and tiny
    {
        /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
        /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
        /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_STUN,
        /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SQUISHED,
        /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
        /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
    },
    // huge
    {
        /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
        /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
        /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
        /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SQUISHED_WITH_BLUE_COIN,
        /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
        /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
    },
};

// from OMM, thanks Peachypeach
static void set_goomba_as_standalone(struct Object *goomba) {
    if (goomba->parentObj != goomba) {

        // Mark the goomba as dead inside the triplet
        set_object_respawn_info_bits(goomba->parentObj, (goomba->oBehParams2ndByte & GOOMBA_BP_TRIPLET_FLAG_MASK) >> 2);
        goomba->parentObj->oBehParams = goomba->parentObj->oBehParams | (goomba->oBehParams2ndByte & GOOMBA_BP_TRIPLET_FLAG_MASK) << 6;

        // Set the goomba as a standalone goomba
        goomba->oBehParams = (goomba->oGoombaSize & GOOMBA_BP_SIZE_MASK) << 16;
        goomba->oBehParams2ndByte = (goomba->oGoombaSize & GOOMBA_BP_SIZE_MASK);
        goomba->parentObj = goomba;
        goomba->prevObj = NULL;
    }
}

/**
 * Update function for goomba triplet spawner.
 */
void bhv_goomba_triplet_spawner_update(void) {
    UNUSED s32 unused1;
    s16 goombaFlag;
    UNUSED s16 unused2;
    s32 angle;
    s32 dAngle;
    s16 dx;
    s16 dz;

    // If mario is close enough and the goombas aren't currently loaded, then
    // spawn them
    if (o->oAction == GOOMBA_TRIPLET_SPAWNER_ACT_UNLOADED) {
        if (o->oDistanceToMario < 30 * configDrawDistance) {
            // The spawner is capable of spawning more than 3 goombas, but this
            // is not used in the game
            dAngle =
                0x10000
                / (((o->oBehParams2ndByte & GOOMBA_TRIPLET_SPAWNER_BP_EXTRA_GOOMBAS_MASK) >> 2) + 3);

            for (angle = 0, goombaFlag = 1 << 8; angle < 0xFFFF; angle += dAngle, goombaFlag <<= 1) {
                // Only spawn goombas which haven't been killed yet
                if (!(o->oBehParams & goombaFlag)) {
                    dx = 500.0f * coss(angle);
                    dz = 500.0f * sins(angle);

                    spawn_object_relative((o->oBehParams2ndByte & GOOMBA_TRIPLET_SPAWNER_BP_SIZE_MASK)
                                              | (goombaFlag >> 6),
                                          dx, 0, dz, o, MODEL_GOOMBA, bhvGoomba);
                }
            }

            o->oAction += 1;
        }
    } else if (o->oDistanceToMario > 40 * configDrawDistance) {
        // If mario is too far away, enter the unloaded action. The goombas
        // will detect this and unload themselves
        o->oAction = GOOMBA_TRIPLET_SPAWNER_ACT_UNLOADED;
    }
}

/**
 * Initialization function for goomba.
 */
void bhv_goomba_init(void) {
    o->oGoombaSize = o->oBehParams2ndByte & GOOMBA_BP_SIZE_MASK;

    o->oGoombaScale = sGoombaProperties[o->oGoombaSize].scale;
    o->oDeathSound = sGoombaProperties[o->oGoombaSize].deathSound;

    obj_set_hitbox(o, &sGoombaHitbox);

    o->oDrawingDistance = sGoombaProperties[o->oGoombaSize].drawDistance;
    o->oDamageOrCoinValue = sGoombaProperties[o->oGoombaSize].damage;

    o->oGravity = -8.0f / 3.0f * o->oGoombaScale;
    set_goomba_as_standalone(o);
}

/**
 * Enter the jump action and set initial y velocity.
 */
static void goomba_begin_jump(void) {
    cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
    o->oAction = GOOMBA_ACT_JUMP;
    o->oForwardVel = 0.0f;
    o->oVelY = 50.0f / 3.0f * o->oGoombaScale;
}

/**
 * If spawned by a triplet spawner, mark the flag in the spawner to indicate that
 * this goomba died. This prevents it from spawning again when mario leaves and
 * comes back.
 */
static void mark_goomba_as_dead(void) {
    if (o->parentObj != o) {
        set_object_respawn_info_bits(o->parentObj,
                                     (o->oBehParams2ndByte & GOOMBA_BP_TRIPLET_FLAG_MASK) >> 2);

        o->parentObj->oBehParams =
            o->parentObj->oBehParams | (o->oBehParams2ndByte & GOOMBA_BP_TRIPLET_FLAG_MASK) << 6;
    }
}

/**
 * Walk around randomly occasionally jumping. If mario comes within range,
 * chase him.
 */
static void goomba_act_walk(void) {
    treat_far_home_as_mario(1000.0f);

    obj_forward_vel_approach(o->oGoombaRelativeSpeed * o->oGoombaScale, 0.4f);

    // If walking fast enough, play footstep sounds
    if (o->oGoombaRelativeSpeed > 4.0f / 3.0f) {
        cur_obj_play_sound_at_anim_range(2, 17, SOUND_OBJ_GOOMBA_WALK);
    }

    //! By strategically hitting a wall, steep slope, or another goomba, we can
    //  prevent the goomba from turning back toward home for a while (goomba
    //  chase extension)
    //! It seems theoretically possible to get 2-3 goombas to repeatedly touch
    //  each other and move arbitrarily far from their home, but it's
    //  extremely precise and chaotic in practice, so probably can't be performed
    //  for nontrivial distances
    if (o->oGoombaTurningAwayFromWall) {
        o->oGoombaTurningAwayFromWall = obj_resolve_collisions_and_turn(o->oGoombaTargetYaw, 0x200);
    } else {
        // If far from home, walk toward home.
        if (o->oDistanceToMario >= 25000.0f) {
            o->oGoombaTargetYaw = o->oAngleToMario;
            o->oGoombaWalkTimer = random_linear_offset(20, 30);
        }

        if (!(o->oGoombaTurningAwayFromWall =
                  obj_bounce_off_walls_edges_objects(&o->oGoombaTargetYaw))) {
            if (o->oDistanceToMario < 500.0f) {
                // If close to mario, begin chasing him. If not already chasing
                // him, jump first

                if (o->oGoombaRelativeSpeed <= 2.0f) {
                    goomba_begin_jump();
                }

                o->oGoombaTargetYaw = o->oAngleToMario;
                o->oGoombaRelativeSpeed = 20.0f;
            } else {
                // If mario is far away, walk at a normal pace, turning randomly
                // and occasionally jumping

                o->oGoombaRelativeSpeed = 4.0f / 3.0f;
                if (o->oGoombaWalkTimer != 0) {
                    o->oGoombaWalkTimer -= 1;
                } else {
                    if (random_u16() & 3) {
                        o->oGoombaTargetYaw = obj_random_fixed_turn(0x2000);
                        o->oGoombaWalkTimer = random_linear_offset(100, 100);
                    } else {
                        goomba_begin_jump();
                        o->oGoombaTargetYaw = obj_random_fixed_turn(0x6000);
                    }
                }
            }
        }

        cur_obj_rotate_yaw_toward(o->oGoombaTargetYaw, 0x200);
    }
}

/**
 * This action occurs when either the goomba attacks mario normally, or mario
 * attacks a huge goomba with an attack that doesn't kill it.
 */
static void goomba_act_attacked_mario(void) {
    if (o->oGoombaSize == GOOMBA_SIZE_TINY) {
        mark_goomba_as_dead();
        o->oNumLootCoins = 0;
        obj_die_if_health_non_positive();
    } else {
        //! This can happen even when the goomba is already in the air. It's
        //  hard to chain these in practice
        goomba_begin_jump();
        o->oGoombaTargetYaw = o->oAngleToMario;
        o->oGoombaTurningAwayFromWall = FALSE;
    }
}

/**
 * Move until landing, and rotate toward target yaw.
 */
static void goomba_act_jump(void) {
    obj_resolve_object_collisions(NULL);

    //! If we move outside the goomba's drawing radius the frame it enters the
    //  jump action, then it will keep its velY, but it will still be counted
    //  as being on the ground.
    //  Next frame, the jump action will think it has already ended because it is
    //  still on the ground.
    //  This puts the goomba back in the walk action, but the positive velY will
    //  make it hop into the air. We can then trigger another jump.
    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        o->oAction = GOOMBA_ACT_WALK;
    } else {
        cur_obj_rotate_yaw_toward(o->oGoombaTargetYaw, 0x800);
    }
}

/**
 * Attack handler for when mario attacks a huge goomba with an attack that
 * doesn't kill it.
 * From the goomba's perspective, this is the same as the goomba attacking
 * mario.
 */
void huge_goomba_weakly_attacked(void) {
    o->oAction = GOOMBA_ACT_ATTACKED_MARIO;
}

static void goomba_act_grab_init(void) {
    //o->oGravity = 2.5f;
    //o->oFriction = 0.875f;
    //o->oBuoyancy = 1.4f;
    o->oTimer = 0;
    spawn_object(o, MODEL_NONE, bhvHorStarParticleSpawner);
    o->oInteractType = INTERACT_GRABBABLE;
    o->oAction = GOOMBA_ACT_GRAB;
}

static void goomba_act_grab(void) {
    o->oAnimState = 1;
    if (o->oHeldState == HELD_FREE && o->oGoombaGrabbed != 1 && o->oTimer <= 150) {
        o->oGoombaTargetYaw += 0x1000;
        cur_obj_rotate_yaw_toward(o->oGoombaTargetYaw, 0x1000);
    }
    if (o->oHeldState == HELD_FREE && o->oGoombaGrabbed != 1 && o->oTimer > 150) {
        o->oInteractType = INTERACT_BOUNCE_TOP;
        o->oAction = GOOMBA_ACT_WALK;
    } 
    //Thrown
    if (o->oHeldState == HELD_FREE && o->oGoombaGrabbed == 1) {
        o->oGravity = 2.5f;
        o->oFriction = 0.875f;
        o->oBuoyancy = 1.4f;
        o->oForwardVel = 50.0f;
        o->oTimer = 0;
        o->oNumLootCoins = 0;
    }

}

void goomba_box_act_move(void) {
    s16 collisionFlags = object_step();

    obj_attack_collided_from_other_object(o);
    if (collisionFlags == 1) {
        cur_obj_play_sound_2(SOUND_GENERAL_BOX_LANDING_2);
    }
    if (collisionFlags & 1) {
        if (o->oForwardVel > 20.0f) {
            spawn_mist_particles();
            obj_spawn_yellow_coins(o, 1);
            create_sound_spawner(SOUND_OBJ_STOMPED);
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
    if (collisionFlags & 2) {
        spawn_mist_particles();
        obj_spawn_yellow_coins(o, 1);
        create_sound_spawner(SOUND_OBJ_STOMPED);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    obj_check_floor_death(collisionFlags, o->oFloor);
}

void goomba_wario_grab() {
    f32 animSpeed;
    if (gMarioState->heldObj != o && o->oGoombaGrabbed == 1) {
        cur_obj_become_tangible();
       o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
       if (o->oHeldState != HELD_FREE) {
        cur_obj_get_dropped();
        o->oForwardVel = 20.0f;
       }
       goomba_box_act_move();
    }
    if (gMarioState->heldObj == o) {
        o->oGoombaGrabbed = 1;
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        cur_obj_become_intangible();
    }

    if (obj_update_standard_actions(o->oGoombaScale)) {
        cur_obj_scale(o->oGoombaScale);
        obj_update_blinking(&o->oGoombaBlinkTimer, 30, 50, 5);
        cur_obj_update_floor_and_walls();

        if ((animSpeed = o->oForwardVel / o->oGoombaScale * 0.4f) < 1.0f) {
            animSpeed = 1.0f;
        }

        if(o->oAction < GOOMBA_ACT_GRAB)
            cur_obj_init_animation_with_accel_and_sound(0, animSpeed);
            
        switch (o->oAction) {
            case GOOMBA_ACT_WALK:
                goomba_act_walk();
                break;
            case GOOMBA_ACT_ATTACKED_MARIO:
                goomba_act_attacked_mario();
                break;
            case GOOMBA_ACT_JUMP:
                goomba_act_jump();
                break;
            case GOOMBA_ACT_GRAB_INIT:
                goomba_act_grab_init();
                break;
            case GOOMBA_ACT_GRAB:
                goomba_act_grab();
                break;
        }
        if(o->oAction < GOOMBA_ACT_GRAB) {
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
                    if (o->oAction != GOOMBA_ACT_ATTACKED_MARIO) {
                        o->oAction = GOOMBA_ACT_ATTACKED_MARIO;
                        o->oTimer = 0;
                    }
                } else {
                    s32 attackType = o->oInteractStatus & INT_STATUS_ATTACK_MASK;

                    switch (sGoombaAttackHandlers[0][attackType - 1]) {
                        case ATTACK_HANDLER_NOP:
                            break;

                        case ATTACK_HANDLER_KNOCKBACK:
                            obj_set_knockback_action(attackType);
                            break;

                        case ATTACK_HANDLER_SQUISHED:
                            obj_set_squished_action();
                            break;

                        case ATTACK_HANDLER_STUN:
                            o->oTimer = 0;
                            o->oAction = GOOMBA_ACT_GRAB_INIT;
                            break;
                    }
                }
                o->oInteractStatus = 0;
            }
            cur_obj_move_standard(-78);
        } 
        else {
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {}
            o->oInteractStatus = 0;
        }
    } else {
        o->oAnimState = TRUE;
    }
}

/**
 * Update function for goomba.
 */
void bhv_goomba_update(void) {
    // PARTIAL_UPDATE
    if (isWario())
        goomba_wario_grab();
    if(!isWario()){
    f32 animSpeed;

    if (obj_update_standard_actions(o->oGoombaScale)) {
        // If this goomba has a spawner and mario moved away from the spawner,
        // unload
        if (o->parentObj != o) {
            if (o->parentObj->oAction == GOOMBA_TRIPLET_SPAWNER_ACT_UNLOADED) {
                obj_mark_for_deletion(o);
            }
        }

        cur_obj_scale(o->oGoombaScale);
        obj_update_blinking(&o->oGoombaBlinkTimer, 30, 50, 5);
        cur_obj_update_floor_and_walls();

        if ((animSpeed = o->oForwardVel / o->oGoombaScale * 0.4f) < 1.0f) {
            animSpeed = 1.0f;
        }
        cur_obj_init_animation_with_accel_and_sound(0, animSpeed);

        switch (o->oAction) {
            case GOOMBA_ACT_WALK:
                goomba_act_walk();
                break;
            case GOOMBA_ACT_ATTACKED_MARIO:
                goomba_act_attacked_mario();
                break;
            case GOOMBA_ACT_JUMP:
                goomba_act_jump();
                break;
        }

        //! @bug Weak attacks on huge goombas in a triplet mark them as dead even if they're not.
        // obj_handle_attacks returns the type of the attack, which is non-zero
        // even for Mario's weak attacks. Thus, if Mario weakly attacks a huge goomba
        // without harming it (e.g. by punching it), the goomba will be marked as dead
        // and will not respawn if Mario leaves and re-enters the spawner's radius
        // even though the goomba isn't actually dead.
        if (obj_handle_attacks(&sGoombaHitbox, GOOMBA_ACT_ATTACKED_MARIO,
                               sGoombaAttackHandlers[o->oGoombaSize & 1])) {
            mark_goomba_as_dead();
        }

        cur_obj_move_standard(-78);
    } else {
        o->oAnimState = TRUE;
    }
    }
}
