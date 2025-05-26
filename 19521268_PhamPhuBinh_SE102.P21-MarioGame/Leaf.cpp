#include "Leaf.h"
#define _USE_MATH_DEFINES
#include <cmath>

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (vy >= 0) 
	{
		time += dt;
		x = originalX + LEAF_AMPLITUDE * sin(2 * PI / LEAF_CYCLE * time);
		vx = 2 * PI / LEAF_CYCLE * LEAF_AMPLITUDE * cos(2 * 3.14 / LEAF_CYCLE * time);
	}
	else
	{
		vx = 0;
	}
	y += vy * dt;
	vy += LEAF_GRAVITY * dt;

	//how to delete leaf
}
void CLeaf::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(LEAF_SPRITE_ID)->Draw(x, y);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}