#include "Card.h"

CCard::CCard(float x, float y, float width, float height, int spriteId) : CGameObject(x, y) 
{
	this->width = width;
	this->height = height;
	this->spriteId = spriteId;
}
void CCard::Render()
{
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);

}

void CCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = l + width;
	b = t + height;
}
int CCard::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}