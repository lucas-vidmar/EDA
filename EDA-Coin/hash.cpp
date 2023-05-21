#include "hash.h"


#define PRIVATE_KEY_CHARS 32
#define PUBLIC_KEY_CHARS 64

std::string myhash(std::string myID)
{
	SHA256 hash;
	std::string digest;
	StringSource s(myID, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
	return digest;
}

ECDSA<ECP, SHA256>::PrivateKey generatePrivKey()
{
	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::PrivateKey privateKey;

	//privateKey.Initialize(autoSeededRandomPool, ASN1::secp160r1());
	privateKey.Initialize(autoSeededRandomPool, ASN1::secp256k1());
	bool result = privateKey.Validate(autoSeededRandomPool, 3);
	if (!result)
		std::cout << "private key is not valid!" << std::endl;
	return privateKey;
}

std::vector<byte> getSignature(ECDSA<ECP, SHA256>::PrivateKey &privKey, std::string &data)
{
	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::Signer signer(privKey); //Creamos el signador
	bool result = signer.AccessKey().Validate(autoSeededRandomPool, 3);
	if (!result)
		std::cout << "failed to create signer" << result;
	size_t siglen = signer.MaxSignatureLength();
	std::vector<byte> signature(siglen, 0x00); //Aqui guardaremos la signature
	siglen = signer.SignMessage(autoSeededRandomPool, (const byte*)data.data(), data.size(), (byte*)signature.data());
	return signature;
}

bool verifySignature(ECDSA<ECP, SHA256>::PublicKey &pubKey, std::string &data, std::vector<byte> &signature)
{
	ECDSA<ECP, SHA256>::Verifier verifier(pubKey);
	return  verifier.VerifyMessage((const byte*)data.data(), data.size(), (const byte*)signature.data(), signature.size());
}



string pubkey2string(ECDSA<ECP, SHA256>::PrivateKey &privKey) {

	vector<byte> privKeyByteArray(PRIVATE_KEY_CHARS);
	const Integer &privateKeyInteger = privKey.GetPrivateExponent(); //La key posta
	privateKeyInteger.Encode(privKeyByteArray.data(), privateKeyInteger.ByteCount());
	unsigned int auxx = privateKeyInteger.ByteCount();
	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(privKeyByteArray.data(), privKeyByteArray.size());
	encoder.MessageEnd();
	return output;
}

string privkey2string(ECDSA<ECP, SHA256>::PublicKey &pubKey) {
	vector<byte> pubKeyByteArray(PUBLIC_KEY_CHARS);
	vector<byte> aux(PUBLIC_KEY_CHARS / 2);
	const ECP::Point &point = pubKey.GetPublicElement();
	point.x.Encode(aux.data(), point.x.ByteCount());
	pubKeyByteArray.clear();
	pubKeyByteArray.insert(pubKeyByteArray.end(), aux.begin(), aux.end());
	point.y.Encode(aux.data(), point.y.ByteCount());
	pubKeyByteArray.insert(pubKeyByteArray.end(), aux.begin(), aux.end());

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(pubKeyByteArray.data(), pubKeyByteArray.size());
	encoder.MessageEnd();
	return output;
}