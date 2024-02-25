#pragma once

#include "../Event.h"

namespace ECS
{
	namespace Events
	{
		struct OnTickEvent : BaseEvent
		{
			size_t tick = 0;
			static size_t type;
		};
	}
}
