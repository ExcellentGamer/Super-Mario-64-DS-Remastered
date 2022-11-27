Lights1 checkerboard_platform_f3d_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx checkerboard_platform_normal_lift_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 checkerboard_platform_normal_lift_rgba32[] = "actors/checkerboard_platform/normal_lift.rgba32";

Vtx checkerboard_platform_000_displaylist_mesh_layer_1_vtx_0[8] = {
	{{{153, 15, 153},0, {1008, -528},{0x49, 0x49, 0x49, 0xFF}}},
	{{{153, 15, -153},0, {1008, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{-153, 15, 153},0, {-16, -528},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{153, -15, 153},0, {1008, -528},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-153, -15, 153},0, {-16, -528},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-153, -15, -153},0, {-16, 496},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-153, 15, -153},0, {-16, 496},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{153, -15, -153},0, {1008, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
};

Gfx checkerboard_platform_000_displaylist_mesh_layer_1_tri_0[] = {
	gsSPVertex(checkerboard_platform_000_displaylist_mesh_layer_1_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(2, 4, 0, 0),
	gsSP1Triangle(4, 2, 5, 0),
	gsSP1Triangle(6, 5, 2, 0),
	gsSP1Triangle(6, 2, 1, 0),
	gsSP1Triangle(1, 7, 6, 0),
	gsSP1Triangle(7, 1, 3, 0),
	gsSP1Triangle(7, 3, 5, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(5, 6, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_checkerboard_platform_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, checkerboard_platform_normal_lift_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 255, 256),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 4, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPSetLights1(checkerboard_platform_f3d_material_lights),
	gsSPEndDisplayList(),
};

Gfx checkerboard_platform_000_displaylist_mesh_layer_1[] = {
	gsSPDisplayList(mat_checkerboard_platform_f3d_material),
	gsSPDisplayList(checkerboard_platform_000_displaylist_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx checkerboard_platform_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

