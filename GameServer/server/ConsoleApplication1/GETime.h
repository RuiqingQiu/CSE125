#pragma once
#include "GameEvents.h"
class GETime : public GameEvents
{


public:
	GETime(int);
	~GETime();
	//time in seconds
	int time;

	void to_string(std::string&) override;
};

