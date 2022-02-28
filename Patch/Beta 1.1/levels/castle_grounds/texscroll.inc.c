void scroll_castle_grounds_dl_Level_mesh_layer_5_vtx_4() {
	int i = 0;
	int count = 13;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(castle_grounds_dl_Level_mesh_layer_5_vtx_4);

	deltaY = (int)(-2.929999828338623 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_castle_grounds_dl_Level_mesh_layer_5_vtx_5() {
	int i = 0;
	int count = 10;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(castle_grounds_dl_Level_mesh_layer_5_vtx_5);

	deltaX = (int)(-0.17000000178813934 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_castle_grounds() {
	scroll_castle_grounds_dl_Level_mesh_layer_5_vtx_4();
	scroll_castle_grounds_dl_Level_mesh_layer_5_vtx_5();
}
