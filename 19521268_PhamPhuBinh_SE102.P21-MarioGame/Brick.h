#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "PieceOfBrick.h"
#include "Scene.h"
#include "PlayScene.h"
#include "QuestionBlock.h"
#include "PButton.h"
#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_HEIGHT 16

#define BRICK_CONTENT_TYPE_NOPE	1
#define BRICK_CONTENT_TYPE_PBUTTON 2
class CBrick : public CGameObject {
protected:
	int contentType;
public:
	CBrick(float x, float y, int contentType = BRICK_CONTENT_TYPE_NOPE) : CGameObject(x, y) 
	{
		this->contentType = contentType;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Broken();
};