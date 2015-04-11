#include "stdafx.h"
#include "guiGameInput.h"


guiGameInput::guiGameInput()
{
}


guiGameInput::~guiGameInput()
{
}

void guiGameInput::VProcessKeyInput(unsigned char key, int x, int y) {
	//no key input yet except switching modes

	//in g_pCore->viewmode:
	//1: build View
	//2: battle View
	//3: help menu
	//4: main menu
	//5: switch to console
	if (key == '1') {
		g_pCore->viewmode = 1;
		g_pCore->gameGui = g_pCore->buildmode;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
	}
	else if (key == '2') {
		g_pCore->viewmode = 2;
		g_pCore->gameGui = g_pCore->defaultGui;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
	}
	else if (key == '3') {
		g_pCore->viewmode = 3;
		g_pCore->gameGui = g_pCore->defaultGui;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
	}
	else if (key == '4') {
		g_pCore->viewmode = 4;
		g_pCore->gameGui = g_pCore->defaultGui;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
	}
	else if (key == '5') {
		g_pCore->viewmode = 5;
		g_pCore->gameGui = g_pCore->defaultGui;
		if (!g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PushGeoNode(g_pCore->skybox);
	}
}

void guiGameInput::VProcessMouseClick(int button, int state, int x, int y) {
	//check which button was pressed here
}