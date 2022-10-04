// breakable_box.c.inc

struct ObjectHitbox sEggHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */ 20,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 250,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 250,
};

void bhv_egg_init(void) {
    o->oGravity = 0.0f;
    o->oFriction = 0.99f;
    o->oBuoyancy = 1.4f;
    cur_obj_scale(0.3f);
    obj_set_hitbox(o, &sEggHitbox);
    o->oAnimState = 1;
    o->activeFlags |= ACTIVE_FLAG_UNK9;
}

void egg_spawn_dust(void) {
    struct Object *sp24 = spawn_object(o, MODEL_SMOKE, bhvSmoke);
    sp24->oPosX += (s32)(random_float() * 80.0f) - 40;
    sp24->oPosZ += (s32)(random_float() * 80.0f) - 40;
}

void egg_act_move(void) {
    s16 sp1E = object_step();

    obj_attack_collided_from_other_object(o);
    if (sp1E == 1)
        cur_obj_play_sound_2(SOUND_GENERAL_BOX_LANDING_2);
    if (sp1E & 1) {
        if (o->oForwardVel > 20.0f) {
            cur_obj_play_sound_2(SOUND_ENV_SLIDING);
            egg_spawn_dust();
        }
    }

    if (sp1E & 2) {
        spawn_mist_particles();
        spawn_triangle_break_particles(20, 138, 0.7f, 3);
        obj_spawn_yellow_coins(o, 3);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    obj_check_floor_death(sp1E, sObjFloor);
}

void egg_released_loop(void) {
    o->oBreakableBoxSmallFramesSinceReleased++;

    // Begin flashing
    if (o->oBreakableBoxSmallFramesSinceReleased > 810) {
        if (o->oBreakableBoxSmallFramesSinceReleased & 1)
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        else
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    }

    // Despawn, and create a corkbox respawner
    if (o->oBreakableBoxSmallFramesSinceReleased > 900) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void egg_idle_loop(void) {
    switch (o->oAction) {
        case 0:
            egg_act_move();
            break;

        case 100:
            obj_lava_death();
            break;

        case 101:
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }

    if (o->oBreakableBoxSmallReleased == 1)
        egg_released_loop();
}

void egg_get_dropped(void) {
    cur_obj_become_tangible();
    cur_obj_enable_rendering();
    cur_obj_get_dropped();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState = 0;
    o->oBreakableBoxSmallReleased = 1;
    o->oBreakableBoxSmallFramesSinceReleased = 0;
}

void egg_get_thrown(void) {
    cur_obj_become_tangible();
    cur_obj_enable_rendering_2();
    cur_obj_enable_rendering();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState = 0;
    o->oFlags &= ~0x08;
    o->oForwardVel = 80.0f;
    o->oVelY = 0.0f;
    o->oBreakableBoxSmallReleased = 1;
    o->oBreakableBoxSmallFramesSinceReleased = 0;
    o->activeFlags &= ~ACTIVE_FLAG_UNK9;
}

void bhv_egg_loop(void) {
    struct Object *goomba;
    f32 distTogoomba;
    switch (o->oHeldState) {
        case 0:
            egg_idle_loop();
            break;

        case 1:
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            break;

        case 2:
            egg_get_thrown();
            goomba=cur_obj_find_nearest_object_with_behavior(bhvGoomba,  &distTogoomba);
            if (goomba != NULL) 
            {
                o->oMoveAngleYaw = obj_angle_to_object(o, goomba);
            }
            if (goomba != NULL && distTogoomba < 300.0f)
            {
                spawn_mist_particles();
                spawn_triangle_break_particles(20, 138, 0.7f, 3);
                create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            if (obj_attack_collided_from_other_object(o) == 1)
            {
                spawn_mist_particles();
                spawn_triangle_break_particles(20, 138, 0.7f, 3);
                create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;

        case 3:
            egg_get_dropped();
            break;
    }

    o->oInteractStatus = 0;
}
