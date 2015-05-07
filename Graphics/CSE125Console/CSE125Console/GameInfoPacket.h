#pragma once
#include "stdafx.h"
#include <vector>
#include "PlayerInfo.h"
#include "EventInfo.h"
using namespace std;
class GameInfoPacket
{
public:
	vector<PlayerInfo*> player_infos;

	vector<EventInfo*> event_infos;

	PlayerInfo* get_player_info(int id);
	unsigned int packet_types;
	GameInfoPacket();
	~GameInfoPacket();
};

