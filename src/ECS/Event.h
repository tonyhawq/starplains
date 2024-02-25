#pragma once

namespace ECS
{
	namespace Events
	{
		struct BaseEvent
		{
		
		};
		struct CancellableEvent : BaseEvent
		{
			bool cancelled = false;
		};
	}
}

