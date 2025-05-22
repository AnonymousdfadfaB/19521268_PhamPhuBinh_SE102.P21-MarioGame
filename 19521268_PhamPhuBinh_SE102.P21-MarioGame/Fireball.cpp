#pragma once
#pragma once

#include "GameObject.h"
#include "Fireball.h"
#include "Animation.h"
#include "Animations.h"



void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	//CCollision::GetInstance()->Process(this, dt, coObjects);
	/*
	if (vy >= 0)
	{
		isDeleted = true;
	}
	*/

}
void CFireball::OnNoCollision(DWORD dt)
{

};
void CFireball::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CFireball::Render()
{

	CAnimations* anis = CAnimations::GetInstance();
	anis->Get(FIREBALL_ANI_ID)->Render(x, y);
}

void CFireball::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_WIDTH / 2;
	t = y - FIREBALL_HEIGHT / 2;
	r = l + FIREBALL_WIDTH;
	b = t + FIREBALL_HEIGHT;
}
