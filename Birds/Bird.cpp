#include <iostream>
#include "Bird.h"



using namespace std;

/*Constructors*/
void Bird::helpConstruct(double n, double m) {
	p.setEverything(randomNum(INF_LIMIT, n), randomNum(INF_LIMIT, m), randomNum(INF_LIMIT, SUP_LIMIT_ANGLE));
	texture = al_load_bitmap("bird.png");
}

Bird::Bird(double n, double m) {
	helpConstruct(n, m);
	speed = randomNum(INF_LIMIT, MAX_SPEED);
}

Bird::Bird()
{
	texture = NULL;
}

Bird::Bird(double speed_, double n, double m) {
	helpConstruct(n, m);
	speed = speed_;
}

void Bird::setBitmap(ALLEGRO_BITMAP* bitmap_c) { 
	texture = bitmap_c; 
	return; 
}

ALLEGRO_BITMAP* Bird::getBitmap() { 
	return texture; 
}

/*Functions*/
double Bird::whereIsBirdX() {
	return p.getX();
}

double Bird::whereIsBirdY() {
	return p.getY();
}
double Bird::whereIsBirdAngle() {
	return p.Get_Angle();
}

bool Bird::intersect(Bird& b, double eyeshight) {
	return sqrt(pow(b.whereIsBirdX() - p.getX(), 2) + pow(b.whereIsBirdY() - p.getY(), 2)) <= (eyeshight * 2);
}

void Bird::setSpeed(double newSpeed) 
{	speed = newSpeed;
}

void Bird::project(Bird* birds, int cantBirds, double eyeshight, double jiggle) {
	int birdsIntersect = 0;
	int angleSum = 0;
	for (int i = 0; i < cantBirds; i++) {
		if (intersect(birds[i], eyeshight)) {
			angleSum += birds[i].whereIsBirdAngle();
			birdsIntersect++;
		}
	}
	newAngle = (angleSum/birdsIntersect)+jiggle;
}

void Bird::moveBird(int n, int m)  /*n es en x y m es un y*/
{ 
	double x_ = whereIsBirdX()+cos((PI / 180)*newAngle)*speed;
	double y_ = whereIsBirdY()+sin((PI / 180)*newAngle)*speed;

	if (y_ > m) {
		y_ -= m;
	
	}
	else if (y_ < 0) {
		y_ += m;
	
	}
	if (x_ < 0) {
		x_ += n;
		
	}
	else if (x_ > n) {
		x_ -= n;
	
	}
    p.setEverything(x_, y_, newAngle);
}

void Bird::setRandomSpeed() {
	speed = randomNum(INF_LIMIT, MAX_SPEED);
}

double Bird::randomNum(double min, double max) {
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}

void Bird::speechChange(bool increment) {
	if (!increment) {
		if (speed - 1 > 0) {
			speed -= 1;
		}
	}
	else {
		if (speed + 1 < MAX_SPEED) {
			speed += 1;
		}
	}
}
