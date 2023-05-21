#pragma once
#include "DrawableObject.h"
#include <cmath>
#include <math.h>
//#define _MATH_DEFINES_DEFINED
#define M_PI       3.14159265358979323846

#define CANT_TEXTURES_WORM_WALKING	15
#define	CANT_TEXTURES_WORM_JUMPING	10

enum class OrientType { left , right };
enum class state {idle , start_walk , walking , start_jump ,jumping };

class worm : public DrawableObject
{
public:

	worm();
	~worm();

	void start_walking(void);
	void walking(void);

	void start_jumping(void);
	void jumping(void);

	void update(void);


	void draw();	//la imagen asociada es un puntero en la clase padre



	//Getters

	OrientType getOrient();
	double getAngle();
	state get_state();
	double getSpeedJ();

	//Setters
	void setPosition_x(double x);
	void setPosition_y(double y);
	void setOrient(OrientType newOrient);
	void setAngle_j(double newAngle);

private:
	OrientType Orient;				//forma de setear Orient = OrientType::left;
	double angle_jump;				//La consigna dice que los worms siempre saltan con 60grados, me parecio interesante
									//ponerla como una variable por si nos interesa en algun momento modificarla
									//aunque ya de entrada la vamos a dejar hardcodeada
	double speed_jump;
	int key_time_count;
	state worm_state;



	ALLEGRO_BITMAP *images_walking[CANT_TEXTURES_WORM_WALKING];
	ALLEGRO_BITMAP *images_jump[CANT_TEXTURES_WORM_JUMPING];

	bool init_okey;
};

