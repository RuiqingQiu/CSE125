
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
	dist = new std::uniform_real_distribution<double>(-1.0f, 1.0f);
	hill = new Hill(0, 0, FIELD_WIDTH, FIELD_HEIGHT/3, FIELD_WIDTH/12, 3);
	counter = 0;
	spawnPoint = new SpawnPoint(FIELD_WIDTH);
	dmgDealtArr[4] = { nullptr };
	int i;
	for (i = 0; i < 4; i++)
	{
		names[i] = "";
	}
	srand(time(NULL));
}

GameLogic::~GameLogic()
{
	delete network;
	delete gamePhysics;
	delete countDown;
	delete damageSystem;
	delete scoreboard;
	delete hill;
	delete spawnPoint;

}

unsigned int GameLogic::waitToConnect()
{
	int cid; 
	cid = network->waitForConnections();

	if (cid == -1) return WAIT;
	

	//GameObj* robot = new Robot(cid, "testname");
	//robot->setX((cid % 2) * 30);
	//robot->setY(4);
	//robot->setZ(cid - 2<0 ? 0 : 30);
	//robot->setqX(0);
	//robot->setqY(0);
	//robot->setqZ(0);
	//robot->setqW(1);
	//robot->setMass(100);
	//robot->setType(BOX);
	//((Robot*)robot)->setCID(cid);
	//robot->setBlockType(THREEBYTHREE_BASIC);
	//((Robot*)robot)->setMaxHealth(10000);//100);


	//this->gameObjs.push_back(robot);
	//clientPair.insert(std::pair<int, GameObj*>(cid, robot));
	
	network->receiveFromClients(&objEventList);
	std::vector<ObjectEvents *>::iterator iter;
	for (iter = objEventList.begin(); iter != objEventList.end(); iter++)
	{
		unsigned int type = (*iter)->getEvent();
		switch (type) {

		case INIT_CONNECTION:
			string name = (*iter)->getName();
			(*iter)->setCid(cid);
			names[cid] = name;
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
	addWalls();
	createCrown();

	hill->createParticles(&gameObjs);


	gamePhysics->initWorld(&gameObjs);//, &objCollisionPair);
    vector<GameObj*>::iterator it;
    for (it = gameObjs.begin(); it != gameObjs.end(); ++it) {
		if ((*it)->getBlockType() == MONEY) 
		{
			(*it)->getRigidBody()->setGravity(btVector3(0, 0, 0));
			(*it)->getRigidBody()->setAngularFactor(btVector3(0, 1, 0));
        }
    }


	//cout << "end of init world" << endl;
	vector<ObjectEvents*>::iterator iter;
	for (iter = buildList.begin(); iter != buildList.end(); iter++)
	{

		double maxHealth = 0;
		//Add robot parts to gameObjs and find the Robot, create rigidbodies
		std::vector<GameObj*>::iterator it;
		std::vector<GameObj*>::iterator it2;
		btDynamicsWorld* d = gamePhysics->getDynamicsWorld();
		Robot* robot = nullptr;
		btVector3 sp = spawnPoint->nextPoint();
		cout << " x y z: " << sp.getX() << " , " << sp.getY() << " , " << sp.getZ() << endl;
		if (sp.getZ() < 0)
		{
			for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
			{

				(*it)->setX((*it)->getX()*-1);
				(*it)->setZ((*it)->getZ()*-1);
				btQuaternion q((*it)->getqX(), (*it)->getqY(), (*it)->getqZ(), (*it)->getqW());
				btQuaternion rotQ(0, 1, 0, 0);
				q = q*rotQ;
				(*it)->setqX(q.getX());
				(*it)->setqY(q.getY());
				(*it)->setqZ(q.getZ());
				(*it)->setqW(q.getW());
			}
		}


		for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
		{

			int cid = (*iter)->getCid();
			float xoffset = sp.getX();
			float zoffset =  sp.getZ();
			float yoffset =  sp.getY();

			if ((*it)->getBuildID() == 0)
			{
				robot = (Robot*)(*it);
				robot->setCID(cid);
				scoreboard->setGold(cid, robot->getCurrMoney());
				char * nameChar = new char[names[cid].length() + 1];
				std::strcpy(nameChar, names[cid].c_str());
				robot->setName(nameChar);
				//delete[] nameChar;

				clientPair.insert(std::pair<int, Robot*>(cid, robot));
				robot->setX(xoffset);
				robot->setY(robot->getY()+yoffset);
				robot->setZ(zoffset);
				robot->createVehicle(d, robot->getWidth(), robot->getHeight(), robot->getDepth());//, &objCollisionPair);
				gameObjs.push_back((*it));
			}
			else
			{
				if (!(*it)->getIsWheel())
				{
					double initY = (*it)->getY();
					double initX = (*it)->getX();
					double initZ = (*it)->getZ();
					(*it)->setX(initX + xoffset);
					(*it)->setZ(initZ + zoffset);
					(*it)->setY(initY + yoffset);

					(*it)->createRigidBody();// &objCollisionPair);
					d->addRigidBody((*it)->getRigidBody());
					//cout << "new build robot ids:  " << (*it)->getId() << endl;
					gameObjs.push_back((*it));
					if ((*it)->getIsWeapon())
					{
						(*it)->setWeapon((*it)->getIsRangedWeapon(), (*it)->getBlockType());
					}
				}
				else
				{
					robot->addSpeedMultipler((*it)->getSpeedMultiplier());
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
			}
		}


		robot->setMaxHealth(maxHealth);

		//Add constraints for the robot
		std::vector<GameObj*> parts = robot->getParts();
		for (it = parts.begin(); it != parts.end(); it++)
		{

			//d->addConstraint(robot->addConstraint(*it)->_joint6DOF);
			int l = (*it)->getLeftID();
			int r = (*it)->getRightID();
			int f = (*it)->getFrontID();
			int ba = (*it)->getBackID();
			int be = (*it)->getBelowID();
			for (it2 = parts.begin(); it2 != parts.end(); it2++)
			{
				for (int z = 0; z < NUM_OF_CONSTRAINTS; z++)
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
		//createHealthUpdateEvent(robot);
		robot->nextState();
	}



	//int i;
	//for (i = 0; i < clientPair.size(); i++)
	//	{
	//		int j, k;
	//	Robot* robot = (Robot*)clientPair.find(i)->second;
	//	robot->setState(PS_ALIVE);
	//	int left = -((int)(robot->getWidth() / 2)) - 1;
	//	int right = ((int)(robot->getWidth() / 2)) + 1;
	//	int front = -((int)(robot->getDepth() / 2)) - 1;
	//	int back = ((int)(robot->getDepth() / 2)) + 1;
	//	for (j = left; j <= right; j++)
	//	{
	//		for (k = front; k <= back; k++)
	//		{
	//			GameObj* gameObj;
	//			if(j == left || j == right || k == front || k == back)
	//			{
	//				btTransform trans;
	//				robot->getRigidBody()->getMotionState()->getWorldTransform(trans);

	//				//btVector3* res = convertQuaternionToEuler(&trans.getRotation());

	//				btQuaternion* q = convertEulerToQuaternion(0, 0, 0);//res->getX(), res->getY(), res->getZ());

	//				gameObj = new GOBox(j + robot->getX(), robot->getY(), k + robot->getZ(), q->getX(), q->getY(), q->getZ(), q->getW(), 10, 1, 1, 1);
	//				delete q;
	//				gameObj->setBlockType(BASICCUBE);

	//				if (j == robot->getX() && k == front)
	//				{
	//					gameObj->setBlockType(BGUN);
	//					gameObj->setWeapon(1, gameObj->getBlockType());
	//				}
	//				
	//				
	//				//cout << "weapon id: " << gameObj->getId() << endl;
	//			}
	//			else
	//			{
	//				int yOffset = ((int)robot->getHeight() / 2) + 1;
	//				gameObj = new GOBox(j + robot->getX(), robot->getY() + yOffset, k + robot->getZ(), 0, 0, 0, 1, 1, 1, 1, 1);
	//				gameObj->setBlockType(BASICCUBE);
	//
	//			}

	//			gameObj->setBelongTo(robot);
	//			gameObj->createRigidBody();


	//			gamePhysics->getDynamicsWorld()->addRigidBody(gameObj->getRigidBody());
	//			int z;
	//			for (z = 0; z < 1; z++)
	//			{
	//				robot->addConstraint(gameObj);
	//				
	//			}
	//			robot->addPart(gameObj);

	//			gameObjs.push_back(gameObj);
	//		}
	//	}

	//	std::vector<Constraint *>::iterator iter;
	//	for (iter = robot->getConstraints()->begin(); iter != robot->getConstraints()->end(); iter++)
	//	{
	//		gamePhysics->getDynamicsWorld()->addConstraint((*iter)->_joint6DOF);
	//	}
	//}


	countDown->startCountdown(600);
	physicsTimer->startClock();
	countDown->startClock();
	lastTime = countDown->getCurrentTime()/1000;
	cout << "Timer: " << lastTime << endl;
	//cout << "end of game start" << endl;
	network->sendInitBuild(INIT_BATTLE, 0);
	objEventList.clear();
	
	return 0;
}

btVector3* GameLogic::convertQuaternionToEuler(btQuaternion* q)
{
	btVector3* pitchYawRoll = new btVector3();
	pitchYawRoll->setY((double)atan2(2.0f * q->getX() * q->getW() + 2.0f * q->getY() * q->getZ(), 1.0f - 2.0f * (q->getZ()*q->getZ() + q->getW()*q->getW())));     // Yaw 
	pitchYawRoll->setX((double)asin(2.0f * (q->getX() * q->getZ() - q->getW() * q->getY())));                             // Pitch 
	pitchYawRoll->setZ((double)atan2(2.0f * q->getX() * q->getY() + 2.0f * q->getZ() * q->getW(), 1.0f - 2.0f * (q->getY()*q->getY() + q->getZ()*q->getZ())));      // Roll 
	return pitchYawRoll;
}

btQuaternion* GameLogic::convertEulerToQuaternion(double x, double y, double z)
{
	double c1 = cos(M_PI*y / 360);
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

	for (int i = 0; i < numPlayers; i++)
	{
		dmgDealtArr[i] = nullptr;
	}
	packet_counter++;
    //ObjectEvents* objEvent = new ObjectEvents(SHOOT);
    //objEvent->setCid(0);
	//objEventList.push_back(objEvent);

    //gameEventList.push_back(new GERobotDeath(0));

	network->receiveFromClients(&objEventList);
	
	//if (countDown->checkCountdown()) return TIMEUP;
	//do gamelogic for all ObjectEvents

	animateCrown();
	animateBuilding();

	prePhyLogic();
	
	//pass the time into physics
	unsigned int time = physicsTimer->getElapsedTime();
	physicsTimer->startClock();

	//do physics
	gamePhysics->getDynamicsWorld()->stepSimulation(btScalar(1/66.0),4);
	gamePhysics->stepSimulation(&gameObjs, &GamePhysics::collisionList);

	
	std::map<int, GameObj *>::iterator iter;
	for (iter = clientPair.begin(); iter != clientPair.end(); iter++)
	{
		Robot* r = (Robot*)(*iter).second;
		if (r->getHasDeleted()) continue;
		if (r->getState() == PS_ALIVE && r->getJustBuilt())
		{
			createHealthUpdateEvent(r);
			r->setJustBuilt(0);
		}
	}


 
	if (lastTime != (int) (countDown->getCurrentTime()/1000))
	{
		lastTime = (int) (countDown->getCurrentTime()/1000);

		cout << "FPS: " << packet_counter << " at Timer: " << lastTime << endl;
		packet_counter = 0;

		std::map<int, GameObj *>::iterator it;
		for (it = clientPair.begin(); it != clientPair.end(); it++)
		{
			Robot* r = (Robot*)(*it).second;
			if (r->getState() == PS_ALIVE)
			{
				int gainedGold = hill->inHill(r->getX(), r->getZ());
				if (gainedGold > 0)
				{
					scoreboard->incGold((*it).first, gainedGold);
					createPlayerHillUpdateEvent((*it).first);
				}
			}
		}

		if (lastTime % UPDATE_HILL == 0)
		{
			hill->update();
			createHillUpdateEvent();
		}



		++secondCounter;
		if (secondCounter >= 3)
		{
			updateBlockEffects();
			secondCounter = 0;
		}

		updateDoTDamage();

		GETime* et = new GETime(lastTime);
		gameEventList.push_back(et);
	}

    hill->updateParticles();


	postPhyLogic();
	if (scoreboard->getHasChanged())
	{
		//cout << "scoreboard changed--------------------------------------------------------------" << endl;
		createScoreboardUpdateEvent();
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
		//cout << "PACKET TYPE: " << type << endl;
		int cid = (*iter)->getCid();
		std::map<int, GameObj *>::iterator it;
		it = clientPair.find(cid);

		//ullptr check still does not work
		GameObj* gObj = it->second;
		if (gObj == nullptr) continue;
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
			case SUICIDE:{
							 r->applyDamage(r->getMaxHealth());
							 r->setDiedTo(r);
							 dmgDealtArr[cid] = r;
							 postDeathLogic(r);
							 break;
			}
			case BOOST:
			{
						  btTransform rbTrans = r->getRigidBody()->getWorldTransform();
						  btVector3 relativeForce = btVector3(0, 0, -4000);
						  btMatrix3x3 boxRot = r->getRigidBody()->getWorldTransform().getBasis();
						  btVector3 correctedForce = boxRot * relativeForce;
						  r->getRigidBody()->applyCentralImpulse(correctedForce);
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
			//cout << "IN PS_BUILD1" << endl;
			switch (type) {
			case BUILD_ROBOT:{
	
								 //cout << "IN PS_BUILD2" << endl;
						   
								 double maxHealth = 0;
								 //Add robot parts to gameObjs and find the Robot, create rigidbodies
								 std::vector<GameObj*>::iterator it;
								 std::vector<GameObj*>::iterator it2;

								 btDynamicsWorld* d = gamePhysics->getDynamicsWorld();
								 Robot* robot = nullptr;
								 btVector3 sp = spawnPoint->nextPoint();
								 if (sp.getZ() < 0)
								 {
									 for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
									 {
										 (*it)->setX((*it)->getX()*-1);
										 (*it)->setZ((*it)->getZ()*-1);
										 btQuaternion q((*it)->getqX(), (*it)->getqY(), (*it)->getqZ(), (*it)->getqW());
										 btQuaternion rotQ(0, 1, 0, 0);
										 q = q*rotQ;
										 (*it)->setqX(q.getX());
										 (*it)->setqY(q.getY());
										 (*it)->setqZ(q.getZ());
										 (*it)->setqW(q.getW());
									 }
								 }

								 for (it = (*iter)->roboBuild.begin(); it != (*iter)->roboBuild.end(); it++)
								 {

									 int cid = (*iter)->getCid();
									 float xoffset = sp.getX();
										 float zoffset = sp.getZ();
									 float yoffset = sp.getY();

									 if ((*it)->getBuildID() == 0)
									 {
										 robot = (Robot *) clientPair.find(cid)->second;
										// if (robot->getIsRobot()) cout << "is robot deleted in rebuild GOID: " << robot->getId() << endl;
										 robot->setImmediateDeleted();
										 robot = (Robot*)(*it);
										 //clientPair.insert(std::pair<int, Robot*>(cid, robot));
										 robot->setCID(cid);
										 scoreboard->setGold(cid, robot->getCurrMoney());
										 char * nameChar = new char[names[cid].length() + 1];
										 std::strcpy(nameChar, names[cid].c_str());
										 robot->setName(nameChar);

										 robot->setX(xoffset);
										 robot->setZ(zoffset);
										 robot->setY(robot->getY() + yoffset);
										 robot->createVehicle(d, robot->getWidth(), robot->getHeight(), robot->getDepth());//, &objCollisionPair);
										 gameObjs.push_back((*it));
										 //cout << "before assign" << clientPair.find(cid)->second << endl;
										 clientPair.find(cid)->second = robot;
										// cout << "after assign" << clientPair.find(cid)->second << endl;

									 }
									 else
									 {
										 if (!(*it)->getIsWheel())
										 {
											 float initX = (*it)->getX();
											 float initZ = (*it)->getZ();
											 float initY = (*it)->getY();
											 (*it)->setX(initX + xoffset);
											 (*it)->setZ(initZ + zoffset);
											 (*it)->setY(initY + yoffset);
											 (*it)->createRigidBody();// &objCollisionPair);
											 d->addRigidBody((*it)->getRigidBody());
											 gameObjs.push_back((*it));
											 if ((*it)->getIsWeapon())
											 {
												 (*it)->setWeapon((*it)->getIsRangedWeapon(), (*it)->getBlockType());
											 }
										 }
										 else
										 {
											 robot->addSpeedMultipler((*it)->getSpeedMultiplier());
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
										 for (int z = 0; z < NUM_OF_CONSTRAINTS; z++)
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
								 //createHealthUpdateEvent(robot);
								 robot->nextState();
								 break;
			}
			default:{
						break;
			}
			}

		}
		else if (r->getState() == PS_DEAD){
			cout << "IN PS_DEAD" << endl;
			r->nextState();
		}
		iter++;
	}

	if (objEventList.size() == 0)
	{
		std::vector<GameObj*>::iterator it;
		for (it = gameObjs.begin(); it != gameObjs.end(); ++it)
		{
			if ((*it)->getIsRobot()==1)
			{
					btRaycastVehicle* v = ((Robot*)*it)->getVehicle();
					btScalar s = v->getCurrentSpeedKmHour();
					double braking_force = s*BRAKE_SPEED;
					v->applyEngineForce(-braking_force, 0);
					v->applyEngineForce(-braking_force, 1);
					v->applyEngineForce(-braking_force, 2);
					v->applyEngineForce(-braking_force, 3);

					btVector3 vel = v->getRigidBody()->getLinearVelocity();
					double mag = sqrt(vel.getX()*vel.getX() + vel.getY()*vel.getY() + vel.getZ()*vel.getZ());

					if (s >= MAX_SPEED*(*it)->getSpeedMultiplier()*((Robot*)(*it))->getSlowValue() || mag > MAX_SPEED*(*it)->getSpeedMultiplier()*((Robot*)(*it))->getSlowValue() / 4)
					{
						v->getRigidBody()->setLinearFactor(btVector3(0.7, 0.7, 0.7));
						v->getRigidBody()->setDamping(0.3, 0);
					}
					else
					{
						v->getRigidBody()->setLinearFactor(btVector3(1, 1, 1));
						v->getRigidBody()->setDamping(0, 0);
					}
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
				btWheelInfo bleftWheel = ((Robot *)*it)->getVehicle()->getWheelInfo(0);
				btWheelInfo brightWheel = ((Robot *)*it)->getVehicle()->getWheelInfo(1);
				double steering_delta = TURN_SPEED / 1.1;

				if (leftWheel.m_steering > 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering += -steering_delta;
				if (rightWheel.m_steering > 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering += -steering_delta;
				if (leftWheel.m_steering < 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering += steering_delta;
				if (rightWheel.m_steering < 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering += steering_delta;

				if (bleftWheel.m_steering > 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(0).m_steering += -steering_delta;
				if (brightWheel.m_steering > 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(1).m_steering += -steering_delta;
				if (bleftWheel.m_steering < 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(0).m_steering += steering_delta;
				if (brightWheel.m_steering < 0)
					((Robot *)*it)->getVehicle()->getWheelInfo(1).m_steering += steering_delta;

				if (leftWheel.m_steering < TURN_SPEED / 1.1 && leftWheel.m_steering > -TURN_SPEED / 1.1) ((Robot *)*it)->getVehicle()->getWheelInfo(2).m_steering = 0;
				if (bleftWheel.m_steering < TURN_SPEED / 1.1 && bleftWheel.m_steering > -TURN_SPEED / 1.1) ((Robot *)*it)->getVehicle()->getWheelInfo(0).m_steering = 0;
				if (rightWheel.m_steering < TURN_SPEED / 1.1 && rightWheel.m_steering > -TURN_SPEED / 1.1) ((Robot *)*it)->getVehicle()->getWheelInfo(3).m_steering = 0;
				if (brightWheel.m_steering < TURN_SPEED / 1.1 && brightWheel.m_steering > -TURN_SPEED / 1.1) ((Robot *)*it)->getVehicle()->getWheelInfo(1).m_steering = 0;


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
		GameObj* GO1 = (GameObj*)obj1->getUserPointer();//objCollisionPair.find(obj1)->second;
		GameObj* GO2 = (GameObj*)obj2->getUserPointer();//objCollisionPair.find(obj2)->second;

		if (GO1 == nullptr || GO2 == nullptr || GO1->getHasDeleted() || GO2->getHasDeleted()) continue;
		if ((GO1->getBelongTo() == GO2->getBelongTo())) continue;

		if (GO1->getBelongTo() != nullptr && GO2->getBelongTo() != nullptr){
			if (((Robot*)GO1->getBelongTo())->getState() != PS_ALIVE) {
				//cout <<"GO1 " << GO1->getCollisionType() << " belongs to null " << endl;
				continue;
			}
			if (((Robot*)GO2->getBelongTo())->getState() != PS_ALIVE) {
				//cout << "GO2 " << GO2->getCollisionType() << " belongs to null " << endl;
				continue;
			}
		}

		//std::cout << "Collision: GO1 Objid = " << GO1->getId() << ", type = " << GO1->getType() << ", GO2 Objid = " << GO2->getId() << ", type = " << GO2->getType() << std::endl;
		

		DamageEvent* e = new DamageEvent(GO1, GO2);
		int clientCollision = damageSystem->performDamage(GO1, GO2, e);
		if (clientCollision != CH_INVALIDCOLLISION)
		{
			applyMeleeForce(GO1, GO2);
			applyMeleeForce(GO2, GO1);
			applyBulletEffect(GO1, GO2);
			applyBulletEffect(GO2, GO1);
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
	for (i = 0; i < numPlayers; i++)
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
	if (r->getState() == PS_ALIVE)
	{
		//cout << "-----" << endl;
		//cout << "prev death:" << scoreboard->getDeaths()[r->getCID()] << endl;
		createDeathEvent(r);
		r->_deathSent = 0;
		scoreboard->incDeaths(r->getCID());
		//cout << "inc death for " << r->getCID() << endl;
		//cout << "after death:" << scoreboard->getDeaths()[r->getCID()] << endl;
		//cout << "prev takedown:" << scoreboard->getTakedowns()[r->getCID()] << endl;
		if (r->getDiedTo() != nullptr && r->getDiedTo()->getCID() != r->getCID())
		{
			scoreboard->incTakedowns(r->getDiedTo()->getCID());
			scoreboard->incGold(r->getDiedTo()->getCID(), GOLD_PER_KILL);
		}
		
		//cout << "inc takedown for " << r->getDiedTo()->getCID() << endl;
		//cout << "prev takedown:" << scoreboard->getTakedowns()[r->getCID()] << endl;
		//cout << "-----" << endl;
		vector<GameObj*> parts = r->getParts();
		vector<GameObj*>::iterator it;
		r->setId(5900000  + counter);
		counter +=10;
		for (it = parts.begin(); it != parts.end(); it++)
		{
			if (!(*it)->getHasDeleted())
			{
				breakConstraints(*it);
			}
		}
		parts.clear();
	}
}

void GameLogic::createHealthUpdateEvent(Robot* r)
{
	GEHealthUpdate* GE = new GEHealthUpdate(r->getCID(), r->getHealth(), r->getMaxHealth());
	//cout << "update health" << r->getHealth() << endl;
	gameEventList.push_back(GE);
}

void GameLogic::postDamageLogic(GameObj* g, int result, btManifoldPoint* pt)
{
	
	if (!g->getHasDeleted())
	{
		if (result == BREAK_CONSTRAINT )
		{
			//cout << "GO Break ID: " << g->getId() << endl;
			breakConstraints(g);

		}
		else if (result == DELETED)
		{
			//cout << "GO Deleted ID: " << g->getId() << endl;
			if (!g->getIsRobot()){
				//if (g->getIsRobot()) cout << "is robot deleted in postdamage GOID: " << g->getId() << endl;
				g->setImmediateDeleted();
				breakConstraints(g);
		    }
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
	std::vector<GameObj*> new_gameObj;
	std::vector<GameObj*>::iterator it;
	for (it = gameObjs.begin(); it != gameObjs.end(); it++)
	{
		if (!(*it)->getDeleted())
		{
	/*		if (((*it)->getIsRobot() == 0) && ((*it)->getCollisionType() != C_PROJECTILE) && !((*it)->getIsWheel()) && ((*it)->getConstraints()->size() == 0))
			{
				(*it)->setDeleted();
			}
			*/
			new_gameObj.push_back((*it));
		}
		else
		{
			(*it)->getRigidBody()->setUserPointer(nullptr);
			gamePhysics->getDynamicsWorld()->removeRigidBody((*it)->getRigidBody());
			delete(*it);
		}
	}
	gameObjs = new_gameObj;
}

int GameLogic::breakConstraints(GameObj* g)
{
	std::vector<Constraint*>::iterator iter;
	for (iter = g->getConstraints()->begin(); iter != g->getConstraints()->end(); iter++)
	{
		(*iter)->_joint6DOF->setEnabled(false);
	}

	g->deleteConstraints();
	
	Robot* r = (Robot*)g->getBelongTo();
	
	if (r->getState() == PS_ALIVE){
		std::vector<GameObj *> parts = r->getParts();
		std::vector<GameObj *> new_parts;
		std::vector<GameObj *>::iterator it1;

		for (it1 = parts.begin(); it1 != parts.end(); it1++)
		{
			if (!(*it1)->getHasDeleted())
			{
				new_parts.push_back((*it1));
			}
		}
		r->setParts(new_parts);
	}
	//cout << "Impulse: " << pt->getAppliedImpulse() << endl;
    btVector3 randomForce((*dist)(generator), (*dist)(generator), (*dist)(generator));
	//cout << "randomForce x y z: " << randomForce.getX() << " , " << randomForce.getY() << " , " << randomForce.getZ() << endl;
    if (randomForce.getY() == 0) {
        randomForce.setY(randomForce.getY() + 0.001);
    }
	randomForce.normalize();
	//cout << "randomForce normalized x y z: " << randomForce.getX() << " , " << randomForce.getY() << " , " << randomForce.getZ() << endl;
	g->getRigidBody()->applyCentralImpulse(randomForce * 400);

	return 0;
}

void GameLogic::createDeathEvent(Robot* r)
{

		r->nextState();
		if (r->getDiedTo() != nullptr){
			GameEvents* GE = new GERobotDeath(r->getCID(), r->getDiedTo()->getCID());
			gameEventList.push_back(GE);
		}
		else{

			GameEvents* GE = new GERobotDeath(r->getCID(), -1);
			gameEventList.push_back(GE);
		}
	
	
}

void GameLogic::animateBuilding()
{
	if (building->getY() - BUILDING_Y_DELTA > 0)
    {
	   building->setY(building->getY() - BUILDING_Y_DELTA);
	   std::vector<GameObj*>::iterator it;
	   for (it = pillars.begin(); it != pillars.end(); it++)
	   {
		   (*it)->setY((*it)->getY() - BUILDING_Y_DELTA);
		   (*it)->getRigidBody()->getWorldTransform().setOrigin(btVector3((*it)->getX(), (*it)->getY() - BUILDING_Y_DELTA, (*it)->getZ()));
	   }
	}
}


void GameLogic::addWalls()
{

	GameObj* b = new GOBox(0, FIELD_HEIGHT, 0, 0, 0, 0, 1, 0, 0.0000001, 0.0000001, 0.0000001);
	b->setBlockType(STONEHENGE);
	b->setCollisionType(C_WALLS);

	GameObj* ceiling = new GOPlane(0, FIELD_HEIGHT, 0, 0, 0, 0, 1, 0, 0, -1, 0, 1);
	GameObj* leftWall = new GOPlane(-FIELD_WIDTH / 2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1);
	GameObj* rightWall = new GOPlane(FIELD_WIDTH / 2, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 1);
	GameObj* frontWall = new GOPlane(0, 0, FIELD_WIDTH / 2, 0, 0, 0, 1, 0, 0, 0, -1, 1);
	GameObj* backWall = new GOPlane(0, 0, -FIELD_WIDTH / 2, 0, 0, 0, 1, 0, 0, 0, 1, 1);

	btQuaternion q0(0, 0, 0, 1);

	 	btQuaternion* rotQ;
	 	btQuaternion q;
	

		 	rotQ = network->convertEulerToQuaternion(0, 22.8, 0);
	 	q = q0*(*rotQ);
	 	GameObj* p1 = new GOBox(10.5, b->getY() + 10, 27.5, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 12.4, 20, 5.2);
	
		rotQ = network->convertEulerToQuaternion(0, -25, 0);
		 	q = q0*(*rotQ);
			GameObj* p2 = new GOBox(-12.01, b->getY() + 10, 27.29, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 12.4, 20, 5.2);
	
		 	rotQ = network->convertEulerToQuaternion(0, 61.4, 0);
		 	q = q0*(*rotQ);
			GameObj* p3 = new GOBox(27.41, b->getY() + 10, 11.48, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 12.4, 20, 5.2);

		 	rotQ = network->convertEulerToQuaternion(0, -77.8, 0);
		 	q = q0*(*rotQ);
			GameObj* p4 = new GOBox(27.4, b->getY() + 10, -11.35, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 12.4, 20, 5.2);

		 	rotQ = network->convertEulerToQuaternion(0, -16, 0);
		 	q = q0*(*rotQ);
			GameObj* p5 = new GOBox(11.72, b->getY() + 10, -28.16, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 12.4, 20, 5.2);
	
		 	rotQ = network->convertEulerToQuaternion(0, 30.3, 0);
			q = q0*(*rotQ);
			GameObj* p6 = new GOBox(-9.24, b->getY() + 10, -25.69, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 15.4, 20, 5.2);

		 	rotQ = network->convertEulerToQuaternion(0, 98.62, 0);
	 		q = q0*(*rotQ);
			GameObj* p7 = new GOBox(-29.39, b->getY() + 10, 10.67, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 12.4, 20, 5.2);
	
		 	rotQ = network->convertEulerToQuaternion(0, 71.049, 0);
		 	q = q0*(*rotQ);
			GameObj* p8 = new GOBox(-24.95, b->getY() + 10, -11.12, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 12.4, 20, 5.2);



			rotQ = network->convertEulerToQuaternion(0, 30.58, 0);
			q = q0*(*rotQ);
			GameObj* corner1 = new GOBox(-FIELD_WIDTH / 2, 10, -FIELD_WIDTH / 2, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 10, 20, 7);
			GameObj* corner4 = new GOBox(FIELD_WIDTH / 2, 10, FIELD_WIDTH / 2, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 10, 20, 7);

			rotQ = network->convertEulerToQuaternion(0, -16, 0);
			q = q0*(*rotQ);
			GameObj* corner2 = new GOBox(FIELD_WIDTH / 2, 10, -FIELD_WIDTH / 2, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 10, 20, 7);
			GameObj* corner3 = new GOBox(-FIELD_WIDTH / 2, 10, FIELD_WIDTH / 2, q.getX(), q.getY(), q.getZ(), q.getW(), 0, 10, 20, 7);


	ceiling->setBlockType(WALL);
	leftWall->setBlockType(WALL);
	rightWall->setBlockType(WALL);
	frontWall->setBlockType(WALL);
	backWall->setBlockType(WALL);
	p1->setBlockType(WALL);
	p2->setBlockType(WALL);
	p3->setBlockType(WALL);
	p4->setBlockType(WALL);
	p5->setBlockType(WALL);
	p6->setBlockType(WALL);
	p7->setBlockType(WALL);
	p8->setBlockType(WALL);
	corner1->setBlockType(WALL);
	corner2->setBlockType(WALL);
	corner3->setBlockType(WALL);
	corner4->setBlockType(WALL);

	ceiling->createRigidBody();
	leftWall->createRigidBody();
	rightWall->createRigidBody();
	frontWall->createRigidBody();
	backWall->createRigidBody();
	p1->createRigidBody();
	p2->createRigidBody();
	p3->createRigidBody();
	p4->createRigidBody();
	p5->createRigidBody();
	p6->createRigidBody();
	p7->createRigidBody();
	p8->createRigidBody();
	corner1->createRigidBody();
	corner2->createRigidBody();
	corner3->createRigidBody();
	corner4->createRigidBody();

	gamePhysics->getDynamicsWorld()->addRigidBody(ceiling->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(leftWall->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(rightWall->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(frontWall->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(backWall->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p1->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p2->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p3->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p4->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p5->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p6->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p7->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(p8->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(corner1->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(corner2->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(corner3->getRigidBody());
	gamePhysics->getDynamicsWorld()->addRigidBody(corner4->getRigidBody());




	gameObjs.push_back(b);
	building = b;
	pillars.push_back(p1);
	pillars.push_back(p2);
	pillars.push_back(p3);
	pillars.push_back(p4);
	pillars.push_back(p5);
	pillars.push_back(p6);
	pillars.push_back(p7);
	pillars.push_back(p8);
	//gameObjs.push_back(ceiling);
	//gameObjs.push_back(leftWall);
	//gameObjs.push_back(rightWall);
	//gameObjs.push_back(frontWall);
	//gameObjs.push_back(backWall);
	//gameObjs.push_back(p1);
	//gameObjs.push_back(p2);
	//gameObjs.push_back(p3);
	//gameObjs.push_back(p4);
	/*gameObjs.push_back(p5);
	gameObjs.push_back(p6);
	gameObjs.push_back(p7);
	gameObjs.push_back(p8);*/
}




void GameLogic::addGround()
{
	GameObj* ground = new GOPlane(0, -1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1);
	//GameObj* ground = new GOBox(0, -0.5, 0, 0, 0, 0, 1, 1, 10000000, 1, 10000000);
	ground->setBlockType(BATTLEFIELD);
	ground->createRigidBody();
	gamePhysics->getDynamicsWorld()->addRigidBody(ground->getRigidBody());
	//gameObjs.push_back(ground);
}

void GameLogic::deleteGameObj(GameObj* g)
{
	//g->deleteConstraints();//&objCollisionPair);
	
	//delete(g);
	g = nullptr;
}

int buildplayer[4] = {0};
int buildnum = 0;

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
						 //cout << "buildnum" << buildnum << endl;
						 buildList.push_back(*iter);
					 }
					break;
		    }
			default:{
						break;
			}
		}
		iter++;
	}

	objEventList.clear();
	

	if (lastTime >(countDown->getCurrentTime())/1000)
	{
		lastTime = (countDown->getCurrentTime()) / 1000;
		cout << "Timer: " << lastTime << endl;
		network->sendInitBuild(TIMER, lastTime);
	}


	if (buildnum >= numPlayers){
		//cout << "build finish" << endl;
		return TIMEUP;
	}
	else if (countDown->checkCountdown()){
		int i;
		for (i = 0; i < numPlayers;i++)
		{
			if (buildplayer[i] != 1)
			{
				network->sendBuildRequest(i);
			}
		}
		return COUNTDOWN;
	}
	return COUNTDOWN;
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

void GameLogic::createHillUpdateEvent()
{
	GEHillUpdate* ge = new GEHillUpdate(hill->getX(), hill->getZ(), hill->getRadius());
	gameEventList.push_back(ge);
}

void GameLogic::createPlayerHillUpdateEvent(int c)
{
	GEPlayerHillUpdate* ge = new GEPlayerHillUpdate(c);
	gameEventList.push_back(ge);
	//cout << " palyer in hill " << endl;
}



void GameLogic::applyMeleeForce(GameObj* GO1, GameObj* GO2){

	if (GO1->getBlockType() == Mallet && !GO2->getDeleted())
	{

		double knockback = ((MeleeWeapon*)GO1->getWeapon())->getKnockback();
		//btTransform rbTrans = GO1->getRigidBody()->getWorldTransform();
		//btVector3 boxRot = rbTrans.getBasis()[2];
		btVector3 boxRot(GO2->getX() - GO1->getX(), 1.3, GO2->getZ() - GO1->getZ());
		boxRot.normalize();
		btVector3 newforce = boxRot*knockback;
		//newforce.setY(0);
		GO2->getRigidBody()->applyCentralImpulse(newforce);
		//cout << "GO1 WEAPON: knockback " << knockback << endl;
		//cout << "GO1 WEAPON force direct: x:" << newforce.getX() << " y: " << newforce.getY() << " Z: " << newforce.getZ() << endl;

	}
	else if (GO1->getBlockType() == Mace && !GO2->getDeleted())
	{

		double knockback = ((MeleeWeapon*)GO1->getWeapon())->getKnockback();
		//btTransform rbTrans = GO1->getRigidBody()->getWorldTransform();
		//btVector3 boxRot = rbTrans.getBasis()[2];
		btVector3 boxRot(GO2->getX() - GO1->getX(), 1.2, GO2->getZ() - GO1->getZ());
		boxRot.normalize();
		btVector3 newforce = boxRot*knockback;
		//newforce.setY(0);
		GO2->getRigidBody()->applyCentralImpulse(newforce);
		Robot* r = (Robot*)GO1->getBelongTo();
		GO2->addDoT(((MeleeWeapon*)GO1->getWeapon())->getDoT(), r->getCID());
		//cout << "GO1 WEAPON: knockback " << knockback << endl;
		//cout << "GO1 WEAPON force direct: x:" << newforce.getX() << " y: " << newforce.getY() << " Z: " << newforce.getZ() << endl;

	}
	else if( GO1->getBlockType() == Needle && !GO2->getDeleted())
	{

		double knockback = ((MeleeWeapon*)GO1->getWeapon())->getKnockback();
		//btTransform rbTrans = GO1->getRigidBody()->getWorldTransform();
		//btVector3 boxRot = rbTrans.getBasis()[2];
		btVector3 boxRot(GO2->getX() - GO1->getX(), 0, GO2->getZ() - GO1->getZ());
		boxRot.normalize();
		btVector3 newforce = boxRot*knockback;
		//newforce.setY(0);
		GO2->getRigidBody()->applyCentralImpulse(newforce);
		//cout << "GO1 WEAPON: knockback " << knockback << endl;
		//cout << "GO1 WEAPON force direct: x:" << newforce.getX() << " y: " << newforce.getY() << " Z: " << newforce.getZ() << endl;
		Robot* r = (Robot*)GO1->getBelongTo();
		r->applyDamage(-((MeleeWeapon*)GO1->getWeapon())->getDamage());
	}
}

void GameLogic::updateDoTDamage()
{
	std::vector<GameObj *>::iterator it2;
	for (it2 = gameObjs.begin(); it2 != gameObjs.end(); it2++)
	{
		//if ((*it2)->getHasDeleted()) continue;
		int cid = (*it2)->applyDotDamage();
		if (cid != -1)
		{
			if ((*it2)->getIsRobot()){
				if ((*it2)->getHealth() <= 0){
					Robot* DieTo = (Robot*)clientPair.find(cid)->second;
					((Robot*)(*it2))->setDiedTo(DieTo);
					postDamageLogic(*it2, DEATH, nullptr);
				}
				dmgDealtArr[((Robot*)(*it2)->getBelongTo())->getCID()] = (Robot*)(*it2)->getBelongTo();
			}
			else{
				Robot* rb = (Robot*)(*it2)->getBelongTo();
				if ((*it2)->getHealth() <= 0){
					if (rb->getDoTFrom() == -1)
					{
						rb->addDoT((*it2)->getDoT(), cid);
					}
					else
					{
						rb->addDoT((*it2)->getDoT(), rb->getDoTFrom());
					}
					(*it2)->addDoT(-(*it2)->getDoT(), -1);
					postDamageLogic(*it2, BREAK_CONSTRAINT, nullptr);
				}

				if (rb->applyDamage((*it2)->getDoTTick()) <= 0){
					Robot* DieTo = (Robot*)clientPair.find(cid)->second;
					rb->setDiedTo(DieTo);
				}
				dmgDealtArr[rb->getCID()] = rb;
			}
		}
	}
}

void GameLogic::updateBlockEffects()
{
	int i;
	double threshold = 30;
	for (i = 0; i < numPlayers; i++)
	{
		Robot* r = (Robot*)clientPair.find(i)->second;
		if (r->getState() != PS_ALIVE) continue;
		double force = 0;
		double healing = 0;
		std::vector<GameObj *>::iterator it;
		std::vector<GameObj*> parts = r->getParts();
		for (it = parts.begin(); it != parts.end(); it++)
		{
			if ((*it)->getBlockType() == BLACKCUBE || (*it)->getBlockType() == GlowingCube || (*it)->getBlockType() == THREEBYTHREE_GLOWING || (*it)->getBlockType() == THREEBYTHREE_BLACK)
			{
				force += (*it)->getBlockForce();
			}
			else if ((*it)->getBlockType() == CrystalCube || (*it)->getBlockType() == THREEBYTHREE_CRYSTAL)
			{
				healing += (*it)->getHealing();
			}
		}
		if (healing != 0)
		{
			r->applyDamage(-healing);
			dmgDealtArr[r->getCID()] = r;
		}

		if (force != 0)
		{
			int j;
			for (j = 0; j < numPlayers; j++)
			{
				if (j != i)
				{
					Robot* opp = (Robot*)clientPair.find(j)->second;
					if (opp->getState() != PS_ALIVE) continue;
					btVector3 direction(opp->getX() - r->getX(), opp->getY() - r->getY(), opp->getZ() - r->getZ());
					double distance = direction.length();
					direction.normalize();
					if ((threshold / distance) >= 1)
					{
						opp->getRigidBody()->applyCentralImpulse(direction*force);
					}
					else
					{
						opp->getRigidBody()->applyCentralImpulse(direction*force*(threshold / distance));
					}
					
				}
			}
		}

		for (it = gameObjs.begin(); it != gameObjs.end(); it++)
		{
			if ((*it)->getHasDeleted())
			{
				btVector3 direction((*it)->getX() - r->getX(), (*it)->getY() - r->getY(), (*it)->getZ() - r->getZ());

				double distance = direction.length();
				direction.normalize();
				if ((threshold / distance) >= 1)
				{
					(*it)->getRigidBody()->applyCentralImpulse(direction*force / 20);
				}
				else
				{
					(*it)->getRigidBody()->applyCentralImpulse(direction*force / (20 * (threshold / distance)));
				}
				
			}
		}
	}
	

	
}

void GameLogic::applyBulletEffect(GameObj* GO1, GameObj* GO2)
{
	if (GO1->getBlockType() == BULLET && !GO2->getDeleted())
	{
		if (GO2->getBelongTo() != nullptr)
		{
			Robot* r = (Robot*)GO2->getBelongTo();
			btRaycastVehicle* v = r->getVehicle();
			r->getRigidBody()->setAngularVelocity(r->getRigidBody()->getAngularVelocity()*0.4);
			r->getRigidBody()->setLinearVelocity(r->getRigidBody()->getLinearVelocity()*0.4);
			v->applyEngineForce(0, 0);
			v->applyEngineForce(0, 1);
			v->applyEngineForce(0, 2);
			v->applyEngineForce(0, 3);
			r->applySlow(GO1->getBlockSlow());
		}
	}
}

void GameLogic::createCrown()
{
	crown = new GOBox(FIELD_WIDTH / 2, FIELD_HEIGHT/4, FIELD_WIDTH / 2, 0, 0, 0, 1, 0.001, 0.01, 0.01, 0.01);
	crown->setBlockType(WoodenCube);
	crown->setMass(0.001);
	crown->setCollisionType(C_INVALID);
	gameObjs.push_back(crown);
}

void GameLogic::animateCrown()
{
	if (numPlayers == 1)
	{
		crown->setBelongTo(clientPair.find(0)->second);
	}
	else
	{

		double kdr[4];
		for (int i = 0; i < numPlayers; i++)
		{
			kdr[i] = (double)scoreboard->getTakedowns()[i] / (double)scoreboard->getDeaths()[i];
		}

		int cid = -1;
		double highestKDR = -1;
		for (int i = 0; i < numPlayers; i++)
		{
			if (kdr[i] > highestKDR)
			{
				highestKDR = kdr[i];
				cid = i;
			}
		}

		for (int i = 0; i < numPlayers; i++)
		{
			if (kdr[i] == highestKDR && cid != i)
			{
				cid = -1;
			}
		}

		if (cid == -1)
		{
			crown->setBelongTo(nullptr);
		}
		else
		{
			crown->setBelongTo(clientPair.find(cid)->second);
		}
	}

	if (crown->getBelongTo() == nullptr)
	{
		crown->setX(FIELD_WIDTH/2);
		crown->setY(FIELD_HEIGHT/4);
		crown->setZ(FIELD_WIDTH/2);
	}
	else
	{
		crown->setX(crown->getBelongTo()->getX());
		crown->setY(crown->getBelongTo()->getY() + 4);
		crown->setZ(crown->getBelongTo()->getZ());
	}

	if (crownYoffset < -CROWN_Y_THRESHOLD)
	{
		crownYdelta = CROWN_Y_DELTA;
	}
	if (crownYoffset > CROWN_Y_THRESHOLD)
	{
		crownYdelta = -CROWN_Y_DELTA;
	}

	if (crownXoffset < -CROWN_X_THRESHOLD)
	{
		crownXdelta = CROWN_XZ_DELTA;
	}
	if (crownXoffset > CROWN_X_THRESHOLD)
	{
		crownXdelta = -CROWN_XZ_DELTA;
	}

	if (crownZoffset < -CROWN_Z_THRESHOLD)
	{
		crownZdelta = CROWN_XZ_DELTA;
	}
	if (crownZoffset > CROWN_Z_THRESHOLD)
	{
		crownZdelta = -CROWN_XZ_DELTA;
	}
	crownXoffset += crownXdelta;
	crownYoffset += crownYdelta;
	crownZoffset += crownZdelta;

	crown->setX(crown->getX() + crownXoffset);
	crown->setY(crown->getY() + crownYoffset);
	crown->setZ(crown->getZ() + crownZoffset);

}