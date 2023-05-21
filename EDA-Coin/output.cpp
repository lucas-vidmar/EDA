#include "output.h"




output::~output()
{
}

void output::fillJson(json & j)
{
	j["payment"] = this->getPayment();
	j["publicID"] = this->getPublicID();
}

void output::fillFromJson(json & j)
{
	this->setPublicID(j["publicID"]);
	this->setPayment(j["payment"]);
}