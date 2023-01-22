#include "src/game/envfx_snow.h"

const GeoLayout wario_key_pumpkin_geo[] = {
GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
        GEO_OPEN_NODE(),
            GEO_ASM(0, geo_rotate_coin),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_OPAQUE, wario_key_pumpkin),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_END(),
};

const GeoLayout wario_key_house_geo[] = {
GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
        GEO_OPEN_NODE(),
            GEO_ASM(0, geo_rotate_coin),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_OPAQUE, wario_key_house),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_END(),
};

const GeoLayout wario_key_tree_geo[] = {
GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
        GEO_OPEN_NODE(),
            GEO_ASM(0, geo_rotate_coin),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_OPAQUE, wario_key_tree),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_END(),
};

const GeoLayout wario_key_koopa_geo[] = {
GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
        GEO_OPEN_NODE(),
            GEO_ASM(0, geo_rotate_coin),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_OPAQUE, wario_key_koopa),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_END(),
};

const GeoLayout wario_key_lunar_geo[] = {
GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
        GEO_OPEN_NODE(),
            GEO_ASM(0, geo_rotate_coin),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_OPAQUE, wario_key_lunar),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_END(),
};

const GeoLayout wario_key_mario_geo[] = {
GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
        GEO_OPEN_NODE(),
            GEO_ASM(0, geo_rotate_coin),
            GEO_ROTATION_NODE(0x00, 0, 0, 0),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_OPAQUE, wario_key_mario),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_END(),
};