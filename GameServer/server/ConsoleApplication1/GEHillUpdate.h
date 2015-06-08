#pragma once

#include "GameEvents.h"
#include <iostream>
class GEHillUpdate : public GameEvents
{
private:
	int x;
	int z;
	int r;

public:
	GEHillUpdate(int x, int z, int r);
	~GEHillUpdate();
	void to_string(std::string&) override;
};

