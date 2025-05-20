#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITE_VIRTICLE_PIPE 11000
#define ID_SPRITE_HORIZONTAL_PIPE 11001
#define ID_SPRITE_VERTICAL_PIPE_WITH_BRICK 11002
#define ID_SPRITE_SUPER_HIGH_PIPE_WITH_BRICK 11003
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CPipe : public CGameObject {
	float height;
	float width;
	int spriteId;
public:
	CPipe(float x, float y, float width = 31, float height = 31, int spriteId = 11004) : CGameObject(x, y) 
	{
		this->width = width;
		this->height = height;
		this->spriteId = spriteId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};