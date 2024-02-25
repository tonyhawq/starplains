#pragma once

#include <unordered_map>

#include "Defines.h"
#include "Component.h"

namespace ECS
{
	class Entity
	{
	public:
		Entity* next = NULL;

		template<class T>
		T* getComponent();
	private:
		std::unordered_map<ComponentType, Component> components;
	};
}

