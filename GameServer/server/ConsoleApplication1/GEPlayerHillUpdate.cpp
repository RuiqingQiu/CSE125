#include "GEPlayerHillUpdate.h"


GEPlayerHillUpdate::GEPlayerHillUpdate(int c) :GameEvents(9)
{
	cid = c;
}


GEPlayerHillUpdate::~GEPlayerHillUpdate()
{
}


void GEPlayerHillUpdate::to_string(std::string &s)
{
	s += std::to_string(_event_type);
	s += " ";
	s += std::to_string(cid);
}