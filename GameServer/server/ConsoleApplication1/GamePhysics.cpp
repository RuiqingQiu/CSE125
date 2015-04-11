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

void GamePhysics::initWorld(std::vector<GameObj*> *gameObj)
{
	dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
	btCollisionShape* ground = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, ground, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		(*it)->createRigidBody();
		dynamicsWorld->addRigidBody((*it)->getRigidBody());
	}
}

void GamePhysics::stepSimulation(std::vector<GameObj*> *gameObj)
{
	
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		btTransform trans;
		(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
		std::cout << "BOX WITH ID:  " << (*it)->getId() << ", X: " << trans.getOrigin().getX() << ", Y: " << trans.getOrigin().getY() << ", Z: " << trans.getOrigin().getZ() << std::endl;
		(*it)->setX(trans.getOrigin().getX());
		(*it)->setY(trans.getOrigin().getY());
		(*it)->setZ(trans.getOrigin().getZ());
		btVector3 vect = trans.getRotation().getAxis();
		(*it)->setRotX(vect.getX());
		(*it)->setRotY(vect.getY());
		(*it)->setRotZ(vect.getZ());
	}
}