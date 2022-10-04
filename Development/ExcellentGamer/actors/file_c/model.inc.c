Lights1 file_c_f3d_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx file_c_main_menu_seg7_us_0B843_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 file_c_main_menu_seg7_us_0B843_rgba16[] = "actors/file_c/main_menu_seg7_us_0B843.rgba16";

Vtx file_c_000_displaylist_mesh_layer_4_vtx_0[4] = {
	{{{2781, -1986, 0},0, {2224, 1456},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{2781, 1986, 0},0, {2224, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-2781, 1986, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-2781, -1986, 0},0, {-16, 1456},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx file_c_000_displaylist_mesh_layer_4_tri_0[] = {
	gsSPVertex(file_c_000_displaylist_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_file_c_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 70, file_c_main_menu_seg7_us_0B843_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 18, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 276, 180),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 18, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0),
	gsDPSetTileSize(0, 0, 0, 276, 180),
	gsSPSetLights1(file_c_f3d_material_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_file_c_f3d_material[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx file_c_000_displaylist_mesh_layer_4[] = {
	gsSPDisplayList(mat_file_c_f3d_material),
	gsSPDisplayList(file_c_000_displaylist_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_file_c_f3d_material),
	gsSPEndDisplayList(),
};

Gfx file_c_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

