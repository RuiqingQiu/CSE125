
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
	robot->setMass(100);
	robot->setType(BOX);
	((Robot*)robot)->setCID(cid);
	((Robot*)robot)->setMaxHealth(100);
	robot->setBlockType(THREEBYTHREE_BASIC);

	this->gameObjs.push_back(robot);
	clientPair.insert(std::pair<int, GameObj*>(cid, robot));
	
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

	int i;
	for (i = 0; i < clientPair.size(); i++)
		{
			int j, k;
		Robot* robot = (Robot*)clientPair.find(i)->second;
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
				if(j == left || j == right || k == front || k == back)
				{
					btTransform trans;
					robot->getRigidBody()->getMotionState()->getWorldTransform(trans);
					
					gameObj = new GOBox(j + robot->getX(), robot->getY(), k + robot->getZ(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ(), trans.getRotation().getW(), 1, 1, 1, 1);
					if (k == back)
					{
						Weapon* w = new RangedWeapon(BGUN, gameObj);
						gameObj->setBlockType(METHCUBE);
						//cout << "weapon id: " << gameObj->getId() << endl;
						robot->addWeapon(w);
					}
					else
					{
						gameObj->setBlockType(WOODENCUBE);
					}
				}
				else
				{
					int yOffset = ((int)robot->getHeight() / 2) + 1;
					gameObj = new GOBox(j + robot->getX(), robot->getY() + yOffset, k + robot->getZ(), 0, 0, 0, 1, 1, 1, 1, 1);
					gameObj->setBlockType(GLOWINGCUBE);
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
			}
		}

		std::vector<Constraint *>::iterator iter;
		for (iter = robot->getConstraints()->begin(); iter != robot->getConstraints()->end(); iter++)
		{
			gamePhysics->getDynamicsWorld()->addConstraint((*iter)->_joint6DOF);
		}
	}
}


unsigned int GameLogic::gameLoop (){

    //ObjectEvents* objEvent = new ObjectEvents(SHOOT);
    //objEvent->setCid(0);
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
	network->sendActionPackets(&gameObjs, &gameEventList);
	gameEventList.clear();
	
	return COUNTDOWN;
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
							
						   double maxHealth = 0;
						   //Add robot parts to gameObjs and find the Robot, create rigidbodies
						   std::vector<GameObj*>::iterator it;
						   std::vector<GameObj*>::iterator it2;
						   
						   btDynamicsWorld* d = gamePhysics->getDynamicsWorld();
						   Robot* robot = nullptr;
						   for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
						   {
							   gameObjs.push_back((*it));
							   if ((*it)->getBuildID() == 0)
							   {
								   robot = (Robot*)(*it);
								   clientPair.find((*iter)->getCid())->second->setDeleted();
								   clientPair.find((*iter)->getCid())->second = (*it);
								   robot->createVehicle(d, robot->getWidth(), robot->getHeight(), robot->getDepth(), &objCollisionPair);
							   }
							   else
							   {
								   if (!(*it)->getIsWheel())
								   {
									   (*it)->createRigidBody(&objCollisionPair);
									   d->addRigidBody((*it)->getRigidBody());
								   }
								
							   }
						   }

						   if (robot == nullptr)
						   {
							   cout << "NO ROBOT WAS SENT FROM BUILD MODE" << endl;
						   }

						   //Group robot and its parts together
						   for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
						   {
							   if ((*it)->getIsWheel())
							   {
								   robot->setWheelType((*it)->getBlockType());
							   }
							   else
							   {

								   (*it)->setBelongTo(robot);
								   robot->addPart((*it));
								   maxHealth += (*it)->getHealth();

								   if ((*it)->getIsWeapon())
								   {
									   Weapon* w;
									   if ((*it)->getIsRangedWeapon())
									   {
										   w = new RangedWeapon((*it)->getBlockType(), (*it));
									   }
									   else
									   {
										   w = new MeleeWeapon((*it)->getBlockType(), (*it));
									   }
									   robot->addWeapon(w);
								   }
							   }
						   }

						   robot->setMaxHealth(maxHealth);

						   //Add constraints for the robot
						   std::vector<GameObj*> parts = robot->getParts();
						   for (it = parts.begin(); it != parts.end(); it++)
						   {
							   int l = (*it)->getLeftID();
							   int r = (*it)->getRightID();
							   int f = (*it)->getFrontID();
							   int ba = (*it)->getBackID();
							   int be = (*it)->getBelowID();
							   for (it2 = parts.begin(); it2 != parts.end(); it2++)
							   {
								   if ((*it2)->getBuildID() == l)
								   {
									   d->addConstraint((*it)->addConstraint((*it2))->_joint6DOF);
								   }
								   if ((*it2)->getBuildID() == r)
								   {
									   d->addConstraint((*it)->addConstraint((*it2))->_joint6DOF);
								   }
								   if ((*it2)->getBuildID() == f)
								   {
									   d->addConstraint((*it)->addConstraint((*it2))->_joint6DOF);
								   }
								   if ((*it2)->getBuildID() == ba)
								   {
									   d->addConstraint((*it)->addConstraint((*it2))->_joint6DOF);
								   }
								   if ((*it2)->getBuildID() == be)
								   {
									   d->addConstraint((*it)->addConstraint((*it2))->_joint6DOF);
								   }
							   }
						   }
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
			btRaycastVehicle* v = ((Robot*)*it)->getVehicle();
			btScalar s = v->getCurrentSpeedKmHour();
			double braking_force = s*BRAKE_SPEED;
			if ((*it)->getIsRobot() != 0)
			{
				v->applyEngineForce(-braking_force, 0);
				v->applyEngineForce(-braking_force, 1);
				v->applyEngineForce(-braking_force, 2);
				v->applyEngineForce(-braking_force, 3);

			}
		}
	}

	std::vector<GameObj*>::iterator it;
	for (it = gameObjs.begin(); it != gameObjs.end(); ++it)
	{
		btTransform trans;
		if ((*it)->getId() == 0)
		{
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
		}
		if ((*it)->getIsWeapon())
		{
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
		}
		if ((*it)->getIsRobot() != 0)
		{
			btWheelInfo leftWheel = ((Robot *)*it)->getVehicle()->getWheelInfo(2);
			btWheelInfo rightWheel = ((Robot *)*it)->getVehicle()->getWheelInfo(3);
			double steering_delta = TURN_SPEED / 2;

			if (leftWheel.m_steering > 0)
				leftWheel.m_steering += -steering_delta;
			if (rightWheel.m_steering > 0)
				rightWheel.m_steering += -steering_delta;
			if (leftWheel.m_steering < 0)
				leftWheel.m_steering += steering_delta;
			if (rightWheel.m_steering < 0)
				rightWheel.m_steering += steering_delta;
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

		//if ((GO1->getBelongTo() != nullptr && GO1->getBelongTo() == GO2) || (GO2->getBelongTo() != nullptr && GO2->getBelongTo() == GO1)) continue;
		//std::cout << "Collision: GO1 Objid = " << GO1->getId() << ", type = " << GO1->getType() << ", GO2 Objid = " << GO2->getId() << ", type = " << GO2->getType() << std::endl;
		
		DamageEvent* e = new DamageEvent(GO1, GO2);
		damageSystem->performDamage(GO1, GO2, e);
		postDamageLogic(GO1, e);
		postDamageLogic(GO2, e);
	}

	cleanDataStructures();
	GamePhysics::collisionList.clear();
}

