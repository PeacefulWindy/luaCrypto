#include"rsa.hpp"

#include<cryptopp/cryptlib.h>
#include<cryptopp/rsa.h>
#include<cryptopp/base64.h>
#include<cryptopp/osrng.h>
#include<cryptopp/files.h>
#include <util/util.hpp>

int rsa_gen(lua_State* L)
{
	auto keyLen = luaL_checkinteger(L, 1);
	auto publicKeyFilePath = luaL_checkstring(L, 2);
	auto privateKeyFilePath = luaL_checkstring(L, 3);

	auto rng = CryptoPP::AutoSeededRandomPool();
	auto privateKey = CryptoPP::InvertibleRSAFunction();
	privateKey.Initialize(rng, 1024);

	auto privateKeySink= CryptoPP::Base64Encoder(new CryptoPP::FileSink(privateKeyFilePath));
	privateKey.DEREncode(privateKeySink);
	privateKeySink.MessageEnd();

	auto publicKey = CryptoPP::RSAFunction(privateKey);

	auto publicKeySink = CryptoPP::Base64Encoder(new CryptoPP::FileSink(publicKeyFilePath));
	publicKey.DEREncode(publicKeySink);
	publicKeySink.MessageEnd();

	return 0;
}

int rsa_decode(lua_State* L)
{
	auto top = lua_gettop(L);
	auto keyPath = luaL_checkstring(L, 1);
	auto input = luaL_checkstring(L, 2);
	auto inputLen = luaL_checkinteger(L, 3);

	auto key = CryptoPP::RSA::PrivateKey();
	try
	{
		auto bytes = CryptoPP::ByteQueue();
		auto file = CryptoPP::FileSource(keyPath, true, new CryptoPP::Base64Decoder);
		file.TransferAllTo(bytes);
		bytes.MessageEnd();
		key.Load(bytes);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 0;
	}

	auto encryptor = CryptoPP::RSAES_OAEP_SHA_Decryptor(key);
	auto outputText = std::string();
	auto rng = CryptoPP::AutoSeededRandomPool();

	CryptoPP::StringSource((const CryptoPP::byte*)input, inputLen, true, new CryptoPP::PK_DecryptorFilter(rng, encryptor, new CryptoPP::StringSink(outputText)));

	lua_pushlstring(L, outputText.c_str(), outputText.length());
	return 1;
}

int rsa_encode(lua_State* L)
{
	auto top = lua_gettop(L);
	auto publicKeyPath = luaL_checkstring(L, 1);
	auto input = luaL_checkstring(L, 2);

	auto inputLen = 0;
	if (top > 2)
	{
		inputLen = luaL_checkinteger(L, 3);
	}
	else
	{
		inputLen = strlen(input);
	}
	

	auto key = CryptoPP::RSA::PublicKey();
	try
	{
		auto bytes = CryptoPP::ByteQueue();
		auto file = CryptoPP::FileSource(publicKeyPath, true, new CryptoPP::Base64Decoder);
		file.TransferAllTo(bytes);
		bytes.MessageEnd();
		key.Load(bytes);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 0;
	}

	auto encryptor = CryptoPP::RSAES_OAEP_SHA_Encryptor(key);
	auto rng = CryptoPP::AutoSeededRandomPool();
	auto outputText = std::string();
	
	CryptoPP::StringSource((const CryptoPP::byte*)input, inputLen, true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::StringSink(outputText)));

	lua_pushlstring(L, outputText.c_str(), outputText.length());
	return 1;
}