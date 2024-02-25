#include "Shared.h"

#include <typeinfo>

size_t ECS::Events::OnTickEvent::type = typeid(ECS::Events::OnTickEvent).hash_code();
