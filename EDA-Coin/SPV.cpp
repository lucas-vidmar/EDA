#include "SPV.h"
#include "NodoFull.h"



SPV::~SPV()
{
}

bool
SPV::Ask4Header(void)
{
	bool found = false;
	list<Nodo*>::iterator it = conections.begin();
	while ((it != conections.end()) && found != true)
	{
		if ((*it)->getType() == nodo_type::FULL_SERVICE)
		{
			found = true; //Lo encontramos
		}
		else
		{
			++it; //pruebo con el siguiente
		}
	}

	if (found == true)
	{
		NodoFull* pFull = (NodoFull*)*it;
		json j = pFull->NextBlock(headerList.back().blockID); //Proximo Header
		Header newHead;
		newHead.blockID = j["blockID"].dump();
		newHead.merkleRoot = j["merkleRoot"].dump();

		headerList.push_back(newHead); //Lo cargamos a la lista
	}

	return found; //PARA QUE COMPILE
}