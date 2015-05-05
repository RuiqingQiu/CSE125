#include "ServerCore.h"


ServerCore::ServerCore()
{
	timeFrame = new TimeFrame();
	gameState = new GameState();
	gameLogic = new GameLogic();
}


ServerCore::~ServerCore()
{
	delete gameLogic;
	delete gameState;
	delete timeFrame;
}



void ServerCore::serverLoop()
{
	int numPlayer =1;
	
	while (true)
	{
		timeFrame->startClock();
		//unsigned t0 = clock();
		unsigned int action;
		switch (gameState->getState())
		{
		case INIT_STATE0:{
			action = gameLogic->waitToConnect();
			if(numPlayer < 1) action = ADDCLIENT;
			cout << "action for init0: " << action << endl;
			break;
		}
		case INIT_STATE1:
		{	
			action = gameLogic->waitToConnect();
			if (numPlayer < 2) action = ADDCLIENT;
			cout << "action for init1: " << action << endl;
			break;
		}
		case INIT_STATE2:
		{	
			action = gameLogic->waitToConnect();
			if (numPlayer < 3) action = ADDCLIENT;
			cout << "action for init2: " << action << endl;
			break;
		}
		case INIT_STATE3:
		{	
			action = gameLogic->waitToConnect();
			if (numPlayer < 4) action = ADDCLIENT;
			break;
		}
		case BUILD_STATE:
		{	
			gameLogic->gameStart();
		    action = TIMEUP;
			cout << "buildMode" << endl;
			break;
		}
		case GAME_STATE0:
		{	
			action = gameLogic->gameLoop();
			break;
		}
		default:
		{	action = WAIT;
			break;
		}
	}

		gameState->nextState(action);
		//cout << "Sleep the frame." << endl;
		//unsigned elapsed = clock() - t0;
		////TimeFrame::frameSleep(timeFrame - elapsed);
		timeFrame->frameSleep(33 - timeFrame->getElapsedTime()); //;
		////cout << elapsed << endl;
		//cout << "Frame has completed sleeping." << endl;
	}
}