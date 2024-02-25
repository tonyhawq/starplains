#pragma once

#include <unordered_map>
#include <memory>

#include "Defines.h"
#include "Component.h"

namespace ECS
{
	class World;
	class Entity
	{
	public:
		Entity(World* world, UUID_t id);

		Entity* next;

		template<class T>
		T* getComponent();

		inline UUID_t id() { return this->UUID; }
	//private: // why be so secretive?
		World* world;
		std::unordered_map<ComponentType, std::shared_ptr<Component>> components;
		UUID_t UUID;
	};
}

