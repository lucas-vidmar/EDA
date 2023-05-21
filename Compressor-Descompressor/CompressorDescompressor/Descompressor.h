#pragma once

#ifndef DESCOMPRESSOR_H
#define DESCOMPRESSOR_H


#define MID_LIMIT_X(x1,x2) (((x1)+(x2))/2)
#define MID_LIMIT_Y(y1,y2) (((y1)+(y2))/2)

#define GET_FIRST_X(x1,x2)	((x1))
#define GET_LAST_X(x1,x2)	((x2))

#define GET_FIRST_Y(y1,y2)	((y1))
#define GET_LAST_Y(y1,y2)	((y2))

#define AVG(x,y)	( ((x)+(y))/2 )


bool descompress_image(const char * image_to_decompress, const char * new_image);

#endif // !DESCOMPRESSOR_H
