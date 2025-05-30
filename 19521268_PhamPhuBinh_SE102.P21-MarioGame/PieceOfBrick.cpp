#pragma once
#include "PieceOfBrick.h"

/*
void CPieceOfBrick::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(PIECE_OF_BRICK_SPRITE_ID)->Draw(x, y);
}*/
void CPieceOfBrick::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	vy += PIECE_OF_BRICK_GRAVITY * dt;
}

