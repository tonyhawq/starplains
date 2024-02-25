#pragma once

namespace ECS
{
	class Entity;

	/// <summary>
	/// Components strictly have NO functions or logic inside of them. All component related things are handled by Systems.
	/// </summary>
	struct Component
	{
		Entity* parent;
	};
}
