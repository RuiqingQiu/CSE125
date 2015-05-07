#ifndef CSE125Death
#define CSE125Death
#include "EventInfo.h"
class EventDeath : public EventInfo
{
public:
	EventDeath();
	~EventDeath();
	int cid;
};

#endif

