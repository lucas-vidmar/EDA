#include "piso.h"
#include "robot.h"
#include "sim.h"
#include "allegro.h"



allegroDisplay_t* iniAllegro(int w, int h) {
	al_init();
	if (al_init_font_addon()) {
		if (al_init_ttf_addon()) {
			if (al_init_image_addon()) {
				if (al_install_mouse()) {

					allegroDisplay_t* screen; //creating screen struct
					screen = ((allegroDisplay_t*)malloc(sizeof(allegroDisplay_t))); //asigning space

					al_set_new_display_refresh_rate(REFRESHRATE); //refresh rate de 30

					screen->queue = al_create_event_queue();

					screen->display = al_create_display((w * TILESIDE), (h * TILESIDE)); //setting display

					al_register_event_source(screen->queue, al_get_display_event_source(screen->display)); //tide disaply to event queue

					screen->font = al_load_ttf_font("GriddyBlocks.ttf", 50, ALLEGRO_TTF_MONOCHROME); //setting font GriddyBlocks

					/*Setting bitmaps*/
					screen->robot = al_load_bitmap("robot2.png");
					screen->cleanTile = al_load_bitmap("tile2.png");
					screen->dirtyTile = al_load_bitmap("dirty-tile2.png");
					screen->blackPixel = al_load_bitmap("blackPixel.png");

					al_clear_to_color(al_map_rgba(255, 0, 0, 0)); //la inicializamos en rojo para que se vean los errores

					return screen; //success
				}
				else
					printf("Mouse addon error");
			}
			else
				printf("Mouse image error");
		}
		else
			printf("Font TTF addon error");
	}
	else
		printf("Font addon error");
	
	return NULL; //there was an error
}

void robotUpdate(allegroDisplay_t* screen, Piso_t* floor, Robot_t* robot, int ancho, int alto, int cant) {

	double pos[MAXROBOTS][2] = { *((double*)NULL) }; //position vector in time
	double Xo[MAXROBOTS], Yo[MAXROBOTS], Xf[MAXROBOTS], Yf[MAXROBOTS], x[MAXROBOTS], y[MAXROBOTS];

	/*Initial Data*/
	for (int i = 0; i < cant; i++) {
		Xo[i] = (robot+i)->getX();
		Yo[i] = (robot+i)->getY(); //setting initial position
		if ((robot + i)->move(ancho, alto)) { //moving the robot
			Xf[i] = (robot + i)->getX();
			Yf[i] = (robot + i)->getY(); //setting ending position
		}
		else { //couldnt move, reached border
			Xf[i] = Xo[i];
			Yf[i] = Yo[i]; //setting ending position equal to initial position
		}
		
	}

	/*Movement*/
	for (double multiplier = 0; multiplier < 1.0; multiplier += STEP) { //drawing each step of movement

		for (int i = 0; i < cant; i++) {
			microUpdate(pos, i, Xo[i], Yo[i], Xf[i], Yf[i], multiplier); //updating position to draw, saves in pos
			x[i] = (pos[i][0] * TILESIDE - ROBOTSIDE / 2); //moving bitmap
			y[i] = (pos[i][1] * TILESIDE - ROBOTSIDE / 2);
			floorUpdate(screen, floor); //drawing floor again
			for (int j = 0; j < cant; j++) {
				al_draw_bitmap(screen->robot, y[j], x[j], ALLEGRO_FLIP_HORIZONTAL); //drawing robots
			}
			al_flip_display();
			al_rest(RUNNINGSPEED); //lets give each frame RUNNINGSPEED seconds
		}
	}

}

int popUp(const char* word, allegroDisplay_t* screen, int ancho, int alto) {

	bool quit = false;
	ALLEGRO_DISPLAY* pop = al_create_display((4 * TILESIDE), (2 * TILESIDE)); //setting display
	al_set_new_display_refresh_rate(REFRESHRATE); //refresh rate
	al_set_target_backbuffer(pop); //switches to new display

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //creating new queue
	al_register_event_source(queue, al_get_display_event_source(pop)); //tide disaply to event queue

	al_clear_to_color(al_map_rgba(0, 0, 0, 0)); //all to black

	al_draw_text(screen->font, al_map_rgb(255, 255, 255), (4 *TILESIDE/2), (2 *TILESIDE / 2), ALLEGRO_ALIGN_CENTER, word); //draw word
	al_flip_display(); //updates display


	while (!quit) {
		quit = displayQuit(queue); //until quit button is pressed
	}

	al_set_target_backbuffer(screen->display); //switches to old display

	al_destroy_display(pop);
	al_destroy_event_queue(queue);

	return SUCCESS;
}


