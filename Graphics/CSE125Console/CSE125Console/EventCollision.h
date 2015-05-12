#pragma once
#include "EventInfo.h"
class EventCollision :
	public EventInfo
{
public:
	int collision_type;
	float x;
	float y;
	float z;
	EventCollision();
	~EventCollision();
};

