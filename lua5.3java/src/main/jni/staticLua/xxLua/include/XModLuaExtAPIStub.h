/****************************************
 * @Author Irvin Pang @ XXTeam
 * @Repo   https://github.com/xxzhushou
 ****************************************/

#ifndef __XMOD_LUA_EXT_API_STUB_H__
#define __XMOD_LUA_EXT_API_STUB_H__

#include <functional>

#include "XModStruct.h"
#include "XModLua53APIStub.h"

typedef std::function<void(lua_State*)> lua_frame;

XMOD_API void lua_push_xmod_point(lua_State* L, const xmod_point& vec);
XMOD_API void lua_push_xmod_size(lua_State* L, const xmod_size& size);
XMOD_API void lua_push_xmod_rect(lua_State* L, const xmod_rect& rect);
XMOD_API void lua_push_xmod_color3b(lua_State* L, const xmod_color3b& c3b);
XMOD_API void lua_push_xmod_color3f(lua_State* L, const xmod_color3f& c3f);
XMOD_API void lua_push_xmod_color4b(lua_State* L, const xmod_color4b& c4b);
XMOD_API void lua_push_xmod_color4f(lua_State* L, const xmod_color4f& c4f);
XMOD_API void lua_push_xmod_image(lua_State* L, const xmod_image* image);

XMOD_API xmod_point lua_to_xmod_point(lua_State* L, int index);
XMOD_API xmod_size lua_to_xmod_size(lua_State* L, int index);
XMOD_API xmod_rect lua_to_xmod_rect(lua_State* L, int index);
XMOD_API xmod_color3b lua_to_xmod_color3b(lua_State* L, int index);
XMOD_API xmod_color3f lua_to_xmod_color3f(lua_State* L, int index);
XMOD_API xmod_color4b lua_to_xmod_color4b(lua_State* L, int index);
XMOD_API xmod_color4f lua_to_xmod_color4f(lua_State* L, int index);
XMOD_API xmod_image* lua_to_xmod_image(lua_State* L, int index);

XMOD_API void dispatch_in_lua_thread(const lua_frame& callback);

#endif // __XMOD_LUA_EXT_API_STUB_H__
