
#include "NoFirePlant.h"

CNoFirePlant::CNoFirePlant(float x, float y, CGameObject* pipe):CGameObject(x, y)
{
	minY = y;
	maxY = y - NO_FIRE_GREEN_PLANT_HEIGHT;
	this->pipe = pipe;
	SetState(BROWN_GOOMBA_STATE_WALKING_LEFT);
}
void CNoFirePlant::SetState(int state)
{

	switch (state)
	{
	case NO_FIRE_GREEN_PLANT_STATE_HIDE:
		vy = 0;
		hide_start = GetTickCount64();
		break;
	case NO_FIRE_GREEN_PLANT_STATE_RISE:
		vy = -NO_FIRE_GREEN_PLANT_VERTICAL_SPEED;
		break;
	case NO_FIRE_GREEN_PLANT_STATE_ATTACK:
		attack_start = GetTickCount64();
		vy = 0;
		break;
	case NO_FIRE_GREEN_PLANT_STATE_DOWN:
		vy = NO_FIRE_GREEN_PLANT_VERTICAL_SPEED;
		break;
	case NO_FIRE_GREEN_PLANT_STATE_DIE:
		vy = 0;
		break;
	}
	CGameObject::SetState(state);
}
void CNoFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == NO_FIRE_GREEN_PLANT_STATE_DIE)
	{
		isDeleted = true;
		return;
	}
	switch (state)
	{
	case NO_FIRE_GREEN_PLANT_STATE_HIDE:
		if (GetTickCount64() - hide_start > HIDE_DURATION)
		{
			hide_start = -1;
			SetState(NO_FIRE_GREEN_PLANT_STATE_RISE);
		}
		break;
	case NO_FIRE_GREEN_PLANT_STATE_RISE:
		if (y >= maxY)
		{
			y = maxY;
			SetState(NO_FIRE_GREEN_PLANT_STATE_ATTACK);
		}
		break;
	case NO_FIRE_GREEN_PLANT_STATE_ATTACK:
		if (GetTickCount64() - attack_start > ATTACK_DURATION)
		{
			attack_start = -1;
			SetState(NO_FIRE_GREEN_PLANT_STATE_DOWN);
		}
		break;
	case NO_FIRE_GREEN_PLANT_STATE_DOWN:
		if (y <= minY)
		{
			y = minY;
			SetState(NO_FIRE_GREEN_PLANT_STATE_HIDE);
		}
		break;
	}
	y += vy * dt;
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CNoFirePlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CNoFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CNoFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - NO_FIRE_GREEN_PLANT_WIDTH / 2;
	top = y - NO_FIRE_GREEN_PLANT_HEIGHT / 2;
	right = left + NO_FIRE_GREEN_PLANT_WIDTH;
	bottom = top + NO_FIRE_GREEN_PLANT_HEIGHT;
}

void CNoFirePlant::Render()
{
	int aniId = NO_FIRE_GREEN_PLANT_ANI_ID;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}


