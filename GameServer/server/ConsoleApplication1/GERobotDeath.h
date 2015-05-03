#pragma once
#include "GameEvents.h"
class GERobotDeath: public GameEvents
{


public:
	GERobotDeath(int);
	~GERobotDeath();
	int cid;

	void to_string(std::string&) override;
};

