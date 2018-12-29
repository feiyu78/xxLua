#ifndef LUA_1_LIBRARY_H
#define LUA_1_LIBRARY_H

#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static int L_Add(lua_State *L);

int luaopen_libAdd(lua_State *L);

#endif
