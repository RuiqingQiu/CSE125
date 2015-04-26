#pragma once
#include "GameEvents.h"
class GERobotDeath: public GameEvents
{


public:
	GERobotDeath();
	~GERobotDeath();

	void to_string(char*) override;
};

