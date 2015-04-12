
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
	GameObj* gameObj = new GOBox(10, 100, -5, 0, 0, 0, 1, 1, 1, 1, 1);
	gameObj->setBlockType(CUBE);
	asd++;
	this->pushGameObj(gameObj);
	clientPair.insert(std::pair<int, GameObj*>(cid, gameObj));
	//GameObj* gameObj1 = new GOBox(10, asd * 15, -5, 0, 0, 0, 1, 1, 1, 1, 1);
	//gameObj1->setBlockType(WHEEL);
	//asd++;
	//this->pushGameObj(gameObj1);
	//clientPair.insert(std::pair<int, GameObj*>(cid + 1, gameObj1));
	//GameObj* gameObj2 = new GOBox(10, asd * 15, -5, 0, 0, 0, 1, 1, 1, 1, 1);
	//gameObj2->setBlockType(NEEDLE);
	//this->pushGameObj(gameObj2);
	//clientPair.insert(std::pair<int, GameObj*>(cid + 2, gameObj2));

	network->receiveFromClients(&elist);

//	if (elist == nullptr) return WAIT;
	std::vector<Events *>::iterator iter;

	for (iter = elist.begin(); iter != elist.end(); iter++)
	{
		unsigned int type = (*iter)->getEvent();
		switch (type) {

		case INIT_CONNECTION:
			string name = (*iter)->getName();
			(*iter)->setCid(cid);
			//cout << name << endl;
			network->sendClientConfirmationPacket(name.c_str(), cid);
			elist.erase(iter);
			return ADDCLIENT;
		}
		elist.erase(iter);
		//cout << "wait to Connect elist size = "<< elist.size() << endl;
	}
	return WAIT;

}


// will be called in build function when the build mode ends
void GameLogic::gameStart(){
	countDown->startCountdown(300);
	countDown->startClock();
	//Events * e = new Events(MOVE_BACKWARD);
	//e->setCid(0);
	//elist.push_back(e);
	gamePhysics->initWorld(&(this->getGameObjs()));
}


unsigned int GameLogic::gameLoop (){
	network->receiveFromClients(&elist);
	

	//if (countDown->checkCountdown()) return TIMEUP;
	
	//do gamelogic for all events
	prePhyLogic();
	
	//pass the time into physics
	
	unsigned int time = countDown->getElapsedTime();

	countDown->startClock();

	//do physics

	
	gamePhysics->getDynamicsWorld()->stepSimulation(1/33.0);

	gamePhysics->stepSimulation(&this->getGameObjs());

	//after phy logic all events 
	
	network->sendActionPackets(&gameObjs);
	return COUNTDOWN;
	//send back 

	
	
}



void GameLogic::prePhyLogic(){
	std::vector<Events *>::iterator iter;
	iter = elist.begin();
	while (iter != elist.end()) 
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

	elist.clear();
	//cout << "elist size == " << elist.size() << endl;
}



std::vector<GameObj*> GameLogic::getGameObjs()
{
	return gameObjs;
}

void GameLogic::pushGameObj(GameObj* obj)
{
	gameObjs.push_back(obj);
}


