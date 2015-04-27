
/* GameLogic.cpp */
#include "GameLogic.h"



GameLogic::GameLogic()
{
	network = new Network();
	gamePhysics = new GamePhysics();
	countDown = new TimeFrame();
	damageSystem = new DamageSystem(INSTANT_KILL);
	counter = 0;
}

GameLogic::~GameLogic()
{
	delete network;
	delete gamePhysics;
	delete countDown;
	delete damageSystem;

}

unsigned int GameLogic::waitToConnect()
{
	int cid; 
	cid = network->waitForConnections();
	if (cid == -1) return WAIT;
	GameObj* robot = new Robot(cid, "testname");
	robot->setZ((cid % 2) * 10);
	robot->setY(2);
	robot->setX(cid - 2<0 ? 0 : 10);
	robot->setqX(0);
	robot->setqY(-50);
	robot->setqZ(0);
	robot->setqW(1);
	robot->setMass(50);
	robot->setType(BOX);
	robot->setBlockType(BASICCUBE);
	this->gameObjs.push_back(robot);
	clientPair.insert(std::pair<int, GameObj*>(cid, robot));
   

	//robot = new Robot(cid+1, "testname1");
	//robot->setZ(-20);
	//robot->setY(2);
	//robot->setX(0);
	//robot->setqX(0);
	//robot->setqY(-50);
	//robot->setqZ(0);
	//robot->setqW(1);
	//robot->setMass(50);
	//robot->setType(BOX);
	//robot->setBlockType(BASICCUBE);
	//this->gameObjs.push_back(robot);
	//clientPair.insert(std::pair<int, GameObj*>(cid+1, robot));


	//GameObj* gameObj = new GOBox(0, 5, 0, 0, 0, 0, 1, 50, 7, 1, 7);
	//gameObj->setBlockType(WOODENCUBE);
	//gameObjs.push_back(gameObj);
	//gameObj = new GOBox(2, 5, -2, 0, 0, 0, 1, 50, 7, 1, 7);
	//gameObj->setBlockType(MALLET);
	//gameObjs.push_back(gameObj);
	//gameObj = new GOBox(-5, 5, 5, 0, 0, 0, 1, 50, 7, 1, 7);
	//gameObj->setBlockType(MACE);
	//gameObjs.push_back(gameObj);
	////asd++;
	

	//GameObj* gameObj1;

	//int k, l;
	//int p = 1;
	//for (k = -2; k <= 2; k++)
	//{
	//	for (l = -2; l <= 2; l++)
	//	{
	//		if (k == 2 || k == -2 || l == 2 || l == -2)
	//		{
	//			gameObj1 = new GOBox(k, 5, l, 0, 0, 0, 1, 75, 1, 1, 1);
	//			gameObj1->setBlockType(CUBE);
	//			this->gameObjs.push_back(gameObj1);
	//			clientPair.insert(std::pair<int, GameObj*>(cid + p, gameObj1));
	//			cout << "p:" << p << endl;
	//			p++;
	//		}
	//	}
	//}




	//GameObj* gameObj1 = new GOBox(10, 5, 0, 0, 0, 0, 1, 1, 1, 1, 1);
	//gameObj1->setBlockType(CUBE);
	//asd++;
	//this->gameObjs.push_back(gameObj1);
	//clientPair.insert(std::pair<int, GameObj*>(cid + 1, gameObj1));
	//int i, j;
	/*for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 20; j++)
		{
			GameObj* gameObj2 = new GOBox(i*1-10, j*1, -5, 0, 0, 0, 1, 1, 1, 1, 1);
			gameObj2->setBlockType(CUBE);
			this->gameObjs.push_back(gameObj2);
		}
	}*/



	//objEvent = new ObjectEvents(SHOOT);
	//objEventList.push_back(objEvent);
	//objEvent = new ObjectEvents(SHOOT);
	//objEventList.push_back(objEvent);
	//objEvent = new ObjectEvents(SHOOT);
	//objEventList.push_back(objEvent);
	//objEvent = new ObjectEvents(SHOOT);


	network->receiveFromClients(&objEventList);

	std::vector<ObjectEvents *>::iterator iter;

	for (iter = objEventList.begin(); iter != objEventList.end(); iter++)
	{
		unsigned int type = (*iter)->getEvent();
		switch (type) {

		case INIT_CONNECTION:
			string name = (*iter)->getName();
			(*iter)->setCid(cid);
			network->sendClientConfirmationPacket(name.c_str(), cid);
			objEventList.erase(iter);
			return ADDCLIENT;
		}
		objEventList.erase(iter);
	}
	return WAIT;

}


