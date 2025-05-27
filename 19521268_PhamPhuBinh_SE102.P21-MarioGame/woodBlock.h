#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define WOODBLOCK_SPRITE_ID 15000
#define WOODBLOCK_WIDTH 16
#define WOODBLOCK_HEIGHT 16

class CWoodBlock : public CGameObject {
public:
	CWoodBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
