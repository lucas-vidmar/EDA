#ifndef ALLEGROAUX_H
#define ALLEGROAUX_H

//*************************************************INCLUDES*************************************************
#include "drawableObject.h"
#include <allegro5/allegro_native_dialog.h>

//*************************************************DEFINES*************************************************
#define SUCCESS (1)
#define FAILURE (0)
#define W_DIS (800)	
#define H_DIS (600)	
#define TEXT_SIZE (20)
#define TEXT_FLAG (0)

using namespace std;

/*Actions*/
enum actions { mouseButtonUp, mouseButtonDown, displayClosed, keyDown, keyChar, keyUp , unidentified, mouseSelect, mouseDeselect};

/*Class*/
class allegroEssentials: public drawableObject {
public:
	/*Default Builder*/
	allegroEssentials() {
		texture = NULL;
		display = NULL;
		queue = NULL;
		posX = 0;
		posY = 0;
		// Instalamos Allegro
		if (!al_init())
		{
			cout << "Failed to initialize Allegro" << endl;
			delete this;
			return;
		}
		//Image Addon init
		if (!al_init_image_addon()) {
			cout << "Failed to initialize Allegro Image Addon" << endl;
			delete this;
			return;
		}
		//Installing keyboard
		if (!al_install_keyboard())
		{
			cout << "Failed to initialize the keyboard" << endl;
			delete this;
			return;
		}
		//Installing Mouse
		if (!al_install_mouse())
		{
			cout << "Failed to initialize the mouse" << endl;
			delete this;
			return;
		}
		//Primitives addon
		if (!al_init_primitives_addon())
		{
			cout << "Failed to initialize primitives Addon" << endl;
			delete this;
			return;
		}
		//FUENTE
		if (!al_init_font_addon())
		{
			cout << "Failed to initialize Font Addon" << endl;
			delete this;
			return;
		}
		//FORMATO DE FUENTE
		if (!al_init_ttf_addon())
		{
			cout << "Failed to initialize ttf Addon" << endl;
			delete this;
			return;
		}
		//cargo la fuente
		font = al_load_ttf_font("arial_narrow_7.ttf", TEXT_SIZE, TEXT_FLAG);
		if (font == nullptr)
		{
			cout << "Failed to create font!" << endl;
			delete this;
			return;
		}

		return;
	}
	/*Builder*/
	allegroEssentials(double w, double h, const char* background, double posX_, double posY_) {
		sizeX = w;
		sizeY = h;
		// Instalamos Allegro
		if (!al_init())
		{
			cout << "Failed to initialize Allegro" << endl;
			delete this;
			return;
		}
		//Image Addon init
		if (!al_init_image_addon()) {
			cout << "Failed to initialize Allegro Image Addon" << endl;
			delete this;
			return;
		}
		//Creamos event queue
		queue = al_create_event_queue();
		if (!queue)
		{
			cout << "Failed to create event_queue!" << endl;
			delete this;
			return;
		}
		//Setting Background
		if (background != "None") {
			texture = al_load_bitmap(background);
			if (texture == nullptr) {
				cout << "Failed to initialize the background texture" << endl;
				delete this;
				return;
			}
		}
		//Installing keyboard
		if (!al_install_keyboard())
		{
			cout << "Failed to initialize the keyboard" << endl;
			delete this;
			return;
		}
		//Installing Mouse
		if (!al_install_mouse())
		{
			cout << "Failed to initialize the mouse" << endl;
			delete this;
			return;
		}
		//Primitives addon
		if (!al_init_primitives_addon())
		{
			cout << "Failed to initialize primitives Addon" << endl;
			delete this;			
			return;
		}
		//FUENTE
		if (!al_init_font_addon())
		{
			cout << "Failed to initialize Font Addon" << endl;
			delete this;
			return;
		}
		//FORMATO DE FUENTE
		if (!al_init_ttf_addon())
		{
			cout << "Failed to initialize ttf Addon" << endl;
			delete this;
			return;
		}
		//cargo la fuente
		font = al_load_ttf_font("arial_narrow_7.ttf", TEXT_SIZE, TEXT_FLAG);
		if (font == nullptr)
		{
			cout << "Failed to create font!" << endl;
			delete this;
			return;
		}
		// Inicializo el display
		display = al_create_display(w, h);
		if (display == nullptr)
		{
			cout << "Failed to create display!" << endl;
			delete this;
			return;
		}
		al_set_window_title(display, "EDACoin");

		/*Register event sources*/
		al_register_event_source(queue, al_get_display_event_source(display));	//Registro al display como generador de eventos
		al_register_event_source(queue, al_get_keyboard_event_source());	//Registro al teclado como generador de eventos
		al_register_event_source(queue, al_get_mouse_event_source()); //Registro al mouse como generador de evento

		al_set_window_position(display, posX_, posY_);
		posX = posX_;
		posY = posY_;

		return;
	}
	/*Destroyer*/
	~allegroEssentials() {
		al_destroy_display(display);
		al_destroy_font(font);
		if (queue!=nullptr)
			al_destroy_event_queue(queue);
		al_uninstall_keyboard();
		al_uninstall_mouse();
		al_shutdown_primitives_addon();
		al_shutdown_font_addon();
	}
	/*Getters*/
	ALLEGRO_EVENT_QUEUE* get_event_queue() { return queue; }
	ALLEGRO_DISPLAY* get_display() { return display; }
	ALLEGRO_FONT* get_font() { return font; }

	/*Methods*/
	void drawObject() { return; }
	void dedrawObject() { return; }
	void clearDisplay(const char* color);
	void updateDisplay(void);
	void drawHere(void);
	void popUp() {
		int button = al_show_native_message_box(
			display,
			"Warning",
			"Are you sure?",
			"If you click yes then you are confirming that \"Yes\" "
			"is your response to the query which you have "
			"generated by the action you took to open this "
			"message box.",
			NULL,
			ALLEGRO_MESSAGEBOX_YES_NO
		);
	}

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_FONT* font;
};

/*Funciones*/
int dispatch(ALLEGRO_EVENT &ev); //tells which action to perform
void drawLine(double x1, double y1, double x2, double y2);

#endif