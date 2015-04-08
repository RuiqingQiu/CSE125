#pragma once
#include "stdafx.h"
#include "ClientGame.h"
#include "GameInfoPacket.h"
#include <string>
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"

class GamePacketManager
{
public:
	ClientGame* client;
	GamePacketManager();
	~GamePacketManager();
	bool ConnectToServer(char* ipaddress);
	bool SendMoveToRight(int id);
	bool SendMoveToLeft(int id);
	bool SendMoveToTop(int id);
	bool SendMoveToDown(int id);
	bool SendMoveToForward(int id);
	bool SendMoveToBackward(int id);

	GameInfoPacket* tryGetGameInfo();
	
};

