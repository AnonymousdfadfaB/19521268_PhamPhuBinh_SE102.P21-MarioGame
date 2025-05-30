#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
#include "PlantEnemy.h"

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
	CPipe(float x, float y, float width, float height, int spriteId, int typeContent) : CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
		this->spriteId = spriteId;
		this->typeContent = typeContent;
		switch (typeContent)
		{
		case PIPE_CONTENT_NONE:
			content = NULL;
			break;
		case PIPE_CONTENT_NO_FIRE_GREEN_PLANT:
			content = new CPlantEnemy(x, y - (height / 2 - NO_FIRE_GREEN_PLANT_HEIGHT / 2), NO_FIRE_GREEN_PLANT, this); // 24
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(content); //view push back in objects, may by leads to wrong index render
			break;
		case PIPE_CONTENT_FIRE_GREEN_PLANT:
			content = new CPlantEnemy(x, y - (height / 2 - FIRE_GREEN_PLANT_HEIGHT / 2), FIRE_GREEN_PLANT, this); // 24
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(content); //view push back in objects, may by leads to wrong index render
			break;
		case PIPE_CONTENT_FIRE_RED_PLANT:
			content = new CPlantEnemy(x, y - (height / 2 - FIRE_RED_PLANT_HEIGHT / 2), FIRE_RED_PLANT, this); // 24
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(content); //view push back in objects, may by leads to wrong index render
			break;
		}
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};