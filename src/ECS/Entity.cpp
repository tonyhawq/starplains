#include "Entity.h"

#include "World.h"

ECS::Entity::Entity(World* world, UUID_t id)
	: world(world), next(NULL), UUID(id)
{
	_ASSERT(world);
}

ECS::Component* ECS::Entity::getComponent(ComponentType cType)
{
	if (!this->components.count(cType))
	{
		return NULL;
	}
	return this->components[cType].get();
}