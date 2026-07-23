#ifndef LUAU_H
#define LUAU_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Official Roblox Luau Engine C API Definitions
typedef struct lua_State lua_State;

lua_State* luau_newstate(void);
void luau_close(lua_State* L);
int luau_load(lua_State* L, const char* chunkname, const char* data, size_t size, int env);

#ifdef __cplusplus
}
#endif

#endif // LUAU_H
