#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "BrownGoomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBlock.h"
#include "Collision.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Koopa.h"
#include "PlantEnemy.h"
#include "VictoryFlower.h"
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// reset untouchable timer if untouchable time has passed
	if (isHoldingShell)
	{
		if (shell->GetState() != KOOPA_STATE_SHELL)
		{
			isHoldingShell = false;
			shell = NULL;
		}
	}
	if (isHoldingShell)
	{
		auto it = std::find(coObjects->begin(), coObjects->end(), shell);
		if (it != coObjects->end())
		{
			coObjects->erase(it);
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
		MoveShell(dt);
	} 
	else
	{
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	
	//CCollision::GetInstance()->Process(this, dt, coObjects);

	//reset action of mario if sactifies

	if (isAttackingLeft)
	{
		if (GetTickCount64() - attack_start > MARIO_ATTACK_TIME)
		{
			isAttackingLeft = false;
			attack_start = -1;
		}
	}
	else if (isAttackingRight)
	{
		if (GetTickCount64() - attack_start > MARIO_ATTACK_TIME)
		{
			isAttackingRight = false;
			attack_start = -1;
		}
	}
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CBrownGoomba*>(e->obj))
		OnCollisionWithBrownGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);	
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CRedGoomba*>(e->obj))
		OnCollisionWithRedGoomba(e);
	else if (dynamic_cast<CPlantEnemy*>(e->obj))
		OnCollisionWithPlantEnemy(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CVictoryFlower*>(e->obj))
		OnCollisionWithVictoryFlower(e);
}

