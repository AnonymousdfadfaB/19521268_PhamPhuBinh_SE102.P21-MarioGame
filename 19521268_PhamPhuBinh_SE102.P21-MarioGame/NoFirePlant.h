#pragma once
#include "GameObject.h"
//#include "Pipe.h"

#define HIDE_DURATION 2000.0f
#define ATTACK_DURATION 2000.0f
#define NO_FIRE_GREEN_PLANT_VERTICAL_SPEED 0.05f

#define NO_FIRE_GREEN_PLANT_WIDTH 16
#define NO_FIRE_GREEN_PLANT_HEIGHT 24

#define NO_FIRE_GREEN_PLANT_STATE_HIDE 100
#define NO_FIRE_GREEN_PLANT_STATE_RISE 101
#define NO_FIRE_GREEN_PLANT_STATE_ATTACK 102
#define NO_FIRE_GREEN_PLANT_STATE_DOWN 103
#define NO_FIRE_GREEN_PLANT_STATE_DIE 104

#define NO_FIRE_GREEN_PLANT_ANI_ID 84001
#define NO_FIRE_PLANT_TYPE_GREEN 1
#define NO_FIRE_PLANT_TYPE_RED 2

class CNoFirePlant : public CGameObject
{
protected:
	CGameObject* pipe;
	int type;
	float maxY;
	float minY;
	ULONGLONG hide_start;
	ULONGLONG attack_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CNoFirePlant(float x, float y, CGameObject* pipe);
	virtual void SetState(int state);
};