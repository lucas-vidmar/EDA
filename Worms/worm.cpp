#include "worm.h"

#include <string>
#include "GeneralDefines.h"



#define PATH_WORM_WALKING_IMAGE_INIT	"Worms Images/wwalking/wwalk-F"
#define PATH_WORM_JUMP_IMAGE_INIT	"Worms Images/wjump/wjump-F"

#define PATH_TYPE_IMAGE_FILE ".png"

#define NOT_FLIP_IMAGE	0
#define FLIP_IMAGE	ALLEGRO_FLIP_HORIZONTAL


#define WORM_NORMAL_WALK 0

#define WORM_START_UP_WALK 6
#define WORM_END_UP_WALK 8

#define WORM_START_UP_JUMP 1
#define WORM_END_UP_JUMP 3

#define WORM_START_SEQ_WALK 9
#define WORM_END_SEQ_WALK 50

#define WORM_START_SEQ_JUMP 4
#define WORM_END_SEQ_JUMP 36

#define WORM_CANT_IMAGES_WALK_SEQ 14
#define WORM_CANT_IMAGES_JUMP_SEQ 33


const unsigned int walking_sequence_images_order[] = { 4,5,6,7,8,9,10,11,11,12,13,14,15,4 };
const unsigned int jump_sequence_images_order[] = { 4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10 };


using namespace std;

worm::worm()
{

	Pos_y = 616;
	angle_jump = (M_PI / 3);	//60 degree
	worm_state = state::idle;
	key_time_count = 0;
	speed_jump = 4.5;
	Orient = OrientType::left;
	

	this->init_okey = true;


	al_set_new_bitmap_flags(ALLEGRO_NO_PREMULTIPLIED_ALPHA);

	//this->setCantTextures(CANT_TEXTURES_WORM_WALKING + CANT_TEXTURES_WORM_JUMPING);
	
	//this->init_textures();


	unsigned int i = 0;

	for ( ; (i < CANT_TEXTURES_WORM_WALKING) && (this->init_okey); i++)
	{
		string path_walk = PATH_WORM_WALKING_IMAGE_INIT;
		path_walk += to_string(i + 1) + PATH_TYPE_IMAGE_FILE;

		
		this->images_walking[i] = al_load_bitmap(path_walk.c_str());

	
		if (!(this->images_walking[i]))
		{
			this->init_okey = false;
		}
				

	}



	unsigned int j = 0;


	for ( ; j < CANT_TEXTURES_WORM_JUMPING; j++)
	{
		string path_jump = PATH_WORM_JUMP_IMAGE_INIT;
		path_jump += to_string(j + 1) + PATH_TYPE_IMAGE_FILE;
		
		this->images_jump[j] = al_load_bitmap(path_jump.c_str());

		


		if (!(this->images_jump[j]))
		{
			this->init_okey = false;
		}



	}

	if (this->init_okey == false)
	{
		for (unsigned int a = 0; a < i; a++)
		{
			free(this->images_walking[a]);
		}

		for (unsigned int b = 0; b < j; b++)
		{
			free(this->images_jump[b]);
		}
	}


	al_set_new_bitmap_flags(ALLEGRO_KEEP_BITMAP_FORMAT);


};



worm::~worm()
{

	if (this->init_okey == true)
	{
		for (unsigned int i = 0; i < CANT_TEXTURES_WORM_WALKING; i++)
		{
			al_destroy_bitmap(this->images_walking[i]);
		}

		for (unsigned int i = 0; i < CANT_TEXTURES_WORM_JUMPING; i++)
		{
			al_destroy_bitmap(this->images_jump[i]);
		}
	
		this->init_okey = false;
	
	}


}

