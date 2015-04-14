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
	groundRigidBodyCI.m_friction = 0.8f;
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);


	btCollisionShape* ground1 = new btStaticPlaneShape(btVector3(0, 0, 1), 1);
	btDefaultMotionState* groundMotionState1 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -15)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI1(0, groundMotionState1, ground1, btVector3(0, 0, 0));
	groundRigidBodyCI1.m_friction = 0.2f;
	btRigidBody* groundRigidBody1 = new btRigidBody(groundRigidBodyCI1);
	dynamicsWorld->addRigidBody(groundRigidBody1);

	btCollisionShape* ground2 = new btStaticPlaneShape(btVector3(0, 0, -1), 1);
	btDefaultMotionState* groundMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 15)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI2(0, groundMotionState2, ground2, btVector3(0, 0, 0));
	groundRigidBodyCI2.m_friction = 0.2f;
	btRigidBody* groundRigidBody2 = new btRigidBody(groundRigidBodyCI2);
	dynamicsWorld->addRigidBody(groundRigidBody2);

	btCollisionShape* ground3 = new btStaticPlaneShape(btVector3(1, 0, 0), 1);
	btDefaultMotionState* groundMotionState3 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-20, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI3(0, groundMotionState3, ground3, btVector3(0, 0, 0));
	groundRigidBodyCI3.m_friction = 0.2f;
	btRigidBody* groundRigidBody3 = new btRigidBody(groundRigidBodyCI3);
	dynamicsWorld->addRigidBody(groundRigidBody3);

	btCollisionShape* ground4 = new btStaticPlaneShape(btVector3(-1, 0, 0), 1);
	btDefaultMotionState* groundMotionState4 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(300, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI4(0, groundMotionState4, ground4, btVector3(0, 0, 0));
	groundRigidBodyCI4.m_friction = 0.2f;
	btRigidBody* groundRigidBody4 = new btRigidBody(groundRigidBodyCI4);
	dynamicsWorld->addRigidBody(groundRigidBody4);


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
		//btVector3 vect = trans.getRotation().getAxis();
		//(*it)->setRotX(vect.getX());
		//(*it)->setRotY(vect.getY());
		//(*it)->setRotZ(vect.getZ());
	}
}

void GamePhysics::createPhysicsEvent(int eventType, btRigidBody* rb)
{

	switch (eventType) {
	case MOVE_LEFT: {

		//btQuaternion* dQ = new btQuaternion(yAxis, TURN_SPEED*((0.5*M_PI)));
		//btTransform T = rb->getWorldTransform();
		//T.setRotation(*dQ * rb->getWorldTransform().getRotation());
		//rb->setWorldTransform(T);
		//btTransform transform;
		//rb->getMotionState()->getWorldTransform(transform);
		rb->setAngularVelocity(btVector3(0, 1, 0));
		//rb->applyTorque(btVector3(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()).cross(btVector3(1, 1, 1)));
		std::cout << "move left" << std::endl;
		break;
	}
	case MOVE_RIGHT: {
		//btQuaternion* dQ = new btQuaternion(yAxis, -TURN_SPEED*((0.5*M_PI)));
		//btTransform T = rb->getWorldTransform();
		//T.setRotation(*dQ * rb->getWorldTransform().getRotation());
		//rb->setWorldTransform(T);
		//btTransform transform;
		//rb->getMotionState()->getWorldTransform(transform);
		//rb->applyTorque(btVector3(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()).cross(btVector3(-1, 1, 1)));
		//rb->applyTorque(btVector3(TURN_SPEED*10, 1, 1));
		rb->setAngularVelocity(btVector3(0, -1, 0));
		std::cout << "move right" << std::endl;
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