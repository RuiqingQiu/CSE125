#include "GamePhysics.h"


GamePhysics::GamePhysics()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
}


GamePhysics::~GamePhysics()
{
	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete dynamicsWorld;
}

btBroadphaseInterface* GamePhysics::getBroadphase()
{
	return broadphase;
}

btDefaultCollisionConfiguration* GamePhysics::getCollisionConfiguration()
{
	return collisionConfiguration;
}
btCollisionDispatcher* GamePhysics::getDispatcher()
{
	return dispatcher;
}

btSequentialImpulseConstraintSolver* GamePhysics::getSolver()
{
	return solver;
}

btDiscreteDynamicsWorld* GamePhysics::getDynamicsWorld()
{
	return dynamicsWorld;
}

//void GamePhysics::initWorld(std::vector<GameObj*> *gameObj)
//{
//	dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
//	std::vector<GameObj*>::iterator it;
//	for (it = gameObj->begin(); it != gameObj->end(); ++it)
//	{
//		
//	}
//}

//btCollisionShape* GamePhysics::convertObj(GameObj* gameObj)
//{
	//switch (gameObj->getType())
	//{
	//	case PLANE:
	//	{

	//	}
	//		TRIANGLE
	//		CAPSULE
	//		CONE
	//		CYLINDER
	//		BOX
	//		CLOUD
	//}
//	return nullptr;
//}