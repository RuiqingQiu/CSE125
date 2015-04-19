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
	dynamicsWorld->setGravity(btVector3(0, -30,0));
	btCollisionShape* ground = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, ground, btVector3(0, 0, 0));
	groundRigidBodyCI.m_friction = 0.1f;
	groundRigidBodyCI.m_restitution = 0.0f;
	groundRigidBodyCI.m_angularDamping = 0.2f;
	groundRigidBodyCI.m_linearDamping = 0.2f;
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	/*btCollisionShape* ground7 = new btStaticPlaneShape(btVector3(0, -1, 0), 1);
	btDefaultMotionState* groundMotionState7 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 20, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI7(0, groundMotionState7, ground7, btVector3(0, 0, 0));
	groundRigidBodyCI7.m_friction = 0.1f;
	groundRigidBodyCI7.m_restitution = 0.0f;
	btRigidBody* groundRigidBody7 = new btRigidBody(groundRigidBodyCI7);
	dynamicsWorld->addRigidBody(groundRigidBody7);


	btCollisionShape* ground1 = new btStaticPlaneShape(btVector3(0, 0, 1), 1);
	btDefaultMotionState* groundMotionState1 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -20)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI1(0, groundMotionState1, ground1, btVector3(0, 0, 0));
	groundRigidBodyCI1.m_friction = 0.2f;
	groundRigidBodyCI1.m_restitution = 0.0f;
	btRigidBody* groundRigidBody1 = new btRigidBody(groundRigidBodyCI1);
	dynamicsWorld->addRigidBody(groundRigidBody1);

	btCollisionShape* ground2 = new btStaticPlaneShape(btVector3(0, 0, -1), 1);
	btDefaultMotionState* groundMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 20)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI2(0, groundMotionState2, ground2, btVector3(0, 0, 0));
	groundRigidBodyCI2.m_friction = 0.2f;
	groundRigidBodyCI2.m_restitution = 0.0f;
	btRigidBody* groundRigidBody2 = new btRigidBody(groundRigidBodyCI2);
	dynamicsWorld->addRigidBody(groundRigidBody2);

	btCollisionShape* ground3 = new btStaticPlaneShape(btVector3(1, 0, 0), 1);
	btDefaultMotionState* groundMotionState3 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-20, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI3(0, groundMotionState3, ground3, btVector3(0, 0, 0));
	groundRigidBodyCI3.m_friction = 0.2f;
	groundRigidBodyCI3.m_restitution = 0.0f;
	btRigidBody* groundRigidBody3 = new btRigidBody(groundRigidBodyCI3);
	dynamicsWorld->addRigidBody(groundRigidBody3);

	btCollisionShape* ground4 = new btStaticPlaneShape(btVector3(-1, 0, 0), 1);
	btDefaultMotionState* groundMotionState4 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(20, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI4(0, groundMotionState4, ground4, btVector3(0, 0, 0));
	groundRigidBodyCI4.m_friction = 0.2f;
	groundRigidBodyCI4.m_restitution = 0.0f;
	btRigidBody* groundRigidBody4 = new btRigidBody(groundRigidBodyCI4);
	dynamicsWorld->addRigidBody(groundRigidBody4);*/


	//dynamicsWorld->clearForces();
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		((Robot *)(*it))->createVehicle(dynamicsWorld, 0, 5, 0, 0, 0, 0, 1, 50, 7, 1, 7);
		//dynamicsWorld->addRigidBody((*it)->getRigidBody());
	}
}

void GamePhysics::stepSimulation(std::vector<GameObj*> *gameObj)
{
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{


		btTransform trans = ((Robot*)(*it))->getVehicle()->getChassisWorldTransform();
		//std::cout << "BOX WITH ID:  " << (*it)->getId() << ", X: " << trans.getOrigin().getX() << ", Y: " << trans.getOrigin().getY() << ", Z: " << trans.getOrigin().getZ() << std::endl;
		std::cout << "Speed: " << ((Robot*)*it)->getVehicle()->getCurrentSpeedKmHour() << std::endl;
		(*it)->setX(trans.getOrigin().getX());
		(*it)->setY(trans.getOrigin().getY());
		(*it)->setZ(trans.getOrigin().getZ());

		//btVector3 vect = trans.getRotation().getAxis();
		//(*it)->setRotX(vect.getX());
		//(*it)->setRotY(vect.getY());
		//(*it)->setRotZ(vect.getZ());
	}
}