void CMario::OnCollisionWithBrownGoomba(LPCOLLISIONEVENT e)
{
	CBrownGoomba* brownGoomba = dynamic_cast<CBrownGoomba*>(e->obj);
	if (isAttackingLeft || isAttackingRight)
	{
		if (brownGoomba->GetState() != BROWN_GOOMBA_STATE_DIE)
		{
			brownGoomba->SetState(BROWN_GOOMBA_STATE_DIE);

		}
		return;
	}
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (brownGoomba->GetState() != BROWN_GOOMBA_STATE_DIE)
		{
			brownGoomba->SetState(BROWN_GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
			if (brownGoomba->GetState() != BROWN_GOOMBA_STATE_DIE)
			{
				MarioIsHit();
			}
	}
}
void CMario::OnCollisionWithPlantEnemy(LPCOLLISIONEVENT e)
{
	CPlantEnemy* plantEnemy = dynamic_cast<CPlantEnemy*>(e->obj);
	int plantEnemyState = plantEnemy->GetState();
	if (plantEnemyState == DIE_STATE)
		return;
	if (isAttackingLeft || isAttackingRight)
	{
		plantEnemy->SetState(DIE_STATE);
		return;
	}
	else
		MarioIsHit();
}
void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
		MarioIsHit();
}
void CMario::OnCollisionWithVictoryFlower(LPCOLLISIONEVENT e)
{
	CVictoryFlower* victoryFlower = dynamic_cast<CVictoryFlower*>(e->obj);
	victoryFlower->Fly();
}
void CMario::OnCollisionWithRedGoomba(LPCOLLISIONEVENT e)
{
	CRedGoomba* redGoomba = dynamic_cast<CRedGoomba*>(e->obj);
	int redGoombaState = redGoomba->GetState();
	int redGoombaLevel = redGoomba->GetLevel();
	if (redGoombaState == RED_GOOMBA_STATE_DIE)
		return;
	if (isAttackingLeft || isAttackingRight)
	{
		redGoomba->SetState(BROWN_GOOMBA_STATE_DIE);
		return;
	}
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (redGoombaLevel == RED_GOOMBA_LEVEL_WINGED)
		{
			redGoomba->SetLevel(RED_GOOMBA_LEVEL_WINGLESS);
			if (redGoomba->GetXDirection() > 0)
			{
				redGoomba->SetState(RED_GOOMBA_STATE_WALKING_RIGHT);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else
			{
				redGoomba->SetState(RED_GOOMBA_STATE_WALKING_LEFT);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else
		{
			redGoomba->SetState(RED_GOOMBA_STATE_DIE);
		}
	}
	else // hit by Goomba
	{
		MarioIsHit();
	}
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}
void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (!questionBlock->IsHit() && e->ny > 0) {
		questionBlock->Hit();
		if (questionBlock->IsQuestionBlockContainCoin())
			coin++;
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (mushroom->IsRedMushroom())
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			SetLevel(MARIO_LEVEL_BIG);
			mushroom->Delete();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_RACCOON);
			mushroom->Delete();
		}
	}
	else
	{
		up++;
		mushroom->Delete();
	}
}
void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	int koopaState = koopa->GetState();
	if (koopaState == KOOPA_STATE_DIE) return;
	if (isAttackingLeft || isAttackingRight)
	{
		koopa->SetState(KOOPA_STATE_DIE);
		return;
	}
	// jump on top >> kill Goomba and deflect a bit 

	if (e->nx != 0)
	{
		if ((this->state == MARIO_STATE_RUNNING_RIGHT || this->state == MARIO_STATE_RUNNING_LEFT) && !IsAction())
		{
			isHoldingShell = true;
			shell = koopa;
			koopa->HeldByMario();
		}
		else if (e->nx > 0 && koopaState == KOOPA_STATE_SHELL)
		{
			koopa->SetPosition(koopa->GetX() - KOOPA_SHELL_BBOX_WIDTH / 2, koopa->GetY());
			koopa->SetState(KOOPA_STATE_SHELL_SLIDING_LEFT);
		}
		else if (e->nx < 0 && koopaState == KOOPA_STATE_SHELL)
		{
			koopa->SetPosition(koopa->GetX() + KOOPA_SHELL_BBOX_WIDTH / 2, koopa->GetY());
			koopa->SetState(KOOPA_STATE_SHELL_SLIDING_RIGHT);
		}
		else
		{
			MarioIsHit();
		}
	}
	else if (e->ny < 0)
	{
		switch (koopaState)
		{
		case KOOPA_STATE_WALKING_LEFT:
		case KOOPA_STATE_WALKING_RIGHT:
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			break;
		case KOOPA_STATE_SHELL:
			if (x > koopa->GetX())
			{
				koopa->SetPosition(koopa->GetX() - KOOPA_SHELL_BBOX_WIDTH / 2, koopa->GetY());
				koopa->SetState(KOOPA_STATE_SHELL_SLIDING_LEFT);
			}
			else
			{
				koopa->SetPosition(koopa->GetX() + KOOPA_SHELL_BBOX_WIDTH / 2, koopa->GetY());
				koopa->SetState(KOOPA_STATE_SHELL_SLIDING_RIGHT);
			}
			break;
		case KOOPA_STATE_SHELL_SLIDING_LEFT:
		case KOOPA_STATE_SHELL_SLIDING_RIGHT:
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			break;
		case KOOPA_STATE_JUMP_LEFT:
			koopa->SetState(KOOPA_STATE_WALKING_LEFT);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			break;
		case KOOPA_STATE_JUMP_RIGHT:
			koopa->SetState(KOOPA_STATE_WALKING_RIGHT);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			break;
		}
	}
	else
	{
		switch (koopaState)
		{
		case KOOPA_STATE_WALKING_LEFT:
		case KOOPA_STATE_WALKING_RIGHT:
		case KOOPA_STATE_SHELL_SLIDING_LEFT:
		case KOOPA_STATE_SHELL_SLIDING_RIGHT:
		case KOOPA_STATE_JUMP_LEFT:
		case KOOPA_STATE_JUMP_RIGHT:
			MarioIsHit();
			break;
		case KOOPA_STATE_SHELL:
			if (x > koopa->GetX())
			{
				koopa->SetPosition(koopa->GetX() - KOOPA_SHELL_BBOX_WIDTH / 2, koopa->GetY());
				koopa->SetState(KOOPA_STATE_SHELL_SLIDING_LEFT);
			}
			else
			{
				koopa->SetPosition(koopa->GetX() + KOOPA_SHELL_BBOX_WIDTH / 2, koopa->GetY());
				koopa->SetState(KOOPA_STATE_SHELL_SLIDING_RIGHT);
			}
			break;
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (level == MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_BIG;
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		leaf->Delete();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		level = MARIO_LEVEL_RACCOON;
		y -= (MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) / 2;
		leaf->Delete();
	}
	else {
		leaf->Delete();
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (isAttackingLeft)
	{
		return aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
	} 
	else if (isAttackingRight)
	{
		return aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
	}
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 
	if (isOnPlatform)
	{
		switch (state)
		{
		case MARIO_STATE_RUNNING_RIGHT:
			if (isSitting) break;
			maxVx = MARIO_RUNNING_SPEED;
			ax = MARIO_ACCEL_RUN_X;
			nx = 1;
			break;
		case MARIO_STATE_RUNNING_LEFT:
			if (isSitting) break;
			maxVx = -MARIO_RUNNING_SPEED;
			ax = -MARIO_ACCEL_RUN_X;
			nx = -1;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			if (isSitting) break;
			maxVx = MARIO_WALKING_SPEED;
			ax = MARIO_ACCEL_WALK_X;
			nx = 1;
			break;
		case MARIO_STATE_WALKING_LEFT:
			if (isSitting) break;
			maxVx = -MARIO_WALKING_SPEED;
			ax = -MARIO_ACCEL_WALK_X;
			nx = -1;
			break;
		case MARIO_STATE_JUMP:
			if (isSitting) break;
			if (isOnPlatform)
			{
				if (abs(this->vx) >= MARIO_RUNNING_SPEED)
					vy = -MARIO_JUMP_RUN_SPEED_Y;
				else
					vy = -MARIO_JUMP_SPEED_Y;
			}
			break;
		case MARIO_STATE_RELEASE_JUMP:
			if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
			break;

		case MARIO_STATE_SIT:
			if (isOnPlatform && !IsAction())
			{
				if (level == MARIO_LEVEL_BIG)
				{
					y += MARIO_BIG_SIT_HEIGHT_ADJUST;
					isSitting = true;
					vx = 0; vy = 0.0f;
				}
				else if (level == MARIO_LEVEL_RACCOON)
				{
					y += MARIO_RACCOON_SIT_HEIGHT_ADJUST;
					isSitting = true;
					vx = 0; vy = 0.0f;
				}
			}
			break;

		case MARIO_STATE_SIT_RELEASE:
			if (isSitting)
			{
				isSitting = false;
				state = MARIO_STATE_IDLE;
				if (level == MARIO_LEVEL_BIG)
				{
					y -= MARIO_BIG_SIT_HEIGHT_ADJUST;
				}
				else
				{
					y -= MARIO_RACCOON_SIT_HEIGHT_ADJUST;
				}
			}
			break;

		case MARIO_STATE_IDLE:
			ax = 0.0f;
			vx = 0.0f;
			break;

		case MARIO_STATE_DIE:
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			vx = 0;
			ax = 0;
			break;
		}
	}
	else
	{
		switch (state)
		{
			case MARIO_STATE_FLY:
				if (level == MARIO_LEVEL_RACCOON)
				{
					if (abs(this->vx) >= MARIO_RUNNING_SPEED)
						vy = -MARIO_FLY_SPEED_Y;
				}
				break;
			case MARIO_STATE_LIGHTLY_FLY:
				if (level == MARIO_LEVEL_RACCOON)
				{
					if (abs(this->vx) != MARIO_RUNNING_SPEED)
						vy = -MARIO_SLIGHTLY_FLY_SPEED_Y;
				}
				break;
			case MARIO_STATE_GLIDE_LEFT:
				vx -= MARIO_ACCEL_WALK_X;
				nx = -1;
				maxVx = -MARIO_RUNNING_SPEED;
				break;
			case MARIO_STATE_GLIDE_RIGHT:
				vx += MARIO_ACCEL_WALK_X;
				nx = 1;
				maxVx = MARIO_RUNNING_SPEED;
				break;
			case MARIO_STATE_FALL:
				//ax = 0.0f;
				//vx = 0.0f;
				break;
			case MARIO_STATE_DIE:
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				vx = 0;
				ax = 0;
				break;
		}
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		if (isSitting) 
		{
			left = x - MARIO_RACCOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACCOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_BBOX_HEIGHT;
		}

	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else if (this->level == MARIO_LEVEL_BIG)
	{
		y -= (MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) / 2;
	}
	level = l;
}
void CMario::MoveShell(DWORD dt)
{
		if (nx > 0)
			shell->SetPosition(x + GetWidth() / 2 + KOOPA_BBOX_WIDTH / 2, y - 10); // y - 10
		else
			shell->SetPosition(x - GetWidth() / 2 - KOOPA_BBOX_WIDTH / 2, y - 10); //
}


