#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define MUSHROOM_VERTICLE_VELOCITY -0.3f
#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_HORIZONTAL_VELOCITY 0.05f

#define ID_SPRI_RED_MUSHROOM 50001
#define ID_SPRI_GREEN_MUSHROOM 50002

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
#define RED_MUSHROOM 301
#define GREEN_MUSHROOM 302

class CMushroom : public CGameObject {
protected:
	int type;
public:
	CMushroom(float x, float y, int type = GREEN_MUSHROOM) : CGameObject(x, y)
	{
		this->type = type;
		this->vy = MUSHROOM_VERTICLE_VELOCITY;
		this->vx = MUSHROOM_HORIZONTAL_VELOCITY;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	bool IsRedMushroom() { return type == RED_MUSHROOM; }
	bool IsGreenMushroom() { return type == GREEN_MUSHROOM; }
};
