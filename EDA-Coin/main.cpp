/*General Includes*/
#include <fstream>
#include <time.h>
#include <stack>
#include <cstdlib>
#include <Windows.h>
#include <nlohmann/json.hpp>

#include "AllegroServices.h"
#include "NodoFull.h"
#include "SPV.h"
#include "miscellaneous.h"
#include "Transaction.h"

#include "controller.h"
#include "model.h"

#include "minero.h"
#include "red.h"
#include "mygraph.h"

/*Allegro Includes*/
#include "button.h"
#include "text.h"
#include "AllegroServices.h"

using namespace std;

using namespace nlohmann;	//59245

void arrange_in_rombo(button* nodes, allegroEssentials &nodesDis, int cant);
void drawConnections(list <Nodo*> lista, button* nodes);
void createTransaction(const char* n, int nodeID1, int nodeID2, list <Nodo*> lista);

#define JSONPATH "backlog.json"


/*
--------------------------------------------------------
Para compilar prueba de allegro definir COMPILE_ALLEGRO
Para compilar lo otro commentar la linea que sigue abajo
--------------------------------------------------------
*/

#define COMPILE_ALLEGRO
#ifdef COMPILE_ALLEGRO

int main(void) {

	/*Backend*/

	srand(time(0));
	//Recibo por linea de comando con cuantos nodos trabajo
	int fullNodes = 10;/*(int) argv[1];*/
	int miners = 5;/*(int)argv[2];*/
	int spvs = 5;/*(int)argv[3];*/
	//controlo primero que metan los parametros como se debe
	red my_network(fullNodes, miners, spvs);	//armo la red con todos los modos full puros y mineros
	if (fullNodes >= 5 && fullNodes <= 20 && miners <= fullNodes && miners >= 5 && miners <= 20 && spvs >= 5 && spvs <= 20)
	{
		cout << "Network size: " << my_network.get_network_size() << endl;
		my_network.list_nodes();
		my_network.connect_nodes();					//conecto todos los nodos full, con al menos dos vecinos por nodo
		my_network.list_nodes();
		GraphL ad_matrix(fullNodes);				//armo mi matriz de adyacencia con n nodos full
		ad_matrix.set_connections(my_network);		//Indico qué nodos están conectados entre sí
		dfs(&ad_matrix, 0);							//recorro toda la matriz a partir del primer nodo

		while (!ad_matrix.is_conex())				//Busca los nodos desconectados y genera nuevas conexiones hasta que sea conexo
		{
			int desertor = ad_matrix.give_me_an_autist();
			my_network.fix_conection(desertor);
			dfs(&ad_matrix, 0);
		}
		my_network.add_filters();					//agrego los spv, cada uno se attachea a dos full antes de unirse
		
	}


	/*-------------------------------------ALLEGRO-------------------------------------*/
	/*Front End*/
	list <Nodo*> lista = my_network.get_network();
	list <Nodo*>::iterator it = lista.begin();
	/*Setting visual ID*/
	for (int i = 0; i < lista.size(); i++) {
		(*it)->set_visualID(i);
		it++;
	}

	int cantNodos = 20;
	double w1 = 500, w2 = w1 / 2, h1 = w1, h2 = h1, secondRowButtons = 120;
	allegroEssentials nodesDis(w1, h1, "None", w1/4, w1 / 4);
	allegroEssentials inputDis(w2, h2, "None", w1 / 4 + 10 + w1, w1 / 4);

	button transButton("button.jpg", "buttonPressed.jpg", w2 / 2, 50, 109, 41, "New Trans", inputDis.get_font());
	button* nodes = new button[cantNodos];
	button leftArrow("arrowR.jpg", "arrowRPressed.jpg", 30, secondRowButtons, 50, 50, "none", inputDis.get_font());
	button rightArrow("arrowL.jpg", "arrowLPressed.jpg", inputDis.get_sizeX() - 30, secondRowButtons - 5, 50, 50, "none", inputDis.get_font());

	stack <int> buttonLog;

	string coinNumber("0");
	text coinNumberText(inputDis.get_sizeX() / 2, secondRowButtons, coinNumber.c_str(), "black");

	/*Por ahora es con 20 nodos, despues veo como hacerlo escalable*/
	arrange_in_rombo(nodes, nodesDis, cantNodos);

	/*Drawing in inputDis*/
	inputDis.drawHere(); //sets inputdis as backbuffer
	inputDis.clearDisplay("white"); //clears to color selected
	transButton.drawObject(); //drawing button in current backbuffer
	leftArrow.drawObject();
	rightArrow.drawObject();
	coinNumberText.drawObject();

	/*Drawing in nodesDis*/
	nodesDis.drawHere(); //sets nodesDis as backbuffer
	nodesDis.clearDisplay("white"); //clears to color selected
	for (int i = 0; i < cantNodos; i++) { //printing nodes
		nodes[i].drawObject();
	}


	drawConnections(lista, nodes);
	/*Drawing connections*/

	/*Events*/
	ALLEGRO_EVENT ev1, ev2;
	int action;
	bool switcher = true;

	do {
		/*Gettin events*/
		al_get_next_event(inputDis.get_event_queue(), &ev1);
		al_get_next_event(nodesDis.get_event_queue(), &ev2);

		/*Alternating between events from display 1 and display 2*/
		if (switcher) {
			action = dispatch(ev1);
			switcher = !switcher;
		}
		else {
			action = dispatch(ev2);
			switcher = !switcher;
		}


		/*Handling events*/
		switch (action) {
		case actions::displayClosed:
			break;
		case actions::mouseSelect:
			/*New Trans Button*/
			if (ev1.mouse.x >= transButton.get_regionXMin() && ev1.mouse.x <= transButton.get_regionXMax() && ev1.mouse.y >= transButton.get_regionYMin() && ev1.mouse.y <= transButton.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				transButton.pressButton();
			}
			/*Nodes*/
			for (int i = 0; i < cantNodos; i++) {
				if (ev2.mouse.x >= nodes[i].get_regionXMin() && ev2.mouse.x <= nodes[i].get_regionXMax() && ev2.mouse.y >= nodes[i].get_regionYMin() && ev2.mouse.y <= nodes[i].get_regionYMax()) {
					nodesDis.drawHere();
					nodes[i].pressButton();
					drawConnections(lista, nodes);
					buttonLog.push(i);
				}
			}
			/*Arrows*/
			if (ev1.mouse.x >= rightArrow.get_regionXMin() && ev1.mouse.x <= rightArrow.get_regionXMax() && ev1.mouse.y >= rightArrow.get_regionYMin() && ev1.mouse.y <= rightArrow.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				rightArrow.pressButton();
				coinNumber = to_string(1 + stoi(coinNumber));
				coinNumberText.set_text(coinNumber.c_str());
				coinNumberText.dedrawObject();
				coinNumberText.drawObject();
			}
			if (ev1.mouse.x >= leftArrow.get_regionXMin() && ev1.mouse.x <= leftArrow.get_regionXMax() && ev1.mouse.y >= leftArrow.get_regionYMin() && ev1.mouse.y <= leftArrow.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				leftArrow.pressButton();
				coinNumber = to_string(-1 + stoi(coinNumber));
				coinNumberText.set_text(coinNumber.c_str());
				coinNumberText.dedrawObject();
				coinNumberText.drawObject();
			}
			break;
		case actions::mouseButtonDown:
			/*New Trans Button*/
			if (ev1.mouse.x >= transButton.get_regionXMin() && ev1.mouse.x <= transButton.get_regionXMax() && ev1.mouse.y >= transButton.get_regionYMin() && ev1.mouse.y <= transButton.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				transButton.pressButton();
			}
			/*Nodes*/
			for (int i = 0; i < cantNodos; i++) {
				if (ev2.mouse.x >= nodes[i].get_regionXMin() && ev2.mouse.x <= nodes[i].get_regionXMax() && ev2.mouse.y >= nodes[i].get_regionYMin() && ev2.mouse.y <= nodes[i].get_regionYMax()) {
					nodesDis.drawHere();
					nodes[i].pressButton();
					drawConnections(lista, nodes);
				}
			}
			/*Arrows*/
			if (ev1.mouse.x >= rightArrow.get_regionXMin() && ev1.mouse.x <= rightArrow.get_regionXMax() && ev1.mouse.y >= rightArrow.get_regionYMin() && ev1.mouse.y <= rightArrow.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				rightArrow.pressButton();
				coinNumber = to_string(1 + stoi(coinNumber));
				coinNumberText.set_text(coinNumber.c_str());
				coinNumberText.dedrawObject();
				coinNumberText.drawObject();
			}
			if (ev1.mouse.x >= leftArrow.get_regionXMin() && ev1.mouse.x <= leftArrow.get_regionXMax() && ev1.mouse.y >= leftArrow.get_regionYMin() && ev1.mouse.y <= leftArrow.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				leftArrow.pressButton();
				coinNumber = to_string(-1 + stoi(coinNumber));
				coinNumberText.set_text(coinNumber.c_str());
				coinNumberText.dedrawObject();
				coinNumberText.drawObject();
			}
			break;
		case actions::mouseButtonUp:
			/*New Trans Button*/
			if (ev1.mouse.x >= transButton.get_regionXMin() && ev1.mouse.x <= transButton.get_regionXMax() && ev1.mouse.y >= transButton.get_regionYMin() && ev1.mouse.y <= transButton.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				transButton.releaseButton();
				/*
				if (createTransaction())
					inputDis.popUp();
				else
					inputDis.popUp();
				*/
			}
			/*Nodes*/
			for (int i = 0; i < cantNodos; i++) {
				if (ev2.mouse.x >= nodes[i].get_regionXMin() && ev2.mouse.x <= nodes[i].get_regionXMax() && ev2.mouse.y >= nodes[i].get_regionYMin() && ev2.mouse.y <= nodes[i].get_regionYMax()) {
					nodesDis.drawHere();
					nodes[i].releaseButton();
					drawConnections(lista, nodes);
				}
			}
			/*Arrows*/
			if (ev1.mouse.x >= rightArrow.get_regionXMin() && ev1.mouse.x <= rightArrow.get_regionXMax() && ev1.mouse.y >= rightArrow.get_regionYMin() && ev1.mouse.y <= rightArrow.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				rightArrow.releaseButton();
			}
			if (ev1.mouse.x >= leftArrow.get_regionXMin() && ev1.mouse.x <= leftArrow.get_regionXMax() && ev1.mouse.y >= leftArrow.get_regionYMin() && ev1.mouse.y <= leftArrow.get_regionYMax()) { //if inside button
				inputDis.drawHere();
				leftArrow.releaseButton();
			}
			break;
		case actions::mouseDeselect:
			/*Nodes*/
			for (int i = 0; i < cantNodos; i++) {
				if (ev2.mouse.x >= nodes[i].get_regionXMin() && ev2.mouse.x <= nodes[i].get_regionXMax() && ev2.mouse.y >= nodes[i].get_regionYMin() && ev2.mouse.y <= nodes[i].get_regionYMax()) {
					nodesDis.drawHere();
					drawConnections(lista, nodes);
					buttonLog.pop();
				}
			}
		default:
			break;
		}

		/*Update both Displays*/
		cout << "last in queue" << buttonLog.top() << endl;
		inputDis.updateDisplay();
		nodesDis.updateDisplay();

	} while (ev2.type != ALLEGRO_EVENT_DISPLAY_CLOSE && ev1.type != ALLEGRO_EVENT_DISPLAY_CLOSE); //end if close button was pressed

	return 0;
}

