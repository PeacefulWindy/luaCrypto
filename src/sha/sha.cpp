#include"sha.hpp"
#include<cryptopp/sha3.h>
#include<util/util.hpp>

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