#pragma once
#include <btBulletDynamicsCommon.h>
#include "GameObj.h"
#include "Projectile.h"
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
#define BRAKE_SPEED 40
#define TURN_SPEED 0.04
#define MAX_TURN_SPEED M_PI/6
#define MAX_SPEED 40
#define GRAVITY -30
#define MAX_ENGINE_SPEED 1500


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

	void initWorld(std::vector<GameObj*>*);// , std::map< btCollisionObject*, GameObj*>*);
	void createPhysicsEvent(int, GameObj*);
	void createPhysicsProjectile(Projectile*);//GameObj*, std::map< btCollisionObject*, GameObj*>*, double initForce);
	void stepSimulation(std::vector<GameObj*>*, std::vector<Collision*> *);
	static std::vector<Collision*> collisionList;

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



