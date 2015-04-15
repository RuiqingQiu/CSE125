
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
	GameObj* gameObj = new GOBox(10, 5, 0, 0, 0, 0, 1, 1, 1, 1, 1);
	gameObj->setBlockType(CUBE);
	asd++;
	this->pushGameObj(gameObj);
	clientPair.insert(std::pair<int, GameObj*>(cid, gameObj));

	//GameObj* gameObj1 = new GOBox(10, 5, 0, 0, 0, 0, 1, 1, 1, 1, 1);
	//gameObj1->setBlockType(CUBE);
	//asd++;
	//this->pushGameObj(gameObj1);
	//clientPair.insert(std::pair<int, GameObj*>(cid + 1, gameObj1));
	int i, j;
	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 10; j++)
		{
			GameObj* gameObj2 = new GOBox(i*1-10, j*1, -5, 0, 0, 0, 1, 1, 1, 1, 1);
			gameObj2->setBlockType(CUBE);
			this->pushGameObj(gameObj2);
		}
	}


	network->receiveFromClients(&objEventList);

//	if (objEventList == nullptr) return WAIT;
	std::vector<ObjectEvents *>::iterator iter;

	for (iter = objEventList.begin(); iter != objEventList.end(); iter++)
	{
		unsigned int type = (*iter)->getEvent();
		switch (type) {

		case INIT_CONNECTION:
			string name = (*iter)->getName();
			(*iter)->setCid(cid);
			//cout << name << endl;
			network->sendClientConfirmationPacket(name.c_str(), cid);
			objEventList.erase(iter);
			return ADDCLIENT;
		}
		objEventList.erase(iter);
		//cout << "wait to Connect objEventList size = "<< objEventList.size() << endl;
	}
	return WAIT;

}


// will be called in build function when the build mode ends
void GameLogic::gameStart(){
	countDown->startCountdown(300);
	countDown->startClock();
	//ObjectEvents * e = new ObjectEvents(MOVE_LEFT);
	//e->setCid(0);
	//objEventList.push_back(e);
	//ObjectEvents * e1 = new ObjectEvents(MOVE_FORWARD);
	//e1->setCid(0);
	//objEventList.push_back(e1);
	gamePhysics->initWorld(&(this->getGameObjs()));
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

	
	gamePhysics->getDynamicsWorld()->stepSimulation(btScalar(1/33.0));

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
		GameObj*  cob = it->second;
		btRigidBody *rb = cob->getRigidBody();
		gamePhysics->createPhysicsEvent(type, rb);
		iter++;
	
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


