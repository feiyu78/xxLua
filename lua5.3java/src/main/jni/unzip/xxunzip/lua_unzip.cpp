
#include "ExtensionSupport.h"
#include "unzip.h"

#include <string.h>
#include <time.h>

#define MAXFILENAME (256)

#define BUFFER_SIZE 1024

typedef struct {
  int zipref;   // userdata
  int nameref;
  int pos, end;
  char buffer[BUFFER_SIZE];
} t_zipentry, *p_zipentry;

typedef struct {
  unzFile uf;
  int current_nameref;
} t_zipfile, *p_zipfile;

int zipfile_close(lua_State* L)
{
  p_zipfile zip = (p_zipfile)luaL_checkudata(L, 1, "LuaZ:UnZip");
  if (zip->uf) {

    if (zip->current_nameref != LUA_NOREF) {
      unzCloseCurrentFile(zip->uf);
      zip->current_nameref = LUA_NOREF;
    }

    unzClose(zip->uf);
    zip->uf = NULL;
  }

  return 0;
}

int zipentry_close(lua_State *L)
{
  p_zipentry zent = (p_zipentry)luaL_checkudata(L, 1, "LuaZ:UnZip:Entry");

  // release zip file
  if (zent->zipref != LUA_NOREF) {
    p_zipfile zip;

    lua_rawgeti(L, LUA_REGISTRYINDEX, zent->zipref);
    zip = (p_zipfile)luaL_checkudata(L, -1, "LuaZ:UnZip");

    if (zip->uf != NULL && zip->current_nameref == zent->nameref) {
      unzCloseCurrentFile(zip->uf);
      zip->current_nameref = LUA_NOREF;
    }
  }

  if (zent->zipref != LUA_NOREF) {
    luaL_unref(L, LUA_REGISTRYINDEX, zent->zipref);
    zent->zipref = LUA_NOREF;

    luaL_unref(L, LUA_REGISTRYINDEX, zent->nameref);
    zent->nameref = LUA_NOREF;
  }

  return 0;
}

int zipfile_open(lua_State* L)
{
    unzFile uf=NULL;
    p_zipfile zip=NULL;

    const char *zipname = luaL_checkstring(L, 1);
	printf("reading %s\n", zipname);

    uf = unzOpen(zipname);

    if (uf == NULL) {
      lua_pushnil(L);
      lua_pushstring(L, "notfound");
      return 2;
    }

    zip = (p_zipfile)lua_newuserdata(L, sizeof(t_zipfile));

    if (!zip) {
      lua_pushnil(L);
      lua_pushstring(L, "error creating ZIP object");
      unzClose(uf);
      return 2;
    }

    // initialize it!
    zip->uf = uf;
    zip->current_nameref = LUA_NOREF;

    luaL_getmetatable(L, "LuaZ:UnZip");
    lua_setmetatable(L, -2);
    return 1;
}

static int zipfile_tostring(lua_State* L)
{
  p_zipfile zip = (p_zipfile)luaL_checkudata(L, 1, "LuaZ:UnZip");
  lua_pushfstring(L, "ZipFile %p, open=%s",
                  zip,
                  (zip->uf ? "true" : "false"));
  return 1;
}

 static void stackDump (lua_State *L) {
     int i;
int top = lua_gettop(L);
for(i=1;i<=top;i++){ /*repeatforeachlevel*/
       int t = lua_type(L, i);
       switch (t) {
         case LUA_TSTRING: {  /* strings */
           printf("’%s’", lua_tostring(L, i));
           break;
         }
         case LUA_TBOOLEAN: {  /* booleans */
           printf(lua_toboolean(L, i) ? "true" : "false");
break; }
         case LUA_TNUMBER: {  /* numbers */
           printf("%g", lua_tonumber(L, i));
           break;
         }
         default: {  /* other values */
           printf("%s", lua_typename(L, t));
break; }
}
       printf("  ");  /* put a separator */
     }
     printf("\n");  /* end the listing */
   }

