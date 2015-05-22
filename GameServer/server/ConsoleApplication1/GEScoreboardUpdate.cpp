#include "GEScoreboardUpdate.h"
#include <iostream>

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
	std::string ss = "";
	for (i = 0; i < 4; i++)
	{
		s += std::to_string(i);
		s += " ";
		s += std::to_string(takedowns[i]);
		s += " ";
		s += std::to_string(deaths[i]);
		s += " ";
		s += std::to_string(gold[i]);
		if (i==3)
		{ 
			s += "\n";
		}
		else s += " ";


		ss += std::to_string(i);
		ss += " ";
		ss += std::to_string(takedowns[i]);
		ss += " ";
		ss += std::to_string(deaths[i]);
		ss += " ";
		ss += std::to_string(gold[i]);
		if (i == 3)
		{
			ss += "\n";
		}
		else ss += " ";
		
	}
	std::cout << "scoreboard is: " << ss << std::endl;


}