#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"
#include "boost\filesystem.hpp"

#define EXTENSION ".eda"
namespace fs = boost::filesystem;

bool compress(unsigned int threshold ,const char * imagePath, unsigned width, unsigned height);

void quadTree(fs::ofstream & text, std::vector<unsigned char>& image, unsigned int threshold, unsigned int width);

//busca valor maximo y minimo en un vector, salteandose de a n elementos, empezando del elemento offset
void setMinMax(std::vector<unsigned char>& image, unsigned int& min, unsigned int& max, unsigned int skipNro, unsigned int offset);

bool fillCuadrant(std::vector<unsigned char>& original, unsigned int originalWidth, std::vector<unsigned char>& nCuadrant, unsigned int n);
