#pragma once
#include "GameObject.h"

#define BROWN_GOOMBA_GRAVITY 0.002f
#define BROWN_GOOMBA_WALKING_SPEED 0.05f


#define BROWN_GOOMBA_BBOX_WIDTH 16
#define BROWN_GOOMBA_BBOX_HEIGHT 16
#define BROWN_GOOMBA_BBOX_HEIGHT_DIE 10

#define BROWN_GOOMBA_DIE_TIMEOUT 500

#define BROWN_GOOMBA_STATE_WALKING_LEFT 100
#define BROWN_GOOMBA_STATE_WALKING_RIGHT 101
#define BROWN_GOOMBA_STATE_DIE 102

#define ID_ANI_BROWN_GOOMBA_WALKING 5000
#define ID_ANI_BROWN_GOOMBA_DIE 5001

class CBrownGoomba : public CGameObject
{
protected:
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBrownGoomba(float x, float y);
	virtual void SetState(int state);
};