#pragma once
#include <btBulletDynamicsCommon.h>
#include "GameObj.h"
#include <vector>
#include <map>
#include "definition.h"
#include <iostream>

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
	void createPhysicsEvent(int, btRigidBody*);
	void stepSimulation(std::vector<GameObj*> *);


private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
};



