#ifndef MARIO_CHEATS_H
#define MARIO_CHEATS_H

#include "types.h"

s32 cheats_update(struct MarioState *m);
s32 cheats_moon_jump(struct MarioState *m);
s32 cheats_moon_gravity(struct MarioState *m);
s32 cheats_super_copter(struct MarioState *m);
s32 cheats_debug_move(struct MarioState *m);
s32 cheats_god_mode(struct MarioState *m);
s32 cheats_infinite_lives(struct MarioState *m);
s32 cheats_responsive(struct MarioState *m);
s32 cheats_speed_modifier(struct MarioState *m);
s32 cheats_jump_modifier(struct MarioState *m);
s32 cheats_swim_modifier(struct MarioState *m);
s32 cheats_size_modifier(struct MarioState *m);
s32 cheats_hurt_mario(struct MarioState *m);
s32 cheats_blj_anywhere(struct MarioState *m);
s32 cheats_swim_anywhere(struct MarioState *m);
s32 cheats_exit_anywhere(struct MarioState *m);
s32 cheats_cap_modifier(struct MarioState *m);
s32 cheats_super_wing_cap(struct MarioState *m);
s32 cheats_auto_wall_kick(struct MarioState *m);
s32 cheats_walk_on_hazards(struct MarioState *m);
s32 cheats_no_death_barrier(struct MarioState *m);
s32 cheats_no_bounds(struct MarioState *m);
s32 cheats_no_hold_heavy(struct MarioState *m);
s32 cheats_coins_magnet(struct MarioState *m);
s32 cheats_time_stop(struct MarioState *m);
s32 cheats_quick_ending(struct MarioState *m);
s32 cheats_water_control(struct MarioState *m);
s32 cheats_speed_display(struct MarioState *m);
s32 cheats_play_as(struct MarioState *m);
s32 cheats_jukebox(struct MarioState *m);
s32 cheats_instant_death(struct MarioState *m);
s32 cheats_spamba(struct MarioState *m);
s32 cheats_chaos_mode(struct MarioState *m);

#endif // MARIO_CHEATS_H
