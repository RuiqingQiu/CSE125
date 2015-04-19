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
	switch (key) {
		case '1':
			g_pCore->viewmode = guiType::BUILD;
			break;
		case '2':
			g_pCore->viewmode = guiType::BATTLE;
			break;
		case '3':
			g_pCore->viewmode = guiType::HELP;
			break;
		case '4':
			g_pCore->viewmode = guiType::MENU;
			break;
		case '5':
			g_pCore->viewmode = guiType::CONSOLE;
			break;
		default:
			break;
	}
	g_pCore->setGui();
}

void guiGameInput::VProcessSpecialKey(int key, int x, int y) {
	switch (key) {
		//move the new block to be added to the robot
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_RIGHT:
			break;
		default:
			break;
	}

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

	//buildmode input for game logic checks
	if (g_pCore->gameGui != g_pCore->buildmode) return;


	if (g_pCore->buildmode->addBlock(state, x, y)) {
		//add geonode to robot
	}
	else if (g_pCore->buildmode->removeBlock(state, x, y)) {
		//remove geonode from robot
	}

	//if no button was pressed, rotate the robot
}

void guiGameInput::VProcessPassiveMouse(int x, int y) {
	g_pCore->gameGui->passiveMouseFunc(x, y);
}