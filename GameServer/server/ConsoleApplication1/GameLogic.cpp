
/* GameLogic.cpp */
#include "GameLogic.h"
GameLogic::GameLogic()
{
	network = new Network();
	gamePhysics = new GamePhysics();

}

GameLogic::~GameLogic()
{
	delete network;
	delete gamePhysics;
}

unsigned int GameLogic::waitToConnect()
{
	unsigned int cid; 
	cid = network->waitForConnections();
	if (cid == -1) return WAIT;
	GameObj * clientOb = new GameObj(0, 0, -5);
	this->pushGameObj(clientOb);
	clientPair.insert(std::pair<unsigned int, GameObj*>(cid, clientOb));
	//elist->push_back(new Events(0));
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
			return ADDCLIENT;
		}
	}
	return WAIT;

}


void GameLogic::pushGameObj(GameObj*){};
std::vector<GameObj*> GameLogic::getGameObjs(){ return gameObjs; };