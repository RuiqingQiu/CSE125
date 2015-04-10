#pragma once
#include "stdafx.h"
#include "GameView.h"
#include "gui.h"
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

	gui* mainView;
	gui* buildView;
	gui* battleView;

	GamePacketManager* pGamePacketManager;
	GamePlayer* pPlayer;
	GameInputInterface* i_pInput;
};

extern GameCore* g_pCore;

#endif

