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
#include "levels/fourth_floor/header.h"

const LevelScript level_fourth_floor_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _fourth_floor_segment_7SegmentRomStart, _fourth_floor_segment_7SegmentRomEnd),
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario),

	AREA(1, fourth_floor_area_1),
		OBJECT(MODEL_PLAYER_LOCK_SWITCH_PIPE, 376, -110, -533, 0, 0, 0, 0x000A0000, bhvWarpPipe),
		WARP_NODE(/*id*/ 0x0A, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x1F, /*flags*/ WARP_NO_CHECKPOINT),
		WARP_NODE(/*id*/ 0xF0, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x1F, /*flags*/ WARP_NO_CHECKPOINT),
		WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x1F, /*flags*/ WARP_NO_CHECKPOINT),
		OBJECT(/*model*/ MODEL_PLAYER_LOCK_SWITCH_GREEN_LOCKED_PIPE, /*pos*/  1895, -110, 2302,/*angle*/ 0, 190, 0, /*behParam*/ 0, /*beh*/ bhvCharacterSwitchPipeLuigiLocked),
		OBJECT(/*model*/ MODEL_PLAYER_LOCK_SWITCH_GREEN_UNLOCKED_PIPE, /*pos*/  1895, -110, 2302,/*angle*/ 0, 190, 0, /*behParam*/ 0, /*beh*/ bhvCharacterSwitchPipeLuigiUnlocked),
		OBJECT(/*model*/ MODEL_PLAYER_LOCK_SWITCH_RED_PIPE, /*pos*/ 311, -110, 2341,/*angle*/ 0, 180, 0, /*behParam*/ 1, /*beh*/ bhvCharacterSwitchPipe),
		OBJECT(/*model*/ MODEL_PLAYER_LOCK_SWITCH_YELLOW_LOCKED_PIPE, /*pos*/ -1281, -110, 2270,/*angle*/ 0, -190, 0, /*behParam*/ 3, /*beh*/ bhvCharacterSwitchPipeWarioLocked),
		OBJECT(/*model*/ MODEL_PLAYER_LOCK_SWITCH_YELLOW_UNLOCKED_PIPE, /*pos*/ -1281, -110, 2270,/*angle*/ 0, -190, 0, /*behParam*/ 3, /*beh*/ bhvCharacterSwitchPipeWarioUnlocked),
		TERRAIN(fourth_floor_area_1_collision),
		MACRO_OBJECTS(fourth_floor_area_1_Area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_SOUND_PLAYER),
		TERRAIN_TYPE(TERRAIN_STONE),
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 373, -120, 450),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};