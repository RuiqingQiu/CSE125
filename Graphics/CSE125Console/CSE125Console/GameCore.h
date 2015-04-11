#pragma once
#include "stdafx.h"
#include "GameView.h"
#include "gui.h"
#include "GeoNode.h"
#include "SkyBox.h"
#include "GamePacketManager.h"
#include "GamePlayer.h"
#include "GameInputInterface.h"
#ifndef CSE125_CORE
#define CSE125_CORE

class GameCore
{
public:
	GameCore();
	~GameCore();

	GameView* pGameView;

	gui* gameGui;

	GamePacketManager* pGamePacketManager;
	GamePlayer* pPlayer;
	GameInputInterface* i_pInput;

	int viewmode;
	gui * buildmode;
	gui * defaultGui;
	GeoNode * skybox;

	GameInputInterface* gui_Input;
	GameInputInterface* standard_Input;
};

extern GameCore* g_pCore;

#endif

