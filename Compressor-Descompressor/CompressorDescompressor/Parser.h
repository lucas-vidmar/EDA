#pragma once

#ifndef PARSER_H
#define PARSER_H

#define POSITION_PARAMETER_MODE		 1
#define POSITION_PARAMETER_PATH		 2
#define POSITION_PARAMETER_THRESHOLD 3

#define MAX_THRESHOLD_PORC	100
#define MIN_THRESHOLD_PORC	0


#include "Definitions.h"

bool parserCmd(int argc, char ** argv, userData_t & userData);


#endif // !PARSER_H
