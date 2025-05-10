#include "Leaf.h"
#define _USE_MATH_DEFINES
#include <cmath>

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	static float originalX = x;
	static float time = 0.0f;
	time += dt;
	x = originalX + LEAF_AMPLITUDE * sin(3.14 / 2 * time);
	y += vy * dt;
	vy += LEAF_GRAVITY * dt;
	//how to delete leaf
}
void CLeaf::Render()
{

	CSprites* sprites = CSprites::GetInstance();

	sprites->Get(70001)->Draw(x, y);

	//RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}