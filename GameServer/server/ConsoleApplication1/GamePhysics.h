#pragma once
#include <btBulletDynamicsCommon.h>
#include "GameObj.h"
#include "Constraint.h"
#include <vector>
#include <map>
#include "definition.h"
#include <iostream>
#define MOVE_SPEED 1000
#define CAP_BRAKE_SPEED 1000
#define BRAKE_SPEED 100
#define TURN_SPEED 100
#define MAX_TURN_SPEED 100
#define MAX_SPEED 80



class GamePhysics
{
public:
	GamePhysics();
	~GamePhysics();

	btBroadphaseInterface* getBroadphase();
	btDefaultCollisionConfiguration* getCollisionConfiguration();
	btCollisionDispatcher* getDispatcher();
	btSequentialImpulseConstraintSolver* getSolver();
	btDiscreteDynamicsWorld* getDynamicsWorld();

	void initWorld(std::vector<GameObj*>*);
	void createPhysicsEvent(int, GameObj*);
	void stepSimulation(std::vector<GameObj*> *);


private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	const btVector3 yAxis = btVector3(0.0f,1.0f,0.0f);
};



