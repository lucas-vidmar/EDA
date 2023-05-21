#include "allegro.h"

allegroEssentials_t::allegroEssentials_t(int w, int h) {
	al_init();
	if (al_init_font_addon()) {
		if (al_init_ttf_addon()) {
			if (al_init_image_addon()) {
				if (al_install_mouse()) {
					if (al_install_keyboard())
					{

						al_set_new_display_refresh_rate(REFRESHRATE); //refresh rate de 30

						queue = al_create_event_queue(); //creating event queue
						display = al_create_display((w * UNIDAD), (h * UNIDAD)); //setting display size
						font = al_load_ttf_font("angryBirds.ttf", 50, ALLEGRO_TTF_MONOCHROME); //setting font monochrome

						al_register_event_source(queue, al_get_display_event_source(display)); //tide display to event queue

						al_clear_to_color(al_map_rgba(255, 0, 0, 0)); //la inicializamos en rojo para que se vean los errores

						return; //success
					}
				}
				else
					printf("Mouse addon error");
			}
			else
				printf("Mouse addon error");
		}
		else
			printf("Font TTF addon error");
	}
	else
		printf("Font addon error");
	
	return; //there was an error
}

int get_keyboard(ALLEGRO_EVENT_QUEUE *event_queue)
{
	ALLEGRO_EVENT event;
	if ((al_get_next_event(event_queue, &event)) && (event.type == ALLEGRO_EVENT_KEY_DOWN))
		return event.keyboard.keycode;
}

void objectUpdate(allegroEssentials_t* allegro, background_t* base, Bird* object, int cant)
{
	al_draw_rotated_bitmap (object->getBitmap(), al_get_bitmap_width( object->getBitmap())/2, \
							al_get_bitmap_height(object->getBitmap())/2, object[cant].whereIsBirdX()*(UNIDAD), \
		                    object[cant].whereIsBirdY()*(UNIDAD), object[cant].whereIsBirdAngle()*ALLEGRO_PI/180,0);
	
	al_flip_display();
}

void microUpdate(int cant, double* pos, const double* prev, const double* next, const int i, const double multiplier) {

	*(pos + i * cant + 0) = *(prev + i * cant + 0) + (*(next + i * cant + 0) - *(prev + i * cant + 0)) * multiplier; //mulitplies the multiplier with the difference of position
	*(pos + i * cant + 1) = *(prev + i * cant + 1) + (*(next + i * cant + 1) - *(prev + i * cant + 1)) * multiplier;

	return;
}

int popUp(const char* word, allegroEssentials_t* screen, int ancho, int alto) {

	bool quit = false;
	ALLEGRO_DISPLAY* pop = al_create_display((ancho * UNIDAD), (alto * UNIDAD)); //setting display
	al_set_new_display_refresh_rate(REFRESHRATE); //refresh rate
	al_set_target_backbuffer(pop); //switches to new display

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //creating new queue
	al_register_event_source(queue, al_get_display_event_source(pop)); //tide disaply to event queue

	al_clear_to_color(al_map_rgba(0, 0, 0, 0)); //all to black

	al_draw_text(screen->getFont(), al_map_rgb(255, 255, 255), (ancho * UNIDAD /2), (alto * UNIDAD / 2), ALLEGRO_ALIGN_CENTER, word); //draw word
	al_flip_display(); //updates display


	while (!quit) {
		quit = displayQuit(queue); //until quit button is pressed
	}

	al_set_target_backbuffer(screen->getDisplay()); //switches to old display

	al_destroy_display(pop);
	al_destroy_event_queue(queue);

	return SUCCESS;
}

int count(double* array) {
	
	int i = 0;

	while (array[i] != 0.0) {
		i++;
	}

	return i;
}



void endAllegro(allegroEssentials_t* screen) {

	al_destroy_display(screen->getDisplay());
	al_destroy_font(screen->getFont());
	al_destroy_event_queue(screen->getQueue());

}

void backgroundUpdate(allegroEssentials_t* allegro, background_t* base) {

	int x = 0, y = 0;
	int w = base->getWidth(), h = base->getHeight();
	for (int i = 0; i < (w*UNIDAD); i += UNIDAD) {
		x = 0; //reinicio x
		for (int j = 0; j < (h*UNIDAD); j += UNIDAD) {
			al_draw_bitmap(base->getBitmap(), (double)i, (double)j, ALLEGRO_FLIP_HORIZONTAL); //drawing each background texture
			x++;
		}
		y++;
	}

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