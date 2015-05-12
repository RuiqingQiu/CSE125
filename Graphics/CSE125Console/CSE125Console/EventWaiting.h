#pragma once
#include "EventInfo.h"
class EventWaiting :
	public EventInfo
{
public:
	int number_of_players;
	EventWaiting();
	~EventWaiting();
};