int zipentry_open(lua_State* L)
{
  p_zipfile zip = (p_zipfile)luaL_checkudata(L, 1, "LuaZ:UnZip");
  const char* filename = luaL_checkstring(L, 2);
  int ignorecase = luaL_optint(L, 3, 0);
  p_zipentry zent;
  int err;

  if (zip->uf == NULL) {
    lua_pushnil(L);
    lua_pushstring(L, "closed");
    return 2;
  }

  // there can only be one open at a time...
  if (zip->current_nameref != LUA_NOREF) {
    err = unzCloseCurrentFile(zip->uf);
    if (err != UNZ_OK) { lua_pushnil(L); lua_pushfstring(L, "zerror:close (%d)", err); return 2; }
    zip->current_nameref = LUA_NOREF;
  }

  err = unzLocateFile(zip->uf, filename, ignorecase);
  if (err != UNZ_OK) {
    lua_pushnil(L);
    lua_pushstring(L, "notfound");
    return 2;
  }

  err = unzOpenCurrentFile(zip->uf);
  if (err != UNZ_OK) { lua_pushnil(L); lua_pushfstring(L, "zerror:open (%d)", err); return 2; }

  zent = (p_zipentry) lua_newuserdata(L, sizeof(t_zipentry));
  luaL_getmetatable(L, "LuaZ:UnZip:Entry");
  lua_setmetatable(L, -2);

  // keep a reference to the ZipFile so it doesn't get GC'd
  lua_pushvalue(L, 1);
  zent->zipref = luaL_ref(L, LUA_REGISTRYINDEX);

  lua_pushvalue(L, 2);
  zent->nameref = luaL_ref(L, LUA_REGISTRYINDEX);

  zent->pos = 0;
  zent->end = 0;

  zip->current_nameref = zent->nameref;

  printf ("/** STACK **/\n");
  stackDump(L);

  return 1;

}

static int zipentry_tostring(lua_State* L)
{
  const char *name = "<none>";
  p_zipentry zent = (p_zipentry)luaL_checkudata(L, 1, "LuaZ:UnZip:Entry");
  p_zipfile zip = NULL;
  if (zent->nameref != LUA_NOREF) {
      lua_rawgeti(L, LUA_REGISTRYINDEX, zent->nameref);
      name = luaL_checkstring(L, -1);
  }
  if (zent->zipref != LUA_NOREF) {
      lua_rawgeti(L, LUA_REGISTRYINDEX, zent->zipref);
      zip = (p_zipfile)luaL_checkudata(L, -1, "LuaZ:UnZip");
  }
  lua_pushfstring(L, "ZipEntry %p name=%s (of %p)", zent, name, zip);
  return 1;
}


#ifndef min
#define min(X,Y) ((X)<(Y)?(X):(Y))
#endif

int
zipentry_read(lua_State* L)
{
  int read_all  = 0;
  int read_N    = 0;
  int read_some = 0;
  int read_line = 0;
  int top = lua_gettop(L);
  p_zipentry zent = (p_zipentry)luaL_checkudata(L, 1, "LuaZ:UnZip:Entry");
  p_zipfile zip;

  if (!lua_isnumber(L, 2)) {
    const char *p= luaL_optstring(L, 2, "*l");
    if        (p[0] == '*' && p[1] == 'l') {
      read_line = 1;
    } else if (p[0] == '*' && p[1] == 'a') {
      read_all = 1;
    } else if (p[0] == '*' && p[1] == 'b') {
      read_some = 1;
    } else {
      luaL_argcheck(L, 0, 2, "invalid read pattern");
    }
  } else {
    double n = lua_tonumber(L, 2);
    read_N = (size_t)n;
    luaL_argcheck(L, n >= 0, 2, "invalid read pattern");
  }

  if(zent->zipref == LUA_NOREF)
    {
      lua_pushnil(L);
      lua_pushstring(L, "closed");
      return 2;
    }

  lua_rawgeti(L, LUA_REGISTRYINDEX, zent->zipref);
  zip = (p_zipfile)luaL_checkudata(L, -1, "LuaZ:UnZip");
  if (zip->uf == NULL)
    {
      lua_pushnil(L);
      lua_pushstring(L, "closed");
      return 2;
    }

  if (zip->current_nameref == zent->nameref)
    {
      /* we're good */
    }
  else
    {
      int err;
      const char *filename;

      if (zip->current_nameref != LUA_NOREF) {
        err = unzCloseCurrentFile(zip->uf);
        if (err != UNZ_OK) { lua_pushnil(L); lua_pushfstring(L, "zerror (%d)", err); return 2; }
        zip->current_nameref = LUA_NOREF;
      }

      lua_rawgeti(L, LUA_REGISTRYINDEX, zent->nameref);
      filename = luaL_checkstring(L, -1);

      err = unzLocateFile(zip->uf, filename, 0);
      if (err != UNZ_OK) {
        lua_pushnil(L);
        lua_pushstring(L, "notfound");
        return 2;
      }

      err = unzOpenCurrentFile(zip->uf);
      if (err != UNZ_OK) { lua_pushnil(L); lua_pushfstring(L, "zerror:ocf (%d)", err); return 2; }
      zip->current_nameref = zent->nameref;
      /* skip to offset? */
    }

  if (read_some)
  {
    long n;
    luaL_Buffer buf;
    char *raw;
    luaL_buffinit(L, &buf);

    luaL_addlstring(&buf, &zent->buffer[zent->pos], zent->end - zent->pos);
    zent->end = zent->pos = 0;

    raw = luaL_prepbuffer(&buf);
    n = unzReadCurrentFile(zip->uf, raw, LUAL_BUFFERSIZE);
    if (n >= 0) {
      luaL_addsize(&buf, n);
    } else {
      lua_pushnil(L);
      lua_pushfstring(L, "readerror (%d)", n);
      return 2;
    }

    if (n == 0) {
      lua_pushnil(L);
      lua_pushstring(L, "eof");
      return 2;
    } else {
      luaL_pushresult(&buf);
      return 1;
    }

  } else if (read_line) {
    int err = 0;
    luaL_Buffer buf;
    luaL_buffinit(L, &buf);

    do {

      /*scan for newline*/
      while (zent->pos < zent->end) {
        char ch = zent->buffer[zent->pos];
        if (ch == '\n') {
          zent->pos += 1;
          luaL_pushresult(&buf);
          return 1;
        } else if (ch == '\r') {
          continue;
        } else {
          luaL_addchar(&buf, ch);
          zent->pos += 1;
        }
      }

      /*fill input*/
      err = unzReadCurrentFile(zip->uf, zent->buffer, BUFFER_SIZE);
      zent->pos = 0;
      if (err >= 0)
        zent->end = err;
      else
        {
          lua_pushnil(L);
          lua_pushstring(L, "readerror");
          return 2;
        }
    } while (err > 0);

    if (err == 0) {
      lua_pushnil(L);
      lua_pushstring(L, "eof");
      return 2;
    } else {
      luaL_pushresult(&buf);
      return 1;
    }

  } else if (read_N > 0) {
    int err = 0;
    size_t n;
    luaL_Buffer buf;
    luaL_buffinit(L, &buf);

    do {
      n = min(zent->end-zent->pos, read_N);
      if (n > 0) {
        luaL_addlstring(&buf, &zent->buffer[zent->pos], n);
        zent->pos += n;
        luaL_addsize(&buf, n);
        read_N -= n;
      }

      if (read_N > 0) {
        err = unzReadCurrentFile(zip->uf, zent->buffer, BUFFER_SIZE);
        zent->pos = 0;
        if (err >= 0)
          zent->end = err;
      }

    } while (read_N > 0 && err > 0);

    luaL_pushresult(&buf);
    return 1;

  } else {
      lua_pushnil(L);
      lua_pushstring(L, "badarg");
      return 2;
  }
}

