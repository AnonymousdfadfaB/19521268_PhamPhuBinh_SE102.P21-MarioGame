#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "BrownGoomba.h"
#include "RedGoomba.h"
#include "SceneObject.h"
#include  "WoodBlock.h"
#include "Cloud.h"
#include "VictoryFlower.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> waitObjects;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();
	void AddObject(LPGAMEOBJECT object) { objects.push_back(object); }
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void PressPButton();
};

typedef CPlayScene* LPPLAYSCENE;

