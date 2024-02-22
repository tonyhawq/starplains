#include <SDL_gpu.h>
#include <vector>
#include <chrono>
#include <box2d.h>

#include "maf.h"
#include "Game/Timer.h"

int main(int argc, char* argv[])
{
	GPU_Target* targ = GPU_Init(1280, 720, GPU_INIT_DISABLE_VSYNC);
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -200.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(500.0f, 100.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	Timer timer;
	float conv = 1.0f / -0.1f;
	maf::fvec2 camera;
	while (true)
	{
		timer.reset();
		GPU_Clear(targ);
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				return 0;
				break;
			}
			case SDL_KEYDOWN:
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_w:
				{
					b2Vec2 newOrigin = { 0, 1 };
					world.ShiftOrigin(newOrigin);
					break;
				}
				case SDLK_a:
				{
					b2Vec2 newOrigin = { 1, 0 };
					world.ShiftOrigin(newOrigin);
					break;
				}
				case SDLK_s:
				{
					b2Vec2 newOrigin = { 0, -1 };
					world.ShiftOrigin(newOrigin);
					break;
				}
				case SDLK_d:
				{
					b2Vec2 newOrigin = { -1, 0 };
					world.ShiftOrigin(newOrigin);
					break;
				}
				}
				break;
			}
			}
		}
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Body* iter = world.GetBodyList();
		while (iter)
		{
			b2Fixture* fix = iter->GetFixtureList();
			while (fix)
			{
				b2Shape* shape = fix->GetShape();
				b2Shape::Type shapeTyp = shape->GetType();
				switch (shapeTyp)
				{
				case b2Shape::e_polygon:
				{
					b2PolygonShape* concrete = (b2PolygonShape*)shape;
					b2Vec2* verts = (b2Vec2*)malloc(sizeof(b2Vec2) * concrete->m_count);
					if (!verts)
					{
						return 1;
					}
					for (int i = 0; i < concrete->m_count; i++)
					{
						verts[i] = iter->GetWorldPoint(concrete->m_vertices[i]);
						verts[i] *= conv;
					}
					GPU_Polygon(targ, concrete->m_count, (float*)(verts), { 255, 0, 0, 255 });
					break;
				}
				}
				fix = fix->GetNext();
			}
			iter = iter->GetNext();
		}
		GPU_Flip(targ);
		printf("%f\n", timer.time());
	}
	return 0;
}