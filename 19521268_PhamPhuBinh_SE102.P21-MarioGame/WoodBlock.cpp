#include "WoodBlock.h"

void CWoodBlock::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(WOODBLOCK_SPRITE_ID)->Draw(x, y);
}

void CWoodBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WOODBLOCK_WIDTH / 2;
	t = y - WOODBLOCK_HEIGHT / 2;
	r = l + WOODBLOCK_WIDTH;
	b = t + WOODBLOCK_HEIGHT;
}