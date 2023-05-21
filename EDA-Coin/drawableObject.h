#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <iostream>

class drawableObject
{
public:
	/*Default Builder*/
	drawableObject() {
		texture = NULL;
		posX = 0;
		posY = 0;
		sizeX = 0;
		sizeY = 0;
	}
	/*Builder*/
	drawableObject(const char* texture_, double posX_, double posY_, double sizeX_, double sizeY_) {
		texture = al_load_bitmap(texture_);
		if (texture == nullptr)
			delete this;
		posX = posX_;
		posY = posY_;
		sizeX = sizeX_;
		sizeY = sizeY_;
	}
	/*Destroyer*/
	~drawableObject() {}

	/*Getter*/
	double get_posX(void) { return posX; }
	double get_posY(void) { return posY; }
	double get_sizeX(void) { return sizeX; }
	double get_sizeY(void) { return sizeY; }

	/*Methods*/
	virtual void drawObject() = 0;
	virtual void dedrawObject() = 0;
	virtual void changePos(double posX_, double posY_);
	double get_regionXMax(void) { return posX + sizeX / 2; }
	double get_regionXMin(void) { return posX - sizeX / 2; }
	double get_regionYMax(void) { return posY + sizeY / 2; }
	double get_regionYMin(void) { return posY - sizeY / 2; }

protected:
	ALLEGRO_BITMAP* texture;
	double posX;
	double posY;
	double sizeX;
	double sizeY;
};

