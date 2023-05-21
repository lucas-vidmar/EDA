#include "Bloque.h"

Bloque::Bloque()
{
	this->cantTX = 0;	//comienza sin transacciones
};

Bloque::~Bloque()
{
}
/*
void
Bloque::draw(float width, float height, int numberOfBlocks, int actualBlock,ALLEGRO_FONT* font)
{
	ALLEGRO_COLOR color_red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR color_black = al_map_rgb(0, 0, 0);
	std::string str = std::to_string(cantTX);

	al_draw_filled_rectangle(width / 2 - 200 / 2, (height / numberOfBlocks) * actualBlock + 30 , width / 2 + 200 / 2, (height / numberOfBlocks) * actualBlock + 30 + (height /(numberOfBlocks+5)) , color_red);
	al_draw_textf(font, color_black, width / 2, (height / numberOfBlocks) * actualBlock + 70, ALLEGRO_ALIGN_CENTER, str.c_str());
	al_draw_textf(font, color_black, width / 2, (height / numberOfBlocks) * actualBlock + 40, ALLEGRO_ALIGN_CENTER, (headerBlock.blockID).c_str());

} */

void Bloque::attachTx(Transaction newTx)
{
	this->txList.push_back(newTx);
	this->incCantTx();
}

void Bloque::setMerkleRoot(ID MerkleRoot)
{
	this->headerBlock.merkleRoot = MerkleRoot;
}

void Bloque::setBlockID(ID BlockID)
{
	this->headerBlock.blockID = BlockID;
}

void Bloque::fillJson(json & j)
{
	j["blockID"] = this->getBlockID();
	j["merkleRoot"] = this->getMerkleRoot();
	j["cantTX"] = this->getCantTx();

	int index = 0;
	j["TXs"][index] = json::array();
	json aux;
	for (auto itTx = getTxList()->begin(); itTx != getTxList()->end(); itTx++)
	{
		(*itTx).fillJson(aux);
		j["TXs"][index] = aux;
		index++;
	}
}

void Bloque::fillFromJson(json & j)
{
	setBlockID(j["blockID"]);
	setMerkleRoot(j["merkleRoot"]);

	for (auto it : j["TXs"])
	{
		Transaction tx;
		tx.fillFromJson(it);
		this->attachTx(tx);
	}
}