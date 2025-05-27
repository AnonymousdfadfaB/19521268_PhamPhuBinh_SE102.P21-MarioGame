#include "Pipe.h"

void CPipe::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(spriteId)->Draw(x, y);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = l + width;
	b = t + height;
}