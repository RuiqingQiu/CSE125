#include "stdafx.h"
#include "GameCore.h"
#include "StandardGameInput.h"

GameCore* g_pCore = new GameCore();

GameCore::GameCore()
{
	gameGui = new gui();
	pGameView = new GameView();
	pGamePacketManager = new GamePacketManager();
	pPlayer = new GamePlayer();
	i_pInput = new StandardGameInput();

	//pGameView->pPlayer = pPlayer;
}


GameCore::~GameCore()
{

}


