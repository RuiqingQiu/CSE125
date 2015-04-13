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
	dynamicsWorld->setGravity(btVector3(0, 0, 0));
	btCollisionShape* ground = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, ground, btVector3(0, 0, 0));
	groundRigidBodyCI.m_friction = 0.8f;
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);
	//dynamicsWorld->clearForces();
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

void GamePhysics::createPhysicsEvent(int eventType, btRigidBody* rb)
{

	switch (eventType) {
	case MOVE_LEFT: {

		btQuaternion* dQ = new btQuaternion(yAxis, TURN_SPEED*((0.5*M_PI)));
		btTransform T = rb->getWorldTransform();
		T.setRotation(*dQ * rb->getWorldTransform().getRotation());
		rb->setWorldTransform(T);
		break;
	}
	case MOVE_RIGHT: {
		btQuaternion* dQ = new btQuaternion(yAxis, -TURN_SPEED*((0.5*M_PI)));
		btTransform T = rb->getWorldTransform();
		T.setRotation(*dQ * rb->getWorldTransform().getRotation());
		rb->setWorldTransform(T);
		break;
	}
	case MOVE_BACKWARD: {
		btVector3 relativeForce = btVector3(0, 0, MOVE_SPEED);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralForce(correctedForce);
		break;
	}
	case MOVE_FORWARD: {
		btVector3 relativeForce = btVector3(0, 0, -MOVE_SPEED);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralForce(correctedForce);
		break;
	}
	case MOVE_UP: {
		btVector3 relativeForce = btVector3(0, MOVE_SPEED*2, 0);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralForce(correctedForce);
		break;
	}

	case MOVE_DOWN: {
		btVector3 relativeForce = btVector3(0, -MOVE_SPEED*2, 0);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralForce(correctedForce);
		break;
	}


	default:{
		printf("error in packet types\n");
		break;
	}
	}
}