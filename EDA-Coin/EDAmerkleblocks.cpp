#include "EDAmerkleblocks.h"



EDAmerkleblocks::EDAmerkleblocks()
{
}


EDAmerkleblocks::~EDAmerkleblocks()
{
}

void EDAmerkleblocks::fillJson(json &j)
{
	j["CantTx"] = this->getCantTx();
	j["MerklePathLen"] = this->getMerkPthLen();

	int index = 0;
	j["MerklePath"][index] = json::array();
	for (auto itID = getMerklePath()->begin(); itID != getMerklePath()->end(); itID++)
	{
		j["MerklePath"][index] = *itID;
		index++;
	}

	index = 0;
	j["TXs"][index] = json::array();
	json aux;
	for (auto itTX = getTx()->begin(); itTX != getTx()->end(); itTX++)
	{
		(*itTX).second.fillJson(aux);
		j["TXs"][index] = aux;	//relleno con las tx

		aux["ID"] = (*itTX).first;
		j["TXs"][index] = aux;  //y el nombre del bloque de la blockchain
		index++;
	}
}

void EDAmerkleblocks::fillFromJson(json &j)
{
	this->setCantTx(j["CantTx"]);
	this->setMerkPthLen(j["MerklePathLen"]);

	for (auto it : j["MerklePath"])
	{
		this->attachMerklePathID(it);
	}

	for (auto it : j["TXs"])
	{
		Transaction tx;
		tx.fillFromJson(it);
		attachTx(it["ID"], tx);
	}

}