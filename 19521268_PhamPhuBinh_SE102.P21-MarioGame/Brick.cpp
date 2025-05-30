#include "Brick.h"
#include "FireBall.h"
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_WIDTH/2;
	t = y - BRICK_HEIGHT/2;
	r = l + BRICK_WIDTH;
	b = t + BRICK_HEIGHT;
}
void CBrick::Broken()
{
	isDeleted = true;
	CPieceOfBrick* pieceOfBrick1 = new CPieceOfBrick(x, y, PIECE_OF_BRICK_LEFT_TOP_DIRECTION);
	CPieceOfBrick* pieceOfBrick2 = new CPieceOfBrick(x, y, PIECE_OF_BRICK_LEFT_BOTTOM_DIRECTION);
	CPieceOfBrick* pieceOfBrick3 = new CPieceOfBrick(x, y, PIECE_OF_BRICK_RIGHT_TOP_DIRECTION);
	CPieceOfBrick* pieceOfBrick4 = new CPieceOfBrick(x, y, PIECE_OF_BRICK_RIGHT_BOTTOM_DIRECTION);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(pieceOfBrick1);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(pieceOfBrick2);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(pieceOfBrick3);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(pieceOfBrick4);
	if (contentType == BRICK_CONTENT_TYPE_PBUTTON)
	{
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(new CQuestionBlock(x, y, QUESTIONBLOCK_CONTENT_TYPE_NOPE, true));
		//dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(new CPButton(x, y - QUESTIONBLOCK_BBOX_WIDTH / 2 - PBUTTON_WIDTH / 2));
	}
}