#pragma once
#include "stdafx.h"
#include "GameView.h"
#include "GamePacketManager.h"
#include "GamePlayer.h"
#include "GameInputInterface.h"
class GameCore
{
public:
	GameCore();
	~GameCore();
	GameView* pGameView;
	GamePacketManager* pGamePacketManager;
	GamePlayer* pPlayer;
	GameInputInterface* i_pInput;
};

extern GameCore* g_pCore;


