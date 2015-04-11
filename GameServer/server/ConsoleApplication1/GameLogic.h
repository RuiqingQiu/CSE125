
/* GameLogic.h */
#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "Network.h"
#include "GamePhysics.h"
#include "definition.h"
#include "TimeFrame.h"


class GameLogic {
private:
	Network* network;
	GamePhysics* gamePhysics;
	TimeFrame* countDown;
	int asd = 1;


	std::vector<GameObj*> gameObjs;
	std::map<int, GameObj *> clientPair;
	std::vector<Events *> elist;
public:
	GameLogic();
	~GameLogic();
	unsigned int waitToConnect();
	void pushGameObj(GameObj*);
	std::vector<GameObj*> getGameObjs();
	unsigned int gameLoop();
	void gameStart();
	void prePhyLogic();
};
#endif