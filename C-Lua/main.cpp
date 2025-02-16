#include <iostream>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

int main (int argc, char *argv[]) {
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "main.lua");
	lua_getglobal(L, "randomize");
    lua_call(L, 0, 0);

    int in;

    while (true) {
        lua_getglobal(L, "guess");
        lua_call(L, 0, 0);
        std::cin >> in;
        lua_pushnumber(L, in);
        lua_setglobal(L, "g");
        lua_getglobal(L, "check");
        lua_call(L, 0, 1);
        if (lua_toboolean(L, 1) == true) {
            lua_pop(L, 1);
            break;
        } else {
            lua_pop(L, 1);
        }
    }

    lua_close(L);
	return 0;
}
