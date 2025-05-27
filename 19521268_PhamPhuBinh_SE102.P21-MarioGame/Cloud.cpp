#include "Cloud.h"

CCloud::CCloud(float x, float y) : CGameObject(x, y)
{

}
void CCloud::Render()
{
	CSprites::GetInstance()->Get(CLOUD_SPRITE_ID)->Draw(x, y);
}

void CCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CLOUD_WIDTH / 2;
	t = y - CLOUD_HEIGHT / 2;
	r = l + CLOUD_WIDTH;
	b = t + CLOUD_HEIGHT;
}
int CCloud::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}