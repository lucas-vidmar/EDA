#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "background.h"
#include "Bird.h"


#define UNIDAD 10
#define ERROR 1
#define SUCCESS 0
#define RUNNINGSPEED 10
#define STEP 0.1
#define REFRESHRATE 30
#define WIDTH 100.0
#define HEIGHT 50.0

//clase

class allegroEssentials_t
{
public:

	allegroEssentials_t() //constructor default
	{
		display = NULL;
		font = NULL;
		queue = NULL;
	}

	/*Prototipos*/
	/*Recieves width and height, returns NULL pounter if fail*/
	allegroEssentials_t(int width, int height);

	//getters
	ALLEGRO_DISPLAY* getDisplay() { return display; }
	ALLEGRO_FONT* getFont() { return font; }
	ALLEGRO_EVENT_QUEUE* getQueue() { return queue; }

	//setters
	void setDisplay(ALLEGRO_DISPLAY* display_c) { display = display_c; return; }
	void setFont(ALLEGRO_FONT* font_c) { font = font_c; return; }
	void setQueue(ALLEGRO_EVENT_QUEUE* queue_c) { queue = queue_c; return; }

private:

	/*Data*/
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT_QUEUE* queue;
};

/*Prototipos*/

/*|Initializes Allegro|*/


int get_keyboard(ALLEGRO_EVENT_QUEUE *);

/*|Terminates Allegro structures|*/
/*Recieves essentials class and destroys allegro objects*/
void endAllegro(allegroEssentials_t* screen);

/*|Updates object position|*/
/*Recieves essentials, background, object, previous position vector and next position vector*/
void objectUpdate(allegroEssentials_t* allegro, background_t* base, Bird* object, int cant);

/*|Updates object position in parts|*/
/*Recieves intial and ending position, aswell as multiplier and count var*/
void microUpdate(int cant, double* pos, const double* prev, const double* next, const int i, const double multiplier);

/*|Updates background|*/
/*Recieves essentials and background*/
void backgroundUpdate(allegroEssentials_t* allegro, background_t* base);

/*|Shows PopUp|*/
/*Receieves words, essentials, width and height of text*/
int popUp(const char* word, allegroEssentials_t* screen, int ancho, int alto);

/*|Waits till display is closed|*/
/*Receieves queue. Returns true if close button was pressed*/
bool displayQuit(ALLEGRO_EVENT_QUEUE* queue);

int count(double* array);

#endif