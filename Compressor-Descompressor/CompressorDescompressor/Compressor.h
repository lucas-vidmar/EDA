#ifndef  COMPRESSOR_H
#define	 COMPRESSOR_H



#define MID_LIMIT_X(x1,x2) (((x1)+(x2))/2)
#define MID_LIMIT_Y(y1,y2) (((y1)+(y2))/2)

#define GET_FIRST_X(x1,x2)	((x1))
#define GET_LAST_X(x1,x2)	((x2))

#define GET_FIRST_Y(y1,y2)	((y1))
#define GET_LAST_Y(y1,y2)	((y2))

#define AVG(x,y)	( ((x)+(y))/2 )




bool compress_image(const char * png_file_name, const char * save_name, unsigned int threshold);



#endif // ! COMPRESSOR_H

