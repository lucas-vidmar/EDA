#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "worm.h"
#include "background.h"
#include "DrawableObject.h"

#define BPS_TO_SECS(x)        (1.0 / (x))
#define FPS 50

#define UNIDAD 1
#define ERROR 1
#define SUCCESS 0
#define RUNNINGSPEED 10
#define STEP 0.1
#define REFRESHRATE 50
#define FONTNAME "gothicRound.ttf"

enum keys { KeyA = 0, KeyD, KeyLeft, KeyRight, KeyW, KeyUp};

class allegroEssentials_t
{
public:

	/*Builder*/
	allegroEssentials_t() //constructor default
	{
		display = NULL;
		font = NULL;
		queue = NULL;
		timer_refresh = NULL;
	}

	/*Destroyer*/
	~allegroEssentials_t();


	/*Prototipos*/
	/*Recieves width and height, returns NULL pounter if fail*/
	allegroEssentials_t(int width, int height);

	/*|Copies allegro events to event queue|*/
	/*Recieves event queue returns. Returns ERROR if queue was full or failed*/
	bool transferQueue(Queue* queueC, ALLEGRO_TIMER* timer[KeyUp + 1]);

	/*Getters*/
	ALLEGRO_DISPLAY* getDisplay() { return display; }
	ALLEGRO_FONT* getFont() { return font; }
	ALLEGRO_EVENT_QUEUE* getQueue() { return queue; }
	ALLEGRO_EVENT getLastEvent() { return lastEvent; }

	void startTimerRefresh(void);
	ALLEGRO_TIMER * getTimerRefresh(void);

	/*Setters*/
	void setDisplay(ALLEGRO_DISPLAY* display_c) { display = display_c; return; }
	void setFont(ALLEGRO_FONT* font_c) { font = font_c; return; }
	void setQueue(ALLEGRO_EVENT_QUEUE* queue_c) { queue = queue_c; return; }

private:

	/*Data*/
	ALLEGRO_EVENT lastEvent;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER * timer_refresh;
	ALLEGRO_SAMPLE* sample;

	bool init_done;
};

/*Prototipos*/

int get_keyboard(ALLEGRO_EVENT_QUEUE *);

/*|Terminates Allegro structures|*/
/*Recieves essentials class and destroys allegro objects*/
void endAllegro(allegroEssentials_t* screen);

/*|Updates background|*/
/*Recieves essentials and background*/
void backgroundUpdate(allegroEssentials_t* allegro, background_t* base);

#endif