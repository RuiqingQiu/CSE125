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
bool GamePacketManager::SendShootEvent(int id){
	CPacket cp;
	cp.packet_type = SHOOT;
	string tmp = to_string(id) + "\n\0";
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}

bool GamePacketManager::SendRobotBuild(int id, std::vector<GeoNode *> nodeList)
{
	CPacket cp;
	cp.packet_type = BUILD_ROBOT;
	string tmp = "";
	for (int i = 0; i < nodeList.size(); i++) {
		//clientID objectID x y z EullerX EullerY EullerZ block_type\n (0 for 1x1 nontexture cube) (1 for nontexture battlefield) (2 for nontexture wall) (3 for nontexture 3x3 cube) \n
		tmp += to_string(id) + " ";
		tmp += to_string(nodeList[i]->identifier) + " ";
		tmp += to_string(nodeList[i]->localTransform.position.x) + " ";
		tmp += to_string(nodeList[i]->localTransform.position.y) + " ";
		tmp += to_string(nodeList[i]->localTransform.position.z) + " ";
		tmp += to_string(nodeList[i]->localTransform.rotation.x) + " ";
		tmp += to_string(nodeList[i]->localTransform.rotation.y) + " ";
		tmp += to_string(nodeList[i]->localTransform.rotation.z) + " ";

		tmp += to_string(nodeList[i]->textureType) + " ";

		tmp += to_string(nodeList[i]->below_id) + " ";
		tmp += to_string(nodeList[i]->left_id) + " ";
		tmp += to_string(nodeList[i]->right_id) + " ";
		tmp += to_string(nodeList[i]->front_id) + " ";
		tmp += to_string(nodeList[i]->back_id) + " ";
		
		tmp += "\n\0";
	}
	strncpy_s(cp.data, tmp.c_str(), sizeof(cp.data));
	return client->sendPacket(cp);
}


