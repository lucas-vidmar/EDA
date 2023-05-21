#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>

#define THRESHOLD_RATE 7.65

//Macros compresor
#define FORCE_EXTENSION 1   //de estar en 1 obligara que el archivo salga con la siguiente ext
#define TYPE_OF_COMPRESS_FILE	".compr"
#define CANT_LETTERS_EXTENSION_COMPRESS 6

#define	TYPE_OF_DESCOMPRESS_FILE_NEW "EDIT.png"
#define TYPE_OF_DESCOMPRESS_FILE ".png"
#define CANT_LETTERS_EXTENSION_DECOMPRESS 4

#define BRANCH_CHARACTER	'B'
#define DRAW_CHARACTER	'N'


#define MODE_COMPRESSOR		1
#define MODE_DESCOMPRESSOR	2



#define WIDTH_DEFAULT 1000
#define HEIGHT_DEFAULT 600
#define FONT_SIZE_DEFAULT 30



#define BACKGROUND_PATH "background2.png" //Imagen de fondo

#define FONT_PATH "Font.ttf"
#define FONT_COLOR "red"

#define IMAGE_DESCOMPRESSOR_PATH "icon_compress.png"

#define MARKER_WIDTH 10


#define PATH_BUTTON_LEFT	"button_left2.png"
#define PATH_BUTTON_RIGHT	"button_right2.png"

typedef struct
{
	std::string path;
	unsigned int mode;
	int threshold;

}userData_t;


#endif // !DEFINITIONS_H
