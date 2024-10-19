#include<lua.hpp>
#include<cryptopp/sha3.h>
#include<cryptopp/cryptlib.h>
#include<cryptopp/hex.h>

const char* hexDigits = "0123456789abcdef";

std::string toHex(const CryptoPP::byte* digest, size_t length) 
{
	auto result=std::string();
	result.reserve(length * 2);

	for (auto i = 0; i < length; ++i) 
	{
		result.push_back(hexDigits[(digest[i] >> 4) & 0x0F]);
		result.push_back(hexDigits[digest[i] & 0x0F]);
	}

	return result;
}

int sha3_256(lua_State* L)
{
	auto top = lua_gettop(L);
	auto input = luaL_checkstring(L, 1);
	auto len = 0;
	if (top > 1)
	{
		len = luaL_checkinteger(L, 2);
	}
	else
	{
		len = strlen(input);
	}

	auto hash = CryptoPP::SHA3_256();
	CryptoPP::byte digest[CryptoPP::SHA3_256::DIGESTSIZE]{};

	hash.Update(reinterpret_cast<const CryptoPP::byte*>(input), len);
	hash.Final(digest);

	auto hexDigest = toHex(digest, sizeof(digest));
	lua_pushstring(L, hexDigest.c_str());

	return 1;
}

static const struct luaL_Reg luaCryptoLib[] = {
	{ "sha3_256", sha3_256 },
	{ NULL  , NULL },
};

extern "C"
{
	__declspec(dllexport) int luaopen_luaCrypto(lua_State* L)
	{
		luaL_newlib(L, luaCryptoLib);
		return 1;
	}
}
