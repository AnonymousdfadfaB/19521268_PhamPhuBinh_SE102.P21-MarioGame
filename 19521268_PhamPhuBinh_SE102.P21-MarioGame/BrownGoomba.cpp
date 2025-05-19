
#include "BrownGoomba.h"

CBrownGoomba::CBrownGoomba(float x, float y) :CGameObject(x, y)
{

	die_start = -1;
	SetState(BROWN_GOOMBA_STATE_WALKING_LEFT);
}
void CBrownGoomba::SetState(int state)
{

	switch (state)
	{
	case BROWN_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (BROWN_GOOMBA_BBOX_HEIGHT - BROWN_GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		break;
	case BROWN_GOOMBA_STATE_WALKING_LEFT:
		vx = -BROWN_GOOMBA_WALKING_SPEED;
		nx = -1;
		break;
	case BROWN_GOOMBA_STATE_WALKING_RIGHT:	
		vx = BROWN_GOOMBA_WALKING_SPEED;
		nx = 1;
		break;
	}
	CGameObject::SetState(state);
}
void CBrownGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += BROWN_GOOMBA_GRAVITY * dt;

	if ((state == BROWN_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > BROWN_GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
		CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CBrownGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBrownGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
void CBrownGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BROWN_GOOMBA_STATE_DIE)
	{
		left = x - BROWN_GOOMBA_BBOX_WIDTH / 2;
		top = y - BROWN_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + BROWN_GOOMBA_BBOX_WIDTH;
		bottom = top + BROWN_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - BROWN_GOOMBA_BBOX_WIDTH / 2;
		top = y - BROWN_GOOMBA_BBOX_HEIGHT / 2;
		right = left + BROWN_GOOMBA_BBOX_WIDTH;
		bottom = top + BROWN_GOOMBA_BBOX_HEIGHT;
	}
}

void CBrownGoomba::Render()
{
	int aniId = ID_ANI_BROWN_GOOMBA_WALKING;
	if (state == BROWN_GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_BROWN_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}


