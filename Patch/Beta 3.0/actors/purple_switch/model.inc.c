Lights1 purple_switch_f3d_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx purple_switch_switch_box_cmp4_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 purple_switch_switch_box_cmp4_rgba32[] = "actors/purple_switch/switch_box_cmp4.rgba32";

Vtx purple_switch_000_displaylist_mesh_layer_4_vtx_0[20] = {
	{{{66, 32, 66},0, {496, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{66, 32, -66},0, {496, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-66, 32, 66},0, {-528, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-66, 32, -66},0, {-528, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-66, 32, 66},0, {558, 1008},{0x0, 0x5E, 0x56, 0xFF}}},
	{{{-101, 0, 101},0, {558, -16},{0x0, 0x5E, 0x56, 0xFF}}},
	{{{66, 32, 66},0, {1458, 1008},{0x0, 0x5E, 0x56, 0xFF}}},
	{{{101, 0, 101},0, {1458, -16},{0x0, 0x5E, 0x56, 0xFF}}},
	{{{66, 32, 66},0, {1458, 1008},{0x56, 0x5E, 0x0, 0xFF}}},
	{{{101, 0, 101},0, {1458, -16},{0x56, 0x5E, 0x0, 0xFF}}},
	{{{66, 32, -66},0, {558, 1008},{0x56, 0x5E, 0x0, 0xFF}}},
	{{{101, 0, -101},0, {558, -16},{0x56, 0x5E, 0x0, 0xFF}}},
	{{{66, 32, -66},0, {558, 1008},{0x0, 0x5E, 0xAA, 0xFF}}},
	{{{101, 0, -101},0, {558, -16},{0x0, 0x5E, 0xAA, 0xFF}}},
	{{{-66, 32, -66},0, {1458, 1008},{0x0, 0x5E, 0xAA, 0xFF}}},
	{{{-101, 0, -101},0, {1458, -16},{0x0, 0x5E, 0xAA, 0xFF}}},
	{{{-66, 32, -66},0, {1458, 1008},{0xAA, 0x5E, 0x0, 0xFF}}},
	{{{-101, 0, -101},0, {1458, -16},{0xAA, 0x5E, 0x0, 0xFF}}},
	{{{-66, 32, 66},0, {558, 1008},{0xAA, 0x5E, 0x0, 0xFF}}},
	{{{-101, 0, 101},0, {558, -16},{0xAA, 0x5E, 0x0, 0xFF}}},
};

Gfx purple_switch_000_displaylist_mesh_layer_4_tri_0[] = {
	gsSPVertex(purple_switch_000_displaylist_mesh_layer_4_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(15, 14, 13, 0),
	gsSPVertex(purple_switch_000_displaylist_mesh_layer_4_vtx_0 + 16, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSPEndDisplayList(),
};


Gfx mat_purple_switch_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, purple_switch_switch_box_cmp4_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(purple_switch_f3d_material_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_purple_switch_f3d_material[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx purple_switch_000_displaylist_mesh_layer_4[] = {
	gsSPDisplayList(mat_purple_switch_f3d_material),
	gsSPDisplayList(purple_switch_000_displaylist_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_purple_switch_f3d_material),
	gsSPEndDisplayList(),
};

Gfx purple_switch_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