void GamePhysics::createPhysicsEvent(int eventType, GameObj* rb)
{

	switch (eventType) {
	case MOVE_LEFT: {

		//btQuaternion* dQ = new btQuaternion(yAxis, TURN_SPEED*((0.5*M_PI)));
		//btTransform T = rb->getWorldTransform();
		//T.setRotation(*dQ * rb->getWorldTransform().getRotation());
		//rb->setWorldTransform(T);
		//btTransform transform;
		//rb->getMotionState()->getWorldTransform(transform);
		//rb->setAngularVelocity(btVector3(0, 1, 0));
		/*btVector3 torque = btVector3(0, 1, 0);
		torque = torque*TURN_SPEED;
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		rb->applyTorque(boxRot*torque);*/
		//rb->applyTorque(btVector3(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()).cross(btVector3(1, 1, 1)));
		
		

		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce + TURN_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce / MAX_TURN_SPEED)), 1);
		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce - TURN_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce / MAX_TURN_SPEED)), 2);
		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce / MAX_TURN_SPEED)), 0);
		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce / MAX_TURN_SPEED)), 3);
		//((Robot*)rb)->getVehicle()->setBrake(TURN_SPEED, 0);
		//((Robot*)rb)->getVehicle()->setBrake(TURN_SPEED, 2);
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
		//rb->setAngularVelocity(btVector3(0, -1, 0));
		/*btVector3 torque = btVector3(0, -1, 0);
		torque = torque*TURN_SPEED;
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		rb->applyTorque(boxRot*torque);
		std::cout << "move right" << std::endl;*/
		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce + TURN_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce / MAX_TURN_SPEED)), 0);
		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce - TURN_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce / MAX_TURN_SPEED)), 3);
		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce / MAX_TURN_SPEED)), 1);
		((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce)*(1 - (((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce / MAX_TURN_SPEED)), 2);
		
		//((Robot*)rb)->getVehicle()->setBrake(TURN_SPEED, 1);
		//((Robot*)rb)->getVehicle()->setBrake(TURN_SPEED, 3);
		break;
	}
	case MOVE_BACKWARD: {
		/*btVector3 relativeForce = btVector3(0, 0, MOVE_SPEED);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralImpulse(correctedForce);*/

		if (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() < -MAX_SPEED)
		{
			std::cout << "breaking backward " << std::endl;
			((Robot*)rb)->getVehicle()->applyEngineForce(CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour()/-MAX_SPEED)-1), 0);
			((Robot*)rb)->getVehicle()->applyEngineForce(CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour()/-MAX_SPEED)-1), 1);
			((Robot*)rb)->getVehicle()->applyEngineForce(CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / -MAX_SPEED) - 1), 2);
			((Robot*)rb)->getVehicle()->applyEngineForce(CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / -MAX_SPEED) - 1), 3);
		}
		/*else if (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() > 0)
		{

			((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce - MOVE_SPEED, 0);
			((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce - MOVE_SPEED, 1);
			((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce - MOVE_SPEED, 2);
			((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce - MOVE_SPEED, 3);
		}*/
		else
		{
			std::cout << "scaling: " << (1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / -MAX_SPEED)) << std::endl;
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce - MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / -MAX_SPEED)), 0);
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce - MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / -MAX_SPEED)), 1);
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce - MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / -MAX_SPEED)), 2);
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce - MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / -MAX_SPEED)), 3);

		}
		break;
	}
	case MOVE_FORWARD: {
		/*btVector3 relativeForce = btVector3(0, 0, -MOVE_SPEED);
		btMatrix3x3& boxRot = rb->getWorldTransform().getBasis();
		btVector3 correctedForce = boxRot * relativeForce;
		rb->applyCentralImpulse(correctedForce);*/

		if (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() > MAX_SPEED)
		{
			std::cout << "breaking forward" << std::endl;
			((Robot*)rb)->getVehicle()->applyEngineForce(-CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED) - 1), 0);
			((Robot*)rb)->getVehicle()->applyEngineForce(-CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED) - 1), 1);
			((Robot*)rb)->getVehicle()->applyEngineForce(-CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED) - 1), 2);
			((Robot*)rb)->getVehicle()->applyEngineForce(-CAP_BRAKE_SPEED*((((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED) - 1), 3);
		}
		//else if (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() < 0)
		//{

		//	((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce + MOVE_SPEED, 0);
		//	((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce + MOVE_SPEED, 1);
		//	((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce + MOVE_SPEED, 2);
		//	((Robot*)rb)->getVehicle()->applyEngineForce(((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce + MOVE_SPEED, 3);
		//}
		else
		{
			std::cout << "scaling: " << (1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED)) << std::endl;
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(0).m_engineForce + MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED)), 0);
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(1).m_engineForce + MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED)), 1);
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(2).m_engineForce + MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED)), 2);
			((Robot*)rb)->getVehicle()->applyEngineForce((((Robot*)rb)->getVehicle()->getWheelInfo(3).m_engineForce + MOVE_SPEED)*(1 - (((Robot*)rb)->getVehicle()->getCurrentSpeedKmHour() / MAX_SPEED)), 3);

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