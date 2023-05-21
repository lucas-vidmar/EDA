
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Definitions.h"
#include "file_access.h"
#include "lodepng.h"
#include "Compressor.h"





void compress_recursion(unsigned char * image_RGB, FILE * image2compress, unsigned int threshold,
	unsigned int first_x, unsigned int first_y, unsigned int last_x, unsigned int last_y, uint32_t dimension);

unsigned int score_cuadrant_rgb(unsigned char*image_RGB, unsigned int first_x, unsigned int first_y,
	unsigned int last_x, unsigned int last_y, uint32_t dimension, unsigned char array_rgb[RGB_SIZE]);







bool compress_image(const char * file_png_path, const char * path_to_save, unsigned int threshold)
{
	bool can_compress = false;

	FILE *image_compress = NULL;

	unsigned int image_width;
	unsigned int image_height;

	unsigned char * image_RGB = NULL;

	if (path_to_save != NULL)
		lodepng_decode24_file(&image_RGB, &image_width, &image_height, (char *)file_png_path);
	if (path_to_save != NULL && image_RGB != NULL)
	{


	#if FORCE_EXTENSION
		
		std::string filename_image_input(file_png_path);
		filename_image_input.resize(filename_image_input.size() - CANT_LETTERS_EXTENSION_DECOMPRESS); 
		std::string extension = TYPE_OF_COMPRESS_FILE;

		std::string new_string = filename_image_input + extension;

		char * new_name_of_file = (char *) malloc(new_string.size());
		
		
		if (new_name_of_file == NULL)
			new_name_of_file = (char *) path_to_save;
		else {
			new_name_of_file = (char *)new_string.c_str();
		}

		image_compress = fopen(new_name_of_file, "wb+");
		
	#else
		image_compress = fopen(save_name, "wb+");
	#endif

		if (image_compress != NULL)
		{

			write_file_with_size(image_compress, &image_width, sizeof(uint32_t));//Guardamos tamaño imagen 
			write_file_with_size(image_compress, &image_height, sizeof(uint32_t));//Guardamos tamaño imagen
			compress_recursion(image_RGB, image_compress, threshold, 0, 0, image_width, image_height, image_width);
			fclose(image_compress);

			can_compress = true;

		}

		free(image_RGB);
	
	}
	return can_compress;
}


void compress_recursion (unsigned char * image_RGB, FILE * image2compress, unsigned int threshold,
	unsigned int first_x, unsigned int first_y, unsigned int last_x, unsigned int last_y, uint32_t dimension)
{
	unsigned char rgb_array[RGB_SIZE];

	if (score_cuadrant_rgb(image_RGB, first_x, first_y, last_x, last_y, dimension, rgb_array) > threshold)
	{

		fputc(BRANCH_CHARACTER, image2compress);
	
		compress_recursion(image_RGB, image2compress, threshold, GET_FIRST_X(first_x, last_x), GET_FIRST_Y(first_y, last_y), MID_LIMIT_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), dimension);
		compress_recursion(image_RGB, image2compress, threshold, MID_LIMIT_X(first_x, last_x), GET_FIRST_Y(first_y, last_y), GET_LAST_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), dimension);
		compress_recursion(image_RGB, image2compress, threshold, GET_FIRST_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), MID_LIMIT_X(first_x, last_x), GET_LAST_Y(first_y, last_y), dimension);
		compress_recursion(image_RGB, image2compress, threshold, MID_LIMIT_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), GET_LAST_X(first_x, last_x), GET_LAST_Y(first_y, last_y), dimension);

	}
	else
	{
		fputc(DRAW_CHARACTER, image2compress);
		//printf("pinta\n");
		write_file_with_size(image2compress, rgb_array, 3);
	}


}


unsigned int score_cuadrant_rgb(unsigned char*image_RGB, unsigned int first_x, unsigned int first_y,
								unsigned int last_x, unsigned int last_y, uint32_t dimension, unsigned char array_rgb[RGB_SIZE])
{
	unsigned int width = first_x;
	unsigned int heigth = first_y;



	unsigned char red_max;
	unsigned char red_min;
	
	unsigned char green_max;
	unsigned char green_min;
	
	unsigned char blue_max;
	unsigned char blue_min;



	red_max = red_min = image_RGB[(first_y*dimension + first_x)*RGB_SIZE];
	green_max = green_min = image_RGB[(first_y*dimension + first_x)*RGB_SIZE + POS_GREEN];
	blue_max = blue_min = image_RGB[(first_y*dimension + first_x)*RGB_SIZE + POS_BLUE];


	for (heigth = first_y; heigth < last_y; heigth++)
		for (width = first_x; width < last_x; width++)
		{
			if (image_RGB[(heigth*dimension + width)*RGB_SIZE] > red_max)
				red_max = image_RGB[(heigth*dimension + width)*RGB_SIZE];

			else if (image_RGB[(heigth*dimension + width)*RGB_SIZE] < red_min)
				red_min = image_RGB[(heigth*dimension + width)*RGB_SIZE];


			if (image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_GREEN] > green_max)
				green_max = image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_GREEN];

			else if (image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_GREEN] < green_min)
				green_min = image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_GREEN];


			if (image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_BLUE] > blue_max)
				blue_max = image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_BLUE];

			else if (image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_BLUE] < blue_min)
				blue_min = image_RGB[(heigth*dimension + width)*RGB_SIZE + POS_BLUE];

		}

	array_rgb[POS_RED] = AVG(red_max, red_min);
	array_rgb[POS_GREEN] = AVG(green_max, green_min);
	array_rgb[POS_BLUE] = AVG(blue_max, blue_min);

	unsigned int score = red_max - red_min + green_max - green_max + blue_max - blue_min;
	
	return score;


}
