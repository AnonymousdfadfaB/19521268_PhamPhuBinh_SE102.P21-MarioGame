#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"

#define ID_ANI_QUESTIONBLOCK 30010
#define ID_SPRITE_QUESTIONBLOCK_AFTER_HIT 30005
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16
#define COIN 101
#define RED_MUSHROOM_OR_LEAF 102
#define GREEN_MUSHROOM 302
#define QUESTIONBLOCK_CONTENT_TYPE_NOPE 104



class CQuestionBlock : public CGameObject {
protected:
	bool hit;
	int contentType;
	LPGAMEOBJECT content;
public:
	CQuestionBlock(float x, float y, int contentType, bool hit = FALSE) : CGameObject(x, y) {
		this->hit = hit;
		this->contentType = contentType;
		this->content = NULL;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	bool IsHit() { return hit; }
	int IsBlocking() { return 1; }
	void Hit();
	bool IsQuestionBlockContainCoin() { return contentType == COIN; }
	void GenerateCoin();
	void GenerateRedMushroom(); 
	void GenerateGreenMushroom();
	void GenerateLeaf();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};