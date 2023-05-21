#pragma once
#include "Bloque.h"



class EDAmerkleblocks
{
public:
	EDAmerkleblocks();
	~EDAmerkleblocks();


	void fillJson(json &j);
	void fillFromJson(json &j);

	/*Setters*/
	void setCantTx(int cant) { this->cantTX = cant; }
	void setMerkPthLen(int len) { this->merklePathLen = len; }
	void attachMerklePathID(ID id) { this->merklePath.push_back(id); }
	void attachTx(string blockid, Transaction tx) { this->Tx.insert(pair<string, Transaction>(blockid, tx)); }
	/*Getters*/
	int getCantTx(void) { return this->cantTX; }
	int getMerkPthLen(void) { return this->merklePathLen; }
	list <ID> * getMerklePath(void) { return &(this->merklePath); }
	map <string, Transaction> * getTx(void) { return &(this->Tx); }
private:
	int cantTX;
	map <string, Transaction> Tx;	
	int merklePathLen;
	list<ID> merklePath;
	
};

