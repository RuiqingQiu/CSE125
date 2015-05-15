
/* GameLogic.cpp */
#include "GameLogic.h"



GameLogic::GameLogic()
{
	network = new Network();
	gamePhysics = new GamePhysics();
	countDown = new TimeFrame();
	physicsTimer = new TimeFrame();
	damageSystem = new DamageSystem(INSTANT_KILL);
	scoreboard = new Scoreboard();
	counter = 0;
}

GameLogic::~GameLogic()
{
	delete network;
	delete gamePhysics;
	delete countDown;
	delete damageSystem;
	delete scoreboard;

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
	robot->setBlockType(THREEBYTHREE_BASIC);
	((Robot*)robot)->setMaxHealth(10000);//100);

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
int GameLogic::gameStart(){


	addGround();
	//addWalls();

	gamePhysics->initWorld(&gameObjs);//, &objCollisionPair);

	//vector<ObjectEvents*>::iterator iter;
	//for (iter = buildList.begin(); iter != buildList.end(); iter++)
	//{
	//	double maxHealth = 0;
	//	//Add robot parts to gameObjs and find the Robot, create rigidbodies
	//	std::vector<GameObj*>::iterator it;
	//	std::vector<GameObj*>::iterator it2;

	//	btDynamicsWorld* d = gamePhysics->getDynamicsWorld();
	//	Robot* robot = nullptr;
	//	for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
	//	{

	//		if ((*it)->getBuildID() == 0)
	//		{
	//			robot = (Robot*)(*it);
	//			clientPair.insert(std::pair<int, Robot*>((*iter)->getCid(), robot));
	//			robot->createVehicle(d, robot->getWidth(), robot->getHeight(), robot->getDepth());//, &objCollisionPair);
	//			gameObjs.push_back((*it));
	//		}
	//		else
	//		{
	//			if (!(*it)->getIsWheel())
	//			{
	//				(*it)->createRigidBody();// &objCollisionPair);
	//				d->addRigidBody((*it)->getRigidBody());
	//				gameObjs.push_back((*it));
	//			}

	//		}
	//	}

	//	if (robot == nullptr)
	//	{
	//		cout << "NO ROBOT WAS SENT FROM BUILD MODE" << endl;
	//	}

	//	//Group robot and its parts together
	//	for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
	//	{
	//		if ((*it)->getIsWheel())
	//		{
	//			robot->setWheelType((*it)->getBlockType());
	//		}
	//		else
	//		{

	//			(*it)->setBelongTo(robot);
	//			robot->addPart((*it));
	//			maxHealth += (*it)->getHealth();

	//			if ((*it)->getIsWeapon())
	//			{
	//				Weapon* w;
	//				if ((*it)->getIsRangedWeapon())
	//				{
	//					w = new RangedWeapon((*it)->getBlockType(), (*it));
	//				}
	//				else
	//				{
	//					w = new MeleeWeapon((*it)->getBlockType(), (*it));
	//				}

	//			}
	//		}
	//	}


	//	robot->setMaxHealth(maxHealth);

	//	//Add constraints for the robot
	//	std::vector<GameObj*> parts = robot->getParts();
	//	for (it = parts.begin(); it != parts.end(); it++)
	//	{

	//		d->addConstraint(robot->addConstraint(*it)->_joint6DOF);
	//	}
	//	robot->nextState();
	//}



	int i;
	for (i = 0; i < clientPair.size(); i++)
		{
			int j, k;
		Robot* robot = (Robot*)clientPair.find(i)->second;
		robot->setState(PS_ALIVE);
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
					//gameObj = new GOBox(j + robot->getX(), robot->getY(), k + robot->getZ(), 0, 0, 0, 1, 1, 1, 1, 1);

					double z, x, y;
					z= 0;
					x = 0;
					y = 90;

					btQuaternion* q = convertEulerToQuaternion(x, y, z);

					cout << "q x y z w: " << q->getX() << " , " << q->getY() << " , " << q->getZ() << " , " << q->getW() << endl;

					gameObj = new GOBox(j + robot->getX(), robot->getY(), k + robot->getZ(), q->getX(), q->getY(), q->getZ(), q->getW(), 10, 1, 1, 1);
					delete q;
					gameObj->setBlockType(BASICCUBE);

					if (j == robot->getX() && k == front)
					{

						gameObj->setBlockType(BGUN);
						gameObj->setWeapon(1, gameObj->getBlockType());
					
					}
					
					
					//cout << "weapon id: " << gameObj->getId() << endl;
				}
				else
				{
					int yOffset = ((int)robot->getHeight() / 2) + 1;
					gameObj = new GOBox(j + robot->getX(), robot->getY() + yOffset, k + robot->getZ(), 0, 0, 0, 1, 1, 1, 1, 1);
					gameObj->setBlockType(BASICCUBE);
	
				}

				gameObj->setCollisionType(C_ROBOT_PARTS);
				gameObj->setBelongTo(robot);
				gameObj->createRigidBody();


				gamePhysics->getDynamicsWorld()->addRigidBody(gameObj->getRigidBody());
				int z;
				for (z = 0; z < 1; z++)
				{
					robot->addConstraint(gameObj);
					
				}
				robot->addPart(gameObj);

				gameObjs.push_back(gameObj);
			}
		}

		std::vector<Constraint *>::iterator iter;
		for (iter = robot->getConstraints()->begin(); iter != robot->getConstraints()->end(); iter++)
		{
			gamePhysics->getDynamicsWorld()->addConstraint((*iter)->_joint6DOF);
		}
	}

	countDown->startCountdown(300);
	physicsTimer->startClock();
	countDown->startClock();
	lastTime = countDown->getCurrentTime()/1000;
	return 0;
}

