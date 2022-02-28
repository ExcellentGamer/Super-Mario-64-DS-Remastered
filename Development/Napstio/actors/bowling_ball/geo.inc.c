#include "src/game/envfx_snow.h"

const GeoLayout bowling_ball_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 200, 280),
		GEO_OPEN_NODE(),
			GEO_SCALE(LAYER_FORCE, 170393),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, bowling_ball_000_displaylist_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bowling_ball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

const GeoLayout bowling_ball_track_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 200, 280),
		GEO_OPEN_NODE(),
			GEO_SCALE(LAYER_FORCE, 170393),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, BlackBobBody_000_displaylist_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bowling_ball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};