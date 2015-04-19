#include "stdafx.h"
#include "GameCore.h"
#include "StandardGameInput.h"
#include "guiGameInput.h"

GameCore* g_pCore = new GameCore();
float GameCore::width = 512;   //Set window width in pixels here
float GameCore::height = 512;   //Set window height in pixels here
GameCore::GameCore()
{
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
void GameCore::setView() {
	//hacky quick fix
	g_pCore->buildmode->updateview = false;

	g_pCore->pGameView->isCurrentView = false;
	//sky boxes needed for battle mode and console.
	//not needed for menus and build mode
	if (g_pCore->viewmode == viewType::BUILD) {
		g_pCore->helpMenu->returnTo = viewType::BUILD;
		g_pCore->pGameView = g_pCore->buildmode;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == viewType::BATTLE) {
		g_pCore->pGameView = g_pCore->battlemode;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->standard_Input;
	}
	else if (g_pCore->viewmode == viewType::HELP) {
		g_pCore->pGameView = g_pCore->helpMenu;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == viewType::MENU) {
		g_pCore->helpMenu->returnTo = viewType::MENU;
		g_pCore->pGameView = g_pCore->menumode;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == viewType::CONSOLE) {
		g_pCore->pGameView = g_pCore->defaultView;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->standard_Input;
	}
	g_pCore->pGameView->isCurrentView = true;
}

