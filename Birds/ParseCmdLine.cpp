#include "ParseCmdLine.h"

int parseCmdLine(int argc, char const *argv[], pCallback checkInputs, void * userData)
{
	int i;
	int sum = 0;
	for (i = 1; i < argc; i++)
	{
		if (*argv[i] == '-')
		{
			if (argv[i][1] == '\0')	//Analiza si el caracter siguiente al guion es vacio
			{
				printf("%s\n", "Missing Key");
				return XERROR;
			}
			else if (i == argc - 1)	//Analiza si no existe valor para la opcion actual
			{
				printf("%s\n", "Missing Value");
				return XERROR;
			}
			else if (!(checkInputs(argv[i] + 1, argv[i + 1], userData)))	//Analiza la validez de la opcion segun lo determinado por el Callback
			{
				printf("%s\n", "Program terminated due to invalid option/value.");
				return XERROR;
			}
			else
				i++;	//Si la opcion es valida, se incrementa el indice para saltear el valor
		}
		else
		{
			if (!(checkInputs(NULL, argv[i], userData)))	//Analiza la validez del parametro segun lo determinado por el Callback
			{
				printf("%s\n", "Program terminated due to invalid parameter");
				return XERROR;
			}
		}
		sum++;	//Si lo analizado es valido, se suma a la cuenta total de opciones y parametros
	}
	return sum;
}

int validKey(const char* clave) { //return 1 if key is valid


	if (strlen(clave) > (MAXLENGTH - 1)) //verifica el largo de la clave
	{
		printf("Supero el limite de %d caracteres de la clave\n", MAXLENGTH);
		return CB_ERR;
	}
	else
	{
		if (!strcmp(clave, "eyesight") || !strcmp(clave, "birds") || !strcmp(clave, "jiggle"))
			return CB_SUXS;
		else
			return CB_ERR;
	}

}

int validValue(const char* valor) { //return 1 if value is valid

	if (strlen(valor) > (MAXLENGTH - 1))	//verifica el largo del valor
	{
		printf("Supero el limite de %d caracteres del valor\n", MAXLENGTH);
		return CB_ERR;
	}
	else
	{
		//free space for validation
		return CB_SUXS;
	}
}

int lastValue(char array[MAXOPTIONS][2][MAXLENGTH]) { //looks for the first 0

	for (int i = 0; i < MAXOPTIONS; i++) {
		if (strlen(array[i][1]) == 0) //busca lel primer string de length nulo
			return i;

	}
	return 0;// caso base
}