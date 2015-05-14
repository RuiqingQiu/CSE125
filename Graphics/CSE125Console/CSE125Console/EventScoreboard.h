#pragma once
#include "EventInfo.h"

class EventScoreboard :
	public EventInfo
{
public:
	int playerid [4];
	int takedowns[4];
	int gold[4];
	int deaths[4];

	EventScoreboard();
	~EventScoreboard();
};

