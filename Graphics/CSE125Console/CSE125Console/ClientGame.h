#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"
#include <string>

class ClientGame
{
public:
	ClientGame(void);
	~ClientGame(void);

	ClientNetwork* network;

	void sendActionPackets();

    char network_data[MAX_PACKET_SIZE];

	std::string  update();

	bool connectToServer(char* ipaddress);
};

