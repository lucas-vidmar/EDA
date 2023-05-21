#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"


#define MAXLENGTH 10		//largo maximo de cada argumento
#define MAXOPTIONS 10	//maximo de argumentos a ingresar
#define CB_ERR 0		//Constantes de error y 
#define CB_SUXS 1		//exito para este archivo


static int parseCallBack (const char*, const char*, void*);
static int lastValue (char [MAXOPTIONS][2][MAXLENGTH]);
static int validValue (const char*);
static int validKey (const char*);
static int parsing(int argc, char const *argv[],char userData[MAXOPTIONS][2][MAXLENGTH]);
static int testing(char data[MAXOPTIONS][2][MAXLENGTH]);

int main (int argc, char const *argv[]) {

	char userData[MAXOPTIONS][2][MAXLENGTH]={{{0}}};
	

	if(argc!= 1) 
	{
		parsing(argc,argv,userData);	//si se ingresaron argumentos comienza el programa normalmente sin usar el banco de pruebas
	}
	else	
	{
		testing(userData);	//si no se ingreso ningun parametro/opcion, comienza con el banco de pruebas
 
	}

	return 0;

}


//extra functions (not main)

static int parsing(int argc, char const *argv[],char userData[MAXOPTIONS][2][MAXLENGTH])
{
	int total;	//cantidad de opciones y parametros encontrados
		//parsing command line
		if ((total=parseCmdLine (argc, argv, parseCallBack, userData))== ERROR)
		{
			printf("Data entry error.\n");

			return 0; //there was an error, abort
		}
		printf("Data entry success.\n");


		printf("\n");
		for (int i=0;i<(total);i++) //imprime en pantalla las opciones y parametros ingresados
			printf("Key %d: %s \t| Value %d: %s \n",i,userData[i][0],i,userData[i][1]);	

		return 0;
}

static int parseCallBack (const char* key, const char* value, void* datosDeUsuario)
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
			strcpy(data[ultimoValor][0], key);
		}
		else //key not valid
			return CB_ERR;
	}

	//checking if value is valid
	if (value!=NULL) 
	{ 
		if(validValue(value)) //check if value is valid
		{ 	
			strcpy(data[ultimoValor][1], value);
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


// Banco de Pruebas
static int testing(char data[MAXOPTIONS][2][MAXLENGTH])
{
	printf("%s\n","Banco de Pruebas:" );

	// Prueba 1: opcion con clave sin valor
	printf("\n-----------------------------------------------");
	char const *prueba1[3]={"name","-clave",NULL};
	printf("\n%s\n","Prueba 1: opcion con clave sin valor");
	printf("%s\nSalida:\n","Ingreso: ./name -clave");
	parsing(2,prueba1,data);

	// Prueba 2: opcion sin clave sin valor
	printf("\n-----------------------------------------------");
	char const *prueba2[3]={"name","-",NULL};
	printf("\n%s\n","Prueba 2: opcion sin clave sin valor");
	printf("%s\nSalida:\n","Ingreso: ./name -");
	parsing(2,prueba2,data);

	// Prueba 3: opcion sin clave con valor
	printf("\n-----------------------------------------------");
	char const *prueba3[4]={"name","-","valor",NULL};
	printf("\n%s\n","Prueba 3: opcion sin clave con valor");
	printf("%s\nSalida:\n","Ingreso: ./name - valor");
	parsing(3,prueba3,data);	

	// Prueba 4: ingreso sin argumentos
	printf("\n-----------------------------------------------");
	char const *prueba4[2]={"name",NULL};
	printf("\n%s\n","Prueba 4: ingreso sin argumentos");
	printf("%s\nSalida:\n","Ingreso: ./name ");
	parsing(1,prueba4,data);

	// Prueba 5: opciones y parametros
	printf("\n-----------------------------------------------");
	char const *prueba5[8]={"name","param1","-clave1","valor1","param2","-clave2","valor2",NULL};
	printf("\n%s\n","Prueba 5: opciones y parametros");
	printf("%s\nSalida:\n","Ingreso: ./name param1 -clave1 valor1 param2 -clave2 valor2");
	parsing(7,prueba5,data);	

	
	// Prueba 6: limite de caracteres de la clave
	printf("\n-----------------------------------------------");
	char const *prueba6[4]={"name","-12345678910","valor",NULL};
	printf("\n%s\n","Prueba 6: limite de caracteres de la clave");
	printf("%s\nSalida:\n","Ingreso: ./name -123456789 valor");
	parsing(3,prueba6,data);

	// Prueba 7: limite de caracteres del valor/parametro
	printf("\n-----------------------------------------------");
	char const *prueba7[4]={"name","-clave","12345678910",NULL};
	printf("\n%s\n","Prueba 7: limite de caracteres del valor/parametro");
	printf("%s\nSalida:\n","Ingreso: ./name -clave 12345678910");
	parsing(3,prueba7,data);	

	// Prueba 8: ingreso limite de opciones definido por MAXOPTIONS
	printf("\n-----------------------------------------------");
	char const *prueba8[22]={"name","-c1","v1","-c2","v2","-c3","v3","-c4","v4","-c5","v5","-c6","v6","-c7","v7","-c8","v8","-c9","v9","-c10","v10",NULL};
	printf("\n%s\n","Prueba 8: ingreso limite de opciones");
	printf("%s\nSalida:\n","Ingreso: ./name -c1 v1 -c2 v2 -c3 v3 -c4 v4 -c5 v5 -c6 v6 -c7 v7 -c8 v8 -c9 v9 -c10 v10");
	parsing(21,prueba8,data);	
	
	// Prueba 9: ingreso limite de parametros definido por MAXOPTIONS
	printf("\n-----------------------------------------------");
	char const *prueba9[12]={"name","p1","p2","p3","p4","p5","p6","p7","p8","p9","p10",NULL};
	printf("\n%s\n","Prueba 9: ingreso limite de parametros");
	printf("%s\nSalida:\n","Ingreso: ./name  p1 p2 p3 p4 p5 p6 p7 p8 p9 p10");
	parsing(11,prueba9,data);	



	return 0;
}
