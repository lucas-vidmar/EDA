#ifndef BIRD_H
#define BIRD_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "Point.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define PI 3.1415

#define	DEFAULT_SPEED 2
#define MAX_SPEED 10 
#define MAX_RANDOM_JIGGLE_LIMIT 360
#define MAX_EYE_SIGHT 10
#define INF_LIMIT 0
#define SUP_LIMIT_ANGLE 360
#define BIRDSIDE 32 //size of bitmap side

class Bird {
public:
	//Comente la parte de allegro para que no tire error y mantener la jerarquia
	
	Bird();

	//Setters
	void setBitmap(ALLEGRO_BITMAP* bitmap_c);

	//Getters
	ALLEGRO_BITMAP* getBitmap();
	

	/*Prototipos*/
	// MBird(double speed, double n, double m);		//Lo comente porque inicializo cada pajaro afuera con numero random
	Bird(double n, double m);						//Lo comente porque inicializo cada pajaro afuera con numero random
	Bird(double speed_, double n, double m);
	void project(Bird* birds, int cantBirds, double eyeshight, double jiggle);
	double whereIsBirdX();
	double whereIsBirdY();
	double whereIsBirdAngle();
	void setSpeed(double newSpeed);
	void setRandomSpeed();
	void speechChange(bool increment);
	void moveBird(int n, int m);

private:
    Point p;
	double newAngle;
	double speed;
	bool intersect(Bird& b, double eyeshight); /*devuelve true si dos pajaros se influencian*/
	double randomNum(double max, double min);
	void helpConstruct(double n, double m);
	ALLEGRO_BITMAP* texture;
};

//Bird* iniBird();   //Comente la parte de allegro para que no tire error y mantener la jerarquia

#endif