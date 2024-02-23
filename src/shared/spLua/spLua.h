#pragma once

#include <string>
#include <vector>
#include <lua.hpp>

class spLua
{
public:
	spLua();
	~spLua();
	int compile(const std::string& code);
	int loadFile(const std::string& filepath, const std::vector<std::string>& dependencies);
	int call();

	lua_State* L;
private:
	std::string loadedTable;
};
