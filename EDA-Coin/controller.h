#pragma once
#include "red.h"

enum state { destiny_selection, origin_selection, tx_quantity_selection, miner_selection};
//enum al_general_events { letter_down, num_down };
//enum al_specific_events { quit_, null_, timer_ };
/*
class simulation
{
public:
	void dispatch(Nodo* node);
	void attach_node(Nodo* node) {
		list <Nodo*> ::iterator it = nodes.end();
		nodes.insert(it, node);
	}
	void deattach_node(Nodo* node) {
		list <Nodo*> ::iterator it;
		for (it = nodes.begin(); it != nodes.end(); it++)
		{
			if (*it == node)
			{
				nodes.remove(*it);
			}
		}
	}
	bool does_it_exist(Nodo* origin, Nodo* destiny) {
		list <Nodo*> ::iterator it = nodes.begin();
		bool o_ex = false;
		bool d_ex = false;
		for (size_t i = 0; i < nodes.size(); i++)
		{
			if (*it == origin)
			{
				o_ex = true;
			}
			it++;
		}
		it = nodes.begin();
		for (size_t i = 0; i < nodes.size(); i++)
		{
			if (*it == destiny)
			{
				d_ex = true;
			}
			it++;
		}
		if (o_ex && d_ex)
			return true;
		else
			return false;
	}
	//Setters
	void set_state(state new_s) { shown = new_s; }
	void set_Gev(al_general_events ev) { input = ev; }
	void set_Sev(al_specific_events ev) { command = ev; }
	//Getters
	state get_state(void) { return shown; }
	al_general_events get_Gev(void) { return input; }
	al_specific_events get_Sev(void) { return command; }
private:
	//For TX creation (the "Cajita")
	string origin_node;
	string destiny_node;
	int coins;
	//The current simulation nodes
	list <Nodo*> nodes;
	//States
	state shown;
	al_general_events input;
	al_specific_events command;
};

*/


class simulation
{
public:
	void dispatch(char c, red my_network);
	void show_next_tx(void) {
		cout << "Próxima transacció:" << endl;
		cout << "Desde nodo" << origin << " hasta nodo" << destiny << endl;
		cout << "Se enviarán un total de " << amount << " EDA coins, presione T para confirmar" << endl;
	}
	void show_instructions(void){
		cout << "Lista de instruciones:" << endl << endl;
		cout << "Presione L para listar los nodos" << endl;
		cout << "Presione O para seleccionar el nodo origen" << endl;
		cout << "Presione D para seleccionar el nodo destino" << endl;
		cout << "Presione E para seleccionar el minero de su transacción" << endl;
		cout << "Presione C para seleccionar la cantidad a transferir" << endl;
		cout << "Presione S para mostrar cómo será la próxima transacción" << endl;
		cout << "Presione T para realizar la transacción" << endl;
		cout << "Presione B para borrar los datos indicados" << endl;
		cout << "Presione M para que el minero haga su trabajo" << endl;
		cout << "Presione Q para salir del programa" << endl;
		cout << "Si en algún momento desea volver a ver las instrucciones presione I" << endl;

	}
	//Getters
	state get_state(void) { return current_state; }
	unsigned int get_amount(void) { return amount; }
	unsigned int get_origin(void) { return origin; }
	unsigned int get_destiny(void) { return destiny; }
	unsigned int get_miner(void) { return minero; }
	//Setters
	void erase(void) {
		origin = 0;
		destiny = 0;
		amount = 0;
		minero = 0;
	}
	void set_state(state new_state) { current_state = new_state; }
	void new_amount(unsigned int n) {
		amount = amount * 10 + n;
	}
	void set_origin(unsigned int n) { origin = origin * 10 + n; }
	void set_destiny(unsigned int n) { destiny = destiny * 10 + n; }
	void set_miner(unsigned int n) { minero = minero * 10 + n; }
	
private:
	unsigned int origin;
	unsigned int destiny;
	unsigned int amount;
	unsigned int minero;
	state current_state;
	std::chrono::time_point<std::chrono::system_clock> start;
};

