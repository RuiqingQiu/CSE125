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
	g_pCore->setGui();
}

void guiGameInput::VProcessSpecialKey(int key, int x, int y) {

}

void guiGameInput::VProcessMouseClick(int button, int state, int x, int y) {
	//check which button was pressed here
	g_pCore->gameGui->onClick(state, x, y);

	guiType s = g_pCore->gameGui->switchClicked(state, x, y);
	if (s != g_pCore->viewmode) {
		g_pCore->viewmode = s;
		g_pCore->setGui();
	}
	else if (g_pCore->gameGui->helpClicked(state, x, y)) {
		g_pCore->viewmode = guiType::HELP;
		g_pCore->setGui();
	}
}

void guiGameInput::VProcessPassiveMouse(int x, int y) {
	g_pCore->gameGui->passiveMouseFunc(x, y);
}