#pragma once

#include "Graph.h"
#include "LList.h"
#include "red.h"

#define GRAPH_UNVISITED 0
#define GRAPH_VISITED 1 



class GraphLEdge {
private:
	int v; // Almacena el índice a vértice
	int w; // Almacena el peso
public:
	GraphLEdge(int v = 0, int w = 0) {
		this->v = v;
		this->w = w;
	}
	int getVertex() {
		return v;
	}
	int getWeight() {
		return w;
	}
};

// Implementación con lista de adyacencia
class GraphL : public Graph {
private:
	int n, e; // Almacena el número de vértices y ejes
	LList<GraphLEdge> ** vLists; // Almacena las listas de adyacencia
	int * mark; // Almacena las marcas

public:
	GraphL(int n) {
		this->n = n;
		e = 0;
		mark = new int[n]; // Inicializa las marcas
		for (int i = 0; i < n; i++)
			mark[i] = GRAPH_UNVISITED;
		vLists = new LList<GraphLEdge> *[n]; // Inicializa las listas de adyacencia
		for (int i = 0; i < n; i++)
			vLists[i] = new LList<GraphLEdge>();
	}
	~GraphL() {
		for (int i = 0; i < n; i++)
			delete vLists[i];
		delete[] vLists;
		delete[] mark;
	}
	int getN() {
		return n;
	}
	int getE() {
		return e;
	}
	int getFirst(int v) {
		if (vLists[v]->getLength() == 0)
			return n; // Retorna n si no se encuentra
		vLists[v]->moveToStart();
		GraphLEdge edge = vLists[v]->getValue();
		return edge.getVertex();
	}
	int getNext(int v, int v2) {
		if (isEdge(v, v2)) {
			if ((vLists[v]->getCurrPos() + 1) < vLists[v]->getLength()) {
				vLists[v]->next();
				GraphLEdge edge = vLists[v]->getValue();
				return edge.getVertex();
			}
		}
		return n; // Retorna n si no se encuentra
	}

	void setEdge(int v, int v2, int w = 1) {
		if (w <= 0)
			return;
		GraphLEdge edge(v2, w);
		if (isEdge(v, v2)) { // El eje ya existe
			vLists[v]->remove();
			vLists[v]->insert(edge);
		}
		else {
			for (vLists[v]->moveToStart();
				vLists[v]->getCurrPos() < vLists[v]->getLength();
				vLists[v]->next()) {
				GraphLEdge temp = vLists[v]->getValue();
				if (temp.getVertex() > v2)
					break;
			}
			vLists[v]->insert(edge);
			e++;
		}
	}
	void removeEdge(int v, int v2) {
		if (isEdge(v, v2)) {
			vLists[v]->remove();
			e--;
		}
	}
	bool isEdge(int v, int v2) {
		for (vLists[v]->moveToStart();
			vLists[v]->getCurrPos() < vLists[v]->getLength();
			vLists[v]->next()) {
			GraphLEdge edge = vLists[v]->getValue();
			if (edge.getVertex() == v2)
				return true;
		}
		return false;
	}
	int getWeight(int v, int v2) {
		if (isEdge(v, v2)) {
			GraphLEdge edge = vLists[v]->getValue();
			return edge.getWeight();
		}
		else
			return 0;
	}
	int getMark(int v) {
		return mark[v];
	}
	void setMark(int v, int value) {
		mark[v] = value;
	}

	bool is_conex(void) {

		int connected = 0;
		for (int i = 0; i < getN(); i++)
		{
			if (getMark(i) == GRAPH_VISITED)
			{
				connected++;
			}
		}
		if (connected == getN())
		{
			return true;
		}
		else
			return false;
	}
	int give_me_an_autist(void) {
		int i = 0;
		while (getMark(i) == GRAPH_VISITED && i<getN())
		{
			i++;
		}
		return i;
	}
	void set_connections(red my_network) {
		list <Nodo*>::iterator it = my_network.get_network().begin();
		size_t v2;
		for (size_t v = 0; v < (my_network.get_network_size()); v++)
		{
			list <Nodo*>::iterator neighbour = (*it)->get_friends_list().begin();
			for (size_t i = 0; i < (*it)->get_friends_list().size(); i++)
			{
				v2 = my_network.where_is_he(*neighbour);
				setEdge(v, v2);
				neighbour++;
			}
			it++;
		}
	}
};

void dfs(Graph * graph, int v);