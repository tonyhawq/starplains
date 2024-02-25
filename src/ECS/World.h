#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <queue>
#include <typeinfo>
#include <functional>

#include "System.h"
#include "Entity.h"
#include "Component.h"
#include "Event.h"
#include "../shared/Timer.h"

namespace ECS
{
	class World
	{
	public:
		World();

		void registerSystem(std::shared_ptr<System::System> system);

		void subscribeTargeted(ComponentType cType, EventType eType, std::function<void(const Entity*, Events::BaseEvent*)> callback);
		void subscribeBroadcast(EventType eType, std::function<void(const Entity*, Events::BaseEvent*)> callback);

		void raiseBroadcast(EventType eType, ECS::Events::BaseEvent* args);
		void raiseEvent(ComponentType cType, EventType eType, ECS::Entity* raised, ECS::Events::BaseEvent* args);

		void update();
	private:
		/// <summary>
		/// list of callback functions as added by subscribeBroadcast();
		/// </summary>
		std::unordered_map<EventType, std::vector<std::function<void(const Entity*, Events::BaseEvent*)>>> broadcastListeners;
		/// <summary>
		/// list of callback functions as added by subscribeTargeted();
		/// </summary>
		std::unordered_map<EventType, std::unordered_map<ComponentType, std::vector<std::function<void(const Entity*, Events::BaseEvent*)>>>> targetedListeners;
		/// <summary>
		/// all entities
		/// </summary>
		Entity* list;
		std::unordered_map<SystemType, std::shared_ptr<System::System>> systems;
		Timer timer;
		size_t tick;
	};
}