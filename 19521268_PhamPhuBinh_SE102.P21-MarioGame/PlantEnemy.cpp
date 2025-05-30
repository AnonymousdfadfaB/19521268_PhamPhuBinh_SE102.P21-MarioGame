
#include "PlantEnemy.h"
#include "cmath"
CPlantEnemy::CPlantEnemy(float x, float y, int type, CGameObject* pipe):CGameObject(x, y)
{
	this->type = type;
	switch (type)
	{
	case NO_FIRE_GREEN_PLANT:
		minY = y;
		maxY = y - NO_FIRE_GREEN_PLANT_HEIGHT;
		canFire = false;
		break;
	case FIRE_GREEN_PLANT:
		minY = y;
		maxY = y - FIRE_GREEN_PLANT_HEIGHT;
		canFire = true;
		break;
	case FIRE_RED_PLANT:
		minY = y;
		maxY = y - FIRE_RED_PLANT_HEIGHT;
		canFire = true;
		break;
	}
	hide_start = -1;
	attack_start = -1;
	die_start = -1;
	alreadyFire = false;
	this->pipe = pipe;
	SetState(HIDE_STATE);
}
void CPlantEnemy::SetState(int state)
{

	switch (state)
	{
	case HIDE_STATE:
		vy = 0;
		hide_start = GetTickCount64();
		break;
	case RISE_STATE:
		vy = -NO_FIRE_GREEN_PLANT_VERTICAL_SPEED;
		break;
	case ATTACK_STATE:
		attack_start = GetTickCount64();
		alreadyFire = false;
		vy = 0;
		break;
	case DOWN_STATE:
		vy = NO_FIRE_GREEN_PLANT_VERTICAL_SPEED;
		break;
	case DIE_STATE:
		die_start = GetTickCount64();
		vy = 0;
		break;
	}
	CGameObject::SetState(state);
}
void CPlantEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == DIE_STATE && GetTickCount64() - die_start > DIE_DURATION)
	{
		isDeleted = true;
		return;
	}
	switch (state)
	{
	case HIDE_STATE:
		if (GetTickCount64() - hide_start > HIDE_DURATION)
		{
			hide_start = -1;
			SetState(RISE_STATE);
		}
		break;
	case RISE_STATE:
		if (y <= maxY)
		{
			y = maxY;
			SetState(ATTACK_STATE);
		}
		break;
	case ATTACK_STATE:
		if (GetTickCount64() - attack_start > ATTACK_DURATION)
		{
			attack_start = -1;
			SetState(DOWN_STATE);
		}
		break;
	case DOWN_STATE:
		if (y >= minY)
		{
			y = minY;
			SetState(HIDE_STATE);
		}
		break;
	}

	if (canFire && state == ATTACK_STATE && !alreadyFire && HaveTarget())
	{
		CMario* mario =(CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(new CFireball(x, y, mario->GetX(), mario->GetY())); //CFireBall(x, y)
		alreadyFire = true;
	}
	y += vy * dt;
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CPlantEnemy::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPlantEnemy::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CPlantEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch(type)
	{
	case NO_FIRE_GREEN_PLANT:
		left = x - NO_FIRE_GREEN_PLANT_WIDTH / 2;
		top = y - NO_FIRE_GREEN_PLANT_HEIGHT / 2;
		right = left + NO_FIRE_GREEN_PLANT_WIDTH;
		bottom = top + NO_FIRE_GREEN_PLANT_HEIGHT;
		break;
	case FIRE_GREEN_PLANT:
		left = x - FIRE_GREEN_PLANT_WIDTH / 2;
		top = y - FIRE_GREEN_PLANT_HEIGHT / 2;
		right = left + FIRE_GREEN_PLANT_WIDTH;
		bottom = top + FIRE_GREEN_PLANT_HEIGHT;
		break;
	case FIRE_RED_PLANT:
		left = x - FIRE_RED_PLANT_WIDTH / 2;
		top = y - FIRE_RED_PLANT_HEIGHT / 2;
		right = left + FIRE_RED_PLANT_WIDTH;
		bottom = top + FIRE_RED_PLANT_HEIGHT;
		break;
	}

}

void CPlantEnemy::Render()
{
	int aniId;
	if (state == DIE_STATE)
	{
		aniId = DIE_EFFECT;
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
		return;
	}
	switch (type)
	{
	case NO_FIRE_GREEN_PLANT:
		aniId = NO_FIRE_GREEN_PLANT_ANI_ID;
		break;
	case FIRE_GREEN_PLANT:
		switch (GetMarioRelativePosition())
		{
		case MARIO_POSITION_LEFT_TOP:
			aniId = FIRE_GREEN_PLANT_LEFT_TOP_ANI_ID;
			break;
		case MARIO_POSITION_RIGHT_TOP:
			aniId = FIRE_GREEN_PLANT_RIGHT_TOP_ANI_ID;
			break;
		case MARIO_POSITION_LEFT_BOTTOM:
			aniId = FIRE_GREEN_PLANT_LEFT_BOTTOM_ANI_ID;
			break;
		case MARIO_POSITION_RIGHT_BOTTOM:
			aniId = FIRE_GREEN_PLANT_RIGHT_BOTTOM_ANI_ID;
			break;
		}
		break;
	case FIRE_RED_PLANT:
		switch (GetMarioRelativePosition())
		{
		case MARIO_POSITION_LEFT_TOP:
			aniId = FIRE_RED_PLANT_LEFT_TOP_ANI_ID;
			break;
		case MARIO_POSITION_RIGHT_TOP:
			aniId = FIRE_RED_PLANT_RIGHT_TOP_ANI_ID;
			break;
		case MARIO_POSITION_LEFT_BOTTOM:
			aniId = FIRE_RED_PLANT_LEFT_BOTTOM_ANI_ID;
			break;
		case MARIO_POSITION_RIGHT_BOTTOM:
			aniId = FIRE_RED_PLANT_RIGHT_BOTTOM_ANI_ID;
			break;
		}
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
int CPlantEnemy::GetMarioRelativePosition()
{
	int position = 0;
	CMario* mario = (CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetY() > y)
		position += 2;
	if (mario->GetX() < x)
		position += 1;
	else
		position += 2;
	return position;
}
bool CPlantEnemy::HaveTarget() {
	CMario* mario = (CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (std::abs(x - mario->GetX()) <= 200 && std::abs(y - mario->GetY()) <= 200)
		return true;
	return false;

}


