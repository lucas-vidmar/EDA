#pragma once
#include "model.h"
#include "EDAmerkleblocks.h"

using namespace std;

enum class nodo_type {FULL_SERVICE, SPV, MINER};

class Nodo //: public subject
{
public:
	Nodo();
	~Nodo();
	nodo_type getType(void) { return this->my_type; }
	virtual void attach(Nodo* node);
	virtual void detach(Nodo* node);

	virtual void createTX(int coins, Nodo* destiny) {
		int mycoins = 0;
		size_t how_many_i_need = 0;
		list <Transaction>::iterator it = utxoList.begin();
		while (mycoins < coins	&& it != utxoList.end()) {
			how_many_i_need++;
			mycoins += (*it).get_coins();
			it++;
		}
		if (mycoins < coins)
			cout << "No tienes suficientes monedas" << endl;
		else
		{
			it = utxoList.begin();
			Transaction tx("new");
			for (size_t i = 0; i < how_many_i_need; i++)				//agrego a la tx todas las txs que uso
			{
				list<input>::iterator ite = (*it).getIn()->begin();
				for (size_t in = 0; in < (*it).getIn()->size(); in++)
				{
					(*ite).used(private_key);	//firmo la tx
					tx.attachin((*ite));
					ite++;
				}
				it++;
			}
			output o(private_key, coins);
			tx.attachout(o);
			tx.setTxID(tx.tx2str());		//hasheo la tx para crear su verdadero ID
			destiny->addTX(tx);
		}
	}
	virtual void addTX(Transaction tx) = 0;
	size_t how_many_friends(void) { return connections.size(); }

	const char* print_type(void) {
		const char * c = "sin tipo";
		if (my_type == nodo_type::FULL_SERVICE)
		{
			c = "full puro";
		}
		else if (my_type == nodo_type::MINER)
		{
			c = "minero";
		}
		else if (my_type == nodo_type::SPV)
		{
			c = "spv";
		}
		cout << c << endl;
		return c;
	}
	/*list<Nodo*>::iterator get_friends_list (void){ 
		list<Nodo*>::iterator it = conections.begin();
		return it;
	}*/
	list<Nodo*> get_friends_list(void) { return connections; }
	void got_the_block(void) { tx_received = true; }
	void back_2_work(void) { tx_received = false; }
	bool did_u_get_it(void) { return tx_received; }
	bool check_challenge(int key2solve, Header head, int challenge_lenght)
	{
		head.nonce = key2solve;
		string str = myhash(head2str(head));
		int num = 0;
		size_t i = 0;
		while (i < str.length() && str[i] == 0)
		{
			num++;
			i++;
		}
		if (num == challenge_lenght)
			return true;
		else
			return false;
	}

	/*Setter*/
	void set_visualID(int id) { visualID = id; }

	/*Getter*/
	list <Nodo*> get_connections(void) { return connections; }
	int get_visualID(void) { return visualID; }
	int get_vault(list <input>* inputs) {			//revisa en la lista de utxos para decir cuantas monedas traen los inputs de una tx

		int coins = 0;
		list <input>::iterator in = (*inputs).begin();
		for (size_t i = 0; i < (*inputs).size(); i++)
		{
			list <Transaction>::iterator it = utxoList.begin();
			for (size_t i = 0; i < utxoList.size(); i++)
			{
				if (*((*it).getTxID()) == (*in).getTxID())
					coins += (*it).get_coins();
				it++;
			}
			in++;
		}
		return coins;
	}

protected:
	int visualID;
	nodo_type my_type;
	string publicID;
	list<Nodo*> connections;

	/* FILTERLOAD

	si le preguntas a un nodo FULL
	- devuelve nullptr (no tiene filtro)
	Si le preguntas a un nodo spv
	- devuelve la direccion de si mismo
	*/
	list <Transaction> utxoList;
	Nodo* filterload(Nodo* node);
	bool tx_received;
	ECDSA<ECP, SHA256>::PrivateKey private_key;
	
};

