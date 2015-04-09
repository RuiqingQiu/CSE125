#pragma once
#include <map>
#include "definition.h"

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

