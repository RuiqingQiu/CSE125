#pragma once
#include "EventInfo.h"
class EventParticle :
	public EventInfo
{
public:
	int particle_id;
	float x;
	float y;
	float z;
	EventParticle();
	~EventParticle();
};

