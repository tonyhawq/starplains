#include "Entity.h"

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