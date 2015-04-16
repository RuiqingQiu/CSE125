#include "stdafx.h"
#include "GameCore.h"
#include "StandardGameInput.h"
#include "guiGameInput.h"

GameCore* g_pCore = new GameCore();
float GameCore::width = 512;   //Set window width in pixels here
float GameCore::height = 512;   //Set window height in pixels here
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


