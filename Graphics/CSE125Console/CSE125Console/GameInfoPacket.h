#pragma once
#include "stdafx.h"
#include <vector>
#include "PlayerInfo.h"
using namespace std;
class GameInfoPacket
{
public:
	vector<PlayerInfo*> player_infos;
	PlayerInfo* get_player_info(int id);
	GameInfoPacket();
	~GameInfoPacket();
};

