#include "GamePhysics.h"

std::vector<Collision*> GamePhysics::collisionList;

GamePhysics::GamePhysics()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	GamePhysics::collisionList = std::vector<Collision*>();
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

void GamePhysics::initWorld(std::vector<GameObj*> *gameObj)//, std::map< btCollisionObject*, GameObj*>* objcpair)
{
	dynamicsWorld->setGravity(btVector3(0,GRAVITY,0));
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		if ((*it)->getIsRobot() != 0)
		{
			((Robot *)(*it))->createVehicle(dynamicsWorld, 3, 1, 3);//, objcpair);

		}
		/*
		else
		{
			(*it)->createRigidBody(objcpair);
			dynamicsWorld->addRigidBody((*it)->getRigidBody());//, COL_OBJECT, objectCollisions);
		}*/
	}

	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		if ((*it)->getIsRobot() != 0)
		{
			//((Robot *)(*it))->createVehicle(dynamicsWorld, 3, 1, 3, objcpair);

		}
		
		else
		{
			(*it)->createRigidBody();// objcpair);
			//if ((*it)->getBlockType() == BATTLEFIELD || (*it)->getBlockType() == WALL)
			//{
			//	(*it)->getRigidBody()->setLinearFactor(btVector3(0, 0, 0));
			//	(*it)->getRigidBody()->setAngularFactor(btVector3(0, 0, 0));
			//}
		    dynamicsWorld->addRigidBody((*it)->getRigidBody());//, COL_OBJECT, objectCollisions);
		}
	}
	dynamicsWorld->setInternalTickCallback((btInternalTickCallback)collisionCallback, &dynamicsWorld, (void*)1);

}

void GamePhysics::stepSimulation(std::vector<GameObj*> *gameObj,  std::vector<Collision*> * collisionList)
{
	std::vector<GameObj*>::iterator it;
	for (it = gameObj->begin(); it != gameObj->end(); ++it)
	{
		if ((*it)->getCollisionType() == C_GROUND || (*it)->getCollisionType() == C_WALLS) continue;
		btTransform trans;
		if ((*it)->getIsRobot() != 0)
		{
			trans = ((Robot*)(*it))->getVehicle()->getChassisWorldTransform();
			//std::cout << "Y: " << trans.getOrigin().getY() << std::endl;
		}
		else
		{
			//std::cout << "stepSimu , not robot" << (*it)->getOid() << "is wheel " << (*it)->getIsWheel() << std::endl;
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
			// std::cout << "X: " << trans.getOrigin().getX() << "  Y: " << trans.getOrigin().getY() << "  Z:  " << trans.getOrigin().getZ() << "   SPEED:" << (*it)->getRigidBody()->getLinearVelocity() << std::endl;
		}
		(*it)->setX(trans.getOrigin().getX());
		(*it)->setY(trans.getOrigin().getY());
		if (trans.getOrigin().getY() < -1.5)
		{
			(*it)->setY(2);
			trans.getOrigin().setY(2);
		}
		(*it)->setZ(trans.getOrigin().getZ());
		//std::cout << "Y: " << trans.getOrigin().getY() << std::endl;//<< ", Y: " << trans.getOrigin().getY() << ", Z: " << trans.getOrigin().getZ() << std::endl;
	}
	dynamicsWorld->performDiscreteCollisionDetection();
	//collisionCallback(dynamicsWorld, collisionList);
}

void GamePhysics::createPhysicsProjectile(Projectile* projectile)//std::map< btCollisionObject*, GameObj*>* map, double initForce)
{

	projectile->createRigidBody();// map);
	projectile->getRigidBody()->setLinearFactor(btVector3(1, 0.1, 1));
	dynamicsWorld->addRigidBody(projectile->getRigidBody());

	btTransform rbTrans = projectile->getRigidBody()->getWorldTransform();
    //std::cout << "-----------------------------------------" << std::endl;
	//std::cout << "rigidbody x y z: " << rbTrans.getOrigin().getX() << " , " << rbTrans.getOrigin().getY() << "  , " << rbTrans.getOrigin().getZ() << std::endl;
	//std::cout << "rigidbody orientation x y z w:" << rbTrans.getRotation().getX() << " , " << rbTrans.getRotation().getY() << "  , " << rbTrans.getRotation().getZ() << " , " << rbTrans.getRotation().getW() << std::endl;


	btVector3 relativeForce = btVector3(0, 0, projectile->initForce);
	btMatrix3x3 boxRot = projectile->getRigidBody()->getWorldTransform().getBasis();
	btVector3 correctedForce = boxRot * relativeForce;
	projectile->getRigidBody()->applyCentralImpulse(correctedForce);
}

