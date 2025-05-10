#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTIONBLOCK 30010
#define ID_SPRITE_QUESTIONBLOCK_AFTER_HIT 30005
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16
#define COIN_CONTENT 101
#define RED_MUSHROOM_CONTENT 102
#define GREEN_MUSHROOM_CONTENT 103
#define LEAF_CONTENT 104


class CQuestionBlock : public CGameObject {
protected:
	bool hit;
	int contentType;
	LPGAMEOBJECT content;
public:
	CQuestionBlock(float x, float y, bool hit = FALSE, int contentType = LEAF_CONTENT) : CGameObject(x, y) {
		this->hit = hit;
		this->contentType = contentType;
		this->content = NULL;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	bool IsHit() { return hit; }
	int IsBlocking() { return 1; }
	void Hit() { hit = true; }
	bool IsQuestionBlockContainCoin() { return contentType == COIN_CONTENT; }
	bool IsQuestionBlockContainRedMushroom() { return contentType == RED_MUSHROOM_CONTENT; }
	bool IsQuestionBlockContainGreenMushroom() { return contentType == GREEN_MUSHROOM_CONTENT; }
	bool IsQuestionBlockContainLeaf() { return contentType ==LEAF_CONTENT; }
	void GenerateCoin();
	void GenerateRedMushroom(); 
	void GenerateGreenMushroom();
	void GenerateLeaf();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};