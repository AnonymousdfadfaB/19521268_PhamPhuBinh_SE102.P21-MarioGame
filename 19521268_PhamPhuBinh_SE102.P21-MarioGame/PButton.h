#pragma once
#include "GameObject.h"

#define PBUTTON_WIDTH 16
#define UNPRESS_PBUTTON_HEIGHT 16
#define PRESS_PBUTTON_HEIGHT 6
#define UNPRESSED_PBUTTON_ANI_ID 18121
#define PRESSED_PBUTTON_ANI_ID 18122


class CPButton : public CGameObject
{

protected:
	bool pressed;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	void Render();

	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }


public:
	CPButton(float x, float y);
	int IsDirectionColliable(float nx, float ny);
	void PressOn();
};
#pragma once
