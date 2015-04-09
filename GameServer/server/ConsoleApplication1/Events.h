#pragma once
#include <string>
#include "NetworkData.h"

class Events
{
	unsigned int _event_type;
	unsigned int _cid;
	std::string _name;

public:
	Events(unsigned int type);
	~Events();
	void setCid(unsigned int cid);
	void setName(std::string name);
	unsigned int getEvent();
	unsigned int getCid();
	std::string getName();


};

