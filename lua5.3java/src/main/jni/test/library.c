//
// Created by Administrator on 2018/12/17.
//

#include "library.h"

static int L_Add(lua_State *L) {
    int n = lua_gettop(L);
    if(n < 2)
        return 0;
    long a = luaL_checkinteger(L, 1);
    long b = luaL_checkinteger(L, 2);

    lua_pushnumber(L, a+b);
    return 1;
}

static const luaL_Reg Add[] = {
        {"Add", L_Add},
        {NULL, NULL}
};


int luaopen_libAdd(lua_State *L) {
    luaL_newlib(L, Add);
    return 1;
}
