Lights1 bowling_ball_f3d_material_003_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx BlackBobBody_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 BlackBobBody_rgba32[] = "actors/bowling_ball/ds_BlackBobBody.rgba32";

Vtx bowling_ball_000_displaylist_mesh_layer_4_vtx_0[6] = {
	{{{0, 49, 0},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-49, 49, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-49, -49, 0},0, {-16, 2032},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, -49, 0},0, {1008, 2032},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{49, 49, 0},0, {2032, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{49, -49, 0},0, {2032, 2032},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx bowling_ball_000_displaylist_mesh_layer_4_tri_0[] = {
	gsSPVertex(bowling_ball_000_displaylist_mesh_layer_4_vtx_0 + 0, 6, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(4, 3, 5, 0),
	gsSPEndDisplayList(),
};


Gfx mat_bowling_ball_f3d_material_003[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, BlackBobBody_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 4095, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPSetLights1(bowling_ball_f3d_material_003_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bowling_ball_f3d_material_003[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx mat_BlackBobBody_f3d_material_003[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, BlackBobBody_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 4095, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPSetLights1(bowling_ball_f3d_material_003_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_BlackBobBody_f3d_material_003[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx BlackBobBody_000_displaylist_mesh_layer_4[] = {
	gsSPDisplayList(mat_BlackBobBody_f3d_material_003),
	gsSPDisplayList(bowling_ball_000_displaylist_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_BlackBobBody_f3d_material_003),
	gsSPEndDisplayList(),
};

Gfx bowling_ball_000_displaylist_mesh_layer_4[] = {
	gsSPDisplayList(mat_bowling_ball_f3d_material_003),
	gsSPDisplayList(bowling_ball_000_displaylist_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bowling_ball_f3d_material_003),
	gsSPEndDisplayList(),
};

Gfx bowling_ball_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

