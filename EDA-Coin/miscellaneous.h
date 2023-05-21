#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Bloque.h"
#include "Transaction.h"
#include "MerkleTree.h"
#include <chrono>

using namespace std;
using namespace chrono;
using namespace nlohmann;

#define MINUTE 60000

string generateROOT(list<Transaction>::iterator begin, list<Transaction>::size_type size);
/*
Generate ID

*/
unsigned long generateID(const unsigned char *str);

/*
generateBlocks
Lee de un json la informacion de los bloques que contenga y los
manda a una lista de bloques.
Un ejemplo de bloque que lee es:
{
	"BlockID":"A",
	"Merkle Root":"??",
	"Txs Count": "4",
	"Txs":[
	  {
		"TxID":"1",
		"input":[
		  {"BlockID":"A",
		  "TxID":"aa"}
		],
		"output":[
		  {"publicKey":"nodo1",
		  "EDACoins":"15"}
		  ]
	  },
	  ...
	  ]
  }

-Recibe: una referencia de Json donde buscar los bloques
		 una referencia a una lista de bloques
-devuelve: en la lista pasada por referencia los bloques
*/
void generateBlocks(json& j, list <Bloque> & listBlocks);

/*
extractJson
devuelve en un json el contenido del path pasado como argumento
recibe referencia a json y string con el path.
*/
void extractJson(json& j, string path);


void headerToJson(json & j, Header & header);
void jsonToHeader(json & j, Header & header);

string my_genID (void);
string my_pkey(void);


void start_counting(std::chrono::time_point<std::chrono::system_clock> start)
{
	start = std::chrono::system_clock::now();
}
bool are_they_late(std::chrono::time_point<std::chrono::system_clock> start)
{
	std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
	if (((current - start) / 60000) < (std::chrono::milliseconds(MINUTE)))
		return false;
	else
		return true;
}