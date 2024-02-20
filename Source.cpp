#include <SDL_gpu.h>
#include <vector>

#include "Game/BoundingBox.h"

int main(int argc, char* argv[])
{
	GPU_Target* targ = GPU_Init(1280, 720, GPU_DEFAULT_INIT_FLAGS);
	std::vector<OBB> boxes;
	for (int i = 0; i < 50; i++)
	{
		boxes.push_back(OBB({ float(rand() % 1280), float(rand() % 720) }, { float(rand() % 50), float(rand() % 50) }, maf::deg_to_rad_f * float(rand() % 360)));
	}
	OBB mouse = OBB({ 0,0 }, { 5,5 }, 0);
	OBB* holding = NULL;
	bool mouseDown = false;
	bool RMB = false;
	bool mouseOff = false;
	while (true)
	{
		GPU_Clear(targ);
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		SDL_Event e;
		mouseOff = false;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return 0;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					mouseDown = true;
				}
				else
				{
					RMB = true;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (mouseDown)
				{
					mouseOff = true;
				}
				RMB = false;
				mouseDown = false;
			}
			else if (e.type == SDL_MOUSEWHEEL)
			{
				if (holding)
				{
					holding->rotate(e.wheel.preciseY / 10);
				}
			}
		}
		if (mouseOff)
		{
			holding = NULL;
		}
		mouse.setPos({ (float)x, (float)y });
		GPU_Rectangle(targ, mouse.topLeft().x, mouse.topLeft().y, mouse.bottomRight().x, mouse.bottomRight().y, { 0, 255, 0, 255 });
		GPU_Rectangle(targ, mouse.topLeft().x, mouse.topLeft().y, mouse.topLeft().x + mouse.getDim().x, mouse.topLeft().y + mouse.getDim().y, { 0, 0, 255, 255 });
		GPU_Polygon(targ, 4, (float*)(&mouse.getCorners()), { 255, 0, 0, 255 });
		for (auto& a : boxes)
		{
			const OBB* other = NULL;
			bool collides = false;
			for (const auto& b : boxes)
			{
				if (&a == &b)
				{
					continue;
				}
				if (a.collides(b))
				{
					collides = true;
					other = &b;
					break;
				}
			}
			maf::fvec2 faces[4] = {
				maf::fvec2{ 0,  1},
				maf::fvec2{-1,  0},
				maf::fvec2{ 0, -1},
				maf::fvec2{ 1,  0}
			};
			for (const auto& face : faces)
			{
				maf::fvec2 normal = {
					(sinf(a.getDir()) * face.x - cosf(a.getDir()) * face.y) * -20,
					(cosf(a.getDir()) * face.x + sinf(a.getDir()) * face.y) * -20
				};
				GPU_Line(targ, a.getPos().x, a.getPos().y, a.getPos().x + normal.x, a.getPos().y + normal.y, {255, 255, 0, 255});
			}
			GPU_Rectangle(targ, a.topLeft().x, a.topLeft().y, a.bottomRight().x, a.bottomRight().y, { 0, 255, 0, 255 });
			GPU_Rectangle(targ, a.topLeft().x, a.topLeft().y, a.topLeft().x + a.getDim().x, a.topLeft().y + a.getDim().y, {0, 0, 255, 255});
			if (collides)
			{
				GPU_PolygonFilled(targ, 4, (float*)(&a.getCorners()), { 255, 0, 0, 255 });
			}
			else
			{
				GPU_Polygon(targ, 4, (float*)(&a.getCorners()), { 255, 0, 0, 255 });
			}
			if (a.collides(mouse) && (mouseDown || RMB) && !holding)
			{
				holding = &a;
			}
		}
		if (holding)
		{
			if (mouseDown)
			{
				holding->setPos(mouse.getPos());
			}
			if (RMB)
			{
				holding->resize((mouse.getPos() - holding->getPos()) * 2.0f);
			}
		}
		GPU_Flip(targ);
	}
	return 0;
}