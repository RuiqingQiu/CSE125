#pragma once
#include "GameEvents.h"
class GEHealthUpdate : public GameEvents
{
public:
	GEHealthUpdate(int, double, double);
	~GEHealthUpdate();

	int cid;
	double health;
	double maxHealth;

	void to_string(std::string&) override;
};

