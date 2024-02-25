#include "World.h"
#include "Events/Shared.h"

ECS::World::World()
	: list(NULL), tick(0)
{

}

void ECS::World::registerSystem(std::shared_ptr<System::System> system)
{
	//size_t typeID = typeid(T).hash_code();
	//this->systems[typeID] = std::make_shared<T>(this);
}


void ECS::World::subscribeTargeted(ComponentType cType, EventType eType, std::function<void(const Entity*, Events::BaseEvent*)> callback)
{
	this->targetedListeners[eType][cType].push_back(callback);
}

void ECS::World::subscribeBroadcast(EventType eType, std::function<void(const Entity*, Events::BaseEvent*)> callback)
{
	this->broadcastListeners[eType].push_back(callback);
}

void ECS::World::raiseBroadcast(EventType eType, ECS::Events::BaseEvent* args)
{
	auto& listeners = this->broadcastListeners[eType];
	for (auto& func : listeners)
	{
		func(NULL, args);
	}
}

void ECS::World::raiseEvent(ComponentType cType, EventType eType, ECS::Entity* raised, ECS::Events::BaseEvent* args)
{
	auto& listeners = this->targetedListeners[eType][cType];
	for (auto& func : listeners)
	{
		func(raised, args);
	}
}

void ECS::World::update()
{
	this->tick++;
	this->timer.reset();
	ECS::Events::OnTickEvent e;
	this->raiseBroadcast(typeid(ECS::Events::OnTickEvent).hash_code(), &e);
	this->timer.time();
}