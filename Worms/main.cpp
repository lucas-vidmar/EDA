#include <iostream>
#include <string>
#include "worm.h"
#include "EventGenerator.h"
#include "Queue.h"
#include "Allegro.h"
#include <iostream>


#define TEST 0

#define START_X_1 750
#define START_X_2 1198


using namespace std;


void
dispatch(eventType ev, worm** worms, int WormCount, allegroEssentials_t * al_p, ALLEGRO_TIMER* timer[KeyUp + 1], bool timerExpired[KeyUp + 1],
		 background_t * background);

#define QUIT eventType::Quit
#define WIDTH	1920
#define HEIGHT	696
#define BPS_TO_SECS(x)        (1.0 / (x))
#define FPS 50

#define TIMER_REFRESH_NUM 5

int
main(void)
{
	allegroEssentials_t Allegro(WIDTH,HEIGHT); //inicializo allegro
	al_flip_display();
	Queue myQueue;		//creo cola de eventos
	bool timerExpired[KeyUp + 1] = { false }; //state of each timer
	ALLEGRO_TIMER* timer[KeyUp + 1];
	for (int i = KeyA; i < KeyUp + 1 ; i++) { //creating timers
		timer[i] = al_create_timer(BPS_TO_SECS(FPS));
		al_register_event_source(Allegro.getQueue(), al_get_timer_event_source(timer[i])); //and making them generate events
	} 

	
	//timer[TIMER_REFRESH_NUM] = timer_refresh;


	int WormCount = 2;	//cantidad de worms
	worm  w1, w2;

	w1.setPosition_x(START_X_1);
	w2.setPosition_x(START_X_2);

	w1.setOrient(OrientType::right);
	w2.setOrient(OrientType::left);

	worm * worms[2];
	worms[0] = &w1;
	worms[1] = &w2;

	background_t background = background_t();
	eventType ev= eventType::Empty;

	Allegro.startTimerRefresh();

#if (TEST==1)

	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer[TIMER_REFRESH_NUM]));
	al_start_timer(timer[TIMER_REFRESH_NUM]);

#endif


	while (ev != QUIT)
	{

		Allegro.transferQueue(&myQueue, timer); //transfering one allegro event to queue
		
		myQueue.print();

		ev = myQueue.get_next_ev();
		cout << (int)ev << endl;

		#if (TEST==1)

		bool hay_evento = false;

		
		if (!al_is_event_queue_empty(event_queue))
		{
			al_get_next_event(event_queue, &ev1);

			if (ev1.type == ALLEGRO_EVENT_TIMER)
			{
				ev = eventType::Refresh;
				hay_evento = true;

			}
		}

		#endif
		
		if (ev != eventType::Empty)
			dispatch(ev, worms, WormCount, &Allegro, timer, timerExpired,&background);

	}


	
	return 0;
	}


