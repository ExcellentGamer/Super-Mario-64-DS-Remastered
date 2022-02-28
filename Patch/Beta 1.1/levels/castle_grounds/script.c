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

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/castle_grounds/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_castle_grounds_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x07, _castle_grounds_segment_7SegmentRomStart, _castle_grounds_segment_7SegmentRomEnd), 
	LOAD_MIO0(0x0A, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0_TEXTURE(0x09, _outside_mio0SegmentRomStart, _outside_mio0SegmentRomEnd), 
	LOAD_MIO0(0x05, _group10_mio0SegmentRomStart, _group10_mio0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group10_geoSegmentRomStart, _group10_geoSegmentRomEnd), 
	LOAD_MIO0(0x06, _group15_mio0SegmentRomStart, _group15_mio0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	LOAD_MIO0(0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_11), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, castle_grounds_geo_0006F4), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_WARP_PIPE, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CASTLE_DOOR, castle_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_METAL_DOOR, metal_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_VCUTM_GRILL, castle_grounds_geo_00070C), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_FLAG, castle_grounds_geo_000660), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CANNON_GRILL, castle_grounds_geo_000724), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, castle_grounds_area_1),
		WARP_NODE(0x00, LEVEL_CASTLE, 0x01, 0x00, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01, LEVEL_CASTLE, 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_CASTLE, 0x03, 0x02, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_CASTLE_GROUNDS, 0x01, 0x03, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04, LEVEL_CASTLE_GROUNDS, 0x01, 0x04, WARP_NO_CHECKPOINT),
		WARP_NODE(0x05, LEVEL_VCUTM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x06, LEVEL_CASTLE_GROUNDS, 0x01, 0x06, WARP_NO_CHECKPOINT),
		WARP_NODE(0x07, LEVEL_CASTLE_GROUNDS, 0x01, 0x07, WARP_NO_CHECKPOINT),
		WARP_NODE(0x08, LEVEL_CASTLE_GROUNDS, 0x01, 0x08, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_CASTLE_GROUNDS, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x14, LEVEL_CASTLE_GROUNDS, 0x01, 0x14, WARP_NO_CHECKPOINT),
		WARP_NODE(0x1E, LEVEL_CASTLE_GROUNDS, 0x01, 0x1E, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CASTLE_GROUNDS_CANNON_GRILL, 56, 48, 1847, 0, 0, 0, 0x00000000, bhvHiddenAt120Stars),
		OBJECT(MODEL_NONE, -5941, 543, 5853, 0, 0, 0, 0x00000000, bhvBirdsSoundLoop),
		OBJECT(MODEL_NONE, 6236, -934, 6726, 0, 0, 0, 0x00000000, bhvBirdsSoundLoop),
		OBJECT(MODEL_NONE, 6279, 2237, -5832, 0, 0, 0, 0x00000000, bhvBirdsSoundLoop),
		OBJECT(MODEL_NONE, -6134, 3022, -6275, 0, 0, 0, 0x00000000, bhvBirdsSoundLoop),
		OBJECT(MODEL_BIRDS, -3571, 260, 4230, 0, 0, 0, 0x00000000, bhvBird),
		OBJECT(MODEL_BIRDS, 5035, 376, 707, 0, 0, 0, 0x00000000, bhvBird),
		OBJECT(MODEL_BUTTERFLY, -4429, 346, 2616, 0, 0, 0, 0x00000000, bhvButterfly),
		OBJECT(MODEL_CASTLE_GROUNDS_FLAG, 2866, 2899, -802, 0, 0, 0, 0x00000000, bhvCastleFlagWaving),
		OBJECT(MODEL_CASTLE_GROUNDS_FLAG, -2852, 2899, -784, 0, 0, 0, 0x00000000, bhvCastleFlagWaving),
		OBJECT(MODEL_CASTLE_GROUNDS_FLAG, -3380, 3440, -5071, 0, 0, 0, 0x00000000, bhvCastleFlagWaving),
		OBJECT(MODEL_CASTLE_GROUNDS_FLAG, 3382, 3440, -5071, 0, 0, 0, 0x00000000, bhvCastleFlagWaving),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 2337, 283, 2476, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -4854, 293, 2400, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -4146, 338, 2121, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -5293, 338, 769, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -5195, 367, -53, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 5849, 463, 344, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 5604, 543, -874, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 5019, 501, -1051, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 5213, 619, -1891, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 5708, 725, -2656, 0, 5, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 1362, 300, 3602, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -47, 572, 4900, 0, 20, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 1184, 341, 4581, 0, -12, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 1691, 313, 2925, 0, 5, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -1751, 435, 4533, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -2324, 474, 4332, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -1478, 679, 3702, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -2515, 536, 3732, 0, -40, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 605, 611, 4392, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, 5276, 392, 749, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, -5657, 360, -622, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_NONE, -1025, 319, 6209, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, 0, -1025, 319, 6209),
		OBJECT(MODEL_MIST, -5647, -98, -2217, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -5462, -98, -2408, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -5334, -98, -2579, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -5150, -98, -2810, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -4999, -98, -3087, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -4978, -98, -3355, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -4937, -98, -3519, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -4901, -98, -3782, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_MIST, -4840, -98, -4005, 0, 0, -90, 0x00000000, bhvWaterMist2),
		OBJECT(MODEL_NONE, -6165, 1346, -4162, 0, 0, 0, 0x00000000, bhvWaterfallSoundLoop),
		TERRAIN(castle_grounds_area_1_collision),
		MACRO_OBJECTS(castle_grounds_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -1025, 319, 6209),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
