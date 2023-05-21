#include "compresor.h"


bool compress(unsigned int threshold, const char * imagePath, unsigned width, unsigned height)
{
	if (width != height)
	{
		std::cout << "No se admiten imagenes no cuadradas" << std::endl;
		return true;
	}
}