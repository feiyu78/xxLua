/****************************************
 * @Author jinqian @ XXTeam
 * @Repo   https://github.com/xxzhushou
 ****************************************/

#ifndef __LUA_API_STUB_53_H__
#define __LUA_API_STUB_53_H__

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

#include "Macros.h"

#define LUA_VERSION_NUM             503

/* option for multiple returns in 'lua_pcall' and 'lua_call' */
#define LUA_MULTRET                 (-1)

/*
** Pseudo-indices
** (-LUAI_MAXSTACK is the minimum valid index; we keep some free empty
** space after that to help overflow detection)
*/
#define LUAI_MAXSTACK               1000000
#define LUA_REGISTRYINDEX           (-LUAI_MAXSTACK - 1000)


/* thread status */
#define LUA_OK                      0
#define LUA_YIELD                   1
#define LUA_ERRRUN                  2
#define LUA_ERRSYNTAX               3
#define LUA_ERRMEM                  4
#define LUA_ERRGCMM                 5
#define LUA_ERRERR                  6

/* data types */
typedef void                        lua_State;
typedef float                       lua_Number;
typedef int32_t                     lua_Integer;
typedef uint32_t                    lua_Unsigned;
typedef ptrdiff_t                   lua_KContext;

/* basic types */
#define LUA_TNONE                   (-1)
#define LUA_TNIL                    0
#define LUA_TBOOLEAN                1
#define LUA_TLIGHTUSERDATA          2
#define LUA_TNUMBER                 3
#define LUA_TSTRING                 4
#define LUA_TTABLE                  5
#define LUA_TFUNCTION               6
#define LUA_TUSERDATA               7
#define LUA_TTHREAD                 8
#define LUA_NUMTAGS                 9

/* minimum Lua stack available to a C function */
#define LUA_MINSTACK                20

/* predefined values in the registry */
#define LUA_RIDX_MAINTHREAD         1
#define LUA_RIDX_GLOBALS            2
#define LUA_RIDX_LAST               LUA_RIDX_GLOBALS

#define LUAL_NUMSIZES               (sizeof(lua_Integer) * 16 + sizeof(lua_Number))
#define LUAL_BUFFERSIZE             ((int)(0x80 * sizeof(void*) * sizeof(lua_Integer)))

#define LUA_NOREF                   (-2)
#define LUA_REFNIL                  (-1)

#define LUA_OPADD                   0   /* ORDER TM, ORDER OP */
#define LUA_OPSUB                   1
#define LUA_OPMUL                   2
#define LUA_OPMOD                   3
#define LUA_OPPOW                   4
#define LUA_OPDIV                   5
#define LUA_OPIDIV                  6
#define LUA_OPBAND                  7
#define LUA_OPBOR                   8
#define LUA_OPBXOR                  9
#define LUA_OPSHL                   10
#define LUA_OPSHR                   11
#define LUA_OPUNM                   12
#define LUA_OPBNOT                  13

#define LUA_OPEQ                    0
#define LUA_OPLT                    1
#define LUA_OPLE                    2

/*
** Type for C functions registered with Lua
*/
typedef int (*lua_CFunction) (lua_State* L);

/*
** Type for continuation functions
*/
typedef int (*lua_KFunction) (lua_State* L, int status, lua_KContext ctx);


/*
** Type for memory-allocation functions
*/
typedef void* (*lua_Alloc) (void* ud, void* ptr, size_t osize, size_t nsize);

typedef struct luaL_Buffer
{
    char* b;  /* buffer address */
    size_t size;  /* buffer size */
    size_t n;  /* number of characters in buffer */
    lua_State* L;
    char initb[LUAL_BUFFERSIZE];  /* initial buffer */
} luaL_Buffer;

typedef struct luaL_Reg
{
    const char* name;
    lua_CFunction func;
} luaL_Reg;

#define API_DEFINE(retType, funcName, ...) \
    XMOD_API retType funcName(__VA_ARGS__)

XMOD_C_API_BEGIN

