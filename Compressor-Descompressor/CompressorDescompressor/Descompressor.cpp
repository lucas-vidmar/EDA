#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Definitions.h"
#include "file_access.h"
#include "lodepng.h"
#include "Descompressor.h"

bool decompress_recursion(unsigned char * data, unsigned int first_x, unsigned int first_y, unsigned int last_x,
	unsigned int last_y, FILE * file_image, uint32_t image_width, uint32_t image_height);


bool descompress_image(const char * image_to_decompress, const char * new_image)
{
	bool can_descompress = false;
	unsigned char * values_image_comp = NULL;
	uint32_t image_width;
	uint32_t image_height;

	FILE * image_file;

	image_file = fopen(image_to_decompress, "rb+");
	
	
	
	if (image_file == NULL)
		perror("ERROR: No se pudo abrir el archivo para descomprimir\n");
	
	else if (get_size_bytes_file(image_file, &image_width, sizeof(uint32_t)) < sizeof(uint32_t))
		perror("ERROR:No se pudo leer el ancho de la imagen\n"); 

	else if (get_size_bytes_file(image_file, &image_height, sizeof(uint32_t)) < sizeof(uint32_t))
		perror("ERROR:No se pudo leer el alto de la imagen\n"); 


	else if ((values_image_comp = (unsigned char *) malloc(image_width*image_height * 4 * sizeof(unsigned char))) == NULL)
		perror("ERROR: No se pudo reservar memoria descomprimir la imagen\n");
	

	else if (decompress_recursion(values_image_comp, 0, 0, image_width, image_height, image_file, image_width, image_height))
	{
		std::string image_name(image_to_decompress);
		image_name.resize(image_name.size() - CANT_LETTERS_EXTENSION_COMPRESS); //remuevo el ".png" del nombre
		std::string extension = TYPE_OF_DESCOMPRESS_FILE_NEW;

		std::string new_string = image_name + extension;

		char * new_save_name = (char *)malloc(new_string.size());


		if (new_save_name == NULL)
			new_save_name = (char *)new_image;
		else {
			new_save_name = (char *)new_string.c_str();
		}


		lodepng_encode32_file(new_save_name, values_image_comp, image_width, image_height);
		free(values_image_comp); 
		can_descompress = true;
	}
	else
		perror("Error: No se puedo descomprir el archivo correctamente \n");

	return can_descompress;
}


bool decompress_recursion(unsigned char * data, unsigned int first_x, unsigned int first_y, unsigned int last_x, 
	unsigned int last_y, FILE * file_image, uint32_t image_width, uint32_t image_height)
{
	unsigned char chr;

	unsigned char red;
	unsigned char green;
	unsigned char blue;

	bool recursion_ok = false;

	chr = fgetc(file_image);


	if (chr == DRAW_CHARACTER)
	{
		red = fgetc(file_image); //se toma el byte del R
		green = fgetc(file_image); //se toma el byte del G
		blue = fgetc(file_image); //se toma el byte del B
		draw(data, first_x, first_y, last_x, last_y, image_width, red, green, blue); 

	}
	else if (chr == BRANCH_CHARACTER)
	{
		if (decompress_recursion(data, GET_FIRST_X(first_x, last_x), GET_FIRST_Y(first_y, last_y), MID_LIMIT_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), file_image, image_width, image_height) == false);
		else if (decompress_recursion(data, MID_LIMIT_X(first_x, last_x), GET_FIRST_Y(first_y, last_y), GET_LAST_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), file_image, image_width, image_height) == false);
		else if (decompress_recursion(data, GET_FIRST_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), MID_LIMIT_X(first_x, last_x), GET_LAST_Y(first_y, last_y), file_image, image_width, image_height) == false);
		else if (decompress_recursion(data, MID_LIMIT_X(first_x, last_x), MID_LIMIT_Y(first_y, last_y), GET_LAST_X(first_x, last_x), GET_LAST_Y(first_y, last_y), file_image, image_width, image_height) == false);
		else recursion_ok = true;
	}

	recursion_ok = true;

	return recursion_ok;
}


