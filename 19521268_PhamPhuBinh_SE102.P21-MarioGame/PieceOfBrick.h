#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define PIECE_OF_BRICK_GRAVITY 0.001f
#define PRICE_OF_BRICK_HORIZONTAL_SPEED 0.1;
#define PRICE_OF_BRICK_SLIGHTLY_VERTICAL_SPEED 0.1;
#define PRICE_OF_BRICK_HIGH_VERTICAL_SPEED 0.2;
#define PIECE_OF_BRICK_SPRITE_ID 15110
#define PIECE_OF_BRICK_WIDTH 4
#define PIECE_OF_BRICK_HEIGHT 4
#define PIECE_OF_BRICK_LEFT_TOP_DIRECTION 1
#define PIECE_OF_BRICK_LEFT_BOTTOM_DIRECTION 2
#define PIECE_OF_BRICK_RIGHT_TOP_DIRECTION 3
#define PIECE_OF_BRICK_RIGHT_BOTTOM_DIRECTION 4

class CPieceOfBrick : public CGameObject {
public:
	CPieceOfBrick(float x, float y, int direction);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsBlocking() { return 0; }

	// Does this object collide with other object at certain direction ( like ColorBox )
	int IsDirectionColliable(float nx, float ny) { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) 
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	};
};
