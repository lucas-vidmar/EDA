#include "Supervisor.h"

#include <iostream>

#include "Compressor.h"
#include "Descompressor.h"


//auxiliar function
void refresh_display(viewer& viewer_, board& board_);


//listo
supervisor::supervisor(viewer& viewer, double threshold)
{
	this->init = true;
	this->finish = false;

	if (!al_install_keyboard())
	{
		this->init = false;
		this->finish = false;
	}
	if ( (!al_install_mouse()) && (this->init))
	{
		if (this->init)
		{
			al_uninstall_keyboard();
		}

		this->init = false;
		this->finish = false;
	}


	this->ev_queue = al_create_event_queue();
	
	if (ev_queue == nullptr)
	{
		al_uninstall_mouse();
		al_uninstall_keyboard();

		this->init = false;
		this->finish = false;

	}
	else if (this->init)
	{
		al_register_event_source(ev_queue, al_get_display_event_source(viewer.get_display()));
		al_register_event_source(ev_queue, al_get_mouse_event_source());
		al_register_event_source(ev_queue, al_get_keyboard_event_source());

		this->threshold = threshold;

	}
	
}

//listo
supervisor::~supervisor()
{
	if (this->init)
	{
		al_uninstall_mouse();
		al_uninstall_keyboard();
		al_destroy_event_queue(this->ev_queue);

		this->init = false;

	}
	
}

//listo
void supervisor::dispatcher(viewer& viewer, board& board)
{
	ALLEGRO_EVENT ev;
	al_get_next_event(ev_queue, &ev);
	unsigned int key_pressed;
	std::vector<ImageDescriptor> & vector_images = board.get_images();

	switch (ev.type)
	{
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		this->finish = true;
		break;

	case ALLEGRO_EVENT_KEY_DOWN:
		switch (ev.keyboard.keycode) //Para cada uno de estos casos debe actualizarse el display.
		{
		case ALLEGRO_KEY_A: //se selecciona todas las imagenes presentes en la pantalla
			board.select_all_images();
			refresh_display(viewer, board);
			break;

		case ALLEGRO_KEY_N: //se deselecciona todas las imagenes presentes en la pantalla
			board.unselect_all_images();
			refresh_display(viewer, board);
			break;

		case ALLEGRO_KEY_1: 
		case ALLEGRO_KEY_2:
		case ALLEGRO_KEY_3: 
		case ALLEGRO_KEY_4: 
		case ALLEGRO_KEY_5:
		case ALLEGRO_KEY_6: 
		case ALLEGRO_KEY_7: 
		case ALLEGRO_KEY_8: 
		case ALLEGRO_KEY_9:
			
			key_pressed = ev.keyboard.keycode - ALLEGRO_KEY_1;
			
			vector_images = board.get_images();

			(vector_images)[key_pressed].toggle_selection();

			refresh_display(viewer, board);

			break;


		case ALLEGRO_KEY_ENTER:
			if (board.is_some_image_select())
			{
				unsigned int mode = viewer.get_mode();
				
				const char * txt = NULL;

				if (mode == MODE_COMPRESSOR)
				{
					txt = "COMPRIMIENDO";
				}
				else if (mode == MODE_DESCOMPRESSOR)
				{
					txt = "DESCOMPRIMIENDO";
				}

				viewer.print_message(txt);

				al_flip_display(); 


				


				for (unsigned int i = 0; i < vector_images.size(); i++)
				{
					if ((vector_images[i]).is_select())
					{
						if (mode == MODE_COMPRESSOR)
						{
							if (compress_image((vector_images[i]).get_path(), (vector_images[i]).get_path(), threshold))
							{
								std::cout << "Compresion de: " << (vector_images[i]).get_path() << " lograda" << std::endl;
							}
							else
							{
								std::cout << "Compresion de: " << (vector_images[i]).get_path() << " fallo" << std::endl;
							}


						}
						else if (mode == MODE_DESCOMPRESSOR)
						{
							if (descompress_image((vector_images[i]).get_path(), (vector_images[i]).get_path()))
							{
								std::cout << "Descompresion de: " << (vector_images[i]).get_path() << " lograda" << std::endl;
							}
							else
							{
								std::cout << "Descompresion de: " << (vector_images[i]).get_path() << " fallo" << std::endl;
							}

						}
					}
				}


				viewer.update_display(board);
				
				txt = NULL;

				if (mode == MODE_COMPRESSOR)
				{
					txt = "COMPRESION TERMINADA";
				}
				else if (mode == MODE_DESCOMPRESSOR)
				{
					txt = "DESCOMPRESION TERMINADA";
				}


				viewer.print_message(txt);
				al_flip_display();
				viewer.update_display(board);

			}
			break;
		}
		break;

	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		board.touch( (int)ev.mouse.x, (int)ev.mouse.y );
		
		refresh_display(viewer, board);
		
		break;

	}
}

//listo
bool supervisor::is_init(void)
{
	return (this->init);
}

//listo
bool supervisor::is_finish(void)
{
	return (this->finish);
}


void refresh_display(viewer& viewer_, board& board_)
{
	al_set_target_backbuffer(viewer_.get_display());
	viewer_.update_display(board_);
	al_flip_display();
}