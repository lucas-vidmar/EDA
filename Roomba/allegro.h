#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>
#include <math.h>
#define PI 3.1415

#define TILESIDE 50
#define ROBOTSIDE 32
#define REFRESHRATE 30
#define ERROR 0
#define SUCCESS 0
#define RUNNINGSPEED 0.000000001
#define STEP 0.01
#define MAXROBOTS 100

//clase

class allegroDisplay_t
{
public:

	allegroDisplay_t()
	{
		display = NULL;
		font = NULL;
		robot = NULL;
		cleanTile = NULL;
		dirtyTile = NULL;
		blackPixel = NULL;
		queue = NULL;
	}


	/*Data*/
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* robot;
	ALLEGRO_BITMAP* cleanTile;
	ALLEGRO_BITMAP* dirtyTile;
	ALLEGRO_BITMAP* blackPixel;
	ALLEGRO_EVENT_QUEUE* queue;
};

/*Prototipos*/

/*|Initializes Allegro|*/
/*Recieves width and height, returns NULL pounter if fail*/
allegroDisplay_t* iniAllegro(int width, int height);

/*|Moves robots to the next step|*/
/*Recieves display and robot class, aswell as width, height and robot quantity.*/
void robotUpdate(allegroDisplay_t* screen, Piso_t* floor, Robot_t* robots, int ancho, int largo, int cant);

/*|Shows PopUp|*/
/*Recieves a pointer to the word, a pointer to display and a pointer to floor. Returns 0  if fail*/
int popUp(const char* word, allegroDisplay_t* screen, int ancho, int alto);

/*|Graphs|*/
/*Recieves array to all tick counts. Graphs data in mode 2*/
int graph(double* tickCount);

/*|Terminates Allegro structures|*/
/*Recieves display class and destroys allegro objects*/
void endAllegro(allegroDisplay_t* screen);

/*|Shows floor in its current state|*/
/*Recieves display class and piso class. Updates floor state and moves graphically*/
void floorUpdate(allegroDisplay_t* screen, Piso_t* floor);

/*|Updates position step by step|*/
/*Recieves initial and ending position aswell as multiplier, and returns position vector*/
void microUpdate(double vec[MAXROBOTS][2], int i, double Xo, double Yo, double Xf, double Yf, double multiplier);

/*|Checks if exit button was pressed|*/
/*Recieves a pointer to the queue event. Returns true if button was pressed, false if not.*/
bool displayQuit(ALLEGRO_EVENT_QUEUE* queue);

/*|Auxiliary function, counts elemnts|*/
/*Recieves a pointer to array. Returns element quantity*/
int count(double* array);

#endif