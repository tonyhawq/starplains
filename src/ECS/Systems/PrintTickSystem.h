#pragma once

#include "../System.h"
#include "../Components/PrintTickComponent.h"
#include "../Events/Shared.h"
#include "../World.h"

namespace ECS
{
	namespace System
	{
		class PrintTickSystem : public System
		{
		public:
			inline PrintTickSystem(World* world)
				: System(world)
			{
				world->subscribeTargeted(ECS::Components::PrintTickComponent::type, ECS::Events::OnTickEvent::type, OnTick);
			}
			inline static void OnTick(const Entity* entity, ECS::Events::BaseEvent* args)
			{
				// just cast ECS::Events::BaseEvent to needed type. in this case, should be ECS::Events::OnTickEvent.
			}
		private:

		};
	}
}