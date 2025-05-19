#include "RedGoomba.h"

CRedGoomba::CRedGoomba(float x, float y) :CGameObject(x, y)
{
	walk_start = -1;
	die_start = -1;
	isOnPlatform = false;
	number_small_jump = -1;
	level = RED_GOOMBA_LEVEL_WINGED;
	SetState(RED_GOOMBA_STATE_HIGH_JUMP_LEFT);
}
void CRedGoomba::SetState(int state)
{
	if (level == RED_GOOMBA_LEVEL_WINGLESS)
	{
		switch (state)
		{
		case RED_GOOMBA_STATE_WALKING_LEFT:
			vx = -RED_GOOMBA_WALKING_SPEED;
			vy = 0;
			nx = -1;
			break;
		case RED_GOOMBA_STATE_WALKING_RIGHT:
			vx = RED_GOOMBA_WALKING_SPEED;
			vy = 0;
			nx = 1;
			break;
		case RED_GOOMBA_STATE_DIE:
			vx = 0;
			vy = 0;
			die_start = GetTickCount64();
			break;
		}
	} 
	else
	{
		switch (state)
		{
		case RED_GOOMBA_STATE_WALKING_LEFT:
			walk_start = GetTickCount64();
			vx = -RED_GOOMBA_WALKING_SPEED;
			vy = 0;
			nx = -1;
			break;
		case RED_GOOMBA_STATE_WALKING_RIGHT:
			walk_start = GetTickCount64();
			vx = RED_GOOMBA_WALKING_SPEED;
			vy = 0;
			nx = 1;
			break;
		case RED_GOOMBA_STATE_SMALL_JUMP_LEFT:
			if (isOnPlatform)
			{
				vy = -RED_GOOMBA_SMALL_JUMP_SPEED;
				isOnPlatform = false;
			}
			vx = -RED_GOOMBA_WALKING_SPEED;
			nx = -1;
			break;
		case RED_GOOMBA_STATE_SMALL_JUMP_RIGHT:
			if (isOnPlatform)
			{
				vy = -RED_GOOMBA_SMALL_JUMP_SPEED;
				isOnPlatform = false;
			}
			vx = RED_GOOMBA_WALKING_SPEED;
			nx = 1;
			break;
		case RED_GOOMBA_STATE_HIGH_JUMP_LEFT:
			if (isOnPlatform)
			{
				vy = -RED_GOOMBA_HIGH_JUMP_SPEED;
				isOnPlatform = false;
			}
			vx = -RED_GOOMBA_WALKING_SPEED;
			nx = -1;
			break;
		case RED_GOOMBA_STATE_HIGH_JUMP_RIGHT:
			if (isOnPlatform)
			{
				vy = -RED_GOOMBA_HIGH_JUMP_SPEED;
				isOnPlatform = false;
			}
			vx = RED_GOOMBA_WALKING_SPEED;
			nx = 1;
			break;
		case RED_GOOMBA_STATE_DIE:
			vx = 0;
			vy = 0;
			die_start = GetTickCount64();
			break;
		}
	}
	CGameObject::SetState(state);
}
void CRedGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += RED_GOOMBA_GRAVITY * dt;


	if ((state == RED_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > RED_GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (level == RED_GOOMBA_LEVEL_WINGED)
	{
		if (state == RED_GOOMBA_STATE_WALKING_LEFT || state == RED_GOOMBA_STATE_WALKING_RIGHT)
		{
			if (GetTickCount64() - walk_start > WALK_DURATION && isOnPlatform)
			{
				walk_start = -1; //reset walk_start
				state == RED_GOOMBA_STATE_WALKING_LEFT ? SetState(RED_GOOMBA_STATE_SMALL_JUMP_LEFT) : SetState(RED_GOOMBA_STATE_SMALL_JUMP_RIGHT);
				number_small_jump = 2;
			}
		}
		else if (state == RED_GOOMBA_STATE_SMALL_JUMP_LEFT || state == RED_GOOMBA_STATE_SMALL_JUMP_RIGHT)
		{
			if (number_small_jump >= 0 )
			{
				if (isOnPlatform)
				{
					SetState(state);
					number_small_jump -= 1;
				}
			} 
			else
			{
				if (isOnPlatform)
				{
					state == RED_GOOMBA_STATE_SMALL_JUMP_LEFT ? SetState(RED_GOOMBA_STATE_HIGH_JUMP_LEFT) : SetState(RED_GOOMBA_STATE_HIGH_JUMP_RIGHT);
				}
			}
		}
		else if (state == RED_GOOMBA_STATE_HIGH_JUMP_LEFT || state == RED_GOOMBA_STATE_HIGH_JUMP_RIGHT)
		{
			if (isOnPlatform)
			{
				state == RED_GOOMBA_STATE_HIGH_JUMP_LEFT ? SetState(RED_GOOMBA_STATE_WALKING_LEFT) : SetState(RED_GOOMBA_STATE_WALKING_RIGHT);
				walk_start = GetTickCount64();
			}
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CRedGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == RED_GOOMBA_STATE_DIE)
	{
		left = x - RED_GOOMBA_BBOX_WIDTH / 2;
		top = y - RED_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + RED_GOOMBA_BBOX_WIDTH;
		bottom = top + RED_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - RED_GOOMBA_BBOX_WIDTH / 2;
		top = y - RED_GOOMBA_BBOX_HEIGHT / 2;
		right = left + RED_GOOMBA_BBOX_WIDTH;
		bottom = top + RED_GOOMBA_BBOX_HEIGHT;
	}
}

void CRedGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRedGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (level == RED_GOOMBA_LEVEL_WINGLESS)
	{
		if (e->ny > 0)
		{
			vy = 0;

		}
		else if (e->ny < 0)
		{
			isOnPlatform = true;
			vy = 0;
		}
		else if (e->nx != 0)
		{
			if (state == RED_GOOMBA_STATE_WALKING_LEFT)
			{
				SetState(RED_GOOMBA_STATE_WALKING_RIGHT);
			}
			else if (state == RED_GOOMBA_STATE_WALKING_RIGHT)
			{
				SetState(RED_GOOMBA_STATE_WALKING_LEFT);
			}
		}
	}
	else
	{
		if (e->ny > 0)
		{
			vy = 0;

		}
		else if (e->ny < 0)
		{
			isOnPlatform = true;
			vy = 0;
		}
		else if (e->nx != 0)
		{
			if (state == RED_GOOMBA_STATE_WALKING_LEFT)
			{
				SetState(RED_GOOMBA_STATE_WALKING_RIGHT);
			}
			else if (state == RED_GOOMBA_STATE_WALKING_RIGHT)
			{
				SetState(RED_GOOMBA_STATE_WALKING_LEFT);
			}
			else if (state == RED_GOOMBA_STATE_SMALL_JUMP_LEFT)
			{
				SetState(RED_GOOMBA_STATE_SMALL_JUMP_RIGHT);
			} 
			else if (state == RED_GOOMBA_STATE_SMALL_JUMP_RIGHT)
			{
				SetState(RED_GOOMBA_STATE_SMALL_JUMP_LEFT);
			}
			else if (state == RED_GOOMBA_STATE_HIGH_JUMP_LEFT)
			{
				SetState(RED_GOOMBA_STATE_HIGH_JUMP_RIGHT);
			}
			else if (state == RED_GOOMBA_STATE_HIGH_JUMP_RIGHT)
			{
				SetState(RED_GOOMBA_STATE_HIGH_JUMP_LEFT);
			}
		}
	}

}

void CRedGoomba::Render()
{
	int aniId;
	if (level == RED_GOOMBA_LEVEL_WINGLESS)
	{
		if (state == RED_GOOMBA_STATE_DIE)
			aniId = ID_ANI_RED_GOOMBA_DIE;
		else if (state == RED_GOOMBA_STATE_WALKING_LEFT || state == RED_GOOMBA_STATE_WALKING_RIGHT)
			aniId = ID_ANI_WINGLESS_RED_GOOMBA_WALKING;
	}
	else
	{
		if (state == RED_GOOMBA_STATE_HIGH_JUMP_RIGHT || state == RED_GOOMBA_STATE_HIGH_JUMP_LEFT)
		{
			aniId = ID_ANI_RED_GOOMBA_HIGH_JUMP;
		} 
		else if (state == RED_GOOMBA_STATE_DIE)
			aniId = ID_ANI_RED_GOOMBA_DIE;
		else
		{
			aniId = ID_ANI_WINGED_RED_GOOMBA_WALKING_AND_SMALL_JUMP;
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
