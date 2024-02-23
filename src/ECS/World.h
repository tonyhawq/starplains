#pragma once

#include <vector>

#include "System.h"
#include "Entity.h"
#include "Component.h"

namespace ECS
{
	class World
	{
	public:

	private:
		std::vector<ECS::System*> systems;
	};
}