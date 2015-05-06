#pragma once
#include <string>
#include "NetworkData.h"

#include <vector>
#include "GameObj.h"
class ObjectEvents
{
	unsigned int _event_type;
	unsigned int _cid;
	std::string _name;

public:
	ObjectEvents(unsigned int type);
	~ObjectEvents();
	void setCid(unsigned int cid);
	void setName(std::string name);
	unsigned int getEvent();
	unsigned int getCid();
	std::string getName();

	std::vector<GameObj *> roboBuild;
};

