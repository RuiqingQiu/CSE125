#include "stdafx.h"
#include "guiGameInput.h"


guiGameInput::guiGameInput() : GameInputInterface()
{
}


guiGameInput::~guiGameInput()
{
}

void guiGameInput::VProcessKeyInput(unsigned char key, int x, int y) {
	g_pCore->pGameView->keyPressFunc(key, x, y);
}

void guiGameInput::VProcessSpecialKey(int key, int x, int y) {
	g_pCore->pGameView->specialKeyFunc(key, x, y);
}

void guiGameInput::VProcessMouseClick(int button, int state, int x, int y) {
	//check which button was pressed here
	viewType s = g_pCore->pGameView->mouseClickFunc(state, x, y);
}

void guiGameInput::VProcessPassiveMouse(int x, int y) {
	g_pCore->pGameView->passiveMouseFunc(x, y);
}