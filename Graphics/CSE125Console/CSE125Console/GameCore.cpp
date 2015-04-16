#include "stdafx.h"
#include "GameCore.h"
#include "StandardGameInput.h"

GameCore* g_pCore = new GameCore();
float GameCore::width = 512;   //Set window width in pixels here
float GameCore::height = 512;   //Set window height in pixels here
GameCore::GameCore()
{
	pGameView = new GameView();
	pGamePacketManager = new GamePacketManager();
	pPlayer = new GamePlayer();
	i_pInput = new StandardGameInput();

	//pGameView->pPlayer = pPlayer;
}


GameCore::~GameCore()
{

}