// will be called in build function when the build mode ends
void GameLogic::gameStart(){
	countDown->startCountdown(300);
	countDown->startClock();

	addGround();
	//addWalls();

	gamePhysics->initWorld(&gameObjs, &objCollisionPair);

	//int i,j,k;
	//int i;
	//for (i = 0; i < 17; i++)
	//{
	//	for (j = i + 1; j < 17; j++)
	//	{
	//		for (k = 0; k < 7; k++)
	//		{
		//clientPair.find(0)->second
		        
		//		gamePhysics->getDynamicsWorld()->addConstraint(b->joint6DOF, true);
		//	}
	//	}
	//}


	/*std::vector<GameObj*>::iterator it;
	for (it = gameObjs.begin(); it != gameObjs.end(); it++)
	{
		
		Constraint* b = new Constraint();
		if (it + 1 == gameObjs.end()){
			break;
		}
		b->addConstraint((*it++), (*it));
		gamePhysics->getDynamicsWorld()->addConstraint(b->joint6DOF);

	}*/
	//gamePhysics->getDynamicsWorld()->addConstraint(b->joint6DOF);

}


unsigned int GameLogic::gameLoop (){
	if (counter++ > 30)
	{
		ObjectEvents* objEvent = new ObjectEvents(SHOOT);


		objEvent->setCid(0);
		objEventList.push_back(objEvent);
		cout << "SHOOTING" << endl;
		counter = 0;
	}


	network->receiveFromClients(&objEventList);
	

	//if (countDown->checkCountdown()) return TIMEUP;
	

	//do gamelogic for all ObjectEvents
	prePhyLogic();
	
	//pass the time into physics
	
	unsigned int time = countDown->getElapsedTime();

	countDown->startClock();

	//do physics

	
	gamePhysics->getDynamicsWorld()->stepSimulation(btScalar(1/66.0),4);

	gamePhysics->stepSimulation(&gameObjs, &GamePhysics::collisionList);


	postPhyLogic();

	GamePhysics::collisionList.clear();
	//std::cout << "after clear check size " << GamePhysics::collisionList1.size() << std::endl;

	//after phy logic all ObjectEvents 
	
	network->sendActionPackets(&gameObjs);
	return COUNTDOWN;
	//send back 

	
	
}



