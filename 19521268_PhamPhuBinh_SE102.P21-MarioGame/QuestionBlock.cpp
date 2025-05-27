#include "QuestionBlock.h"
#include "Game.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBlock::Render()
{
	if (!hit) {
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_QUESTIONBLOCK)->Render(x, y);
	}
	else {
		CSprites* sprites = CSprites::GetInstance();
		sprites->Get(ID_SPRITE_QUESTIONBLOCK_AFTER_HIT)->Draw(x, y);
	}

	//RenderBoundingBox();
}
void CQuestionBlock::GenerateCoin() {
	content = new CCoin(x, y,BOUNCE_COIN);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(content);
}
void CQuestionBlock::GenerateRedMushroom() {
	content = new CMushroom(x, y, RED_MUSHROOM);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(content);
}
void CQuestionBlock::GenerateGreenMushroom() {
	content = new CMushroom(x, y, GREEN_MUSHROOM);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(content);
}
void CQuestionBlock::GenerateLeaf() {
	content = new CLeaf(x, y);
	content->SetSpeed(0, -LEAF_BOUNCE_SPEED);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(content);
}
void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
	t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBLOCK_BBOX_WIDTH;
	b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}