#include "Coin.h"


void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == BOUNCE_COIN)
	{
		y += vy * dt;
		vy += ACCEL_GRAVITY * dt;
		if (vy >= 0)
			isDeleted = true;
	}
}
void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}