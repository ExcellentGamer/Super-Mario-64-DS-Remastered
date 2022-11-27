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
#include "levels/bob/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bob_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_MIO0_TEXTURE(0x09, _generic_mio0SegmentRomStart, _generic_mio0SegmentRomEnd), 
	LOAD_MIO0(0x0A, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0(0x05, _group3_mio0SegmentRomStart, _group3_mio0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_MIO0(0x06, _group14_mio0SegmentRomStart, _group14_mio0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_MIO0(0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_CHAIN_CHOMP_GATE, bob_geo_000440), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_SEESAW_PLATFORM, bob_geo_000458), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BARS_GRILLS, bob_geo_000470), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bob_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_BOB, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0E, LEVEL_BOB, 0x01, 0x0D, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_BOB, 0x01, 0x0E, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 0x32, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 0x64, WARP_NO_CHECKPOINT),
		OBJECT_WITH_ACTS(MODEL_DL_CANNON_LID, -5704, -920, 5606, 0, -180, 0, 0x00000000, bhvCannonClosed, ACT_2 | ACT_3 | ACT_4 | ACT_5 | ACT_6),
		OBJECT(MODEL_CANNON_BASE, 1396, 1869, -2387, 0, -18, 0, 0x00010000, bhvWaterBombCannon),
		OBJECT(MODEL_BOB_CHAIN_CHOMP_GATE, 1484, -280, 417, 0, -32, 0, 0x00000000, bhvChainChompGate),
		OBJECT(MODEL_PURPLE_SWITCH, -2304, -1048, -3635, 0, 27, 0, 0x00000000, bhvFloorSwitchGrills),
		OBJECT(MODEL_STAR, 1566, 27, 270, 0, 0, 0, 0x05000000, bhvStar),
		OBJECT(MODEL_NONE, -6219, -49, 2747, 0, 0, 0, 0x03000000, bhvHiddenRedCoinStar),
		OBJECT_WITH_ACTS(MODEL_NONE, 1512, 2787, -5659, 0, -147, 0, 0x00000000, bhvBobBowlingBallSpawner, ACT_1 | ACT_2),
		OBJECT_WITH_ACTS(MODEL_NONE, 1512, 2787, -5659, 0, -147, 0, 0x00000000, bhvTtmBowlingBallSpawner, ACT_3 | ACT_4 | ACT_5 | ACT_6),
		OBJECT_WITH_ACTS(MODEL_NONE, 433, 1776, -5558, 0, -151, 0, 0x00020000, bhvBobBowlingBallSpawner, ACT_1 | ACT_2),
		OBJECT_WITH_ACTS(MODEL_NONE, 433, 1776, -5558, 0, -151, 0, 0x00020000, bhvTtmBowlingBallSpawner, ACT_3 | ACT_4 | ACT_5 | ACT_6),
		OBJECT(MODEL_BOWLING_BALL, -1345, -239, -3761, 0, 0, 0, 0x00000000, bhvPitBowlingBall),
		OBJECT(MODEL_BOWLING_BALL, -101, -229, -3425, 0, 0, 0, 0x00000000, bhvPitBowlingBall),
		OBJECT(MODEL_BOB_SEESAW_PLATFORM, -2304, -331, 1024, 0, 45, 0, 0x00030000, bhvSeesawPlatform),
		OBJECT(MODEL_NONE, -6451, -178, 1075, 0, 0, 0, 0x04040000, bhvHiddenStar),
		OBJECT(MODEL_NONE, -2048, -1049, -3069, 0, 25, 0, 0x00000000, bhvOpenableGrill),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -6131, -146, -6508, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -5793, -25, -4655, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -1509, -915, 5093, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 2910, -281, 5916, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 5427, -178, 6042, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 4207, -121, 3771, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 4096, 2024, 1638, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 6798, 959, -5588, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 6032, 1145, -7661, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -6804, -9, -4867, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -6173, -24, -431, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -5120, -281, 2048, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -4096, -281, 1535, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -6655, -280, 3584, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -4096, -280, 3072, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -3583, -281, 2559, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, -4268, -1048, 4767, 0, 0, 0, 0x00010000, bhvTree),
		OBJECT(MODEL_CHECKERBOARD_PLATFORM, 1614, -749, 4611, 0, 0, 0, 0x00280000, bhvCheckerboardElevatorGroup),
		OBJECT(MODEL_NONE, -6374, 693, 6505, 0, 135, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, 135, -6374, -967, 6505),
		OBJECT_WITH_ACTS(MODEL_BOBOMB_BUDDY, -6093, -1048, 6656, 0, 0, 0, DIALOG_003 << 16, bhvBobombBuddy, ACT_2 | ACT_3 | ACT_4 | ACT_5 | ACT_6),
		OBJECT_WITH_ACTS(MODEL_BOBOMB_BUDDY, -5632, -895, 5939, 0, 0, 0, DIALOG_002 << 16, bhvBobombBuddyOpensCannon, ACT_2 | ACT_3 | ACT_4 | ACT_5 | ACT_6),
		OBJECT_WITH_ACTS(MODEL_BOBOMB_BUDDY, -4314, -1048, 5119, 0, 0, 0, DIALOG_003 << 16, bhvBobombBuddy, ACT_2 | ACT_3 | ACT_4 | ACT_5 | ACT_6),
		OBJECT_WITH_ACTS(MODEL_CHAIN_CHOMP, 410, -280, 1946, 0, 0, 0, 0x00000000, bhvChainChomp, ACT_1 | ACT_2),
		OBJECT_WITH_ACTS(MODEL_GOOMBA, 5326, -50, 3695, 0, -45, 0, 0x00000000, bhvGoomba, ACT_1 | ACT_2 | ACT_3 | ACT_5 | ACT_6),
		OBJECT_WITH_ACTS(MODEL_GOOMBA, -205, -1048, 4321, 0, -90, 0, 0x00000000, bhvGoomba, ACT_1 | ACT_2 | ACT_3 | ACT_5 | ACT_6),
		OBJECT_WITH_ACTS(MODEL_BLACK_BOBOMB, 1149, 1852, -2472, 0, -18, 0, 0x00000000, bhvBobomb, ACT_1),
		OBJECT_WITH_ACTS(MODEL_BOBOMB_BUDDY, -6093, -1048, 6656, 0, 0, 0, DIALOG_001 << 16, bhvBobombBuddy, ACT_1),
		OBJECT_WITH_ACTS(MODEL_BOBOMB_BUDDY, -5632, -895, 5939, 0, 0, 0, DIALOG_002 << 16, bhvBobombBuddy, ACT_1),
		OBJECT_WITH_ACTS(MODEL_CANNON_BASE, -5695, -920, 5599, 0, 135, 0, 0x00010000, bhvWaterBombCannon, ACT_1),
		OBJECT_WITH_ACTS(MODEL_KING_BOBOMB, 1537, 3244, -5516, 0, -146, 0, 0x00000000, bhvKingBobomb, ACT_1),
		OBJECT_WITH_ACTS(MODEL_NONE, 3072, 3244, -4710, 0, 0, 0, 0x00000000, bhvKoopaRaceEndpoint, ACT_2),
		OBJECT_WITH_ACTS(MODEL_KOOPA_WITH_SHELL, -3789, -1048, 5222, 0, 0, 0, 0x01020000, bhvKoopa, ACT_2),
		OBJECT(MODEL_WOODEN_SIGNPOST, -4588, -1048, 5435, 0, -90, 0, DIALOG_033, bhvSignOnWall),
		OBJECT_WITH_ACTS(MODEL_BREAKABLE_BOX, -2960, -280, 256, 0, 45, 0, 0x00000000, bhvBreakableBox, ACT_4),
		OBJECT_WITH_ACTS(MODEL_BREAKABLE_BOX, -3105, -280, 400, 0, 45, 0, 0x00000000, bhvBreakableBox, ACT_4),
		OBJECT_WITH_ACTS(MODEL_BREAKABLE_BOX, -2418, -73, -4801, 0, 27, 0, 0x00000000, bhvBreakableBox, ACT_4),
		OBJECT_WITH_ACTS(MODEL_BREAKABLE_BOX, -2511, -73, -4983, 0, 27, 0, 0x00000000, bhvBreakableBox, ACT_4),
		OBJECT_WITH_ACTS(MODEL_BREAKABLE_BOX, -4404, -24, -662, 0, 45, 0, 0x00000000, bhvBreakableBox, ACT_4),
		OBJECT_WITH_ACTS(MODEL_BREAKABLE_BOX, -4961, -24, -768, 0, 0, 0, 0x00000000, bhvBreakableBox, ACT_4),
		OBJECT_WITH_ACTS(MODEL_KING_BOBOMB, 3072, 3244, -4710, 0, -146, 0, 0x00000000, bhvKingBobomb, ACT_4),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		SHOW_DIALOG(0x00, DIALOG_000),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 135, -6374, -967, 6505),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
