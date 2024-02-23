#include "spLua.h"

#include <fstream>
#include <sstream>

spLua::spLua()
	: L(lua_open())
{
	luaL_openlibs(this->L);
}

spLua::~spLua()
{
	lua_close(this->L);
}

int spLua::compile(const std::string& code)
{
	return luaL_loadbuffer(this->L, code.c_str(), code.length(), "LuaState");
}

int spLua::loadFile(const std::string& filepath, const std::vector<std::string>& dependencies)
{
	std::fstream file(filepath);
	std::stringstream sstream;
	for (const auto& dep : dependencies)
	{
		sstream << "require(\"../../" << dep << "\")\n";
	}
	sstream << file.rdbuf();
	printf("%s\n", sstream.str().c_str());
	return this->compile(sstream.str().c_str());
}

int spLua::call()
{
	return lua_pcall(this->L, 0, 0, 0);
}
