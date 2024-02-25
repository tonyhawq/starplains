#include "PrototypeLoader.h"

void ECS::Prototypes::PrototypeLoader::loadContent()
{
	if (lua.loadFile("content/prototypes/entry.lua", { "content/lualib/core" }))
	{
		printf("%s\n", lua_tostring(lua.L, -1));
		lua_pop(lua.L, 1);
	}
	if (lua.call())
	{
		printf("%s\n", lua_tostring(lua.L, -1));
		lua_pop(lua.L, 1);
	}
} 

const ECS::Entity* ECS::Prototypes::PrototypeLoader::getPrototype(size_t id)
{
	if (id >= this->prototypes.size())
	{
		return NULL;
	}
	return &this->prototypes[id];
}

const ECS::Entity* ECS::Prototypes::PrototypeLoader::getPrototype(const std::string& name)
{
	if (!this->name_map.count(name))
	{
		return NULL;
	}
	return &this->prototypes[this->name_map[name]];
}
