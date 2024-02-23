#include <SDL_gpu.h>
#include <vector>
#include <chrono>
#include <box2d.h>

#include "src/shared/maf.h"
#include "src/shared/Timer.h"
#include "src/shared/spLua/spLua.h"

int main(int argc, char* argv[])
{
	spLua lua;
	if (lua.loadFile("content/prototypes/entry.lua", {"content/lualib/core"}))
	{
		printf("%s", lua_tostring(lua.L, -1));
		lua_pop(lua.L, 0);
	}
	if (lua.call())
	{
		printf("%s", lua_tostring(lua.L, -1));
		lua_pop(lua.L, 0);
	}
	return 0;
}