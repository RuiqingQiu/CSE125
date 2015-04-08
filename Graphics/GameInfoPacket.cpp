#include "stdafx.h"
#include "GameInfoPacket.h"

PlayerInfo* GameInfoPacket::get_player_info(int id){
	for each (PlayerInfo* p in player_infos){
		if (p->id == id){
			return p;
		}
	}
	//If not found, return nullptr
	return nullptr;
}

GameInfoPacket::GameInfoPacket()
{
}


GameInfoPacket::~GameInfoPacket()
{
}
