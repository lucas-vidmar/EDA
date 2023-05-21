#pragma once
#include "Nodo.h"
#include "SPV.h"
#include "Bloque.h"
#include <map>
#include "MerkleTree.h"
#include "miscellaneous.h"
#include <nlohmann/json.hpp>
using namespace nlohmann;

class NodoFull: public Nodo
{
public:
	NodoFull();
	~NodoFull();
	virtual void attach(Nodo* node);
	virtual void detach(Nodo* node);
	json NextBlock(ID search);
	void receiveBlock(Bloque Block, int key2solve, int challenge_lenght);//el bloque llega sin el merkleroot
	Bloque get_last_block(void) {
		std::list <Bloque>::iterator it = BlockChain.end();
		return *it;
	}

	void addTX(Transaction tx) {
		bool control = true;
		if (!(myhash(tx.tx2str()) == tx.getTxID))			//verifico el hash ID
			control = false;
		list <input> *inputs = tx.getIn();
		list <input>::iterator it = inputs->begin();
		for (size_t i = 0; i < inputs->size(); i++)
		{
			if (!(is_it_in_the_list((*it).getTxID())))		//verifico que las IDs de los inputs se encuentren en la utxoList
				control = false;
			it++;
		}
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
	bool is_it_in_the_list(string myID)
	{
		bool is_there = false;
		list <Transaction>::iterator it = utxoList.begin();
		for (size_t i = 0; i < utxoList.size(); i++)
		{
			if (*((*it).getTxID()) == myID)
				is_there = true;
			it++;
		}
		return is_there;
	}
	bool check_pbh(string pbh)
	{
		list <Bloque>::iterator it = BlockChain.end();
		if (myhash((*it).getBlockID()) == myhash(pbh))
			return true;
		else
			return false;
	}
	void beginning(Bloque block, Transaction tx)
	{
		BlockChain.push_back(block);
		utxoList.push_back(tx);
	}
	
private:

	//Me parece mas comodo usar stack teniendo en cuenta
	//para lo que se va a usar. (PARATE DE MANOS)
	std::list<Nodo*> filters;
	std::list <Bloque> BlockChain;
	std::map <ID, MerkleTree> MerkleWoods; //No estoy seguro de que deban ser ambos int
	//list <observer&> observers;
	list <Transaction> utxoList;
};

