#pragma once

#include <optional>

#include "../Entity.h"
#include "../../shared/spLua/spLua.h"
#include "LoaderPackages/blob.h"

namespace ECS
{
	namespace Prototypes
	{
		struct EntityPrototype
		{
			std::string name = "uninitalized";
			size_t id = 0;
			std::vector<Component*> components;
		};

		
		
		class PrototypeLoader
		{
		public:
			void loadContent();

			const ECS::Entity* getPrototype(size_t id);
			const ECS::Entity* getPrototype(const std::string& name);
		private:
			void _loadPrototype();
			void _loadComponents(EntityPrototype& ptype);
			void _loadComponent(EntityPrototype& ptype, const char* ctype);

			spLua lua;

			std::vector<Entity> prototypes;
			std::unordered_map<std::string, size_t> name_map;
		};
	}
}
