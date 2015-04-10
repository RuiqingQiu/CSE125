
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

	// USE CID INSTEAD OF OBJ
	GameObj* gameObj = new GOBox(asd * 10, asd * 100, -5, 0, 0, 0, 1, 1, 1, 1, 1);
	asd++;
	this->pushGameObj(gameObj);
	clientPair.insert(std::pair<int, GameObj*>(0, gameObj));
	GameObj* gameObj1 = new GOBox(asd * 10, asd * 100, -5, 0, 0, 0, 1, 1, 1, 1, 1);
	this->pushGameObj(gameObj1);
	clientPair.insert(std::pair<int, GameObj*>(1, gameObj1));
	GameObj* gameObj2 = new GOBox(asd * 10, asd * 100, -5, 0, 0, 0, 1, 1, 1, 1, 1);
	this->pushGameObj(gameObj);
	clientPair.insert(std::pair<int, GameObj*>(2, gameObj2));
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

	//after phy logic all events 
	gamePhysics->getDynamicsWorld()->stepSimulation(1/33.0);

	std::vector<GameObj*> gameObj = this->getGameObjs();
	std::vector<GameObj*>::iterator it;
	for (it = gameObj.begin(); it != gameObj.end(); ++it)
	{
		btTransform trans;
		(*it)->getRigidBody()->getMotionState()->getWorldTransform(trans);
		std::cout << "BOX WITH ID:  " << (*it)->getId() <<", HEIGHT: " << trans.getOrigin().getY() << std::endl;
		(*it)->setY(trans.getOrigin().getY());
	}
	
	

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
		switch (type) {
		case MOVE_LEFT: {

							printf("Server in MOVE_LEFT prephysics\n");
							std::map<int, GameObj *>::iterator it;
							it = clientPair.find(cid);
							if (it == clientPair.end()) cout << "not found\n" << endl;
							GameObj*  cob = it->second;
							cob->setX(cob->getX() - oneStep);
							cout << cob->getX() << endl;
							break;
		}
		case MOVE_RIGHT: {
							 printf("Server in MOVE_RIGHT prephysics\n");
							 std::map< int, GameObj *>::iterator it;
							 it = clientPair.find(cid);
							 GameObj*  cob = it->second;
							 cob->setX(cob->getX() + oneStep);
							 cout << cob->getX() << endl;
							 break;
		}
		case MOVE_BACKWARD: {
								printf("Server in MOVE_BACKWARD prephysics\n");
								std::map< int, GameObj *>::iterator it;
								it = clientPair.find(cid);
								GameObj*  cob = it->second;
								cob->setZ(cob->getZ() + oneStep);
								cout << cob->getX() << endl;
								break;
		}
		case MOVE_FORWARD: {

							   std::map<int, GameObj *>::iterator it;
							   it = clientPair.find(cid);
							   GameObj*  cob = it->second;
							   cob->setZ(cob->getZ() - oneStep);
							   cout << cob->getX() << endl;
							   break;
		}
		case MOVE_UP: {

						  std::map<int, GameObj *>::iterator it;
						  it = clientPair.find(cid);
						  GameObj*  cob = it->second;
						  cob->setY(cob->getY() + oneStep);
						  cout << cob->getX() << endl;
						  break;
		}

		case MOVE_DOWN: {
							std::map<int, GameObj *>::iterator it;
							it = clientPair.find(cid);
							GameObj*  cob = it->second;
							cob->setY(cob->getY() - oneStep);
							cout << cob->getX() << endl;
							break;
		}


		default:{
					printf("error in packet types\n");
					break;
		}
		}

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


