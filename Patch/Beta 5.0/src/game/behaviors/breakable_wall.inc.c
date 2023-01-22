// breakable_wall.c.inc

void bhv_wf_breakable_wall_loop(void) {
    if (gMarioStates->action == ACT_SHOT_FROM_CANNON) {
        cur_obj_become_tangible();
        if (obj_check_if_collided_with_object(o, gMarioObject)) {
            if (cur_obj_has_behavior(bhvWfBreakableWallRight)) {
                r96_play_jingle(R96_EVENT_SOLVE_PUZZLE, 0.1, 1.0, 1);
                r96_music_fade(0, -1, 0.0, 1, 1);
            }
            create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
            o->oInteractType = 8;
            o->oDamageOrCoinValue = 1;
            obj_explode_and_spawn_coins(80.0f, 0);
        }
    } else
        cur_obj_become_intangible();
}
