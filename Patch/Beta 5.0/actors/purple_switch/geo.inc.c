#include "src/game/envfx_snow.h"

const GeoLayout purple_switch_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(300),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, purple_switch_000_displaylist_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, purple_switch_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
