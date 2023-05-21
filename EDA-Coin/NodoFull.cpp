#include "NodoFull.h"
#include "SPV.h"
#include "minero.h"

NodoFull::NodoFull()
{
	my_type = nodo_type::FULL_SERVICE;
	tx_received = false;
	private_key = generatePrivKey();
}

NodoFull::~NodoFull()
{
}

void NodoFull::attach(Nodo* node)
{
	this->Nodo::attach(node);

	if (node->getType() == nodo_type::SPV)
	{
		this->filters.push_back(node); //Filtro agregado
	}
}

void NodoFull::detach(Nodo* node)
{
	this->Nodo::detach(node);

	for (auto& it : this->filters)
	{
		if (it == node)
			this->filters.remove(it);
	}

}


void NodoFull::receiveBlock(Bloque block, int key2solve, int challenge_lenght)
{ 
	bool control = true;
	if (!(check_challenge(key2solve, block.getHead(), challenge_lenght)))				//reviso que cumpla el challenge
		control = false;
	if (!(check_pbh(block.get_pbh())))													//reviso que el bloque tenga el hash del bloque previo
		control = false;
	if (control)	//Reviso que realmente cumpla el challenge
	{
		if (!did_u_get_it())		//Revisa si ya recibió el bloque para no repetirlo
		{
			//Creamos y llenamos el arbol del bloque
			MerkleTree biTree(block.getCantTx());
			list<Binodo_t>::iterator scapeGoatTree = biTree.nodeBegin();			//Para safar de L value
			list<Transaction>::iterator scapeGoatTx = block.getTxList()->begin();	//		"

			biTree.createBranches(scapeGoatTree, biTree.calculateHeight(block.getCantTx()));
			biTree.fillTreeIDs(biTree.getRootPos(), scapeGoatTx, generateID);

			MerkleWoods.insert(std::pair<ID, MerkleTree>(block.getBlockID(), biTree));	//guardamos ID con MerkleTree

			BlockChain.push_back(block);//Metemos el bloque con el merkleroot ya completo en la BlockChain.
			got_the_block();
		}
		list<Nodo*>::iterator it = connections.begin();		//Luego lo manda a las conexiones
		for (size_t i = 0; i < connections.size(); i++)
		{
			if ((*it)->getType() == nodo_type::FULL_SERVICE)
			{
				NodoFull* my_node = (NodoFull*)*it;
				my_node->receiveBlock(block, key2solve, challenge_lenght);
			}
			else if ((*it)->getType() == nodo_type::MINER)
			{
				miner* my_node = (miner*)*it;
				my_node->receiveBlock(block, key2solve, challenge_lenght);
				my_node->prepare_next_block();
			}
			it++;
		}
	}
}	

json NodoFull::NextBlock(ID search)
{
	list<Bloque>::reverse_iterator r_it = BlockChain.rbegin();

	while (r_it->getBlockID() != search)
		++r_it; //"anterior"

	--r_it; //Quiero el "siguiente"

	json j;
	r_it->JsonHead(j);
	return j;

}