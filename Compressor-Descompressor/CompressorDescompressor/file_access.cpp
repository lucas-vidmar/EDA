/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "file_access.h"

#define ERROR -1


int get_size_bytes_file(FILE * file_source, void *destination_variable, size_t cant_bytes)
{
	size_t cant_bytes_read;

	unsigned int actual_chr;

	if (file_source == NULL || destination_variable == NULL)
		cant_bytes_read = ERROR;
	else
		for (cant_bytes_read = 0; cant_bytes_read < cant_bytes; cant_bytes_read++)
		{
			if ((actual_chr = fgetc(file_source)) == EOF)
				break;
			else
				((char*)destination_variable)[cant_bytes_read] = actual_chr;
		}
			

	return cant_bytes_read;
}

int write_file_with_size(FILE *file_destination, void *source_variable, size_t cant_bytes)
{

	size_t cant_bytes_to_write;

	if (file_destination == NULL || source_variable == NULL)
		cant_bytes_to_write = ERROR;
	else
		for (cant_bytes_to_write = 0; cant_bytes_to_write < cant_bytes; cant_bytes_to_write++)
			if (fputc(((char*)source_variable)[cant_bytes_to_write], file_destination) == EOF)
			{
				--cant_bytes_to_write;
				break;
			}

	return cant_bytes_to_write;

}

void draw(unsigned char * data, unsigned int first_x, unsigned int first_y, unsigned int last_x,
		  unsigned int last_y, uint32_t width_to_write, unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned int  counter_row;
	unsigned int  counter_column;

	for (counter_row = first_y; counter_row < last_y; counter_row++)
		for (counter_column = first_x; counter_column < last_x; counter_column++)
		{
			data[((counter_column * 4) + (4 * width_to_write*counter_row)) + POS_RED	] = red; 
			data[((counter_column * 4) + (4 * width_to_write*counter_row)) + POS_GREEN	] = green;
			data[((counter_column * 4) + (4 * width_to_write*counter_row)) + POS_BLUE	] = blue;
			data[((counter_column * 4) + (4 * width_to_write*counter_row)) + POS_ALPHA	] = 0xFF;
		}
}
