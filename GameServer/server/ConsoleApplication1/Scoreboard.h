#pragma once
#define INTIAL_GOLD 100
class Scoreboard
{
private:
	int takedowns[4];
	int deaths[4];
	int gold[4];
	int hasChanged = 0;
public:
	Scoreboard();
	~Scoreboard();

	void incTakedowns(int);
	void incDeaths(int);
	void incGold(int, int);
	void setGold(int cid, int amt);
	int getHasChanged();
	int* getTakedowns();
	int* getDeaths();
	int* getGold();
};


