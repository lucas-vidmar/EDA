/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 /*
  * File:   file_access.h
  * Author: r2d2
  *
  * Created on April 8, 2016, 10:10 PM
  */

#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define RGB_SIZE	3

#define POS_RED     0
#define POS_GREEN	1
#define POS_BLUE	2
#define POS_ALPHA	3



int write_file_with_size(FILE *dest_file, void *source, size_t num_bytes);
int get_size_bytes_file(FILE *source_file, void *dest, size_t num_bytes);
void draw(unsigned char * image_arrey, unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, uint32_t w_size, unsigned char red, unsigned char green, unsigned char blue);

#endif /* FILE_ACCESS_H */

