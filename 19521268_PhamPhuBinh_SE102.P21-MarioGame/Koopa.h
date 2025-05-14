#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_SHELL_BBOX_WIDTH 16
#define KOOPA_SHELL_BBOX_HEIGHT 16

#define GOOMBA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALKING_LEFT 150
#define KOOPA_STATE_WALKING_RIGHT 160
#define KOOPA_STATE_SHELL 170
#define KOOPA_STATE_SHELL_SLIDING_LEFT 180
#define KOOPA_STATE_SHELL_SLIDING_RIGHT 190

#define KOOPA_STATE_DIE 250

#define ID_ANI_KOOPA_SHELL 60100
#define ID_ANI_KOOPA_WALKING_RIGHT 60101
#define ID_ANI_KOOPA_WALKING_LEFT 60102
#define ID_ANI_KOOPA_DIE 18200

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
	void ToShell() { SetState(KOOPA_STATE_SHELL); }
	void ToShellSlidingRight() { SetState(KOOPA_STATE_SHELL_SLIDING_RIGHT); }
	void ToShellSlidingLeft() { SetState(KOOPA_STATE_SHELL_SLIDING_LEFT); }
	void Die() {
		SetState(KOOPA_STATE_DIE);
		//die_start = GetTickCount64();
	}
};