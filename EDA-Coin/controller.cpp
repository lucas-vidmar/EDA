#include "controller.h"



void
simulation::dispatch(char c, red my_network)
{
	switch (c)
	{
		case 'i': case 'I':		//listar las instrucciones posibles
		{
			show_instructions();
			break;
		}
		case 'l': case 'L':		//listar los nodos
		{
			my_network.list_nodes();
			break;
		}
		case 'm': case 'M':		//minar
		{
			int i = 0;								//ojo! esto es para que compile, porque esto no va
			my_network.time_2_mine(get_miner(), i);
			list<Nodo*>::iterator it = my_network.get_network().begin();
			for (size_t i = 0; i < my_network.get_network_size(); i++)
			{
				(*it)->back_2_work();		//Vuelvo a marcar que todos estan sin recibir un bloque
				it++;
			}
			break;
		}
		case 'e': case 'E':		//Seleccionar minero
		{
			set_state(miner_selection);
			break;
		}
		case 'o': case 'O':		//selecionar nodo origen
		{
			set_state(origin_selection);
			break;
		}
		case 'd': case 'D':		//seleccionar destino
		{
			set_state(destiny_selection);
			break;
		}
		case 'c': case 'C':		//seleccionar cantidad
		{
			set_state(tx_quantity_selection);
			break;
		}
		case 't': case 'T':		//realizar una transacción
		{
			if (my_network.is_valid(get_origin(), get_destiny()))	//si los nodos indicados son válidos
			{
				my_network.generate_tx(get_origin(), get_destiny(), get_amount());
				cout << "Transacción realizada" << endl;
			}
			else
				cout << "No se pudo completar la tx" << endl;
			break;
		}
		case 's': case 'S':		//mostrar cómo será la próxima tx
		{
			show_next_tx();
			break;
		}
		case 'b': case 'B':		//borra los datos actuales para la proxima tx
		{
			erase();
			break;
		}
		case '0': case '1': case'2': case'3': case'4': case'5': case '6': case '7': case'8': case'9': 
		{
			char num;
			int new_num;
			switch (get_state())
			{
				case origin_selection:
				{
					num = c - '0';
					new_num = (int)num;
					set_destiny(new_num);
				}
				case destiny_selection:
				{
					num = c - '0';
					new_num = (int)num;
					set_origin(new_num);
				}
				case tx_quantity_selection:
				{
					num = c - '0';
					new_num = (int)num;
					new_amount(new_num);
				}
				case miner_selection:
				{
					num = c - '0';
					new_num = (int)num;
					set_miner(new_num);
				}
				default:
					break;
			}
		}
		default:
			break;
	}
}

/*void
simulation::dispatch(Nodo* node)
{																						
	switch (shown)
	{
		case showing_nodes:
		{
			switch (input)
			{
				case letter_down:
				{
					switch (command)		//this has nothing in special, you're suppossed to be looking at the nodes, no to do other things
					{
						case quit_:
							break;
						case null_:
							break;
						case timer_:
							break;
						default:
							break;
					}
				}
				case num_down:
					break;		//ignores, we're not expecting numbers here
				default:
					break;

			}
		}
		case destiny_selected:
		{
			switch (input)
			{
				case letter_down:
				{
					switch (command)
					{
						//adds the letter to what's going to be the the destiny node
						//general case
						/*case letter_x:
						{
							string letter ("x");
							destiny_node = destiny_node + letter;
						}
						default:
							break;
					}
				}
				case num_down:
					break;	//ignores, we're not expecting numbers here
			}
		}
		case origin_selected:
		{
			switch (input)
			{
				case letter_down:
				{
					switch (command)	//adds the letter to what's going to be the the origin node
					{
						//general case
						/*case letter_x:
						{
							string letter ("x");
							origin_node = origin_node + letter;
						}
						
					default:
						break;
					}
				}
				case num_down:
					break;	//ignores, we're not expecting numbers here
			}
		}
		case tx_quantity_selected:
		{
			switch (input)
			{
				case letter_down:
					break;	//ignores, we're not expecting letters here, except the keys left/right (change state) e (erase) and the q (quit)
				case num_down:
				{
					switch (command)
					{
					//prototype of general case
					/*case num_x:
					{
						coins *= 10;
						coins += x;
					}

					default:
						break;
					}
				}
			}
		}
		case create_tx:
			//prototype
			/*{
				if (does_it_exist(origin_node, destiny_node))
				{
					origin->createTX (ID, publick_key, coins);
					destiny->notify_all_observers();
				}

			}
			//creates the so-called tx and adds it to its txs list
			//after all changes it'd be ideal to notify the observers
			break;
		default:
			break;
			
	
	}
}*/