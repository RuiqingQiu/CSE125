#include "GEHealthUpdate.h"
#include <iostream>


GEHealthUpdate::GEHealthUpdate(int c, double h, double mH)
	:GameEvents(4)
{
	cid = c;
	health = h;
	maxHealth = mH;
}


GEHealthUpdate::~GEHealthUpdate()
{
}

void GEHealthUpdate::to_string(std::string &s)
{
	s += std::to_string(_event_type);
	s += " ";
	s += std::to_string(cid);
	s += " ";
	s += std::to_string(health);
	s += " ";
	s += std::to_string(maxHealth);
	std::cout << "health" << health << "  max :" << maxHealth << std::endl;
}