API_DEFINE(lua_State*,              lua_newthread,              lua_State* L);
API_DEFINE(lua_CFunction,           lua_atpanic,                lua_State* L, lua_CFunction panicf);
API_DEFINE(const lua_Number*,       lua_version,                lua_State* L);
API_DEFINE(int,                     lua_absindex,               lua_State* L, int idx);
API_DEFINE(int,                     lua_gettop,                 lua_State* L);
API_DEFINE(void,                    lua_settop,                 lua_State* L, int idx);
API_DEFINE(void,                    lua_pushvalue,              lua_State* L, int idx);
API_DEFINE(void,                    lua_rotate,                 lua_State* L, int idx, int n);
API_DEFINE(void,                    lua_copy,                   lua_State* L, int fromidx, int toidx);
API_DEFINE(int,                     lua_checkstack,             lua_State* L, int n);
API_DEFINE(void,                    lua_xmove,                  lua_State* from, lua_State* to, int n);
API_DEFINE(int,                     lua_isnumber,               lua_State* L, int idx);
API_DEFINE(int,                     lua_isstring,               lua_State* L, int idx);
API_DEFINE(int,                     lua_iscfunction,            lua_State* L, int idx);
API_DEFINE(int,                     lua_isinteger,              lua_State* L, int idx);
API_DEFINE(int,                     lua_isuserdata,             lua_State* L, int idx);
API_DEFINE(int,                     lua_type,                   lua_State* L, int idx);
API_DEFINE(const char*,             lua_typename,               lua_State* L, int tp);
API_DEFINE(lua_Number,              lua_tonumberx,              lua_State* L, int idx, int* isnum);
API_DEFINE(lua_Integer,             lua_tointegerx,             lua_State* L, int idx, int* isnum);
API_DEFINE(int,                     lua_toboolean,              lua_State* L, int idx);
API_DEFINE(const char*,             lua_tolstring,              lua_State* L, int idx, size_t* len);
API_DEFINE(size_t,                  lua_rawlen,                 lua_State* L, int idx);
API_DEFINE(lua_CFunction,           lua_tocfunction,            lua_State* L, int idx);
API_DEFINE(void*,                   lua_touserdata,             lua_State* L, int idx);
API_DEFINE(lua_State*,              lua_tothread,               lua_State* L, int idx);
API_DEFINE(const void*,             lua_topointer,              lua_State* L, int idx);
API_DEFINE(void,                    lua_arith,                  lua_State* L, int op);
API_DEFINE(int,                     lua_rawequal,               lua_State* L, int idx1, int idx2);
API_DEFINE(int,                     lua_compare,                lua_State* L, int idx1, int idx2, int op);
API_DEFINE(void,                    lua_pushnil,                lua_State* L);
API_DEFINE(void,                    lua_pushnumber,             lua_State* L, lua_Number n);
API_DEFINE(void,                    lua_pushinteger,            lua_State* L, lua_Integer n);
API_DEFINE(const char*,             lua_pushlstring,            lua_State* L, const char* s, size_t len);
API_DEFINE(const char*,             lua_pushstring,             lua_State* L, const char* s);
API_DEFINE(const char*,             lua_pushvfstring,           lua_State* L, const char* fmt, va_list argp);
API_DEFINE(const char*,             lua_pushfstring,            lua_State* L, const char* fmt, ...);
API_DEFINE(void,                    lua_pushcclosure,           lua_State* L, lua_CFunction fn, int n);
API_DEFINE(void,                    lua_pushboolean,            lua_State* L, int b);
API_DEFINE(void,                    lua_pushlightuserdata,      lua_State* L, void* p);
API_DEFINE(int,                     lua_pushthread,             lua_State* L);
API_DEFINE(int,                     lua_getglobal,              lua_State* L, const char* name);
API_DEFINE(int,                     lua_gettable,               lua_State* L, int idx);
API_DEFINE(int,                     lua_getfield,               lua_State* L, int idx, const char* k);
API_DEFINE(int,                     lua_geti,                   lua_State* L, int idx, lua_Integer n);
API_DEFINE(int,                     lua_rawget,                 lua_State* L, int idx);
API_DEFINE(int,                     lua_rawgeti,                lua_State* L, int idx, lua_Integer n);
API_DEFINE(int,                     lua_rawgetp,                lua_State* L, int idx, const void* p);
API_DEFINE(void,                    lua_createtable,            lua_State* L, int narr, int nrec);
API_DEFINE(void*,                   lua_newuserdata,            lua_State* L, size_t sz);
API_DEFINE(int,                     lua_getmetatable,           lua_State* L, int objindex);
API_DEFINE(int,                     lua_getuservalue,           lua_State* L, int idx);
API_DEFINE(void,                    lua_setglobal,              lua_State* L, const char* name);
API_DEFINE(void,                    lua_settable,               lua_State* L, int idx);
API_DEFINE(void,                    lua_setfield,               lua_State* L, int idx, const char* k);
API_DEFINE(void,                    lua_seti,                   lua_State* L, int idx, lua_Integer n);
API_DEFINE(void,                    lua_rawset,                 lua_State* L, int idx);
API_DEFINE(void,                    lua_rawseti,                lua_State* L, int idx, lua_Integer n);
API_DEFINE(void,                    lua_rawsetp,                lua_State* L, int idx, const void* p);
API_DEFINE(int,                     lua_setmetatable,           lua_State* L, int objindex);
API_DEFINE(void,                    lua_setuservalue,           lua_State* L, int idx);
API_DEFINE(void,                    lua_callk,                  lua_State* L, int nargs, int nresults, lua_KContext ctx, lua_KFunction k);
API_DEFINE(int,                     lua_pcallk,                 lua_State* L, int nargs, int nresults, int errfunc, lua_KContext ctx, lua_KFunction k);
API_DEFINE(int,                     lua_yieldk,                 lua_State* L, int nresults, lua_KContext ctx, lua_KFunction k);
API_DEFINE(int,                     lua_resume,                 lua_State* L, lua_State* from, int narg);
API_DEFINE(int,                     lua_status,                 lua_State* L);
API_DEFINE(int,                     lua_isyieldable,            lua_State* L);
API_DEFINE(int,                     lua_gc,                     lua_State* L, int what, int data);
API_DEFINE(int,                     lua_error,                  lua_State* L);
API_DEFINE(int,                     lua_next,                   lua_State* L, int idx);
API_DEFINE(void,                    lua_concat,                 lua_State* L, int n);
API_DEFINE(void,                    lua_len,                    lua_State* L, int idx);
API_DEFINE(size_t,                  lua_stringtonumber,         lua_State* L, const char* s);
API_DEFINE(lua_Alloc,               lua_getallocf,              lua_State* L, void** ud);
API_DEFINE(void,                    lua_setallocf,              lua_State* L, lua_Alloc f, void* ud);
API_DEFINE(const char*,             lua_getupvalue,             lua_State* L, int funcindex, int n);
API_DEFINE(const char*,             lua_setupvalue,             lua_State* L, int funcindex, int n);
API_DEFINE(void*,                   lua_upvalueid,              lua_State* L, int fidx, int n);
API_DEFINE(void,                    lua_upvaluejoin,            lua_State* L, int fidx1, int n1, int fidx2, int n2);
API_DEFINE(void,                    luaL_checkversion_,         lua_State* L, lua_Number ver, size_t sz);
API_DEFINE(int,                     luaL_getmetafield,          lua_State* L, int obj, const char* e);
API_DEFINE(int,                     luaL_callmeta,              lua_State* L, int obj, const char* e);
API_DEFINE(const char*,             luaL_tolstring,             lua_State* L, int idx, size_t* len);
API_DEFINE(int,                     luaL_argerror,              lua_State* L, int arg, const char* extramsg);
API_DEFINE(const char*,             luaL_checklstring,          lua_State* L, int arg, size_t* l);
API_DEFINE(const char*,             luaL_optlstring,            lua_State* L, int arg, const char* def, size_t* l);
API_DEFINE(lua_Number,              luaL_checknumber,           lua_State* L, int arg);
API_DEFINE(lua_Number,              luaL_optnumber,             lua_State* L, int arg, lua_Number def);
API_DEFINE(lua_Integer,             luaL_checkinteger,          lua_State* L, int arg);
API_DEFINE(lua_Integer,             luaL_optinteger,            lua_State* L, int arg, lua_Integer def);
API_DEFINE(void,                    luaL_checkstack,            lua_State* L, int sz, const char* msg);
API_DEFINE(void,                    luaL_checktype,             lua_State* L, int arg, int t);
API_DEFINE(void,                    luaL_checkany,              lua_State* L, int arg);
API_DEFINE(int,                     luaL_newmetatable,          lua_State* L, const char* tname);
API_DEFINE(void,                    luaL_setmetatable,          lua_State* L, const char* tname);
API_DEFINE(void*,                   luaL_testudata,             lua_State* L, int ud, const char* tname);
API_DEFINE(void*,                   luaL_checkudata,            lua_State* L, int ud, const char* tname);
API_DEFINE(void,                    luaL_where,                 lua_State* L, int lvl);
API_DEFINE(int,                     luaL_error,                 lua_State* L, const char* fmt, ...);
API_DEFINE(int,                     luaL_checkoption,           lua_State* L, int arg, const char* def, const char* const lst[]);
API_DEFINE(int,                     luaL_fileresult,            lua_State* L, int stat, const char* fname);
API_DEFINE(int,                     luaL_execresult,            lua_State* L, int stat);
API_DEFINE(int,                     luaL_ref,                   lua_State* L, int t);
API_DEFINE(void,                    luaL_unref,                 lua_State* L, int t, int ref);
API_DEFINE(lua_Integer,             luaL_len,                   lua_State* L, int idx);
API_DEFINE(const char*,             luaL_gsub,                  lua_State* L, const char* s, const char* p, const char* r);
API_DEFINE(void,                    luaL_setfuncs,              lua_State* L, const luaL_Reg* l, int nup);
API_DEFINE(int,                     luaL_getsubtable,           lua_State* L, int idx, const char* fname);
API_DEFINE(void,                    luaL_traceback,             lua_State* L, lua_State* L1, const char* msg, int level);
API_DEFINE(void,                    luaL_requiref,              lua_State* L, const char* modname, lua_CFunction openf, int glb);
API_DEFINE(void,                    luaL_buffinit,              lua_State* L, luaL_Buffer* B);
API_DEFINE(char*,                   luaL_prepbuffsize,          luaL_Buffer* B, size_t sz);
API_DEFINE(void,                    luaL_addlstring,            luaL_Buffer* B, const char* s, size_t l);
API_DEFINE(void,                    luaL_addstring,             luaL_Buffer* B, const char* s);
API_DEFINE(void,                    luaL_addvalue,              luaL_Buffer* B);
API_DEFINE(void,                    luaL_pushresult,            luaL_Buffer* B);
API_DEFINE(void,                    luaL_pushresultsize,        luaL_Buffer* B, size_t sz);
API_DEFINE(char*,                   luaL_buffinitsize,          lua_State* L, luaL_Buffer* B, size_t sz);
API_DEFINE(void,                    luaL_pushmodule,            lua_State* L, const char* modname, int sizehint);
API_DEFINE(void,                    luaL_openlib,               lua_State* L, const char* libname, const luaL_Reg* l, int nup);

