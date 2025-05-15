#include "Koopa.h"
#include "Goomba.h"
#include "QuestionBlock.h"
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
#include "Mario.h"
CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	SetState(KOOPA_STATE_WALKING_RIGHT);
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
		if (e->ny != 0)
			vy = 0;
		else if (e->nx != 0)
		{
			//vx = -vx;
			if (state == KOOPA_STATE_WALKING_LEFT)
				SetState(KOOPA_STATE_WALKING_RIGHT);
			else if (state == KOOPA_STATE_WALKING_RIGHT)
				SetState(KOOPA_STATE_WALKING_LEFT);
			else if (state == KOOPA_STATE_SHELL_SLIDING_LEFT)
				SetState(KOOPA_STATE_SHELL_SLIDING_RIGHT);
			else if (state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
				SetState(KOOPA_STATE_SHELL_SLIDING_LEFT);
		}
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);

}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	ULONGLONG now = GetTickCount64();
	if (state == KOOPA_STATE_SHELL && now - shell_start > KOOPA_RETURN_WALKING_INTERVAL)
	{
		(int)now % 2 == 0 ? SetState(KOOPA_STATE_WALKING_RIGHT) : SetState(KOOPA_STATE_WALKING_LEFT);
	}
	/*
	else if (state == KOOPA_STATE_DIE)
	{
		if (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT)
			isDeleted = true;
	}*/
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_SLIDING_LEFT || state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
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
		if (anotherKoopa->IsShellState() || anotherKoopa->IsShellSlidingLeftState() || anotherKoopa->IsShellSlidingRightState())
		{
			vx = -vx;
			if (anotherKoopa->IsShellSlidingLeftState())
				anotherKoopa->ToShellSlidingRight();
			else if (anotherKoopa->IsShellSlidingRightState())
				anotherKoopa->ToShellSlidingLeft();
		}
		else 
			anotherKoopa->Delete(); //temporary
	}
}
void CKoopa::Render()
{
	int aniId;
	if (state == KOOPA_STATE_WALKING_LEFT)
	{
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}
	else if (state == KOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_SLIDING_LEFT)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_SLIDING_RIGHT)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		ax = 0;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		if (this->state == KOOPA_STATE_SHELL)
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		if (this->state == KOOPA_STATE_SHELL)
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2;
		break;
	case KOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ax = 0;
		if (this->state == KOOPA_STATE_WALKING_LEFT || this->state == KOOPA_STATE_WALKING_RIGHT)
			y += (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2;
		break;
	case KOOPA_STATE_SHELL_SLIDING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_SLIDING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		break;
	}
	this->state = state;
}
