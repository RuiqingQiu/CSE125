#pragma once
#include "EventInfo.h"
class EventTimer :
	public EventInfo
{
public:
	int time;
	EventTimer();
	~EventTimer();
};

