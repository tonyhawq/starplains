#pragma once

#include <string>
#include <vector>
#include <lua.hpp>

#define sp_iterate_table(L) 	lua_pushnil(L);\
							while (lua_next(L, -2))

class spLua
{
public:
	spLua();
	~spLua();
	int compile(const std::string& code);
	int loadFile(const std::string& filepath, const std::vector<std::string>& dependencies);
	int call();
	void reset();

	lua_State* L;
private:
	std::string loadedTable;
};
