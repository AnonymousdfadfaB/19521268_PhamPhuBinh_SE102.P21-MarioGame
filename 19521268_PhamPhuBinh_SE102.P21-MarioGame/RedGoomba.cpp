#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int type) :CGameObject(x, y)
{

	this->type = type;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING_LEFT);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if (state == GOOMBA_STATE_WALKING_LEFT)
		{
			SetState(GOOMBA_STATE_WALKING_RIGHT);
		}
		else if (state == GOOMBA_STATE_WALKING_RIGHT)
		{
			SetState(GOOMBA_STATE_WALKING_LEFT);
		}
		if (type == GOOMBA_TYPE_RED)
		{
			if (state == GOOMBA_STATE_WALKING_JUMP_LEFT)
			{
				SetState(GOOMBA_STATE_WALKING_JUMP_RIGHT);
			}
			else if (state == GOOMBA_STATE_WALKING_JUMP_RIGHT)
			{
				SetState(GOOMBA_STATE_WALKING_JUMP_LEFT);
			}
		}
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += GOOMBA_GRAVITY * dt;


	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (type == GOOMBA_TYPE_RED)
		aniID = GetAniIdGoombaRed();
	else
		aniID = GetAniIdGoombaBrown();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CGoomba::SetState(int state)
{
	if (type == GOOMBA_TYPE_RED)
	{
		switch (state)
		{
		case GOOMBA_STATE_WALKING_JUMP_LEFT:
			vx = -GOOMBA_WALKING_JUMP_SPEED;
			vy = -GOOMBA_WALKING_JUMP_SPEED;
			break;
		case GOOMBA_STATE_WALKING_JUMP_RIGHT:
			vx = GOOMBA_WALKING_JUMP_SPEED;
			vy = -GOOMBA_WALKING_JUMP_SPEED;
			break;
		}
	}
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING_LEFT:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_WALKING_RIGHT:
		vx = GOOMBA_WALKING_SPEED;
		break;
	}

	CGameObject::SetState(state);
}
int CGoomba::GetAniIdGoombaBrown()
{
	if (state == GOOMBA_STATE_DIE)
		return ID_ANI_GOOMBA_BROWN_DIE;
	else if (state == GOOMBA_STATE_WALKING_LEFT || state == GOOMBA_STATE_WALKING_RIGHT)
		return ID_ANI_GOOMBA_BROWN_WALKING;
}
int CGoomba::GetAniIdGoombaRed()
{
	if (state == GOOMBA_STATE_DIE)
		return ID_ANI_GOOMBA_RED_DIE;
	else if (state == GOOMBA_STATE_WALKING_LEFT || state == GOOMBA_STATE_WALKING_RIGHT)
		return ID_ANI_GOOMBA_RED_WALKING;
	else if (state == GOOMBA_STATE_WALKING_JUMP_LEFT || state == GOOMBA_STATE_WALKING_JUMP_RIGHT)
		return ID_ANI_GOOMBA_WALKING_JUMP_LEFT;
	else if (state == GOOMBA_STATE_WALKING_JUMP_RIGHT)
		return ID_ANI_GOOMBA_WALKING_JUMP_RIGHT;
}