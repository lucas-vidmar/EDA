#pragma once

#include "CryptoppFiles/cryptlib.h"
#include "CryptoppFiles/osrng.h"
#include "CryptoppFiles/eccrypto.h"
#include "CryptoppFiles/oids.h"
#include "CryptoppFiles/hex.h"
#include "CryptoppFiles/sha3.h"
/*#include "CryptoppFiles/modes.h"
#include "CryptoppFiles/aes.h"
#include "CryptoppFiles/filters.h"*/
#include <string>
#include <vector>

using namespace CryptoPP;
using namespace std;

std::string myhash(std::string myID);
ECDSA<ECP, SHA256>::PrivateKey generatePrivKey(void);
std::vector<byte> getSignature(ECDSA<ECP, SHA256>::PrivateKey &privKey, std::string &data);
bool verifySignature(ECDSA<ECP, SHA256>::PublicKey &pubKey, std::string &data, std::vector<byte> &signature);


string pubkey2string(ECDSA<ECP, SHA256>::PrivateKey &privKey);
string privkey2string(ECDSA<ECP, SHA256>::PublicKey &pubKey);