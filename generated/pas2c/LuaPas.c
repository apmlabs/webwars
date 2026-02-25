#include "fpcrtl.h"

#include "LuaPas.h"
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
#include "uUtils.h"
void luapas_lua_saveline(Plua_State L,LongInt idx)
{
};
void luapas_lua_freeline(Plua_State L,PChar b)
{
};
LongInt luapas_lua_upvalueindex(LongInt idx)
{
    LongInt lua_upvalueindex_result;
    lua_upvalueindex_result = LUA_GLOBALSINDEX - idx;
    return lua_upvalueindex_result;
};
void luapas_lua_pop(Plua_State L,LongInt n)
{
    lua_settop(L, -n - 1);
};
void luapas_lua_newtable(Plua_State L)
{
    lua_createtable(L, 0, 0);
};
void luapas_lua_register(Plua_State L,PChar n,luapas_lua_CFunction luapas_f)
{
    luapas_lua_pushcfunction(L, luapas_f);
    luapas_lua_setglobal(L, n);
};
void luapas_lua_pushcfunction(Plua_State L,luapas_lua_CFunction luapas_f)
{
    lua_pushcclosure(L, luapas_f, 0);
};
LongInt luapas_lua_strlen(Plua_State L,LongInt idx)
{
    LongInt lua_strlen_result;
    lua_strlen_result = lua_objlen(L, idx);
    return lua_strlen_result;
};
boolean luapas_lua_isfunction(Plua_State L,LongInt n)
{
    boolean lua_isfunction_result;
    lua_isfunction_result = lua_type(L, n) == LUA_TFUNCTION;
    return lua_isfunction_result;
};
boolean luapas_lua_istable(Plua_State L,LongInt n)
{
    boolean lua_istable_result;
    lua_istable_result = lua_type(L, n) == LUA_TTABLE;
    return lua_istable_result;
};
boolean luapas_lua_islightuserdata(Plua_State L,LongInt n)
{
    boolean lua_islightuserdata_result;
    lua_islightuserdata_result = lua_type(L, n) == LUA_TLIGHTUSERDATA;
    return lua_islightuserdata_result;
};
boolean luapas_lua_isnil(Plua_State L,LongInt n)
{
    boolean lua_isnil_result;
    lua_isnil_result = lua_type(L, n) == LUA_TNIL;
    return lua_isnil_result;
};
boolean luapas_lua_isboolean(Plua_State L,LongInt n)
{
    boolean lua_isboolean_result;
    lua_isboolean_result = lua_type(L, n) == LUA_TBOOLEAN;
    return lua_isboolean_result;
};
boolean luapas_lua_isthread(Plua_State L,LongInt n)
{
    boolean lua_isthread_result;
    lua_isthread_result = lua_type(L, n) == LUA_TTHREAD;
    return lua_isthread_result;
};
boolean luapas_lua_isnone(Plua_State L,LongInt n)
{
    boolean lua_isnone_result;
    lua_isnone_result = lua_type(L, n) == LUA_TNONE;
    return lua_isnone_result;
};
boolean luapas_lua_isnoneornil(Plua_State L,LongInt n)
{
    boolean lua_isnoneornil_result;
    lua_isnoneornil_result = lua_type(L, n) <= 0;
    return lua_isnoneornil_result;
};
void luapas_lua_pushliteral(Plua_State L,PChar s)
{
    lua_pushlstring(L, s, fpcrtl_StrLen(s));
};
void luapas_lua_setglobal(Plua_State L,PChar s)
{
    lua_setfield(L, LUA_GLOBALSINDEX, s);
};
void luapas_lua_getglobal(Plua_State L,PChar s)
{
    lua_getfield(L, LUA_GLOBALSINDEX, s);
};
string255 luapas_lua_tostring(Plua_State L,LongInt idx)
{
    string255 lua_tostring_result;
    lua_tostring_result = fpcrtl_StrPas(lua_tolstring(L, idx, NULL));
    return lua_tostring_result;
};
astring luapas_lua_tostringA(Plua_State L,LongInt idx)
{
    astring lua_tostringa_result;
    PChar p;
    p = lua_tolstring(L, idx, NULL);
    lua_tostringa_result = fpcrtl_pchar2astr(p);
    return lua_tostringa_result;
};
Plua_State luapas_lua_open()
{
    Plua_State lua_open_result;
    lua_open_result = luaL_newstate();
    return lua_open_result;
};
void luapas_lua_getregistry(Plua_State L)
{
    lua_pushvalue(L, LUA_REGISTRYINDEX);
};
LongInt luapas_lua_getgccount(Plua_State L)
{
    LongInt lua_getgccount_result;
    lua_getgccount_result = lua_gc(L, LUA_GCCOUNT, 0);
    return lua_getgccount_result;
};
void luapas_lua_assert(boolean x)
{
};
LongInt luapas_luaL_getn(Plua_State L,LongInt idx)
{
    LongInt lual_getn_result;
    lual_getn_result = lua_objlen(L, idx);
    return lual_getn_result;
};
void luapas_luaL_setn(Plua_State L,LongInt i,LongInt j)
{
};
LongInt luapas_luaL_argcheck(Plua_State L,boolean cond,LongInt numarg,PChar extramsg)
{
    LongInt lual_argcheck_result;
    if(!cond)
    {
        lual_argcheck_result = luaL_argerror(L, numarg, extramsg);
    }
    else
    {
        lual_argcheck_result = 0;
    }
    return lual_argcheck_result;
};
PChar luapas_luaL_checkstring(Plua_State L,LongInt n)
{
    PChar lual_checkstring_result;
    lual_checkstring_result = luaL_checklstring(L, n, NULL);
    return lual_checkstring_result;
};
PChar luapas_luaL_optstring(Plua_State L,LongInt n,PChar d)
{
    PChar lual_optstring_result;
    lual_optstring_result = luaL_optlstring(L, n, d, NULL);
    return lual_optstring_result;
};
lua_Integer luapas_luaL_checkint(Plua_State L,LongInt n)
{
    lua_Integer lual_checkint_result;
    lual_checkint_result = luaL_checkinteger(L, n);
    return lual_checkint_result;
};
lua_Integer luapas_luaL_optint(Plua_State L,LongInt n,lua_Integer d)
{
    lua_Integer lual_optint_result;
    lual_optint_result = luaL_optinteger(L, n, d);
    return lual_optint_result;
};
lua_Integer luapas_luaL_checklong(Plua_State L,LongInt n)
{
    lua_Integer lual_checklong_result;
    lual_checklong_result = luaL_checkinteger(L, n);
    return lual_checklong_result;
};
lua_Integer luapas_luaL_optlong(Plua_State L,LongInt n,lua_Integer d)
{
    lua_Integer lual_optlong_result;
    lual_optlong_result = luaL_optinteger(L, n, d);
    return lual_optlong_result;
};
PChar luapas_luaL_typename(Plua_State L,LongInt idx)
{
    PChar lual_typename_result;
    lual_typename_result = lua_typename(L, lua_type(L, idx));
    return lual_typename_result;
};
LongInt luapas_luaL_dofile(Plua_State L,PChar fn)
{
    LongInt lual_dofile_result;
    lual_dofile_result = luaL_loadfile(L, fn);
    if(lual_dofile_result == 0)
    {
        lual_dofile_result = lua_pcall(L, 0, 0, 0);
    }
    return lual_dofile_result;
};
LongInt luapas_luaL_dostring(Plua_State L,PChar s)
{
    LongInt lual_dostring_result;
    lual_dostring_result = luaL_loadstring(L, s);
    if(lual_dostring_result == 0)
    {
        lual_dostring_result = lua_pcall(L, 0, 0, 0);
    }
    return lual_dostring_result;
};
void luapas_luaL_getmetatable(Plua_State L,PChar n)
{
    lua_getfield(L, LUA_REGISTRYINDEX, n);
};
void luapas_luaL_addchar(PluaL_Buffer B,char c)
{
    if(!(B->p < (B->buffer + LUAL_BUFFERSIZE)))
    {
        luaL_prepbuffer(B);
    }
    (*B->p) = c;
    ++B->p;
};
void luapas_luaL_putchar(PluaL_Buffer B,char c)
{
    luapas_luaL_addchar(B, c);
};
void luapas_luaL_addsize(PluaL_Buffer B,LongInt n)
{
    B->p += n;
};
LongInt luapas_lua_ref(Plua_State L,boolean lock)
{
    LongInt lua_ref_result;
    if(lock)
    {
        lua_ref_result = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    else
    {
        lua_pushstring(L, "unlocked references are obsolete");
        lua_error(L);
        lua_ref_result = 0;
    }
    return lua_ref_result;
};
void luapas_lua_unref(Plua_State L,LongInt ref)
{
    luaL_unref(L, LUA_REGISTRYINDEX, ref);
};
void luapas_lua_getref(Plua_State L,LongInt ref)
{
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
};
