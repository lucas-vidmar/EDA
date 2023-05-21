#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "DrawableObject.h"


class background_t : public DrawableObject
{


public:
	background_t(void);
	~background_t(void);
	void draw(void);

	ALLEGRO_BITMAP * get_images_background(void);


private:
	double sizeX;
	double sizeY;


	ALLEGRO_BITMAP *images_background;

	bool init_okey;
};



#endif // !BACKGROUND_H