void arrange_in_rombo(button* nodes, allegroEssentials &nodesDis, int cant) {
	/*vertice uno*/
	for (int i = 0; i < cant / 4; i++) {
		button node("node.jpg", "nodePressed.jpg", 30 + i * nodesDis.get_sizeX() / 12, nodesDis.get_sizeY() / 2 - 30 - i * nodesDis.get_sizeY() / 12, 44, 50, "none", nodesDis.get_font());
		nodes[i] = node;
	}
	/*vertice dos*/
	for (int i = 0; i < cant / 4; i++) {
		button node("node.jpg", "nodePressed.jpg", nodesDis.get_sizeX() - 30 - i * nodesDis.get_sizeX() / 12, nodesDis.get_sizeY() / 2 - 30 - i * nodesDis.get_sizeY() / 12, 44, 50, "none", nodesDis.get_font());
		nodes[cant / 4 + i] = node;
	}
	/*vertice tres*/
	for (int i = 0; i < cant / 4; i++) {
		button node("node.jpg", "nodePressed.jpg", nodesDis.get_sizeX() - 30 - i * nodesDis.get_sizeX() / 12, nodesDis.get_sizeY() / 2 + 30 + i * nodesDis.get_sizeY() / 12, 44, 50, "none", nodesDis.get_font());
		nodes[2 * cant / 4 + i] = node;
	}
	/*vertice cuatro*/
	for (int i = 0; i < cant / 4; i++) {
		button node("node.jpg", "nodePressed.jpg", 30 + i * nodesDis.get_sizeX() / 12, nodesDis.get_sizeY() / 2 + 30 + i * nodesDis.get_sizeY() / 12, 44, 50, "none", nodesDis.get_font());
		nodes[3 * cant / 4 + i] = node;
	}
}

