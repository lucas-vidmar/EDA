#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include "Transaction.h"
#include "Drawable.h"

using namespace std;

typedef string ID;

typedef struct
{
	/*creo que el merkleroot seria algo asi*/
	ID merkleRoot;
	ID blockID;
	int nonce;
}Header;

class Bloque //: public Drawable
{
public:
	Bloque();
	~Bloque();

	//virtual void draw(float width, float height, int numberOfBlocks, int actualBlock,  ALLEGRO_FONT*);

	void JsonHead(json& j)
	{
		j["blockID"] = this->getBlockID();
		j["merkleRoot"] = this->getMerkleRoot();
	}

	void fillJson(json & j);
	void fillFromJson(json & j);

	/*Setters*/
	void attachTx(Transaction newTx);
	void setMerkleRoot(ID MerkleRoot);
	void setBlockID(ID BlockID);
	void set_nonce(int n) { headerBlock.nonce = n; }
	void set_pbh(string pID) { prev_block_hash = pID; }

	/*Getters*/
	ID getBlockID() { return this->headerBlock.blockID; }
	Header getHead() { return this->headerBlock; }
	list <Transaction> * getTxList() 
	{ 
		
		return &this->txList; 
	}
	int getCantTx(void) { return cantTX; }
	string getMerkleRoot(void) { return headerBlock.merkleRoot; }
	string get_pbh(void) { return prev_block_hash; }

	string block2string(void) {
		string str;
		str = head2str(headerBlock) + to_string(cantTX);
		string txs;
		list <Transaction>::iterator it = txList.begin();
		for (size_t i = 0; i < txList.size(); i++)
		{
			str = str + (*it).tx2str();
			it++;
		}
		str = str + privkey2string(publicKey);
	}

private:
	/*----  HEADER ----*/
	Header headerBlock;
	int cantTX;			//cantidad de transacciones en el bloque
	list <Transaction> txList;	//arreglo de transacciones
	ECDSA<ECP, SHA256>::PublicKey publicKey;
	
	//metodos privado
	void incCantTx() { cantTX++; }
	string prev_block_hash;
};

string head2str(Header head)
{
	string str = head.blockID + head.merkleRoot + to_string(head.nonce);
	return str;

}