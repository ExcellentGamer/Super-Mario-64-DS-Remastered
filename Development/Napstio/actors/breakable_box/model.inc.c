Lights1 breakable_box_WoodenBlock_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx breakable_box_kibako_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 breakable_box_kibako_rgba32[] = "actors/breakable_box/kibako.rgba32";

Vtx breakable_box_000_displaylist_mesh_layer_1_vtx_0[24] = {
	{{{100, 200, 100},0, {2018, 1014},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, 200, -100},0, {2018, 3052},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 200, 100},0, {-20, 1014},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 200, -100},0, {-20, 3052},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 200, 100},0, {-20, 1014},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, 0, 100},0, {-20, -1024},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{100, 200, 100},0, {2018, 1014},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{100, 0, 100},0, {2018, -1024},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{100, 200, 100},0, {2018, 1014},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 0, 100},0, {2018, -1024},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 200, -100},0, {4056, 1014},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 0, -100},0, {4056, -1024},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 200, -100},0, {2018, 3052},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, 0, -100},0, {2018, 5090},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-100, 200, -100},0, {-20, 3052},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-100, 0, -100},0, {-20, 5090},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-100, 200, -100},0, {-2058, 1014},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 0, -100},0, {-2058, -1024},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 200, 100},0, {-20, 1014},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 0, 100},0, {-20, -1024},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 0, 100},0, {-20, 7128},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-100, 0, -100},0, {-20, 5090},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, 0, 100},0, {2018, 7128},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, 0, -100},0, {2018, 5090},{0x0, 0x81, 0x0, 0xFF}}},
};

Gfx breakable_box_000_displaylist_mesh_layer_1_tri_0[] = {
	gsSPVertex(breakable_box_000_displaylist_mesh_layer_1_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(15, 14, 13, 0),
	gsSPVertex(breakable_box_000_displaylist_mesh_layer_1_vtx_0 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSPEndDisplayList(),
};


Gfx mat_breakable_box_WoodenBlock[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, breakable_box_kibako_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(breakable_box_WoodenBlock_lights),
	gsSPEndDisplayList(),
};

Gfx breakable_box_000_displaylist_mesh_layer_1[] = {
	gsSPDisplayList(mat_breakable_box_WoodenBlock),
	gsSPDisplayList(breakable_box_000_displaylist_mesh_layer_1_tri_0),
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

