#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"
#include <string>
#include "GameInfoPacket.h"
#include <stdio.h>
#include "PacketDecoder.h"
class ClientGame
{
public:
	ClientGame(void);
	~ClientGame(void);

	ClientNetwork* network;

	void sendActionPackets();

    char network_data[MAX_PACKET_SIZE];

	GameInfoPacket* update();

	bool connectToServer(char* ipaddress);

	bool sendPacket(CPacket p);
};

