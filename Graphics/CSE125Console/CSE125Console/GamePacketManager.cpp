#include "stdafx.h"
#include "GamePacketManager.h"
#include <vector>

GamePacketManager::GamePacketManager()
{
	client = new ClientGame();
	client->connectToServer("128.54.70.27");
}


GamePacketManager::~GamePacketManager()
{
}

unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

GameInfoPacket* GamePacketManager::tryGetGameInfo(){
	//char* data = client->update();
	string result = client->update();
	if (result == ""){
		return nullptr;
	}
	//Process the result
	else{
		std::vector<std::string> v;
		split(result, v, ' ');
		GameInfoPacket* g = new GameInfoPacket();
		PlayerInfo* p = new PlayerInfo();
		p->id = stof(v[0]);
		p->x = stof(v[1]);
		p->y = stof(v[2]);
		p->z = stof(v[3]);
		g->player_infos.push_back(p);
		return g;
	}
}