int graph(double* tickCount) {

	bool quit = false;
	double ancho = 10, alto = 10;
	double desfasaje = 20;
	allegroDisplay_t* screen = iniAllegro((int)ancho, (int)alto);

	int total = count(tickCount); //cuento la cantidad de valores
	double max = *tickCount; //el primer valor es el mas alto

	al_set_target_backbuffer(screen->display);

	al_clear_to_color(al_map_rgba(255, 255, 255, 0)); //la inicializamos en blanco

	double xInc = ((ancho*TILESIDE) - 2 * desfasaje) / total; //separacion entre elementos en x
	double x = 5, y = 0;

	for (double i=0; i<(ancho*TILESIDE)- 2*desfasaje; i++) { //graphing x axis
		al_draw_bitmap(screen->blackPixel, desfasaje + i, (alto*TILESIDE) - desfasaje, ALLEGRO_FLIP_HORIZONTAL);
		al_flip_display();
	}
		
	for (double i = 0; i < (alto*TILESIDE)- 2*desfasaje; i++) { //graphing y axis
		al_draw_bitmap(screen->blackPixel, desfasaje, (alto*TILESIDE) - desfasaje - i, ALLEGRO_FLIP_HORIZONTAL);
		al_flip_display();
	}

	for (int i = 0; i < total; i++) { //dots
		y = ((alto*TILESIDE) - 2* desfasaje) * tickCount[i] / tickCount[0];
		al_draw_bitmap(screen->blackPixel, desfasaje + x, ((alto*TILESIDE) - 2 * desfasaje) - y, ALLEGRO_FLIP_HORIZONTAL);
		x = x + xInc;
		al_flip_display();
	}
	

	while (!quit) {
		quit = displayQuit(screen->queue); //until quit button is pressed
	}

	al_destroy_display(screen->display);

	return SUCCESS;
}

int count(double* array) {
	
	int i = 0;

	while (array[i] != 0.0) {
		i++;
	}

	return i;
}



void endAllegro(allegroDisplay_t* screen) {

	al_destroy_display(screen->display);
	al_destroy_font(screen->font);
	al_destroy_event_queue(screen->queue);

	return;
}

void floorUpdate(allegroDisplay_t* screen, Piso_t* floor) {

	int x = 0, y = 0;
	int w = floor->ancho, h = floor->largo;
	for (int i = 0; i < (w*TILESIDE); i += 50) {
		x = 0; //reinicio x
		for (int j = 0; j < (h*TILESIDE); j += 50) {
			if (floor->get_status_baldosa(x,y))
				al_draw_bitmap(screen->cleanTile, (double)j, (double)i, ALLEGRO_FLIP_HORIZONTAL); //drawing clean tiles
			else
				al_draw_bitmap(screen->dirtyTile, (double)j, (double)i, ALLEGRO_FLIP_HORIZONTAL); //drawing dirty tiles
			x++;
		}
		y++;
	}

	return;
}

void microUpdate(double vec[MAXROBOTS][2], int i, double Xo, double Yo, double Xf, double Yf, double multiplier) {

	double vector[MAXROBOTS][2] = { *((double*)NULL) }; //vector posicion

	memcpy(vector, vec, MAXROBOTS * 2 * sizeof(double)); //working with auxiliary array
	
	vector[i][0] = Xo + ( (Xf-Xo) * multiplier); //mulitplies the multiplier with the difference of position
	vector[i][1] = Yo + ( (Yf-Yo) * multiplier);

	memcpy(vec, vector, MAXROBOTS * 2 * sizeof(double)); //copying aux

	return;
}


bool displayQuit(ALLEGRO_EVENT_QUEUE* queue) {

	bool quit = false, get_event = true;
	ALLEGRO_EVENT evento;

	while (get_event) { //until event queue is empty
		if (get_event = al_get_next_event(queue, &evento)) { //there is an event in the queue
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //the event is display closing
				quit = true;
		}
	}

	return quit;
}