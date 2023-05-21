#include "background.h"

background_t::background_t(int ancho_c, int alto_c) {

	bitmap = al_load_bitmap("sky.png"); //setting bitmap
	ancho = ancho_c;
	alto = alto_c;

	return;
}