#pragma once
#include "GameEvents.h"
class GEScoreboardUpdate : public GameEvents
{
private:
	int* takedowns;
	int* deaths;
	int* gold;
public:
	GEScoreboardUpdate(int takedowns[], int deaths[], int gold[]);

	~GEScoreboardUpdate();

	void to_string(std::string&) override;
};

