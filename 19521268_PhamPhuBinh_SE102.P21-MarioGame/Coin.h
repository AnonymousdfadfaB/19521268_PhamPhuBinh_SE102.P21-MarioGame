#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ACCEL_GRAVITY 0.002f
#define COIN_VERTICLE_VELOCITY -0.5f
#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define BOUNCE_COIN 201
#define NORMAL_COIN 202

class CCoin : public CGameObject {
protected:
	int type;
public:
	CCoin(float x, float y, int type = NORMAL_COIN) : CGameObject(x, y) 
	{ 
		this->type = type;
		if (type == BOUNCE_COIN)
			this->vy = -COIN_VERTICLE_VELOCITY;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};