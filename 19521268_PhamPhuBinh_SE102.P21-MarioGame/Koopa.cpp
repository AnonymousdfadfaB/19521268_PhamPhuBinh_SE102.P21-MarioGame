#include "Koopa.h"
#include "BrownGoomba.h"
#include "QuestionBlock.h"
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
//#include "Mario.h"
CKoopa::CKoopa(float x, float y, float patrolDistance, int state, int type) :CGameObject(x, y)
{
	isHeld = false;
	die_start = -1;
	shell_start = -1;
	if (type == KOOPA_TYPE_RED)
	{
		leftBoundary = x - patrolDistance / 2;
		rightBoundary = x + patrolDistance / 2;
	}
	this->x = x;
	this->y = y;
	this->type = type;
	SetState(state);
}
void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += KOOPA_GRAVITY * dt;
	ULONGLONG now = GetTickCount64();
	if (state == KOOPA_STATE_DIE && GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT)
	{
		isDeleted = true;
	}
	if (state == KOOPA_STATE_SHELL && now - shell_start > KOOPA_RETURN_WALKING_INTERVAL)
	{
		(int)now % 2 == 0 ? SetState(KOOPA_STATE_WALKING_RIGHT) : SetState(KOOPA_STATE_WALKING_LEFT);
	}
	if (isHeld == true && state != KOOPA_STATE_SHELL)
		isHeld = false;
	if (type == KOOPA_TYPE_RED && (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT))
	{
		if (x <= leftBoundary)
		{
			if (state == KOOPA_STATE_WALKING_LEFT)
				SetState(KOOPA_STATE_WALKING_RIGHT);
		}
		else if (x >= rightBoundary)
		{
			if (state == KOOPA_STATE_WALKING_RIGHT)
				SetState(KOOPA_STATE_WALKING_LEFT);
		}
	}
	if (isHeld)
	{
		vx = 0;
		vy = 0;
		nx = 0;
	} 
	else if (state == KOOPA_STATE_DIE)
		OnNoCollision(dt);
	else
		CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL ||state == KOOPA_STATE_SHELL_SLIDING_LEFT || state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		left = x - KOOPA_SHELL_BBOX_WIDTH / 2;
		top = y - KOOPA_SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPA_SHELL_BBOX_WIDTH;
		bottom = top + KOOPA_SHELL_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
		x += vx * dt;
		y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking()) {
		if (e->ny < 0)
		{
			if (state == KOOPA_STATE_JUMP_LEFT || state == KOOPA_STATE_JUMP_RIGHT)
			{
				vy = -KOOPA_JUMP_SPEED;
			}
			else
				vy = 0;
		}
		else if (e->ny > 0)
		{
			vy = 0;
		}
		else
		{
			if (state == KOOPA_STATE_WALKING_LEFT)
				SetState(KOOPA_STATE_WALKING_RIGHT);
			else if (state == KOOPA_STATE_WALKING_RIGHT)
				SetState(KOOPA_STATE_WALKING_LEFT);
			else if (state == KOOPA_STATE_SHELL_SLIDING_LEFT)
				SetState(KOOPA_STATE_SHELL_SLIDING_RIGHT);
			else if (state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
				SetState(KOOPA_STATE_SHELL_SLIDING_LEFT);
			else if (state == KOOPA_STATE_JUMP_LEFT)
				SetState(KOOPA_STATE_JUMP_RIGHT);
			else if (state == KOOPA_STATE_JUMP_RIGHT)
				SetState(KOOPA_STATE_JUMP_LEFT);
		}
	}
	if (dynamic_cast<CBrownGoomba*>(e->obj))
		OnCollisionWithBrownGoomba(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
}


void CKoopa::OnCollisionWithBrownGoomba(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_SLIDING_LEFT || state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		CBrownGoomba* brownGoomba = dynamic_cast<CBrownGoomba*>(e->obj);
		if (brownGoomba->GetState() != BROWN_GOOMBA_STATE_DIE)
		{
			brownGoomba->SetState(BROWN_GOOMBA_STATE_DIE);
		}
	}
}
void CKoopa::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_SLIDING_LEFT || state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);

		if (!questionBlock->IsHit() && e->nx != 0)
			questionBlock->Hit();
	}

}
void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_SLIDING_LEFT || state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		CKoopa* anotherKoopa = dynamic_cast<CKoopa*>(e->obj);
		int anotherKoopaState = anotherKoopa->GetState();
		if (anotherKoopaState == KOOPA_STATE_SHELL || anotherKoopaState == KOOPA_STATE_SHELL_SLIDING_LEFT || anotherKoopaState == KOOPA_STATE_SHELL_SLIDING_RIGHT)
		{
			state == KOOPA_STATE_SHELL_SLIDING_LEFT ? KOOPA_STATE_SHELL_SLIDING_RIGHT : KOOPA_STATE_SHELL_SLIDING_LEFT;
			if (anotherKoopaState == KOOPA_STATE_SHELL_SLIDING_LEFT)
				anotherKoopa->SetState(KOOPA_STATE_SHELL_SLIDING_RIGHT);
			else if (anotherKoopaState == KOOPA_STATE_SHELL_SLIDING_RIGHT)
				anotherKoopa->SetState(KOOPA_STATE_SHELL_SLIDING_LEFT);
		}
		else if (anotherKoopa->GetState() != KOOPA_STATE_DIE)
			anotherKoopa->SetState(KOOPA_STATE_DIE);
	}
}
void CKoopa::Render()
{
	int aniId;
	if (type == KOOPA_TYPE_RED)
		aniId = GetAniIdRedKoopa();
	else
		aniId = GetAniIdGreenKoopa();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CKoopa::SetState(int state)
{

	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = -KOOPA_DIE_BOUNCE_SPEED;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		nx = -1;
		if (this->state == KOOPA_STATE_SHELL)
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		nx = 1;
		if (this->state == KOOPA_STATE_SHELL)
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2;
		break;
	case KOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		vx = 0;
		vy = 0;
		nx = 0;
		if (this->state == KOOPA_STATE_WALKING_LEFT || this->state == KOOPA_STATE_WALKING_RIGHT)
			y += (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2;
		break;
	case KOOPA_STATE_SHELL_SLIDING_LEFT:
		nx = -1;
		vx = -KOOPA_SHELL_SLIDING_SPEED;
		break;
	case KOOPA_STATE_SHELL_SLIDING_RIGHT:
		nx = 1;
		vx = KOOPA_SHELL_SLIDING_SPEED;
		break;
	case KOOPA_STATE_JUMP_LEFT:
		nx = -1;
		vx = -KOOPA_WALKING_SPEED;
		vy = -KOOPA_JUMP_SPEED;
		break;
	case KOOPA_STATE_JUMP_RIGHT:
		nx = 1;
		vx = KOOPA_WALKING_SPEED;
		vy = -KOOPA_JUMP_SPEED;
		break;
	}
	this->state = state;
}
int CKoopa::GetAniIdRedKoopa()
{
	int aniId;
	if (state == KOOPA_STATE_WALKING_LEFT)
	{
		aniId = ID_ANI_RED_KOOPA_WALKING_LEFT;
	}
	else if (state == KOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_RED_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_SLIDING_LEFT)
	{
		aniId = ID_ANI_RED_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		aniId = ID_ANI_RED_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_JUMP_LEFT)
	{
		aniId = ID_ANI_RED_KOOPA_JUMP_LEFT;
	}
	else if (state == KOOPA_STATE_JUMP_RIGHT)
	{
		aniId = ID_ANI_RED_KOOPA_JUMP_RIGHT;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_RED_KOOPA_DIE;
	}
	return aniId;
}
int CKoopa::GetAniIdGreenKoopa()
{
	int aniId;
	if (state == KOOPA_STATE_WALKING_LEFT)
	{
		aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
	}
	else if (state == KOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_SLIDING_LEFT)
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_JUMP_LEFT)
	{
		aniId = ID_ANI_GREEN_KOOPA_JUMP_LEFT;
	}
	else if (state == KOOPA_STATE_JUMP_RIGHT)
	{
		aniId = ID_ANI_GREEN_KOOPA_JUMP_RIGHT;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_GREEN_KOOPA_DIE;
	}
	return aniId;
}
void CKoopa::HeldByMario()
{
	isHeld = true;
}
int CKoopa::IsCollidable() { return 1; }
int CKoopa::IsBlocking() { return 0; }