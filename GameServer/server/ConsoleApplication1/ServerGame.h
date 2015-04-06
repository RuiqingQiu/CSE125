#pragma once
#include "ServerNetwork.h"
#include "NetworkData.h"
#include <iostream>
#include <vector>
#include "GameObj.h"
#include <string>
#include <iostream>
#include <map>

class ServerGame
{

	std::vector<GameObj*> gameObjs;
	std::map<unsigned int, GameObj *> clientPair;

public:

	ServerGame(void);
	~ServerGame(void);

	void update();

	void receiveFromClients();

	void sendActionPackets();

	void pushGameObj(GameObj*);

	std::vector<GameObj*> getGameObjs();

	void sendClientConfirmationPacket(char* clientName, unsigned int client_ID);

	unsigned int ServerGame::waitForConnections();


	string convertData();
private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	// The ServerNetwork object 
	ServerNetwork* network;


	// data buffer
	char network_data[MAX_PACKET_SIZE];
};