#include "stdafx.h"
#include "StandardGameInput.h"


StandardGameInput::StandardGameInput()
{
	sound = new Sound();
	for (int i = 0; i < 256; i++){
		keyStates[i] = false;
	}
}


StandardGameInput::~StandardGameInput()
{
}
static int mx,my;
void StandardGameInput::VProcessMouseClick(int button, int state, int x, int y) {
	//do nothing for now, need this function in gui
	if (button == GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
	{
		printf("right mouse\n");
		g_pCore->pGameView->pViewCamera->IsFollowingEnabled = false;
		mx = x;
		my = y;
	}

	if (button == GLUT_RIGHT_BUTTON&&state == GLUT_UP)
	{
		g_pCore->pGameView->pViewCamera->IsFollowingEnabled = true;
		printf("release mouse\n");
	}
}

void StandardGameInput::VProcessSpecialKey(int key, int x, int y) {
	//do nothing for now, need this function in gui
}
void StandardGameInput::VProcessPassiveMouse(int x, int y) {
	//do nothing for now, need this function in gui


}

void StandardGameInput::VProcessMouse(int x, int y)
{
	if (g_pCore->pGameView->pViewCamera->IsFollowingEnabled == false){
		int delx = x - mx;
		int dely = y - my;
		float deltaAnglex = (delx) * 0.001f;
		float deltaAngley = (dely)* 0.001f;
		g_pCore->pGameView->pViewCamera->rotation->x = dely%360;
		g_pCore->pGameView->pViewCamera->rotation->y = delx%360;

	}
}


void StandardGameInput::VProcessKeyInput(unsigned char key, int x, int y)
{

	if (key == 27){
		exit(0);
	}
	if (key == 'a'){
		if (keyStates['a'] != true){
			keyStates['a'] = true;
			g_pCore->pGamePacketManager->SendMoveToLeft(g_pCore->pPlayer->playerid);
		}
	}
	if (key == 'w'){
		if (keyStates['w'] != true){
			keyStates['w'] = true;
			g_pCore->pGamePacketManager->SendMoveToForward(g_pCore->pPlayer->playerid);
		}
	}
	if (key == 's'){
		if (keyStates['s'] != true){
			keyStates['s'] = true;
			g_pCore->pGamePacketManager->SendMoveToBackward(g_pCore->pPlayer->playerid);
		}
	}
	if (key == 'd'){
		if (keyStates['d'] != true){
			keyStates['d'] = true;

			g_pCore->pGamePacketManager->SendMoveToRight(g_pCore->pPlayer->playerid);
		}
	}
	else if (key == 'q'){
		g_pCore->pGamePacketManager->SendShootEvent(g_pCore->pPlayer->playerid);
		// play explosion sound here
		float x = 0;
		float y = 0;
		float z = 0;
		sound->playExplosion(x, y, z);
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
		g_pCore->pGameView->pViewCamera->position->y += 0.1;
	}
	else if (key == 'X'){
		g_pCore->pGameView->pViewCamera->position->y -= 0.1;
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
	else if (key == 'r'){
		g_pCore->pGameView->pViewCamera->mode = (g_pCore->pGameView->pViewCamera->mode + 1) % 2;
	}
	else if (key == 'i'){
	}
	else if (key == 'k'){
	}
	else if (key == 'l'){
	}
}

void StandardGameInput::VProcessKeyInputUp(unsigned char key, int x, int y){
	cout << "key up " << key << endl;
	if (key == 'a'){
		keyStates['a'] = false;
	}
	if (key == 'w'){
		keyStates['w'] = false;
	}
	if (key == 's'){
		keyStates['s'] = false;
	}
	if (key == 'd'){
		keyStates['d'] = false;
	}
	cout << "keyboard" << keyStates['a']  << " " <<  keyStates['w']  << " " << keyStates['s']  << " "<< keyStates['d'] << endl;

}
