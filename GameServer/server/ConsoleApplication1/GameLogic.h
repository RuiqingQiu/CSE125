
/* GameLogic.h */
#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "Robot.h"
#include "ObjectEvents.h"
#include "Network.h"
#include "GamePhysics.h"
#include "definition.h"
#include "TimeFrame.h"
#include "DamageSystem.h"
#include "GERobotDeath.h"
#include "GameState.h"
#include <math.h>
#include "GEHealthUpdate.h"
#include "GETime.h"
#include "Scoreboard.h"
#include "GECollisonHappen.h"
#include "GEScoreboardUpdate.h"
#include <math.h>

#define FIELD_WIDTH 50
#define FIELD_HEIGHT 50
#define INSTANT_KILL 1


class GameLogic {
private:
	Network* network;
	GamePhysics* gamePhysics;
	TimeFrame* countDown;
	TimeFrame*	physicsTimer;
	DamageSystem* damageSystem;
	Scoreboard* scoreboard;
	int counter;


	std::vector<GameObj*> gameObjs;
	//when you delete a obj, deleteConstraints(), ~() delete rigidBody, set to nullptr
	//
	//check gameObjs vector every X ticks, push !null objs into new_gmaeObjs list
	//gameObjs = new_gameObjs

	std::map<int, GameObj *> clientPair;
	//clear

	//std::map< btCollisionObject*, GameObj*> objCollisionPair;
	//clear

	//std::vector<Constraint*> constraints;
	std::vector<ObjectEvents *> objEventList;
    std::vector<GameEvents *> gameEventList;
	std::vector<ObjectEvents *> buildList;

	int lastTime;

public:
	GameLogic();
	~GameLogic();
	unsigned int waitToConnect();
	unsigned int gameLoop();
	int gameStart();
	void prePhyLogic();
	void addWalls();
	void addGround();
	void postPhyLogic();
	void deleteGameObj(GameObj*);
	void cleanDataStructures();
	int breakConstraints(GameObj*);
	void createDeathEvent(Robot*);
	void createHealthUpdateEvent(Robot*);
	void createScoreboardUpdateEvent();
	void createGEClientCollision( GameObj*, GameObj*);
	void postDamageLogic(GameObj*, int e, btManifoldPoint*);
	void postHealthLogic(Robot* arr[]);
	void postDeathLogic(Robot*);

	int buildMode();
	int startBuild();
	int endGame();



	btVector3* convertQuaternionToEuler(btQuaternion* q);
	btQuaternion* convertEulerToQuaternion(double, double, double);
	int clearGame();
};
#endif