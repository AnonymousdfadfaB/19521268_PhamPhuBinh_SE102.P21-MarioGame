#pragma once
#include "PButton.h"
#include "Game.h"
#include "PlayScene.h"
CPButton::CPButton(float x, float y) : CGameObject(x, y)
{
	pressed = false;
}
void CPButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (pressed)
		animations->Get(PRESSED_PBUTTON_ANI_ID)->Render(x, y);
	else
		animations->Get(UNPRESSED_PBUTTON_ANI_ID)->Render(x, y);
}

void CPButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (pressed)
	{
		l = x - PBUTTON_WIDTH / 2;
		t = y - PRESS_PBUTTON_HEIGHT / 2;
		r = l + PBUTTON_WIDTH;
		b = t + PRESS_PBUTTON_HEIGHT;
	} 
	else
	{
		l = x - PBUTTON_WIDTH / 2;
		t = y - UNPRESS_PBUTTON_HEIGHT / 2;
		r = l + PBUTTON_WIDTH;
		b = t + UNPRESS_PBUTTON_HEIGHT;
	}
}
void CPButton::PressOn()
{
	if (pressed) return;
	pressed = TRUE;
	y += (UNPRESS_PBUTTON_HEIGHT - PRESS_PBUTTON_HEIGHT) / 2;
	//impact
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->PressPButton();
}
int CPButton::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}
