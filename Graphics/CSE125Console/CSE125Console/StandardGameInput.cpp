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
		g_pCore->pGamePacketManager->SendMoveToLeft(1);
	}
	else if (key == 'w'){
		g_pCore->pGamePacketManager->SendMoveToForward(1);
	}
	else if (key == 's'){
		g_pCore->pGamePacketManager->SendMoveToBackward(1);
	}
	else if (key == 'd'){
		g_pCore->pGamePacketManager->SendMoveToRight(1);
	}
}
