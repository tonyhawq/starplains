#pragma once

namespace ECS
{
	class World;

	namespace System
	{
		class System
		{
		public:
			System(World* world);
		private:
			World* world;
		};
	}
}
