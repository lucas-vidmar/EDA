#ifndef PARSECMDLINE_H
#define PARSECMDLINE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLENGTH 10	//largo maximo de cada argumento
#define MAXOPTIONS 7	//maximo de argumentos a ingresar
#define CB_ERR 0		//Constantes de error y 
#define CB_SUXS 1		//exito para este archivo
#define XERROR -1

typedef int(*pCallback) (const char*, const char*, void*); //Declaracion de la funcion de callback (se encuentra en main.c)

int lastValue(char[MAXOPTIONS][2][MAXLENGTH]);
int validValue(const char*);
int validKey(const char*);
int parseCmdLine(int argc, char const *argv[], pCallback checkInputs, void * userData);

#endif