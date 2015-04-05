#pragma once
#include "ServerNetwork.h"
#include "NetworkData.h"
#include <iostream>
#include <vector>
#include "GameObj.h"
#include <string>

class ServerGame
{

	std::vector<GameObj> gameObjs;

public:

	ServerGame(void);
	~ServerGame(void);

	void update();

	void receiveFromClients();

	void sendActionPackets();

	void pushGameObj(GameObj);

	std::vector<GameObj> getGameObjs();


	string convertData(char*);
private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	// The ServerNetwork object 
	ServerNetwork* network;


	// data buffer
	char network_data[MAX_PACKET_SIZE];
};