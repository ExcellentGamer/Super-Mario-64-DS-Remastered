Gfx breakable_box_renga_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 breakable_box_renga_rgba16[] = "actors/breakable_box/ds_renga.rgba16";

Vtx breakable_box_000_displaylist_mesh_layer_1_vtx_0[23] = {
	{{{-125, 0, -125}, 0, {-58, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 0, 125}, 0, {966, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 250, 125}, 0, {966, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 250, -125}, 0, {-58, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 0, -125}, 0, {966, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 0, -125}, 0, {-58, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 0, 125}, 0, {-58, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 250, -125}, 0, {966, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 0, -125}, 0, {-58, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 0, -125}, 0, {966, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 250, -125}, 0, {-58, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 0, 125}, 0, {-50, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 0, 125}, 0, {974, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 250, 125}, 0, {974, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 250, 125}, 0, {-50, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 250, 125}, 0, {940, 4}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 250, 125}, 0, {-4, 4}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 250, -125}, 0, {-4, 956}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-125, 250, -125}, 0, {940, 956}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 0, 125}, 0, {-42, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 0, -125}, 0, {982, 1008}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 250, -125}, 0, {982, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{125, 250, 125}, 0, {-42, -16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx breakable_box_000_displaylist_mesh_layer_1_tri_0[] = {
	gsSPVertex(breakable_box_000_displaylist_mesh_layer_1_vtx_0 + 0, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 1, 0),
	gsSP1Triangle(7, 8, 9, 0),
	gsSP1Triangle(7, 10, 8, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(11, 13, 14, 0),
	gsSPVertex(breakable_box_000_displaylist_mesh_layer_1_vtx_0 + 15, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_breakable_box_Breakable_Box_Mario[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0),
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, breakable_box_renga_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_revert_breakable_box_Breakable_Box_Mario[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx breakable_box_000_displaylist_mesh_layer_1[] = {
	gsSPDisplayList(mat_breakable_box_Breakable_Box_Mario),
	gsSPDisplayList(breakable_box_000_displaylist_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_breakable_box_Breakable_Box_Mario),
	gsSPEndDisplayList(),
};

Gfx breakable_box_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

