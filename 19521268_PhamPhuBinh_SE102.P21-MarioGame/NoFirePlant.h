#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
//#include "Pipe.h" due to loop of include dependency
//operation parameters 
#define HIDE_DURATION 2000.0f
#define ATTACK_DURATION 2000.0f
#define NO_FIRE_GREEN_PLANT_VERTICAL_SPEED 0.05f
//width and height
#define NO_FIRE_GREEN_PLANT_WIDTH 16
#define NO_FIRE_GREEN_PLANT_HEIGHT 24

#define FIRE_GREEN_PLANT_WIDTH 16
#define FIRE_GREEN_PLANT_HEIGHT 24

#define FIRE_RED_PLANT_WIDTH 16
#define FIRE_RED_PLANT_HEIGHT 32
//states
#define	HIDE_STATE 100
#define RISE_STATE 101
#define ATTACK_STATE 102
#define DOWN_STATE 103
#define DIE_STATE 104
//animation ids
#define NO_FIRE_GREEN_PLANT_ANI_ID 84001

#define FIRE_GREEN_PLANT_LEFT_TOP_ANI_ID 85001
#define FIRE_GREEN_PLANT_RIGHT_TOP_ANI_ID 85002
#define FIRE_GREEN_PLANT_LEFT_BOTTOM_ANI_ID 85003
#define FIRE_GREEN_PLANT_RIGHT_BOTTOM_ANI_ID 85004

//type
#define NO_FIRE_GREEN_PLANT 1
#define FIRE_GREEN_PLANT 2
#define FIRE_RED_PLANT	3
//mario position
#define MARIO_POSITION_LEFT_TOP 1
#define MARIO_POSITION_RIGHT_TOP 2
#define MARIO_POSITION_LEFT_BOTTOM 3
#define MARIO_POSITION_RIGHT_BOTTOM 4
class CNoFirePlant : public CGameObject
{
protected:
	CGameObject* pipe;
	int type;
	float maxY;
	float minY;
	bool canFire;
	bool alreadyFire;
	ULONGLONG hide_start;
	ULONGLONG attack_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetMarioRelativePosition();

public:
	CNoFirePlant(float x, float y, int type, CGameObject* pipe);
	virtual void SetState(int state);
};