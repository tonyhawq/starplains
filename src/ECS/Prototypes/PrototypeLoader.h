#pragma once

#include <optional>

#include "../Entity.h"
#include "../../shared/spLua/spLua.h"

namespace ECS
{
	namespace Prototypes
	{
		class PrototypeLoader
		{
		public:
			void loadContent();

			const ECS::Entity* getPrototype(size_t id);
			const ECS::Entity* getPrototype(const std::string& name);
		private:
			spLua lua;

			std::vector<Entity> prototypes;
			std::unordered_map<std::string, size_t> name_map;
		};
	}
}
