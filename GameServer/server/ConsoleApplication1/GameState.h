#pragma once
#include <map>
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


class GameState
{
	
	
	unsigned int state;
	
	std::map<unsigned int, std::map<unsigned int, unsigned int>> STATEMAP;
	std::map<unsigned int, unsigned int> init0map;
	std::map<unsigned int, unsigned int> init1map;
	std::map<unsigned int, unsigned int> init2map;
	std::map<unsigned int, unsigned int> init3map;
	std::map<unsigned int, unsigned int> buildmap;
	std::map<unsigned int, unsigned int> gamemap;
	std::map<unsigned int, unsigned int> endmap;

	

public:
	GameState();
	~GameState();
	unsigned int getState();
	void nextState(unsigned int);


};

