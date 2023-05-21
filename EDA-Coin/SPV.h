#pragma once
#include "Nodo.h"
#include "NodoFull.h"
#include <cstdbool>

class SPV : public Nodo {
public:
	SPV()
 	{
		my_type = nodo_type::SPV;
		tx_received = false;
		private_key = generatePrivKey();
	}
	~SPV();
	void setTrusfulFull(Nodo* Full) { this->TrusfulFull = Full; }
	/* SET FULL NODE ADDRESS
	   Esta funcion le indica a un nodo spv la direccion de un FULL node (de confianza)
	   al cual el SPV le pedira informacion.
	*/
	bool Ask4Header(void);

	void createTX(int coins, Nodo* destiny) {

		Transaction tx("new");
		output o(private_key, coins);
		tx.attachout(o);
		tx.setTxID(tx.tx2str());
		utxoList.push_back(tx);
		destiny->addTX(tx);
														
	}
	Transaction get_last_tx(void) {
		list<Transaction>::iterator it = utxoList.end();
		return *it;
	}
	void addTX(Transaction tx) {
		bool control = true;
		if (!(myhash(tx.tx2str()) == tx.getTxID))			//verifico el hash ID
			control = false;
		list <input> *inputs = tx.getIn();
		list <input>::iterator it = inputs->begin();
		
		if (!(tx.get_coins() == get_vault(tx.getIn())))		//verifico que efectivamente tenga la cantidad de monedas que esta gastando
			control = false;

		list <output>::iterator out = tx.getOut()->begin();
		it = inputs->begin();
		for (size_t i = 0; i < tx.getOut()->size(); i++)
		{
			ECDSA<ECP, SHA256>::PublicKey pub_key = (*out).getPublicID();
			string data = (*it).input2str();
			vector <byte> sign = (*it).get_my_sign();
			if (!(verifySignature(pub_key, data, sign)))	//miro que los unlocking scripts desbloqueen la utxo
				control = false;
			it++;
			out++;
		}

		if (control)
		{
			utxoList.push_back(tx);
			list<Nodo*>::iterator myit = connections.begin();
			for (size_t i = 0; i < connections.size(); i++)
			{
				(*myit)->addTX(tx);
				myit++;
			}
		}
	}
	
	void beginning(Bloque block, Transaction tx)
	{
		headerList.push_back(block.getHead());
		utxoList.push_back(tx);
	}

	
private:
	Nodo* TrusfulFull;
	list <Header> headerList;
	list <EDAmerkleblocks> merkleblocksList;
	list <Transaction> utxoList; //lista de utxo propias (mi cantidad de EDACoins)
	//list <observer&> observers;
};

