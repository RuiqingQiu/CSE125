#pragma once
	//ACTIONS FOR STATE MACHINE
	enum ACTION
	{
		WAIT = 0,
		ADDCLIENT = 1,
		TIMEUP = 2,
		COUNTDOWN = 3,
		RESTART = 4,
	};


	//game states
	enum STATE {
		INIT_STATE0 = 0,
		INIT_STATE1 = 1,
		INIT_STATE2 = 2,
		INIT_STATE3 = 3,
		BUILD_STATE = 4,
		GAME_STATE0 = 5,
		END_STATE = 8,

	};

#define oneStep 0.1
#define TIMEFRAME 300;