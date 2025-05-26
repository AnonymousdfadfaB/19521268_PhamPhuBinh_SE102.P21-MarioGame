#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CSceneObject : public CGameObject {
protected:
	int spriteId;
public:
	CSceneObject(float x, float y, int spriteId);
	void Render();
	void Update(DWORD dt) {}
	int IsDirectionColliable(float nx, float ny) 
	{
		return 0;
	}
	virtual int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};
