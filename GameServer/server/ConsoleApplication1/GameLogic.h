
/* GameLogic.h */
#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "Network.h"
#include "GamePhysics.h"
#include "definition.h"
#include "TimeFrame.h"
#include "DamageSystem.h"
#include "GERobotDeath.h"
#include "GameState.h"
#include <math.h>

#define FIELD_WIDTH 50
#define FIELD_HEIGHT 50
#define INSTANT_KILL 1


class GameLogic {
private:
	Network* network;
	GamePhysics* gamePhysics;
	TimeFrame* countDown;
	DamageSystem* damageSystem;
	int counter;


	std::vector<GameObj*> gameObjs;
	//when you delete a obj, deleteConstraints(), ~() delete rigidBody, set to nullptr
	//
	//check gameObjs vector every X ticks, push !null objs into new_gmaeObjs list
	//gameObjs = new_gameObjs

	std::map<int, GameObj *> clientPair;
	//clear

	std::map< btCollisionObject*, GameObj*> objCollisionPair;
	//clear

	//std::vector<Constraint*> constraints;
	std::vector<ObjectEvents *> objEventList;
    std::vector<GameEvents *> gameEventList;

public:
	GameLogic();
	~GameLogic();
	unsigned int waitToConnect();
	unsigned int gameLoop();
	void gameStart();
	void prePhyLogic();
	void addWalls();
	void addGround();
	void postPhyLogic();
	void deleteGameObj(GameObj*);
	void cleanDataStructures();

};
#endif