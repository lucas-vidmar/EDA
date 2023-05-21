#include "piso.h"

bool Piso_t::is_floor_clean()
{
	double w = ancho;
	double l = largo;
	for (int i = 0; i < (w*l); i++)	//recorro las baldosas
	{
		if (baldosas[i] == SUCIO)	//Si encuentro una sucia
		{
			return false;		//Devuelve false indicando que no esta completamente limpia
		}
	}
	return true;	//Caso contrario, devuelve true
}
bool Piso_t::get_status_baldosa(int baldosaX, int baldosaY)
{
	if (baldosas[(baldosaX*(ancho)) + baldosaY])
	{
		return LIMPIO;
	}
	else
	{
		return SUCIO;
	}
}
void Piso_t::clean_baldosa(int baldosaX, int baldosaY)
{
	baldosas[(baldosaY*ancho) + baldosaX] = LIMPIO;
	return;
}
int Piso_t::get_ancho()
{
	return ancho;
}
int Piso_t::get_largo()
{
	return largo;
}


Piso_t* init_Piso(int ancho_, int largo_)
{
	Piso_t* floor = NULL;		//Defino un piso
	floor = (Piso_t*)malloc(sizeof(Piso_t));	//le reservo espacio
	if (floor != NULL)	//si le pudo reservar espacio
	{
		floor->ancho = ancho_;	//Defino el ancho
		floor->largo = largo_;	//Defino el largo
		floor->baldosas = (bool*)malloc(sizeof(bool*)*ancho_*largo_);	//Reservo espacio para las baldosas
		if (floor->baldosas != NULL)	//si le pude reservar espacio
		{
			for (int i = 0; i < (ancho_*largo_); i++)
			{
				floor->baldosas[i] = SUCIO;		//inicializo todas como sucias
			}
		}
		else
		{		//caso contrario
			free(floor);	//libero el espacio reservado
			floor = NULL;
		}

	}
	return floor;
}

void destroy_piso(Piso_t*piso)
{
	//************************************************
	free(piso->baldosas);
	//************************************************
	free(piso);
	
	piso = NULL;
	return;
}