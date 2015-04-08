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
	
	while (true)
	{
		timeFrame->startClock();
		//unsigned t0 = clock();
		unsigned int action;
		switch (gameState->getState())
		{
		case INIT_STATE0:{
							 action = gameLogic->waitToConnect();
		}
		case INIT_STATE1:
		{	action = ADDCLIENT;
		}
		case INIT_STATE2:
		{	action = ADDCLIENT;
		}
		case INIT_STATE3:
		{	action = ADDCLIENT;
		}
		case BUILD_STATE:
		{	gameLogic->gameStart();
		action = TIMEUP;
		}
		case GAME_STATE0:
		{	action = gameLogic->gameLoop();
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
		timeFrame->frameSleep(1000 - timeFrame->getElapsedTime()); //;
		////cout << elapsed << endl;
		//cout << "Frame has completed sleeping." << endl;
	}
}