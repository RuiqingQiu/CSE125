#pragma once
#include "stdafx.h"
#ifndef __GamePlayer__
#define __GamePlayer__
#include <string>

class GamePlayer
{
public:
	int playerid;
	std::string name = "Thomas\n\0";
	GamePlayer();
	~GamePlayer();
};
#endif

