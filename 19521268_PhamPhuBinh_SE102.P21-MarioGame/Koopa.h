#pragma once
#include "GameObject.h"


#define KOOPA_TYPE_RED 10
#define KOOPA_TYPE_GREEN 11

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

#define ID_ANI_RED_KOOPA_SHELL 60100
#define ID_ANI_RED_KOOPA_WALKING_RIGHT 60101
#define ID_ANI_RED_KOOPA_WALKING_LEFT 60102
#define ID_ANI_RED_KOOPA_JUMP_RIGHT 60103
#define ID_ANI_RED_KOOPA_JUMP_LEFT 60104
#define ID_ANI_RED_KOOPA_DIE 60105

#define ID_ANI_GREEN_KOOPA_SHELL 70100
#define ID_ANI_GREEN_KOOPA_WALKING_RIGHT 70101
#define ID_ANI_GREEN_KOOPA_WALKING_LEFT 70102
#define ID_ANI_GREEN_KOOPA_JUMP_RIGHT 70103
#define ID_ANI_GREEN_KOOPA_JUMP_LEFT 70104
#define ID_ANI_GREEN_KOOPA_DIE 70105

class CKoopa : public CGameObject
{
protected:
	int type;
	bool isHeld;
	float leftBoundary;
	float rightBoundary;
	ULONGLONG die_start;
	ULONGLONG shell_start;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable();
	int IsBlocking();
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBrownGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	int GetAniIdRedKoopa();
	int GetAniIdGreenKoopa();
public:
	CKoopa(float x, float y, float patrolDistance, int state, int type);
	virtual void SetState(int state);
	void HeldByMario();
};