bool createTransaction(const char* n, button* nodes, list <Nodo*> lista) {
	int number = std::atoi(n);
	int cantOfSelected = 0;
	int nodeID1, nodeID2;
	Nodo *dest, *origen;
	bool first = true; //first one found
	/*Counting how many were pressed*/
	for (int i = 0; i < lista.size(); i++) {
		if (nodes[i].get_state() == buttonStates::Pressed) {
			cantOfSelected++;
			if (first) {
				nodeID1 = i;
				first = false; //not first anymore
			}
			else if (!first)
				nodeID2 = i;
		}
	}
	if (cantOfSelected != 2)
		return false;
	//Quantity was ok
	list <Nodo*>::iterator it = lista.begin();
	for (int i = 0; i < lista.size(); i++) {
		if ((*it)->get_visualID() == nodeID1)
			origen = (*it);
		else if ((*it)->get_visualID() == nodeID2)
			dest = (*it);
	}
}

void drawConnections(list <Nodo*> lista, button* nodes) {
	list <Nodo*>::iterator it = lista.begin();
	list <Nodo*>::iterator it2;
	for (int i = 0; i < lista.size(); i++) {
		list <Nodo*> connected = (*it)->get_connections();
		it2 = connected.begin();
		for (int j = 0; j < connected.size(); j++) {
			int numberOfConnected = (*it2)->get_visualID();
			drawLine(nodes[i].get_posX(), nodes[i].get_posY(), nodes[numberOfConnected].get_posX(), nodes[numberOfConnected].get_posY());
			it2++;
		}
		it++;
	}
}

