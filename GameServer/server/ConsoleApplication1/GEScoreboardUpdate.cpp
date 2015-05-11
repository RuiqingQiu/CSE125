#include "GEScoreboardUpdate.h"


GEScoreboardUpdate::GEScoreboardUpdate(int t[4], int d[4], int g[4]) :GameEvents(3)
{
	takedowns = t;
	deaths = d;
	gold = g;
}


GEScoreboardUpdate::~GEScoreboardUpdate()
{
}

void GEScoreboardUpdate::to_string(std::string &s)
{
	s += std::to_string(_event_type);
	s += " ";
	int i;
	for (i = 0; i < 4; i++)
	{
		s += std::to_string(takedowns[i]);
		s += " ";
		s += std::to_string(deaths[i]);
		s += " ";
		s += std::to_string(gold[i]);
		if (i!=3)
		{ 
			s += " ";
		}	
	}

}