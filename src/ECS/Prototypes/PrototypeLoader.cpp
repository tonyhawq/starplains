#include "PrototypeLoader.h"

#include "../../shared/logtools.h"

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
	lua_getglobal(lua.L, "data");
	lua_getfield(lua.L, -1, "internal");
	int i = 0;
	sp_iterate_table(lua.L)
	{
		i++;
		printf("loading prototype %i\n", i);
		this->_loadPrototype();
		lua_pop(lua.L, 1);
	}
} 

void ECS::Prototypes::PrototypeLoader::_loadPrototype()
{
	EntityPrototype ptype;
	int i = 0;
	sp_iterate_table(lua.L)
	{
		printf("loading prototype table iteration %i\n", i++);
		lua_pushvalue(lua.L, -2);
		const char* key = lua_tostring(lua.L, -1);
		if (key == "name")
		{
			ptype.name = lua_tostring(lua.L, -2);
		}
		else if (key == "components")
		{
			this->_loadComponents(ptype);
		}
		lua_pop(lua.L, 2);
	}
}

void ECS::Prototypes::PrototypeLoader::_loadComponents(EntityPrototype& ptype)
{
	int i = 0;
	sp_iterate_table(lua.L)
	{
		i++;
		printf("loading component table, component %i\n", i);
		lua_pushvalue(lua.L, -2);
		const char* ctype = lua_tostring(lua.L, -1);
		this->_loadComponent(ptype, ctype);
		lua_pop(lua.L, 2);
	}
}

void ECS::Prototypes::PrototypeLoader::_loadComponent(EntityPrototype& ptype, const char* ctype)
{
	printf("loading component data for %s\n", ctype);
	// who needs typechecking or namespaces when you have macros?
	sp_LoaderPackage_Base(ptype, ctype, lua.L)
	sp_LoaderPackage_Print(ptype, ctype, lua.L)
	sp_LoaderPackage_PrintTick(ptype, ctype, lua.L)
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
