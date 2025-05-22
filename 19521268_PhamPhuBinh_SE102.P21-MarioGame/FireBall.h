#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//parameters of operation
#define FIREBALL_VERTICLE_SPEED 0.01f
#define FIREBALL_HORIZONTAL_SPEED 0.01f
//ani id
#define FIREBALL_ANI_ID 91001
//width, height
#define FIREBALL_WIDTH 10
#define FIREBALL_HEIGHT 10


class CFireball : public CGameObject {
protected:
public:
	CFireball(float x, float y,float targetX = 0, float targetY = 0) : CGameObject(x, y)
	{
		this->vx = FIREBALL_HORIZONTAL_SPEED;
		this->vy = FIREBALL_HORIZONTAL_SPEED;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
};
