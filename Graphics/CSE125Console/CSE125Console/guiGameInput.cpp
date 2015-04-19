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

	if (key == '1') {
		g_pCore->viewmode = guiType::BUILD;
	}
	else if (key == '2') {
		g_pCore->viewmode = guiType::BATTLE;
	}
	else if (key == '3') {
		g_pCore->viewmode = guiType::HELP;
	}
	else if (key == '4') {
		g_pCore->viewmode = guiType::MENU;
	}
	else if (key == '5') {
		g_pCore->viewmode = guiType::CONSOLE;
	}
	setGui();
}

void guiGameInput::VProcessMouseClick(int button, int state, int x, int y) {
	//check which button was pressed here
	g_pCore->gameGui->onClick(state, x, y);

	guiType s = g_pCore->gameGui->switchClicked(state, x, y);
	if (s != g_pCore->viewmode) {
		g_pCore->viewmode = s;
		setGui();
	}
	else if (g_pCore->gameGui->helpClicked(state, x, y)) {
		g_pCore->viewmode = guiType::HELP;
		setGui();
	}
}


void guiGameInput::setGui() {
	
	if (g_pCore->viewmode == guiType::BUILD) {
		g_pCore->gameGui = g_pCore->buildmode;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::BATTLE) {
		g_pCore->gameGui = g_pCore->battlemode;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::HELP) {
		g_pCore->gameGui = g_pCore->helpMenu;
		if (g_pCore->pGameView->FindGeoNode(g_pCore->skybox))
			g_pCore->pGameView->PopGeoNode(g_pCore->skybox);
		g_pCore->i_pInput = g_pCore->gui_Input;
	}
	else if (g_pCore->viewmode == guiType::MENU) {
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
}