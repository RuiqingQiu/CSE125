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
	light = new Light();
	i_pInput = standard_Input;

	light->setPosition(10, 0, 5);
	//pGameView->pPlayer = pPlayer;
}


GameCore::~GameCore()
{

}

//a gui factory
void GameCore::setGui() {
	//hacky quick fix
	g_pCore->buildmode->updateview = false;

	g_pCore->gameGui->isCurrentView = false;
	//sky boxes needed for battle mode and console.
	//not needed for menus and build mode
	if (g_pCore->viewmode == guiType::BUILD) {
		g_pCore->helpMenu->returnTo = guiType::BUILD;
		g_pCore->gameGui = g_pCore->buildmode;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::BATTLE) {
		g_pCore->gameGui = g_pCore->battlemode;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::HELP) {
		g_pCore->gameGui = g_pCore->helpMenu;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::MENU) {
		g_pCore->helpMenu->returnTo = guiType::MENU;
		g_pCore->gameGui = g_pCore->menumode;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::CONSOLE) {
		g_pCore->gameGui = g_pCore->defaultGui;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->standard_Input;
	}
	g_pCore->gameGui->isCurrentView = true;
}

