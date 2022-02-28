Lights1 blue_coin_switch_BleuCoinSwith_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx blue_coin_switch_bc_switch_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 blue_coin_switch_bc_switch_rgba32[] = "actors/blue_coin_switch/bc_switch.rgba32";

Vtx blue_coin_switch_000_displaylist_mesh_layer_1_vtx_0[12] = {
	{{{-25, 26, -26},0, {3056, 496},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{27, 26, -26},0, {2032, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{-25, 0, -26},0, {3056, -16},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{27, 0, -26},0, {2032, -16},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{27, 26, 27},0, {1008, 496},{0x49, 0x49, 0x49, 0xFF}}},
	{{{27, 0, 27},0, {1008, -16},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{-25, 26, 27},0, {-16, 496},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{27, 26, -26},0, {1008, 1520},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{-25, 26, -26},0, {-16, 1520},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-25, 0, 27},0, {-16, -16},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-25, 26, -26},0, {-1040, 496},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-25, 0, -26},0, {-1040, -16},{0xA6, 0x0, 0xA6, 0xFF}}},
};

Gfx blue_coin_switch_000_displaylist_mesh_layer_1_tri_0[] = {
	gsSPVertex(blue_coin_switch_000_displaylist_mesh_layer_1_vtx_0 + 0, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(4, 6, 5, 0),
	gsSP1Triangle(4, 7, 6, 0),
	gsSP1Triangle(8, 6, 7, 0),
	gsSP1Triangle(9, 5, 6, 0),
	gsSP1Triangle(6, 10, 9, 0),
	gsSP1Triangle(11, 9, 10, 0),
	gsSPEndDisplayList(),
};


Gfx mat_blue_coin_switch_BleuCoinSwith[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, blue_coin_switch_bc_switch_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(blue_coin_switch_BleuCoinSwith_lights),
	gsSPEndDisplayList(),
};

Gfx blue_coin_switch_000_displaylist_mesh_layer_1[] = {
	gsSPDisplayList(mat_blue_coin_switch_BleuCoinSwith),
	gsSPDisplayList(blue_coin_switch_000_displaylist_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx blue_coin_switch_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

