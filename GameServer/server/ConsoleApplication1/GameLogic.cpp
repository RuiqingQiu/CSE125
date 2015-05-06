
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
	robot->setX((cid % 2)* 30);
	robot->setY(4);
	robot->setZ(cid - 2<0 ? 0 : 30);
	robot->setqX(0);
	robot->setqY(0);
	robot->setqZ(0);
	robot->setqW(1);
	robot->setMass(100);//50);
	robot->setType(BOX);
	((Robot*)robot)->setCID(cid);
	((Robot*)robot)->setMaxHealth(100);
	robot->setBlockType(THREEBYTHREE_BASIC);
	this->gameObjs.push_back(robot);

	clientPair.insert(std::pair<int, GameObj*>(cid, robot));
	//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE//REMOVE next state
	robot = new Robot(cid+1, "testname");
	robot->setX(((cid +1)% 2) * 30);
	robot->setY(4);
	robot->setZ((cid+1) - 2<0 ? 0 : 30);
	robot->setqX(0);
	robot->setqY(0);
	robot->setqZ(0);
	robot->setqW(1);
	robot->setMass(100);//50);
	robot->setType(BOX);
	((Robot*)robot)->setCID(cid+1);
	((Robot*)robot)->setMaxHealth(100);
	robot->setBlockType(THREEBYTHREE_BASIC);

	this->gameObjs.push_back(robot);
	clientPair.insert(std::pair<int, GameObj*>(cid+1, robot));
	
	

	/*
		this->gameObjs.push_back(robot);
		robot = new Robot(101, "testname");
		robot->setX(-5);
		robot->setY(2);
		robot->setZ(0);
		robot->setqX(0);
		robot->setqY(0);
		robot->setqZ(0);
		robot->setqW(1);
		robot->setMass(100);//50);
		robot->setType(BOX);
		((Robot*)robot)->setCID(101);
		((Robot*)robot)->setMaxHealth(100);
		robot->setBlockType(THREEBYTHREE_BASIC);
		this->gameObjs.push_back(robot);
		tmp = false;
	}
	*/
   

	



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

	//cout << "started" << endl;
	//int i,j,k;
	int i;
	for (i = 0; i < clientPair.size(); i++)
	{
		int j, k;
		Robot* robot= (Robot*)clientPair.find(i)->second;
		robot->nextState();
		int left = -((int)(robot->getWidth() / 2)) - 1;
		int right = ((int)(robot->getWidth() / 2)) + 1;
		int front = -((int)(robot->getDepth() / 2)) - 1;
		int back = ((int)(robot->getDepth() / 2)) + 1;
		for (j = left; j <= right; j++)
		{
			for (k = front; k <= back; k++)
			{
				GameObj* gameObj;
				//if (k==front)
				if(j == left || j == right || k == front || k == back)
				{
					btTransform trans;
					robot->getRigidBody()->getMotionState()->getWorldTransform(trans);
					
					gameObj = new GOBox(j + robot->getX(), robot->getY(), k + robot->getZ(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ(), trans.getRotation().getW(), 1, 1, 1, 1);
					if (k == front)
					{
						//Weapon* w = new RangedWeapon(GUN, gameObj);
						gameObj->setBlockType(BASICCUBE);
						//cout << "weapon id: " << gameObj->getId() << endl;
						//robot->addWeapon(w);
					}
					else{
						gameObj->setBlockType(BASICCUBE);
					}

				
				}
				else
				{
					cout << "height" << robot->getHeight() << endl;
					int yOffset = ((int)robot->getHeight() / 2) + 1;
					gameObj = new GOBox(j + robot->getX(), robot->getY() + yOffset, k + robot->getZ(), 0, 0, 0, 1, 1, 1, 1, 1);
					gameObj->setBlockType(BASICCUBE);
					
					
					GameObj* gameObj2 = new GOBox(j + robot->getX(), robot->getY() + 1 + yOffset, k + robot->getZ(), 0, 0, 0, 1, 1, 1, 1, 1);
					gameObj2->setBlockType(BASICCUBE);
					gameObj2->setCollisionType(C_ROBOT_PARTS);
					gameObj2->setBelongTo(robot);
					gameObj2->createRigidBody(&objCollisionPair);
					gamePhysics->getDynamicsWorld()->addRigidBody(gameObj2->getRigidBody());
					robot->addConstraint(gameObj2);	gameObjs.push_back(gameObj2);
					Weapon* w = new RangedWeapon(GUN, gameObj2);
					cout << "weapon id: " << gameObj->getId() << endl;
					robot->addWeapon(w);
				}


				gameObj->setCollisionType(C_ROBOT_PARTS);
				gameObj->setBelongTo(robot);
				gameObj->createRigidBody(&objCollisionPair);
				gamePhysics->getDynamicsWorld()->addRigidBody(gameObj->getRigidBody());
				int z;
				for (z = 0; z < 1; z++)
				{
					robot->addConstraint(gameObj);
				}

				gameObjs.push_back(gameObj);
				/*gameObj->setCollisionType(C_ROBOT_PARTS);
				gameObj->setBelongTo(robot);
				gameObj->createRigidBody(&objCollisionPair);
				gamePhysics->getDynamicsWorld()->addRigidBody(gameObj->getRigidBody());
				int z;
				for (z = 0; z <1 ; z++)
				{
					robot->addConstraint(gameObj);
				}
				std::vector<Constraint *>::iterator iter;
				for (iter = robot->getConstraints()->begin(); iter != robot->getConstraints()->end(); iter++)
				{
					gamePhysics->getDynamicsWorld()->addConstraint((*iter)->_joint6DOF);
				}

				gameObjs.push_back(gameObj); */
				
			}

			
		}

		std::vector<Constraint *>::iterator iter;
		for (iter = robot->getConstraints()->begin(); iter != robot->getConstraints()->end(); iter++)
		{
			gamePhysics->getDynamicsWorld()->addConstraint((*iter)->_joint6DOF);
		}
	}


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

		//ObjectEvents* objEvent = new ObjectEvents(SHOOT);
  //   	objEvent->setCid(0);
		//objEventList.push_back(objEvent);
	//gameEventList.push_back(new GERobotDeath(0));

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

	//std::cout << "after clear check size " << GamePhysics::collisionList1.size() << std::endl;

	//after phy logic all ObjectEvents 
	
	network->sendActionPackets(&gameObjs, &gameEventList);
	gameEventList.clear();
	//network->sendEventPackets(&gameEventList);
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
		Robot *r = (Robot*)gObj;
		if (r->getState() == PS_ALIVE){

			switch (type) {
			case SHOOT:{
					   std::vector<std::pair<GameObj*, double>> projectiles;
					   r->shoot(&projectiles);
					   std::vector<std::pair<GameObj*, double>>::iterator it;
					   for (it = projectiles.begin(); it != projectiles.end(); it++)
					   {
						   gameObjs.push_back((*it).first);
						   gamePhysics->createPhysicsProjectile((*it).first, &objCollisionPair, (*it).second);
						}
						break;
			}
			default:{
					gamePhysics->createPhysicsEvent(type, gObj);
					break;
			}
			}
		}
		else if(r->getState() == PS_BUILD)
		{
			switch (type) {
			case BUILD_ROBOT:{

						   
						  /* std::vector<GameObj*>::iterator it;
						   for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
						   {
							   gameObjs.push_back((*it));
							   if ((*it)->getBuildID() == 0)
							   {
								   clientPair.find((*iter)->getCid())->second = (*it);
							   }
						   }
						   Robot* robot = (Robot*)clientPair.find((*iter)->getCid())->second;
						   for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
						   {
							   (*it)->setBelongTo(robot);
							   if ((*it)->getLeftID() != -1)
							   {
								   (*it)->addConstraint(findObjbyBuildID());
							   }
						   }*/
			}
			default:{
						gamePhysics->createPhysicsEvent(type, gObj);
						break;
			}
			}

		}
		else if (r->getState() == PS_DEAD){

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
		if ((*it)->getId() == 0)
		{
			btTransform trans;
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
			//std::cout << "id OF VEHICLE: " << (*it)->getId() << "X: " << trans.getOrigin().getX() << "  Y: " << trans.getOrigin().getY() << "  Z:  " << trans.getOrigin().getZ() << std::endl;
		}
		if ((*it)->getIsWeapon())
		{
			btTransform trans;
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
			//std::cout << "id: " << (*it)->getId() << "X: " << trans.getOrigin().getX() << "  Y: " << trans.getOrigin().getY() << "  Z:  " << trans.getOrigin().getZ() << std::endl;
		}
		/*if (gameObjs.size() == 4)
		{
			btTransform trans;
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
			std::cout << "id: " << (*it)->getId() << "X: " << trans.getOrigin().getX() << "  Y: " << trans.getOrigin().getY() << "  Z:  " << trans.getOrigin().getZ() << "   SPEED:" << (*it)->getRigidBody()->getLinearVelocity() << std::endl;
		}*/
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
	int hasDeleted = 0;

	//cout << "SIZE OF COLLISION LIST " << GamePhysics::collisionList.size() << endl;
	for (it = GamePhysics::collisionList.begin(); it != GamePhysics::collisionList.end(); it++)
	{
		btCollisionObject* obj1 = static_cast<btCollisionObject*>((*it)->getObj1());
		btCollisionObject* obj2 = static_cast<btCollisionObject*>((*it)->getObj2());
		GameObj* GO1 = objCollisionPair.find(obj1)->second;
		GameObj* GO2 = objCollisionPair.find(obj2)->second;

		//if ((GO1->getBelongTo() != nullptr && GO1->getBelongTo() == GO2) || (GO2->getBelongTo() != nullptr && GO2->getBelongTo() == GO1)) continue;
		//std::cout << "Collision: GO1 Objid = " << GO1->getId() << ", type = " << GO1->getType() << ", GO2 Objid = " << GO2->getId() << ", type = " << GO2->getType() << std::endl;
		
		DamageEvent* e = new DamageEvent(GO1, GO2);
		damageSystem->performDamage(GO1, GO2, e);
		if (!GO1->getDeleted())
		{
			if (e->getResult1() == BREAK_CONSTRAINT && GO1->getConstraints() != nullptr)
			{
				//gamePhysics break constraint
				std::vector<Constraint*>::iterator iter;
				for (iter = GO1->getConstraints()->begin(); iter != GO1->getConstraints()->end(); iter++)
				{
					if ((*iter)->_joint6DOF != nullptr)
					{
						(*iter)->_joint6DOF->setEnabled(false);
						//gamePhysics->getDynamicsWorld()->removeConstraint((*iter)->_joint6DOF);
						if (GO1->getIsWeapon())
						{
							Robot* r = (Robot*)GO1->getBelongTo();
							std::vector<Weapon *> weapons = r->getWeapons();
							std::vector<Weapon *>new_weapons;
							std::vector<Weapon *>::iterator it1;
							for (it1 = weapons.begin(); it1 != weapons.end(); it1++)
							{
								if ((*it1)->getGameObj() != GO1)
								{
									new_weapons.push_back((*it1));
								}
								else
								{
									delete (*it1);
								}
							}
							r->setWeapons(new_weapons);
						}
					}
				}
				GO1->deleteConstraints(&objCollisionPair);
				cout << "GO1 Break ID: " << GO1->getId() << endl;
			
			}
			else if (e->getResult1() == DELETED)
			{
				cout << "GO1 Deleted ID: " << GO1->getId() << endl;
				GO1->setDeleted();
				hasDeleted = 1;
				//set gameevent
			}
			else if (e->getResult1() == DEATH)
			{
				cout << "GO1 Death ID: " << GO1->getId() << endl;
				GO1->getRigidBody()->setLinearFactor(btVector3(0, 0, 0));
				GO1->getRigidBody()->setAngularFactor(btVector3(0, 0, 0));
				((Robot*)(GO1))->nextState();
				GameEvents* GE = new GERobotDeath(((Robot*)GO1)->getCID());
				gameEventList.push_back(GE);
			}
		}
		if (!GO2->getDeleted())
		{
			if (e->getResult2() == BREAK_CONSTRAINT && GO2->getConstraints() != nullptr)
			{
				//gamePhysics break constraint
				std::vector<Constraint*>::iterator iter;
				for (iter = GO2->getConstraints()->begin(); iter != GO2->getConstraints()->end(); iter++)
				{
					if (GO2->getIsWeapon())
					{
						Robot* r = (Robot*)GO2->getBelongTo();
						std::vector<Weapon *> weapons = r->getWeapons();
						std::vector<Weapon *> new_weapons;
						std::vector<Weapon *>::iterator it1;
						for (it1 = weapons.begin(); it1 != weapons.end(); it1++)
						{
							if ((*it1)->getGameObj() != GO2)
							{
								new_weapons.push_back((*it1));
							}
							else
							{
								delete (*it1);
							}
						}
						r->setWeapons(new_weapons);
					}
				}
				GO2->deleteConstraints(&objCollisionPair);
				cout << "GO2 Break ID: " << GO2->getId() << endl;
			}
			else if (e->getResult2() == DELETED)
			{
				cout << "GO2 Deleted ID: " << GO2->getId() << endl;
				GO2->setDeleted();
				hasDeleted = 1;
				//set gameevent
			}
			else if (e->getResult2() == DEATH)
			{
				cout << "GO2 Death ID: " << GO1->getId() << endl;
				GO2->getRigidBody()->setLinearFactor(btVector3(0, 0, 0));
				GO2->getRigidBody()->setAngularFactor(btVector3(0, 0, 0));
				((Robot*)(GO2))->nextState();
				GameEvents* GE = new GERobotDeath(((Robot*)GO2)->getCID());
				gameEventList.push_back(GE);
			}
		}
	}
	if (hasDeleted)
	{
		cleanDataStructures();
	}
	GamePhysics::collisionList.clear();
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
	std::map<int, GameObj *> new_clientPair;
	std::map<int, GameObj *>::iterator it1;
	for (it1 = clientPair.begin(); it1 != clientPair.end(); it1++)
	{
		if (!(*it1).second->getDeleted())
		{
			new_clientPair.insert((*it1));
		}
	}
	clientPair = new_clientPair;
	std::map< btCollisionObject*, GameObj*> new_objCollisionPair;
	std::map< btCollisionObject*, GameObj*>::iterator it2;
	for (it2 = objCollisionPair.begin(); it2 != objCollisionPair.end(); it2++)
	{
		if (!(*it2).second->getDeleted())
		{
			new_objCollisionPair.insert((*it2));
		}
	}
	objCollisionPair = new_objCollisionPair;

	std::vector<GameObj*> new_gameObj;
	std::vector<GameObj*>::iterator it;
	for (it = gameObjs.begin(); it != gameObjs.end(); it++)
	{
		if (!(*it)->getDeleted())
		{
			new_gameObj.push_back((*it));
		}
		else
		{
			std::vector<Constraint*>::iterator iter;
			for (iter = (*it)->getConstraints()->begin(); iter != (*it)->getConstraints()->end(); iter++)
			{
				if ((*iter)->_joint6DOF != nullptr)
				{
					(*iter)->_joint6DOF->setEnabled(false);
					//gamePhysics->getDynamicsWorld()->removeConstraint((*iter)->_joint6DOF);
				}
			}
			gamePhysics->getDynamicsWorld()->removeRigidBody((*it)->getRigidBody());
			deleteGameObj((*it));
		}
	}
	gameObjs = new_gameObj;
}


void GameLogic::deleteGameObj(GameObj* g)
{
	g->deleteConstraints(&objCollisionPair);
	delete(g);
}


/*




void method()
{
   //assume clientPair is setup
   std::vector<GameObj*>::iterator it;




}






*/