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
}
