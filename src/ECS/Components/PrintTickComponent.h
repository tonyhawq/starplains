#pragma once

#include "../Component.h"

namespace ECS
{
	namespace Components
	{
		struct PrintTickComponent : Component
		{
			static size_t type;
		};
	}
}
