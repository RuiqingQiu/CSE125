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

	GameInfoPacket* tryGetGameInfo();
	
};