void GameLogic::prePhyLogic(){
	std::vector<ObjectEvents *>::iterator iter;
	iter = objEventList.begin();
	while (iter != objEventList.end()) 
	{
		unsigned int type = (*iter)->getEvent();
		int cid = (*iter)->getCid();
		std::map<int, GameObj *>::iterator it;
		it = clientPair.find(cid);

		GameObj* gObj = it->second;

		switch(type) {
		case SHOOT:{
					   double initBulletSpd = 1;
					   double bulletMass = 10;
					   double bulletWidth = 0.3;
					   double bulletHeight = 0.3;
					   double bulletdepth = 0.5;
					   double rbWidth = ((Robot*)gObj)->getWidth();
					   btTransform rbTrans = gObj->getRigidBody()->getWorldTransform();
					   btVector3 relativeForce = btVector3(0, 0, rbWidth/2);
					   btVector3 boxRot = rbTrans.getBasis()[2];
					   boxRot.normalize();
					   btVector3 correctedForce = boxRot * rbWidth/2;
					   double x = rbTrans.getOrigin().getX() + correctedForce.getX();
					   double y = rbTrans.getOrigin().getY() + correctedForce.getY();
					   double z = rbTrans.getOrigin().getZ() + correctedForce.getZ();
					   /*btScalar qx;
					   double qy;
					   double qz;
					   rbTrans.getBasis().getEulerZYX(qz, qy, qx);
*/
					   GameObj* bullet = new GOBox(x, y, z, rbTrans.getRotation().getX(), rbTrans.getRotation().getY(), rbTrans.getRotation().getZ(), rbTrans.getRotation().getW(),
						 bulletMass  , bulletWidth, bulletHeight, bulletdepth);
					   bullet->setCollisionType(C_PROJECTILE);
					   bullet->setBelongTo(gObj);
					   bullet->setBlockType(NEEDLE);
					   gameObjs.push_back(bullet);
					   gamePhysics->createPhysicsProjectile(type, bullet, &objCollisionPair);
				break;
		}
		default:{
					gamePhysics->createPhysicsEvent(type, gObj);
					break;
		}

		}

		iter++;
	}
	if (objEventList.size() == 0)
	{
		std::vector<GameObj*>::iterator it;
		for (it = gameObjs.begin(); it != gameObjs.end(); ++it)
		{
			if ((*it)->getIsRobot() != 0)
			{
				((Robot*)*it)->getVehicle()->applyEngineForce(-(((Robot*)*it)->getVehicle()->getCurrentSpeedKmHour()*BRAKE_SPEED), 0);
				((Robot*)*it)->getVehicle()->applyEngineForce(-(((Robot*)*it)->getVehicle()->getCurrentSpeedKmHour()*BRAKE_SPEED), 1);
				((Robot*)*it)->getVehicle()->applyEngineForce(-(((Robot*)*it)->getVehicle()->getCurrentSpeedKmHour()*BRAKE_SPEED), 2);
				((Robot*)*it)->getVehicle()->applyEngineForce(-(((Robot*)*it)->getVehicle()->getCurrentSpeedKmHour()*BRAKE_SPEED), 3);

			}
		}
	}

	std::vector<GameObj*>::iterator it;
	for (it = gameObjs.begin(); it != gameObjs.end(); ++it)
	{
		if ((*it)->getIsRobot() != 0)
		{
			//std::cout << "forward speed: " << ((Robot*)*it)->getVehicle()->getCurrentSpeedKmHour() << std::endl;
			if (((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering > 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering += -TURN_SPEED / 2;
			if (((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering > 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering += -TURN_SPEED / 2;
			if (((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering < 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering += TURN_SPEED / 2;
			if (((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering < 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering += TURN_SPEED / 2;
		}
	}

	objEventList.clear();
	//cout << "objEventList size == " << objEventList.size() << endl;
}


void GameLogic::postPhyLogic(){
	std::vector<Collision *>::iterator it;
	for (it = GamePhysics::collisionList.begin(); it != GamePhysics::collisionList.end(); it++)
	{
		btCollisionObject* obj1 = static_cast<btCollisionObject*>((*it)->getObj1());
		btCollisionObject* obj2 = static_cast<btCollisionObject*>((*it)->getObj2());
		GameObj* GO1 = objCollisionPair.find(obj1)->second;
		GameObj* GO2 = objCollisionPair.find(obj2)->second;
		std::cout << "Collision: GO1 Objid = " << GO1->getId() << ", type = " << GO1->getType() << ", GO2 Objid = " << GO2->getId() << ", type = " << GO2->getType() << std::endl;

		DamageEvent* e = nullptr;
		damageSystem->performDamage(GO1, GO2, e);
		if (e->getResult1() == BREAK_CONSTRAINT)
		{
			//gamePhysics break constraint
			std::vector<Constraint*>::iterator iter;
			for (iter = GO1->getConstraints().begin(); iter != GO1->getConstraints().end(); iter++)
			{
				gamePhysics->getDynamicsWorld()->removeConstraint((*iter)->_joint6DOF);
			}
			GO1->deleteConstraints(&objCollisionPair);
		}
		else if (e->getResult1() == DELETED)
		{
			//gamePhysics remove rigidBody
			gamePhysics->getDynamicsWorld()->removeRigidBody(GO1->getRigidBody());
			deleteGameObj(GO1);
			//set gameevent
		}
		if (e->getResult2() == BREAK_CONSTRAINT)
		{
			//gamePhysics break constraint
			std::vector<Constraint*>::iterator iter;
			for (iter = GO2->getConstraints().begin(); iter != GO2->getConstraints().end(); iter++)
			{
				gamePhysics->getDynamicsWorld()->removeConstraint((*iter)->_joint6DOF);
			}
			GO2->deleteConstraints(&objCollisionPair);
		}
		else if (e->getResult2() == DELETED)
		{
			//gamePhysics remove rigidBody

			gamePhysics->getDynamicsWorld()->removeRigidBody(GO2->getRigidBody());
			deleteGameObj(GO2);
			//set gameevent
		}
		
	}
	if (!GamePhysics::collisionList.empty())
	{
		cleanDataStructures();
		GamePhysics::collisionList.clear();
	}
}


void GameLogic::addWalls()
{
	GameObj* ceiling = new GOPlane(0, FIELD_HEIGHT, 0, 0, 0, 0, 1, 0, 0, -1, 0, 1);
	GameObj* leftWall = new GOPlane(-FIELD_WIDTH / 2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1);
	GameObj* rightWall = new GOPlane(FIELD_WIDTH / 2, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 1);
	GameObj* frontWall = new GOPlane(0, 0, FIELD_WIDTH / 2, 0, 0, 0, 1, 0, 0, 0, -1, 1);
	GameObj* backWall = new GOPlane(0, 0, -FIELD_WIDTH / 2, 0, 0, 0, 1, 0, 0, 0, 1, 1);

	ceiling->setBlockType(WALL);
	leftWall->setBlockType(WALL);
	rightWall->setBlockType(WALL);
	frontWall->setBlockType(WALL);
	backWall->setBlockType(WALL);	

	ceiling->setCollisionType(C_WALLS);
	leftWall->setCollisionType(C_WALLS);
	rightWall->setCollisionType(C_WALLS);
	frontWall->setCollisionType(C_WALLS);
	backWall->setCollisionType(C_WALLS);

	gameObjs.push_back(ceiling);
	gameObjs.push_back(leftWall);
	gameObjs.push_back(rightWall);
	gameObjs.push_back(frontWall);
	gameObjs.push_back(backWall);
}
void GameLogic::addGround()
{
	GameObj* ground = new GOPlane(0, -1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1);
	ground->setBlockType(BATTLEFIELD);
	ground->setCollisionType(C_GROUND);
	gameObjs.push_back(ground);
}

//TODO: print gameObjs after calling to double-check the vector is not garbage
void GameLogic::cleanDataStructures()
{
	std::vector<GameObj*> new_gameObj;
	std::vector<GameObj*>::iterator it;
	for (it = gameObjs.begin(); it != gameObjs.end(); it++)
	{
		if ((*it) != nullptr)
		{
			new_gameObj.push_back((*it));
		}
	}
	gameObjs = new_gameObj;

	std::map<int, GameObj *> new_clientPair;
	std::map<int, GameObj *>::iterator it1;
	for (it1 = clientPair.begin(); it1 != clientPair.end(); it1++)
	{
		if ((*it1).second != nullptr)
		{
			new_clientPair.insert((*it1));
		}
	}
	clientPair = new_clientPair;

	std::map< btCollisionObject*, GameObj*> new_objCollisionPair;
	std::map< btCollisionObject*, GameObj*>::iterator it2;
	for (it2 = objCollisionPair.begin(); it2 != objCollisionPair.end(); it2++)
	{
		if ((*it2).second != nullptr)
		{
			new_objCollisionPair.insert((*it2));
		}
	}
	objCollisionPair = new_objCollisionPair;
}


void GameLogic::deleteGameObj(GameObj* g)
{
	g->deleteConstraints(&objCollisionPair);
	delete(g);
	g = nullptr;
}