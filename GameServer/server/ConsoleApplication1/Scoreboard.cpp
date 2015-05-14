#include "Scoreboard.h"


Scoreboard::Scoreboard()
{
	int i;
	for (i = 0; i < 4; i++){
		takedowns[i] = 0;
		deaths[i] = 0;
		gold[i] = 0;
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
	gold[cid] += amt;
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