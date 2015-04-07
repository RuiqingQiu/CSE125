#include "GameState.h"


GameState::GameState()
{


	init0map[WAIT] = INIT_STATE0;
	init0map[ADDCLIENT] = INIT_STATE1;

	init1map[WAIT] = INIT_STATE1;
	init1map[ADDCLIENT] = INIT_STATE2;

	init2map[WAIT] = INIT_STATE2;
	init2map[ADDCLIENT] = INIT_STATE3;

	init3map[WAIT] = INIT_STATE3;
	init3map[ADDCLIENT] = BUILD_STATE;

	buildmap[COUNTDOWN] = BUILD_STATE;
	buildmap[TIMEUP] = GAME_STATE;


	gamemap[COUNTDOWN] = GAME_STATE;
	gamemap[TIMEUP] = END_STATE;

	endmap[RESTART] = INIT_STATE0;


	STATEMAP[INIT_STATE0] = init0map;
	STATEMAP[INIT_STATE1] = init1map;
	STATEMAP[INIT_STATE2] = init2map;
	STATEMAP[INIT_STATE3] = init3map;
	STATEMAP[BUILD_STATE] = buildmap;
	STATEMAP[GAME_STATE] = gamemap;
	STATEMAP[END_STATE] = endmap;



}


GameState::~GameState()
{
}


unsigned int GameState::getState()
{
	return state;
}

void GameState::nextState(unsigned int action)
{
	state = ((STATEMAP.find(state))->second).find(action)->second;
}
