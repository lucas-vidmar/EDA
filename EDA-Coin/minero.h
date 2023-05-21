#pragma once

#include "NodoFull.h"
#include "miscellaneous.h"

class miner : public NodoFull {

public:
	miner() { 
		my_type = nodo_type::MINER; 
		tx_received = false;
		try_again();
		private_key = generatePrivKey();
	}
	void addTX(Transaction tx) { 
		if (!is_double_spent(tx))
		{
			nextBlock.attachTx(tx);
		}
	}
	void mining(int challenge_lenght, int key2solve) {
		got_the_block();
		nextBlock.setBlockID(nextBlock.block2string());		//hace un hash para crear su ID
		receiveBlock(nextBlock, key2solve, challenge_lenght);
		list<Nodo*>::iterator it = connections.begin();
		
		for (size_t i = 0; i < connections.size(); i++)
		{
			(*it)->got_the_block();
			if ((*it)->getType() == nodo_type::FULL_SERVICE)
			{
				NodoFull* my_node = (NodoFull*)*it;
				my_node->receiveBlock(nextBlock, key2solve, challenge_lenght);
			}
			else if ((*it)->getType() == nodo_type::MINER)
			{
				miner* my_node = (miner*)*it;
				my_node->receiveBlock(nextBlock, key2solve, challenge_lenght);
			}
			it++;
		}
		
		prepare_next_block();
	}
	bool is_double_spent(Transaction tx) {
		return false;
	}
	
	void prepare_next_block(void) {
		Bloque block;
		nextBlock = block;
		list <Bloque>::iterator it = BlockChain.end();
		nextBlock.set_pbh(myhash((*it).getBlockID()));
		Transaction tx ("new");
		output o(private_key, 50);
		tx.attachout(o);
		tx.setTxID(tx.tx2str());
		nextBlock.attachTx(tx);
		try_again();
		back_2_work();
	}
	void try_again(void)
	{
		my_try = rand() % sizeof(int);
	}
	bool challenge(int n)
	{
		nextBlock.set_nonce(my_try);
		string str = myhash(head2str(nextBlock.getHead()));
		int num = 0;
		size_t i = 0;
		while (i < str.length() && str[i] == 0)
		{
			num++;
			i++;
		}
		my_try++;
		if (num == n)
		{
			set_solution(my_try - 1);
			return true;
		}
		else
			return false;
	}
	void set_solution(int n) { ket2solve = n; }
private:
	std::list<Nodo*> filters;
	std::list <Bloque> BlockChain;
	std::map <ID, MerkleTree> MerkleWoods; //No estoy seguro de que deban ser ambos int
	list <Transaction> utxoList;
	Bloque nextBlock;
	int my_try;
	int ket2solve;
};