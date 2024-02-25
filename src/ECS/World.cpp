#include "World.h"
#include "Events/Shared.h"

ECS::World::World()
	: list(NULL), tick(0)
{

}


ECS::Entity* ECS::World::createEntity()
{
	if (!this->list)
	{
		this->list = new Entity(this, currentUUID++);
	}
	else
	{
		Entity* next = this->list->next;
		this->list = new Entity(this, currentUUID++);
		this->list->next = next;
	}
	return this->list;
}

#include "Components/PrintComponent.h"

std::shared_ptr<ECS::Component> ECS::World::addComponentToEntity(Entity* entity, std::shared_ptr<Component> component, ComponentType cType)
{
	entity->components[cType] = component;
	this->componentsByOwner[cType][entity->id()] = entity;
	return component;
}

void ECS::World::registerSystem(std::shared_ptr<System::System> system, SystemType sType)
{
	this->systems[sType] = system;
}

void ECS::World::subscribeTargeted(ComponentType cType, EventType eType, EventCallbackFunc callback)
{
	this->targetedListeners[eType][cType].push_back(callback);
}

void ECS::World::subscribeBroadcast(EventType eType, EventCallbackFunc callback)
{
	this->broadcastListeners[eType].push_back(callback);
}

void ECS::World::raiseBroadcast(EventType eType, ECS::Events::BaseEvent* args)
{
	auto& listeners = this->broadcastListeners[eType];
	for (auto& func : listeners)
	{
		func(this, NULL, args);
	}
}

void ECS::World::raiseEvent(ComponentType cType, EventType eType, ECS::Entity* raised, ECS::Events::BaseEvent* args)
{
	auto& listeners = this->targetedListeners[eType][cType];
	for (auto& func : listeners)
	{
		func(this, raised, args);
	}
}

const std::unordered_map<ECS::UUID_t, ECS::Entity*>& ECS::World::getEntitiesOwning(ComponentType cType)
{
	return this->componentsByOwner[cType];
}

void ECS::World::update()
{
	this->tick++;
	this->timer.reset();
	ECS::Events::OnTickEvent e;
	this->raiseBroadcast(ECS::Events::OnTickEvent::type, &e);
	this->timer.time();
}