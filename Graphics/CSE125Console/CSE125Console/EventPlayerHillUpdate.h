#pragma once
#include "EventInfo.h"
class EventPlayerHillUpdate :
	public EventInfo
{
public:
	EventPlayerHillUpdate();
	~EventPlayerHillUpdate();
	int playerid;
};

