#pragma once
#include "PieceOfBrick.h"


CPieceOfBrick::CPieceOfBrick(float x, float y, int direction) : CGameObject(x, y)
{
	switch (direction)
	{
	case PIECE_OF_BRICK_LEFT_TOP_DIRECTION:
		vx = -PRICE_OF_BRICK_HORIZONTAL_SPEED;
		vy = PRICE_OF_BRICK_HIGH_VERTICAL_SPEED;
		break;
	case PIECE_OF_BRICK_LEFT_BOTTOM_DIRECTION:
		vx = -PRICE_OF_BRICK_HORIZONTAL_SPEED;
		vy = PRICE_OF_BRICK_SLIGHTLY_VERTICAL_SPEED;
		break;
	case PIECE_OF_BRICK_RIGHT_TOP_DIRECTION:
		vx = PRICE_OF_BRICK_HORIZONTAL_SPEED;
		vy = PRICE_OF_BRICK_HIGH_VERTICAL_SPEED;
		break;
	case PIECE_OF_BRICK_RIGHT_BOTTOM_DIRECTION:
		vx = PRICE_OF_BRICK_HORIZONTAL_SPEED;
		vy = PRICE_OF_BRICK_SLIGHTLY_VERTICAL_SPEED;
		break;
	}
}
void CPieceOfBrick::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(PIECE_OF_BRICK_SPRITE_ID)->Draw(x, y);
}
void CPieceOfBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	vy += PIECE_OF_BRICK_GRAVITY * dt;
}

