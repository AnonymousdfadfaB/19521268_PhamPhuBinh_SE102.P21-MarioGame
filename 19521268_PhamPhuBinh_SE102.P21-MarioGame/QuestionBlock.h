#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"
#include "Scene.h"
#include "PlayScene.h"

#define ID_ANI_QUESTIONBLOCK 30010
#define ID_SPRITE_QUESTIONBLOCK_AFTER_HIT 30005
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16
#define COIN 101
#define RED_MUSHROOM_OR_LEAF 102
#define GREEN_MUSHROOM 103



class CQuestionBlock : public CGameObject {
protected:
	bool hit;
	int contentType;
	LPGAMEOBJECT content;
public:
	CQuestionBlock(float x, float y, int contentType = RED_MUSHROOM_OR_LEAF, bool hit = FALSE) : CGameObject(x, y) {
		this->hit = hit;
		this->contentType = contentType;
		this->content = NULL;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	bool IsHit() { return hit; }
	int IsBlocking() { return 1; }
	void Hit() 
	{ 
		hit = true; 
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		switch (contentType)
		{
		case COIN:
			GenerateCoin();
			break;
		case RED_MUSHROOM_OR_LEAF:
			if (mario->IsSmall())
				GenerateRedMushroom();
			else
				GenerateLeaf();
			break;
		case GREEN_MUSHROOM:
			GenerateGreenMushroom();
			break;
		}
	}
	bool IsQuestionBlockContainCoin() { return contentType == COIN; }
	void GenerateCoin();
	void GenerateRedMushroom(); 
	void GenerateGreenMushroom();
	void GenerateLeaf();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};