#include "DrawableObject.h"

using namespace std;

DrawableObject::DrawableObject()
{
	this->init_done = false;
	this->load_done = false;
}

DrawableObject::~DrawableObject()
{

	/*
	
	if (textures)
	{
		for (unsigned int i = 0; i < this->cant_textures; i++)
		{
			al_destroy_bitmap(this->getBitmap(i));
		}

		free(this->textures);
	}
	
	
	*/
	

}



bool DrawableObject::init_textures()
{

	 
	this->init_done = false;

	textures = nullptr;
	textures = (ALLEGRO_BITMAP**)malloc(this->cant_textures);

	if (textures)
	{
		this->init_done = true;
	}


	//paths_textures = nullptr;
	//paths_textures = (char ** )malloc(cant_textures);


	//if (paths_textures && can_init_textures)
	//{
	//	this->init_done = true;
	//}


	return this->init_done;

}

/*
ALLEGRO_BITMAP* DrawableObject::getBitmap(unsigned int num) //start with zero....bitmap zero is the first bitmap
{
	ALLEGRO_BITMAP* Bitmap = nullptr;

	bool is_init_done = this->is_init_done();
	unsigned int cant = this->cant_textures;


	if (is_init_done &&(num < this->cant_textures))
	{

		Bitmap = this->textures[num];

	}

	return Bitmap;


}


*/

	
double DrawableObject::getPosition_x() { return this->Pos_x; }


double DrawableObject::getPosition_y() { return this->Pos_y; }

unsigned int DrawableObject::getCantTextures() { return this->cant_textures; }

/*
bool DrawableObject::load_textures(void)
{
	this->load_done = true;

	if (init_done)
	{

		for (unsigned int i = 0; (i < cant_textures) && (load_done); i++)
		{
			ALLEGRO_BITMAP * current_bitmap = nullptr;

			current_bitmap = al_load_bitmap(this->getPathTexture(i));



			if (!textures[i])
			{
				load_done = false;

				for (unsigned int j = 0; j < i; j++)
				{

					al_destroy_bitmap(this->textures[j]);

				}

			}


		}

	}
	else
	{
		load_done = false;
	}



	return this->load_done;


}



*/


/*Setters*/
void DrawableObject::setX(double x) { this->Pos_x = x; }

void DrawableObject::setY(double y) { this->Pos_y = y; }

void DrawableObject::setTexture(ALLEGRO_BITMAP* texture, unsigned int num) //start with zero....bitmap zero is the first bitmap
{
	if (this->init_done && (num < this->cant_textures))
	{
		this->textures[num] = texture;

	}
	
}

void DrawableObject::setCantTextures(unsigned int cant_textures)
{

	this->cant_textures = cant_textures;

}


/*
void DrawableObject::setPathTexture(string path, unsigned int num)
{

	if (this->init_done && (num < this->cant_textures))
	{
		(this->paths_textures)[num] = (char *) path.c_str();

	}

}



*/



/*Getters*/
double DrawableObject::getX(void) { return this->Pos_x; }


double DrawableObject::getY(void) { return this->Pos_y; }


ALLEGRO_BITMAP* DrawableObject::getTexture(unsigned int num) //start with zero....bitmap zero is the first bitmap
{
	ALLEGRO_BITMAP* Bitmap = nullptr;

	if (this->init_done && (num < this->cant_textures))
	{

		Bitmap = this->textures[num];

	}

	return Bitmap;


}

/*
const char * DrawableObject::getPathTexture(unsigned int num)
{
	char * path = nullptr;

	if (this->init_done && (num < this->cant_textures))
	{
		path = this->paths_textures[num];

	}

	return path;
}

*/


bool DrawableObject::is_init_done(void)
{
	return this->init_done;

}


bool DrawableObject::is_load_done(void)
{
	return this->load_done;

}