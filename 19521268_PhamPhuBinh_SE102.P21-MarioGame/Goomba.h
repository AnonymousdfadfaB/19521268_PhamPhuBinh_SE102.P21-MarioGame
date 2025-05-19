#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 16
#define GOOMBA_BBOX_HEIGHT_DIE 10

#define GOOMBA_DIE_TIMEOUT 500



#define ID_ANI_GOOMBA_BROWN_WALKING 5000
#define ID_ANI_GOOMBA_BROWN_DIE 5001

#define ID_ANI_GOOMBA_RED_WALKING 5002
#define ID_ANI_GOOMBA_RED_DIE 5003
#define ID_ANI_GOOMBA_BROWN_WALKING_JUMP 5004

#define GOOMBA_TYPE_RED 1
#define GOOMBA_TYPE_BROWN 2

#define GOOMBA_STATE_WALKING_LEFT 100
#define GOOMBA_STATE_WALKING_RIGHT 101
#define GOOMBA_STATE_WALKING_JUMP_LEFT 102
#define GOOMBA_STATE_WALKING_JUMP_RIGHT 103
#define GOOMBA_STATE_DIE 104

class CGoomba : public CGameObject
{
protected:
	int type;
	int state;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int type);
	virtual void SetState(int state);
	int GetAniIdGoombaRed();
	int GetAniIdGoombaBrown();
};