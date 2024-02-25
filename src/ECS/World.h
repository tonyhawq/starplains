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
	using EventCallbackFunc = std::function<void(World*, const Entity*, Events::BaseEvent*)>;

	class World
	{
	public:
		World();

		Entity* createEntity();
		// don't hold onto this pointer, no guarantees where it'll end up
		std::shared_ptr<Component> addComponentToEntity(Entity* entity, std::shared_ptr<Component> component, ComponentType cType);
		
		const std::unordered_map<UUID_t, Entity*>& getEntitiesOwning(ComponentType cType);

		void registerSystem(std::shared_ptr<System::System> system, SystemType sType);

		void subscribeTargeted(ComponentType cType, EventType eType, EventCallbackFunc callback);
		void subscribeBroadcast(EventType eType, EventCallbackFunc callback);

		void raiseBroadcast(EventType eType, ECS::Events::BaseEvent* args);
		void raiseEvent(ComponentType cType, EventType eType, ECS::Entity* raised, ECS::Events::BaseEvent* args);

		void update();
	private:
		/// <summary>
		/// list of callback functions as added by subscribeBroadcast();
		/// </summary>
		std::unordered_map<EventType, std::vector<EventCallbackFunc>> broadcastListeners;
		std::unordered_map<ComponentType, std::unordered_map<UUID_t, Entity*>> componentsByOwner;
		/// <summary>
		/// list of callback functions as added by subscribeTargeted();
		/// </summary>
		std::unordered_map<EventType, std::unordered_map<ComponentType, std::vector<EventCallbackFunc>>> targetedListeners;
		/// <summary>
		/// all entities
		/// </summary>
		Entity* list;
		std::unordered_map<SystemType, std::shared_ptr<System::System>> systems;
		Timer timer;
		size_t tick;
		UUID_t currentUUID = 1;
	};
}