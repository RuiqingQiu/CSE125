#include "stdafx.h"
#include "StandardGameInput.h"


StandardGameInput::StandardGameInput()
{
}


StandardGameInput::~StandardGameInput()
{
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
}
