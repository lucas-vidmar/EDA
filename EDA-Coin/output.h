#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "hash.h"

using namespace std;
using namespace nlohmann;


class output
{
public:
	output() {}
	output(ECDSA<ECP, SHA256>::PrivateKey &privKey, int EDAcoin)
	{
		ECDSA<ECP, SHA256>::PublicKey publicKey;
		privKey.MakePublicKey(publicKey);
		this->public_key = publicKey;
		this->payment = EDAcoin;
	}
	~output();

	void fillJson(json & j);
	void fillFromJson(json & j);

	/*setters*/
	void setPublicID(ECDSA<ECP, SHA256>::PublicKey ID) { this->public_key = ID; }
	void setPayment(int amount) { this->payment = amount; }
	/*getters*/
	ECDSA<ECP, SHA256>::PublicKey getPublicID(void) { return this->public_key; }
	int getPayment(void) { return this->payment; }
	string output2string(void) {						//esta mal!!! output tiene una publick key, no un string de ID
		string str = privkey2string(public_key) + to_string(payment);		
		return str;
	}

private:
	ECDSA<ECP, SHA256>::PublicKey public_key;	//nombre publico del nodo
	int payment;	//cantidad de EDAcoin a pagar al usuario representado por la publicID
};

