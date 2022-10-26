Lights1 bobomb_BobBody_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 bobomb__3D_Black_Bomb_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 bobomb__3D_Red_Bomb_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 bobomb_BobEye_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx bobomb_BlackBobBody_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 bobomb_BlackBobBody_rgba32[] = "actors/bobomb/BlackBobBody.rgba32";

Gfx bobomb_RedBobBody_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 bobomb_RedBobBody_rgba32[] = "actors/bobomb/RedBobBody.rgba32";

Gfx bobomb_bombhei_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 bobomb_bombhei_rgba32[] = "actors/bobomb/bombhei.rgba32";

Gfx bobomb_red_bombhei_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 bobomb_red_bombhei_rgba32[] = "actors/bobomb/red_bombhei.rgba32";

Gfx bobomb_Eyes_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 bobomb_Eyes_rgba32[] = "actors/bobomb/Eyes.rgba32";

Vtx bobomb_000_displaylist_mesh_layer_4_vtx_0[8] = {
	{{{0, -49, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{49, -49, 0},0, {974, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{49, 49, 0},0, {974, 1960},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, 49, 0},0, {-16, 1960},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-49, -49, 0},0, {974, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, 49, 0},0, {-16, 1960},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-49, 49, 0},0, {974, 1960},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, -49, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx bobomb_000_displaylist_mesh_layer_4_tri_0[] = {
	gsSPVertex(bobomb_000_displaylist_mesh_layer_4_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 7, 5, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_000_offset_005_mesh_layer_4_vtx_0[28] = {
	{{{-35, -5, 2},0, {1008, 784},{0x92, 0xC0, 0x4, 0xFF}}},
	{{{-10, -27, 2},0, {1008, 816},{0xA3, 0xAA, 0x5, 0xFF}}},
	{{{-11, 26, 35},0, {1232, 816},{0xD1, 0x3D, 0x65, 0xFF}}},
	{{{-12, 26, -34},0, {784, 816},{0xCE, 0x3A, 0x9B, 0xFF}}},
	{{{28, -29, -15},0, {880, 912},{0x11, 0xAB, 0xA3, 0xFF}}},
	{{{85, 16, -38},0, {784, 1360},{0x23, 0xF, 0x87, 0xFF}}},
	{{{88, -16, -19},0, {880, 1296},{0x38, 0xA0, 0xC2, 0xFF}}},
	{{{120, 11, 2},0, {1008, 1488},{0x7E, 0xF1, 0x0, 0xFF}}},
	{{{88, -15, 24},0, {1136, 1296},{0x35, 0xA0, 0x40, 0xFF}}},
	{{{85, 16, 43},0, {1232, 1360},{0x20, 0xF, 0x7A, 0xFF}}},
	{{{28, -24, 19},0, {1136, 912},{0x9, 0xB1, 0x63, 0xFF}}},
	{{{-35, -5, 2},0, {816, 816},{0x92, 0xC0, 0x4, 0xFF}}},
	{{{-11, 26, 35},0, {816, 816},{0xD1, 0x3D, 0x65, 0xFF}}},
	{{{-37, 26, 2},0, {816, 816},{0x97, 0x48, 0x4, 0xFF}}},
	{{{107, 26, 28},0, {816, 816},{0x52, 0x3E, 0x4A, 0xFF}}},
	{{{85, 16, 43},0, {816, 816},{0x20, 0xF, 0x7A, 0xFF}}},
	{{{120, 11, 2},0, {816, 816},{0x7E, 0xF1, 0x0, 0xFF}}},
	{{{107, 26, 28},0, {816, 816},{0x52, 0x3E, 0x4A, 0xFF}}},
	{{{85, 16, 43},0, {816, 816},{0x20, 0xF, 0x7A, 0xFF}}},
	{{{107, 26, -23},0, {816, 816},{0x53, 0x3E, 0xB6, 0xFF}}},
	{{{85, 16, -38},0, {816, 816},{0x23, 0xF, 0x87, 0xFF}}},
	{{{-12, 26, -34},0, {816, 816},{0xCE, 0x3A, 0x9B, 0xFF}}},
	{{{-37, 26, 2},0, {816, 816},{0x97, 0x48, 0x4, 0xFF}}},
	{{{-35, -5, 2},0, {816, 816},{0x92, 0xC0, 0x4, 0xFF}}},
	{{{-10, -27, 2},0, {816, 528},{0xA3, 0xAA, 0x5, 0xFF}}},
	{{{15, -119, 2},0, {1040, 624},{0x0, 0x81, 0x0, 0xFF}}},
	{{{28, -24, 19},0, {816, 720},{0x9, 0xB1, 0x63, 0xFF}}},
	{{{28, -29, -15},0, {784, 624},{0x11, 0xAB, 0xA3, 0xFF}}},
};

Gfx bobomb_000_offset_005_mesh_layer_4_tri_0[] = {
	gsSPVertex(bobomb_000_offset_005_mesh_layer_4_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 1, 0, 0),
	gsSP1Triangle(1, 3, 4, 0),
	gsSP1Triangle(5, 4, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 8, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(2, 10, 9, 0),
	gsSP1Triangle(10, 2, 1, 0),
	gsSP1Triangle(10, 4, 8, 0),
	gsSP1Triangle(6, 8, 4, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(12, 15, 14, 0),
	gsSPVertex(bobomb_000_offset_005_mesh_layer_4_vtx_0 + 16, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(3, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(6, 1, 3, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(9, 8, 11, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_000_offset_005_mesh_layer_4_vtx_1[36] = {
	{{{77, 26, -44},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-14, 26, -35},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{114, 26, -28},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-46, 26, 1},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{114, 26, -28},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-14, 26, -35},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-46, 26, 1},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{126, 26, 2},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{118, 26, 33},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-13, 26, 40},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{81, 26, 51},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-14, 26, -35},0, {1178, 1264},{0xD0, 0x3C, 0x9B, 0xFF}}},
	{{{77, 26, -44},0, {1020, 1264},{0x14, 0x3C, 0x92, 0xFF}}},
	{{{32, -32, -19},0, {1072, 1488},{0x12, 0xAF, 0xA0, 0xFF}}},
	{{{84, -20, -15},0, {962, 1464},{0x39, 0x9C, 0xC9, 0xFF}}},
	{{{114, 26, -28},0, {910, 1264},{0x56, 0x33, 0xB2, 0xFF}}},
	{{{126, 26, 2},0, {842, 1264},{0x76, 0x30, 0xFA, 0xFF}}},
	{{{84, -20, -15},0, {962, 1464},{0x39, 0x9C, 0xC9, 0xFF}}},
	{{{114, 26, -28},0, {910, 1264},{0x56, 0x33, 0xB2, 0xFF}}},
	{{{86, -20, 22},0, {912, 1462},{0x39, 0x9B, 0x35, 0xFF}}},
	{{{118, 26, 33},0, {826, 1264},{0x5E, 0x31, 0x47, 0xFF}}},
	{{{81, 26, 51},0, {878, 1264},{0x15, 0x3A, 0x6F, 0xFF}}},
	{{{32, -31, 23},0, {1012, 1484},{0xE, 0xAF, 0x60, 0xFF}}},
	{{{-13, 26, 40},0, {1082, 1264},{0xCF, 0x3A, 0x66, 0xFF}}},
	{{{-39, -8, 1},0, {1182, 1420},{0x97, 0xB9, 0xFF, 0xFF}}},
	{{{-46, 26, 1},0, {1194, 1264},{0x93, 0x41, 0x0, 0xFF}}},
	{{{-14, 26, -35},0, {1178, 1264},{0xD0, 0x3C, 0x9B, 0xFF}}},
	{{{32, -32, -19},0, {1072, 1488},{0x12, 0xAF, 0xA0, 0xFF}}},
	{{{-17, -29, 3},0, {1136, 1488},{0x9E, 0xAF, 0x7, 0xFF}}},
	{{{32, -32, -19},0, {848, 1232},{0x12, 0xAF, 0xA0, 0xFF}}},
	{{{15, -119, 2},0, {848, 400},{0xFF, 0x81, 0x0, 0xFF}}},
	{{{-17, -29, 3},0, {784, 1232},{0x9E, 0xAF, 0x7, 0xFF}}},
	{{{15, -119, 2},0, {848, 400},{0xFF, 0x81, 0x0, 0xFF}}},
	{{{32, -32, -19},0, {848, 1232},{0x12, 0xAF, 0xA0, 0xFF}}},
	{{{32, -31, 23},0, {912, 1232},{0xE, 0xAF, 0x60, 0xFF}}},
	{{{-17, -29, 3},0, {784, 1232},{0x9E, 0xAF, 0x7, 0xFF}}},
};

Gfx bobomb_000_offset_005_mesh_layer_4_tri_1[] = {
	gsSPVertex(bobomb_000_offset_005_mesh_layer_4_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(8, 7, 6, 0),
	gsSP1Triangle(6, 9, 8, 0),
	gsSP1Triangle(10, 8, 9, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(12, 15, 14, 0),
	gsSPVertex(bobomb_000_offset_005_mesh_layer_4_vtx_1 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(5, 6, 3, 0),
	gsSP1Triangle(6, 5, 7, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 8, 7, 0),
	gsSP1Triangle(9, 10, 8, 0),
	gsSP1Triangle(11, 8, 10, 0),
	gsSP1Triangle(8, 11, 12, 0),
	gsSP1Triangle(12, 6, 8, 0),
	gsSP1Triangle(11, 3, 6, 0),
	gsSP1Triangle(11, 1, 3, 0),
	gsSP1Triangle(13, 14, 15, 0),
	gsSPVertex(bobomb_000_offset_005_mesh_layer_4_vtx_1 + 32, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 3, 0, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_000_offset_008_mesh_layer_4_vtx_0[28] = {
	{{{-35, -3, -4},0, {1008, 784},{0x92, 0xC0, 0xFC, 0xFF}}},
	{{{-10, -25, -4},0, {1008, 816},{0xA3, 0xAA, 0xFB, 0xFF}}},
	{{{-12, 28, 32},0, {784, 816},{0xCE, 0x3A, 0x65, 0xFF}}},
	{{{-11, 28, -37},0, {1232, 816},{0xD1, 0x3D, 0x9B, 0xFF}}},
	{{{28, -22, -21},0, {1136, 912},{0x9, 0xB1, 0x9D, 0xFF}}},
	{{{85, 18, -45},0, {1232, 1360},{0x20, 0xF, 0x86, 0xFF}}},
	{{{88, -13, -26},0, {1136, 1296},{0x35, 0xA0, 0xC0, 0xFF}}},
	{{{120, 13, -4},0, {1008, 1488},{0x7E, 0xF1, 0x0, 0xFF}}},
	{{{88, -14, 17},0, {880, 1296},{0x38, 0xA0, 0x3E, 0xFF}}},
	{{{85, 18, 36},0, {784, 1360},{0x23, 0xF, 0x79, 0xFF}}},
	{{{28, -27, 13},0, {880, 912},{0x11, 0xAB, 0x5D, 0xFF}}},
	{{{-35, -3, -4},0, {816, 816},{0x92, 0xC0, 0xFC, 0xFF}}},
	{{{-37, 28, -4},0, {816, 816},{0x97, 0x48, 0xFC, 0xFF}}},
	{{{-11, 28, -37},0, {816, 816},{0xD1, 0x3D, 0x9B, 0xFF}}},
	{{{-12, 28, 32},0, {816, 816},{0xCE, 0x3A, 0x65, 0xFF}}},
	{{{107, 28, 21},0, {816, 816},{0x53, 0x3E, 0x4A, 0xFF}}},
	{{{107, 28, 21},0, {816, 816},{0x53, 0x3E, 0x4A, 0xFF}}},
	{{{-12, 28, 32},0, {816, 816},{0xCE, 0x3A, 0x65, 0xFF}}},
	{{{85, 18, 36},0, {816, 816},{0x23, 0xF, 0x79, 0xFF}}},
	{{{120, 13, -4},0, {816, 816},{0x7E, 0xF1, 0x0, 0xFF}}},
	{{{107, 28, -30},0, {816, 816},{0x52, 0x3E, 0xB6, 0xFF}}},
	{{{85, 18, -45},0, {816, 816},{0x20, 0xF, 0x86, 0xFF}}},
	{{{-11, 28, -37},0, {816, 816},{0xD1, 0x3D, 0x9B, 0xFF}}},
	{{{-37, 28, -4},0, {816, 816},{0x97, 0x48, 0xFC, 0xFF}}},
	{{{-10, -25, -4},0, {816, 528},{0xA3, 0xAA, 0xFB, 0xFF}}},
	{{{15, -117, -4},0, {1040, 624},{0x0, 0x81, 0x0, 0xFF}}},
	{{{28, -27, 13},0, {784, 624},{0x11, 0xAB, 0x5D, 0xFF}}},
	{{{28, -22, -21},0, {816, 720},{0x9, 0xB1, 0x9D, 0xFF}}},
};

Gfx bobomb_000_offset_008_mesh_layer_4_tri_0[] = {
	gsSPVertex(bobomb_000_offset_008_mesh_layer_4_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 1, 3, 0),
	gsSP1Triangle(5, 4, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 8, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(2, 10, 9, 0),
	gsSP1Triangle(10, 2, 1, 0),
	gsSP1Triangle(8, 10, 6, 0),
	gsSP1Triangle(4, 6, 10, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(12, 11, 14, 0),
	gsSP1Triangle(14, 15, 12, 0),
	gsSPVertex(bobomb_000_offset_008_mesh_layer_4_vtx_0 + 16, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 3, 0, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(3, 5, 4, 0),
	gsSP1Triangle(6, 4, 5, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(4, 7, 0, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(9, 8, 11, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_000_offset_008_mesh_layer_4_vtx_1[31] = {
	{{{81, 28, -53},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-13, 28, -42},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{118, 28, -35},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-46, 28, -3},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{126, 28, -4},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{114, 28, 26},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-14, 28, 33},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{77, 28, 42},0, {1200, 1296},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-13, 28, -42},0, {1082, 1264},{0xCF, 0x3A, 0x9A, 0xFF}}},
	{{{81, 28, -53},0, {878, 1264},{0x15, 0x3A, 0x91, 0xFF}}},
	{{{32, -29, -25},0, {1012, 1484},{0xE, 0xAF, 0xA0, 0xFF}}},
	{{{86, -18, -24},0, {912, 1462},{0x39, 0x9B, 0xCB, 0xFF}}},
	{{{118, 28, -35},0, {826, 1264},{0x5E, 0x31, 0xB9, 0xFF}}},
	{{{126, 28, -4},0, {842, 1264},{0x76, 0x30, 0x6, 0xFF}}},
	{{{84, -18, 13},0, {962, 1464},{0x39, 0x9C, 0x37, 0xFF}}},
	{{{114, 28, 26},0, {910, 1264},{0x56, 0x33, 0x4E, 0xFF}}},
	{{{114, 28, 26},0, {910, 1264},{0x56, 0x33, 0x4E, 0xFF}}},
	{{{77, 28, 42},0, {1020, 1264},{0x14, 0x3C, 0x6E, 0xFF}}},
	{{{84, -18, 13},0, {962, 1464},{0x39, 0x9C, 0x37, 0xFF}}},
	{{{32, -30, 17},0, {1072, 1488},{0x12, 0xAF, 0x60, 0xFF}}},
	{{{-14, 28, 33},0, {1178, 1264},{0xD0, 0x3C, 0x65, 0xFF}}},
	{{{-39, -6, -3},0, {1182, 1420},{0x97, 0xB9, 0x1, 0xFF}}},
	{{{-46, 28, -3},0, {1194, 1264},{0x93, 0x41, 0x0, 0xFF}}},
	{{{-13, 28, -42},0, {1082, 1264},{0xCF, 0x3A, 0x9A, 0xFF}}},
	{{{32, -29, -25},0, {1012, 1484},{0xE, 0xAF, 0xA0, 0xFF}}},
	{{{-17, -27, -5},0, {1136, 1488},{0x9E, 0xAF, 0xF9, 0xFF}}},
	{{{86, -18, -24},0, {912, 1462},{0x39, 0x9B, 0xCB, 0xFF}}},
	{{{32, -29, -25},0, {912, 1232},{0xE, 0xAF, 0xA0, 0xFF}}},
	{{{32, -30, 17},0, {848, 1232},{0x12, 0xAF, 0x60, 0xFF}}},
	{{{15, -117, -4},0, {848, 400},{0xFF, 0x81, 0x0, 0xFF}}},
	{{{-17, -27, -5},0, {784, 1232},{0x9E, 0xAF, 0xF9, 0xFF}}},
};

Gfx bobomb_000_offset_008_mesh_layer_4_tri_1[] = {
	gsSPVertex(bobomb_000_offset_008_mesh_layer_4_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(2, 3, 4, 0),
	gsSP1Triangle(5, 4, 3, 0),
	gsSP1Triangle(3, 6, 5, 0),
	gsSP1Triangle(7, 5, 6, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSP1Triangle(9, 12, 11, 0),
	gsSP1Triangle(13, 11, 12, 0),
	gsSP1Triangle(11, 13, 14, 0),
	gsSP1Triangle(15, 14, 13, 0),
	gsSPVertex(bobomb_000_offset_008_mesh_layer_4_vtx_1 + 16, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(4, 6, 5, 0),
	gsSP1Triangle(6, 7, 5, 0),
	gsSP1Triangle(8, 5, 7, 0),
	gsSP1Triangle(5, 8, 9, 0),
	gsSP1Triangle(3, 5, 9, 0),
	gsSP1Triangle(2, 3, 10, 0),
	gsSP1Triangle(8, 10, 3, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(13, 14, 11, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_006_offset_mesh_layer_4_vtx_0[32] = {
	{{{61, -150, -2},0, {1168, 1712},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{44, -150, 41},0, {1104, 1776},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{44, -150, -44},0, {1104, 1616},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{1, -149, -62},0, {1008, 1616},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{1, -149, 58},0, {1008, 1776},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{-41, -147, -44},0, {912, 1616},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{-41, -147, 41},0, {912, 1776},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{-59, -147, -2},0, {848, 1712},{0xFD, 0x81, 0x0, 0xFF}}},
	{{{44, -150, -44},0, {752, 1840},{0x44, 0xAF, 0xBA, 0xFF}}},
	{{{62, -100, -2},0, {1006, 1552},{0x7F, 0xFF, 0x0, 0xFF}}},
	{{{61, -150, -2},0, {1006, 1840},{0x61, 0xAE, 0x0, 0xFF}}},
	{{{44, -99, -44},0, {752, 1552},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{1, -149, -62},0, {528, 1840},{0xFE, 0xB1, 0x9D, 0xFF}}},
	{{{2, -98, -61},0, {528, 1552},{0x0, 0x1, 0x81, 0xFF}}},
	{{{-41, -147, -44},0, {752, 1840},{0xB8, 0xB2, 0xBA, 0xFF}}},
	{{{-40, -97, -44},0, {752, 1552},{0xA6, 0x4, 0xA6, 0xFF}}},
	{{{-59, -147, -2},0, {1006, 1840},{0x9B, 0xB3, 0x0, 0xFF}}},
	{{{-40, -97, -44},0, {752, 1552},{0xA6, 0x4, 0xA6, 0xFF}}},
	{{{-41, -147, -44},0, {752, 1840},{0xB8, 0xB2, 0xBA, 0xFF}}},
	{{{-57, -97, -2},0, {1006, 1552},{0x81, 0x5, 0x0, 0xFF}}},
	{{{-41, -147, 41},0, {1264, 1840},{0xB8, 0xB2, 0x46, 0xFF}}},
	{{{-40, -97, 40},0, {1264, 1552},{0xA7, 0x5, 0x5B, 0xFF}}},
	{{{1, -149, 58},0, {1488, 1840},{0xFF, 0xB2, 0x65, 0xFF}}},
	{{{2, -98, 56},0, {1488, 1552},{0x1, 0x5, 0x7F, 0xFF}}},
	{{{44, -150, 41},0, {1264, 1840},{0x44, 0xAF, 0x47, 0xFF}}},
	{{{44, -99, 40},0, {1264, 1552},{0x58, 0x0, 0x5C, 0xFF}}},
	{{{61, -150, -2},0, {1006, 1840},{0x61, 0xAE, 0x0, 0xFF}}},
	{{{62, -100, -2},0, {1006, 1552},{0x7F, 0xFF, 0x0, 0xFF}}},
	{{{-15, -184, -15},0, {1008, 1712},{0xD8, 0x1D, 0x8B, 0xFF}}},
	{{{-15, -184, 12},0, {1008, 1712},{0xD9, 0x1D, 0x75, 0xFF}}},
	{{{8, -101, -2},0, {1008, 1712},{0x19, 0x7D, 0x0, 0xFF}}},
	{{{2, -191, -2},0, {1008, 1712},{0x7F, 0xF9, 0x0, 0xFF}}},
};

Gfx bobomb_006_offset_mesh_layer_4_tri_0[] = {
	gsSPVertex(bobomb_006_offset_mesh_layer_4_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(4, 6, 5, 0),
	gsSP1Triangle(7, 5, 6, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(9, 8, 11, 0),
	gsSP1Triangle(12, 11, 8, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(13, 14, 15, 0),
	gsSPVertex(bobomb_006_offset_mesh_layer_4_vtx_0 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 0, 3, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(5, 6, 7, 0),
	gsSP1Triangle(8, 7, 6, 0),
	gsSP1Triangle(7, 8, 9, 0),
	gsSP1Triangle(10, 9, 8, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(15, 14, 13, 0),
	gsSP1Triangle(14, 15, 12, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_006_offset_mesh_layer_4_vtx_1[32] = {
	{{{-59, -146, 0},0, {848, 1712},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{-42, -146, -43},0, {912, 1616},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{-42, -146, 43},0, {912, 1776},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{1, -148, 60},0, {1008, 1776},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{1, -148, -60},0, {1008, 1616},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{43, -150, 43},0, {1104, 1776},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{43, -150, -43},0, {1104, 1616},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{61, -151, 0},0, {1168, 1712},{0xFB, 0x81, 0x0, 0xFF}}},
	{{{-42, -146, 43},0, {1264, 1840},{0xB6, 0xB4, 0x46, 0xFF}}},
	{{{-56, -95, 0},0, {1006, 1552},{0x81, 0x7, 0x0, 0xFF}}},
	{{{-59, -146, 0},0, {1006, 1840},{0x99, 0xB5, 0x0, 0xFF}}},
	{{{-39, -96, 42},0, {1264, 1552},{0xA7, 0x7, 0x5B, 0xFF}}},
	{{{1, -148, 60},0, {1488, 1840},{0xFE, 0xB2, 0x65, 0xFF}}},
	{{{3, -98, 58},0, {1488, 1552},{0x1, 0x5, 0x7F, 0xFF}}},
	{{{43, -150, 43},0, {1264, 1840},{0x42, 0xAE, 0x47, 0xFF}}},
	{{{45, -100, 42},0, {1264, 1552},{0x58, 0xFF, 0x5C, 0xFF}}},
	{{{61, -151, 0},0, {1006, 1840},{0x60, 0xAC, 0x0, 0xFF}}},
	{{{45, -100, 42},0, {1264, 1552},{0x58, 0xFF, 0x5C, 0xFF}}},
	{{{43, -150, 43},0, {1264, 1840},{0x42, 0xAE, 0x47, 0xFF}}},
	{{{62, -101, 0},0, {1006, 1552},{0x7F, 0xFD, 0x0, 0xFF}}},
	{{{43, -150, -43},0, {752, 1840},{0x43, 0xAE, 0xBA, 0xFF}}},
	{{{45, -100, -42},0, {752, 1552},{0x5A, 0xFF, 0xA6, 0xFF}}},
	{{{1, -148, -60},0, {528, 1840},{0xFD, 0xB1, 0x9D, 0xFF}}},
	{{{3, -98, -59},0, {528, 1552},{0x0, 0x2, 0x81, 0xFF}}},
	{{{-42, -146, -43},0, {752, 1840},{0xB6, 0xB4, 0xBA, 0xFF}}},
	{{{-39, -96, -42},0, {752, 1552},{0xA6, 0x5, 0xA6, 0xFF}}},
	{{{-59, -146, 0},0, {1006, 1840},{0x99, 0xB5, 0x0, 0xFF}}},
	{{{-56, -95, 0},0, {1006, 1552},{0x81, 0x7, 0x0, 0xFF}}},
	{{{-16, -183, -13},0, {1008, 1712},{0xD9, 0x1E, 0x8B, 0xFF}}},
	{{{-16, -183, 13},0, {1008, 1712},{0xD9, 0x1E, 0x75, 0xFF}}},
	{{{8, -100, 0},0, {1008, 1712},{0x1B, 0x7C, 0x0, 0xFF}}},
	{{{1, -191, 0},0, {1008, 1712},{0x7F, 0xF7, 0x0, 0xFF}}},
};

Gfx bobomb_006_offset_mesh_layer_4_tri_1[] = {
	gsSPVertex(bobomb_006_offset_mesh_layer_4_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(4, 6, 5, 0),
	gsSP1Triangle(7, 5, 6, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(9, 8, 11, 0),
	gsSP1Triangle(12, 11, 8, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(13, 14, 15, 0),
	gsSPVertex(bobomb_006_offset_mesh_layer_4_vtx_1 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 0, 3, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(5, 6, 7, 0),
	gsSP1Triangle(8, 7, 6, 0),
	gsSP1Triangle(7, 8, 9, 0),
	gsSP1Triangle(10, 9, 8, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(15, 14, 13, 0),
	gsSP1Triangle(14, 15, 12, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_000_offset_009_mesh_layer_4_vtx_0[8] = {
	{{{128, -59, -65},0, {2, -16},{0x7E, 0xFF, 0xF4, 0xFF}}},
	{{{133, 34, -24},0, {482, 974},{0x7E, 0xFF, 0xF4, 0xFF}}},
	{{{133, -55, -17},0, {482, -16},{0x7E, 0xFF, 0xF4, 0xFF}}},
	{{{128, 30, -72},0, {2, 974},{0x7E, 0xFF, 0xF4, 0xFF}}},
	{{{133, -55, 17},0, {482, -16},{0x7E, 0x0, 0xC, 0xFF}}},
	{{{133, 34, 24},0, {482, 974},{0x7E, 0x0, 0xC, 0xFF}}},
	{{{128, 30, 73},0, {992, 974},{0x7E, 0x0, 0xC, 0xFF}}},
	{{{128, -59, 66},0, {992, -16},{0x7E, 0x0, 0xC, 0xFF}}},
};

Gfx bobomb_000_offset_009_mesh_layer_4_tri_0[] = {
	gsSPVertex(bobomb_000_offset_009_mesh_layer_4_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};

Vtx bobomb_008_offset_mesh_layer_4_vtx_0[13] = {
	{{{-1, -38, 0},0, {2512, 1552},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-1, 65, 0},0, {1552, 1552},{0x0, 0x0, 0x81, 0xFF}}},
	{{{102, -38, 0},0, {2512, 2512},{0x0, 0x0, 0x81, 0xFF}}},
	{{{102, 65, 0},0, {1552, 2512},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-1, -38, 0},0, {2512, 2512},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-103, -38, 0},0, {2512, 1552},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-1, 65, 0},0, {1552, 2512},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-103, 65, 0},0, {1552, 1552},{0x0, 0x0, 0x81, 0xFF}}},
	{{{18, -46, 0},0, {528, 2160},{0x7F, 0x9, 0x0, 0xFF}}},
	{{{-1, -46, -20},0, {528, 2032},{0x0, 0x9, 0x81, 0xFF}}},
	{{{-1, 219, 0},0, {1136, 2032},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-21, -46, 0},0, {528, 1904},{0x81, 0x9, 0x0, 0xFF}}},
	{{{-1, -46, 20},0, {528, 2032},{0x0, 0x9, 0x7F, 0xFF}}},
};

Gfx bobomb_008_offset_mesh_layer_4_tri_0[] = {
	gsSPVertex(bobomb_008_offset_mesh_layer_4_vtx_0 + 0, 13, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 12, 8, 0),
	gsSPEndDisplayList(),
};


Gfx mat_bobomb_BobBody[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, bobomb_BlackBobBody_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 252),
	gsSPSetLights1(bobomb_BobBody_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bobomb_BobBody[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx mat_bobomb_RedBobBody[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, bobomb_RedBobBody_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 252),
	gsSPSetLights1(bobomb_BobBody_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bobomb_RedBobBody[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx mat_bobomb__3D_Black_Bomb[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, bobomb_bombhei_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 6, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 6, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 252),
	gsSPSetLights1(bobomb__3D_Black_Bomb_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bobomb__3D_Black_Bomb[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx mat_bobomb__3D_Red_Bomb[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, bobomb_red_bombhei_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 6, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 6, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 252),
	gsSPSetLights1(bobomb__3D_Red_Bomb_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bobomb__3D_Red_Bomb[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx mat_bobomb_BobEye[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, bobomb_Eyes_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(bobomb_BobEye_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bobomb_BobEye[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx bobomb_000_displaylist_mesh_layer_4[] = {
	gsSPDisplayList(mat_bobomb_BobBody),
	gsSPDisplayList(bobomb_000_displaylist_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bobomb_BobBody),
	gsSPEndDisplayList(),
};

Gfx bobomb_000_displaylist_red_mesh_layer_4[] = {
	gsSPDisplayList(mat_bobomb_RedBobBody),
	gsSPDisplayList(bobomb_000_displaylist_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bobomb_RedBobBody),
	gsSPEndDisplayList(),
};

Gfx bobomb_000_offset_005_mesh_layer_4[] = {
	gsSPDisplayList(mat_bobomb__3D_Black_Bomb),
	gsSPDisplayList(bobomb_000_offset_005_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bobomb__3D_Black_Bomb),
	gsSPEndDisplayList(),
};

Gfx bobomb_000_offset_008_mesh_layer_4[] = {
	gsSPDisplayList(mat_bobomb__3D_Black_Bomb),
	gsSPDisplayList(bobomb_000_offset_008_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bobomb__3D_Black_Bomb),
	gsSPEndDisplayList(),
};

Gfx bobomb_006_offset_mesh_layer_4[] = {
	gsSPDisplayList(mat_bobomb__3D_Black_Bomb),
	gsSPDisplayList(bobomb_006_offset_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bobomb__3D_Black_Bomb),
	gsSPEndDisplayList(),
};

Gfx bobomb_000_offset_009_mesh_layer_4[] = {
	gsSPDisplayList(mat_bobomb_BobEye),
	gsSPDisplayList(bobomb_000_offset_009_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bobomb_BobEye),
	gsSPEndDisplayList(),
};

Gfx bobomb_008_offset_mesh_layer_4[] = {
	gsSPDisplayList(mat_bobomb__3D_Black_Bomb),
	gsSPDisplayList(bobomb_008_offset_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_bobomb__3D_Black_Bomb),
	gsSPEndDisplayList(),
};



Gfx bobomb_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

