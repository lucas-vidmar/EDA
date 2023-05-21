#pragma once
#include <string>
#include <list>
#include <cstdbool>
#include <math.h>
#include "Transaction.h"

using namespace std;
typedef unsigned long (*pGenID) (const unsigned char *);
enum class dir {LEFT,RIGHT};
typedef string ID;

typedef struct Binodo
{
	Binodo* left;
	Binodo* right;
	ID myID;
}Binodo_t;

typedef struct{ dir direction; ID theID; }step_t;

class MerkleTree
{
public:
	MerkleTree(int cantTx);
	~MerkleTree();
	Binodo_t* getRootPos(); //Devuelve un puntero al ROOT
	ID& getRootID() { &this->nodes.front().myID; }; //Devuelve el ID del ROOT
	size_t calculateHeight(int a) { return(log2(a) + 1); };
//SEARCHPATH: carga la lista de steps si encontro la hoja. devuelve TRUE si la encontro, FLASE si no.
	bool searchPath(list<step_t>* path, Binodo_t* nodo,ID& wally);
//FILLTREEIDS: carga los IDS de todo el arbol, es muy importante pasar la lista de tx CORRECTA
	void fillTreeIDs(Binodo_t* nodo,list<Transaction>::iterator& begin, pGenID GenID);
//CREATEBRANCES: crea las conecciones del arbol binario, padres, hijos y hermanos.
	Binodo_t* createBranches(list<Binodo_t>::iterator& it,size_t height);
	list<Binodo_t>* getterListNodes(void) { return &this->nodes; };
	list<Binodo_t>::iterator nodeBegin(void) { return this->nodes.begin(); };
private:
	list<Binodo_t> nodes;
	void insertLeftSon(list<Binodo_t>::iterator it, pGenID GenID, ID myID);//No me mires...
	void insertRightSon(list<Binodo_t>::iterator it, pGenID GenID, ID myID);//No me mires...
};

/* IMPLEMENTACION: (COPIAR LITERAL)
*
*					MerkleTree Angela(CANTIDAD DE TRANSACCIONES/HOJAS);
*					createBranches(Angela.nodeBegin(),Angela.calculateHeight(IDEM ARRIBA));
*					fillTreeIDs(Angela.getRootPos(),INICIO LISTA TXs,FUNCION generateID);
*
* COMENTARIO: searchPath te crea el camino y ademas te dice si esta detro del arbol,
*				para crear el camino le mandas una lista de <step_t>.
*
* Cualquier duda preguntame, cualquier queja/critica guardatela. <3
*/