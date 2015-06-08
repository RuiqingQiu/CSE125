#pragma once
#include "GameEvents.h"
class GEPlayerHillUpdate:public GameEvents
{
private:
	int cid;
public:
	GEPlayerHillUpdate(int);
	~GEPlayerHillUpdate();
	void to_string(std::string&) override;
};

