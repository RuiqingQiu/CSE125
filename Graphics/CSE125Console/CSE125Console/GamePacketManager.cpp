#include "stdafx.h"
#include "GamePacketManager.h"
#include <vector>

GamePacketManager::GamePacketManager()
{
	client = new ClientGame();
}


GamePacketManager::~GamePacketManager()
{
}

bool GamePacketManager::ConnectToServer(char* ipaddress)
{
	return client->connectToServer(ipaddress);
}


GameInfoPacket* GamePacketManager::tryGetGameInfo(){
	//char* data = client->update();
	GameInfoPacket* result = client->update();
	return result;
}

bool GamePacketManager::SendMoveToRight(int id)
{
	CPacket cp;
	cp.packet_type = MOVE_RIGHT;
	string tmp = to_string(id) + "\n\0";
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}
bool GamePacketManager::SendMoveToLeft(int id)
{
	CPacket cp;
	cp.packet_type = MOVE_LEFT;
	string tmp = to_string(id) + "\n\0";
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}
bool GamePacketManager::SendMoveToTop(int id)
{
	CPacket cp;
	cp.packet_type = MOVE_UP;
	string tmp = to_string(id) + "\n\0";
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}
bool GamePacketManager::SendMoveToDown(int id)
{
	CPacket cp;
	cp.packet_type = MOVE_DOWN;
	string tmp = to_string(id) + "\n\0";
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}
bool GamePacketManager::SendMoveToForward(int id)
{
	CPacket cp;
	cp.packet_type = MOVE_FORWARD;
	string tmp = to_string(id) + "\n\0";
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}
bool GamePacketManager::SendMoveToBackward(int id)
{
	CPacket cp;
	cp.packet_type = MOVE_BACKWARD;
	string tmp = to_string(id) + "\n\0";
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}


