#pragma once
#include "GameEvents.h"
class GERobotDeath: public GameEvents
{


public:
	GERobotDeath(int, int);
	~GERobotDeath();
	int cid;
	int kcid;

	void to_string(std::string&) override;
};

