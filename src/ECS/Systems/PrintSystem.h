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
			
			inline static void OnTick(World* world, const Entity* entity, ECS::Events::BaseEvent* args)
			{
				printf("OnTick called into PrintSystem\n");
				const std::unordered_map<ECS::UUID_t, ECS::Entity*>& components = world->getEntitiesOwning(Components::PrintComponent::type);
				printf("%zu results for id %zu", components.count(1), 1u);
				for (const auto& container : components)
				{
					printf("getting PrintComponent from container\n");
					// i have somehow gotten rid of the const qualifier. how interesting.
					Components::PrintComponent* c = (Components::PrintComponent*)container.second->getComponent(Components::PrintComponent::type);
					printf("%s\n", c->string.c_str());
				}
			}
		private:

		};
	}
}
