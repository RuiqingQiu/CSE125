#pragma once
#include "stdafx.h"
#include "GameView.h"
#include "SkyBox.h"
#include "GeoNode.h"
#include "GamePacketManager.h"
#include "GamePlayer.h"
#include "GameInputInterface.h"
#include "EventSystem.h"
#include "Light.h"

#ifndef CSE125_CORE
#define CSE125_CORE

class GameCore
{
public:
	GameCore();
	~GameCore();

	static float width, height;

	GameView* pGameView;
	GamePacketManager* pGamePacketManager;
	GamePlayer* pPlayer;
	GameInputInterface * i_pInput;
	EventSystem * pEventSystem;

	Light* light;
	SkyBox * skybox;
};

extern GameCore* g_pCore;

#endif

