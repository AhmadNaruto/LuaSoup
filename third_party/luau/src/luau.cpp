#include "luau.h"
#include <cstdlib>

lua_State* luau_newstate(void) {
    return nullptr;
}

void luau_close(lua_State* L) {
    (void)L;
}

int luau_load(lua_State* L, const char* chunkname, const char* data, size_t size, int env) {
    (void)L; (void)chunkname; (void)data; (void)size; (void)env;
    return 0;
}
