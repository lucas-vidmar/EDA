#include "Allegro.h"

using namespace std;

allegroEssentials_t::allegroEssentials_t(int w, int h) {
	this->init_done = false;
	
	al_init();
	if (al_init_font_addon()) {
		if (al_init_ttf_addon()) {
			if (al_init_image_addon()) {
				if (al_install_mouse()) {
					if (al_install_keyboard())
					{
						if (!al_install_audio())
						{
							return;
						}

						if (!al_init_acodec_addon())
						{
							return;
						}
						if (!al_reserve_samples(1))
						{
							return;
						}
						sample = NULL;
						sample = al_load_sample("street_fighter_theme.wav");
						if (sample)
						{
							al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
						}


						//_new_display_refresh_rate(REFRESHRATE); //refresh rate de 30

						timer_refresh = al_create_timer(BPS_TO_SECS(FPS));

						queue = al_create_event_queue(); //creating event queue
						display = al_create_display((w * UNIDAD), (h * UNIDAD)); //setting display size
						
						
						if (!display)
						{
							cout << "no pude abrir el display" << endl;
							return;
						}
						al_set_window_position(display, 0, 0);

						font = al_load_ttf_font(FONTNAME, 50, ALLEGRO_TTF_MONOCHROME); //setting font monochrome

						al_register_event_source(queue, al_get_display_event_source(display)); //tide display to event queue
						al_register_event_source(queue, al_get_timer_event_source(timer_refresh));
						al_register_event_source(queue, al_get_keyboard_event_source());
						al_clear_to_color(al_map_rgba(255, 255, 0, 0)); //la inicializamos en rojo para que se vean los errores


						this->init_done = true;

						return; //success
					}
				}
				else
					cout << "Keyboard addon error" << endl;
			}
			else
				cout << "Mouse addon error" << endl;
		}
		else
			cout << "Font TTF addon error" << endl;
	}
	else
		cout << "Font addon error" << endl;

	return; //there was an error
}

ALLEGRO_TIMER * allegroEssentials_t::getTimerRefresh(void)
{

	return this->timer_refresh;

}


void allegroEssentials_t::startTimerRefresh(void)
{
	al_start_timer(this->timer_refresh);
	
}


allegroEssentials_t::~allegroEssentials_t()
{

	if (this->init_done)
	{


		al_destroy_display(this->display);
		al_destroy_font(this->font);
		al_destroy_event_queue(this->queue);
		al_destroy_timer(this->timer_refresh);

		al_uninstall_keyboard();
		
		al_uninstall_mouse();

		this->init_done = false;
	}

}

bool allegroEssentials_t::transferQueue(Queue* queueC, ALLEGRO_TIMER* timer[KeyUp + 1]) {

	bool get_event = true; 

	if (!queueC->isQueueFull()) { //queue is not full
		get_event = al_get_next_event(queue, &lastEvent); //is there is an event in the queue?
		if (get_event) { //if there is an event, we notify queueC
			switch (lastEvent.type) {
				case ALLEGRO_EVENT_TIMER: //we will see wich timer generated it
					if (lastEvent.timer.source == timer_refresh) //the time event is comming from refresh timer
						queueC->put_event(eventType::Refresh); //we just copy it to lastEvent
					else if (lastEvent.timer.source == timer[KeyUp] || lastEvent.timer.source == timer[KeyW]) 
						queueC->put_event(eventType::Jumping);
					else
						queueC->put_event(eventType::Walking);
					break;
				case ALLEGRO_EVENT_DISPLAY_CLOSE: queueC->put_event(eventType::Quit); break; //display close event
				case ALLEGRO_EVENT_KEY_DOWN: //pressed key
					switch (lastEvent.keyboard.keycode) {
						case ALLEGRO_KEY_ESCAPE: queueC->put_event(eventType::Quit); break; //display close event
						case ALLEGRO_KEY_LEFT:
						case ALLEGRO_KEY_RIGHT:
						case ALLEGRO_KEY_A:
						case ALLEGRO_KEY_D:
							queueC->put_event(eventType::Walking); break; //moving
						case ALLEGRO_KEY_W:
						case ALLEGRO_KEY_UP:
							queueC->put_event(eventType::Jumping); break; //jumping
						default: break;
					}
					break;
				case ALLEGRO_EVENT_KEY_UP: //released key
					switch (lastEvent.keyboard.keycode) { //we just copy it to lastEvent
						case ALLEGRO_KEY_LEFT:
						case ALLEGRO_KEY_RIGHT:
						case ALLEGRO_KEY_A:
						case ALLEGRO_KEY_D:
							queueC->put_event(eventType::Walking); break; //moving
						case ALLEGRO_KEY_W:
						case ALLEGRO_KEY_UP:
							queueC->put_event(eventType::Jumping); break; //jumping
						default: break;
					}
					break;
			}
		}
		else
			return ERROR;
	}

	return SUCCESS;

}


void backgroundUpdate(allegroEssentials_t* allegro, background_t* base) {

	int x = 0, y = 0;
	int w = 1920, h = 696;
	for (int i = 0; i < (w*UNIDAD); i += UNIDAD) {
		x = 0; //reinicio x
		for (int j = 0; j < (h*UNIDAD); j += UNIDAD) {
			al_draw_bitmap(base->get_images_background(), (double)i, (double)j, ALLEGRO_FLIP_HORIZONTAL); //drawing each background texture
			x++;
		}
		y++;
	}

	return;
}