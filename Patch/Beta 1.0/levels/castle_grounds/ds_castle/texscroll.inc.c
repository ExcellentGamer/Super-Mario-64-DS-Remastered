void scroll_ds_castle_000_displaylist_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 13;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(ds_castle_000_displaylist_mesh_layer_5_vtx_0);

	deltaY = (int)(-1.5499999523162842 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_ds_castle_000_displaylist_mesh_layer_5_vtx_6() {
	int i = 0;
	int count = 9;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(ds_castle_000_displaylist_mesh_layer_5_vtx_6);

	deltaX = (int)(0.1899999976158142 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_castle_grounds_level_geo_ds_castle() {
	scroll_ds_castle_000_displaylist_mesh_layer_5_vtx_0();
	scroll_ds_castle_000_displaylist_mesh_layer_5_vtx_6();
}
