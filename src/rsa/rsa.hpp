#pragma once
#include<lua.hpp>

int rsa_gen(lua_State* L);
int rsa_decode(lua_State* L);
int rsa_encode(lua_State* L);