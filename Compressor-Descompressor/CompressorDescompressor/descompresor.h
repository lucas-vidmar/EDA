#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"
#include "boost\filesystem.hpp"

#define EXTENSION2 ".png"

namespace fs = boost::filesystem;

bool descompress(const char * imagePath);
