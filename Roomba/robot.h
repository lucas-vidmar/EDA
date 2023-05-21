#ifndef ROBOT_H
#define ROBOT_H

#include "piso.h"

/*Clase de robot*/
class Robot_t
{
public:
	Robot_t(double x_, double y_, double angle_)	//constructores
	{
		x = x_;
		y = y_;
		angle=angle_;
	}
	Robot_t()
	{
		x = 0.0;
		y = 0.0;
	}

	/*mueve el robot acorde a su posicion y angulo. Recibe como parametro los valores maximos. 
	Si se pasase de esos valores, cambia el angulo. Devuelve 'true' si hubo movimiento, 'false' si solo cambio el angulo*/
	bool move(int maxX, int maxY);
	
	double getX();		//getter coordenada X
	double getY();		//getter coordenada Y
	double getAngle();	//getter angle
	
	double x;
	double y;
	double angle;
};

/*Inicia los robots con posicion y angulo random dentro de un piso. Devuelve un puntero al "string" de robots*/
Robot_t* initRobots(int cant_Robots, Piso_t* piso);

/*Hace el movimiento de un robot e incrementa el contador de ticks. Devuelve contador de ticks.*/
int movement(Robot_t* robots, int cant_Robots, Piso_t*piso, int tick_counter);

/*Destruyelos robots*/
void destroy_robot(Robot_t* robots);
#endif
