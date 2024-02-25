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
	world.registerSystem(std::make_shared<ECS::System::PrintSystem>(&world), typeid(ECS::System::PrintSystem).hash_code());
	world.registerSystem(std::make_shared<ECS::System::PrintTickSystem>(&world), typeid(ECS::System::PrintTickSystem).hash_code());
	for (int i = 0; i < 10; i++)
	{
		ECS::Entity* ent = world.createEntity();
		std::shared_ptr<ECS::Component> comp = world.addComponentToEntity(ent, std::make_shared<ECS::Components::PrintComponent>(), ECS::Components::PrintComponent::type);
		ECS::Components::PrintComponent* concrete = (ECS::Components::PrintComponent*)comp.get();
		concrete->string = "Hello World! " + std::to_string(i);
	}
	ECS::Entity* ent = world.createEntity();
	std::shared_ptr<ECS::Component> comp = world.addComponentToEntity(ent, std::make_shared<ECS::Components::PrintTickComponent>(), ECS::Components::PrintTickComponent::type);
	world.update(); // calls on_tick events
	return 0;
}