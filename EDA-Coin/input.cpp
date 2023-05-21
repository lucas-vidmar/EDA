#include "input.h"



input::~input()
{
}

void input::fillJson(json & j)
{
	j["txID"] = this->getTxID();
	j["bloqueID"] = this->getBlockID();
}

void input::fillFromJson(json & j)
{
	this->setBlockID(j["bloqueID"]);
	this->setTxID(j["txID"]);
}