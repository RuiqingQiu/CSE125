#pragma once
#include "GameState.h"
#include "GameLogic.h"
#include "definition.h"

class ServerCore
{
	GameState* gameState;
	GameLogic* gameLogic;

public:
	ServerCore();
	~ServerCore();
	void serverLoop(void)

};

