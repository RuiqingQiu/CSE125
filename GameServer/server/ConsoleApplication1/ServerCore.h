#pragma once
#include "GameState.h"
#include "GameLogic.h"
#include "TimeFrame.h"

class ServerCore
{
	TimeFrame* timeFrame;
	GameState* gameState;
	GameLogic* gameLogic;

public:
	ServerCore();
	~ServerCore();
	void serverLoop(void);

};

