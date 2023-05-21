#pragma once

#include <vector>

#ifndef CUADRANT_H
#define CUADRANT_H

#define MAX_VALUE	255 //0xFF
#define MIN_VALUE	0	//0x00

enum types { RED = 0, GREEN, BLUE }; 


class cuadrant
{
	public:
		cuadrant();
		~cuadrant();

		void set_min_max_image_RGB_skip(std::vector<unsigned char>& image, unsigned int step);
		void uptdate_score(void);

		unsigned int get_score(void);
		unsigned int get_red_avg(void);
		unsigned int get_green_avg(void);
		unsigned int get_blue_avg(void);


	private:

		unsigned int min_red;
		unsigned int max_red;

		unsigned int min_green;
		unsigned int max_green;

		unsigned int min_blue;
		unsigned int max_blue; 

		unsigned int score;


};


#endif // !CUADRANT_H