void
dispatch(eventType ev, worm** worms, int WormCount, allegroEssentials_t * al_p, ALLEGRO_TIMER* timer[KeyUp + 1], bool timerExpired[KeyUp + 1],
			background_t * background) {

	switch (ev) {
		/*-----------------WALKING-----------------*/
		case eventType::Walking: 
			switch (al_p->getLastEvent().type) {

				/*KEY PRESSED CASE*/
				case ALLEGRO_EVENT_KEY_DOWN:
					switch (al_p->getLastEvent().keyboard.keycode) {
						case ALLEGRO_KEY_A:
							if (timerExpired[keys::KeyA] && !timerExpired[keys::KeyD] && !timerExpired[keys::KeyW] && (worms[0]->get_state() == state::idle) ) { //if timer expired for that key and other keys are not pressed (runned for 1 sec or more)
								worms[0]->setOrient(OrientType::left);
								worms[0]->walking();
							}
							else if (!timerExpired[keys::KeyD] && !timerExpired[keys::KeyW] && (worms[0]->get_state() == state::idle) ) { //timer hasnt expired (running under 1 sec)
								worms[0]->setOrient(OrientType::left);
								worms[0]->start_walking();
								if (!al_get_timer_started(timer[keys::KeyA])) //timer wasnt running
									al_start_timer(timer[keys::KeyA]); //we start the timer
							}
							break;
						case ALLEGRO_KEY_D:
							if (!timerExpired[keys::KeyA] && timerExpired[keys::KeyD] && !timerExpired[keys::KeyW] && (worms[0]->get_state() == state::idle) ) { //if timer expired for that key and other keys are not pressed (runned for 1 sec or more)
								worms[0]->setOrient(OrientType::right);
								worms[0]->walking();
							}
							else if (!timerExpired[keys::KeyA] && !timerExpired[keys::KeyW] && (worms[0]->get_state() == state::idle) ) { //timer hasnt expired and other timers havent expired either (running under 1 sec)
								worms[0]->setOrient(OrientType::right);
								worms[0]->start_walking();
								if (!al_get_timer_started(timer[keys::KeyD])) //timer wasnt running
									al_start_timer(timer[keys::KeyD]); //we start the timer
							}
							break;
						case ALLEGRO_KEY_LEFT:
							if (timerExpired[keys::KeyLeft] && !timerExpired[keys::KeyRight] && !timerExpired[keys::KeyUp] && (worms[1]->get_state() == state::idle) ) { //if timer expired for that key and other keys are not pressed (runned for 1 sec or more)
								worms[1]->setOrient(OrientType::left);
								worms[1]->walking();
							}
							else if (!timerExpired[keys::KeyRight] && !timerExpired[keys::KeyUp] && (worms[1]->get_state() == state::idle) ) { //timer hasnt expired and other timers havent expired either (running under 1 sec)
								worms[1]->setOrient(OrientType::left);
								worms[1]->start_walking();
								if (!al_get_timer_started(timer[keys::KeyLeft])) //timer wasnt running
									al_start_timer(timer[keys::KeyLeft]); //we start the timer
							}
							break;
						case ALLEGRO_KEY_RIGHT:
							if (!timerExpired[keys::KeyLeft] && timerExpired[keys::KeyRight] && !timerExpired[keys::KeyUp] && (worms[1]->get_state() == state::idle) ) { //if timer expired for that key and other keys are not pressed (runned for 1 sec or more)
								worms[1]->setOrient(OrientType::right);
								worms[1]->walking();
							}
							else if (!timerExpired[keys::KeyLeft] && !timerExpired[keys::KeyUp] && (worms[1]->get_state() == state::idle) ) { //timer hasnt expired and other timers havent expired either (running under 1 sec)
								worms[1]->setOrient(OrientType::right);
								worms[1]->start_walking();
								if (!al_get_timer_started(timer[keys::KeyRight])) //timer wasnt running
									al_start_timer(timer[keys::KeyRight]); //we start the timer
							}
							break;
						default: break;
					}
					break;

				/*KEY RELEASE CASE*/
				case ALLEGRO_EVENT_KEY_UP:
					switch (al_p->getLastEvent().keyboard.keycode) { //we stop timers and reset timers states
						case ALLEGRO_KEY_A: al_stop_timer(timer[keys::KeyA]); timerExpired[keys::KeyA] = false; break;
						case ALLEGRO_KEY_D:	al_stop_timer(timer[keys::KeyD]); timerExpired[keys::KeyD] = false; break;
						case ALLEGRO_KEY_LEFT: al_stop_timer(timer[keys::KeyLeft]); timerExpired[keys::KeyLeft] = false; break;
						case ALLEGRO_KEY_RIGHT: al_stop_timer(timer[keys::KeyRight]); timerExpired[keys::KeyRight] = false; break;
						default: break;
					}
					break;

				/*TIMER*/
				case ALLEGRO_EVENT_TIMER: //one of the timers timed out, we check which and we set time expire to true
					if (al_get_timer_count(timer[keys::KeyA]) > 1 && al_p->getLastEvent().timer.source == timer[keys::KeyA])
						timerExpired[keys::KeyA] = true;
					else if (al_get_timer_count(timer[keys::KeyD]) > 1 && al_p->getLastEvent().timer.source == timer[keys::KeyD])
						timerExpired[keys::KeyD] = true;
					else if (al_get_timer_count(timer[keys::KeyLeft]) > 1 && al_p->getLastEvent().timer.source == timer[keys::KeyLeft])
						timerExpired[keys::KeyLeft] = true;
					else if (al_get_timer_count(timer[keys::KeyRight]) > 1 && al_p->getLastEvent().timer.source == timer[keys::KeyRight])
						timerExpired[keys::KeyRight] = true;
					break;
			}
			break;
								

		/*-----------------JUMPING-----------------*/
		case eventType::Jumping:
			switch (al_p->getLastEvent().type) {

				/*KEY PRESSED CASE*/
				case ALLEGRO_EVENT_KEY_DOWN:
					switch (al_p->getLastEvent().keyboard.keycode) {
						case ALLEGRO_KEY_W:
							if (timerExpired[keys::KeyW] && !timerExpired[keys::KeyA] && !timerExpired[keys::KeyD] && (worms[0]->get_state() == state::idle) ) { //if timer expired for that key and other keys are not pressed (runned for 1 sec or more)
								worms[0]->jumping();
							}
							else if (!timerExpired[keys::KeyA] && !timerExpired[keys::KeyD] && (worms[0]->get_state() == state::idle) ) { //timer hasnt expired and other timers havent expired either (running under 1 sec)
								worms[0]->start_jumping();
								if (!al_get_timer_started(timer[keys::KeyW])) //timer wasnt running
									al_start_timer(timer[keys::KeyW]); //we start the timer
							}
							break;
						case ALLEGRO_KEY_UP:
							if (timerExpired[keys::KeyUp] && !timerExpired[keys::KeyLeft] && !timerExpired[keys::KeyRight] && (worms[1]->get_state() == state::idle) ) { //if timer expired for that key and other keys are not pressed (runned for 1 sec or more)
								worms[1]->jumping();
							}
							else if (!timerExpired[keys::KeyLeft] && !timerExpired[keys::KeyRight] && (worms[1]->get_state() == state::idle) ) { //timer hasnt expired and other timers havent expired either (running under 1 sec)
								worms[1]->start_jumping();
								if (!al_get_timer_started(timer[keys::KeyUp])) //timer wasnt running
									al_start_timer(timer[keys::KeyUp]); //we start the timer
							}
							break;
						default: break;
					}
					break;

				/*KEY RELEASE CASE*/
				case ALLEGRO_EVENT_KEY_UP:
					switch (al_p->getLastEvent().keyboard.keycode) { //we stop timers and reset timers states
						case ALLEGRO_KEY_W:	al_stop_timer(timer[keys::KeyW]); timerExpired[keys::KeyW] = false; break;
						case ALLEGRO_KEY_UP:	al_stop_timer(timer[keys::KeyUp]); timerExpired[keys::KeyUp] = false; break;
						default: break;
					}
					break;

				/*TIMER*/
				case ALLEGRO_EVENT_TIMER: //one of the timers timed out, we check which and we set time expire to true
					if (al_get_timer_count(timer[keys::KeyW]) > 1 && al_p->getLastEvent().timer.source == timer[keys::KeyW])
						timerExpired[keys::KeyW] = true;
					else if (al_get_timer_count(timer[keys::KeyUp]) > 1 && al_p->getLastEvent().timer.source == timer[keys::KeyUp])
						timerExpired[keys::KeyUp] = true;
					break;
			}
			break;


		/*-----------------REFRESHING-----------------*/
		case eventType::Refresh: //cada 20ms
			
			al_clear_to_color(al_map_rgba(255, 255, 0, 0)); //la inicializamos en rojo para que se vean los errores
			
			background->draw();

			for (int i = 0; i < WormCount; i++)
			{
				worms[i]->update();

				worms[i]->draw();

			}
			
			al_flip_display();
			break;	

		/*-----------------DEFAULT-----------------*/
		default: break;
	}

	return;
}


