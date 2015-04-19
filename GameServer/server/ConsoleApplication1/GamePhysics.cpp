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
	dynamicsWorld->setGravity(btVector3(0,GRAVITY,0));
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		if ((*it)->getIsRobot() != 0)
		{
			((Robot *)(*it))->createVehicle(dynamicsWorld, 0, 5, 0, 0, 0, 0, 1, 50, 7, 1, 7);
		}
		else
		{
			(*it)->createRigidBody();
			dynamicsWorld->addRigidBody((*it)->getRigidBody());
		}
	}
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
		std::cout << "X: " << trans.getOrigin().getX() << ", Y: " << trans.getOrigin().getY() << ", Z: " << trans.getOrigin().getZ() << std::endl;
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



