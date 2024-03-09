#pragma once

#include "InheritBase.h"

#include "../../Components/PrintComponent.h"
#include "../../Components/PrintTickComponent.h"

#define sp_LoaderPackage_Base(prototype, componentType, lL) if (componentType == NULL) { /* pass */ }
#define sp_LoaderPackage_Push(toPush, componentToPush) toPush.components.push_back((ECS::Component*)componentToPush)

#define sp_LoaderPackage_Print(prototype, componentType, lL) sp_Package_I(componentType, "Print")\
{\
	ECS::Components::PrintComponent* newComp = new ECS::Components::PrintComponent;\
	lua_getfield(lL, -2, "string");\
	newComp->string = lua_tostring(lL, -1);\
	lua_pop(lL, -1);\
	sp_LoaderPackage_Push(prototype, newComp);\
}

#define sp_LoaderPackage_PrintTick(prototype, componentType, lL) sp_Package_I(componentType, "PrintTick")\
{\
	ECS::Components::PrintTickComponent* newComp = new ECS::Components::PrintTickComponent;\
	sp_LoaderPackage_Push(prototype, newComp);\
}
