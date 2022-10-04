Lights1 amp_f3d_material_002_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 amp_f3d_material_003_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 amp_AmpFace_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx amp_bilikyu_ef_2_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 amp_bilikyu_ef_2_rgba16[] = "actors/amp/bilikyu_ef_2.rgba16";

Gfx amp_bilikyu_ef_1_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 amp_bilikyu_ef_1_rgba16[] = "actors/amp/bilikyu_ef_1.rgba16";

Gfx amp_bilikyu_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 amp_bilikyu_rgba16[] = "actors/amp/bilikyu.rgba16";

Vtx amp_000_offset_001_mesh_layer_4_vtx_0[4] = {
	{{{68, 72, 158},0, {-16, -16},{0x8, 0x0, 0x7F, 0xFF}}},
	{{{-27, -71, 164},0, {974, 974},{0x8, 0x0, 0x7F, 0xFF}}},
	{{{68, -71, 158},0, {974, -16},{0x8, 0x0, 0x7F, 0xFF}}},
	{{{-27, 72, 164},0, {-16, 974},{0x8, 0x0, 0x7F, 0xFF}}},
};

Gfx amp_000_offset_001_mesh_layer_4_tri_0[] = {
	gsSPVertex(amp_000_offset_001_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPEndDisplayList(),
};

Vtx amp_002_offset_001_mesh_layer_4_vtx_0[4] = {
	{{{-29, 72, 164},0, {-16, -16},{0xCC, 0x0, 0x74, 0xFF}}},
	{{{-124, -71, 121},0, {974, 974},{0xCC, 0x0, 0x74, 0xFF}}},
	{{{-29, -71, 164},0, {974, -16},{0xCC, 0x0, 0x74, 0xFF}}},
	{{{-124, 72, 121},0, {-16, 974},{0xCC, 0x0, 0x74, 0xFF}}},
};

Gfx amp_002_offset_001_mesh_layer_4_tri_0[] = {
	gsSPVertex(amp_002_offset_001_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPEndDisplayList(),
};

Vtx amp_000_displaylist_mesh_layer_4_vtx_0[20] = {
	{{{22, -29, 22},0, {496, 66},{0x3B, 0xDA, 0x6A, 0xFF}}},
	{{{22, 6, 35},0, {1254, 66},{0x3B, 0xDA, 0x6A, 0xFF}}},
	{{{11, -29, 28},0, {496, 502},{0x2A, 0xD8, 0x71, 0xFF}}},
	{{{11, 6, 41},0, {1254, 502},{0x27, 0xD8, 0x72, 0xFF}}},
	{{{0, -29, 30},0, {496, 1008},{0x0, 0xD5, 0x78, 0xFF}}},
	{{{0, 6, 43},0, {1254, 1008},{0x0, 0xD5, 0x78, 0xFF}}},
	{{{-11, 6, 41},0, {1254, 502},{0xD9, 0xD8, 0x72, 0xFF}}},
	{{{-11, -29, 28},0, {496, 502},{0xD6, 0xD8, 0x71, 0xFF}}},
	{{{-22, 6, 35},0, {1254, 66},{0xC5, 0xDA, 0x6A, 0xFF}}},
	{{{-22, -29, 22},0, {496, 66},{0xC5, 0xDA, 0x6A, 0xFF}}},
	{{{-25, 5, 31},0, {1224, 502},{0xD3, 0x1F, 0x73, 0xFF}}},
	{{{0, 5, 41},0, {2032, 502},{0x0, 0x19, 0x7D, 0xFF}}},
	{{{-21, 19, 29},0, {1224, 932},{0xD0, 0x1B, 0x73, 0xFF}}},
	{{{0, 19, 39},0, {2032, 932},{0x0, 0x13, 0x7E, 0xFF}}},
	{{{21, 19, 29},0, {1224, 932},{0x30, 0x1B, 0x73, 0xFF}}},
	{{{25, 5, 31},0, {1224, 502},{0x2D, 0x1F, 0x73, 0xFF}}},
	{{{-58, 0, 0},0, {-538, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, -58, 0},0, {-538, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, 58, 0},0, {506, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{58, 0, 0},0, {506, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx amp_000_displaylist_mesh_layer_4_tri_0[] = {
	gsSPVertex(amp_000_displaylist_mesh_layer_4_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(2, 3, 4, 0),
	gsSP1Triangle(5, 4, 3, 0),
	gsSP1Triangle(5, 6, 4, 0),
	gsSP1Triangle(7, 4, 6, 0),
	gsSP1Triangle(6, 8, 7, 0),
	gsSP1Triangle(9, 7, 8, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(13, 12, 11, 0),
	gsSP1Triangle(13, 11, 14, 0),
	gsSP1Triangle(15, 14, 11, 0),
	gsSPVertex(amp_000_displaylist_mesh_layer_4_vtx_0 + 16, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSPEndDisplayList(),
};


Gfx mat_amp_f3d_material_002[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, amp_bilikyu_ef_2_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(amp_f3d_material_002_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_amp_f3d_material_002[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx mat_amp_f3d_material_003[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, amp_bilikyu_ef_1_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(amp_f3d_material_003_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_amp_f3d_material_003[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx mat_amp_AmpFace[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, amp_bilikyu_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 124),
	gsSPSetLights1(amp_AmpFace_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_amp_AmpFace[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx amp_000_offset_001_mesh_layer_4[] = {
	gsSPDisplayList(mat_amp_f3d_material_002),
	gsSPDisplayList(amp_000_offset_001_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_amp_f3d_material_002),
	gsSPEndDisplayList(),
};

Gfx amp_002_offset_001_mesh_layer_4[] = {
	gsSPDisplayList(mat_amp_f3d_material_003),
	gsSPDisplayList(amp_002_offset_001_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_amp_f3d_material_003),
	gsSPEndDisplayList(),
};

Gfx amp_000_displaylist_mesh_layer_4[] = {
	gsSPDisplayList(mat_amp_AmpFace),
	gsSPDisplayList(amp_000_displaylist_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_amp_AmpFace),
	gsSPEndDisplayList(),
};

Gfx amp_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

