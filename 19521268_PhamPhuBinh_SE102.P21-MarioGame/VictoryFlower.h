#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define VICTORYFLOWER_VERTICLE_SPEED 0.5f
#define VICTORYFLOWER_ANI_ID 20001

#define VICTORYFLOWER_WIDTH 16
#define VICTORYFLOWER_HEIGHT 16


class CVictoryFlower : public CGameObject {
protected:
	bool alreadyHit;
public:
	CVictoryFlower(float x, float y) : CGameObject(x, y)
	{
		alreadyHit = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	void BeingHit()
	{
			alreadyHit = true;
			this->vy = -VICTORYFLOWER_VERTICLE_SPEED;
	}
};
