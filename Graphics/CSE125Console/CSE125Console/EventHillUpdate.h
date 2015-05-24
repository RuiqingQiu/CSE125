#pragma once
#include "EventInfo.h"
class EventHillUpdate :
	public EventInfo
{
public:
	EventHillUpdate();
	~EventHillUpdate();
	float x;
	float y;
	float z;
	float radius;
};

