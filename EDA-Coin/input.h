#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "hash.h"
using namespace std;
using namespace nlohmann;

class input
{
public:
	input() {}
	input(string blockID, string txID)
	{
		this->bloqueID = blockID;
		this->txID = txID;
	};
	~input();


	void fillJson(json & j);
	void fillFromJson(json & j);
	string input2str(void) {
		string str = bloqueID + txID;
		return str;
	}

	/*Getters*/
	string getBlockID(void) { return this->bloqueID; }
	string getTxID(void) { return this->txID; }
	vector<byte> get_my_sign(void) { return signature; }
	/*Setters*/
	void setBlockID(string blockID) { this->bloqueID = blockID; }
	void setTxID(string txID) { this->txID = txID; }
	void used(ECDSA<ECP, SHA256>::PrivateKey private_key)
	{
		string str = bloqueID + txID;
		signature = getSignature(private_key, str);
	}
	string input2string(void) {
		string str;
		str = bloqueID + txID;
		return str;
	}
private:
	string bloqueID;	
	string txID;	//ID de transaccion que corresponde a la UTXO
	vector<byte> signature;
};

