#include "Mushroom.h"


void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += MUSHROOM_GRAVITY * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	/*
	if (vy >= 0)
	{
		isDeleted = true;
	}
	*/

}
void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
	}
}
void CMushroom::Render()
{

	CSprites* sprites = CSprites::GetInstance();
	
	sprites->Get(ID_SPRI_RED_MUSHROOM)->Draw(x, y);
	
	//RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}