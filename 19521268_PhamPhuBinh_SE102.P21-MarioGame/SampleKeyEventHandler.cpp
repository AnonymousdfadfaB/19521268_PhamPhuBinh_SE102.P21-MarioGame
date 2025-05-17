#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			mario->IsGoRight() ? mario->AttackLeft() : mario->AttackRight();
		}
		break;
	case DIK_S:
		if (mario->IsOnPlatform())
			mario->SetState(MARIO_STATE_JUMP);
		else if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			if (abs(mario->GetVx()) >= MARIO_RUNNING_SPEED)
				mario->SetState(MARIO_STATE_FLY);
			else
				mario->SetState(MARIO_STATE_LIGHTLY_FLY); // if not running, jump
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->IsOnPlatform()) {
		if (game->IsKeyDown(DIK_DOWN))
		{
			mario->SetState(MARIO_STATE_SIT);
		}
		else if (game->IsKeyDown(DIK_RIGHT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
	else
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			mario->SetState(MARIO_STATE_GLIDE_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			mario->SetState(MARIO_STATE_GLIDE_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_FALL);
	}
	
}