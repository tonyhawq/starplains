#include "Entity.h"

#include "World.h"

ECS::Entity::Entity(World* world, UUID_t id)
	: world(world), next(NULL), UUID(id)
{
	_ASSERT(world);
}

template <class T>
T* ECS::Entity::getComponent()
{
	ComponentType typeID = typeid(T).hash_code();
	if (!this->components.count(typeID))
	{
		return NULL;
	}
	return this->components[typeID];
}