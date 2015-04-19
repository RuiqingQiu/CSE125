
/* GameLogic.cpp */
#include "GameLogic.h"
GameLogic::GameLogic()
{
	network = new Network();
	gamePhysics = new GamePhysics();
	countDown = new TimeFrame();
}

GameLogic::~GameLogic()
{
	delete network;
	delete gamePhysics;
	delete countDown;

}

unsigned int GameLogic::waitToConnect()
{
	int cid; 
	cid = network->waitForConnections();


    if (cid == -1) return WAIT;
	//GameObj* gameObj = new GOBox(0, 5, 0, 0, 0, 0, 1, 50, 7, 1, 7);
	//ameObj->setBlockType(CUBE);
	//asd++;
	GameObj* robot = new Robot(cid, "testname");
	robot->setType(CUBE);
	this->pushGameObj(robot);
	clientPair.insert(std::pair<int, GameObj*>(cid, robot));

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
	//			this->pushGameObj(gameObj1);
	//			clientPair.insert(std::pair<int, GameObj*>(cid + p, gameObj1));
	//			cout << "p:" << p << endl;
	//			p++;
	//		}
	//	}
	//}




	//GameObj* gameObj1 = new GOBox(10, 5, 0, 0, 0, 0, 1, 1, 1, 1, 1);
	//gameObj1->setBlockType(CUBE);
	//asd++;
	//this->pushGameObj(gameObj1);
	//clientPair.insert(std::pair<int, GameObj*>(cid + 1, gameObj1));
	//int i, j;
	/*for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 20; j++)
		{
			GameObj* gameObj2 = new GOBox(i*1-10, j*1, -5, 0, 0, 0, 1, 1, 1, 1, 1);
			gameObj2->setBlockType(CUBE);
			this->pushGameObj(gameObj2);
		}
	}*/


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
	addWalls();

	gamePhysics->initWorld(&(this->getGameObjs()));

	//int i,j,k;

	//for (i = 0; i < 17; i++)
	//{
	//	clientPair.find(i)->second->getRigidBody()->setAngularFactor(0.3);
	//	for (j = i + 1; j < 17; j++)
	//	{
	//		for (k = 0; k < 7; k++)
	//		{
	//			Constraint* b = new Constraint();
	//			b->addConstraint(clientPair.find(i)->second, clientPair.find(j)->second);
	//			gamePhysics->getDynamicsWorld()->addConstraint(b->joint6DOF, true);
	//		}
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
	network->receiveFromClients(&objEventList);
	

	//if (countDown->checkCountdown()) return TIMEUP;
	

	//do gamelogic for all ObjectEvents
	prePhyLogic();
	
	//pass the time into physics
	
	unsigned int time = countDown->getElapsedTime();

	countDown->startClock();

	//do physics

	
	gamePhysics->getDynamicsWorld()->stepSimulation(btScalar(1/66.0),4);

	gamePhysics->stepSimulation(&this->getGameObjs());

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
		gamePhysics->createPhysicsEvent(type, gObj);
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
			if (((Robot *)*it)->getVehicle()->getWheelInfo(0).m_steering > 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(0).m_steering += -TURN_SPEED / 2;
			if (((Robot *)*it)->getVehicle()->getWheelInfo(1).m_steering > 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(1).m_steering += -TURN_SPEED / 2;
			if (((Robot *)*it)->getVehicle()->getWheelInfo(0).m_steering < 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(0).m_steering += TURN_SPEED / 2;
			if (((Robot *)*it)->getVehicle()->getWheelInfo(1).m_steering < 0)
				((Robot *)*it)->getVehicle()->getWheelInfo(1).m_steering += TURN_SPEED / 2;
		}
	}

	objEventList.clear();
	//cout << "objEventList size == " << objEventList.size() << endl;
}



std::vector<GameObj*> GameLogic::getGameObjs()
{
	return gameObjs;
}

void GameLogic::pushGameObj(GameObj* obj)
{
	gameObjs.push_back(obj);
}


void GameLogic::addWalls()
{
	GameObj* ceiling = new GOPlane(0, FIELD_HEIGHT, 0, 0, 0, 0, 1, 0, 0, -1, 0, 1);
	GameObj* leftWall = new GOPlane(-FIELD_WIDTH / 2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1);
	GameObj* rightWall = new GOPlane(FIELD_WIDTH / 2, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 1);
	GameObj* frontWall = new GOPlane(0, 0, FIELD_WIDTH / 2, 0, 0, 0, 1, 0, 0, 0, -1, 1);
	GameObj* backWall = new GOPlane(0, 0, -FIELD_WIDTH / 2, 0, 0, 0, 1, 0, 0, 0, 1, 1);

	ceiling->setType(WALL);
	leftWall->setType(WALL);
	rightWall->setType(WALL);
	frontWall->setType(WALL);
	backWall->setType(WALL);

	pushGameObj(ceiling);
	pushGameObj(leftWall);
	pushGameObj(rightWall);
	pushGameObj(frontWall);
	pushGameObj(backWall);
}
void GameLogic::addGround()
{
	GameObj* ground = new GOPlane(0, -1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1);
	ground->setType(WALL);
	pushGameObj(ground);
}

