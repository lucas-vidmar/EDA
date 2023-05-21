#include "background.h"


#define PATH_BACKGROUND "Worms Images/Scenario1.png"

#define NO_FLAGS 0
#define NO_DX 0
#define NO_DY 0

background_t::background_t (void)
{

	this->Pos_x = 0;
	this->Pos_y = 0;



	al_set_new_bitmap_flags(ALLEGRO_KEEP_BITMAP_FORMAT);



	//this->setCantTextures(CANT_BACKGROUND_IMAGES);

	//this->init_textures();


	this->init_okey = true;


	//string background_path = PATH_BACKGROUND;

	this->images_background = al_load_bitmap(PATH_BACKGROUND);

	if(!(this->images_background))
	{
		this->init_okey = false;
	}
	

	if (this->init_okey == false)
	{
		free(this->images_background);
	}
	


}


background_t::~background_t(void)
{
	if (this->init_okey)
	{
		al_destroy_bitmap(this->images_background);
		this->init_okey = false;
		
	}

}

void background_t::draw(void) 
{
	al_draw_bitmap(this->images_background, NO_DX, NO_DY, NO_FLAGS);
}

ALLEGRO_BITMAP * background_t::get_images_background(void)
{
	
	return this->images_background;
	
}


