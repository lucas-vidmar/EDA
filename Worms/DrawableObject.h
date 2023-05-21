#pragma once

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Queue.h"

using namespace std;

class DrawableObject: public Queue
{
public:
	DrawableObject();
	~DrawableObject();

	virtual void draw(void) = 0;
	//getters
	//ALLEGRO_BITMAP* getBitmap(unsigned int num);
	double getPosition_x();
	double getPosition_y();
	unsigned int getCantTextures();
	

	bool init_textures(void);
	//bool load_textures(void);
	
	void setCantTextures(unsigned int cant_textures);

	void setTexture(ALLEGRO_BITMAP* texture_, unsigned int num);
	//void setPathTexture(string path, unsigned int num);

	ALLEGRO_BITMAP* getTexture(unsigned int num);
	//const char * getPathTexture(unsigned int num);
	bool is_init_done(void);
	bool is_load_done(void);


protected:


	/*Setters*/
	void setX(double x);
	void setY(double y);
	
	

	/*Getters*/
	double getX(void);
	double getY(void);



	double Pos_x;
	double Pos_y;

	unsigned int cant_textures;
	ALLEGRO_BITMAP** textures;

	//char ** paths_textures;


private:
	bool init_done;
	bool load_done;

};

