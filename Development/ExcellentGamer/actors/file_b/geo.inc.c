#include "src/game/envfx_snow.h"

const GeoLayout file_b_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(106385),
		GEO_OPEN_NODE(),
			GEO_SHADOW(0, 180, 240),
			GEO_OPEN_NODE(),
				GEO_SWITCH_CASE(2, geo_switch_anim_state),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_ALPHA, file_b_000_displaylist_mesh_layer_4),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, file_b_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
