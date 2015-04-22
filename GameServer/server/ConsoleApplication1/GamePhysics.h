#pragma once
#include <btBulletDynamicsCommon.h>
#include "GameObj.h"
#include "Robot.h"
#include "GOPlane.h"
#include "Constraint.h"
#include "CollisionDetector.h"
#include <vector>
#include <map>
#include "definition.h"
#include <iostream>
#define MOVE_SPEED 1000
#define CAP_BRAKE_SPEED 1000
#define BRAKE_SPEED 5
#define TURN_SPEED 0.02
#define MAX_TURN_SPEED M_PI/10
#define MAX_SPEED 80
#define GRAVITY -10


class GamePhysics
{
public:
	GamePhysics();
	~GamePhysics();

	static void collisionCallback(btDynamicsWorld* world, btScalar);

	btBroadphaseInterface* getBroadphase();
	btDefaultCollisionConfiguration* getCollisionConfiguration();
	btCollisionDispatcher* getDispatcher();
	btSequentialImpulseConstraintSolver* getSolver();
	btDiscreteDynamicsWorld* getDynamicsWorld();

	void initWorld(std::vector<GameObj*>*,  std::map< btCollisionObject*, GameObj*>*);
	void createPhysicsEvent(int, GameObj*);
	void stepSimulation(std::vector<GameObj*>*, std::vector<Collision*> *);
	static std::vector<Collision*> collisionList1;

private:



	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	void robotTurnLeft(Robot*);
	void robotTurnRight(Robot*);
	void robotForward(Robot*);
	void robotBackward(Robot*);


};



