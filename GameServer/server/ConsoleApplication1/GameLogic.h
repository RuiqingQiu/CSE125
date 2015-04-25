
/* GameLogic.h */
#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "Network.h"
#include "GamePhysics.h"
#include "definition.h"
#include "TimeFrame.h"
#include "DamageSystem.h"
#include "GameEvents.h"
#include "GameState.h"
#include <math.h>

#define FIELD_WIDTH 50
#define FIELD_HEIGHT 50


class GameLogic {
private:
	Network* network;
	GamePhysics* gamePhysics;
	TimeFrame* countDown;
	DamageSystem* damageSystem;
	int asd = 1;


	std::vector<GameObj*> gameObjs;
	std::map<int, GameObj *> clientPair;
	std::map< btCollisionObject*, GameObj*> objCollisionPair;
	std::vector<Constraint*> constraints;
	std::vector<ObjectEvents *> objEventList;
    std::vector<GameEvents *> gameEventList;

public:
	GameLogic();
	~GameLogic();
	unsigned int waitToConnect();
	void pushGameObj(GameObj*);
	std::vector<GameObj*> getGameObjs();
	unsigned int gameLoop();
	void gameStart();
	void prePhyLogic();
	void addWalls();
	void addGround();
	void postPhyLogic();

};
#endif