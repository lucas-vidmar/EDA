#include "miscellaneous.h"
static void createLeaf(string* my_id, MerkleTree* Angela);
static void createNode(string* my_id, MerkleTree* Angela, size_t size);

string generateROOT(list<Transaction>::iterator begin, list<Transaction>::size_type size)
{
	if (size / 2 == 1) //Legamos a las hojas, creamos los nodos de las hojas y el antecesor
	{
		//Cada += '\0' es para que generateID termine
		string tx_copy1 = *begin->getTxID();
		string tx_copy2 = *(++begin)->getTxID(); //++begin para la siguiente hoja
		//Creamos string de los ID nuevos y los concatenamos para el nuevo ID final
		tx_copy1 = to_string(generateID((const unsigned char*) tx_copy1.c_str()));
		tx_copy2 = to_string(generateID((const unsigned char*) tx_copy2.c_str()));
		tx_copy1 += tx_copy2;
		//Devolvemos el ID del nodo interno anterior a las 2 hojas
		return (to_string(generateID((const unsigned char*)tx_copy1.c_str())));
	}
	else
	{
		string ID1 = generateROOT(begin, size / 2); //Ya se creo mi nodo
		advance(begin, size / 2);
		string ID2 = generateROOT(begin, size / 2); //Ya se creo mi nodo
		ID1 += ID2; //Concateno los strings...
		return(to_string(generateID((const unsigned char*)ID1.c_str())));
	}
}

static void createLeaf(string* my_id, MerkleTree* Angela)
{
	Binodo_t leaf;
	leaf.right = NULL;
	leaf.left = NULL;
	leaf.myID = *my_id;
	Angela->getterListNodes()->push_back(leaf); //Mando la hoja
}

static void createNode(string* my_id, MerkleTree* Angela, size_t size)
{
	
	Binodo_t nodo;
	list<Binodo_t>::reverse_iterator it = Angela->getterListNodes()->rend();
	nodo.myID = *my_id;
	nodo.right = &(*it); //Puntero al de la IZQUIERDA
	for (unsigned int i = 0; i < size; ++i) ++it; //El size = cantidad de nodos a saltar
	nodo.left = &(*it); //Puntero al de la DERECHA
	Angela->getterListNodes()->push_back(nodo);
}

unsigned long generateID(const unsigned char *str)
{
	unsigned long ID = 0;
	int c;
	while (c = *str++)
		ID = c + (ID << 6) + (ID << 16) - ID;
	return ID;
}

void generateBlocks(json &j, list <Bloque> & listBlocks)
{

	for (auto it : j.items())	//para cada bloque dentro del json
	{
		Bloque block;	//genero un bloque
		//cout << j[stoi(it.key())]["BlockID"] << "\n";
		block.setBlockID(j[stoi(it.key())]["BlockID"]);	//a cada bloque guardo su ID


		for (auto itTxs : j[stoi(it.key())]["Txs"].items())	//pusheo a block cada transaction
		{
			//cout << j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["TxID"] << endl;
			Transaction tx(j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["TxID"]);

			for (auto itIn : j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["input"].items())	// para cada input
			{
				//cout << j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["input"][stoi(itIn.key())] << endl;
				input in(j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["input"][stoi(itIn.key())]["BlockID"], j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["input"][stoi(itIn.key())]["TxID"]);
				tx.attachin(in);	// attacheo input a la tx
			}

			for (auto itOut : j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["output"].items())	// para cada output
			{
				string toconvert = j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["output"][stoi(itOut.key())]["EDACoins"];
				int EDACoins = stoi(toconvert);
				output out(j[stoi(it.key())]["Txs"][stoi(itTxs.key())]["output"][stoi(itOut.key())]["publicKey"], EDACoins);
				tx.attachout(out);	// attacheo output a la tx
			}

			block.attachTx(tx);	// attacheo tx al bloqueo

		}

		/* Generamos merkleRoot  */
		list<Transaction>::iterator it = block.getTxList()->begin();
		block.setMerkleRoot(generateROOT(it, block.getCantTx())); 
		listBlocks.push_back(block);
	}
}

void extractJson(json& j, string path)
{
	std::ifstream  fp;
	fp.open(path, ifstream::binary);

	if (fp.is_open())
	{
		string fileContent;
		string buffer;
		while (!fp.eof())
		{
			getline(fp, buffer);
			fileContent += buffer;
		}

		try
		{
			j = json::parse(fileContent);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			system("pause");
		}
	}
}



void headerToJson(json & j, Header & header)
{
	j["BlockID"] = header.blockID;
	j["merkleRoot"] = header.merkleRoot;
}

void jsonToHeader(json & j, Header & header)
{
	header.blockID = j["BlockID"].dump();
	header.merkleRoot = j["merkleRoot"].dump();
}

string my_genID(void) {

	int a = (rand() % 26);
	char b = (char)a + 'A';
	string ID(1, b);
	a = (rand() % 10);
	b = (char)a + '0';
	string s(1, b);
	ID = ID + s;
	return ID;
}
string my_pkey(void) {
	string pkey("nodo");
	int a = (rand() % 10);
	char b = (char)a + '0';
	string s(1, b);
	pkey = pkey + s;
	return pkey;
}