#else

int main(/*int arc, char* argv[]*/ void)
{
	srand(time(0));
	//Recibo por linea de comando con cuantos nodos trabajo
	int fullNodes = 15;/*(int) argv[1];*/
	int miners = 5;/*(int)argv[2];*/
	int spvs = 5;/*(int)argv[3];*/
	//controlo primero que metan los parametros como se debe
	if (fullNodes >= 5 && fullNodes <= 20 && miners <= fullNodes && miners >= 5 && miners <= 20 && spvs >= 5 && spvs <= 20)
	{
		red my_network(fullNodes, miners, spvs);	//armo la red con todos los modos full puros y mineros
		cout << "Network size: " << my_network.get_network_size() << endl;
		my_network.list_nodes();
		my_network.connect_nodes();					//conecto todos los nodos full, con al menos dos vecinos por nodo
		my_network.list_nodes();
		GraphL ad_matrix(fullNodes);				//armo mi matriz de adyacencia con n nodos full
		ad_matrix.set_connections(my_network);		//Indico qué nodos están conectados entre sí
		dfs(&ad_matrix, 0);							//recorro toda la matriz a partir del primer nodo
		
		while (!ad_matrix.is_conex())				//Busca los nodos desconectados y genera nuevas conexiones hasta que sea conexo
		{
			int desertor = ad_matrix.give_me_an_autist();
			my_network.fix_conection(desertor);
			dfs(&ad_matrix, 0);
		}
		my_network.add_filters();					//agrego los spv, cada uno se attachea a dos full antes de unirse

		
		system("pause");

		char c = getchar();
		simulation sim;
		sim.dispatch('i', my_network);
		while (1)
		{
			c = getchar();
			if (c != 'q' || c != 'Q')
				sim.dispatch(c, my_network);
			else
				break;

		}

		
		return 0;
	}
	
}

#endif

