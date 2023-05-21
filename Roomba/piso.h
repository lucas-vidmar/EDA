#ifndef PISO_H
#define PISO_H

#define LIMPIO true
#define SUCIO false

#include <iostream>
#include <stdio.h>

class Piso_t
{
public:

	Piso_t()
	{
		baldosas = NULL;
		ancho = 0;
		largo = 0;
	}

	/*Indica si el piso esta completamente limpio. Devuelve false si no lo esta.*/
	bool is_floor_clean();

	/*Indica estado de una baldosa. false-->sucio; true-->limpio.*/
	bool get_status_baldosa(int baldosaX, int baldosaY);

	/*Limpia una baldosa, segun coordenadas X e Y.*/
	void clean_baldosa(int baldosaX, int baldosaY);

	int get_largo();	//getter de largo
	int get_ancho();	//getterde ancho

	bool* baldosas;
	int ancho;
	int largo;
};

/*Inicializa el piso, poniendo todos en false. Devuelve puntero al piso.*/
Piso_t* init_Piso(int ancho_, int largo_);

void destroy_piso(Piso_t*piso);

#endif