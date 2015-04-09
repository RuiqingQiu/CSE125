#include "stdafx.h"
#include "PlayerInfo.h"


PlayerInfo::PlayerInfo()
{
}


PlayerInfo::~PlayerInfo()
{
}

void PlayerInfo::print(){
	std::cout << "object with id: " << id << " is at (" << x << ", " << y << ", " << z << ")" << std::endl;
}