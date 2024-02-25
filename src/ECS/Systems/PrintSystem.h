#pragma once

#include "../System.h"
#include "../Components/PrintComponent.h"
#include "../Events/Shared.h"
#include "../World.h"

namespace ECS
{
	namespace System
	{
		class PrintSystem : public System
		{
		public:
			inline PrintSystem(World* world)
				:System(world)
			{
				world->subscribeBroadcast(ECS::Events::OnTickEvent::type, OnTick);
			}
			
			inline static void OnTick(const Entity* entity, ECS::Events::BaseEvent* args)
			{

			}
		private:

		};
	}
}
