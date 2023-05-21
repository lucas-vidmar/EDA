#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class background_t
{
public:

	background_t() //constructor
	{
		alto = 0;
		ancho = 0;
		bitmap = NULL;
	}

	/*Prototipos*/

	/*|Initializes background|*/
	background_t(int alto, int ancho);

	//getters
	ALLEGRO_BITMAP* getBitmap() { return bitmap; }
	int getHeight() { return alto; }
	int getWidth() { return ancho; }

	//setters
	void setBitmap(ALLEGRO_BITMAP* bitmap_c) { bitmap = bitmap_c; return; }
	void setHeight(int alto_c) { alto = alto_c; return; }
	void setWidth(int ancho_c) { ancho = ancho_c; return; }


private:

	/*Data*/
	ALLEGRO_BITMAP* bitmap;
	int alto;
	int ancho;
};


#endif

