#include "text.h"

void text::drawObject(void) {
	if (texto != "none") {
		if (color == "black")
			al_draw_text(font, al_map_rgb(0, 0, 0), posX, posY, ALLEGRO_ALIGN_CENTRE, texto);
		if (color == "white")
			al_draw_text(font, al_map_rgb(255, 255, 255), posX, posY, ALLEGRO_ALIGN_CENTRE, texto);
		if (color == "red")
			al_draw_text(font, al_map_rgb(255, 0, 0), posX, posY, ALLEGRO_ALIGN_CENTRE, texto);
	}
}

void text::dedrawObject(void) {
	int bbx, bby, bbw, bbh;
	al_get_text_dimensions(font, texto, &bbx, &bby, &bbw, &bbh);
	al_draw_filled_rectangle(posX - bbw / 2 - 10, posY - bbh / 2, posX + bbw / 2 + 5, posY + bbh / 2 + 10, al_map_rgb(255, 255, 255));
}