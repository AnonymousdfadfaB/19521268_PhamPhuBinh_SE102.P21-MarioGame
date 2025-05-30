#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//parameters of operation
#define FIREBALL_SPEED 0.1f
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
		//don't need to handle, case targetX = x, targetY = y
		float dx = targetX - x;
		float dy = targetY - y;
		float d = sqrt(pow(dx, 2) + pow(dy, 2));
		this->vx = dx / d * FIREBALL_SPEED;
		this->vy = dy / d * FIREBALL_SPEED;

	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	//virtual int IsCollidable() { return 1; };
};
