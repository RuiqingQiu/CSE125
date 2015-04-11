#include "stdafx.h"
#include "GameCore.h"
#include "StandardGameInput.h"
#include "guiGameInput.h"

GameCore* g_pCore = new GameCore();

GameCore::GameCore()
{
	gameGui = new gui();
	pGameView = new GameView();
	pGamePacketManager = new GamePacketManager();
	pPlayer = new GamePlayer();
	gui_Input = new guiGameInput();
	standard_Input = new StandardGameInput();
	i_pInput = standard_Input;

	//pGameView->pPlayer = pPlayer;
}


GameCore::~GameCore()
{

}