void GameLogic::postDamageLogic(GameObj*, DamageEvent* e)
{
	if (!g->getDeleted())
	{
		if (e->getResult1() == BREAK_CONSTRAINT && g->getConstraints() != nullptr)
		{
			//cout << "GO Break ID: " << g->getId() << endl;
			breakConstraints(g);
		}
		else if (e->getResult1() == DELETED)
		{
			//cout << "GO Deleted ID: " << g->getId() << endl;
			g->setDeleted();
		}
		else if (e->getResult1() == DEATH)
		{
			//cout << "GO Death ID: " << g->getId() << endl;
			createDeathEvent(g);
		}
	}
}

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
			breakConstraints(*it);
			gamePhysics->getDynamicsWorld()->removeRigidBody((*it)->getRigidBody());
			deleteGameObj(*it);
		}
	}
	gameObjs = new_gameObj;
}

int GameLogic::breakConstraints(GameObj* g)
{
	std::vector<Constraint*>::iterator iter;
	for (iter = g->getConstraints()->begin(); iter != g->getConstraints()->end(); iter++)
	{
		if ((*iter)->_joint6DOF != nullptr)
		{
			(*iter)->_joint6DOF->setEnabled(false);
		}
	}
	if (g->getIsWeapon())
	{
		Robot* r = (Robot*)g->getBelongTo();
		std::vector<Weapon *> weapons = r->getWeapons();
		std::vector<Weapon *>new_weapons;
		std::vector<Weapon *>::iterator it1;
		for (it1 = weapons.begin(); it1 != weapons.end(); it1++)
		{
			if ((*it1)->getGameObj() != g)
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
	return g->deleteConstraints(&objCollisionPair);
}

void GameLogic::createDeathEvent(GameObj* g)
{
	((Robot*)(g))->setState(PS_DEAD);
	GameEvents* GE = new GERobotDeath(((Robot*)g)->getCID());
	gameEventList.push_back(GE);
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

void GameLogic::deleteGameObj(GameObj* g)
{
	g->deleteConstraints(&objCollisionPair);
	delete(g);
}