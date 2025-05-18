#include "Koopa.h"
#include "Goomba.h"
#include "QuestionBlock.h"
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
#include "Mario.h"
CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	isHeld = false;
	die_start = -1;
	//SetState(KOOPA_STATE_WALKING_RIGHT);
	SetState(KOOPA_STATE_DIE);
}
void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (isHeld)
	{
		vy = 0;
	}
	else
	{
		vy += KOOPA_GRAVITY * dt;
	}

	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	ULONGLONG now = GetTickCount64();
	if (state == KOOPA_STATE_SHELL && now - shell_start > KOOPA_RETURN_WALKING_INTERVAL)
	{
		(int)now % 2 == 0 ? SetState(KOOPA_STATE_WALKING_RIGHT) : SetState(KOOPA_STATE_WALKING_LEFT);
	}
	if (state != KOOPA_STATE_SHELL)
		isHeld = false;

	if (state == KOOPA_STATE_DIE)
	
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
	if (isHeld)
	{

	}
	else
	{
		x += vx * dt;
		y += vy * dt;
	}

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
		die_start = GetTickCount64();
		vx = 0;
		vy = -KOOPA_DIE_BOUNCE_SPEED_Y;
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
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_SLIDING_RIGHT:
		nx = 1;
		vx = KOOPA_WALKING_SPEED;
		break;
	}
	this->state = state;
}
