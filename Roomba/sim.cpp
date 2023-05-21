#include "sim.h"
#include "allegro.h"
#include "piso.h"
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <sstream>
#include <string.h>
using namespace std;


sim_t* CrearSim(int ancho_, int largo_, int cant_robots_, int modo_)
{
	sim_t* simulation = NULL;			//creo una simulacion
	simulation = (sim_t*)malloc(sizeof(sim_t));	//reservo memoria
	
	if (simulation != NULL)			//si se pudo guardar memoria
	{
		switch (modo_)		//defino el modo de la simulacion
		{
		case 1:case 2:

		{
			simulation->modo = modo_;
			break;
		}
		default:		//si se ingresaron valores no validos para el modo
		{
			//imprimir "ingrese modo valido (1 o 2)"
			free(simulation);	//libera memoria
			simulation = NULL;
			return simulation;		//termina devolviendo NULL
		}
		}
		//Defino los elementos de la simulacion con valores iniciales
		simulation->cant_robots = cant_robots_;
		simulation->tickcount = 0;
		simulation->piso = init_Piso(ancho_, largo_);
		simulation->robots = initRobots(cant_robots_, (simulation->piso));
	}
	return simulation;
}

void destroy_sim(sim_t* simulation)
{
	
	destroy_piso(simulation->piso);
	destroy_robot(simulation->robots);
	free(simulation);
	simulation = NULL;

	return;
}

int getTickCount(sim_t* simulation)
{
	return simulation->tickcount;
}

void simulate(sim_t* s) {

	s->tickcount = 0;
	string temp_str;
	stringstream strs;
	char* numberChar;

	switch (s->modo)
	{
	case mode1:
		floorUpdate(s->screen, s->piso);

		while (!s->piso->is_floor_clean())
		{

			bool quit = false;

			quit = displayQuit(s->screen->queue); //check if quit button is pressed

			if (!quit) { //if quit button is not pressed

				robotUpdate(s->screen, s->piso, s->robots, s->piso->ancho, s->piso->largo, s->cant_robots); //updating robots

				cleanFloor(s->piso, s->robots, s->cant_robots); //cleaning floor

				al_flip_display(); //update display

				s->tickcount++;

				printf("Tick Count = %d \n", s->tickcount);
			}
			else
				break; //quit button pressed, end loop
		}

		floorUpdate(s->screen, s->piso); //updating floor one more time
		al_flip_display();

		strs << s->tickcount;
		temp_str = strs.str();
		numberChar = (char*)temp_str.c_str();

		popUp(numberChar, s->screen, s->piso->ancho, s->piso->largo);
		popUp("ended", s->screen, s->piso->ancho, s->piso->largo);


		endAllegro(s->screen);

		break;
	case mode2:
		bool floor_status = false;
		while (!floor_status)
		{
			s->tickcount = movement(s->robots, s->cant_robots, s->piso, s->tickcount);
			floor_status = s->piso->is_floor_clean();

		}
		break;
	/*default:
		break;*/
	}
	



}


void cleanFloor(Piso_t* floor, Robot_t* robots, int quant) {

	for (int i = 0; i < quant; i++) {
		floor->clean_baldosa((int)(robots + i)->getX(),(int)(robots + i)->getY()); //limpio todas las baldosas cuyas coordenadas esten ocupadas por robot
	}
}