#pragma once

#include "drawableObject.h"
#include "AllegroServices.h"

class text: public drawableObject {

public:
	/*Default Builder*/
	text(){
		posX = 0;
		posY = 0;
		sizeX = 0;
		sizeY = 0;
		texture = NULL;
		color = NULL;
		font = al_load_ttf_font("arial_narrow_7.ttf", TEXT_SIZE, TEXT_FLAG);;
	}
	/*Builder*/
	text(double posX_, double posY_, const char* text_, const char* color_) {
		posX = posX_;
		posY = posY_;
		texto = text_;
		texture = NULL;
		color = color_;
		font = al_load_ttf_font("arial_narrow_7.ttf", TEXT_SIZE, TEXT_FLAG);
	}
	/*Destroyer*/
	~text(){}

	/*Setter*/
	void set_text(const char* text_) { texto = text_; }

	/*Getter*/
	const char* get_text(void) { return texto; }

	/*Methods*/
	void drawObject();
	void dedrawObject();

protected:
	const char* texto;
	const char* color;
	ALLEGRO_FONT* font;
};

