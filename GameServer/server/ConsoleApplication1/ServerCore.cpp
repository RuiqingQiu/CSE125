#include "ServerCore.h"


ServerCore::ServerCore()
{
	gameState = new GameState();
	gameLogic = new GameLogic();
}


ServerCore::~ServerCore()
{
	delete gameLogic;
	delete gameState;
}



void ServerCore::serverLoop()
{
	int timeFrame = 1000;

	while (true)
	{
		//unsigned t0 = clock();
		unsigned int action;

		switch (gameState->getState())
		{
		case INIT_STATE0:
			action = gameLogic->waitToConnect();
		default:
			action = WAIT; 
			break;
		}

		gameState->nextState(action);


		//cout << "Sleep the frame." << endl;
		//unsigned elapsed = clock() - t0;
		////TimeFrame::frameSleep(timeFrame - elapsed);
		//Sleep(timeFrame - elapsed);
		////cout << elapsed << endl;
		//cout << "Frame has completed sleeping." << endl;
	}
}