#include "SceneObject.h"

CSceneObject::CSceneObject(float x, float y, int spriteId) : CGameObject(x, y)
{
	this->spriteId = spriteId;
}
void CSceneObject::Render()
{
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}


