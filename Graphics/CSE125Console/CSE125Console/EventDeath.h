#ifndef CSE125Death
#define CSE125Death
#include "EventInfo.h"
class EventDeath : public EventInfo
{
public:
	EventDeath();
	~EventDeath();
	int death_id;
	int killer_id;
	float x;
	float y;
	float z;
};

#endif

