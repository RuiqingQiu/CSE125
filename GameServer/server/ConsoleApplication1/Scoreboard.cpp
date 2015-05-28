#include "Scoreboard.h"
#include <iostream>

Scoreboard::Scoreboard()
{
	int i;
	for (i = 0; i < 4; i++){
		takedowns[i] = 0;
		deaths[i] = 0;
		gold[i] = 40;
	}

}


Scoreboard::~Scoreboard()
{
}

void Scoreboard::incTakedowns(int cid)
{
	takedowns[cid]++;
	hasChanged=1;
}
void Scoreboard::incDeaths(int cid)
{
	deaths[cid]++;
	hasChanged = 1;
}
void Scoreboard::incGold(int cid, int amt)
{
	//std::cout << "old gold: " << gold[cid] << ", new gold: " << gold[cid] + amt << std::endl;
	gold[cid] += amt;
	hasChanged = 1;
}
void Scoreboard::setGold(int cid, int amt)
{
	//std::cout << "old gold: " << gold[cid] << ", new gold: " << amt << std::endl;
	gold[cid] = amt;
	hasChanged = 1;
}

int* Scoreboard::getTakedowns()
{
	return takedowns;
}
int* Scoreboard::getDeaths()
{
	return deaths;
}
int* Scoreboard::getGold()
{
	return gold;
}

int Scoreboard::getHasChanged()
{
	if (hasChanged)
	{
		hasChanged = 0;
		return 1;
	}
	return 0;
}