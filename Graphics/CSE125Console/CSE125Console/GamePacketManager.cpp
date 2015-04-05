#include "stdafx.h"
#include "GamePacketManager.h"


GamePacketManager::GamePacketManager()
{
	client = new ClientGame();
	client->connectToServer("127.1.1.1");
}


GamePacketManager::~GamePacketManager()
{
}

GameInfoPacket* GamePacketManager::tryGetGameInfo(){
	char* data = client->update();

	Packet packet;
	packet.deserialize(&(data[0]));

	return nullptr;
	switch (packet.packet_type) {

		case ACTION_EVENT:

			printf("client received action event packet from server\n");


			//convert packet to gameinfo
			//sendActionPackets();

			break;

		default:

			printf("error in packet types\n");

			break;
		}
	
}

