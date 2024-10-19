#include"base64.hpp"
#include<cryptopp/base64.h>

int base64_encode(lua_State* L)
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
		len=strlen(input);
	}

	auto outputStr=std::string();
	CryptoPP::StringSource(input, len, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(outputStr)));

	lua_pushlstring(L, outputStr.c_str(), outputStr.length());
	return 1;
}

int base64_decode(lua_State* L)
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

	auto outputStr = std::string();
	CryptoPP::StringSource(input, len, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(outputStr)));

	lua_pushlstring(L, outputStr.c_str(), outputStr.length());
	return 1;
}