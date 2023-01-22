#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"
#include "game/level_update.h"
#include "levels/scripts.h"
#include "make_const_nonconst.h"
#include "levels/rec_room/header.h"
#include "actors/common1.h"

	// Luigi Doors
	static const LevelScript script_func_local_1[] = 
	{
		WARP_NODE(0x00, LEVEL_REC_ROOM, 0x01, 0x00, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -2141,607,-338, 0, 0, 0, 0x00000000, bhvInstantActiveWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 1423, -434, -3581, 0, 0, 0, 0x04000000, bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 1579, -434, -3581, 0, 180, 0, 0x04000000, bhvDoorWarp),
		RETURN(),
	};

	// Wario Doors
	static const LevelScript script_func_local_2[] = 
	{
		WARP_NODE(0x01, LEVEL_REC_ROOM, 0x01, 0x01, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -1075,607,230, 0, -90, 0, 0x00010000, bhvInstantActiveWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 2748, -434, -2906, 0, -90, 0, 0x05010000, bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 2748, -434, -2747, 0, 90, 0, 0x05010000, bhvDoorWarp),
		RETURN(),
	};	

	// Mario Doors
	static const LevelScript script_func_local_3[] = 
	{
		WARP_NODE(0x02, LEVEL_REC_ROOM, 0x01, 0x02, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -1644, 607, -321, 0, 0, 0, 0x00020000, bhvInstantActiveWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 1912, -434, -3581, 0, 0, 0, 0x03020000, bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 2069, -434, -3581, 0, 180, 0, 0x03020000, bhvDoorWarp),
		RETURN(),
	};

	// Other Doors
	static const LevelScript script_func_local_4[] = 
	{
		WARP_NODE(0x0A, LEVEL_CASTLE, 0x01, 0x07, WARP_NO_CHECKPOINT),
	    OBJECT(MODEL_CASTLE_DOOR_1_STAR, 643, -434, -1476, 0, -45, 0, 0x000A0000, bhvDoorWarp),
		RETURN(),
	};

const LevelScript level_rec_room_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _rec_room_segment_7SegmentRomStart, _rec_room_segment_7SegmentRomEnd), 
	LOAD_MIO0(0x06, _group15_mio0SegmentRomStart, _group15_mio0SegmentRomEnd),
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart,  _group15_geoSegmentRomEnd),
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CASTLE_DOOR,        castle_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WOODEN_DOOR,        wooden_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_METAL_DOOR,         metal_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CASTLE_DOOR_UNUSED, castle_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WOODEN_DOOR_UNUSED, wooden_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_0_STARS,       castle_door_0_star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_1_STAR,        castle_door_1_star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_3_STARS,       castle_door_3_stars_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_KEY_DOOR,           key_door_geo),

	AREA(1, rec_room_area_1),
		WARP_NODE(0x0A, LEVEL_REC_ROOM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 0x27, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 0x28, WARP_NO_CHECKPOINT),
		JUMP_LINK(script_func_local_1),
		JUMP_LINK(script_func_local_2),
		JUMP_LINK(script_func_local_3),
		JUMP_LINK(script_func_local_4),
		MARIO_POS(0x01, 135, 968, -331, -1792),
		TERRAIN(rec_room_area_1_collision),
		MACRO_OBJECTS(rec_room_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_INSIDE_CASTLE),
		TERRAIN_TYPE(TERRAIN_STONE),
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 135, 968, -331, -1792),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
