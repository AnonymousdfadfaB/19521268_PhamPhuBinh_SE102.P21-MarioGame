#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define LEAF_HORIZONTAL_VELOCITY 0.1f
#define LEAF_GRAVITY 0.00002f
#define ID_SPRI_LEAF 70001
#define LEAF_AMPLITUDE 25
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16


class CLeaf : public CGameObject {
protected:
public:
	CLeaf(float x, float y) : CGameObject(x, y)
	{
		this->vx = LEAF_HORIZONTAL_VELOCITY;

	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

