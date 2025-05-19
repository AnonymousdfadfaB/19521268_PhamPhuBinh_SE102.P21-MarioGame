#pragma once
#include "GameObject.h"

#define RED_GOOMBA_LEVEL_WINGED 1
#define RED_GOOMBA_LEVEL_WINGLESS 2

#define RED_GOOMBA_GRAVITY 0.002f
#define RED_GOOMBA_WALKING_SPEED 0.05f
#define RED_GOOMBA_SMALL_JUMP_SPEED 0.15f
#define RED_GOOMBA_HIGH_JUMP_SPEED 0.375f

#define RED_GOOMBA_BBOX_WIDTH 16
#define RED_GOOMBA_BBOX_HEIGHT 16
#define RED_GOOMBA_BBOX_HEIGHT_DIE 10

#define RED_GOOMBA_DIE_TIMEOUT 500

#define RED_GOOMBA_STATE_WALKING_LEFT 100
#define RED_GOOMBA_STATE_WALKING_RIGHT 101
#define RED_GOOMBA_STATE_SMALL_JUMP_LEFT 102
#define RED_GOOMBA_STATE_SMALL_JUMP_RIGHT 103
#define RED_GOOMBA_STATE_HIGH_JUMP_LEFT 104
#define RED_GOOMBA_STATE_HIGH_JUMP_RIGHT 105
#define RED_GOOMBA_STATE_DIE 106

#define ID_ANI_WINGLESS_RED_GOOMBA_WALKING 6000
#define ID_ANI_WINGED_RED_GOOMBA_WALKING_AND_SMALL_JUMP 6001
#define ID_ANI_RED_GOOMBA_HIGH_JUMP 6002
#define ID_ANI_RED_GOOMBA_DIE 6003

#define WALK_DURATION 1270
class CRedGoomba : public CGameObject
{
protected:
	ULONGLONG die_start;
	ULONGLONG walk_start;
	bool isOnPlatform;
	int number_small_jump;
	int level;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CRedGoomba(float x, float y);
	virtual void SetState(int state);

}; 
