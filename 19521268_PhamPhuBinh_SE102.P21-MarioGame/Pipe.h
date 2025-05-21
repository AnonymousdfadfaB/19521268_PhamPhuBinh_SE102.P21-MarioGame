#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
#include "NoFirePlant.h"

#define ID_SPRITE_VIRTICLE_PIPE 11000
#define ID_SPRITE_HORIZONTAL_PIPE 11001
#define ID_SPRITE_VERTICAL_PIPE_WITH_BRICK 11002
#define ID_SPRITE_SUPER_HIGH_PIPE_WITH_BRICK 11003
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define PIPE_CONTENT_NONE 1
#define PIPE_CONTENT_NO_FIRE_GREEN_PLANT 2
#define PIPE_CONTENT_FIRE_GREEN_PLANT 3
#define PIPE_CONTENT_FIRE_RED_PLANT 4
class CPipe : public CGameObject {
	float height;
	float width;
	int spriteId;
	int typeContent;
	CGameObject* content;
public:
	CPipe(float x, float y, float width = 31, float height = 31, int spriteId = 11001, int typeContent = PIPE_CONTENT_NO_FIRE_GREEN_PLANT) : CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
		this->spriteId = spriteId;

		switch (typeContent)
		{
		case PIPE_CONTENT_NONE:
			content = NULL;
			break;
		case PIPE_CONTENT_NO_FIRE_GREEN_PLANT:
			content = new CNoFirePlant(x, y - (height / 2 - NO_FIRE_GREEN_PLANT_HEIGHT / 2), FIRE_GREEN_PLANT, this); // 24
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(content); //view push back in objects, may by leads to wrong index render
			break;
		case PIPE_CONTENT_FIRE_GREEN_PLANT:
			//content = new CFirePlant(x, y, this);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(content);
			break;
		case PIPE_CONTENT_FIRE_RED_PLANT:
			//content = new CFirePlant(x, y, this);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(content);
			break;
		}
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};