#include "button.h"

void button::drawObject(void) {
	if (state == buttonStates::NotPressed) {
		al_draw_bitmap(texture, posX - sizeX / 2, posY - sizeY / 2, ALLEGRO_FLIP_HORIZONTAL);
		if (text != "none")
			al_draw_text(font, al_map_rgb(255, 255, 255), posX - sizeX / 2 + 10, posY - sizeY / 2 + 12, 0, text);
	}
	else if (state == buttonStates::Pressed) {
		al_draw_bitmap(pressedTexture, posX - sizeX / 2, posY - sizeY / 2, ALLEGRO_FLIP_HORIZONTAL);
		if (text != "none")
			al_draw_text(font, al_map_rgb(255, 255, 255), posX - sizeX / 2 + 10, posY - sizeY / 2 + 12, 0, text);
	}
	
}

void button::pressButton(void) {
	al_rest(0.1);
	if (state == buttonStates::NotPressed) {
		this->toggle_state();
		std::cout << this->get_state() << std::endl;
		this->drawObject();
	}
	else if (state == buttonStates::Pressed) {
		this->toggle_state();
		std::cout << this->get_state() << std::endl;
		this->drawObject();
	}
}

void button::releaseButton(void) {
	al_rest(0.1);
	if (state == buttonStates::Pressed) {
		this->toggle_state();
		this->drawObject();
	}
		
}