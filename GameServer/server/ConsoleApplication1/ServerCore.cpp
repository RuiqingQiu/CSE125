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
	gameLogic->numPlayers = 2;
	while (true)
	{
		timeFrame->startClock();
		//unsigned t0 = clock();
		unsigned int action;
		switch (gameState->getState())
		{
		case INIT_STATE0:{
			action = gameLogic->waitToConnect();
			if (gameLogic->numPlayers < 1) action = ADDCLIENT;
			cout << "action for init0: " << action << endl;
			break;
		}
		case INIT_STATE1:
		{	
			action = gameLogic->waitToConnect();
			if (gameLogic->numPlayers < 2) action = ADDCLIENT;
			cout << "action for init1: " << action << endl;
			break;
		}
		case INIT_STATE2:
		{	
			action = gameLogic->waitToConnect();
			if (gameLogic->numPlayers < 3) action = ADDCLIENT;
			cout << "action for init2: " << action << endl;
			break;
		}
		case INIT_STATE3:
		{	
			action = gameLogic->waitToConnect();
			if (gameLogic->numPlayers< 4) action = ADDCLIENT;
			cout << "action for init3: " << action << endl;
			break;
		}
		case INIT_BUILD_STATE:
		{
			action = gameLogic->startBuild();
			break;
		}
		case BUILD_STATE:
		{	
		    action=	gameLogic->buildMode();
			//gameLogic->gameStart();
		    //action = TIMEUP;
			break;
		}
		case INIT_GAME: 
		{
			 cout << "init game start " << endl;
			 action = gameLogic->gameStart();
			 break;
		}
		case GAME_STATE0:
		{	
			action = gameLogic->gameLoop();
			break;
		}
		case CLEAR_STATE:{
		    action = gameLogic->clearGame();
			break;
		}
		case END_STATE:{
 		    action = gameLogic->endGame();
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