void GamePhysics::createPhysicsEvent(int eventType, GameObj* gameObj)
{
	//std::cout << "Event Type: " << eventType << std::endl;
	switch (eventType) {
	case MOVE_LEFT: {
		if (gameObj->getIsRobot()!= 0)
		{
			robotTurnLeft((Robot*)gameObj);
			//robotForward((Robot*)gameObj);
		}
		break;
	}
	case MOVE_RIGHT: {
		if (gameObj->getIsRobot()!= 0)
		{
			robotTurnRight((Robot*)gameObj);
			//robotForward((Robot*)gameObj);
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
	//case WEAPON1:{
	//	break;
	//}
	default:{
		printf("error in packet types\n");
		break;
	}
	}
}

void GamePhysics::robotTurnLeft(Robot* rb){
	btRaycastVehicle* v = rb->getVehicle();
	//std::cout << "trunLeft : " << v->getWheelInfo(2).m_steering << std::endl;
	//if (v->getWheelInfo(2).m_steering < MAX_TURN_SPEED)
	//	v->getWheelInfo(2).m_steering += TURN_SPEED;
	//if (v->getWheelInfo(3).m_steering < MAX_TURN_SPEED)
	//	v->getWheelInfo(3).m_steering += TURN_SPEED;
	if (v->getWheelInfo(2).m_steering < MAX_TURN_SPEED)
		v->getWheelInfo(2).m_steering += TURN_SPEED;
	if (v->getWheelInfo(3).m_steering < MAX_TURN_SPEED)
		v->getWheelInfo(3).m_steering += TURN_SPEED;

	if (v->getWheelInfo(0).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(0).m_steering -= TURN_SPEED;
	if (v->getWheelInfo(1).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(1).m_steering -= TURN_SPEED;




	
}
void GamePhysics::robotTurnRight(Robot* rb){

	btRaycastVehicle* v = rb->getVehicle();
	//std::cout << "trunRight : " << v->getWheelInfo(2).m_steering << std::endl;
	/*if (v->getWheelInfo(2).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(2).m_steering += -TURN_SPEED;
	if (v->getWheelInfo(3).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(3).m_steering += -TURN_SPEED;*/
	if (v->getWheelInfo(2).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(2).m_steering += -TURN_SPEED;
	if (v->getWheelInfo(3).m_steering > -MAX_TURN_SPEED)
		v->getWheelInfo(3).m_steering += -TURN_SPEED;

	if (v->getWheelInfo(0).m_steering < MAX_TURN_SPEED)
		v->getWheelInfo(0).m_steering += TURN_SPEED;
	if (v->getWheelInfo(1).m_steering < MAX_TURN_SPEED)
		v->getWheelInfo(1).m_steering += TURN_SPEED;

}
void GamePhysics::robotBackward(Robot* rb){

	btRaycastVehicle* v = rb->getVehicle();
	//std::cout << "backward speed: " << v->getCurrentSpeedKmHour() << std::endl;

	if (v->getCurrentSpeedKmHour() > MAX_SPEED*rb->getSpeedMultiplier())
	{
		//std::cout << "forward speed: " << v->getCurrentSpeedKmHour() << std::endl;
		//std::cout << "forward: " <<v->getWheelInfo(0).m_engineForce << std::endl;
		double scale = (v->getCurrentSpeedKmHour() / (MAX_SPEED*rb->getSpeedMultiplier())) - 1;
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 0);
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 1);
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 2);
	v->applyEngineForce(-CAP_BRAKE_SPEED*(scale), 3);
	}
	else
	{

		//std::cout << "backward speed: " << v->getCurrentSpeedKmHour() << std::endl;
		//std::cout << "forward: " << v->getWheelInfo(0).m_engineForce << std::endl;
		double scale = 1 - (v->getCurrentSpeedKmHour() / (MAX_SPEED*rb->getSpeedMultiplier()));
		//std::cout << v->getWheelInfo(0).m_engineForce << std::endl;
		v->applyEngineForce((v->getWheelInfo(0).m_engineForce + MOVE_SPEED)*(scale), 0);
		v->applyEngineForce((v->getWheelInfo(1).m_engineForce + MOVE_SPEED)*(scale), 1);
		v->applyEngineForce((v->getWheelInfo(2).m_engineForce + MOVE_SPEED)*(scale), 2);
		v->applyEngineForce((v->getWheelInfo(3).m_engineForce + MOVE_SPEED)*(scale), 3);
	}

	if (v->getWheelInfo(0).m_engineForce > MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(MAX_ENGINE_SPEED, 0);
	}
	if (v->getWheelInfo(1).m_engineForce > MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(MAX_ENGINE_SPEED, 1);
	}
	if (v->getWheelInfo(2).m_engineForce > MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(MAX_ENGINE_SPEED, 2);
	}
	if (v->getWheelInfo(3).m_engineForce > MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(MAX_ENGINE_SPEED, 3);
	}
}
void GamePhysics::robotForward(Robot* rb){

	//std::cout << "forward speed: " << rb->getVehicle()->getCurrentSpeedKmHour() << std::endl;

	btRaycastVehicle* v = rb->getVehicle(); 
	//std::cout << "forward speed: " << v->getCurrentSpeedKmHour() << std::endl;

	if (v->getCurrentSpeedKmHour() < -MAX_SPEED*rb->getSpeedMultiplier())
	{
		double scale = (v->getCurrentSpeedKmHour() / (-MAX_SPEED*rb->getSpeedMultiplier())) - 1;
		v->applyEngineForce((v->getWheelInfo(0).m_engineForce + CAP_BRAKE_SPEED)*(scale), 0);
		v->applyEngineForce((v->getWheelInfo(1).m_engineForce + CAP_BRAKE_SPEED)*(scale), 1);
		v->applyEngineForce((v->getWheelInfo(2).m_engineForce + CAP_BRAKE_SPEED)*(scale), 2);
		v->applyEngineForce((v->getWheelInfo(3).m_engineForce + CAP_BRAKE_SPEED)*(scale), 3);
	}
	else
	{
		//btVector3 vel = v->getRigidBody()->getLinearVelocity();
		//std::cout << "linear vector: " << vel.getX() << " , " << vel.getY() << " , " << vel.getZ() << std::endl;
		//double mag = sqrt(vel.getX()*vel.getX() + vel.getY()*vel.getY() + vel.getZ()*vel.getZ());
		//std::cout << "linear magnitude: " << mag << std::endl;
		double scale = 1 - (v->getCurrentSpeedKmHour() / (-MAX_SPEED*rb->getSpeedMultiplier()));
		v->applyEngineForce((v->getWheelInfo(0).m_engineForce - MOVE_SPEED)*(scale), 0);
		v->applyEngineForce((v->getWheelInfo(1).m_engineForce - MOVE_SPEED)*(scale), 1);
		v->applyEngineForce((v->getWheelInfo(2).m_engineForce - MOVE_SPEED)*(scale), 2);
		v->applyEngineForce((v->getWheelInfo(3).m_engineForce - MOVE_SPEED)*(scale), 3);
	}
	if (v->getWheelInfo(0).m_engineForce < -MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(-MAX_ENGINE_SPEED, 0);
	}
	if (v->getWheelInfo(1).m_engineForce < -MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(-MAX_ENGINE_SPEED, 1);
	}
	if (v->getWheelInfo(2).m_engineForce < -MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(-MAX_ENGINE_SPEED, 2);
	}
	if (v->getWheelInfo(3).m_engineForce < -MAX_ENGINE_SPEED)
	{
		v->applyEngineForce(-MAX_ENGINE_SPEED, 3);
	}
}





void GamePhysics::collisionCallback(btDynamicsWorld* world, btScalar timestep)// std::vector<Collision*> * collisionList)
{
	//std::cout << "dispatch" << std::endl;
	int numManifolds = world->getDispatcher()->getNumManifolds();
	//std::cout << numManifolds << std::endl;
	for (int i = 0; i<numManifolds; i++)
	{
		//std::cout << "static-static collision!" << std::endl;
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());
		//std::cout << "static-static collision! finial" << std::endl;

		//std::cout << obA->getCollisionShape() << std::endl;
		//std::cout << obB->getCollisionShape() << std::endl;
		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j<numContacts; j++)
		{
			//int countDis = 0;
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				Collision* col = new Collision(obA, obB, &pt);
				GamePhysics::collisionList.push_back(col);
				

				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
			//std::cout << countDis << std::endl;
			
		}

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