XMOD_C_API_END

#undef API_DEFINE

#define luaL_checkint(L, n)         luaL_checkinteger(L, (n))
#define luaL_optint(L, n, def)      luaL_optinteger(L, (n), def)

#define lua_upvalueindex(i)         (LUA_REGISTRYINDEX - (i))
#define lua_call(L, n, r)           lua_callk(L, (n), (r), 0, NULL)
#define lua_pcall(L, n, r, f)       lua_pcallk(L, (n), (r), (f), 0, NULL)
#define lua_yield(L, n)             lua_yieldk(L, (n), 0, NULL)
#define lua_getextraspace(L)        ((void* )((char* )(L) - LUA_EXTRASPACE))
#define lua_tonumber(L, i)          lua_tonumberx(L, (i), NULL)
#define lua_tointeger(L, i)         lua_tointegerx(L, (i), NULL)
#define lua_pop(L, n)               lua_settop(L, -(n) -1)
#define lua_newtable(L)             lua_createtable(L, 0, 0)
#define lua_register(L, n, f)       (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))
#define lua_pushcfunction(L, f)     lua_pushcclosure(L, (f), 0)
#define lua_isfunction(L, n)        (lua_type(L, (n)) == LUA_TFUNCTION)
#define lua_istable(L, n)           (lua_type(L, (n)) == LUA_TTABLE)
#define lua_islightuserdata(L, n)   (lua_type(L, (n)) == LUA_TLIGHTUSERDATA)
#define lua_isnil(L, n)             (lua_type(L, (n)) == LUA_TNIL)
#define lua_isboolean(L, n)         (lua_type(L, (n)) == LUA_TBOOLEAN)
#define lua_isthread(L, n)          (lua_type(L, (n)) == LUA_TTHREAD)
#define lua_isnone(L, n)            (lua_type(L, (n)) == LUA_TNONE)
#define lua_isnoneornil(L, n)       (lua_type(L, (n)) <= 0)
#define lua_pushliteral(L, s)       lua_pushstring(L, "" s)
#define lua_pushglobaltable(L)      ((void)lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS))
#define lua_tostring(L, i)          lua_tolstring(L, (i), NULL)
#define lua_insert(L, idx)          lua_rotate(L, (idx), 1)
#define lua_remove(L, idx)          (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#define lua_replace(L, idx)         (lua_copy(L, -1, (idx)), lua_pop(L, 1))
#define luaL_register(L, n, l)      (luaL_openlib(L,(n),(l),0))
#define luaL_checkversion(L)        luaL_checkversion_(L, LUA_VERSION_NUM, LUAL_NUMSIZES)
#define luaL_newlibtable(L, l)      lua_createtable(L, 0, sizeof(l) / sizeof((l)[0]) - 1)
#define luaL_newlib(L, l)           (luaL_checkversion(L), luaL_newlibtable(L, l), luaL_setfuncs(L, l, 0))
#define luaL_argcheck(L, cond, arg, extramsg) ((void)((cond) || luaL_argerror(L, (arg), (extramsg))))
#define luaL_checkstring(L, n)      (luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L, n, d)     (luaL_optlstring(L, (n), (d), NULL))
#define luaL_typename(L, i)         lua_typename(L, lua_type(L, (i)))
#define luaL_getmetatable(L, n)     (lua_getfield(L, LUA_REGISTRYINDEX, (n)))
#define luaL_opt(L, f, n, d)        (lua_isnoneornil(L, (n)) ? (d) : f(L, (n)))
#define luaL_addchar(B, c)          ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), ((B)->b[(B)->n++] = (c)))
#define luaL_addsize(B, s)          ((B)->n += (s))
#define luaL_prepbuffer(B)          luaL_prepbuffsize(B, LUAL_BUFFERSIZE)
#define lua_getfenv(L, l)           lua_getuservalue(L, (l))
#define lua_setfenv(L, l)           lua_setuservalue(L, (l))

#define lua_cpcall(L, f, u)         (lua_pushcfunction(L, (f)), lua_pushlightuserdata(L, (u)), lua_pcall(L, 1, 0, 0))
#define lua_strlen(L, i)            lua_rawlen(L, (i))
#define lua_objlen(L, i)            lua_rawlen(L, (i))
#define lua_equal(L, idx1, idx2)    lua_compare(L, (idx1), (idx2), LUA_OPEQ)
#define lua_lessthan(L, idx1, idx2) lua_compare(L, (idx1), (idx2), LUA_OPLT)

#endif // __LUA_API_STUB_53_H__