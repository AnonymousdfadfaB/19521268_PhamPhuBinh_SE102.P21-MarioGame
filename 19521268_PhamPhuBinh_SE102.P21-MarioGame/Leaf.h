#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define LEAF_CYCLE 512
#define LEAF_GRAVITY 0.00002f
#define PI 3.1415926535897932f
#define ID_SPRI_LEAF 70001
#define LEAF_AMPLITUDE 25
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16
#define LEAF_SPRITE_ID 70001

class CLeaf : public CGameObject {
protected:
public:
	CLeaf(float x, float y) : CGameObject(x, y)
	{
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

