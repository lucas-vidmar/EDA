#include "Nodo.h"



Nodo::Nodo()
{
}


Nodo::~Nodo()
{
}

void Nodo::attach(Nodo* node)	//el nodo full le pregunta al nodo si tiene algun filtro
{
	this->conections.push_back(node);
}

void Nodo::detach(Nodo* node)	//posiblemente haya que reemplazar lo de abajo con un switch
{
	for (auto& it : this->conections)
	{
		if (it == node)
			this->conections.remove(it);
	}
}
/* FILTERLOAD

	si le preguntas a un nodo FULL
	- devuelve nullptr (no tiene filtro)
	Si le preguntas a un nodo spv
	- devuelve la direccion de si mismo
*/
Nodo* Nodo::filterload(Nodo* node)
{
	switch (node->my_type)	//lo hice con un switch por la simplicidad de agregar mas tipos de nodos
	{
		case nodo_type::FULL_SERVICE: return NULL;
		case nodo_type::SPV: return node;
		default:	return NULL;
	}
}