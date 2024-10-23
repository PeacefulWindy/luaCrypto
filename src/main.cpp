#include<lua.hpp>
#include <fstream>
#include<base64/base64.hpp>
#include<sha/sha.hpp>
#include<rsa/rsa.hpp>
//#include<chacha/chacha.hpp>

static const struct luaL_Reg luaCryptoLib[] = 
{
	//Base64
	{"base64_encode", base64_encode},
	{"base64_decode", base64_decode},

	//SHA
	{"sha3_256", sha3_256},
	{"sha3_512", sha3_512},

	//RSA
	{"rsa_gen", rsa_gen},
	{"rsa_decode", rsa_decode},
	{"rsa_encode", rsa_encode},
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
