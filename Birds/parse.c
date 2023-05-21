
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"



int parseCallBack (const char* key, const char* value, void* datosDeUsuario)
{

	char data[MAXOPTIONS][2][MAXLENGTH]={{{0}}}; //utilizamos otro arreglo temporaneo para no confundirnos
	memcpy(data, datosDeUsuario, MAXOPTIONS*MAXLENGTH*2*(sizeof(char))); //igualamos los arreglos
	int ultimoValor=lastValue(data); //miro el ultimo valor

	if((ultimoValor)==(MAXOPTIONS-1))
	{
		printf("Supero el limite de %d opciones/parametros\n",MAXOPTIONS);
		return CB_ERR;
	}

	//checking if key is valid
	if (key!=NULL) //es opcion
	{ 
		if(validKey(key)) //check if key is valid
		{ 
			strcpy_s(data[ultimoValor][0], MAXLENGTH*sizeof(char),key);
		}
		else //key not valid
			return CB_ERR;
	}

	//checking if value is valid
	if (value!=NULL) 
	{ 
		if(validValue(value)) //check if value is valid
		{ 	
			strcpy_s(data[ultimoValor][1], MAXLENGTH * sizeof(char), value);
		}
		else //value not valid
			return CB_ERR;
	}
	else //value cant be null
		return CB_ERR;

	//key and value were ok
	memcpy(datosDeUsuario, data, MAXOPTIONS*MAXLENGTH*2*(sizeof(char))); //volvemos a igualar los arreglos
	
	return CB_SUXS;
}


static int validKey (const char* clave) { //return 1 if key is valid

	
	if(strlen(clave)>(MAXLENGTH-1)) //verifica el largo de la clave
	{
		printf("Supero el limite de %d caracteres de la clave\n",MAXLENGTH);
		return CB_ERR;
	}
	else
	{
		//free space for validation
		return CB_SUXS;
	}
	
}

static int validValue (const char* valor) { //return 1 if value is valid

	if(strlen(valor)>(MAXLENGTH-1))	//verifica el largo del valor
	{
		printf("Supero el limite de %d caracteres del valor\n",MAXLENGTH);
		return CB_ERR;
	}
	else
	{
		//free space for validation
		return CB_SUXS;
	}
}

static int lastValue (char array[MAXOPTIONS][2][MAXLENGTH]) { //looks for the first 0
	
	for (int i=0;i<MAXOPTIONS;i++) {
		if (strlen(array[i][1])==0) //busca lel primer string de length nulo
			return i;
		
	}
	return 0;// caso base
}