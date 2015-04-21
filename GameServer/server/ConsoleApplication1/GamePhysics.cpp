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

void GamePhysics::initWorld(std::vector<GameObj*> *gameObj, std::vector<Collision*>* collisionList, std::map< btCollisionObject*, GameObj*>* objcpair)
{
	dynamicsWorld->setGravity(btVector3(0,GRAVITY,0));
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		if ((*it)->getIsRobot() != 0)
		{
			((Robot *)(*it))->createVehicle(dynamicsWorld, 3, 1, 3, objcpair);
		}
		else
		{
			(*it)->createRigidBody(objcpair);
			dynamicsWorld->addRigidBody((*it)->getRigidBody(), COL_OBJECT, objectCollisions);
		}
	}
	collisionCallback(dynamicsWorld, collisionList);
}

void GamePhysics::stepSimulation(std::vector<GameObj*> *gameObj)
{
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		btTransform trans;
		if ((*it)->getIsRobot() != 0)
		{
			trans = ((Robot*)(*it))->getVehicle()->getChassisWorldTransform();
		}
		else
		{
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
		}
		(*it)->setX(trans.getOrigin().getX());
		(*it)->setY(trans.getOrigin().getY());
		(*it)->setZ(trans.getOrigin().getZ());
		//std::cout << "X: " << trans.getOrigin().getX() << ", Y: " << trans.getOrigin().getY() << ", Z: " << trans.getOrigin().getZ() << std::endl;
	}
}

void GamePhysics::createPhysicsEvent(int eventType, GameObj* gameObj)
{
	std::cout << "Event Type: " << eventType << std::endl;
	switch (eventType) {
	case MOVE_LEFT: {
		if (gameObj->getIsRobot()!= 0)
		{
			robotTurnLeft((Robot*)gameObj);
		}
		break;
	}
	case MOVE_RIGHT: {
		if (gameObj->getIsRobot()!= 0)
		{
			robotTurnRight((Robot*)gameObj);
		}
		break;
	}
	case MOVE_BACKWARD: {
		if (gameObj->getIsRobot()!= 0)
		{
			robotBackward((Robot*)gameObj);
		}
		break;
	}
	case MOVE_FORWARD: {
		if (gameObj->getIsRobot()!= 0)
		{
			robotForward((Robot*)gameObj);
		}
		break;
	}
	case MOVE_UP: {
		/*btVector3 relativeForce = btVector3(0, MOVE_SPEED*2, 0);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralImpulse(correctedForce);*/
		break;
	}

	case MOVE_DOWN: {
		/*btVector3 relativeForce = btVector3(0, -MOVE_SPEED*2, 0);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralImpulse(correctedForce);*/
		break;
	}
	case WEAPON1:{
		break;
	}
	default:{
		printf("error in packet types\n");
		break;
	}
	}
}

void GamePhysics::robotTurnLeft(Robot* rb){
	btRaycastVehicle* v = rb->getVehicle();
	if (v->getWheelInfo(0).m_steering < MAX_TURN_SPEED)
		v->getWheelInfo(0).m_steering += TURN_SPEED;
	if (v->getWheelInfo(1).m_steering < MAX_TURN_SPEED)
		v->getWheelInfo(1).m_steering += TURN_SPEED;
}
void GamePhysics::robotTurnRight(Robot* rb){
	btRaycastVehicle* v = rb->getVehicle();
	if (v->getWheelInfo(0).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(0).m_steering += -TURN_SPEED;
	if (v->getWheelInfo(1).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(1).m_steering += -TURN_SPEED;
}
void GamePhysics::robotForward(Robot* rb){
	btRaycastVehicle* v = rb->getVehicle();
	if (v->getCurrentSpeedKmHour() > MAX_SPEED)
	{
		double scale = (v->getCurrentSpeedKmHour() / MAX_SPEED) - 1;
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 0);
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 1);
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 2);
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 3);
	}
	else
	{
		double scale = 1 - (v->getCurrentSpeedKmHour() / MAX_SPEED);
		v->applyEngineForce((v->getWheelInfo(0).m_engineForce + MOVE_SPEED)*(scale), 0);
		v->applyEngineForce((v->getWheelInfo(1).m_engineForce + MOVE_SPEED)*(scale), 1);
		v->applyEngineForce((v->getWheelInfo(2).m_engineForce + MOVE_SPEED)*(scale), 2);
		v->applyEngineForce((v->getWheelInfo(3).m_engineForce + MOVE_SPEED)*(scale), 3);
	}
}
void GamePhysics::robotBackward(Robot* rb){

	btRaycastVehicle* v = rb->getVehicle();
	if (v->getCurrentSpeedKmHour() < -MAX_SPEED)
	{
		double scale = (v->getCurrentSpeedKmHour() / -MAX_SPEED) - 1;
		v->applyEngineForce((v->getWheelInfo(0).m_engineForce + CAP_BRAKE_SPEED)*(scale), 0);
		v->applyEngineForce((v->getWheelInfo(1).m_engineForce + CAP_BRAKE_SPEED)*(scale), 1);
		v->applyEngineForce((v->getWheelInfo(2).m_engineForce + CAP_BRAKE_SPEED)*(scale), 2);
		v->applyEngineForce((v->getWheelInfo(3).m_engineForce + CAP_BRAKE_SPEED)*(scale), 3);
	}
	else
	{
		double scale = 1 - (v->getCurrentSpeedKmHour() / -MAX_SPEED);
		v->applyEngineForce((v->getWheelInfo(0).m_engineForce - MOVE_SPEED)*(scale), 0);
		v->applyEngineForce((v->getWheelInfo(1).m_engineForce - MOVE_SPEED)*(scale), 1);
		v->applyEngineForce((v->getWheelInfo(2).m_engineForce - MOVE_SPEED)*(scale), 2);
		v->applyEngineForce((v->getWheelInfo(3).m_engineForce - MOVE_SPEED)*(scale), 3);
	}
	}





void GamePhysics::collisionCallback(btDynamicsWorld* world, std::vector<Collision*> * collisionList)
{
	//std::cout << "dispatch" << std::endl;
	int numManifolds = world->getDispatcher()->getNumManifolds();
	//std::cout << "dispatch end" << std::endl;
	for (int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		Collision* col = new Collision(obA, obB);
		//collisionList->push_back(col);
		//int numContacts = contactManifold->getNumContacts();
		//for (int j = 0; j<numContacts; j++)
		//{
		//	btManifoldPoint& pt = contactManifold->getContactPoint(j);
		//	if (pt.getDistance()<0.f)
		//	{
		//		const btVector3& ptA = pt.getPositionWorldOnA();
		//		const btVector3& ptB = pt.getPositionWorldOnB();
		//		const btVector3& normalOnB = pt.m_normalWorldOnB;
		//	}
		//}
	}
}