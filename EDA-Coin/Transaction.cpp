#include "Transaction.h"





Transaction::~Transaction()
{
}

void Transaction::fillJson(json & j)
{
	j["txID"] = *this->getTxID();

	int i = 0;
	j["inputs"][i] = json::array();
	json aux;
	for (auto itIn = getIn()->begin(); itIn != getIn()->end(); itIn++)
	{
		(*itIn).fillJson(aux);
		j["inputs"][i] = aux;
		i++;
	}

	aux.clear();
	i = 0;
	j["outputs"][i] = json::array();
	for (auto itOut = getOut()->begin(); itOut != getOut()->end(); itOut++)
	{
		(*itOut).fillJson(aux);
		j["outputs"][i] = aux;
		i++;
	}
}


void Transaction::fillFromJson(json & j)
{
	this->setTxID(j["txID"]);

	input in;
	for (auto it : j["inputs"])
	{
		in.fillFromJson(it);
		this->attachin(in);
	}

	output out;
	for (auto it : j["outputs"])
	{
		out.fillFromJson(it);
		this->attachout(out);
	}

}