void worm::draw()
{
	unsigned int flag_flip_image;
	
	if (this->Orient == OrientType::left) {
		flag_flip_image = NOT_FLIP_IMAGE;
	}
	else
	{
		flag_flip_image = FLIP_IMAGE;
	}

	if ((this->get_state() == state::idle) || (this->get_state() == state::start_walk) || (this->get_state() == state::start_jump))
	{
		al_draw_bitmap(this->images_walking[WORM_NORMAL_WALK],
					   this->getPosition_x() - IMAGE_OFFSET_CORD_X, this->getPosition_y() - IMAGE_OFFSET_CORD_Y, flag_flip_image);
	}
	else if (this->get_state() == state::walking) 
		{

			if ((this->key_time_count >= WORM_START_UP_WALK) && (this->key_time_count <= WORM_END_UP_WALK)) // Walk worm up
			{  
				al_draw_bitmap(this->images_walking[this->key_time_count - WORM_NORMAL_WALK],
					this->Pos_x - IMAGE_OFFSET_CORD_X, this->Pos_y - IMAGE_OFFSET_CORD_Y, flag_flip_image);

			}
			else
				if ((this->key_time_count >= WORM_START_SEQ_WALK) && (this->key_time_count <= WORM_END_SEQ_WALK))	// Moving sequence
				{ 
					unsigned int stage_in_the_lopp = (this->key_time_count - WORM_START_SEQ_WALK) % WORM_CANT_IMAGES_WALK_SEQ;
					al_draw_bitmap(this->images_walking[(walking_sequence_images_order[stage_in_the_lopp]) - 1],					//el -1 esta porque las imagenes estan enumeradas 1,2,3,.. y en el arreglo la nro 1 esta en la posicion 0 y asi sucesivamente
								   this->Pos_x - IMAGE_OFFSET_CORD_X, this->Pos_y - IMAGE_OFFSET_CORD_Y, flag_flip_image);
				}

		}
		
	
	else if (this->get_state() == state::jumping)
			{

				if ((this->key_time_count >= WORM_START_UP_JUMP) && (this->key_time_count <= WORM_END_UP_JUMP))  // Jump worm up
				{
					al_draw_bitmap(this->images_jump[this->key_time_count - WORM_START_UP_JUMP ],
						this->getPosition_x() - IMAGE_OFFSET_CORD_X, this->getPosition_y() - IMAGE_OFFSET_CORD_Y, flag_flip_image);
				}

				else if ((this->key_time_count >= WORM_START_SEQ_JUMP) && (this->key_time_count <= WORM_END_SEQ_JUMP)) // Jumping sequence
				{ 
					al_draw_bitmap(this->images_jump[(jump_sequence_images_order[this->key_time_count - WORM_START_SEQ_JUMP]) - 1], 			//el -1 esta porque las imagenes estan enumeradas 1,2,3,.. y en el arreglo la nro 1 esta en la posicion 0 y asi sucesivamente
								   this->getPosition_x() - IMAGE_OFFSET_CORD_X, this->getPosition_y() - IMAGE_OFFSET_CORD_Y, flag_flip_image);
				}
			}
		
}
	


void worm::start_walking(void) 
{ 
	worm_state = state::start_walk;
}

void worm::start_jumping(void)
{
	worm_state = state::start_jump;
}


void worm::update(void)
{
	ALLEGRO_KEYBOARD_STATE keyboard_state;
	switch (worm_state)
	{
		case state::idle:
								break;

		case state::start_walk:
								
								al_get_keyboard_state(&keyboard_state);
								if (al_key_down(&keyboard_state, ALLEGRO_KEY_A) || al_key_down(&keyboard_state, ALLEGRO_KEY_D) //esto no esta bien
									|| al_key_down(&keyboard_state, ALLEGRO_KEY_RIGHT) || al_key_down(&keyboard_state, ALLEGRO_KEY_LEFT))
								{
									key_time_count++;
								}
								else
								{
									key_time_count = 0;
									worm_state = state::idle;
								}

								if (key_time_count == 5)
								{
									worm_state = state::walking;
								}
								break;

		case state::walking:	walking();
								key_time_count++;
								if (key_time_count == 50)
								{
									key_time_count = 0;
									worm_state = state::idle;
								}
								break;



		case state::start_jump:
								al_get_keyboard_state(&keyboard_state);
								if (al_key_down(&keyboard_state, ALLEGRO_KEY_W) || al_key_down(&keyboard_state, ALLEGRO_KEY_UP))//esto no esta bien
								{
									key_time_count++;
								}
								else
								{
									key_time_count = 0;
									worm_state = state::idle;
								}

								if (key_time_count == 5)
								{
									worm_state = state::jumping;
								}
								break;

		case state::jumping:	jumping();
								key_time_count++;
								if (key_time_count == 38)	//puse 38 pero no me acuerdo cuantas imagenes hay que mostrar
								{
									key_time_count = 0;
									worm_state = state::idle;
								}
								break;



	}




	
}


void worm::walking(void) 
{
	double offset = (Orient == OrientType::right ? 27.0/50.0 : -27.0/50.0);
	if((getX() + offset) <= 1210 && (getX() + offset) >= 725)
	{
		setX(getX() + offset);
	}
	return;
}

void worm::jumping(void)
{
	double t = key_time_count-15;
	double offset_y = -getSpeedJ()*sin(getAngle()) + 0.5*0.24*pow(t, 2);
	double offset_x = getSpeedJ()*cos(getAngle())*(Orient == OrientType::right ? 1 : -1);

	if ((getX() + offset_x) <= 1210 && (getX() + offset_x) >= 725)
	{
		setX(getX() + offset_x);
	}

	//if (getY() + offset_y <= 616)
	{
		setY(getY() + offset_y);
	}
	if (getY() > 616)
	{
		setY(616);
	}



}



OrientType worm::getOrient() { return this->Orient; }
double worm::getAngle() { return this->angle_jump; }
state worm::get_state() { return this->worm_state; }
double worm::getSpeedJ() { return this->speed_jump; }

//Setters
void worm::setPosition_x(double x) { this->Pos_x = x; }
void worm::setPosition_y(double y) { this->Pos_y = y; }
void worm::setOrient(OrientType newOrient) { this->Orient = newOrient; }
void worm::setAngle_j(double newAngle) { this->angle_jump = newAngle; }