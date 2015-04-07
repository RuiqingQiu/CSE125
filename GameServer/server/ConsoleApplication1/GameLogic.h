
/* GameLogic.h */
#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "Network.h"
#include "GamePhysics.h"
class GameLogic {
private:
	Network* network;
	GamePhysics* gamePhysics;


	std::vector<GameObj*> gameObjs;
	std::map<unsigned int, GameObj *> clientPair;
	std::vector<Events *> elist;
public:
	GameLogic();
	~GameLogic();
	unsigned int waitToConnect();
	void pushGameObj(GameObj*);
	std::vector<GameObj*> getGameObjs();

};
#endif
