#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"

#define CLOUD_SPRITE_ID 19001
#define CLOUD_WIDTH 16
#define CLOUD_HEIGHT 16
class CCloud : public CGameObject {
public:
	CCloud(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
};

