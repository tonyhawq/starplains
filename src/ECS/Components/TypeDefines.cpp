#include "PrintComponent.h"
#include "PrintTickComponent.h"

#include <typeinfo>

using namespace ECS::Components;

#define TYPE(ARGS) size_t ARGS::type = typeid( ARGS ).hash_code()

TYPE(PrintComponent);
TYPE(PrintTickComponent);
