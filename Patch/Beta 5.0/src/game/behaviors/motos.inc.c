enum sMotosActions {
    MOTOS_ACT_WAIT,
    MOTOS_ACT_PLAYER_SEARCH,
    MOTOS_ACT_PLAYER_CARRY,
    MOTOS_ACT_PLAYER_PITCH,
    MOTOS_ACT_CARRY_RUN,
    MOTOS_ACT_THROWN,
    MOTOS_ACT_RECOVER,
    MOTOS_ACT_DEATH
};

enum sMotosAnimations {
    MOTOS_ANIM_BASE,
    MOTOS_ANIM_CARRY,
    MOTOS_ANIM_CARRY_RUN,
    MOTOS_ANIM_CARRY_START,
    MOTOS_ANIM_DOWN_RECOVER,
    MOTOS_ANIM_DOWN_STOP,
    MOTOS_ANIM_PITCH,
    MOTOS_ANIM_SAFE_DOWN,
    MOTOS_ANIM_WAIT,
    MOTOS_ANIM_WALK,
};

void bhv_motos_wait() {
    o->oForwardVel = 0.f;
    o->oVelY = 0.f;
    
    cur_obj_init_animation_with_sound(MOTOS_ANIM_WAIT);
    
    if (o->oDistanceToMario < 500.f) {
        o->oAction = MOTOS_ACT_PLAYER_SEARCH;
    }
}

void bhv_motos_player_search() {
    cur_obj_init_animation_with_sound(MOTOS_ANIM_WALK);
    o->oForwardVel = 6.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, 350);
    cur_obj_update_floor_and_walls();

    if (o->oInteractStatus & INT_STATUS_GRABBED_MARIO) {
        o->oAction = MOTOS_ACT_PLAYER_CARRY;
        o->oChuckyaUnk88 = 1;
    }
}

void bhv_motos_player_carry() {
    cur_obj_init_animation_with_sound(MOTOS_ANIM_CARRY_START);
    o->oForwardVel = 0.f;
    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = MOTOS_ACT_CARRY_RUN;
    }
}

void bhv_motos_carry_run(void) {
    o->oForwardVel = 15.0f;
    cur_obj_init_animation_with_sound(MOTOS_ANIM_CARRY_RUN);

    if ((o->oTimer > 45) || (o->oMoveFlags & OBJ_MOVE_HIT_EDGE))
        o->oAction = MOTOS_ACT_PLAYER_PITCH;
}

void bhv_motos_player_pitch(void) {
    o->oForwardVel = 0.0f;
    cur_obj_init_animation_with_sound(MOTOS_ANIM_PITCH);
    
    if (cur_obj_check_anim_frame(14)) {
        o->oChuckyaUnk88 = 2;
        o->numCollidedObjs = 10;
    }
    
    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = MOTOS_ACT_WAIT;
        o->oInteractStatus &= (~INT_STATUS_GRABBED_MARIO);
    }
}

void bhv_motos_thrown(void) {
    cur_obj_init_animation_with_sound(MOTOS_ANIM_CARRY);
    
    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        o->oAction = MOTOS_ACT_RECOVER;
        cur_obj_play_sound_2(SOUND_OBJ2_LARGE_BULLY_ATTACKED);
    }
}

void bhv_motos_recover(void) {
    o->oForwardVel = 0.0f;
    if (o->oSubAction == 0) {
        cur_obj_init_animation_with_sound(MOTOS_ANIM_DOWN_RECOVER);
        if (cur_obj_check_if_near_animation_end())
            o->oAction = MOTOS_ACT_WAIT;
    }
}

void moto_spawn_coin(void) {
    struct Object *coin = spawn_object(o, MODEL_BLUE_COIN, bhvBlueCoinMotos);
    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_2);
    coin->oForwardVel = 10.0f;
    coin->oVelY = 100.0f;
    coin->oPosY = o->oPosY + 310.0f;
    coin->oMoveAngleYaw = (f32)(o->oFaceAngleYaw + 0x8000) + random_float() * 1024.0f;
}

void bhv_motos_death(void) {
    if (obj_lava_death() == 1)
        moto_spawn_coin();
}

void bhv_motos_main() {
    f32 floorY;

    cur_obj_update_floor_and_walls();

    switch (o->oAction) {
        case MOTOS_ACT_WAIT:
            bhv_motos_wait();
            break;
        case MOTOS_ACT_PLAYER_SEARCH:
            bhv_motos_player_search();
            break;
        case MOTOS_ACT_PLAYER_CARRY:
            bhv_motos_player_carry();
            break;
        case MOTOS_ACT_PLAYER_PITCH:
            bhv_motos_player_pitch();
            break;
        case MOTOS_ACT_CARRY_RUN:
            bhv_motos_carry_run();
            break;
        case MOTOS_ACT_THROWN:
            bhv_motos_thrown();
            break;
        case MOTOS_ACT_RECOVER:
            bhv_motos_recover();
            break;
    }
    
    cur_obj_move_standard(-78);

    floorY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &sObjFloor);
    if (sObjFloor != NULL) {
        if ((floorY + 1.f > o->oPosY) && (sObjFloor->type == SURFACE_BURNING)) {
            o->oAction = MOTOS_ACT_DEATH;
        }
    }
}

void bhv_motos_loop(void) {
    cur_obj_scale(2.0f);
    o->oInteractionSubtype |= INT_SUBTYPE_GRABS_MARIO;
    
    switch (o->oHeldState) {
        case HELD_FREE:
            if (o->oAction == MOTOS_ACT_DEATH)
                bhv_motos_death();
            else
                bhv_motos_main();
            break;
        case HELD_HELD:
            cur_obj_unrender_and_reset_state(MOTOS_ANIM_CARRY, MOTOS_ACT_WAIT);
            break;
        case HELD_THROWN:
        case HELD_DROPPED:
            cur_obj_get_thrown_or_placed(15.0f, 35.0f, MOTOS_ACT_THROWN);
            break;
    }
    o->oInteractStatus = 0;
    set_object_visibility(o, 2000);
}
