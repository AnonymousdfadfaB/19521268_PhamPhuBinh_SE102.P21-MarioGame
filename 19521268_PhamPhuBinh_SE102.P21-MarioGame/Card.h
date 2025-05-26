#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"

class CCard : public CGameObject {
protected:
	float width;
	float height;
	int spriteId;
public:
	CCard(float x, float y, float width, float height, int spriteId);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
};
