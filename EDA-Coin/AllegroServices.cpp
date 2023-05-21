#include "allegroServices.h"

void allegroEssentials::clearDisplay(const char* color){
	this->drawHere();
	if (color=="white")
		al_clear_to_color(al_map_rgb(255, 255, 255));
	else if (color=="red")
		al_clear_to_color(al_map_rgb(255, 0, 0));
	else if (color == "blue")
		al_clear_to_color(al_map_rgb(0, 0, 255));
	else if (color == "green")
		al_clear_to_color(al_map_rgb(0, 255, 0));
	else
		al_clear_to_color(al_map_rgb(0, 0, 0));
}

void allegroEssentials::updateDisplay(void)
{
	this->drawHere();
	al_flip_display();
}

void allegroEssentials::drawHere(void) {
	al_set_target_backbuffer(display);
}

int dispatch(ALLEGRO_EVENT &ev) {

	switch (ev.type) {
	case ALLEGRO_EVENT_KEY_DOWN:
		return actions::keyDown;
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		return actions::keyChar;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		return actions::keyUp;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		return actions::mouseButtonDown;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		if (ev.mouse.button == 1)
			return actions::mouseButtonUp;
		else
			return actions::mouseDeselect;
		break;
	default:
		return actions::unidentified;
		break;


	}
}

void drawLine(double x1, double y1, double x2, double y2) {
	al_draw_line(x1, y1, x2, y2, al_map_rgb(0, 0, 0), 2);
}

/*
   ALLEGRO_EVENT_JOYSTICK_AXIS               =  1,
   ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN        =  2,
   ALLEGRO_EVENT_JOYSTICK_BUTTON_UP          =  3,
   ALLEGRO_EVENT_JOYSTICK_CONFIGURATION      =  4,

   ALLEGRO_EVENT_KEY_DOWN                    = 10,
   ALLEGRO_EVENT_KEY_CHAR                    = 11,
   ALLEGRO_EVENT_KEY_UP                      = 12,

   ALLEGRO_EVENT_MOUSE_AXES                  = 20,
   ALLEGRO_EVENT_MOUSE_BUTTON_DOWN           = 21,
   ALLEGRO_EVENT_MOUSE_BUTTON_UP             = 22,
   ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY         = 23,
   ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY         = 24,
   ALLEGRO_EVENT_MOUSE_WARPED                = 25,

   ALLEGRO_EVENT_TIMER                       = 30,

   ALLEGRO_EVENT_DISPLAY_EXPOSE              = 40,
   ALLEGRO_EVENT_DISPLAY_RESIZE              = 41,
   ALLEGRO_EVENT_DISPLAY_CLOSE               = 42,
   ALLEGRO_EVENT_DISPLAY_LOST                = 43,
   ALLEGRO_EVENT_DISPLAY_FOUND               = 44,
   ALLEGRO_EVENT_DISPLAY_SWITCH_IN           = 45,
   ALLEGRO_EVENT_DISPLAY_SWITCH_OUT          = 46,
   ALLEGRO_EVENT_DISPLAY_ORIENTATION         = 47,
   ALLEGRO_EVENT_DISPLAY_HALT_DRAWING        = 48,
   ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING      = 49,

   ALLEGRO_EVENT_TOUCH_BEGIN                 = 50,
   ALLEGRO_EVENT_TOUCH_END                   = 51,
   ALLEGRO_EVENT_TOUCH_MOVE                  = 52,
   ALLEGRO_EVENT_TOUCH_CANCEL                = 53,

   ALLEGRO_EVENT_DISPLAY_CONNECTED           = 60,
   ALLEGRO_EVENT_DISPLAY_DISCONNECTED        = 61
*/