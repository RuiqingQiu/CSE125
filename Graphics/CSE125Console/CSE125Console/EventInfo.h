
#ifndef CSE125_EVENTINFO
#define CSE125_EVENTINFO

#include "Definition.h"
class EventInfo
{
public:
	EventInfo();
	~EventInfo();
	bool processed = false;
	TEventType event_type = TEventDefault;
};

#endif // !CSE125_EVENTINFO
