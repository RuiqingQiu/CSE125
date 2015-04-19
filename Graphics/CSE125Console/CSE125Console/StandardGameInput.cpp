#include "stdafx.h"
#include "StandardGameInput.h"


StandardGameInput::StandardGameInput()
{
}


StandardGameInput::~StandardGameInput()
{
}

void StandardGameInput::VProcessMouseClick(int button, int state, int x, int y) {
	//do nothing for now, need this function in gui
}

void StandardGameInput::VProcessKeyInput(unsigned char key, int x, int y)
{
	if (key == 27){
		exit(0);
	}
	else if (key == 'a'){
		cout << g_pCore->pGamePacketManager->SendMoveToLeft(g_pCore->pPlayer->playerid) << endl;
	}
	else if (key == 'w'){
		g_pCore->pGamePacketManager->SendMoveToForward(g_pCore->pPlayer->playerid);
	}
	else if (key == 's'){
		g_pCore->pGamePacketManager->SendMoveToBackward(g_pCore->pPlayer->playerid);
	}
	else if (key == 'd'){
		g_pCore->pGamePacketManager->SendMoveToRight(g_pCore->pPlayer->playerid);
	}
	else if (key == 'z'){
		//g_pCore->pGameView->pViewCamera.rotateLeft();
		g_pCore->pGameView->pViewCamera->position->x -= 1;
	}
	else if (key == 'Z'){
		g_pCore->pGameView->pViewCamera->position->x += 1;
	}
	else if (key == 'c'){
		g_pCore->pGameView->pViewCamera->position->z += 1;
	}
	else if (key == 'C'){
		g_pCore->pGameView->pViewCamera->position->z -= 1;
	}
	else if (key == 'x'){
		g_pCore->pGameView->pViewCamera->position->y += 1;
	}
	else if (key == 'X'){
		g_pCore->pGameView->pViewCamera->position->y -= 1;
	}
	else if (key == 'v'){
		g_pCore->pGameView->pViewCamera->rotation->x += 10;
	}
	else if (key == 'V'){
		g_pCore->pGameView->pViewCamera->rotation->x -= 10;
	}
	else if (key == 'b'){
		g_pCore->pGameView->pViewCamera->rotation->y += 10;
	}
	else if (key == 'B'){
		g_pCore->pGameView->pViewCamera->rotation->y -= 10;
	}
	else if (key == 'n'){
		g_pCore->pGameView->pViewCamera->rotation->z += 10;
	}
	else if (key == 'N'){
		g_pCore->pGameView->pViewCamera->rotation->z -= 10;
	}
	else if (key == 'j'){
	}
	else if (key == 'i'){
	}
	else if (key == 'k'){
	}
	else if (key == 'l'){
	}
	else if (key == '1') {
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

void StandardGameInput::setGui() {
	
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