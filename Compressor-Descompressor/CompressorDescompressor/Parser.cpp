#include "Parser.h"
#include <string>
#include <iostream>
#include <sstream>




#define CANT_ELEMENTS_INPUT		3 //path + mode + threshold (optional)
#define CANT_ELEMENTS_PER_CMD (CANT_ELEMENTS_INPUT + 1)


//auxiliar functions
int interpret_threshold(double threshold_cmd);
double string_to_double(const char * num_string);

using namespace std;

bool parserCmd(int argc, char ** argv, userData_t & userData)
{
	bool can_parse = true;
	
	if ((argc == CANT_ELEMENTS_PER_CMD) || (argc == CANT_ELEMENTS_PER_CMD -1)) //siempre el primer parametro es el modo (estrictamente)
	{
		int mode = atoi(argv[POSITION_PARAMETER_MODE]);

		if (mode == MODE_COMPRESSOR && (argc == CANT_ELEMENTS_PER_CMD ))
		{
			userData.mode = mode;

			string path;
			path = argv[POSITION_PARAMETER_PATH];
			userData.path = path;

			double threshold_cmd = string_to_double(argv[POSITION_PARAMETER_THRESHOLD]); //ultimo parametro es el threshold

			if ((threshold_cmd >= MIN_THRESHOLD_PORC) && (threshold_cmd <= MAX_THRESHOLD_PORC))
			{
				userData.threshold = interpret_threshold(threshold_cmd);
			}
			else
			{
				cout << "Threshold (2do parametro) debe ser un numero entre " << MIN_THRESHOLD_PORC << " y " << MAX_THRESHOLD_PORC << endl;
				can_parse = false;
			}
		}
		else if (mode == MODE_DESCOMPRESSOR)
		{
			userData.mode = mode;

			std::string path;
			path = argv[POSITION_PARAMETER_PATH];
			userData.path = path;
		}
		else
		{
			can_parse = false;
		}

	}
	else
	{
		cout << "ERROR:  ingreso lineas de comandos" << endl;
		can_parse = false;
	}

	return can_parse;
}


double string_to_double(const char * num_string)
{
	double num_dec = 0.0;
	string num_string_aux = num_string;
	num_dec = (double) stof(num_string_aux, nullptr);

	return num_dec;
}


int interpret_threshold(double threshold_cmd)
{
	int threshold = (int)ceil(threshold_cmd * THRESHOLD_RATE);
	return threshold;
}