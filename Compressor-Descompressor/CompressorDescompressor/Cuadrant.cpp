#pragma once
#include "Cuadrant.h"

//auxiliar
void set_min_max_image_auxiliar(std::vector<unsigned char>& image, unsigned int step, unsigned int color, unsigned int & max, unsigned int & min);


cuadrant::cuadrant(void)
{
	//inicializo con los peores casos

	min_red = MAX_VALUE; 
	max_red = MIN_VALUE;

	min_green = MAX_VALUE;
	max_green = MIN_VALUE;

	min_blue = MAX_VALUE;
	max_blue = MIN_VALUE;

	score = 0;

}

cuadrant::~cuadrant(void)
{

}


void cuadrant::set_min_max_image_RGB_skip(std::vector<unsigned char>& image,  unsigned int step)
{
	unsigned int color;

	color = RED;
	set_min_max_image_auxiliar(image, step, color, this->max_red, this->min_red);
	
	color = GREEN;
	set_min_max_image_auxiliar(image, step, color, this->max_green, this->min_green);

	color = BLUE;
	set_min_max_image_auxiliar(image, step, color, this->max_blue, this->min_blue);

}


void cuadrant::uptdate_score(void)
{

	unsigned int red_val	 = this->max_red - this->min_red;
	unsigned int green_val	 = this->max_green - this->min_green;
	unsigned int blue_val	 = this->max_blue - this->min_blue;
	
	this->score = red_val + green_val + blue_val;

}


unsigned int cuadrant :: get_score(void)
{
	return this->score;
}

unsigned int cuadrant :: get_red_avg(void) {

	unsigned int aux;
	aux = ((this->max_red + this->min_red) / 2);
	return aux;

}

unsigned int cuadrant::get_green_avg(void) {

	unsigned int aux;
	aux = ((this->max_green + this->min_green) / 2);
	return aux;

}

unsigned int cuadrant::get_blue_avg(void) {

	unsigned int aux;
	aux = ((this->max_blue + this->min_blue) / 2);
	return aux;

}




void set_min_max_image_auxiliar(std::vector<unsigned char>& image, unsigned int step, unsigned int color, unsigned int & max, unsigned int & min)
{

	for (unsigned int i = color; (i < image.size()); i += (step + 1))
	{
		if (image[i] > max)
		{
			max = image[i];
		}
		if (image[i] < min)
		{
			min = image[i];
		}
	}

}

