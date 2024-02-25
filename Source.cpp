#include <SDL_gpu.h>
#include <vector>
#include <chrono>
#include <typeinfo>

#include "src/ECS/World.h"

#include "src/ECS/Systems/PrintSystem.h"
#include "src/ECS/Systems/PrintTickSystem.h"

int main(int argc, char* argv[])
{
	ECS::World world;
	world.registerSystem(std::make_shared<ECS::System::PrintSystem>(&world));
	world.registerSystem(std::make_shared<ECS::System::PrintTickSystem>(&world));
	ECS::Entity* ent = world.createEntity();
	world.addComponentToEntity(ent, std::make_shared<ECS::Components::PrintComponent>());
	world.update(); // calls on_tick events
	return 0;
}