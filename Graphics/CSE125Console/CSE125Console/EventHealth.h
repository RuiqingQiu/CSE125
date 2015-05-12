#pragma once
#include "EventInfo.h"
class EventHealth :
	public EventInfo
{
public:
	int player1id;
	int health;
	int maxhealth;

	EventHealth();
	~EventHealth();
};

