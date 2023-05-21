#include "MerkleTree.h"

MerkleTree::MerkleTree(int cantTx)
{
	int cantNodos = 2 * cantTx - 1;

	for (int i = 0; i < cantNodos; i++)
		nodes.push_back(Binodo_t());
}


MerkleTree::~MerkleTree()
{
}

Binodo_t*
MerkleTree::getRootPos()
{
	if (!nodes.empty())
	{
		return &nodes.front(); //Direccion al primero
	}
	else
	{
		return NULL;
	}
}

Binodo_t*
MerkleTree::createBranches(list<Binodo_t>::iterator& it, size_t height)
{
	if (height == 1) //Nivel hoja
	{
		it->left = NULL;
		it->right = NULL;
	}
	else //Otro Nivel...
	{
		list<Binodo_t>::iterator it_copy = it; //Guardo copia para hacer los punteros
		//Puntero a hijo IZQUIERDO
		it_copy->left = createBranches(++it, height - 1); //Reservo pos. de la lista para el hijo
		//Puntero a hijo DERECHO
		it_copy->right = createBranches(++it, height - 1); //Reservo pos. de la lista para el hijo
	}

	return &(*it); //Siempre devolvemos la posicion del nodo (no todo lo que brilla es oro);
}

void 
MerkleTree::fillTreeIDs(Binodo_t* nodo,list<Transaction>::iterator& begin, pGenID GenID)
{
	if (nodo->left == NULL || nodo->right == NULL) //Es una hoja
	{
		nodo->myID = to_string(GenID((const unsigned char*)begin->getTxID()->c_str()));
		++begin; //Corro el iterador porque ya use la transaccion
	}
	else //Es un nodo
	{
		fillTreeIDs(nodo->left, begin, GenID);//Cargo el nodo IZQUIERDO
		fillTreeIDs(nodo->right, begin, GenID);//Cargo el nodo DERECHO
	//CONCATENAMOS EL IZQUIERDO CON EL DERECHO, MUY IMPORTANTE!!!!
		nodo->myID = nodo->left->myID + nodo->right->myID;
		nodo->myID = to_string(GenID((const unsigned char*)nodo->myID.c_str())); //Genero mi ID
	}
}

bool 
MerkleTree::searchPath(list<step_t>* path, Binodo_t* nodo, ID& wally)
{
	//PRIMEROS DOS CASOS SON UNA HOJA!!!!
	if (nodo->myID == wally) //Encontre a Wally
	{
		return true;
	}
	else if (nodo->left == NULL || nodo->right == NULL) //Es OTRA hoja
	{
		return false;
	}
	else //Es un nodo
	{
		if (searchPath(path, nodo->left, wally)) //Busco en la IZQUIERDA
		{
			step_t brother;
			brother.direction = dir::RIGHT; //Guardo al hermano
			brother.theID = nodo->right->myID;
			path->push_back(brother);
			return true; //Debo notifica que este es el camino CORRECTO
		}
		else if (searchPath(path, nodo->right, wally)) //Busco en la DERECHA
		{
			step_t brother;
			brother.direction = dir::LEFT; //Guardo al hermano
			brother.theID = nodo->left->myID;
			path->push_back(brother);
			return true; //Debo notifica que este es el camino CORRECTO
		}
		else
			return false; //No encontre nada de nada
	}
}

void MerkleTree::insertLeftSon(list<Binodo_t>::iterator it, pGenID GenID, ID myID)
{
	Binodo_t dummy;
	dummy.left = NULL; dummy.right = NULL;
	dummy.myID = to_string(GenID((const unsigned char*)myID.c_str())); //Cargo su ID
	nodes.push_back(dummy);
	it->left = &nodes.back();
}

void MerkleTree::insertRightSon(list<Binodo_t>::iterator it, pGenID GenID, ID myID)
{
	Binodo_t dummy;
	dummy.left = NULL; dummy.right = NULL;
	dummy.myID = to_string(GenID((const unsigned char*)myID.c_str())); //Cargo su ID
	nodes.push_back(dummy);
	it->right = &nodes.back();
}