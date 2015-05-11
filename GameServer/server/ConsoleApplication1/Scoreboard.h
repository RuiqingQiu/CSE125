#pragma once
#define INTIAL_GOLD 100
class Scoreboard
{
private:
	int takedowns[4] = { 0 };
	int deaths[4] = { 0 };
	int gold[4] = { 100 };
	int hasChanged = 0;
public:
	Scoreboard();
	~Scoreboard();

	void incTakedowns(int);
	void incDeaths(int);
	void incGold(int, int);

	int getHasChanged();
	int* getTakedowns();
	int* getDeaths();
	int* getGold();
};


