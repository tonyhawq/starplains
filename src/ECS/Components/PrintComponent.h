#pragma once

#include <string>

#include "../Component.h"

namespace ECS
{
	namespace Components
	{
		struct PrintComponent : Component
		{
			std::string string;
			static size_t type;
		};
	}
}