btQuaternion* GameLogic::convertEulerToQuaternion(double x, double y, double z)
{
	double c1 = cos(M_PI*y / 360) ;
	double 	c2 = cos(M_PI*z / 360);
	double c3 = cos(M_PI*x / 360);
	double 	s1 = sin(M_PI*y / 360);
	double 	s2 = sin(M_PI*z / 360);
	double 	s3 = sin(M_PI*x / 360);

	double qW = c1*c2*c3 - s1*s2*s3;
	double qX = s1*s2*c3 + c1*c2*s3;
	double qY = s1*c2*c3 + c1*s2*s3;
	double qZ = c1*s2*c3 - s1*c2*s3;

	return new btQuaternion(qX, qY, qZ, qW);
}

int packet_counter = 0;

unsigned int GameLogic::gameLoop (){

	packet_counter++;
    //ObjectEvents* objEvent = new ObjectEvents(SHOOT);
    //objEvent->setCid(0);
	//objEventList.push_back(objEvent);

    //gameEventList.push_back(new GERobotDeath(0));

	network->receiveFromClients(&objEventList);
	
	//if (countDown->checkCountdown()) return TIMEUP;
	//do gamelogic for all ObjectEvents
	prePhyLogic();
	
	//pass the time into physics
	unsigned int time = physicsTimer->getElapsedTime();
	physicsTimer->startClock();

	//do physics
	gamePhysics->getDynamicsWorld()->stepSimulation(btScalar(1/66.0),4);
	gamePhysics->stepSimulation(&gameObjs, &GamePhysics::collisionList);
	postPhyLogic();
	
	
	if (lastTime != (int) (countDown->getCurrentTime()/1000))
	{

		lastTime = (int) (countDown->getCurrentTime()/1000);

		cout << "packet counter: " << packet_counter << " at time " << lastTime << endl;
		packet_counter = 0;

		GETime* et = new GETime(lastTime);
		gameEventList.push_back(et);
	}
	network->sendActionPackets(&gameObjs, &gameEventList);
	gameEventList.clear();
	
	if (countDown->checkCountdown()){
		return TIMEUP;
	}
	else 	return COUNTDOWN;
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
					   std::vector<GameObj*> projectiles;
					   r->shoot(&projectiles);
					   std::vector<GameObj*>::iterator it;
					  // cout << "size of projectiles" << projectiles.size() << endl;
					   for (it = projectiles.begin(); it != projectiles.end(); it++)
					   {
						  // cout << "before push back:" << gameObjs.size() << endl;
						   gameObjs.push_back((*it));
						  // cout << "after push back:" << gameObjs.size() << endl;
						   gamePhysics->createPhysicsProjectile((Projectile*)(*it));// &objCollisionPair, (*it).second);
						}
					    projectiles.clear();
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
						   
						   cout << "enter build mode " << endl;
						   double maxHealth = 0;
						   //Add robot parts to gameObjs and find the Robot, create rigidbodies
						   std::vector<GameObj*>::iterator it;
						   std::vector<GameObj*>::iterator it2;
						   
						   btDynamicsWorld* d = gamePhysics->getDynamicsWorld();
						   Robot* robot = nullptr;
						   for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
						   {
								
							   if ((*it)->getBuildID() == 0)
							   {
								   robot = (Robot*)(*it);
								   clientPair.find((*iter)->getCid())->second->setImmediateDeleted();
								   clientPair.find((*iter)->getCid())->second = (*it);
								   robot->createVehicle(d, robot->getWidth(), robot->getHeight(), robot->getDepth());// , &objCollisionPair);
								   gameObjs.push_back((*it));
							   }
							   else
							   {
								   if (!(*it)->getIsWheel())
								   {
									   (*it)->createRigidBody();//&objCollisionPair);
									   d->addRigidBody((*it)->getRigidBody());
									   gameObjs.push_back((*it));
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
									   (*it)->setWeapon((*it)->getIsRangedWeapon(), (*it)->getBlockType());
								   }
							   }
						   }


						   robot->setMaxHealth(maxHealth);

						   //Add constraints for the robot
						   std::vector<GameObj*> parts = robot->getParts();
						   for (it = parts.begin(); it != parts.end(); it++)
						   {
							  
							   d->addConstraint(robot->addConstraint(*it)->_joint6DOF);
							   /*
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
							   }*/
						   }
						   robot->nextState();
			}
			default:{
						//gamePhysics->createPhysicsEvent(type, gObj);
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
				btRaycastVehicle* v = ((Robot*)*it)->getVehicle();
				btScalar s = v->getCurrentSpeedKmHour();
				double braking_force = s*BRAKE_SPEED;
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
		/*btTransform trans;
		if ((*it)->getId() == 0)
		{
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
		}
		if ((*it)->getIsWeapon())
		{
			(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
		}*/
		if ((*it)->getIsRobot() != 0)
		{
		//	cout << "release wheel " << endl;
			btWheelInfo leftWheel = ((Robot *)*it)->getVehicle()->getWheelInfo(2);
			btWheelInfo rightWheel = ((Robot *)*it)->getVehicle()->getWheelInfo(3);
			double steering_delta = TURN_SPEED / 2;

			if (leftWheel.m_steering > 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering += -steering_delta;
			if (rightWheel.m_steering > 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering += -steering_delta;
			if (leftWheel.m_steering < 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering += steering_delta;
			if (rightWheel.m_steering < 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering += steering_delta;
		}
	}

	objEventList.clear();
	//cout << "objEventList size == " << objEventList.size() << endl;
}

void GameLogic::postPhyLogic(){
	std::vector<Collision *>::iterator it;
	Robot* dmgDealtArr[4] = { nullptr };
	for (it = GamePhysics::collisionList.begin(); it != GamePhysics::collisionList.end(); it++)
	{
		btCollisionObject* obj1 = static_cast<btCollisionObject*>((*it)->getObj1());
		btCollisionObject* obj2 = static_cast<btCollisionObject*>((*it)->getObj2());
		GameObj* GO1 = (GameObj*)obj1->getUserPointer();//objCollisionPair.find(obj1)->second;
		GameObj* GO2 = (GameObj*)obj2->getUserPointer();//objCollisionPair.find(obj2)->second;

		//cout << "Collision pairs: GO1: " << GO1->getId() << endl;
		//cout << "GO2: " << GO2->getId() << endl;
		//if ((GO1->getBelongTo() != nullptr && GO1->getBelongTo() == GO2) || (GO2->getBelongTo() != nullptr && GO2->getBelongTo() == GO1)) continue;
		//std::cout << "Collision: GO1 Objid = " << GO1->getId() << ", type = " << GO1->getType() << ", GO2 Objid = " << GO2->getId() << ", type = " << GO2->getType() << std::endl;
		
		DamageEvent* e = new DamageEvent(GO1, GO2);
		int clientCollision = damageSystem->performDamage(GO1, GO2, e);
		if (clientCollision != CH_INVALIDCOLLISION)
		{
			//cout << "clientCollision" << clientCollision << endl;
			GECollisonHappen* gech = new GECollisonHappen(clientCollision, (*it)->getX(), (*it)->getY(), (*it)->getZ());
			gameEventList.push_back(gech);
		}
		

		postDamageLogic(GO1, e->getResult1(), (*it)->getPt());
		postDamageLogic(GO2, e->getResult2(), (*it)->getPt());



		if (e->getDamage1())
		{
			dmgDealtArr[((Robot*)GO1->getBelongTo())->getCID()] = (Robot*)GO1->getBelongTo();
		}
		if (e->getDamage2())
		{
			dmgDealtArr[((Robot*)GO2->getBelongTo())->getCID()] = (Robot*)GO2->getBelongTo();
		}
	}

	postHealthLogic(dmgDealtArr);

	
	if (scoreboard->getHasChanged())
	{
		createScoreboardUpdateEvent();
	}

	cleanDataStructures();
	GamePhysics::collisionList.clear();
}

void GameLogic::createScoreboardUpdateEvent()
{
	GEScoreboardUpdate* GE = new GEScoreboardUpdate(scoreboard->getTakedowns(), scoreboard->getDeaths(), scoreboard->getGold());
	gameEventList.push_back(GE);
}

void GameLogic::postHealthLogic(Robot* arr[4])
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if (arr[i] != nullptr)
		{
			createHealthUpdateEvent(arr[i]);
			if (arr[i]->getHealth() == 0)
			{
				postDeathLogic(arr[i]);
			}
		}
	}
}

void GameLogic::postDeathLogic(Robot* r)
{
	scoreboard->incDeaths(r->getCID());
	scoreboard->incTakedowns(r->getDiedTo()->getCID());
	createDeathEvent(r);
}

void GameLogic::createHealthUpdateEvent(Robot* r)
{
	GEHealthUpdate* GE = new GEHealthUpdate(r->getCID(), r->getHealth(), r->getMaxHealth());
	gameEventList.push_back(GE);
}

void GameLogic::postDamageLogic(GameObj* g, int result, btManifoldPoint* pt)
{
	if (!g->getDeleted())
	{
		if (result == BREAK_CONSTRAINT && g->getConstraints() != nullptr)
		{
			//cout << "GO Break ID: " << g->getId() << endl;
			breakConstraints(g);
			cout << "Impulse: " << pt->getAppliedImpulse() << endl;
			btVector3 randomForce(rand(), rand(), rand());
			randomForce.normalize();
			
			g->getRigidBody()->applyCentralImpulse(randomForce*pt->getAppliedImpulse());
		}
		else if (result == DELETED)
		{
			//cout << "GO Deleted ID: " << g->getId() << endl;
			g->setImmediateDeleted();
		}
		else if (result == DEATH)
		{
			//cout << "GO Death ID: " << g->getId() << endl;
			postDeathLogic((Robot*)g);
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

	//std::map< btCollisionObject*, GameObj*> new_objCollisionPair;
	//std::map< btCollisionObject*, GameObj*>::iterator it2;
	//for (it2 = objCollisionPair.begin(); it2 != objCollisionPair.end(); it2++)
	//{
	//	if (!(*it2).second->getDeleted())
	//	{
	//		new_objCollisionPair.insert((*it2));
	//	}
	//}
	//objCollisionPair = new_objCollisionPair;

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
	
		Robot* r = (Robot*)g->getBelongTo();
		std::vector<GameObj *> parts = r->getParts();
		std::vector<GameObj *>new_parts;
		std::vector<GameObj *>::iterator it1;
		for (it1 = parts.begin(); it1 != parts.end(); it1++)
		{
			if ((*it1) != g)
			{
				new_parts.push_back((*it1));
			}
			else
			{
				if ((*it1) != nullptr)
				 {
					(*it1)->setDeleted();
				}
			}
		}
		r->setParts(new_parts);
	
	return g->deleteConstraints();//&objCollisionPair);
}

void GameLogic::createDeathEvent(Robot* r)
{
	r->setState(PS_DEAD);
	if (r->getDiedTo() != nullptr){
		GameEvents* GE = new GERobotDeath(r->getCID(), r->getDiedTo()->getCID());
		gameEventList.push_back(GE);
	}
	else{

		GameEvents* GE = new GERobotDeath(r->getCID(),-1);
		gameEventList.push_back(GE);
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

void GameLogic::deleteGameObj(GameObj* g)
{
	g->deleteConstraints();//&objCollisionPair);
	delete(g);
}

int buildplayer[4] = {0};
int buildnum;
int GameLogic::buildMode(){
	network->receiveFromClients(&objEventList);
	
	std::vector<ObjectEvents *>::iterator iter;
	iter = objEventList.begin();
	while (iter != objEventList.end())
	{
		int cid = (*iter)->getCid();
		int type = (*iter)->getEvent();
		switch (type){
		case BUILD_ROBOT:{
					if (buildplayer[cid] == 0){
						 buildplayer[cid] = 1;
						 buildnum++;
						 buildList.push_back(*iter);
					 }
			}
			default:{
						break;
			}
		}
	}

	objEventList.clear();
	

	if (lastTime > countDown->getCurrentTime())
	{
		lastTime = countDown->getCurrentTime();
		network->sendInitBuild(TIMER, lastTime);
	}

	if (countDown->checkCountdown()){
		int i;
		for (i = 0; i < 4;i++)
		{
			if (buildplayer[i] != 1)
			{
				network->sendBuildRequest(i);
			}
		}
		return COUNTDOWN;
	}else if(buildnum < 4){
		return COUNTDOWN;
	}
	else{
		return TIMEUP;
	}
}


int GameLogic::startBuild(){

	network->sendInitBuild(INIT_BUILD, 120);
	countDown->startCountdown(120);
	countDown->startClock();
	lastTime = countDown->getCurrentTime();
	return 0;
}


int GameLogic::endGame(){
	//wait until recieve restart package
	return WAIT;
}



int GameLogic::clearGame(){

	gameEventList.clear();
	// store scoreboard create ScoreBoard Event
	// create end game event;
	clientPair.clear();
	gameObjs.clear();
	//objCollisionPair.clear();
	network->sendActionPackets(&gameObjs, &gameEventList);
	return 0;
}