int push_fileinfo(lua_State* L, const char *name, unz_file_info *file_info)
{
  lua_newtable(L);

  lua_pushstring(L, name);
  lua_setfield(L, -2, "filename");

  lua_pushnumber(L, file_info->compressed_size);
  lua_setfield(L, -2, "compressed_size");

  lua_pushnumber(L, file_info->uncompressed_size);
  lua_setfield(L, -2, "uncompressed_size");

  {
    struct tm newdate;
    time_t t;
    tm_unz *date = &file_info->tmu_date;
    newdate.tm_sec = date->tm_sec;
    newdate.tm_min=date->tm_min;
    newdate.tm_hour=date->tm_hour;
    newdate.tm_mday=date->tm_mday;
    newdate.tm_mon=date->tm_mon;
    if (date->tm_year > 1900)
      newdate.tm_year=date->tm_year - 1900;
    else
      newdate.tm_year=date->tm_year ;
    newdate.tm_isdst=-1;
    t = mktime(&newdate);

    lua_pushnumber(L, t);
    lua_setfield(L, -2, "time");
  }

  return 0;
}

int
zipfile_list(lua_State* L)
{
  p_zipfile zip = (p_zipfile)luaL_checkudata(L, 1, "LuaZ:UnZip");
  uLong i;
  unz_global_info gi;
  int err;

  if (zip->uf == NULL) {
    lua_pushnil(L);
    lua_pushstring(L, "closed");
    return 2;
  }


  if (zip->current_nameref != LUA_NOREF) {
    err = unzCloseCurrentFile(zip->uf);
    zip->current_nameref = LUA_NOREF;
  }

  err = unzGetGlobalInfo(zip->uf,&gi);
  if (err != UNZ_OK) {
    lua_pushnil(L);
    lua_pushstring(L, "error in GetGlobalInfo");
    return 2;
  }

  err = unzGoToFirstFile(zip->uf);
  if (err != UNZ_OK) {
    lua_pushnil(L);
    lua_pushstring(L, "error in GoToFirstFile");
    return 2;
  }

  lua_newtable(L);
  for (i=0;i<gi.number_entry;i++)
    {
      char filename_inzip[256];
      unz_file_info file_info;
      uLong ratio=0;
      char charCrypt=' ';
      err = unzGetCurrentFileInfo(zip->uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
      if (err!=UNZ_OK) {
        char buffer[256];
        sprintf(buffer, "error %d in GetCurrentFileInfo", err);
        lua_pushnil(L);
        lua_pushstring(L, buffer);
        return 2;
      }

      push_fileinfo(L, filename_inzip, &file_info);
      lua_rawseti(L, -2, i+1);

      if ((i+1)<gi.number_entry) {
        err = unzGoToNextFile(zip->uf);
      if (err!=UNZ_OK) {
        char buffer[256];
        sprintf(buffer, "error %d in GoToNextFile", err);
        lua_pushnil(L);
        lua_pushstring(L, buffer);
        return 2;
      }
      }
    }

  return 1;

}

static int file_iter(lua_State* L)
{
  int idx = lua_tointeger(L, lua_upvalueindex(2));
  idx += 1;

  lua_pushinteger(L, idx);
  lua_replace(L, lua_upvalueindex(2));

  lua_rawgeti(L, lua_upvalueindex(1), idx);

  return 1;
}

int
zipfile_files(lua_State* L)
{
  int num = zipfile_list(L);
  if (num != 1) return num;
  lua_pushinteger(L, 0);
  lua_pushcclosure(L, &file_iter, 2);
  return 1;
}


int
zipfile_read(lua_State* L)
{
  p_zipfile zip = (p_zipfile)luaL_checkudata(L, 1, "LuaZ:UnZip");
  const char* filename = luaL_checkstring(L, 2);
  int ignorecase = luaL_optint(L, 3, 0);
  int is_open = 0;
  char *content = NULL;
  int err;

  if (zip->uf == NULL) {
    lua_pushnil(L);
    lua_pushstring(L, "closed");
    return 2;
  }

  if (zip->current_nameref != LUA_NOREF) {
    unzCloseCurrentFile(zip->uf);
    zip->current_nameref = LUA_NOREF;
  }

  err = unzLocateFile(zip->uf, filename, ignorecase);
  if (err != UNZ_OK) { goto error; }

  {
    char filename_inzip[256];
    unz_file_info file_info;

    err = unzGetCurrentFileInfo(zip->uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
    if (err != UNZ_OK) goto error;

    content = (char*)malloc ( file_info.uncompressed_size );
    if (content == NULL) {
      lua_pushnil(L);
      lua_pushstring(L, "malloc");
      return 2;
    }

    err = unzOpenCurrentFile(zip->uf);
    if (err != UNZ_OK) { free (content); content=NULL; goto error; }
    is_open = 1;

    {
      int n;
      int pos = 0;
      do {
        n = unzReadCurrentFile(zip->uf, content+pos, 1024);
        if (n>0) pos += n;
      } while (n > 0);

      lua_pushlstring(L, content, file_info.uncompressed_size);
      free (content);
      unzCloseCurrentFile(zip->uf);
      return 1;

    }
  }


 error:
  if (is_open) {
    unzCloseCurrentFile(zip->uf);
  }

  if (content) {
    free (content);
  }

  lua_pushnil(L);
  lua_pushstring(L, "notfound");
  return 2;
}


static luaL_Reg core_funcs[] = {
  {"open", 	zipfile_open},
  {NULL, NULL}
};

static luaL_Reg zipfile_meta[] = {
  {"__gc",	zipfile_close},
  {"__tostring", zipfile_tostring},
  {NULL, NULL}
};

static luaL_Reg zipfile_methods[] = {
  {"files",	zipfile_files},
  {"list",	zipfile_list},
  {"read",	zipfile_read},
  {"close",	zipfile_close},
  {"open",	zipentry_open},
  {NULL, NULL}
};

static luaL_Reg zipentry_meta[] = {
  {"__gc",	zipentry_close},
  {"__tostring", zipentry_tostring},
  {NULL, NULL}
};

static luaL_Reg zipentry_methods[] = {
  {"close",	zipentry_close},
  {"read",	zipentry_read},
  {NULL, NULL}
};

extern "C" __attribute__((visibility("default")))
int luaopen_unzip(lua_State *L)
{
  /* Register the functions and tables */
  luaL_newmetatable(L, "LuaZ:UnZip");
  luaL_register(L, NULL, zipfile_meta);

  lua_newtable(L);
  luaL_register(L, NULL, zipfile_methods);
  lua_setfield(L, -2, "__index");
  lua_pop(L, 1);

  /* Register the functions and tables */
  luaL_newmetatable(L, "LuaZ:UnZip:Entry");
  luaL_register(L, NULL, zipentry_meta);

  lua_newtable(L);
  luaL_register(L, NULL, zipentry_methods);
  lua_setfield(L, -2, "__index");
  lua_pop(L, 1);

  lua_newtable(L);
  luaL_register(L, "unzip", core_funcs);

  return 1;
}
