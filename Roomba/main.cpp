#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "sim.h"
#include "robot.h"
#include "piso.h"
#include "allegro.h"
#include "pcmdl.h"

#define ERROR 0
#define SUCCESS 0
#define MAXROBOTS 100
#define MAXEVAL 1000
#define SENSITIVITY 0.1



typedef struct {
	int width;
	int height;
	int mode;
	int cant_robots;
}data_t;

int parseCallback(char *, char *, void *);	 //Declaracion de la funcion de callback

//Se fija si se paso todo lo necesario en la linea de comando
int chk_CmdLine(int argc, char*argv[]);

int main(int argc, char * argv[])
{
	data_t * UserData = (data_t*)malloc((sizeof(data_t)));
	srand(time(NULL));

	if (UserData == NULL)
	{
		printf( "Cannot allocate dynamic memory");
		return 0;
	}
	
	if (parseCmdline(argc, argv, parseCallback, UserData) <0 )
	{	
		free(UserData);
		return 0;
	}
	if (!chk_CmdLine(argc, argv))
	{
		free(UserData);
		return 0;
	}
	

	if (UserData->mode == mode1)
	{
		allegroDisplay_t* screen = iniAllegro(UserData->width, UserData->height); //screen struct
		if (screen != NULL)
		{
			sim_t * s = CrearSim(UserData->height, UserData->width, UserData->cant_robots, UserData->mode);
			if (s != NULL)
			{
				s->screen = screen;
				simulate(s);
				destroy_sim(s);
			}
			else
			{
				printf("Cannot allocate dynamic memory");
			}
		}
		else
		{
			printf("Cannot initialize allegro");
		}
	}
	else if (UserData->mode == mode2)
	{
		double histogram[MAXROBOTS];
		for (int i = 0; i < MAXROBOTS; i++)
		{
			histogram[i] = 0.0;
		}
		bool exit = false;
		int robot_count;
		for (robot_count = 1; exit == false; robot_count++)
		{
			double tick_count = 0;
					
					
			
			printf("\n\n");
			for (int i = 0; i < MAXEVAL; i++)
			{
				sim_t * s = CrearSim(UserData->height, UserData->width, robot_count, UserData->mode);
				if (s != NULL)
				{
					
					//printf("|x:%f| |y:%f| |Angle:%10f|\t", s->robots->x, s->robots->y, s->robots->angle);
					simulate(s);
					//printf("|T:%3d|\n", getTickCount(s));
					tick_count += getTickCount(s);
					
					destroy_sim(s);
				}
				else
				{
					printf("Cannot allocate dynamic memory");
					i = MAXEVAL;
				}
			}
					
			printf("\n|Tickcount %d: %f|\n",robot_count, tick_count);
			histogram[robot_count - 1] = tick_count / MAXEVAL;
			if (abs(histogram[robot_count - 1] - histogram[robot_count - 2]) < SENSITIVITY)
			{
				exit = true;
			}
			printf("|Robot %d: %f|\n", robot_count, histogram[robot_count - 1]);
			printf("----------------------------------------------------------\n");
		}
		printf("Press close button to end.\n");
		graph(histogram);
	}

	free(UserData);
}


int parseCallback(char* key, char* valor, void* UserData)
{
	if (key == NULL)		//Si pasa algun parametro
	{
		printf("No parameters allowed\n");
		return 0;
	}
	for (int i = 0; valor[i] != '\0'; i++)
	{
		if (valor[i] < '0' || valor[i]>'9')		//error si algun valor no es un numero
		{
			printf("Values can only be positive numbers\n");
			return 0;
		}
	}
	if (!atoi(valor))		//error si algun valor es igual a cero
	{
		printf("No value can be 0\n");
		return 0;
	}
	
	if (!strcmp(key, "width"))		//para width
	{
		if (atoi(valor) > 70)		//error si es mayor a 70
		{
			printf("Width has to be below 71\n");
			return 0;
		}
		else
		{
			((data_t*)UserData)->width = atoi(valor);
			return 1;
		}
	}
	if (!strcmp(key, "height"))		//para height
	{
		if (atoi(valor) > 100)		//error si es mayor a 100
		{
			printf("Height has to be below 101\n");
			return 0;
		}
		else
		{
			((data_t*)UserData)->height = atoi(valor);
			return 1;
		}
	}
	if (!strcmp(key, "mode"))	//para modo
	{
		int modo = atoi(valor);
		if (modo <= 0 || modo > 2) //error si pide modo distinito de 1 o 2
		{
			printf("Specify mode 1 or 2\n");
			return 0;
		}
		else
		{
			((data_t*)UserData)->mode = modo;
			return 1;
		}
	}
	if (!strcmp(key, "robots"))		//para robots
	{
		int robot = atoi(valor);
		if (robot >MAXROBOTS || robot<=0)		//error si robots se pasa del maximo, es negativo o igual a cero
		{
			printf("Specify robots between 1 and 100\n");
			return 0;
		}
		else
		{
			((data_t*)UserData)->cant_robots = robot;
			return 1;
		}
	}
	else
	{
		printf("Do not specify other options than height, width, robots and mode\n");	//error si encuentra una opcion que no sea ninguna de las anteriores
		return 0;
	}
	
}

int chk_CmdLine(int argc, char*argv[])
{
	
	int robots = 0, modo = 0, height = 0, width = 0;
	for (int i = 1; i<argc; i++)		//recorro la linea de comando
	{
		
		if (!strcmp(argv[i], "mode"))		//si encuentro mode
		{
			if (atoi(argv[i+1])==1)		//si el valor de mode es 1
			{
				if (argc == 9)		//y hay 9 elementos (4 parametros + 4 valores + nombre)
				{
					robots++;	//"defino" robots
				}
			}
			else if (atoi(argv[i + 1]) == 2)	//si el valor es 2
			{
				if (argc == 7)		//y hay 7 elementos (3 parametros + 3 valores + nombre)
				{
					robots++;		//"defino" robots
				}
			}
			modo++;		//"defino" modo
		}
		if (!strcmp(argv[i], "height"))		//si encuentro height, la "defino"
		{
			height = 1;
		}
		if (!strcmp(argv[i], "width"))	//si encuentro width, la "defino"
		{
			width = 1;
		}
	}
	if ((modo!=0)&&(height!=0)&&(width!=0)&&(robots!=0))	//si esta todo definido
	{
		return 1;		//devuelve OK
	}
	else
	{		//de lo contrario indica donde esta el error
		if (!modo)
		{
			printf("Specify mode 1 or 2.\n");
		}
		if (!height)
		{
			printf("Specify height higher than 0\n");
		}
		if (!width)
		{
			printf("Specify width higher than 0\n");
		}
		if (!robots)
		{
			printf("Specify robots higher than 0 for mode 1. For mode 2, do not specify robots.\n");
		}
		return 0;
	}
	return 1;
}