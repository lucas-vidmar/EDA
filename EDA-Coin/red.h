#pragma once

#include "NodoFull.h"
#include "SPV.h"
#include "minero.h"

class red {

public:
	red(int fullNum, int minersNum, int spvsNum) {
		
		challenge_lenght = rand() % 3 + 1;		//inicialmente es un valor de entre 1 y 3 digitos
		fullNodes = fullNum;
		miners = minersNum;
		spvs = spvsNum;
		for (int i = 0; i < (fullNum-minersNum); i++) //creating FullNodes
		{
			NodoFull* node = new NodoFull;
			/*if (node.getType() == nodo_type::FULL_SERVICE)
			{
				cout << "es full!" << endl;
			}*/
			network.push_back(node);
			/*list <Nodo*>::iterator it = network.end();
			if ((*it)->getType() == nodo_type::FULL_SERVICE)
			{
				cout << "es full!" << endl;
			}
			else
				cout << "what happened?" << endl;*/
		}
		for (int i = 0; i < minersNum; i++) //Creating Miners
		{
			miner* node2 = new miner;
			network.push_back(node2);

		}
		for (int i = 0; i < spvsNum; i++) //creating spvs
		{
			SPV* node3 = new SPV;
			Nodo* randomNode;
			do {
				randomNode = get_random_node();
			} while (randomNode == node3);
			node3->setTrusfulFull(randomNode);
			network.push_back(node3);
		}
		
	}
	~red() {
		list <Nodo*>::iterator it = network.begin();
		for (size_t i = 0; i < network.size(); i++)
		{
			delete (*it);
			it++;
		}
	}

	//Para conexiones de la red
	void connect_nodes(void) {
		list <Nodo*>::iterator current_node = network.begin();
		int random;
		for (size_t n = 0; n < network.size(); n++)	//attachea dos nodos aleatorios a cada nodo de la red (dentro de los nodos de la misma red
		{
			Nodo* node = *current_node;		
			if (node->how_many_friends() == 0)
			{
				do {
					random = (rand() % fullNodes);
				} while (random == n); //me aseguro que no sea el mismo nodo
				
				if (random != n)		//me fijo que no se attachee a si mismo
				{
					node->attach(rattach(random, network));
				}
	
			}
			else if (node->how_many_friends() == 1)
			{
				random = (rand() % fullNodes);
				if (random != n)		
				{
					node->attach(rattach(random, network));
				}
			}
			current_node++;
		}

	}
	void add_filters(void) {
		for (int i = 0; i < spvs; i++)
		{
			SPV*spv = new SPV;
			Nodo* node = get_random_node();
			spv->attach(node);
			node->attach(spv);
			node = get_random_node();
			spv->attach(node);
			node->attach(spv);
			network.push_back(spv);
		}
	}
	void fix_conection(int node_num) {
		Nodo* n = rattach(node_num, network);
		
		//Nodo* node = *i
		int new_conection;
		do {
			new_conection = (rand() % fullNodes);
		} while (new_conection == node_num); //checking new connection is not this node
		
		if (new_conection != node_num)
		{
			n->attach(rattach(new_conection, network));
		}
	}

	//Funciones auxiliares
	Nodo* rattach(int node_num, list <Nodo*> network) {	//looks for a node in the network
		list <Nodo*>::iterator it = network.begin();
		for (int i = 0; i < node_num; i++)
		{
			it++;
		}

		return *it;
	}

	void list_nodes(void) {
		list <Nodo*>::iterator it = network.begin();
		for (size_t i=0; i < network.size(); i++)
		{
			//Nodo*  node = *it;
			cout << endl << "Nodo " << i << ':' << endl;
			//cout << "Tipo: " << node->print_type() << endl;
			cout << "Tipo: " << (*it)->print_type() << endl;
			it++;
		}
	}
	bool is_valid(unsigned int origin_num, unsigned int destiny_num)
	{
		if ((origin_num < get_network_size()) && (destiny_num < get_network_size()) && (origin_num != destiny_num))	//Existen dentro de la red y son distintos
		{
			return true;
		}
		else
		{
			cout << "numero de nodo origen o destino inválidos" << endl;
			return false;
		}
	}
	void generate_tx(int origin_num, int destiny_num, int amount)
	{
		Nodo* origin = rattach(origin_num, network);
		Nodo* destiny = rattach(destiny_num, network);
		origin->createTX(amount, destiny);
	}
	void time_2_mine(int miner_num, int key2solve)
	{
		list <Nodo*>::iterator it = network.begin();
		miner* my_miner;
		Nodo* node;
		for (size_t i = 0; i < network.size(); i++)
		{
			node = *it;
			if (i == miner_num && node->getType()== nodo_type::MINER)
			{
				my_miner = (miner*)*it;
				my_miner->mining(challenge_lenght, key2solve);
				cout << "El minero " << miner_num << " ha ganado 50 EDA coins" << endl;
			}
			else if (i == miner_num && node->getType() != nodo_type::MINER)
				cout << "Error, el minero indicado no es válido" << endl;
			it++;
		}
	}
	
	//Getters
	Nodo* get_random_node(void)
	{
		int random = rand() % fullNodes;
		Nodo* n = rattach(random, network);
		return n;
	}
	int get_full_amount(void) { return fullNodes; }
	size_t get_network_size(void) { return network.size(); }
	list <Nodo*> get_network(void) { return network; }
	size_t where_is_he(Nodo* wanted)
	{
		list <Nodo*>::iterator it = network.begin();
		for (size_t i = 0; i < network.size(); i++)
		{
			if (*it == wanted)
			{
				return i;
			}
			else
				it++;
		}
	}
	void and_so_it_begins(void)		//tiene que generar el bloque genesis de la blockchain
	{
		ECDSA<ECP, SHA256>::PrivateKey private_key;
		ECDSA<ECP, SHA256>::PublicKey public_key;
		private_key = generatePrivKey();
		private_key.MakePublicKey(public_key);
		Transaction tx("new");			//La primera tx, regalo 35 EDA coins a todos los bloques
		output o(private_key, 35);
		tx.attachout(o);
		tx.setTxID(tx.tx2str());
		Bloque block;
		string str("genesis");
		block.set_pbh(myhash(str));
		block.attachTx(tx);
		block.setBlockID(myhash(block.block2string()));

		list <Nodo*>::iterator it = network.begin();
		for (size_t i = 0; i < network.size(); i++)
		{
			if ((*it)->getType() == nodo_type::SPV)
			{
				SPV * node = (SPV*)(*it);
				node->beginning(block, tx);
			}
			if ((*it)->getType() == nodo_type::FULL_SERVICE)
			{
				NodoFull * node = (NodoFull*)(*it);
				node->beginning(block, tx);
			}
			if ((*it)->getType() == nodo_type::MINER)
			{
				miner * node = (miner*)(*it);
				node->beginning(block, tx);
			}
			it++;
		}
	}

private:
	list <Nodo*> network;
	int fullNodes;
	int miners;
	int spvs;
	int challenge_lenght;
};

