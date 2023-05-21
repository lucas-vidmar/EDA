#pragma once
#include <list>
#include "input.h"
#include "output.h"
#include "hash.h"
using namespace std;

class Transaction
{
public:
	Transaction() {}
	Transaction(string ID)
	{
		this->txID = ID;
	}
	~Transaction();

	void fillJson(json & j);
	void fillFromJson(json & j);
	string tx2str(void) {
		string str;
		string myin;
		list <input>::iterator in = inputs.begin();
		for (size_t i = 0; i < inputs.size(); i++)
		{
			myin = myin + (*in).input2str();
			in++;
		}
		string myout;
		list <output>::iterator out = outputs.begin();
		for (size_t i = 0; i < inputs.size(); i++)
		{
			myout = myout + (*out).output2string();
			out++;
		}
		str = txID + myin + myout;
		return str;
	}

	/*Setters*/
	void attachin(input in)
	{
		inputs.push_back(in);
	}
	void attachout(output out)
	{
		outputs.push_back(out);
	}
	void setTxID(string txID) { this->txID = txID; }

	/*Getters*/
	list <input> * getIn() { return &this->inputs; }
	list <output> * getOut() { return &this->outputs; }
	string* getTxID() { return &txID; }
	int get_coins(void) {
		int coins = 0;
		list <output>::iterator out = outputs.begin();
		for (size_t i = 0; i < outputs.size(); i++)
		{
			coins += (*out).getPayment();
			out++;
		}
		return coins;
	}
	
	
private:
	string txID;
	list <input> inputs;	
	list <output> outputs;
};

