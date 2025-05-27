#include "VictoryFlower.h"


void CVictoryFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (alreadyHit)
	{
		y += vy * dt;
	}
}
void CVictoryFlower::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(VICTORYFLOWER_ANI_ID)->Render(x, y);
}

void CVictoryFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VICTORYFLOWER_WIDTH / 2;
	t = y - VICTORYFLOWER_HEIGHT / 2;
	r = l + VICTORYFLOWER_WIDTH;
	b = t + VICTORYFLOWER_HEIGHT;
}