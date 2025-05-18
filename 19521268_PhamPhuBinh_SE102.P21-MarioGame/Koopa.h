#pragma once
#include "GameObject.h"


#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_SLIDING_SPEED 0.2f
#define KOOPA_JUMP_SPEED 0.4f
#define KOOPA_DIE_BOUNCE_SPEED 0.5f

#define KOOPA_RETURN_WALKING_INTERVAL 5000
#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_SHELL_BBOX_WIDTH 16
#define KOOPA_SHELL_BBOX_HEIGHT 16

#define KOOPA_DIE_TIMEOUT 1000

#define KOOPA_STATE_WALKING_LEFT 150
#define KOOPA_STATE_WALKING_RIGHT 160
#define KOOPA_STATE_SHELL 170
#define KOOPA_STATE_SHELL_SLIDING_LEFT 180
#define KOOPA_STATE_SHELL_SLIDING_RIGHT 190
#define KOOPA_STATE_JUMP_LEFT 200
#define KOOPA_STATE_JUMP_RIGHT 210
#define KOOPA_STATE_DIE 220

#define ID_ANI_KOOPA_SHELL 60100
#define ID_ANI_KOOPA_WALKING_RIGHT 60101
#define ID_ANI_KOOPA_WALKING_LEFT 60102
#define ID_ANI_KOOPA_JUMP_RIGHT 60103
#define ID_ANI_KOOPA_JUMP_LEFT 60104
#define ID_ANI_KOOPA_DIE 60105

class CKoopa : public CGameObject
{
protected:
	bool isHeld;
	ULONGLONG die_start;
	ULONGLONG shell_start;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
};