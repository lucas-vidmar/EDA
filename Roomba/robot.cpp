#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#define _USE_MATH_DEFINES
#include <time.h>
#include <math.h>

bool Robot_t::move(int maxX, int maxY)
{
	double a = x + cos(angle*M_PI / 180.0);		//sumandole a la posicion inicial el coseno y el seno del angulo (para las coordenadas 
	double b = y + sin(angle*M_PI / 180.0);		//...X e Y, respectivamente) consigo la siguiente posicion del robot segun su angulo
	if (a >= maxX || b >= maxY || a <= 0.0 || b <= 0.0)	//si se pasa del limite
	{
		angle = (double)rand() / (RAND_MAX / 360);	//busco un nuevo angulo random
		return false;	//Devuelvo false indicando que no se movio
	}
	else
	{	//caso contrario
		x = a;		//defino nueva posicion X
		y = b;		//defino nueva posicion Y
		return true;	//Devuelvo true indicando que hubo movimiento
	}
}
double Robot_t::getX()
{
	return x;
}
double Robot_t::getY()
{
	return y;
}
double Robot_t::getAngle()
{
	return angle;
}

Robot_t* initRobots(int cant_Robots, Piso_t* piso)
{
	Robot_t* robots = NULL;		//defino robots
	robots = (Robot_t*)malloc(sizeof(Robot_t)*cant_Robots);	//reservo espacio para la cantidad de robots asignada

	if (robots != NULL)
	{
		//srand(time(NULL));		//semilla para randomizar
		for (int i = 0; i < cant_Robots; i++)
		{	/*randomizo posicion y angulo como double para cada robot*/
			double robotX = (double)rand() / (double)(RAND_MAX / (piso->ancho));		//random double www.stackoverflow.com
			double robotY = (double)rand() / (double)(RAND_MAX / (piso->largo));
			double angle_ = (double)rand() / (double)(RAND_MAX / 360);
			(robots + i)->x = robotX;
			(robots + i)->y = robotY;
			(robots+i)->angle = angle_;
		}
	}
	return robots;
}

int movement(Robot_t* robots, int cant_Robots, Piso_t*piso, int tick_counter)
{
	static int counter2 = 0;
	

	for (int i = 0; i < cant_Robots; i++)	//mueve cada robot
	{
		(robots + i)->move(piso->ancho, piso->largo);
		//
		//if ((piso->get_status_baldosa((int)((robots + i)->x), (int)((robots + i)->y))) == SUCIO)
		//{
			piso->clean_baldosa((int)((robots + i)->x), (int)((robots + i)->y));
			/*if (counter2 < 50)
			{
			printf("llama clean\n");
			}*/
		//}
		
		/*if (counter2 < 50)
		{
			printf("clean x:%d, y:%d\n", (int)((robots + i)->x), (int)((robots + i)->y));
			printf("R%d: x:%f y:%f\n", i, ((robots + i)->x), ((robots + i)->y));
			counter2++;
		}*/
		
	}
	//tick_counter++;		//y aumenta el contador de ticks
	/*
	printf(".\n");
	*/
	return tick_counter+1;	//Devuelve contador de ticks
}

void destroy_robot(Robot_t* robots)
{
	free(robots);
	robots = NULL;
	return;
}